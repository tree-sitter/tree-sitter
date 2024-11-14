use serde::{ser::SerializeStruct, Serialize, Serializer};
use std::path::PathBuf;
use similar::{TextDiff, ChangeTag};

#[derive(Clone, Serialize)]
#[serde(untagged)]
pub enum TestResult {
    Executed {
        name: String,
        results: Vec<(String, LanguageResult)>,
    },
    NoPlatform {
        name: String,
    },
    Skipped {
        name: String,
        update: Option<(String, String, String, usize, usize)>,
    },
    Group {
        name: String,
        file_path: Option<PathBuf>,
        children: Vec<TestResult>,
    }
}

// pub impl Iter for TestResult {
//     type Item = TestResult;

//     fn next(&mut self) -> Option(Self::Item) {
//         let current = self.curr;

//         self.curr = self.next;
//         self.next = 
//     }
// }

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
        match self {
            TestResult::Executed { results, .. } => {
                results.iter().any(|(_, result)| match result {
                    LanguageResult::Fail { .. } => true,
                    _ => false,
                })
            }
            TestResult::Group { children, .. } => {
                children.iter().any(|child| child.has_failures())
            }
            _ => false,
        }
    }
    pub fn get_failures(&self) -> Vec<(String, String, String)> {
        match self {
            TestResult::Executed { name, results, .. } => {
                results.iter().filter_map(|(_, result)| {
                    match result {
                        LanguageResult::Fail { expected, result, .. } => Some((name.clone(), result.clone(), expected.clone())),
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
}
#[derive(Clone)]
pub enum LanguageResult {
    Pass {
        name: String,
        expected: String,
        intended: bool,
        update: Option<(String, usize, usize)>
    },
    Fail {
        name: String,
        expected: String,
        result: String,
        diff: Vec<DiffResult>,
        update: Option<(String, usize, usize)>,
    },
    ExpectedFailure {
        name: String,
        expected: String,
        update: Option<(String, usize, usize)>,
    },
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
    pub fn pass(name: String, expected: String, update: Option<(String, usize, usize)>) -> Self {
        LanguageResult::Pass {
            name: name,
            expected,
            update,
            intended: true,
        }
    }
    pub fn unexpected_pass(name: String, expected: String, update: Option<(String, usize, usize)>) -> Self {
        LanguageResult::Pass {
            name: name,
            expected,
            update,
            intended: false,
        }
    }
    pub fn expected_fail(name: String, expected: String, update: Option<(String, usize, usize)>) -> Self {
        LanguageResult::ExpectedFailure {
            name,
            expected,
            update,
        }
    }
    pub fn fail(name: String, expected: String, result: String, update: Option<(String, usize, usize)>) -> Self {
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
            name,
            expected,
            result,
            diff: diff_vec,
            update,
        }
    }
}

#[derive(Clone)]
enum DiffResult {
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