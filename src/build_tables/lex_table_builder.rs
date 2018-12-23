use crate::rules::Symbol;
use crate::tables::LexTable;
use crate::grammars::{SyntaxGrammar, LexicalGrammar};

pub(crate) struct LexTableBuilder<'a> {
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    table: LexTable,
}

impl<'a> LexTableBuilder<'a> {
    pub fn new(
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
    ) -> Self {
        Self {
            syntax_grammar, lexical_grammar, table: LexTable::default()
        }
    }

    pub fn build(self) -> (LexTable, LexTable, Option<Symbol>) {
        (LexTable::default(), LexTable::default(), None)
    }
}
