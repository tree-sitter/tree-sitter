use self::build_tables::build_tables;
use self::parse_grammar::parse_grammar;
use self::prepare_grammar::prepare_grammar;
use self::render::render_c_code;
use crate::error::Result;
use std::io::Write;
use std::path::PathBuf;
use std::process::{Command, Stdio};

mod build_tables;
mod grammars;
mod nfa;
mod parse_grammar;
mod prepare_grammar;
mod render;
mod rules;
mod tables;

pub fn generate_parser_for_grammar(
    grammar_path: &PathBuf,
    minimize: bool,
    state_ids_to_log: Vec<usize>,
) -> Result<String> {
    let grammar_json = load_js_grammar_file(grammar_path);
    let input_grammar = parse_grammar(&grammar_json)?;
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

fn load_js_grammar_file(grammar_path: &PathBuf) -> String {
    let mut node_process = Command::new("node")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("Failed to run `node`");

    let js_prelude = include_str!("./dsl.js");
    let mut node_stdin = node_process
        .stdin
        .take()
        .expect("Failed to open stdin for node");
    write!(
        node_stdin,
        "{}\nconsole.log(JSON.stringify(require(\"{}\"), null, 2));\n",
        js_prelude,
        grammar_path.to_str().unwrap()
    )
    .expect("Failed to write to node's stdin");
    drop(node_stdin);
    let output = node_process
        .wait_with_output()
        .expect("Failed to read output from node");
    match output.status.code() {
        None => panic!("Node process was killed"),
        Some(0) => {}
        Some(code) => panic!(format!("Node process exited with status {}", code)),
    }

    String::from_utf8(output.stdout).expect("Got invalid UTF8 from node")
}
