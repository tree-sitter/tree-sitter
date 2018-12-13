use super::ExtractedLexicalGrammar;
use crate::error::{Error, Result};
use crate::grammars::{LexicalGrammar, LexicalVariable};
use crate::nfa::{CharacterSet, Nfa, NfaState};
use crate::rules::Rule;
use regex_syntax::ast::{parse, Ast, Class, ClassPerlKind, ClassSet, ClassSetItem, RepetitionKind};

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
        _ => Err(Error::regex("Unsupported character class syntax")),
    }
}

fn expand_regex(ast: &Ast, nfa: &mut Nfa, mut next_state_index: u32, is_sep: bool) -> Result<bool> {
    match ast {
        Ast::Empty(_) => Ok(false),
        Ast::Flags(_) => Err(Error::regex("Flags are not supported")),
        Ast::Literal(literal) => {
            nfa.states.push(NfaState::Advance {
                chars: CharacterSet::Include(vec![literal.c]),
                state: next_state_index,
                is_sep,
            });
            Ok(true)
        }
        Ast::Dot(_) => {
            nfa.states.push(NfaState::Advance {
                chars: CharacterSet::Exclude(vec!['\n']),
                state: next_state_index,
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
                    state: next_state_index,
                    is_sep,
                });
                Ok(true)
            }
            Class::Bracketed(class) => match &class.kind {
                ClassSet::Item(item) => {
                    let character_set = expand_character_class(&item)?;
                    nfa.states.push(NfaState::Advance {
                        chars: character_set,
                        state: next_state_index,
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
                if expand_regex(&repetition.ast, nfa, next_state_index, is_sep)? {
                    nfa.prepend(|last_state| NfaState::Split(next_state_index, last_state));
                    Ok(true)
                } else {
                    Ok(false)
                }
            }
            RepetitionKind::OneOrMore => {
                nfa.states.push(NfaState::Accept(0)); // Placeholder for split
                let split_index = nfa.last_state();
                if expand_regex(&repetition.ast, nfa, split_index, is_sep)? {
                    nfa.states[split_index as usize] =
                        NfaState::Split(nfa.last_state(), next_state_index);
                    Ok(true)
                } else {
                    nfa.states.pop();
                    Ok(false)
                }
            }
            RepetitionKind::ZeroOrMore => {
                nfa.states.push(NfaState::Accept(0)); // Placeholder for split
                let split_index = nfa.last_state();
                if expand_regex(&repetition.ast, nfa, split_index, is_sep)? {
                    nfa.states[split_index as usize] =
                        NfaState::Split(nfa.last_state(), next_state_index);
                    nfa.prepend(|last_state| NfaState::Split(last_state, next_state_index));
                    Ok(true)
                } else {
                    Ok(false)
                }
            }
            RepetitionKind::Range(_) => unimplemented!(),
        },
        Ast::Group(group) => expand_regex(&group.ast, nfa, nfa.last_state(), is_sep),
        Ast::Alternation(alternation) => {
            let mut alternative_start_indices = Vec::new();
            for ast in alternation.asts.iter() {
                if expand_regex(&ast, nfa, next_state_index, is_sep)? {
                    alternative_start_indices.push(nfa.last_state());
                }
            }
            alternative_start_indices.pop();
            for alternative_start_index in alternative_start_indices {
                nfa.prepend(|last_state| NfaState::Split(last_state, alternative_start_index));
            }
            Ok(true)
        }
        Ast::Concat(concat) => {
            let mut result = false;
            for ast in concat.asts.iter().rev() {
                if expand_regex(&ast, nfa, next_state_index, is_sep)? {
                    result = true;
                }
                next_state_index = nfa.last_state();
            }
            Ok(result)
        }
    }
}

fn expand_rule(rule: &Rule, nfa: &mut Nfa, mut next_state_index: u32, is_sep: bool) -> Result<bool> {
    match rule {
        Rule::Pattern(s) => {
            let ast = parse::Parser::new()
                .parse(&s)
                .map_err(|e| Error::GrammarError(e.to_string()))?;
            expand_regex(&ast, nfa, next_state_index, is_sep)
        }
        Rule::String(s) => {
            for c in s.chars().rev() {
                nfa.prepend(|last_state| {
                    NfaState::Advance {
                        chars: CharacterSet::empty().add_char(c),
                        state: last_state,
                        is_sep,
                    }
                });
            }
            Ok(s.len() > 0)
        }
        Rule::Choice(elements) => {
            let mut alternative_start_indices = Vec::new();
            for element in elements {
                if expand_rule(element, nfa, next_state_index, is_sep)? {
                    alternative_start_indices.push(nfa.last_state());
                }
            }
            alternative_start_indices.pop();
            for alternative_start_index in alternative_start_indices {
                nfa.prepend(|last_state| NfaState::Split(last_state, alternative_start_index));
            }
            Ok(true)
        }
        Rule::Seq(elements) => {
            let mut result = false;
            for element in elements.into_iter().rev() {
                if expand_rule(element, nfa, next_state_index, is_sep)? {
                    result = true;
                }
                next_state_index = nfa.last_state();
            }
            Ok(result)
        }
        Rule::Repeat(rule) => {
            nfa.states.push(NfaState::Accept(0)); // Placeholder for split
            let split_index = nfa.last_state();
            if expand_rule(rule, nfa, split_index, is_sep)? {
                nfa.states[split_index as usize] = NfaState::Split(nfa.last_state(), next_state_index);
                Ok(true)
            } else {
                Ok(false)
            }
        }
        Rule::Blank => Ok(false),
        _ => Err(Error::grammar(&format!("Unexpected rule {:?}", rule))),
    }
}

pub(super) fn expand_tokens(grammar: ExtractedLexicalGrammar) -> Result<LexicalGrammar> {
    let mut nfa = Nfa::new();

    let separator_rule = if grammar.separators.len() > 0 {
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
        let last_state = nfa.last_state();
        expand_rule(&variable.rule, &mut nfa, last_state, false)?;

        if !is_immediate_token {
            let last_state = nfa.last_state();
            expand_rule(&separator_rule, &mut nfa, last_state, true)?;
        }

        variables.push(LexicalVariable {
            name: variable.name,
            kind: variable.kind,
            start_state: nfa.last_state(),
        });
    }

    Ok(LexicalGrammar { nfa, variables })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::nfa::NfaCursor;
    use crate::grammars::Variable;

    fn simulate_nfa<'a>(nfa: &'a Nfa, s: &'a str) -> Option<&'a str> {
        let mut result = None;
        let mut char_count = 0;
        let mut cursor = NfaCursor::new(nfa);
        for c in s.chars() {
            if cursor.finished_ids().count() > 0 {
                result = Some(&s[0..char_count]);
            }
            if cursor.advance(c) {
                char_count += 1;
            } else {
                break;
            }
        }
        result
    }

    #[test]
    fn test_rule_expansion() {
        struct Row {
            rules: Vec<Rule>,
            examples: Vec<(&'static str, Option<&'static str>)>,
        }

        let table = [
            Row {
                rules: vec![Rule::pattern("a|bc")],
                examples: vec![
                    ("a12", Some("a")),
                    ("bc12", Some("bc")),
                    ("b12", None),
                    ("c12", None),
                ],
            },
            Row {
                rules: vec![Rule::pattern("(a|b|c)d(e|f|g)h?")],
                examples: vec![
                    ("ade1", Some("ade")),
                    ("bdf1", Some("bdf")),
                    ("bdfh1", Some("bdfh")),
                    ("ad1", None),
                ],
            },
            Row {
                rules: vec![Rule::pattern("a*")],
                examples: vec![
                    ("aaa1", Some("aaa")),
                    ("b", Some("")),
                ],
            },
            Row {
                rules: vec![Rule::pattern("a((bc)+|(de)*)f")],
                examples: vec![
                    ("af1", Some("af")),
                    ("adedef1", Some("adedef")),
                    ("abcbcbcf1", Some("abcbcbcf")),
                    ("a", None),
                ],
            },
            Row {
                rules: vec![Rule::pattern("[a-fA-F0-9]+")],
                examples: vec![
                    ("A1ff0", Some("A1ff")),
                ],
            },
            Row {
                rules: vec![Rule::pattern("\\w\\d\\s")],
                examples: vec![
                    ("_0  ", Some("_0 ")),
                ],
            },
            Row {
                rules: vec![Rule::string("abc")],
                examples: vec![
                    ("abcd", Some("abc")),
                    ("ab", None)
                ],
            },
            Row {
                rules: vec![
                    Rule::repeat(Rule::seq(vec![
                        Rule::string("{"),
                        Rule::pattern("[a-f]+"),
                        Rule::string("}"),
                    ])),
                ],
                examples: vec![
                    ("{a}{", Some("{a}")),
                    ("{a}{d", Some("{a}")),
                    ("ab", None),
                ],
            },
        ];

        for Row { rules, examples } in &table {
            let grammar = expand_tokens(ExtractedLexicalGrammar {
                separators: vec![],
                variables: rules
                    .into_iter()
                    .map(|rule| Variable::named("", rule.clone()))
                    .collect(),
            }).unwrap();

            for (haystack, needle) in examples.iter() {
                assert_eq!(simulate_nfa(&grammar.nfa, haystack), *needle);
            }
        }
    }
}
