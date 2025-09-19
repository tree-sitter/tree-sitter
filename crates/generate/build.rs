use std::{env, fs, path::PathBuf};

fn main() {
    // This will always be ran in CI before publishing.
    // We don't use a symlink for windows compatibility.
    let out_dir = PathBuf::from(env::var("OUT_DIR").expect("OUT_DIR should be set"));
    let parser_h = out_dir.join("parser.h");

    if let Ok(workspace_dir) = find_workspace_root() {
        let source_path = workspace_dir.join("lib/src/parser.h");
        if source_path.exists() {
            fs::copy(&source_path, &parser_h).expect("failed to copy parser.h template");
            return;
        }
    }

    // If we can't find parser.h in the workspace (e.g., when published to crates.io),
    // the file should already be included in the package.
    let manifest_dir =
        PathBuf::from(env::var("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR should be set"));
    let local_parser_h = manifest_dir.join("src/templates/parser.h");

    if local_parser_h.exists() {
        fs::copy(&local_parser_h, &parser_h).expect("failed to copy local parser.h template");
    } else {
        panic!("parser.h not found in workspace or crate package. This crate may not be properly packaged.");
    }
}

fn find_workspace_root() -> Result<PathBuf, String> {
    if let Ok(workspace_dir) = env::var("CARGO_WORKSPACE_DIR") {
        if !workspace_dir.is_empty() {
            return Ok(PathBuf::from(workspace_dir));
        }
    }

    let manifest_dir =
        PathBuf::from(env::var("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR should be set"));
    let mut current = manifest_dir.as_path();

    loop {
        if current.join("Cargo.toml").exists() {
            if let Ok(cargo_toml) = fs::read_to_string(current.join("Cargo.toml")) {
                if cargo_toml.contains("[workspace]") {
                    return Ok(current.to_path_buf());
                }
            }
        }

        if let Some(parent) = current.parent() {
            current = parent;
        } else {
            return Err(format!(
                "Could not find workspace root from {}",
                manifest_dir.display()
            ));
        }
    }
}
