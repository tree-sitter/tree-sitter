use super::error::{Error, Result};
use super::print::print_tree;
use super::util;
use ansi_term::Colour;
use difference::{Changeset, Difference};
use lazy_static::lazy_static;
use regex::bytes::{Regex as ByteRegex, RegexBuilder as ByteRegexBuilder};
use regex::Regex;
use std::char;
use std::fs;
use std::io::{self, Write};
use std::path::{Path, PathBuf};
use std::str;
use tree_sitter::{Language, LogType, Parser};

lazy_static! {
    static ref HEADER_REGEX: ByteRegex = ByteRegexBuilder::new(r"^===+\r?\n([^=]*)\r?\n===+\r?\n")
        .multi_line(true)
        .build()
        .unwrap();
    static ref DIVIDER_REGEX: ByteRegex = ByteRegexBuilder::new(r"\r?\n---+\r?\n")
        .multi_line(true)
        .build()
        .unwrap();
    static ref WHITESPACE_REGEX: Regex = Regex::new(r"\s+").unwrap();
    static ref SEXP_FIELD_REGEX: Regex = Regex::new(r" \w+: \(").unwrap();
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
        has_fields: bool,
    },
}

impl Default for TestEntry {
    fn default() -> Self {
        TestEntry::Group {
            name: String::new(),
            children: Vec::new(),
            file_path: None,
        }
    }
}

pub fn run_tests_at_path(
    language: Language,
    path: &Path,
    debug: bool,
    debug_graph: bool,
    filter: Option<&str>,
    update: bool,
) -> Result<()> {
    let test_entry = parse_tests(path, false)?;
    let mut _log_session = None;
    let mut parser = Parser::new();
    parser.set_language(language).map_err(|e| e.to_string())?;

    if !update {
        if debug_graph {
            _log_session = Some(util::log_graphs(&mut parser, "log.html")?);
        } else if debug {
            parser.set_logger(Some(Box::new(|log_type, message| {
                if log_type == LogType::Lex {
                    io::stderr().write(b"  ").unwrap();
                }
                write!(&mut io::stderr(), "{}\n", message).unwrap();
            })));
        }
    }

    let mut diffs = Vec::new();
    let mut update_entries = Vec::new();
    run_tests(&mut parser, test_entry, filter, update, &mut update_entries, -1, &mut diffs)?;

    if diffs.len() > 0 {
        println!("");

        let diff_name = if update { "update" } else { "failure" };
        if diffs.len() == 1 {
            println!("1 {}:", diff_name)
        } else {
            println!("{} {}s:", diffs.len(), diff_name)
        }

        if update {
            print_update_diff_key();
        } else {
            print_diff_key();
        }
        for (i, (name, parsed, provided)) in diffs.iter().enumerate() {
            println!("\n  {}. {}:", i + 1, name);
            if update {
                print_update_diff(provided, parsed);
            } else {
                print_diff(parsed, provided);
            }
        }
        Error::err(String::new())
    } else {
        Ok(())
    }
}

pub fn print_diff_key() {
    print_diff_key_with_colors("actual", "expected", Colour::Red, Colour::Green);
}

fn print_update_diff_key() {
    print_diff_key_with_colors("original", "updated", Colour::Yellow, Colour::Green);
}

fn print_diff_key_with_colors(
    actual_name: &str,
    expected_name: &str,
    actual_color: Colour,
    expected_color: Colour,
) {
    println!(
        "\n{} / {}",
        expected_color.paint(expected_name),
        actual_color.paint(actual_name)
    );
}

pub fn print_diff(actual: &String, expected: &String) {
    print_diff_with_colors(actual, expected, Colour::Red, Colour::Green);
}

fn print_update_diff(actual: &String, expected: &String) {
    print_diff_with_colors(actual, expected, Colour::Yellow, Colour::Green);
}

fn print_diff_with_colors(
    actual: &String,
    expected: &String,
    actual_color: Colour,
    expected_color: Colour,
) {
    let changeset = Changeset::new(actual, expected, " ");
    print!("    ");
    for diff in &changeset.diffs {
        match diff {
            Difference::Same(part) => {
                print!("{}{}", part, changeset.split);
            }
            Difference::Add(part) => {
                print!("{}{}", expected_color.paint(part), changeset.split);
            }
            Difference::Rem(part) => {
                print!("{}{}", actual_color.paint(part), changeset.split);
            }
        }
    }
    println!("");
}

fn run_tests(
    parser: &mut Parser,
    test_entry: TestEntry,
    filter: Option<&str>,
    update: bool,
    update_entries: &mut Vec<(String, String, String)>,
    mut indent_level: i32,
    diffs: &mut Vec<(String, String, String)>,
) -> Result<()> {
    match test_entry {
        TestEntry::Example {
            name,
            input,
            output,
            has_fields,
        } => {
            if let Some(filter) = filter {
                if !name.contains(filter) {
                    if update {
                        let input = String::from_utf8(input).unwrap();
                        update_entries.push((name, input, output));
                    }
                    return Ok(());
                }
            }
            let tree = parser.parse(&input, None).unwrap();
            let mut parsed = tree.root_node().to_sexp();
            if !has_fields {
                parsed = strip_sexp_fields(parsed);
            }
            for _ in 0..indent_level {
                print!("  ");
            }
            let provided = normalize_sexp(&output);
            if parsed == provided {
                println!("✓ {}", Colour::Green.paint(&name));
                if update {
                    let input = String::from_utf8(input).unwrap();
                    update_entries.push((name, input, output));
                }
            } else {
                if update {
                    let input = String::from_utf8(input).unwrap();
                    let mut fixed_output = Vec::new();
                    let mut cursor = tree.walk();
                    print_tree(&mut fixed_output, &mut cursor, false)?;
                    let fixed_output = String::from_utf8(fixed_output).unwrap();
                    update_entries.push((name.clone(), input, fixed_output));
                    println!("✓ {}", Colour::Yellow.paint(&name));
                } else {
                    println!("✗ {}", Colour::Red.paint(&name));
                }
                diffs.push((name, parsed, provided));
            }
        }
        TestEntry::Group { name, children, file_path } => {
            if indent_level >= 0 {
                for _ in 0..indent_level {
                    print!("  ");
                }
                println!("{}:", name);
            }

            let diff_count = diffs.len();

            indent_level += 1;
            for child in children {
                run_tests(parser, child, filter, update, update_entries, indent_level, diffs)?;
            }

            if let Some(file_path) = file_path {
                if update && diffs.len() - diff_count > 0 {
                    write_tests(&file_path, &update_entries)?;
                }
                update_entries.clear();
            }
        }
    }
    Ok(())
}

