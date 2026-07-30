use std::{cmp::Ordering, fmt};

use rustc_hash::FxHashSet;

use bitflags::bitflags;

use crate::{
    build_tables::item::TokenSetDisplay,
    grammars::{LexicalGrammar, SyntaxGrammar},
    nfa::{CharacterSet, NfaCursor, NfaTransition},
    rules::{Symbol, TokenSet},
};

bitflags! {
    /// Per-(i,j) token conflict status, packed into a single byte.
    #[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
    struct TokenConflictStatus: u8 {
        const MATCHES_PREFIX              = 1 << 0;
        const DOES_MATCH_CONTINUATION     = 1 << 1;
        const DOES_MATCH_VALID_CONT       = 1 << 2;
        const DOES_MATCH_SEPARATORS       = 1 << 3;
        const MATCHES_SAME_STRING         = 1 << 4;
        const MATCHES_DIFFERENT_STRING    = 1 << 5;
    }
}

pub struct TokenConflictMap<'a> {
    n: usize,
    status_matrix: Vec<TokenConflictStatus>,
    following_tokens: Vec<TokenSet>,
    starting_chars_by_index: Vec<CharacterSet>,
    following_chars_by_index: Vec<CharacterSet>,
    separator_consumption_chars_by_index: Vec<CharacterSet>,
    grammar: &'a LexicalGrammar,
    /// Per-row bitsets for fast batch conflict checks.
    /// Row `i` spans `[i * row_words .. (i+1) * row_words]`.
    /// Bit `j` is set iff [`does_conflict(i, j)`](Self::does_conflict) || [`does_match_prefix(i, j)`](Self::does_match_prefix).
    pub(crate) conflict_or_prefix_bits: Vec<u64>,
    /// Bit `j` is set iff [`does_overlap(i, j)`](Self::does_overlap) || [`does_overlap(j, i)`](Self::does_overlap).
    pub(crate) overlap_either_bits: Vec<u64>,
    pub(crate) row_words: usize,
}

impl<'a> TokenConflictMap<'a> {
    /// Create a token conflict map based on a lexical grammar, which describes the structure
    /// of each token, and a `following_token` map, which indicates which tokens may appear
    /// immediately after each other token.
    ///
    /// This analyzes the possible kinds of overlap between each pair of tokens and stores
    /// them in a matrix.
    #[must_use]
    pub fn new(grammar: &'a LexicalGrammar, following_tokens: Vec<TokenSet>) -> Self {
        let mut cursor = NfaCursor::new(&grammar.nfa, Vec::new());
        let starting_chars = get_starting_chars(&mut cursor, grammar);
        let following_chars = get_following_chars(&starting_chars, &following_tokens);
        let separator_consumption = get_separator_consumption_chars(&mut cursor, grammar);

        // Pre-compute O(1) lookup: NFA state ID->owning variable index.
        // Replaces repeated O(log n) binary searches in compute_conflict_status.
        let nfa_state_to_var = (0..grammar.nfa.states.len())
            .map(|id| grammar.variable_index_for_nfa_state(id as u32))
            .collect::<Vec<usize>>();

        let n = grammar.variables.len();
        let mut status_matrix = vec![TokenConflictStatus::empty(); n * n];
        for i in 0..grammar.variables.len() {
            for j in 0..i {
                let status = compute_conflict_status(
                    &mut cursor,
                    grammar,
                    &following_chars,
                    &nfa_state_to_var,
                    i,
                    j,
                );
                status_matrix[matrix_index(n, i, j)] = status.0;
                status_matrix[matrix_index(n, j, i)] = status.1;
            }
        }

        // Precompute per-row bitsets for vectorized check_token_conflicts.
        let row_words = n.div_ceil(64);
        let conflict_mask = TokenConflictStatus::DOES_MATCH_VALID_CONT
            | TokenConflictStatus::DOES_MATCH_SEPARATORS
            | TokenConflictStatus::MATCHES_SAME_STRING
            | TokenConflictStatus::MATCHES_PREFIX;
        let overlap_mask = TokenConflictStatus::DOES_MATCH_SEPARATORS
            | TokenConflictStatus::MATCHES_PREFIX
            | TokenConflictStatus::MATCHES_SAME_STRING
            | TokenConflictStatus::DOES_MATCH_CONTINUATION;

        let mut conflict_or_prefix_bits = vec![0u64; n * row_words];
        let mut overlap_either_bits = vec![0u64; n * row_words];
        for i in 0..n {
            let row_base = i * row_words;
            for j in 0..n {
                let entry_ij = status_matrix[matrix_index(n, i, j)];
                if entry_ij.intersects(conflict_mask) {
                    conflict_or_prefix_bits[row_base + j / 64] |= 1u64 << (j % 64);
                }
                let entry_ji = status_matrix[matrix_index(n, j, i)];
                if entry_ij.intersects(overlap_mask) || entry_ji.intersects(overlap_mask) {
                    overlap_either_bits[row_base + j / 64] |= 1u64 << (j % 64);
                }
            }
        }

        TokenConflictMap {
            n,
            status_matrix,
            following_tokens,
            starting_chars_by_index: starting_chars,
            following_chars_by_index: following_chars,
            separator_consumption_chars_by_index: separator_consumption,
            grammar,
            conflict_or_prefix_bits,
            overlap_either_bits,
            row_words,
        }
    }

