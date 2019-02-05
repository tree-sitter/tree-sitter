use super::item::TokenSet;
use super::token_conflicts::TokenConflictMap;
use crate::generate::grammars::{LexicalGrammar, SyntaxGrammar, VariableType};
use crate::generate::rules::{AliasMap, Symbol};
use crate::generate::tables::{ParseAction, ParseState, ParseTable, ParseTableEntry};
use hashbrown::{HashMap, HashSet};
use log::info;

pub(crate) fn minimize_parse_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    token_conflict_map: &TokenConflictMap,
    keywords: &TokenSet,
) {
    let mut minimizer = Minimizer {
        parse_table,
        syntax_grammar,
        lexical_grammar,
        token_conflict_map,
        keywords,
        simple_aliases,
    };
    minimizer.remove_unit_reductions();
    minimizer.merge_compatible_states();
    minimizer.remove_unused_states();
}

struct Minimizer<'a> {
    parse_table: &'a mut ParseTable,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    token_conflict_map: &'a TokenConflictMap<'a>,
    keywords: &'a TokenSet,
    simple_aliases: &'a AliasMap,
}

impl<'a> Minimizer<'a> {
    fn remove_unit_reductions(&mut self) {
        let mut aliased_symbols = HashSet::new();
        for variable in &self.syntax_grammar.variables {
            for production in &variable.productions {
                for step in &production.steps {
                    if step.alias.is_some() {
                        aliased_symbols.insert(step.symbol);
                    }
                }
            }
        }

        let mut unit_reduction_symbols_by_state = HashMap::new();
        for (i, state) in self.parse_table.states.iter().enumerate() {
            let mut only_unit_reductions = true;
            let mut unit_reduction_symbol = None;
            for (_, entry) in &state.terminal_entries {
                for action in &entry.actions {
                    match action {
                        ParseAction::ShiftExtra => continue,
                        ParseAction::Reduce {
                            child_count: 1,
                            alias_sequence_id: 0,
                            symbol,
                            ..
                        } => {
                            if !self.simple_aliases.contains_key(&symbol)
                                && !aliased_symbols.contains(&symbol)
                                && self.syntax_grammar.variables[symbol.index].kind
                                    != VariableType::Named
                                && (unit_reduction_symbol.is_none()
                                    || unit_reduction_symbol == Some(symbol))
                            {
                                unit_reduction_symbol = Some(symbol);
                                continue;
                            }
                        }
                        _ => {}
                    }
                    only_unit_reductions = false;
                    break;
                }

                if !only_unit_reductions {
                    break;
                }
            }

            if let Some(symbol) = unit_reduction_symbol {
                if only_unit_reductions {
                    unit_reduction_symbols_by_state.insert(i, *symbol);
                }
            }
        }

        for state in self.parse_table.states.iter_mut() {
            let mut done = false;
            while !done {
                done = true;
                state.update_referenced_states(|other_state_id, state| {
                    if let Some(symbol) = unit_reduction_symbols_by_state.get(&other_state_id) {
                        done = false;
                        state.nonterminal_entries[symbol]
                    } else {
                        other_state_id
                    }
                })
            }
        }
    }

    fn merge_compatible_states(&mut self) {
        let mut state_ids_by_signature = HashMap::new();
        for (i, state) in self.parse_table.states.iter().enumerate() {
            state_ids_by_signature
                .entry(state.unfinished_item_signature)
                .or_insert(Vec::new())
                .push(i);
        }

        let mut deleted_states = HashSet::new();
        loop {
            let mut state_replacements = HashMap::new();
            for (_, state_ids) in &state_ids_by_signature {
                for i in state_ids {
                    for j in state_ids {
                        if j == i {
                            break;
                        }
                        if deleted_states.contains(j) || deleted_states.contains(i) {
                            continue;
                        }
                        if self.merge_parse_state(*j, *i) {
                            deleted_states.insert(*i);
                            state_replacements.insert(*i, *j);
                        }
                    }
                }
            }

            if state_replacements.is_empty() {
                break;
            }

            for state in self.parse_table.states.iter_mut() {
                state.update_referenced_states(|other_state_id, _| {
                    *state_replacements
                        .get(&other_state_id)
                        .unwrap_or(&other_state_id)
                });
            }
        }
    }

