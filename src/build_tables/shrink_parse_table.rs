use super::token_conflicts::TokenConflictMap;
use crate::grammars::{SyntaxGrammar, VariableType};
use crate::rules::{AliasMap, Symbol};
use crate::tables::{ParseAction, ParseState, ParseTable, ParseTableEntry};
use std::collections::{HashMap, HashSet};

pub(crate) fn shrink_parse_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    simple_aliases: &AliasMap,
    token_conflict_map: &TokenConflictMap,
) {
    remove_unit_reductions(parse_table, syntax_grammar, simple_aliases);
    merge_compatible_states(parse_table, syntax_grammar, token_conflict_map);
    remove_unused_states(parse_table);
}

fn remove_unit_reductions(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    simple_aliases: &AliasMap,
) {
    let mut aliased_symbols = HashSet::new();
    for variable in &syntax_grammar.variables {
        for production in &variable.productions {
            for step in &production.steps {
                if step.alias.is_some() {
                    aliased_symbols.insert(step.symbol);
                }
            }
        }
    }

    let mut unit_reduction_symbols_by_state = HashMap::new();
    for (i, state) in parse_table.states.iter().enumerate() {
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
                        if !simple_aliases.contains_key(&symbol)
                            && !aliased_symbols.contains(&symbol)
                            && syntax_grammar.variables[symbol.index].kind != VariableType::Named
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

    for state in parse_table.states.iter_mut() {
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

fn merge_compatible_states(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    token_conflict_map: &TokenConflictMap,
) {
    let mut state_ids_by_signature = HashMap::new();
    for (i, state) in parse_table.states.iter().enumerate() {
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
                    if merge_parse_state(syntax_grammar, token_conflict_map, parse_table, *j, *i) {
                        deleted_states.insert(*i);
                        state_replacements.insert(*i, *j);
                    }
                }
            }
        }

        if state_replacements.is_empty() {
            break;
        }

        for state in parse_table.states.iter_mut() {
            state.update_referenced_states(|other_state_id, _| {
                *state_replacements
                    .get(&other_state_id)
                    .unwrap_or(&other_state_id)
            });
        }
    }
}

fn merge_parse_state(
    syntax_grammar: &SyntaxGrammar,
    token_conflict_map: &TokenConflictMap,
    parse_table: &mut ParseTable,
    left: usize,
    right: usize,
) -> bool {
    let left_state = &parse_table.states[left];
    let right_state = &parse_table.states[right];

    if left_state.nonterminal_entries != right_state.nonterminal_entries {
        return false;
    }

    for (symbol, left_entry) in &left_state.terminal_entries {
        if let Some(right_entry) = right_state.terminal_entries.get(symbol) {
            if right_entry.actions != left_entry.actions {
                return false;
            }
        } else if !can_add_entry_to_state(
            syntax_grammar,
            token_conflict_map,
            right_state,
            *symbol,
            left_entry,
        ) {
            return false;
        }
    }

    eprintln!("maybe merge {} {}", left, right);

    let mut symbols_to_add = Vec::new();
    for (symbol, right_entry) in &right_state.terminal_entries {
        if !left_state.terminal_entries.contains_key(&symbol) {
            if !can_add_entry_to_state(
                syntax_grammar,
                token_conflict_map,
                left_state,
                *symbol,
                right_entry,
            ) {
                return false;
            }
            symbols_to_add.push(*symbol);
        }
    }

    for symbol in symbols_to_add {
        let entry = parse_table.states[right].terminal_entries[&symbol].clone();
        parse_table.states[left]
            .terminal_entries
            .insert(symbol, entry);
    }

    true
}

fn can_add_entry_to_state(
    syntax_grammar: &SyntaxGrammar,
    token_conflict_map: &TokenConflictMap,
    state: &ParseState,
    token: Symbol,
    entry: &ParseTableEntry,
) -> bool {
    // Do not add external tokens; they could conflict lexically with any of the state's
    // existing lookahead tokens.
    if token.is_external() {
        return false;
    }

    // Only merge parse states by allowing existing reductions to happen
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
    if syntax_grammar
        .external_tokens
        .iter()
        .any(|t| t.corresponding_internal_token == Some(token))
    {
        return false;
    }

    // Do not add a token if it conflicts with an existing token.
    if token.is_terminal() {
        for existing_token in state.terminal_entries.keys() {
            if token_conflict_map.does_conflict(token.index, existing_token.index) {
                return false;
            }
        }
    }

    true
}

fn remove_unused_states(parse_table: &mut ParseTable) {
    let mut state_usage_map = vec![false; parse_table.states.len()];
    for state in &parse_table.states {
        for referenced_state in state.referenced_states() {
            state_usage_map[referenced_state] = true;
        }
    }
    let mut removed_predecessor_count = 0;
    let mut state_replacement_map = vec![0; parse_table.states.len()];
    for state_id in 0..parse_table.states.len() {
        state_replacement_map[state_id] = state_id - removed_predecessor_count;
        if !state_usage_map[state_id] {
            removed_predecessor_count += 1;
        }
    }
    let mut state_id = 0;
    let mut original_state_id = 0;
    while state_id < parse_table.states.len() {
        if state_usage_map[original_state_id] {
            parse_table.states[state_id].update_referenced_states(|other_state_id, _| {
                state_replacement_map[other_state_id]
            });
            state_id += 1;
        } else {
            parse_table.states.remove(state_id);
        }
        original_state_id += 1;
    }
}
