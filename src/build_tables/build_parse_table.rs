use super::item::{LookaheadSet, ParseItem, ParseItemSet};
use super::item_set_builder::ParseItemSetBuilder;
use crate::error::{Error, Result};
use crate::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar, VariableType};
use crate::rules::{Alias, Associativity, Symbol, SymbolType};
use crate::tables::{
    AliasSequenceId, ParseAction, ParseState, ParseStateId, ParseTable, ParseTableEntry,
};
use core::ops::Range;
use hashbrown::hash_map::Entry;
use hashbrown::{HashMap, HashSet};
use std::collections::hash_map::DefaultHasher;
use std::collections::VecDeque;

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
    following_tokens: Vec<LookaheadSet>,
}

impl<'a> ParseTableBuilder<'a> {
    fn build(mut self) -> Result<(ParseTable, Vec<LookaheadSet>)> {
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
                    LookaheadSet::with([Symbol::end()].iter().cloned()),
                )]
                .iter()
                .cloned(),
            ),
        );

        while let Some(entry) = self.parse_state_queue.pop_front() {
            // info!(
            //     "state: {}, item set: {}",
            //     entry.state_id,
            //     super::item::ParseItemSetDisplay(
            //         &self.item_sets_by_state_id[entry.state_id],
            //         self.syntax_grammar,
            //         self.lexical_grammar,
            //     )
            // );

            let item_set = self
                .item_set_builder
                .transitive_closure(&self.item_sets_by_state_id[entry.state_id]);

            // info!(
            //     "state: {}, closed item set: {}",
            //     entry.state_id,
            //     super::item::ParseItemSetDisplay(
            //         &item_set,
            //         self.syntax_grammar,
            //         self.lexical_grammar,
            //     )
            // );

            self.add_actions(
                entry.preceding_symbols,
                entry.preceding_auxiliary_symbols,
                entry.state_id,
                item_set,
            )?;
        }

        self.populate_used_symbols();
        self.remove_precedences();

        Ok((self.parse_table, self.following_tokens))
    }

    fn add_parse_state(
        &mut self,
        preceding_symbols: &SymbolSequence,
        preceding_auxiliary_symbols: &AuxiliarySymbolSequence,
        item_set: ParseItemSet<'a>,
    ) -> ParseStateId {
        if preceding_symbols.len() > 1 {
            let left_tokens = self
                .item_set_builder
                .last_set(&preceding_symbols[preceding_symbols.len() - 2]);
            let right_tokens = self
                .item_set_builder
                .first_set(&preceding_symbols[preceding_symbols.len() - 1]);
            for left_token in left_tokens.iter() {
                if left_token.is_terminal() {
                    self.following_tokens[left_token.index].insert_all(right_tokens);
                }
            }
        }

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
                        .entries
                        .entry(successor)
                        .or_insert_with(|| LookaheadSet::new())
                        .insert_all(lookaheads);
                } else {
                    terminal_successors
                        .entry(next_symbol)
                        .or_insert_with(|| ParseItemSet::default())
                        .entries
                        .entry(successor)
                        .or_insert_with(|| LookaheadSet::new())
                        .insert_all(lookaheads);
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
                        conflicting_items.insert(item);
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
                conflicting_items.insert(item);
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
        write!(&mut msg, "Possible interpretations:\n").unwrap();
        for (i, item) in conflicting_items.iter().enumerate() {
            write!(&mut msg, "\n  {}:", i).unwrap();

            for preceding_symbol in preceding_symbols
                .iter()
                .take(preceding_symbols.len() - item.step_index as usize)
            {
                write!(&mut msg, "  {}", self.symbol_name(preceding_symbol)).unwrap();
            }

            write!(
                &mut msg,
                "  ({}",
                &self.syntax_grammar.variables[item.variable_index as usize].name
            )
            .unwrap();

            for (j, step) in item.production.steps.iter().enumerate() {
                if j as u32 == item.step_index {
                    write!(&mut msg, "  •").unwrap();
                }
                write!(&mut msg, "  {}", self.symbol_name(&step.symbol)).unwrap();
            }

            write!(&mut msg, ")").unwrap();

            if item.is_done() {
                write!(
                    &mut msg,
                    "  •  {}",
                    self.symbol_name(&conflicting_lookahead)
                )
                .unwrap();
            }

            let precedence = item.precedence();
            let associativity = item.associativity();
            if precedence != 0 || associativity.is_some() {
                write!(
                    &mut msg,
                    "(precedence: {}, associativity: {:?})",
                    precedence, associativity
                )
                .unwrap();
            }
        }

        // TODO - generate suggested resolutions

        Err(Error::ConflictError(msg))
    }

    fn get_auxiliary_node_info(
        &self,
        item_set: &ParseItemSet,
        symbol: Symbol,
    ) -> AuxiliarySymbolInfo {
        let parent_symbols = item_set
            .entries
            .keys()
            .filter_map(|item| {
                if item.symbol() == Some(symbol) {
                    None
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

    fn populate_used_symbols(&mut self) {
        self.parse_table.symbols.push(Symbol::end());
        let mut terminal_usages = vec![false; self.lexical_grammar.variables.len()];
        let mut non_terminal_usages = vec![false; self.syntax_grammar.variables.len()];
        let mut external_usages = vec![false; self.syntax_grammar.external_tokens.len()];
        for state in &self.parse_table.states {
            for symbol in state.terminal_entries.keys() {
                match symbol.kind {
                    SymbolType::Terminal => terminal_usages[symbol.index] = true,
                    SymbolType::External => external_usages[symbol.index] = true,
                    _ => {}
                }
            }
            for symbol in state.nonterminal_entries.keys() {
                non_terminal_usages[symbol.index] = true;
            }
        }
        for (i, value) in terminal_usages.into_iter().enumerate() {
            if value {
                self.parse_table.symbols.push(Symbol::terminal(i));
            }
        }
        for (i, value) in external_usages.into_iter().enumerate() {
            if value {
                self.parse_table.symbols.push(Symbol::external(i));
            }
        }
        for (i, value) in non_terminal_usages.into_iter().enumerate() {
            if value {
                self.parse_table.symbols.push(Symbol::non_terminal(i));
            }
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
                    format!("\"{}\"", &variable.name)
                }
            }
        }
    }
}

pub(crate) fn build_parse_table(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    inlines: &InlinedProductionMap,
) -> Result<(ParseTable, Vec<LookaheadSet>)> {
    ParseTableBuilder {
        syntax_grammar,
        lexical_grammar,
        item_set_builder: ParseItemSetBuilder::new(syntax_grammar, lexical_grammar, inlines),
        state_ids_by_item_set: HashMap::new(),
        item_sets_by_state_id: Vec::new(),
        parse_state_queue: VecDeque::new(),
        parse_table: ParseTable {
            states: Vec::new(),
            alias_sequences: Vec::new(),
            symbols: Vec::new(),
        },
        following_tokens: vec![LookaheadSet::new(); lexical_grammar.variables.len()],
    }
    .build()
}
