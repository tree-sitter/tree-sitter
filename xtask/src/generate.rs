use std::{ffi::OsStr, fs, process::Command};

use anyhow::{Context, Result};

use crate::{bail_on_err, GenerateFixtures};

const HEADER_PATH: &str = "include/tree_sitter/api.h";

pub fn run_fixtures(args: &GenerateFixtures) -> Result<()> {
    let output = std::process::Command::new("cargo")
        .args(["build", "--release"])
        .spawn()?
        .wait_with_output()?;
    bail_on_err(&output, "Failed to run cargo build")?;

    let tree_sitter_binary = std::env::current_dir()?
        .join("target")
        .join("release")
        .join("tree-sitter");

    let grammars_dir = std::env::current_dir()?
        .join("test")
        .join("fixtures")
        .join("grammars");

    for grammar_file in find_grammar_files(grammars_dir.to_str().unwrap()).flatten() {
        let grammar_dir = grammar_file.parent().unwrap();
        let grammar_name = grammar_dir.file_name().and_then(OsStr::to_str).unwrap();

        println!(
            "Regenerating {grammar_name} parser{}",
            if args.wasm { " to wasm" } else { "" }
        );

        if args.wasm {
            let mut cmd = Command::new(&tree_sitter_binary);
            let cmd = cmd.args([
                "build",
                "--wasm",
                "-o",
                &format!("target/release/tree-sitter-{grammar_name}.wasm"),
                grammar_dir.to_str().unwrap(),
            ]);
            if args.docker {
                cmd.arg("--docker");
            }
            bail_on_err(
                &cmd.spawn()?.wait_with_output()?,
                &format!("Failed to regenerate {grammar_name} parser to wasm"),
            )?;
        } else {
            let output = Command::new(&tree_sitter_binary)
                .arg("generate")
                .arg("src/grammar.json")
                .arg("--abi=latest")
                .current_dir(grammar_dir)
                .spawn()?
                .wait_with_output()?;
            bail_on_err(
                &output,
                &format!("Failed to regenerate {grammar_name} parser"),
            )?;
        }
    }

    Ok(())
}

pub fn run_bindings() -> Result<()> {
    let no_copy = [
        "TSInput",
        "TSLanguage",
        "TSLogger",
        "TSLookaheadIterator",
        "TSParser",
        "TSTree",
        "TSQuery",
        "TSQueryCursor",
        "TSQueryCapture",
        "TSQueryMatch",
        "TSQueryPredicateStep",
    ];

    let bindings = bindgen::Builder::default()
        .header(HEADER_PATH)
        .layout_tests(false)
        .allowlist_type("^TS.*")
        .allowlist_function("^ts_.*")
        .allowlist_var("^TREE_SITTER.*")
        .no_copy(no_copy.join("|"))
        .prepend_enum_name(false)
        .use_core()
        .clang_arg("-D TREE_SITTER_FEATURE_WASM")
        .generate()
        .expect("Failed to generate bindings");

    bindings
        .write_to_file("lib/binding_rust/bindings.rs")
        .with_context(|| "Failed to write bindings")
}

fn find_grammar_files(
    dir: &str,
) -> impl Iterator<Item = Result<std::path::PathBuf, std::io::Error>> {
    fs::read_dir(dir)
        .expect("Failed to read directory")
        .filter_map(Result::ok)
        .flat_map(|entry| {
            let path = entry.path();
            if path.is_dir() && !path.to_string_lossy().contains("node_modules") {
                Box::new(find_grammar_files(path.to_str().unwrap())) as Box<dyn Iterator<Item = _>>
            } else if path.is_file() && path.file_name() == Some(OsStr::new("grammar.js")) {
                Box::new(std::iter::once(Ok(path))) as _
            } else {
                Box::new(std::iter::empty()) as _
            }
        })
}
