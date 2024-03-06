use std::path::Path;

use anyhow::Result;

pub fn fetch() -> Result<()> {
    let grammars_dir = Path::new(env!("CARGO_MANIFEST_DIR"))
        .parent()
        .unwrap()
        .join("test")
        .join("fixtures")
        .join("grammars");

    [
        ("bash", "master"),
        ("c", "master"),
        ("cpp", "master"),
        ("embedded-template", "master"),
        ("go", "master"),
        ("html", "master"),
        ("java", "master"),
        ("javascript", "master"),
        ("jsdoc", "master"),
        ("json", "master"),
        ("php", "master"),
        ("python", "master"),
        ("ruby", "master"),
        ("rust", "master"),
        ("typescript", "master"),
    ]
    .iter()
    .try_for_each(|(grammar, r#ref)| {
        let grammar_dir = grammars_dir.join(grammar);
        let grammar_url = format!("https://github.com/tree-sitter/tree-sitter-{grammar}");

        println!("Updating the {grammar} grammar...");

        if !grammar_dir.exists() {
            let mut command = std::process::Command::new("git");
            command
                .args([
                    "clone",
                    "--depth",
                    "1",
                    &grammar_url,
                    &grammar_dir.to_string_lossy(),
                ])
                .stdout(std::process::Stdio::null())
                .stderr(std::process::Stdio::null());
            let output = command.spawn()?.wait_with_output()?;
            if !output.status.success() {
                let stderr = String::from_utf8_lossy(&output.stderr);
                anyhow::bail!("Failed to clone the {grammar} grammar\n{stderr}");
            }
        }

        std::env::set_current_dir(&grammar_dir)?;

        let mut command = std::process::Command::new("git");
        command
            .args(["fetch", "origin", r#ref, "--depth", "1"])
            .stdout(std::process::Stdio::null())
            .stderr(std::process::Stdio::null());
        let output = command.spawn()?.wait_with_output()?;

        if !output.status.success() {
            let stderr = String::from_utf8_lossy(&output.stderr);
            anyhow::bail!("Failed to fetch the {grammar} grammar\n{stderr}");
        }

        let mut command = std::process::Command::new("git");
        command
            .args(["reset", "--hard", "FETCH_HEAD"])
            .stdout(std::process::Stdio::null())
            .stderr(std::process::Stdio::null());
        let output = command.spawn()?.wait_with_output()?;

        if !output.status.success() {
            let stderr = String::from_utf8_lossy(&output.stderr);
            anyhow::bail!("Failed to reset the {grammar} grammar\n{stderr}");
        }

        Ok(())
    })
}