    /// Does token `i` match any strings that token `j` also matches, such that token `i`
    /// is preferred over token `j`?
    #[must_use]
    pub fn has_same_conflict_status(&self, a: usize, b: usize, other: usize) -> bool {
        let left = &self.status_matrix[matrix_index(self.n, a, other)];
        let right = &self.status_matrix[matrix_index(self.n, b, other)];
        left == right
    }

    /// The characters token `i` can consume inside the leading separator region.
    #[must_use]
    pub fn separator_consumption_chars(&self, i: usize) -> &CharacterSet {
        &self.separator_consumption_chars_by_index[i]
    }

    /// The union over a token set, for callers that gate on whole sets.
    #[must_use]
    pub fn separator_consumption_chars_for(
        &self,
        tokens: impl IntoIterator<Item = Symbol>,
    ) -> CharacterSet {
        let mut result = CharacterSet::empty();
        for token in tokens {
            if token.is_terminal() {
                result = result.add(self.separator_consumption_chars(token.index));
            }
        }
        result
    }

    /// Whether any token consumes separator characters at all; false makes
    /// both merge gates vacuous.
    #[must_use]
    pub fn has_any_separator_consumption(&self) -> bool {
        self.separator_consumption_chars_by_index
            .iter()
            .any(|chars| chars.ranges().next().is_some())
    }

    /// Does token `i` match any strings that token `j` does *not* match?
    #[must_use]
    pub fn does_match_different_string(&self, i: usize, j: usize) -> bool {
        self.status_matrix[matrix_index(self.n, i, j)]
            .contains(TokenConflictStatus::MATCHES_DIFFERENT_STRING)
    }

    /// Does token `i` match any strings that token `j` also matches, where
    /// token `i` is preferred over token `j`?
    #[inline]
    #[must_use]
    pub fn does_match_same_string(&self, i: usize, j: usize) -> bool {
        self.status_matrix[matrix_index(self.n, i, j)]
            .contains(TokenConflictStatus::MATCHES_SAME_STRING)
    }

    #[inline]
    #[must_use]
    pub fn does_conflict(&self, i: usize, j: usize) -> bool {
        debug_assert!(i < self.n && j < self.n, "token indices out of bounds");
        // Safety: i < n and j < n imply n*i+j < n*n == status_matrix.len().
        let entry = unsafe { *self.status_matrix.get_unchecked(matrix_index(self.n, i, j)) };
        entry.intersects(
            TokenConflictStatus::DOES_MATCH_VALID_CONT
                | TokenConflictStatus::DOES_MATCH_SEPARATORS
                | TokenConflictStatus::MATCHES_SAME_STRING,
        )
    }

    /// Does token `i` match any strings that are *prefixes* of strings matched by `j`?
    #[inline]
    #[must_use]
    #[allow(dead_code)]
    pub fn does_match_prefix(&self, i: usize, j: usize) -> bool {
        self.status_matrix[matrix_index(self.n, i, j)].contains(TokenConflictStatus::MATCHES_PREFIX)
    }

