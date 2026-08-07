use std::{
    cmp::Ordering,
    fmt,
    hash::{Hash, Hasher},
    sync::LazyLock,
};

use rustc_hash::FxHashMap;

use crate::{
    grammars::{
        InlinedProductionMap, LexicalGrammar, NO_RESERVED_WORDS, Production, ProductionStep,
        ReservedWordSetId, SyntaxGrammar,
    },
    rules::{Associativity, Precedence, Symbol, SymbolType, TokenSet},
};

static START_PRODUCTION: LazyLock<Production> = LazyLock::new(|| Production {
    dynamic_precedence: 0,
    steps: vec![ProductionStep {
        symbol: Symbol {
            index: 0,
            kind: SymbolType::NonTerminal,
        },
        precedence: Precedence::None,
        associativity: None,
        alias: None,
        field_name: None,
        reserved_word_set_id: NO_RESERVED_WORDS,
    }],
});

/// Precomputed identity keys for one `(production, dot)` pair.
///
/// `cmp` is the rank of the content tuple `Ord` compared (dynamic precedence,
/// length, precedence/associativity at the dot, then completed steps' aliases and fields
/// and remaining steps in full). Equal ranks hold _exactly_ when the tuple is equal,
/// so it doubles as the equality class for items without preceding inherited fields.
/// `eq_with_syms` subdivides `cmp` by the completed steps' symbols, which participate
/// in equality only when `has_preceding_inherited_fields` is set.
#[derive(Clone, Copy, Default, PartialEq, Eq, Debug)]
pub struct DotKeys {
    pub cmp: u32,
    pub eq_with_syms: u32,
}

/// Identity keys for every `(production, dot)` in a grammar (all grammar productions,
/// every inlined production, and the augmented start production).
pub struct ItemKeyMap {
    keys: FxHashMap<*const Production, Box<[DotKeys]>>,
    start: Box<[DotKeys]>,
}

impl ItemKeyMap {
    pub fn new(grammar: &SyntaxGrammar, inlines: &InlinedProductionMap) -> Self {
        let mut prods = Vec::<&Production>::with_capacity(
            1 + grammar.variables.len() + inlines.productions.len(),
        );
        prods.push(&START_PRODUCTION);
        for var in &grammar.variables {
            prods.extend(var.productions.iter());
        }
        prods.extend(inlines.productions.iter());

        let mut contents: Vec<(u32, u32)> = Vec::with_capacity(prods.len());
        for (pi, p) in prods.iter().enumerate() {
            for dot in 0..=p.steps.len() {
                contents.push((pi as u32, dot as u32));
            }
        }
        let content = |&(pi, dot): &(u32, u32)| ItemContent {
            production: prods[pi as usize],
            dot: dot as usize,
        };
        contents.sort_unstable_by(|a, b| content(a).cmp(&content(b)));

        let mut slot_keys: Vec<Box<[DotKeys]>> = prods
            .iter()
            .map(|p| vec![DotKeys::default(); p.steps.len() + 1].into_boxed_slice())
            .collect();
        // Dense ids in sorted order: equal content shares an id, distinct content gets the next up
        let mut cmp_id = 0u32;
        let mut prev: Option<(u32, u32)> = None;
        for &(pi, dot) in &contents {
            if let Some(p) = prev
                && content(&p) != content(&(pi, dot))
            {
                cmp_id += 1;
            }
            slot_keys[pi as usize][dot as usize].cmp = cmp_id;
            prev = Some((pi, dot));
        }

        // Refine each cmp class by preceding symbols: read only under
        // `has_preceding_inherited_fields`.
        let mut sym_classes: FxHashMap<(u32, Vec<Symbol>), u32> = FxHashMap::default();
        for &(pi, dot) in &contents {
            let syms: Vec<Symbol> = prods[pi as usize].steps[..dot as usize]
                .iter()
                .map(|s| s.symbol)
                .collect();
            let next = sym_classes.len() as u32;
            let keys = &mut slot_keys[pi as usize][dot as usize];
            keys.eq_with_syms = *sym_classes.entry((keys.cmp, syms)).or_insert(next);
        }

        let mut slots = slot_keys.into_iter();
        let start = slots.next().unwrap();
        let keys = prods[1..]
            .iter()
            .zip(slots)
            .map(|(p, ks)| (core::ptr::from_ref::<Production>(p), ks))
            .collect();

        Self { keys, start }
    }

    /// The keys slice (indexed by `dot`) for a production of this grammar.
    pub fn keys_for(&self, production: &Production) -> &[DotKeys] {
        &self.keys[&core::ptr::from_ref::<Production>(production)]
    }

    pub fn start_keys(&self) -> &[DotKeys] {
        &self.start
    }
}

/// The content tuple that `ParseItem`'s `Ord` (and flagless `Eq`) observe, evaluated on
/// `(production, dot)` directly. Ranking the set of all keys by this order makes
/// the dense `cmp` order-preserving. Item ordering only ever compares same-dot pairs,
/// and the dot comparison keeps the order total across dots so ranks are well defined.
#[derive(Eq)]
struct ItemContent<'a> {
    production: &'a Production,
    dot: usize,
}

impl ItemContent<'_> {
    fn prec(&self) -> &Precedence {
        if self.dot > 0 {
            &self.production.steps[self.dot - 1].precedence
        } else {
            &Precedence::None
        }
    }

    fn assoc(&self) -> Option<Associativity> {
        if self.dot > 0 {
            self.production.steps[self.dot - 1].associativity
        } else {
            None
        }
    }
}

