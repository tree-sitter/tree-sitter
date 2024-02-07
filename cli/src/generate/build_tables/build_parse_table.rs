use super::item::{ParseItem, ParseItemSet, ParseItemSetCore};
use super::item_set_builder::ParseItemSetBuilder;
use crate::generate::grammars::PrecedenceEntry;
use crate::generate::grammars::{
    InlinedProductionMap, LexicalGrammar, SyntaxGrammar, VariableType,
};
use crate::generate::node_types::VariableInfo;
use crate::generate::rules::{Associativity, Precedence, Symbol, SymbolType, TokenSet};
use crate::generate::tables::{
    FieldLocation, GotoAction, ParseAction, ParseState, ParseStateId, ParseTable, ParseTableEntry,
    ProductionInfo, ProductionInfoId,
};
use anyhow::{anyhow, Result};
use std::cmp::Ordering;
use std::collections::{BTreeMap, HashMap, HashSet, VecDeque};
use std::fmt::Write;
use std::hash::BuildHasherDefault;
use std::u32;

use indexmap::{map::Entry, IndexMap};
use rustc_hash::FxHasher;

// For conflict reporting, each parse state is associated with an example
// sequence of symbols that could lead to that parse state.
type SymbolSequence = Vec<Symbol>;

type AuxiliarySymbolSequence = Vec<AuxiliarySymbolInfo>;
pub type ParseStateInfo<'a> = (SymbolSequence, ParseItemSet<'a>);

#[derive(Clone)]
struct AuxiliarySymbolInfo {
    auxiliary_symbol: Symbol,
    parent_symbols: Vec<Symbol>,
}

#[derive(Debug, Default)]
struct ReductionInfo {
    precedence: Precedence,
    symbols: Vec<Symbol>,
    has_left_assoc: bool,
    has_right_assoc: bool,
    has_non_assoc: bool,
}

struct ParseStateQueueEntry {
    state_id: ParseStateId,
    preceding_auxiliary_symbols: AuxiliarySymbolSequence,
}

struct ParseTableBuilder<'a> {
    item_set_builder: ParseItemSetBuilder<'a>,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    variable_info: &'a [VariableInfo],
    core_ids_by_core: HashMap<ParseItemSetCore<'a>, usize>,
    state_ids_by_item_set: IndexMap<ParseItemSet<'a>, ParseStateId, BuildHasherDefault<FxHasher>>,
    parse_state_info_by_id: Vec<ParseStateInfo<'a>>,
    parse_state_queue: VecDeque<ParseStateQueueEntry>,
    non_terminal_extra_states: Vec<(Symbol, usize)>,
    actual_conflicts: HashSet<Vec<Symbol>>,
    parse_table: ParseTable,
}

