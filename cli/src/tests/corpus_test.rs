use super::helpers::allocations;
use super::helpers::edits::{get_random_edit, invert_edit};
use super::helpers::fixtures::{fixtures_dir, get_language, get_test_language};
use super::helpers::random::Rand;
use super::helpers::scope_sequence::ScopeSequence;
use crate::generate;
use crate::parse::perform_edit;
use crate::test::{parse_tests, print_diff, print_diff_key, strip_sexp_fields, TestEntry};
use crate::util;
use lazy_static::lazy_static;
use std::{env, fs, time, usize};
use tree_sitter::{LogType, Node, Parser, Tree};

const EDIT_COUNT: usize = 3;
const TRIAL_COUNT: usize = 10;
const LANGUAGES: &'static [&'static str] = &[
    "bash",
    "c",
    "cpp",
    "embedded-template",
    "go",
    "html",
    "javascript",
    "json",
    "python",
];

lazy_static! {
    static ref LOG_ENABLED: bool = env::var("TREE_SITTER_TEST_ENABLE_LOG").is_ok();
    static ref LOG_GRAPH_ENABLED: bool = env::var("TREE_SITTER_TEST_ENABLE_LOG_GRAPHS").is_ok();
    static ref LANGUAGE_FILTER: Option<String> = env::var("TREE_SITTER_TEST_LANGUAGE_FILTER").ok();
    static ref EXAMPLE_FILTER: Option<String> = env::var("TREE_SITTER_TEST_EXAMPLE_FILTER").ok();
    static ref TRIAL_FILTER: Option<usize> = env::var("TREE_SITTER_TEST_TRIAL_FILTER")
        .map(|s| usize::from_str_radix(&s, 10).unwrap())
        .ok();
    pub static ref SEED: usize = env::var("TREE_SITTER_TEST_SEED")
        .map(|s| usize::from_str_radix(&s, 10).unwrap())
        .unwrap_or(
            time::SystemTime::now()
                .duration_since(time::UNIX_EPOCH)
                .unwrap()
                .as_secs() as usize,
        );
}

