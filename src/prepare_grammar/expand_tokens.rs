use super::ExtractedLexicalGrammar;
use crate::error::{Error, Result};
use crate::grammars::{LexicalGrammar, LexicalVariable};
use crate::nfa::{CharacterSet, Nfa, NfaState};
use crate::rules::Rule;
use regex_syntax::ast::{
    parse, Ast, Class, ClassPerlKind, ClassSet, ClassSetItem, RepetitionKind, RepetitionRange,
};

pub(super) fn expand_tokens(mut grammar: ExtractedLexicalGrammar) -> Result<LexicalGrammar> {
    let mut nfa = Nfa::new();

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

        nfa.states.push(NfaState::Accept(i));
        let last_state_id = nfa.last_state_id();
        expand_rule(&variable.rule, &mut nfa, last_state_id, false).map_err(|e| match e {
            Error::RegexError(msg) => Error::RegexError(format!("Rule {} {}", variable.name, msg)),
            _ => e,
        })?;

        if !is_immediate_token {
            let last_state_id = nfa.last_state_id();
            expand_rule(&separator_rule, &mut nfa, last_state_id, true)?;
        }

        variables.push(LexicalVariable {
            name: variable.name,
            kind: variable.kind,
            start_state: nfa.last_state_id(),
        });
    }

    Ok(LexicalGrammar { nfa, variables })
}

fn expand_rule(rule: &Rule, nfa: &mut Nfa, mut next_state_id: u32, is_sep: bool) -> Result<bool> {
    match rule {
        Rule::Pattern(s) => {
            let ast = parse::Parser::new()
                .parse(&s)
                .map_err(|e| Error::GrammarError(e.to_string()))?;
            expand_regex(&ast, nfa, next_state_id, is_sep)
        }
        Rule::String(s) => {
            for c in s.chars().rev() {
                nfa.prepend(|last_state_id| NfaState::Advance {
                    chars: CharacterSet::empty().add_char(c),
                    state_id: last_state_id,
                    is_sep,
                });
            }
            Ok(s.len() > 0)
        }
        Rule::Choice(elements) => {
            let mut alternative_state_ids = Vec::new();
            for element in elements {
                if expand_rule(element, nfa, next_state_id, is_sep)? {
                    alternative_state_ids.push(nfa.last_state_id());
                } else {
                    alternative_state_ids.push(next_state_id);
                }
            }
            alternative_state_ids.retain(|i| *i != nfa.last_state_id());
            for alternative_state_id in alternative_state_ids {
                nfa.prepend(|last_state_id| NfaState::Split(last_state_id, alternative_state_id));
            }
            Ok(true)
        }
        Rule::Seq(elements) => {
            let mut result = false;
            for element in elements.into_iter().rev() {
                if expand_rule(element, nfa, next_state_id, is_sep)? {
                    result = true;
                }
                next_state_id = nfa.last_state_id();
            }
            Ok(result)
        }
        Rule::Repeat(rule) => {
            nfa.states.push(NfaState::Accept(0)); // Placeholder for split
            let split_state_id = nfa.last_state_id();
            if expand_rule(rule, nfa, split_state_id, is_sep)? {
                nfa.states[split_state_id as usize] =
                    NfaState::Split(nfa.last_state_id(), next_state_id);
                Ok(true)
            } else {
                Ok(false)
            }
        }
        Rule::Metadata { rule, .. } => {
            // TODO - implement precedence
            expand_rule(rule, nfa, next_state_id, is_sep)
        }
        Rule::Blank => Ok(false),
        _ => Err(Error::grammar(&format!("Unexpected rule {:?}", rule))),
    }
}

fn expand_one_or_more(ast: &Ast, nfa: &mut Nfa, next_state_id: u32, is_sep: bool) -> Result<bool> {
    nfa.states.push(NfaState::Accept(0)); // Placeholder for split
    let split_state_id = nfa.last_state_id();
    if expand_regex(&ast, nfa, split_state_id, is_sep)? {
        nfa.states[split_state_id as usize] = NfaState::Split(nfa.last_state_id(), next_state_id);
        Ok(true)
    } else {
        nfa.states.pop();
        Ok(false)
    }
}

fn expand_zero_or_one(ast: &Ast, nfa: &mut Nfa, next_state_id: u32, is_sep: bool) -> Result<bool> {
    if expand_regex(ast, nfa, next_state_id, is_sep)? {
        nfa.prepend(|last_state_id| NfaState::Split(next_state_id, last_state_id));
        Ok(true)
    } else {
        Ok(false)
    }
}

fn expand_zero_or_more(ast: &Ast, nfa: &mut Nfa, next_state_id: u32, is_sep: bool) -> Result<bool> {
    if expand_one_or_more(&ast, nfa, next_state_id, is_sep)? {
        nfa.prepend(|last_state_id| NfaState::Split(last_state_id, next_state_id));
        Ok(true)
    } else {
        Ok(false)
    }
}

fn expand_count(
    ast: &Ast,
    count: u32,
    nfa: &mut Nfa,
    mut next_state_id: u32,
    is_sep: bool,
) -> Result<bool> {
    let mut result = false;
    for _ in 0..count {
        if expand_regex(ast, nfa, next_state_id, is_sep)? {
            result = true;
            next_state_id = nfa.last_state_id();
        }
    }
    Ok(result)
}

