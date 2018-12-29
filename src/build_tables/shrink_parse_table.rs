use crate::grammars::{SyntaxGrammar, VariableType};
use crate::rules::AliasMap;
use crate::tables::{ParseAction, ParseTable};
use std::collections::{HashMap, HashSet};

pub(crate) fn shrink_parse_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    simple_aliases: &AliasMap,
) {
    remove_unit_reductions(parse_table, syntax_grammar, simple_aliases);
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
