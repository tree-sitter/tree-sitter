use std::{
    cmp::Ordering,
    fmt,
    hash::{BuildHasherDefault, Hash, Hasher},
};

use indexmap::IndexSet;
use rustc_hash::{FxHashMap, FxHasher};

use crate::{
    grammars::{LexicalGrammar, ProdRef, ProductionStep, ReservedWordSetId, SyntaxGrammar},
    rules::{Associativity, Precedence, Symbol, SymbolType, TokenSet},
    strpool::StrPool,
};

const START_STEPS: [ProductionStep; 1] = [ProductionStep {
    sym_index: 0,
    prec_val: 0,
    alias: 0,
    field: 0,
    reserved: ProductionStep::NO_RESERVED_WORDS,
    flags: SymbolType::NonTerminal as u8,
}];

pub const START_PRODUCTION_ID: u32 = u32::MAX;

const fn start_production() -> ProdRef<'static> {
    ProdRef {
        steps: &START_STEPS,
        dynamic_precedence: 0,
        requires_eof_lookahead: false,
    }
}

/// Precomputed identity keys for one `(production, dot)` pair.
///
/// `cmp` is the rank of the content tuple `Ord` compared (dynamic precedence,
/// `requires_eof_lookahead`, length, precedence/associativity at the dot, then
/// completed steps' aliases and fields and remaining steps in full). Equal ranks
/// hold _exactly_ when the tuple is equal, so it doubles as the equality class
/// for items without preceding inherited fields. `eq_with_syms` subdivides `cmp`
/// by the completed steps' symbols, which participate in equality only when
/// `has_preceding_inherited_fields` is set.
#[derive(Clone, Copy, Default, PartialEq, Eq, Debug)]
pub struct DotKeys {
    pub cmp: u32,
    pub eq_with_syms: u32,
}

/// Identity keys for every `(production, dot)` in a grammar (all grammar productions,
/// every inlined production, and the augmented start production).
pub struct ItemKeyMap {
    keys: Vec<Box<[DotKeys]>>,
    start: Box<[DotKeys]>,
}

impl ItemKeyMap {
    pub fn new(grammar: &SyntaxGrammar, str_pool: &StrPool) -> Self {
        let prod = |slot: usize| -> ProdRef {
            if slot == 0 {
                start_production()
            } else {
                grammar.production(slot as u32 - 1)
            }
        };
        let slot_count = grammar.productions.len() + 1;

        let mut contents: Vec<(u32, u32)> = Vec::with_capacity(slot_count);
        for pi in 0..slot_count {
            for dot in 0..=prod(pi).steps.len() {
                contents.push((pi as u32, dot as u32));
            }
        }
        let content = |&(pi, dot): &(u32, u32)| ItemContent {
            production: prod(pi as usize),
            dot: dot as usize,
            str_pool,
        };
        contents.sort_unstable_by(|a, b| content(a).cmp(&content(b)));

        let mut slot_keys: Vec<Box<[DotKeys]>> = (0..slot_count)
            .map(|pi| vec![DotKeys::default(); prod(pi).steps.len() + 1].into_boxed_slice())
            .collect::<Vec<_>>();
        // Dense ids in sorted order: equal content shares an id, distinct content gets the next up
        let mut cmp_id = 0;
        let mut prev = None;
        for &(pi, dot) in &contents {
            if let Some(p) = prev
                && content(&p) != content(&(pi, dot))
            {
                cmp_id += 1;
            }
            slot_keys[pi as usize][dot as usize].cmp = cmp_id;
            prev = Some((pi, dot));
        }

        // Refine each cmp class by preceding symbols:  read only under
        // `has_preceding_inherited_fields`.
        let mut sym_classes = FxHashMap::default();
        for &(pi, dot) in &contents {
            let syms = prod(pi as usize).steps[..dot as usize]
                .iter()
                .map(|s| s.symbol())
                .collect::<Vec<_>>();
            let next = sym_classes.len() as u32;
            let keys = &mut slot_keys[pi as usize][dot as usize];
            keys.eq_with_syms = *sym_classes.entry((keys.cmp, syms)).or_insert(next);
        }

        let start = slot_keys.remove(0);
        Self {
            keys: slot_keys,
            start,
        }
    }

