use super::languages;
use crate::test::{parse_tests, TestEntry};
use std::path::PathBuf;
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
}

#[test]
fn test_corpus_files() {
    let mut parser = Parser::new();
    let grammars_dir: PathBuf = [
        env!("CARGO_MANIFEST_DIR"),
        "..",
        "test",
        "fixtures",
        "grammars",
    ]
    .iter()
    .collect();

    for (name, language) in LANGUAGES.iter().cloned() {
        let corpus_dir = grammars_dir.join(name).join("corpus");
        let test = parse_tests(&corpus_dir).unwrap();
        parser.set_language(language).unwrap();
        run_mutation_tests(&mut parser, test);
    }
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
