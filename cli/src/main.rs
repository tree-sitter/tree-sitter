use std::{
    collections::HashSet,
    env, fs,
    path::{Path, PathBuf},
};

use anstyle::{AnsiColor, Color, Style};
use anyhow::{anyhow, Context, Result};
use clap::{crate_authors, Args, Command, FromArgMatches as _, Subcommand, ValueEnum};
use clap_complete::{generate, Shell};
use dialoguer::{theme::ColorfulTheme, Confirm, FuzzySelect, Input};
use glob::glob;
use heck::ToUpperCamelCase;
use regex::Regex;
use semver::Version as SemverVersion;
use serde_json::json;
use tree_sitter::{ffi, Parser, Point};
use tree_sitter_cli::{
    fuzz::{
        fuzz_language_corpus, FuzzOptions, EDIT_COUNT, ITERATION_COUNT, LOG_ENABLED,
        LOG_GRAPH_ENABLED, START_SEED,
    }, highlight, init::{generate_grammar_files, get_root_path, migrate_package_json, JsonConfigOpts}, logger, parse::{self, ParseFileOptions, ParseOutput, ParseTheme}, playground, query, tags, test::{self, TestOptions}, test_result::{TestResult, HighlightTestResult}, test_highlight, test_tags, util, version, wasm
};
use tree_sitter_config::Config;
use tree_sitter_highlight::Highlighter;
use tree_sitter_loader::{self as loader, TreeSitterJSON};
use tree_sitter_tags::TagsContext;
use url::Url;

const BUILD_VERSION: &str = env!("CARGO_PKG_VERSION");
const BUILD_SHA: Option<&'static str> = option_env!("BUILD_SHA");
const DEFAULT_GENERATE_ABI_VERSION: usize = 15;

#[derive(Subcommand)]
#[command(about="Generates and tests parsers", author=crate_authors!("\n"), styles=get_styles())]
enum Commands {
    InitConfig(InitConfig),
    Init(Init),
    Generate(Generate),
    Build(Build),
    Parse(Parse),
    Test(Test),
    Version(Version),
    Fuzz(Fuzz),
    Query(Query),
    Highlight(Highlight),
    Tags(Tags),
    Playground(Playground),
    DumpLanguages(DumpLanguages),
    Complete(Complete),
}

#[derive(Args)]
#[command(about = "Generate a default config file")]
struct InitConfig;

#[derive(Args)]
#[command(about = "Initialize a grammar repository", alias = "i")]
struct Init {
    #[arg(long, short, help = "Update outdated files")]
    pub update: bool,
}

#[derive(Args)]
#[command(about = "Generate a parser", alias = "gen", alias = "g")]
struct Generate {
    #[arg(index = 1, help = "The path to the grammar file")]
    pub grammar_path: Option<String>,
    #[arg(long, short, help = "Show debug log during generation")]
    pub log: bool,
    #[arg(long, help = "Deprecated (no-op)")]
    pub no_bindings: bool,
    #[arg(
        long = "abi",
        value_name = "VERSION",
        help = format!(concat!(
                    "Select the language ABI version to generate (default {}).\n",
                    "Use --abi=latest to generate the newest supported version ({}).",
                    ),
                DEFAULT_GENERATE_ABI_VERSION,
                tree_sitter::LANGUAGE_VERSION,
                )
    )]
    pub abi_version: Option<String>,
    #[arg(
        long,
        short = 'b',
        help = "Compile all defined languages in the current dir"
    )]
    pub build: bool,
    #[arg(long, short = '0', help = "Compile a parser in debug mode")]
    pub debug_build: bool,
    #[arg(
        long,
        value_name = "PATH",
        help = "The path to the directory containing the parser library"
    )]
    pub libdir: Option<String>,
    #[arg(
        long,
        short,
        value_name = "DIRECTORY",
        help = "The path to output the generated source files"
    )]
    pub output: Option<String>,
    #[arg(
        long,
        help = "Produce a report of the states for the given rule, use `-` to report every rule"
    )]
    pub report_states_for_rule: Option<String>,

    #[arg(
        long,
        value_name = "EXECUTABLE",
        env = "TREE_SITTER_JS_RUNTIME",
        default_value = "node",
        help = "The name or path of the JavaScript runtime to use for generating parsers"
    )]
    pub js_runtime: Option<String>,
}

#[derive(Args)]
#[command(about = "Compile a parser", alias = "b")]
struct Build {
    #[arg(short, long, help = "Build a WASM module instead of a dynamic library")]
    pub wasm: bool,
    #[arg(
        short,
        long,
        help = "Run emscripten via docker even if it is installed locally (only if building a WASM module with --wasm)"
    )]
    pub docker: bool,
    #[arg(short, long, help = "The path to output the compiled file")]
    pub output: Option<String>,
    #[arg(index = 1, num_args = 1, help = "The path to the grammar directory")]
    pub path: Option<String>,
    #[arg(long, help = "Make the parser reuse the same allocator as the library")]
    pub reuse_allocator: bool,
    #[arg(long, short = '0', help = "Compile a parser in debug mode")]
    pub debug: bool,
}