impl<'a> ParseTableBuilder<'a> {
    fn build(mut self) -> Result<(ParseTable, Vec<ParseStateInfo<'a>>)> {
        // Ensure that the empty alias sequence has index 0.
        self.parse_table
            .production_infos
            .push(ProductionInfo::default());

        // Add the error state at index 0.
        self.add_parse_state(&Vec::new(), &Vec::new(), ParseItemSet::default());

        // Add the starting state at index 1.
        self.add_parse_state(
            &Vec::new(),
            &Vec::new(),
            ParseItemSet::with(std::iter::once((
                ParseItem::start(),
                std::iter::once(&Symbol::end()).copied().collect(),
            ))),
        );

        // Compute the possible item sets for non-terminal extras.
        let mut non_terminal_extra_item_sets_by_first_terminal = BTreeMap::new();
        for extra_non_terminal in self
            .syntax_grammar
            .extra_symbols
            .iter()
            .filter(|s| s.is_non_terminal())
        {
            let variable = &self.syntax_grammar.variables[extra_non_terminal.index];
            for production in &variable.productions {
                non_terminal_extra_item_sets_by_first_terminal
                    .entry(production.first_symbol().unwrap())
                    .or_insert_with(ParseItemSet::default)
                    .insert(
                        ParseItem {
                            variable_index: extra_non_terminal.index as u32,
                            production,
                            step_index: 1,
                            has_preceding_inherited_fields: false,
                        },
                        &std::iter::once(&Symbol::end_of_nonterminal_extra())
                            .copied()
                            .collect(),
                    );
            }
        }

        // Add a state for each starting terminal of a non-terminal extra rule.
        for (terminal, item_set) in non_terminal_extra_item_sets_by_first_terminal {
            self.non_terminal_extra_states
                .push((terminal, self.parse_table.states.len()));
            self.add_parse_state(&Vec::new(), &Vec::new(), item_set);
        }

        while let Some(entry) = self.parse_state_queue.pop_front() {
            let item_set = self
                .item_set_builder
                .transitive_closure(&self.parse_state_info_by_id[entry.state_id].1);

            self.add_actions(
                self.parse_state_info_by_id[entry.state_id].0.clone(),
                entry.preceding_auxiliary_symbols,
                entry.state_id,
                &item_set,
            )?;
        }

        if !self.actual_conflicts.is_empty() {
            println!("Warning: unnecessary conflicts");
            for conflict in &self.actual_conflicts {
                println!(
                    "  {}",
                    conflict
                        .iter()
                        .map(|symbol| format!("`{}`", self.symbol_name(symbol)))
                        .collect::<Vec<_>>()
                        .join(", ")
                );
            }
        }

        Ok((self.parse_table, self.parse_state_info_by_id))
    }

    fn add_parse_state(
        &mut self,
        preceding_symbols: &SymbolSequence,
        preceding_auxiliary_symbols: &AuxiliarySymbolSequence,
        item_set: ParseItemSet<'a>,
    ) -> ParseStateId {
        match self.state_ids_by_item_set.entry(item_set) {
            // If an equivalent item set has already been processed, then return
            // the existing parse state index.
            Entry::Occupied(o) => *o.get(),

            // Otherwise, insert a new parse state and add it to the queue of
            // parse states to populate.
            Entry::Vacant(v) => {
                let core = v.key().core();
                let core_count = self.core_ids_by_core.len();
                let core_id = *self.core_ids_by_core.entry(core).or_insert(core_count);

                let state_id = self.parse_table.states.len();
                self.parse_state_info_by_id
                    .push((preceding_symbols.clone(), v.key().clone()));

                self.parse_table.states.push(ParseState {
                    id: state_id,
                    lex_state_id: 0,
                    external_lex_state_id: 0,
                    terminal_entries: IndexMap::default(),
                    nonterminal_entries: IndexMap::default(),
                    core_id,
                });
                self.parse_state_queue.push_back(ParseStateQueueEntry {
                    state_id,
                    preceding_auxiliary_symbols: preceding_auxiliary_symbols.clone(),
                });
                v.insert(state_id);
                state_id
            }
        }
    }

