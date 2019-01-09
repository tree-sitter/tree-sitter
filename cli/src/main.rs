#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate log;
#[macro_use]
extern crate serde_derive;
extern crate hashbrown;
extern crate regex;
extern crate serde_json;

mod error;
mod generate;
mod loader;
mod logger;
mod parse;
mod test;
mod util;

use self::loader::Loader;
use clap::{App, Arg, SubCommand};
use std::env;
use std::path::Path;
use std::process::exit;
use std::usize;

fn main() {
    if let Err(e) = run() {
        eprintln!("{}", e.0);
        exit(1);
    }
}

fn run() -> error::Result<()> {
    let matches = App::new("tree-sitter")
        .version("0.1")
        .author("Max Brunsfeld <maxbrunsfeld@gmail.com>")
        .about("Generates and tests parsers")
        .subcommand(
            SubCommand::with_name("generate")
                .about("Generate a parser")
                .arg(Arg::with_name("log").long("log"))
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
                .arg(Arg::with_name("path").index(1).required(true))
                .arg(Arg::with_name("debug").long("debug").short("d"))
                .arg(Arg::with_name("debug-graph").long("debug-graph").short("D")),
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
        .get_matches();

    let home_dir = dirs::home_dir().unwrap();
    let current_dir = env::current_dir().unwrap();
    let mut loader = Loader::new(home_dir.join(".tree-sitter"));

    if let Some(matches) = matches.subcommand_matches("generate") {
        if matches.is_present("log") {
            logger::init();
        }

        let minimize = !matches.is_present("no-minimize");
        let state_ids_to_log = matches
            .values_of("state-ids-to-log")
            .map_or(Vec::new(), |ids| {
                ids.filter_map(|id| usize::from_str_radix(id, 10).ok())
                    .collect()
            });
        generate::generate_parser_for_grammar(&current_dir, minimize, state_ids_to_log)?;
    } else if let Some(matches) = matches.subcommand_matches("test") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let filter = matches.value_of("filter");
        let corpus_path = current_dir.join("corpus");
        if let Some((language, _)) = loader.language_configuration_at_path(&current_dir)? {
            test::run_tests_at_path(language, &corpus_path, debug, debug_graph, filter)?;
        } else {
            eprintln!("No language found");
        }
    } else if let Some(matches) = matches.subcommand_matches("parse") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        loader.find_parsers(&vec![home_dir.join("github")])?;
        let source_path = Path::new(matches.value_of("path").unwrap());
        if let Some((language, _)) = loader.language_for_file_name(source_path)? {
            parse::parse_file_at_path(language, source_path, debug, debug_graph)?;
        } else {
            eprintln!("No language found");
        }
    }

    Ok(())
}