#[derive(Args)]
#[command(about = "Parse files", alias = "p")]
struct Parse {
    #[arg(
        long = "paths",
        help = "The path to a file with paths to source file(s)"
    )]
    pub paths_file: Option<String>,
    #[arg(num_args=1.., help = "The source file(s) to use")]
    pub paths: Option<Vec<String>>,
    #[arg(
        long,
        help = "Select a language by the scope instead of a file extension"
    )]
    pub scope: Option<String>,
    #[arg(long, short = 'd', help = "Show parsing debug log")]
    pub debug: bool,
    #[arg(long, short = '0', help = "Compile a parser in debug mode")]
    pub debug_build: bool,
    #[arg(
        long,
        short = 'D',
        help = "Produce the log.html file with debug graphs"
    )]
    pub debug_graph: bool,
    #[arg(
        long,
        help = "Compile parsers to wasm instead of native dynamic libraries"
    )]
    pub wasm: bool,
    #[arg(long = "dot", help = "Output the parse data with graphviz dot")]
    pub output_dot: bool,
    #[arg(
        long = "xml",
        short = 'x',
        help = "Output the parse data in XML format"
    )]
    pub output_xml: bool,
    #[arg(
        long = "cst",
        short = 'c',
        help = "Output the parse data in a pretty-printed CST format"
    )]
    pub output_cst: bool,
    #[arg(long, short, help = "Show parsing statistic")]
    pub stat: bool,
    #[arg(long, help = "Interrupt the parsing process by timeout (µs)")]
    pub timeout: Option<u64>,
    #[arg(long, short, help = "Measure execution time")]
    pub time: bool,
    #[arg(long, short, help = "Suppress main output")]
    pub quiet: bool,
    #[arg(
        long,
        num_args = 1..,
        help = "Apply edits in the format: \"row, col delcount insert_text\""
    )]
    pub edits: Option<Vec<String>>,
    #[arg(long, help = "The encoding of the input files")]
    pub encoding: Option<Encoding>,
    #[arg(
        long,
        help = "Open `log.html` in the default browser, if `--debug-graph` is supplied"
    )]
    pub open_log: bool,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
    #[arg(long, short = 'n', help = "Parse the contents of a specific test")]
    #[clap(conflicts_with = "paths", conflicts_with = "paths_file")]
    pub test_number: Option<u32>,
    #[arg(short, long, help = "Force rebuild the parser")]
    pub rebuild: bool,
    #[arg(long, help = "Omit ranges in the output")]
    pub no_ranges: bool,
}

#[derive(ValueEnum, Clone)]
pub enum Encoding {
    Utf8,
    Utf16LE,
    Utf16BE,
}

#[derive(Args)]
#[command(about = "Run a parser's tests", alias = "t")]
struct Test {
    #[arg(
        long,
        short,
        help = "Only run corpus test cases whose name matches the given regex"
    )]
    pub include: Option<Regex>,
    #[arg(
        long,
        short,
        help = "Only run corpus test cases whose name does not match the given regex"
    )]
    pub exclude: Option<Regex>,
    #[arg(
        long,
        short,
        help = "Update all syntax trees in corpus files with current parser output"
    )]
    pub update: bool,
    #[arg(long, short = 'd', help = "Show parsing debug log")]
    pub debug: bool,
    #[arg(long, short = '0', help = "Compile a parser in debug mode")]
    pub debug_build: bool,
    #[arg(
        long,
        short = 'D',
        help = "Produce the log.html file with debug graphs"
    )]
    pub debug_graph: bool,
    #[arg(
        long,
        help = "Compile parsers to wasm instead of native dynamic libraries"
    )]
    pub wasm: bool,
    #[arg(
        long,
        help = "Open `log.html` in the default browser, if `--debug-graph` is supplied"
    )]
    pub open_log: bool,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
    #[arg(long, help = "Force showing fields in test diffs")]
    pub show_fields: bool,
    #[arg(short, long, help = "Force rebuild the parser")]
    pub rebuild: bool,
    #[arg(long, help = "Show only the pass-fail overview tree")]
    pub overview_only: bool,
    #[arg(
        long,
        help = "Generate a JSON report of the test results. Use `:stdout:` as the filename to print to screen.")]
    pub report: Option<String>,
    #[arg(long, help = "Open the JSON report in the default browser. Only works if JSON reporting is enabled and an actual filename is provided.")]
    pub open_report: bool,
}

#[derive(Args)]
#[command(alias = "publish")]
/// Increment the version of a grammar
struct Version {
    #[arg(num_args = 1)]
    /// The version to bump to
    pub version: SemverVersion,
}

#[derive(Args)]
#[command(about = "Fuzz a parser", alias = "f")]
struct Fuzz {
    #[arg(long, short, help = "List of test names to skip")]
    pub skip: Option<Vec<String>>,
    #[arg(long, help = "Subdirectory to the language")]
    pub subdir: Option<String>,
    #[arg(long, help = "Maximum number of edits to perform per fuzz test")]
    pub edits: Option<usize>,
    #[arg(long, help = "Number of fuzzing iterations to run per test")]
    pub iterations: Option<usize>,
    #[arg(
        long,
        short,
        help = "Only fuzz corpus test cases whose name matches the given regex"
    )]
    pub include: Option<Regex>,
    #[arg(
        long,
        short,
        help = "Only fuzz corpus test cases whose name does not match the given regex"
    )]
    pub exclude: Option<Regex>,
    #[arg(long, help = "Enable logging of graphs and input")]
    pub log_graphs: bool,
    #[arg(long, short, help = "Enable parser logging")]
    pub log: bool,
    #[arg(short, long, help = "Force rebuild the parser")]
    pub rebuild: bool,
}

