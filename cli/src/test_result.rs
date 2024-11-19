use anstyle::AnsiColor;
use serde::{ser::SerializeStruct, Serialize, Serializer};
use std::path::PathBuf;
use std::fmt::{Display, Formatter};
use similar::{TextDiff, ChangeTag};
use super::test::paint;

#[derive(Clone, Debug)]
// #[serde(untagged)]
pub enum TestResult {
    Executed {
        name: String,
        input: String,
        results: Vec<(String, LanguageResult)>,
    },
    NoPlatform {
        idx: usize,
        name: String,
    },
    Skipped {
        idx: usize,
        name: String,
        update: Option<(String, String, String, usize, usize)>,
    },
    Group {
        name: String,
        file_path: Option<PathBuf>,
        children: Vec<TestResult>,
    }
}

impl Default for TestResult {
    fn default() -> Self {
        TestResult::Group {
            name: "corpus".to_string(),
            file_path: None,
            children: vec![],
        }
    }
}

impl TestResult {
    pub fn get_all_tests(self) -> Vec<TestResult> {
        match self {
            TestResult::Group { children, .. } => {
                children.iter().flat_map(|child| child.clone().get_all_tests()).collect()
            }
            // TestResult::Executed { results } => {

            // }
            _ => vec![self],
        }
    }
    pub fn has_failures(&self) -> bool {
        self.get_failures().len() > 0
    }
    pub fn get_failures(&self) -> Vec<(String, String, String)> {
        match self {
            TestResult::Executed { name, results, .. } => {
                results.iter().filter_map(|(_, result)| {
                    match result {
                        LanguageResult::Fail { expected, result, .. } => Some((name.clone(), result.clone(), expected.clone())),
                        LanguageResult::Pass { intended: false, .. } => Some((name.clone(), "".to_string(), "NO ERROR".to_string())),
                        _ => None,
                    }
                }).collect()
            }
            TestResult::Group { children, .. } => {
                children.iter().flat_map(|child| child.get_failures()).collect()
            }
            _ => vec![],
        }
    }
    pub fn get_corrections(&self) -> Vec<CorrectedEntry> {
        match &self {
            TestResult::Group { children, .. } => {
                children.iter().flat_map(|child| child.get_corrections()).collect()
            }
            TestResult::Executed { input, results, .. } => {
                results.iter().filter_map(|(name, result)| {
                    match result {
                        LanguageResult::ExpectedFailure { name, expected, update: Some((attr_str, header_delim_len, divider_delim_len)), .. } => {
                            Some(CorrectedEntry {
                                name: name.clone(),
                                input: input.clone(),
                                output: expected.clone(),
                                attr_str: attr_str.clone(),
                                header_delim_len: *header_delim_len,
                                divider_delim_len: *divider_delim_len,
                            })
                        }
                        LanguageResult::Fail { result, expected, update: Some((attr_str, header_delim_len, divider_delim_len)), .. } => {
                            Some(CorrectedEntry {
                                name: name.clone(),
                                input: input.clone(),
                                output: if result.contains("ERROR") || result.contains("MISSING") { expected.clone() } else { result.clone() },
                                attr_str: attr_str.clone(),
                                header_delim_len: *header_delim_len,
                                divider_delim_len: *divider_delim_len,
                            })
                        }
                        LanguageResult::Pass { expected, name, update: Some((attr_str, a, b)), .. } => {
                            Some(CorrectedEntry {
                                name: name.clone(),
                                input: input.clone(),
                                output: expected.clone(),
                                attr_str: attr_str.clone(),
                                header_delim_len: *a,
                                divider_delim_len: *b,
                            })
                        }
                        _ => None,
                    }
                }).collect()
            }
            _ => vec![],
        }
    }
    pub fn has_parse_errors(&self) -> bool {
        self.get_failures().iter().any(|(_, result, _)| {
            result.contains("ERROR") || result.contains("MISSING")
        })
    }
}

pub struct CorrectedEntry {
    name: String,
    input: String,
    output: String,
    attr_str: String,
    header_delim_len: usize,
    divider_delim_len: usize,
}

