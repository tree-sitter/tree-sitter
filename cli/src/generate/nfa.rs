use std::char;
use std::cmp::max;
use std::cmp::Ordering;
use std::fmt;
use std::iter::FromIterator;
use std::mem::swap;
use unic_char_range::{chars, CharRange};

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct CharacterSet {
    ranges: Vec<CharRange>,
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
        Self { ranges: Vec::new() }
    }

    pub fn singleton(c: char) -> Self {
        Self {
            ranges: vec![chars!(c..=c)],
        }
    }

    pub fn negate(&self) -> Self {
        let mut new = Self::empty();
        if self.ranges[0].low != '\0' {
            let high = self.ranges[0].low;
            new.ranges.push(chars!('\0'..high));
        }
        for pair in self.ranges.windows(2) {
            let low = pair[0].high;
            let high = pair[1].low;
            let mut range = chars!(low..high).iter();
            range.next(); // remove front
            new.ranges.push(range.into());
        }
        if self.ranges.last().unwrap().high != char::MAX {
            let low = self.ranges.last().unwrap().high;
            let high = char::MAX;
            let mut range = chars!(low..=high).iter();
            range.next(); // remove front
            new.ranges.push(range.into());
        }
        new
    }

    fn normalize(&mut self) {
        self.ranges.sort_unstable_by_key(|r| r.low);
        self.ranges.retain(|r| !r.is_empty());
        let mut i = 1;
        while i < self.ranges.len() {
            let low = self.ranges[i - 1].high;
            let high = self.ranges[i].low;
            if chars!(low..=high).len() <= 2 {
                self.ranges[i - 1].high = self.ranges[i].high;
                self.ranges.remove(i);
            } else {
                i += 1;
            }
        }
    }

    pub fn add_char(mut self, c: char) -> Self {
        if let Err(i) = self.ranges.binary_search_by(|r| r.cmp_char(c)) {
            self.ranges.insert(i, chars!(c..=c));
            self.normalize(); // TODO: can we keep it normalized?
        }
        self
    }

    pub fn remove_char(&mut self, c: char) {
        if let Ok(i) = self.ranges.binary_search_by(|r| r.cmp_char(c)) {
            let mut right = chars!(c..=(self.ranges[i].high)).iter();
            let mut left = chars!((self.ranges[i].low)..=c).iter();
            // remove c
            let _ = right.next();
            let _ = left.next_back();
            // reinsert ranges
            self.ranges[i] = left.into();
            self.ranges.insert(i, right.into());
            self.normalize(); // TODO: can we keep it normalized?
        }
    }

    pub fn add_range(mut self, start: char, end: char) -> Self {
        self.ranges.push(chars!(start..=end));
        self.normalize(); // TODO: can we keep it normalized?
        self
    }

    pub fn remove_range(&mut self, start: char, end: char) {
        self.remove_char(start);
        self.remove_char(end);
        let low = self
            .ranges
            .binary_search_by(|r| r.cmp_char(start))
            .unwrap_err();
        let high = self
            .ranges
            .binary_search_by(|r| r.cmp_char(end))
            .unwrap_err();
        self.ranges.drain(low..high);
    }

    pub fn add(mut self, other: &CharacterSet) -> Self {
        self.ranges.extend(&other.ranges);
        self.normalize();
        self
    }

    pub fn does_intersect(&self, other: &CharacterSet) -> bool {
        let mut li = 0;
        let mut ri = 0;

        while li < self.ranges.len() && ri < other.ranges.len() {
            if self.ranges[li].high < other.ranges[ri].low {
                li += 1;
            } else if other.ranges[ri].high < self.ranges[li].low {
                ri += 1;
            } else {
                return true;
            }
        }

        false
    }

    fn intersection(&self, other: &CharacterSet) -> CharacterSet {
        let mut intersection = CharacterSet::empty();
        let mut si = 0;
        let mut oi = 0;
        while si < self.ranges.len() && oi < other.ranges.len() {
            if self.ranges[si].high < other.ranges[oi].low {
                // self before other
                si += 1;
            } else if other.ranges[oi].high < self.ranges[si].low {
                // other before self
                oi += 1;
            } else {
                // self overlaps other
                // self.high >= other.low
                // self.low <= other.high
                match (
                    self.ranges[si].low >= other.ranges[oi].low,
                    other.ranges[oi].high <= self.ranges[si].high,
                ) {
                    (true, true) => {
                        //   |--self---|
                        // |--other--|
                        intersection =
                            intersection.add_range(self.ranges[si].low, other.ranges[oi].high);
                        oi += 1;
                    }
                    (true, false) => {
                        //  |--self---|
                        // |---other---|
                        intersection =
                            intersection.add_range(self.ranges[si].low, self.ranges[si].high);
                        si += 1;
                    }
                    (false, true) => {
                        // |--self---|
                        //  |-other-|
                        intersection =
                            intersection.add_range(other.ranges[oi].low, other.ranges[oi].high);
                        oi += 1;
                    }
                    (false, false) => {
                        // |--self---|
                        //  |---other---|
                        intersection =
                            intersection.add_range(other.ranges[oi].low, self.ranges[si].high);
                        si += 1;
                    }
                }
            }
        }
        intersection
    }

    pub fn remove_intersection(&mut self, other: &mut CharacterSet) -> CharacterSet {
        let intersection = self.intersection(other);
        for r in &intersection.ranges {
            self.remove_range(r.low, r.high);
            other.remove_range(r.low, r.high);
        }
        intersection
    }

    pub fn is_empty(&self) -> bool {
        self.ranges.is_empty()
    }

    #[cfg(test)]
    pub fn contains(&self, c: char) -> bool {
        self.ranges.binary_search_by(|r| r.cmp_char(c)).is_ok()
    }

    pub fn iter(&self) -> impl Iterator<Item = char> + '_ {
        self.ranges.iter().flat_map(|r| r.iter())
    }

    pub fn ranges(&self) -> impl Iterator<Item = std::ops::RangeInclusive<char>> + '_ {
        self.ranges.iter().map(|r| r.low..=r.high)
    }

    pub fn count(&self) -> usize {
        self.ranges.iter().map(|r| r.len()).count()
    }
}

