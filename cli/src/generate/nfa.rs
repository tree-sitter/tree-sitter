use std::char;
use std::cmp::max;
use std::cmp::Ordering;
use std::fmt;
use std::mem::swap;

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum CharacterSet {
    Include(Vec<char>),
    Exclude(Vec<char>),
}

#[derive(Debug, PartialEq, Eq)]
pub enum NfaState {
    Advance {
        chars: CharacterSet,
        state_id: u32,
        is_sep: bool,
        precedence: i32,
    },
    Split(u32, u32),
    Accept {
        variable_index: usize,
        precedence: i32,
    },
}

#[derive(PartialEq, Eq)]
pub struct Nfa {
    pub states: Vec<NfaState>,
}

#[derive(Debug)]
pub struct NfaCursor<'a> {
    pub(crate) state_ids: Vec<u32>,
    nfa: &'a Nfa,
}

#[derive(Debug, PartialEq, Eq)]
pub struct NfaTransition {
    pub characters: CharacterSet,
    pub is_separator: bool,
    pub precedence: i32,
    pub states: Vec<u32>,
}

impl Default for Nfa {
    fn default() -> Self {
        Self { states: Vec::new() }
    }
}

impl CharacterSet {
    pub fn empty() -> Self {
        CharacterSet::Include(Vec::new())
    }

    pub fn negate(self) -> CharacterSet {
        match self {
            CharacterSet::Include(chars) => CharacterSet::Exclude(chars),
            CharacterSet::Exclude(chars) => CharacterSet::Include(chars),
        }
    }

    pub fn add_char(self, c: char) -> Self {
        if let CharacterSet::Include(mut chars) = self {
            if let Err(i) = chars.binary_search(&c) {
                chars.insert(i, c);
            }
            CharacterSet::Include(chars)
        } else {
            panic!("Called add with a negated character set");
        }
    }

    pub fn add_range(self, start: char, end: char) -> Self {
        if let CharacterSet::Include(mut chars) = self {
            let mut c = start as u32;
            while c <= end as u32 {
                chars.push(char::from_u32(c).unwrap());
                c += 1;
            }
            chars.sort_unstable();
            chars.dedup();
            CharacterSet::Include(chars)
        } else {
            panic!("Called add with a negated character set");
        }
    }

    pub fn add(self, other: &CharacterSet) -> Self {
        match self {
            CharacterSet::Include(mut chars) => match other {
                CharacterSet::Include(other_chars) => {
                    chars.extend(other_chars);
                    chars.sort_unstable();
                    chars.dedup();
                    CharacterSet::Include(chars)
                }
                CharacterSet::Exclude(other_chars) => {
                    let excluded_chars = other_chars
                        .iter()
                        .cloned()
                        .filter(|c| !chars.contains(&c))
                        .collect();
                    CharacterSet::Exclude(excluded_chars)
                }
            },
            CharacterSet::Exclude(mut chars) => match other {
                CharacterSet::Include(other_chars) => {
                    chars.retain(|c| !other_chars.contains(&c));
                    CharacterSet::Exclude(chars)
                }
                CharacterSet::Exclude(other_chars) => {
                    chars.retain(|c| other_chars.contains(&c));
                    CharacterSet::Exclude(chars)
                }
            },
        }
    }

    pub fn does_intersect(&self, other: &CharacterSet) -> bool {
        match self {
            CharacterSet::Include(chars) => match other {
                CharacterSet::Include(other_chars) => compare_chars(chars, other_chars).common,
                CharacterSet::Exclude(other_chars) => compare_chars(chars, other_chars).left_only,
            },
            CharacterSet::Exclude(chars) => match other {
                CharacterSet::Include(other_chars) => compare_chars(chars, other_chars).right_only,
                CharacterSet::Exclude(_) => true,
            },
        }
    }

    pub fn remove_intersection(&mut self, other: &mut CharacterSet) -> CharacterSet {
        match self {
            CharacterSet::Include(chars) => match other {
                CharacterSet::Include(other_chars) => {
                    CharacterSet::Include(remove_chars(chars, other_chars, true))
                }
                CharacterSet::Exclude(other_chars) => {
                    let mut removed = remove_chars(chars, other_chars, false);
                    add_chars(other_chars, chars);
                    swap(&mut removed, chars);
                    CharacterSet::Include(removed)
                }
            },
            CharacterSet::Exclude(chars) => match other {
                CharacterSet::Include(other_chars) => {
                    let mut removed = remove_chars(other_chars, chars, false);
                    add_chars(chars, other_chars);
                    swap(&mut removed, other_chars);
                    CharacterSet::Include(removed)
                }
                CharacterSet::Exclude(other_chars) => {
                    let mut result_exclusion = chars.clone();
                    result_exclusion.extend(other_chars.iter().cloned());
                    result_exclusion.sort_unstable();
                    result_exclusion.dedup();
                    remove_chars(chars, other_chars, true);
                    let mut included_characters = Vec::new();
                    let mut other_included_characters = Vec::new();
                    swap(&mut included_characters, other_chars);
                    swap(&mut other_included_characters, chars);
                    *self = CharacterSet::Include(included_characters);
                    *other = CharacterSet::Include(other_included_characters);
                    CharacterSet::Exclude(result_exclusion)
                }
            },
        }
    }

