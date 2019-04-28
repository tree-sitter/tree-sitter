use clap::{App, AppSettings, Arg, SubCommand};
use std::env;
use std::fs;
use std::path::Path;
use std::process::exit;
use std::usize;
use tree_sitter_cli::{
    config, error, generate, highlight, loader, logger, parse, properties, test, wasm,
};

fn main() {
    if let Err(e) = run() {
        eprintln!("{}", e.0);
        exit(1);
    }
}

fn run() -> error::Result<()> {
    let matches = App::new("tree-sitter")
        .version(concat!(
            env!("CARGO_PKG_VERSION"),
            " (",
            env!("BUILD_SHA"),
            ")"
        ))
        .setting(AppSettings::SubcommandRequiredElseHelp)
        .author("Max Brunsfeld <maxbrunsfeld@gmail.com>")
        .about("Generates and tests parsers")
        .subcommand(SubCommand::with_name("init-config").about("Generate a default config file"))
        .subcommand(
            SubCommand::with_name("generate")
                .about("Generate a parser")
                .arg(Arg::with_name("grammar-path").index(1))
                .arg(Arg::with_name("log").long("log"))
                .arg(Arg::with_name("properties-only").long("properties"))
                .arg(
                    Arg::with_name("state-ids-to-log")
                        .long("log-state")
                        .takes_value(true),
                )
                .arg(Arg::with_name("no-minimize").long("no-minimize")),
        )
        .subcommand(
            SubCommand::with_name("parse")
                .about("Parse a file")
                .arg(
                    Arg::with_name("path")
                        .index(1)
                        .multiple(true)
                        .required(true),
                )
                .arg(Arg::with_name("debug").long("debug").short("d"))
                .arg(Arg::with_name("debug-graph").long("debug-graph").short("D"))
                .arg(Arg::with_name("quiet").long("quiet").short("q"))
                .arg(Arg::with_name("time").long("time").short("t")),
        )
        .subcommand(
            SubCommand::with_name("test")
                .about("Run a parser's tests")
                .arg(
                    Arg::with_name("filter")
                        .long("filter")
                        .short("f")
                        .takes_value(true),
                )
                .arg(Arg::with_name("debug").long("debug").short("d"))
                .arg(Arg::with_name("debug-graph").long("debug-graph").short("D")),
        )
        .subcommand(
            SubCommand::with_name("highlight")
                .about("Highlight a file")
                .arg(
                    Arg::with_name("path")
                        .index(1)
                        .multiple(true)
                        .required(true),
                )
                .arg(Arg::with_name("scope").long("scope").takes_value(true))
                .arg(Arg::with_name("html").long("html").short("h")),
        )
        .subcommand(
            SubCommand::with_name("build-wasm")
                .about("Compile a parser to WASM")
                .arg(Arg::with_name("path").index(1).multiple(true)),
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
        if matches.is_present("log") {
            logger::init();
        }

        let grammar_path = matches.value_of("grammar-path");
        let minimize = !matches.is_present("no-minimize");
        let properties_only = matches.is_present("properties-only");
        let parser_only = grammar_path.is_some();
        let state_ids_to_log = matches
            .values_of("state-ids-to-log")
            .map_or(Vec::new(), |ids| {
                ids.filter_map(|id| usize::from_str_radix(id, 10).ok())
                    .collect()
            });

        if !properties_only {
            generate::generate_parser_in_directory(
                &current_dir,
                grammar_path,
                minimize,
                state_ids_to_log,
            )?;
        }

        if !parser_only {
            properties::generate_property_sheets_in_directory(&current_dir)?;
        }
    } else if let Some(matches) = matches.subcommand_matches("test") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let filter = matches.value_of("filter");
        let corpus_path = current_dir.join("corpus");
        if let Some(language) = loader.language_at_path(&current_dir)? {
            test::run_tests_at_path(language, &corpus_path, debug, debug_graph, filter)?;
        } else {
            eprintln!("No language found");
        }
    } else if let Some(matches) = matches.subcommand_matches("parse") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let quiet = matches.is_present("quiet");
        let time = matches.is_present("time");
        loader.find_all_languages(&config.parser_directories)?;
        let paths = matches
            .values_of("path")
            .unwrap()
            .into_iter()
            .collect::<Vec<_>>();
        let max_path_length = paths.iter().map(|p| p.chars().count()).max().unwrap();
        let mut has_error = false;
        for path in paths {
            let path = Path::new(path);
            let language =
                if let Some((l, _)) = loader.language_configuration_for_file_name(path)? {
                    l
                } else if let Some(l) = loader.language_at_path(&current_dir)? {
                    l
                } else {
                    eprintln!("No language found");
                    return Ok(());
                };
            has_error |= parse::parse_file_at_path(
                language,
                path,
                max_path_length,
                quiet,
                time,
                debug,
                debug_graph,
            )?;
        }

        if has_error {
            return Err(error::Error(String::new()));
        }
    } else if let Some(matches) = matches.subcommand_matches("highlight") {
        let paths = matches.values_of("path").unwrap().into_iter();
        let html_mode = matches.is_present("html");
        loader.find_all_languages(&config.parser_directories)?;

        if html_mode {
            println!("{}", highlight::HTML_HEADER);
        }

        let language_config;
        if let Some(scope) = matches.value_of("scope") {
            language_config = loader.language_configuration_for_scope(scope)?;
            if language_config.is_none() {
                return Err(error::Error(format!("Unknown scope '{}'", scope)));
            }
        } else {
            language_config = None;
        }

        for path in paths {
            let path = Path::new(path);
            let (language, language_config) = match language_config {
                Some(v) => v,
                None => match loader.language_configuration_for_file_name(path)? {
                    Some(v) => v,
                    None => {
                        eprintln!("No language found for path {:?}", path);
                        continue;
                    }
                },
            };

            if let Some(sheet) = language_config.highlight_property_sheet(language)? {
                let source = fs::read(path)?;
                if html_mode {
                    highlight::html(&loader, &config.theme, &source, language, sheet)?;
                } else {
                    highlight::ansi(&loader, &config.theme, &source, language, sheet)?;
                }
            } else {
                return Err(error::Error(format!(
                    "No syntax highlighting property sheet specified"
                )));
            }
        }
    } else if let Some(matches) = matches.subcommand_matches("build-wasm") {
        let grammar_path = current_dir.join(matches.value_of("path").unwrap_or(""));
        wasm::compile_language_to_wasm(&grammar_path)?;
    }

    Ok(())
}
