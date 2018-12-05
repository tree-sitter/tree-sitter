use crate::rules::{Symbol, AliasMap};
use crate::grammars::{SyntaxGrammar, LexicalGrammar};
use crate::tables::{ParseTable, LexTable};

pub fn render_c_code(
    name: &str,
    parse_table: ParseTable,
    main_lex_table: LexTable,
    keyword_lex_table: LexTable,
    keyword_capture_token: Option<Symbol>,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    simple_aliases: AliasMap,
) -> String {
    unimplemented!();
}
