use crate::error::{Error, Result};
use crate::rules::Rule;
use crate::grammars::LexicalGrammar;
use crate::nfa::{Nfa, NfaState, NfaCursor, CharacterSet};
use regex_syntax::ast::{parse, Ast, Class, ClassPerlKind, ClassSet, ClassSetItem, RepetitionKind};

fn evaluate_perl_class(item: &ClassPerlKind) -> CharacterSet {
    match item {
        ClassPerlKind::Digit => CharacterSet::empty()
            .add_range('0', '9'),
        ClassPerlKind::Space => CharacterSet::empty()
            .add_char(' ')
            .add_char('\t')
            .add_char('\r')
            .add_char('\n'),
        ClassPerlKind::Word => CharacterSet::empty()
            .add_char('_')
            .add_range('A', 'Z')
            .add_range('a', 'z')
            .add_range('0', '9')
    }
}

fn evaluate_character_class(item: &ClassSetItem) -> Result<CharacterSet> {
    match item {
        ClassSetItem::Empty(_) => Ok(CharacterSet::Include(Vec::new())),
        ClassSetItem::Literal(literal) => Ok(CharacterSet::Include(vec![literal.c])),
        ClassSetItem::Range(range) => Ok(CharacterSet::empty().add_range(range.start.c, range.end.c)),
        ClassSetItem::Union(union) => {
            let mut result = CharacterSet::empty();
            for item in &union.items {
                result = result.add(evaluate_character_class(&item)?);
            }
            Ok(result)
        }
        _ => Err(Error::regex("Unsupported character class syntax")),
    }
}

fn regex_to_nfa(ast: &Ast, nfa: &mut Nfa, mut next_state_index: u32) -> Result<()> {
    match ast {
        Ast::Empty(_) => Ok(()),
        Ast::Flags(_) => Err(Error::regex("Flags are not supported")),
        Ast::Literal(literal) => {
            nfa.states.push(NfaState::Advance(CharacterSet::Include(vec![literal.c]), next_state_index));
            Ok(())
        },
        Ast::Dot(_) => {
            nfa.states.push(NfaState::Advance(CharacterSet::Exclude(vec!['\n']), next_state_index));
            Ok(())
        },
        Ast::Assertion(_) => Err(Error::regex("Assertions are not supported")),
        Ast::Class(class) => match class {
            Class::Unicode(_) => Err(Error::regex("Unicode character classes are not supported")),
            Class::Perl(class) => {
                nfa.states.push(NfaState::Advance(evaluate_perl_class(&class.kind), next_state_index));
                Ok(())
            },
            Class::Bracketed(class) => match &class.kind {
                ClassSet::Item(item) => {
                    let character_set = evaluate_character_class(&item)?;
                    nfa.states.push(NfaState::Advance(character_set, next_state_index));
                    Ok(())
                },
                ClassSet::BinaryOp(_) => {
                    Err(Error::regex("Binary operators in character classes aren't supported"))
                }
            }
        },
        Ast::Repetition(repetition) => match repetition.op.kind {
            RepetitionKind::ZeroOrOne => {
                regex_to_nfa(&repetition.ast, nfa, next_state_index)?;
                nfa.prepend(|start_index| NfaState::Split(next_state_index, start_index));
                Ok(())
            },
            RepetitionKind::OneOrMore => {
                nfa.states.push(NfaState::Accept); // Placeholder for split
                let split_index = nfa.start_index();
                regex_to_nfa(&repetition.ast, nfa, split_index)?;
                nfa.states[split_index as usize] = NfaState::Split(
                    nfa.start_index(),
                    next_state_index
                );
                Ok(())
            },
            RepetitionKind::ZeroOrMore => {
                nfa.states.push(NfaState::Accept); // Placeholder for split
                let split_index = nfa.start_index();
                regex_to_nfa(&repetition.ast, nfa, split_index)?;
                nfa.states[split_index as usize] = NfaState::Split(
                    nfa.start_index(),
                    next_state_index
                );
                nfa.prepend(|start_index| NfaState::Split(start_index, next_state_index));
                Ok(())
            },
            RepetitionKind::Range(_) => unimplemented!(),
        },
        Ast::Group(group) => regex_to_nfa(&group.ast, nfa, nfa.start_index()),
        Ast::Alternation(alternation) => {
            let mut alternative_start_indices = Vec::new();
            for ast in alternation.asts.iter() {
                regex_to_nfa(&ast, nfa, next_state_index)?;
                alternative_start_indices.push(nfa.start_index());
            }
            alternative_start_indices.pop();
            for alternative_start_index in alternative_start_indices {
                nfa.prepend(|start_index| NfaState::Split(start_index, alternative_start_index));
            }
            Ok(())
        },
        Ast::Concat(concat) => {
            for ast in concat.asts.iter().rev() {
                regex_to_nfa(&ast, nfa, next_state_index)?;
                next_state_index = nfa.start_index();
            }
            Ok(())
        }
    }
}

