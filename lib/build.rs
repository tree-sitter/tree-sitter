extern crate cc;

use std::env;
use std::path::PathBuf;

fn main() {
    let mut config = cc::Build::new();
    let src_path: PathBuf = ["src"].iter().collect();

    config
        .define("UTF8PROC_STATIC", "")
        .flag_if_supported("-std=c99")
        .flag_if_supported("-Wno-unused-parameter")
        .include("include")
        .include("utf8proc")
        .file(src_path.join("runtime.c"));

    if env::var("RUST_TREE_SITTER_TEST").is_ok() {
        let parser_dir: PathBuf = ["fixtures", "tree-sitter-rust", "src"].iter().collect();
        config
            .file(parser_dir.join("parser.c"))
            .file(parser_dir.join("scanner.c"));
    }

    config.compile("tree-sitter-runtime");
}
