use crate::{bail_on_err, root_dir, EMSCRIPTEN_VERSION};
use anyhow::Result;
use std::{fs, path::Path, process::Command};

enum FixtureRef<'a> {
    Tag(&'a str),
    Branch(&'a str),
}

impl<'a> FixtureRef<'a> {
    #[allow(clippy::use_self)]
    const fn new(tag: &'a str, branch: Option<&'a str>) -> FixtureRef<'a> {
        if let Some(b) = branch {
            Self::Branch(b)
        } else {
            Self::Tag(tag)
        }
    }

    const fn ref_type(&self) -> &'static str {
        match self {
            FixtureRef::Tag(_) => "tag",
            FixtureRef::Branch(_) => "branch",
        }
    }
}

impl std::fmt::Display for FixtureRef<'_> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            FixtureRef::Tag(tag) => write!(f, "{tag}"),
            FixtureRef::Branch(branch) => write!(f, "{branch}"),
        }
    }
}

fn current_ref_name(grammar_dir: &Path) -> Result<(String, Option<&'static str>)> {
    let tag_args = ["describe", "--tags", "--exact-match", "HEAD"];
    let branch_args = ["rev-parse", "--abbrev-ref", "HEAD"];

    for (args, ref_type) in [tag_args.as_ref(), branch_args.as_ref()]
        .iter()
        .zip(&["tag", "branch"])
    {
        let name_cmd = Command::new("git")
            .current_dir(grammar_dir)
            .args(*args)
            .output()?;
        let name = String::from_utf8_lossy(&name_cmd.stdout);
        let name = name.trim();
        if !name.is_empty() {
            return Ok((name.to_string(), Some(ref_type)));
        }
    }

    Ok(("<unknown>".to_string(), None))
}

pub fn run_fixtures() -> Result<()> {
    let fixtures_dir = root_dir().join("test").join("fixtures");
    let grammars_dir = fixtures_dir.join("grammars");
    let fixtures_path = fixtures_dir.join("fixtures.json");

    // grammar name, tag, [branch]
    let fixtures: Vec<(String, String, Option<String>)> =
        serde_json::from_str(&fs::read_to_string(&fixtures_path)?)?;

    for (grammar, tag, branch) in &fixtures {
        let grammar_dir = grammars_dir.join(grammar);
        let grammar_url = format!("https://github.com/tree-sitter/tree-sitter-{grammar}");
        let target_ref = FixtureRef::new(tag, branch.as_deref());

        println!("Fetching the {grammar} grammar...");

        if !grammar_dir.exists() {
            let mut command = Command::new("git");
            command.args([
                "clone",
                "--depth",
                "1",
                "--branch",
                &target_ref.to_string(),
                &grammar_url,
                &grammar_dir.to_string_lossy(),
            ]);
            bail_on_err(
                &command.spawn()?.wait_with_output()?,
                &format!("Failed to clone the {grammar} grammar"),
            )?;
        } else {
            let (current_ref, current_ref_type) = current_ref_name(&grammar_dir)?;
            if current_ref != target_ref.to_string() {
                println!(
                    "Updating {grammar} grammar from {} {current_ref} to {} {target_ref}...",
                    current_ref_type.unwrap_or("<unknown>"),
                    target_ref.ref_type(),
                );

                match target_ref {
                    FixtureRef::Branch(branch) => {
                        let mut fetch_cmd = Command::new("git");
                        fetch_cmd.current_dir(&grammar_dir).args([
                            "fetch",
                            "--update-shallow",
                            "origin",
                            &format!("+refs/heads/{branch}:refs/remotes/origin/{branch}"),
                        ]);
                        bail_on_err(
                            &fetch_cmd.spawn()?.wait_with_output()?,
                            &format!("Failed to fetch branch {branch}"),
                        )?;
                        let mut switch_cmd = Command::new("git");
                        switch_cmd
                            .current_dir(&grammar_dir)
                            .args(["switch", branch]);
                        bail_on_err(
                            &switch_cmd.spawn()?.wait_with_output()?,
                            &format!("Failed to checkout branch {branch}"),
                        )?;
                        let mut set_upstream_cmd = Command::new("git");
                        set_upstream_cmd.current_dir(&grammar_dir).args([
                            "branch",
                            "--set-upstream-to",
                            &format!("origin/{branch}"),
                            branch,
                        ]);
                        bail_on_err(
                            &set_upstream_cmd.spawn()?.wait_with_output()?,
                            &format!("Failed to set upstream for branch {branch}"),
                        )?;
                        let mut pull_cmd = Command::new("git");
                        pull_cmd
                            .current_dir(&grammar_dir)
                            .args(["pull", "origin", branch]);
                        bail_on_err(
                            &pull_cmd.spawn()?.wait_with_output()?,
                            &format!("Failed to pull latest from branch {branch}"),
                        )?;
                    }
                    FixtureRef::Tag(tag) => {
                        let mut fetch_command = Command::new("git");
                        fetch_command.current_dir(&grammar_dir).args([
                            "fetch",
                            "origin",
                            &format!("refs/tags/{tag}:refs/tags/{tag}"),
                        ]);
                        bail_on_err(
                            &fetch_command.spawn()?.wait_with_output()?,
                            &format!(
                                "Failed to fetch {} {target_ref} for {grammar} grammar",
                                target_ref.ref_type()
                            ),
                        )?;
                    }
                }

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
                    .args(["checkout", &target_ref.to_string()]);
                bail_on_err(
                    &checkout_command.spawn()?.wait_with_output()?,
                    &format!(
                        "Failed to checkout {} {target_ref} for {grammar} grammar",
                        target_ref.ref_type()
                    ),
                )?;
            } else {
                println!(
                    "{grammar} grammar is already at {} {target_ref}",
                    target_ref.ref_type()
                );
            }
        }
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