impl CorrectedEntry {
    pub fn to_tuple(&self) -> (String, String, String, String, usize, usize) {
        (self.name.clone(), self.input.clone(), self.output.clone(), self.attr_str.clone(), self.header_delim_len, self.divider_delim_len)
    }
}

#[derive(Clone, Debug)]
pub enum LanguageResult {
    Pass {
        idx: usize,
        name: String,
        expected: String,
        intended: bool,
        update: Option<(String, usize, usize)>
    },
    Fail {
        idx: usize,
        name: String,
        expected: String,
        result: String,
        diff: Vec<DiffResult>,
        update: Option<(String, usize, usize)>,
    },
    ExpectedFailure {
        idx: usize,
        name: String,
        expected: String,
        update: Option<(String, usize, usize)>,
    },
}

impl Serialize for TestResult {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where S: Serializer,
    {
        match self {
            TestResult::NoPlatform { name, .. } => {
                let mut state = serializer.serialize_struct("NoPlatform", 2)?;
                state.serialize_field("status", "no platform")?;
                state.serialize_field("name", &name)?;
                state.end()
            }
            TestResult::Skipped { name, .. } => {
                let mut state = serializer.serialize_struct("Skipped", 2)?;
                state.serialize_field("status", "skipped")?;
                state.serialize_field("name", &name)?;
                state.end()
            }
            TestResult::Executed { name, input, results } => {
                let mut state = serializer.serialize_struct("Executed", 4)?;
                state.serialize_field("status", "executed")?;
                state.serialize_field("name", &name)?;
                state.serialize_field("input", &input)?;
                state.serialize_field("results", &results)?;
                state.end()
            }
            TestResult::Group { name, file_path, children } => {
                let mut state = serializer.serialize_struct("Group", 3)?;
                state.serialize_field("name", &name)?;
                state.serialize_field("file_path", file_path)?;
                state.serialize_field("children", children)?;
                state.end()
            }
        }
    }
}

impl Serialize for LanguageResult {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where S: Serializer, 
    {
        // let mut state = serializer.serialize_struct("LanguageResult")
        match self {
            LanguageResult::Pass { name, expected, intended, .. } => {
                let mut state = serializer.serialize_struct("Pass", 4)?;
                state.serialize_field("status", "passed")?;
                state.serialize_field("name", &name)?;
                state.serialize_field("expected", &expected)?;
                state.serialize_field("intended", intended)?;
                state.end()
            }
            LanguageResult::Fail { name, expected, result, diff, .. } => {
                let mut state = serializer.serialize_struct("Fail", 5)?;
                state.serialize_field("status", "failed")?;
                state.serialize_field("name", &name)?;
                state.serialize_field("expected", &expected)?;
                state.serialize_field("result", &result)?;
                state.serialize_field("diff", diff)?;
                state.end()
            }
            LanguageResult::ExpectedFailure { name, expected, .. } => {
                let mut state = serializer.serialize_struct("ExpectedFailure", 3)?;
                state.serialize_field("status", "expected failure")?;
                state.serialize_field("name", &name)?;
                state.serialize_field("expected", &expected)?;
                state.end()
            }
        }
    }
}
impl LanguageResult {
    pub fn pass(idx: usize, name: String, expected: String, update: Option<(String, usize, usize)>) -> Self {
        LanguageResult::Pass {
            idx,
            name,
            expected,
            update,
            intended: true,
        }
    }
    pub fn unexpected_pass(idx: usize, name: String, expected: String, update: Option<(String, usize, usize)>) -> Self {
        LanguageResult::Pass {
            idx,
            name,
            expected,
            update,
            intended: false,
        }
    }
    pub fn expected_fail(idx: usize, name: String, expected: String, update: Option<(String, usize, usize)>) -> Self {
        LanguageResult::ExpectedFailure {
            idx,
            name,
            expected,
            update,
        }
    }
    pub fn fail(idx: usize, name: String, expected: String, result: String, update: Option<(String, usize, usize)>) -> Self {
        let diff = TextDiff::from_lines(&expected, &result);
        let mut diff_vec = vec![];
        for d in diff.iter_all_changes() {
            let line = match d.tag() {
                ChangeTag::Equal => DiffResult::Equal { value: d.as_str().unwrap().to_string()},
                ChangeTag::Delete => DiffResult::Delete { value: d.as_str().unwrap().to_string()},
                ChangeTag::Insert => DiffResult::Insert { value: d.as_str().unwrap().to_string()}
            };
            diff_vec.push(line);
        }
        LanguageResult::Fail {
            idx,
            name,
            expected,
            result,
            diff: diff_vec,
            update,
        }
    }
}