impl FromIterator<char> for CharacterSet {
    fn from_iter<T: IntoIterator<Item = char>>(iter: T) -> Self {
        let mut set = CharacterSet::empty();
        for c in iter {
            set = set.add_char(c);
        }
        set
    }
}

impl Ord for CharacterSet {
    fn cmp(&self, other: &CharacterSet) -> Ordering {
        if self.is_empty() {
            if other.is_empty() {
                Ordering::Equal
            } else {
                Ordering::Less
            }
        } else if other.is_empty() {
            Ordering::Greater
        } else {
            let cmp = self.count().cmp(&other.count());
            if cmp != Ordering::Equal {
                return cmp;
            }
            let mut si = 0;
            let mut oi = 0;
            while si < self.ranges.len() && oi < other.ranges.len() {
                let s = self.ranges[si];
                let o = other.ranges[oi];
                let lcmp = s.low.cmp(&o.low);
                if lcmp != Ordering::Equal {
                    return lcmp;
                }
                let hcmp = s.high.cmp(&o.high);
                if hcmp != Ordering::Equal {
                    return hcmp;
                }
                si += 1;
                oi += 1;
            }
            if si < self.ranges.len() {
                Ordering::Greater
            } else if oi < other.ranges.len() {
                Ordering::Less
            } else {
                Ordering::Equal
            }
        }
    }
}

