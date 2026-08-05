fn main() {
    let src_dir = std::path::Path::new("src");

    let mut c_config = cc::Build::new();
    c_config.std("c11").include(src_dir);

    #[cfg(target_env = "msvc")]
    c_config.flag("-utf-8");

    if std::env::var("TARGET").unwrap() == "wasm32-unknown-unknown" {
        let Ok(wasm_headers) = std::env::var("DEP_TREE_SITTER_LANGUAGE_WASM_HEADERS") else {
            panic!("Environment variable DEP_TREE_SITTER_LANGUAGE_WASM_HEADERS must be set by the language crate");
        };
        let Ok(wasm_src) =
            std::env::var("DEP_TREE_SITTER_LANGUAGE_WASM_SRC").map(std::path::PathBuf::from)
        else {
            panic!("Environment variable DEP_TREE_SITTER_LANGUAGE_WASM_SRC must be set by the language crate");
        };

        c_config.include(&wasm_headers);
        c_config.files([
            wasm_src.join("stdio.c"),
            wasm_src.join("stdlib.c"),
            wasm_src.join("string.c"),
        ]);
    }

    let parser_path = src_dir.join("parser.c");
    c_config.file(&parser_path);
    println!("cargo:rerun-if-changed={}", parser_path.to_str().unwrap());

    let scanner_path = src_dir.join("scanner.c");
    if scanner_path.exists() {
        c_config.file(&scanner_path);
        println!("cargo:rerun-if-changed={}", scanner_path.to_str().unwrap());
    }

    c_config.compile("tree-sitter-KEBAB_PARSER_NAME");

    println!("cargo:rustc-check-cfg=cfg(with_highlights_query)");
    if !"HIGHLIGHTS_QUERY_PATH".is_empty() && std::path::Path::new("HIGHLIGHTS_QUERY_PATH").exists() {
        println!("cargo:rustc-cfg=with_highlights_query");
    }
    println!("cargo:rustc-check-cfg=cfg(with_injections_query)");
    if !"INJECTIONS_QUERY_PATH".is_empty() && std::path::Path::new("INJECTIONS_QUERY_PATH").exists() {
        println!("cargo:rustc-cfg=with_injections_query");
    }
    println!("cargo:rustc-check-cfg=cfg(with_locals_query)");
    if !"LOCALS_QUERY_PATH".is_empty() && std::path::Path::new("LOCALS_QUERY_PATH").exists() {
        println!("cargo:rustc-cfg=with_locals_query");
    }
    println!("cargo:rustc-check-cfg=cfg(with_tags_query)");
    if !"TAGS_QUERY_PATH".is_empty() && std::path::Path::new("TAGS_QUERY_PATH").exists() {
        println!("cargo:rustc-cfg=with_tags_query");
    }
}
