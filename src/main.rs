use clap::{App, Arg, SubCommand};

#[macro_use] extern crate serde_derive;
#[macro_use] extern crate serde_json;

mod build_tables;
mod error;
mod generate;
mod grammars;
mod nfa;
mod parse_grammar;
mod prepare_grammar;
mod render;
mod rules;
mod tables;

fn main() -> error::Result<()> {
    let matches = App::new("tree-sitter")
        .version("0.1")
        .author("Max Brunsfeld <maxbrunsfeld@gmail.com>")
        .about("Generates and tests parsers")
        .subcommand(
            SubCommand::with_name("generate")
                .about("Generate a parser")
        ).subcommand(
            SubCommand::with_name("parse")
                .about("Parse a file")
                .arg(Arg::with_name("path").index(1))
        ).subcommand(
            SubCommand::with_name("test")
                .about("Run a parser's tests")
                .arg(Arg::with_name("path").index(1).required(true))
                .arg(Arg::with_name("line").index(2).required(true))
                .arg(Arg::with_name("column").index(3).required(true))
        ).get_matches();

    if let Some(matches) = matches.subcommand_matches("generate") {
        let code = generate::generate_parser_for_grammar(String::new())?;
        println!("{}", code);
    }

    Ok(())
}