    /// The keys slice (indexed by `dot`) for a production of this grammar.
    pub fn keys_for(&self, id: u32) -> &[DotKeys] {
        if id == START_PRODUCTION_ID {
            &self.start
        } else {
            &self.keys[id as usize]
        }
    }

    pub fn start_keys(&self) -> &[DotKeys] {
        &self.start
    }
}

/// The content tuple that `ParseItem`'s `Ord` (and flagless `Eq`) observe, evaluated on
/// `(production, dot)` directly. Ranking the set of all keys by this order makes
/// the dense `cmp` order-preserving. Item ordering only ever compares same-dot pairs,
/// and the dot comparison keeps the order total across dots so ranks are well defined.
struct ItemContent<'a> {
    production: ProdRef<'a>,
    dot: usize,
    str_pool: &'a StrPool,
}

impl Eq for ItemContent<'_> {}

impl ItemContent<'_> {
    const fn prec(&self) -> Precedence {
        if self.dot > 0 {
            self.production.steps[self.dot - 1].precedence()
        } else {
            Precedence::None
        }
    }

    const fn assoc(&self) -> Option<Associativity> {
        if self.dot > 0 {
            self.production.steps[self.dot - 1].associativity()
        } else {
            None
        }
    }

    fn prec_cmp(&self, a: Precedence, b: Precedence) -> Ordering {
        match (a, b) {
            (Precedence::None, Precedence::None) => Ordering::Equal,
            (Precedence::Integer(a), Precedence::Integer(b)) => a.cmp(&b),
            (Precedence::Name(a), Precedence::Name(b)) => {
                self.str_pool.resolve(a).cmp(self.str_pool.resolve(b))
            }
            (Precedence::None, _) | (Precedence::Integer(_), Precedence::Name(_)) => Ordering::Less,
            (_, Precedence::None) | (Precedence::Name(_), Precedence::Integer(_)) => {
                Ordering::Greater
            }
        }
    }

    fn alias_cmp(&self, a: ProductionStep, b: ProductionStep) -> Ordering {
        let key = |step: ProductionStep| {
            step.alias()
                .map(|alias| (self.str_pool.resolve(alias.value), alias.is_named))
        };
        key(a).cmp(&key(b))
    }

    fn field_cmp(&self, a: ProductionStep, b: ProductionStep) -> Ordering {
        let key = |step: ProductionStep| step.field().map(|field| self.str_pool.resolve(field));
        key(a).cmp(&key(b))
    }

    fn step_cmp(&self, a: ProductionStep, b: ProductionStep) -> Ordering {
        a.symbol()
            .cmp(&b.symbol())
            .then_with(|| self.prec_cmp(a.precedence(), b.precedence()))
            .then_with(|| a.associativity().cmp(&b.associativity()))
            .then_with(|| self.alias_cmp(a, b))
            .then_with(|| self.field_cmp(a, b))
            .then_with(|| a.reserved.cmp(&b.reserved))
    }
}

impl Ord for ItemContent<'_> {
    fn cmp(&self, other: &Self) -> Ordering {
        self.production
            .dynamic_precedence
            .cmp(&other.production.dynamic_precedence)
            .then_with(|| {
                self.production
                    .requires_eof_lookahead
                    .cmp(&other.production.requires_eof_lookahead)
            })
            .then_with(|| {
                self.production
                    .steps
                    .len()
                    .cmp(&other.production.steps.len())
            })
            .then_with(|| self.prec_cmp(self.prec(), other.prec()))
            .then_with(|| self.assoc().cmp(&other.assoc()))
            .then_with(|| self.dot.cmp(&other.dot))
            .then_with(|| {
                let steps = self.production.steps.iter().zip(other.production.steps);
                for (i, (&sa, &sb)) in steps.enumerate() {
                    let o = if i < self.dot {
                        self.alias_cmp(sa, sb).then_with(|| self.field_cmp(sa, sb))
                    } else {
                        self.step_cmp(sa, sb)
                    };
                    if o != Ordering::Equal {
                        return o;
                    }
                }
                Ordering::Equal
            })
    }
}

