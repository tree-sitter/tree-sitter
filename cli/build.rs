use std::{
    env,
    ffi::OsStr,
    fs,
    path::{Path, PathBuf},
    time::SystemTime,
};

fn main() {
    if let Some(git_sha) = read_git_sha() {
        println!("cargo:rustc-env=BUILD_SHA={git_sha}");
    }

    println!("cargo:rustc-check-cfg=cfg(sanitizing)");
    println!("cargo:rustc-check-cfg=cfg(TREE_SITTER_EMBED_WASM_BINDING)");

    if web_playground_files_present() {
        println!("cargo:rustc-cfg=TREE_SITTER_EMBED_WASM_BINDING");
    }

    let build_time = SystemTime::now()
        .duration_since(SystemTime::UNIX_EPOCH)
        .unwrap()
        .as_secs_f64();
    println!("cargo:rustc-env=BUILD_TIME={build_time}");

    #[cfg(any(
        target_os = "linux",
        target_os = "android",
        target_os = "freebsd",
        target_os = "openbsd",
        target_os = "netbsd",
        target_os = "dragonfly",
    ))]
    {
        let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap()).join("dynamic-symbols.txt");
        std::fs::write(
            &out_dir,
            "{
                ts_current_malloc;
                ts_current_calloc;
                ts_current_realloc;
                ts_current_free;
            };",
        )
        .unwrap();
        println!(
            "cargo:rustc-link-arg=-Wl,--dynamic-list={}",
            out_dir.display()
        );
    }
}

fn web_playground_files_present() -> bool {
    let paths = [
        "../docs/assets/js/playground.js",
        "../lib/binding_web/tree-sitter.js",
        "../lib/binding_web/tree-sitter.wasm",
    ];

    paths.iter().all(|p| Path::new(p).exists())
}

fn read_git_sha() -> Option<String> {
    let mut repo_path = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());

    let mut git_path;
    loop {
        git_path = repo_path.join(".git");
        if git_path.exists() {
            break;
        }
        if !repo_path.pop() {
            return None;
        }
    }

    let git_dir_path;
    if git_path.is_dir() {
        git_dir_path = git_path;
    } else if let Ok(git_path_content) = fs::read_to_string(&git_path) {
        git_dir_path = repo_path.join(git_path_content.get("gitdir: ".len()..).unwrap().trim_end());
    } else {
        return None;
    }
    let git_head_path = git_dir_path.join("HEAD");
    if let Some(path) = git_head_path.to_str() {
        println!("cargo:rerun-if-changed={path}");
    }
    if let Ok(mut head_content) = fs::read_to_string(&git_head_path) {
        if head_content.ends_with('\n') {
            head_content.pop();
        }

        // If we're on a branch, read the SHA from the ref file.
        if head_content.starts_with("ref: ") {
            head_content.replace_range(0.."ref: ".len(), "");
            let ref_filename = {
                // Go to real non-worktree gitdir
                let git_dir_path = git_dir_path
                    .parent()
                    .and_then(|p| {
                        p.file_name()
                            .map(|n| n == OsStr::new("worktrees"))
                            .and_then(|x| x.then(|| p.parent()))
                    })
                    .flatten()
                    .unwrap_or(&git_dir_path);

                let file = git_dir_path.join(&head_content);
                if file.is_file() {
                    file
                } else {
                    let packed_refs = git_dir_path.join("packed-refs");
                    if let Ok(packed_refs_content) = fs::read_to_string(&packed_refs) {
                        for line in packed_refs_content.lines() {
                            if let Some((hash, r#ref)) = line.split_once(' ') {
                                if r#ref == head_content {
                                    if let Some(path) = packed_refs.to_str() {
                                        println!("cargo:rerun-if-changed={path}");
                                    }
                                    return Some(hash.to_string());
                                }
                            }
                        }
                    }
                    return None;
                }
            };
            if let Some(path) = ref_filename.to_str() {
                println!("cargo:rerun-if-changed={path}");
            }
            return fs::read_to_string(&ref_filename).ok();
        }
        // If we're on a detached commit, then the `HEAD` file itself contains the sha.
        if head_content.len() == 40 {
            return Some(head_content);
        }
    }

    None
}
