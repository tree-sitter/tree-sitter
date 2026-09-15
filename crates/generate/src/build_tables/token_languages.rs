use rustc_hash::FxHashSet;

use crate::{
    grammars::LexicalGrammar,
    nfa::{Nfa, NfaCursor},
};

/// Exact relationships between raw token languages, without precedence,
/// declaration order, or the separators prepended by the lexer.
pub(super) struct TokenLanguageRelations {
    subsets: Vec<Vec<bool>>,
    intersections: Vec<Vec<bool>>,
}

impl TokenLanguageRelations {
    pub(super) fn new(grammar: &LexicalGrammar) -> Self {
        Self::from_nfa(
            &grammar.nfa,
            &grammar
                .variables
                .iter()
                .map(|variable| variable.token_start_state)
                .collect::<Vec<_>>(),
        )
    }

    fn from_nfa(nfa: &Nfa, starts: &[u32]) -> Self {
        let count = starts.len();
        let mut result = Self {
            subsets: vec![vec![true; count]; count],
            intersections: vec![vec![false; count]; count],
        };
        for i in 0..count {
            for j in i..count {
                let mut cursor = NfaCursor::new(nfa, vec![starts[i], starts[j]]);
                let mut visited = FxHashSet::default();
                visited.insert(cursor.state_ids.clone());
                let mut pending = vec![cursor.state_ids.clone()];
                while let Some(states) = pending.pop() {
                    cursor.force_reset(states);
                    let mut accepts_i = false;
                    let mut accepts_j = false;
                    for (index, _) in cursor.completions() {
                        accepts_i |= index == i;
                        accepts_j |= index == j;
                    }

                    // Acceptance, not the existence of a viable path, decides
                    // inclusion. At "a", a|ab accepts but ab|abc does not,
                    // even though both can still consume more input.
                    if accepts_i && !accepts_j {
                        result.subsets[i][j] = false;
                    }
                    if accepts_j && !accepts_i {
                        result.subsets[j][i] = false;
                    }
                    if accepts_i && accepts_j {
                        result.intersections[i][j] = true;
                        result.intersections[j][i] = true;
                    }
                    if !result.subsets[i][j] && !result.subsets[j][i] && result.intersections[i][j]
                    {
                        break;
                    }

                    // NfaCursor partitions the alphabet into disjoint character
                    // sets and keeps all destinations, regardless of precedence.
                    // Each transition represents every character in its set,
                    // not just some bounded sample of possible strings.
                    for transition in cursor.transitions() {
                        // CharacterSet can include surrogate code points, which
                        // are not characters in token strings.
                        if transition.characters.chars().next().is_none() {
                            continue;
                        }
                        let next = NfaCursor::new(nfa, transition.states).state_ids;
                        // Store full canonical state sets: hash collisions must
                        // never turn a counterexample into a claimed inclusion.
                        if visited.insert(next.clone()) {
                            pending.push(next);
                        }
                    }
                }
            }
        }
        result
    }

    pub(super) fn is_subset(&self, i: usize, j: usize) -> bool {
        self.subsets[i][j]
    }

    pub(super) fn is_strict_subset(&self, i: usize, j: usize) -> bool {
        self.subsets[i][j] && !self.subsets[j][i]
    }

