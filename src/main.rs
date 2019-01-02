#[macro_use]
extern crate serde_derive;
#[macro_use]
extern crate serde_json;
#[macro_use]
extern crate lazy_static;

use std::path::PathBuf;
use clap::{App, Arg, SubCommand};
use std::env;
use std::io::Write;
use std::process::{Command, Stdio};

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
        .subcommand(SubCommand::with_name("generate").about("Generate a parser"))
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

    if let Some(_) = matches.subcommand_matches("generate") {
        let mut grammar_path = env::current_dir().expect("Failed to read CWD");
        grammar_path.push("grammar.js");
        let grammar_json = load_js_grammar_file(grammar_path);
        let code = generate::generate_parser_for_grammar(&grammar_json)?;
        println!("{}", code);
    }

    Ok(())
}

fn load_js_grammar_file(grammar_path: PathBuf) -> String {
    let mut node_process = Command::new("node")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("Failed to run `node`");

    let js_prelude = include_str!("./js/dsl.js");
    let mut node_stdin = node_process
        .stdin
        .take()
        .expect("Failed to open stdin for node");
    write!(
        node_stdin,
        "{}\nconsole.log(JSON.stringify(require(\"{}\"), null, 2));\n",
        js_prelude,
        grammar_path.to_str().unwrap()
    ).expect("Failed to write to node's stdin");
    drop(node_stdin);
    let output = node_process
        .wait_with_output()
        .expect("Failed to read output from node");
    match output.status.code() {
        None => panic!("Node process was killed"),
        Some(0) => {}
        Some(code) => panic!(format!("Node process exited with status {}", code)),
    }

    String::from_utf8(output.stdout).expect("Got invalid UTF8 from node")
}
