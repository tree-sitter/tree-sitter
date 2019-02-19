use crate::loader::Loader;
use lazy_static::lazy_static;
use std::fs;
use std::path::{Path, PathBuf};
use tree_sitter::{Language, PropertySheet};
use tree_sitter_highlight::{load_property_sheet, Properties};

include!("./dirs.rs");

lazy_static! {
    static ref TEST_LOADER: Loader = Loader::new(SCRATCH_DIR.clone());
}

pub fn fixtures_dir<'a>() -> &'static Path {
    &FIXTURES_DIR
}

pub fn get_language(name: &str) -> Language {
    TEST_LOADER
        .load_language_at_path(&GRAMMARS_DIR.join(name).join("src"), &HEADER_DIR)
        .unwrap()
}

pub fn get_property_sheet(language_name: &str, sheet_name: &str) -> PropertySheet<Properties> {
    let path = GRAMMARS_DIR
        .join(language_name)
        .join("src")
        .join(sheet_name);
    let json = fs::read_to_string(path).unwrap();
    let language = get_language(language_name);
    load_property_sheet(language, &json).unwrap()
}

pub fn get_test_language(name: &str, parser_code: &str, path: Option<&Path>) -> Language {
    let parser_c_path = SCRATCH_DIR.join(&format!("{}-parser.c", name));
    if !fs::read_to_string(&parser_c_path)
        .map(|content| content == parser_code)
        .unwrap_or(false)
    {
        fs::write(&parser_c_path, parser_code).unwrap();
    }
    let scanner_path = path.and_then(|p| {
        let result = p.join("scanner.c");
        if result.exists() {
            Some(result)
        } else {
            None
        }
    });
    TEST_LOADER
        .load_language_from_sources(name, &HEADER_DIR, &parser_c_path, &scanner_path)
        .unwrap()
}
