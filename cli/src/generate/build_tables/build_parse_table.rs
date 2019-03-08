use super::item::{ParseItem, ParseItemSet, TokenSet};
use super::item_set_builder::ParseItemSetBuilder;
use crate::error::{Error, Result};
use crate::generate::grammars::{
    InlinedProductionMap, LexicalGrammar, SyntaxGrammar, VariableType,
};
use crate::generate::rules::{Associativity, Symbol, SymbolType};
use crate::generate::tables::{
    ChildType, FieldInfo, FieldLocation, ParseAction, ParseState, ParseStateId, ParseTable,
    ParseTableEntry, ProductionInfo, ProductionInfoId, VariableInfo,
};
use core::ops::Range;
use hashbrown::hash_map::Entry;
use hashbrown::{HashMap, HashSet};
use std::collections::hash_map::DefaultHasher;
use std::collections::{BTreeMap, VecDeque};
use std::fmt::Write;
use std::hash::Hasher;
use std::{mem, u32};

#[derive(Clone)]
struct AuxiliarySymbolInfo {
    auxiliary_symbol: Symbol,
    parent_symbols: Vec<Symbol>,
}

type SymbolSequence = Vec<Symbol>;
type AuxiliarySymbolSequence = Vec<AuxiliarySymbolInfo>;

struct ParseStateQueueEntry {
    preceding_symbols: SymbolSequence,
    preceding_auxiliary_symbols: AuxiliarySymbolSequence,
    state_id: ParseStateId,
}

struct ParseTableBuilder<'a> {
    item_set_builder: ParseItemSetBuilder<'a>,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    state_ids_by_item_set: HashMap<ParseItemSet<'a>, ParseStateId>,
    item_sets_by_state_id: Vec<ParseItemSet<'a>>,
    parse_state_queue: VecDeque<ParseStateQueueEntry>,
    parse_table: ParseTable,
    state_ids_to_log: Vec<ParseStateId>,
}

impl<'a> ParseTableBuilder<'a> {
    fn build(mut self) -> Result<ParseTable> {
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
            ParseItemSet::with(
                [(
                    ParseItem::start(),
                    [Symbol::end()].iter().cloned().collect(),
                )]
                .iter()
                .cloned(),
            ),
        );

        while let Some(entry) = self.parse_state_queue.pop_front() {
            let item_set = self
                .item_set_builder
                .transitive_closure(&self.item_sets_by_state_id[entry.state_id]);

            if self.state_ids_to_log.contains(&entry.state_id) {
                eprintln!(
                    "state: {}\n\ninitial item set:\n\n{}closed item set:\n\n{}",
                    entry.state_id,
                    super::item::ParseItemSetDisplay(
                        &self.item_sets_by_state_id[entry.state_id],
                        self.syntax_grammar,
                        self.lexical_grammar,
                    ),
                    super::item::ParseItemSetDisplay(
                        &item_set,
                        self.syntax_grammar,
                        self.lexical_grammar,
                    )
                );
            }

            self.add_actions(
                entry.preceding_symbols,
                entry.preceding_auxiliary_symbols,
                entry.state_id,
                item_set,
            )?;
        }

        self.remove_precedences();

