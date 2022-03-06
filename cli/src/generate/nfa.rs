use std::char;
use std::cmp::max;
use std::cmp::Ordering;
use std::collections::HashSet;
use std::fmt;
use std::mem::swap;
use std::ops::Range;

/// A set of characters represented as a vector of ranges.
#[derive(Clone, PartialEq, Eq, Hash)]
pub struct CharacterSet {
    ranges: Vec<Range<u32>>,
}

/// A state in an NFA representing a regular grammar.
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

const END: u32 = char::MAX as u32 + 1;

impl CharacterSet {
    /// Create a character set with a single character.
    pub fn empty() -> Self {
        CharacterSet { ranges: Vec::new() }
    }

    /// Create a character set with a given *inclusive* range of characters.
    pub fn from_range(mut first: char, mut last: char) -> Self {
        if first > last {
            swap(&mut first, &mut last);
        }
        CharacterSet {
            ranges: vec![(first as u32)..(last as u32 + 1)],
        }
    }

    /// Create a character set with a single character.
    pub fn from_char(c: char) -> Self {
        CharacterSet {
            ranges: vec![(c as u32)..(c as u32 + 1)],
        }
    }

    /// Create a character set containing all characters *not* present
    /// in this character set.
    pub fn negate(mut self) -> CharacterSet {
        let mut i = 0;
        let mut previous_end = 0;
        while i < self.ranges.len() {
            let range = &mut self.ranges[i];
            let start = previous_end;
            previous_end = range.end;
            if start < range.start {
                self.ranges[i] = start..range.start;
                i += 1;
            } else {
                self.ranges.remove(i);
            }
        }
        if previous_end < END {
            self.ranges.push(previous_end..END);
        }
        self
    }

    pub fn add_char(mut self, c: char) -> Self {
        self.add_int_range(0, c as u32, c as u32 + 1);
        self
    }

    pub fn add_range(mut self, start: char, end: char) -> Self {
        self.add_int_range(0, start as u32, end as u32 + 1);
        self
    }

    pub fn add(mut self, other: &CharacterSet) -> Self {
        let mut index = 0;
        for range in &other.ranges {
            index = self.add_int_range(index, range.start as u32, range.end as u32);
        }
        self
    }

    fn add_int_range(&mut self, mut i: usize, start: u32, end: u32) -> usize {
        while i < self.ranges.len() {
            let range = &mut self.ranges[i];
            if range.start > end {
                self.ranges.insert(i, start..end);
                return i;
            }
            if range.end >= start {
                range.end = range.end.max(end);
                range.start = range.start.min(start);

                // Join this range with the next range if needed.
                while i + 1 < self.ranges.len() && self.ranges[i + 1].start <= self.ranges[i].end {
                    self.ranges[i].end = self.ranges[i].end.max(self.ranges[i + 1].end);
                    self.ranges.remove(i + 1);
                }

                return i;
            }
            i += 1;
        }
        self.ranges.push(start..end);
        i
    }

    pub fn does_intersect(&self, other: &CharacterSet) -> bool {
        let mut left_ranges = self.ranges.iter();
        let mut right_ranges = other.ranges.iter();
        let mut left_range = left_ranges.next();
        let mut right_range = right_ranges.next();
        while let (Some(left), Some(right)) = (&left_range, &right_range) {
            if left.end <= right.start {
                left_range = left_ranges.next();
            } else if left.start >= right.end {
                right_range = right_ranges.next();
            } else {
                return true;
            }
        }
        false
    }