impl Ord for ItemContent<'_> {
    fn cmp(&self, other: &Self) -> Ordering {
        self.production
            .dynamic_precedence
            .cmp(&other.production.dynamic_precedence)
            .then_with(|| {
                self.production
                    .steps
                    .len()
                    .cmp(&other.production.steps.len())
            })
            .then_with(|| self.prec().cmp(other.prec()))
            .then_with(|| self.assoc().cmp(&other.assoc()))
            .then_with(|| self.dot.cmp(&other.dot))
            .then_with(|| {
                let steps = self.production.steps.iter().zip(&other.production.steps);
                for (i, (sa, sb)) in steps.enumerate() {
                    let o = if i < self.dot {
                        sa.alias
                            .cmp(&sb.alias)
                            .then_with(|| sa.field_name.cmp(&sb.field_name))
                    } else {
                        sa.cmp(sb)
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
    /// The production being matched.
    pub production: &'a Production,
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
    pub lookaheads: TokenSet,
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
);

pub struct TokenSetDisplay<'a>(
    pub &'a TokenSet,
    pub &'a SyntaxGrammar,
    pub &'a LexicalGrammar,
);

pub struct ParseItemSetDisplay<'a>(
    pub &'a ParseItemSet<'a>,
    pub &'a SyntaxGrammar,
    pub &'a LexicalGrammar,
);

impl<'a> ParseItem<'a> {
    #[must_use]
    pub fn start(key_map: &'a ItemKeyMap) -> Self {
        ParseItem {
            variable_index: u32::MAX,
            production: &START_PRODUCTION,
            keys: key_map.start_keys(),
            step_index: 0,
            has_preceding_inherited_fields: false,
        }
    }

    #[must_use]
    pub fn step(&self) -> Option<&'a ProductionStep> {
        self.production.steps.get(self.step_index as usize)
    }

    #[must_use]
    pub fn symbol(&self) -> Option<Symbol> {
        self.step().map(|step| step.symbol)
    }

    #[must_use]
    pub fn associativity(&self) -> Option<Associativity> {
        self.prev_step().and_then(|step| step.associativity)
    }

    #[must_use]
    pub fn precedence(&self) -> &Precedence {
        self.prev_step()
            .map_or(&Precedence::None, |step| &step.precedence)
    }

    #[must_use]
    pub fn prev_step(&self) -> Option<&'a ProductionStep> {
        if self.step_index > 0 {
            Some(&self.production.steps[self.step_index as usize - 1])
        } else {
            None
        }
    }

    #[must_use]
    pub const fn is_done(&self) -> bool {
        self.step_index as usize == self.production.steps.len()
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
            production: self.production,
            keys: self.keys,
            step_index: self.step_index + 1,
            has_preceding_inherited_fields: self.has_preceding_inherited_fields,
        }
    }

    /// Create an item identical to this one, but with a different production.
    /// This is used when dynamically "inlining" certain symbols in a production.
    #[must_use]
    pub const fn substitute_production(
        &self,
        production: &'a Production,
        keys: &'a [DotKeys],
    ) -> Self {
        let mut result = *self;
        result.production = production;
        result.keys = keys;
        result
    }

    /// This item's identity keys at the current dot.
    #[must_use]
    fn dot_keys(&self) -> DotKeys {
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
                        lookaheads: TokenSet::new(),
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

impl fmt::Display for ParseItemDisplay<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        if self.0.is_augmented() {
            write!(f, "START →")?;
        } else {
            write!(
                f,
                "{} →",
                self.1.variables[self.0.variable_index as usize].name
            )?;
        }

        for (i, step) in self.0.production.steps.iter().enumerate() {
            if i == self.0.step_index as usize {
                write!(f, " •")?;
                if !step.precedence.is_none()
                    || step.associativity.is_some()
                    || step.reserved_word_set_id != ReservedWordSetId::default()
                {
                    write!(f, " (")?;
                    if !step.precedence.is_none() {
                        write!(f, " {}", step.precedence)?;
                    }
                    if let Some(associativity) = step.associativity {
                        write!(f, " {associativity:?}")?;
                    }
                    if step.reserved_word_set_id != ReservedWordSetId::default() {
                        write!(f, "reserved: {}", step.reserved_word_set_id)?;
                    }
                    write!(f, " )")?;
                }
            }

            write!(f, " ")?;
            if step.symbol.is_terminal() {
                if let Some(variable) = self.2.variables.get(step.symbol.index) {
                    write!(f, "{}", variable.name)?;
                } else {
                    write!(f, "terminal-{}", step.symbol.index)?;
                }
            } else if step.symbol.is_external() {
                write!(f, "{}", self.1.external_tokens[step.symbol.index].name)?;
            } else {
                write!(f, "{}", self.1.variables[step.symbol.index].name)?;
            }

            if let Some(alias) = &step.alias {
                write!(f, "@{}", alias.value)?;
            }
        }

        if self.0.is_done() {
            write!(f, " •")?;
            if let Some(step) = self.0.production.steps.last() {
                if let Some(associativity) = step.associativity {
                    if step.precedence.is_none() {
                        write!(f, " ({associativity:?})")?;
                    } else {
                        write!(f, " ({} {associativity:?})", step.precedence)?;
                    }
                } else if !step.precedence.is_none() {
                    write!(f, " ({})", step.precedence)?;
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
                if let Some(variable) = self.2.variables.get(symbol.index) {
                    write!(f, "{}", display_variable_name(&variable.name))?;
                } else {
                    write!(f, "terminal-{}", symbol.index)?;
                }
            } else if symbol.is_external() {
                write!(f, "{}", self.1.external_tokens[symbol.index].name)?;
            } else {
                write!(f, "{}", self.1.variables[symbol.index].name)?;
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
                ParseItemDisplay(&entry.item, self.1, self.2),
                TokenSetDisplay(&entry.lookaheads, self.1, self.2),
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