    fn add_actions(
        &mut self,
        mut preceding_symbols: SymbolSequence,
        mut preceding_auxiliary_symbols: Vec<AuxiliarySymbolInfo>,
        state_id: ParseStateId,
        item_set: &ParseItemSet<'a>,
    ) -> Result<()> {
        let mut terminal_successors = BTreeMap::new();
        let mut non_terminal_successors = BTreeMap::new();
        let mut lookaheads_with_conflicts = TokenSet::new();
        let mut reduction_infos = HashMap::<Symbol, ReductionInfo>::new();

        // Each item in the item set contributes to either or a Shift action or a Reduce
        // action in this state.
        for (item, lookaheads) in &item_set.entries {
            // If the item is unfinished, then this state has a transition for the item's
            // next symbol. Advance the item to its next step and insert the resulting
            // item into the successor item set.
            if let Some(next_symbol) = item.symbol() {
                let mut successor = item.successor();
                if next_symbol.is_non_terminal() {
                    let variable = &self.syntax_grammar.variables[next_symbol.index];

                    // Keep track of where auxiliary non-terminals (repeat symbols) are
                    // used within visible symbols. This information may be needed later
                    // for conflict resolution.
                    if variable.is_auxiliary() {
                        preceding_auxiliary_symbols
                            .push(self.get_auxiliary_node_info(item_set, next_symbol));
                    }

                    // For most parse items, the symbols associated with the preceding children
                    // don't matter: they have no effect on the REDUCE action that would be
                    // performed at the end of the item. But the symbols *do* matter for
                    // children that are hidden and have fields, because those fields are
                    // "inherited" by the parent node.
                    //
                    // If this item has consumed a hidden child with fields, then the symbols
                    // of its preceding children need to be taken into account when comparing
                    // it with other items.
                    if variable.is_hidden()
                        && !self.variable_info[next_symbol.index].fields.is_empty()
                    {
                        successor.has_preceding_inherited_fields = true;
                    }

                    non_terminal_successors
                        .entry(next_symbol)
                        .or_insert_with(ParseItemSet::default)
                        .insert(successor, lookaheads);
                } else {
                    terminal_successors
                        .entry(next_symbol)
                        .or_insert_with(ParseItemSet::default)
                        .insert(successor, lookaheads);
                }
            }
            // If the item is finished, then add a Reduce action to this state based
            // on this item.
            else {
                let symbol = Symbol::non_terminal(item.variable_index as usize);
                let action = if item.is_augmented() {
                    ParseAction::Accept
                } else {
                    ParseAction::Reduce {
                        symbol,
                        child_count: item.step_index as usize,
                        dynamic_precedence: item.production.dynamic_precedence,
                        production_id: self.get_production_id(item),
                    }
                };

                let precedence = item.precedence();
                let associativity = item.associativity();
                for lookahead in lookaheads.iter() {
                    let table_entry = self.parse_table.states[state_id]
                        .terminal_entries
                        .entry(lookahead)
                        .or_insert_with(ParseTableEntry::new);
                    let reduction_info = reduction_infos.entry(lookahead).or_default();

                    // While inserting Reduce actions, eagerly resolve conflicts related
                    // to precedence: avoid inserting lower-precedence reductions, and
                    // clear the action list when inserting higher-precedence reductions.
                    if table_entry.actions.is_empty() {
                        table_entry.actions.push(action);
                    } else {
                        match Self::compare_precedence(
                            self.syntax_grammar,
                            precedence,
                            &[symbol],
                            &reduction_info.precedence,
                            &reduction_info.symbols,
                        ) {
                            Ordering::Greater => {
                                table_entry.actions.clear();
                                table_entry.actions.push(action);
                                lookaheads_with_conflicts.remove(&lookahead);
                                *reduction_info = ReductionInfo::default();
                            }
                            Ordering::Equal => {
                                table_entry.actions.push(action);
                                lookaheads_with_conflicts.insert(lookahead);
                            }
                            Ordering::Less => continue,
                        }
                    }

                    reduction_info.precedence = precedence.clone();
                    if let Err(i) = reduction_info.symbols.binary_search(&symbol) {
                        reduction_info.symbols.insert(i, symbol);
                    }
                    match associativity {
                        Some(Associativity::Left) => reduction_info.has_left_assoc = true,
                        Some(Associativity::Right) => reduction_info.has_right_assoc = true,
                        None => reduction_info.has_non_assoc = true,
                    }
                }
            }
        }

        // Having computed the the successor item sets for each symbol, add a new
        // parse state for each of these item sets, and add a corresponding Shift
        // action to this state.
        for (symbol, next_item_set) in terminal_successors {
            preceding_symbols.push(symbol);
            let next_state_id = self.add_parse_state(
                &preceding_symbols,
                &preceding_auxiliary_symbols,
                next_item_set,
            );
            preceding_symbols.pop();

            let entry = self.parse_table.states[state_id]
                .terminal_entries
                .entry(symbol);
            if let Entry::Occupied(e) = &entry {
                if !e.get().actions.is_empty() {
                    lookaheads_with_conflicts.insert(symbol);
                }
            }

            entry
                .or_insert_with(ParseTableEntry::new)
                .actions
                .push(ParseAction::Shift {
                    state: next_state_id,
                    is_repetition: false,
                });
        }

        for (symbol, next_item_set) in non_terminal_successors {
            preceding_symbols.push(symbol);
            let next_state_id = self.add_parse_state(
                &preceding_symbols,
                &preceding_auxiliary_symbols,
                next_item_set,
            );
            preceding_symbols.pop();
            self.parse_table.states[state_id]
                .nonterminal_entries
                .insert(symbol, GotoAction::Goto(next_state_id));
        }

        // For any symbol with multiple actions, perform conflict resolution.
        // This will either
        // * choose one action over the others using precedence or associativity
        // * keep multiple actions if this conflict has been whitelisted in the grammar
        // * fail, terminating the parser generation process
        for symbol in lookaheads_with_conflicts.iter() {
            self.handle_conflict(
                item_set,
                state_id,
                &preceding_symbols,
                &preceding_auxiliary_symbols,
                symbol,
                reduction_infos.get(&symbol).unwrap(),
            )?;
        }

        // Finally, add actions for the grammar's `extra` symbols.
        let state = &mut self.parse_table.states[state_id];
        let is_end_of_non_terminal_extra = state.is_end_of_non_terminal_extra();

        // If this state represents the end of a non-terminal extra rule, then make sure that
        // it doesn't have other successor states. Non-terminal extra rules must have
        // unambiguous endings.
        if is_end_of_non_terminal_extra {
            if state.terminal_entries.len() > 1 {
                let parent_symbols = item_set
                    .entries
                    .iter()
                    .filter_map(|(item, _)| {
                        if !item.is_augmented() && item.step_index > 0 {
                            Some(item.variable_index)
                        } else {
                            None
                        }
                    })
                    .collect::<HashSet<_>>();
                let mut message =
                    "Extra rules must have unambiguous endings. Conflicting rules: ".to_string();
                for (i, variable_index) in parent_symbols.iter().enumerate() {
                    if i > 0 {
                        message += ", ";
                    }
                    message += &self.syntax_grammar.variables[*variable_index as usize].name;
                }
                return Err(anyhow!(message));
            }
        }
        // Add actions for the start tokens of each non-terminal extra rule.
        else {
            for (terminal, state_id) in &self.non_terminal_extra_states {
                state
                    .terminal_entries
                    .entry(*terminal)
                    .or_insert(ParseTableEntry {
                        reusable: true,
                        actions: vec![ParseAction::Shift {
                            state: *state_id,
                            is_repetition: false,
                        }],
                    });
            }

            // Add ShiftExtra actions for the terminal extra tokens. These actions
            // are added to every state except for those at the ends of non-terminal
            // extras.
            for extra_token in &self.syntax_grammar.extra_symbols {
                if extra_token.is_non_terminal() {
                    state
                        .nonterminal_entries
                        .insert(*extra_token, GotoAction::ShiftExtra);
                } else {
                    state
                        .terminal_entries
                        .entry(*extra_token)
                        .or_insert(ParseTableEntry {
                            reusable: true,
                            actions: vec![ParseAction::ShiftExtra],
                        });
                }
            }
        }

        Ok(())
    }

