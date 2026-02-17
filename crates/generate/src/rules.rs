use std::{
    collections::BTreeMap,
    fmt,
    hash::{Hash, Hasher},
};

use serde::Serialize;

use super::grammars::VariableType;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize)]
pub enum SymbolType {
    External,
    End,
    EndOfNonTerminalExtra,
    Terminal,
    NonTerminal,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize)]
pub enum Associativity {
    Left,
    Right,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize)]
pub struct Alias {
    pub value: String,
    pub is_named: bool,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Default, Serialize)]
pub enum Precedence {
    #[default]
    None,
    Integer(i32),
    Name(String),
}

pub type AliasMap = BTreeMap<Symbol, Alias>;

#[derive(Clone, Debug, Default, PartialEq, Eq, Hash, Serialize)]
pub struct MetadataParams {
    pub precedence: Precedence,
    pub dynamic_precedence: i32,
    pub associativity: Option<Associativity>,
    pub is_token: bool,
    pub is_main_token: bool,
    pub alias: Option<Alias>,
    pub field_name: Option<String>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize)]
pub struct Symbol {
    pub kind: SymbolType,
    pub index: usize,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, Serialize)]
pub enum Rule {
    Blank,
    String(String),
    Pattern(String, String),
    NamedSymbol(String),
    Symbol(Symbol),
    Choice(Vec<Self>),
    Metadata {
        params: MetadataParams,
        rule: Box<Self>,
    },
    Repeat(Box<Self>),
    Seq(Vec<Self>),
    Reserved {
        rule: Box<Self>,
        context_name: String,
    },
}

/// A bit vector backed by Vec<u64> that supports efficient word-level bulk
/// operations. Token sets are OR'd together many of times and doing this at
/// the word level rather than bit-by-bit is much faster.
#[derive(Clone, Default)]
struct BitVec {
    data: Vec<u64>,
    num_bits: usize,
}

impl BitVec {
    const fn new() -> Self {
        Self {
            data: Vec::new(),
            num_bits: 0,
        }
    }

    fn with_capacity(n_bits: usize) -> Self {
        Self {
            data: Vec::with_capacity((n_bits + 63) / 64),
            num_bits: 0,
        }
    }

    fn len(&self) -> usize {
        self.num_bits
    }

    fn get(&self, index: usize) -> Option<bool> {
        if index >= self.num_bits {
            return None;
        }
        Some(self.data[index / 64] >> (index % 64) & 1 != 0)
    }

    fn set(&mut self, index: usize, val: bool) {
        let word_idx = index / 64;
        let bit_idx = index % 64;
        if val {
            self.data[word_idx] |= 1u64 << bit_idx;
        } else {
            self.data[word_idx] &= !(1u64 << bit_idx);
        }
    }

    fn resize(&mut self, new_len: usize, val: bool) {
        let fill = if val { !0u64 } else { 0u64 };
        self.data.resize((new_len + 63) / 64, fill);
        self.num_bits = new_len;
    }

    fn last(&self) -> Option<bool> {
        if self.num_bits == 0 {
            return None;
        }
        self.get(self.num_bits - 1)
    }

    fn pop(&mut self) -> Option<bool> {
        if self.num_bits == 0 {
            return None;
        }
        self.num_bits -= 1;
        let word_idx = self.num_bits / 64;
        let bit_idx = self.num_bits % 64;
        let val = self.data[word_idx] >> bit_idx & 1 != 0;
        if val {
            self.data[word_idx] &= !(1u64 << bit_idx);
        }
        self.data.truncate((self.num_bits + 63) / 64);
        Some(val)
    }

    /// Word-level OR: self |= other. Returns true if any new bits were set.
    fn insert_all(&mut self, other: &Self) -> bool {
        if other.data.len() > self.data.len() {
            self.data.resize(other.data.len(), 0);
        }
        if other.num_bits > self.num_bits {
            self.num_bits = other.num_bits;
        }
        let mut changed = false;
        for (sw, &ow) in self.data.iter_mut().zip(other.data.iter()) {
            let new_bits = ow & !*sw;
            if new_bits != 0 {
                *sw |= ow;
                changed = true;
            }
        }
        changed
    }
}

impl PartialEq for BitVec {
    fn eq(&self, other: &Self) -> bool {
        let max_len = self.data.len().max(other.data.len());
        for i in 0..max_len {
            if self.data.get(i).copied().unwrap_or(0) != other.data.get(i).copied().unwrap_or(0) {
                return false;
            }
        }
        true
    }
}