fn expand_regex(ast: &Ast, nfa: &mut Nfa, mut next_state_id: u32, is_sep: bool) -> Result<bool> {
    match ast {
        Ast::Empty(_) => Ok(false),
        Ast::Flags(_) => Err(Error::regex("Flags are not supported")),
        Ast::Literal(literal) => {
            nfa.states.push(NfaState::Advance {
                chars: CharacterSet::Include(vec![literal.c]),
                state_id: next_state_id,
                is_sep,
            });
            Ok(true)
        }
        Ast::Dot(_) => {
            nfa.states.push(NfaState::Advance {
                chars: CharacterSet::Exclude(vec!['\n']),
                state_id: next_state_id,
                is_sep,
            });
            Ok(true)
        }
        Ast::Assertion(_) => Err(Error::regex("Assertions are not supported")),
        Ast::Class(class) => match class {
            Class::Unicode(_) => Err(Error::regex("Unicode character classes are not supported")),
            Class::Perl(class) => {
                nfa.states.push(NfaState::Advance {
                    chars: expand_perl_character_class(&class.kind),
                    state_id: next_state_id,
                    is_sep,
                });
                Ok(true)
            }
            Class::Bracketed(class) => match &class.kind {
                ClassSet::Item(item) => {
                    let character_set = expand_character_class(&item)?;
                    nfa.states.push(NfaState::Advance {
                        chars: character_set,
                        state_id: next_state_id,
                        is_sep,
                    });
                    Ok(true)
                }
                ClassSet::BinaryOp(_) => Err(Error::regex(
                    "Binary operators in character classes aren't supported",
                )),
            },
        },
        Ast::Repetition(repetition) => match repetition.op.kind {
            RepetitionKind::ZeroOrOne => {
                expand_zero_or_one(&repetition.ast, nfa, next_state_id, is_sep)
            }
            RepetitionKind::OneOrMore => {
                expand_one_or_more(&repetition.ast, nfa, next_state_id, is_sep)
            }
            RepetitionKind::ZeroOrMore => {
                expand_zero_or_more(&repetition.ast, nfa, next_state_id, is_sep)
            }
            RepetitionKind::Range(RepetitionRange::Exactly(count)) => {
                expand_count(&repetition.ast, count, nfa, next_state_id, is_sep)
            }
            RepetitionKind::Range(RepetitionRange::AtLeast(min)) => {
                if expand_zero_or_more(&repetition.ast, nfa, next_state_id, is_sep)? {
                    expand_count(ast, min, nfa, next_state_id, is_sep)
                } else {
                    Ok(false)
                }
            }
            RepetitionKind::Range(RepetitionRange::Bounded(min, max)) => {
                let mut result = expand_count(&repetition.ast, min, nfa, next_state_id, is_sep)?;
                for _ in min..max {
                    if result {
                        next_state_id = nfa.last_state_id();
                    }
                    if expand_zero_or_one(&repetition.ast, nfa, next_state_id, is_sep)? {
                        result = true;
                    }
                }
                Ok(result)
            }
        },
        Ast::Group(group) => expand_regex(&group.ast, nfa, nfa.last_state_id(), is_sep),
        Ast::Alternation(alternation) => {
            let mut alternative_state_ids = Vec::new();
            for ast in alternation.asts.iter() {
                if expand_regex(&ast, nfa, next_state_id, is_sep)? {
                    alternative_state_ids.push(nfa.last_state_id());
                } else {
                    alternative_state_ids.push(next_state_id);
                }
            }
            alternative_state_ids.retain(|i| *i != nfa.last_state_id());
            for alternative_state_id in alternative_state_ids {
                nfa.prepend(|last_state_id| NfaState::Split(last_state_id, alternative_state_id));
            }
            Ok(true)
        }
        Ast::Concat(concat) => {
            let mut result = false;
            for ast in concat.asts.iter().rev() {
                if expand_regex(&ast, nfa, next_state_id, is_sep)? {
                    result = true;
                    next_state_id = nfa.last_state_id();
                }
            }
            Ok(result)
        }
    }
}

fn expand_character_class(item: &ClassSetItem) -> Result<CharacterSet> {
    match item {
        ClassSetItem::Empty(_) => Ok(CharacterSet::Include(Vec::new())),
        ClassSetItem::Literal(literal) => Ok(CharacterSet::Include(vec![literal.c])),
        ClassSetItem::Range(range) => {
            Ok(CharacterSet::empty().add_range(range.start.c, range.end.c))
        }
        ClassSetItem::Union(union) => {
            let mut result = CharacterSet::empty();
            for item in &union.items {
                result = result.add(expand_character_class(&item)?);
            }
            Ok(result)
        }
        ClassSetItem::Perl(class) => Ok(expand_perl_character_class(&class.kind)),
        _ => Err(Error::regex(&format!(
            "Unsupported character class syntax {:?}",
            item
        ))),
    }
}

fn expand_perl_character_class(item: &ClassPerlKind) -> CharacterSet {
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

#[cfg(test)]
mod tests {
    use super::*;
    use crate::grammars::Variable;
    use crate::nfa::NfaCursor;

    fn simulate_nfa<'a>(grammar: &'a LexicalGrammar, s: &'a str) -> Option<(usize, &'a str)> {
        let start_states = grammar.variables.iter().map(|v| v.start_state).collect();
        let mut cursor = NfaCursor::new(&grammar.nfa, start_states);

        let mut result = None;
        let mut start_char = 0;
        let mut end_char = 0;
        for c in s.chars() {
            if let Some(id) = cursor.finished_id() {
                result = Some((id, &s[start_char..end_char]));
            }
            if cursor.advance(c) {
                end_char += 1;
                if cursor.in_separator() {
                    start_char = end_char;
                }
            } else {
                break;
            }
        }

        if let Some(id) = cursor.finished_id() {
            result = Some((id, &s[start_char..end_char]));
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