#[derive(Clone, Debug)]
pub enum DiffResult {
    Equal { value: String },
    Insert { value: String },
    Delete { value: String },
}
impl Serialize for DiffResult {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error> where S: Serializer {
        let mut state = serializer.serialize_struct("DiffResult", 2)?;
        match self {
            DiffResult::Equal { value } => {
                state.serialize_field("value", &value)?;
                state.serialize_field("tag", "equal")?
            }
            DiffResult::Delete { value } => {
                state.serialize_field("value", &value)?;
                state.serialize_field("tag", "delete")?
            }
            DiffResult::Insert { value } => {
                state.serialize_field("value", &value)?;
                state.serialize_field("tag", "insert")?
            }
        }
        state.end()
    }
}

pub enum HighlightTestResult {
    Suite {
        name: String,
        children: Vec<HighlightTestResult>,
    },
    Pass {
        name: String,
        assertion_count: usize,
    },
    Fail {
        name: String,
        error: anyhow::Error,
    }
}

impl Default for HighlightTestResult {
    fn default() -> Self {
        HighlightTestResult::Suite {
            name: "highlights".to_string(),
            children: vec![],
        }
    }
}

impl HighlightTestResult {
    pub fn to_string(&self, use_color: bool, depth: usize) -> String {
        match self {
            HighlightTestResult::Suite { name, children } => {
                let mut acc = String::new();
                if depth > 0 {
                    acc.push_str(&format!("{indent:indent_level$}{name}\n", indent = "", indent_level = 2 * (depth + 1)));
                }
                for child in children {
                    let a = child.to_string(use_color, depth + 1);
                    // let indented = a.lines().map(|line| format!("{indent:indent_level$}{line}", indent = "", indent_level = 2, line = line)).collect::<Vec<String>>().join("\n");
                    acc.push_str(&a);
                }
                acc
            },
            HighlightTestResult::Pass { name, assertion_count } => {
                let nname = paint(use_color.then_some(AnsiColor::Green), name);
                format!("{indent:indent_level$}✓ {nname} ({assertion_count} assertions)\n", indent = "", indent_level = (depth + 1) * 2)
            },
            HighlightTestResult::Fail { name, error } => {
                let nname = paint(use_color.then_some(AnsiColor::Red), name);
                format!("{indent:indent_level$}✗ {nname}\n  {error}\n", indent = "", indent_level = (depth + 1) * 2)
            },
        }

    }
}

impl Display for HighlightTestResult {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        match self {
            HighlightTestResult::Suite { name, children } => {
                let mut acc = format!("{}", name);
                // write!(f, "{}", name)?;
                for child in children {
                    let a = format!("{}", child);
                    acc.push_str(&a);
                }
                write!(f, "{}", acc)
                // Ok(())
            },
            HighlightTestResult::Pass { name, assertion_count } => {
                writeln!(f, "✓ {} ({} assertions)", name, assertion_count)
            },
            HighlightTestResult::Fail { name, error } => {
                writeln!(f, "✗ {}\n  {error}", name)
                // writeln!(f, "  {error}")
            },
        }
    }
}

impl Serialize for HighlightTestResult {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error> where S: Serializer {
        match self {
            HighlightTestResult::Suite { name, children } => {
                let mut state = serializer.serialize_struct("Suite", 2)?;
                state.serialize_field("name", name)?;
                state.serialize_field("children", children)?;
                state.end()
            },
            HighlightTestResult::Pass { name, assertion_count } => {
                let mut state = serializer.serialize_struct("Pass", 2)?;
                state.serialize_field("name", name)?;
                state.serialize_field("assertion_count", assertion_count)?;
                state.end()
            },
            HighlightTestResult::Fail { name, error } => {
                let mut state = serializer.serialize_struct("Fail", 2)?;
                state.serialize_field("name", name)?;
                state.serialize_field("error", &error.to_string())?;
                state.end()
            },
        }
    }
}

