use clap::{App, AppSettings, Arg, SubCommand};
use error::Error;
use glob::glob;
use std::path::Path;
use std::process::exit;
use std::{env, fs, u64};
use tree_sitter::Language;
use tree_sitter_cli::{
    config, error, generate, highlight, loader, logger, parse, query, tags, test, test_highlight,
    util, wasm, web_ui,
};

const BUILD_VERSION: &'static str = env!("CARGO_PKG_VERSION");
const BUILD_SHA: Option<&'static str> = option_env!("BUILD_SHA");

fn main() {
    if let Err(e) = run() {
        if !e.message().is_empty() {
            println!("");
            eprintln!("{}", e.message());
        }
        exit(1);
    }
}

fn run() -> error::Result<()> {
    let version = if let Some(build_sha) = BUILD_SHA {
        format!("{} ({})", BUILD_VERSION, build_sha)
    } else {
        BUILD_VERSION.to_string()
    };

    let matches = App::new("tree-sitter")
        .version(version.as_str())
        .setting(AppSettings::SubcommandRequiredElseHelp)
        .author("Max Brunsfeld <maxbrunsfeld@gmail.com>")
        .about("Generates and tests parsers")
        .subcommand(SubCommand::with_name("init-config").about("Generate a default config file"))
        .subcommand(
            SubCommand::with_name("generate")
                .about("Generate a parser")
                .arg(Arg::with_name("grammar-path").index(1))
                .arg(Arg::with_name("log").long("log"))
                .arg(Arg::with_name("prev-abi").long("prev-abi"))
                .arg(Arg::with_name("no-bindings").long("no-bindings"))
                .arg(
                    Arg::with_name("report-states-for-rule")
                        .long("report-states-for-rule")
                        .value_name("rule-name")
                        .takes_value(true),
                )
                .arg(Arg::with_name("no-minimize").long("no-minimize")),
        )
        .subcommand(
            SubCommand::with_name("parse")
                .about("Parse files")
                .arg(Arg::with_name("paths-file").long("paths").takes_value(true))
                .arg(
                    Arg::with_name("paths")
                        .index(1)
                        .multiple(true)
                        .required(false),
                )
                .arg(Arg::with_name("scope").long("scope").takes_value(true))
                .arg(Arg::with_name("debug").long("debug").short("d"))
                .arg(Arg::with_name("debug-graph").long("debug-graph").short("D"))
                .arg(Arg::with_name("debug-xml").long("xml").short("x"))
                .arg(Arg::with_name("quiet").long("quiet").short("q"))
                .arg(Arg::with_name("stat").long("stat").short("s"))
                .arg(Arg::with_name("time").long("time").short("t"))
                .arg(Arg::with_name("timeout").long("timeout").takes_value(true))
                .arg(
                    Arg::with_name("edits")
                        .long("edit")
                        .short("edit")
                        .takes_value(true)
                        .multiple(true)
                        .number_of_values(1),
                ),
        )
        .subcommand(
            SubCommand::with_name("query")
                .about("Search files using a syntax tree query")
                .arg(Arg::with_name("query-path").index(1).required(true))
                .arg(Arg::with_name("paths-file").long("paths").takes_value(true))
                .arg(
                    Arg::with_name("paths")
                        .index(2)
                        .multiple(true)
                        .required(false),
                )
                .arg(
                    Arg::with_name("byte-range")
                        .help("The range of byte offsets in which the query will be executed")
                        .long("byte-range")
                        .takes_value(true),
                )
                .arg(Arg::with_name("scope").long("scope").takes_value(true))
                .arg(Arg::with_name("captures").long("captures").short("c"))
                .arg(Arg::with_name("test").long("test")),
        )
        .subcommand(
            SubCommand::with_name("tags")
                .arg(Arg::with_name("quiet").long("quiet").short("q"))
                .arg(Arg::with_name("time").long("time").short("t"))
                .arg(Arg::with_name("scope").long("scope").takes_value(true))
                .arg(Arg::with_name("paths-file").long("paths").takes_value(true))
                .arg(
                    Arg::with_name("paths")
                        .help("The source file to use")
                        .index(1)
                        .multiple(true),
                ),
        )
        .subcommand(
            SubCommand::with_name("test")
                .about("Run a parser's tests")
                .arg(
                    Arg::with_name("filter")
                        .long("filter")
                        .short("f")
                        .takes_value(true)
                        .help("Only run corpus test cases whose name includes the given string"),
                )
                .arg(Arg::with_name("update").long("update").short("u").help("Update all syntax trees in corpus files with current parser output"))
                .arg(Arg::with_name("debug").long("debug").short("d"))
                .arg(Arg::with_name("debug-graph").long("debug-graph").short("D")),
        )
        .subcommand(
            SubCommand::with_name("highlight")
                .about("Highlight a file")
                .arg(Arg::with_name("paths-file").long("paths").takes_value(true))
                .arg(
                    Arg::with_name("paths")
                        .index(1)
                        .multiple(true)
                        .required(false),
                )
                .arg(Arg::with_name("scope").long("scope").takes_value(true))
                .arg(Arg::with_name("html").long("html").short("h"))
                .arg(Arg::with_name("time").long("time").short("t"))
                .arg(Arg::with_name("quiet").long("quiet").short("q")),
        )
        .subcommand(
            SubCommand::with_name("build-wasm")
                .about("Compile a parser to WASM")
                .arg(
                    Arg::with_name("docker")
                        .long("docker")
                        .help("Run emscripten via docker even if it is installed locally"),
                )
                .arg(Arg::with_name("path").index(1).multiple(true)),
        )
        .subcommand(
            SubCommand::with_name("web-ui")
                .about("Test a parser interactively in the browser")
                .arg(
                    Arg::with_name("quiet")
                        .long("quiet")
                        .short("q")
                        .help("open in default browser"),
                ),
        )
        .subcommand(
            SubCommand::with_name("dump-languages")
                .about("Print info about all known language parsers"),
        )
        .get_matches();

    let home_dir = dirs::home_dir().expect("Failed to read home directory");
    let current_dir = env::current_dir().unwrap();
    let config = config::Config::load(&home_dir);
    let mut loader = loader::Loader::new(config.binary_directory.clone());

    if matches.subcommand_matches("init-config").is_some() {
        let config = config::Config::new(&home_dir);
        config.save(&home_dir)?;
    } else if let Some(matches) = matches.subcommand_matches("generate") {
        let grammar_path = matches.value_of("grammar-path");
        let report_symbol_name = matches.value_of("report-states-for-rule").or_else(|| {
            if matches.is_present("report-states") {
                Some("")
            } else {
                None
            }
        });
        if matches.is_present("log") {
            logger::init();
        }
        let new_abi = !matches.is_present("prev-abi");
        let generate_bindings = !matches.is_present("no-bindings");
        generate::generate_parser_in_directory(
            &current_dir,
            grammar_path,
            new_abi,
            generate_bindings,
            report_symbol_name,
        )?;
    } else if let Some(matches) = matches.subcommand_matches("test") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let update = matches.is_present("update");
        let filter = matches.value_of("filter");
        let languages = loader.languages_at_path(&current_dir)?;
        let language = languages
            .first()
            .ok_or_else(|| "No language found".to_string())?;
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
                debug,
                debug_graph,
                filter,
                update,
            )?;
        }

        // Check that all of the queries are valid.
        test::check_queries_at_path(*language, &current_dir.join("queries"))?;

        // Run the syntax highlighting tests.
        let test_highlight_dir = test_dir.join("highlight");
        if test_highlight_dir.is_dir() {
            test_highlight::test_highlights(&loader, &test_highlight_dir)?;
        }
    } else if let Some(matches) = matches.subcommand_matches("parse") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let debug_xml = matches.is_present("debug-xml");
        let quiet = matches.is_present("quiet");
        let time = matches.is_present("time");
        let edits = matches
            .values_of("edits")
            .map_or(Vec::new(), |e| e.collect());
        let cancellation_flag = util::cancel_on_stdin();

        let timeout = matches
            .value_of("timeout")
            .map_or(0, |t| u64::from_str_radix(t, 10).unwrap());

        let paths = collect_paths(matches.value_of("paths-file"), matches.values_of("paths"))?;

        let max_path_length = paths.iter().map(|p| p.chars().count()).max().unwrap();
        let mut has_error = false;
        loader.find_all_languages(&config.parser_directories)?;

        let should_track_stats = matches.is_present("stat");
        let mut stats = parse::Stats::default();

        for path in paths {
            let path = Path::new(&path);
            let language =
                select_language(&mut loader, path, &current_dir, matches.value_of("scope"))?;

            let this_file_errored = parse::parse_file_at_path(
                language,
                path,
                &edits,
                max_path_length,
                quiet,
                time,
                timeout,
                debug,
                debug_graph,
                debug_xml,
                Some(cancellation_flag.clone()),
            )?;

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
            return Error::err(String::new());
        }
    } else if let Some(matches) = matches.subcommand_matches("query") {
        let ordered_captures = matches.values_of("captures").is_some();
        let paths = collect_paths(matches.value_of("paths-file"), matches.values_of("paths"))?;
        loader.find_all_languages(&config.parser_directories)?;
        let language = select_language(
            &mut loader,
            Path::new(&paths[0]),
            &current_dir,
            matches.value_of("scope"),
        )?;
        let query_path = Path::new(matches.value_of("query-path").unwrap());
        let range = matches.value_of("byte-range").map(|br| {
            let r: Vec<&str> = br.split(":").collect();
            (r[0].parse().unwrap(), r[1].parse().unwrap())
        });
        let should_test = matches.is_present("test");
        query::query_files_at_paths(
            language,
            paths,
            query_path,
            ordered_captures,
            range,
            should_test,
        )?;
    } else if let Some(matches) = matches.subcommand_matches("tags") {
        loader.find_all_languages(&config.parser_directories)?;
        let paths = collect_paths(matches.value_of("paths-file"), matches.values_of("paths"))?;
        tags::generate_tags(
            &loader,
            matches.value_of("scope"),
            &paths,
            matches.is_present("quiet"),
            matches.is_present("time"),
        )?;
    } else if let Some(matches) = matches.subcommand_matches("highlight") {
        loader.configure_highlights(&config.theme.highlight_names);
        loader.find_all_languages(&config.parser_directories)?;

        let time = matches.is_present("time");
        let quiet = matches.is_present("quiet");
        let html_mode = quiet || matches.is_present("html");
        let paths = collect_paths(matches.value_of("paths-file"), matches.values_of("paths"))?;

        if html_mode && !quiet {
            println!("{}", highlight::HTML_HEADER);
        }

        let cancellation_flag = util::cancel_on_stdin();

        let mut lang = None;
        if let Some(scope) = matches.value_of("scope") {
            lang = loader.language_configuration_for_scope(scope)?;
            if lang.is_none() {
                return Error::err(format!("Unknown scope '{}'", scope));
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
                        &config.theme,
                        &source,
                        highlight_config,
                        quiet,
                        time,
                    )?;
                } else {
                    highlight::ansi(
                        &loader,
                        &config.theme,
                        &source,
                        highlight_config,
                        time,
                        Some(cancellation_flag.clone()),
                    )?;
                }
            } else {
                eprintln!("No syntax highlighting config found for path {:?}", path);
            }
        }

        if html_mode && !quiet {
            println!("{}", highlight::HTML_FOOTER);
        }
    } else if let Some(matches) = matches.subcommand_matches("build-wasm") {
        let grammar_path = current_dir.join(matches.value_of("path").unwrap_or(""));
        wasm::compile_language_to_wasm(&grammar_path, matches.is_present("docker"))?;
    } else if let Some(matches) = matches.subcommand_matches("web-ui") {
        let open_in_browser = !matches.is_present("quiet");
        web_ui::serve(&current_dir, open_in_browser);
    } else if matches.subcommand_matches("dump-languages").is_some() {
        loader.find_all_languages(&config.parser_directories)?;
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

    Ok(())
}

