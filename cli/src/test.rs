use std::{
    collections::{BTreeMap, HashSet},
    ffi::OsStr,
    fs,
    io::{self, Write},
    path::{Path, PathBuf},
    str,
};

use anstyle::{AnsiColor, Color, Style};
use anyhow::{anyhow, Context, Result};
use indoc::indoc;
use lazy_static::lazy_static;
use regex::Regex;
use similar::{ChangeTag, TextDiff};
use tree_sitter::{format_sexp, Language, LogType, Parser, Query};
use walkdir::WalkDir;

use super::util;

lazy_static! {
    static ref COMMENT_REGEX: Regex = Regex::new(r"(?m)^\s*;.*$").unwrap();
    static ref WHITESPACE_REGEX: Regex = Regex::new(r"\s+").unwrap();
    static ref SEXP_FIELD_REGEX: Regex = Regex::new(r" \w+: \(").unwrap();
    static ref POINT_REGEX: Regex = Regex::new(r"\s*\[\s*\d+\s*,\s*\d+\s*\]\s*").unwrap();
}

#[derive(Debug, PartialEq, Eq)]
pub enum TestEntry {
    Group {
        name: String,
        children: Vec<TestEntry>,
        file_path: Option<PathBuf>,
    },
    Example {
        name: String,
        input: Vec<u8>,
        output: String,
        header: String,
        divider_delim: String,
        has_fields: bool,
        attributes: TestAttributes,
    },
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TestAttributes {
    pub skip: bool,
    pub platform: bool,
    pub fail_fast: bool,
    pub error: bool,
    pub languages: Vec<Box<str>>,
}

impl Default for TestEntry {
    fn default() -> Self {
        Self::Group {
            name: String::new(),
            children: Vec::new(),
            file_path: None,
        }
    }
}

impl Default for TestAttributes {
    fn default() -> Self {
        Self {
            skip: false,
            platform: true,
            fail_fast: false,
            error: false,
            languages: vec!["".into()],
        }
    }
}

pub struct TestOptions<'a> {
    pub path: PathBuf,
    pub debug: bool,
    pub debug_graph: bool,
    pub filter: Option<&'a str>,
    pub include: Option<Regex>,
    pub exclude: Option<Regex>,
    pub update: bool,
    pub open_log: bool,
    pub languages: BTreeMap<&'a str, &'a Language>,
    pub color: bool,
    pub test_num: usize,
    pub show_fields: bool,
}