    pub fn is_empty(&self) -> bool {
        if let CharacterSet::Include(c) = self {
            c.is_empty()
        } else {
            false
        }
    }

    #[cfg(test)]
    pub fn contains(&self, c: char) -> bool {
        match self {
            CharacterSet::Include(chars) => chars.contains(&c),
            CharacterSet::Exclude(chars) => !chars.contains(&c),
        }
    }
}

impl Ord for CharacterSet {
    fn cmp(&self, other: &CharacterSet) -> Ordering {
        match self {
            CharacterSet::Include(chars) => {
                if let CharacterSet::Include(other_chars) = other {
                    order_chars(chars, other_chars)
                } else {
                    Ordering::Less
                }
            }
            CharacterSet::Exclude(chars) => {
                if let CharacterSet::Exclude(other_chars) = other {
                    order_chars(chars, other_chars)
                } else {
                    Ordering::Greater
                }
            }
        }
    }
}

impl PartialOrd for CharacterSet {
    fn partial_cmp(&self, other: &CharacterSet) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn add_chars(left: &mut Vec<char>, right: &Vec<char>) {
    for c in right {
        match left.binary_search(c) {
            Err(i) => left.insert(i, *c),
            _ => {}
        }
    }
}

fn remove_chars(left: &mut Vec<char>, right: &mut Vec<char>, mutate_right: bool) -> Vec<char> {
    let mut result = Vec::new();
    right.retain(|right_char| {
        if let Some(index) = left.iter().position(|left_char| *left_char == *right_char) {
            left.remove(index);
            result.push(*right_char);
            false || !mutate_right
        } else {
            true
        }
    });
    result
}

struct SetComparision {
    left_only: bool,
    common: bool,
    right_only: bool,
}

fn compare_chars(left: &Vec<char>, right: &Vec<char>) -> SetComparision {
    let mut result = SetComparision {
        left_only: false,
        common: false,
        right_only: false,
    };
    let mut left = left.iter().cloned();
    let mut right = right.iter().cloned();
    let mut i = left.next();
    let mut j = right.next();
    while let (Some(left_char), Some(right_char)) = (i, j) {
        if left_char < right_char {
            i = left.next();
            result.left_only = true;
        } else if left_char > right_char {
            j = right.next();
            result.right_only = true;
        } else {
            i = left.next();
            j = right.next();
            result.common = true;
        }
    }

    match (i, j) {
        (Some(_), _) => result.left_only = true,
        (_, Some(_)) => result.right_only = true,
        _ => {}
    }

    result
}

fn order_chars(chars: &Vec<char>, other_chars: &Vec<char>) -> Ordering {
    if chars.is_empty() {
        if other_chars.is_empty() {
            Ordering::Equal
        } else {
            Ordering::Less
        }
    } else if other_chars.is_empty() {
        Ordering::Greater
    } else {
        let cmp = chars.len().cmp(&other_chars.len());
        if cmp != Ordering::Equal {
            return cmp;
        }
        for (c, other_c) in chars.iter().zip(other_chars.iter()) {
            let cmp = c.cmp(other_c);
            if cmp != Ordering::Equal {
                return cmp;
            }
        }
        Ordering::Equal
    }
}

impl Nfa {
    pub fn new() -> Self {
        Nfa { states: Vec::new() }
    }

    pub fn last_state_id(&self) -> u32 {
        self.states.len() as u32 - 1
    }
}

impl fmt::Debug for Nfa {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Nfa {{ states: {{\n")?;
        for (i, state) in self.states.iter().enumerate() {
            write!(f, "  {}: {:?},\n", i, state)?;
        }
        write!(f, "}} }}")?;
        Ok(())
    }
}

impl<'a> NfaCursor<'a> {
    pub fn new(nfa: &'a Nfa, mut states: Vec<u32>) -> Self {
        let mut result = Self {
            nfa,
            state_ids: Vec::new(),
        };
        result.add_states(&mut states);
        result
    }

