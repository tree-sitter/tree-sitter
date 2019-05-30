use super::ExtractedLexicalGrammar;
use crate::error::{Error, Result};
use crate::generate::grammars::{LexicalGrammar, LexicalVariable};
use crate::generate::nfa::{CharacterSet, Nfa, NfaState};
use crate::generate::rules::Rule;
use lazy_static::lazy_static;
use regex::Regex;
use regex_syntax::ast::{
    parse, Ast, Class, ClassPerlKind, ClassSet, ClassSetItem, RepetitionKind, RepetitionRange,
};
use std::i32;

lazy_static! {
    static ref CURLY_BRACE_REGEX: Regex =
        Regex::new(r#"(^|[^\\])\{([^}]*[^0-9A-F,}][^}]*)\}"#).unwrap();
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
    let content = CURLY_BRACE_REGEX.replace(content, "$1\\{$2\\}");
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
                let ast = parse::Parser::new().parse(&s)?;
                self.expand_regex(&ast, next_state_id)
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

    fn expand_regex(&mut self, ast: &Ast, mut next_state_id: u32) -> Result<bool> {
        match ast {
            Ast::Empty(_) => Ok(false),
            Ast::Flags(_) => Err(Error::regex("Flags are not supported")),
            Ast::Literal(literal) => {
                self.push_advance(CharacterSet::Include(vec![literal.c]), next_state_id);
                Ok(true)
            }
            Ast::Dot(_) => {
                self.push_advance(CharacterSet::Exclude(vec!['\n']), next_state_id);
                Ok(true)
            }
            Ast::Assertion(_) => Err(Error::regex("Assertions are not supported")),
            Ast::Class(class) => match class {
                Class::Unicode(_) => {
                    Err(Error::regex("Unicode character classes are not supported"))
                }
                Class::Perl(class) => {
                    let mut chars = self.expand_perl_character_class(&class.kind);
                    if class.negated {
                        chars = chars.negate();
                    }
                    self.push_advance(chars, next_state_id);
                    Ok(true)
                }
                Class::Bracketed(class) => match &class.kind {
                    ClassSet::Item(item) => {
                        let mut chars = self.expand_character_class(&item)?;
                        if class.negated {
                            chars = chars.negate();
                        }
                        self.push_advance(chars, next_state_id);
                        Ok(true)
                    }
                    ClassSet::BinaryOp(_) => Err(Error::regex(
                        "Binary operators in character classes aren't supported",
                    )),
                },
            },
            Ast::Repetition(repetition) => match repetition.op.kind {
                RepetitionKind::ZeroOrOne => {
                    self.expand_zero_or_one(&repetition.ast, next_state_id)
                }
                RepetitionKind::OneOrMore => {
                    self.expand_one_or_more(&repetition.ast, next_state_id)
                }
                RepetitionKind::ZeroOrMore => {
                    self.expand_zero_or_more(&repetition.ast, next_state_id)
                }
                RepetitionKind::Range(RepetitionRange::Exactly(count)) => {
                    self.expand_count(&repetition.ast, count, next_state_id)
                }
                RepetitionKind::Range(RepetitionRange::AtLeast(min)) => {
                    if self.expand_zero_or_more(&repetition.ast, next_state_id)? {
                        self.expand_count(&repetition.ast, min, next_state_id)
                    } else {
                        Ok(false)
                    }
                }
                RepetitionKind::Range(RepetitionRange::Bounded(min, max)) => {
                    let mut result = self.expand_count(&repetition.ast, min, next_state_id)?;
                    for _ in min..max {
                        if result {
                            next_state_id = self.nfa.last_state_id();
                        }
                        if self.expand_zero_or_one(&repetition.ast, next_state_id)? {
                            result = true;
                        }
                    }
                    Ok(result)
                }
            },
            Ast::Group(group) => self.expand_regex(&group.ast, next_state_id),
            Ast::Alternation(alternation) => {
                let mut alternative_state_ids = Vec::new();
                for ast in alternation.asts.iter() {
                    if self.expand_regex(&ast, next_state_id)? {
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
            Ast::Concat(concat) => {
                let mut result = false;
                for ast in concat.asts.iter().rev() {
                    if self.expand_regex(&ast, next_state_id)? {
                        result = true;
                        next_state_id = self.nfa.last_state_id();
                    }
                }
                Ok(result)
            }
        }
    }

    fn expand_one_or_more(&mut self, ast: &Ast, next_state_id: u32) -> Result<bool> {
        self.nfa.states.push(NfaState::Accept {
            variable_index: 0,
            precedence: 0,
        }); // Placeholder for split
        let split_state_id = self.nfa.last_state_id();
        if self.expand_regex(&ast, split_state_id)? {
            self.nfa.states[split_state_id as usize] =
                NfaState::Split(self.nfa.last_state_id(), next_state_id);
            Ok(true)
        } else {
            self.nfa.states.pop();
            Ok(false)
        }
    }

    fn expand_zero_or_one(&mut self, ast: &Ast, next_state_id: u32) -> Result<bool> {
        if self.expand_regex(ast, next_state_id)? {
            self.push_split(next_state_id);
            Ok(true)
        } else {
            Ok(false)
        }
    }

    fn expand_zero_or_more(&mut self, ast: &Ast, next_state_id: u32) -> Result<bool> {
        if self.expand_one_or_more(&ast, next_state_id)? {
            self.push_split(next_state_id);
            Ok(true)
        } else {
            Ok(false)
        }
    }

    fn expand_count(&mut self, ast: &Ast, count: u32, mut next_state_id: u32) -> Result<bool> {
        let mut result = false;
        for _ in 0..count {
            if self.expand_regex(ast, next_state_id)? {
                result = true;
                next_state_id = self.nfa.last_state_id();
            }
        }
        Ok(result)
    }

    fn expand_character_class(&self, item: &ClassSetItem) -> Result<CharacterSet> {
        match item {
            ClassSetItem::Empty(_) => Ok(CharacterSet::Include(Vec::new())),
            ClassSetItem::Literal(literal) => Ok(CharacterSet::Include(vec![literal.c])),
            ClassSetItem::Range(range) => {
                Ok(CharacterSet::empty().add_range(range.start.c, range.end.c))
            }
            ClassSetItem::Union(union) => {
                let mut result = CharacterSet::empty();
                for item in &union.items {
                    result = result.add(&self.expand_character_class(&item)?);
                }
                Ok(result)
            }
            ClassSetItem::Perl(class) => Ok(self.expand_perl_character_class(&class.kind)),
            _ => Err(Error::regex(&format!(
                "Unsupported character class syntax {:?}",
                item
            ))),
        }
    }

    fn expand_perl_character_class(&self, item: &ClassPerlKind) -> CharacterSet {
        match item {
            ClassPerlKind::Digit => CharacterSet::empty().add_range('0', '9'),
            ClassPerlKind::Space => CharacterSet::empty()
                .add_char(' ')
                .add_char('\t')
                .add_char('\r')
                .add_char('\n'),
            ClassPerlKind::Word => CharacterSet::empty()
                .add_char('_')
                .add_range('A', 'Z')
                .add_range('a', 'z')
                .add_range('0', '9'),
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
                ],
                separators: vec![],
                examples: vec![
                    ("u{1234} ok", Some((0, "u{1234}"))),
                    ("{aba}}", Some((1, "{aba}"))),
                    ("\u{1000A}", Some((2, "\u{1000A}"))),
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