#[test]
fn test_real_language_corpus_files() {
    eprintln!("\n\nRandom seed: {}\n", *SEED);
    let grammars_dir = fixtures_dir().join("grammars");
    let error_corpus_dir = fixtures_dir().join("error_corpus");

    let mut failure_count = 0;
    for language_name in LANGUAGES.iter().cloned() {
        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }

        let language = get_language(language_name);
        let mut corpus_dir = grammars_dir.join(language_name).join("corpus");
        if !corpus_dir.is_dir() {
            corpus_dir = grammars_dir.join(language_name).join("test").join("corpus");
        }

        let error_corpus_file = error_corpus_dir.join(&format!("{}_errors.txt", language_name));
        let main_tests = parse_tests(&corpus_dir).unwrap();
        let error_tests = parse_tests(&error_corpus_file).unwrap_or(TestEntry::default());
        let mut tests = flatten_tests(main_tests);
        tests.extend(flatten_tests(error_tests));

        if !tests.is_empty() {
            eprintln!("language: {:?}", language_name);
        }

        for (example_name, input, expected_output, has_fields) in tests {
            eprintln!("  example: {:?}", example_name);

            if TRIAL_FILTER.map_or(true, |t| t == 0) {
                allocations::start_recording();
                let mut log_session = None;
                let mut parser = get_parser(&mut log_session, "log.html");
                parser.set_language(language).unwrap();
                let tree = parser.parse(&input, None).unwrap();
                let mut actual_output = tree.root_node().to_sexp();
                if !has_fields {
                    actual_output = strip_sexp_fields(actual_output);
                }
                drop(tree);
                drop(parser);
                if actual_output != expected_output {
                    print_diff_key();
                    print_diff(&actual_output, &expected_output);
                    println!("");
                    failure_count += 1;
                    continue;
                }
                allocations::stop_recording();
            }

            let mut parser = Parser::new();
            parser.set_language(language).unwrap();
            let tree = parser.parse(&input, None).unwrap();
            drop(parser);

            for trial in 1..=TRIAL_COUNT {
                if TRIAL_FILTER.map_or(true, |filter| filter == trial) {
                    let mut rand = Rand::new(*SEED + trial);

                    allocations::start_recording();
                    let mut log_session = None;
                    let mut parser = get_parser(&mut log_session, "log.html");
                    parser.set_language(language).unwrap();
                    let mut tree = tree.clone();
                    let mut input = input.clone();

                    if *LOG_GRAPH_ENABLED {
                        eprintln!("{}\n", String::from_utf8_lossy(&input));
                    }

                    // Perform a random series of edits and reparse.
                    let mut undo_stack = Vec::new();
                    for _ in 0..EDIT_COUNT {
                        let edit = get_random_edit(&mut rand, &input);
                        undo_stack.push(invert_edit(&input, &edit));
                        perform_edit(&mut tree, &mut input, &edit);
                    }
                    if *LOG_GRAPH_ENABLED {
                        eprintln!("{}\n", String::from_utf8_lossy(&input));
                    }

                    let mut tree2 = parser.parse(&input, Some(&tree)).unwrap();

                    // Check that the new tree is consistent.
                    check_consistent_sizes(&tree2, &input);
                    if let Err(message) = check_changed_ranges(&tree, &tree2, &input) {
                        println!(
                            "\nUnexpected scope change in trial {}\n{}\n\n",
                            trial, message
                        );
                        failure_count += 1;
                        break;
                    }

                    // Undo all of the edits and re-parse again.
                    while let Some(edit) = undo_stack.pop() {
                        perform_edit(&mut tree2, &mut input, &edit);
                    }
                    if *LOG_GRAPH_ENABLED {
                        eprintln!("{}\n", String::from_utf8_lossy(&input));
                    }

                    let tree3 = parser.parse(&input, Some(&tree2)).unwrap();

                    // Verify that the final tree matches the expectation from the corpus.
                    let mut actual_output = tree3.root_node().to_sexp();
                    if !has_fields {
                        actual_output = strip_sexp_fields(actual_output);
                    }

                    if actual_output != expected_output {
                        println!(
                            "Incorrect parse for {} - {} - trial {}",
                            language_name, example_name, trial
                        );
                        print_diff_key();
                        print_diff(&actual_output, &expected_output);
                        println!("");
                        failure_count += 1;
                        break;
                    }

                    // Check that the edited tree is consistent.
                    check_consistent_sizes(&tree3, &input);
                    if let Err(message) = check_changed_ranges(&tree2, &tree3, &input) {
                        eprintln!(
                            "Unexpected scope change in trial {}\n{}\n\n",
                            trial, message
                        );
                        failure_count += 1;
                        break;
                    }

                    drop(tree);
                    drop(tree2);
                    drop(tree3);
                    drop(parser);
                    allocations::stop_recording();
                }
            }
        }
    }
    if failure_count > 0 {
        panic!("{} corpus tests failed", failure_count);
    }
}

#[test]
fn test_feature_corpus_files() {
    let test_grammars_dir = fixtures_dir().join("test_grammars");

    let mut failure_count = 0;
    for entry in fs::read_dir(&test_grammars_dir).unwrap() {
        let entry = entry.unwrap();
        if !entry.metadata().unwrap().is_dir() {
            continue;
        }
        let language_name = entry.file_name();
        let language_name = language_name.to_str().unwrap();

        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }

        let test_path = entry.path();
        let grammar_path = test_path.join("grammar.json");
        let error_message_path = test_path.join("expected_error.txt");
        let grammar_json = fs::read_to_string(grammar_path).unwrap();
        let generate_result = generate::generate_parser_for_grammar(&grammar_json);

        if error_message_path.exists() {
            if EXAMPLE_FILTER.is_some() {
                continue;
            }

            eprintln!("test language: {:?}", language_name);

            let expected_message = fs::read_to_string(&error_message_path).unwrap();
            if let Err(e) = generate_result {
                if e.message() != expected_message {
                    eprintln!(
                        "Unexpected error message.\n\nExpected:\n\n{}\nActual:\n\n{}\n",
                        expected_message,
                        e.message()
                    );
                    failure_count += 1;
                }
            } else {
                eprintln!(
                    "Expected error message but got none for test grammar '{}'",
                    language_name
                );
                failure_count += 1;
            }
        } else {
            let corpus_path = test_path.join("corpus.txt");
            let c_code = generate_result.unwrap().1;
            let language = get_test_language(language_name, &c_code, Some(&test_path));
            let test = parse_tests(&corpus_path).unwrap();
            let tests = flatten_tests(test);

            if !tests.is_empty() {
                eprintln!("test language: {:?}", language_name);
            }

            for (name, input, expected_output, has_fields) in tests {
                eprintln!("  example: {:?}", name);

                allocations::start_recording();
                let mut log_session = None;
                let mut parser = get_parser(&mut log_session, "log.html");
                parser.set_language(language).unwrap();
                let tree = parser.parse(&input, None).unwrap();
                let mut actual_output = tree.root_node().to_sexp();
                if !has_fields {
                    actual_output = strip_sexp_fields(actual_output);
                }

                drop(tree);
                drop(parser);
                if actual_output != expected_output {
                    print_diff_key();
                    print_diff(&actual_output, &expected_output);
                    println!("");
                    failure_count += 1;
                    continue;
                }
                allocations::stop_recording();
            }
        }
    }
    if failure_count > 0 {
        panic!("{} corpus tests failed", failure_count);
    }
}