    pub fn reset(&mut self, mut states: Vec<u32>) {
        self.state_ids.clear();
        self.add_states(&mut states);
    }

    pub fn force_reset(&mut self, states: Vec<u32>) {
        self.state_ids = states
    }

    pub fn transition_chars(&self) -> impl Iterator<Item = (&CharacterSet, bool)> {
        self.raw_transitions().map(|t| (t.0, t.1))
    }

    pub fn transitions(&self) -> Vec<NfaTransition> {
        Self::group_transitions(self.raw_transitions())
    }

    fn raw_transitions(&self) -> impl Iterator<Item = (&CharacterSet, bool, i32, u32)> {
        self.state_ids.iter().filter_map(move |id| {
            if let NfaState::Advance {
                chars,
                state_id,
                precedence,
                is_sep,
            } = &self.nfa.states[*id as usize]
            {
                Some((chars, *is_sep, *precedence, *state_id))
            } else {
                None
            }
        })
    }

    fn group_transitions<'b>(
        iter: impl Iterator<Item = (&'b CharacterSet, bool, i32, u32)>,
    ) -> Vec<NfaTransition> {
        let mut result: Vec<NfaTransition> = Vec::new();
        for (chars, is_sep, prec, state) in iter {
            let mut chars = chars.clone();
            let mut i = 0;
            while i < result.len() && !chars.is_empty() {
                let intersection = result[i].characters.remove_intersection(&mut chars);
                if !intersection.is_empty() {
                    let mut intersection_states = result[i].states.clone();
                    match intersection_states.binary_search(&state) {
                        Err(j) => intersection_states.insert(j, state),
                        _ => {}
                    }
                    let intersection_transition = NfaTransition {
                        characters: intersection,
                        is_separator: result[i].is_separator && is_sep,
                        precedence: max(result[i].precedence, prec),
                        states: intersection_states,
                    };
                    if result[i].characters.is_empty() {
                        result[i] = intersection_transition;
                    } else {
                        result.insert(i, intersection_transition);
                        i += 1;
                    }
                }
                i += 1;
            }
            if !chars.is_empty() {
                result.push(NfaTransition {
                    characters: chars,
                    precedence: prec,
                    states: vec![state],
                    is_separator: is_sep,
                });
            }
        }
        result.sort_unstable_by(|a, b| a.characters.cmp(&b.characters));

        let mut i = 0;
        'i_loop: while i < result.len() {
            for j in 0..i {
                if result[j].states == result[i].states
                    && result[j].is_separator == result[i].is_separator
                    && result[j].precedence == result[i].precedence
                {
                    let mut characters = CharacterSet::empty();
                    swap(&mut characters, &mut result[j].characters);
                    result[j].characters = characters.add(&result[i].characters);
                    result.remove(i);
                    continue 'i_loop;
                }
            }
            i += 1;
        }

        result
    }

    pub fn completions(&self) -> impl Iterator<Item = (usize, i32)> + '_ {
        self.state_ids.iter().filter_map(move |state_id| {
            if let NfaState::Accept {
                variable_index,
                precedence,
            } = self.nfa.states[*state_id as usize]
            {
                Some((variable_index, precedence))
            } else {
                None
            }
        })
    }