#[derive(Args)]
#[command(about = "Search files using a syntax tree query", alias = "q")]
struct Query {
    #[arg(help = "Path to a file with queries", index = 1, required = true)]
    query_path: String,
    #[arg(long, short, help = "Measure execution time")]
    pub time: bool,
    #[arg(long, short, help = "Suppress main output")]
    pub quiet: bool,
    #[arg(
        long = "paths",
        help = "The path to a file with paths to source file(s)"
    )]
    pub paths_file: Option<String>,
    #[arg(index = 2, num_args=1.., help = "The source file(s) to use")]
    pub paths: Option<Vec<String>>,
    #[arg(
        long,
        help = "The range of byte offsets in which the query will be executed"
    )]
    pub byte_range: Option<String>,
    #[arg(long, help = "The range of rows in which the query will be executed")]
    pub row_range: Option<String>,
    #[arg(
        long,
        help = "Select a language by the scope instead of a file extension"
    )]
    pub scope: Option<String>,
    #[arg(long, short, help = "Order by captures instead of matches")]
    pub captures: bool,
    #[arg(long, help = "Whether to run query tests or not")]
    pub test: bool,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
}

#[derive(Args)]
#[command(about = "Highlight a file", alias = "hi")]
struct Highlight {
    #[arg(long, short = 'H', help = "Generate highlighting as an HTML document")]
    pub html: bool,
    #[arg(
        long,
        help = "Check that highlighting captures conform strictly to standards"
    )]
    pub check: bool,
    #[arg(long, help = "The path to a file with captures")]
    pub captures_path: Option<String>,
    #[arg(long, num_args = 1.., help = "The paths to files with queries")]
    pub query_paths: Option<Vec<String>>,
    #[arg(
        long,
        help = "Select a language by the scope instead of a file extension"
    )]
    pub scope: Option<String>,
    #[arg(long, short, help = "Measure execution time")]
    pub time: bool,
    #[arg(long, short, help = "Suppress main output")]
    pub quiet: bool,
    #[arg(
        long = "paths",
        help = "The path to a file with paths to source file(s)"
    )]
    pub paths_file: Option<String>,
    #[arg(num_args = 1.., help = "The source file(s) to use")]
    pub paths: Option<Vec<String>>,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
}

#[derive(Args)]
#[command(about = "Generate a list of tags")]
struct Tags {
    #[arg(
        long,
        help = "Select a language by the scope instead of a file extension"
    )]
    pub scope: Option<String>,
    #[arg(long, short, help = "Measure execution time")]
    pub time: bool,
    #[arg(long, short, help = "Suppress main output")]
    pub quiet: bool,
    #[arg(
        long = "paths",
        help = "The path to a file with paths to source file(s)"
    )]
    pub paths_file: Option<String>,
    #[arg(num_args = 1.., help = "The source file(s) to use")]
    pub paths: Option<Vec<String>>,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
}

#[derive(Args)]
#[command(
    about = "Start local playground for a parser in the browser",
    alias = "play",
    alias = "pg",
    alias = "web-ui"
)]
struct Playground {
    #[arg(long, short, help = "Don't open in default browser")]
    pub quiet: bool,
    #[arg(
        long,
        help = "Path to the directory containing the grammar and wasm files"
    )]
    pub grammar_path: Option<String>,
}

#[derive(Args)]
#[command(about = "Print info about all known language parsers", alias = "langs")]
struct DumpLanguages {
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
}

#[derive(Args)]
#[command(about = "Generate shell completions", alias = "comp")]
struct Complete {
    #[arg(
        long,
        short,
        value_enum,
        help = "The shell to generate completions for"
    )]
    pub shell: Shell,
}

impl InitConfig {
    fn run() -> Result<()> {
        if let Ok(Some(config_path)) = Config::find_config_file() {
            return Err(anyhow!(
                "Remove your existing config file first: {}",
                config_path.to_string_lossy()
            ));
        }
        let mut config = Config::initial()?;
        config.add(tree_sitter_loader::Config::initial())?;
        config.add(tree_sitter_cli::highlight::ThemeConfig::default())?;
        config.save()?;
        println!(
            "Saved initial configuration to {}",
            config.location.display()
        );
        Ok(())
    }
}

