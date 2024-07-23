use std::{
    env, fs,
    io::Write,
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use anyhow::{anyhow, Context, Result};
use build_tables::build_tables;
use grammar_files::path_in_ignore;
use grammars::InputGrammar;
use lazy_static::lazy_static;
use parse_grammar::parse_grammar;
use prepare_grammar::prepare_grammar;
use regex::{Regex, RegexBuilder};
use render_target::RenderTarget;
use render_target_c::RenderTargetC;
use render_target_swift::RenderTargetSwift;
use render::Generator;
use semver::Version;

mod build_tables;
mod dedup;
mod grammar_files;
mod grammars;
mod nfa;
mod node_types;
pub mod parse_grammar;
mod prepare_grammar;
mod render_buffer;
mod render_context;
#[macro_use]
mod render_target;
mod render_target_c;
mod render_target_swift;
mod render;
mod rules;
mod tables;

pub use grammar_files::lookup_package_json_for_path;

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

pub const ALLOC_HEADER: &str = include_str!("./templates/alloc.h");

pub fn generate_parser_in_directory(
    repo_path: &Path,
    grammar_path: Option<&str>,
    abi_version: usize,
    generate_bindings: bool,
    report_symbol_name: Option<&str>,
    js_runtime: Option<&str>,
) -> Result<()> {
    let mut repo_path = repo_path.to_owned();
    let mut grammar_path = grammar_path;

    // Populate a new empty grammar directory.
    if let Some(path) = grammar_path {
        let path = PathBuf::from(path);
        if !path
            .try_exists()
            .with_context(|| "Some error with specified path")?
        {
            fs::create_dir_all(&path)?;
            grammar_path = None;
            repo_path = path;
        }
    }

    if repo_path.is_dir() && !repo_path.join("grammar.js").exists() && !path_in_ignore(&repo_path) {
        if let Some(dir_name) = repo_path
            .file_name()
            .map(|x| x.to_string_lossy().to_ascii_lowercase())
        {
            if let Some(language_name) = dir_name
                .strip_prefix("tree-sitter-")
                .or_else(|| Some(dir_name.as_ref()))
            {
                grammar_files::generate_grammar_files(&repo_path, language_name, false)?;
            }
        }
    }

    // Read the grammar.json.
    let grammar_json = if let Some(path) = grammar_path {
        load_grammar_file(path.as_ref(), js_runtime)?
    } else {
        let grammar_js_path =
            grammar_path.map_or(repo_path.join("grammar.js"), std::convert::Into::into);
        load_grammar_file(&grammar_js_path, js_runtime)?
    };

    let src_path = repo_path.join("src");
    let header_path = src_path.join("tree_sitter");

    // Ensure that the output directories exist.
    fs::create_dir_all(&src_path)?;
    fs::create_dir_all(&header_path)?;

    if grammar_path.is_none() {
        fs::write(src_path.join("grammar.json"), &grammar_json)
            .with_context(|| format!("Failed to write grammar.json to {src_path:?}"))?;
    }

    // Parse and preprocess the grammar.
    let input_grammar = parse_grammar(&grammar_json)?;

    // Generate the parser and related files.
    let GeneratedParser {
        c_code,
        node_types_json,
    } = generate_parser_for_grammar_with_opts(&input_grammar, abi_version, report_symbol_name)?;

    write_file(&src_path.join("parser.c"), c_code)?;
    write_file(&src_path.join("node-types.json"), node_types_json)?;
    write_file(&header_path.join("alloc.h"), ALLOC_HEADER)?;
    write_file(&header_path.join("array.h"), tree_sitter::ARRAY_HEADER)?;
    write_file(&header_path.join("parser.h"), tree_sitter::PARSER_HEADER)?;

    if !path_in_ignore(&repo_path) {
        grammar_files::generate_grammar_files(&repo_path, &input_grammar.name, generate_bindings)?;
    }

    Ok(())
}

pub fn generate_parser_for_grammar(grammar_json: &str) -> Result<(String, String)> {
    let grammar_json = JSON_COMMENT_REGEX.replace_all(grammar_json, "\n");
    let input_grammar = parse_grammar(&grammar_json)?;
    let parser =
        generate_parser_for_grammar_with_opts(&input_grammar, tree_sitter::LANGUAGE_VERSION, None)?;
    Ok((input_grammar.name.clone(), parser.c_code))
}

fn generate_parser_for_grammar_with_opts(
    input_grammar: &InputGrammar,
    abi_version: usize,
    report_symbol_name: Option<&str>,
) -> Result<GeneratedParser> {
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(input_grammar)?;
    let variable_info =
        node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases)?;
    let node_types_json = node_types::generate_node_types_json(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
    );
    let tables = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
        &inlines,
        report_symbol_name,
    )?;
    let generator = Generator::new(
        input_grammar.name.clone(),
        tables,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        abi_version
    );
    let mut target : Box<dyn RenderTarget> = Box::new(RenderTargetC::new(2));
    generator.generate(&mut target);
    let c_code = target.buffer_ref().get_text();
    Ok(GeneratedParser {
        c_code,
        node_types_json: serde_json::to_string_pretty(&node_types_json).unwrap(),
    })
}