    #[must_use]
    pub fn does_match_shorter_or_longer(&self, i: usize, j: usize) -> bool {
        let entry = self.status_matrix[matrix_index(self.n, i, j)];
        let reverse_entry = self.status_matrix[matrix_index(self.n, j, i)];
        entry.intersects(
            TokenConflictStatus::DOES_MATCH_VALID_CONT | TokenConflictStatus::DOES_MATCH_SEPARATORS,
        ) && !reverse_entry.contains(TokenConflictStatus::DOES_MATCH_SEPARATORS)
    }

    #[inline]
    #[must_use]
    pub fn does_overlap(&self, i: usize, j: usize) -> bool {
        self.status_matrix[matrix_index(self.n, i, j)].intersects(
            TokenConflictStatus::DOES_MATCH_SEPARATORS
                | TokenConflictStatus::MATCHES_PREFIX
                | TokenConflictStatus::MATCHES_SAME_STRING
                | TokenConflictStatus::DOES_MATCH_CONTINUATION,
        )
    }

    #[must_use]
    pub fn prefer_token(grammar: &LexicalGrammar, left: (i32, usize), right: (i32, usize)) -> bool {
        match left.0.cmp(&right.0) {
            Ordering::Less => false,
            Ordering::Greater => true,
            Ordering::Equal => match grammar.variables[left.1]
                .implicit_precedence
                .cmp(&grammar.variables[right.1].implicit_precedence)
            {
                Ordering::Less => false,
                Ordering::Greater => true,
                Ordering::Equal => left.1 < right.1,
            },
        }
    }

    #[must_use]
    pub fn prefer_transition(
        grammar: &LexicalGrammar,
        t: &NfaTransition,
        completed_id: usize,
        completed_precedence: i32,
        has_separator_transitions: bool,
    ) -> bool {
        if t.precedence < completed_precedence {
            return false;
        }
        if t.precedence == completed_precedence {
            if t.is_separator {
                return false;
            }
            if has_separator_transitions
                && !grammar
                    .variable_indices_for_nfa_states(&t.states)
                    .any(|i| i == completed_id)
            {
                return false;
            }
        }
        true
    }
}

impl fmt::Debug for TokenConflictMap<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        writeln!(f, "TokenConflictMap {{")?;

        let syntax_grammar = SyntaxGrammar::default();

        writeln!(f, "  following_tokens: {{")?;
        for (i, following_tokens) in self.following_tokens.iter().enumerate() {
            writeln!(
                f,
                "    follow({:?}): {},",
                self.grammar.variables[i].name,
                TokenSetDisplay(following_tokens, &syntax_grammar, self.grammar)
            )?;
        }
        writeln!(f, "  }},")?;

        writeln!(f, "  starting_characters: {{")?;
        for i in 0..self.n {
            writeln!(
                f,
                "    {:?}: {:?},",
                self.grammar.variables[i].name, self.starting_chars_by_index[i]
            )?;
        }
        writeln!(f, "  }},")?;

        writeln!(f, "  following_characters: {{")?;
        for i in 0..self.n {
            writeln!(
                f,
                "    {:?}: {:?},",
                self.grammar.variables[i].name, self.following_chars_by_index[i]
            )?;
        }
        writeln!(f, "  }},")?;

        writeln!(f, "  status_matrix: {{")?;
        for i in 0..self.n {
            writeln!(f, "    {:?}: {{", self.grammar.variables[i].name)?;
            for j in 0..self.n {
                writeln!(
                    f,
                    "      {:?}: {:?},",
                    self.grammar.variables[j].name,
                    self.status_matrix[matrix_index(self.n, i, j)]
                )?;
            }
            writeln!(f, "    }},")?;
        }
        write!(f, "  }},")?;
        write!(f, "}}")?;
        Ok(())
    }
}

#[inline]
const fn matrix_index(variable_count: usize, i: usize, j: usize) -> usize {
    variable_count * i + j
}

fn get_starting_chars(cursor: &mut NfaCursor, grammar: &LexicalGrammar) -> Vec<CharacterSet> {
    let mut result = Vec::with_capacity(grammar.variables.len());
    for variable in &grammar.variables {
        cursor.reset(vec![variable.start_state]);
        let mut all_chars = CharacterSet::empty();
        for (chars, _) in cursor.transition_chars() {
            all_chars = all_chars.add(chars);
        }
        result.push(all_chars);
    }
    result
}