pub fn run_tests_at_path(parser: &mut Parser, opts: &mut TestOptions) -> Result<()> {
    let test_entry = parse_tests(&opts.path)?;
    let mut _log_session = None;

    if opts.debug_graph {
        _log_session = Some(util::log_graphs(parser, "log.html", opts.open_log)?);
    } else if opts.debug {
        parser.set_logger(Some(Box::new(|log_type, message| {
            if log_type == LogType::Lex {
                io::stderr().write_all(b"  ").unwrap();
            }
            writeln!(&mut io::stderr(), "{message}").unwrap();
        })));
    }

    let mut failures = Vec::new();
    let mut corrected_entries = Vec::new();
    let mut has_parse_errors = false;
    run_tests(
        parser,
        test_entry,
        opts,
        0,
        &mut failures,
        &mut corrected_entries,
        &mut has_parse_errors,
    )?;

    parser.stop_printing_dot_graphs();

    if failures.is_empty() {
        Ok(())
    } else {
        println!();

        if opts.update && !has_parse_errors {
            if failures.len() == 1 {
                println!("1 update:\n");
            } else {
                println!("{} updates:\n", failures.len());
            }

            for (i, (name, ..)) in failures.iter().enumerate() {
                println!("  {}. {name}", i + 1);
            }

            Ok(())
        } else {
            has_parse_errors = opts.update && has_parse_errors;

            if !has_parse_errors {
                if failures.len() == 1 {
                    println!("1 failure:");
                } else {
                    println!("{} failures:", failures.len());
                }
            }

            if opts.color {
                print_diff_key();
            }
            for (i, (name, actual, expected)) in failures.iter().enumerate() {
                println!("\n  {}. {name}:", i + 1);
                let actual = format_sexp(actual, 2);
                let expected = format_sexp(expected, 2);
                print_diff(&actual, &expected, opts.color);
            }

            if has_parse_errors {
                Err(anyhow!(indoc! {"
                    Some tests failed to parse with unexpected `ERROR` or `MISSING` nodes, as shown above, and cannot be updated automatically.
                    Either fix the grammar or manually update the tests if this is expected."}))
            } else {
                Err(anyhow!(""))
            }
        }
    }
}

#[allow(clippy::type_complexity)]
pub fn get_test_info<'test>(
    test_entry: &'test TestEntry,
    target_test: u32,
    test_num: &mut u32,
) -> Option<(&'test str, &'test [u8], Vec<Box<str>>)> {
    match test_entry {
        TestEntry::Example {
            name,
            input,
            attributes,
            ..
        } => {
            if *test_num == target_test {
                return Some((name, input, attributes.languages.clone()));
            } else {
                *test_num += 1;
            }
        }
        TestEntry::Group { children, .. } => {
            for child in children {
                if let Some((name, input, languages)) = get_test_info(child, target_test, test_num)
                {
                    return Some((name, input, languages));
                }
            }
        }
    }

    None
}

/// Writes the input of `target_test` to a temporary file and returns the path
pub fn get_tmp_test_file(target_test: u32, color: bool) -> Result<(PathBuf, Vec<Box<str>>)> {
    let current_dir = std::env::current_dir().unwrap();
    let test_dir = current_dir.join("test").join("corpus");

    // Get the input of the target test
    let test_entry = parse_tests(&test_dir)?;
    let mut test_num = 0;
    let Some((test_name, test_contents, languages)) =
        get_test_info(&test_entry, target_test - 1, &mut test_num)
    else {
        return Err(anyhow!("Failed to fetch contents of test #{target_test}"));
    };

    // Write the test contents to a temporary file
    let test_path = std::env::temp_dir().join(".tree-sitter-test");
    let mut test_file = std::fs::File::create(&test_path)?;
    test_file.write_all(test_contents)?;

    println!(
        "{target_test}. {}\n",
        paint(color.then_some(AnsiColor::Green), test_name)
    );

    Ok((test_path, languages))
}

pub fn check_queries_at_path(language: &Language, path: &Path) -> Result<()> {
    if path.exists() {
        for entry in WalkDir::new(path)
            .into_iter()
            .filter_map(std::result::Result::ok)
            .filter(|e| {
                e.file_type().is_file()
                    && e.path().extension().and_then(OsStr::to_str) == Some("scm")
                    && !e.path().starts_with(".")
            })
        {
            let filepath = entry.file_name().to_str().unwrap_or("");
            let content = fs::read_to_string(entry.path())
                .with_context(|| format!("Error reading query file {filepath:?}"))?;
            Query::new(language, &content)
                .with_context(|| format!("Error in query file {filepath:?}"))?;
        }
    }
    Ok(())
}

pub fn print_diff_key() {
    println!(
        "\ncorrect / {} / {}",
        paint(Some(AnsiColor::Green), "expected"),
        paint(Some(AnsiColor::Red), "unexpected")
    );
}

pub fn print_diff(actual: &str, expected: &str, use_color: bool) {
    let diff = TextDiff::from_lines(actual, expected);
    for diff in diff.iter_all_changes() {
        match diff.tag() {
            ChangeTag::Equal => {
                if use_color {
                    print!("{diff}");
                } else {
                    print!(" {diff}");
                }
            }
            ChangeTag::Insert => {
                if use_color {
                    print!("{}", paint(Some(AnsiColor::Green), diff.as_str().unwrap()));
                } else {
                    print!("+{diff}");
                }
                if diff.missing_newline() {
                    println!();
                }
            }
            ChangeTag::Delete => {
                if use_color {
                    print!("{}", paint(Some(AnsiColor::Red), diff.as_str().unwrap()));
                } else {
                    print!("-{diff}");
                }
                if diff.missing_newline() {
                    println!();
                }
            }
        }
    }

    println!();
}

pub fn paint(color: Option<AnsiColor>, text: &str) -> String {
    let style = Style::new().fg_color(color.map(Color::Ansi));
    format!("{style}{text}{style:#}")
}

/// This will return false if we want to "fail fast". It will bail and not parse any more tests.
#[allow(clippy::too_many_arguments)]
fn run_tests(
    parser: &mut Parser,
    test_entry: TestEntry,
    opts: &mut TestOptions,
    mut indent_level: i32,
    failures: &mut Vec<(String, String, String)>,
    corrected_entries: &mut Vec<(String, String, String, String, String)>,
    has_parse_errors: &mut bool,
) -> Result<bool> {
    match test_entry {
        TestEntry::Example {
            name,
            input,
            output,
            header: header_delim_len,
            divider_delim: divider_delim_len,
            has_fields,
            attributes,
        } => {
            print!("{}", "  ".repeat(indent_level as usize));

            if attributes.skip {
                println!(
                    "{:>3}.  {}",
                    opts.test_num,
                    paint(opts.color.then_some(AnsiColor::Yellow), &name),
                );
                return Ok(true);
            }

            if !attributes.platform {
                println!(
                    "{:>3}.  {}",
                    opts.test_num,
                    paint(opts.color.then_some(AnsiColor::Magenta), &name),
                );
                return Ok(true);
            }

            for (i, language_name) in attributes.languages.iter().enumerate() {
                if !language_name.is_empty() {
                    let language = opts
                        .languages
                        .get(language_name.as_ref())
                        .ok_or_else(|| anyhow!("Language not found: {language_name}"))?;
                    parser.set_language(language)?;
                }
                let tree = parser.parse(&input, None).unwrap();

                if attributes.error {
                    if tree.root_node().has_error() {
                        println!(
                            "{:>3}.  {}",
                            opts.test_num,
                            paint(opts.color.then_some(AnsiColor::Green), &name)
                        );
                    } else {
                        println!(
                            "{:>3}.  {}",
                            opts.test_num,
                            paint(opts.color.then_some(AnsiColor::Red), &name)
                        );
                    }

                    if attributes.fail_fast {
                        return Ok(false);
                    }
                } else {
                    let mut actual = tree.root_node().to_sexp();
                    if !(opts.show_fields || has_fields) {
                        actual = strip_sexp_fields(&actual);
                    }

                    if actual == output {
                        println!(
                            "{:>3}. ✓ {}",
                            opts.test_num,
                            paint(opts.color.then_some(AnsiColor::Green), &name)
                        );
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            let output = format_sexp(&output, 0);
                            corrected_entries.push((
                                name.clone(),
                                input,
                                output,
                                header_delim_len.clone(),
                                divider_delim_len.clone(),
                            ));
                        }
                    } else {
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            let expected_output = format_sexp(&output, 0);
                            let actual_output = format_sexp(&actual, 0);

                            // Only bail early before updating if the actual is not the output,
                            // sometimes users want to test cases that
                            // are intended to have errors, hence why this
                            // check isn't shown above
                            if actual.contains("ERROR") || actual.contains("MISSING") {
                                *has_parse_errors = true;

                                // keep the original `expected` output if the actual output has an
                                // error
                                corrected_entries.push((
                                    name.clone(),
                                    input,
                                    expected_output,
                                    header_delim_len.clone(),
                                    divider_delim_len.clone(),
                                ));
                            } else {
                                corrected_entries.push((
                                    name.clone(),
                                    input,
                                    actual_output,
                                    header_delim_len.clone(),
                                    divider_delim_len.clone(),
                                ));
                                println!(
                                    "{:>3}. ✓ {}",
                                    opts.test_num,
                                    paint(opts.color.then_some(AnsiColor::Blue), &name),
                                );
                            }
                        } else {
                            println!(
                                "{:>3}. ✗ {}",
                                opts.test_num,
                                paint(opts.color.then_some(AnsiColor::Red), &name),
                            );
                        }
                        failures.push((name.clone(), actual, output.clone()));

                        if attributes.fail_fast {
                            return Ok(false);
                        }
                    }
                }

                if i == attributes.languages.len() - 1 {
                    // reset to the first language
                    parser.set_language(opts.languages.values().next().unwrap())?;
                }
            }
            opts.test_num += 1;
        }
        TestEntry::Group {
            name,
            mut children,
            file_path,
        } => {
            // track which tests are being skipped to maintain consistent numbering while using
            // filters
            let mut skipped_tests = HashSet::new();
            let mut advance_counter = opts.test_num;
            children.retain(|child| match child {
                TestEntry::Example { name, .. } => {
                    if let Some(filter) = opts.filter {
                        if !name.contains(filter) {
                            skipped_tests.insert(advance_counter);
                            advance_counter += 1;
                            return false;
                        }
                    }
                    if let Some(include) = &opts.include {
                        if !include.is_match(name) {
                            skipped_tests.insert(advance_counter);
                            advance_counter += 1;
                            return false;
                        }
                    }
                    if let Some(exclude) = &opts.exclude {
                        if exclude.is_match(name) {
                            skipped_tests.insert(advance_counter);
                            advance_counter += 1;
                            return false;
                        }
                    }
                    advance_counter += 1;
                    true
                }
                TestEntry::Group { .. } => {
                    advance_counter += count_subtests(child);
                    true
                }
            });

            if children.is_empty() {
                opts.test_num = advance_counter;
                return Ok(true);
            }

            if indent_level > 0 {
                print!("{}", "  ".repeat(indent_level as usize));
                println!("{name}:");
            }

            let failure_count = failures.len();

            indent_level += 1;
            for child in children {
                if let TestEntry::Example { .. } = child {
                    while skipped_tests.remove(&opts.test_num) {
                        opts.test_num += 1;
                    }
                }
                if !run_tests(
                    parser,
                    child,
                    opts,
                    indent_level,
                    failures,
                    corrected_entries,
                    has_parse_errors,
                )? {
                    // fail fast
                    return Ok(false);
                }
            }

            opts.test_num += skipped_tests.len();

            if let Some(file_path) = file_path {
                if opts.update && failures.len() - failure_count > 0 {
                    write_tests(&file_path, corrected_entries)?;
                }
                corrected_entries.clear();
            }
        }
    }
    Ok(true)
}