    fn handle_conflict(
        &mut self,
        item_set: &ParseItemSet,
        state_id: ParseStateId,
        preceding_symbols: &SymbolSequence,
        preceding_auxiliary_symbols: &[AuxiliarySymbolInfo],
        conflicting_lookahead: Symbol,
        reduction_info: &ReductionInfo,
    ) -> Result<()> {
        let entry = self.parse_table.states[state_id]
            .terminal_entries
            .get_mut(&conflicting_lookahead)
            .unwrap();

        // Determine which items in the set conflict with each other, and the
        // precedences associated with SHIFT vs REDUCE actions. There won't
        // be multiple REDUCE actions with different precedences; that is
        // sorted out ahead of time in `add_actions`. But there can still be
        // REDUCE-REDUCE conflicts where all actions have the *same*
        // precedence, and there can still be SHIFT/REDUCE conflicts.
        let mut considered_associativity = false;
        let mut shift_precedence: Vec<(&Precedence, Symbol)> = Vec::new();
        let mut conflicting_items = HashSet::new();
        for (item, lookaheads) in &item_set.entries {
            if let Some(step) = item.step() {
                if item.step_index > 0
                    && self
                        .item_set_builder
                        .first_set(&step.symbol)
                        .contains(&conflicting_lookahead)
                {
                    if item.variable_index != u32::MAX {
                        conflicting_items.insert(item);
                    }

                    let p = (
                        item.precedence(),
                        Symbol::non_terminal(item.variable_index as usize),
                    );
                    if let Err(i) = shift_precedence.binary_search(&p) {
                        shift_precedence.insert(i, p);
                    }
                }
            } else if lookaheads.contains(&conflicting_lookahead) && item.variable_index != u32::MAX
            {
                conflicting_items.insert(item);
            }
        }

        if let ParseAction::Shift { is_repetition, .. } = entry.actions.last_mut().unwrap() {
            // If all of the items in the conflict have the same parent symbol,
            // and that parent symbols is auxiliary, then this is just the intentional
            // ambiguity associated with a repeat rule. Resolve that class of ambiguity
            // by leaving it in the parse table, but marking the SHIFT action with
            // an `is_repetition` flag.
            let conflicting_variable_index =
                conflicting_items.iter().next().unwrap().variable_index;
            if self.syntax_grammar.variables[conflicting_variable_index as usize].is_auxiliary()
                && conflicting_items
                    .iter()
                    .all(|item| item.variable_index == conflicting_variable_index)
            {
                *is_repetition = true;
                return Ok(());
            }

            // If the SHIFT action has higher precedence, remove all the REDUCE actions.
            let mut shift_is_less = false;
            let mut shift_is_more = false;
            for p in shift_precedence {
                match Self::compare_precedence(
                    self.syntax_grammar,
                    p.0,
                    &[p.1],
                    &reduction_info.precedence,
                    &reduction_info.symbols,
                ) {
                    Ordering::Greater => shift_is_more = true,
                    Ordering::Less => shift_is_less = true,
                    Ordering::Equal => {}
                }
            }

            if shift_is_more && !shift_is_less {
                entry.actions.drain(0..entry.actions.len() - 1);
            }
            // If the REDUCE actions have higher precedence, remove the SHIFT action.
            else if shift_is_less && !shift_is_more {
                entry.actions.pop();
                conflicting_items.retain(|item| item.is_done());
            }
            // If the SHIFT and REDUCE actions have the same predence, consider
            // the REDUCE actions' associativity.
            else if !shift_is_less && !shift_is_more {
                considered_associativity = true;

                // If all Reduce actions are left associative, remove the SHIFT action.
                // If all Reduce actions are right associative, remove the REDUCE actions.
                match (
                    reduction_info.has_left_assoc,
                    reduction_info.has_non_assoc,
                    reduction_info.has_right_assoc,
                ) {
                    (true, false, false) => {
                        entry.actions.pop();
                        conflicting_items.retain(|item| item.is_done());
                    }
                    (false, false, true) => {
                        entry.actions.drain(0..entry.actions.len() - 1);
                    }
                    _ => {}
                }
            }
        }

        // If all of the actions but one have been eliminated, then there's no problem.
        let entry = self.parse_table.states[state_id]
            .terminal_entries
            .get_mut(&conflicting_lookahead)
            .unwrap();
        if entry.actions.len() == 1 {
            return Ok(());
        }

        // Determine the set of parent symbols involved in this conflict.
        let mut actual_conflict = Vec::new();
        for item in &conflicting_items {
            let symbol = Symbol::non_terminal(item.variable_index as usize);
            if self.syntax_grammar.variables[symbol.index].is_auxiliary() {
                actual_conflict.extend(
                    preceding_auxiliary_symbols
                        .iter()
                        .rev()
                        .find_map(|info| {
                            if info.auxiliary_symbol == symbol {
                                Some(&info.parent_symbols)
                            } else {
                                None
                            }
                        })
                        .unwrap()
                        .iter(),
                );
            } else {
                actual_conflict.push(symbol);
            }
        }
        actual_conflict.sort_unstable();
        actual_conflict.dedup();

        // If this set of symbols has been whitelisted, then there's no error.
        if self
            .syntax_grammar
            .expected_conflicts
            .contains(&actual_conflict)
        {
            self.actual_conflicts.remove(&actual_conflict);
            return Ok(());
        }

        let mut msg = "Unresolved conflict for symbol sequence:\n\n".to_string();
        for symbol in preceding_symbols {
            write!(&mut msg, "  {}", self.symbol_name(symbol)).unwrap();
        }

        write!(
            &mut msg,
            "  •  {}  …\n\n",
            self.symbol_name(&conflicting_lookahead)
        )
        .unwrap();
        write!(&mut msg, "Possible interpretations:\n\n").unwrap();

        let mut interpretations = conflicting_items
            .iter()
            .map(|item| {
                let mut line = String::new();
                for preceding_symbol in preceding_symbols
                    .iter()
                    .take(preceding_symbols.len() - item.step_index as usize)
                {
                    write!(&mut line, "  {}", self.symbol_name(preceding_symbol)).unwrap();
                }

                write!(
                    &mut line,
                    "  ({}",
                    &self.syntax_grammar.variables[item.variable_index as usize].name
                )
                .unwrap();

                for (j, step) in item.production.steps.iter().enumerate() {
                    if j as u32 == item.step_index {
                        write!(&mut line, "  •").unwrap();
                    }
                    write!(&mut line, "  {}", self.symbol_name(&step.symbol)).unwrap();
                }

                write!(&mut line, ")").unwrap();

                if item.is_done() {
                    write!(
                        &mut line,
                        "  •  {}  …",
                        self.symbol_name(&conflicting_lookahead)
                    )
                    .unwrap();
                }

                let precedence = item.precedence();
                let associativity = item.associativity();

                let prec_line = if let Some(associativity) = associativity {
                    Some(format!(
                        "(precedence: {precedence}, associativity: {associativity:?})",
                    ))
                } else if !precedence.is_none() {
                    Some(format!("(precedence: {precedence})"))
                } else {
                    None
                };

                (line, prec_line)
            })
            .collect::<Vec<_>>();

        let max_interpretation_length = interpretations
            .iter()
            .map(|i| i.0.chars().count())
            .max()
            .unwrap();
        interpretations.sort_unstable();
        for (i, (line, prec_suffix)) in interpretations.into_iter().enumerate() {
            write!(&mut msg, "  {}:", i + 1).unwrap();
            msg += &line;
            if let Some(prec_suffix) = prec_suffix {
                for _ in line.chars().count()..max_interpretation_length {
                    msg.push(' ');
                }
                msg += "  ";
                msg += &prec_suffix;
            }
            msg.push('\n');
        }

        let mut resolution_count = 0;
        write!(&mut msg, "\nPossible resolutions:\n\n").unwrap();
        let mut shift_items = Vec::new();
        let mut reduce_items = Vec::new();
        for item in conflicting_items {
            if item.is_done() {
                reduce_items.push(item);
            } else {
                shift_items.push(item);
            }
        }
        shift_items.sort_unstable();
        reduce_items.sort_unstable();

        let list_rule_names = |mut msg: &mut String, items: &[&ParseItem]| {
            let mut last_rule_id = None;
            for item in items {
                if last_rule_id == Some(item.variable_index) {
                    continue;
                }

                if last_rule_id.is_some() {
                    write!(&mut msg, " and").unwrap();
                }

                last_rule_id = Some(item.variable_index);
                write!(
                    msg,
                    " `{}`",
                    self.symbol_name(&Symbol::non_terminal(item.variable_index as usize))
                )
                .unwrap();
            }
        };

        if actual_conflict.len() > 1 {
            if !shift_items.is_empty() {
                resolution_count += 1;
                write!(
                    &mut msg,
                    "  {resolution_count}:  Specify a higher precedence in",
                )
                .unwrap();
                list_rule_names(&mut msg, &shift_items);
                writeln!(&mut msg, " than in the other rules.").unwrap();
            }

            for item in &reduce_items {
                resolution_count += 1;
                writeln!(
                    &mut msg,
                    "  {resolution_count}:  Specify a higher precedence in `{}` than in the other rules.",
                    self.symbol_name(&Symbol::non_terminal(item.variable_index as usize))
                )
                .unwrap();
            }
        }

        if considered_associativity {
            resolution_count += 1;
            write!(
                &mut msg,
                "  {resolution_count}:  Specify a left or right associativity in",
            )
            .unwrap();
            list_rule_names(&mut msg, &reduce_items);
            writeln!(&mut msg).unwrap();
        }

        resolution_count += 1;
        write!(
            &mut msg,
            "  {resolution_count}:  Add a conflict for these rules: ",
        )
        .unwrap();
        for (i, symbol) in actual_conflict.iter().enumerate() {
            if i > 0 {
                write!(&mut msg, ", ").unwrap();
            }
            write!(&mut msg, "`{}`", self.symbol_name(symbol)).unwrap();
        }
        writeln!(&mut msg).unwrap();

        Err(anyhow!(msg))
    }

