use anstyle::{AnsiColor, Color, Style};
use anyhow::{anyhow, Context, Result};
use clap::{crate_authors, Args, Command, FromArgMatches as _, Subcommand};
use glob::glob;
use regex::Regex;
use std::collections::HashSet;
use std::path::{Path, PathBuf};
use std::{env, fs, u64};
use tree_sitter::{ffi, Parser, Point};
use tree_sitter_cli::test::TestOptions;
use tree_sitter_cli::{
    generate, highlight, logger,
    parse::{self, ParseFileOptions, ParseOutput},
    playground, query, tags, test, test_highlight, test_tags, util, wasm,
};
use tree_sitter_config::Config;
use tree_sitter_highlight::Highlighter;
use tree_sitter_loader as loader;
use tree_sitter_tags::TagsContext;

const BUILD_VERSION: &str = env!("CARGO_PKG_VERSION");
const BUILD_SHA: Option<&'static str> = option_env!("BUILD_SHA");
const DEFAULT_GENERATE_ABI_VERSION: usize = 14;

#[derive(Subcommand)]
#[command(about="Generates and tests parsers", author=crate_authors!("\n"), styles=get_styles())]
enum Commands {
    InitConfig(InitConfig),
    Generate(Generate),
    Parse(Parse),
    Test(Test),
    Query(Query),
    Highlight(Highlight),
    Tags(Tags),
    BuildWasm(BuildWasm),
    Playground(Playground),
    DumpLanguages(DumpLanguages),
}

#[derive(Args)]
#[command(about = "Generate a default config file")]
struct InitConfig;

#[derive(Args)]
#[command(about = "Generate a parser", alias = "gen", alias = "g")]
struct Generate {
    #[arg(long, index = 1, help = "The path to the grammar file")]
    pub grammar_path: Option<String>,
    #[arg(long, short, help = "Show debug log during generation")]
    pub log: bool,
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
    #[arg(long, help = "Don't generate language bindings")]
    pub no_bindings: bool,
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
        help = "Produce a report of the states for the given rule, use `-` to report every rule"
    )]
    pub report_states_for_rule: Option<String>,

    #[arg(
        long,
        value_name = "EXECUTABLE",
        env = "TREE_SITTER_JS_RUNTIME",
        help = "The path to the JavaScript runtime to use for generating parsers"
    )]
    pub js_runtime: Option<String>,
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
    pub encoding: Option<String>,
}

impl Parse {
    fn run(self, config: Config, mut loader: loader::Loader, current_dir: PathBuf) -> Result<()> {
        let output = if self.output_dot {
            ParseOutput::Dot
        } else if self.output_xml {
            ParseOutput::Xml
        } else if self.quiet {
            ParseOutput::Quiet
        } else {
            ParseOutput::Normal
        };

        let encoding = if let Some(encoding) = self.encoding {
            match encoding.as_str() {
                "utf16" => Some(ffi::TSInputEncodingUTF16),
                "utf8" => Some(ffi::TSInputEncodingUTF8),
                _ => return Err(anyhow!("Invalid encoding. Expected one of: utf8, utf16")),
            }
        } else {
            None
        };

        let time = self.time;
        let edits = self.edits.unwrap_or_default();
        let cancellation_flag = util::cancel_on_signal();
        let mut parser = Parser::new();

        if self.debug {
            // For augmenting debug logging in external scanners
            env::set_var("TREE_SITTER_DEBUG", "1");
        }

        loader.use_debug_build(self.debug_build);

        #[cfg(feature = "wasm")]
        if self.wasm {
            let engine = tree_sitter::wasmtime::Engine::default();
            parser
                .set_wasm_store(tree_sitter::WasmStore::new(engine.clone()).unwrap())
                .unwrap();
            loader.use_wasm(engine);
        }

        let timeout = self.timeout.unwrap_or_default();

        let paths = collect_paths(self.paths_file.as_deref(), self.paths)?;

        let max_path_length = paths.iter().map(|p| p.chars().count()).max().unwrap_or(0);
        let mut has_error = false;
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;

        let should_track_stats = self.stat;
        let mut stats = parse::Stats::default();

        for path in paths {
            let path = Path::new(&path);

            let language = loader.select_language(path, &current_dir, self.scope.as_deref())?;
            parser
                .set_language(&language)
                .context("incompatible language")?;

            let opts = ParseFileOptions {
                language: language.clone(),
                path,
                edits: &edits.iter().map(|s| s.as_str()).collect::<Vec<&str>>(),
                max_path_length,
                output,
                print_time: time,
                timeout,
                debug: self.debug,
                debug_graph: self.debug_graph,
                cancellation_flag: Some(&cancellation_flag),
                encoding,
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

#[derive(Args)]
#[command(about = "Run a parser's tests", alias = "t")]
struct Test {
    #[arg(
        long,
        short,
        help = "Only run corpus test cases whose name includes the given string"
    )]
    pub filter: Option<String>,
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
    #[arg(long, help = "Apply all captures to highlights")]
    pub apply_all_captures: bool,
}

impl Test {
    fn run(self, mut loader: loader::Loader, current_dir: PathBuf) -> Result<()> {
        if self.debug {
            // For augmenting debug logging in external scanners
            env::set_var("TREE_SITTER_DEBUG", "1");
        }

        loader.use_debug_build(self.debug_build);

        let mut parser = Parser::new();

        #[cfg(feature = "wasm")]
        if self.wasm {
            let engine = tree_sitter::wasmtime::Engine::default();
            parser
                .set_wasm_store(tree_sitter::WasmStore::new(engine.clone()).unwrap())
                .unwrap();
            loader.use_wasm(engine);
        }

        let languages = loader.languages_at_path(&current_dir)?;
        let language = languages
            .first()
            .ok_or_else(|| anyhow!("No language found"))?;
        parser.set_language(language)?;

        let test_dir = current_dir.join("test");

        // Run the corpus tests. Look for them at two paths: `test/corpus` and `corpus`.
        let mut test_corpus_dir = test_dir.join("corpus");
        if !test_corpus_dir.is_dir() {
            test_corpus_dir = current_dir.join("corpus");
        }
        if test_corpus_dir.is_dir() {
            let mut opts = TestOptions {
                path: test_corpus_dir,
                debug: self.debug,
                debug_graph: self.debug_graph,
                filter: self.filter.as_deref(),
                include: self.include,
                exclude: self.exclude,
                update: self.update,
            };

            test::run_tests_at_path(&mut parser, &mut opts)?;
        }

        // Check that all of the queries are valid.
        test::check_queries_at_path(language, &current_dir.join("queries"))?;

        // Run the syntax highlighting tests.
        let test_highlight_dir = test_dir.join("highlight");
        if test_highlight_dir.is_dir() {
            let mut highlighter = Highlighter::new();
            highlighter.parser = parser;
            test_highlight::test_highlights(
                &loader,
                &mut highlighter,
                &test_highlight_dir,
                self.apply_all_captures,
            )?;
            parser = highlighter.parser;
        }

        let test_tag_dir = test_dir.join("tags");
        if test_tag_dir.is_dir() {
            let mut tags_context = TagsContext::new();
            tags_context.parser = parser;
            test_tags::test_tags(&loader, &mut tags_context, &test_tag_dir)?;
        }
        Ok(())
    }
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
}

impl Query {
    fn run(self, config: Config, mut loader: loader::Loader, current_dir: PathBuf) -> Result<()> {
        let paths = collect_paths(self.paths_file.as_deref(), self.paths)?;
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;
        let language =
            loader.select_language(Path::new(&paths[0]), &current_dir, self.scope.as_deref())?;
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
    #[arg(long, help = "Apply all captures to highlights")]
    pub apply_all_captures: bool,
}

impl Highlight {
    fn run(self, config: Config, mut loader: loader::Loader) -> Result<()> {
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
                        eprintln!("No language found for path {path:?}");
                        continue;
                    }
                }
            };

            if let Some(highlight_config) = language_config.highlight_config(
                language,
                self.apply_all_captures,
                self.query_paths.as_deref(),
            )? {
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
}

impl Tags {
    fn run(self, config: Config, mut loader: loader::Loader) -> Result<()> {
        let loader_config = config.get()?;
        loader.find_all_languages(&loader_config)?;
        let paths = collect_paths(self.paths_file.as_deref(), self.paths)?;
        tags::generate_tags(
            &loader,
            self.scope.as_deref(),
            &paths,
            self.quiet,
            self.time,
        )?;
        Ok(())
    }
}

#[derive(Args)]
#[command(about = "Compile a parser to WASM", alias = "bw")]
struct BuildWasm {
    #[arg(
        long,
        help = "Run emscripten via docker even if it is installed locally"
    )]
    pub docker: bool,
    #[arg(index = 1, num_args = 1.., help = "The path to output the wasm file")]
    pub path: Option<String>,
}

