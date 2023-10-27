use std::path::{Path, PathBuf};
use std::{env, fs};

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

    #[cfg(feature = "bindgen")]
    generate_bindings();

    let mut config = cc::Build::new();

    println!("cargo:rerun-if-env-changed=CARGO_FEATURE_WASM");
    if env::var("CARGO_FEATURE_WASM").is_ok() {
        config.define("TREE_SITTER_FEATURE_WASM", "");
    }

    let src_path = Path::new("src");
    for entry in fs::read_dir(&src_path).unwrap() {
        let entry = entry.unwrap();
        let path = src_path.join(entry.file_name());
        println!("cargo:rerun-if-changed={}", path.to_str().unwrap());
    }

    config
        .flag_if_supported("-std=c99")
        .flag_if_supported("-fvisibility=hidden")
        .flag_if_supported("-Wshadow")
        .flag_if_supported("-Wno-unused-parameter")
        .include(src_path)
        .include(src_path.join("wasm"))
        .include("include")
        .file(src_path.join("lib.c"))
        .compile("tree-sitter");
}

#[cfg(feature = "bindgen")]
fn generate_bindings() {
    const HEADER_PATH: &str = "include/tree_sitter/api.h";

    println!("cargo:rerun-if-changed={}", HEADER_PATH);

    let no_copy = [
        "TSInput",
        "TSLanguage",
        "TSLogger",
        "TSLookaheadIterator",
        "TSParser",
        "TSTree",
        "TSQuery",
        "TSQueryCursor",
        "TSQueryCapture",
        "TSQueryMatch",
        "TSQueryPredicateStep",
    ];

    let bindings = bindgen::Builder::default()
        .header(HEADER_PATH)
        .layout_tests(false)
        .allowlist_type("^TS.*")
        .allowlist_function("^ts_.*")
        .allowlist_var("^TREE_SITTER.*")
        .no_copy(no_copy.join("|"))
        .prepend_enum_name(false)
        .generate()
        .expect("Failed to generate bindings");

    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let bindings_rs = out_dir.join("bindings.rs");

    bindings.write_to_file(&bindings_rs).expect(&*format!(
        "Failed to write bindings into path: {bindings_rs:?}"
    ));
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
