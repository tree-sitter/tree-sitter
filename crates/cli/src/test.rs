use std::{
    collections::BTreeMap,
    ffi::OsStr,
    fmt::Display as _,
    fs,
    io::{self, Write},
    path::{Path, PathBuf},
    str,
    sync::LazyLock,
    time::Duration,
};

use anstyle::AnsiColor;
use anyhow::{anyhow, Context, Result};
use clap::ValueEnum;
use indoc::indoc;
use regex::{
    bytes::{Regex as ByteRegex, RegexBuilder as ByteRegexBuilder},
    Regex,
};
use schemars::{JsonSchema, Schema, SchemaGenerator};
use serde::Serialize;
use similar::{ChangeTag, TextDiff};
use tree_sitter::{format_sexp, Language, LogType, Parser, Query, Tree};
use walkdir::WalkDir;

use super::util;
use crate::{
    logger::paint,
    parse::{
        render_cst, ParseDebugType, ParseFileOptions, ParseOutput, ParseStats, ParseTheme, Stats,
    },
};

static HEADER_REGEX: LazyLock<ByteRegex> = LazyLock::new(|| {
    ByteRegexBuilder::new(
        r"^(?x)
           (?P<equals>(?:=+){3,})
           (?P<suffix1>[^=\r\n][^\r\n]*)?
           \r?\n
           (?P<test_name_and_markers>(?:([^=\r\n]|\s+:)[^\r\n]*\r?\n)+)
           ===+
           (?P<suffix2>[^=\r\n][^\r\n]*)?\r?\n",
    )
    .multi_line(true)
    .build()
    .unwrap()
});

static DIVIDER_REGEX: LazyLock<ByteRegex> = LazyLock::new(|| {
    ByteRegexBuilder::new(r"^(?P<hyphens>(?:-+){3,})(?P<suffix>[^-\r\n][^\r\n]*)?\r?\n")
        .multi_line(true)
        .build()
        .unwrap()
});

static COMMENT_REGEX: LazyLock<Regex> = LazyLock::new(|| Regex::new(r"(?m)^\s*;.*$").unwrap());

static WHITESPACE_REGEX: LazyLock<Regex> = LazyLock::new(|| Regex::new(r"\s+").unwrap());

static SEXP_FIELD_REGEX: LazyLock<Regex> = LazyLock::new(|| Regex::new(r" \w+: \(").unwrap());

static POINT_REGEX: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r"\s*\[\s*\d+\s*,\s*\d+\s*\]\s*").unwrap());

#[derive(Debug, PartialEq, Eq)]
pub enum TestEntry {
    Group {
        name: String,
        children: Vec<Self>,
        file_path: Option<PathBuf>,
    },
    Example {
        name: String,
        input: Vec<u8>,
        output: String,
        header_delim_len: usize,
        divider_delim_len: usize,
        has_fields: bool,
        attributes_str: String,
        attributes: TestAttributes,
        file_name: Option<String>,
    },
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TestAttributes {
    pub skip: bool,
    pub platform: bool,
    pub fail_fast: bool,
    pub error: bool,
    pub cst: bool,
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
            cst: false,
            languages: vec!["".into()],
        }
    }
}

#[derive(ValueEnum, Default, Debug, Copy, Clone, PartialEq, Eq, Serialize)]
pub enum TestStats {
    All,
    #[default]
    OutliersAndTotal,
    TotalOnly,
}

pub struct TestOptions<'a> {
    pub path: PathBuf,
    pub debug: bool,
    pub debug_graph: bool,
    pub include: Option<Regex>,
    pub exclude: Option<Regex>,
    pub file_name: Option<String>,
    pub update: bool,
    pub open_log: bool,
    pub languages: BTreeMap<&'a str, &'a Language>,
    pub color: bool,
    pub show_fields: bool,
    pub overview_only: bool,
}

/// A stateful object used to collect results from running a grammar's test suite
#[derive(Debug, Default, Serialize, JsonSchema)]
pub struct TestSummary {
    // Parse test results and associated data
    #[schemars(schema_with = "schema_as_array")]
    #[serde(serialize_with = "serialize_as_array")]
    pub parse_results: TestResultHierarchy,
    pub parse_failures: Vec<TestFailure>,
    pub parse_stats: Stats,
    #[schemars(skip)]
    #[serde(skip)]
    pub has_parse_errors: bool,
    #[schemars(skip)]
    #[serde(skip)]
    pub parse_stat_display: TestStats,

    // Other test results
    #[schemars(schema_with = "schema_as_array")]
    #[serde(serialize_with = "serialize_as_array")]
    pub highlight_results: TestResultHierarchy,
    #[schemars(schema_with = "schema_as_array")]
    #[serde(serialize_with = "serialize_as_array")]
    pub tag_results: TestResultHierarchy,
    #[schemars(schema_with = "schema_as_array")]
    #[serde(serialize_with = "serialize_as_array")]
    pub query_results: TestResultHierarchy,

    // Data used during construction
    #[schemars(skip)]
    #[serde(skip)]
    pub test_num: usize,
    // Options passed in from the CLI which control how the summary is displayed
    #[schemars(skip)]
    #[serde(skip)]
    pub color: bool,
    #[schemars(skip)]
    #[serde(skip)]
    pub overview_only: bool,
    #[schemars(skip)]
    #[serde(skip)]
    pub update: bool,
    #[schemars(skip)]
    #[serde(skip)]
    pub json: bool,
}

impl TestSummary {
    #[must_use]
    pub fn new(
        color: bool,
        stat_display: TestStats,
        parse_update: bool,
        overview_only: bool,
        json_summary: bool,
    ) -> Self {
        Self {
            color,
            parse_stat_display: stat_display,
            update: parse_update,
            overview_only,
            json: json_summary,
            test_num: 1,
            ..Default::default()
        }
    }
}

#[derive(Debug, Default, JsonSchema)]
pub struct TestResultHierarchy {
    root_group: Vec<TestResult>,
    traversal_idxs: Vec<usize>,
}

fn serialize_as_array<S>(results: &TestResultHierarchy, serializer: S) -> Result<S::Ok, S::Error>
where
    S: serde::Serializer,
{
    results.root_group.serialize(serializer)
}