/// Per token, the characters it can consume where a separator could have
/// consumed them too; only there can a token start land inside skipped text.
fn get_separator_consumption_chars(
    cursor: &mut NfaCursor,
    grammar: &LexicalGrammar,
) -> Vec<CharacterSet> {
    // Any non-immediate token's entry state can drive the separator side.
    let mut separator_cursor = NfaCursor::new(&grammar.nfa, Vec::new());
    let mut separator_start = None;
    for variable in &grammar.variables {
        separator_cursor.reset(vec![variable.start_state]);
        if separator_cursor
            .transition_chars()
            .any(|(_, is_separator)| is_separator)
        {
            separator_start = Some(variable.start_state);
            break;
        }
    }
    let Some(separator_start) = separator_start else {
        return vec![CharacterSet::empty(); grammar.variables.len()];
    };

    let mut result = Vec::with_capacity(grammar.variables.len());
    let mut visited = FxHashSet::default();
    let mut queue = Vec::new();
    let mut advanced_chars = CharacterSet::empty();
    let mut shared_scratch = CharacterSet::empty();
    for variable in &grammar.variables {
        let mut consumable_chars = CharacterSet::empty();
        visited.clear();
        queue.clear();
        queue.push((vec![variable.start_state], vec![separator_start]));
        while let Some((token_states, separator_states)) = queue.pop() {
            cursor.reset(token_states);
            separator_cursor.reset(separator_states);
            if !visited.insert((cursor.state_ids.clone(), separator_cursor.state_ids.clone())) {
                continue;
            }

            let mut main_chars = CharacterSet::empty();
            for (chars, is_separator) in cursor.transition_chars() {
                if !is_separator {
                    main_chars = main_chars.add(chars);
                }
            }
            let mut separator_chars = CharacterSet::empty();
            for (chars, is_separator) in separator_cursor.transition_chars() {
                if is_separator {
                    separator_chars = separator_chars.add(chars);
                }
            }

            let shared_chars = main_chars.intersection(separator_chars);
            if shared_chars.ranges().next().is_none() {
                continue;
            }
            consumable_chars = consumable_chars.add(&shared_chars);

            let separator_transitions = separator_cursor.transitions();
            for transition in cursor.transitions() {
                if transition.is_separator {
                    continue;
                }
                advanced_chars.assign(&transition.characters);
                shared_scratch.assign(&shared_chars);
                let advanced = advanced_chars.remove_intersection(&mut shared_scratch);
                if advanced.ranges().next().is_none() {
                    continue;
                }
                // Follow every group covering these characters: grouping
                // marks a transition separator only if every contributor is.
                let mut separator_next = Vec::new();
                for separator_transition in &separator_transitions {
                    if separator_transition.characters.does_intersect(&advanced) {
                        separator_next.extend_from_slice(&separator_transition.states);
                    }
                }
                queue.push((transition.states.clone(), separator_next));
            }
        }
        result.push(consumable_chars);
    }
    result
}

fn get_following_chars(
    starting_chars: &[CharacterSet],
    following_tokens: &[TokenSet],
) -> Vec<CharacterSet> {
    following_tokens
        .iter()
        .map(|following_tokens| {
            let mut chars = CharacterSet::empty();
            for token in following_tokens.iter() {
                if token.is_terminal() {
                    chars = chars.add(&starting_chars[token.index]);
                }
            }
            chars
        })
        .collect()
}

/// Hash a sorted slice of NFA state IDs to a single `u64` for use as a
/// visited-set key.
///
/// NOTE: This trades exact equality for speed. Two distinct state sets that
/// hash to the same `u64` will be treated as "already visited," potentially
/// causing the BFS to skip a state set. In practice the collision probability
/// is negligible (1 in 2^64 per comparison), but this is technically a
/// probabilistic optimization rather than an exact one.
#[inline]
fn hash_state_set(states: &[u32]) -> u64 {
    use std::hash::{Hash, Hasher};
    let mut h = rustc_hash::FxHasher::default();
    states.hash(&mut h);
    h.finish()
}