impl Init {
    fn run(self, current_dir: &Path, migrated: bool) -> Result<()> {
        let configure_json = !current_dir.join("tree-sitter.json").exists()
            && (!current_dir.join("package.json").exists() || !migrated);

        let (language_name, json_config_opts) = if configure_json {
            let mut opts = JsonConfigOpts::default();

            let name = || {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("Parser name")
                    .validate_with(|input: &String| {
                        if input.chars().all(|c| c.is_ascii_lowercase() || c.is_ascii_digit() || c == '_') {
                            Ok(())
                        } else {
                            Err("The name must be lowercase and contain only letters, digits, and underscores")
                        }
                    })
                    .interact_text()
            };

            let camelcase_name = |name: &str| {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("CamelCase name")
                    .default(name.to_upper_camel_case())
                    .validate_with(|input: &String| {
                        if input
                            .chars()
                            .all(|c| c.is_ascii_alphabetic() || c.is_ascii_digit() || c == '_')
                        {
                            Ok(())
                        } else {
                            Err("The name must contain only letters, digits, and underscores")
                        }
                    })
                    .interact_text()
            };

            let description = |name: &str| {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("Description")
                    .default(format!(
                        "{} grammar for tree-sitter",
                        name.to_upper_camel_case()
                    ))
                    .show_default(false)
                    .allow_empty(true)
                    .interact_text()
            };

            let repository = |name: &str| {
                Input::<Url>::with_theme(&ColorfulTheme::default())
                    .with_prompt("Repository URL")
                    .allow_empty(true)
                    .default(
                        Url::parse(&format!(
                            "https://github.com/tree-sitter/tree-sitter-{name}"
                        ))
                        .expect("Failed to parse default repository URL"),
                    )
                    .show_default(false)
                    .interact_text()
            };

            let scope = |name: &str| {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("TextMate scope")
                    .default(format!("source.{name}"))
                    .validate_with(|input: &String| {
                        if input.starts_with("source.") || input.starts_with("text.") {
                            Ok(())
                        } else {
                            Err("The scope must start with 'source.' or 'text.'")
                        }
                    })
                    .interact_text()
            };

            let file_types = |name: &str| {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("File types (space-separated)")
                    .default(format!(".{name}"))
                    .interact_text()
                    .map(|ft| {
                        let mut set = HashSet::new();
                        for ext in ft.split(' ') {
                            let ext = ext.trim();
                            if !ext.is_empty() {
                                set.insert(ext.to_string());
                            }
                        }
                        set.into_iter().collect::<Vec<_>>()
                    })
            };

            let initial_version = || {
                Input::<SemverVersion>::with_theme(&ColorfulTheme::default())
                    .with_prompt("Version")
                    .default(SemverVersion::new(0, 1, 0))
                    .interact_text()
            };

            let license = || {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("License")
                    .default("MIT".to_string())
                    .allow_empty(true)
                    .interact()
            };

            let author = || {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("Author name")
                    .interact_text()
            };

            let email = || {
                Input::with_theme(&ColorfulTheme::default())
                    .with_prompt("Author email")
                    .validate_with({
                        move |input: &String| -> Result<(), &str> {
                            if (input.contains('@') && input.contains('.'))
                                || input.trim().is_empty()
                            {
                                Ok(())
                            } else {
                                Err("This is not a valid email address")
                            }
                        }
                    })
                    .allow_empty(true)
                    .interact_text()
                    .map(|e| (!e.trim().is_empty()).then_some(e))
            };

            let url = || {
                Input::<String>::with_theme(&ColorfulTheme::default())
                    .with_prompt("Author URL")
                    .allow_empty(true)
                    .validate_with(|input: &String| -> Result<(), &str> {
                        if input.trim().is_empty() || Url::parse(input).is_ok() {
                            Ok(())
                        } else {
                            Err("This is not a valid URL")
                        }
                    })
                    .interact_text()
                    .map(|e| (!e.trim().is_empty()).then(|| Url::parse(&e).unwrap()))
            };

            let choices = [
                "name",
                "camelcase",
                "description",
                "repository",
                "scope",
                "file_types",
                "version",
                "license",
                "author",
                "email",
                "url",
                "exit",
            ];

            macro_rules! set_choice {
                ($choice:expr) => {
                    match $choice {
                        "name" => opts.name = name()?,
                        "camelcase" => opts.camelcase = camelcase_name(&opts.name)?,
                        "description" => opts.description = description(&opts.name)?,
                        "repository" => opts.repository = Some(repository(&opts.name)?),
                        "scope" => opts.scope = scope(&opts.name)?,
                        "file_types" => opts.file_types = file_types(&opts.name)?,
                        "version" => opts.version = initial_version()?,
                        "license" => opts.license = license()?,
                        "author" => opts.author = author()?,
                        "email" => opts.email = email()?,
                        "url" => opts.url = url()?,
                        "exit" => break,
                        _ => unreachable!(),
                    }
                };
            }

            // Initial configuration
            for choice in choices.iter().take(choices.len() - 1) {
                set_choice!(*choice);
            }

            // Loop for editing the configuration
            loop {
                println!(
                    "Your current configuration:\n{}",
                    serde_json::to_string_pretty(&opts)?
                );

                if Confirm::with_theme(&ColorfulTheme::default())
                    .with_prompt("Does the config above look correct?")
                    .interact()?
                {
                    break;
                }

                let idx = FuzzySelect::with_theme(&ColorfulTheme::default())
                    .with_prompt("Which field would you like to change?")
                    .items(&choices)
                    .interact()?;

                set_choice!(choices[idx]);
            }

            (opts.name.clone(), Some(opts))
        } else {
            let mut json = serde_json::from_str::<TreeSitterJSON>(
                &fs::read_to_string(current_dir.join("tree-sitter.json"))
                    .with_context(|| "Failed to read tree-sitter.json")?,
            )?;
            (json.grammars.swap_remove(0).name, None)
        };

        generate_grammar_files(
            current_dir,
            &language_name,
            self.update,
            json_config_opts.as_ref(),
        )?;

        Ok(())
    }
}

impl Generate {
    fn run(self, mut loader: loader::Loader, current_dir: &Path) -> Result<()> {
        if self.no_bindings {
            eprint!("The --no-bindings flag is no longer used and will be removed in v0.25.0");
        }
        if self.log {
            logger::init();
        }
        let abi_version =
            self.abi_version
                .as_ref()
                .map_or(DEFAULT_GENERATE_ABI_VERSION, |version| {
                    if version == "latest" {
                        tree_sitter::LANGUAGE_VERSION
                    } else {
                        version.parse().expect("invalid abi version flag")
                    }
                });
        tree_sitter_generate::generate_parser_in_directory(
            current_dir,
            self.output.as_deref(),
            self.grammar_path.as_deref(),
            abi_version,
            self.report_states_for_rule.as_deref(),
            self.js_runtime.as_deref(),
        )?;
        if self.build {
            if let Some(path) = self.libdir {
                loader = loader::Loader::with_parser_lib_path(PathBuf::from(path));
            }
            loader.debug_build(self.debug_build);
            loader.languages_at_path(current_dir)?;
        }
        Ok(())
    }
}