impl PartialOrd for ItemContent<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for ItemContent<'_> {
    fn eq(&self, other: &Self) -> bool {
        self.cmp(other) == Ordering::Equal
    }
}

/// A [`ParseItem`] represents an in-progress match of a single production in a grammar.
#[derive(Clone, Copy, Debug)]
pub struct ParseItem<'a> {
    /// The index of the parent rule within the grammar.
    pub variable_index: u32,
    /// The number of symbols that have already been matched.
    pub step_index: u32,
    /// The id of the production being matched.
    pub prod_id: u32,
    /// The `production`'s identity keys, indexed by `step_index`.
    pub keys: &'a [DotKeys],
    /// A boolean indicating whether any of the already-matched children were
    /// hidden nodes and had fields. Ordinarily, a parse item's behavior is not
    /// affected by the symbols of its preceding children; it only needs to
    /// keep track of their fields and aliases.
    ///
    /// Take for example these two items:
    ///   X -> a b • c
    ///   X -> a g • c
    ///
    /// They can be considered equivalent, for the purposes of parse table
    /// generation, because they entail the same actions. But if this flag is
    /// true, then the item's set of inherited fields may depend on the specific
    /// symbols of its preceding children.
    pub has_preceding_inherited_fields: bool,
}

/// Interned lookahead set. An index into a [`LookaheadPool`]. Ids are canonical,
/// so id equality is equivalent to underlying [`TokenSet`] equality.
#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct LookaheadSetId(u32);

impl Default for LookaheadSetId {
    fn default() -> Self {
        LookaheadSetPool::EMPTY
    }
}

/// Interner for lookahead [`TokenSet`]s. Item-set entries store ids.
pub struct LookaheadSetPool {
    sets: IndexSet<TokenSet, BuildHasherDefault<FxHasher>>,
    union_memo: FxHashMap<(LookaheadSetId, LookaheadSetId), LookaheadSetId>,
    insert_memo: FxHashMap<(LookaheadSetId, Symbol), LookaheadSetId>,
}

impl LookaheadSetPool {
    pub const EMPTY: LookaheadSetId = LookaheadSetId(0);

    #[must_use]
    pub fn new() -> Self {
        let mut pool = Self {
            sets: IndexSet::default(),
            union_memo: FxHashMap::default(),
            insert_memo: FxHashMap::default(),
        };
        let empty = pool.intern(TokenSet::new());
        debug_assert_eq!(empty, Self::EMPTY);
        pool
    }

    #[must_use]
    pub fn get(&self, id: LookaheadSetId) -> &TokenSet {
        &self.sets[id.0 as usize]
    }

    pub fn intern(&mut self, set: TokenSet) -> LookaheadSetId {
        let (index, _) = self.sets.insert_full(set);
        LookaheadSetId(index as u32)
    }

    pub fn intern_ref(&mut self, set: &TokenSet) -> LookaheadSetId {
        if let Some(index) = self.sets.get_index_of(set) {
            return LookaheadSetId(index as u32);
        }
        self.intern(set.clone())
    }

    pub fn singleton(&mut self, symbol: Symbol) -> LookaheadSetId {
        self.insert(Self::EMPTY, symbol)
    }

    pub fn insert(&mut self, id: LookaheadSetId, symbol: Symbol) -> LookaheadSetId {
        if self.get(id).contains(symbol) {
            return id;
        }
        if let Some(&result) = self.insert_memo.get(&(id, symbol)) {
            return result;
        }
        let mut set = self.get(id).clone();
        set.insert(symbol);
        let result = self.intern(set);
        self.insert_memo.insert((id, symbol), result);
        result
    }

    pub fn union(&mut self, left: LookaheadSetId, right: LookaheadSetId) -> LookaheadSetId {
        if left == right || right == Self::EMPTY {
            return left;
        }
        if left == Self::EMPTY {
            return right;
        }
        let key = (left.min(right), left.max(right));
        if let Some(&result) = self.union_memo.get(&key) {
            return result;
        }
        let mut set = self.get(key.0).clone();
        set.insert_all(self.get(key.1));
        let result = self.intern(set);
        self.union_memo.insert(key, result);
        result
    }
}

