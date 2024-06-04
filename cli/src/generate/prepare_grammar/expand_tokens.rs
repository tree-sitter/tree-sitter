use std::collections::HashMap;

use anyhow::{anyhow, Context, Result};
use lazy_static::lazy_static;
use regex_syntax::{
    ast::parse,
    hir::{translate::Translator, Hir, HirKind},
};

use super::ExtractedLexicalGrammar;
use crate::generate::{
    grammars::{LexicalGrammar, LexicalVariable},
    nfa::{CharacterSet, Nfa, NfaState},
    rules::{Precedence, Rule},
};

lazy_static! {
    static ref UNICODE_CATEGORIES: HashMap<&'static str, Vec<u32>> =
        serde_json::from_str(UNICODE_CATEGORIES_JSON).unwrap();
    static ref UNICODE_PROPERTIES: HashMap<&'static str, Vec<u32>> =
        serde_json::from_str(UNICODE_PROPERTIES_JSON).unwrap();
    static ref UNICODE_CATEGORY_ALIASES: HashMap<&'static str, String> =
        serde_json::from_str(UNICODE_CATEGORY_ALIASES_JSON).unwrap();
    static ref UNICODE_PROPERTY_ALIASES: HashMap<&'static str, String> =
        serde_json::from_str(UNICODE_PROPERTY_ALIASES_JSON).unwrap();
}

const UNICODE_CATEGORIES_JSON: &str = include_str!("./unicode-categories.json");
const UNICODE_PROPERTIES_JSON: &str = include_str!("./unicode-properties.json");
const UNICODE_CATEGORY_ALIASES_JSON: &str = include_str!("./unicode-category-aliases.json");
const UNICODE_PROPERTY_ALIASES_JSON: &str = include_str!("./unicode-property-aliases.json");

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

const fn get_completion_precedence(rule: &Rule) -> i32 {
    if let Rule::Metadata { params, .. } = rule {
        if let Precedence::Integer(p) = params.precedence {
            return p;
        }
    }
    0
}

