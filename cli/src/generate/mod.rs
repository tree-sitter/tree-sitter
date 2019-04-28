use self::build_tables::build_tables;
use self::parse_grammar::parse_grammar;
use self::prepare_grammar::prepare_grammar;
use self::render::render_c_code;
use crate::error::{Error, Result};
use lazy_static::lazy_static;
use regex::{Regex, RegexBuilder};
use std::fs;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};

mod build_tables;
mod grammars;
mod nfa;
mod npm_files;
pub mod parse_grammar;
mod prepare_grammar;
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
    grammar_path: Option<&str>,
    minimize: bool,
    state_ids_to_log: Vec<usize>,
) -> Result<()> {
    let repo_src_path = repo_path.join("src");
    let repo_header_path = repo_src_path.join("tree_sitter");

    fs::create_dir_all(&repo_src_path)?;
    fs::create_dir_all(&repo_header_path)?;

    let grammar_json;
    match grammar_path {
        Some(path) => {
            grammar_json = load_grammar_file(path.as_ref())?;
        }
        None => {
            let grammar_js_path = grammar_path.map_or(repo_path.join("grammar.js"), |s| s.into());
            grammar_json = load_grammar_file(&grammar_js_path)?;
            fs::write(&repo_src_path.join("grammar.json"), &grammar_json)?;
        }
    }

    let (language_name, c_code) =
        generate_parser_for_grammar_with_opts(&grammar_json, minimize, state_ids_to_log)?;
    fs::write(&repo_src_path.join("parser.c"), c_code)
        .map_err(|e| format!("Failed to write parser.c: {}", e))?;
    fs::write(
        &repo_header_path.join("parser.h"),
        tree_sitter::PARSER_HEADER,
    )
    .map_err(|e| format!("Failed to write parser.h: {}", e))?;
    ensure_file(&repo_src_path.join("binding.cc"), || {
        npm_files::binding_cc(&language_name)
    })?;
    ensure_file(&repo_path.join("binding.gyp"), || {
        npm_files::binding_gyp(&language_name)
    })?;
    ensure_file(&repo_path.join("index.js"), || {
        npm_files::index_js(&language_name)
    })?;
    Ok(())
}

pub fn generate_parser_for_grammar(grammar_json: &str) -> Result<(String, String)> {
    let grammar_json = JSON_COMMENT_REGEX.replace_all(grammar_json, "\n");
    generate_parser_for_grammar_with_opts(&grammar_json, true, Vec::new())
}

fn generate_parser_for_grammar_with_opts(
    grammar_json: &str,
    minimize: bool,
    state_ids_to_log: Vec<usize>,
) -> Result<(String, String)> {
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
    Ok((input_grammar.name, c_code))
}

fn load_grammar_file(grammar_path: &Path) -> Result<String> {
    match grammar_path.extension().and_then(|e| e.to_str()) {
        Some("js") => Ok(load_js_grammar_file(grammar_path)?),
        Some("json") => Ok(fs::read_to_string(grammar_path)?),
        _ => Err(Error(format!(
            "Unknown grammar file extension: {:?}",
            grammar_path
        ))),
    }
}

fn load_js_grammar_file(grammar_path: &Path) -> Result<String> {
    let mut node_process = Command::new("node")
        .env("TREE_SITTER_GRAMMAR_PATH", grammar_path)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("Failed to run `node`");

    let mut node_stdin = node_process
        .stdin
        .take()
        .expect("Failed to open stdin for node");
    let javascript_code = include_bytes!("./dsl.js");
    node_stdin
        .write(javascript_code)
        .expect("Failed to write to node's stdin");
    drop(node_stdin);
    let output = node_process
        .wait_with_output()
        .expect("Failed to read output from node");
    match output.status.code() {
        None => panic!("Node process was killed"),
        Some(0) => {}
        Some(code) => return Err(Error(format!("Node process exited with status {}", code))),
    }

    Ok(String::from_utf8(output.stdout).expect("Got invalid UTF8 from node"))
}

fn ensure_file<T: AsRef<[u8]>>(path: &PathBuf, f: impl Fn() -> T) -> Result<()> {
    if path.exists() {
        Ok(())
    } else {
        fs::write(path, f().as_ref())
            .map_err(|e| Error(format!("Failed to write file {:?}: {}", path, e)))
    }
}
