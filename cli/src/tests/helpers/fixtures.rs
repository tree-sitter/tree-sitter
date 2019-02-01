use crate::loader::Loader;
use lazy_static::lazy_static;
use std::fs;
use std::path::{Path, PathBuf};
use tree_sitter::Language;

include!("./dirs.rs");

lazy_static! {
    static ref TEST_LOADER: Loader = Loader::new(SCRATCH_DIR.clone());
}

pub fn fixtures_dir<'a>() -> &'static Path {
    &FIXTURES_DIR
}

pub fn get_language(name: &str) -> Language {
    TEST_LOADER
        .load_language_at_path(name, &GRAMMARS_DIR.join(name).join("src"), &HEADER_DIR)
        .unwrap()
}

pub fn get_test_language(name: &str, parser_code: String, path: &Path) -> Language {
    let parser_c_path = SCRATCH_DIR.join(&format!("{}-parser.c", name));
    if !fs::read_to_string(&parser_c_path)
        .map(|content| content == parser_code)
        .unwrap_or(false)
    {
        fs::write(&parser_c_path, parser_code).unwrap();
    }
    let scanner_path = path.join("scanner.c");
    let scanner_path = if scanner_path.exists() {
        Some(scanner_path)
    } else {
        None
    };
    TEST_LOADER
        .load_language_from_sources(name, &HEADER_DIR, &parser_c_path, &scanner_path)
        .unwrap()
}
