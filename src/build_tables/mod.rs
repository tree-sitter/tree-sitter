mod item;

use std::collections::{HashMap, VecDeque};
use crate::grammars::{SyntaxGrammar, LexicalGrammar};
use crate::tables::{ParseTable, LexTable, ParseStateId};
use crate::rules::{AliasMap, Symbol};
use crate::error::Result;
use self::item::ParseItemSet;

type SymbolSequence = Vec<Symbol>;

struct ParseStateQueueEntry {
    preceding_symbols: SymbolSequence,
    item_set: ParseItemSet,
    state_id: ParseStateId,
}

struct ParseTableBuilder<'a> {
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    simple_aliases: &'a AliasMap,
    state_ids_by_item_set: HashMap<ParseItemSet, ParseStateId>,
    item_sets_by_state_id: Vec<&'a ParseItemSet>,
    parse_state_queue: VecDeque<ParseStateQueueEntry>,
    parse_table: ParseTable,
}

pub fn build_tables(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap
) -> Result<(ParseTable, LexTable, LexTable, Option<Symbol>)> {
    unimplemented!();
}
