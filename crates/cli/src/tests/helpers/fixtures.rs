use std::{
    env, fs,
    path::{Path, PathBuf},
    sync::LazyLock,
};

use anyhow::Context;
use tree_sitter::Language;
use tree_sitter_generate::{load_grammar_file, ALLOC_HEADER, ARRAY_HEADER};
use tree_sitter_highlight::HighlightConfiguration;
use tree_sitter_loader::{CompileConfig, Loader};
use tree_sitter_tags::TagsConfiguration;

use crate::tests::generate_parser;

include!("./dirs.rs");

static TEST_LOADER: LazyLock<Loader> = LazyLock::new(|| {
    let mut loader = Loader::with_parser_lib_path(SCRATCH_DIR.clone());
    if env::var("TREE_SITTER_GRAMMAR_DEBUG").is_ok() {
        loader.debug_build(true);
    }
    loader
});

#[cfg(feature = "wasm")]
pub static ENGINE: LazyLock<tree_sitter::wasmtime::Engine> = LazyLock::new(Default::default);

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
    let src_dir = GRAMMARS_DIR.join(name).join("src");
    let mut config = CompileConfig::new(&src_dir, None, None);
    config.header_paths.push(&HEADER_DIR);
    TEST_LOADER.load_language_at_path(config).unwrap()
}

pub fn get_test_fixture_language(name: &str) -> Language {
    get_test_fixture_language_internal(name, false)
}

#[cfg(feature = "wasm")]
pub fn get_test_fixture_language_wasm(name: &str) -> Language {
    get_test_fixture_language_internal(name, true)
}

fn get_test_fixture_language_internal(name: &str, wasm: bool) -> Language {
    let grammar_dir_path = fixtures_dir().join("test_grammars").join(name);
    let grammar_json = load_grammar_file(&grammar_dir_path.join("grammar.js"), None).unwrap();
    let (parser_name, parser_code, header_code) = generate_parser(&grammar_json).unwrap();
    get_test_language_internal(
        &parser_name,
        &parser_code,
        &header_code,
        Some(&grammar_dir_path),
        wasm,
    )
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

pub fn get_test_language(
    name: &str,
    parser_code: &str,
    header_code: &str,
    path: Option<&Path>,
) -> Language {
    get_test_language_internal(name, parser_code, header_code, path, false)
}

fn get_test_language_internal(
    name: &str,
    parser_code: &str,
    header_code: &str,
    path: Option<&Path>,
    wasm: bool,
) -> Language {
    let src_dir = scratch_dir().join("src").join(name);
    fs::create_dir_all(&src_dir).unwrap();

    let parser_path = src_dir.join("parser.c");
    if !fs::read_to_string(&parser_path).is_ok_and(|content| content == parser_code) {
        fs::write(&parser_path, parser_code).unwrap();
    }

    let scanner_path = if let Some(path) = path {
        let scanner_path = path.join("scanner.c");
        if scanner_path.exists() {
            let scanner_code = fs::read_to_string(&scanner_path).unwrap();
            let scanner_copy_path = src_dir.join("scanner.c");
            if !fs::read_to_string(&scanner_copy_path).is_ok_and(|content| content == scanner_code)
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

    let parser_h_content = if header_code.is_empty() {
        tree_sitter::PARSER_HEADER.to_string()
    } else {
        let Some(insert_pos) = tree_sitter::PARSER_HEADER.find("}\n\n/*\n *  Lexer Macros\n */")
        else {
            panic!("Failed to find insertion point in parser.h");
        };

        let mut content = tree_sitter::PARSER_HEADER.to_string();
        content.insert_str(insert_pos + 1, &format!("\n\n{header_code}"));
        content
    };

    for (file, content) in [
        ("alloc.h", ALLOC_HEADER),
        ("array.h", ARRAY_HEADER),
        ("parser.h", parser_h_content.as_str()),
    ] {
        let file = header_path.join(file);
        fs::write(&file, content)
            .with_context(|| format!("Failed to write {:?}", file.file_name().unwrap()))
            .unwrap();
    }

    let paths_to_check = if let Some(scanner_path) = &scanner_path {
        vec![parser_path, scanner_path.clone()]
    } else {
        vec![parser_path]
    };

    let mut config = CompileConfig::new(&src_dir, Some(&paths_to_check), None);
    config.header_paths = vec![&HEADER_DIR];
    config.name = name.to_string();

    if wasm {
        #[cfg(feature = "wasm")]
        {
            let mut loader = Loader::with_parser_lib_path(SCRATCH_DIR.clone());
            loader.use_wasm(&ENGINE);
            if env::var("TREE_SITTER_GRAMMAR_DEBUG").is_ok() {
                loader.debug_build(true);
            }
            loader.load_language_at_path_with_name(config).unwrap()
        }
        #[cfg(not(feature = "wasm"))]
        {
            unimplemented!("Wasm feature is not enabled")
        }
    } else {
        TEST_LOADER.load_language_at_path_with_name(config).unwrap()
    }
}
