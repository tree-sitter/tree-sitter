use rustc_hash::FxHashMap;

use crate::{
    node_types::ChildType,
    rules::{Alias, AliasMap, Associativity, Precedence, RuleId, RulePool, SymbolType},
    strpool::StrId,
};

use super::{
    nfa::Nfa,
    rules::{Symbol, TokenSet},
};

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub enum VariableType {
    Hidden,
    Auxiliary,
    Anonymous,
    Named,
}

#[derive(Clone, Copy)]
pub struct Variable {
    pub name: StrId,
    pub root: RuleId,
}

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash, Debug)]
pub enum PrecedenceEntry {
    Name(StrId),
    Symbol(StrId),
}

/// The parsed grammar.
#[derive(Default)]
pub struct InputGrammar {
    pub pool: RulePool,
    pub name: StrId,
    pub variables: Vec<Variable>,
    pub external_roots: Vec<RuleId>,
    pub extra_roots: Vec<RuleId>,
    pub reserved_sets: Vec<ReservedWordContext>,
    pub supertype_names: Vec<StrId>,
    pub conflict_names: Vec<Vec<StrId>>,
    pub inline_names: Vec<StrId>,
    pub word_name: Option<StrId>,
    pub precedence_orderings: Vec<Vec<PrecedenceEntry>>,
}

#[derive(Clone)]
pub struct ReservedWordContext {
    pub name: StrId,
    pub roots: Vec<RuleId>,
}

// Extracted lexical grammar

#[derive(Debug, PartialEq, Eq)]
pub struct LexicalVariable {
    pub name: StrId,
    pub kind: VariableType,
    pub implicit_precedence: i32,
    pub start_state: u32,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub struct LexicalGrammar {
    pub nfa: Nfa,
    pub variables: Vec<LexicalVariable>,
}

#[derive(Clone, Copy, PartialEq, Eq, Hash, Debug, Default)]
pub struct ProductionStep {
    pub sym_index: u32,
    pub prec_val: i32,
    pub alias: u32,
    pub field: u32,
    pub reserved: u16,
    pub flags: u8,
}

const _: () = assert!(std::mem::size_of::<ProductionStep>() == 20);

#[rustfmt::skip]
impl ProductionStep {
    // `FStep::flags` bit layout
    //     - 0-2 kind (`SymbolType`)
    //     - 3-4 precedence tag (None 00, Integer 01, Name 10)
    //     - 5-6 associativity  (None 00, Left 01, Right 10)
    //     - 7   alias `is_named`
    const KIND_MASK: u8    = 0b0000_0111;
    const PREC_INTEGER: u8 = 0b0000_1000;
    const PREC_NAME: u8    = 0b0001_0000;
    const PREC_MASK: u8    = 0b0001_1000;
    const ASSOC_LEFT: u8   = 0b0010_0000;
    const ASSOC_RIGHT: u8  = 0b0100_0000;
    const ASSOC_MASK: u8   = 0b0110_0000;
    const ALIAS_NAMED: u8  = 0b1000_0000;

    /// `FStep::reserved` sentinel, meaning no reserved word set at all. Only the augmented
    /// start production carries it, and it must never index the reserved-sets table.
    pub const NO_RESERVED_WORDS: u16 = u16::MAX;
}

impl ProductionStep {
    /// Pack a production step's components into its flat `FStep` representation.
    #[must_use]
    pub fn pack(
        symbol: Symbol,
        prec: Precedence,
        assoc: Option<Associativity>,
        alias: Option<Alias>,
        field: Option<StrId>,
        reserved: u16,
    ) -> Self {
        let mut step = Self {
            sym_index: symbol.index,
            reserved,
            flags: symbol.kind as u8,
            ..Default::default()
        };
        step.set_precedence(prec);
        step.set_associativity(assoc);
        step.set_alias(alias);
        step.set_field(field);
        step
    }

    #[must_use]
    pub const fn symbol(self) -> Symbol {
        Symbol {
            kind: match self.flags & Self::KIND_MASK {
                0 => SymbolType::External,
                1 => SymbolType::End,
                2 => SymbolType::EndOfNonTerminalExtra,
                3 => SymbolType::Terminal,
                _ => SymbolType::NonTerminal,
            },
            index: self.sym_index,
        }
    }

    #[must_use]
    pub const fn precedence(self) -> Precedence {
        match self.flags & Self::PREC_MASK {
            Self::PREC_INTEGER => Precedence::Integer(self.prec_val),
            Self::PREC_NAME => Precedence::Name(StrId::from_raw(self.prec_val as u32)),
            _ => Precedence::None,
        }
    }

    pub const fn set_precedence(&mut self, prec: Precedence) {
        let (bits, val) = match prec {
            Precedence::None => (0, 0),
            Precedence::Integer(n) => (Self::PREC_INTEGER, n),
            Precedence::Name(sid) => (Self::PREC_NAME, sid.raw() as i32),
        };
        self.prec_val = val;
        self.flags = (self.flags & !Self::PREC_MASK) | bits;
    }

    #[must_use]
    pub const fn associativity(self) -> Option<Associativity> {
        match self.flags & Self::ASSOC_MASK {
            Self::ASSOC_LEFT => Some(Associativity::Left),
            Self::ASSOC_RIGHT => Some(Associativity::Right),
            _ => None,
        }
    }

    pub const fn set_associativity(&mut self, assoc: Option<Associativity>) {
        let bits = match assoc {
            None => 0,
            Some(Associativity::Left) => Self::ASSOC_LEFT,
            Some(Associativity::Right) => Self::ASSOC_RIGHT,
        };
        self.flags = (self.flags & !Self::ASSOC_MASK) | bits;
    }

