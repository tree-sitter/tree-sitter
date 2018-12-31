use crate::error::Result;
use crate::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar};
use crate::rules::{AliasMap, Symbol};
use crate::tables::{LexTable, ParseTable};

mod build_parse_table;
mod item;
mod item_set_builder;
mod lex_table_builder;
mod shrink_parse_table;
mod token_conflict_map;

use self::build_parse_table::build_parse_table;
use self::shrink_parse_table::shrink_parse_table;
use self::token_conflict_map::TokenConflictMap;

pub(crate) fn build_tables(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    inlines: &InlinedProductionMap,
) -> Result<(ParseTable, LexTable, LexTable, Option<Symbol>)> {
    let (mut parse_table, following_tokens) =
        build_parse_table(syntax_grammar, lexical_grammar, inlines)?;
    let token_conflict_map = TokenConflictMap::new(lexical_grammar, following_tokens);
    shrink_parse_table(&mut parse_table, syntax_grammar, simple_aliases);
    Ok((parse_table, LexTable::default(), LexTable::default(), None))
}
