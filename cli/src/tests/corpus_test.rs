use super::helpers::{
    allocations,
    edits::{get_random_edit, invert_edit},
    fixtures::{fixtures_dir, get_language, get_test_language, SCRATCH_BASE_DIR},
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
use std::{collections::HashMap, env, fs};
use tree_sitter::{LogType, Node, Parser, Point, Range, Tree};
use tree_sitter_proc_macro::test_with_seed;

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_bash(seed: usize) {
    test_language_corpus(
        "bash",
        seed,
        Some(&[
            // Fragile tests where edit customization changes
            // lead to significant parse tree structure changes.
            "bash - corpus - commands - Nested Heredocs",
            "bash - corpus - commands - Quoted Heredocs",
            "bash - corpus - commands - Heredocs with weird characters",
        ]),
        None,
    );
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_c(seed: usize) {
    test_language_corpus("c", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_cpp(seed: usize) {
    test_language_corpus("cpp", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_embedded_template(seed: usize) {
    test_language_corpus("embedded-template", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_go(seed: usize) {
    test_language_corpus("go", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_html(seed: usize) {
    test_language_corpus("html", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_java(seed: usize) {
    test_language_corpus("java", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_javascript(seed: usize) {
    test_language_corpus("javascript", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_json(seed: usize) {
    test_language_corpus("json", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_php(seed: usize) {
    test_language_corpus("php", seed, None, Some("php"));
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_python(seed: usize) {
    test_language_corpus("python", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_ruby(seed: usize) {
    test_language_corpus("ruby", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_rust(seed: usize) {
    test_language_corpus("rust", seed, None, None);
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_typescript(seed: usize) {
    test_language_corpus("typescript", seed, None, Some("typescript"));
}

#[test_with_seed(retry=10, seed=*START_SEED, seed_fn=new_seed)]
fn test_corpus_for_tsx(seed: usize) {
    test_language_corpus("typescript", seed, None, Some("tsx"));
}

fn test_language_corpus(
    language_name: &str,
    start_seed: usize,
    skipped: Option<&[&str]>,
    subdir: Option<&str>,
) {
    let subdir = subdir.unwrap_or_default();

    let grammars_dir = fixtures_dir().join("grammars");
    let error_corpus_dir = fixtures_dir().join("error_corpus");
    let template_corpus_dir = fixtures_dir().join("template_corpus");
    let mut corpus_dir = grammars_dir.join(language_name).join(subdir).join("corpus");
    if !corpus_dir.is_dir() {
        corpus_dir = grammars_dir
            .join(language_name)
            .join(subdir)
            .join("test")
            .join("corpus");
    }

    let error_corpus_file = error_corpus_dir.join(format!("{language_name}_errors.txt"));
    let template_corpus_file = template_corpus_dir.join(format!("{language_name}_templates.txt"));
    let main_tests = parse_tests(&corpus_dir).unwrap();
    let error_tests = parse_tests(&error_corpus_file).unwrap_or_default();
    let template_tests = parse_tests(&template_corpus_file).unwrap_or_default();
    let mut tests = flatten_tests(main_tests);
    tests.extend(flatten_tests(error_tests));
    tests.extend(flatten_tests(template_tests).into_iter().map(|mut t| {
        t.template_delimiters = Some(("<%", "%>"));
        t
    }));

    let mut skipped = skipped.map(|x| x.iter().map(|x| (*x, 0)).collect::<HashMap<&str, usize>>());

    let language_path = if subdir.is_empty() {
        language_name.to_string()
    } else {
        format!("{language_name}/{subdir}")
    };
    let language = get_language(&language_path);
    let mut failure_count = 0;

    let log_seed = env::var("TREE_SITTER_LOG_SEED").is_ok();
    let dump_edits = env::var("TREE_SITTER_DUMP_EDITS").is_ok();

    if log_seed {
        println!("  start seed: {start_seed}");
    }

    println!();
    for (test_index, test) in tests.iter().enumerate() {
        let test_name = format!("{language_name} - {}", test.name);
        if let Some(skipped) = skipped.as_mut() {
            if let Some(counter) = skipped.get_mut(test_name.as_str()) {
                println!("  {test_index}. {test_name} - SKIPPED");
                *counter += 1;
                continue;
            }
        }

        println!("  {test_index}. {test_name}");

        let passed = allocations::record(|| {
            let mut log_session = None;
            let mut parser = get_parser(&mut log_session, "log.html");
            parser.set_language(&language).unwrap();
            set_included_ranges(&mut parser, &test.input, test.template_delimiters);

            let tree = parser.parse(&test.input, None).unwrap();
            let mut actual_output = tree.root_node().to_sexp();
            if !test.has_fields {
                actual_output = strip_sexp_fields(&actual_output);
            }

            if actual_output != test.output {
                println!("Incorrect initial parse for {test_name}");
                print_diff_key();
                print_diff(&actual_output, &test.output);
                println!();
                return false;
            }

            true
        });

        if !passed {
            failure_count += 1;
            continue;
        }

        let mut parser = Parser::new();
        parser.set_language(&language).unwrap();
        let tree = parser.parse(&test.input, None).unwrap();
        drop(parser);

        for trial in 0..*ITERATION_COUNT {
            let seed = start_seed + trial;
            let passed = allocations::record(|| {
                let mut rand = Rand::new(seed);
                let mut log_session = None;
                let mut parser = get_parser(&mut log_session, "log.html");
                parser.set_language(&language).unwrap();
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
                    perform_edit(&mut tree, &mut input, &edit).unwrap();
                }

                if log_seed {
                    println!("   {test_index}.{trial:<2} seed: {seed}");
                }

                if dump_edits {
                    fs::write(
                        SCRATCH_BASE_DIR
                            .join(format!("edit.{seed}.{test_index}.{trial} {test_name}")),
                        &input,
                    )
                    .unwrap();
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
                    perform_edit(&mut tree2, &mut input, &edit).unwrap();
                }
                if *LOG_GRAPH_ENABLED {
                    eprintln!("{}\n", String::from_utf8_lossy(&input));
                }

                set_included_ranges(&mut parser, &test.input, test.template_delimiters);
                let tree3 = parser.parse(&input, Some(&tree2)).unwrap();

                // Verify that the final tree matches the expectation from the corpus.
                let mut actual_output = tree3.root_node().to_sexp();
                if !test.has_fields {
                    actual_output = strip_sexp_fields(&actual_output);
                }

                if actual_output != test.output {
                    println!("Incorrect parse for {test_name} - seed {seed}");
                    print_diff_key();
                    print_diff(&actual_output, &test.output);
                    println!();
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

    assert!(
        failure_count == 0,
        "{failure_count} {language_name} corpus tests failed"
    );

    if let Some(skipped) = skipped.as_mut() {
        skipped.retain(|_, v| *v == 0);

        if !skipped.is_empty() {
            println!("Non matchable skip definitions:");
            for k in skipped.keys() {
                println!("  {k}");
            }
            panic!("Non matchable skip definitions needs to be removed");
        }
    }
}

#[test]
fn test_feature_corpus_files() {
    let test_grammars_dir = fixtures_dir().join("test_grammars");

    let mut failure_count = 0;
    for entry in fs::read_dir(test_grammars_dir).unwrap() {
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
        let grammar_json = generate::load_grammar_file(&grammar_path, None).unwrap();
        let generate_result = generate::generate_parser_for_grammar(&grammar_json);

        if error_message_path.exists() {
            if EXAMPLE_FILTER.is_some() {
                continue;
            }

            eprintln!("test language: {language_name:?}");

            let expected_message = fs::read_to_string(&error_message_path)
                .unwrap()
                .replace("\r\n", "\n");
            if let Err(e) = generate_result {
                let actual_message = e.to_string().replace("\r\n", "\n");
                if expected_message != actual_message {
                    eprintln!(
                        "Unexpected error message.\n\nExpected:\n\n{expected_message}\nActual:\n\n{actual_message}\n",
                    );
                    failure_count += 1;
                }
            } else {
                eprintln!("Expected error message but got none for test grammar '{language_name}'",);
                failure_count += 1;
            }
        } else {
            if let Err(e) = &generate_result {
                eprintln!("Unexpected error for test grammar '{language_name}':\n{e}",);
                failure_count += 1;
                continue;
            }

            let corpus_path = test_path.join("corpus.txt");
            let c_code = generate_result.unwrap().1;
            let language = get_test_language(language_name, &c_code, Some(&test_path));
            let test = parse_tests(&corpus_path).unwrap();
            let tests = flatten_tests(test);

            if !tests.is_empty() {
                eprintln!("test language: {language_name:?}");
            }

            for test in tests {
                eprintln!("  example: {:?}", test.name);

                let passed = allocations::record(|| {
                    let mut log_session = None;
                    let mut parser = get_parser(&mut log_session, "log.html");
                    parser.set_language(&language).unwrap();
                    let tree = parser.parse(&test.input, None).unwrap();
                    let mut actual_output = tree.root_node().to_sexp();
                    if !test.has_fields {
                        actual_output = strip_sexp_fields(&actual_output);
                    }
                    if actual_output == test.output {
                        true
                    } else {
                        print_diff_key();
                        print_diff(&actual_output, &test.output);
                        println!();
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

    assert!(failure_count == 0, "{failure_count} corpus tests failed");
}

fn check_consistent_sizes(tree: &Tree, input: &[u8]) {
    fn check(node: Node, line_offsets: &[usize]) {
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
        if *c == b'\n' {
            line_offsets.push(i + 1);
        }
    }

    check(tree.root_node(), &line_offsets);
}

fn check_changed_ranges(old_tree: &Tree, new_tree: &Tree, input: &[u8]) -> Result<(), String> {
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
                "changed range extends outside of the old and new trees {range:?}",
            ));
        }
    }

    old_scope_sequence.check_changes(&new_scope_sequence, input, &changed_ranges)
}

fn set_included_ranges(parser: &mut Parser, input: &[u8], delimiters: Option<(&str, &str)>) {
    if let Some((start, end)) = delimiters {
        let mut ranges = Vec::new();
        let mut ix = 0;
        while ix < input.len() {
            let Some(mut start_ix) = input[ix..]
                .windows(2)
                .position(|win| win == start.as_bytes())
            else {
                break;
            };
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
                eprintln!("  {msg}");
            } else {
                eprintln!("{msg}");
            }
        })));
    } else if *LOG_GRAPH_ENABLED {
        *session = Some(util::log_graphs(&mut parser, log_filename, false).unwrap());
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
                ..
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
