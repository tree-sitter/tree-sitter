mod binding_files;
mod build_tables;
mod char_tree;
mod dedup;
mod grammars;
mod nfa;
mod node_types;
pub mod parse_grammar;
mod prepare_grammar;
mod render;
mod rules;
mod tables;

use self::build_tables::build_tables;
use self::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar};
use self::parse_grammar::parse_grammar;
use self::prepare_grammar::prepare_grammar;
use self::render::render_c_code;
use self::rules::AliasMap;
use anyhow::{anyhow, Context, Result};
use lazy_static::lazy_static;
use regex::{Regex, RegexBuilder};
use semver::Version;
use std::fs;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};

lazy_static! {
    static ref JSON_COMMENT_REGEX: Regex = RegexBuilder::new("^\\s*//.*")
        .multi_line(true)
        .build()
        .unwrap();
}

struct GeneratedParser {
    c_code: String,
    node_types_json: String,
}

pub fn generate_parser_in_directory(
    repo_path: &PathBuf,
    grammar_path: Option<&str>,
    abi_version: usize,
    generate_bindings: bool,
    report_symbol_name: Option<&str>,
) -> Result<()> {
    let src_path = repo_path.join("src");
    let header_path = src_path.join("tree_sitter");

    // Ensure that the output directories exist.
    fs::create_dir_all(&src_path)?;
    fs::create_dir_all(&header_path)?;

    // Read the grammar.json.
    let grammar_json;
    match grammar_path {
        Some(path) => {
            grammar_json = load_grammar_file(path.as_ref())?;
        }
        None => {
            let grammar_js_path = grammar_path.map_or(repo_path.join("grammar.js"), |s| s.into());
            grammar_json = load_grammar_file(&grammar_js_path)?;
            fs::write(&src_path.join("grammar.json"), &grammar_json)?;
        }
    }

    // Parse and preprocess the grammar.
    let input_grammar = parse_grammar(&grammar_json)?;
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(&input_grammar)?;
    let language_name = input_grammar.name;

    // Generate the parser and related files.
    let GeneratedParser {
        c_code,
        node_types_json,
    } = generate_parser_for_grammar_with_opts(
        &language_name,
        syntax_grammar,
        lexical_grammar,
        inlines,
        simple_aliases,
        abi_version,
        report_symbol_name,
    )?;

    write_file(&src_path.join("parser.c"), c_code)?;
    write_file(&src_path.join("node-types.json"), node_types_json)?;
    write_file(&header_path.join("parser.h"), tree_sitter::PARSER_HEADER)?;

    if generate_bindings {
        binding_files::generate_binding_files(&repo_path, &language_name)?;
    }

    Ok(())
}

pub fn generate_parser_for_grammar(grammar_json: &str) -> Result<(String, String)> {
    let grammar_json = JSON_COMMENT_REGEX.replace_all(grammar_json, "\n");
    let input_grammar = parse_grammar(&grammar_json)?;
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(&input_grammar)?;
    let parser = generate_parser_for_grammar_with_opts(
        &input_grammar.name,
        syntax_grammar,
        lexical_grammar,
        inlines,
        simple_aliases,
        tree_sitter::LANGUAGE_VERSION,
        None,
    )?;
    Ok((input_grammar.name, parser.c_code))
}

fn generate_parser_for_grammar_with_opts(
    name: &String,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    inlines: InlinedProductionMap,
    simple_aliases: AliasMap,
    abi_version: usize,
    report_symbol_name: Option<&str>,
) -> Result<GeneratedParser> {
    let variable_info =
        node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases)?;
    let node_types_json = node_types::generate_node_types_json(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
    );
    let (parse_table, main_lex_table, keyword_lex_table, keyword_capture_token) = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
        &inlines,
        report_symbol_name,
    )?;
    let c_code = render_c_code(
        name,
        parse_table,
        main_lex_table,
        keyword_lex_table,
        keyword_capture_token,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        abi_version,
    );
    Ok(GeneratedParser {
        c_code,
        node_types_json: serde_json::to_string_pretty(&node_types_json).unwrap(),
    })
}

pub fn load_grammar_file(grammar_path: &Path) -> Result<String> {
    match grammar_path.extension().and_then(|e| e.to_str()) {
        Some("js") => Ok(load_js_grammar_file(grammar_path)?),
        Some("json") => Ok(fs::read_to_string(grammar_path)?),
        _ => Err(anyhow!(
            "Unknown grammar file extension: {:?}",
            grammar_path
        )),
    }
}

fn load_js_grammar_file(grammar_path: &Path) -> Result<String> {
    let grammar_path = fs::canonicalize(grammar_path)?;
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
    let cli_version = Version::parse(env!("CARGO_PKG_VERSION"))
        .expect("Could not parse this package's version as semver.");
    write!(
        node_stdin,
        "global.TREE_SITTER_CLI_VERSION_MAJOR = {};
        global.TREE_SITTER_CLI_VERSION_MINOR = {};
        global.TREE_SITTER_CLI_VERSION_PATCH = {};",
        cli_version.major, cli_version.minor, cli_version.patch,
    )
    .expect("Failed to write tree-sitter version to node's stdin");
    let javascript_code = include_bytes!("./dsl.js");
    node_stdin
        .write(javascript_code)
        .expect("Failed to write grammar dsl to node's stdin");
    drop(node_stdin);
    let output = node_process
        .wait_with_output()
        .expect("Failed to read output from node");
    match output.status.code() {
        None => panic!("Node process was killed"),
        Some(0) => {}
        Some(code) => return Err(anyhow!("Node process exited with status {}", code)),
    }

    let mut result = String::from_utf8(output.stdout).expect("Got invalid UTF8 from node");
    result.push('\n');
    Ok(result)
}

fn write_file(path: &Path, body: impl AsRef<[u8]>) -> Result<()> {
    fs::write(path, body)
        .with_context(|| format!("Failed to write {:?}", path.file_name().unwrap()))
}