/// Represents a set of in-progress matches of productions in a grammar.
///
/// For each in-progress match, a set of "lookaheads" (tokens that are allowed to
/// *follow* the in-progress rule) are included. This object corresponds directly
/// to a state in the final parse table.
#[derive(Clone, Debug, PartialEq, Eq, Default)]
pub struct ParseItemSet<'a> {
    pub entries: Vec<ParseItemSetEntry<'a>>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ParseItemSetEntry<'a> {
    pub item: ParseItem<'a>,
    pub lookaheads: LookaheadSetId,
    pub following_reserved_word_set: ReservedWordSetId,
}

/// A [`ParseItemSetCore`] is like a [`ParseItemSet`], but without the lookahead
/// information. Parse states with the same core are candidates for merging.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ParseItemSetCore<'a> {
    pub entries: Vec<ParseItem<'a>>,
}

pub struct ParseItemDisplay<'a>(
    pub &'a ParseItem<'a>,
    pub &'a SyntaxGrammar,
    pub &'a LexicalGrammar,
    pub &'a StrPool,
);

pub struct TokenSetDisplay<'a>(
    pub &'a TokenSet,
    pub &'a SyntaxGrammar,
    pub &'a LexicalGrammar,
    pub &'a StrPool,
);

pub struct ParseItemSetDisplay<'a>(
    pub &'a ParseItemSet<'a>,
    pub &'a SyntaxGrammar,
    pub &'a LexicalGrammar,
    pub &'a StrPool,
    pub &'a LookaheadSetPool,
);

impl<'a> ParseItem<'a> {
    #[must_use]
    pub fn start(key_map: &'a ItemKeyMap) -> Self {
        ParseItem {
            variable_index: u32::MAX,
            prod_id: START_PRODUCTION_ID,
            keys: key_map.start_keys(),
            step_index: 0,
            has_preceding_inherited_fields: false,
        }
    }

    /// The production being matched.
    #[must_use]
    pub fn production<'g>(&self, grammar: &'g SyntaxGrammar) -> ProdRef<'g> {
        if self.prod_id == START_PRODUCTION_ID {
            start_production()
        } else {
            grammar.production(self.prod_id)
        }
    }

    #[must_use]
    pub fn step(&self, grammar: &SyntaxGrammar) -> Option<ProductionStep> {
        self.production(grammar)
            .steps
            .get(self.step_index as usize)
            .copied()
    }

    #[must_use]
    pub fn symbol(&self, grammar: &SyntaxGrammar) -> Option<Symbol> {
        self.step(grammar).map(ProductionStep::symbol)
    }

    #[must_use]
    pub fn associativity(&self, grammar: &SyntaxGrammar) -> Option<Associativity> {
        self.prev_step(grammar)
            .and_then(ProductionStep::associativity)
    }

    #[must_use]
    pub fn precedence(&self, grammar: &SyntaxGrammar) -> Precedence {
        self.prev_step(grammar)
            .map_or(Precedence::None, ProductionStep::precedence)
    }

    #[must_use]
    pub fn prev_step(&self, grammar: &SyntaxGrammar) -> Option<ProductionStep> {
        if self.step_index > 0 {
            Some(self.production(grammar).steps[self.step_index as usize - 1])
        } else {
            None
        }
    }

    #[must_use]
    pub const fn is_done(&self) -> bool {
        self.step_index as usize + 1 == self.keys.len()
    }

    #[must_use]
    pub const fn is_augmented(&self) -> bool {
        self.variable_index == u32::MAX
    }

    /// Create an item like this one, but advanced by one step.
    #[must_use]
    pub const fn successor(&self) -> Self {
        ParseItem {
            variable_index: self.variable_index,
            prod_id: self.prod_id,
            keys: self.keys,
            step_index: self.step_index + 1,
            has_preceding_inherited_fields: self.has_preceding_inherited_fields,
        }
    }

    /// Create an item identical to this one, but with a different production.
    /// This is used when dynamically "inlining" certain symbols in a production.
    #[must_use]
    pub const fn substitute_production(&self, prod_id: u32, keys: &'a [DotKeys]) -> Self {
        let mut result = *self;
        result.prod_id = prod_id;
        result.keys = keys;
        result
    }

    /// This item's identity keys at the current dot.
    #[must_use]
    const fn dot_keys(&self) -> DotKeys {
        self.keys[self.step_index as usize]
    }
}