    /// Get the set of characters that are present in both this set
    /// and the other set. Remove those common characters from both
    /// of the operands.
    pub fn remove_intersection(&mut self, other: &mut CharacterSet) -> CharacterSet {
        let mut intersection = Vec::new();
        let mut left_i = 0;
        let mut right_i = 0;
        while left_i < self.ranges.len() && right_i < other.ranges.len() {
            let left = &mut self.ranges[left_i];
            let right = &mut other.ranges[right_i];

            match left.start.cmp(&right.start) {
                Ordering::Less => {
                    // [ L ]
                    //     [ R ]
                    if left.end <= right.start {
                        left_i += 1;
                        continue;
                    }

                    match left.end.cmp(&right.end) {
                        // [ L ]
                        //   [ R ]
                        Ordering::Less => {
                            intersection.push(right.start..left.end);
                            swap(&mut left.end, &mut right.start);
                            left_i += 1;
                        }

                        // [  L  ]
                        //   [ R ]
                        Ordering::Equal => {
                            intersection.push(right.clone());
                            left.end = right.start;
                            other.ranges.remove(right_i);
                        }

                        // [   L   ]
                        //   [ R ]
                        Ordering::Greater => {
                            intersection.push(right.clone());
                            let new_range = left.start..right.start;
                            left.start = right.end;
                            self.ranges.insert(left_i, new_range);
                            other.ranges.remove(right_i);
                            left_i += 1;
                        }
                    }
                }
                Ordering::Equal => {
                    // [ L ]
                    // [  R  ]
                    if left.end < right.end {
                        intersection.push(left.start..left.end);
                        right.start = left.end;
                        self.ranges.remove(left_i);
                    }
                    // [ L ]
                    // [ R ]
                    else if left.end == right.end {
                        intersection.push(left.clone());
                        self.ranges.remove(left_i);
                        other.ranges.remove(right_i);
                    }
                    // [  L  ]
                    // [ R ]
                    else if left.end > right.end {
                        intersection.push(right.clone());
                        left.start = right.end;
                        other.ranges.remove(right_i);
                    }
                }
                Ordering::Greater => {
                    //     [ L ]
                    // [ R ]
                    if left.start >= right.end {
                        right_i += 1;
                        continue;
                    }

                    match left.end.cmp(&right.end) {
                        //   [ L ]
                        // [   R   ]
                        Ordering::Less => {
                            intersection.push(left.clone());
                            let new_range = right.start..left.start;
                            right.start = left.end;
                            other.ranges.insert(right_i, new_range);
                            self.ranges.remove(left_i);
                            right_i += 1;
                        }

                        //   [ L ]
                        // [  R  ]
                        Ordering::Equal => {
                            intersection.push(left.clone());
                            right.end = left.start;
                            self.ranges.remove(left_i);
                        }

                        //   [   L   ]
                        // [   R   ]
                        Ordering::Greater => {
                            intersection.push(left.start..right.end);
                            swap(&mut left.start, &mut right.end);
                            right_i += 1;
                        }
                    }
                }
            }
        }
        CharacterSet {
            ranges: intersection,
        }
    }

    /// Produces a `CharacterSet` containing every character in `self` that is not present in
    /// `other`.
    pub fn difference(mut self, mut other: CharacterSet) -> CharacterSet {
        self.remove_intersection(&mut other);
        self
    }

    /// Produces a `CharacterSet` containing every character that is in _exactly one_ of `self` or
    /// `other`, but is not present in both sets.
    pub fn symmetric_difference(mut self, mut other: CharacterSet) -> CharacterSet {
        self.remove_intersection(&mut other);
        self.add(&other)
    }