    fn compare_precedence(
        grammar: &SyntaxGrammar,
        left: &Precedence,
        left_symbols: &[Symbol],
        right: &Precedence,
        right_symbols: &[Symbol],
    ) -> Ordering {
        let precedence_entry_matches =
            |entry: &PrecedenceEntry, precedence: &Precedence, symbols: &[Symbol]| -> bool {
                match entry {
                    PrecedenceEntry::Name(n) => {
                        if let Precedence::Name(p) = precedence {
                            n == p
                        } else {
                            false
                        }
                    }
                    PrecedenceEntry::Symbol(n) => symbols
                        .iter()
                        .any(|s| &grammar.variables[s.index].name == n),
                }
            };

        match (left, right) {
            // Integer precedences can be compared to other integer precedences,
            // and to the default precedence, which is zero.
            (Precedence::Integer(l), Precedence::Integer(r)) if *l != 0 || *r != 0 => l.cmp(r),
            (Precedence::Integer(l), Precedence::None) if *l != 0 => l.cmp(&0),
            (Precedence::None, Precedence::Integer(r)) if *r != 0 => 0.cmp(r),

            // Named precedences can be compared to other named precedences.
            _ => grammar
                .precedence_orderings
                .iter()
                .find_map(|list| {
                    let mut saw_left = false;
                    let mut saw_right = false;
                    for entry in list {
                        let matches_left = precedence_entry_matches(entry, left, left_symbols);
                        let matches_right = precedence_entry_matches(entry, right, right_symbols);
                        if matches_left {
                            saw_left = true;
                            if saw_right {
                                return Some(Ordering::Less);
                            }
                        } else if matches_right {
                            saw_right = true;
                            if saw_left {
                                return Some(Ordering::Greater);
                            }
                        }
                    }
                    None
                })
                .unwrap_or(Ordering::Equal),
        }
    }

