use super::languages;
use crate::generate;
use crate::loader::Loader;
use crate::test::{parse_tests, TestEntry};
use crate::util;
use std::fs;
use std::path::PathBuf;
use tree_sitter::{Language, Parser, LogType};

lazy_static! {
    static ref LANGUAGES: [(&'static str, Language); 7] = [
        ("bash", languages::bash()),
        ("c", languages::c()),
        ("cpp", languages::cpp()),
        ("embedded-template", languages::embedded_template()),
        ("go", languages::go()),
        ("html", languages::html()),
        ("javascript", languages::javascript()),
    ];
    static ref ROOT_DIR: PathBuf = [env!("CARGO_MANIFEST_DIR"), ".."].iter().collect();
    static ref HEADER_DIR: PathBuf = ROOT_DIR.join("lib").join("include");
    static ref SCRATCH_DIR: PathBuf = ROOT_DIR.join("target").join("scratch");
    static ref FIXTURES_DIR: PathBuf = ROOT_DIR.join("test").join("fixtures");
    static ref EXEC_PATH: PathBuf = std::env::current_exe().unwrap();
    static ref LANGUAGE_FILTER: Option<String> =
        std::env::var("TREE_SITTER_TEST_LANGUAGE_FILTER").ok();
    static ref EXAMPLE_FILTER: Option<String> =
        std::env::var("TREE_SITTER_TEST_EXAMPLE_FILTER").ok();
    static ref LOG_ENABLED: bool = std::env::var("TREE_SITTER_ENABLE_LOG").is_ok();
    static ref LOG_GRAPH_ENABLED: bool = std::env::var("TREE_SITTER_ENABLE_LOG_GRAPHS").is_ok();
}

#[test]
fn test_real_language_corpus_files() {
    let mut log_session = None;
    let mut parser = Parser::new();
    let grammars_dir = FIXTURES_DIR.join("grammars");

    if *LOG_ENABLED {
        parser.set_logger(Some(Box::new(|log_type, msg| {
            if log_type == LogType::Lex {
                eprintln!("  {}", msg);
            } else {
                eprintln!("{}", msg);
            }
        })));
    } else if *LOG_GRAPH_ENABLED {
        log_session = Some(util::log_graphs(&mut parser, "log.html").unwrap());
    }

    for (language_name, language) in LANGUAGES.iter().cloned() {
        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if !language_name.contains(filter.as_str()) {
                continue;
            }
        }

        eprintln!("language: {:?}", language_name);

        let corpus_dir = grammars_dir.join(language_name).join("corpus");
        let test = parse_tests(&corpus_dir).unwrap();
        parser.set_language(language).unwrap();
        run_mutation_tests(&mut parser, test);
    }

    drop(parser);
    drop(log_session);
}

#[test]
fn test_feature_corpus_files() {
    fs::create_dir_all(SCRATCH_DIR.as_path()).unwrap();

    let loader = Loader::new(SCRATCH_DIR.clone());
    let mut log_session = None;
    let mut parser = Parser::new();
    let test_grammars_dir = FIXTURES_DIR.join("test_grammars");

    if *LOG_ENABLED {
        parser.set_logger(Some(Box::new(|log_type, msg| {
            if log_type == LogType::Lex {
                eprintln!("  {}", msg);
            } else {
                eprintln!("{}", msg);
            }
        })));
    } else if *LOG_GRAPH_ENABLED {
        log_session = Some(util::log_graphs(&mut parser, "log.html").unwrap());
    }

    for entry in fs::read_dir(&test_grammars_dir).unwrap() {
        let entry = entry.unwrap();
        if !entry.metadata().unwrap().is_dir() {
            continue;
        }
        let language_name = entry.file_name();
        let language_name = language_name.to_str().unwrap();

        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if !language_name.contains(filter.as_str()) {
                continue;
            }
        }

        eprintln!("test language: {:?}", language_name);

        let test_path = entry.path();
        let grammar_path = test_path.join("grammar.json");
        let error_message_path = test_path.join("expected_error.txt");
        let grammar_json = fs::read_to_string(grammar_path).unwrap();
        let generate_result = generate::generate_parser_for_grammar(&grammar_json);

        if error_message_path.exists() {
            let expected_message = fs::read_to_string(&error_message_path).unwrap();
            if let Err(e) = generate_result {
                if e.0 != expected_message {
                    panic!(
                        "Unexpected error message.\n\nExpected:\n\n{}\nActual:\n\n{}\n",
                        expected_message, e.0
                    );
                }
            } else {
                panic!(
                    "Expected error message but got none for test grammar '{}'",
                    language_name
                );
            }
        } else {
            let corpus_path = test_path.join("corpus.txt");
            let c_code = generate_result.unwrap();
            let parser_c_path = SCRATCH_DIR.join(&format!("{}-parser.c", language_name));
            if !fs::read_to_string(&parser_c_path)
                .map(|content| content == c_code)
                .unwrap_or(false)
            {
                fs::write(&parser_c_path, c_code).unwrap();
            }
            let scanner_path = test_path.join("scanner.c");
            let scanner_path = if scanner_path.exists() {
                Some(scanner_path)
            } else {
                None
            };
            let language = loader
                .load_language_from_sources(
                    language_name,
                    &HEADER_DIR,
                    &parser_c_path,
                    &scanner_path,
                )
                .unwrap();
            let test = parse_tests(&corpus_path).unwrap();
            parser.set_language(language).unwrap();
            run_mutation_tests(&mut parser, test);
        }
    }

    drop(parser);
    drop(log_session);
}

fn run_mutation_tests(parser: &mut Parser, test: TestEntry) {
    match test {
        TestEntry::Example {
            name,
            input,
            output,
        } => {
            if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                if !name.contains(filter.as_str()) {
                    return;
                }
            }

            eprintln!("  example: {:?}", name);

            let tree = parser
                .parse_utf8(&mut |byte_offset, _| &input[byte_offset..], None)
                .unwrap();
            let actual = tree.root_node().to_sexp();
            assert_eq!(actual, output);
        }
        TestEntry::Group { name, children } => {
            for child in children {
                run_mutation_tests(parser, child);
            }
        }
    }
}