    fn merge_parse_state(&mut self, left: usize, right: usize) -> bool {
        let left_state = &self.parse_table.states[left];
        let right_state = &self.parse_table.states[right];

        if left_state.nonterminal_entries != right_state.nonterminal_entries {
            return false;
        }

        for (symbol, left_entry) in &left_state.terminal_entries {
            if let Some(right_entry) = right_state.terminal_entries.get(symbol) {
                if right_entry.actions != left_entry.actions {
                    return false;
                }
            } else if !self.can_add_entry_to_state(right_state, *symbol, left_entry) {
                return false;
            }
        }

        let mut symbols_to_add = Vec::new();
        for (symbol, right_entry) in &right_state.terminal_entries {
            if !left_state.terminal_entries.contains_key(&symbol) {
                if !self.can_add_entry_to_state(left_state, *symbol, right_entry) {
                    return false;
                }
                symbols_to_add.push(*symbol);
            }
        }

        for symbol in symbols_to_add {
            let entry = self.parse_table.states[right].terminal_entries[&symbol].clone();
            self.parse_table.states[left]
                .terminal_entries
                .insert(symbol, entry);
        }

        true
    }

    fn can_add_entry_to_state(
        &self,
        state: &ParseState,
        token: Symbol,
        entry: &ParseTableEntry,
    ) -> bool {
        // Do not add external tokens; they could conflict lexically with any of the state's
        // existing lookahead tokens.
        if token.is_external() {
            return false;
        }

        // Only merge_compatible_states parse states by allowing existing reductions to happen
        // with additional lookahead tokens. Do not alter parse states in ways
        // that allow entirely new types of actions to happen.
        if state.terminal_entries.iter().all(|(_, e)| e != entry) {
            return false;
        }
        match entry.actions.last() {
            Some(ParseAction::Reduce { .. }) => {}
            _ => return false,
        }

        // Do not add tokens which are both internal and external. Their validity could
        // influence the behavior of the external scanner.
        if self
            .syntax_grammar
            .external_tokens
            .iter()
            .any(|t| t.corresponding_internal_token == Some(token))
        {
            return false;
        }

        let is_word_token = self.syntax_grammar.word_token == Some(token);
        let is_keyword = self.keywords.contains(&token);

        // Do not add a token if it conflicts with an existing token.
        if token.is_terminal() {
            for existing_token in state.terminal_entries.keys() {
                if (is_word_token || is_keyword)
                    && (self.keywords.contains(existing_token)
                        || self.syntax_grammar.word_token.as_ref() == Some(existing_token))
                {
                    continue;
                }
                if self
                    .token_conflict_map
                    .does_conflict(token.index, existing_token.index)
                    || self
                        .token_conflict_map
                        .does_match_same_string(token.index, existing_token.index)
                {
                    info!(
                        "can't merge parse states because of conflict between {} and {}",
                        self.lexical_grammar.variables[token.index].name,
                        self.lexical_grammar.variables[existing_token.index].name
                    );
                    return false;
                }
            }
        }

        true
    }

    fn remove_unused_states(&mut self) {
        let mut state_usage_map = vec![false; self.parse_table.states.len()];

        state_usage_map[0] = true;
        state_usage_map[1] = true;

        for state in &self.parse_table.states {
            for referenced_state in state.referenced_states() {
                state_usage_map[referenced_state] = true;
            }
        }
        let mut removed_predecessor_count = 0;
        let mut state_replacement_map = vec![0; self.parse_table.states.len()];
        for state_id in 0..self.parse_table.states.len() {
            state_replacement_map[state_id] = state_id - removed_predecessor_count;
            if !state_usage_map[state_id] {
                removed_predecessor_count += 1;
            }
        }
        let mut state_id = 0;
        let mut original_state_id = 0;
        while state_id < self.parse_table.states.len() {
            if state_usage_map[original_state_id] {
                self.parse_table.states[state_id].update_referenced_states(|other_state_id, _| {
                    state_replacement_map[other_state_id]
                });
                state_id += 1;
            } else {
                self.parse_table.states.remove(state_id);
            }
            original_state_id += 1;
        }
    }
}