    #[must_use]
    pub fn alias(self) -> Option<Alias> {
        (self.alias != 0).then(|| Alias {
            value: StrId::from_raw(self.alias),
            is_named: self.flags & Self::ALIAS_NAMED != 0,
        })
    }

    pub fn set_alias(&mut self, alias: Option<Alias>) {
        self.alias = alias.map_or(0, |a| a.value.raw());
        self.set_alias_named(alias.is_some_and(|a| a.is_named));
    }

    pub const fn set_alias_named(&mut self, named: bool) {
        self.flags = (self.flags & !Self::ALIAS_NAMED) | if named { Self::ALIAS_NAMED } else { 0 };
    }

    #[must_use]
    pub fn field(self) -> Option<StrId> {
        (self.field != 0).then(|| StrId::from_raw(self.field))
    }

    pub fn set_field(&mut self, field: Option<StrId>) {
        self.field = field.map_or(0, StrId::raw);
    }

    pub fn child_type(&self, default_aliases: &AliasMap) -> ChildType {
        if let Some(alias) = self.alias() {
            ChildType::Aliased(alias)
        } else if let Some(alias) = default_aliases.get(&self.symbol()) {
            ChildType::Aliased(*alias)
        } else {
            ChildType::Normal(self.symbol())
        }
    }
}

// Extracted syntax grammar

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct ReservedWordSetId(pub u32);

impl std::fmt::Display for ReservedWordSetId {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.0.fmt(f)
    }
}

/// A flattened production consisting of a step range and its dynamic precedence
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct Production {
    pub steps_start: u32,
    pub steps_len: u32,
    pub dynamic_precedence: i32,
}

impl Production {
    #[must_use]
    pub const fn step_range(self) -> std::ops::Range<usize> {
        self.steps_start as usize..(self.steps_start + self.steps_len) as usize
    }
}

/// Flattened output: one backing store of steps, productions as `[start, len)`
/// ranges into it, and per-variable production ranges.
#[derive(Clone, Default)]
pub struct ProductionStore {
    pub steps: Vec<ProductionStep>,
    pub productions: Vec<Production>,
    pub var_prods: Vec<(u32, u32)>,
}

#[derive(Debug, Default)]
pub struct InlinedProductionMap {
    pub map: FxHashMap<(u32, u32), Vec<u32>>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct SyntaxVariable {
    pub name: StrId,
    pub kind: VariableType,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ExternalToken {
    pub name: StrId,
    pub kind: VariableType,
    pub corresponding_internal_token: Option<Symbol>,
}

#[derive(Debug, Default)]
pub struct SyntaxGrammar {
    pub variables: Vec<SyntaxVariable>,
    pub extra_symbols: Vec<Symbol>,
    pub expected_conflicts: Vec<Vec<Symbol>>,
    pub external_tokens: Vec<ExternalToken>,
    pub supertype_symbols: Vec<Symbol>,
    pub variables_to_inline: Vec<Symbol>,
    pub word_token: Option<Symbol>,
    pub precedence_orderings: Vec<Vec<PrecedenceEntry>>,
    pub reserved_word_sets: Vec<TokenSet>,

    pub steps: Vec<ProductionStep>,
    pub productions: Vec<Production>,
    pub var_prods: Vec<(u32, u32)>,
}

impl SyntaxGrammar {
    #[must_use]
    pub fn production(&self, id: u32) -> ProdRef<'_> {
        let p = self.productions[id as usize];
        ProdRef {
            steps: &self.steps[p.step_range()],
            dynamic_precedence: p.dynamic_precedence,
        }
    }

    /// The pooled production ids belonging to a variable
    #[must_use]
    pub fn variable_prod_ids(&self, variable_index: usize) -> std::ops::Range<u32> {
        let (start, end) = self.var_prods[variable_index];
        start..end
    }
}

/// A production in the pooled [`SyntaxGrammar`] storage
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct ProdRef<'a> {
    pub steps: &'a [ProductionStep],
    pub dynamic_precedence: i32,
}

impl ProdRef<'_> {
    #[must_use]
    pub fn first_symbol(&self) -> Option<Symbol> {
        self.steps.first().map(|s| s.symbol())
    }
}

impl VariableType {
    #[must_use]
    pub fn is_visible(self) -> bool {
        self == Self::Named || self == Self::Anonymous
    }
}

impl LexicalGrammar {
    pub fn variable_indices_for_nfa_states<'a>(
        &'a self,
        state_ids: &'a [u32],
    ) -> impl Iterator<Item = usize> + 'a {
        let mut prev = None;
        state_ids.iter().filter_map(move |state_id| {
            let variable_id = self.variable_index_for_nfa_state(*state_id);
            if prev == Some(variable_id) {
                None
            } else {
                prev = Some(variable_id);
                prev
            }
        })
    }

    #[must_use]
    pub fn variable_index_for_nfa_state(&self, state_id: u32) -> usize {
        // The NFA is built in reverse (accept state first, entry state last), so
        // each variable's `start_state` is the last (highest) NFA state allocated
        // for it. These values are monotonically increasing, so we can binary
        // search for the first variable whose start_state >= state_id.
        self.variables.partition_point(|v| v.start_state < state_id)
    }
}

impl SyntaxVariable {
    #[must_use]
    pub fn is_auxiliary(&self) -> bool {
        self.kind == VariableType::Auxiliary
    }

    #[must_use]
    pub fn is_hidden(&self) -> bool {
        self.kind == VariableType::Hidden || self.kind == VariableType::Auxiliary
    }
}

impl InlinedProductionMap {
    #[must_use]
    pub fn inlined_prod_ids(&self, prod_id: u32, step_index: u32) -> Option<&[u32]> {
        self.map.get(&(prod_id, step_index)).map(Vec::as_slice)
    }
}
