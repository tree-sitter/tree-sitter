use super::error::{Error, Result};
use super::util;
use ansi_term::Colour;
use difference::{Changeset, Difference};
use lazy_static::lazy_static;
use regex::bytes::{Regex as ByteRegex, RegexBuilder as ByteRegexBuilder};
use regex::Regex;
use std::char;
use std::fs;
use std::io::{self, Write};
use std::path::Path;
use std::str;
use tree_sitter::{Language, LogType, Parser, Query};

lazy_static! {
    static ref HEADER_REGEX: ByteRegex = ByteRegexBuilder::new(r"^===+\r?\n([^=]*)\r?\n===+\r?\n")
        .multi_line(true)
        .build()
        .unwrap();
    static ref DIVIDER_REGEX: ByteRegex = ByteRegexBuilder::new(r"^---+\r?\n")
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
        }
    }
}

pub fn run_tests_at_path(
    language: Language,
    path: &Path,
    debug: bool,
    debug_graph: bool,
    filter: Option<&str>,
) -> Result<()> {
    let test_entry = parse_tests(path)?;
    let mut _log_session = None;
    let mut parser = Parser::new();
    parser.set_language(language).map_err(|e| e.to_string())?;

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

    let mut failures = Vec::new();
    if let TestEntry::Group { children, .. } = test_entry {
        for child in children {
            run_tests(&mut parser, child, filter, 0, &mut failures)?;
        }
    }

    if failures.len() > 0 {
        println!("");

        if failures.len() == 1 {
            println!("1 failure:")
        } else {
            println!("{} failures:", failures.len())
        }

        print_diff_key();
        for (i, (name, actual, expected)) in failures.iter().enumerate() {
            println!("\n  {}. {}:", i + 1, name);
            print_diff(actual, expected);
        }
        Error::err(String::new())
    } else {
        Ok(())
    }
}

pub fn check_queries_at_path(language: Language, path: &Path) -> Result<()> {
    if path.exists() {
        for entry in fs::read_dir(path)? {
            let entry = entry?;
            let hidden = entry.file_name().to_str().unwrap_or("").starts_with(".");
            if !hidden {
                let content = fs::read_to_string(entry.path()).map_err(Error::wrap(|| {
                    format!("Error reading query file {:?}", entry.file_name())
                }))?;
                Query::new(language, &content).map_err(Error::wrap(|| {
                    format!("Error in query file {:?}", entry.file_name())
                }))?;
            }
        }
    }
    Ok(())
}

pub fn print_diff_key() {
    println!(
        "\n{} / {}",
        Colour::Green.paint("expected"),
        Colour::Red.paint("actual")
    );
}

pub fn print_diff(actual: &String, expected: &String) {
    let changeset = Changeset::new(actual, expected, " ");
    print!("    ");
    for diff in &changeset.diffs {
        match diff {
            Difference::Same(part) => {
                print!("{}{}", part, changeset.split);
            }
            Difference::Add(part) => {
                print!("{}{}", Colour::Green.paint(part), changeset.split);
            }
            Difference::Rem(part) => {
                print!("{}{}", Colour::Red.paint(part), changeset.split);
            }
        }
    }
    println!("");
}

fn run_tests(
    parser: &mut Parser,
    test_entry: TestEntry,
    filter: Option<&str>,
    mut indent_level: i32,
    failures: &mut Vec<(String, String, String)>,
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
                    return Ok(());
                }
            }
            let tree = parser.parse(&input, None).unwrap();
            let mut actual = tree.root_node().to_sexp();
            if !has_fields {
                actual = strip_sexp_fields(actual);
            }
            for _ in 0..indent_level {
                print!("  ");
            }
            if actual == output {
                println!("✓ {}", Colour::Green.paint(&name));
            } else {
                println!("✗ {}", Colour::Red.paint(&name));
                failures.push((name, actual, output));
            }
        }
        TestEntry::Group { name, children } => {
            for _ in 0..indent_level {
                print!("  ");
            }
            println!("{}:", name);
            indent_level += 1;
            for child in children {
                run_tests(parser, child, filter, indent_level, failures)?;
            }
        }
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
            let hidden = entry.file_name().to_str().unwrap_or("").starts_with(".");
            if !hidden {
                children.push(parse_tests(&entry.path())?);
            }
        }
        Ok(TestEntry::Group { name, children })
    } else {
        let content = fs::read_to_string(path)?;
        Ok(parse_test_content(name, content))
    }
}

pub fn strip_sexp_fields(sexp: String) -> String {
    SEXP_FIELD_REGEX.replace_all(&sexp, " (").to_string()
}

fn parse_test_content(name: String, content: String) -> TestEntry {
    let mut children = Vec::new();
    let bytes = content.as_bytes();
    let mut prev_name = String::new();
    let mut prev_header_end = 0;

    // Identify all of the test descriptions using the `======` headers.
    for (header_start, header_end) in HEADER_REGEX
        .find_iter(&bytes)
        .map(|m| (m.start(), m.end()))
        .chain(Some((bytes.len(), bytes.len())))
    {
        // Find the longest line of dashes following each test description.
        // That is the divider between input and expected output.
        if prev_header_end > 0 {
            let divider_match = DIVIDER_REGEX
                .find_iter(&bytes[prev_header_end..header_start])
                .map(|m| (prev_header_end + m.start(), prev_header_end + m.end()))
                .max_by_key(|(start, end)| end - start);
            if let Some((divider_start, divider_end)) = divider_match {
                if let Ok(output) = str::from_utf8(&bytes[divider_end..header_start]) {
                    let mut input = bytes[prev_header_end..divider_start].to_vec();

                    // Remove trailing newline from the input.
                    input.pop();
                    if input.last() == Some(&b'\r') {
                        input.pop();
                    }

                    // Normalize the whitespace in the expected output.
                    let output = WHITESPACE_REGEX.replace_all(output.trim(), " ").to_string();
                    let output = output.replace(" )", ")");

                    // Identify if the expected output has fields indicated. If not, then
                    // fields will not be checked.
                    let has_fields = SEXP_FIELD_REGEX.is_match(&output);

                    children.push(TestEntry::Example {
                        name: prev_name,
                        input,
                        output,
                        has_fields,
                    });
                }
            }
        }
        prev_name = String::from_utf8_lossy(&bytes[header_start..header_end])
            .trim_matches(|c| char::is_whitespace(c) || c == '=')
            .to_string();
        prev_header_end = header_end;
    }
    TestEntry::Group { name, children }
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
                ]
            }
        );
    }

    #[test]
    fn test_parse_test_content_with_dashes_in_source_code() {
        let entry = parse_test_content(
            "the-filename".to_string(),
            r#"
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
        "#
            .trim()
            .to_string(),
        );

        assert_eq!(
            entry,
            TestEntry::Group {
                name: "the-filename".to_string(),
                children: vec![
                    TestEntry::Example {
                        name: "Code with dashes".to_string(),
                        input: "abc\n---\ndefg\n----\nhijkl".as_bytes().to_vec(),
                        output: "(a (b))".to_string(),
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "Code ending with dashes".to_string(),
                        input: "abc\n-----------".as_bytes().to_vec(),
                        output: "(c (d))".to_string(),
                        has_fields: false,
                    },
                ]
            }
        );
    }
}