    fn get_auxiliary_node_info(
        &self,
        item_set: &ParseItemSet,
        symbol: Symbol,
    ) -> AuxiliarySymbolInfo {
        let parent_symbols = item_set
            .entries
            .iter()
            .filter_map(|(item, _)| {
                let variable_index = item.variable_index as usize;
                if item.symbol() == Some(symbol)
                    && !self.syntax_grammar.variables[variable_index].is_auxiliary()
                {
                    Some(Symbol::non_terminal(variable_index))
                } else {
                    None
                }
            })
            .collect();
        AuxiliarySymbolInfo {
            auxiliary_symbol: symbol,
            parent_symbols,
        }
    }

    fn get_production_id(&mut self, item: &ParseItem) -> ProductionInfoId {
        let mut production_info = ProductionInfo {
            alias_sequence: Vec::new(),
            field_map: BTreeMap::new(),
        };

        for (i, step) in item.production.steps.iter().enumerate() {
            production_info.alias_sequence.push(step.alias.clone());
            if let Some(field_name) = &step.field_name {
                production_info
                    .field_map
                    .entry(field_name.clone())
                    .or_default()
                    .push(FieldLocation {
                        index: i,
                        inherited: false,
                    });
            }

            if step.symbol.kind == SymbolType::NonTerminal
                && !self.syntax_grammar.variables[step.symbol.index]
                    .kind
                    .is_visible()
            {
                let info = &self.variable_info[step.symbol.index];
                for field_name in info.fields.keys() {
                    production_info
                        .field_map
                        .entry(field_name.clone())
                        .or_default()
                        .push(FieldLocation {
                            index: i,
                            inherited: true,
                        });
                }
            }
        }

        while production_info.alias_sequence.last() == Some(&None) {
            production_info.alias_sequence.pop();
        }

        if item.production.steps.len() > self.parse_table.max_aliased_production_length {
            self.parse_table.max_aliased_production_length = item.production.steps.len();
        }

        if let Some(index) = self
            .parse_table
            .production_infos
            .iter()
            .position(|seq| *seq == production_info)
        {
            index
        } else {
            self.parse_table.production_infos.push(production_info);
            self.parse_table.production_infos.len() - 1
        }
    }

