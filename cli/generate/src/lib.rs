use std::{
    env, fs,
    io::Write,
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use anyhow::{anyhow, Context, Result};
use build_tables::build_tables;
use grammars::InputGrammar;
use lazy_static::lazy_static;
use parse_grammar::parse_grammar;
use prepare_grammar::prepare_grammar;
use regex::{Regex, RegexBuilder};
use render::render_c_code;
use semver::Version;

mod build_tables;
mod dedup;
mod grammar_files;
mod grammars;
mod nfa;
mod node_types;
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

struct GeneratedParser {
    c_code: String,
    node_types_json: String,
}

pub const ALLOC_HEADER: &str = include_str!("templates/alloc.h");
pub const ARRAY_HEADER: &str = include_str!("templates/array.h");

pub fn generate_parser_in_directory(
    repo_path: &Path,
    out_path: Option<&str>,
    grammar_path: Option<&str>,
    abi_version: usize,
    report_symbol_name: Option<&str>,
    js_runtime: Option<&str>,
    #[cfg(feature = "qjs-rt")] parser_directories: &[PathBuf],
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

    let grammar_path = grammar_path.map_or_else(|| repo_path.join("grammar.js"), PathBuf::from);

    // Read the grammar file.
    let grammar_json = load_grammar_file(
        &grammar_path,
        js_runtime,
        #[cfg(feature = "qjs-rt")]
        parser_directories,
    )?;

    let src_path = out_path.map_or_else(|| repo_path.join("src"), PathBuf::from);
    let header_path = src_path.join("tree_sitter");

    // Ensure that the output directories exist.
    fs::create_dir_all(&src_path)?;
    fs::create_dir_all(&header_path)?;

    if grammar_path.file_name().unwrap() != "grammar.json" {
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
    write_file(&header_path.join("array.h"), ARRAY_HEADER)?;
    write_file(&header_path.join("parser.h"), tree_sitter::PARSER_HEADER)?;

    Ok(())
}

pub fn generate_parser_for_grammar(grammar_json: &str) -> Result<(String, String)> {
    let grammar_json = JSON_COMMENT_REGEX.replace_all(grammar_json, "\n");
    let input_grammar = parse_grammar(&grammar_json)?;
    let parser =
        generate_parser_for_grammar_with_opts(&input_grammar, tree_sitter::LANGUAGE_VERSION, None)?;
    Ok((input_grammar.name, parser.c_code))
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
    let c_code = render_c_code(
        &input_grammar.name,
        tables,
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

pub fn load_grammar_file(
    grammar_path: &Path,
    js_runtime: Option<&str>,
    #[cfg(feature = "qjs-rt")] parser_directories: &[PathBuf],
) -> Result<String> {
    if grammar_path.is_dir() {
        return Err(anyhow!(
            "Path to a grammar file with `.js` or `.json` extension is required"
        ));
    }
    match grammar_path.extension().and_then(|e| e.to_str()) {
        Some("js") => Ok(load_js_grammar_file(
            grammar_path,
            js_runtime,
            #[cfg(feature = "qjs-rt")]
            parser_directories,
        )
        .with_context(|| "Failed to load grammar.js")?),
        Some("json") => {
            Ok(fs::read_to_string(grammar_path).with_context(|| "Failed to load grammar.json")?)
        }
        _ => Err(anyhow!("Unknown grammar file extension: {grammar_path:?}",)),
    }
}

const DSL: &[u8] = include_bytes!("dsl.js");

fn load_js_grammar_file(
    grammar_path: &Path,
    js_runtime: Option<&str>,
    #[cfg(feature = "qjs-rt")] parser_directories: &[PathBuf],
) -> Result<String> {
    let grammar_path = fs::canonicalize(grammar_path)?;

    #[cfg(windows)]
    let grammar_path = url::Url::from_file_path(grammar_path)
        .expect("Failed to convert path to URL")
        .to_string();

    #[cfg(feature = "qjs-rt")]
    if js_runtime == Some("native") {
        return qjs::execute_native_runtime(&grammar_path, parser_directories);
    }

    let js_runtime = js_runtime.unwrap_or("node");

    let mut js_command = Command::new(js_runtime);
    match js_runtime {
        "node" => {
            js_command.args(["--experimental-fetch", "--input-type=module", "-"]);
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
        .write(DSL)
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

#[cfg(feature = "qjs-rt")]
mod qjs {
    use std::{
        env,
        path::{Path, PathBuf},
    };

    use anyhow::{Context, Result as AnyResult};
    use rquickjs::{
        loader::{FileResolver, ScriptLoader},
        Array, Context as QJSContext, Ctx, Error, Function, Module, Object, Result as QJSResult,
        Runtime, String as QJSString, Value,
    };

    const STDLIB: &[u8] = include_bytes!("stdlib.js");

    fn pretty_print_js_error(v: Value) -> anyhow::Error {
        let Some(exception) = v.into_exception() else {
            return anyhow::anyhow!("Expected a JS exception");
        };

        anyhow::anyhow!(exception.to_string())
    }

    #[allow(clippy::needless_pass_by_value)]
    fn print(s: String) {
        println!("{s}");
    }

    #[allow(clippy::needless_pass_by_value)]
    fn warn(s: String) {
        eprintln!("Warning: {s}");
    }

    #[allow(clippy::needless_pass_by_value)]
    fn error(s: String) {
        eprintln!("Error: {s}");
    }

    #[allow(clippy::needless_pass_by_value)]
    fn stat_path(ctx: Ctx, path: String) -> QJSResult<Object> {
        let path = Path::new(&path);
        let globals = ctx.globals();
        let searchable_dirs = globals.get::<_, Array>("_searchableDirs")?;
        let mut last_error = None;

        for d in searchable_dirs.iter::<QJSString>() {
            let d = d?.to_string()?;
            let dir = Path::new(&d);
            let mut target_path = dir.join(path);
            let mut metadata = std::fs::metadata(&target_path);
            if metadata.is_err() && target_path.extension().is_none() {
                target_path = dir.join(path.with_extension("js"));
                if target_path.exists() {
                    metadata = std::fs::metadata(&target_path);
                }
            }
            match metadata {
                Ok(metadata) => {
                    let obj = Object::new(ctx.clone())?;
                    obj.set("resolved", target_path.to_string_lossy().to_string())?;
                    obj.set("errno", 0)?;
                    obj.set("isFile", metadata.is_file())?;
                    obj.set("isDir", metadata.is_dir())?;

                    // This module should be able to resolve imports from the same directory.
                    // We sort the array to ensure that the empty string is last, otherwise
                    // imports that import a file of the same name as the folder will resolve to
                    // the folder itself - e.g. importing `./common` from a folder called `common`
                    // should give us `./common/common.js`, not `./common` again.
                    let dir = target_path.parent().unwrap().to_string_lossy().to_string();
                    if !searchable_dirs
                        .iter::<QJSString>()
                        .any(|d| d.map_or(false, |d| d.to_string().map_or(false, |d| d == dir)))
                    {
                        let mut rust_array = searchable_dirs
                            .iter::<QJSString>()
                            .map(|d| d.unwrap().to_string().unwrap())
                            .collect::<Vec<_>>();
                        rust_array
                            .push(target_path.parent().unwrap().to_string_lossy().to_string());
                        rust_array.sort_by(|a, b| {
                            if a.is_empty() {
                                std::cmp::Ordering::Greater
                            } else if b.is_empty() {
                                std::cmp::Ordering::Less
                            } else {
                                std::cmp::Ordering::Equal
                            }
                        });
                        let searchable_dirs = Array::new(ctx.clone())?;
                        for (i, dir) in rust_array.iter().enumerate() {
                            searchable_dirs.set(i, dir)?;
                        }
                        globals.set("_searchableDirs", searchable_dirs)?;
                    }

                    return Ok(obj);
                }
                Err(e) => {
                    last_error = Some(e);
                }
            }
        }
        let obj = Object::new(ctx)?;
        let errno = last_error.map_or(-1, |e| e.raw_os_error().unwrap_or(-1));
        obj.set("errno", errno)?;
        Ok(obj)
    }

    #[allow(clippy::needless_pass_by_value)]
    fn realpath(ctx: Ctx, path: String) -> QJSResult<QJSString> {
        let str = QJSString::from_str(ctx, &std::fs::canonicalize(&path)?.to_string_lossy())?;
        Ok(str)
    }

    pub fn execute_native_runtime(
        grammar_path: &Path,
        parser_directories: &[PathBuf],
    ) -> AnyResult<String> {
        let runtime = Runtime::new()?;
        let context = QJSContext::full(&runtime)?;

        let cwd = std::env::current_dir()?;

        let parser_directory_paths = parser_directories
            .iter()
            .filter_map(|p| pathdiff::diff_paths(p, &cwd).map(|p| p.to_string_lossy().to_string()))
            .chain(std::iter::once(String::new()))
            .collect::<Vec<_>>();

        let resolver = FileResolver::default()
            .with_path("./")
            .with_paths(&parser_directory_paths);
        let loader = ScriptLoader::default();

        runtime.set_loader(resolver, loader);

        let relative_path_to_cwd = pathdiff::diff_paths(grammar_path, &cwd)
            .map(|p| p.to_string_lossy().to_string())
            .with_context(|| {
                format!(
                    "Failed to get relative path of {} to cwd",
                    grammar_path.display()
                )
            })?;

        env::set_var("TREE_SITTER_GRAMMAR_PATH", &relative_path_to_cwd);

        context.with(|ctx| -> Result<String, anyhow::Error> {
            let wrap_err = |e| {
                if matches!(e, Error::Exception) {
                    pretty_print_js_error(ctx.catch())
                } else {
                    e.into()
                }
            };

            let globals = ctx.globals();
            globals.set("native", true).map_err(wrap_err)?;
            globals
                .set("__ts_grammar_path", relative_path_to_cwd)
                .map_err(wrap_err)?;
            globals
                .set(
                    "__print",
                    Function::new(ctx.clone(), print)?.with_name("__print")?,
                )
                .map_err(wrap_err)?;
            globals
                .set(
                    "__warn",
                    Function::new(ctx.clone(), warn)?.with_name("__warn")?,
                )
                .map_err(wrap_err)?;
            globals
                .set(
                    "__error",
                    Function::new(ctx.clone(), error)?.with_name("__error")?,
                )
                .map_err(wrap_err)?;

            let std = Object::new(ctx.clone()).map_err(wrap_err)?;
            std.set(
                "loadFile",
                Function::new(ctx.clone(), |path: String| {
                    let path = Path::new(&path);
                    std::fs::read_to_string(path)
                })?,
            )
            .map_err(wrap_err)?;
            globals.set("std", std).map_err(wrap_err)?;

            let process = Object::new(ctx.clone()).map_err(wrap_err)?;
            let env = Object::new(ctx.clone()).map_err(wrap_err)?;
            for (k, v) in std::env::vars() {
                env.set(k, v).map_err(wrap_err)?;
            }
            process.set("env", env).map_err(wrap_err)?;
            globals.set("process", process).map_err(wrap_err)?;

            let searchable_dirs = Array::new(ctx.clone()).map_err(wrap_err)?;
            for (i, dir) in parser_directory_paths.iter().enumerate() {
                searchable_dirs.set(i, dir).map_err(wrap_err)?;
            }
            globals
                .set("_searchableDirs", searchable_dirs)
                .map_err(wrap_err)?;

            globals
                .set("_statPath", Function::new(ctx.clone(), stat_path)?)
                .map_err(wrap_err)?;
            globals
                .set("_realpath", Function::new(ctx.clone(), realpath)?)
                .map_err(wrap_err)?;

            let module = Object::new(ctx.clone()).map_err(wrap_err)?;
            module
                .set("exports", Object::new(ctx.clone()).map_err(wrap_err)?)
                .map_err(wrap_err)?;
            globals.set("module", module).map_err(wrap_err)?;

            Module::evaluate(ctx.clone(), "stdlib", STDLIB)
                .map_err(wrap_err)
                .with_context(|| "Failed to load stdlib.js")?;

            let promise = Module::evaluate(ctx.clone(), "dsl", super::DSL)
                .map_err(wrap_err)
                .with_context(|| "Failed to evaluate DSL")?;
            promise.finish::<()>().map_err(wrap_err)?;

            let grammar_json = ctx
                .eval::<QJSString, _>("globalThis.output")
                .map(|x| x.to_string())
                .map_err(wrap_err)?
                .map_err(wrap_err)?;

            Ok(serde_json::to_string_pretty(
                &serde_json::from_str::<serde_json::Value>(&grammar_json)
                    .with_context(|| "Failed to parse grammar JSON")?,
            )
            .with_context(|| "Failed to serialize grammar JSON")?
                + "\n")
        })
    }
}

pub fn write_file(path: &Path, body: impl AsRef<[u8]>) -> Result<()> {
    fs::write(path, body)
        .with_context(|| format!("Failed to write {:?}", path.file_name().unwrap()))
}
