mod build_parse_table;
mod coincident_tokens;
mod item;
mod item_set_builder;
mod lex_table_builder;
mod shrink_parse_table;
mod token_conflicts;

use self::build_parse_table::build_parse_table;
use self::coincident_tokens::CoincidentTokenIndex;
use self::item::LookaheadSet;
use self::shrink_parse_table::shrink_parse_table;
use self::token_conflicts::TokenConflictMap;
use crate::error::Result;
use crate::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar};
use crate::rules::{AliasMap, Symbol};
use crate::tables::{LexTable, ParseAction, ParseTable, ParseTableEntry};

pub(crate) fn build_tables(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    inlines: &InlinedProductionMap,
) -> Result<(ParseTable, LexTable, LexTable, Option<Symbol>)> {
    let (mut parse_table, following_tokens) =
        build_parse_table(syntax_grammar, lexical_grammar, inlines)?;
    let token_conflict_map = TokenConflictMap::new(lexical_grammar, following_tokens);
    let coincident_token_index = CoincidentTokenIndex::new(&parse_table);
    populate_error_state(
        &mut parse_table,
        syntax_grammar,
        lexical_grammar,
        &coincident_token_index,
        &token_conflict_map,
    );
    shrink_parse_table(
        &mut parse_table,
        syntax_grammar,
        simple_aliases,
        &token_conflict_map,
    );
    Ok((parse_table, LexTable::default(), LexTable::default(), None))
}

fn populate_error_state(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    coincident_token_index: &CoincidentTokenIndex,
    token_conflict_map: &TokenConflictMap,
) {
    let state = &mut parse_table.states[0];
    let n = lexical_grammar.variables.len();
    let conflict_free_tokens = LookaheadSet::with((0..n).into_iter().filter_map(|i| {
        let conflicts_with_other_tokens = (0..n).into_iter().all(|j| {
            j == i
                || coincident_token_index.contains(Symbol::terminal(i), Symbol::terminal(j))
                || !token_conflict_map.does_conflict(i, j)
        });
        if conflicts_with_other_tokens {
            None
        } else {
            Some(Symbol::terminal(i))
        }
    }));

    let recover_entry = ParseTableEntry {
        reusable: false,
        actions: vec![ParseAction::Recover],
    };

    for i in 0..n {
        let symbol = Symbol::terminal(i);
        let can_be_used_for_recovery = conflict_free_tokens.contains(&symbol)
            || conflict_free_tokens.iter().all(|t| {
                coincident_token_index.contains(symbol, t)
                    || !token_conflict_map.does_conflict(i, t.index)
            });
        if can_be_used_for_recovery {
            eprintln!("include {}", &lexical_grammar.variables[symbol.index].name);
            state
                .terminal_entries
                .entry(symbol)
                .or_insert_with(|| recover_entry.clone());
        } else {
            eprintln!("exclude {}", &lexical_grammar.variables[symbol.index].name);
        }
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