fn count_subtests(test_entry: &TestEntry) -> usize {
    match test_entry {
        TestEntry::Example { .. } => 1,
        TestEntry::Group { children, .. } => children
            .iter()
            .fold(0, |count, child| count + count_subtests(child)),
    }
}

fn write_tests(
    file_path: &Path,
    corrected_entries: &[(String, String, String, String, String)],
) -> Result<()> {
    let mut buffer = fs::File::create(file_path)?;
    write_tests_to_buffer(&mut buffer, corrected_entries)
}

fn write_tests_to_buffer(
    buffer: &mut impl Write,
    corrected_entries: &[(String, String, String, String, String)],
) -> Result<()> {
    for (i, (_, input, output, header, divider_delim)) in corrected_entries.iter().enumerate() {
        if i > 0 {
            writeln!(buffer)?;
        }
        writeln!(
            buffer,
            "{header}\n{input}\n{divider_delim}\n\n{}",
            output.trim()
        )?;
    }
    Ok(())
}

pub fn parse_tests(path: &Path) -> io::Result<TestEntry> {
    let name = path
        .file_stem()
        .and_then(|s| s.to_str())
        .unwrap_or("")
        .to_string();
    if path.is_dir() {
        let mut children = Vec::new();
        for entry in fs::read_dir(path)? {
            let entry = entry?;
            let hidden = entry.file_name().to_str().unwrap_or("").starts_with('.');
            if !hidden {
                children.push(entry.path());
            }
        }
        children.sort_by(|a, b| {
            a.file_name()
                .unwrap_or_default()
                .cmp(b.file_name().unwrap_or_default())
        });
        let children = children
            .iter()
            .map(|path| parse_tests(path))
            .collect::<io::Result<Vec<TestEntry>>>()?;
        Ok(TestEntry::Group {
            name,
            children,
            file_path: None,
        })
    } else {
        let content = fs::read_to_string(path)?;
        Ok(parse_test_content(name, &content, Some(path.to_path_buf())))
    }
}