fn schema_as_array(gen: &mut SchemaGenerator) -> Schema {
    gen.subschema_for::<Vec<TestResult>>()
}

/// Stores arbitrarily nested parent test groups and child cases. Supports creation
/// in DFS traversal order
impl TestResultHierarchy {
    /// Signifies the start of a new group's traversal during construction.
    fn push_traversal(&mut self, idx: usize) {
        self.traversal_idxs.push(idx);
    }

    /// Signifies the end of the current group's traversal during construction.
    /// Must be paired with a prior call to [`TestResultHierarchy::add_group`].
    pub fn pop_traversal(&mut self) {
        self.traversal_idxs.pop();
    }

    /// Adds a new group as a child of the current group. Caller is responsible
    /// for calling [`TestResultHierarchy::pop_traversal`] once the group is done
    /// being traversed.
    pub fn add_group(&mut self, group_name: &str) {
        let new_group_idx = self.curr_group_len();
        self.push(TestResult {
            name: group_name.to_string(),
            info: TestInfo::Group {
                children: Vec::new(),
            },
        });
        self.push_traversal(new_group_idx);
    }

    /// Adds a new test example as a child of the current group.
    /// Asserts that `test_case.info` is not [`TestInfo::Group`].
    pub fn add_case(&mut self, test_case: TestResult) {
        assert!(!matches!(test_case.info, TestInfo::Group { .. }));
        self.push(test_case);
    }

    /// Adds a new `TestResult` to the current group.
    fn push(&mut self, result: TestResult) {
        // If there are no traversal steps, we're adding to the root
        if self.traversal_idxs.is_empty() {
            self.root_group.push(result);
            return;
        }

        #[allow(clippy::manual_let_else)]
        let mut curr_group = match self.root_group[self.traversal_idxs[0]].info {
            TestInfo::Group { ref mut children } => children,
            _ => unreachable!(),
        };
        for idx in self.traversal_idxs.iter().skip(1) {
            curr_group = match curr_group[*idx].info {
                TestInfo::Group { ref mut children } => children,
                _ => unreachable!(),
            };
        }

        curr_group.push(result);
    }

    fn curr_group_len(&self) -> usize {
        if self.traversal_idxs.is_empty() {
            return self.root_group.len();
        }

        #[allow(clippy::manual_let_else)]
        let mut curr_group = match self.root_group[self.traversal_idxs[0]].info {
            TestInfo::Group { ref children } => children,
            _ => unreachable!(),
        };
        for idx in self.traversal_idxs.iter().skip(1) {
            curr_group = match curr_group[*idx].info {
                TestInfo::Group { ref children } => children,
                _ => unreachable!(),
            };
        }
        curr_group.len()
    }

    #[allow(clippy::iter_without_into_iter)]
    #[must_use]
    pub fn iter(&self) -> TestResultIterWithDepth<'_> {
        let mut stack = Vec::with_capacity(self.root_group.len());
        for child in self.root_group.iter().rev() {
            stack.push((0, child));
        }
        TestResultIterWithDepth { stack }
    }
}

pub struct TestResultIterWithDepth<'a> {
    stack: Vec<(usize, &'a TestResult)>,
}

impl<'a> Iterator for TestResultIterWithDepth<'a> {
    type Item = (usize, &'a TestResult);

    fn next(&mut self) -> Option<Self::Item> {
        self.stack.pop().inspect(|(depth, result)| {
            if let TestInfo::Group { children } = &result.info {
                for child in children.iter().rev() {
                    self.stack.push((depth + 1, child));
                }
            }
        })
    }
}

#[derive(Debug, Serialize, JsonSchema)]
pub struct TestResult {
    pub name: String,
    #[schemars(flatten)]
    #[serde(flatten)]
    pub info: TestInfo,
}

#[derive(Debug, Serialize, JsonSchema)]
#[schemars(untagged)]
#[serde(untagged)]
pub enum TestInfo {
    Group {
        children: Vec<TestResult>,
    },
    ParseTest {
        outcome: TestOutcome,
        // True parse rate, adjusted parse rate
        #[schemars(schema_with = "parse_rate_schema")]
        #[serde(serialize_with = "serialize_parse_rates")]
        parse_rate: Option<(f64, f64)>,
        test_num: usize,
    },
    AssertionTest {
        outcome: TestOutcome,
        test_num: usize,
    },
}

fn serialize_parse_rates<S>(
    parse_rate: &Option<(f64, f64)>,
    serializer: S,
) -> Result<S::Ok, S::Error>
where
    S: serde::Serializer,
{
    match parse_rate {
        None => serializer.serialize_none(),
        Some((first, _)) => serializer.serialize_some(first),
    }
}

fn parse_rate_schema(gen: &mut SchemaGenerator) -> Schema {
    gen.subschema_for::<Option<f64>>()
}

#[derive(Debug, Clone, Eq, PartialEq, Serialize, JsonSchema)]
pub enum TestOutcome {
    // Parse outcomes
    Passed,
    Failed,
    Updated,
    Skipped,
    Platform,