#[derive(Serialize)]
pub enum TagTestResult {
    Success { name: String, assertion_count: usize },
    Failure { name: String, error: String },
}

impl TagTestResult {
    pub fn to_string(&self, use_color: bool) -> String {
        match &self {
            TagTestResult::Success { name, assertion_count } => {
                let nname = paint(use_color.then_some(AnsiColor::Green), name);
                format!("  ✓ {} ({assertion_count} assertions)", nname)
            },
            TagTestResult::Failure { name, error } => {
                let nname = paint(use_color.then_some(AnsiColor::Red), name);
                format!("  ✗ {nname}\n    {error}")
            },
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn serialize_diff() {
        let eq_input = DiffResult::Equal { value: "hello".to_string() };
        let eq_expected = r#"{"value":"hello","tag":"equal"}"#;
        let eq_result = serde_json::to_string(&eq_input).unwrap();
        assert_eq!(eq_expected, eq_result);

        let ins_input = DiffResult::Insert { value: "hello".to_string() };
        let ins_expected = r#"{"value":"hello","tag":"insert"}"#;
        let ins_result = serde_json::to_string(&ins_input).unwrap();
        assert_eq!(ins_expected, ins_result);

        let del_input = DiffResult::Delete { value: "hello".to_string() };
        let del_expected = r#"{"value":"hello","tag":"delete"}"#;
        let del_result = serde_json::to_string(&del_input).unwrap();
        assert_eq!(del_expected, del_result);
    }

    #[test]
    fn pass_result_is_intended() {
        let p = LanguageResult::pass(0, "name".to_string(), "expected".to_string(), None);
        match p {
            LanguageResult::Pass { intended, .. } => {
                assert!(intended);
            }
            _ => {
                panic!("Expected pass result");
            }
        }
    }

    #[test]
    fn unexpected_pass_result_is_not_intended() {
        let p = LanguageResult::unexpected_pass(0, "name".to_string(), "expected".to_string(), None);
        match p {
            LanguageResult::Pass { intended, .. } => {
                assert!(!intended);
            }
            _ => {
                panic!("Expected pass result");
            }
        }
    }

    #[test]
    fn get_failures_includes_unexpected_pass() {
        let p = LanguageResult::unexpected_pass(0, "name".to_string(), "expected".to_string(), None);
        let e = TestResult::Executed { name: "".to_string(), input: String::new(), results: vec![("".to_string(), p)] };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![e],
        };
        let result = group.get_failures();
        assert_eq!(result.len(), 1);
    }

    #[test]
    fn get_failures_includes_failure() {
        let f = LanguageResult::fail(0, "name".to_string(), "expected".to_string(), "result".to_string(), None);
        let e = TestResult::Executed { name: "".to_string(), input: String::new(), results: vec![("".to_string(), f)] };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![e],
        };
        let result = group.get_failures();
        assert_eq!(result.len(), 1);
    }

