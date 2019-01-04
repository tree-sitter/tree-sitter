use crate::build_tables::build_tables;
use crate::error::Result;
use crate::parse_grammar::parse_grammar;
use crate::prepare_grammar::prepare_grammar;
use crate::render::render_c_code;

pub fn generate_parser_for_grammar(
    input: &str,
    minimize: bool,
    state_ids_to_log: Vec<usize>,
) -> Result<String> {
    let input_grammar = parse_grammar(input)?;
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(&input_grammar)?;
    let (parse_table, main_lex_table, keyword_lex_table, keyword_capture_token) = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &inlines,
        minimize,
        state_ids_to_log,
    )?;
    let c_code = render_c_code(
        &input_grammar.name,
        parse_table,
        main_lex_table,
        keyword_lex_table,
        keyword_capture_token,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
    );
    Ok(c_code)
}
