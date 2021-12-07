use std::path::{Path, PathBuf};
use std::{env, fs};

#[cfg(feature = "generate-bindings")]
fn generate_bindings() {
    const HEADER_FILE: &'static str = "include/tree_sitter/api.h";

    println!("cargo:rerun-if-changed={}", HEADER_FILE);
    let bindings = bindgen::Builder::default()
        .header(HEADER_FILE)
        .layout_tests(false)
        .allowlist_type("^TS.*")
        .allowlist_function("^ts_.*")
        .allowlist_var("^TREE_SITTER.*")
        .blocklist_function("ts_tree_print_dot_graph")
        .opaque_type("FILE")
        .size_t_is_usize(true)
        .generate()
        .expect("Unable to generate bindings");

    let output = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(output.join("bindings.rs"))
        .expect("Unable to write bindings");
}

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

    #[cfg(feature = "generate-bindings")]
    generate_bindings();

    let src_path = Path::new("src");
    for entry in fs::read_dir(&src_path).unwrap() {
        let entry = entry.unwrap();
        let path = src_path.join(entry.file_name());
        println!("cargo:rerun-if-changed={}", path.to_str().unwrap());
    }

    cc::Build::new()
        .flag_if_supported("-std=c99")
        .flag_if_supported("-Wno-unused-parameter")
        .include(src_path)
        .include("include")
        .file(src_path.join("lib.c"))
        .compile("tree-sitter");
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