fn check_consistent_sizes(tree: &Tree, input: &Vec<u8>) {
    fn check(node: Node, line_offsets: &Vec<usize>) {
        let start_byte = node.start_byte();
        let end_byte = node.end_byte();
        let start_point = node.start_position();
        let end_point = node.end_position();

        assert!(start_byte <= end_byte);
        assert!(start_point <= end_point);
        assert_eq!(
            start_byte,
            line_offsets[start_point.row] + start_point.column
        );
        assert_eq!(end_byte, line_offsets[end_point.row] + end_point.column);

        let mut last_child_end_byte = start_byte;
        let mut last_child_end_point = start_point;
        let mut some_child_has_changes = false;
        let mut actual_named_child_count = 0;
        for i in 0..node.child_count() {
            let child = node.child(i).unwrap();
            assert!(child.start_byte() >= last_child_end_byte);
            assert!(child.start_position() >= last_child_end_point);
            check(child, line_offsets);
            if child.has_changes() {
                some_child_has_changes = true;
            }
            if child.is_named() {
                actual_named_child_count += 1;
            }
            last_child_end_byte = child.end_byte();
            last_child_end_point = child.end_position();
        }

        assert_eq!(actual_named_child_count, node.named_child_count());

        if node.child_count() > 0 {
            assert!(end_byte >= last_child_end_byte);
            assert!(end_point >= last_child_end_point);
        }

        if some_child_has_changes {
            assert!(node.has_changes());
        }
    }

    let mut line_offsets = vec![0];
    for (i, c) in input.iter().enumerate() {
        if *c == '\n' as u8 {
            line_offsets.push(i + 1);
        }
    }

    check(tree.root_node(), &line_offsets);
}

fn check_changed_ranges(old_tree: &Tree, new_tree: &Tree, input: &Vec<u8>) -> Result<(), String> {
    let changed_ranges = old_tree.changed_ranges(new_tree).collect();
    let old_scope_sequence = ScopeSequence::new(old_tree);
    let new_scope_sequence = ScopeSequence::new(new_tree);
    old_scope_sequence.check_changes(&new_scope_sequence, &input, &changed_ranges)
}

fn get_parser(session: &mut Option<util::LogSession>, log_filename: &str) -> Parser {
    let mut parser = Parser::new();

    if *LOG_ENABLED {
        parser.set_logger(Some(Box::new(|log_type, msg| {
            if log_type == LogType::Lex {
                eprintln!("  {}", msg);
            } else {
                eprintln!("{}", msg);
            }
        })));
    } else if *LOG_GRAPH_ENABLED {
        *session = Some(util::log_graphs(&mut parser, log_filename).unwrap());
    }

    parser
}

fn flatten_tests(test: TestEntry) -> Vec<(String, Vec<u8>, String, bool)> {
    fn helper(test: TestEntry, prefix: &str, result: &mut Vec<(String, Vec<u8>, String, bool)>) {
        match test {
            TestEntry::Example {
                mut name,
                input,
                output,
                has_fields,
            } => {
                if !prefix.is_empty() {
                    name.insert_str(0, " - ");
                    name.insert_str(0, prefix);
                }
                if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                    if !name.contains(filter.as_str()) {
                        return;
                    }
                }
                result.push((name, input, output, has_fields));
            }
            TestEntry::Group { mut name, children } => {
                if !prefix.is_empty() {
                    name.insert_str(0, " - ");
                    name.insert_str(0, prefix);
                }
                for child in children {
                    helper(child, &name, result);
                }
            }
        }
    }
    let mut result = Vec::new();
    helper(test, "", &mut result);
    result
}
