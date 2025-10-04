use std::{collections::BTreeMap, sync::LazyLock};
#[cfg(feature = "load")]
use std::{
    env, fs,
    io::Write,
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use bitflags::bitflags;
use log::warn;
use node_types::VariableInfo;
use regex::{Regex, RegexBuilder};
use rules::{Alias, Symbol};
#[cfg(feature = "load")]
use semver::Version;
#[cfg(feature = "load")]
use serde::Deserialize;
use serde::Serialize;
use thiserror::Error;

mod build_tables;
mod dedup;
mod grammars;
mod nfa;
mod node_types;
pub mod parse_grammar;
mod prepare_grammar;
#[cfg(feature = "qjs-rt")]
mod quickjs;
mod render;
mod rules;
mod tables;

use build_tables::build_tables;
pub use build_tables::ParseTableBuilderError;
use grammars::{InlinedProductionMap, InputGrammar, LexicalGrammar, SyntaxGrammar};
pub use node_types::{SuperTypeCycleError, VariableInfoError};
use parse_grammar::parse_grammar;
pub use parse_grammar::ParseGrammarError;
use prepare_grammar::prepare_grammar;
pub use prepare_grammar::PrepareGrammarError;
use render::render_c_code;
pub use render::{ABI_VERSION_MAX, ABI_VERSION_MIN};

static JSON_COMMENT_REGEX: LazyLock<Regex> = LazyLock::new(|| {
    RegexBuilder::new("^\\s*//.*")
        .multi_line(true)
        .build()
        .unwrap()
});

struct JSONOutput {
    #[cfg(feature = "load")]
    node_types_json: String,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    inlines: InlinedProductionMap,
    simple_aliases: BTreeMap<Symbol, Alias>,
    variable_info: Vec<VariableInfo>,
}

struct GeneratedParser {
    c_code: String,
    #[cfg(feature = "load")]
    node_types_json: String,
}

// NOTE: This constant must be kept in sync with the definition of
// `TREE_SITTER_LANGUAGE_VERSION` in `lib/include/tree_sitter/api.h`.
const LANGUAGE_VERSION: usize = 15;

pub const ALLOC_HEADER: &str = include_str!("templates/alloc.h");
pub const ARRAY_HEADER: &str = include_str!("templates/array.h");
pub const PARSER_HEADER: &str = include_str!("parser.h.inc");

pub type GenerateResult<T> = Result<T, GenerateError>;

#[derive(Debug, Error, Serialize)]
pub enum GenerateError {
    #[error("Error with specified path -- {0}")]
    GrammarPath(String),
    #[error(transparent)]
    IO(IoError),
    #[cfg(feature = "load")]
    #[error(transparent)]
    LoadGrammarFile(#[from] LoadGrammarError),
    #[error(transparent)]
    ParseGrammar(#[from] ParseGrammarError),
    #[error(transparent)]
    Prepare(#[from] PrepareGrammarError),
    #[error(transparent)]
    VariableInfo(#[from] VariableInfoError),
    #[error(transparent)]
    BuildTables(#[from] ParseTableBuilderError),
    #[cfg(feature = "load")]
    #[error(transparent)]
    ParseVersion(#[from] ParseVersionError),
    #[error(transparent)]
    SuperTypeCycle(#[from] SuperTypeCycleError),
}

#[derive(Debug, Error, Serialize)]
pub struct IoError {
    pub error: String,
    pub path: Option<String>,
}

impl IoError {
    fn new(error: &std::io::Error, path: Option<&Path>) -> Self {
        Self {
            error: error.to_string(),
            path: path.map(|p| p.to_string_lossy().to_string()),
        }
    }
}

impl std::fmt::Display for IoError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.error)?;
        if let Some(ref path) = self.path {
            write!(f, " ({path})")?;
        }
        Ok(())
    }
}

#[cfg(feature = "load")]
pub type LoadGrammarFileResult<T> = Result<T, LoadGrammarError>;

#[cfg(feature = "load")]
#[derive(Debug, Error, Serialize)]
pub enum LoadGrammarError {
    #[error("Path to a grammar file with `.js` or `.json` extension is required")]
    InvalidPath,
    #[error("Failed to load grammar.js -- {0}")]
    LoadJSGrammarFile(#[from] JSError),
    #[error("Failed to load grammar.json -- {0}")]
    IO(IoError),
    #[error("Unknown grammar file extension: {0:?}")]
    FileExtension(PathBuf),
}

#[cfg(feature = "load")]
#[derive(Debug, Error, Serialize)]
pub enum ParseVersionError {
    #[error("{0}")]
    Version(String),
    #[error("{0}")]
    JSON(String),
    #[error(transparent)]
    IO(IoError),
}

#[cfg(feature = "load")]
pub type JSResult<T> = Result<T, JSError>;

#[cfg(feature = "load")]
#[derive(Debug, Error, Serialize)]
pub enum JSError {
    #[error("Failed to run `{runtime}` -- {error}")]
    JSRuntimeSpawn { runtime: String, error: String },
    #[error("Got invalid UTF8 from `{runtime}` -- {error}")]
    JSRuntimeUtf8 { runtime: String, error: String },
    #[error("`{runtime}` process exited with status {code}")]
    JSRuntimeExit { runtime: String, code: i32 },
    #[error("Failed to open stdin for `{runtime}`")]
    JSRuntimeStdin { runtime: String },
    #[error("Failed to write {item} to `{runtime}`'s stdin -- {error}")]
    JSRuntimeWrite {
        runtime: String,
        item: String,
        error: String,
    },
    #[error("Failed to read output from `{runtime}` -- {error}")]
    JSRuntimeRead { runtime: String, error: String },
    #[error(transparent)]
    IO(IoError),
    #[cfg(feature = "qjs-rt")]
    #[error("Failed to get relative path")]
    RelativePath,
    #[error("Could not parse this package's version as semver -- {0}")]
    Semver(String),
    #[error("Failed to serialze grammar JSON -- {0}")]
    Serialzation(String),
    #[cfg(feature = "qjs-rt")]
    #[error("QuickJS error: {0}")]
    QuickJS(String),
}

#[cfg(feature = "load")]
impl From<serde_json::Error> for JSError {
    fn from(value: serde_json::Error) -> Self {
        Self::Serialzation(value.to_string())
    }
}

#[cfg(feature = "load")]
impl From<semver::Error> for JSError {
    fn from(value: semver::Error) -> Self {
        Self::Semver(value.to_string())
    }
}

#[cfg(feature = "qjs-rt")]
impl From<rquickjs::Error> for JSError {
    fn from(value: rquickjs::Error) -> Self {
        Self::QuickJS(value.to_string())
    }
}

bitflags! {
    #[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
    pub struct OptLevel: u32 {
        const MergeStates = 1 << 0;
    }
}

impl Default for OptLevel {
    fn default() -> Self {
        Self::MergeStates
    }
}

#[cfg(feature = "load")]
#[allow(clippy::too_many_arguments)]
pub fn generate_parser_in_directory<T, U, V>(
    repo_path: T,
    out_path: Option<U>,
    grammar_path: Option<V>,
    mut abi_version: usize,
    report_symbol_name: Option<&str>,
    js_runtime: Option<&str>,
    generate_parser: bool,
    optimizations: OptLevel,
) -> GenerateResult<()>
where
    T: Into<PathBuf>,
    U: Into<PathBuf>,
    V: Into<PathBuf>,
{
    let mut repo_path: PathBuf = repo_path.into();

    // Populate a new empty grammar directory.
    let grammar_path = if let Some(path) = grammar_path {
        let path_buf: PathBuf = path.into();
        if !path_buf
            .try_exists()
            .map_err(|e| GenerateError::GrammarPath(e.to_string()))?
        {
            fs::create_dir_all(&path_buf)
                .map_err(|e| GenerateError::IO(IoError::new(&e, Some(path_buf.as_path()))))?;
            repo_path = path_buf;
            repo_path.join("grammar.js")
        } else {
            path_buf
        }
    } else {
        repo_path.join("grammar.js")
    };

    // Read the grammar file.
    let grammar_json = load_grammar_file(&grammar_path, js_runtime)?;

    let src_path = out_path.map_or_else(|| repo_path.join("src"), |p| p.into());
    let header_path = src_path.join("tree_sitter");

    // Ensure that the output directory exists
    fs::create_dir_all(&src_path)
        .map_err(|e| GenerateError::IO(IoError::new(&e, Some(src_path.as_path()))))?;

    if grammar_path.file_name().unwrap() != "grammar.json" {
        fs::write(src_path.join("grammar.json"), &grammar_json)
            .map_err(|e| GenerateError::IO(IoError::new(&e, Some(src_path.as_path()))))?;
    }

    // If our job is only to generate `grammar.json` and not `parser.c`, stop here.
    let input_grammar = parse_grammar(&grammar_json)?;

    if !generate_parser {
        let node_types_json = generate_node_types_from_grammar(&input_grammar)?.node_types_json;
        write_file(&src_path.join("node-types.json"), node_types_json)?;
        return Ok(());
    }

    let semantic_version = read_grammar_version(&repo_path)?;

    if semantic_version.is_none() && abi_version > ABI_VERSION_MIN {
        warn!(
            concat!(
                "No `tree-sitter.json` file found in your grammar, ",
                "this file is required to generate with ABI {}. ",
                "Using ABI version {} instead.\n",
                "This file can be set up with `tree-sitter init`. ",
                "For more information, see https://tree-sitter.github.io/tree-sitter/cli/init."
            ),
            abi_version, ABI_VERSION_MIN
        );
        abi_version = ABI_VERSION_MIN;
    }

    // Generate the parser and related files.
    let GeneratedParser {
        c_code,
        node_types_json,
    } = generate_parser_for_grammar_with_opts(
        &input_grammar,
        abi_version,
        semantic_version.map(|v| (v.major as u8, v.minor as u8, v.patch as u8)),
        report_symbol_name,
        optimizations,
    )?;

    write_file(&src_path.join("parser.c"), c_code)?;
    write_file(&src_path.join("node-types.json"), node_types_json)?;
    fs::create_dir_all(&header_path)
        .map_err(|e| GenerateError::IO(IoError::new(&e, Some(header_path.as_path()))))?;
    write_file(&header_path.join("alloc.h"), ALLOC_HEADER)?;
    write_file(&header_path.join("array.h"), ARRAY_HEADER)?;
    write_file(&header_path.join("parser.h"), PARSER_HEADER)?;

    Ok(())
}

pub fn generate_parser_for_grammar(
    grammar_json: &str,
    semantic_version: Option<(u8, u8, u8)>,
) -> GenerateResult<(String, String)> {
    let grammar_json = JSON_COMMENT_REGEX.replace_all(grammar_json, "\n");
    let input_grammar = parse_grammar(&grammar_json)?;
    let parser = generate_parser_for_grammar_with_opts(
        &input_grammar,
        LANGUAGE_VERSION,
        semantic_version,
        None,
        OptLevel::empty(),
    )?;
    Ok((input_grammar.name, parser.c_code))
}

fn generate_node_types_from_grammar(input_grammar: &InputGrammar) -> GenerateResult<JSONOutput> {
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(input_grammar)?;
    let variable_info =
        node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases)?;

    #[cfg(feature = "load")]
    let node_types_json = node_types::generate_node_types_json(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
    )?;
    Ok(JSONOutput {
        #[cfg(feature = "load")]
        node_types_json: serde_json::to_string_pretty(&node_types_json).unwrap(),
        syntax_grammar,
        lexical_grammar,
        inlines,
        simple_aliases,
        variable_info,
    })
}

fn generate_parser_for_grammar_with_opts(
    input_grammar: &InputGrammar,
    abi_version: usize,
    semantic_version: Option<(u8, u8, u8)>,
    report_symbol_name: Option<&str>,
    optimizations: OptLevel,
) -> GenerateResult<GeneratedParser> {
    let JSONOutput {
        syntax_grammar,
        lexical_grammar,
        inlines,
        simple_aliases,
        variable_info,
        #[cfg(feature = "load")]
        node_types_json,
    } = generate_node_types_from_grammar(input_grammar)?;
    let supertype_symbol_map =
        node_types::get_supertype_symbol_map(&syntax_grammar, &simple_aliases, &variable_info);
    let tables = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
        &inlines,
        report_symbol_name,
        optimizations,
    )?;
    let c_code = render_c_code(
        &input_grammar.name,
        tables,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        abi_version,
        semantic_version,
        supertype_symbol_map,
    );
    Ok(GeneratedParser {
        c_code,
        #[cfg(feature = "load")]
        node_types_json,
    })
}

/// This will read the `tree-sitter.json` config file and attempt to extract the version.
///
/// If the file is not found in the current directory or any of its parent directories, this will
/// return `None` to maintain backwards compatibility. If the file is found but the version cannot
/// be parsed as semver, this will return an error.
#[cfg(feature = "load")]
fn read_grammar_version(repo_path: &Path) -> Result<Option<Version>, ParseVersionError> {
    #[derive(Deserialize)]
    struct TreeSitterJson {
        metadata: Metadata,
    }

    #[derive(Deserialize)]
    struct Metadata {
        version: String,
    }

    let filename = "tree-sitter.json";
    let mut path = repo_path.join(filename);

    loop {
        let json = path
            .exists()
            .then(|| {
                let contents = fs::read_to_string(path.as_path())
                    .map_err(|e| ParseVersionError::IO(IoError::new(&e, Some(path.as_path()))))?;
                serde_json::from_str::<TreeSitterJson>(&contents).map_err(|e| {
                    ParseVersionError::JSON(format!("Failed to parse `{}` -- {e}", path.display()))
                })
            })
            .transpose()?;
        if let Some(json) = json {
            return Version::parse(&json.metadata.version)
                .map_err(|e| {
                    ParseVersionError::Version(format!(
                        "Failed to parse `{}` version as semver -- {e}",
                        path.display()
                    ))
                })
                .map(Some);
        }
        path.pop(); // filename
        if !path.pop() {
            return Ok(None);
        }
        path.push(filename);
    }
}

#[cfg(feature = "load")]
pub fn load_grammar_file(
    grammar_path: &Path,
    js_runtime: Option<&str>,
) -> LoadGrammarFileResult<String> {
    if grammar_path.is_dir() {
        Err(LoadGrammarError::InvalidPath)?;
    }
    match grammar_path.extension().and_then(|e| e.to_str()) {
        Some("js") => Ok(load_js_grammar_file(grammar_path, js_runtime)?),
        Some("json") => Ok(fs::read_to_string(grammar_path)
            .map_err(|e| LoadGrammarError::IO(IoError::new(&e, Some(grammar_path))))?),
        _ => Err(LoadGrammarError::FileExtension(grammar_path.to_owned()))?,
    }
}

#[cfg(feature = "load")]
fn load_js_grammar_file(grammar_path: &Path, js_runtime: Option<&str>) -> JSResult<String> {
    let grammar_path = dunce::canonicalize(grammar_path)
        .map_err(|e| JSError::IO(IoError::new(&e, Some(grammar_path))))?;

    #[cfg(feature = "qjs-rt")]
    if js_runtime == Some("native") {
        return quickjs::execute_native_runtime(&grammar_path);
    }

    // The "file:///" prefix is incompatible with the quickjs runtime, but is required
    // for node and bun
    #[cfg(windows)]
    let grammar_path = PathBuf::from(format!("file:///{}", grammar_path.display()));

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
        .map_err(|e| JSError::JSRuntimeSpawn {
            runtime: js_runtime.to_string(),
            error: e.to_string(),
        })?;

    let mut js_stdin = js_process
        .stdin
        .take()
        .ok_or_else(|| JSError::JSRuntimeStdin {
            runtime: js_runtime.to_string(),
        })?;

    let cli_version = Version::parse(env!("CARGO_PKG_VERSION"))?;
    write!(
        js_stdin,
        "globalThis.TREE_SITTER_CLI_VERSION_MAJOR = {};
         globalThis.TREE_SITTER_CLI_VERSION_MINOR = {};
         globalThis.TREE_SITTER_CLI_VERSION_PATCH = {};",
        cli_version.major, cli_version.minor, cli_version.patch,
    )
    .map_err(|e| JSError::JSRuntimeWrite {
        runtime: js_runtime.to_string(),
        item: "tree-sitter version".to_string(),
        error: e.to_string(),
    })?;
    js_stdin
        .write(include_bytes!("./dsl.js"))
        .map_err(|e| JSError::JSRuntimeWrite {
            runtime: js_runtime.to_string(),
            item: "grammar dsl".to_string(),
            error: e.to_string(),
        })?;
    drop(js_stdin);

    let output = js_process
        .wait_with_output()
        .map_err(|e| JSError::JSRuntimeRead {
            runtime: js_runtime.to_string(),
            error: e.to_string(),
        })?;
    match output.status.code() {
        Some(0) => {
            let stdout = String::from_utf8(output.stdout).map_err(|e| JSError::JSRuntimeUtf8 {
                runtime: js_runtime.to_string(),
                error: e.to_string(),
            })?;

            let mut grammar_json = &stdout[..];

            if let Some(pos) = stdout.rfind('\n') {
                // If there's a newline, split the last line from the rest of the output
                let node_output = &stdout[..pos];
                grammar_json = &stdout[pos + 1..];

                let mut stdout = std::io::stdout().lock();
                stdout
                    .write_all(node_output.as_bytes())
                    .map_err(|e| JSError::IO(IoError::new(&e, None)))?;
                stdout
                    .write_all(b"\n")
                    .map_err(|e| JSError::IO(IoError::new(&e, None)))?;
                stdout
                    .flush()
                    .map_err(|e| JSError::IO(IoError::new(&e, None)))?;
            }

            Ok(serde_json::to_string_pretty(&serde_json::from_str::<
                serde_json::Value,
            >(grammar_json)?)?)
        }
        Some(code) => Err(JSError::JSRuntimeExit {
            runtime: js_runtime.to_string(),
            code,
        }),
        None => Err(JSError::JSRuntimeExit {
            runtime: js_runtime.to_string(),
            code: -1,
        }),
    }
}

#[cfg(feature = "load")]
pub fn write_file(path: &Path, body: impl AsRef<[u8]>) -> GenerateResult<()> {
    fs::write(path, body).map_err(|e| GenerateError::IO(IoError::new(&e, Some(path))))
}

#[cfg(test)]
mod tests {
    use super::{LANGUAGE_VERSION, PARSER_HEADER};
    #[test]
    fn test_language_versions_are_in_sync() {
        let api_h = include_str!("../../../lib/include/tree_sitter/api.h");
        let api_language_version = api_h
            .lines()
            .find_map(|line| {
                line.trim()
                    .strip_prefix("#define TREE_SITTER_LANGUAGE_VERSION ")
                    .and_then(|v| v.parse::<usize>().ok())
            })
            .expect("Failed to find TREE_SITTER_LANGUAGE_VERSION definition in api.h");
        assert_eq!(LANGUAGE_VERSION, api_language_version);
    }

    #[test]
    fn test_parser_header_in_sync() {
        let parser_h = include_str!("../../../lib/src/parser.h");
        assert!(
            parser_h == PARSER_HEADER,
            "parser.h.inc is out of sync with lib/src/parser.h. Run: cp lib/src/parser.h crates/generate/src/parser.h.inc"
        );
    }
}
