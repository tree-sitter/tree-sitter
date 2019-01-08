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
                .arg(Arg::with_name("path").index(1)),
        )
        .subcommand(SubCommand::with_name("test").about("Run a parser's tests"))
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
        let grammar_path = current_dir.join("grammar.js");
        let code =
            generate::generate_parser_for_grammar(&grammar_path, minimize, state_ids_to_log)?;
        println!("{}", code);
        return Ok(());
    }

    if let Some(_matches) = matches.subcommand_matches("test") {
        let corpus_path = current_dir.join("corpus");
        let home_dir = dirs::home_dir().unwrap();
        let mut loader = Loader::new(home_dir.join(".tree-sitter"));
        if let Some((language, _)) = loader.language_configuration_at_path(&current_dir)? {
            test::run_tests_at_path(language, &corpus_path)?;
        } else {
            eprintln!("No language found");
        }
    }

    if let Some(matches) = matches.subcommand_matches("parse") {
        loader.find_parsers(&vec![home_dir.join("github")])?;
        let source_path = Path::new(matches.value_of("path").unwrap());
        if let Some((language, _)) = loader.language_for_file_name(source_path)? {
            parse::parse_file_at_path(language, source_path)?;
        } else {
            eprintln!("No language found");
        }
    }

    Ok(())
}
