//! Flat, pool-indexed rule IR for the grammar backend.
//!
//! Nodes live in one append-only arena and reference children by index, so passes
//! are iterative pool walks with in-place rewrites.

use serde::{Deserialize, Serialize};

use crate::{
    bitvec::{BitVec, SetBitsIter},
    grammars::VariableType,
    strpool::{StrId, StrPool},
};

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize, Deserialize)]
pub enum SymbolType {
    External = 0,
    End = 1,
    EndOfNonTerminalExtra = 2,
    Terminal = 3,
    NonTerminal = 4,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize, Deserialize)]
pub enum Associativity {
    Left,
    Right,
}

#[derive(Clone, Copy, PartialEq, Eq, Hash, Debug, PartialOrd, Ord)]
pub struct Alias {
    pub value: StrId,
    pub is_named: bool,
}

impl Alias {
    #[must_use]
    pub const fn kind(self) -> VariableType {
        if self.is_named {
            VariableType::Named
        } else {
            VariableType::Anonymous
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash, Debug, Default)]
pub enum Precedence {
    #[default]
    None,
    Integer(i32),
    Name(StrId),
}

#[derive(Clone, Copy, PartialEq, Eq, Debug, Default)]
pub struct MetadataParams {
    pub precedence: Precedence,
    pub associativity: Option<Associativity>,
    pub dynamic_precedence: i32,
    pub alias: Option<Alias>,
    pub field: Option<StrId>,
    pub is_token: bool,
    pub is_main_token: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Serialize, Deserialize)]
pub struct Symbol {
    pub kind: SymbolType,
    pub index: u32,
}

impl Symbol {
    #[must_use]
    pub fn is_terminal(self) -> bool {
        self.kind == SymbolType::Terminal
    }

    #[must_use]
    pub fn is_non_terminal(self) -> bool {
        self.kind == SymbolType::NonTerminal
    }

    #[must_use]
    pub fn is_external(self) -> bool {
        self.kind == SymbolType::External
    }

    #[must_use]
    pub fn is_eof(self) -> bool {
        self.kind == SymbolType::End
    }

    #[must_use]
    pub const fn non_terminal(index: usize) -> Self {
        Self {
            kind: SymbolType::NonTerminal,
            index: index as u32,
        }
    }

    #[must_use]
    pub const fn terminal(index: usize) -> Self {
        Self {
            kind: SymbolType::Terminal,
            index: index as u32,
        }
    }

