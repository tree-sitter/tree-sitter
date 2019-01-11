use super::languages;
use crate::generate;
use crate::loader::Loader;
use crate::test::{parse_tests, TestEntry};
use std::fs;
use std::path::{Path, PathBuf};
use tree_sitter::{Language, Parser};

lazy_static! {
    static ref LANGUAGES: [(&'static str, Language); 6] = [
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
}

#[test]
fn test_real_language_corpus_files() {
    let mut parser = Parser::new();
    let grammars_dir = FIXTURES_DIR.join("grammars");

    for (name, language) in LANGUAGES.iter().cloned() {
        let corpus_dir = grammars_dir.join(name).join("corpus");
        let test = parse_tests(&corpus_dir).unwrap();
        parser.set_language(language).unwrap();
        run_mutation_tests(&mut parser, test);
    }
}

#[test]
fn test_feature_corpus_files() {
    fs::create_dir_all(SCRATCH_DIR.as_path()).unwrap();

    let mut loader = Loader::new(SCRATCH_DIR.clone());
    let mut parser = Parser::new();
    let test_grammars_dir = FIXTURES_DIR.join("test_grammars");

    for entry in fs::read_dir(&test_grammars_dir).unwrap() {
        let entry = entry.unwrap();
        let test_name = entry.file_name();
        let test_name = test_name.to_str().unwrap();

        eprintln!("test name: {}", test_name);
        let test_path = entry.path();
        let grammar_path = test_path.join("grammar.json");
        let corpus_path = test_path.join("corpus.txt");
        let error_message_path = test_path.join("expected_error.txt");

        let grammar_json = fs::read_to_string(grammar_path).unwrap();
        let generate_result = generate::generate_parser_for_grammar(&grammar_json);
        if error_message_path.exists() {
            continue;
            if let Err(e) = generate_result {
                assert_eq!(e.0, fs::read_to_string(&error_message_path).unwrap());
            } else {
                panic!(
                    "Expected error message but got none for test grammar '{}'",
                    test_name
                );
            }
        } else {
            let c_code = generate_result.unwrap();
            let parser_c_path = SCRATCH_DIR.join(&format!("{}-parser.c", test_name));
            fs::write(&parser_c_path, c_code).unwrap();
            let scanner_path = test_path.join("scanner.c");
            let scanner_path = if scanner_path.exists() {
                Some(scanner_path)
            } else {
                None
            };
            let language = loader
                .load_language_from_sources(test_name, &HEADER_DIR, &parser_c_path, &scanner_path)
                .unwrap();
        }
    }

    // for (name, language) in LANGUAGES.iter().cloned() {
    //     let corpus_dir = grammars_dir.join(name).join("corpus");
    //     let test = parse_tests(&corpus_dir).unwrap();
    //     parser.set_language(language).unwrap();
    //     run_mutation_tests(&mut parser, test);
    // }
}

fn run_mutation_tests(parser: &mut Parser, test: TestEntry) {
    match test {
        TestEntry::Example {
            name,
            input,
            output,
        } => {
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