    fn symbol_name(&self, symbol: &Symbol) -> String {
        match symbol.kind {
            SymbolType::End | SymbolType::EndOfNonTerminalExtra => "EOF".to_string(),
            SymbolType::External => self.syntax_grammar.external_tokens[symbol.index]
                .name
                .clone(),
            SymbolType::NonTerminal => self.syntax_grammar.variables[symbol.index].name.clone(),
            SymbolType::Terminal => {
                let variable = &self.lexical_grammar.variables[symbol.index];
                if variable.kind == VariableType::Named {
                    variable.name.clone()
                } else {
                    format!("'{}'", &variable.name)
                }
            }
        }
    }
}

fn populate_following_tokens(
    result: &mut [TokenSet],
    grammar: &SyntaxGrammar,
    inlines: &InlinedProductionMap,
    builder: &ParseItemSetBuilder,
) {
    let productions = grammar
        .variables
        .iter()
        .flat_map(|v| &v.productions)
        .chain(&inlines.productions);
    let all_tokens = (0..result.len())
        .map(Symbol::terminal)
        .collect::<TokenSet>();
    for production in productions {
        for i in 1..production.steps.len() {
            let left_tokens = builder.last_set(&production.steps[i - 1].symbol);
            let right_tokens = builder.first_set(&production.steps[i].symbol);
            for left_token in left_tokens.iter() {
                if left_token.is_terminal() {
                    result[left_token.index].insert_all_terminals(right_tokens);
                }
            }
        }
    }
    for extra in &grammar.extra_symbols {
        if extra.is_terminal() {
            for entry in result.iter_mut() {
                entry.insert(*extra);
            }
            result[extra.index] = all_tokens.clone();
        }
    }
}