    #[must_use]
    pub const fn external(index: usize) -> Self {
        Self {
            kind: SymbolType::External,
            index: index as u32,
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

/// A pooled rule node.
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Rule {
    Blank,
    String(StrId),
    Pattern(StrId, StrId),
    NamedSymbol(StrId),
    Sym { kind: SymbolType, index: u32 },
    Seq(RuleIdRange),
    Choice(RuleIdRange),
    Repeat(RuleId),
    Eof,
    Metadata { params: ParamsId, rule: RuleId },
    Reserved { rule: RuleId, ctx: StrId },
}

const _: () = assert!(std::mem::size_of::<Rule>() <= 12);

impl From<Symbol> for Rule {
    fn from(value: Symbol) -> Self {
        Self::Sym {
            kind: value.kind,
            index: value.index,
        }
    }
}

impl Rule {
    pub const fn symbol(self) -> Option<Symbol> {
        match self {
            Self::Sym { kind, index } => Some(Symbol { kind, index }),
            _ => None,
        }
    }
}

/// The arena: nodes, their pooled children/params, and the string interner.
/// Storage is append-only, passes rewrite nodes in place and may orphan subtrees.
#[derive(Clone, Default)]
pub struct RulePool {
    nodes: Vec<Rule>,
    children: Vec<RuleId>,
    params: Vec<MetadataParams>,
    str_pool: StrPool,
    /// Reusable walk scratch for choice flattening
    scratch: Vec<RuleId>,
}

impl RulePool {
    #[must_use]
    pub fn node(&self, id: RuleId) -> Rule {
        self.nodes[id.index()]
    }

    pub fn set_node(&mut self, id: RuleId, node: Rule) {
        self.nodes[id.index()] = node;
    }

    pub fn push_node(&mut self, node: Rule) -> RuleId {
        let id = RuleId(self.nodes.len() as u32);
        self.nodes.push(node);
        id
    }

    #[must_use]
    pub fn child_slice(&self, range: RuleIdRange) -> &[RuleId] {
        &self.children[range.as_range()]
    }

    pub fn push_children(&mut self, ids: &[RuleId]) -> RuleIdRange {
        let start = self.children.len() as u32;
        self.children.extend_from_slice(ids);
        RuleIdRange {
            start,
            len: ids.len() as u32,
        }
    }

    #[must_use]
    pub fn params(&self, id: ParamsId) -> MetadataParams {
        self.params[id.0 as usize]
    }

    pub fn push_params(&mut self, params: MetadataParams) -> ParamsId {
        let id = ParamsId(self.params.len() as u32);
        self.params.push(params);
        id
    }

    pub fn set_params(&mut self, id: ParamsId, params: MetadataParams) {
        self.params[id.0 as usize] = params;
    }

    fn metadata_with(&mut self, content: RuleId, f: impl FnOnce(&mut MetadataParams)) -> RuleId {
        if let Rule::Metadata { params, .. } = self.node(content) {
            let mut p = self.params(params);
            if !p.is_token {
                f(&mut p);
                self.set_params(params, p);
                return content;
            }
        }
        let mut p = MetadataParams::default();
        f(&mut p);
        let params = self.push_params(p);
        self.push_node(Rule::Metadata {
            params,
            rule: content,
        })
    }

    pub fn blank(&mut self) -> RuleId {
        self.push_node(Rule::Blank)
    }

    pub fn string(&mut self, value: StrId) -> RuleId {
        self.push_node(Rule::String(value))
    }

    pub fn pattern(&mut self, value: StrId, flags: StrId) -> RuleId {
        self.push_node(Rule::Pattern(value, flags))
    }

    pub fn named_symbol(&mut self, name: StrId) -> RuleId {
        self.push_node(Rule::NamedSymbol(name))
    }

    pub fn field(&mut self, name: StrId, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| p.field = Some(name))
    }

    pub fn alias(&mut self, content: RuleId, value: StrId, is_named: bool) -> RuleId {
        self.metadata_with(content, |p| p.alias = Some(Alias { value, is_named }))
    }

    pub fn token(&mut self, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| p.is_token = true)
    }

    pub fn immediate_token(&mut self, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| {
            p.is_token = true;
            p.is_main_token = true;
        })
    }

