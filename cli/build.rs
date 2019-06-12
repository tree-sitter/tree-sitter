use std::path::PathBuf;
use std::{env, fs};

fn main() {
    if let Some(git_sha) = read_git_sha() {
        println!("cargo:rustc-env={}={}", "BUILD_SHA", git_sha);
    }

    println!(
        "cargo:rustc-env=BUILD_TARGET={}",
        std::env::var("TARGET").unwrap()
    );
}

fn read_git_sha() -> Option<String> {
    let mut repo_path = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());

    let mut git_path;
    loop {
        git_path = repo_path.join(".git");
        if git_path.exists() {
            break;
        } else if !repo_path.pop() {
            return None;
        }
    }

    let git_head_path = git_path.join("HEAD");
    if let Some(path) = git_head_path.to_str() {
        println!("cargo:rerun-if-changed={}", path);
    }
    if let Ok(mut head_content) = fs::read_to_string(&git_head_path) {
        if head_content.ends_with("\n") {
            head_content.pop();
        }

        // If we're on a branch, read the SHA from the ref file.
        if head_content.starts_with("ref: ") {
            head_content.replace_range(0.."ref: ".len(), "");
            let ref_filename = git_path.join(&head_content);
            if let Some(path) = ref_filename.to_str() {
                println!("cargo:rerun-if-changed={}", path);
            }
            return fs::read_to_string(&ref_filename).ok();
        }

        // If we're on a detached commit, then the `HEAD` file itself contains the sha.
        else if head_content.len() == 40 {
            return Some(head_content);
        }
    }

    None
}