impl PartialOrd for CharacterSet {
    fn partial_cmp(&self, other: &CharacterSet) -> Option<Ordering> {
        Some(self.cmp(other))
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
                    (CharacterSet::singleton('a'), false, 0, 1),
                    (
                        vec!['a', 'b', 'c']
                            .into_iter()
                            .collect::<CharacterSet>()
                            .negate(),
                        false,
                        0,
                        2,
                    ),
                    (CharacterSet::singleton('g'), false, 0, 6),
                    (
                        vec!['d', 'e', 'f']
                            .into_iter()
                            .collect::<CharacterSet>()
                            .negate(),
                        false,
                        0,
                        3,
                    ),
                    (
                        vec!['g', 'h', 'i']
                            .into_iter()
                            .collect::<CharacterSet>()
                            .negate(),
                        false,
                        0,
                        4,
                    ),
                    (CharacterSet::singleton('g'), false, 0, 5),
                ],
                vec![
                    NfaTransition {
                        characters: CharacterSet::singleton('a'),
                        precedence: 0,
                        states: vec![1, 3, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: CharacterSet::singleton('g'),
                        precedence: 0,
                        states: vec![2, 3, 5, 6],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: vec!['b', 'c'].into_iter().collect(),
                        precedence: 0,
                        states: vec![3, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: vec!['h', 'i'].into_iter().collect(),
                        precedence: 0,
                        states: vec![2, 3],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: vec!['d', 'e', 'f'].into_iter().collect(),
                        precedence: 0,
                        states: vec![2, 4],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: vec!['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
                            .into_iter()
                            .collect::<CharacterSet>()
                            .negate(),
                        precedence: 0,
                        states: vec![2, 3, 4],
                        is_separator: false,
                    },
                ],
            ),
            // disjoint characters with same state
            (
                vec![
                    (CharacterSet::singleton('a'), false, 0, 1),
                    (CharacterSet::singleton('b'), false, 0, 2),
                    (CharacterSet::singleton('c'), false, 0, 1),
                    (CharacterSet::singleton('d'), false, 0, 1),
                    (CharacterSet::singleton('e'), false, 0, 2),
                ],
                vec![
                    NfaTransition {
                        characters: vec!['a', 'c', 'd'].into_iter().collect(),
                        precedence: 0,
                        states: vec![1],
                        is_separator: false,
                    },
                    NfaTransition {
                        characters: vec!['b', 'e'].into_iter().collect(),
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
                        .map(|(chars, is_sep, prec, state)| (chars, *is_sep, *prec, *state)),
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
            vec!['e', 'f', 'm'].into_iter().collect()
        );
        assert_eq!(a, vec!['c', 'd', 'g', 'h', 'k', 'l'].into_iter().collect());
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
            vec!['e', 'f', 'm'].into_iter().collect()
        );
        assert_eq!(a, vec!['c', 'd', 'g', 'h', 'k', 'l'].into_iter().collect());
        assert_eq!(b, CharacterSet::empty().add_range('a', 'm').negate());

        // A blacklist and an overlapping blacklist.
        // Both sets exclude 'c', 'd', and 'e'
        let mut a = CharacterSet::empty().add_range('a', 'e').negate();
        let mut b = CharacterSet::empty().add_range('c', 'h').negate();
        assert_eq!(
            a.remove_intersection(&mut b),
            CharacterSet::empty().add_range('a', 'h').negate(),
        );
        assert_eq!(a, vec!['f', 'g', 'h'].into_iter().collect());
        assert_eq!(b, vec!['a', 'b'].into_iter().collect());

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
            CharacterSet::singleton('b'),
            vec!['a', 'b', 'c']
                .into_iter()
                .collect::<CharacterSet>()
                .negate(),
        );
        assert!(!a.does_intersect(&b));
        assert!(!b.does_intersect(&a));

        let (a, b) = (
            CharacterSet::singleton('b'),
            vec!['a', 'c']
                .into_iter()
                .collect::<CharacterSet>()
                .negate(),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));

        let (a, b) = (
            vec!['a'].into_iter().collect::<CharacterSet>().negate(),
            vec!['a'].into_iter().collect::<CharacterSet>().negate(),
        );
        assert!(a.does_intersect(&b));
        assert!(b.does_intersect(&a));
    }
}