impl Build {
    fn run(self, mut loader: loader::Loader, current_dir: &Path) -> Result<()> {
        let grammar_path = current_dir.join(self.path.as_deref().unwrap_or_default());

        if self.wasm {
            let output_path = self.output.map(|path| current_dir.join(path));
            let root_path = get_root_path(&grammar_path.join("tree-sitter.json"))?;
            wasm::compile_language_to_wasm(
                &loader,
                Some(&root_path),
                &grammar_path,
                current_dir,
                output_path,
                self.docker,
            )?;
        } else {
            let output_path = if let Some(ref path) = self.output {
                let path = Path::new(path);
                if path.is_absolute() {
                    path.to_path_buf()
                } else {
                    current_dir.join(path)
                }
            } else {
                let file_name = grammar_path
                    .file_stem()
                    .unwrap()
                    .to_str()
                    .unwrap()
                    .strip_prefix("tree-sitter-")
                    .unwrap_or("parser");
                current_dir
                    .join(file_name)
                    .with_extension(env::consts::DLL_EXTENSION)
            };

            let flags: &[&str] = match (self.reuse_allocator, self.debug) {
                (true, true) => &["TREE_SITTER_REUSE_ALLOCATOR", "TREE_SITTER_DEBUG"],
                (true, false) => &["TREE_SITTER_REUSE_ALLOCATOR"],
                (false, true) => &["TREE_SITTER_DEBUG"],
                (false, false) => &[],
            };

            loader.debug_build(self.debug);
            loader.force_rebuild(true);

            let config = Config::load(None)?;
            let loader_config = config.get()?;
            loader.find_all_languages(&loader_config).unwrap();
            loader
                .compile_parser_at_path(&grammar_path, output_path, flags)
                .unwrap();
        }
        Ok(())
    }
}

impl Parse {
    fn run(self, mut loader: loader::Loader, current_dir: &Path) -> Result<()> {
        let config = Config::load(self.config_path)?;
        let color = env::var("NO_COLOR").map_or(true, |v| v != "1");
        let output = if self.output_dot {
            ParseOutput::Dot
        } else if self.output_xml {
            ParseOutput::Xml
        } else if self.output_cst {
            ParseOutput::Cst
        } else if self.quiet {
            ParseOutput::Quiet
        } else {
            ParseOutput::Normal
        };

        let parse_theme = if color {
            config
                .get::<parse::Config>()
                .with_context(|| "Failed to parse CST theme")?
                .parse_theme
                .unwrap_or_default()
                .into()
        } else {
            ParseTheme::empty()
        };

        let encoding = self.encoding.map(|e| match e {
            Encoding::Utf8 => ffi::TSInputEncodingUTF8,
            Encoding::Utf16LE => ffi::TSInputEncodingUTF16LE,
            Encoding::Utf16BE => ffi::TSInputEncodingUTF16BE,
        });

        let time = self.time;
        let edits = self.edits.unwrap_or_default();
        let cancellation_flag = util::cancel_on_signal();
        let mut parser = Parser::new();

        loader.debug_build(self.debug_build);
        loader.force_rebuild(self.rebuild);

        #[cfg(feature = "wasm")]
        if self.wasm {
            let engine = tree_sitter::wasmtime::Engine::default();
            parser
                .set_wasm_store(tree_sitter::WasmStore::new(&engine).unwrap())
                .unwrap();
            loader.use_wasm(&engine);
        }

        let timeout = self.timeout.unwrap_or_default();

        let (paths, language) = if let Some(target_test) = self.test_number {
            let (test_path, language_names) = test::get_tmp_test_file(target_test, color)?;
            let languages = loader.languages_at_path(current_dir)?;
            let language = languages
                .iter()
                .find(|(_, n)| language_names.contains(&Box::from(n.as_str())))
                .map(|(l, _)| l.clone());
            let paths = collect_paths(None, Some(vec![test_path.to_str().unwrap().to_owned()]))?;
            (paths, language)
        } else {
            (collect_paths(self.paths_file.as_deref(), self.paths)?, None)
        };

        let max_path_length = paths.iter().map(|p| p.chars().count()).max().unwrap_or(0);
        let mut has_error = false;
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;

        let should_track_stats = self.stat;
        let mut stats = parse::Stats::default();

        for path in &paths {
            let path = Path::new(&path);

            let language = if let Some(ref language) = language {
                language.clone()
            } else {
                loader.select_language(path, current_dir, self.scope.as_deref())?
            };
            parser
                .set_language(&language)
                .context("incompatible language")?;

            let opts = ParseFileOptions {
                language: language.clone(),
                path,
                edits: &edits
                    .iter()
                    .map(std::string::String::as_str)
                    .collect::<Vec<&str>>(),
                max_path_length,
                output,
                print_time: time,
                timeout,
                debug: self.debug,
                debug_graph: self.debug_graph,
                cancellation_flag: Some(&cancellation_flag),
                encoding,
                open_log: self.open_log,
                no_ranges: self.no_ranges,
                parse_theme: &parse_theme,
            };

            let parse_result = parse::parse_file_at_path(&mut parser, &opts)?;

            if should_track_stats {
                stats.total_parses += 1;
                if parse_result.successful {
                    stats.successful_parses += 1;
                }
                if let Some(duration) = parse_result.duration {
                    stats.total_bytes += parse_result.bytes;
                    stats.total_duration += duration;
                }
            }

            has_error |= !parse_result.successful;
        }

        if should_track_stats {
            println!("\n{stats}");
        }

        if has_error {
            return Err(anyhow!(""));
        }

        Ok(())
    }
}

