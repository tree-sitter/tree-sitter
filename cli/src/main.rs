use anyhow::{anyhow, Context, Result};
use clap::{Args, Command, FromArgMatches, Subcommand};
use glob::glob;
use std::path::{Path, PathBuf};
use std::{env, fs, u64};
use tree_sitter::{ffi, Point};
use tree_sitter_cli::parse::{ParseFileOptions, ParseOutput};
use tree_sitter_cli::{
    generate, highlight, logger, parse, playground, query, tags, test, test_highlight, test_tags,
    util, wasm,
};
use tree_sitter_config::Config;
use tree_sitter_loader as loader;

const BUILD_VERSION: &'static str = env!("CARGO_PKG_VERSION");
const BUILD_SHA: Option<&'static str> = option_env!("BUILD_SHA");
const DEFAULT_GENERATE_ABI_VERSION: usize = 14;

#[derive(Subcommand)]
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
    #[arg(long, index = 1)]
    pub grammar_path: Option<String>,
    #[arg(long, short, help = "Show debug log during generation")]
    pub log: bool,
    #[arg(
        long = "abi",
        value_name = "version",
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
    #[arg(long, value_name = "path")]
    pub libdir: Option<String>,
    #[arg(long)]
    pub report_states_for_rule: Option<String>,
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
    #[arg(long = "dot")]
    pub output_dot: bool,
    #[arg(long = "xml", short = 'x')]
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
    #[arg(long, short)]
    pub captures: bool,
    #[arg(long)]
    pub test: bool,
}

#[derive(Args)]
#[command(about = "Highlight a file", alias = "hi")]
struct Highlight {
    #[arg(long, short = 'H', help = "Generate highlighting as an HTML document")]
    pub html: bool,
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
        help = "Thepath to a file with paths to source file(s)"
    )]
    pub paths_file: Option<String>,
    #[arg(num_args = 1.., help = "The source file(s) to use")]
    pub paths: Option<Vec<String>>,
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
        help = "Thepath to a file with paths to source file(s)"
    )]
    pub paths_file: Option<String>,
    #[arg(num_args = 1.., help = "The source file(s) to use")]
    pub paths: Option<Vec<String>>,
}

#[derive(Args)]
#[command(about = "Compile a parser to WASM", alias = "bw")]
struct BuildWasm {
    #[arg(
        long,
        help = "Run emscripten via docker even if it is installed locally"
    )]
    pub docker: bool,
    #[arg(index = 1, num_args = 1..)]
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
}

#[derive(Args)]
#[command(about = "Print info about all known language parsers", alias = "langs")]
struct DumpLanguages;

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
            eprintln!("{:?}", err);
        }
        std::process::exit(1);
    }
}

