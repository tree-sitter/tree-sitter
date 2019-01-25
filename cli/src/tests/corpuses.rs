use super::allocations;
use super::fixtures::{fixtures_dir, get_language, get_test_language};
use super::random::Rand;
use crate::generate;
use crate::test::{parse_tests, print_diff, print_diff_key, TestEntry};
use crate::util;
use std::{env, fs, time, usize};
use tree_sitter::{InputEdit, LogType, Parser, Point, Tree};

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
        let corpus_dir = grammars_dir.join(language_name).join("corpus");
        let error_corpus_file = error_corpus_dir.join(&format!("{}_errors.txt", language_name));
        let main_tests = parse_tests(&corpus_dir).unwrap();
        let error_tests = parse_tests(&error_corpus_file).unwrap_or(TestEntry::default());
        let mut tests = flatten_tests(main_tests);
        tests.extend(flatten_tests(error_tests));

        if !tests.is_empty() {
            eprintln!("language: {:?}", language_name);
        }

        for (example_name, input, expected_output) in tests {
            eprintln!("  example: {:?}", example_name);

            if TRIAL_FILTER.map_or(true, |t| t == 0) {
                allocations::start_recording();
                let mut log_session = None;
                let mut parser = get_parser(&mut log_session, "log.html");
                parser.set_language(language).unwrap();
                let tree = parser.parse_utf8(&mut |i, _| &input[i..], None).unwrap();
                let actual_output = tree.root_node().to_sexp();
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
            let tree = parser
                .parse_utf8(&mut |i, _| input.get(i..).unwrap_or(&[]), None)
                .unwrap();
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

                    let mut tree2 = parser
                        .parse_utf8(&mut |i, _| input.get(i..).unwrap_or(&[]), Some(&tree))
                        .unwrap();

                    // Check that the new tree is consistent.
                    check_consistent_sizes(&tree2, &input);
                    check_changed_ranges(&tree, &tree2, &input);

                    // Undo all of the edits and re-parse again.
                    while let Some(edit) = undo_stack.pop() {
                        perform_edit(&mut tree2, &mut input, &edit);
                    }
                    if *LOG_GRAPH_ENABLED {
                        eprintln!("{}\n", String::from_utf8_lossy(&input));
                    }

                    let tree3 = parser
                        .parse_utf8(&mut |i, _| input.get(i..).unwrap_or(&[]), Some(&tree2))
                        .unwrap();

                    // Check that the edited tree is consistent.
                    check_consistent_sizes(&tree3, &input);
                    check_changed_ranges(&tree2, &tree3, &input);

                    // Verify that the final tree matches the expectation from the corpus.
                    let actual_output = tree3.root_node().to_sexp();
                    if actual_output != expected_output {
                        println!("Incorrect parse for {} - {} - trial {}", language_name, example_name, trial);
                        print_diff_key();
                        print_diff(&actual_output, &expected_output);
                        println!("");
                        failure_count += 1;
                        // break;
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

struct Edit {
    position: usize,
    deleted_length: usize,
    inserted_text: Vec<u8>,
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
                if e.0 != expected_message {
                    eprintln!(
                        "Unexpected error message.\n\nExpected:\n\n{}\nActual:\n\n{}\n",
                        expected_message, e.0
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
            let language = get_test_language(language_name, c_code, &test_path);
            let test = parse_tests(&corpus_path).unwrap();
            let tests = flatten_tests(test);

            if !tests.is_empty() {
                eprintln!("test language: {:?}", language_name);
            }

            for (name, input, expected_output) in tests {
                eprintln!("  example: {:?}", name);

                allocations::start_recording();
                let mut log_session = None;
                let mut parser = get_parser(&mut log_session, "log.html");
                parser.set_language(language).unwrap();
                let tree = parser.parse_utf8(&mut |i, _| &input[i..], None).unwrap();
                let actual_output = tree.root_node().to_sexp();
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

fn get_random_edit(rand: &mut Rand, input: &Vec<u8>) -> Edit {
    let choice = rand.unsigned(10);
    if choice < 2 {
        // Insert text at end
        let inserted_text = rand.words(3);
        Edit {
            position: input.len(),
            deleted_length: 0,
            inserted_text,
        }
    } else if choice < 5 {
        // Delete text from the end
        let mut deleted_length = rand.unsigned(10);
        if deleted_length > input.len() {
            deleted_length = input.len();
        }
        Edit {
            position: input.len() - deleted_length,
            deleted_length,
            inserted_text: vec![],
        }
    } else if choice < 8 {
        // Insert at a random position
        let position = rand.unsigned(input.len());
        let word_count = 1 + rand.unsigned(3);
        let inserted_text = rand.words(word_count);
        Edit {
            position,
            deleted_length: 0,
            inserted_text,
        }
    } else {
        // Replace at random position
        let position = rand.unsigned(input.len());
        let deleted_length = rand.unsigned(input.len() - position);
        let word_count = 1 + rand.unsigned(3);
        let inserted_text = rand.words(word_count);
        Edit {
            position,
            deleted_length,
            inserted_text,
        }
    }
}

fn invert_edit(input: &Vec<u8>, edit: &Edit) -> Edit {
    let position = edit.position;
    let removed_content = &input[position..(position + edit.deleted_length)];
    Edit {
        position,
        deleted_length: edit.inserted_text.len(),
        inserted_text: removed_content.to_vec(),
    }
}

fn perform_edit(tree: &mut Tree, input: &mut Vec<u8>, edit: &Edit) {
    let start_byte = edit.position;
    let old_end_byte = edit.position + edit.deleted_length;
    let new_end_byte = edit.position + edit.inserted_text.len();
    let start_position = position_for_offset(input, start_byte);
    let old_end_position = position_for_offset(input, old_end_byte);
    input.splice(start_byte..old_end_byte, edit.inserted_text.iter().cloned());
    let new_end_position = position_for_offset(input, new_end_byte);
    tree.edit(&InputEdit {
        start_byte,
        old_end_byte,
        new_end_byte,
        start_position,
        old_end_position,
        new_end_position,
    });
}

fn position_for_offset(input: &Vec<u8>, offset: usize) -> Point {
    let mut result = Point { row: 0, column: 0 };
    for c in &input[0..offset] {
        if *c as char == '\n' {
            result.row += 1;
            result.column = 0;
        } else {
            result.column += 1;
        }
    }
    result
}

fn check_consistent_sizes(tree: &Tree, input: &Vec<u8>) {}

fn check_changed_ranges(old_tree: &Tree, new_tree: &Tree, input: &Vec<u8>) {}

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

fn flatten_tests(test: TestEntry) -> Vec<(String, Vec<u8>, String)> {
    fn helper(test: TestEntry, prefix: &str, result: &mut Vec<(String, Vec<u8>, String)>) {
        match test {
            TestEntry::Example {
                mut name,
                input,
                output,
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
                result.push((name, input, output));
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
