use super::item::{ParseItem, ParseItemSet, TokenSet};
use super::item_set_builder::ParseItemSetBuilder;
use crate::error::{Error, Result};
use crate::generate::grammars::{
    InlinedProductionMap, LexicalGrammar, SyntaxGrammar, VariableType,
};
use crate::generate::rules::{Alias, Associativity, Symbol, SymbolType};
use crate::generate::tables::{
    AliasSequenceId, ParseAction, ParseState, ParseStateId, ParseTable, ParseTableEntry,
};
use core::ops::Range;
use hashbrown::hash_map::Entry;
use hashbrown::{HashMap, HashSet};
use std::collections::hash_map::DefaultHasher;
use std::collections::VecDeque;
use std::u32;

use std::fmt::Write;
use std::hash::Hasher;

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
        self.parse_table.alias_sequences.push(Vec::new());

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
                        alias_sequence_id: self.get_alias_sequence_id(item),
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

        let interpretions = conflicting_items
            .iter()
            .enumerate()
            .map(|(i, item)| {
                let mut line = String::new();
                write!(&mut line, "  {}:", i + 1).unwrap();

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

        for (line, prec_suffix) in interpretions {
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
        let shift_items = conflicting_items
            .iter()
            .filter(|i| !i.is_done())
            .cloned()
            .collect::<Vec<_>>();
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

    fn get_alias_sequence_id(&mut self, item: &ParseItem) -> AliasSequenceId {
        let mut alias_sequence: Vec<Option<Alias>> = item
            .production
            .steps
            .iter()
            .map(|s| s.alias.clone())
            .collect();
        while alias_sequence.last() == Some(&None) {
            alias_sequence.pop();
        }
        if item.production.steps.len() > self.parse_table.max_aliased_production_length {
            self.parse_table.max_aliased_production_length = item.production.steps.len()
        }
        if let Some(index) = self
            .parse_table
            .alias_sequences
            .iter()
            .position(|seq| *seq == alias_sequence)
        {
            index
        } else {
            self.parse_table.alias_sequences.push(alias_sequence);
            self.parse_table.alias_sequences.len() - 1
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
            alias_sequences: Vec::new(),
            max_aliased_production_length: 0,
        },
    }
    .build()?;

    Ok((table, following_tokens))
}