fn compute_conflict_status(
    cursor: &mut NfaCursor,
    grammar: &LexicalGrammar,
    following_chars: &[CharacterSet],
    nfa_state_to_var: &[usize],
    i: usize,
    j: usize,
) -> (TokenConflictStatus, TokenConflictStatus) {
    let mut visited_state_sets = FxHashSet::<u64>::default();
    let mut state_set_queue = Vec::with_capacity(4);
    state_set_queue.push(vec![
        grammar.variables[i].start_state,
        grammar.variables[j].start_state,
    ]);
    let mut result = (TokenConflictStatus::empty(), TokenConflictStatus::empty());

    while let Some(state_set) = state_set_queue.pop() {
        // If only one of the two tokens could possibly match from this state, then
        // there is no reason to analyze any of its successors. Just record the fact
        // that the token matches a string that the other token does not match.
        let first_live_variable_index = nfa_state_to_var[state_set[0] as usize];
        if state_set
            .iter()
            .all(|&s| nfa_state_to_var[s as usize] == first_live_variable_index)
        {
            if first_live_variable_index == i {
                result
                    .0
                    .insert(TokenConflictStatus::MATCHES_DIFFERENT_STRING);
            } else {
                result
                    .1
                    .insert(TokenConflictStatus::MATCHES_DIFFERENT_STRING);
            }
            continue;
        }

        // Don't pursue states where there's no potential for conflict.
        cursor.reset(state_set);

        // Compute lazily: most BFS states have no completions, so
        // `within_separator` is never needed in those iterations.
        let mut within_separator: Option<bool> = None;

        // Examine each possible completed token in this state.
        let mut completion = None;
        for (id, precedence) in cursor.completions() {
            let sep = *within_separator
                .get_or_insert_with(|| cursor.transition_chars().any(|(_, sep)| sep));
            if sep {
                if id == i {
                    result.0.insert(TokenConflictStatus::DOES_MATCH_SEPARATORS);
                } else {
                    result.1.insert(TokenConflictStatus::DOES_MATCH_SEPARATORS);
                }
            }

            // If the other token has already completed, then this is
            // a same-string conflict.
            if let Some((prev_id, prev_precedence)) = completion {
                if id == prev_id {
                    continue;
                }

                // Determine which of the two tokens is preferred.
                let preferred_id;
                if TokenConflictMap::prefer_token(
                    grammar,
                    (prev_precedence, prev_id),
                    (precedence, id),
                ) {
                    preferred_id = prev_id;
                } else {
                    preferred_id = id;
                    completion = Some((id, precedence));
                }

                if preferred_id == i {
                    result.0.insert(TokenConflictStatus::MATCHES_SAME_STRING);
                } else {
                    result.1.insert(TokenConflictStatus::MATCHES_SAME_STRING);
                }
            } else {
                completion = Some((id, precedence));
            }
        }

        // Examine each possible transition from this state to detect substring conflicts.
        for transition in cursor.transitions() {
            let mut can_advance = true;

            // If there is already a completed token in this state, then determine
            // if the next state can also match the completed token. If so, then
            // this is *not* a conflict.
            if let Some((completed_id, completed_precedence)) = completion {
                let mut advanced_id = None;
                let mut successor_contains_completed_id = false;
                let mut prev_var = None;
                for &state_id in &transition.states {
                    let var_id = nfa_state_to_var[state_id as usize];
                    if prev_var == Some(var_id) {
                        continue;
                    }
                    prev_var = Some(var_id);
                    if var_id == completed_id {
                        successor_contains_completed_id = true;
                        break;
                    }
                    advanced_id = Some(var_id);
                }

                // Determine which action is preferred: matching the already complete
                // token, or continuing on to try and match the other longer token.
                if let (Some(advanced_id), false) = (advanced_id, successor_contains_completed_id) {
                    if TokenConflictMap::prefer_transition(
                        grammar,
                        &transition,
                        completed_id,
                        completed_precedence,
                        within_separator.unwrap_or(false),
                    ) {
                        can_advance = true;
                        if advanced_id == i {
                            result
                                .0
                                .insert(TokenConflictStatus::DOES_MATCH_CONTINUATION);
                            if transition.characters.does_intersect(&following_chars[j]) {
                                result.0.insert(TokenConflictStatus::DOES_MATCH_VALID_CONT);
                            }
                        } else {
                            result
                                .1
                                .insert(TokenConflictStatus::DOES_MATCH_CONTINUATION);
                            if transition.characters.does_intersect(&following_chars[i]) {
                                result.1.insert(TokenConflictStatus::DOES_MATCH_VALID_CONT);
                            }
                        }
                    } else if completed_id == i {
                        result.0.insert(TokenConflictStatus::MATCHES_PREFIX);
                    } else {
                        result.1.insert(TokenConflictStatus::MATCHES_PREFIX);
                    }
                }
            }

            if can_advance && visited_state_sets.insert(hash_state_set(&transition.states)) {
                state_set_queue.push(transition.states);
            }
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        grammars::{Variable, VariableType},
        prepare_grammar::{ExtractedLexicalGrammar, expand_tokens},
        rules::{Precedence, Rule, Symbol},
    };

    #[test]
    fn test_starting_characters() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: Vec::new(),
            variables: vec![
                Variable {
                    name: "token_0".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("[a-f]1|0x\\d", ""),
                },
                Variable {
                    name: "token_1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("d*ef", ""),
                },
            ],
        })
        .unwrap();

        let token_map = TokenConflictMap::new(&grammar, Vec::new());

        assert_eq!(
            token_map.starting_chars_by_index[0],
            CharacterSet::empty().add_range('a', 'f').add_char('0')
        );
        assert_eq!(
            token_map.starting_chars_by_index[1],
            CharacterSet::empty().add_range('d', 'e')
        );
    }

    #[test]
    fn test_separator_consumption_characters() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: vec![Rule::pattern("\\s", "")],
            variables: vec![
                Variable {
                    name: "make".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("make"),
                },
                Variable {
                    name: "ws_colon".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::seq(vec![Rule::pattern("\\s*", ""), Rule::string(":")]),
                },
                Variable {
                    name: "space_p".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string(" p"),
                },
                Variable {
                    name: "space_newline_q".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string(" \nq"),
                },
            ],
        })
        .unwrap();

        let token_map = TokenConflictMap::new(&grammar, Vec::new());
        let consumption =
            |name: &str| token_map.separator_consumption_chars(index_of_var(&grammar, name));

        assert_eq!(*consumption("make"), CharacterSet::empty());
        assert_eq!(*consumption("space_p"), CharacterSet::from_char(' '));
        // The closure looks past the first character while consumed text stays
        // inside the separator set: `' \nq'` consumes `'\n'` at depth 2.
        assert_eq!(
            *consumption("space_newline_q"),
            CharacterSet::empty().add_char(' ').add_char('\n')
        );
        assert!(consumption("ws_colon").contains(' '));
        assert!(consumption("ws_colon").contains('\n'));
    }

    #[test]
    fn test_separator_consumption_characters_inside_a_multi_character_separator() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: vec![Rule::pattern("[ \\t]", ""), Rule::pattern("#[ab]*", "")],
            variables: vec![
                Variable {
                    name: "hash_ap".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("#ap"),
                },
                Variable {
                    name: "hash_bq".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("#bq"),
                },
            ],
        })
        .unwrap();

        let token_map = TokenConflictMap::new(&grammar, Vec::new());
        let consumption =
            |name: &str| token_map.separator_consumption_chars(index_of_var(&grammar, name));

        // `'a'` and `'b'` begin no separator, but `#[ab]*` consumes them after
        // `'#'`, so the two tokens diverge inside the region.
        assert_eq!(
            *consumption("hash_ap"),
            CharacterSet::empty().add_char('#').add_char('a')
        );
        assert_eq!(
            *consumption("hash_bq"),
            CharacterSet::empty().add_char('#').add_char('b')
        );
    }

    #[test]
    fn test_separator_consumption_characters_of_an_immediate_token() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: vec![Rule::pattern("\\s", "")],
            variables: vec![
                Variable {
                    name: "make".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("make"),
                },
                Variable {
                    name: "immediate_space_p".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::immediate_token(Rule::string(" p")),
                },
                Variable {
                    name: "immediate_two_spaces".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::immediate_token(Rule::string("  p")),
                },
            ],
        })
        .unwrap();

        let token_map = TokenConflictMap::new(&grammar, Vec::new());
        let consumption =
            |name: &str| token_map.separator_consumption_chars(index_of_var(&grammar, name));

        // An immediate token has no separator prefix of its own, so measuring it
        // against its own automaton would score empty and let it pool.
        assert_eq!(
            *consumption("immediate_space_p"),
            CharacterSet::from_char(' ')
        );
        assert_eq!(
            *consumption("immediate_two_spaces"),
            CharacterSet::from_char(' ')
        );
        assert_eq!(*consumption("make"), CharacterSet::empty());
    }

    #[test]
    fn test_separator_consumption_characters_of_an_immediate_token_inside_a_separator() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: vec![Rule::pattern("[ \\t]", ""), Rule::pattern("#[ab]*", "")],
            variables: vec![
                Variable {
                    name: "immediate_hash_ax".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::immediate_token(Rule::string("#ax")),
                },
                Variable {
                    name: "hash_z".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("#z"),
                },
            ],
        })
        .unwrap();

        let token_map = TokenConflictMap::new(&grammar, Vec::new());
        let consumption =
            |name: &str| token_map.separator_consumption_chars(index_of_var(&grammar, name));

        // The immediate token reaches the comment's interior `'a'` while `#z`
        // stops at `'#'`, so their consumption must differ.
        assert_eq!(
            *consumption("immediate_hash_ax"),
            CharacterSet::empty().add_char('#').add_char('a')
        );
        assert_eq!(*consumption("hash_z"), CharacterSet::from_char('#'));
    }

    #[test]
    fn test_token_conflicts() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: Vec::new(),
            variables: vec![
                Variable {
                    name: "in".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("in"),
                },
                Variable {
                    name: "identifier".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("\\w+", ""),
                },
                Variable {
                    name: "instanceof".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("instanceof"),
                },
            ],
        })
        .unwrap();

        let var = |name| index_of_var(&grammar, name);

        let token_map = TokenConflictMap::new(
            &grammar,
            vec![
                std::iter::once(&Symbol::terminal(var("identifier")))
                    .copied()
                    .collect(),
                std::iter::once(&Symbol::terminal(var("in")))
                    .copied()
                    .collect(),
                std::iter::once(&Symbol::terminal(var("identifier")))
                    .copied()
                    .collect(),
            ],
        );

        // Given the string "in", the `in` token is preferred over the `identifier` token
        assert!(token_map.does_match_same_string(var("in"), var("identifier")));
        assert!(!token_map.does_match_same_string(var("identifier"), var("in")));

        // Depending on what character follows, the string "in" may be treated as part of an
        // `identifier` token.
        assert!(token_map.does_conflict(var("identifier"), var("in")));

        // Depending on what character follows, the string "instanceof" may be treated as part of
        // an `identifier` token.
        assert!(token_map.does_conflict(var("identifier"), var("instanceof")));
        assert!(token_map.does_conflict(var("instanceof"), var("in")));
    }

    #[test]
    fn test_token_conflicts_with_separators() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: vec![Rule::pattern("\\s", "")],
            variables: vec![
                Variable {
                    name: "x".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("x"),
                },
                Variable {
                    name: "newline".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("\n"),
                },
            ],
        })
        .unwrap();

        let var = |name| index_of_var(&grammar, name);

        let token_map = TokenConflictMap::new(&grammar, vec![TokenSet::new(); 4]);

        assert!(token_map.does_conflict(var("newline"), var("x")));
        assert!(!token_map.does_conflict(var("x"), var("newline")));
    }

    #[test]
    fn test_token_conflicts_with_open_ended_tokens() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: vec![Rule::pattern("\\s", "")],
            variables: vec![
                Variable {
                    name: "x".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::string("x"),
                },
                Variable {
                    name: "anything".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::prec(Precedence::Integer(-1), Rule::pattern(".*", "")),
                },
            ],
        })
        .unwrap();

        let var = |name| index_of_var(&grammar, name);

        let token_map = TokenConflictMap::new(&grammar, vec![TokenSet::new(); 4]);

        assert!(token_map.does_match_shorter_or_longer(var("anything"), var("x")));
        assert!(!token_map.does_match_shorter_or_longer(var("x"), var("anything")));
    }

    fn index_of_var(grammar: &LexicalGrammar, name: &str) -> usize {
        grammar
            .variables
            .iter()
            .position(|v| v.name == name)
            .unwrap()
    }
}