impl Test {
    fn run(self, mut loader: loader::Loader, current_dir: &Path) -> Result<()> {
        let config = Config::load(self.config_path)?;
        let color = env::var("NO_COLOR").map_or(true, |v| v != "1");

        loader.debug_build(self.debug_build);
        loader.force_rebuild(self.rebuild);

        let mut parser = Parser::new();

        #[cfg(feature = "wasm")]
        if self.wasm {
            let engine = tree_sitter::wasmtime::Engine::default();
            parser
                .set_wasm_store(tree_sitter::WasmStore::new(&engine).unwrap())
                .unwrap();
            loader.use_wasm(&engine);
        }

        let languages = loader.languages_at_path(current_dir)?;
        let language = &languages
            .first()
            .ok_or_else(|| anyhow!("No language found"))?
            .0;
        parser.set_language(language)?;

        let test_dir = current_dir.join("test");

        // Run the corpus tests. Look for them in `test/corpus`.
        let test_corpus_dir = test_dir.join("corpus");
        let corpus_results = if test_corpus_dir.is_dir() {
            let mut opts = TestOptions {
                path: test_corpus_dir,
                debug: self.debug,
                debug_graph: self.debug_graph,
                include: self.include,
                exclude: self.exclude,
                update: self.update,
                open_log: self.open_log,
                languages: languages.iter().map(|(l, n)| (n.as_str(), l)).collect(),
                color,
                test_num: 1,
                show_fields: self.show_fields,
                overview_only: self.overview_only,
                generate_report: self.report.clone(),
            };

            let results = test::run_tests_at_path(&mut parser, &mut opts)?;
            if let TestResult::Group { name, children, .. } = results {
                if name == String::from("corpus") {
                    Some(children)
                } else {
                    panic!("This should not happen. Top level should be entire corpus test group.")
                }
            } else {
                panic!("This should not happen. Top level should be a group.")
            }
        } else {
            None
        };

        // Check that all of the queries are valid.
        test::check_queries_at_path(language, &current_dir.join("queries"))?;

        // Run the syntax highlighting tests.
        let test_highlight_dir = test_dir.join("highlight");
        let highlight_results = if test_highlight_dir.is_dir() {
            let mut highlighter = Highlighter::new();
            highlighter.parser = parser;
            let highlight_results = test_highlight::test_highlights(
                &loader,
                &config.get()?,
                &mut highlighter,
                &test_highlight_dir,
            )?;
            parser = highlighter.parser;
            if self.report.is_none() {
                println!("syntax highlighting:");
                print!("{}", highlight_results.to_string(color, 0));
            }
            if let HighlightTestResult::Suite { children, name, .. } = highlight_results {
                if name == String::from("highlight") {
                    Some(children)
                } else {
                    panic!("This should not happen. Top level should be entire highlight test group.")
                }
            } else {
                panic!("This should not happen. Top level should be a group.")
            }
            // Some(highlight_results)
        } else {
            None
        };

        let test_tag_dir = test_dir.join("tags");
        let tag_results = if test_tag_dir.is_dir() {
            let mut tags_context = TagsContext::new();
            tags_context.parser = parser;
            let tag_results = test_tags::test_tags(
                &loader,
                &config.get()?,
                &mut tags_context,
                &test_tag_dir,
            )?;
            if self.report.is_none() {
                println!("tags:");
                for child in &tag_results {
                    println!("{}", child.to_string(color));
                }
            }
            tag_results
        } else {
            vec![]
        };

        if self.report.is_some() {
            let output = format!("{}", json!({
                "corpus": corpus_results.unwrap_or_default(),
                "highlight": highlight_results.unwrap_or_default(),
                "tags": tag_results,
            }));
            let target = self.report.unwrap();
            if target == ":stdout:" {
                print!("{output}");
            } else {
                // let output_dir = current_dir;
                let ofilename = current_dir.join("report.json");
                std::fs::write(&ofilename, output)?;
                if self.open_report {
                    let fname = ofilename.to_string_lossy();
                    webbrowser::open(&fname)?;
                }
            }
            return Ok(());
        }

        
        // if self.report.is_some() {
        //     print!("{}", json!({
        //         "corpus": corpus_results.unwrap_or_default(),
        //         "highlight": highlight_results.unwrap_or_default(),
        //         "tags": tag_results,
        //     }));
        //     return Ok(());
        // }

        // For the rest of the queries, find their tests and run them
        for entry in walkdir::WalkDir::new(current_dir.join("queries"))
            .into_iter()
            .filter_map(|e| e.ok())
            .filter(|e| e.file_type().is_file())
        {
            let stem = entry
                .path()
                .file_stem()
                .map(|s| s.to_str().unwrap_or_default())
                .unwrap_or_default();
            if stem != "highlights" && stem != "tags" {
                let paths = walkdir::WalkDir::new(test_dir.join(stem))
                    .into_iter()
                    .filter_map(|e| {
                        let entry = e.ok()?;
                        if entry.file_type().is_file() {
                            Some(String::from(entry.path().to_string_lossy()))
                        } else {
                            None
                        }
                    })
                    .collect::<Vec<String>>();
                if !paths.is_empty() {
                    println!("{stem}:");
                }
                query::query_files_at_paths(
                    language,
                    paths,
                    entry.path(),
                    false,
                    None,
                    None,
                    true,
                    false,
                    false,
                )?;
            }
        }
        Ok(())
    }
}

impl Version {
    fn run(self, current_dir: PathBuf) -> Result<()> {
        version::Version::new(self.version.to_string(), current_dir).run()
    }
}