    pub fn iter<'a>(&'a self) -> impl Iterator<Item = u32> + 'a {
        self.ranges.iter().flat_map(|r| r.clone())
    }

    pub fn chars<'a>(&'a self) -> impl Iterator<Item = char> + 'a {
        self.iter().filter_map(char::from_u32)
    }

    pub fn is_empty(&self) -> bool {
        self.ranges.is_empty()
    }

    /// Get a reduced list of character ranges, assuming that a given
    /// set of characters can be safely ignored.
    pub fn simplify_ignoring<'a>(
        &'a self,
        ruled_out_characters: &'a HashSet<u32>,
    ) -> Vec<Range<char>> {
        let mut prev_range: Option<Range<char>> = None;
        self.chars()
            .map(|c| (c, false))
            .chain(Some(('\0', true)))
            .filter_map(move |(c, done)| {
                if done {
                    return prev_range.clone();
                }
                if ruled_out_characters.contains(&(c as u32)) {
                    return None;
                }
                if let Some(range) = prev_range.clone() {
                    let mut prev_range_successor = range.end as u32 + 1;
                    while prev_range_successor < c as u32 {
                        if !ruled_out_characters.contains(&prev_range_successor) {
                            prev_range = Some(c..c);
                            return Some(range);
                        }
                        prev_range_successor += 1;
                    }
                    prev_range = Some(range.start..c);
                    None
                } else {
                    prev_range = Some(c..c);
                    None
                }
            })
            .collect()
    }

    pub fn contains(&self, c: char) -> bool {
        self.ranges.iter().any(|r| r.contains(&(c as u32)))
    }
}

impl Ord for CharacterSet {
    fn cmp(&self, other: &CharacterSet) -> Ordering {
        let count_cmp = self
            .ranges
            .iter()
            .map(|r| r.len())
            .sum::<usize>()
            .cmp(&other.ranges.iter().map(|r| r.len()).sum());
        if count_cmp != Ordering::Equal {
            return count_cmp;
        }

        for (left_range, right_range) in self.ranges.iter().zip(other.ranges.iter()) {
            let cmp = left_range.len().cmp(&right_range.len());
            if cmp != Ordering::Equal {
                return cmp;
            }

            for (left, right) in left_range.clone().zip(right_range.clone()) {
                let cmp = left.cmp(&right);
                if cmp != Ordering::Equal {
                    return cmp;
                }
            }
        }
        return Ordering::Equal;
    }
}

