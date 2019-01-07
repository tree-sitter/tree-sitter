#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate log;
#[macro_use]
extern crate serde_derive;
extern crate hashbrown;
extern crate serde_json;

mod error;
mod generate;
mod logger;

use clap::{App, Arg, SubCommand};
use std::env;
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
                .arg(Arg::with_name("path").index(1)),
        )
        .subcommand(
            SubCommand::with_name("test")
                .about("Run a parser's tests")
                .arg(Arg::with_name("path").index(1).required(true))
                .arg(Arg::with_name("line").index(2).required(true))
                .arg(Arg::with_name("column").index(3).required(true)),
        )
        .get_matches();

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
        let mut grammar_path = env::current_dir().expect("Failed to read CWD");
        grammar_path.push("grammar.js");
        let code =
            generate::generate_parser_for_grammar(&grammar_path, minimize, state_ids_to_log)?;
        println!("{}", code);
    }

    Ok(())
}
