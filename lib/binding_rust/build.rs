use std::{
    env, fs,
    path::{Path, PathBuf},
};

fn main() {
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());

    #[cfg(feature = "bindgen")]
    generate_bindings(&out_dir);

    fs::copy(
        "src/wasm/stdlib-symbols.txt",
        out_dir.join("stdlib-symbols.txt"),
    )
    .unwrap();

    let mut config = cc::Build::new();

    println!("cargo:rerun-if-env-changed=CARGO_FEATURE_WASM");
    if env::var("CARGO_FEATURE_WASM").is_ok() {
        config
            .define("TREE_SITTER_FEATURE_WASM", "")
            .define("static_assert(...)", "")
            .include(env::var("DEP_WASMTIME_C_API_INCLUDE").unwrap())
            .include(env::var("DEP_WASMTIME_C_API_WASM_INCLUDE").unwrap());
    }

    let manifest_path = Path::new(env!("CARGO_MANIFEST_DIR"));
    let include_path = manifest_path.join("include");
    let src_path = manifest_path.join("src");
    let wasm_path = src_path.join("wasm");
    for entry in fs::read_dir(&src_path).unwrap() {
        let entry = entry.unwrap();
        let path = src_path.join(entry.file_name());
        println!("cargo:rerun-if-changed={}", path.to_str().unwrap());
    }

    config
        .flag_if_supported("-std=c11")
        .flag_if_supported("-fvisibility=hidden")
        .flag_if_supported("-Wshadow")
        .flag_if_supported("-Wno-unused-parameter")
        .include(&src_path)
        .include(&wasm_path)
        .include(&include_path)
        .file(src_path.join("lib.c"))
        .compile("tree-sitter");

    println!("cargo:include={}", include_path.display());
}

#[cfg(feature = "bindgen")]
fn generate_bindings(out_dir: &Path) {
    const HEADER_PATH: &str = "include/tree_sitter/api.h";

    println!("cargo:rerun-if-changed={HEADER_PATH}");

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

    let bindings_rs = out_dir.join("bindings.rs");
    bindings
        .write_to_file(&bindings_rs)
        .unwrap_or_else(|_| panic!("Failed to write bindings into path: {bindings_rs:?}"));
}