    // Highlight/Tag/Query outcomes
    AssertionPassed { assertion_count: usize },
    AssertionFailed { error: String },
}

impl TestSummary {
    fn fmt_parse_results(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let (count, total_adj_parse_time) = self
            .parse_results
            .iter()
            .filter_map(|(_, result)| match result.info {
                TestInfo::Group { .. } => None,
                TestInfo::ParseTest { parse_rate, .. } => parse_rate,
                _ => unreachable!(),
            })
            .fold((0usize, 0.0f64), |(count, rate_accum), (_, adj_rate)| {
                (count + 1, rate_accum + adj_rate)
            });

        let avg = total_adj_parse_time / count as f64;
        let std_dev = {
            let variance = self
                .parse_results
                .iter()
                .filter_map(|(_, result)| match result.info {
                    TestInfo::Group { .. } => None,
                    TestInfo::ParseTest { parse_rate, .. } => parse_rate,
                    _ => unreachable!(),
                })
                .map(|(_, rate_i)| (rate_i - avg).powi(2))
                .sum::<f64>()
                / count as f64;
            variance.sqrt()
        };

        for (depth, entry) in self.parse_results.iter() {
            write!(f, "{}", "  ".repeat(depth + 1))?;
            match &entry.info {
                TestInfo::Group { .. } => writeln!(f, "{}:", entry.name)?,
                TestInfo::ParseTest {
                    outcome,
                    parse_rate,
                    test_num,
                } => {
                    let (color, result_char) = match outcome {
                        TestOutcome::Passed => (AnsiColor::Green, "✓"),
                        TestOutcome::Failed => (AnsiColor::Red, "✗"),
                        TestOutcome::Updated => (AnsiColor::Blue, "✓"),
                        TestOutcome::Skipped => (AnsiColor::Yellow, "⌀"),
                        TestOutcome::Platform => (AnsiColor::Magenta, "⌀"),
                        _ => unreachable!(),
                    };
                    let stat_display = match (self.parse_stat_display, parse_rate) {
                        (TestStats::TotalOnly, _) | (_, None) => String::new(),
                        (display, Some((true_rate, adj_rate))) => {
                            let mut stats = if display == TestStats::All {
                                format!(" ({true_rate:.3} bytes/ms)")
                            } else {
                                String::new()
                            };
                            // 3 standard deviations below the mean, aka the "Empirical Rule"
                            if *adj_rate < 3.0f64.mul_add(-std_dev, avg) {
                                stats += &paint(
                                    self.color.then_some(AnsiColor::Yellow),
                                    &format!(
                                        " -- Warning: Slow parse rate ({true_rate:.3} bytes/ms)"
                                    ),
                                );
                            }
                            stats
                        }
                    };
                    writeln!(
                        f,
                        "{test_num:>3}. {result_char} {}{stat_display}",
                        paint(self.color.then_some(color), &entry.name),
                    )?;
                }
                TestInfo::AssertionTest { .. } => unreachable!(),
            }
        }

        // Parse failure info
        if !self.parse_failures.is_empty() && self.update && !self.has_parse_errors {
            writeln!(
                f,
                "\n{} update{}:\n",
                self.parse_failures.len(),
                if self.parse_failures.len() == 1 {
                    ""
                } else {
                    "s"
                }
            )?;

            for (i, TestFailure { name, .. }) in self.parse_failures.iter().enumerate() {
                writeln!(f, "  {}. {name}", i + 1)?;
            }
        } else if !self.parse_failures.is_empty() && !self.overview_only {
            if !self.has_parse_errors {
                writeln!(
                    f,
                    "\n{} failure{}:",
                    self.parse_failures.len(),
                    if self.parse_failures.len() == 1 {
                        ""
                    } else {
                        "s"
                    }
                )?;
            }

            if self.color {
                DiffKey.fmt(f)?;
            }
            for (
                i,
                TestFailure {
                    name,
                    actual,
                    expected,
                    is_cst,
                },
            ) in self.parse_failures.iter().enumerate()
            {
                if expected == "NO ERROR" {
                    writeln!(f, "\n  {}. {name}:\n", i + 1)?;
                    writeln!(f, "  Expected an ERROR node, but got:")?;
                    let actual = if *is_cst {
                        actual
                    } else {
                        &format_sexp(actual, 2)
                    };
                    writeln!(
                        f,
                        "  {}",
                        paint(self.color.then_some(AnsiColor::Red), actual)
                    )?;
                } else {
                    writeln!(f, "\n  {}. {name}:", i + 1)?;
                    if *is_cst {
                        writeln!(
                            f,
                            "{}",
                            TestDiff::new(actual, expected).with_color(self.color)
                        )?;
                    } else {
                        writeln!(
                            f,
                            "{}",
                            TestDiff::new(&format_sexp(actual, 2), &format_sexp(expected, 2))
                                .with_color(self.color,)
                        )?;
                    }
                }
            }
        } else {
            writeln!(f)?;
        }

        Ok(())
    }
}

impl std::fmt::Display for TestSummary {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.fmt_parse_results(f)?;

        let mut render_assertion_results =
            |name: &str, results: &TestResultHierarchy| -> std::fmt::Result {
                writeln!(f, "{name}:")?;
                for (depth, entry) in results.iter() {
                    write!(f, "{}", "  ".repeat(depth + 2))?;
                    match &entry.info {
                        TestInfo::Group { .. } => writeln!(f, "{}", entry.name)?,
                        TestInfo::AssertionTest { outcome, test_num } => match outcome {
                            TestOutcome::AssertionPassed { assertion_count } => writeln!(
                                f,
                                "{:>3}. ✓ {} ({assertion_count} assertions)",
                                test_num,
                                paint(self.color.then_some(AnsiColor::Green), &entry.name)
                            )?,
                            TestOutcome::AssertionFailed { error } => {
                                writeln!(
                                    f,
                                    "{:>3}. ✗ {}",
                                    test_num,
                                    paint(self.color.then_some(AnsiColor::Red), &entry.name)
                                )?;
                                writeln!(f, "{}  {error}", "  ".repeat(depth + 1))?;
                            }
                            _ => unreachable!(),
                        },
                        TestInfo::ParseTest { .. } => unreachable!(),
                    }
                }
                Ok(())
            };

        if !self.highlight_results.root_group.is_empty() {
            render_assertion_results("syntax highlighting", &self.highlight_results)?;
        }

        if !self.tag_results.root_group.is_empty() {
            render_assertion_results("tags", &self.tag_results)?;
        }

        if !self.query_results.root_group.is_empty() {
            render_assertion_results("queries", &self.query_results)?;
        }

        Ok(())
    }
}