pub fn load_grammar_file(grammar_path: &Path, js_runtime: Option<&str>) -> Result<String> {
    if grammar_path.is_dir() {
        return Err(anyhow!(
            "Path to a grammar file with `.js` or `.json` extension is required"
        ));
    }
    match grammar_path.extension().and_then(|e| e.to_str()) {
        Some("js") => Ok(load_js_grammar_file(grammar_path, js_runtime)
            .with_context(|| "Failed to load grammar.js")?),
        Some("json") => {
            Ok(fs::read_to_string(grammar_path).with_context(|| "Failed to load grammar.json")?)
        }
        _ => Err(anyhow!("Unknown grammar file extension: {grammar_path:?}",)),
    }
}

fn load_js_grammar_file(grammar_path: &Path, js_runtime: Option<&str>) -> Result<String> {
    let grammar_path = fs::canonicalize(grammar_path)?;

    #[cfg(windows)]
    let grammar_path = url::Url::from_file_path(grammar_path)
        .expect("Failed to convert path to URL")
        .to_string();

    let js_runtime = js_runtime.unwrap_or("node");

    let mut js_command = Command::new(js_runtime);
    match js_runtime {
        "node" => {
            js_command.args(["--input-type=module", "-"]);
        }
        "bun" => {
            js_command.arg("-");
        }
        "deno" => {
            js_command.args(["run", "--allow-all", "-"]);
        }
        _ => {}
    }

    let mut js_process = js_command
        .env("TREE_SITTER_GRAMMAR_PATH", grammar_path)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .with_context(|| format!("Failed to run `{js_runtime}`"))?;

    let mut js_stdin = js_process
        .stdin
        .take()
        .with_context(|| format!("Failed to open stdin for {js_runtime}"))?;
    let cli_version = Version::parse(env!("CARGO_PKG_VERSION"))
        .with_context(|| "Could not parse this package's version as semver.")?;
    write!(
        js_stdin,
        "globalThis.TREE_SITTER_CLI_VERSION_MAJOR = {};
         globalThis.TREE_SITTER_CLI_VERSION_MINOR = {};
         globalThis.TREE_SITTER_CLI_VERSION_PATCH = {};",
        cli_version.major, cli_version.minor, cli_version.patch,
    )
    .with_context(|| format!("Failed to write tree-sitter version to {js_runtime}'s stdin"))?;
    js_stdin
        .write(include_bytes!("./dsl.js"))
        .with_context(|| format!("Failed to write grammar dsl to {js_runtime}'s stdin"))?;
    drop(js_stdin);

    let output = js_process
        .wait_with_output()
        .with_context(|| format!("Failed to read output from {js_runtime}"))?;
    match output.status.code() {
        None => panic!("{js_runtime} process was killed"),
        Some(0) => {
            let stdout = String::from_utf8(output.stdout)
                .with_context(|| format!("Got invalid UTF8 from {js_runtime}"))?;

            let mut grammar_json = &stdout[..];

            if let Some(pos) = stdout.rfind('\n') {
                // If there's a newline, split the last line from the rest of the output
                let node_output = &stdout[..pos];
                grammar_json = &stdout[pos + 1..];

                let mut stdout = std::io::stdout().lock();
                stdout.write_all(node_output.as_bytes())?;
                stdout.write_all(b"\n")?;
                stdout.flush()?;
            }

            Ok(serde_json::to_string_pretty(
                &serde_json::from_str::<serde_json::Value>(grammar_json)
                    .with_context(|| "Failed to parse grammar JSON")?,
            )
            .with_context(|| "Failed to serialize grammar JSON")?
                + "\n")
        }
        Some(code) => Err(anyhow!("{js_runtime} process exited with status {code}")),
    }
}