impl BuildWasm {
    fn run(self, current_dir: PathBuf, loader: loader::Loader) -> Result<()> {
        let grammar_path = current_dir.join(self.path.unwrap_or_default());
        wasm::compile_language_to_wasm(
            &loader,
            &grammar_path,
            &current_dir,
            self.docker)?;
        Ok(())
    }
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
}

#[derive(Args)]
#[command(about = "Print info about all known language parsers", alias = "langs")]
struct DumpLanguages;

impl DumpLanguages {
    fn run(&self, config: Config, mut loader: loader::Loader) -> Result<()> {
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
    let cli = Commands::augment_subcommands(cli);

    let command = Commands::from_arg_matches(&cli.get_matches())?;

    let current_dir = env::current_dir().unwrap();
    let config = Config::load()?;
    let mut loader = loader::Loader::new()?;

    match command {
        Commands::InitConfig(_) => {
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
        }

        Commands::Generate(generate_options) => {
            if generate_options.log {
                logger::init();
            }
            let abi_version = match generate_options.abi_version {
                Some(ref version) => {
                    if version == "latest" {
                        tree_sitter::LANGUAGE_VERSION
                    } else {
                        version.parse().expect("invalid abi version flag")
                    }
                }
                None => DEFAULT_GENERATE_ABI_VERSION,
            };
            generate::generate_parser_in_directory(
                &current_dir,
                generate_options.grammar_path.as_deref(),
                abi_version,
                !generate_options.no_bindings,
                generate_options.report_states_for_rule.as_deref(),
                generate_options.js_runtime.as_deref(),
            )?;
            if generate_options.build {
                if let Some(path) = generate_options.libdir {
                    loader = loader::Loader::with_parser_lib_path(PathBuf::from(path));
                }
                loader.use_debug_build(generate_options.debug_build);
                loader.languages_at_path(&current_dir)?;
            }
        }

        Commands::Parse(parse_options) => return parse_options.run(config, loader, current_dir),

        Commands::Test(test_options) => return test_options.run(loader, current_dir),

        Commands::Query(query_options) => return query_options.run(config, loader, current_dir),

        Commands::Highlight(highlight_options) => return highlight_options.run(config, loader),

        Commands::Tags(tags_options) => return tags_options.run(config, loader),

        Commands::BuildWasm(wasm_options) => return wasm_options.run(current_dir, loader),

        Commands::Playground(playground_options) => {
            let open_in_browser = !playground_options.quiet;
            playground::serve(&current_dir, open_in_browser)?;
        }

        Commands::DumpLanguages(command) => return command.run(config, loader),
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
