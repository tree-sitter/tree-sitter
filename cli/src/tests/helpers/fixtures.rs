use anyhow::Context;
use lazy_static::lazy_static;
use std::path::{Path, PathBuf};
use std::{env, fs};
use tree_sitter::Language;
use tree_sitter_highlight::HighlightConfiguration;
use tree_sitter_loader::Loader;
use tree_sitter_tags::TagsConfiguration;

include!("./dirs.rs");

lazy_static! {
    static ref TEST_LOADER: Loader = {
        let mut loader = Loader::with_parser_lib_path(SCRATCH_DIR.clone());
        if env::var("TREE_SITTER_GRAMMAR_DEBUG").is_ok() {
            loader.use_debug_build(true);
        }
        loader
    };
}

pub fn test_loader() -> &'static Loader {
    &TEST_LOADER
}

pub fn fixtures_dir() -> &'static Path {
    &FIXTURES_DIR
}

pub fn scratch_dir() -> &'static Path {
    &SCRATCH_DIR
}

pub fn get_language(name: &str) -> Language {
    TEST_LOADER
        .load_language_at_path(
            &GRAMMARS_DIR.join(name).join("src"),
            &[&HEADER_DIR, &GRAMMARS_DIR.join(name).join("src")],
            None,
        )
        .unwrap()
}

pub fn get_language_queries_path(language_name: &str) -> PathBuf {
    GRAMMARS_DIR.join(language_name).join("queries")
}

pub fn get_highlight_config(
    language_name: &str,
    injection_query_filename: Option<&str>,
    highlight_names: &[String],
) -> HighlightConfiguration {
    let language = get_language(language_name);
    let queries_path = get_language_queries_path(language_name);
    let highlights_query = fs::read_to_string(queries_path.join("highlights.scm")).unwrap();
    let injections_query =
        injection_query_filename.map_or_else(String::new, |injection_query_filename| {
            fs::read_to_string(queries_path.join(injection_query_filename)).unwrap()
        });
    let locals_query = fs::read_to_string(queries_path.join("locals.scm")).unwrap_or_default();
    let mut result = HighlightConfiguration::new(
        language,
        language_name,
        &highlights_query,
        &injections_query,
        &locals_query,
    )
    .unwrap();
    result.configure(highlight_names);
    result
}

pub fn get_tags_config(language_name: &str) -> TagsConfiguration {
    let language = get_language(language_name);
    let queries_path = get_language_queries_path(language_name);
    let tags_query = fs::read_to_string(queries_path.join("tags.scm")).unwrap();
    let locals_query = fs::read_to_string(queries_path.join("locals.scm")).unwrap_or_default();
    TagsConfiguration::new(language, &tags_query, &locals_query).unwrap()
}

pub fn get_test_language(name: &str, parser_code: &str, path: Option<&Path>) -> Language {
    let src_dir = scratch_dir().join("src").join(name);
    fs::create_dir_all(&src_dir).unwrap();

    let parser_path = src_dir.join("parser.c");
    if !fs::read_to_string(&parser_path).map_or(false, |content| content == parser_code) {
        fs::write(&parser_path, parser_code).unwrap();
    }

    let scanner_path = if let Some(path) = path {
        let scanner_path = path.join("scanner.c");
        if scanner_path.exists() {
            let scanner_code = fs::read_to_string(&scanner_path).unwrap();
            let scanner_copy_path = src_dir.join("scanner.c");
            if !fs::read_to_string(&scanner_copy_path)
                .map_or(false, |content| content == scanner_code)
            {
                fs::write(&scanner_copy_path, scanner_code).unwrap();
            }
            Some(scanner_copy_path)
        } else {
            None
        }
    } else {
        None
    };

    let header_path = src_dir.join("tree_sitter");
    fs::create_dir_all(&header_path).unwrap();

    fs::write(header_path.join("alloc.h"), tree_sitter::PARSER_HEADER)
        .with_context(|| {
            format!(
                "Failed to write {:?}",
                header_path.join("alloc.h").file_name().unwrap()
            )
        })
        .unwrap();

    fs::write(header_path.join("array.h"), tree_sitter::PARSER_HEADER)
        .with_context(|| {
            format!(
                "Failed to write {:?}",
                header_path.join("array.h").file_name().unwrap()
            )
        })
        .unwrap();

    fs::write(header_path.join("parser.h"), tree_sitter::PARSER_HEADER)
        .with_context(|| {
            format!(
                "Failed to write {:?}",
                header_path.join("parser.h").file_name().unwrap()
            )
        })
        .unwrap();

    let paths_to_check = if let Some(scanner_path) = &scanner_path {
        vec![parser_path, scanner_path.clone()]
    } else {
        vec![parser_path]
    };

    TEST_LOADER
        .load_language_at_path_with_name(&src_dir, &[&HEADER_DIR], name, Some(&paths_to_check))
        .unwrap()
}