    pub fn add_states(&mut self, new_state_ids: &mut Vec<u32>) {
        let mut i = 0;
        while i < new_state_ids.len() {
            let state_id = new_state_ids[i];
            let state = &self.nfa.states[state_id as usize];
            if let NfaState::Split(left, right) = state {
                let mut has_left = false;
                let mut has_right = false;
                for new_state_id in new_state_ids.iter() {
                    if *new_state_id == *left {
                        has_left = true;
                    }
                    if *new_state_id == *right {
                        has_right = true;
                    }
                }
                if !has_left {
                    new_state_ids.push(*left);
                }
                if !has_right {
                    new_state_ids.push(*right);
                }
            } else if let Err(i) = self.state_ids.binary_search(&state_id) {
                self.state_ids.insert(i, state_id);
            }
            i += 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_group_transitions() {
        let table = [
            // overlapping character classes
            (
                vec![
                    (CharacterSet::empty().add_range('a', 'f'), false, 0, 1),
                    (CharacterSet::empty().add_range('d', 'i'), false, 1, 2),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::empty().add_range('a', 'c'),
                        is_separator: false,
                        precedence: 0,
                        states: vec![1],
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_range('d', 'f'),
                        is_separator: false,
                        precedence: 1,
                        states: vec![1, 2],
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_range('g', 'i'),
                        is_separator: false,
                        precedence: 1,
                        states: vec![2],
                    },
                ],
            ),
            // large character class followed by many individual characters
            (
                vec![
                    (CharacterSet::empty().add_range('a', 'z'), false, 0, 1),
                    (CharacterSet::empty().add_char('d'), false, 0, 2),
                    (CharacterSet::empty().add_char('i'), false, 0, 3),
                    (CharacterSet::empty().add_char('f'), false, 0, 4),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('d'),
                        is_separator: false,
                        precedence: 0,
                        states: vec![1, 2],
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('f'),
                        is_separator: false,
                        precedence: 0,
                        states: vec![1, 4],
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('i'),
                        is_separator: false,
                        precedence: 0,
                        states: vec![1, 3],
                    },
                    NfaTransition {
                        characters: CharacterSet::empty()
                            .add_range('a', 'c')
                            .add_char('e')
                            .add_range('g', 'h')
                            .add_range('j', 'z'),
                        is_separator: false,
                        precedence: 0,
                        states: vec![1],
                    },
                ],
            ),
            // negated character class followed by an individual character
            (
                vec![
                    (CharacterSet::empty().add_char('0'), false, 0, 1),
                    (CharacterSet::empty().add_char('b'), false, 0, 2),
                    (
                        CharacterSet::empty().add_range('a', 'f').negate(),
                        false,
                        0,
                        3,
                    ),
                    (CharacterSet::empty().add_char('c'), false, 0, 4),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('0'),
                        precedence: 0,
                        states: vec![1, 3],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('b'),
                        precedence: 0,
                        states: vec![2],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('c'),
                        precedence: 0,
                        states: vec![4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::empty()
                            .add_range('a', 'f')
                            .add_char('0')
                            .negate(),
                        precedence: 0,
                        states: vec![3],
                        is_separator: false,
                    },
                ],
            ),
            // multiple negated character classes
            (
                vec![
                    (CharacterSet::Include(vec!['a']), false, 0, 1),
                    (CharacterSet::Exclude(vec!['a', 'b', 'c']), false, 0, 2),
                    (CharacterSet::Include(vec!['g']), false, 0, 6),
                    (CharacterSet::Exclude(vec!['d', 'e', 'f']), false, 0, 3),
                    (CharacterSet::Exclude(vec!['g', 'h', 'i']), false, 0, 4),
                    (CharacterSet::Include(vec!['g']), false, 0, 5),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['a']),
                        precedence: 0,
                        states: vec![1, 3, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['g']),
                        precedence: 0,
                        states: vec![2, 3, 5, 6],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['b', 'c']),
                        precedence: 0,
                        states: vec![3, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['h', 'i']),
                        precedence: 0,
                        states: vec![2, 3],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['d', 'e', 'f']),
                        precedence: 0,
                        states: vec![2, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::Exclude(vec![
                            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                        ]),
                        precedence: 0,
                        states: vec![2, 3, 4],
                        is_separator: false,
                    },
                ],
            ),
            // disjoint characters with same state
            (
                vec![
                    (CharacterSet::Include(vec!['a']), false, 0, 1),
                    (CharacterSet::Include(vec!['b']), false, 0, 2),
                    (CharacterSet::Include(vec!['c']), false, 0, 1),
                    (CharacterSet::Include(vec!['d']), false, 0, 1),
                    (CharacterSet::Include(vec!['e']), false, 0, 2),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['a', 'c', 'd']),
                        precedence: 0,
                        states: vec![1],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::Include(vec!['b', 'e']),
                        precedence: 0,
                        states: vec![2],
                        is_separator: false,
                    },
                ],
            ),
        ];

        for row in table.iter() {
            assert_eq!(
                NfaCursor::group_transitions(
                    row.0
                        .iter()
                        .map(|(chars, is_sep, prec, state)| (chars, *is_sep, *prec, *state))
                ),
                row.1
            );
        }
    }

    #[test]
    fn test_character_set_remove_intersection() {
        // A whitelist and an overlapping whitelist.
        // Both sets contain 'c', 'd', and 'f'
        let mut a = CharacterSet::empty().add_range('a', 'f');
        let mut b = CharacterSet::empty().add_range('c', 'h');
        assert_eq!(
            a.remove_intersection(&mut b),
            CharacterSet::empty().add_range('c', 'f')
        );
        assert_eq!(a, CharacterSet::empty().add_range('a', 'b'));
        assert_eq!(b, CharacterSet::empty().add_range('g', 'h'));

        let mut a = CharacterSet::empty().add_range('a', 'f');
        let mut b = CharacterSet::empty().add_range('c', 'h');
        assert_eq!(
            b.remove_intersection(&mut a),
            CharacterSet::empty().add_range('c', 'f')
        );
        assert_eq!(a, CharacterSet::empty().add_range('a', 'b'));
        assert_eq!(b, CharacterSet::empty().add_range('g', 'h'));

        // A whitelist and a larger whitelist.
        let mut a = CharacterSet::empty().add_char('c');
        let mut b = CharacterSet::empty().add_range('a', 'e');
        assert_eq!(
            a.remove_intersection(&mut b),
            CharacterSet::empty().add_char('c')
        );
        assert_eq!(a, CharacterSet::empty());
        assert_eq!(
            b,
            CharacterSet::empty()
                .add_range('a', 'b')
                .add_range('d', 'e')
        );

        let mut a = CharacterSet::empty().add_char('c');
        let mut b = CharacterSet::empty().add_range('a', 'e');
        assert_eq!(
            b.remove_intersection(&mut a),
            CharacterSet::empty().add_char('c')
        );
        assert_eq!(a, CharacterSet::empty());
        assert_eq!(
            b,
            CharacterSet::empty()
                .add_range('a', 'b')
                .add_range('d', 'e')
        );

        // A whitelist and an intersecting blacklist.
        // Both sets contain 'e', 'f', and 'm'
        let mut a = CharacterSet::empty()
            .add_range('c', 'h')
            .add_range('k', 'm');
        let mut b = CharacterSet::empty()
            .add_range('a', 'd')
            .add_range('g', 'l')
            .negate();
        assert_eq!(
            a.remove_intersection(&mut b),
            CharacterSet::Include(vec!['e', 'f', 'm'])
        );
        assert_eq!(a, CharacterSet::Include(vec!['c', 'd', 'g', 'h', 'k', 'l']));
        assert_eq!(b, CharacterSet::empty().add_range('a', 'm').negate());

        let mut a = CharacterSet::empty()
            .add_range('c', 'h')
            .add_range('k', 'm');
        let mut b = CharacterSet::empty()
            .add_range('a', 'd')
            .add_range('g', 'l')
            .negate();
        assert_eq!(
            b.remove_intersection(&mut a),
            CharacterSet::Include(vec!['e', 'f', 'm'])
        );
        assert_eq!(a, CharacterSet::Include(vec!['c', 'd', 'g', 'h', 'k', 'l']));
        assert_eq!(b, CharacterSet::empty().add_range('a', 'm').negate());

        // A blacklist and an overlapping blacklist.
        // Both sets exclude 'c', 'd', and 'e'
        let mut a = CharacterSet::empty().add_range('a', 'e').negate();
        let mut b = CharacterSet::empty().add_range('c', 'h').negate();
        assert_eq!(
            a.remove_intersection(&mut b),
            CharacterSet::empty().add_range('a', 'h').negate(),
        );
        assert_eq!(a, CharacterSet::Include(vec!['f', 'g', 'h']));
        assert_eq!(b, CharacterSet::Include(vec!['a', 'b']));

        // A blacklist and a larger blacklist.
        let mut a = CharacterSet::empty().add_range('b', 'c').negate();
        let mut b = CharacterSet::empty().add_range('a', 'd').negate();
        assert_eq!(
            a.remove_intersection(&mut b),
            CharacterSet::empty().add_range('a', 'd').negate(),
        );
        assert_eq!(a, CharacterSet::empty().add_char('a').add_char('d'));
        assert_eq!(b, CharacterSet::empty());
    }

    #[test]
    fn test_character_set_does_intersect() {
        let (a, b) = (CharacterSet::empty(), CharacterSet::empty());
        assert!(!a.does_intersect(&b));
        assert!(!b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::empty().add_char('a'),
            CharacterSet::empty().add_char('a'),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::empty().add_char('b'),
            CharacterSet::empty().add_char('a').add_char('c'),
        );
        assert!(!a.does_intersect(&b));
        assert!(!b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::Include(vec!['b']),
            CharacterSet::Exclude(vec!['a', 'b', 'c']),
        );
        assert!(!a.does_intersect(&b));
        assert!(!b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::Include(vec!['b']),
            CharacterSet::Exclude(vec!['a', 'c']),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::Exclude(vec!['a']),
            CharacterSet::Exclude(vec!['a']),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::Include(vec!['c']),
            CharacterSet::Exclude(vec!['a']),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));
    }
}