impl<'a> ParseItemSet<'a> {
    #[inline]
    pub fn insert(&mut self, item: ParseItem<'a>) -> &mut ParseItemSetEntry<'a> {
        match self.entries.binary_search_by(|e| e.item.cmp(&item)) {
            Err(i) => {
                self.entries.insert(
                    i,
                    ParseItemSetEntry {
                        item,
                        lookaheads: LookaheadSetPool::EMPTY,
                        following_reserved_word_set: ReservedWordSetId::default(),
                    },
                );
                &mut self.entries[i]
            }
            Ok(i) => &mut self.entries[i],
        }
    }

    #[must_use]
    pub fn core(&self) -> ParseItemSetCore<'a> {
        ParseItemSetCore {
            entries: self.entries.iter().map(|e| e.item).collect(),
        }
    }
}

pub fn prec_display(prec: Precedence, str_pool: &StrPool) -> String {
    match prec {
        Precedence::None => "none".to_string(),
        Precedence::Integer(i) => i.to_string(),
        Precedence::Name(sid) => format!("'{}'", str_pool.resolve(sid)),
    }
}

impl fmt::Display for ParseItemDisplay<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        if self.0.is_augmented() {
            write!(f, "START →")?;
        } else {
            write!(
                f,
                "{} →",
                self.3
                    .resolve(self.1.variables[self.0.variable_index as usize].name)
            )?;
        }

        let production = self.0.production(self.1);
        for (i, step) in production.steps.iter().enumerate() {
            let symbol = step.symbol();
            if i == self.0.step_index as usize {
                write!(f, " •")?;
                if step.precedence() != Precedence::None
                    || step.associativity().is_some()
                    || step.reserved != 0
                {
                    write!(f, " (")?;
                    if step.precedence() != Precedence::None {
                        write!(f, " {}", prec_display(step.precedence(), self.3))?;
                    }
                    if let Some(associativity) = step.associativity() {
                        write!(f, " {associativity:?}")?;
                    }
                    if step.reserved != 0 {
                        write!(f, "reserved: {}", step.reserved)?;
                    }
                    write!(f, " )")?;
                }
            }

            write!(f, " ")?;
            if symbol.is_terminal() {
                if let Some(variable) = self.2.variables.get(symbol.index as usize) {
                    write!(f, "{}", self.3.resolve(variable.name))?;
                } else {
                    write!(f, "terminal-{}", symbol.index)?;
                }
            } else if symbol.is_external() {
                write!(
                    f,
                    "{}",
                    self.3
                        .resolve(self.1.external_tokens[symbol.index as usize].name)
                )?;
            } else {
                write!(
                    f,
                    "{}",
                    self.3.resolve(self.1.variables[symbol.index as usize].name)
                )?;
            }

            if let Some(alias) = &step.alias() {
                write!(f, "@{}", self.3.resolve(alias.value))?;
            }
        }

        if self.0.is_done() {
            write!(f, " •")?;
            if let Some(&step) = production.steps.last() {
                if let Some(associativity) = step.associativity() {
                    if step.precedence() == Precedence::None {
                        write!(f, " ({associativity:?})")?;
                    } else {
                        write!(
                            f,
                            " ({} {associativity:?})",
                            prec_display(step.precedence(), self.3)
                        )?;
                    }
                } else if step.precedence() != Precedence::None {
                    write!(f, " ({})", prec_display(step.precedence(), self.3))?;
                }
            }
        }

        Ok(())
    }
}

const fn escape_invisible(c: char) -> Option<&'static str> {
    Some(match c {
        '\n' => "\\n",
        '\r' => "\\r",
        '\t' => "\\t",
        '\0' => "\\0",
        '\\' => "\\\\",
        '\x0b' => "\\v",
        '\x0c' => "\\f",
        _ => return None,
    })
}