impl Fuzz {
    fn run(self, mut loader: loader::Loader, current_dir: &Path) -> Result<()> {
        loader.sanitize_build(true);
        loader.force_rebuild(self.rebuild);

        let languages = loader.languages_at_path(current_dir)?;
        let (language, language_name) = &languages
            .first()
            .ok_or_else(|| anyhow!("No language found"))?;

        let mut fuzz_options = FuzzOptions {
            skipped: self.skip,
            subdir: self.subdir,
            edits: self.edits.unwrap_or(*EDIT_COUNT),
            iterations: self.iterations.unwrap_or(*ITERATION_COUNT),
            include: self.include,
            exclude: self.exclude,
            log_graphs: self.log_graphs || *LOG_GRAPH_ENABLED,
            log: self.log || *LOG_ENABLED,
        };

        fuzz_language_corpus(
            language,
            language_name,
            *START_SEED,
            current_dir,
            &mut fuzz_options,
        );
        Ok(())
    }
}

impl Query {
    fn run(self, mut loader: loader::Loader, current_dir: &Path) -> Result<()> {
        let config = Config::load(self.config_path)?;
        let paths = collect_paths(self.paths_file.as_deref(), self.paths)?;
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;
        let language =
            loader.select_language(Path::new(&paths[0]), current_dir, self.scope.as_deref())?;
        let query_path = Path::new(&self.query_path);

        let byte_range = self.byte_range.as_ref().and_then(|range| {
            let mut parts = range.split(':');
            let start = parts.next()?.parse().ok()?;
            let end = parts.next().unwrap().parse().ok()?;
            Some(start..end)
        });
        let point_range = self.row_range.as_ref().and_then(|range| {
            let mut parts = range.split(':');
            let start = parts.next()?.parse().ok()?;
            let end = parts.next().unwrap().parse().ok()?;
            Some(Point::new(start, 0)..Point::new(end, 0))
        });

        query::query_files_at_paths(
            &language,
            paths,
            query_path,
            self.captures,
            byte_range,
            point_range,
            self.test,
            self.quiet,
            self.time,
        )?;
        Ok(())
    }
}

impl Highlight {
    fn run(self, mut loader: loader::Loader) -> Result<()> {
        let config = Config::load(self.config_path)?;
        let theme_config: tree_sitter_cli::highlight::ThemeConfig = config.get()?;
        loader.configure_highlights(&theme_config.theme.highlight_names);
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;

        let quiet = self.quiet;
        let html_mode = quiet || self.html;
        let paths = collect_paths(self.paths_file.as_deref(), self.paths)?;

        if html_mode && !quiet {
            println!("{}", highlight::HTML_HEADER);
        }

        let cancellation_flag = util::cancel_on_signal();

        let mut language = None;
        if let Some(scope) = self.scope.as_deref() {
            language = loader.language_configuration_for_scope(scope)?;
            if language.is_none() {
                return Err(anyhow!("Unknown scope '{scope}'"));
            }
        }

        for path in paths {
            let path = Path::new(&path);
            let (language, language_config) = match language.clone() {
                Some(v) => v,
                None => {
                    if let Some(v) = loader.language_configuration_for_file_name(path)? {
                        v
                    } else {
                        eprintln!("{}", util::lang_not_found_for_path(path, &loader_config));
                        continue;
                    }
                }
            };

            if let Some(highlight_config) =
                language_config.highlight_config(language, self.query_paths.as_deref())?
            {
                if self.check {
                    let names = if let Some(path) = self.captures_path.as_deref() {
                        let path = Path::new(path);
                        let file = fs::read_to_string(path)?;
                        let capture_names = file
                            .lines()
                            .filter_map(|line| {
                                if line.trim().is_empty() || line.trim().starts_with(';') {
                                    return None;
                                }
                                line.split(';').next().map(|s| s.trim().trim_matches('"'))
                            })
                            .collect::<HashSet<_>>();
                        highlight_config.nonconformant_capture_names(&capture_names)
                    } else {
                        highlight_config.nonconformant_capture_names(&HashSet::new())
                    };
                    if names.is_empty() {
                        eprintln!("All highlight captures conform to standards.");
                    } else {
                        eprintln!(
                            "Non-standard highlight {} detected:",
                            if names.len() > 1 {
                                "captures"
                            } else {
                                "capture"
                            }
                        );
                        for name in names {
                            eprintln!("* {name}");
                        }
                    }
                }

                let source = fs::read(path)?;
                if html_mode {
                    highlight::html(
                        &loader,
                        &theme_config.theme,
                        &source,
                        highlight_config,
                        quiet,
                        self.time,
                        Some(&cancellation_flag),
                    )?;
                } else {
                    highlight::ansi(
                        &loader,
                        &theme_config.theme,
                        &source,
                        highlight_config,
                        self.time,
                        Some(&cancellation_flag),
                    )?;
                }
            } else {
                eprintln!("No syntax highlighting config found for path {path:?}");
            }
        }

        if html_mode && !quiet {
            println!("{}", highlight::HTML_FOOTER);
        }
        Ok(())
    }
}

impl Tags {
    fn run(self, mut loader: loader::Loader) -> Result<()> {
        let config = Config::load(self.config_path)?;
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;
        let paths = collect_paths(self.paths_file.as_deref(), self.paths)?;
        tags::generate_tags(
            &loader,
            &config.get()?,
            self.scope.as_deref(),
            &paths,
            self.quiet,
            self.time,
        )?;
        Ok(())
    }
}

