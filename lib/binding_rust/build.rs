use std::{env, fs};
use std::path::{Path, PathBuf};
use std::process::Command;

fn main() {
    println!("cargo:rerun-if-env-changed=TREE_SITTER_STATIC_ANALYSIS");
    if env::var("TREE_SITTER_STATIC_ANALYSIS").is_ok() {
        if let (Some(clang_path), Some(scan_build_path)) = (which("clang"), which("scan-build")) {
            let clang_path = clang_path.to_str().unwrap();
            let scan_build_path = scan_build_path.to_str().unwrap();
            env::set_var(
                "CC",
                &format!(
                    "{} -analyze-headers --use-analyzer={} cc",
                    scan_build_path, clang_path
                ),
            );
        }
    }

    let mut c_args = "-Wno-unused-parameter".to_string();

    println!("cargo:rerun-if-env-changed=TREE_SITTER_TEST");
    if env::var("TREE_SITTER_TEST").is_ok() {
        c_args.push_str("-DTREE_SITTER_TEST");
    }

    let src_path = Path::new("src");

    for entry in fs::read_dir(&src_path).unwrap() {
        let entry = entry.unwrap();
        let path = src_path.join(entry.file_name());
        println!("cargo:rerun-if-changed={}", path.to_str().unwrap());
    }

    let ts_path = Path::new("..");
    let build_path = ts_path.join("build").join("rust");

    fs::create_dir_all(&build_path).unwrap();
    Command::new("meson")
        .arg(ts_path.to_str().unwrap())
        .arg(build_path.to_str().unwrap())
        .arg("--buildtype=release")
        .arg("-Ddefault_library=static")
        .arg(&format!("-Dc_args=\"{}\"", c_args))
        .status()
        .expect("failed to run meson");
    Command::new("meson")
        .arg("configure")
        .arg(build_path.to_str().unwrap())
        .arg("-Dlib_binding=rust")
        .status()
        .expect("failed to run meson configure");
    Command::new("ninja")
        .arg("-C")
        .arg(build_path.to_str().unwrap())
        .status()
        .expect("failed to run ninja");

    println!("cargo:rustc-link-search=native={}", build_path.join("lib")
             .canonicalize().unwrap().to_str().unwrap());
    println!("cargo:rustc-link-lib=static=tree-sitter");
}

fn which(exe_name: impl AsRef<Path>) -> Option<PathBuf> {
    env::var_os("PATH").and_then(|paths| {
        env::split_paths(&paths).find_map(|dir| {
            let full_path = dir.join(&exe_name);
            if full_path.is_file() {
                Some(full_path)
            } else {
                None
            }
        })
    })
}
