use std::{env, path::PathBuf, process::Command};

fn main() {
    if let Some(git_sha) = read_git_sha() {
        println!("cargo:rustc-env=BUILD_SHA={git_sha}");
    }
}

// This is copied from the build.rs in parent directory. This should be updated if the
// parent build.rs gets fixes.
fn read_git_sha() -> Option<String> {
    let crate_path = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());

    if !crate_path
        .parent()?
        .parent()
        .is_some_and(|p| p.join(".git").exists())
    {
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