pub fn run_tests_at_path(
    parser: &mut Parser,
    opts: &TestOptions,
    test_summary: &mut TestSummary,
) -> Result<()> {
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

    let mut corrected_entries = Vec::new();
    run_tests(
        parser,
        test_entry,
        opts,
        test_summary,
        &mut corrected_entries,
        true,
    )?;

    parser.stop_printing_dot_graphs();

    if test_summary.parse_failures.is_empty() || (opts.update && !test_summary.has_parse_errors) {
        Ok(())
    } else if opts.update && test_summary.has_parse_errors {
        Err(anyhow!(indoc! {"
                Some tests failed to parse with unexpected `ERROR` or `MISSING` nodes, as shown above, and cannot be updated automatically.
                Either fix the grammar or manually update the tests if this is expected."}))
    } else {
        Err(anyhow!(""))
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

pub struct DiffKey;

impl std::fmt::Display for DiffKey {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "\ncorrect / {} / {}",
            paint(Some(AnsiColor::Green), "expected"),
            paint(Some(AnsiColor::Red), "unexpected")
        )?;
        Ok(())
    }
}

impl DiffKey {
    /// Writes [`DiffKey`] to stdout
    pub fn print() {
        println!("{Self}");
    }
}

pub struct TestDiff<'a> {
    pub actual: &'a str,
    pub expected: &'a str,
    pub color: bool,
}

impl<'a> TestDiff<'a> {
    #[must_use]
    pub const fn new(actual: &'a str, expected: &'a str) -> Self {
        Self {
            actual,
            expected,
            color: true,
        }
    }

    #[must_use]
    pub const fn with_color(mut self, color: bool) -> Self {
        self.color = color;
        self
    }
}

impl std::fmt::Display for TestDiff<'_> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let diff = TextDiff::from_lines(self.actual, self.expected);
        for diff in diff.iter_all_changes() {
            match diff.tag() {
                ChangeTag::Equal => {
                    if self.color {
                        write!(f, "{diff}")?;
                    } else {
                        write!(f, " {diff}")?;
                    }
                }
                ChangeTag::Insert => {
                    if self.color {
                        write!(
                            f,
                            "{}",
                            paint(Some(AnsiColor::Green), diff.as_str().unwrap())
                        )?;
                    } else {
                        write!(f, "+{diff}")?;
                    }
                    if diff.missing_newline() {
                        writeln!(f)?;
                    }
                }
                ChangeTag::Delete => {
                    if self.color {
                        write!(f, "{}", paint(Some(AnsiColor::Red), diff.as_str().unwrap()))?;
                    } else {
                        write!(f, "-{diff}")?;
                    }
                    if diff.missing_newline() {
                        writeln!(f)?;
                    }
                }
            }
        }

        Ok(())
    }
}

#[derive(Debug, Serialize, JsonSchema)]
pub struct TestFailure {
    name: String,
    actual: String,
    expected: String,
    is_cst: bool,
}

impl TestFailure {
    fn new<T, U, V>(name: T, actual: U, expected: V, is_cst: bool) -> Self
    where
        T: Into<String>,
        U: Into<String>,
        V: Into<String>,
    {
        Self {
            name: name.into(),
            actual: actual.into(),
            expected: expected.into(),
            is_cst,
        }
    }
}

struct TestCorrection {
    name: String,
    input: String,
    output: String,
    attributes_str: String,
    header_delim_len: usize,
    divider_delim_len: usize,
}

impl TestCorrection {
    fn new<T, U, V, W>(
        name: T,
        input: U,
        output: V,
        attributes_str: W,
        header_delim_len: usize,
        divider_delim_len: usize,
    ) -> Self
    where
        T: Into<String>,
        U: Into<String>,
        V: Into<String>,
        W: Into<String>,
    {
        Self {
            name: name.into(),
            input: input.into(),
            output: output.into(),
            attributes_str: attributes_str.into(),
            header_delim_len,
            divider_delim_len,
        }
    }
}

