use std::fmt;
use std::char;

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
    },
    Split(u32, u32),
    Accept(usize),
}

#[derive(PartialEq, Eq)]
pub struct Nfa {
    pub states: Vec<NfaState>
}

impl Default for Nfa {
    fn default() -> Self {
        Self { states: Vec::new() }
    }
}

#[derive(Debug)]
pub struct NfaCursor<'a> {
    pub(crate) state_ids: Vec<u32>,
    nfa: &'a Nfa,
    in_sep: bool,
}

impl CharacterSet {
    pub fn empty() -> Self {
        CharacterSet::Include(Vec::new())
    }

    pub fn all() -> Self {
        CharacterSet::Exclude(Vec::new())
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

    pub fn add(self, other: CharacterSet) -> Self {
        if let (CharacterSet::Include(mut chars), CharacterSet::Include(other_chars)) = (self, other) {
            chars.extend(other_chars);
            chars.sort_unstable();
            chars.dedup();
            CharacterSet::Include(chars)
        } else {
            panic!("Called add with a negated character set");
        }
    }

    pub fn contains(&self, c: char) -> bool {
        match self {
            CharacterSet::Include(chars) => chars.contains(&c),
            CharacterSet::Exclude(chars) => !chars.contains(&c),
        }
    }
}

impl Nfa {
    pub fn new() -> Self {
        Nfa { states: Vec::new() }
    }

    pub fn last_state_id(&self) -> u32 {
        self.states.len() as u32 - 1
    }

    pub fn prepend(&mut self, f: impl Fn(u32) -> NfaState) {
        self.states.push(f(self.last_state_id()));
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
        let mut result = Self { nfa, state_ids: Vec::new(), in_sep: true };
        result.add_states(&mut states);
        result
    }

    pub fn advance(&mut self, c: char) -> bool {
        let mut result = false;
        let mut new_state_ids = Vec::new();
        let mut any_sep_transitions = false;
        for current_state_id in &self.state_ids {
            if let NfaState::Advance { chars, state_id, is_sep } = &self.nfa.states[*current_state_id as usize] {
                if chars.contains(c) {
                    if *is_sep {
                        any_sep_transitions = true;
                    }
                    new_state_ids.push(*state_id);
                    result = true;
                }
            }
        }
        if !any_sep_transitions {
            self.in_sep = false;
        }
        self.state_ids.clear();
        self.add_states(&mut new_state_ids);
        result
    }

    pub fn finished_id(&self) -> Option<usize> {
        let mut result = None;
        for state_id in self.state_ids.iter() {
            if let NfaState::Accept(id) = self.nfa.states[*state_id as usize] {
                match result {
                    None => {
                        result = Some(id)
                    },
                    Some(existing_id) => if id < existing_id {
                        result = Some(id)
                    }
                }
            }
        }
        result
    }

    pub fn in_separator(&self) -> bool {
        self.in_sep
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
