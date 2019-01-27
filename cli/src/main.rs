#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate log;
#[macro_use]
extern crate serde_derive;
extern crate hashbrown;
extern crate regex;
extern crate rsass;
extern crate serde_json;

mod error;
mod generate;
mod loader;
mod logger;
mod parse;
mod test;
mod util;

#[cfg(test)]
mod tests;

use self::loader::Loader;
use clap::{App, AppSettings, Arg, SubCommand};
use std::env;
use std::fs;
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
        .version(concat!(
            env!("CARGO_PKG_VERSION"),
            " (",
            env!("BUILD_SHA"),
            ")"
        ))
        .setting(AppSettings::SubcommandRequiredElseHelp)
        .author("Max Brunsfeld <maxbrunsfeld@gmail.com>")
        .about("Generates and tests parsers")
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
        .get_matches();

    let home_dir = dirs::home_dir().unwrap();
    let current_dir = env::current_dir().unwrap();
    let config_dir = home_dir.join(".tree-sitter");

    fs::create_dir_all(&config_dir).unwrap();
    let mut loader = Loader::new(config_dir);

    if let Some(matches) = matches.subcommand_matches("generate") {
        if matches.is_present("log") {
            logger::init();
        }

        let grammar_path = matches.value_of("grammar-path");
        let minimize = !matches.is_present("no-minimize");
        let properties_only = matches.is_present("properties-only");
        let state_ids_to_log = matches
            .values_of("state-ids-to-log")
            .map_or(Vec::new(), |ids| {
                ids.filter_map(|id| usize::from_str_radix(id, 10).ok())
                    .collect()
            });
        generate::generate_parser_in_directory(
            &current_dir,
            grammar_path,
            minimize,
            state_ids_to_log,
            properties_only,
        )?;
    } else if let Some(matches) = matches.subcommand_matches("test") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let filter = matches.value_of("filter");
        let corpus_path = current_dir.join("corpus");
        if let Some(language) = loader.language_at_path(&current_dir)? {
            if !test::run_tests_at_path(language, &corpus_path, debug, debug_graph, filter)? {
                exit(1);
            }
        } else {
            eprintln!("No language found");
        }
    } else if let Some(matches) = matches.subcommand_matches("parse") {
        let debug = matches.is_present("debug");
        let debug_graph = matches.is_present("debug-graph");
        let quiet = matches.is_present("quiet");
        let time = matches.is_present("time");
        loader.find_all_languages(&vec![home_dir.join("github")])?;
        let paths = matches
            .values_of("path")
            .unwrap()
            .into_iter()
            .collect::<Vec<_>>();
        let max_path_length = paths.iter().map(|p| p.chars().count()).max().unwrap();
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
            parse::parse_file_at_path(
                language,
                path,
                max_path_length,
                quiet,
                time,
                debug,
                debug_graph,
            )?;
        }
    }

    Ok(())
}