impl Eq for BitVec {}

impl Hash for BitVec {
    fn hash<H: Hasher>(&self, state: &mut H) {
        let effective_len = self
            .data
            .iter()
            .rposition(|&w| w != 0)
            .map_or(0, |i| i + 1);
        self.data[..effective_len].hash(state);
    }
}

impl Ord for BitVec {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        let max_len = self.data.len().max(other.data.len());
        for i in 0..max_len {
            let a = self.data.get(i).copied().unwrap_or(0);
            let b = other.data.get(i).copied().unwrap_or(0);
            if a != b {
                let first_diff = (a ^ b).trailing_zeros();
                return if (a >> first_diff) & 1 != 0 {
                    std::cmp::Ordering::Greater
                } else {
                    std::cmp::Ordering::Less
                };
            }
        }
        std::cmp::Ordering::Equal
    }
}

impl PartialOrd for BitVec {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl std::ops::Index<usize> for BitVec {
    type Output = bool;

    fn index(&self, index: usize) -> &Self::Output {
        static TRUE: bool = true;
        static FALSE: bool = false;
        if self.data[index / 64] >> (index % 64) & 1 != 0 {
            &TRUE
        } else {
            &FALSE
        }
    }
}

/// Iterator that yields only the indices of set bits, skipping zero words
/// entirely and using `trailing_zeros()` within each word.
struct SetBitsIter<'a> {
    data: &'a [u64],
    word_idx: usize,
    current_word: u64,
}

impl<'a> SetBitsIter<'a> {
    fn new(data: &'a [u64]) -> Self {
        Self {
            data,
            word_idx: 0,
            current_word: data.first().copied().unwrap_or(0),
        }
    }
}

impl Iterator for SetBitsIter<'_> {
    type Item = usize;

    fn next(&mut self) -> Option<usize> {
        while self.current_word == 0 {
            self.word_idx += 1;
            if self.word_idx >= self.data.len() {
                return None;
            }
            self.current_word = self.data[self.word_idx];
        }
        let bit = self.current_word.trailing_zeros() as usize;
        self.current_word &= self.current_word - 1; // clear lowest set bit
        Some(self.word_idx * 64 + bit)
    }
}

// Because tokens are represented as small (~400 max) unsigned integers,
// sets of tokens can be efficiently represented as bit vectors with each
// index corresponding to a token, and each value representing whether or not
// the token is present in the set.
#[derive(Default, Clone, PartialEq, Eq, Hash)]
pub struct TokenSet {
    terminal_bits: BitVec,
    external_bits: BitVec,
    eof: bool,
    end_of_nonterminal_extra: bool,
}

impl fmt::Debug for TokenSet {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_list().entries(self.iter()).finish()
    }
}

impl PartialOrd for TokenSet {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for TokenSet {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.terminal_bits
            .cmp(&other.terminal_bits)
            .then_with(|| self.external_bits.cmp(&other.external_bits))
            .then_with(|| self.eof.cmp(&other.eof))
            .then_with(|| {
                self.end_of_nonterminal_extra
                    .cmp(&other.end_of_nonterminal_extra)
            })
    }
}

impl Rule {
    pub fn field(name: String, content: Self) -> Self {
        add_metadata(content, move |params| {
            params.field_name = Some(name);
        })
    }

    pub fn alias(content: Self, value: String, is_named: bool) -> Self {
        add_metadata(content, move |params| {
            params.alias = Some(Alias { value, is_named });
        })
    }

    pub fn token(content: Self) -> Self {
        add_metadata(content, |params| {
            params.is_token = true;
        })
    }

    pub fn immediate_token(content: Self) -> Self {
        add_metadata(content, |params| {
            params.is_token = true;
            params.is_main_token = true;
        })
    }

    pub fn prec(value: Precedence, content: Self) -> Self {
        add_metadata(content, |params| {
            params.precedence = value;
        })
    }

    pub fn prec_left(value: Precedence, content: Self) -> Self {
        add_metadata(content, |params| {
            params.associativity = Some(Associativity::Left);
            params.precedence = value;
        })
    }

    pub fn prec_right(value: Precedence, content: Self) -> Self {
        add_metadata(content, |params| {
            params.associativity = Some(Associativity::Right);
            params.precedence = value;
        })
    }

    pub fn prec_dynamic(value: i32, content: Self) -> Self {
        add_metadata(content, |params| {
            params.dynamic_precedence = value;
        })
    }

    pub fn repeat(rule: Self) -> Self {
        Self::Repeat(Box::new(rule))
    }