fn collect_paths<'a>(
    paths_file: Option<&str>,
    paths: Option<impl Iterator<Item = &'a str>>,
) -> error::Result<Vec<String>> {
    if let Some(paths_file) = paths_file {
        return Ok(fs::read_to_string(paths_file)
            .map_err(Error::wrap(|| {
                format!("Failed to read paths file {}", paths_file)
            }))?
            .trim()
            .split_ascii_whitespace()
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
                path = path.trim_start_matches("!");
            }

            if Path::new(path).exists() {
                incorporate_path(path, positive);
            } else {
                let paths = glob(path)
                    .map_err(Error::wrap(|| format!("Invalid glob pattern {:?}", path)))?;
                for path in paths {
                    if let Some(path) = path?.to_str() {
                        incorporate_path(path, positive);
                    }
                }
            }
        }

        if result.is_empty() {
            Error::err(
                "No files were found at or matched by the provided pathname/glob".to_string(),
            )?;
        }

        return Ok(result);
    }

    Err(Error::new("Must provide one or more paths".to_string()))
}

fn select_language(
    loader: &mut loader::Loader,
    path: &Path,
    current_dir: &Path,
    scope: Option<&str>,
) -> Result<Language, Error> {
    if let Some(scope) = scope {
        if let Some(config) =
            loader
                .language_configuration_for_scope(scope)
                .map_err(Error::wrap(|| {
                    format!("Failed to load language for scope '{}'", scope)
                }))?
        {
            Ok(config.0)
        } else {
            return Error::err(format!("Unknown scope '{}'", scope));
        }
    } else if let Some((lang, _)) =
        loader
            .language_configuration_for_file_name(path)
            .map_err(Error::wrap(|| {
                format!(
                    "Failed to load language for file name {:?}",
                    path.file_name().unwrap()
                )
            }))?
    {
        Ok(lang)
    } else if let Some(lang) = loader
        .languages_at_path(&current_dir)
        .map_err(Error::wrap(|| {
            "Failed to load language in current directory"
        }))?
        .first()
        .cloned()
    {
        Ok(lang)
    } else {
        eprintln!("No language found");
        Error::err("No language found".to_string())
    }
}
