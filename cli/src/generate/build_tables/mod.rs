pub(crate) mod build_lex_table;
pub(crate) mod build_parse_table;
mod coincident_tokens;
mod item;
mod item_set_builder;
mod minimize_parse_table;
mod token_conflicts;

use self::build_lex_table::build_lex_table;
use self::build_parse_table::{build_parse_table, ParseStateInfo};
use self::coincident_tokens::CoincidentTokenIndex;
use self::minimize_parse_table::minimize_parse_table;
use self::token_conflicts::TokenConflictMap;
use crate::generate::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar};
use crate::generate::nfa::NfaCursor;
use crate::generate::node_types::VariableInfo;
use crate::generate::rules::{AliasMap, Symbol, SymbolType, TokenSet};
use crate::generate::tables::{LexTable, ParseAction, ParseTable, ParseTableEntry};
use anyhow::Result;
use log::info;
use std::collections::{BTreeSet, HashMap};

pub(crate) fn build_tables(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    variable_info: &Vec<VariableInfo>,
    inlines: &InlinedProductionMap,
    report_symbol_name: Option<&str>,
) -> Result<(ParseTable, LexTable, LexTable, Option<Symbol>)> {
    let (mut parse_table, following_tokens, parse_state_info) =
        build_parse_table(syntax_grammar, lexical_grammar, inlines, variable_info)?;
    let token_conflict_map = TokenConflictMap::new(lexical_grammar, following_tokens);
    let coincident_token_index = CoincidentTokenIndex::new(&parse_table, lexical_grammar);
    let keywords = identify_keywords(
        lexical_grammar,
        &parse_table,
        syntax_grammar.word_token,
        &token_conflict_map,
        &coincident_token_index,
    );
    populate_error_state(
        &mut parse_table,
        syntax_grammar,
        lexical_grammar,
        &coincident_token_index,
        &token_conflict_map,
        &keywords,
    );
    populate_used_symbols(&mut parse_table, syntax_grammar, lexical_grammar);
    minimize_parse_table(
        &mut parse_table,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        &token_conflict_map,
        &keywords,
    );
    let (main_lex_table, keyword_lex_table) = build_lex_table(
        &mut parse_table,
        syntax_grammar,
        lexical_grammar,
        &keywords,
        &coincident_token_index,
        &token_conflict_map,
    );
    populate_external_lex_states(&mut parse_table, syntax_grammar);
    mark_fragile_tokens(&mut parse_table, lexical_grammar, &token_conflict_map);

    if let Some(report_symbol_name) = report_symbol_name {
        report_state_info(
            &syntax_grammar,
            &lexical_grammar,
            &parse_table,
            &parse_state_info,
            report_symbol_name,
        );
    }
    Ok((
        parse_table,
        main_lex_table,
        keyword_lex_table,
        syntax_grammar.word_token,
    ))
}

fn populate_error_state(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    coincident_token_index: &CoincidentTokenIndex,
    token_conflict_map: &TokenConflictMap,
    keywords: &TokenSet,
) {
    let state = &mut parse_table.states[0];
    let n = lexical_grammar.variables.len();

    // First identify the *conflict-free tokens*: tokens that do not overlap with
    // any other token in any way, besides matching exactly the same string.
    let conflict_free_tokens: TokenSet = (0..n)
        .into_iter()
        .filter_map(|i| {
            let conflicts_with_other_tokens = (0..n).into_iter().any(|j| {
                j != i
                    && !coincident_token_index.contains(Symbol::terminal(i), Symbol::terminal(j))
                    && token_conflict_map.does_match_shorter_or_longer(i, j)
            });
            if conflicts_with_other_tokens {
                None
            } else {
                info!(
                    "error recovery - token {} has no conflicts",
                    lexical_grammar.variables[i].name
                );
                Some(Symbol::terminal(i))
            }
        })
        .collect();

    let recover_entry = ParseTableEntry {
        reusable: false,
        actions: vec![ParseAction::Recover],
    };

    // Exclude from the error-recovery state any token that conflicts with one of
    // the *conflict-free tokens* identified above.
    for i in 0..n {
        let symbol = Symbol::terminal(i);
        if !conflict_free_tokens.contains(&symbol) && !keywords.contains(&symbol) {
            if syntax_grammar.word_token != Some(symbol) {
                if let Some(t) = conflict_free_tokens.iter().find(|t| {
                    !coincident_token_index.contains(symbol, *t)
                        && token_conflict_map.does_conflict(symbol.index, t.index)
                }) {
                    info!(
                        "error recovery - exclude token {} because of conflict with {}",
                        lexical_grammar.variables[i].name, lexical_grammar.variables[t.index].name
                    );
                    continue;
                }
            }
        }
        info!(
            "error recovery - include token {}",
            lexical_grammar.variables[i].name
        );
        state
            .terminal_entries
            .entry(symbol)
            .or_insert_with(|| recover_entry.clone());
    }

    for (i, external_token) in syntax_grammar.external_tokens.iter().enumerate() {
        if external_token.corresponding_internal_token.is_none() {
            state
                .terminal_entries
                .entry(Symbol::external(i))
                .or_insert_with(|| recover_entry.clone());
        }
    }

    state.terminal_entries.insert(Symbol::end(), recover_entry);
}