impl Playground {
    fn run(self, current_dir: &Path) -> Result<()> {
        let open_in_browser = !self.quiet;
        let grammar_path = self.grammar_path.as_deref().map_or(current_dir, Path::new);
        playground::serve(grammar_path, open_in_browser)?;
        Ok(())
    }
}

impl DumpLanguages {
    fn run(self, mut loader: loader::Loader) -> Result<()> {
        let config = Config::load(self.config_path)?;
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;
        for (configuration, language_path) in loader.get_all_language_configurations() {
            println!(
                concat!(
                    "scope: {}\n",
                    "parser: {:?}\n",
                    "highlights: {:?}\n",
                    "file_types: {:?}\n",
                    "content_regex: {:?}\n",
                    "injection_regex: {:?}\n",
                ),
                configuration.scope.as_ref().unwrap_or(&String::new()),
                language_path,
                configuration.highlights_filenames,
                configuration.file_types,
                configuration.content_regex,
                configuration.injection_regex,
            );
        }
        Ok(())
    }
}

impl Complete {
    fn run(self, cli: &mut Command) {
        generate(
            self.shell,
            cli,
            cli.get_name().to_string(),
            &mut std::io::stdout(),
        );
    }
}

fn main() {
    let result = run();
    if let Err(err) = &result {
        // Ignore BrokenPipe errors
        if let Some(error) = err.downcast_ref::<std::io::Error>() {
            if error.kind() == std::io::ErrorKind::BrokenPipe {
                return;
            }
        }
        if !err.to_string().is_empty() {
            eprintln!("{err:?}");
        }
        std::process::exit(1);
    }
}

fn run() -> Result<()> {
    let version = BUILD_SHA.map_or_else(
        || BUILD_VERSION.to_string(),
        |build_sha| format!("{BUILD_VERSION} ({build_sha})"),
    );
    let version: &'static str = Box::leak(version.into_boxed_str());

    let cli = Command::new("tree-sitter")
        .help_template(
            "\
{before-help}{name} {version}
{author-with-newline}{about-with-newline}
{usage-heading} {usage}

{all-args}{after-help}
",
        )
        .version(version)
        .subcommand_required(true)
        .arg_required_else_help(true)
        .disable_help_subcommand(true)
        .disable_colored_help(false);
    let mut cli = Commands::augment_subcommands(cli);

    let command = Commands::from_arg_matches(&cli.clone().get_matches())?;

    let current_dir = env::current_dir().unwrap();
    let loader = loader::Loader::new()?;

    let migrated = if !current_dir.join("tree-sitter.json").exists()
        && current_dir.join("package.json").exists()
    {
        migrate_package_json(&current_dir).unwrap_or(false)
    } else {
        false
    };

    match command {
        Commands::InitConfig(_) => InitConfig::run()?,
        Commands::Init(init_options) => init_options.run(&current_dir, migrated)?,
        Commands::Generate(generate_options) => generate_options.run(loader, &current_dir)?,
        Commands::Build(build_options) => build_options.run(loader, &current_dir)?,
        Commands::Parse(parse_options) => parse_options.run(loader, &current_dir)?,
        Commands::Test(test_options) => test_options.run(loader, &current_dir)?,
        Commands::Version(version_options) => version_options.run(current_dir)?,
        Commands::Fuzz(fuzz_options) => fuzz_options.run(loader, &current_dir)?,
        Commands::Query(query_options) => query_options.run(loader, &current_dir)?,
        Commands::Highlight(highlight_options) => highlight_options.run(loader)?,
        Commands::Tags(tags_options) => tags_options.run(loader)?,
        Commands::Playground(playground_options) => playground_options.run(&current_dir)?,
        Commands::DumpLanguages(dump_options) => dump_options.run(loader)?,
        Commands::Complete(complete_options) => complete_options.run(&mut cli),
    }

    Ok(())
}

#[must_use]
const fn get_styles() -> clap::builder::Styles {
    clap::builder::Styles::styled()
        .usage(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Yellow))),
        )
        .header(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Yellow))),
        )
        .literal(Style::new().fg_color(Some(Color::Ansi(AnsiColor::Green))))
        .invalid(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Red))),
        )
        .error(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Red))),
        )
        .valid(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Green))),
        )
        .placeholder(Style::new().fg_color(Some(Color::Ansi(AnsiColor::White))))
}

fn collect_paths(paths_file: Option<&str>, paths: Option<Vec<String>>) -> Result<Vec<String>> {
    if let Some(paths_file) = paths_file {
        return Ok(fs::read_to_string(paths_file)
            .with_context(|| format!("Failed to read paths file {paths_file}"))?
            .trim()
            .lines()
            .map(String::from)
            .collect::<Vec<_>>());
    }

    if let Some(paths) = paths {
        let mut result = Vec::new();

        let mut incorporate_path = |path: &str, positive| {
            if positive {
                result.push(path.to_string());
            } else if let Some(index) = result.iter().position(|p| p == path) {
                result.remove(index);
            }
        };

        for mut path in paths {
            let mut positive = true;
            if path.starts_with('!') {
                positive = false;
                path = path.trim_start_matches('!').to_string();
            }

            if Path::new(&path).exists() {
                incorporate_path(&path, positive);
            } else {
                let paths =
                    glob(&path).with_context(|| format!("Invalid glob pattern {path:?}"))?;
                for path in paths {
                    if let Some(path) = path?.to_str() {
                        incorporate_path(path, positive);
                    }
                }
            }
        }

        if result.is_empty() {
            return Err(anyhow!(
                "No files were found at or matched by the provided pathname/glob"
            ));
        }

        return Ok(result);
    }

    Err(anyhow!("Must provide one or more paths"))
}
