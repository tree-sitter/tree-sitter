use self::build_tables::build_tables;
use self::parse_grammar::parse_grammar;
use self::prepare_grammar::prepare_grammar;
use self::render::render_c_code;
use crate::error::Result;
use regex::{Regex, RegexBuilder};
use std::fs;
use std::io::Write;
use std::path::PathBuf;
use std::process::{Command, Stdio};

mod build_tables;
mod grammars;
mod nfa;
mod parse_grammar;
mod prepare_grammar;
mod properties;
mod render;
mod rules;
mod tables;

lazy_static! {
    static ref JSON_COMMENT_REGEX: Regex = RegexBuilder::new("^\\s*//.*")
        .multi_line(true)
        .build()
        .unwrap();
}

pub fn generate_parser_in_directory(
    repo_path: &PathBuf,
    minimize: bool,
    state_ids_to_log: Vec<usize>,
    properties_only: bool,
) -> Result<()> {
    if !properties_only {
        let grammar_json = load_js_grammar_file(&repo_path.join("grammar.js"));
        let c_code =
            generate_parser_for_grammar_with_opts(&grammar_json, minimize, state_ids_to_log)?;
        fs::write(repo_path.join("src").join("parser.c"), c_code)?;
    }
    properties::generate_property_sheets(repo_path)?;
    Ok(())
}

#[cfg(test)]
pub fn generate_parser_for_grammar(grammar_json: &String) -> Result<String> {
    let grammar_json = JSON_COMMENT_REGEX.replace_all(grammar_json, "\n");
    generate_parser_for_grammar_with_opts(&grammar_json, true, Vec::new())
}

fn generate_parser_for_grammar_with_opts(
    grammar_json: &str,
    minimize: bool,
    state_ids_to_log: Vec<usize>,
) -> Result<String> {
    let input_grammar = parse_grammar(grammar_json)?;
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
    Ok(render_c_code(
        &input_grammar.name,
        parse_table,
        main_lex_table,
        keyword_lex_table,
        keyword_capture_token,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
    ))
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