#[must_use]
pub fn strip_sexp_fields(sexp: &str) -> String {
    SEXP_FIELD_REGEX.replace_all(sexp, " (").to_string()
}

#[must_use]
pub fn strip_points(sexp: &str) -> String {
    POINT_REGEX.replace_all(sexp, "").to_string()
}

fn parse_test_content(name: String, content: &str, file_path: Option<PathBuf>) -> TestEntry {
    let mut parser = Parser::new();
    parser.set_language(&tree_sitter_test::language()).unwrap();
    let root = parser.parse(content, None).unwrap();
    let root = root.root_node();

    let children = root
        .children(&mut root.walk())
        .map(|item| {
            let source = content.as_bytes();
            let input = {
                let input = item.child(1).unwrap();
                let range = input.byte_range();
                source[range.start..range.end].to_vec()
            };
            let sep = item
                .child(2)
                .unwrap()
                .utf8_text(source)
                .unwrap()
                .to_string();

            let output = {
                item.child(3)
                    .map(|item| item.utf8_text(source).unwrap())
                    .map(|item| {
                        // Remove all comments
                        let output = COMMENT_REGEX.replace_all(item, "").to_string();

                        // Normalize the whitespace in the expected output.
                        let output = WHITESPACE_REGEX.replace_all(output.trim(), " ");
                        output.replace(" )", ")")
                    })
                    .unwrap_or_default()
            };

            let has_fields = SEXP_FIELD_REGEX.is_match(&output);
            let header = item.child(0).unwrap();
            let header_delim_len = header
                .child(0)
                .unwrap()
                .utf8_text(source)
                .unwrap()
                .to_string();

            let name = header.child(1).unwrap().utf8_text(source).unwrap();
            let attributes = {
                header
                    .child(3)
                    .filter(|item| item.kind() == "attributes")
                    .map(|item| {
                        let mut attrs = TestAttributes::default();
                        for node in item.children(&mut item.walk()) {
                            if node.kind() != "attribute" {
                                continue;
                            }
                            if node.kind() == "_language" {
                                let language = node.child(2).unwrap().utf8_text(source).unwrap();
                                attrs.languages.push(language.to_string().into_boxed_str());
                            } else if node.kind() == "_platform" {
                                let node = node.child(2).unwrap().utf8_text(source).unwrap();
                                attrs.platform = node == std::env::consts::OS;
                            } else {
                                match node.utf8_text(source).unwrap() {
                                    ":skip" => {
                                        attrs.skip = true;
                                    }
                                    ":error" => {
                                        attrs.error = true;
                                    }
                                    ":fail-fast" => {
                                        attrs.fail_fast = true;
                                    }
                                    _ => unreachable!(),
                                }
                            }
                        }
                        attrs
                    })
                    .unwrap_or_default()
            };

            TestEntry::Example {
                name: name.to_string(),
                input,
                output,
                header: header_delim_len,
                divider_delim: sep,
                has_fields,
                attributes,
            }
        })
        .collect();

    TestEntry::Group {
        name,
        children,
        file_path,
    }
}