    pub(super) fn overlaps(&self, i: usize, j: usize) -> bool {
        self.intersections[i][j]
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::nfa::{CharacterSet, NfaState};

    /// Regular-expression builder independent of token expansion and its
    /// rejection of empty-string tokens.
    #[derive(Clone)]
    enum Pattern {
        Chars(CharacterSet),
        Seq(Vec<Self>),
        Alt(Vec<Self>),
        Star(Box<Self>),
    }

    fn literal(text: &str) -> Pattern {
        Pattern::Seq(
            text.chars()
                .map(|c| Pattern::Chars(CharacterSet::from_char(c)))
                .collect(),
        )
    }

    fn alternatives(strings: &[&str]) -> Pattern {
        Pattern::Alt(strings.iter().map(|s| literal(s)).collect())
    }

    fn push(nfa: &mut Nfa, state: NfaState) -> u32 {
        let id = nfa.states.len() as u32;
        nfa.states.push(state);
        id
    }

    fn compile(nfa: &mut Nfa, pattern: &Pattern, end: u32) -> u32 {
        match pattern {
            Pattern::Chars(chars) => push(
                nfa,
                NfaState::Advance {
                    chars: chars.clone(),
                    state_id: end,
                    is_sep: false,
                    precedence: end as i32,
                },
            ),
            Pattern::Seq(parts) => parts
                .iter()
                .rev()
                .fold(end, |end, part| compile(nfa, part, end)),
            Pattern::Alt(parts) => {
                let mut start = compile(nfa, &Pattern::Chars(CharacterSet::empty()), end);
                for part in parts {
                    let branch = compile(nfa, part, end);
                    start = push(nfa, NfaState::Split(start, branch));
                }
                start
            }
            Pattern::Star(part) => {
                let start = push(nfa, NfaState::Split(end, end));
                let branch = compile(nfa, part, start);
                nfa.states[start as usize] = NfaState::Split(end, branch);
                start
            }
        }
    }

    fn grammar(patterns: &[Pattern]) -> (Nfa, Vec<u32>) {
        let mut nfa = Nfa::new();
        let starts = patterns
            .iter()
            .enumerate()
            .map(|(variable_index, pattern)| {
                let end = push(
                    &mut nfa,
                    NfaState::Accept {
                        variable_index,
                        precedence: -(variable_index as i32),
                    },
                );
                compile(&mut nfa, pattern, end)
            })
            .collect();
        (nfa, starts)
    }

    fn relations(patterns: &[Pattern]) -> TokenLanguageRelations {
        let (nfa, starts) = grammar(patterns);
        TokenLanguageRelations::from_nfa(&nfa, &starts)
    }

    #[test]
    fn prefix_counterexample_has_two_one_sided_acceptances() {
        let r = relations(&[alternatives(&["a", "ab"]), alternatives(&["ab", "abc"])]);
        assert!(r.overlaps(0, 1));
        assert!(!r.is_subset(0, 1));
        assert!(!r.is_subset(1, 0));
    }

    #[test]
    fn equal_disjoint_and_strict_languages() {
        let r = relations(&[
            literal("ab"),
            Pattern::Seq(vec![literal("a"), literal("b")]),
            alternatives(&["ab", "ac"]),
            literal("z"),
        ]);
        assert!(r.is_subset(0, 1));
        assert!(r.is_subset(1, 0));
        assert!(!r.is_strict_subset(0, 1));
        assert!(r.is_strict_subset(0, 2));
        assert!(!r.is_subset(2, 0));
        assert!(r.overlaps(0, 2));
        assert!(!r.overlaps(2, 3));
        for i in 0..4 {
            assert!(r.is_subset(i, i));
            assert!(!r.is_strict_subset(i, i));
            assert!(r.overlaps(i, i));
        }
    }

    #[test]
    fn finite_regex_alternatives_and_character_classes_are_equal() {
        let r = relations(&[
            alternatives(&["ab", "ac", "db", "dc"]),
            Pattern::Seq(vec![
                Pattern::Chars(CharacterSet::from_char('a').add_char('d')),
                Pattern::Chars(CharacterSet::empty().add_range('b', 'c')),
            ]),
        ]);
        assert!(r.is_subset(0, 1));
        assert!(r.is_subset(1, 0));
        assert!(r.overlaps(0, 1));
    }

    #[test]
    fn unbounded_unicode_classes() {
        let letters = Pattern::Chars(CharacterSet::empty().add_range('α', 'ω'));
        let all = Pattern::Chars(CharacterSet::empty().negate());
        let r = relations(&[
            Pattern::Star(Box::new(letters.clone())),
            Pattern::Star(Box::new(all)),
            literal("αω"),
            literal("😀"),
            Pattern::Seq(vec![letters.clone(), Pattern::Star(Box::new(letters))]),
        ]);
        assert!(r.is_strict_subset(0, 1));
        assert!(r.is_strict_subset(2, 0));
        assert!(r.is_strict_subset(3, 1));
        assert!(!r.overlaps(0, 3));
        assert!(r.is_strict_subset(4, 0)); // Empty string distinguishes them.
    }

    #[test]
    fn empty_languages_epsilon_and_dead_cycles() {
        let (mut nfa, mut starts) = grammar(&[
            Pattern::Alt(vec![]),
            literal(""),
            literal("a"),
            Pattern::Alt(vec![]),
        ]);
        // A consuming cycle with no accepting path is also an empty language.
        let dead = nfa.states.len() as u32;
        starts[3] = push(
            &mut nfa,
            NfaState::Advance {
                chars: CharacterSet::empty().negate(),
                state_id: dead,
                is_sep: false,
                precedence: 0,
            },
        );
        let r = TokenLanguageRelations::from_nfa(&nfa, &starts);
        for i in [0, 3] {
            for j in 0..4 {
                assert!(r.is_subset(i, j));
                assert!(!r.overlaps(i, j));
            }
        }
        assert!(!r.is_strict_subset(0, 3));
        assert!(r.is_strict_subset(0, 1));
        assert!(!r.overlaps(1, 2));
        assert!(!r.is_subset(1, 2));
        assert!(r.overlaps(1, 1));
    }

    #[test]
    fn epsilon_cycles_terminate() {
        let r = relations(&[
            Pattern::Star(Box::new(literal(""))),
            literal(""),
            literal("a"),
        ]);
        assert!(r.is_subset(0, 1));
        assert!(r.is_subset(1, 0));
        assert!(!r.overlaps(0, 2));
    }

    #[test]
    fn declaration_and_state_order_do_not_choose_a_language() {
        let patterns = [
            literal("a"),
            alternatives(&["a", "ab"]),
            alternatives(&["ab", "abc"]),
            Pattern::Star(Box::new(Pattern::Chars(
                CharacterSet::empty().add_range('a', 'z'),
            ))),
            Pattern::Alt(vec![]),
            literal("a"),
        ];
        let original = relations(&patterns);
        for permutation in [[5, 4, 3, 2, 1, 0], [2, 0, 4, 1, 5, 3]] {
            let reordered = permutation.map(|i| patterns[i].clone());
            let r = relations(&reordered);
            for (i, &old_i) in permutation.iter().enumerate() {
                for (j, &old_j) in permutation.iter().enumerate() {
                    assert_eq!(r.is_subset(i, j), original.is_subset(old_i, old_j));
                    assert_eq!(
                        r.is_strict_subset(i, j),
                        original.is_strict_subset(old_i, old_j)
                    );
                    assert_eq!(r.overlaps(i, j), original.overlaps(old_i, old_j));
                }
            }
        }
    }
}