        Ok(self.parse_table)
    }

    fn add_parse_state(
        &mut self,
        preceding_symbols: &SymbolSequence,
        preceding_auxiliary_symbols: &AuxiliarySymbolSequence,
        item_set: ParseItemSet<'a>,
    ) -> ParseStateId {
        let mut hasher = DefaultHasher::new();
        item_set.hash_unfinished_items(&mut hasher);
        let unfinished_item_signature = hasher.finish();

        match self.state_ids_by_item_set.entry(item_set) {
            Entry::Occupied(o) => *o.get(),
            Entry::Vacant(v) => {
                let state_id = self.parse_table.states.len();
                self.item_sets_by_state_id.push(v.key().clone());
                self.parse_table.states.push(ParseState {
                    lex_state_id: 0,
                    terminal_entries: HashMap::new(),
                    nonterminal_entries: HashMap::new(),
                    unfinished_item_signature,
                });
                self.parse_state_queue.push_back(ParseStateQueueEntry {
                    state_id,
                    preceding_symbols: preceding_symbols.clone(),
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
        item_set: ParseItemSet<'a>,
    ) -> Result<()> {
        let mut terminal_successors = HashMap::new();
        let mut non_terminal_successors = HashMap::new();
        let mut lookaheads_with_conflicts = HashSet::new();

        for (item, lookaheads) in &item_set.entries {
            if let Some(next_symbol) = item.symbol() {
                let successor = item.successor();
                if next_symbol.is_non_terminal() {
                    // Keep track of where auxiliary non-terminals (repeat symbols) are
                    // used within visible symbols. This information may be needed later
                    // for conflict resolution.
                    if self.syntax_grammar.variables[next_symbol.index].is_auxiliary() {
                        preceding_auxiliary_symbols
                            .push(self.get_auxiliary_node_info(&item_set, next_symbol));
                    }

                    non_terminal_successors
                        .entry(next_symbol)
                        .or_insert_with(|| ParseItemSet::default())
                        .insert(successor, lookaheads);
                } else {
                    terminal_successors
                        .entry(next_symbol)
                        .or_insert_with(|| ParseItemSet::default())
                        .insert(successor, lookaheads);
                }
            } else {
                let action = if item.is_augmented() {
                    ParseAction::Accept
                } else {
                    ParseAction::Reduce {
                        symbol: Symbol::non_terminal(item.variable_index as usize),
                        child_count: item.step_index as usize,
                        precedence: item.precedence(),
                        associativity: item.associativity(),
                        dynamic_precedence: item.production.dynamic_precedence,
                        production_id: self.get_production_id(item),
                    }
                };

                for lookahead in lookaheads.iter() {
                    let entry = self.parse_table.states[state_id]
                        .terminal_entries
                        .entry(lookahead);
                    let entry = entry.or_insert_with(|| ParseTableEntry::new());
                    if entry.actions.is_empty() {
                        entry.actions.push(action);
                    } else if action.precedence() > entry.actions[0].precedence() {
                        entry.actions.clear();
                        entry.actions.push(action);
                        lookaheads_with_conflicts.remove(&lookahead);
                    } else if action.precedence() == entry.actions[0].precedence() {
                        entry.actions.push(action);
                        lookaheads_with_conflicts.insert(lookahead);
                    }
                }
            }
        }

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
                .or_insert_with(|| ParseTableEntry::new())
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
                .insert(symbol, next_state_id);
        }

        for symbol in lookaheads_with_conflicts {
            self.handle_conflict(
                &item_set,
                state_id,
                &preceding_symbols,
                &preceding_auxiliary_symbols,
                symbol,
            )?;
        }

        let state = &mut self.parse_table.states[state_id];
        for extra_token in &self.syntax_grammar.extra_tokens {
            state
                .terminal_entries
                .entry(*extra_token)
                .or_insert(ParseTableEntry {
                    reusable: true,
                    actions: vec![ParseAction::ShiftExtra],
                });
        }

        Ok(())
    }

    fn handle_conflict(
        &mut self,
        item_set: &ParseItemSet,
        state_id: ParseStateId,
        preceding_symbols: &SymbolSequence,
        preceding_auxiliary_symbols: &Vec<AuxiliarySymbolInfo>,
        conflicting_lookahead: Symbol,
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
        let reduce_precedence = entry.actions[0].precedence();
        let mut considered_associativity = false;
        let mut shift_precedence: Option<Range<i32>> = None;
        let mut conflicting_items = HashSet::new();
        for (item, lookaheads) in &item_set.entries {
            if let Some(step) = item.step() {
                if item.step_index > 0 {
                    if self
                        .item_set_builder
                        .first_set(&step.symbol)
                        .contains(&conflicting_lookahead)
                    {
                        if item.variable_index != u32::MAX {
                            conflicting_items.insert(item);
                        }

                        let precedence = item.precedence();
                        if let Some(range) = &mut shift_precedence {
                            if precedence < range.start {
                                range.start = precedence;
                            } else if precedence > range.end {
                                range.end = precedence;
                            }
                        } else {
                            shift_precedence = Some(precedence..precedence);
                        }
                    }
                }
            } else if lookaheads.contains(&conflicting_lookahead) {
                if item.variable_index != u32::MAX {
                    conflicting_items.insert(item);
                }
            }
        }

        if let ParseAction::Shift { is_repetition, .. } = entry.actions.last_mut().unwrap() {
            let shift_precedence = shift_precedence.unwrap_or(0..0);

            // If all of the items in the conflict have the same parent symbol,
            // and that parent symbols is auxiliary, then this is just the intentional
            // ambiguity associated with a repeat rule. Resolve that class of ambiguity
            // by leaving it in the parse table, but marking the SHIFT action with
            // an `is_repetition` flag.
            let conflicting_variable_index =
                conflicting_items.iter().next().unwrap().variable_index;
            if self.syntax_grammar.variables[conflicting_variable_index as usize].is_auxiliary() {
                if conflicting_items
                    .iter()
                    .all(|item| item.variable_index == conflicting_variable_index)
                {
                    *is_repetition = true;
                    return Ok(());
                }
            }

            // If the SHIFT action has higher precedence, remove all the REDUCE actions.
            if shift_precedence.start > reduce_precedence
                || (shift_precedence.start == reduce_precedence
                    && shift_precedence.end > reduce_precedence)
            {
                entry.actions.drain(0..entry.actions.len() - 1);
            }
            // If the REDUCE actions have higher precedence, remove the SHIFT action.
            else if shift_precedence.end < reduce_precedence
                || (shift_precedence.end == reduce_precedence
                    && shift_precedence.start < reduce_precedence)
            {
                entry.actions.pop();
                conflicting_items.retain(|item| item.is_done());
            }
            // If the SHIFT and REDUCE actions have the same predence, consider
            // the REDUCE actions' associativity.
            else if shift_precedence == (reduce_precedence..reduce_precedence) {
                considered_associativity = true;
                let mut has_left = false;
                let mut has_right = false;
                let mut has_non = false;
                for action in &entry.actions {
                    if let ParseAction::Reduce { associativity, .. } = action {
                        match associativity {
                            Some(Associativity::Left) => has_left = true,
                            Some(Associativity::Right) => has_right = true,
                            None => has_non = true,
                        }
                    }
                }

                // If all reduce actions are left associative, remove the SHIFT action.
                // If all reduce actions are right associative, remove the REDUCE actions.
                match (has_left, has_non, has_right) {
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

        let mut interpretions = conflicting_items
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
                        "(precedence: {}, associativity: {:?})",
                        precedence, associativity
                    ))
                } else if precedence > 0 {
                    Some(format!("(precedence: {})", precedence))
                } else {
                    None
                };

                (line, prec_line)
            })
            .collect::<Vec<_>>();

        let max_interpretation_length = interpretions
            .iter()
            .map(|i| i.0.chars().count())
            .max()
            .unwrap();
        interpretions.sort_unstable();
        for (i, (line, prec_suffix)) in interpretions.into_iter().enumerate() {
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
        let mut shift_items = conflicting_items
            .iter()
            .filter(|i| !i.is_done())
            .cloned()
            .collect::<Vec<_>>();
        shift_items.sort_unstable();
        if actual_conflict.len() > 1 {
            if shift_items.len() > 0 {
                resolution_count += 1;
                write!(
                    &mut msg,
                    "  {}:  Specify a higher precedence in",
                    resolution_count
                )
                .unwrap();
                for (i, item) in shift_items.iter().enumerate() {
                    if i > 0 {
                        write!(&mut msg, " and").unwrap();
                    }
                    write!(
                        &mut msg,
                        " `{}`",
                        self.symbol_name(&Symbol::non_terminal(item.variable_index as usize))
                    )
                    .unwrap();
                }
                write!(&mut msg, " than in the other rules.\n").unwrap();
            }

            for item in &conflicting_items {
                if item.is_done() {
                    resolution_count += 1;
                    write!(
                        &mut msg,
                        "  {}:  Specify a higher precedence in `{}` than in the other rules.\n",
                        resolution_count,
                        self.symbol_name(&Symbol::non_terminal(item.variable_index as usize))
                    )
                    .unwrap();
                }
            }
        }

        if considered_associativity {
            resolution_count += 1;
            write!(
                &mut msg,
                "  {}:  Specify a left or right associativity in ",
                resolution_count
            )
            .unwrap();
            for (i, item) in conflicting_items.iter().filter(|i| i.is_done()).enumerate() {
                if i > 0 {
                    write!(&mut msg, " and ").unwrap();
                }
                write!(
                    &mut msg,
                    "`{}`",
                    self.symbol_name(&Symbol::non_terminal(item.variable_index as usize))
                )
                .unwrap();
            }
            write!(&mut msg, "\n").unwrap();
        }

        resolution_count += 1;
        write!(
            &mut msg,
            "  {}:  Add a conflict for these rules: ",
            resolution_count
        )
        .unwrap();
        for (i, symbol) in actual_conflict.iter().enumerate() {
            if i > 0 {
                write!(&mut msg, ", ").unwrap();
            }
            write!(&mut msg, "`{}`", self.symbol_name(symbol)).unwrap();
        }
        write!(&mut msg, "\n").unwrap();

        Err(Error(msg))
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

    fn remove_precedences(&mut self) {
        for state in self.parse_table.states.iter_mut() {
            for (_, entry) in state.terminal_entries.iter_mut() {
                for action in entry.actions.iter_mut() {
                    match action {
                        ParseAction::Reduce {
                            precedence,
                            associativity,
                            ..
                        } => {
                            *precedence = 0;
                            *associativity = None;
                        }
                        _ => {}
                    }
                }
            }
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
                    .or_insert(Vec::new())
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
                let info = &self.parse_table.variable_info[step.symbol.index];
                for (field_name, _) in &info.fields {
                    production_info
                        .field_map
                        .entry(field_name.clone())
                        .or_insert(Vec::new())
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
            self.parse_table.max_aliased_production_length = item.production.steps.len()
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
            SymbolType::End => "EOF".to_string(),
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
    result: &mut Vec<TokenSet>,
    grammar: &SyntaxGrammar,
    inlines: &InlinedProductionMap,
    builder: &ParseItemSetBuilder,
) {
    let productions = grammar
        .variables
        .iter()
        .flat_map(|v| &v.productions)
        .chain(&inlines.productions);
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
}

pub(crate) fn get_variable_info(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
) -> Result<Vec<VariableInfo>> {
    let mut result = Vec::new();

    // Determine which field names and child node types can appear directly
    // within each type of node.
    for (i, variable) in syntax_grammar.variables.iter().enumerate() {
        let mut info = VariableInfo {
            fields: HashMap::new(),
            subclasses: Vec::new(),
            child_types: Vec::new(),
            has_multi_step_production: false,
        };
        let is_recursive = variable
            .productions
            .iter()
            .any(|p| p.steps.iter().any(|s| s.symbol == Symbol::non_terminal(i)));

        for production in &variable.productions {
            if production.steps.len() > 1 {
                info.has_multi_step_production = true;
            }

            for step in &production.steps {
                let child_type = if let Some(alias) = &step.alias {
                    ChildType::Aliased(alias.clone())
                } else {
                    ChildType::Normal(step.symbol)
                };

                if let Some(field_name) = &step.field_name {
                    let field_info = info.fields.entry(field_name.clone()).or_insert(FieldInfo {
                        multiple: false,
                        required: true,
                        types: Vec::new(),
                    });
                    field_info.multiple |= is_recursive;
                    if let Err(i) = field_info.types.binary_search(&child_type) {
                        field_info.types.insert(i, child_type.clone());
                    }
                }

                if let Err(i) = info.child_types.binary_search(&child_type) {
                    info.child_types.insert(i, child_type.clone());
                }
            }
        }

        for production in &variable.productions {
            let production_fields: Vec<&String> = production
                .steps
                .iter()
                .filter_map(|s| s.field_name.as_ref())
                .collect();
            for (field_name, field_info) in info.fields.iter_mut() {
                if !production_fields.contains(&field_name) {
                    field_info.required = false;
                }
            }
        }

        result.push(info);
    }

    // Expand each node type's information recursively to inherit the properties of
    // hidden children.
    let mut done = false;
    while !done {
        done = true;
        for (i, variable) in syntax_grammar.variables.iter().enumerate() {
            // Move this variable's info out of the vector so it can be modified
            // while reading from other entries of the vector.
            let mut variable_info = VariableInfo::default();
            mem::swap(&mut variable_info, &mut result[i]);

            for production in &variable.productions {
                for step in &production.steps {
                    let child_symbol = step.symbol;
                    if child_symbol.kind == SymbolType::NonTerminal
                        && !syntax_grammar.variables[child_symbol.index]
                            .kind
                            .is_visible()
                    {
                        let child_variable_info = &result[child_symbol.index];

                        if child_variable_info.has_multi_step_production {
                            variable_info.has_multi_step_production = true;
                        }

                        // Inherit fields from this hidden child
                        for (field_name, child_field_info) in &child_variable_info.fields {
                            let field_info = variable_info
                                .fields
                                .entry(field_name.clone())
                                .or_insert_with(|| {
                                    done = false;
                                    child_field_info.clone()
                                });
                            if child_field_info.multiple && !field_info.multiple {
                                field_info.multiple = child_field_info.multiple;
                                done = false;
                            }
                            if !child_field_info.required && field_info.required {
                                field_info.required = child_field_info.required;
                                done = false;
                            }
                            for child_type in &child_field_info.types {
                                if let Err(i) = field_info.types.binary_search(&child_type) {
                                    field_info.types.insert(i, child_type.clone());
                                    done = false;
                                }
                            }
                        }

                        // Inherit child types from this hidden child
                        for child_type in &child_variable_info.child_types {
                            if let Err(i) = variable_info.child_types.binary_search(&child_type) {
                                variable_info.child_types.insert(i, child_type.clone());
                                done = false;
                            }
                        }

                        // If any field points to this hidden child, inherit child types
                        // for the field.
                        if let Some(field_name) = &step.field_name {
                            let field_info = variable_info.fields.get_mut(field_name).unwrap();
                            for child_type in &child_variable_info.child_types {
                                if let Err(i) = field_info.types.binary_search(&child_type) {
                                    field_info.types.insert(i, child_type.clone());
                                    done = false;
                                }
                            }
                        }
                    }
                }
            }

            // Move this variable's info back into the vector.
            result[i] = variable_info;
        }
    }

    for supertype_symbol in &syntax_grammar.supertype_symbols {
        let variable = &syntax_grammar.variables[supertype_symbol.index];
        if variable.kind != VariableType::Hidden {
            return Err(Error::grammar(&format!(
                "Supertype symbols must be hidden, but `{}` is not",
                variable.name
            )));
        }

        if result[supertype_symbol.index].has_multi_step_production {
            return Err(Error::grammar(&format!(
                "Supertype symbols must always have a single visible child, but `{}` can have multiple",
                variable.name
            )));
        }
    }

    let child_type_is_visible = |child_type: &ChildType| match child_type {
        ChildType::Aliased(_) => true,
        ChildType::Normal(symbol) => {
            let variable_kind = match symbol.kind {
                SymbolType::NonTerminal => syntax_grammar.variables[symbol.index].kind,
                SymbolType::Terminal => lexical_grammar.variables[symbol.index].kind,
                SymbolType::External => syntax_grammar.external_tokens[symbol.index].kind,
                _ => VariableType::Hidden,
            };
            variable_kind.is_visible()
        }
    };

    for supertype_symbol in &syntax_grammar.supertype_symbols {
        result[supertype_symbol.index]
            .child_types
            .retain(child_type_is_visible);
    }

    for i in 0..result.len() {
        let mut variable_info = VariableInfo::default();
        mem::swap(&mut variable_info, &mut result[i]);

        // For each field, make the `types` list more concise by replacing sets of
        // subtypes with a single supertype.
        for (_, field_info) in variable_info.fields.iter_mut() {
            for supertype_symbol in &syntax_grammar.supertype_symbols {
                if sorted_vec_replace(
                    &mut field_info.types,
                    &result[supertype_symbol.index].child_types,
                    ChildType::Normal(*supertype_symbol),
                ) {
                    break;
                }
            }

            field_info.types.retain(|t| {
                if let ChildType::Normal(symbol) = t {
                    if syntax_grammar.supertype_symbols.contains(&symbol) {
                        return true;
                    }
                }
                child_type_is_visible(t)
            });
        }

        result[i] = variable_info;
    }

    Ok(result)
}

fn sorted_vec_replace<T>(left: &mut Vec<T>, right: &Vec<T>, value: T) -> bool
where
    T: Eq + Ord,
{
    let mut i = 0;
    for right_elem in right.iter() {
        while left[i] < *right_elem {
            i += 1;
            if i == left.len() {
                return false;
            }
        }
        if left[i] != *right_elem {
            return false;
        }
    }

    i = 0;
    left.retain(|left_elem| {
        if i == right.len() {
            return true;
        }
        while right[i] < *left_elem {
            i += 1;
            if i == right.len() {
                return true;
            }
        }
        right[i] != *left_elem
    });

    if let Err(i) = left.binary_search(&value) {
        left.insert(i, value);
    }

    true
}

pub(crate) fn build_parse_table(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    inlines: &InlinedProductionMap,
    state_ids_to_log: Vec<usize>,
) -> Result<(ParseTable, Vec<TokenSet>)> {
    let item_set_builder = ParseItemSetBuilder::new(syntax_grammar, lexical_grammar, inlines);
    let mut following_tokens = vec![TokenSet::new(); lexical_grammar.variables.len()];
    populate_following_tokens(
        &mut following_tokens,
        syntax_grammar,
        inlines,
        &item_set_builder,
    );

    let variable_info = get_variable_info(syntax_grammar, lexical_grammar)?;

    let table = ParseTableBuilder {
        syntax_grammar,
        lexical_grammar,
        state_ids_to_log,
        item_set_builder,
        state_ids_by_item_set: HashMap::new(),
        item_sets_by_state_id: Vec::new(),
        parse_state_queue: VecDeque::new(),
        parse_table: ParseTable {
            states: Vec::new(),
            symbols: Vec::new(),
            production_infos: Vec::new(),
            max_aliased_production_length: 0,
            variable_info,
        },
    }
    .build()?;

    Ok((table, following_tokens))
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::grammars::{
        LexicalVariable, Production, ProductionStep, SyntaxVariable, VariableType,
    };

    #[test]
    fn test_get_variable_info() {
        let variable_info = get_variable_info(
            &build_syntax_grammar(
                vec![
                    // Required field `field1` has only one node type.
                    SyntaxVariable {
                        name: "rule0".to_string(),
                        kind: VariableType::Named,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(0)),
                                ProductionStep::new(Symbol::non_terminal(1))
                                    .with_field_name("field1"),
                            ],
                        }],
                    },
                    // Hidden node
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![ProductionStep::new(Symbol::terminal(1))],
                        }],
                    },
                    // Optional field `field2` can have two possible node types.
                    SyntaxVariable {
                        name: "rule2".to_string(),
                        kind: VariableType::Named,
                        productions: vec![
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::terminal(0))],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![
                                    ProductionStep::new(Symbol::terminal(0)),
                                    ProductionStep::new(Symbol::terminal(2))
                                        .with_field_name("field2"),
                                ],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![
                                    ProductionStep::new(Symbol::terminal(0)),
                                    ProductionStep::new(Symbol::terminal(3))
                                        .with_field_name("field2"),
                                ],
                            },
                        ],
                    },
                ],
                vec![],
            ),
            &build_lexical_grammar(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    required: true,
                    multiple: false,
                    types: vec![ChildType::Normal(Symbol::terminal(1))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );

        assert_eq!(
            variable_info[2].fields,
            vec![(
                "field2".to_string(),
                FieldInfo {
                    required: false,
                    multiple: false,
                    types: vec![
                        ChildType::Normal(Symbol::terminal(2)),
                        ChildType::Normal(Symbol::terminal(3)),
                    ],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );
    }

    #[test]
    fn test_get_variable_info_with_inherited_fields() {
        let variable_info = get_variable_info(
            &build_syntax_grammar(
                vec![
                    SyntaxVariable {
                        name: "rule0".to_string(),
                        kind: VariableType::Named,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(0)),
                                ProductionStep::new(Symbol::non_terminal(1)),
                                ProductionStep::new(Symbol::terminal(1)),
                            ],
                        }],
                    },
                    // Hidden node with fields
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(2)),
                                ProductionStep::new(Symbol::terminal(3)).with_field_name("field1"),
                            ],
                        }],
                    },
                ],
                vec![],
            ),
            &build_lexical_grammar(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    required: true,
                    multiple: false,
                    types: vec![ChildType::Normal(Symbol::terminal(3))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );
    }

    #[test]
    fn test_get_variable_info_with_supertypes() {
        let variable_info = get_variable_info(
            &build_syntax_grammar(
                vec![
                    SyntaxVariable {
                        name: "rule0".to_string(),
                        kind: VariableType::Named,
                        productions: vec![Production {
                            dynamic_precedence: 0,
                            steps: vec![
                                ProductionStep::new(Symbol::terminal(0)),
                                ProductionStep::new(Symbol::non_terminal(1))
                                    .with_field_name("field1"),
                                ProductionStep::new(Symbol::terminal(1)),
                            ],
                        }],
                    },
                    SyntaxVariable {
                        name: "_rule1".to_string(),
                        kind: VariableType::Hidden,
                        productions: vec![
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::terminal(2))],
                            },
                            Production {
                                dynamic_precedence: 0,
                                steps: vec![ProductionStep::new(Symbol::terminal(3))],
                            },
                        ],
                    },
                ],
                // _rule1 is a supertype
                vec![Symbol::non_terminal(1)],
            ),
            &build_lexical_grammar(),
        )
        .unwrap();

        assert_eq!(
            variable_info[0].fields,
            vec![(
                "field1".to_string(),
                FieldInfo {
                    required: true,
                    multiple: false,
                    types: vec![ChildType::Normal(Symbol::non_terminal(1))],
                }
            )]
            .into_iter()
            .collect::<HashMap<_, _>>()
        );
    }

    fn build_syntax_grammar(
        variables: Vec<SyntaxVariable>,
        supertype_symbols: Vec<Symbol>,
    ) -> SyntaxGrammar {
        let mut syntax_grammar = SyntaxGrammar::default();
        syntax_grammar.variables = variables;
        syntax_grammar.supertype_symbols = supertype_symbols;
        syntax_grammar
    }

    fn build_lexical_grammar() -> LexicalGrammar {
        let mut lexical_grammar = LexicalGrammar::default();
        for i in 0..10 {
            lexical_grammar.variables.push(LexicalVariable {
                name: format!("token_{}", i),
                kind: VariableType::Named,
                implicit_precedence: 0,
                start_state: 0,
            });
        }
        lexical_grammar
    }
}