#[cfg(disable)]
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_test_content_simple() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r"
===============
The first test
===============

a b c

---

(a
    (b c))

================
The second test
================
d
---
(d)
        "
            .trim(),
            None,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                children: vec![
                    TestEntry::Example {
                        name: "The first test".to_string(),
                        input: b"\na b c\n".to_vec(),
                        output: "(a (b c))".to_string(),
                        header_delim_len: 15,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "The second test".to_string(),
                        input: b"d".to_vec(),
                        output: "(d)".to_string(),
                        header_delim_len: 16,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                ],
                file_path: None,
            }
        );
    }

    #[test]
    fn test_parse_test_content_with_dashes_in_source_code() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r"
==================
Code with dashes
==================
abc
---
defg
----
hijkl
-------

(a (b))

=========================
Code ending with dashes
=========================
abc
-----------
-------------------

(c (d))
        "
            .trim(),
            None,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                children: vec![
                    TestEntry::Example {
                        name: "Code with dashes".to_string(),
                        input: b"abc\n---\ndefg\n----\nhijkl".to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 7,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "Code ending with dashes".to_string(),
                        input: b"abc\n-----------".to_vec(),
                        output: "(c (d))".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 19,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                ],
                file_path: None,
            }
        );
    }

    #[test]
    fn test_format_sexp() {
        assert_eq!(format_sexp("", 0), "");
        assert_eq!(
            format_sexp("(a b: (c) (d) e: (f (g (h (MISSING i)))))", 0),
            r"
(a
  b: (c)
  (d)
  e: (f
    (g
      (h
        (MISSING i)))))
"
            .trim()
        );
        assert_eq!(
            format_sexp("(program (ERROR (UNEXPECTED ' ')) (identifier))", 0),
            r"
(program
  (ERROR
    (UNEXPECTED ' '))
  (identifier))
"
            .trim()
        );
        assert_eq!(
            format_sexp(r#"(source_file (MISSING ")"))"#, 0),
            r#"
(source_file
  (MISSING ")"))
        "#
            .trim()
        );
        assert_eq!(
            format_sexp(
                r"(source_file (ERROR (UNEXPECTED 'f') (UNEXPECTED '+')))",
                0
            ),
            r#"
(source_file
  (ERROR
    (UNEXPECTED 'f')
    (UNEXPECTED '+')))
"#
            .trim()
        );
    }

    #[test]
    fn test_write_tests_to_buffer() {
        let mut buffer = Vec::new();
        let corrected_entries = vec![
            (
                "title 1".to_string(),
                "input 1".to_string(),
                "output 1".to_string(),
                80,
                80,
            ),
            (
                "title 2".to_string(),
                "input 2".to_string(),
                "output 2".to_string(),
                80,
                80,
            ),
        ];
        write_tests_to_buffer(&mut buffer, &corrected_entries).unwrap();
        assert_eq!(
            String::from_utf8(buffer).unwrap(),
            r"
================================================================================
title 1
================================================================================
input 1
--------------------------------------------------------------------------------

output 1

================================================================================
title 2
================================================================================
input 2
--------------------------------------------------------------------------------

output 2
"
            .trim_start()
            .to_string()
        );
    }

    #[test]
    fn test_parse_test_content_with_comments_in_sexp() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r#"
==================
sexp with comment
==================
code
---

; Line start comment
(a (b))

==================
sexp with comment between
==================
code
---

; Line start comment
(a
; ignore this
    (b)
    ; also ignore this
)

=========================
sexp with ';'
=========================
code
---

(MISSING ";")
        "#
            .trim(),
            None,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                children: vec![
                    TestEntry::Example {
                        name: "sexp with comment".to_string(),
                        input: b"code".to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "sexp with comment between".to_string(),
                        input: b"code".to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "sexp with ';'".to_string(),
                        input: b"code".to_vec(),
                        output: "(MISSING \";\")".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    }
                ],
                file_path: None,
            }
        );
    }

    #[test]
    fn test_parse_test_content_with_suffixes() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r"