pub fn expand_tokens(mut grammar: ExtractedLexicalGrammar) -> Result<LexicalGrammar> {
    let mut builder = NfaBuilder {
        nfa: Nfa::new(),
        is_sep: true,
        precedence_stack: vec![0],
    };

    let separator_rule = if grammar.separators.is_empty() {
        Rule::Blank
    } else {
        grammar.separators.push(Rule::Blank);
        Rule::repeat(Rule::choice(grammar.separators))
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
            .with_context(|| format!("Error processing rule {}", variable.name))?;

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
            Rule::Pattern(s, f) => {
                let ast = parse::Parser::new().parse(s)?;
                let hir = Translator::new().translate(s, &ast)?;
                self.expand_regex(&hir, next_state_id, f.contains('i'))
            }
            Rule::String(s) => {
                for c in s.chars().rev() {
                    self.push_advance(CharacterSet::empty().add_char(c), next_state_id);
                    next_state_id = self.nfa.last_state_id();
                }
                Ok(!s.is_empty())
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
                for element in elements.iter().rev() {
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
                let has_precedence = if let Precedence::Integer(precedence) = &params.precedence {
                    self.precedence_stack.push(*precedence);
                    true
                } else {
                    false
                };
                let result = self.expand_rule(rule, next_state_id);
                if has_precedence {
                    self.precedence_stack.pop();
                }
                result
            }
            Rule::Blank => Ok(false),
            _ => Err(anyhow!("Grammar error: Unexpected rule {rule:?}")),
        }
    }

    fn expand_regex(
        &mut self,
        hir: &Hir,
        mut next_state_id: u32,
        case_insensitive: bool,
    ) -> Result<bool> {
        const fn inverse_char(c: char) -> char {
            match c {
                'a'..='z' => (c as u8 - b'a' + b'A') as char,
                'A'..='Z' => (c as u8 - b'A' + b'a') as char,
                c => c,
            }
        }

        fn with_inverse_char(mut chars: CharacterSet) -> CharacterSet {
            for char in chars.clone().chars() {
                let inverted = inverse_char(char);
                if char != inverted {
                    chars = chars.add_char(inverted);
                }
            }
            chars
        }

        match hir.kind() {
            HirKind::Empty => Ok(false),
            HirKind::Literal(literal) => {
                for character in std::str::from_utf8(&literal.0)?.chars() {
                    let mut char_set = CharacterSet::from_char(character);
                    if case_insensitive {
                        let inverted = inverse_char(character);
                        if character != inverted {
                            char_set = char_set.add_char(inverted);
                        }
                    }
                    self.push_advance(char_set, next_state_id);
                }

                Ok(true)
            }
            HirKind::Concat(concat) => {
                let mut result = false;
                for hir in concat.iter().rev() {
                    if self.expand_regex(hir, next_state_id, case_insensitive)? {
                        result = true;
                        next_state_id = self.nfa.last_state_id();
                    }
                }
                Ok(result)
            }
            HirKind::Alternation(alternations) => {
                let mut alternative_state_ids = Vec::new();
                for hir in alternations {
                    if self.expand_regex(hir, next_state_id, case_insensitive)? {
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
            HirKind::Repetition(repetition) => match (repetition.min, repetition.max) {
                (0, Some(1)) => {
                    self.expand_zero_or_one(&repetition.sub, next_state_id, case_insensitive)
                }
                (1, None) => {
                    self.expand_one_or_more(&repetition.sub, next_state_id, case_insensitive)
                }
                (0, None) => {
                    self.expand_zero_or_more(&repetition.sub, next_state_id, case_insensitive)
                }
                (min, Some(max)) if min == max => {
                    self.expand_count(&repetition.sub, min, next_state_id, case_insensitive)
                }
                (min, None) => {
                    if self.expand_zero_or_more(&repetition.sub, next_state_id, case_insensitive)? {
                        self.expand_count(&repetition.sub, min, next_state_id, case_insensitive)
                    } else {
                        Ok(false)
                    }
                }
                (min, Some(max)) => {
                    let mut result =
                        self.expand_count(&repetition.sub, min, next_state_id, case_insensitive)?;
                    for _ in min..max {
                        if result {
                            next_state_id = self.nfa.last_state_id();
                        }
                        if self.expand_zero_or_one(
                            &repetition.sub,
                            next_state_id,
                            case_insensitive,
                        )? {
                            result = true;
                        }
                    }
                    Ok(result)
                }
            },
            HirKind::Class(class) => match class {
                regex_syntax::hir::Class::Unicode(class) => {
                    let mut chars = CharacterSet::default();
                    for c in class.ranges() {
                        chars = chars.add_range(c.start(), c.end());
                    }
                    if case_insensitive {
                        //??
                        chars = with_inverse_char(chars);
                    }
                    self.push_advance(chars, next_state_id);
                    Ok(true)
                }
                regex_syntax::hir::Class::Bytes(bytes_class) => {
                    let mut chars = CharacterSet::default();
                    for c in bytes_class.ranges() {
                        chars = chars.add_range(c.start().into(), c.end().into());
                    }
                    if case_insensitive {
                        //??
                        chars = with_inverse_char(chars);
                    }
                    self.push_advance(chars, next_state_id);
                    Ok(true)
                }
            },
            HirKind::Look(_) => Err(anyhow!("Regex error: Assertions are not supported")),
            HirKind::Capture(capture) => {
                self.expand_regex(&capture.sub, next_state_id, case_insensitive)
            } /*Hir::Flags(_) => Err(anyhow!("Regex error: Flags are not supported")),
              Ast::Literal(literal) => {}
              Ast::Dot(_) => {
                  self.push_advance(CharacterSet::from_char('\n').negate(), next_state_id);
                  Ok(true)
              }
              Ast::Assertion(_) => Err(anyhow!("Regex error: Assertions are not supported")),
              Ast::ClassUnicode(class) => {
                  let mut chars = self.expand_unicode_character_class(&class.kind)?;
                  if class.negated {
                      chars = chars.negate();
                  }
                  if case_insensitive {
                      chars = with_inverse_char(chars);
                  }
                  self.push_advance(chars, next_state_id);
                  Ok(true)
              }
              Ast::ClassPerl(class) => {
                  let mut chars = self.expand_perl_character_class(&class.kind);
                  if class.negated {
                      chars = chars.negate();
                  }
                  if case_insensitive {
                      chars = with_inverse_char(chars);
                  }
                  self.push_advance(chars, next_state_id);
                  Ok(true)
              }
              Ast::ClassBracketed(class) => {
                  let mut chars = self.translate_class_set(&class.kind)?;
                  if class.negated {
                      chars = chars.negate();
                  }
                  if case_insensitive {
                      chars = with_inverse_char(chars);
                  }
                  self.push_advance(chars, next_state_id);
                  Ok(true)
              }
              Ast::Repetition(repetition) => match repetition.op.kind {
                  RepetitionKind::ZeroOrOne => {
                      self.expand_zero_or_one(&repetition.ast, next_state_id, case_insensitive)
                  }
                  RepetitionKind::OneOrMore => {
                      self.expand_one_or_more(&repetition.ast, next_state_id, case_insensitive)
                  }
                  RepetitionKind::ZeroOrMore => {
                      self.expand_zero_or_more(&repetition.ast, next_state_id, case_insensitive)
                  }
                  RepetitionKind::Range(RepetitionRange::Exactly(count)) => {
                      self.expand_count(&repetition.ast, count, next_state_id, case_insensitive)
                  }
                  RepetitionKind::Range(RepetitionRange::AtLeast(min)) => {
                      if self.expand_zero_or_more(&repetition.ast, next_state_id, case_insensitive)? {
                          self.expand_count(&repetition.ast, min, next_state_id, case_insensitive)
                      } else {
                          Ok(false)
                      }
                  }
                  RepetitionKind::Range(RepetitionRange::Bounded(min, max)) => {
                      let mut result =
                          self.expand_count(&repetition.ast, min, next_state_id, case_insensitive)?;
                      for _ in min..max {
                          if result {
                              next_state_id = self.nfa.last_state_id();
                          }
                          if self.expand_zero_or_one(
                              &repetition.ast,
                              next_state_id,
                              case_insensitive,
                          )? {
                              result = true;
                          }
                      }
                      Ok(result)
                  }
              },
              Ast::Group(group) => self.expand_regex(&group.ast, next_state_id, case_insensitive),
              Ast::Alternation(alternation) => {}
              Ast::Concat(concat) => {}*/
        }
    }

    fn expand_one_or_more(
        &mut self,
        hir: &Hir,
        next_state_id: u32,
        case_insensitive: bool,
    ) -> Result<bool> {
        self.nfa.states.push(NfaState::Accept {
            variable_index: 0,
            precedence: 0,
        }); // Placeholder for split
        let split_state_id = self.nfa.last_state_id();
        if self.expand_regex(hir, split_state_id, case_insensitive)? {
            self.nfa.states[split_state_id as usize] =
                NfaState::Split(self.nfa.last_state_id(), next_state_id);
            Ok(true)
        } else {
            self.nfa.states.pop();
            Ok(false)
        }
    }

    fn expand_zero_or_one(
        &mut self,
        hir: &Hir,
        next_state_id: u32,
        case_insensitive: bool,
    ) -> Result<bool> {
        if self.expand_regex(hir, next_state_id, case_insensitive)? {
            self.push_split(next_state_id);
            Ok(true)
        } else {
            Ok(false)
        }
    }

    fn expand_zero_or_more(
        &mut self,
        hir: &Hir,
        next_state_id: u32,
        case_insensitive: bool,
    ) -> Result<bool> {
        if self.expand_one_or_more(hir, next_state_id, case_insensitive)? {
            self.push_split(next_state_id);
            Ok(true)
        } else {
            Ok(false)
        }
    }

    fn expand_count(
        &mut self,
        hir: &Hir,
        count: u32,
        mut next_state_id: u32,
        case_insensitive: bool,
    ) -> Result<bool> {
        let mut result = false;
        for _ in 0..count {
            if self.expand_regex(hir, next_state_id, case_insensitive)? {
                result = true;
                next_state_id = self.nfa.last_state_id();
            }
        }
        Ok(result)
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
    use crate::generate::{
        grammars::Variable,
        nfa::{NfaCursor, NfaTransition},
    };

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
                rules: vec![Rule::pattern("(a|b|c)d(e|f|g)h?", "")],
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
                rules: vec![Rule::pattern("a*", "")],
                separators: vec![],
                examples: vec![("aaa1", Some((0, "aaa"))), ("b", Some((0, "")))],
            },
            // regex with repeats in sequences
            Row {
                rules: vec![Rule::pattern("a((bc)+|(de)*)f", "")],
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
                rules: vec![Rule::pattern("[a-fA-F0-9]+", "")],
                separators: vec![],
                examples: vec![("A1ff0.", Some((0, "A1ff0")))],
            },
            // regex with perl character classes
            Row {
                rules: vec![Rule::pattern("\\w\\d\\s", "")],
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
                    Rule::pattern("[a-f]+", ""),
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
                    Rule::pattern("a|bc", ""),
                    Rule::pattern("aa", ""),
                    Rule::pattern("bcd", ""),
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
                rules: vec![Rule::pattern("a(b|)+c", "")],
                separators: vec![],
                examples: vec![
                    ("ac.", Some((0, "ac"))),
                    ("abc.", Some((0, "abc"))),
                    ("abbc.", Some((0, "abbc"))),
                ],
            },
            // separators
            Row {
                rules: vec![Rule::pattern("[a-f]+", "")],
                separators: vec![Rule::string("\\\n"), Rule::pattern("\\s", "")],
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
                    Rule::prec(Precedence::Integer(2), Rule::pattern("abc", "")),
                    Rule::prec(Precedence::Integer(1), Rule::pattern("ab[cd]e", "")),
                    Rule::pattern("[a-e]+", ""),
                ],
                separators: vec![Rule::string("\\\n"), Rule::pattern("\\s", "")],
                examples: vec![
                    ("abceef", Some((0, "abc"))),
                    ("abdeef", Some((1, "abde"))),
                    ("aeeeef", Some((2, "aeeee"))),
                ],
            },
            // immediate tokens with higher precedence
            Row {
                rules: vec![
                    Rule::prec(Precedence::Integer(1), Rule::pattern("[^a]+", "")),
                    Rule::immediate_token(Rule::prec(
                        Precedence::Integer(2),
                        Rule::pattern("[^ab]+", ""),
                    )),
                ],
                separators: vec![Rule::pattern("\\s", "")],
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
                    Rule::pattern("[0-9]+", ""),
                    Rule::choice(vec![
                        Rule::Blank,
                        Rule::choice(vec![Rule::seq(vec![
                            Rule::choice(vec![Rule::string("e"), Rule::string("E")]),
                            Rule::choice(vec![
                                Rule::Blank,
                                Rule::choice(vec![Rule::string("+"), Rule::string("-")]),
                            ]),
                            Rule::pattern("[0-9]+", ""),
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
                rules: vec![Rule::seq(vec![Rule::pattern(r"([^x\\]|\\(.|\n))+", "")])],
                separators: vec![],
                examples: vec![("abcx", Some((0, "abc"))), ("abc\\0x", Some((0, "abc\\0")))],
            },
            // allowing unrecognized escape sequences
            Row {
                rules: vec![
                    // Escaped forward slash (used in JS because '/' is the regex delimiter)
                    Rule::pattern(r"\/", ""),
                    // Escaped quotes
                    Rule::pattern(r#"\"\'"#, ""),
                    // Quote preceded by a literal backslash
                    Rule::pattern(r"[\\']+", ""),
                ],
                separators: vec![],
                examples: vec![
                    ("/", Some((0, "/"))),
                    ("\"\'", Some((1, "\"\'"))),
                    (r"'\'a", Some((2, r"'\'"))),
                ],
            },
            // unicode property escapes
            Row {
                rules: vec![
                    Rule::pattern(r"\p{L}+\P{L}+", ""),
                    Rule::pattern(r"\p{White_Space}+\P{White_Space}+[\p{White_Space}]*", ""),
                ],
                separators: vec![],
                examples: vec![
                    ("  123   abc", Some((1, "  123   "))),
                    ("ბΨƁ___ƀƔ", Some((0, "ბΨƁ___"))),
                ],
            },
            // unicode property escapes in bracketed sets
            Row {
                rules: vec![Rule::pattern(r"[\p{L}\p{Nd}]+", "")],
                separators: vec![],
                examples: vec![("abΨ12٣٣, ok", Some((0, "abΨ12٣٣")))],
            },
            // unicode character escapes
            Row {
                rules: vec![
                    Rule::pattern(r"\u{00dc}", ""),
                    Rule::pattern(r"\U{000000dd}", ""),
                    Rule::pattern(r"\u00de", ""),
                    Rule::pattern(r"\U000000df", ""),
                ],
                separators: vec![],
                examples: vec![
                    ("\u{00dc}", Some((0, "\u{00dc}"))),
                    ("\u{00dd}", Some((1, "\u{00dd}"))),
                    ("\u{00de}", Some((2, "\u{00de}"))),
                    ("\u{00df}", Some((3, "\u{00df}"))),
                ],
            },
            Row {
                rules: vec![
                    Rule::pattern(r"u\{[0-9a-fA-F]+\}", ""),
                    // Already-escaped curly braces
                    Rule::pattern(r"\{[ab]{3}\}", ""),
                    // Unicode codepoints
                    Rule::pattern(r"\u{1000A}", ""),
                    // Unicode codepoints (lowercase)
                    Rule::pattern(r"\u{1000b}", ""),
                ],
                separators: vec![],
                examples: vec![
                    ("u{1234} ok", Some((0, "u{1234}"))),
                    ("{aba}}", Some((1, "{aba}"))),
                    ("\u{1000A}", Some((2, "\u{1000A}"))),
                    ("\u{1000b}", Some((3, "\u{1000b}"))),
                ],
            },
            // Emojis
            Row {
                rules: vec![Rule::pattern(r"\p{Emoji}+", "")],
                separators: vec![],
                examples: vec![
                    ("🐎", Some((0, "🐎"))),
                    ("🐴🐴", Some((0, "🐴🐴"))),
                    ("#0", Some((0, "#0"))), // These chars are technically emojis!
                    ("⻢", None),
                    ("♞", None),
                    ("horse", None),
                ],
            },
            // Intersection
            Row {
                rules: vec![Rule::pattern(r"[[0-7]&&[4-9]]+", "")],
                separators: vec![],
                examples: vec![
                    ("456", Some((0, "456"))),
                    ("64", Some((0, "64"))),
                    ("452", Some((0, "45"))),
                    ("91", None),
                    ("8", None),
                    ("3", None),
                ],
            },
            // Difference
            Row {
                rules: vec![Rule::pattern(r"[[0-9]--[4-7]]+", "")],
                separators: vec![],
                examples: vec![
                    ("123", Some((0, "123"))),
                    ("83", Some((0, "83"))),
                    ("9", Some((0, "9"))),
                    ("124", Some((0, "12"))),
                    ("67", None),
                    ("4", None),
                ],
            },
            // Symmetric difference
            Row {
                rules: vec![Rule::pattern(r"[[0-7]~~[4-9]]+", "")],
                separators: vec![],
                examples: vec![
                    ("123", Some((0, "123"))),
                    ("83", Some((0, "83"))),
                    ("9", Some((0, "9"))),
                    ("124", Some((0, "12"))),
                    ("67", None),
                    ("4", None),
                ],
            },
            // Nested set operations
            Row {
                //               0 1 2 3 4 5 6 7 8 9
                // [0-5]:        y y y y y y
                // [2-4]:            y y y
                // [0-5]--[2-4]: y y       y
                // [3-9]:              y y y y y y y
                // [6-7]:                    y y
                // [3-9]--[5-7]:       y y y     y y
                // final regex:  y y   y y       y y
                rules: vec![Rule::pattern(r"[[[0-5]--[2-4]]~~[[3-9]--[6-7]]]+", "")],
                separators: vec![],
                examples: vec![
                    ("01", Some((0, "01"))),
                    ("432", Some((0, "43"))),
                    ("8", Some((0, "8"))),
                    ("9", Some((0, "9"))),
                    ("2", None),
                    ("567", None),
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
                    .iter()
                    .map(|rule| Variable::named("", rule.clone()))
                    .collect(),
            })
            .unwrap();

            for (haystack, needle) in examples {
                assert_eq!(simulate_nfa(&grammar, haystack), *needle);
            }
        }
    }
}