/// This will return false if we want to "fail fast". It will bail and not parse any more tests.
fn run_tests(
    parser: &mut Parser,
    test_entry: TestEntry,
    opts: &TestOptions,
    test_summary: &mut TestSummary,
    corrected_entries: &mut Vec<TestCorrection>,
    is_root: bool,
) -> Result<bool> {
    match test_entry {
        TestEntry::Example {
            name,
            input,
            output,
            header_delim_len,
            divider_delim_len,
            has_fields,
            attributes_str,
            attributes,
            ..
        } => {
            if attributes.skip {
                test_summary.parse_results.add_case(TestResult {
                    name: name.clone(),
                    info: TestInfo::ParseTest {
                        outcome: TestOutcome::Skipped,
                        parse_rate: None,
                        test_num: test_summary.test_num,
                    },
                });
                test_summary.test_num += 1;
                return Ok(true);
            }

            if !attributes.platform {
                test_summary.parse_results.add_case(TestResult {
                    name: name.clone(),
                    info: TestInfo::ParseTest {
                        outcome: TestOutcome::Platform,
                        parse_rate: None,
                        test_num: test_summary.test_num,
                    },
                });
                test_summary.test_num += 1;
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
                let start = std::time::Instant::now();
                let tree = parser.parse(&input, None).unwrap();
                let parse_rate = {
                    let parse_time = start.elapsed();
                    let true_parse_rate = tree.root_node().byte_range().len() as f64
                        / (parse_time.as_nanos() as f64 / 1_000_000.0);
                    let adj_parse_rate = adjusted_parse_rate(&tree, parse_time);

                    test_summary.parse_stats.total_parses += 1;
                    test_summary.parse_stats.total_duration += parse_time;
                    test_summary.parse_stats.total_bytes += tree.root_node().byte_range().len();

                    Some((true_parse_rate, adj_parse_rate))
                };

                if attributes.error {
                    if tree.root_node().has_error() {
                        test_summary.parse_results.add_case(TestResult {
                            name: name.clone(),
                            info: TestInfo::ParseTest {
                                outcome: TestOutcome::Passed,
                                parse_rate,
                                test_num: test_summary.test_num,
                            },
                        });
                        test_summary.parse_stats.successful_parses += 1;
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            let output = if attributes.cst {
                                output.clone()
                            } else {
                                format_sexp(&output, 0)
                            };
                            corrected_entries.push(TestCorrection::new(
                                &name,
                                input,
                                output,
                                &attributes_str,
                                header_delim_len,
                                divider_delim_len,
                            ));
                        }
                    } else {
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            // Keep the original `expected` output if the actual output has no error
                            let output = if attributes.cst {
                                output.clone()
                            } else {
                                format_sexp(&output, 0)
                            };
                            corrected_entries.push(TestCorrection::new(
                                &name,
                                input,
                                output,
                                &attributes_str,
                                header_delim_len,
                                divider_delim_len,
                            ));
                        }
                        test_summary.parse_results.add_case(TestResult {
                            name: name.clone(),
                            info: TestInfo::ParseTest {
                                outcome: TestOutcome::Failed,
                                parse_rate,
                                test_num: test_summary.test_num,
                            },
                        });
                        let actual = if attributes.cst {
                            render_test_cst(&input, &tree)?
                        } else {
                            tree.root_node().to_sexp()
                        };
                        test_summary.parse_failures.push(TestFailure::new(
                            &name,
                            actual,
                            "NO ERROR",
                            attributes.cst,
                        ));
                    }

                    if attributes.fail_fast {
                        return Ok(false);
                    }
                } else {
                    let mut actual = if attributes.cst {
                        render_test_cst(&input, &tree)?
                    } else {
                        tree.root_node().to_sexp()
                    };
                    if !(attributes.cst || opts.show_fields || has_fields) {
                        actual = strip_sexp_fields(&actual);
                    }

                    if actual == output {
                        test_summary.parse_results.add_case(TestResult {
                            name: name.clone(),
                            info: TestInfo::ParseTest {
                                outcome: TestOutcome::Passed,
                                parse_rate,
                                test_num: test_summary.test_num,
                            },
                        });
                        test_summary.parse_stats.successful_parses += 1;
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            let output = if attributes.cst {
                                actual
                            } else {
                                format_sexp(&output, 0)
                            };
                            corrected_entries.push(TestCorrection::new(
                                &name,
                                input,
                                output,
                                &attributes_str,
                                header_delim_len,
                                divider_delim_len,
                            ));
                        }
                    } else {
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            let (expected_output, actual_output) = if attributes.cst {
                                (output.clone(), actual.clone())
                            } else {
                                (format_sexp(&output, 0), format_sexp(&actual, 0))
                            };

                            // Only bail early before updating if the actual is not the output,
                            // sometimes users want to test cases that
                            // are intended to have errors, hence why this
                            // check isn't shown above
                            if actual.contains("ERROR") || actual.contains("MISSING") {
                                test_summary.has_parse_errors = true;

                                // keep the original `expected` output if the actual output has an
                                // error
                                corrected_entries.push(TestCorrection::new(
                                    &name,
                                    input,
                                    expected_output,
                                    &attributes_str,
                                    header_delim_len,
                                    divider_delim_len,
                                ));
                            } else {
                                corrected_entries.push(TestCorrection::new(
                                    &name,
                                    input,
                                    actual_output,
                                    &attributes_str,
                                    header_delim_len,
                                    divider_delim_len,
                                ));
                                test_summary.parse_results.add_case(TestResult {
                                    name: name.clone(),
                                    info: TestInfo::ParseTest {
                                        outcome: TestOutcome::Updated,
                                        parse_rate,
                                        test_num: test_summary.test_num,
                                    },
                                });
                            }
                        } else {
                            test_summary.parse_results.add_case(TestResult {
                                name: name.clone(),
                                info: TestInfo::ParseTest {
                                    outcome: TestOutcome::Failed,
                                    parse_rate,
                                    test_num: test_summary.test_num,
                                },
                            });
                        }
                        test_summary.parse_failures.push(TestFailure::new(
                            &name,
                            actual,
                            &output,
                            attributes.cst,
                        ));

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
            test_summary.test_num += 1;
        }
        TestEntry::Group {
            name,
            children,
            file_path,
        } => {
            if children.is_empty() {
                return Ok(true);
            }

            let failure_count = test_summary.parse_failures.len();
            let mut ran_test_in_group = false;

            let matches_filter = |name: &str, file_name: &Option<String>, opts: &TestOptions| {
                if let (Some(test_file_path), Some(filter_file_name)) = (file_name, &opts.file_name)
                {
                    if !filter_file_name.eq(test_file_path) {
                        return false;
                    }
                }
                if let Some(include) = &opts.include {
                    include.is_match(name)
                } else if let Some(exclude) = &opts.exclude {
                    !exclude.is_match(name)
                } else {
                    true
                }
            };

            for child in children {
                if let TestEntry::Example {
                    ref name,
                    ref file_name,
                    ref input,
                    ref output,
                    ref attributes_str,
                    header_delim_len,
                    divider_delim_len,
                    ..
                } = child
                {
                    if !matches_filter(name, file_name, opts) {
                        if opts.update {
                            let input = String::from_utf8(input.clone()).unwrap();
                            let output = format_sexp(output, 0);
                            corrected_entries.push(TestCorrection::new(
                                name,
                                input,
                                output,
                                attributes_str,
                                header_delim_len,
                                divider_delim_len,
                            ));
                        }

                        test_summary.test_num += 1;
                        continue;
                    }
                }

                if !ran_test_in_group && !is_root {
                    test_summary.parse_results.add_group(&name);
                    ran_test_in_group = true;
                }
                if !run_tests(parser, child, opts, test_summary, corrected_entries, false)? {
                    // fail fast
                    return Ok(false);
                }
            }
            // Now that we're done traversing the children of the current group, pop
            // the index
            test_summary.parse_results.pop_traversal();

            if let Some(file_path) = file_path {
                if opts.update && test_summary.parse_failures.len() - failure_count > 0 {
                    write_tests(&file_path, corrected_entries)?;
                }
                corrected_entries.clear();
            }
        }
    }
    Ok(true)
}

/// Convenience wrapper to render a CST for a test entry.
fn render_test_cst(input: &[u8], tree: &Tree) -> Result<String> {
    let mut rendered_cst: Vec<u8> = Vec::new();
    let mut cursor = tree.walk();
    let opts = ParseFileOptions {
        edits: &[],
        output: ParseOutput::Cst,
        stats: &mut ParseStats::default(),
        print_time: false,
        timeout: 0,
        debug: ParseDebugType::Quiet,
        debug_graph: false,
        cancellation_flag: None,
        encoding: None,
        open_log: false,
        no_ranges: false,
        parse_theme: &ParseTheme::empty(),
    };
    render_cst(input, tree, &mut cursor, &opts, &mut rendered_cst)?;
    Ok(String::from_utf8_lossy(&rendered_cst).trim().to_string())
}