    pub fn choice(rules: Vec<Self>) -> Self {
        let mut elements = Vec::with_capacity(rules.len());
        for rule in rules {
            choice_helper(&mut elements, rule);
        }
        Self::Choice(elements)
    }

    pub const fn seq(rules: Vec<Self>) -> Self {
        Self::Seq(rules)
    }

    pub fn is_empty(&self) -> bool {
        match self {
            Self::Blank | Self::Pattern(..) | Self::NamedSymbol(_) | Self::Symbol(_) => false,
            Self::String(string) => string.is_empty(),
            Self::Metadata { rule, .. } | Self::Repeat(rule) | Self::Reserved { rule, .. } => {
                rule.is_empty()
            }
            Self::Choice(rules) => rules.iter().any(Self::is_empty),
            Self::Seq(rules) => rules.iter().all(Self::is_empty),
        }
    }
}

impl Alias {
    #[must_use]
    pub const fn kind(&self) -> VariableType {
        if self.is_named {
            VariableType::Named
        } else {
            VariableType::Anonymous
        }
    }
}

impl Precedence {
    #[must_use]
    pub const fn is_none(&self) -> bool {
        matches!(self, Self::None)
    }
}

#[cfg(test)]
impl Rule {
    #[must_use]
    pub const fn terminal(index: usize) -> Self {
        Self::Symbol(Symbol::terminal(index))
    }

    #[must_use]
    pub const fn non_terminal(index: usize) -> Self {
        Self::Symbol(Symbol::non_terminal(index))
    }

    #[must_use]
    pub const fn external(index: usize) -> Self {
        Self::Symbol(Symbol::external(index))
    }

    #[must_use]
    pub fn named(name: &'static str) -> Self {
        Self::NamedSymbol(name.to_string())
    }

    #[must_use]
    pub fn string(value: &'static str) -> Self {
        Self::String(value.to_string())
    }

    #[must_use]
    pub fn pattern(value: &'static str, flags: &'static str) -> Self {
        Self::Pattern(value.to_string(), flags.to_string())
    }
}

impl Symbol {
    #[must_use]
    pub fn is_terminal(&self) -> bool {
        self.kind == SymbolType::Terminal
    }

    #[must_use]
    pub fn is_non_terminal(&self) -> bool {
        self.kind == SymbolType::NonTerminal
    }

    #[must_use]
    pub fn is_external(&self) -> bool {
        self.kind == SymbolType::External
    }

    #[must_use]
    pub fn is_eof(&self) -> bool {
        self.kind == SymbolType::End
    }

    #[must_use]
    pub const fn non_terminal(index: usize) -> Self {
        Self {
            kind: SymbolType::NonTerminal,
            index,
        }
    }

    #[must_use]
    pub const fn terminal(index: usize) -> Self {
        Self {
            kind: SymbolType::Terminal,
            index,
        }
    }

    #[must_use]
    pub const fn external(index: usize) -> Self {
        Self {
            kind: SymbolType::External,
            index,
        }
    }

    #[must_use]
    pub const fn end() -> Self {
        Self {
            kind: SymbolType::End,
            index: 0,
        }
    }

    #[must_use]
    pub const fn end_of_nonterminal_extra() -> Self {
        Self {
            kind: SymbolType::EndOfNonTerminalExtra,
            index: 0,
        }
    }
}

impl From<Symbol> for Rule {
    fn from(symbol: Symbol) -> Self {
        Self::Symbol(symbol)
    }
}

impl TokenSet {
    #[must_use]
    pub const fn new() -> Self {
        Self {
            terminal_bits: BitVec::new(),
            external_bits: BitVec::new(),
            eof: false,
            end_of_nonterminal_extra: false,
        }
    }

    pub fn with_capacity(n_terminals: usize, n_externals: usize) -> Self {
        Self {
            terminal_bits: BitVec::with_capacity(n_terminals),
            external_bits: BitVec::with_capacity(n_externals),
            eof: false,
            end_of_nonterminal_extra: false,
        }
    }