fn write_file(path: &Path, body: impl AsRef<[u8]>) -> Result<()> {
    fs::write(path, body)
        .with_context(|| format!("Failed to write {:?}", path.file_name().unwrap()))
}

/// Generate Swift source for the given json grammar description.
pub fn swift_parser_source_from_json(json_str: &str, access_modifier: String, abi_version: u32) -> Result<String> {
    let input_grammar: InputGrammar = parse_grammar(json_str)?;
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(&input_grammar)?;
    let variable_info =
        node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases)?;
    let tables = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
        &inlines,
        None,
    )?;
    let mut target : Box<dyn RenderTarget> = Box::new(RenderTargetSwift::new(access_modifier));
    let generator = Generator::new(
        input_grammar.name.clone(),
        tables,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        abi_version as usize,
    );
    generator.generate(&mut target);
    Ok(target.buffer_ref().get_text())
}

// TODO: use bindgen on include/tree_sitter_cli.h
pub const SWIFTGEN_ERROR_INVALID_VERSION: u32 = 1;
pub const SWIFTGEN_ERROR_INVALID_INPUT: u32 = 2;
pub const SWIFTGEN_ERROR_OUTPUT_TOO_LONG: u32 = 3;
pub const SWIFTGEN_ERROR_OTHER: u32 = 4;

/// Generate Swift source for the given json grammar description. If successful,
/// return the result of invoking the given function with the generated source;
/// otherwise return NULL.
#[no_mangle]
pub extern "C" fn swiftgen(
    json_bytes: *const u8, 
    json_len: u32, 
    access_bytes: *const u8,
    access_len: u32,
    abi_version: u32, 
    completion: unsafe extern "C" fn(u32, *const u8, u32) -> *const std::ffi::c_void
) -> *const std::ffi::c_void {
    fn fail(completion: unsafe extern "C" fn(u32, *const u8, u32) -> *const std::ffi::c_void, status: u32, message: &str) -> *const std::ffi::c_void {
        let message_bytes = message.as_bytes();
        unsafe { completion(status, message_bytes.as_ptr(), message_bytes.len() as u32) }
    }
    let abi_version = if abi_version == 0 { render::ABI_VERSION_MAX } else { abi_version as usize };
    if !(render::ABI_VERSION_MIN <= abi_version && abi_version <= render::ABI_VERSION_MAX) {
        return fail(completion, SWIFTGEN_ERROR_INVALID_VERSION, "Invalid ABI version")
    }
    let access_slice = unsafe { std::slice::from_raw_parts(access_bytes, access_len as usize) };
    let access_modifier : String;
    match std::str::from_utf8(access_slice) {
        Ok(str) => 
            access_modifier = str.to_string(),
        Err(err) =>
            return fail(completion, SWIFTGEN_ERROR_INVALID_INPUT, format!("Invalid input: {err}").as_ref())
    }
    let json_slice = unsafe { std::slice::from_raw_parts(json_bytes, json_len as usize) };
    match std::str::from_utf8(json_slice) {
        Ok(json_str) => {
            match swift_parser_source_from_json(json_str, access_modifier, abi_version as u32) {
                Ok(swift_text) => {
                    let swift_bytes = swift_text.as_bytes();
                    if swift_bytes.len() <= u32::MAX as usize {
                        unsafe { completion(0, swift_bytes.as_ptr(), swift_bytes.len() as u32) }
                    } else {
                        fail(completion, SWIFTGEN_ERROR_OUTPUT_TOO_LONG, "The length of the generated source exceeds the allowed maximum.")
                    }
                },
                Err(err) => {
                    fail(completion, SWIFTGEN_ERROR_OTHER, format!("Parser generation failed: {err}").as_ref())
                }
            }
        },
        Err(err) => {
            fail(completion, SWIFTGEN_ERROR_INVALID_INPUT, format!("Invalid input: {err}").as_ref())
        }
    }
}

#[no_mangle]
pub extern "C" fn swiftgen_max_abi_version() -> u32 {
    render::ABI_VERSION_MAX as u32
}
