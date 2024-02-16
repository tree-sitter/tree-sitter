use super::util;
use ansi_term::Colour;
use anyhow::{anyhow, Context, Result};
use difference::{Changeset, Difference};
use lazy_static::lazy_static;
use regex::bytes::{Regex as ByteRegex, RegexBuilder as ByteRegexBuilder};
use regex::Regex;
use std::ffi::OsStr;
use std::fmt::Write as FmtWrite;
use std::fs;
use std::io::{self, Write};
use std::path::{Path, PathBuf};
use std::str;
use tree_sitter::{Language, LogType, Parser, Query};
use walkdir::WalkDir;

lazy_static! {
    static ref HEADER_REGEX: ByteRegex =
        ByteRegexBuilder::new(r"^(?P<equals>(?:=+){3,})(?P<suffix1>[^=\r\n][^\r\n]*)?\r?\n(?P<test_name>([^=\r\n][^\r\n]*\r?\n)+)===+(?P<suffix2>[^=\r\n][^\r\n]*)?\r?\n")
            .multi_line(true)
            .build()
            .unwrap();
    static ref DIVIDER_REGEX: ByteRegex = ByteRegexBuilder::new(r"^(?P<hyphens>(?:-+){3,})(?P<suffix>[^-\r\n][^\r\n]*)?\r?\n")
        .multi_line(true)
        .build()
        .unwrap();
    static ref COMMENT_REGEX: Regex = Regex::new(r"(?m)^\s*;.*$").unwrap();
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
        header_delim_len: usize,
        divider_delim_len: usize,
        has_fields: bool,
    },
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

pub struct TestOptions<'a> {
    pub path: PathBuf,
    pub debug: bool,
    pub debug_graph: bool,
    pub filter: Option<&'a str>,
    pub include: Option<Regex>,
    pub exclude: Option<Regex>,
    pub update: bool,
    pub open_log: bool,
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
    run_tests(
        parser,
        test_entry,
        opts,
        0,
        &mut failures,
        &mut corrected_entries,
    )?;

    parser.stop_printing_dot_graphs();

    if failures.is_empty() {
        Ok(())
    } else {
        println!();

        if opts.update {
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
            if failures.len() == 1 {
                println!("1 failure:");
            } else {
                println!("{} failures:", failures.len());
            }

            print_diff_key();
            for (i, (name, actual, expected)) in failures.iter().enumerate() {
                println!("\n  {}. {name}:", i + 1);
                let actual = format_sexp_indented(actual, 2);
                let expected = format_sexp_indented(expected, 2);
                print_diff(&actual, &expected);
            }
            Err(anyhow!(""))
        }
    }
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
        "\n{} / {} / {}",
        Colour::White.paint("correct"),
        Colour::Green.paint("expected"),
        Colour::Red.paint("unexpected")
    );
}

pub fn print_diff(actual: &str, expected: &str) {
    let changeset = Changeset::new(actual, expected, "\n");
    for diff in &changeset.diffs {
        match diff {
            Difference::Same(part) => {
                print!("{part}{}", changeset.split);
            }
            Difference::Add(part) => {
                print!("{}{}", Colour::Green.paint(part), changeset.split);
            }
            Difference::Rem(part) => {
                print!("{}{}", Colour::Red.paint(part), changeset.split);
            }
        }
    }
    println!();
}