pub fn build_parse_table<'a>(
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    inlines: &'a InlinedProductionMap,
    variable_info: &'a [VariableInfo],
) -> Result<(ParseTable, Vec<TokenSet>, Vec<ParseStateInfo<'a>>)> {
    let actual_conflicts = syntax_grammar.expected_conflicts.iter().cloned().collect();
    let item_set_builder = ParseItemSetBuilder::new(syntax_grammar, lexical_grammar, inlines);
    let mut following_tokens = vec![TokenSet::new(); lexical_grammar.variables.len()];
    populate_following_tokens(
        &mut following_tokens,
        syntax_grammar,
        inlines,
        &item_set_builder,
    );

    let (table, item_sets) = ParseTableBuilder {
        syntax_grammar,
        lexical_grammar,
        item_set_builder,
        variable_info,
        non_terminal_extra_states: Vec::new(),
        actual_conflicts,
        state_ids_by_item_set: IndexMap::default(),
        core_ids_by_core: HashMap::new(),
        parse_state_info_by_id: Vec::new(),
        parse_state_queue: VecDeque::new(),
        parse_table: ParseTable {
            states: Vec::new(),
            symbols: Vec::new(),
            external_lex_states: Vec::new(),
            production_infos: Vec::new(),
            max_aliased_production_length: 1,
        },
    }
    .build()?;

    Ok((table, following_tokens, item_sets))
}
