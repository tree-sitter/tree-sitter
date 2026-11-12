use std::{env, path::Path, process::Command};

fn main() {
    println!("cargo:rerun-if-changed=.");

    let package = env::var("CARGO_PKG_VERSION").expect("Cargo sets CARGO_PKG_VERSION");
    let version = match read_git_sha() {
        Some(sha) => format!("{package} ({sha})"),
        None => package,
    };
    println!("cargo:rustc-env=TREE_SITTER_VERSION={version}");

    println!("cargo:rustc-check-cfg=cfg(sanitizing)");
    println!("cargo:rustc-check-cfg=cfg(TREE_SITTER_EMBED_WASM_BINDING)");

    if web_playground_files_present() {
        println!("cargo:rustc-cfg=TREE_SITTER_EMBED_WASM_BINDING");
    }

    #[cfg(any(
        target_os = "linux",
        target_os = "android",
        target_os = "freebsd",
        target_os = "openbsd",
        target_os = "netbsd",
        target_os = "dragonfly",
    ))]
    {
        let out_dir =
            std::path::PathBuf::from(env::var("OUT_DIR").unwrap()).join("dynamic-symbols.txt");
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
        "../../docs/src/assets/js/playground.js",
        "../../lib/binding_web/web-tree-sitter.js",
        "../../lib/binding_web/web-tree-sitter.wasm",
    ];

    paths.iter().all(|p| Path::new(p).exists())
}

fn read_git_sha() -> Option<String> {
    let sha = git(&["rev-parse", "HEAD"])?;

    // Resolve paths through Git so this also works in linked worktrees.
    for name in ["HEAD", "refs/heads", "packed-refs", "reftable/tables.list"] {
        let Some(path) = git(&["rev-parse", "--git-path", name]) else {
            continue;
        };
        if Path::new(&path).exists() {
            println!("cargo:rerun-if-changed={path}");
        }
    }

    Some(sha)
}

fn git(args: &[&str]) -> Option<String> {
    let output = Command::new("git").args(args).output().ok()?;
    if !output.status.success() {
        return None;
    }
    let text = String::from_utf8(output.stdout).ok()?.trim().to_string();
    (!text.is_empty()).then_some(text)
}