fn run_tests(
    parser: &mut Parser,
    test_entry: TestEntry,
    opts: &mut TestOptions,
    mut indent_level: i32,
    failures: &mut Vec<(String, String, String)>,
    corrected_entries: &mut Vec<(String, String, String, usize, usize)>,
) -> Result<()> {
    match test_entry {
        TestEntry::Example {
            name,
            input,
            output,
            header_delim_len,
            divider_delim_len,
            has_fields,
        } => {
            let tree = parser.parse(&input, None).unwrap();
            let mut actual = tree.root_node().to_sexp();
            if !has_fields {
                actual = strip_sexp_fields(&actual);
            }
            print!("{}", "  ".repeat(indent_level as usize));
            if actual == output {
                println!("✓ {}", Colour::Green.paint(&name));
                if opts.update {
                    let input = String::from_utf8(input).unwrap();
                    let output = format_sexp(&output);
                    corrected_entries.push((
                        name,
                        input,
                        output,
                        header_delim_len,
                        divider_delim_len,
                    ));
                }
            } else {
                if opts.update {
                    let input = String::from_utf8(input).unwrap();
                    let output = format_sexp(&actual);
                    corrected_entries.push((
                        name.clone(),
                        input,
                        output,
                        header_delim_len,
                        divider_delim_len,
                    ));
                    println!("✓ {}", Colour::Blue.paint(&name));
                } else {
                    println!("✗ {}", Colour::Red.paint(&name));
                }
                failures.push((name, actual, output));
            }
        }
        TestEntry::Group {
            name,
            mut children,
            file_path,
        } => {
            children.retain(|child| {
                if let TestEntry::Example { name, .. } = child {
                    if let Some(filter) = opts.filter {
                        if !name.contains(filter) {
                            return false;
                        }
                    }
                    if let Some(include) = &opts.include {
                        if !include.is_match(name) {
                            return false;
                        }
                    }
                    if let Some(exclude) = &opts.exclude {
                        if exclude.is_match(name) {
                            return false;
                        }
                    }
                }
                true
            });

            if children.is_empty() {
                return Ok(());
            }

            if indent_level > 0 {
                print!("{}", "  ".repeat(indent_level as usize));
                println!("{name}:");
            }

            let failure_count = failures.len();

            indent_level += 1;
            for child in children {
                run_tests(
                    parser,
                    child,
                    opts,
                    indent_level,
                    failures,
                    corrected_entries,
                )?;
            }

            if let Some(file_path) = file_path {
                if opts.update && failures.len() - failure_count > 0 {
                    write_tests(&file_path, corrected_entries)?;
                }
                corrected_entries.clear();
            }
        }
    }
    Ok(())
}

fn format_sexp(sexp: &str) -> String {
    format_sexp_indented(sexp, 0)
}

fn format_sexp_indented(sexp: &str, initial_indent_level: u32) -> String {
    let mut formatted = String::new();

    if sexp.is_empty() {
        return formatted;
    }

    let mut indent_level = initial_indent_level;
    let mut has_field = false;

    let mut c_iter = sexp.chars().peekable();
    let mut s = String::with_capacity(sexp.len());
    let mut quote = '\0';
    let mut saw_paren = false;
    let mut did_last = false;

    let mut fetch_next_str = |next: &mut String| {
        next.clear();
        while let Some(c) = c_iter.next() {
            if c == '\'' || c == '"' {
                quote = c;
            } else if c == ' ' || (c == ')' && quote != '\0') {
                if let Some(next_c) = c_iter.peek() {
                    if *next_c == quote {
                        next.push(c);
                        next.push(*next_c);
                        c_iter.next();
                        quote = '\0';
                        continue;
                    }
                }
                break;
            }
            if c == ')' {
                saw_paren = true;
                break;
            }
            next.push(c);
        }

        // at the end
        if c_iter.peek().is_none() && next.is_empty() {
            if saw_paren {
                // but did we see a ) before ending?
                saw_paren = false;
                return Some(());
            }
            if !did_last {
                // but did we account for the end empty string as if we're splitting?
                did_last = true;
                return Some(());
            }
            return None;
        }
        Some(())
    };

    while fetch_next_str(&mut s).is_some() {
        if s.is_empty() && indent_level > 0 {
            // ")"
            indent_level -= 1;
            write!(formatted, ")").unwrap();
        } else if s.starts_with('(') {
            if has_field {
                has_field = false;
            } else {
                if indent_level > 0 {
                    writeln!(formatted).unwrap();
                    for _ in 0..indent_level {
                        write!(formatted, "  ").unwrap();
                    }
                }
                indent_level += 1;
            }

            // "(node_name"
            write!(formatted, "{s}").unwrap();

            // "(MISSING node_name" or "(UNEXPECTED 'x'"
            if s.starts_with("(MISSING") || s.starts_with("(UNEXPECTED") {
                fetch_next_str(&mut s).unwrap();
                write!(formatted, " {s}").unwrap();
            }
        } else if s.ends_with(':') {
            // "field:"
            writeln!(formatted).unwrap();
            for _ in 0..indent_level {
                write!(formatted, "  ").unwrap();
            }
            write!(formatted, "{s} ").unwrap();
            has_field = true;
            indent_level += 1;
        }
    }

    formatted
}