fn expand_rule(rule: Rule) -> Result<Nfa> {
    match rule {
        Rule::Pattern(s) => {
            let ast = parse::Parser::new().parse(&s).map_err(|e| Error::GrammarError(e.to_string()))?;
            let mut nfa = Nfa::new();
            regex_to_nfa(&ast, &mut nfa, 0)?;
            Ok(nfa)
        },
        Rule::String(s) => {
            let mut nfa = Nfa::new();
            for c in s.chars().rev() {
                nfa.prepend(|start_index| NfaState::Advance(CharacterSet::empty().add_char(c), start_index));
            }
            Ok(nfa)
        },
        _ => Err(Error::grammar("Unexpected rule type")),
    }
}

pub(super) fn normalize_rules(grammar: LexicalGrammar) -> LexicalGrammar {
    unimplemented!();
}

#[cfg(test)]
mod tests {
    use super::*;

    fn simulate_nfa<'a>(nfa: &'a Nfa, s: &'a str) -> Option<&'a str> {
        let mut result = None;
        let mut char_count = 0;
        let mut cursor = NfaCursor::new(nfa);
        for c in s.chars() {
            if cursor.is_done() {
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
    fn test_regex_expansion() {
        struct Row {
            pattern: &'static str,
            examples: Vec<(&'static str, Option<&'static str>)>,
        }

        let table = [
            Row {
                pattern: "a|bc",
                examples: vec![
                    ("a12", Some("a")),
                    ("bc12", Some("bc")),
                    ("b12", None),
                    ("c12", None),
                ],
            },
            Row {
                pattern: "(a|b|c)d(e|f|g)h?",
                examples: vec![
                    ("ade1", Some("ade")),
                    ("bdf1", Some("bdf")),
                    ("bdfh1", Some("bdfh")),
                    ("ad1", None),
                ],
            },
            Row {
                pattern: "a*",
                examples: vec![
                    ("aaa1", Some("aaa")),
                    ("b", Some("")),
                ],
            },
            Row {
                pattern: "a((bc)+|(de)*)f",
                examples: vec![
                    ("af1", Some("af")),
                    ("adedef1", Some("adedef")),
                    ("abcbcbcf1", Some("abcbcbcf")),
                    ("a", None),
                ],
            },
            Row {
                pattern: "[a-fA-F0-9]+",
                examples: vec![
                    ("A1ff0", Some("A1ff")),
                ],
            },
            Row {
                pattern: "\\w\\d\\s",
                examples: vec![
                    ("_0  ", Some("_0 ")),
                ],
            },
        ];

        for Row { pattern, examples } in table.iter() {
            let nfa = expand_rule(Rule::pattern(pattern)).unwrap();
            for (haystack, needle) in examples.iter() {
                assert_eq!(simulate_nfa(&nfa, haystack), *needle);
            }
        }
    }
}
