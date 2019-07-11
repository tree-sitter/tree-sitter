use super::ExtractedLexicalGrammar;
use crate::error::{Error, Result};
use crate::generate::grammars::{LexicalGrammar, LexicalVariable};
use crate::generate::nfa::{CharacterSet, Nfa, NfaState};
use crate::generate::rules::Rule;
use lazy_static::lazy_static;
use regex::Regex;
use regex_syntax::hir::{
    Class as HirClass, Hir, HirKind, Literal, RepetitionKind as HirRepetitionKind,
    RepetitionRange as HirRepetitionRange,
};
use std::{char, i32};

lazy_static! {
    static ref CURLY_BRACE_REGEX: Regex = Regex::new(r#"(?x)
        # captures: $1: lookbehind, $2, $4: close bracket; $3, $5: content
        ( ^[^\\\{]?? | \\[^pPuUx] | [^\\][^\\] )               # lookbehind is not \p, \P, \u, \U, \x, \
        \{                                                     # followed by a openning bracket
        (?: $ | (\}) |                                         # followed by eoi or close bracket, or
            ( (?:\\\}|[^}])*?(?:[^0-9,}]|\\\})(?:\\\}|[^}])*?  # content and
              [^\\] ) (\}) |                                   # a non-escaped close bracket, or
            ( (?:\\\}|[^}])*?(?:[^0-9,}]|\\\})(?:\\\}|[^}])*?)$# content and lacks a close bracket
        )
    "#).unwrap();
}

const ALLOWED_REDUNDANT_ESCAPED_CHARS: [char; 4] = ['!', '\'', '"', '/'];

struct NfaBuilder {
    nfa: Nfa,
    is_sep: bool,
    precedence_stack: Vec<i32>,
}

fn get_implicit_precedence(rule: &Rule) -> i32 {
    match rule {
        Rule::String(_) => 2,
        Rule::Metadata { rule, params } => {
            if params.is_main_token {
                get_implicit_precedence(rule) + 1
            } else {
                get_implicit_precedence(rule)
            }
        }
        _ => 0,
    }
}

fn get_completion_precedence(rule: &Rule) -> i32 {
    match rule {
        Rule::Metadata { params, .. } => params.precedence.unwrap_or(0),
        _ => 0,
    }
}