fn write_tests(
    file_path: &Path,
    corrected_entries: &[(String, String, String, usize, usize)],
) -> Result<()> {
    let mut buffer = fs::File::create(file_path)?;
    write_tests_to_buffer(&mut buffer, corrected_entries)
}

fn write_tests_to_buffer(
    buffer: &mut impl Write,
    corrected_entries: &[(String, String, String, usize, usize)],
) -> Result<()> {
    for (i, (name, input, output, header_delim_len, divider_delim_len)) in
        corrected_entries.iter().enumerate()
    {
        if i > 0 {
            writeln!(buffer)?;
        }
        write!(
            buffer,
            "{}\n{name}\n{}\n{input}\n{}\n\n{}\n",
            "=".repeat(*header_delim_len),
            "=".repeat(*header_delim_len),
            "-".repeat(*divider_delim_len),
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

fn parse_test_content(name: String, content: &str, file_path: Option<PathBuf>) -> TestEntry {
    let mut children = Vec::new();
    let bytes = content.as_bytes();
    let mut prev_name = String::new();
    let mut prev_header_end = 0;

    // Find the first test header in the file, and determine if it has a
    // custom suffix. If so, then this suffix will be used to identify
    // all subsequent headers and divider lines in the file.
    let first_suffix = HEADER_REGEX
        .captures(bytes)
        .and_then(|c| c.name("suffix1"))
        .map(|m| String::from_utf8_lossy(m.as_bytes()));

    // Find all of the `===` test headers, which contain the test names.
    // Ignore any matches whose suffix does not match the first header
    // suffix in the file.
    let header_matches = HEADER_REGEX.captures_iter(bytes).filter_map(|c| {
        let header_delim_len = c.name("equals").map_or(80, |m| m.as_bytes().len());
        let suffix1 = c
            .name("suffix1")
            .map(|m| String::from_utf8_lossy(m.as_bytes()));
        let suffix2 = c
            .name("suffix2")
            .map(|m| String::from_utf8_lossy(m.as_bytes()));
        if suffix1 == first_suffix && suffix2 == first_suffix {
            let header_range = c.get(0).unwrap().range();
            let test_name = c
                .name("test_name")
                .map(|c| String::from_utf8_lossy(c.as_bytes()).trim_end().to_string());
            Some((header_delim_len, header_range, test_name))
        } else {
            None
        }
    });

    let mut prev_header_len = 80;
    for (header_delim_len, header_range, test_name) in
        header_matches.chain(Some((80, bytes.len()..bytes.len(), None)))
    {
        // Find the longest line of dashes following each test description. That line
        // separates the input from the expected output. Ignore any matches whose suffix
        // does not match the first suffix in the file.
        if prev_header_end > 0 {
            let divider_range = DIVIDER_REGEX
                .captures_iter(&bytes[prev_header_end..header_range.start])
                .filter_map(|m| {
                    let divider_delim_len = m.name("hyphens").map_or(80, |m| m.as_bytes().len());
                    let suffix = m
                        .name("suffix")
                        .map(|m| String::from_utf8_lossy(m.as_bytes()));
                    if suffix == first_suffix {
                        let range = m.get(0).unwrap().range();
                        Some((
                            divider_delim_len,
                            (prev_header_end + range.start)..(prev_header_end + range.end),
                        ))
                    } else {
                        None
                    }
                })
                .max_by_key(|(_, range)| range.len());

            if let Some((divider_delim_len, divider_range)) = divider_range {
                if let Ok(output) = str::from_utf8(&bytes[divider_range.end..header_range.start]) {
                    let mut input = bytes[prev_header_end..divider_range.start].to_vec();

                    // Remove trailing newline from the input.
                    input.pop();
                    if input.last() == Some(&b'\r') {
                        input.pop();
                    }

                    // Remove all comments
                    let output = COMMENT_REGEX.replace_all(output, "").to_string();

                    // Normalize the whitespace in the expected output.
                    let output = WHITESPACE_REGEX.replace_all(output.trim(), " ");
                    let output = output.replace(" )", ")");

                    // Identify if the expected output has fields indicated. If not, then
                    // fields will not be checked.
                    let has_fields = SEXP_FIELD_REGEX.is_match(&output);

                    children.push(TestEntry::Example {
                        name: prev_name,
                        input,
                        output,
                        header_delim_len: prev_header_len,
                        divider_delim_len,
                        has_fields,
                    });
                }
            }
        }
        prev_name = test_name.unwrap_or(String::new());
        prev_header_len = header_delim_len;
        prev_header_end = header_range.end;
    }
    TestEntry::Group {
        name,
        children,
        file_path,
    }
}

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
                        input: "\na b c\n".as_bytes().to_vec(),
                        output: "(a (b c))".to_string(),
                        header_delim_len: 15,
                        divider_delim_len: 3,
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "The second test".to_string(),
                        input: "d".as_bytes().to_vec(),
                        output: "(d)".to_string(),
                        header_delim_len: 16,
                        divider_delim_len: 3,
                        has_fields: false,
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
                        input: "abc\n---\ndefg\n----\nhijkl".as_bytes().to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 7,
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "Code ending with dashes".to_string(),
                        input: "abc\n-----------".as_bytes().to_vec(),
                        output: "(c (d))".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 19,
                        has_fields: false,
                    },
                ],
                file_path: None,
            }
        );
    }

    #[test]
    fn test_format_sexp() {
        assert_eq!(format_sexp(""), "");
        assert_eq!(
            format_sexp("(a b: (c) (d) e: (f (g (h (MISSING i)))))"),
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
        assert_eq!(format_sexp("()"), "()");
        assert_eq!(format_sexp("(A (M (B)))"), "(A\n  (M\n    (B)))");
        assert_eq!(format_sexp("(A (U (B)))"), "(A\n  (U\n    (B)))");
        assert_eq!(
            format_sexp("(program (ERROR (UNEXPECTED ' ')) (identifier))"),
            r"
(program
  (ERROR
    (UNEXPECTED ' '))
  (identifier))
"
            .trim()
        );
        assert_eq!(
            format_sexp(r#"(source_file (MISSING ")"))"#),
            r#"
(source_file
  (MISSING ")"))
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
                        input: "code".as_bytes().to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "sexp with comment between".to_string(),
                        input: "code".as_bytes().to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "sexp with ';'".to_string(),
                        input: "code".as_bytes().to_vec(),
                        output: "(MISSING \";\")".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
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

        let expected_input = "\n=========================\n\
            NOT A TEST HEADER\n\
            =========================\n\
            -------------------------\n"
            .as_bytes()
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
                    },
                    TestEntry::Example {
                        name: "Second test".to_string(),
                        input: expected_input.clone(),
                        output: "(a)".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                    },
                    TestEntry::Example {
                        name: "Test name with = symbol".to_string(),
                        input: expected_input,
                        output: "(a)".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
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
                    },
                    TestEntry::Example {
                        name: "name with === signs".to_string(),
                        input: b"code with ----".to_vec(),
                        output: "(d)".to_string(),
                        header_delim_len: 20,
                        divider_delim_len: 3,
                        has_fields: false,
                    }
                ]
            }
        );
    }
}