fn run() -> Result<()> {
    let version = if let Some(build_sha) = BUILD_SHA {
        format!("{} ({})", BUILD_VERSION, build_sha)
    } else {
        BUILD_VERSION.to_string()
    };
    let version: &'static str = Box::leak(version.into_boxed_str());

    let cli = Command::new("tree-sitter")
        .author("Max Brunsfeld <maxbrunsfeld@gmail.com>")
        .about("Generates and tests parsers")
        .version(version)
        .subcommand_required(true)
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
                    "utf16" => Some(ffi::TSInputEncoding_TSInputEncodingUTF16),
                    "utf8" => Some(ffi::TSInputEncoding_TSInputEncodingUTF8),
                    _ => return Err(anyhow!("Invalid encoding. Expected one of: utf8, utf16")),
                }
            } else {
                None
            };

            let time = parse_options.time;
            let edits = parse_options.edits.unwrap_or_default();
            let cancellation_flag = util::cancel_on_signal();

            if parse_options.debug {
                // For augmenting debug logging in external scanners
                env::set_var("TREE_SITTER_DEBUG", "1");
            }

            loader.use_debug_build(parse_options.debug_build);

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

                let opts = ParseFileOptions {
                    language,
                    path,
                    edits: &edits.iter().map(|s| s.as_str()).collect::<Vec<&str>>(),
                    max_path_length,
                    output,
                    print_time: time,
                    timeout,
                    debug: parse_options.debug,
                    debug_graph: parse_options.debug_graph,
                    cancellation_flag: Some(&cancellation_flag),
                    encoding,
                };

                let this_file_errored = parse::parse_file_at_path(opts)?;

                if should_track_stats {
                    stats.total_parses += 1;
                    if !this_file_errored {
                        stats.successful_parses += 1;
                    }
                }

                has_error |= this_file_errored;
            }

            if should_track_stats {
                println!("{}", stats)
            }

            if has_error {
                return Err(anyhow!(""));
            }
        }
        Commands::Test(test_options) => {
            if test_options.debug {
                // For augmenting debug logging in external scanners
                env::set_var("TREE_SITTER_DEBUG", "1");
            }

            loader.use_debug_build(test_options.debug_build);

            let languages = loader.languages_at_path(&current_dir)?;
            let language = languages
                .first()
                .ok_or_else(|| anyhow!("No language found"))?;
            let test_dir = current_dir.join("test");

            // Run the corpus tests. Look for them at two paths: `test/corpus` and `corpus`.
            let mut test_corpus_dir = test_dir.join("corpus");
            if !test_corpus_dir.is_dir() {
                test_corpus_dir = current_dir.join("corpus");
            }
            if test_corpus_dir.is_dir() {
                test::run_tests_at_path(
                    *language,
                    &test_corpus_dir,
                    test_options.debug,
                    test_options.debug_graph,
                    test_options.filter.as_deref(),
                    test_options.update,
                )?;
            }

            // Check that all of the queries are valid.
            test::check_queries_at_path(*language, &current_dir.join("queries"))?;

            // Run the syntax highlighting tests.
            let test_highlight_dir = test_dir.join("highlight");
            if test_highlight_dir.is_dir() {
                test_highlight::test_highlights(&loader, &test_highlight_dir)?;
            }

            let test_tag_dir = test_dir.join("tags");
            if test_tag_dir.is_dir() {
                test_tags::test_tags(&loader, &test_tag_dir)?;
            }
        }
        Commands::Query(query_options) => {
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
                let mut parts = range.split(":");
                let start = parts.next()?.parse().ok()?;
                let end = parts.next().unwrap().parse().ok()?;
                Some(start..end)
            });
            let point_range = query_options.row_range.as_ref().and_then(|range| {
                let mut parts = range.split(":");
                let start = parts.next()?.parse().ok()?;
                let end = parts.next().unwrap().parse().ok()?;
                Some(Point::new(start, 0)..Point::new(end, 0))
            });
            query::query_files_at_paths(
                language,
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

            let mut lang = None;
            if let Some(scope) = highlight_options.scope.as_deref() {
                lang = loader.language_configuration_for_scope(scope)?;
                if lang.is_none() {
                    return Err(anyhow!("Unknown scope '{}'", scope));
                }
            }

            for path in paths {
                let path = Path::new(&path);
                let (language, language_config) = match lang {
                    Some(v) => v,
                    None => match loader.language_configuration_for_file_name(path)? {
                        Some(v) => v,
                        None => {
                            eprintln!("No language found for path {:?}", path);
                            continue;
                        }
                    },
                };

                if let Some(highlight_config) = language_config.highlight_config(language)? {
                    let source = fs::read(path)?;
                    if html_mode {
                        highlight::html(
                            &loader,
                            &theme_config.theme,
                            &source,
                            highlight_config,
                            quiet,
                            highlight_options.time,
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
                    eprintln!("No syntax highlighting config found for path {:?}", path);
                }
            }

            if html_mode && !quiet {
                println!("{}", highlight::HTML_FOOTER);
            }
        }
        Commands::Tags(tags_options) => {
            let loader_config = config.get()?;
            loader.find_all_languages(&loader_config)?;
            let paths = collect_paths(tags_options.paths_file.as_deref(), tags_options.paths)?;
            tags::generate_tags(
                &loader,
                tags_options.scope.as_deref(),
                &paths,
                tags_options.quiet,
                tags_options.time,
            )?;
        }
        Commands::BuildWasm(wasm_options) => {
            let grammar_path = current_dir.join(&wasm_options.path.unwrap_or_default());
            wasm::compile_language_to_wasm(&grammar_path, wasm_options.docker)?;
        }
        Commands::Playground(playground_options) => {
            let open_in_browser = !playground_options.quiet;
            playground::serve(&current_dir, open_in_browser);
        }
        Commands::DumpLanguages(_) => {
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

fn collect_paths(paths_file: Option<&str>, paths: Option<Vec<String>>) -> Result<Vec<String>> {
    if let Some(paths_file) = paths_file {
        return Ok(fs::read_to_string(paths_file)
            .with_context(|| format!("Failed to read paths file {}", paths_file))?
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
            } else {
                if let Some(index) = result.iter().position(|p| p == path) {
                    result.remove(index);
                }
            }
        };

        for mut path in paths {
            let mut positive = true;
            if path.starts_with("!") {
                positive = false;
                path = path.trim_start_matches("!").to_string();
            }

            if Path::new(&path).exists() {
                incorporate_path(&path, positive);
            } else {
                let paths =
                    glob(&path).with_context(|| format!("Invalid glob pattern {:?}", path))?;
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
