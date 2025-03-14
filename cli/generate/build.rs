use std::{env, fs, path::PathBuf, process::Command};

fn main() {
    // This will always be ran in CI before publishing.
    // We don't use a symlink for windows compatibility.
    fs::copy(
        concat!(env!("CARGO_WORKSPACE_DIR"), "lib/src/parser.h"),
        PathBuf::from(env::var("OUT_DIR").unwrap_or_default()).join("parser.h"),
    )
    .expect("failed to copy parser.h template");

    if let Some(git_sha) = read_git_sha() {
        println!("cargo:rustc-env=BUILD_SHA={git_sha}");
    }
}

// This is copied from the build.rs in parent directory. This should be updated if the
// parent build.rs gets fixes.
fn read_git_sha() -> Option<String> {
    let crate_path = PathBuf::from(env!("CARGO_WORKSPACE_DIR"));

    if !crate_path.join(".git").exists() {
        return None;
    }

    Command::new("git")
        .args(["rev-parse", "HEAD"])
        .current_dir(crate_path)
        .output()
        .map_or(None, |output| {
            if !output.status.success() {
                return None;
            }
            Some(String::from_utf8_lossy(&output.stdout).to_string())
        })
}