// Parse time is interpreted in ns before converting to ms to avoid truncation issues
// Parse rates often have several outliers, leading to a large standard deviation. Taking
// the log of these rates serves to "flatten" out the distribution, yielding a more
// usable standard deviation for finding statistically significant slow parse rates
// NOTE: This is just a heuristic
#[must_use]
pub fn adjusted_parse_rate(tree: &Tree, parse_time: Duration) -> f64 {
    f64::ln(
        tree.root_node().byte_range().len() as f64 / (parse_time.as_nanos() as f64 / 1_000_000.0),
    )
}

fn write_tests(file_path: &Path, corrected_entries: &[TestCorrection]) -> Result<()> {
    let mut buffer = fs::File::create(file_path)?;
    write_tests_to_buffer(&mut buffer, corrected_entries)
}

fn write_tests_to_buffer(
    buffer: &mut impl Write,
    corrected_entries: &[TestCorrection],
) -> Result<()> {
    for (
        i,
        TestCorrection {
            name,
            input,
            output,
            attributes_str,
            header_delim_len,
            divider_delim_len,
        },
    ) in corrected_entries.iter().enumerate()
    {
        if i > 0 {
            writeln!(buffer)?;
        }
        writeln!(
            buffer,
            "{}\n{name}\n{}{}\n{input}\n{}\n\n{}",
            "=".repeat(*header_delim_len),
            if attributes_str.is_empty() {
                attributes_str.clone()
            } else {
                format!("{attributes_str}\n")
            },
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

#[must_use]
pub fn strip_points(sexp: &str) -> String {
    POINT_REGEX.replace_all(sexp, "").to_string()
}

fn parse_test_content(name: String, content: &str, file_path: Option<PathBuf>) -> TestEntry {
    let mut children = Vec::new();
    let bytes = content.as_bytes();
    let mut prev_name = String::new();
    let mut prev_attributes_str = String::new();
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

        let (mut skip, mut platform, mut fail_fast, mut error, mut cst, mut languages) =
            (false, None, false, false, false, vec![]);

        let test_name_and_markers = c
            .name("test_name_and_markers")
            .map_or("".as_bytes(), |m| m.as_bytes());

        let mut test_name = String::new();
        let mut attributes_str = String::new();

        let mut seen_marker = false;

        let test_name_and_markers = str::from_utf8(test_name_and_markers).unwrap();
        for line in test_name_and_markers
            .split_inclusive('\n')
            .filter(|s| !s.is_empty())
        {
            let trimmed_line = line.trim();
            match trimmed_line.split('(').next().unwrap() {
                ":skip" => (seen_marker, skip) = (true, true),
                ":platform" => {
                    if let Some(platforms) = trimmed_line.strip_prefix(':').and_then(|s| {
                        s.strip_prefix("platform(")
                            .and_then(|s| s.strip_suffix(')'))
                    }) {
                        seen_marker = true;
                        platform = Some(
                            platform.unwrap_or(false) || platforms.trim() == std::env::consts::OS,
                        );
                    }
                }
                ":fail-fast" => (seen_marker, fail_fast) = (true, true),
                ":error" => (seen_marker, error) = (true, true),
                ":language" => {
                    if let Some(lang) = trimmed_line.strip_prefix(':').and_then(|s| {
                        s.strip_prefix("language(")
                            .and_then(|s| s.strip_suffix(')'))
                    }) {
                        seen_marker = true;
                        languages.push(lang.into());
                    }
                }
                ":cst" => (seen_marker, cst) = (true, true),
                _ if !seen_marker => {
                    test_name.push_str(line);
                }
                _ => {}
            }
        }
        attributes_str.push_str(test_name_and_markers.strip_prefix(&test_name).unwrap());

        // prefer skip over error, both shouldn't be set
        if skip {
            error = false;
        }

        // add a default language if none are specified, will defer to the first language
        if languages.is_empty() {
            languages.push("".into());
        }

        if suffix1 == first_suffix && suffix2 == first_suffix {
            let header_range = c.get(0).unwrap().range();
            let test_name = if test_name.is_empty() {
                None
            } else {
                Some(test_name.trim_end().to_string())
            };
            let attributes_str = if attributes_str.is_empty() {
                None
            } else {
                Some(attributes_str.trim_end().to_string())
            };
            Some((
                header_delim_len,
                header_range,
                test_name,
                attributes_str,
                TestAttributes {
                    skip,
                    platform: platform.unwrap_or(true),
                    fail_fast,
                    error,
                    cst,
                    languages,
                },
            ))
        } else {
            None
        }
    });

    let (mut prev_header_len, mut prev_attributes) = (80, TestAttributes::default());
    for (header_delim_len, header_range, test_name, attributes_str, attributes) in header_matches
        .chain(Some((
            80,
            bytes.len()..bytes.len(),
            None,
            None,
            TestAttributes::default(),
        )))
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

                    let (output, has_fields) = if prev_attributes.cst {
                        (output.trim().to_string(), false)
                    } else {
                        // Remove all comments
                        let output = COMMENT_REGEX.replace_all(output, "").to_string();

                        // Normalize the whitespace in the expected output.
                        let output = WHITESPACE_REGEX.replace_all(output.trim(), " ");
                        let output = output.replace(" )", ")");

                        // Identify if the expected output has fields indicated. If not, then
                        // fields will not be checked.
                        let has_fields = SEXP_FIELD_REGEX.is_match(&output);

                        (output, has_fields)
                    };

                    let file_name = if let Some(ref path) = file_path {
                        path.file_name().map(|n| n.to_string_lossy().to_string())
                    } else {
                        None
                    };

                    let t = TestEntry::Example {
                        name: prev_name,
                        input,
                        output,
                        header_delim_len: prev_header_len,
                        divider_delim_len,
                        has_fields,
                        attributes_str: prev_attributes_str,
                        attributes: prev_attributes,
                        file_name,
                    };

                    children.push(t);
                }
            }
        }
        prev_attributes = attributes;
        prev_name = test_name.unwrap_or_default();
        prev_attributes_str = attributes_str.unwrap_or_default();
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
    use serde_json::json;

    use crate::tests::get_language;

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
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "The second test".to_string(),
                        input: b"d".to_vec(),
                        output: "(d)".to_string(),
                        header_delim_len: 16,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
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
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Code ending with dashes".to_string(),
                        input: b"abc\n-----------".to_vec(),
                        output: "(c (d))".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 19,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
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
            r"