==================asdf\()[]|{}*+?^$.-
First test
==================asdf\()[]|{}*+?^$.-

=========================
NOT A TEST HEADER
=========================
-------------------------

---asdf\()[]|{}*+?^$.-

(a)

==================asdf\()[]|{}*+?^$.-
Second test
==================asdf\()[]|{}*+?^$.-

=========================
NOT A TEST HEADER
=========================
-------------------------

---asdf\()[]|{}*+?^$.-

(a)

=========================asdf\()[]|{}*+?^$.-
Test name with = symbol
=========================asdf\()[]|{}*+?^$.-

=========================
NOT A TEST HEADER
=========================
-------------------------

---asdf\()[]|{}*+?^$.-

(a)
        "
            .trim(),
            None,
        );

        let expected_input = b"\n=========================\n\
            NOT A TEST HEADER\n\
            =========================\n\
            -------------------------\n"
            .to_vec();
        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                children: vec![
                    TestEntry::Example {
                        name: "First test".to_string(),
                        input: expected_input.clone(),
                        output: "(a)".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "Second test".to_string(),
                        input: expected_input.clone(),
                        output: "(a)".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "Test name with = symbol".to_string(),
                        input: expected_input,
                        output: "(a)".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    }
                ],
                file_path: None,
            }
        );
    }

    #[test]
    fn test_parse_test_content_with_newlines_in_test_names() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r"
