extern crate cc;

use std::env;
use std::path::{Path, PathBuf};
use std::fs;

fn main() {
    let mut config = cc::Build::new();
    config
        .define("UTF8PROC_STATIC", "")
        .flag_if_supported("-std=c99")
        .flag_if_supported("-Wno-unused-parameter")
        .include("include")
        .include("utf8proc")
        .file(Path::new("src").join("lib.c"))
        .compile("tree-sitter");

    if env::var("TREE_SITTER_TEST").is_ok() {
        let mut parser_config = cc::Build::new();
        parser_config
            .opt_level(0)
            .flag_if_supported("-Wno-unused-parameter");

        let mut scanner_c_config = cc::Build::new();
        scanner_c_config
            .flag_if_supported("-std=c99")
            .flag_if_supported("-Wno-unused-parameter");

        let mut scanner_cxx_config = cc::Build::new();
        scanner_cxx_config
            .cpp(true)
            .flag_if_supported("-Wno-unused-parameter");

        let grammars_dir: PathBuf = ["..", "test", "fixtures", "grammars"].iter().collect();
        for entry in fs::read_dir(&grammars_dir).expect("Failed to list grammar directory") {
            let entry = entry.expect("Failed to load grammars directory entry");
            if !entry.path().is_dir() {
                continue;
            }
            let parser_dir_path = entry.path();
            let parser_src_path = parser_dir_path.join("src");
            let parser_c_path = parser_src_path.join("parser.c");
            let scanner_c_path = parser_src_path.join("scanner.c");
            let scanner_cc_path = parser_src_path.join("scanner.cc");

            println!("cargo:rerun-if-changed={}", parser_c_path.to_str().unwrap());
            parser_config
                .include(&parser_src_path)
                .opt_level(0)
                .file(&parser_c_path);
            if scanner_cc_path.exists() {
                println!("cargo:rerun-if-changed={}", scanner_cc_path.to_str().unwrap());
                scanner_cxx_config
                    .include(&parser_src_path)
                    .file(&scanner_cc_path);
            } else if scanner_c_path.exists() {
                println!("cargo:rerun-if-changed={}", scanner_c_path.to_str().unwrap());
                scanner_c_config
                    .include(&parser_src_path)
                    .file(&scanner_c_path);
            }
        }

        parser_config.compile("fixture-parsers");
        scanner_c_config.compile("fixture-scanners-c");
        scanner_cxx_config.compile("fixture-scanners-cxx");
    }
}