fn write_tests(file_path: &Path, update_entries: &Vec<(String, String, String)>) -> Result<()> {
    let mut buffer = fs::File::create(file_path)?;
    write_tests_to_buffer(&mut buffer, update_entries)
}

fn write_tests_to_buffer(
    buffer: &mut Write,
    update_entries: &Vec<(String, String, String)>,
) -> Result<()> {
    for (i, (name, input, output)) in update_entries.iter().enumerate() {
        if i > 0 {
            write!(buffer, "\n")?;
        }
        write!(
            buffer,
            "{}\n{}\n{}\n{}\n{}\n\n{}\n",
            "=".repeat(80),
            name,
            "=".repeat(80),
            input,
            "-".repeat(80),
            output.trim()
        )?;
    }
    Ok(())
}

pub fn parse_tests(path: &Path, norm_sexp: bool) -> io::Result<TestEntry> {
    let name = path
        .file_stem()
        .and_then(|s| s.to_str())
        .unwrap_or("")
        .to_string();
    if path.is_dir() {
        let mut children = Vec::new();
        for entry in fs::read_dir(path)? {
            let entry = entry?;
            let hidden = entry
                .file_name()
                .to_str()
                .unwrap_or("")
                .starts_with(".");
            if !hidden {
                children.push(parse_tests(&entry.path(), norm_sexp)?);
            }
        }
        Ok(TestEntry::Group { name, children, file_path: None })
    } else {
        let content = fs::read_to_string(path)?;
        Ok(parse_test_content(name, content, Some(path.to_path_buf()), norm_sexp))
    }
}

pub fn strip_sexp_fields(sexp: String) -> String {
    SEXP_FIELD_REGEX.replace_all(&sexp, " (").to_string()
}

fn parse_test_content(
    name: String,
    content: String,
    file_path: Option<PathBuf>,
    norm_sexp: bool,
) -> TestEntry {
    let mut children = Vec::new();
    let bytes = content.as_bytes();
    let mut previous_name = String::new();
    let mut previous_header_end = 0;
    for header_match in HEADER_REGEX
        .find_iter(&bytes)
        .map(|m| (m.start(), m.end()))
        .chain(Some((bytes.len(), bytes.len())))
    {
        let (header_start, header_end) = header_match;
        if previous_header_end > 0 {
            if let Some(divider_match) =
                DIVIDER_REGEX.find(&bytes[previous_header_end..header_start])
            {
                let (divider_start, divider_end) = (
                    previous_header_end + divider_match.start(),
                    previous_header_end + divider_match.end(),
                );
                if let Ok(output) = str::from_utf8(&bytes[divider_end..header_start]) {
                    let input = bytes[previous_header_end..divider_start].to_vec();
                    let output = if norm_sexp {
                        normalize_sexp(output)
                    } else {
                        output.to_owned()
                    };
                    let has_fields = SEXP_FIELD_REGEX.is_match(&output);
                    children.push(TestEntry::Example {
                        name: previous_name,
                        input,
                        output,
                        has_fields,
                    });
                }
            }
        }
        previous_name = String::from_utf8_lossy(&bytes[header_start..header_end])
            .trim_matches(|c| char::is_whitespace(c) || c == '=')
            .to_string();
        previous_header_end = header_end;
    }
    TestEntry::Group { name, children, file_path }
}

fn normalize_sexp(sexp: &str) -> String {
    let sexp = WHITESPACE_REGEX.replace_all(sexp.trim(), " ").to_string();
    let sexp = sexp.replace(" )", ")");
    return sexp;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_test_content() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r#"
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
        "#
            .trim()
            .to_string(),
            None,
            true,
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                children: vec![
                    TestEntry::Example {
                        name: "The first test".to_string(),
                        input: "\na b c\n".as_bytes().to_vec(),
                        output: "(a (b c))".to_string(),
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "The second test".to_string(),
                        input: "d".as_bytes().to_vec(),
                        output: "(d)".to_string(),
                        has_fields: false,
                    },
                ],
                file_path: None
            }
        );
    }

    #[test]
    fn test_write_tests_to_buffer() {
        let mut buffer = Vec::new();
        let update_entries = vec![
            (
                "title 1".to_string(),
                "input 1".to_string(),
                "output 1".to_string(),
            ),
            (
                "title 2".to_string(),
                "input 2".to_string(),
                "output 2".to_string(),
            ),
        ];
        write_tests_to_buffer(&mut buffer, &update_entries).unwrap();
        assert_eq!(
            String::from_utf8(buffer).unwrap(),
            r#"
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
"#
            .trim_start()
            .to_string()
        );
    }
}
