use crate::{bail_on_err, root_dir, FetchFixtures, EMSCRIPTEN_VERSION};
use anyhow::Result;
use std::{fs, process::Command};

pub fn run_fixtures(args: &FetchFixtures) -> Result<()> {
    let fixtures_dir = root_dir().join("test").join("fixtures");
    let grammars_dir = fixtures_dir.join("grammars");
    let fixtures_path = fixtures_dir.join("fixtures.json");

    // grammar name, tag
    let mut fixtures: Vec<(String, String)> =
        serde_json::from_str(&fs::read_to_string(&fixtures_path)?)?;

    for (grammar, tag) in &mut fixtures {
        let grammar_dir = grammars_dir.join(&grammar);
        let grammar_url = format!("https://github.com/tree-sitter/tree-sitter-{grammar}");

        println!("Fetching the {grammar} grammar...");

        if !grammar_dir.exists() {
            let mut command = Command::new("git");
            command.args([
                "clone",
                "--depth",
                "1",
                "--branch",
                tag,
                &grammar_url,
                &grammar_dir.to_string_lossy(),
            ]);
            bail_on_err(
                &command.spawn()?.wait_with_output()?,
                &format!("Failed to clone the {grammar} grammar"),
            )?;
        } else {
            let mut describe_command = Command::new("git");
            describe_command.current_dir(&grammar_dir).args([
                "describe",
                "--tags",
                "--exact-match",
                "HEAD",
            ]);

            let output = describe_command.output()?;
            let current_tag = String::from_utf8_lossy(&output.stdout);
            let current_tag = current_tag.trim();

            if current_tag != tag {
                println!("Updating {grammar} grammar from {current_tag} to {tag}...");

                let mut fetch_command = Command::new("git");
                fetch_command.current_dir(&grammar_dir).args([
                    "fetch",
                    "origin",
                    &format!("refs/tags/{tag}:refs/tags/{tag}"),
                ]);
                bail_on_err(
                    &fetch_command.spawn()?.wait_with_output()?,
                    &format!("Failed to fetch tag {tag} for {grammar} grammar"),
                )?;

                let mut reset_command = Command::new("git");
                reset_command
                    .current_dir(&grammar_dir)
                    .args(["reset", "--hard", "HEAD"]);
                bail_on_err(
                    &reset_command.spawn()?.wait_with_output()?,
                    &format!("Failed to reset {grammar} grammar working tree"),
                )?;

                let mut checkout_command = Command::new("git");
                checkout_command
                    .current_dir(&grammar_dir)
                    .args(["checkout", tag]);
                bail_on_err(
                    &checkout_command.spawn()?.wait_with_output()?,
                    &format!("Failed to checkout tag {tag} for {grammar} grammar"),
                )?;
            } else {
                println!("{grammar} grammar is already at tag {tag}");
            }
        }
    }

    if args.update {
        println!("Updating the fixtures lock file");
        fs::write(
            &fixtures_path,
            // format the JSON without extra newlines
            serde_json::to_string(&fixtures)?
                .replace("[[", "[\n  [")
                .replace("],", "],\n  ")
                .replace("]]", "]\n]"),
        )?;
    }

    Ok(())
}

pub fn run_emscripten() -> Result<()> {
    let emscripten_dir = root_dir().join("target").join("emsdk");
    if emscripten_dir.exists() {
        println!("Emscripten SDK already exists");
        return Ok(());
    }
    println!("Cloning the Emscripten SDK...");

    let mut command = Command::new("git");
    command.args([
        "clone",
        "https://github.com/emscripten-core/emsdk.git",
        &emscripten_dir.to_string_lossy(),
    ]);
    bail_on_err(
        &command.spawn()?.wait_with_output()?,
        "Failed to clone the Emscripten SDK",
    )?;

    std::env::set_current_dir(&emscripten_dir)?;

    let emsdk = if cfg!(windows) {
        "emsdk.bat"
    } else {
        "./emsdk"
    };

    let mut command = Command::new(emsdk);
    command.args(["install", EMSCRIPTEN_VERSION]);
    bail_on_err(
        &command.spawn()?.wait_with_output()?,
        "Failed to install Emscripten",
    )?;

    let mut command = Command::new(emsdk);
    command.args(["activate", EMSCRIPTEN_VERSION]);
    bail_on_err(
        &command.spawn()?.wait_with_output()?,
        "Failed to activate Emscripten",
    )
}
