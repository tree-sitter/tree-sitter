use std::fmt;
use std::char;

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum CharacterSet {
    Include(Vec<char>),
    Exclude(Vec<char>),
}

#[derive(Debug, PartialEq, Eq)]
pub enum NfaState {
    Advance(CharacterSet, u32),
    Split(u32, u32),
    Accept,
}

#[derive(PartialEq, Eq)]
pub struct Nfa {
    pub states: Vec<NfaState>
}

#[derive(Debug)]
pub struct NfaCursor<'a> {
    indices: Vec<u32>,
    nfa: &'a Nfa,
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
        Nfa { states: vec![NfaState::Accept] }
    }

    pub fn start_index(&self) -> u32 {
        self.states.len() as u32 - 1
    }

    pub fn prepend(&mut self, f: impl Fn(u32) -> NfaState) {
        self.states.push(f(self.start_index()));
    }
}

impl fmt::Debug for Nfa {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Nfa {{ states: {{")?;
        for (i, state) in self.states.iter().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }
            write!(f, "{}: {:?}", i, state)?;
        }
        write!(f, "}} }}")?;
        Ok(())
    }
}

impl<'a> NfaCursor<'a> {
    pub fn new(nfa: &'a Nfa) -> Self {
        let mut result = Self { nfa, indices: Vec::new() };
        result.add_indices(&mut vec![nfa.start_index()]);
        result
    }

    pub fn advance(&mut self, c: char) -> bool {
        let mut result = false;
        let mut new_indices = Vec::new();
        for index in &self.indices {
            if let NfaState::Advance(chars, next_index) = &self.nfa.states[*index as usize] {
                if chars.contains(c) {
                    new_indices.push(*next_index);
                    result = true;
                }
            }
        }
        self.indices.clear();
        self.add_indices(&mut new_indices);
        result
    }

    pub fn is_done(&self) -> bool {
        self.indices.iter().any(|index| {
            if let NfaState::Accept = self.nfa.states[*index as usize] {
                true
            } else {
                false
            }
        })
    }

    pub fn add_indices(&mut self, new_indices: &mut Vec<u32>) {
        while let Some(index) = new_indices.pop() {
            let state = &self.nfa.states[index as usize];
            if let NfaState::Split(left, right) = state {
                new_indices.push(*left);
                new_indices.push(*right);
            } else if let Err(i) = self.indices.binary_search(&index) {
                self.indices.insert(i, index);
            }
        }
    }
}