fn display_variable_name(source: &str) -> String {
    source
        .chars()
        .fold(String::with_capacity(source.len()), |mut acc, c| {
            if let Some(esc) = escape_invisible(c) {
                acc.push_str(esc);
            } else {
                acc.push(c);
            }
            acc
        })
}

impl fmt::Display for TokenSetDisplay<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "[")?;
        for (i, symbol) in self.0.iter().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }

            if symbol.is_terminal() {
                if let Some(variable) = self.2.variables.get(symbol.index as usize) {
                    write!(
                        f,
                        "{}",
                        display_variable_name(self.3.resolve(variable.name))
                    )?;
                } else {
                    write!(f, "terminal-{}", symbol.index)?;
                }
            } else if symbol.is_external() {
                write!(
                    f,
                    "{}",
                    self.3
                        .resolve(self.1.external_tokens[symbol.index as usize].name)
                )?;
            } else {
                write!(
                    f,
                    "{}",
                    self.3.resolve(self.1.variables[symbol.index as usize].name)
                )?;
            }
        }
        write!(f, "]")?;
        Ok(())
    }
}

impl fmt::Display for ParseItemSetDisplay<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        for entry in &self.0.entries {
            write!(
                f,
                "{}\t{}",
                ParseItemDisplay(&entry.item, self.1, self.2, self.3),
                TokenSetDisplay(self.4.get(entry.lookaheads), self.1, self.2, self.3),
            )?;
            if entry.following_reserved_word_set != ReservedWordSetId::default() {
                write!(
                    f,
                    "\treserved word set: {}",
                    entry.following_reserved_word_set
                )?;
            }
            writeln!(f)?;
        }
        Ok(())
    }
}

impl Hash for ParseItem<'_> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_u32(self.variable_index);
        hasher.write_u32(self.step_index);

        // The already-matched children don't play any role in the parse state for
        // this item, unless any of the following are true:
        //   * the children have fields
        //   * the children have aliases
        //   * the children are hidden and represent rules that have fields.
        // See the docs for `has_preceding_inherited_fields`.
        // Preceding symbols participate only in `eq_with_syms`.
        let keys = self.dot_keys();
        if self.has_preceding_inherited_fields {
            hasher.write_u8(1);
            hasher.write_u32(keys.eq_with_syms);
        } else {
            hasher.write_u8(0);
            hasher.write_u32(keys.cmp);
        }
    }
}

impl PartialEq for ParseItem<'_> {
    #[inline]
    fn eq(&self, other: &Self) -> bool {
        if self.variable_index != other.variable_index
            || self.step_index != other.step_index
            || self.has_preceding_inherited_fields != other.has_preceding_inherited_fields
        {
            return false;
        }

        if self.has_preceding_inherited_fields {
            self.dot_keys().eq_with_syms == other.dot_keys().eq_with_syms
        } else {
            self.dot_keys().cmp == other.dot_keys().cmp
        }
    }
}

impl Ord for ParseItem<'_> {
    #[inline]
    fn cmp(&self, other: &Self) -> Ordering {
        self.step_index
            .cmp(&other.step_index)
            .then_with(|| self.variable_index.cmp(&other.variable_index))
            .then_with(|| self.dot_keys().cmp.cmp(&other.dot_keys().cmp))
            .then_with(|| {
                self.has_preceding_inherited_fields
                    .cmp(&other.has_preceding_inherited_fields)
            })
            .then_with(|| {
                if self.has_preceding_inherited_fields {
                    self.dot_keys()
                        .eq_with_syms
                        .cmp(&other.dot_keys().eq_with_syms)
                } else {
                    Ordering::Equal
                }
            })
    }
}

impl PartialOrd for ParseItem<'_> {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Eq for ParseItem<'_> {}

impl Hash for ParseItemSet<'_> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_usize(self.entries.len());
        for entry in &self.entries {
            entry.item.hash(hasher);
            entry.lookaheads.hash(hasher);
            entry.following_reserved_word_set.hash(hasher);
        }
    }
}

impl Hash for ParseItemSetCore<'_> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_usize(self.entries.len());
        for item in &self.entries {
            item.hash(hasher);
        }
    }
}
