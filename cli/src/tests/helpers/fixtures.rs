use crate::loader::Loader;
use lazy_static::lazy_static;
use std::fs;
use std::path::{Path, PathBuf};
use tree_sitter::Language;
use tree_sitter_highlight::{HighlightConfiguration, Highlighter};

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

pub fn get_highlight_query_sources(language_name: &str) -> (String, String, String) {
    let queries_path = GRAMMARS_DIR.join(language_name).join("queries");
    let highlights_path = queries_path.join("highlights.scm");
    let injections_path = queries_path.join("injections.scm");
    let locals_path = queries_path.join("locals.scm");

    let highlights_query = fs::read_to_string(highlights_path).unwrap();
    let injections_query = if injections_path.exists() {
        fs::read_to_string(injections_path).unwrap()
    } else {
        String::new()
    };
    let locals_query = if locals_path.exists() {
        fs::read_to_string(locals_path).unwrap()
    } else {
        String::new()
    };

    (highlights_query, injections_query, locals_query)
}

pub fn get_highlight_config(
    language_name: &str,
    highlighter: &Highlighter,
) -> HighlightConfiguration {
    let language = get_language(language_name);
    let (highlights_query, injections_query, locals_query) =
        get_highlight_query_sources(language_name);
    highlighter
        .load_configuration(
            language,
            &highlights_query,
            &injections_query,
            &locals_query,
        )
        .unwrap()
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
