use super::helpers::{
    allocations,
    edits::{get_random_edit, invert_edit},
    fixtures::{fixtures_dir, get_language, get_test_language},
    new_seed,
    random::Rand,
    scope_sequence::ScopeSequence,
    EDIT_COUNT, EXAMPLE_FILTER, ITERATION_COUNT, LANGUAGE_FILTER, LOG_ENABLED, LOG_GRAPH_ENABLED,
    START_SEED,
};
use crate::{
    generate,
    parse::perform_edit,
    test::{parse_tests, print_diff, print_diff_key, strip_sexp_fields, TestEntry},
    util,
};
use proc_macro::test_with_seed;
use std::{env, fs};
use tree_sitter::{LogType, Node, Parser, Point, Range, Tree};

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_bash(seed: usize) {
    test_language_corpus(seed, "bash");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_c(seed: usize) {
    test_language_corpus(seed, "c");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_cpp(seed: usize) {
    test_language_corpus(seed, "cpp");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_embedded_template(seed: usize) {
    test_language_corpus(seed, "embedded-template");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_go(seed: usize) {
    test_language_corpus(seed, "go");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_html(seed: usize) {
    test_language_corpus(seed, "html");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_javascript(seed: usize) {
    test_language_corpus(seed, "javascript");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_json(seed: usize) {
    test_language_corpus(seed, "json");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_php(seed: usize) {
    test_language_corpus(seed, "php");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_python(seed: usize) {
    test_language_corpus(seed, "python");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_ruby(seed: usize) {
    test_language_corpus(seed, "ruby");
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_rust(seed: usize) {
    test_language_corpus(seed, "rust");
}

fn test_language_corpus(start_seed: usize, language_name: &str) {
    let grammars_dir = fixtures_dir().join("grammars");
    let error_corpus_dir = fixtures_dir().join("error_corpus");
    let template_corpus_dir = fixtures_dir().join("template_corpus");
    let mut corpus_dir = grammars_dir.join(language_name).join("corpus");
    if !corpus_dir.is_dir() {
        corpus_dir = grammars_dir.join(language_name).join("test").join("corpus");
    }

    let error_corpus_file = error_corpus_dir.join(&format!("{}_errors.txt", language_name));
    let template_corpus_file =
        template_corpus_dir.join(&format!("{}_templates.txt", language_name));
    let main_tests = parse_tests(&corpus_dir).unwrap();
    let error_tests = parse_tests(&error_corpus_file).unwrap_or(TestEntry::default());
    let template_tests = parse_tests(&template_corpus_file).unwrap_or(TestEntry::default());
    let mut tests = flatten_tests(main_tests);
    tests.extend(flatten_tests(error_tests));
    tests.extend(flatten_tests(template_tests).into_iter().map(|mut t| {
        t.template_delimiters = Some(("<%", "%>"));
        t
    }));

    let language = get_language(language_name);
    let mut failure_count = 0;

    let log_seed = env::var("TREE_SITTER_LOG_SEED").is_ok();

    println!();
    for test in tests {
        println!("  {} example - {}", language_name, test.name);

        let passed = allocations::record(|| {
            let mut log_session = None;
            let mut parser = get_parser(&mut log_session, "log.html");
            parser.set_language(language).unwrap();
            set_included_ranges(&mut parser, &test.input, test.template_delimiters);

            let tree = parser.parse(&test.input, None).unwrap();
            let mut actual_output = tree.root_node().to_sexp();
            if !test.has_fields {
                actual_output = strip_sexp_fields(actual_output);
            }

            if actual_output != test.output {
                println!(
                    "Incorrect initial parse for {} - {}",
                    language_name, test.name,
                );
                print_diff_key();
                print_diff(&actual_output, &test.output);
                println!("");
                return false;
            }

            true
        });

        if !passed {
            failure_count += 1;
            continue;
        }

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(&test.input, None).unwrap();
        drop(parser);

        for trial in 0..*ITERATION_COUNT {
            let seed = start_seed + trial;
            let passed = allocations::record(|| {
                let mut rand = Rand::new(seed);
                let mut log_session = None;
                let mut parser = get_parser(&mut log_session, "log.html");
                parser.set_language(language).unwrap();
                let mut tree = tree.clone();
                let mut input = test.input.clone();

                if *LOG_GRAPH_ENABLED {
                    eprintln!("{}\n", String::from_utf8_lossy(&input));
                }

                // Perform a random series of edits and reparse.
                let mut undo_stack = Vec::new();
                for _ in 0..1 + rand.unsigned(*EDIT_COUNT) {
                    let edit = get_random_edit(&mut rand, &input);
                    undo_stack.push(invert_edit(&input, &edit));
                    perform_edit(&mut tree, &mut input, &edit);
                }

                if log_seed {
                    println!("    seed: {}", seed);
                }

                if *LOG_GRAPH_ENABLED {
                    eprintln!("{}\n", String::from_utf8_lossy(&input));
                }

                set_included_ranges(&mut parser, &input, test.template_delimiters);
                let mut tree2 = parser.parse(&input, Some(&tree)).unwrap();

                // Check that the new tree is consistent.
                check_consistent_sizes(&tree2, &input);
                if let Err(message) = check_changed_ranges(&tree, &tree2, &input) {
                    println!("\nUnexpected scope change in seed {seed} with start seed {start_seed}\n{message}\n\n",);
                    return false;
                }

                // Undo all of the edits and re-parse again.
                while let Some(edit) = undo_stack.pop() {
                    perform_edit(&mut tree2, &mut input, &edit);
                }
                if *LOG_GRAPH_ENABLED {
                    eprintln!("{}\n", String::from_utf8_lossy(&input));
                }

                set_included_ranges(&mut parser, &test.input, test.template_delimiters);
                let tree3 = parser.parse(&input, Some(&tree2)).unwrap();

                // Verify that the final tree matches the expectation from the corpus.
                let mut actual_output = tree3.root_node().to_sexp();
                if !test.has_fields {
                    actual_output = strip_sexp_fields(actual_output);
                }

                if actual_output != test.output {
                    println!(
                        "Incorrect parse for {} - {} - seed {}",
                        language_name, test.name, seed
                    );
                    print_diff_key();
                    print_diff(&actual_output, &test.output);
                    println!("");
                    return false;
                }

                // Check that the edited tree is consistent.
                check_consistent_sizes(&tree3, &input);
                if let Err(message) = check_changed_ranges(&tree2, &tree3, &input) {
                    println!("Unexpected scope change in seed {seed} with start seed {start_seed}\n{message}\n\n");
                    return false;
                }

                true
            });

            if !passed {
                failure_count += 1;
                break;
            }
        }
    }

    if failure_count > 0 {
        panic!("{} {} corpus tests failed", failure_count, language_name);
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
        let mut grammar_path = test_path.join("grammar.js");
        if !grammar_path.exists() {
            grammar_path = test_path.join("grammar.json");
        }
        let error_message_path = test_path.join("expected_error.txt");
        let grammar_json = generate::load_grammar_file(&grammar_path).unwrap();
        let generate_result = generate::generate_parser_for_grammar(&grammar_json);

        if error_message_path.exists() {
            if EXAMPLE_FILTER.is_some() {
                continue;
            }

            eprintln!("test language: {:?}", language_name);

            let expected_message = fs::read_to_string(&error_message_path)
                .unwrap()
                .replace("\r\n", "\n");
            if let Err(e) = generate_result {
                let actual_message = e.to_string().replace("\r\n", "\n");
                if expected_message != actual_message {
                    eprintln!(
                        "Unexpected error message.\n\nExpected:\n\n{}\nActual:\n\n{}\n",
                        expected_message, actual_message
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
            if let Err(e) = &generate_result {
                eprintln!(
                    "Unexpected error for test grammar '{}':\n{}",
                    language_name, e
                );
                failure_count += 1;
                continue;
            }

            let corpus_path = test_path.join("corpus.txt");
            let c_code = generate_result.unwrap().1;
            let language = get_test_language(language_name, &c_code, Some(&test_path));
            let test = parse_tests(&corpus_path).unwrap();
            let tests = flatten_tests(test);

            if !tests.is_empty() {
                eprintln!("test language: {:?}", language_name);
            }

            for test in tests {
                eprintln!("  example: {:?}", test.name);

                let passed = allocations::record(|| {
                    let mut log_session = None;
                    let mut parser = get_parser(&mut log_session, "log.html");
                    parser.set_language(language).unwrap();
                    let tree = parser.parse(&test.input, None).unwrap();
                    let mut actual_output = tree.root_node().to_sexp();
                    if !test.has_fields {
                        actual_output = strip_sexp_fields(actual_output);
                    }
                    if actual_output == test.output {
                        true
                    } else {
                        print_diff_key();
                        print_diff(&actual_output, &test.output);
                        println!("");
                        false
                    }
                });

                if !passed {
                    failure_count += 1;
                    continue;
                }
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
    let changed_ranges = old_tree.changed_ranges(new_tree).collect::<Vec<_>>();
    let old_scope_sequence = ScopeSequence::new(old_tree);
    let new_scope_sequence = ScopeSequence::new(new_tree);

    let old_range = old_tree.root_node().range();
    let new_range = new_tree.root_node().range();

    let byte_range =
        old_range.start_byte.min(new_range.start_byte)..old_range.end_byte.max(new_range.end_byte);
    let point_range = old_range.start_point.min(new_range.start_point)
        ..old_range.end_point.max(new_range.end_point);

    for range in &changed_ranges {
        if range.end_byte > byte_range.end || range.end_point > point_range.end {
            return Err(format!(
                "changed range extends outside of the old and new trees {:?}",
                range
            ));
        }
    }

    old_scope_sequence.check_changes(&new_scope_sequence, &input, &changed_ranges)
}

fn set_included_ranges(parser: &mut Parser, input: &[u8], delimiters: Option<(&str, &str)>) {
    if let Some((start, end)) = delimiters {
        let mut ranges = Vec::new();
        let mut ix = 0;
        while ix < input.len() {
            let Some(mut start_ix) = input[ix..].windows(2).position(|win| win == start.as_bytes()) else { break };
            start_ix += ix + start.len();
            let end_ix = input[start_ix..]
                .windows(2)
                .position(|win| win == end.as_bytes())
                .map_or(input.len(), |ix| start_ix + ix);
            ix = end_ix;
            ranges.push(Range {
                start_byte: start_ix,
                end_byte: end_ix,
                start_point: point_for_offset(input, start_ix),
                end_point: point_for_offset(input, end_ix),
            });
        }

        parser.set_included_ranges(&ranges).unwrap();
    } else {
        parser.set_included_ranges(&[]).unwrap();
    }
}

fn point_for_offset(text: &[u8], offset: usize) -> Point {
    let mut point = Point::default();
    for byte in &text[..offset] {
        if *byte == b'\n' {
            point.row += 1;
            point.column = 0;
        } else {
            point.column += 1;
        }
    }
    point
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

struct FlattenedTest {
    name: String,
    input: Vec<u8>,
    output: String,
    has_fields: bool,
    template_delimiters: Option<(&'static str, &'static str)>,
}

fn flatten_tests(test: TestEntry) -> Vec<FlattenedTest> {
    fn helper(test: TestEntry, is_root: bool, prefix: &str, result: &mut Vec<FlattenedTest>) {
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
                result.push(FlattenedTest {
                    name,
                    input,
                    output,
                    has_fields,
                    template_delimiters: None,
                });
            }
            TestEntry::Group {
                mut name, children, ..
            } => {
                if !is_root && !prefix.is_empty() {
                    name.insert_str(0, " - ");
                    name.insert_str(0, prefix);
                }
                for child in children {
                    helper(child, false, &name, result);
                }
            }
        }
    }
    let mut result = Vec::new();
    helper(test, true, "", &mut result);
    result
}