===============
name
with
newlines
===============
a
---
(b)

====================
name with === signs
====================
code with ----
---
(d)
",
            None,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                file_path: None,
                children: vec![
                    TestEntry::Example {
                        name: "name\nwith\nnewlines".to_string(),
                        input: b"a".to_vec(),
                        output: "(b)".to_string(),
                        header_delim_len: 15,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    },
                    TestEntry::Example {
                        name: "name with === signs".to_string(),
                        input: b"code with ----".to_vec(),
                        output: "(d)".to_string(),
                        header_delim_len: 20,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes::default(),
                    }
                ]
            }
        );
    }

    #[test]
    fn test_parse_test_with_markers() {
        // do one with :skip, we should not see it in the entry output

        let entry = parse_test_content(
            "the-filename".to_string(),
            r"
=====================
Test with skip marker
:skip
=====================
a
---
(b)
",
            None,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                file_path: None,
                children: vec![TestEntry::Example {
                    name: "Test with skip marker".to_string(),
                    input: b"a".to_vec(),
                    output: "(b)".to_string(),
                    header_delim_len: 21,
                    divider_delim_len: 3,
                    has_fields: false,
                    attributes: TestAttributes {
                        skip: true,
                        platform: true,
                        fail_fast: false,
                        error: false,
                        languages: vec!["".into()]
                    },
                }]
            }
        );

        let entry = parse_test_content(
            "the-filename".to_string(),
            &format!(
                r"
=========================
Test with platform marker
:platform({})
:fail-fast
=========================
a
---
(b)

=============================
Test with bad platform marker
:platform({})
:language(foo)
=============================
a
---
(b)
",
                std::env::consts::OS,
                if std::env::consts::OS == "linux" {
                    "macos"
                } else {
                    "linux"
                }
            ),
            None,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                file_path: None,
                children: vec![
                    TestEntry::Example {
                        name: "Test with platform marker".to_string(),
                        input: b"a".to_vec(),
                        output: "(b)".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes {
                            skip: false,
                            platform: true,
                            fail_fast: true,
                            error: false,
                            languages: vec!["".into()]
                        },
                    },
                    TestEntry::Example {
                        name: "Test with bad platform marker".to_string(),
                        input: b"a".to_vec(),
                        output: "(b)".to_string(),
                        header_delim_len: 29,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes: TestAttributes {
                            skip: false,
                            platform: false,
                            fail_fast: false,
                            error: false,
                            languages: vec!["foo".into()]
                        },
                    }
                ]
            }
        );
    }
}