(source_file
  (ERROR
    (UNEXPECTED 'f')
    (UNEXPECTED '+')))
"
            .trim()
        );
    }

    #[test]
    fn test_write_tests_to_buffer() {
        let mut buffer = Vec::new();
        let corrected_entries = vec![
            TestCorrection::new(
                "title 1".to_string(),
                "input 1".to_string(),
                "output 1".to_string(),
                String::new(),
                80,
                80,
            ),
            TestCorrection::new(
                "title 2".to_string(),
                "input 2".to_string(),
                "output 2".to_string(),
                String::new(),
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
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "sexp with comment between".to_string(),
                        input: b"code".to_vec(),
                        output: "(a (b))".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "sexp with ';'".to_string(),
                        input: b"code".to_vec(),
                        output: "(MISSING \";\")".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
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

==============================asdf\()[]|{}*+?^$.-
Test containing equals
==============================asdf\()[]|{}*+?^$.-

===

------------------------------asdf\()[]|{}*+?^$.-

(a)

==============================asdf\()[]|{}*+?^$.-
Subsequent test containing equals
==============================asdf\()[]|{}*+?^$.-

===

------------------------------asdf\()[]|{}*+?^$.-

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
        pretty_assertions::assert_eq!(
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
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Second test".to_string(),
                        input: expected_input.clone(),
                        output: "(a)".to_string(),
                        header_delim_len: 18,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Test name with = symbol".to_string(),
                        input: expected_input,
                        output: "(a)".to_string(),
                        header_delim_len: 25,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Test containing equals".to_string(),
                        input: "\n===\n".into(),
                        output: "(a)".into(),
                        header_delim_len: 30,
                        divider_delim_len: 30,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Subsequent test containing equals".to_string(),
                        input: "\n===\n".into(),
                        output: "(a)".into(),
                        header_delim_len: 30,
                        divider_delim_len: 30,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
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
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "name with === signs".to_string(),
                        input: b"code with ----".to_vec(),
                        output: "(d)".to_string(),
                        header_delim_len: 20,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: String::new(),
                        attributes: TestAttributes::default(),
                        file_name: None,
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
                    attributes_str: ":skip".to_string(),
                    attributes: TestAttributes {
                        skip: true,
                        platform: true,
                        fail_fast: false,
                        error: false,
                        cst: false,
                        languages: vec!["".into()]
                    },
                    file_name: None,
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

====================
Test with cst marker
:cst
====================
1
---
0:0 - 1:0   source_file
0:0 - 0:1   expression
0:0 - 0:1     number_literal `1`
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
                        attributes_str: format!(":platform({})\n:fail-fast", std::env::consts::OS),
                        attributes: TestAttributes {
                            skip: false,
                            platform: true,
                            fail_fast: true,
                            error: false,
                            cst: false,
                            languages: vec!["".into()]
                        },
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Test with bad platform marker".to_string(),
                        input: b"a".to_vec(),
                        output: "(b)".to_string(),
                        header_delim_len: 29,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: if std::env::consts::OS == "linux" {
                            ":platform(macos)\n\n:language(foo)".to_string()
                        } else {
                            ":platform(linux)\n\n:language(foo)".to_string()
                        },
                        attributes: TestAttributes {
                            skip: false,
                            platform: false,
                            fail_fast: false,
                            error: false,
                            cst: false,
                            languages: vec!["foo".into()]
                        },
                        file_name: None,
                    },
                    TestEntry::Example {
                        name: "Test with cst marker".to_string(),
                        input: b"1".to_vec(),
                        output: "0:0 - 1:0   source_file
0:0 - 0:1   expression
0:0 - 0:1     number_literal `1`"
                            .to_string(),
                        header_delim_len: 20,
                        divider_delim_len: 3,
                        has_fields: false,
                        attributes_str: ":cst".to_string(),
                        attributes: TestAttributes {
                            skip: false,
                            platform: true,
                            fail_fast: false,
                            error: false,
                            cst: true,
                            languages: vec!["".into()]
                        },
                        file_name: None,
                    }
                ]
            }
        );
    }

    fn clear_parse_rate(result: &mut TestResult) {
        let test_case_info = &mut result.info;
        match test_case_info {
            TestInfo::ParseTest {
                ref mut parse_rate, ..
            } => {
                assert!(parse_rate.is_some());
                *parse_rate = None;
            }
            TestInfo::Group { .. } | TestInfo::AssertionTest { .. } => {
                panic!("Unexpected test result")
            }
        }
    }

    #[test]
    fn run_tests_simple() {
        let mut parser = Parser::new();
        let language = get_language("c");
        parser
            .set_language(&language)
            .expect("Failed to set language");
        let mut languages = BTreeMap::new();
        languages.insert("c", &language);
        let opts = TestOptions {
            path: PathBuf::from("foo"),
            debug: true,
            debug_graph: false,
            include: None,
            exclude: None,
            file_name: None,
            update: false,
            open_log: false,
            languages,
            color: true,
            show_fields: false,
            overview_only: false,
        };

        // NOTE: The following test cases are combined to work around a race condition
        // in the loader
        {
            let test_entry = TestEntry::Group {
                name: "foo".to_string(),
                file_path: None,
                children: vec![TestEntry::Example {
                    name: "C Test 1".to_string(),
                    input: b"1;\n".to_vec(),
                    output: "(translation_unit (expression_statement (number_literal)))"
                        .to_string(),
                    header_delim_len: 25,
                    divider_delim_len: 3,
                    has_fields: false,
                    attributes_str: String::new(),
                    attributes: TestAttributes::default(),
                    file_name: None,
                }],
            };

            let mut test_summary = TestSummary::new(true, TestStats::All, false, false, false);
            let mut corrected_entries = Vec::new();
            run_tests(
                &mut parser,
                test_entry,
                &opts,
                &mut test_summary,
                &mut corrected_entries,
                true,
            )
            .expect("Failed to run tests");

            // parse rates will always be different, so we need to clear out these
            // fields to reliably assert equality below
            clear_parse_rate(&mut test_summary.parse_results.root_group[0]);
            test_summary.parse_stats.total_duration = Duration::from_secs(0);

            let json_results = serde_json::to_string(&test_summary).unwrap();

            assert_eq!(
                json_results,
                json!({
                  "parse_results": [
                    {
                      "name": "C Test 1",
                      "outcome": "Passed",
                      "parse_rate": null,
                      "test_num": 1
                    }
                  ],
                  "parse_failures": [],
                  "parse_stats": {
                    "successful_parses": 1,
                    "total_parses": 1,
                    "total_bytes": 3,
                    "total_duration": {
                      "secs": 0,
                      "nanos": 0,
                    }
                  },
                  "highlight_results": [],
                  "tag_results": [],
                  "query_results": []
                })
                .to_string()
            );
        }
        {
            let test_entry = TestEntry::Group {
                name: "corpus".to_string(),
                file_path: None,
                children: vec![
                    TestEntry::Group {
                        name: "group1".to_string(),
                        // This test passes
                        children: vec![TestEntry::Example {
                            name: "C Test 1".to_string(),
                            input: b"1;\n".to_vec(),
                            output: "(translation_unit (expression_statement (number_literal)))"
                                .to_string(),
                            header_delim_len: 25,
                            divider_delim_len: 3,
                            has_fields: false,
                            attributes_str: String::new(),
                            attributes: TestAttributes::default(),
                            file_name: None,
                        }],
                        file_path: None,
                    },
                    TestEntry::Group {
                        name: "group2".to_string(),
                        children: vec![
                            // This test passes
                            TestEntry::Example {
                                name: "C Test 2".to_string(),
                                input: b"1;\n".to_vec(),
                                output:
                                    "(translation_unit (expression_statement (number_literal)))"
                                        .to_string(),
                                header_delim_len: 25,
                                divider_delim_len: 3,
                                has_fields: false,
                                attributes_str: String::new(),
                                attributes: TestAttributes::default(),
                                file_name: None,
                            },
                            // This test fails, and is marked with fail-fast
                            TestEntry::Example {
                                name: "C Test 3".to_string(),
                                input: b"1;\n".to_vec(),
                                output:
                                    "(translation_unit (expression_statement (string_literal)))"
                                        .to_string(),
                                header_delim_len: 25,
                                divider_delim_len: 3,
                                has_fields: false,
                                attributes_str: String::new(),
                                attributes: TestAttributes {
                                    fail_fast: true,
                                    ..Default::default()
                                },
                                file_name: None,
                            },
                        ],
                        file_path: None,
                    },
                    // This group never runs because of the previous failure
                    TestEntry::Group {
                        name: "group3".to_string(),
                        // This test fails, and is marked with fail-fast
                        children: vec![TestEntry::Example {
                            name: "C Test 4".to_string(),
                            input: b"1;\n".to_vec(),
                            output: "(translation_unit (expression_statement (number_literal)))"
                                .to_string(),
                            header_delim_len: 25,
                            divider_delim_len: 3,
                            has_fields: false,
                            attributes_str: String::new(),
                            attributes: TestAttributes::default(),
                            file_name: None,
                        }],
                        file_path: None,
                    },
                ],
            };

            let mut test_summary = TestSummary::new(true, TestStats::All, false, false, false);
            let mut corrected_entries = Vec::new();
            run_tests(
                &mut parser,
                test_entry,
                &opts,
                &mut test_summary,
                &mut corrected_entries,
                true,
            )
            .expect("Failed to run tests");

            // parse rates will always be different, so we need to clear out these
            // fields to reliably assert equality below
            {
                let test_group_1_info = &mut test_summary.parse_results.root_group[0].info;
                match test_group_1_info {
                    TestInfo::Group {
                        ref mut children, ..
                    } => clear_parse_rate(&mut children[0]),
                    TestInfo::ParseTest { .. } | TestInfo::AssertionTest { .. } => {
                        panic!("Unexpected test result");
                    }
                }
                let test_group_2_info = &mut test_summary.parse_results.root_group[1].info;
                match test_group_2_info {
                    TestInfo::Group {
                        ref mut children, ..
                    } => {
                        clear_parse_rate(&mut children[0]);
                        clear_parse_rate(&mut children[1]);
                    }
                    TestInfo::ParseTest { .. } | TestInfo::AssertionTest { .. } => {
                        panic!("Unexpected test result");
                    }
                }
                test_summary.parse_stats.total_duration = Duration::from_secs(0);
            }

            let json_results = serde_json::to_string(&test_summary).unwrap();

            assert_eq!(
                json_results,
                json!({
                  "parse_results": [
                    {
                      "name": "group1",
                      "children": [
                        {
                          "name": "C Test 1",
                          "outcome": "Passed",
                          "parse_rate": null,
                          "test_num": 1
                        }
                      ]
                    },
                    {
                      "name": "group2",
                      "children": [
                        {
                          "name": "C Test 2",
                          "outcome": "Passed",
                          "parse_rate": null,
                          "test_num": 2
                        },
                        {
                          "name": "C Test 3",
                          "outcome": "Failed",
                          "parse_rate": null,
                          "test_num": 3
                        }
                      ]
                    }
                  ],
                  "parse_failures": [
                    {
                      "name": "C Test 3",
                      "actual": "(translation_unit (expression_statement (number_literal)))",
                      "expected": "(translation_unit (expression_statement (string_literal)))",
                      "is_cst": false,
                    }
                  ],
                  "parse_stats": {
                    "successful_parses": 2,
                    "total_parses": 3,
                    "total_bytes": 9,
                    "total_duration": {
                      "secs": 0,
                      "nanos": 0,
                    }
                  },
                  "highlight_results": [],
                  "tag_results": [],
                  "query_results": []
                })
                .to_string()
            );
        }
    }
}