impl PartialOrd for CharacterSet {
    fn partial_cmp(&self, other: &CharacterSet) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl fmt::Debug for CharacterSet {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "CharacterSet [")?;
        let mut set = self.clone();
        if self.contains(char::MAX) {
            write!(f, "^ ")?;
            set = set.negate();
        }
        for (i, c) in set.chars().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }
            write!(f, "{:?}", c)?;
        }
        write!(f, "]")?;
        Ok(())
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
    fn test_adding_ranges() {
        let mut set = CharacterSet::empty()
            .add_range('c', 'm')
            .add_range('q', 's');

        // within existing range
        set = set.add_char('d');
        assert_eq!(
            set,
            CharacterSet::empty()
                .add_range('c', 'm')
                .add_range('q', 's')
        );

        // at end of existing range
        set = set.add_char('m');
        assert_eq!(
            set,
            CharacterSet::empty()
                .add_range('c', 'm')
                .add_range('q', 's')
        );

        // adjacent to end of existing range
        set = set.add_char('n');
        assert_eq!(
            set,
            CharacterSet::empty()
                .add_range('c', 'n')
                .add_range('q', 's')
        );

        // filling gap between existing ranges
        set = set.add_range('o', 'p');
        assert_eq!(set, CharacterSet::empty().add_range('c', 's'));

        set = CharacterSet::empty()
            .add_range('c', 'f')
            .add_range('i', 'l')
            .add_range('n', 'r');
        set = set.add_range('d', 'o');
        assert_eq!(set, CharacterSet::empty().add_range('c', 'r'));
    }

    #[test]
    fn test_adding_sets() {
        let set1 = CharacterSet::empty()
            .add_range('c', 'f')
            .add_range('i', 'l');
        let set2 = CharacterSet::empty().add_range('b', 'g').add_char('h');
        assert_eq!(
            set1.add(&set2),
            CharacterSet::empty()
                .add_range('b', 'g')
                .add_range('h', 'l')
        );
    }

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
                    (CharacterSet::from_char('a'), false, 0, 1),
                    (CharacterSet::from_range('a', 'c').negate(), false, 0, 2),
                    (CharacterSet::from_char('g'), false, 0, 6),
                    (CharacterSet::from_range('d', 'f').negate(), false, 0, 3),
                    (CharacterSet::from_range('g', 'i').negate(), false, 0, 4),
                    (CharacterSet::from_char('g'), false, 0, 5),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::from_char('a'),
                        precedence: 0,
                        states: vec![1, 3, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::from_char('g'),
                        precedence: 0,
                        states: vec![2, 3, 5, 6],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::from_range('b', 'c'),
                        precedence: 0,
                        states: vec![3, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::from_range('h', 'i'),
                        precedence: 0,
                        states: vec![2, 3],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::from_range('d', 'f'),
                        precedence: 0,
                        states: vec![2, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::from_range('a', 'i').negate(),
                        precedence: 0,
                        states: vec![2, 3, 4],
                        is_separator: false,
                    },
                ],
            ),
            // disjoint characters with same state
            (
                vec![
                    (CharacterSet::from_char('a'), false, 0, 1),
                    (CharacterSet::from_char('b'), false, 0, 2),
                    (CharacterSet::from_char('c'), false, 0, 1),
                    (CharacterSet::from_char('d'), false, 0, 1),
                    (CharacterSet::from_char('e'), false, 0, 2),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('a').add_range('c', 'd'),
                        precedence: 0,
                        states: vec![1],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::empty().add_char('b').add_char('e'),
                        precedence: 0,
                        states: vec![2],
                        is_separator: false,
                    },
                ],
            ),
        ];

        for (i, row) in table.iter().enumerate() {
            assert_eq!(
                NfaCursor::group_transitions(
                    row.0
                        .iter()
                        .map(|(chars, is_sep, prec, state)| (chars, *is_sep, *prec, *state))
                ),
                row.1,
                "row {}",
                i
            );
        }
    }

    #[test]
    fn test_character_set_intersection_difference_ops() {
        struct Row {
            left: CharacterSet,
            right: CharacterSet,
            left_only: CharacterSet,
            right_only: CharacterSet,
            intersection: CharacterSet,
        }

        let rows = [
            // [ L ]
            //     [ R ]
            Row {
                left: CharacterSet::from_range('a', 'f'),
                right: CharacterSet::from_range('g', 'm'),
                left_only: CharacterSet::from_range('a', 'f'),
                right_only: CharacterSet::from_range('g', 'm'),
                intersection: CharacterSet::empty(),
            },
            // [ L ]
            //   [ R ]
            Row {
                left: CharacterSet::from_range('a', 'f'),
                right: CharacterSet::from_range('c', 'i'),
                left_only: CharacterSet::from_range('a', 'b'),
                right_only: CharacterSet::from_range('g', 'i'),
                intersection: CharacterSet::from_range('c', 'f'),
            },
            // [  L  ]
            //   [ R ]
            Row {
                left: CharacterSet::from_range('a', 'f'),
                right: CharacterSet::from_range('d', 'f'),
                left_only: CharacterSet::from_range('a', 'c'),
                right_only: CharacterSet::empty(),
                intersection: CharacterSet::from_range('d', 'f'),
            },
            // [   L   ]
            //   [ R ]
            Row {
                left: CharacterSet::from_range('a', 'm'),
                right: CharacterSet::from_range('d', 'f'),
                left_only: CharacterSet::empty()
                    .add_range('a', 'c')
                    .add_range('g', 'm'),
                right_only: CharacterSet::empty(),
                intersection: CharacterSet::from_range('d', 'f'),
            },
            // [    L    ]
            //         [R]
            Row {
                left: CharacterSet::from_range(',', '/'),
                right: CharacterSet::from_char('/'),
                left_only: CharacterSet::from_range(',', '.'),
                right_only: CharacterSet::empty(),
                intersection: CharacterSet::from_char('/'),
            },
            // [    L    ]
            //         [R]
            Row {
                left: CharacterSet::from_range(',', '/'),
                right: CharacterSet::from_char('/'),
                left_only: CharacterSet::from_range(',', '.'),
                right_only: CharacterSet::empty(),
                intersection: CharacterSet::from_char('/'),
            },
            // [ L1 ] [ L2 ]
            //    [  R  ]
            Row {
                left: CharacterSet::empty()
                    .add_range('a', 'e')
                    .add_range('h', 'l'),
                right: CharacterSet::from_range('c', 'i'),
                left_only: CharacterSet::empty()
                    .add_range('a', 'b')
                    .add_range('j', 'l'),
                right_only: CharacterSet::from_range('f', 'g'),
                intersection: CharacterSet::empty()
                    .add_range('c', 'e')
                    .add_range('h', 'i'),
            },
        ];

        for (i, row) in rows.iter().enumerate() {
            let mut left = row.left.clone();
            let mut right = row.right.clone();
            assert_eq!(
                left.remove_intersection(&mut right),
                row.intersection,
                "row {}a: {:?} && {:?}",
                i,
                row.left,
                row.right
            );
            assert_eq!(
                left, row.left_only,
                "row {}a: {:?} - {:?}",
                i, row.left, row.right
            );
            assert_eq!(
                right, row.right_only,
                "row {}a: {:?} - {:?}",
                i, row.right, row.left
            );

            let mut left = row.left.clone();
            let mut right = row.right.clone();
            assert_eq!(
                right.remove_intersection(&mut left),
                row.intersection,
                "row {}b: {:?} && {:?}",
                i,
                row.left,
                row.right
            );
            assert_eq!(
                left, row.left_only,
                "row {}b: {:?} - {:?}",
                i, row.left, row.right
            );
            assert_eq!(
                right, row.right_only,
                "row {}b: {:?} - {:?}",
                i, row.right, row.left
            );

            assert_eq!(
                row.left.clone().difference(row.right.clone()),
                row.left_only,
                "row {}b: {:?} -- {:?}",
                i,
                row.left,
                row.right
            );

            let symm_difference = row.left_only.clone().add(&mut row.right_only.clone());
            assert_eq!(
                row.left.clone().symmetric_difference(row.right.clone()),
                symm_difference,
                "row {}b: {:?} ~~ {:?}",
                i,
                row.left,
                row.right
            )
        }
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
            CharacterSet::from_char('b'),
            CharacterSet::from_range('a', 'c'),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::from_char('b'),
            CharacterSet::from_range('a', 'c').negate(),
        );
        assert!(!a.does_intersect(&b));
        assert!(!b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::from_char('a').negate(),
            CharacterSet::from_char('a').negate(),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::from_char('c'),
            CharacterSet::from_char('a').negate(),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::from_range('c', 'f'),
            CharacterSet::from_char('f'),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));
    }

    #[test]
    fn test_character_set_get_ranges() {
        struct Row {
            chars: Vec<char>,
            ruled_out_chars: Vec<char>,
            expected_ranges: Vec<Range<char>>,
        }

        let table = [
            Row {
                chars: vec!['a'],
                ruled_out_chars: vec![],
                expected_ranges: vec!['a'..'a'],
            },
            Row {
                chars: vec!['a', 'b', 'c', 'e', 'z'],
                ruled_out_chars: vec![],
                expected_ranges: vec!['a'..'c', 'e'..'e', 'z'..'z'],
            },
            Row {
                chars: vec!['a', 'b', 'c', 'e', 'h', 'z'],
                ruled_out_chars: vec!['d', 'f', 'g'],
                expected_ranges: vec!['a'..'h', 'z'..'z'],
            },
        ];

        for Row {
            chars,
            ruled_out_chars,
            expected_ranges,
        } in table.iter()
        {
            let ruled_out_chars = ruled_out_chars
                .into_iter()
                .map(|c: &char| *c as u32)
                .collect();
            let mut set = CharacterSet::empty();
            for c in chars {
                set = set.add_char(*c);
            }
            let ranges = set.simplify_ignoring(&ruled_out_chars);
            assert_eq!(ranges, *expected_ranges);
        }
    }
}
