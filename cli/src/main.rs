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
    #[arg(index = 1, help = "The path to the grammar file")]
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
    #[arg(
        long,
        help = "Open `log.html` in the default browser, if `--debug-graph` is supplied"
    )]
    pub open_log: bool,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
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
    #[arg(
        long,
        help = "Open `log.html` in the default browser, if `--debug-graph` is supplied"
    )]
    pub open_log: bool,
    #[arg(long, help = "The path to an alternative config.json file")]
    pub config_path: Option<PathBuf>,
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
            let abi_version = generate_options.abi_version.as_ref().map_or(
                DEFAULT_GENERATE_ABI_VERSION,
                |version| {
                    if version == "latest" {
                        tree_sitter::LANGUAGE_VERSION
                    } else {
                        version.parse().expect("invalid abi version flag")
                    }
                },
            );
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

        Commands::Parse(parse_options) => {
            let config = Config::load(parse_options.config_path)?;
            let output = if parse_options.output_dot {
                ParseOutput::Dot
            } else if parse_options.output_xml {
                ParseOutput::Xml
            } else if parse_options.quiet {
                ParseOutput::Quiet
            } else {
                ParseOutput::Normal
            };

            let encoding = if let Some(encoding) = parse_options.encoding {
                match encoding.as_str() {
                    "utf16" => Some(ffi::TSInputEncodingUTF16),
                    "utf8" => Some(ffi::TSInputEncodingUTF8),
                    _ => return Err(anyhow!("Invalid encoding. Expected one of: utf8, utf16")),
                }
            } else {
                None
            };

            let time = parse_options.time;
            let edits = parse_options.edits.unwrap_or_default();
            let cancellation_flag = util::cancel_on_signal();
            let mut parser = Parser::new();

            if parse_options.debug {
                // For augmenting debug logging in external scanners
                env::set_var("TREE_SITTER_DEBUG", "1");
            }

            loader.use_debug_build(parse_options.debug_build);

            #[cfg(feature = "wasm")]
            if parse_options.wasm {
                let engine = tree_sitter::wasmtime::Engine::default();
                parser
                    .set_wasm_store(tree_sitter::WasmStore::new(engine.clone()).unwrap())
                    .unwrap();
                loader.use_wasm(engine);
            }

            let timeout = parse_options.timeout.unwrap_or_default();

            let paths = collect_paths(parse_options.paths_file.as_deref(), parse_options.paths)?;

            let max_path_length = paths.iter().map(|p| p.chars().count()).max().unwrap_or(0);
            let mut has_error = false;
            let loader_config = config.get()?;
            loader.find_all_languages(&loader_config)?;

            let should_track_stats = parse_options.stat;
            let mut stats = parse::Stats::default();

            for path in paths {
                let path = Path::new(&path);

                let language =
                    loader.select_language(path, &current_dir, parse_options.scope.as_deref())?;
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
                    debug: parse_options.debug,
                    debug_graph: parse_options.debug_graph,
                    cancellation_flag: Some(&cancellation_flag),
                    encoding,
                    open_log: parse_options.open_log,
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
        }

        Commands::Test(test_options) => {
            let config = Config::load(test_options.config_path)?;
            if test_options.debug {
                // For augmenting debug logging in external scanners
                env::set_var("TREE_SITTER_DEBUG", "1");
            }

            loader.use_debug_build(test_options.debug_build);

            let mut parser = Parser::new();

            #[cfg(feature = "wasm")]
            if test_options.wasm {
                let engine = tree_sitter::wasmtime::Engine::default();
                parser
                    .set_wasm_store(tree_sitter::WasmStore::new(engine.clone()).unwrap())
                    .unwrap();
                loader.use_wasm(engine);
            }

            let languages = loader.languages_at_path(&current_dir)?;
            let language = &languages
                .first()
                .ok_or_else(|| anyhow!("No language found"))?
                .0;
            parser.set_language(language)?;

            let test_dir = current_dir.join("test");

            // Run the corpus tests. Look for them in `test/corpus`.
            let test_corpus_dir = test_dir.join("corpus");
            if test_corpus_dir.is_dir() {
                let mut opts = TestOptions {
                    path: test_corpus_dir,
                    debug: test_options.debug,
                    debug_graph: test_options.debug_graph,
                    filter: test_options.filter.as_deref(),
                    include: test_options.include,
                    exclude: test_options.exclude,
                    update: test_options.update,
                    open_log: test_options.open_log,
                    languages: languages.iter().map(|(l, n)| (n.as_str(), l)).collect(),
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
                    &config.get()?,
                    &mut highlighter,
                    &test_highlight_dir,
                )?;
                parser = highlighter.parser;
            }

            let test_tag_dir = test_dir.join("tags");
            if test_tag_dir.is_dir() {
                let mut tags_context = TagsContext::new();
                tags_context.parser = parser;
                test_tags::test_tags(&loader, &config.get()?, &mut tags_context, &test_tag_dir)?;
            }
        }

        Commands::Query(query_options) => {
            let config = Config::load(query_options.config_path)?;
            let paths = collect_paths(query_options.paths_file.as_deref(), query_options.paths)?;
            let loader_config = config.get()?;
            loader.find_all_languages(&loader_config)?;
            let language = loader.select_language(
                Path::new(&paths[0]),
                &current_dir,
                query_options.scope.as_deref(),
            )?;
            let query_path = Path::new(&query_options.query_path);

            let byte_range = query_options.byte_range.as_ref().and_then(|range| {
                let mut parts = range.split(':');
                let start = parts.next()?.parse().ok()?;
                let end = parts.next().unwrap().parse().ok()?;
                Some(start..end)
            });
            let point_range = query_options.row_range.as_ref().and_then(|range| {
                let mut parts = range.split(':');
                let start = parts.next()?.parse().ok()?;
                let end = parts.next().unwrap().parse().ok()?;
                Some(Point::new(start, 0)..Point::new(end, 0))
            });

            query::query_files_at_paths(
                &language,
                paths,
                query_path,
                query_options.captures,
                byte_range,
                point_range,
                query_options.test,
                query_options.quiet,
                query_options.time,
            )?;
        }

        Commands::Highlight(highlight_options) => {
            let config = Config::load(highlight_options.config_path)?;
            let theme_config: tree_sitter_cli::highlight::ThemeConfig = config.get()?;
            loader.configure_highlights(&theme_config.theme.highlight_names);
            let loader_config = config.get()?;
            loader.find_all_languages(&loader_config)?;

            let quiet = highlight_options.quiet;
            let html_mode = quiet || highlight_options.html;
            let paths = collect_paths(
                highlight_options.paths_file.as_deref(),
                highlight_options.paths,
            )?;

            if html_mode && !quiet {
                println!("{}", highlight::HTML_HEADER);
            }

            let cancellation_flag = util::cancel_on_signal();

            let mut language = None;
            if let Some(scope) = highlight_options.scope.as_deref() {
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

                if let Some(highlight_config) = language_config
                    .highlight_config(language, highlight_options.query_paths.as_deref())?
                {
                    if highlight_options.check {
                        let names = if let Some(path) = highlight_options.captures_path.as_deref() {
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
                            highlight_options.time,
                            Some(&cancellation_flag),
                        )?;
                    } else {
                        highlight::ansi(
                            &loader,
                            &theme_config.theme,
                            &source,
                            highlight_config,
                            highlight_options.time,
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
        }

        Commands::Tags(tags_options) => {
            let config = Config::load(tags_options.config_path)?;
            let loader_config = config.get()?;
            loader.find_all_languages(&loader_config)?;
            let paths = collect_paths(tags_options.paths_file.as_deref(), tags_options.paths)?;
            tags::generate_tags(
                &loader,
                &config.get()?,
                tags_options.scope.as_deref(),
                &paths,
                tags_options.quiet,
                tags_options.time,
            )?;
        }

        Commands::BuildWasm(wasm_options) => {
            let grammar_path = current_dir.join(wasm_options.path.unwrap_or_default());
            wasm::compile_language_to_wasm(
                &loader,
                &grammar_path,
                &current_dir,
                wasm_options.docker,
            )?;
        }

        Commands::Playground(playground_options) => {
            let open_in_browser = !playground_options.quiet;
            let grammar_path = playground_options
                .grammar_path
                .map(PathBuf::from)
                .unwrap_or(current_dir);
            playground::serve(&grammar_path, open_in_browser)?;
        }

        Commands::DumpLanguages(dump_options) => {
            let config = Config::load(dump_options.config_path)?;
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
        }
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