    #[test]
    fn get_failures_excludes_pass() {
        let p = LanguageResult::pass(0, "name".to_string(), "expected".to_string(), None);
        let e = TestResult::Executed { name: "".to_string(), input: String::new(), results: vec![("".to_string(), p)] };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![e],
        };
        let result = group.get_failures();
        assert_eq!(result.len(), 0);
    }

    #[test]
    fn get_failures_excludes_expected_fail() {
        let p = LanguageResult::expected_fail(0, "name".to_string(), "expected".to_string(), None);
        let e = TestResult::Executed { name: "".to_string(), input: String::new(), results: vec![("".to_string(), p)] };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![e],
        };
        let result = group.get_failures();
        assert_eq!(result.len(), 0);
    }

    #[test]
    fn get_failures_excludes_skipped() {
        let s = TestResult::Skipped { idx: 0, name: "".to_string(), update: None };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![s],
        };
        let result = group.get_failures();
        assert_eq!(result.len(), 0);
    }

    #[test]
    fn get_failures_excludes_no_platform() {
        let s = TestResult::NoPlatform { idx: 0, name: "".to_string() };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![s],
        };
        let result = group.get_failures();
        assert_eq!(result.len(), 0);
    }

    #[test]
    fn test_results_include_tag() {
        let p = LanguageResult::pass(0, "name".to_string(), "expected".to_string(), None);
        let f = LanguageResult::fail(0, "name".to_string(), "expected".to_string(), "result".to_string(), None);
        let skipped = TestResult::Skipped { idx: 0, name: "".to_string(), update: None };
        let no_platform = TestResult::NoPlatform { idx: 0, name: "".to_string() };
        let unexpected = LanguageResult::unexpected_pass(0, "name".to_string(), "expected".to_string(), None);
        let expected_fail = LanguageResult::expected_fail(0, "name".to_string(), "expected".to_string(), None);
        // let e = TestResult::Executed { name: "".to_string(), results: vec![("".to_string(), p)] };
        let mut result = serde_json::to_string(&p).unwrap();
        assert!(result.contains(r#""status":"passed""#));
        result = serde_json::to_string(&f).unwrap();
        assert!(result.contains(r#""status":"failed""#));
        result = serde_json::to_string(&skipped).unwrap();
        assert!(result.contains(r#""status":"skipped""#));
        result = serde_json::to_string(&no_platform).unwrap();
        assert!(result.contains(r#""status":"no platform""#));
        result = serde_json::to_string(&unexpected).unwrap();
        assert!(result.contains(r#""status":"passed""#));
        result = serde_json::to_string(&expected_fail).unwrap();
        assert!(result.contains(r#""status":"expected failure""#));
    }

    #[test]
    fn has_failures() {
        let f = LanguageResult::fail(0, "name".to_string(), "expected".to_string(), "result".to_string(), None);
        let e = TestResult::Executed { name: "".to_string(), input: String::new(), results: vec![("".to_string(), f)] };
        let group = TestResult::Group {
            name: "".to_string(),
            file_path: None,
            children: vec![e],
        };
        assert!(group.has_failures());
    }

    #[test]
    fn if_expected_error_add_to_corrections_with_expected() {
        let r = LanguageResult::expected_fail(0, String::new(), "foo".to_string(), Some((String::new(), 1, 2)));
        let t = TestResult::Executed { name: String::new(), input: String::new(), results: vec![(String::new(), r)] };
        let c = t.get_corrections();
        assert_eq!(c.len(), 1);
        assert_eq!(c[0].output, "foo");
    }

    #[test]
    fn if_unexpected_success_add_to_corrections_with_expected() {
        let r = LanguageResult::unexpected_pass(0, String::new(), "foo".to_string(), Some((String::new(), 1, 2)));
        let t = TestResult::Executed { name: String::new(), input: String::new(), results: vec![(String::new(), r)] };
        let c = t.get_corrections();
        assert_eq!(c.len(), 1);
        assert_eq!(c[0].output, "foo");
    }

    #[test]
    fn if_expected_success_add_to_corrections_with_expected() {
        let r = LanguageResult::pass(0, String::new(), "foo".to_string(), Some((String::new(), 1, 2)));
        let t = TestResult::Executed { name: String::new(), input: String::new(), results: vec![(String::new(), r)] };
        let c = t.get_corrections();
        assert_eq!(c.len(), 1);
        assert_eq!(c[0].output, "foo");
    }

    #[test]
    fn if_unexpected_error_with_error_or_missing_add_to_corrections_with_expected() {
        let r = LanguageResult::fail(1, String::new(), "foo".to_string(), "this is ERROR".to_string(), Some((String::new(), 1, 2)));
        let t = TestResult::Executed { name: String::new(), input: String::new(), results: vec![(String::new(), r)] };
        let c = t.get_corrections();
        assert_eq!(c.len(), 1);
        assert_eq!(c[0].output, "foo");
    }

    #[test]
    fn if_unexpected_error_with_no_parsing_issues_add_actual_to_corrections() {
        let r = LanguageResult::fail(1, String::new(), "foo".to_string(), "bar".to_string(), Some((String::new(), 1, 2)));
        let t = TestResult::Executed { name: String::new(), input: String::new(), results: vec![(String::new(), r)] };
        let c = t.get_corrections();
        assert_eq!(c.len(), 1);
        assert_eq!(c[0].output, "bar");
    }
    
}