    pub fn iter(&self) -> impl Iterator<Item = Symbol> + '_ {
        SetBitsIter::new(&self.terminal_bits.data)
            .map(Symbol::terminal)
            .chain(SetBitsIter::new(&self.external_bits.data).map(Symbol::external))
            .chain(if self.eof { Some(Symbol::end()) } else { None })
            .chain(if self.end_of_nonterminal_extra {
                Some(Symbol::end_of_nonterminal_extra())
            } else {
                None
            })
    }

    pub fn terminals(&self) -> impl Iterator<Item = Symbol> + '_ {
        SetBitsIter::new(&self.terminal_bits.data).map(Symbol::terminal)
    }

    pub fn contains(&self, symbol: &Symbol) -> bool {
        match symbol.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => self.terminal_bits.get(symbol.index).unwrap_or(false),
            SymbolType::External => self.external_bits.get(symbol.index).unwrap_or(false),
            SymbolType::End => self.eof,
            SymbolType::EndOfNonTerminalExtra => self.end_of_nonterminal_extra,
        }
    }

    pub fn contains_terminal(&self, index: usize) -> bool {
        self.terminal_bits.get(index).unwrap_or(false)
    }

    pub fn insert(&mut self, other: Symbol) {
        let vec = match other.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => &mut self.terminal_bits,
            SymbolType::External => &mut self.external_bits,
            SymbolType::End => {
                self.eof = true;
                return;
            }
            SymbolType::EndOfNonTerminalExtra => {
                self.end_of_nonterminal_extra = true;
                return;
            }
        };
        if other.index >= vec.len() {
            vec.resize(other.index + 1, false);
        }
        vec.set(other.index, true);
    }

    pub fn remove(&mut self, other: &Symbol) -> bool {
        let vec = match other.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => &mut self.terminal_bits,
            SymbolType::External => &mut self.external_bits,
            SymbolType::End => {
                return if self.eof {
                    self.eof = false;
                    true
                } else {
                    false
                };
            }
            SymbolType::EndOfNonTerminalExtra => {
                return if self.end_of_nonterminal_extra {
                    self.end_of_nonterminal_extra = false;
                    true
                } else {
                    false
                };
            }
        };
        if other.index < vec.len() && vec[other.index] {
            vec.set(other.index, false);
            while vec.last() == Some(false) {
                vec.pop();
            }
            return true;
        }
        false
    }

    pub fn is_empty(&self) -> bool {
        !self.eof
            && !self.end_of_nonterminal_extra
            && self.terminal_bits.data.iter().all(|&w| w == 0)
            && self.external_bits.data.iter().all(|&w| w == 0)
    }

    pub fn len(&self) -> usize {
        usize::from(self.eof)
            + usize::from(self.end_of_nonterminal_extra)
            + self
                .terminal_bits
                .data
                .iter()
                .map(|w| w.count_ones() as usize)
                .sum::<usize>()
            + self
                .external_bits
                .data
                .iter()
                .map(|w| w.count_ones() as usize)
                .sum::<usize>()
    }

    pub fn insert_all_terminals(&mut self, other: &Self) -> bool {
        self.terminal_bits.insert_all(&other.terminal_bits)
    }

    fn insert_all_externals(&mut self, other: &Self) -> bool {
        self.external_bits.insert_all(&other.external_bits)
    }

    pub fn insert_all(&mut self, other: &Self) -> bool {
        let mut result = false;
        if other.eof {
            result |= !self.eof;
            self.eof = true;
        }
        if other.end_of_nonterminal_extra {
            result |= !self.end_of_nonterminal_extra;
            self.end_of_nonterminal_extra = true;
        }
        result |= self.insert_all_terminals(other);
        result |= self.insert_all_externals(other);
        result
    }
}

impl FromIterator<Symbol> for TokenSet {
    fn from_iter<T: IntoIterator<Item = Symbol>>(iter: T) -> Self {
        let mut result = Self::new();
        for symbol in iter {
            result.insert(symbol);
        }
        result
    }
}

fn add_metadata<T: FnOnce(&mut MetadataParams)>(input: Rule, f: T) -> Rule {
    match input {
        Rule::Metadata { rule, mut params } if !params.is_token => {
            f(&mut params);
            Rule::Metadata { rule, params }
        }
        _ => {
            let mut params = MetadataParams::default();
            f(&mut params);
            Rule::Metadata {
                rule: Box::new(input),
                params,
            }
        }
    }
}

fn choice_helper(result: &mut Vec<Rule>, rule: Rule) {
    match rule {
        Rule::Choice(elements) => {
            for element in elements {
                choice_helper(result, element);
            }
        }
        _ => {
            if !result.contains(&rule) {
                result.push(rule);
            }
        }
    }
}

impl fmt::Display for Precedence {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Integer(i) => write!(f, "{i}"),
            Self::Name(s) => write!(f, "'{s}'"),
            Self::None => write!(f, "none"),
        }
    }
}
