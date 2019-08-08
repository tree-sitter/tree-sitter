mod build_tables;
mod dedup;
mod grammars;
mod nfa;
mod node_types;
mod npm_files;
pub mod parse_grammar;
mod prepare_grammar;
pub mod properties;
mod render;
mod rules;
mod tables;

use self::build_tables::build_tables;
use self::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar, VariableType};
use self::parse_grammar::parse_grammar;
use self::prepare_grammar::prepare_grammar;
use self::render::render_c_code;
use self::rules::AliasMap;
use crate::error::{Error, Result};
use lazy_static::lazy_static;
use regex::{Regex, RegexBuilder};
use std::collections::HashSet;
use std::fs::{self, File};
use std::io::{BufWriter, Write};
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
    properties_only: bool,
) -> Result<()> {
    let src_path = repo_path.join("src");
    let header_path = src_path.join("tree_sitter");
    let properties_dir_path = repo_path.join("properties");

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

    // If run with no arguments, read all of the property sheets and compile them to JSON.
    if grammar_path.is_none() {
        let token_names = get_token_names(&syntax_grammar, &lexical_grammar);
        if let Ok(entries) = fs::read_dir(properties_dir_path) {
            for entry in entries {
                let css_path = entry?.path();
                let css = fs::read_to_string(&css_path)?;
                let sheet = properties::generate_property_sheet(&css_path, &css, &token_names)?;
                let property_sheet_json_path = src_path
                    .join(css_path.file_name().unwrap())
                    .with_extension("json");
                let property_sheet_json_file =
                    File::create(&property_sheet_json_path).map_err(Error::wrap(|| {
                        format!("Failed to create {:?}", property_sheet_json_path)
                    }))?;
                let mut writer = BufWriter::new(property_sheet_json_file);
                serde_json::to_writer_pretty(&mut writer, &sheet)?;
            }
        }
    }

    // Generate the parser and related files.
    if !properties_only {
        let GeneratedParser {
            c_code,
            node_types_json,
        } = generate_parser_for_grammar_with_opts(
            &language_name,
            syntax_grammar,
            lexical_grammar,
            inlines,
            simple_aliases,
        )?;

        write_file(&src_path.join("parser.c"), c_code)?;
        write_file(&src_path.join("node-types.json"), node_types_json)?;
        write_file(&header_path.join("parser.h"), tree_sitter::PARSER_HEADER)?;
        ensure_file(&repo_path.join("index.js"), || {
            npm_files::index_js(&language_name)
        })?;
        ensure_file(&src_path.join("binding.cc"), || {
            npm_files::binding_cc(&language_name)
        })?;
        ensure_file(&repo_path.join("binding.gyp"), || {
            npm_files::binding_gyp(&language_name)
        })?;
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
    )?;
    Ok((input_grammar.name, parser.c_code))
}

fn generate_parser_for_grammar_with_opts(
    name: &String,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    inlines: InlinedProductionMap,
    simple_aliases: AliasMap,
) -> Result<GeneratedParser> {
    let variable_info = node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &inlines)?;
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
    );
    Ok(GeneratedParser {
        c_code,
        node_types_json: serde_json::to_string_pretty(&node_types_json).unwrap(),
    })
}

fn get_token_names(
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
) -> HashSet<String> {
    let mut result = HashSet::new();
    for variable in &lexical_grammar.variables {
        if variable.kind == VariableType::Named {
            result.insert(variable.name.clone());
        }
    }
    for token in &syntax_grammar.external_tokens {
        if token.kind == VariableType::Named {
            result.insert(token.name.clone());
        }
    }
    for variable in &syntax_grammar.variables {
        for production in &variable.productions {
            for step in &production.steps {
                if let Some(alias) = &step.alias {
                    if !step.symbol.is_non_terminal() && alias.is_named {
                        result.insert(alias.value.clone());
                    }
                }
            }
        }
    }
    result
}

fn load_grammar_file(grammar_path: &Path) -> Result<String> {
    match grammar_path.extension().and_then(|e| e.to_str()) {
        Some("js") => Ok(load_js_grammar_file(grammar_path)?),
        Some("json") => Ok(fs::read_to_string(grammar_path)?),
        _ => Err(Error::new(format!(
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
        Some(code) => return Error::err(format!("Node process exited with status {}", code)),
    }

    let mut result = String::from_utf8(output.stdout).expect("Got invalid UTF8 from node");
    result.push('\n');
    Ok(result)
}

fn write_file(path: &Path, body: impl AsRef<[u8]>) -> Result<()> {
    fs::write(path, body).map_err(Error::wrap(|| {
        format!("Failed to write {:?}", path.file_name().unwrap())
    }))
}

fn ensure_file<T: AsRef<[u8]>>(path: &PathBuf, f: impl Fn() -> T) -> Result<()> {
    if path.exists() {
        Ok(())
    } else {
        write_file(path, f().as_ref())
    }
}