fn preprocess_regex(content: &str) -> String {
    let content = {
        let mut content = content.to_string();
        loop {
            // continually replace _paired_ brackets that aren't part of an escape/class
            let mut next;
            if let Some(c) = CURLY_BRACE_REGEX.captures(&content) {
                let c: regex::Captures = c;
                next = String::with_capacity(content.len());
                next.push_str(&content[..c.get(1).unwrap().end()]);
                next.push_str(r#"\{"#);
                let mid = c.get(3).or_else(|| c.get(5)).map_or("", |m| m.as_str());
                next.push_str(mid);
                let (end, close) = c
                    .get(2)
                    .or_else(|| c.get(4))
                    .map_or_else(|| (content.len(), ""), |m| (m.end(), r#"\}"#));
                next.push_str(close);
                next.push_str(&content[end..]);
            } else {
                break;
            };
            content = next;
        }
        content
    };
    let mut result = String::with_capacity(content.len());
    let mut is_escaped = false;
    for c in content.chars() {
        if is_escaped {
            if ALLOWED_REDUNDANT_ESCAPED_CHARS.contains(&c) {
                result.push(c);
            } else {
                result.push('\\');
                result.push(c);
            }
            is_escaped = false;
        } else if c == '\\' {
            is_escaped = true;
        } else {
            result.push(c);
        }
    }
    if is_escaped {
        result.push('\\');
    }
    result
}

pub(crate) fn expand_tokens(mut grammar: ExtractedLexicalGrammar) -> Result<LexicalGrammar> {
    let mut builder = NfaBuilder {
        nfa: Nfa::new(),
        is_sep: true,
        precedence_stack: vec![0],
    };

    let separator_rule = if grammar.separators.len() > 0 {
        grammar.separators.push(Rule::Blank);
        Rule::repeat(Rule::choice(grammar.separators))
    } else {
        Rule::Blank
    };

    let mut variables = Vec::new();
    for (i, variable) in grammar.variables.into_iter().enumerate() {
        let is_immediate_token = match &variable.rule {
            Rule::Metadata { params, .. } => params.is_main_token,
            _ => false,
        };

        builder.is_sep = false;
        builder.nfa.states.push(NfaState::Accept {
            variable_index: i,
            precedence: get_completion_precedence(&variable.rule),
        });
        let last_state_id = builder.nfa.last_state_id();
        builder
            .expand_rule(&variable.rule, last_state_id)
            .map_err(Error::wrap(|| {
                format!("Error processing rule {}", variable.name)
            }))?;

        if !is_immediate_token {
            builder.is_sep = true;
            let last_state_id = builder.nfa.last_state_id();
            builder.expand_rule(&separator_rule, last_state_id)?;
        }

        variables.push(LexicalVariable {
            name: variable.name,
            kind: variable.kind,
            implicit_precedence: get_implicit_precedence(&variable.rule),
            start_state: builder.nfa.last_state_id(),
        });
    }

    Ok(LexicalGrammar {
        nfa: builder.nfa,
        variables,
    })
}

impl NfaBuilder {
    fn expand_rule(&mut self, rule: &Rule, mut next_state_id: u32) -> Result<bool> {
        match rule {
            Rule::Pattern(s) => {
                let s = preprocess_regex(s);
                let hir = regex_syntax::Parser::new().parse(&s)?;
                self.expand_regex(&hir, next_state_id)
            }
            Rule::String(s) => {
                for c in s.chars().rev() {
                    self.push_advance(CharacterSet::empty().add_char(c), next_state_id);
                    next_state_id = self.nfa.last_state_id();
                }
                Ok(s.len() > 0)
            }
            Rule::Choice(elements) => {
                let mut alternative_state_ids = Vec::new();
                for element in elements {
                    if self.expand_rule(element, next_state_id)? {
                        alternative_state_ids.push(self.nfa.last_state_id());
                    } else {
                        alternative_state_ids.push(next_state_id);
                    }
                }
                alternative_state_ids.sort_unstable();
                alternative_state_ids.dedup();
                alternative_state_ids.retain(|i| *i != self.nfa.last_state_id());
                for alternative_state_id in alternative_state_ids {
                    self.push_split(alternative_state_id);
                }
                Ok(true)
            }
            Rule::Seq(elements) => {
                let mut result = false;
                for element in elements.into_iter().rev() {
                    if self.expand_rule(element, next_state_id)? {
                        result = true;
                    }
                    next_state_id = self.nfa.last_state_id();
                }
                Ok(result)
            }
            Rule::Repeat(rule) => {
                self.nfa.states.push(NfaState::Accept {
                    variable_index: 0,
                    precedence: 0,
                }); // Placeholder for split
                let split_state_id = self.nfa.last_state_id();
                if self.expand_rule(rule, split_state_id)? {
                    self.nfa.states[split_state_id as usize] =
                        NfaState::Split(self.nfa.last_state_id(), next_state_id);
                    Ok(true)
                } else {
                    Ok(false)
                }
            }
            Rule::Metadata { rule, params } => {
                if let Some(precedence) = params.precedence {
                    self.precedence_stack.push(precedence);
                }
                let result = self.expand_rule(rule, next_state_id);
                if params.precedence.is_some() {
                    self.precedence_stack.pop();
                }
                result
            }
            Rule::Blank => Ok(false),
            _ => Err(Error::grammar(&format!("Unexpected rule {:?}", rule))),
        }
    }

    fn expand_regex(&mut self, hir: &Hir, mut next_state_id: u32) -> Result<bool> {
        match hir.kind() {
            HirKind::Empty => Ok(false),
            HirKind::Literal(literal) => {
                let c = match literal {
                    Literal::Unicode(c) => *c,
                    Literal::Byte(_) => unreachable!("all regex are utf8-correct"),
                };
                self.push_advance(CharacterSet::singleton(c), next_state_id);
                Ok(true)
            }
            HirKind::Class(class) => {
                let chars = self.expand_character_class(class)?;
                self.push_advance(chars, next_state_id);
                Ok(true)
            }
            HirKind::Anchor(_) => Err(Error::regex("Anchors are not supported")),
            HirKind::WordBoundary(_) => Err(Error::regex("Word boundaries are not supported")),
            HirKind::Repetition(repetition) => {
                if repetition.greedy {
                    match repetition.kind {
                        HirRepetitionKind::ZeroOrOne => {
                            self.expand_zero_or_one(&repetition.hir, next_state_id)
                        }
                        HirRepetitionKind::ZeroOrMore => {
                            self.expand_zero_or_more(&repetition.hir, next_state_id)
                        }
                        HirRepetitionKind::OneOrMore => {
                            self.expand_one_or_more(&repetition.hir, next_state_id)
                        }
                        HirRepetitionKind::Range(HirRepetitionRange::Exactly(count)) => {
                            self.expand_count(&repetition.hir, count, next_state_id)
                        }
                        HirRepetitionKind::Range(HirRepetitionRange::AtLeast(min)) => {
                            if self.expand_one_or_more(&repetition.hir, next_state_id)? {
                                self.expand_count(&repetition.hir, min, next_state_id)
                            } else {
                                Ok(false)
                            }
                        }
                        HirRepetitionKind::Range(HirRepetitionRange::Bounded(min, max)) => {
                            let mut result =
                                self.expand_count(&repetition.hir, min, next_state_id)?;
                            for _ in min..max {
                                if result {
                                    next_state_id = self.nfa.last_state_id();
                                }
                                if self.expand_zero_or_one(&repetition.hir, next_state_id)? {
                                    result = true;
                                }
                            }
                            Ok(result)
                        }
                    }
                } else {
                    Err(Error::regex("Non-greedy repetition are not supported"))
                }
            }
            HirKind::Group(group) => self.expand_regex(&group.hir, next_state_id),
            HirKind::Concat(concat) => {
                let mut result = false;
                for hir in concat.iter().rev() {
                    if self.expand_regex(&hir, next_state_id)? {
                        result = true;
                        next_state_id = self.nfa.last_state_id();
                    }
                }
                Ok(result)
            }
            HirKind::Alternation(alternation) => {
                let mut alternative_state_ids = Vec::new();
                for hir in alternation {
                    if self.expand_regex(&hir, next_state_id)? {
                        alternative_state_ids.push(self.nfa.last_state_id());
                    } else {
                        alternative_state_ids.push(next_state_id);
                    }
                }
                alternative_state_ids.sort_unstable();
                alternative_state_ids.dedup();
                alternative_state_ids.retain(|i| *i != self.nfa.last_state_id());

                for alternative_state_id in alternative_state_ids {
                    self.push_split(alternative_state_id);
                }
                Ok(true)
            }
        }
    }

    fn expand_one_or_more(&mut self, hir: &Hir, next_state_id: u32) -> Result<bool> {
        self.nfa.states.push(NfaState::Accept {
            variable_index: 0,
            precedence: 0,
        }); // Placeholder for split
        let split_state_id = self.nfa.last_state_id();
        if self.expand_regex(hir, split_state_id)? {
            self.nfa.states[split_state_id as usize] =
                NfaState::Split(self.nfa.last_state_id(), next_state_id);
            Ok(true)
        } else {
            self.nfa.states.pop();
            Ok(false)
        }
    }

    fn expand_zero_or_one(&mut self, hir: &Hir, next_state_id: u32) -> Result<bool> {
        if self.expand_regex(hir, next_state_id)? {
            self.push_split(next_state_id);
            Ok(true)
        } else {
            Ok(false)
        }
    }

    fn expand_zero_or_more(&mut self, hir: &Hir, next_state_id: u32) -> Result<bool> {
        if self.expand_one_or_more(hir, next_state_id)? {
            self.push_split(next_state_id);
            Ok(true)
        } else {
            Ok(false)
        }
    }

    fn expand_count(&mut self, hir: &Hir, count: u32, mut next_state_id: u32) -> Result<bool> {
        let mut result = false;
        for _ in 0..count {
            if self.expand_regex(hir, next_state_id)? {
                result = true;
                next_state_id = self.nfa.last_state_id();
            }
        }
        Ok(result)
    }

    fn expand_character_class(&self, item: &HirClass) -> Result<CharacterSet> {
        match item {
            HirClass::Unicode(class) => {
                let mut chars = CharacterSet::empty();
                for cs in class.iter() {
                    chars = chars.add_range(cs.start(), cs.end());
                }
                Ok(chars)
            }
            HirClass::Bytes(class) => {
                let mut chars = CharacterSet::empty();
                for cs in class.iter() {
                    chars = chars.add_range(char::from(cs.start()), char::from(cs.end()));
                }
                Ok(chars)
            }
        }
    }

    fn push_advance(&mut self, chars: CharacterSet, state_id: u32) {
        let precedence = *self.precedence_stack.last().unwrap();
        self.nfa.states.push(NfaState::Advance {
            chars,
            state_id,
            precedence,
            is_sep: self.is_sep,
        });
    }

    fn push_split(&mut self, state_id: u32) {
        let last_state_id = self.nfa.last_state_id();
        self.nfa
            .states
            .push(NfaState::Split(state_id, last_state_id));
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::generate::grammars::Variable;
    use crate::generate::nfa::{NfaCursor, NfaTransition};

    fn simulate_nfa<'a>(grammar: &'a LexicalGrammar, s: &'a str) -> Option<(usize, &'a str)> {
        let start_states = grammar.variables.iter().map(|v| v.start_state).collect();
        let mut cursor = NfaCursor::new(&grammar.nfa, start_states);

        let mut result = None;
        let mut result_precedence = i32::MIN;
        let mut start_char = 0;
        let mut end_char = 0;
        for c in s.chars() {
            for (id, precedence) in cursor.completions() {
                if result.is_none() || result_precedence <= precedence {
                    result = Some((id, &s[start_char..end_char]));
                    result_precedence = precedence;
                }
            }
            if let Some(NfaTransition {
                states,
                is_separator,
                ..
            }) = cursor
                .transitions()
                .into_iter()
                .find(|t| t.characters.contains(c) && t.precedence >= result_precedence)
            {
                cursor.reset(states);
                end_char += c.len_utf8();
                if is_separator {
                    start_char = end_char;
                }
            } else {
                break;
            }
        }

        for (id, precedence) in cursor.completions() {
            if result.is_none() || result_precedence <= precedence {
                result = Some((id, &s[start_char..end_char]));
                result_precedence = precedence;
            }
        }

        result
    }

    #[test]
    fn test_rule_expansion() {
        struct Row {
            rules: Vec<Rule>,
            separators: Vec<Rule>,
            examples: Vec<(&'static str, Option<(usize, &'static str)>)>,
        }

        let table = [
            // regex with sequences and alternatives
            Row {
                rules: vec![Rule::pattern("(a|b|c)d(e|f|g)h?")],
                separators: vec![],
                examples: vec![
                    ("ade1", Some((0, "ade"))),
                    ("bdf1", Some((0, "bdf"))),
                    ("bdfh1", Some((0, "bdfh"))),
                    ("ad1", None),
                ],
            },
            // regex with repeats
            Row {
                rules: vec![Rule::pattern("a*")],
                separators: vec![],
                examples: vec![("aaa1", Some((0, "aaa"))), ("b", Some((0, "")))],
            },
            // regex with repeats in sequences
            Row {
                rules: vec![Rule::pattern("a((bc)+|(de)*)f")],
                separators: vec![],
                examples: vec![
                    ("af1", Some((0, "af"))),
                    ("adedef1", Some((0, "adedef"))),
                    ("abcbcbcf1", Some((0, "abcbcbcf"))),
                    ("a", None),
                ],
            },
            // regex with character ranges
            Row {
                rules: vec![Rule::pattern("[a-fA-F0-9]+")],
                separators: vec![],
                examples: vec![("A1ff0.", Some((0, "A1ff0")))],
            },
            // regex with perl character classes
            Row {
                rules: vec![Rule::pattern("\\w\\d\\s")],
                separators: vec![],
                examples: vec![("_0  ", Some((0, "_0 ")))],
            },
            // string
            Row {
                rules: vec![Rule::string("abc")],
                separators: vec![],
                examples: vec![("abcd", Some((0, "abc"))), ("ab", None)],
            },
            // complex rule containing strings and regexes
            Row {
                rules: vec![Rule::repeat(Rule::seq(vec![
                    Rule::string("{"),
                    Rule::pattern("[a-f]+"),
                    Rule::string("}"),
                ]))],
                separators: vec![],
                examples: vec![
                    ("{a}{", Some((0, "{a}"))),
                    ("{a}{d", Some((0, "{a}"))),
                    ("ab", None),
                ],
            },
            // longest match rule
            Row {
                rules: vec![
                    Rule::pattern("a|bc"),
                    Rule::pattern("aa"),
                    Rule::pattern("bcd"),
                ],
                separators: vec![],
                examples: vec![
                    ("a.", Some((0, "a"))),
                    ("bc.", Some((0, "bc"))),
                    ("aa.", Some((1, "aa"))),
                    ("bcd?", Some((2, "bcd"))),
                    ("b.", None),
                    ("c.", None),
                ],
            },
            // regex with an alternative including the empty string
            Row {
                rules: vec![Rule::pattern("a(b|)+c")],
                separators: vec![],
                examples: vec![
                    ("ac.", Some((0, "ac"))),
                    ("abc.", Some((0, "abc"))),
                    ("abbc.", Some((0, "abbc"))),
                ],
            },
            // separators
            Row {
                rules: vec![Rule::pattern("[a-f]+")],
                separators: vec![Rule::string("\\\n"), Rule::pattern("\\s")],
                examples: vec![
                    ("  a", Some((0, "a"))),
                    ("  \nb", Some((0, "b"))),
                    ("  \\a", None),
                    ("  \\\na", Some((0, "a"))),
                ],
            },
            // shorter tokens with higher precedence
            Row {
                rules: vec![
                    Rule::prec(2, Rule::pattern("abc")),
                    Rule::prec(1, Rule::pattern("ab[cd]e")),
                    Rule::pattern("[a-e]+"),
                ],
                separators: vec![Rule::string("\\\n"), Rule::pattern("\\s")],
                examples: vec![
                    ("abceef", Some((0, "abc"))),
                    ("abdeef", Some((1, "abde"))),
                    ("aeeeef", Some((2, "aeeee"))),
                ],
            },
            // immediate tokens with higher precedence
            Row {
                rules: vec![
                    Rule::prec(1, Rule::pattern("[^a]+")),
                    Rule::immediate_token(Rule::prec(2, Rule::pattern("[^ab]+"))),
                ],
                separators: vec![Rule::pattern("\\s")],
                examples: vec![("cccb", Some((1, "ccc")))],
            },
            Row {
                rules: vec![Rule::seq(vec![
                    Rule::string("a"),
                    Rule::choice(vec![Rule::string("b"), Rule::string("c")]),
                    Rule::string("d"),
                ])],
                separators: vec![],
                examples: vec![
                    ("abd", Some((0, "abd"))),
                    ("acd", Some((0, "acd"))),
                    ("abc", None),
                    ("ad", None),
                    ("d", None),
                    ("a", None),
                ],
            },
            // nested choices within sequences
            Row {
                rules: vec![Rule::seq(vec![
                    Rule::pattern("[0-9]+"),
                    Rule::choice(vec![
                        Rule::Blank,
                        Rule::choice(vec![Rule::seq(vec![
                            Rule::choice(vec![Rule::string("e"), Rule::string("E")]),
                            Rule::choice(vec![
                                Rule::Blank,
                                Rule::choice(vec![Rule::string("+"), Rule::string("-")]),
                            ]),
                            Rule::pattern("[0-9]+"),
                        ])]),
                    ]),
                ])],
                separators: vec![],
                examples: vec![
                    ("12", Some((0, "12"))),
                    ("12e", Some((0, "12"))),
                    ("12g", Some((0, "12"))),
                    ("12e3", Some((0, "12e3"))),
                    ("12e+", Some((0, "12"))),
                    ("12E+34 +", Some((0, "12E+34"))),
                    ("12e34", Some((0, "12e34"))),
                ],
            },
            // nested groups
            Row {
                rules: vec![Rule::seq(vec![Rule::pattern(r#"([^x\\]|\\(.|\n))+"#)])],
                separators: vec![],
                examples: vec![("abcx", Some((0, "abc"))), ("abc\\0x", Some((0, "abc\\0")))],
            },
            // allowing unrecognized escape sequences
            Row {
                rules: vec![
                    // Escaped forward slash (used in JS because '/' is the regex delimiter)
                    Rule::pattern(r#"\/"#),
                    // Escaped quotes
                    Rule::pattern(r#"\"\'"#),
                    // Quote preceded by a literal backslash
                    Rule::pattern(r#"[\\']+"#),
                ],
                separators: vec![],
                examples: vec![
                    ("/", Some((0, "/"))),
                    ("\"\'", Some((1, "\"\'"))),
                    (r#"'\'a"#, Some((2, r#"'\'"#))),
                ],
            },
            // allowing un-escaped curly braces
            Row {
                rules: vec![
                    // Un-escaped curly braces
                    Rule::pattern(r#"u{[0-9a-fA-F]+}"#),
                    // Already-escaped curly braces
                    Rule::pattern(r#"\{[ab]{3}\}"#),
                    // Unicode codepoints
                    Rule::pattern(r#"\u{1000A}"#),
                    // This isn't a repetition
                    Rule::pattern(r#"{DEADBEEF}"#),
                ],
                separators: vec![],
                examples: vec![
                    ("u{1234} ok", Some((0, "u{1234}"))),
                    ("{aba}}", Some((1, "{aba}"))),
                    ("\u{1000A}", Some((2, "\u{1000A}"))),
                    ("{DEADBEEF}", Some((3, "{DEADBEEF}"))),
                ],
            },
        ];

        for Row {
            rules,
            separators,
            examples,
        } in &table
        {
            let grammar = expand_tokens(ExtractedLexicalGrammar {
                separators: separators.clone(),
                variables: rules
                    .into_iter()
                    .map(|rule| Variable::named("", rule.clone()))
                    .collect(),
            })
            .unwrap();

            for (haystack, needle) in examples.iter() {
                assert_eq!(simulate_nfa(&grammar, haystack), *needle);
            }
        }
    }
}