    pub fn prec(&mut self, value: Precedence, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| p.precedence = value)
    }

    pub fn prec_left(&mut self, value: Precedence, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| {
            p.associativity = Some(Associativity::Left);
            p.precedence = value;
        })
    }

    pub fn prec_right(&mut self, value: Precedence, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| {
            p.associativity = Some(Associativity::Right);
            p.precedence = value;
        })
    }

    pub fn prec_dynamic(&mut self, value: i32, content: RuleId) -> RuleId {
        self.metadata_with(content, |p| p.dynamic_precedence = value)
    }

    pub fn repeat(&mut self, content: RuleId) -> RuleId {
        self.push_node(Rule::Repeat(content))
    }

    pub fn eof(&mut self) -> RuleId {
        self.push_node(Rule::Eof)
    }

    #[cfg_attr(not(test), expect(dead_code))]
    pub fn seq(&mut self, ids: &[RuleId]) -> RuleId {
        let range = self.push_children(ids);
        self.push_node(Rule::Seq(range))
    }

    pub fn try_seq<T, E>(
        &mut self,
        items: impl ExactSizeIterator<Item = T>,
        mut f: impl FnMut(&mut Self, T) -> Result<RuleId, E>,
    ) -> Result<RuleId, E> {
        let len = items.len();
        let start = self.children.len();
        self.children.resize(start + len, RuleId(0));
        for (i, item) in items.enumerate() {
            let id = f(self, item)?;
            self.children[start + i] = id;
        }

        let range = RuleIdRange {
            start: start as u32,
            len: len as u32,
        };
        Ok(self.push_node(Rule::Seq(range)))
    }

    /// Flatten nested choices and de-dup structurally, keeping a `Choice` node
    /// even for a single element
    pub fn choice(&mut self, ids: &[RuleId]) -> RuleId {
        // Elements build directly at the children tail. The walk only reads
        // existing nodes, so nothing else appends while the range grows
        let start = self.children.len();
        let mut stack = std::mem::take(&mut self.scratch);
        stack.extend(ids.iter().rev());
        while let Some(id) = stack.pop() {
            if let Rule::Choice(range) = self.node(id) {
                let base = stack.len();
                stack.extend_from_slice(self.child_slice(range));
                stack[base..].reverse();
            } else if !self.children[start..]
                .iter()
                .copied()
                .any(|e| self.subtree_eq(e, id))
            {
                self.children.push(id);
            }
        }
        self.scratch = stack;
        let range = RuleIdRange {
            start: start as u32,
            len: (self.children.len() - start) as u32,
        };
        self.push_node(Rule::Choice(range))
    }

    pub fn reserved(&mut self, content: RuleId, ctx: StrId) -> RuleId {
        self.push_node(Rule::Reserved { rule: content, ctx })
    }

    #[inline]
    #[must_use]
    pub fn intern(&mut self, s: &str) -> StrId {
        self.str_pool.intern(s)
    }

    #[inline]
    #[must_use]
    pub fn resolve(&self, id: StrId) -> &str {
        self.str_pool.resolve(id)
    }

    #[must_use]
    pub fn into_interner(self) -> StrPool {
        self.str_pool
    }

    #[must_use]
    pub fn subtree_hash(&self, root: RuleId) -> u64 {
        use std::hash::{Hash, Hasher};
        let mut hasher = rustc_hash::FxHasher::default();
        let mut stack = vec![root];
        while let Some(id) = stack.pop() {
            let node = self.node(id);
            std::mem::discriminant(&node).hash(&mut hasher);
            match node {
                Rule::Blank | Rule::Eof => {}
                Rule::String(s) | Rule::NamedSymbol(s) => s.hash(&mut hasher),
                Rule::Pattern(p, f) => {
                    p.hash(&mut hasher);
                    f.hash(&mut hasher);
                }
                Rule::Sym { kind, index } => {
                    (kind as u8).hash(&mut hasher);
                    index.hash(&mut hasher);
                }
                Rule::Seq(range) | Rule::Choice(range) => {
                    hasher.write_u32(range.len);
                    let base = stack.len();
                    stack.extend_from_slice(self.child_slice(range));
                    stack[base..].reverse();
                }
                Rule::Repeat(inner) => stack.push(inner),
                Rule::Metadata { params, rule } => {
                    let p = self.params(params);
                    (p.precedence, p.associativity, p.dynamic_precedence).hash(&mut hasher);
                    p.alias.map(|a| (a.value, a.is_named)).hash(&mut hasher);
                    (p.field, p.is_token, p.is_main_token).hash(&mut hasher);
                    stack.push(rule);
                }
                Rule::Reserved { rule, ctx } => {
                    ctx.hash(&mut hasher);
                    stack.push(rule);
                }
            }
        }
        hasher.finish()
    }

    pub fn subtree_eq(&self, a: RuleId, b: RuleId) -> bool {
        let mut stack = vec![(a, b)];
        while let Some((a, b)) = stack.pop() {
            match (self.node(a), self.node(b)) {
                (Rule::Blank, Rule::Blank) | (Rule::Eof, Rule::Eof) => {}
                (Rule::String(x), Rule::String(y))
                | (Rule::NamedSymbol(x), Rule::NamedSymbol(y)) => {
                    if x != y {
                        return false;
                    }
                }
                (Rule::Pattern(p1, f1), Rule::Pattern(p2, f2)) => {
                    if p1 != p2 || f1 != f2 {
                        return false;
                    }
                }
                (n1 @ Rule::Sym { .. }, n2 @ Rule::Sym { .. }) => {
                    if n1 != n2 {
                        return false;
                    }
                }
                (Rule::Seq(r1), Rule::Seq(r2)) | (Rule::Choice(r1), Rule::Choice(r2)) => {
                    if r1.len != r2.len {
                        return false;
                    }
                    stack.extend(
                        self.child_slice(r1)
                            .iter()
                            .copied()
                            .zip(self.child_slice(r2).iter().copied()),
                    );
                }
                (Rule::Repeat(i1), Rule::Repeat(i2)) => stack.push((i1, i2)),
                #[rustfmt::skip]
                (Rule::Metadata { params: p1, rule: r1 }, Rule::Metadata { params: p2, rule: r2 }) => {
                    if self.params(p1) != self.params(p2) {
                        return false;
                    }
                    stack.push((r1, r2));
                }
                (Rule::Reserved { rule: r1, ctx: c1 }, Rule::Reserved { rule: r2, ctx: c2 }) => {
                    if c1 != c2 {
                        return false;
                    }
                    stack.push((r1, r2));
                }
                _ => return false,
            }
        }
        true
    }

    /// Whether the subtree at `id` can only match the empty string.
    pub fn subtree_matches_empty_str(&self, id: RuleId) -> bool {
        match self.node(id) {
            Rule::String(sid) => self.resolve(sid).is_empty(),
            Rule::Metadata { rule, .. } | Rule::Repeat(rule) | Rule::Reserved { rule, .. } => {
                self.subtree_matches_empty_str(rule)
            }
            Rule::Choice(range) => self
                .child_slice(range)
                .iter()
                .any(|&c| self.subtree_matches_empty_str(c)),
            Rule::Seq(range) => self
                .child_slice(range)
                .iter()
                .all(|&c| self.subtree_matches_empty_str(c)),
            _ => false,
        }
    }

    /// Check if a rule is referenced by another rule.
    ///
    /// This function is used to determine if a variable is used in a given rule,
    /// and `is_external` indicates if the rule is an external, and if it is,
    /// to not assume that a named symbol that is equal to itself means it's being referenced.
    ///
    /// For example, if we have an external rule **and** a normal rule both called `foo`,
    /// `foo` should not be thought of as directly used unless it's used within another rule.
    pub fn rule_is_referenced(&self, id: RuleId, target: StrId, is_external: bool) -> bool {
        match self.node(id) {
            Rule::NamedSymbol(name) => name == target && !is_external,
            Rule::Choice(range) | Rule::Seq(range) => self
                .child_slice(range)
                .iter()
                .any(|&c| self.rule_is_referenced(c, target, false)),
            Rule::Metadata { rule, .. } | Rule::Reserved { rule, .. } => {
                self.rule_is_referenced(rule, target, is_external)
            }
            Rule::Repeat(inner) => self.rule_is_referenced(inner, target, false),
            Rule::Blank | Rule::Eof | Rule::String(_) | Rule::Pattern(..) | Rule::Sym { .. } => {
                false
            }
        }
    }

    /// Append every `NamedSymbol` name reachable in `id` to `out`. If
    /// `skip_top_level` is true, a `NamedSymbol` at the root of `id` is
    /// ignored (used for externals entries, which name themselves).
    pub fn collect_referenced_ids(&self, id: RuleId, skip_top_level: bool, out: &mut Vec<StrId>) {
        match self.node(id) {
            Rule::NamedSymbol(name) => {
                if !skip_top_level {
                    out.push(name);
                }
            }
            Rule::Choice(range) | Rule::Seq(range) => {
                for &c in self.child_slice(range) {
                    self.collect_referenced_ids(c, false, out);
                }
            }
            Rule::Metadata { rule, .. } | Rule::Reserved { rule, .. } => {
                self.collect_referenced_ids(rule, skip_top_level, out);
            }
            Rule::Repeat(inner) => self.collect_referenced_ids(inner, false, out),
            Rule::Blank | Rule::Eof | Rule::String(_) | Rule::Pattern(..) | Rule::Sym { .. } => {}
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct RuleId(u32);

impl RuleId {
    #[must_use]
    pub const fn index(self) -> usize {
        self.0 as usize
    }
}

/// Index into [`RulePool::params`].
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct ParamsId(u32);

/// A `[start, start + len)` slice of [`RulePool::children`].
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct RuleIdRange {
    pub start: u32,
    pub len: u32,
}

impl RuleIdRange {
    #[must_use]
    pub const fn as_range(self) -> std::ops::Range<usize> {
        self.start as usize..(self.start + self.len) as usize
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

impl std::fmt::Debug for TokenSet {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
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

    #[must_use]
    pub fn with_capacity(n_terminals: usize, n_externals: usize) -> Self {
        Self {
            terminal_bits: BitVec::with_capacity(n_terminals),
            external_bits: BitVec::with_capacity(n_externals),
            eof: false,
            end_of_nonterminal_extra: false,
        }
    }

    pub fn iter(&self) -> impl Iterator<Item = Symbol> + '_ {
        SetBitsIter::new(self.terminal_bits.as_slice())
            .map(Symbol::terminal)
            .chain(SetBitsIter::new(self.external_bits.as_slice()).map(Symbol::external))
            .chain(if self.eof { Some(Symbol::end()) } else { None })
            .chain(if self.end_of_nonterminal_extra {
                Some(Symbol::end_of_nonterminal_extra())
            } else {
                None
            })
    }

    pub fn terminals(&self) -> impl Iterator<Item = Symbol> + '_ {
        SetBitsIter::new(self.terminal_bits.as_slice()).map(Symbol::terminal)
    }

    #[inline]
    #[must_use]
    pub fn contains(&self, symbol: Symbol) -> bool {
        match symbol.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => self
                .terminal_bits
                .get(symbol.index as usize)
                .unwrap_or(false),
            SymbolType::External => self
                .external_bits
                .get(symbol.index as usize)
                .unwrap_or(false),
            SymbolType::End => self.eof,
            SymbolType::EndOfNonTerminalExtra => self.end_of_nonterminal_extra,
        }
    }

    #[inline]
    #[must_use]
    pub fn contains_terminal(&self, index: usize) -> bool {
        self.terminal_bits.get(index).unwrap_or(false)
    }

    /// Raw u64 word slice backing the terminal bitset.
    #[inline]
    #[must_use]
    pub const fn terminal_bits_words(&self) -> &[u64] {
        self.terminal_bits.as_slice()
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
        let other_index = other.index as usize;
        if other_index >= vec.len() {
            vec.resize(other_index + 1, false);
        }
        vec.set(other_index, true);
    }

    pub fn remove(&mut self, other: Symbol) -> bool {
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
        let other_index = other.index as usize;
        if other_index < vec.len() && vec[other_index] {
            vec.set(other_index, false);
            while vec.last() == Some(false) {
                vec.pop();
            }
            return true;
        }
        false
    }

    #[must_use]
    pub fn is_empty(&self) -> bool {
        !self.eof
            && !self.end_of_nonterminal_extra
            && self.terminal_bits.as_slice().iter().all(|&w| w == 0)
            && self.external_bits.as_slice().iter().all(|&w| w == 0)
    }

    #[must_use]
    pub fn len(&self) -> usize {
        usize::from(self.eof)
            + usize::from(self.end_of_nonterminal_extra)
            + self
                .terminal_bits
                .as_slice()
                .iter()
                .map(|w| w.count_ones() as usize)
                .sum::<usize>()
            + self
                .external_bits
                .as_slice()
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

pub type AliasMap = std::collections::BTreeMap<Symbol, Alias>;