fn populate_used_symbols(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
) {
    let mut terminal_usages = vec![false; lexical_grammar.variables.len()];
    let mut non_terminal_usages = vec![false; syntax_grammar.variables.len()];
    let mut external_usages = vec![false; syntax_grammar.external_tokens.len()];
    for state in &parse_table.states {
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
    parse_table.symbols.push(Symbol::end());
    for (i, value) in terminal_usages.into_iter().enumerate() {
        if value {
            // Assign the grammar's word token a low numerical index. This ensures that
            // it can be stored in a subtree with no heap allocations, even for grammars with
            // very large numbers of tokens. This is an optimization, but it's also important to
            // ensure that a subtree's symbol can be successfully reassigned to the word token
            // without having to move the subtree to the heap.
            // See https://github.com/tree-sitter/tree-sitter/issues/258
            if syntax_grammar.word_token.map_or(false, |t| t.index == i) {
                parse_table.symbols.insert(1, Symbol::terminal(i));
            } else {
                parse_table.symbols.push(Symbol::terminal(i));
            }
        }
    }
    for (i, value) in external_usages.into_iter().enumerate() {
        if value {
            parse_table.symbols.push(Symbol::external(i));
        }
    }
    for (i, value) in non_terminal_usages.into_iter().enumerate() {
        if value {
            parse_table.symbols.push(Symbol::non_terminal(i));
        }
    }
}

fn populate_external_lex_states(parse_table: &mut ParseTable, syntax_grammar: &SyntaxGrammar) {
    let mut external_tokens_by_corresponding_internal_token = HashMap::new();
    for (i, external_token) in syntax_grammar.external_tokens.iter().enumerate() {
        if let Some(symbol) = external_token.corresponding_internal_token {
            external_tokens_by_corresponding_internal_token.insert(symbol.index, i);
        }
    }

    // Ensure that external lex state 0 represents the absence of any
    // external tokens.
    parse_table.external_lex_states.push(TokenSet::new());

    for i in 0..parse_table.states.len() {
        let mut external_tokens = TokenSet::new();
        for token in parse_table.states[i].terminal_entries.keys() {
            if token.is_external() {
                external_tokens.insert(*token);
            } else if token.is_terminal() {
                if let Some(index) =
                    external_tokens_by_corresponding_internal_token.get(&token.index)
                {
                    external_tokens.insert(Symbol::external(*index));
                }
            }
        }

        parse_table.states[i].external_lex_state_id = parse_table
            .external_lex_states
            .iter()
            .position(|tokens| *tokens == external_tokens)
            .unwrap_or_else(|| {
                parse_table.external_lex_states.push(external_tokens);
                parse_table.external_lex_states.len() - 1
            });
    }
}

fn identify_keywords(
    lexical_grammar: &LexicalGrammar,
    parse_table: &ParseTable,
    word_token: Option<Symbol>,
    token_conflict_map: &TokenConflictMap,
    coincident_token_index: &CoincidentTokenIndex,
) -> TokenSet {
    if word_token.is_none() {
        return TokenSet::new();
    }

    let word_token = word_token.unwrap();
    let mut cursor = NfaCursor::new(&lexical_grammar.nfa, Vec::new());

    // First find all of the candidate keyword tokens: tokens that start with
    // letters or underscore and can match the same string as a word token.
    let keyword_candidates: TokenSet = lexical_grammar
        .variables
        .iter()
        .enumerate()
        .filter_map(|(i, variable)| {
            cursor.reset(vec![variable.start_state]);
            if all_chars_are_alphabetical(&cursor)
                && token_conflict_map.does_match_same_string(i, word_token.index)
                && !token_conflict_map.does_match_different_string(i, word_token.index)
            {
                info!(
                    "Keywords - add candidate {}",
                    lexical_grammar.variables[i].name
                );
                Some(Symbol::terminal(i))
            } else {
                None
            }
        })
        .collect();

    // Exclude keyword candidates that shadow another keyword candidate.
    let keywords: TokenSet = keyword_candidates
        .iter()
        .filter(|token| {
            for other_token in keyword_candidates.iter() {
                if other_token != *token
                    && token_conflict_map.does_match_same_string(other_token.index, token.index)
                {
                    info!(
                        "Keywords - exclude {} because it matches the same string as {}",
                        lexical_grammar.variables[token.index].name,
                        lexical_grammar.variables[other_token.index].name
                    );
                    return false;
                }
            }
            true
        })
        .collect();

    // Exclude keyword candidates for which substituting the keyword capture
    // token would introduce new lexical conflicts with other tokens.
    let keywords = keywords
        .iter()
        .filter(|token| {
            for other_index in 0..lexical_grammar.variables.len() {
                if keyword_candidates.contains(&Symbol::terminal(other_index)) {
                    continue;
                }

                // If the word token was already valid in every state containing
                // this keyword candidate, then substituting the word token won't
                // introduce any new lexical conflicts.
                if coincident_token_index
                    .states_with(*token, Symbol::terminal(other_index))
                    .iter()
                    .all(|state_id| {
                        parse_table.states[*state_id]
                            .terminal_entries
                            .contains_key(&word_token)
                    })
                {
                    continue;
                }

                if !token_conflict_map.has_same_conflict_status(
                    token.index,
                    word_token.index,
                    other_index,
                ) {
                    info!(
                        "Keywords - exclude {} because of conflict with {}",
                        lexical_grammar.variables[token.index].name,
                        lexical_grammar.variables[other_index].name
                    );
                    return false;
                }
            }

            info!(
                "Keywords - include {}",
                lexical_grammar.variables[token.index].name,
            );
            true
        })
        .collect();

    keywords
}

fn mark_fragile_tokens(
    parse_table: &mut ParseTable,
    lexical_grammar: &LexicalGrammar,
    token_conflict_map: &TokenConflictMap,
) {
    let n = lexical_grammar.variables.len();
    let mut valid_tokens_mask = Vec::with_capacity(n);
    for state in parse_table.states.iter_mut() {
        valid_tokens_mask.clear();
        valid_tokens_mask.resize(n, false);
        for token in state.terminal_entries.keys() {
            if token.is_terminal() {
                valid_tokens_mask[token.index] = true;
            }
        }
        for (token, entry) in state.terminal_entries.iter_mut() {
            if token.is_terminal() {
                for (i, is_valid) in valid_tokens_mask.iter().enumerate() {
                    if *is_valid {
                        if token_conflict_map.does_overlap(i, token.index) {
                            entry.reusable = false;
                            break;
                        }
                    }
                }
            }
        }
    }
}

fn report_state_info<'a>(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    parse_table: &ParseTable,
    parse_state_info: &Vec<ParseStateInfo<'a>>,
    report_symbol_name: &'a str,
) {
    let mut all_state_indices = BTreeSet::new();
    let mut symbols_with_state_indices = (0..syntax_grammar.variables.len())
        .map(|i| (Symbol::non_terminal(i), BTreeSet::new()))
        .collect::<Vec<_>>();

    for (i, state) in parse_table.states.iter().enumerate() {
        all_state_indices.insert(i);
        let item_set = &parse_state_info[state.id];
        for (item, _) in item_set.1.entries.iter() {
            if !item.is_augmented() {
                symbols_with_state_indices[item.variable_index as usize]
                    .1
                    .insert(i);
            }
        }
    }

    symbols_with_state_indices.sort_unstable_by_key(|(_, states)| -(states.len() as i32));

    let max_symbol_name_length = syntax_grammar
        .variables
        .iter()
        .map(|v| v.name.len())
        .max()
        .unwrap();
    for (symbol, states) in &symbols_with_state_indices {
        eprintln!(
            "{:width$}\t{}",
            syntax_grammar.variables[symbol.index].name,
            states.len(),
            width = max_symbol_name_length
        );
    }
    eprintln!("");

    let state_indices = if report_symbol_name == "*" {
        Some(&all_state_indices)
    } else {
        symbols_with_state_indices
            .iter()
            .find_map(|(symbol, state_indices)| {
                if syntax_grammar.variables[symbol.index].name == report_symbol_name {
                    Some(state_indices)
                } else {
                    None
                }
            })
    };

    if let Some(state_indices) = state_indices {
        let mut state_indices = state_indices.into_iter().cloned().collect::<Vec<_>>();
        state_indices.sort_unstable_by_key(|i| (parse_table.states[*i].core_id, *i));

        for state_index in state_indices {
            let id = parse_table.states[state_index].id;
            let (preceding_symbols, item_set) = &parse_state_info[id];
            eprintln!("state index: {}", state_index);
            eprintln!("state id: {}", id);
            eprint!("symbol sequence:");
            for symbol in preceding_symbols {
                let name = if symbol.is_terminal() {
                    &lexical_grammar.variables[symbol.index].name
                } else if symbol.is_external() {
                    &syntax_grammar.external_tokens[symbol.index].name
                } else {
                    &syntax_grammar.variables[symbol.index].name
                };
                eprint!(" {}", name);
            }
            eprintln!(
                "\nitems:\n{}",
                self::item::ParseItemSetDisplay(&item_set, syntax_grammar, lexical_grammar,),
            );
        }
    }
}

fn all_chars_are_alphabetical(cursor: &NfaCursor) -> bool {
    cursor.transition_chars().all(|(chars, is_sep)| {
        if is_sep {
            true
        } else {
            chars.chars().all(|c| c.is_alphabetic() || c == '_')
        }
    })
}
