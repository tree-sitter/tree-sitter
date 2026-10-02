use std::{
    cmp::Ordering,
    collections::{BTreeMap, BTreeSet, VecDeque},
    hash::{BuildHasher as _, BuildHasherDefault},
    num::NonZeroU32,
};

use hashbrown::{HashTable, hash_table};
use indexmap::{IndexMap, map::Entry};
use rustc_hash::{FxBuildHasher, FxHashMap, FxHashSet, FxHasher};
use serde::{Deserialize, Serialize};
use thiserror::Error;

use super::{
    SymbolIndexer,
    item::{ParseItem, ParseItemSet, ParseItemSetCore, ParseItemSetEntry},
    item_set_builder::ParseItemSetBuilder,
};
use crate::{
    Diagnostic,
    build_tables::item::{LookaheadSetPool, START_PRODUCTION_ID, prec_display},
    grammars::{LexicalGrammar, PrecedenceEntry, ReservedWordSetId, SyntaxGrammar, VariableType},
    node_types::VariableInfo,
    rules::{Associativity, NonTerminalIndex, Precedence, Symbol, SymbolView, TokenSet},
    strpool::StrPool,
    tables::{
        ActionList, ActionListPool, FieldLocation, GotoAction, ParseAction, ParseState,
        ParseStateId, ParseTable, ParseTableEntry, ProductionInfo, ProductionInfoId,
    },
};

// For conflict reporting, each parse state is associated with an example
// sequence of symbols that could lead to that parse state.
type SymbolSequence = Vec<Symbol>;

/// Index into [`AuxiliarySymbolContexts::contexts`].
#[derive(Clone, Copy, PartialEq, Eq)]
struct AuxiliaryContextId(NonZeroU32);

impl AuxiliaryContextId {
    /// Inverse of [`Self::index`].
    const fn from_index(index: usize) -> Self {
        Self(NonZeroU32::new(index as u32 + 1).unwrap())
    }

    /// Dense 0-based index (ids are 1-based).
    const fn index(self) -> usize {
        self.0.get() as usize - 1
    }
}

/// Index into [`AuxiliarySymbolContexts::parent_sets`].
#[derive(Clone, Copy)]
struct AuxiliaryParentSetId(u32);

/// For conflict reporting, each parse state is associated with the auxiliary (repeat)
/// symbols in progress along the path to that state, and their parents: the non-auxiliary
/// rules that were using them. Auxiliary symbols can't be named in the grammar's
/// `conflicts`, so a conflict inside a repeat rule is reported in terms of its parents.
///
/// A state's context only holds the auxiliary symbols at a dot in that state, and links
/// to its predecessor: the context of the state that first led to it. Successor states
/// share a context, and a lookup follows the predecessors back to the most recent state
/// that used the symbol.
#[derive(Default)]
struct AuxiliarySymbolContexts {
    /// Indexed by [`AuxiliaryContextId::index`].
    contexts: Vec<AuxiliaryContext>,
    /// Every context's (auxiliary symbol, parent set) pairs.
    entries: Vec<(NonTerminalIndex, AuxiliaryParentSetId)>,
    /// Symbols of every distinct parent set, concatenated in intern order.
    parent_symbols: Vec<Symbol>,
    /// Each parent set's slice of `parent_symbols`, indexed by [`AuxiliaryParentSetId`].
    parent_sets: Vec<AuxiliaryParentSet>,
    /// [`AuxiliaryParentSetId`]s of every distinct parent set.
    parent_set_ids: HashTable<AuxiliaryParentSetId>,
}

/// One state's slice of [`AuxiliarySymbolContexts::entries`], and its predecessor.
struct AuxiliaryContext {
    predecessor: Option<AuxiliaryContextId>,
    start: u32,
    len: u32,
}

/// One parent set's slice of [`AuxiliarySymbolContexts::parent_symbols`].
#[derive(Clone, Copy)]
struct AuxiliaryParentSet {
    start: u32,
    len: u32,
}

impl AuxiliarySymbolContexts {
    /// Adds the context of a state whose predecessor is `predecessor`. `uses` pairs each
    /// auxiliary symbol at a dot in the state with the rule of an item using it. Auxiliary
    /// rules aren't parents, but a symbol used only by auxiliary rules still gets an (empty)
    /// entry, which hides any earlier one.
    fn push(
        &mut self,
        grammar: &SyntaxGrammar,
        predecessor: Option<AuxiliaryContextId>,
        mut uses: Vec<(NonTerminalIndex, NonTerminalIndex)>,
    ) -> Option<AuxiliaryContextId> {
        if uses.is_empty() {
            return predecessor;
        }
        uses.sort_unstable();
        uses.dedup();
        let start = self.entries.len() as u32;
        let mut parents = Vec::new();
        for group in uses.chunk_by(|a, b| a.0 == b.0) {
            parents.clear();
            parents.extend(
                group
                    .iter()
                    .filter(|(_, parent)| !grammar.variables[usize::from(*parent)].is_auxiliary())
                    .map(|&(_, parent)| Symbol::from(parent)),
            );
            let parent_set = self.intern(&parents);
            let symbol = group[0].0;
            self.entries.push((symbol, parent_set));
        }
        let id = AuxiliaryContextId::from_index(self.contexts.len());
        self.contexts.push(AuxiliaryContext {
            predecessor,
            start,
            len: self.entries.len() as u32 - start,
        });
        Some(id)
    }

    /// Returns the parents of `symbol` in the most recent state that had it at a dot, along
    /// the path to the state whose context is `context`.
    fn parents(
        &self,
        mut context: Option<AuxiliaryContextId>,
        symbol: NonTerminalIndex,
    ) -> Option<&[Symbol]> {
        while let Some(id) = context {
            let AuxiliaryContext {
                predecessor,
                start,
                len,
            } = self.contexts[id.index()];
            let entries = &self.entries[start as usize..(start + len) as usize];
            if let Some(&(_, parent_set)) = entries.iter().find(|(s, _)| *s == symbol) {
                return Some(Self::parent_set(
                    &self.parent_symbols,
                    &self.parent_sets,
                    parent_set,
                ));
            }
            context = predecessor;
        }
        None
    }

    /// Returns the id of the parent set `parents`, interning it if it's new.
    fn intern(&mut self, parents: &[Symbol]) -> AuxiliaryParentSetId {
        let Self {
            parent_symbols,
            parent_sets,
            parent_set_ids,
            ..
        } = self;
        let hash = FxBuildHasher.hash_one(parents);
        match parent_set_ids.entry(
            hash,
            |&id| Self::parent_set(parent_symbols, parent_sets, id) == parents,
            |&id| FxBuildHasher.hash_one(Self::parent_set(parent_symbols, parent_sets, id)),
        ) {
            hash_table::Entry::Occupied(entry) => *entry.get(),
            hash_table::Entry::Vacant(entry) => {
                let id = AuxiliaryParentSetId(parent_sets.len() as u32);
                parent_sets.push(AuxiliaryParentSet {
                    start: parent_symbols.len() as u32,
                    len: parents.len() as u32,
                });
                parent_symbols.extend_from_slice(parents);
                entry.insert(id);
                id
            }
        }
    }

    fn parent_set<'a>(
        parent_symbols: &'a [Symbol],
        parent_sets: &[AuxiliaryParentSet],
        id: AuxiliaryParentSetId,
    ) -> &'a [Symbol] {
        let AuxiliaryParentSet { start, len } = parent_sets[id.0 as usize];
        &parent_symbols[start as usize..(start + len) as usize]
    }
}

pub struct ParseStateInfo<'a> {
    pub preceding_symbols_by_id: Vec<SymbolSequence>,
    item_sets_by_ids: IndexMap<ParseItemSet<'a>, ParseStateId, BuildHasherDefault<FxHasher>>,
    pub lookaheads: LookaheadSetPool,
}

impl<'a> ParseStateInfo<'a> {
    #[must_use]
    pub fn item_set(&self, id: ParseStateId) -> &ParseItemSet<'a> {
        self.item_sets_by_ids.get_index(id as usize).unwrap().0
    }
}

#[derive(Clone, Debug, Default)]
struct ReductionInfo {
    precedence: Precedence,
    symbols: Vec<Symbol>,
    has_left_assoc: bool,
    has_right_assoc: bool,
    has_non_assoc: bool,
}

impl ReductionInfo {
    /// Resets this to the default, keeping the `symbols` buffer.
    fn clear(&mut self) {
        self.symbols.clear();
        *self = Self {
            symbols: std::mem::take(&mut self.symbols),
            ..Self::default()
        };
    }
}

/// The reductions on each lookahead of the state that `add_actions` is working on.
struct ReductionInfos {
    /// Gives each lookahead its slot in `infos`.
    indexer: SymbolIndexer,
    /// Each lookahead's reductions, by [`SymbolIndexer::index`]. Only the lookaheads with a
    /// reduction in the current state are up to date: `add_actions` clears a lookahead's info at
    /// its first reduction in each state.
    infos: Vec<ReductionInfo>,
}

impl ReductionInfos {
    fn new(indexer: SymbolIndexer) -> Self {
        Self {
            indexer,
            infos: vec![ReductionInfo::default(); indexer.token_count() as usize],
        }
    }

    /// The reductions on `lookahead`.
    fn get(&self, lookahead: Symbol) -> &ReductionInfo {
        &self.infos[self.indexer.index(lookahead)]
    }

    /// The reductions on `lookahead`, to update.
    fn get_mut(&mut self, lookahead: Symbol) -> &mut ReductionInfo {
        &mut self.infos[self.indexer.index(lookahead)]
    }
}

/// The item sets of a state's successors, one for each symbol that follows a dot in the state.
struct SuccessorSets<'a> {
    /// Gives each symbol its slot in `sets`.
    indexer: SymbolIndexer,
    /// Each symbol's successor item set, by [`SymbolIndexer::index`].
    sets: Vec<Option<ParseItemSet<'a>>>,
    /// The symbols that have a set in `sets`, in the order their sets were added.
    symbols: Vec<Symbol>,
}

impl<'a> SuccessorSets<'a> {
    fn new(indexer: SymbolIndexer) -> Self {
        Self {
            indexer,
            sets: vec![None; indexer.symbol_count() as usize],
            symbols: Vec::new(),
        }
    }

    /// The item set of the successor after `symbol`, added if it's new.
    fn item_set(&mut self, symbol: Symbol) -> &mut ParseItemSet<'a> {
        let slot = &mut self.sets[self.indexer.index(symbol)];
        if slot.is_none() {
            self.symbols.push(symbol);
        }
        slot.get_or_insert_default()
    }

    /// Takes the sets out in symbol order, leaving this empty for the next state.
    fn take_all(&mut self) -> Vec<(Symbol, ParseItemSet<'a>)> {
        self.symbols.sort_unstable();
        self.symbols
            .drain(..)
            .map(|symbol| {
                // INVARIANT: every symbol in `symbols` has a set
                let set = self.sets[self.indexer.index(symbol)].take().unwrap();
                (symbol, set)
            })
            .collect()
    }
}

struct ParseStateQueueEntry {
    state_id: ParseStateId,
    preceding_auxiliary_context: Option<AuxiliaryContextId>,
}

struct ParseTableBuilder<'a> {
    item_set_builder: ParseItemSetBuilder<'a>,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    variable_info: &'a [VariableInfo],
    core_ids_by_core: FxHashMap<ParseItemSetCore<'a>, u32>,
    state_ids_by_item_set: IndexMap<ParseItemSet<'a>, ParseStateId, BuildHasherDefault<FxHasher>>,
    preceding_symbols_by_id: Vec<SymbolSequence>,
    production_info_ids_by_prod_id: Vec<Option<ProductionInfoId>>,
    parse_state_queue: VecDeque<ParseStateQueueEntry>,
    auxiliary_contexts: AuxiliarySymbolContexts,
    non_terminal_extra_states: Vec<(Symbol, ParseStateId)>,
    actual_conflicts: FxHashSet<Vec<Symbol>>,
    parse_table: ParseTable<ParseTableEntry>,
    str_pool: &'a StrPool,
    /// Scratch for `add_actions`: The successor item sets of the state it's working on.
    successor_sets: SuccessorSets<'a>,
    /// Scratch for `add_actions`: The reductions on each lookahead of the state it's working on.
    reduction_infos: ReductionInfos,
}

pub type BuildTableResult<T> = Result<T, ParseTableBuilderError>;

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub enum ParseTableBuilderError {
    #[error("Unresolved conflict for symbol sequence:\n\n{0}")]
    Conflict(Box<ConflictError>),
    #[error("Extra rules must have unambiguous endings. Conflicting rules: {0}")]
    AmbiguousExtra(#[from] AmbiguousExtraError),
    #[error(
        "The non-terminal rule `{0}` is used in a non-terminal `extra` rule, which is not allowed."
    )]
    ImproperNonTerminalExtra(Box<str>),
    #[error("State count `{0}` exceeds the max value {max}.", max=u16::MAX)]
    StateCount(usize),
}

impl From<ConflictError> for ParseTableBuilderError {
    fn from(error: ConflictError) -> Self {
        Self::Conflict(Box::new(error))
    }
}

#[derive(Default, Debug, Serialize, Error, Deserialize, PartialEq, Eq)]
pub struct ConflictError {
    pub symbol_sequence: Box<[Box<str>]>,
    pub conflicting_lookahead: Box<str>,
    pub possible_interpretations: Vec<Interpretation>,
    pub possible_resolutions: Vec<Resolution>,
}

#[derive(Default, Debug, Serialize, Error, Deserialize, PartialEq, Eq)]
pub struct Interpretation {
    pub preceding_symbols: Box<[Box<str>]>,
    pub variable_name: Box<str>,
    pub production_step_symbols: Box<[Box<str>]>,
    pub step_index: u32,
    pub done: bool,
    pub conflicting_lookahead: Box<str>,
    pub precedence: Option<Box<str>>,
    pub associativity: Option<Box<str>>,
    pub requires_eof_lookahead: bool,
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
pub enum Resolution {
    Precedence { symbols: Box<[Box<str>]> },
    Associativity { symbols: Box<[Box<str>]> },
    AddConflict { symbols: Box<[Box<str>]> },
}

#[derive(Debug, Serialize, Deserialize, Error, PartialEq, Eq)]
pub struct AmbiguousExtraError {
    pub parent_symbols: Box<[Box<str>]>,
}

impl std::fmt::Display for ConflictError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        for symbol in &self.symbol_sequence {
            write!(f, "  {symbol}")?;
        }
        writeln!(f, "  •  {}  …\n", self.conflicting_lookahead)?;

        writeln!(f, "Possible interpretations:\n")?;
        let mut interpretations = self
            .possible_interpretations
            .iter()
            .map(|i| {
                let line = i.to_string();
                let mut annotations = Vec::new();
                if let (Some(precedence), Some(associativity)) = (&i.precedence, &i.associativity) {
                    annotations.push(format!(
                        "(precedence: {precedence}, associativity: {associativity})",
                    ));
                } else if let Some(precedence) = &i.precedence {
                    annotations.push(format!("(precedence: {precedence})"));
                }
                if i.requires_eof_lookahead {
                    annotations.push("(reduces only at end of input)".to_string());
                }
                let prec_line = if annotations.is_empty() {
                    None
                } else {
                    Some(annotations.join("  "))
                };

                (line, prec_line)
            })
            .collect::<Vec<_>>();
        let max_interpretation_length = interpretations
            .iter()
            .map(|i| i.0.chars().count())
            .max()
            .unwrap();
        interpretations.sort_unstable();
        for (i, (line, prec_suffix)) in interpretations.into_iter().enumerate() {
            write!(f, "  {}:", i + 1).unwrap();
            write!(f, "{line}")?;
            if let Some(prec_suffix) = prec_suffix {
                write!(
                    f,
                    "{:1$}",
                    "",
                    max_interpretation_length.saturating_sub(line.chars().count()) + 2
                )?;
                write!(f, "{prec_suffix}")?;
            }
            writeln!(f)?;
        }

        writeln!(f, "\nPossible resolutions:\n")?;
        for (i, resolution) in self.possible_resolutions.iter().enumerate() {
            writeln!(f, "  {}:  {resolution}", i + 1)?;
        }
        Ok(())
    }
}

impl std::fmt::Display for Interpretation {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        for symbol in &self.preceding_symbols {
            write!(f, "  {symbol}")?;
        }
        write!(f, "  ({}", self.variable_name)?;
        for (i, symbol) in self.production_step_symbols.iter().enumerate() {
            if i == self.step_index as usize {
                write!(f, "  •")?;
            }
            write!(f, "  {symbol}")?;
        }
        write!(f, ")")?;
        if self.done {
            write!(f, "  •  {}  …", self.conflicting_lookahead)?;
        }
        Ok(())
    }
}

impl std::fmt::Display for Resolution {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            Self::Precedence { symbols } => {
                write!(f, "Specify a higher precedence in ")?;
                for (i, symbol) in symbols.iter().enumerate() {
                    if i > 0 {
                        write!(f, " and ")?;
                    }
                    write!(f, "`{symbol}`")?;
                }
                write!(f, " than in the other rules.")?;
            }
            Self::Associativity { symbols } => {
                write!(f, "Specify a left or right associativity in ")?;
                for (i, symbol) in symbols.iter().enumerate() {
                    if i > 0 {
                        write!(f, ", ")?;
                    }
                    write!(f, "`{symbol}`")?;
                }
            }
            Self::AddConflict { symbols } => {
                write!(f, "Add a conflict for these rules: ")?;
                for (i, symbol) in symbols.iter().enumerate() {
                    if i > 0 {
                        write!(f, ", ")?;
                    }
                    write!(f, "`{symbol}`")?;
                }
            }
        }
        Ok(())
    }
}

impl std::fmt::Display for AmbiguousExtraError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        for (i, symbol) in self.parent_symbols.iter().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }
            write!(f, "{symbol}")?;
        }
        Ok(())
    }
}

impl<'a> ParseTableBuilder<'a> {
    fn new(
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
        item_set_builder: ParseItemSetBuilder<'a>,
        variable_info: &'a [VariableInfo],
        str_pool: &'a StrPool,
    ) -> Self {
        let symbol_indexer = SymbolIndexer::new(syntax_grammar, lexical_grammar);
        Self {
            syntax_grammar,
            lexical_grammar,
            item_set_builder,
            variable_info,
            non_terminal_extra_states: Vec::new(),
            state_ids_by_item_set: IndexMap::default(),
            core_ids_by_core: FxHashMap::default(),
            preceding_symbols_by_id: Vec::new(),
            production_info_ids_by_prod_id: vec![None; syntax_grammar.productions.len()],
            parse_state_queue: VecDeque::new(),
            auxiliary_contexts: AuxiliarySymbolContexts::default(),
            actual_conflicts: syntax_grammar.expected_conflicts.iter().cloned().collect(),
            parse_table: ParseTable {
                states: Vec::new(),
                action_lists: ActionListPool::default(),
                symbols: Vec::new(),
                external_lex_states: Vec::new(),
                production_infos: Vec::new(),
                max_aliased_production_length: 1,
            },
            str_pool,
            successor_sets: SuccessorSets::new(symbol_indexer),
            reduction_infos: ReductionInfos::new(symbol_indexer),
        }
    }

    fn build(
        mut self,
        diagnostics: &mut Vec<Diagnostic>,
    ) -> BuildTableResult<(ParseTable<ParseTableEntry>, ParseStateInfo<'a>)> {
        // Ensure that the empty alias sequence has index 0.
        self.parse_table
            .production_infos
            .push(ProductionInfo::default());

        // Add the error state at index 0.
        self.add_parse_state(&Vec::new(), None, ParseItemSet::default());

        // Add the starting state at index 1.
        let end_lookaheads = self.item_set_builder.lookaheads.singleton(Symbol::End);
        self.add_parse_state(
            &Vec::new(),
            None,
            ParseItemSet {
                entries: vec![ParseItemSetEntry {
                    item: ParseItem::start(self.item_set_builder.key_map),
                    lookaheads: end_lookaheads,
                    following_reserved_word_set: ReservedWordSetId::default(),
                }],
            },
        );

        // Compute the possible item sets for non-terminal extras.
        let mut non_terminal_extra_item_sets_by_first_terminal =
            BTreeMap::<Symbol, ParseItemSet<'a>>::new();
        for extra_non_terminal in self
            .syntax_grammar
            .extra_symbols
            .iter()
            .filter_map(|s| s.non_terminal_index())
        {
            let extra_index = extra_non_terminal;
            for prod_id in self
                .syntax_grammar
                .variable_prod_ids(usize::from(extra_index))
            {
                let production = self.syntax_grammar.production(prod_id);
                let entry = non_terminal_extra_item_sets_by_first_terminal
                    .entry(production.first_symbol().unwrap())
                    .or_default()
                    .insert(ParseItem {
                        variable_index: extra_index.into(),
                        prod_id,
                        step_index: 1,
                        keys: self.item_set_builder.key_map.keys_for(prod_id),
                        has_preceding_inherited_fields: false,
                    });
                entry.lookaheads = self
                    .item_set_builder
                    .lookaheads
                    .insert(entry.lookaheads, Symbol::EndOfNonTerminalExtra);
            }
        }

        let non_terminal_sets_len = non_terminal_extra_item_sets_by_first_terminal.len();
        self.non_terminal_extra_states
            .reserve(non_terminal_sets_len);
        self.preceding_symbols_by_id.reserve(non_terminal_sets_len);
        self.parse_table.states.reserve(non_terminal_sets_len);
        self.parse_state_queue.reserve(non_terminal_sets_len);
        // Add a state for each starting terminal of a non-terminal extra rule.
        for (terminal_key, item_set) in non_terminal_extra_item_sets_by_first_terminal {
            let terminal = terminal_key;
            if terminal.non_terminal_index().is_some() {
                Err(ParseTableBuilderError::ImproperNonTerminalExtra(
                    self.symbol_name(terminal),
                ))?;
            }

            // Add the parse state, and *then* push the terminal and the state id into the
            // list of nonterminal extra states
            let state_id = self.add_parse_state(&Vec::new(), None, item_set);
            self.non_terminal_extra_states.push((terminal, state_id));
        }

        while let Some(entry) = self.parse_state_queue.pop_front() {
            // The dedup-map key is each state's kernel (the GOTO result, pre closure).
            // Two states are identical iff their kernels match.
            let kernel = self
                .state_ids_by_item_set
                .get_index(entry.state_id as usize)
                // Invariant: `state_id` is the map's insertion index
                .unwrap()
                .0;
            let item_set = self.item_set_builder.transitive_closure(kernel);

            self.add_actions(
                self.preceding_symbols_by_id[entry.state_id as usize].clone(),
                entry.preceding_auxiliary_context,
                entry.state_id,
                &item_set,
            )?;
        }

        if !self.actual_conflicts.is_empty() {
            let mut conflicts = self
                .actual_conflicts
                .iter()
                .map(|conf| conf.iter().map(|&s| self.symbol_name(s)).collect())
                .collect::<Vec<_>>();
            conflicts.sort_unstable();
            diagnostics.push(Diagnostic::UnnecessaryConflicts(conflicts.into()));
        }

        Ok((
            self.parse_table,
            ParseStateInfo {
                preceding_symbols_by_id: self.preceding_symbols_by_id,
                item_sets_by_ids: self.state_ids_by_item_set,
                lookaheads: self.item_set_builder.lookaheads,
            },
        ))
    }

    fn add_parse_state(
        &mut self,
        preceding_symbols: &SymbolSequence,
        preceding_auxiliary_context: Option<AuxiliaryContextId>,
        item_set: ParseItemSet<'a>,
    ) -> ParseStateId {
        match self.state_ids_by_item_set.entry(item_set) {
            // If an equivalent item set has already been processed, then return
            // the existing parse state index.
            Entry::Occupied(o) => *o.get(),

            // Otherwise, insert a new parse state and add it to the queue of
            // parse states to populate.
            Entry::Vacant(v) => {
                let core = v.key().core();
                let core_count = self.core_ids_by_core.len() as u32;
                let core_id = *self.core_ids_by_core.entry(core).or_insert(core_count);

                let state_id = self.parse_table.states.len() as u32;
                self.preceding_symbols_by_id.push(preceding_symbols.clone());

                self.parse_table.states.push(ParseState {
                    id: state_id,
                    lex_state_id: 0,
                    external_lex_state_id: 0,
                    terminal_entries: IndexMap::default(),
                    nonterminal_entries: IndexMap::default(),
                    reserved_words: TokenSet::default(),
                    core_id,
                    has_eof_gated_reduce: false,
                });
                self.parse_state_queue.push_back(ParseStateQueueEntry {
                    state_id,
                    preceding_auxiliary_context,
                });
                v.insert(state_id);
                state_id
            }
        }
    }

    fn add_actions(
        &mut self,
        mut preceding_symbols: SymbolSequence,
        preceding_auxiliary_context: Option<AuxiliaryContextId>,
        state_id: ParseStateId,
        item_set: &ParseItemSet<'a>,
    ) -> BuildTableResult<()> {
        let mut lookaheads_with_conflicts = TokenSet::new();
        let mut auxiliary_uses = Vec::new();

        // Each item in the item set contributes to either or a Shift action or a Reduce
        // action in this state.
        for ParseItemSetEntry {
            item,
            lookaheads,
            following_reserved_word_set: reserved_lookaheads,
        } in &item_set.entries
        {
            // If the item is unfinished, then this state has a transition for the item's
            // next symbol. Advance the item to its next step and insert the resulting
            // item into the successor item set.
            if let Some(next_symbol) = item.symbol(self.syntax_grammar) {
                let mut successor = item.successor();
                if let Some(non_terminal_index) = next_symbol.non_terminal_index() {
                    let index = usize::from(non_terminal_index);
                    let variable = &self.syntax_grammar.variables[index];

                    // Keep track of where auxiliary non-terminals (repeat symbols) are
                    // used within visible symbols. This information may be needed later
                    // for conflict resolution.
                    if variable.is_auxiliary() {
                        let parent = NonTerminalIndex::new(item.variable_index);
                        auxiliary_uses.push((non_terminal_index, parent));
                    }

                    // For most parse items, the symbols associated with the preceding children
                    // don't matter: they have no effect on the REDUCE action that would be
                    // performed at the end of the item. But the symbols *do* matter for
                    // children that are hidden and have fields, because those fields are
                    // "inherited" by the parent node.
                    //
                    // If this item has consumed a hidden child with fields, then the symbols
                    // of its preceding children need to be taken into account when comparing
                    // it with other items.
                    if variable.is_hidden() && !self.variable_info[index].fields.is_empty() {
                        successor.has_preceding_inherited_fields = true;
                    }
                }
                let successor_set = self.successor_sets.item_set(next_symbol);
                let successor_entry = successor_set.insert(successor);
                successor_entry.lookaheads = self
                    .item_set_builder
                    .lookaheads
                    .union(successor_entry.lookaheads, *lookaheads);
                successor_entry.following_reserved_word_set = successor_entry
                    .following_reserved_word_set
                    .max(*reserved_lookaheads);
            }
            // If the item is finished, then add a Reduce action to this state based
            // on this item.
            else {
                let symbol = Symbol::non_terminal(item.variable_index as usize);
                let action = if item.is_augmented() {
                    ParseAction::Accept
                } else {
                    // These values are narrowed to u16 to reduce the size of
                    // ParseAction. No real-world grammar approaches these limits.
                    debug_assert!(
                        u16::try_from(item.step_index).is_ok(),
                        "production step count exceeds u16::MAX"
                    );
                    let production_id = self.get_production_id(item);
                    debug_assert!(
                        u16::try_from(production_id).is_ok(),
                        "production info id exceeds u16::MAX"
                    );
                    ParseAction::Reduce {
                        symbol,
                        child_count: item.step_index as u16,
                        dynamic_precedence: item.production(self.syntax_grammar).dynamic_precedence,
                        production_id: production_id as u16,
                    }
                };

                let precedence = item.precedence(self.syntax_grammar);
                let associativity = item.associativity(self.syntax_grammar);
                if item.production(self.syntax_grammar).requires_eof_lookahead {
                    self.parse_table.states[state_id as usize].has_eof_gated_reduce = true;
                }
                for lookahead in self.item_set_builder.lookaheads.get(*lookaheads).iter() {
                    if item.production(self.syntax_grammar).requires_eof_lookahead
                        && lookahead != Symbol::End
                    {
                        continue;
                    }
                    let table_entry = self.parse_table.states[state_id as usize]
                        .terminal_entries
                        .entry(lookahead)
                        .or_insert_with(ParseTableEntry::new);
                    let reduction_info = self.reduction_infos.get_mut(lookahead);

                    // While inserting Reduce actions, eagerly resolve conflicts related
                    // to precedence: avoid inserting lower-precedence reductions, and
                    // clear the action list when inserting higher-precedence reductions.
                    if table_entry.actions.is_empty() {
                        // This is the lookahead's first reduction in this state, so its info is
                        // still from an earlier state.
                        reduction_info.clear();
                        table_entry.actions.push(action);
                    } else {
                        match Self::compare_precedence(
                            self.syntax_grammar,
                            precedence,
                            &[symbol],
                            reduction_info.precedence,
                            &reduction_info.symbols,
                        ) {
                            Ordering::Greater => {
                                table_entry.actions.clear();
                                table_entry.actions.push(action);
                                lookaheads_with_conflicts.remove(lookahead);
                                reduction_info.clear();
                            }
                            // Two items that reduce identically build the same tree, so
                            // there is nothing for the user to resolve. Precedence is
                            // still compared first, because an item that only repeats an
                            // existing action can still outrank it and clear the entry.
                            Ordering::Equal => {
                                if !table_entry.actions.contains(&action) {
                                    table_entry.actions.push(action);
                                    lookaheads_with_conflicts.insert(lookahead);
                                }
                            }
                            Ordering::Less => continue,
                        }
                    }

                    reduction_info.precedence = precedence;
                    if let Err(i) = reduction_info.symbols.binary_search(&symbol) {
                        reduction_info.symbols.insert(i, symbol);
                    }
                    match associativity {
                        Some(Associativity::Left) => reduction_info.has_left_assoc = true,
                        Some(Associativity::Right) => reduction_info.has_right_assoc = true,
                        None => reduction_info.has_non_assoc = true,
                    }
                }
            }
        }

        let auxiliary_context = self.auxiliary_contexts.push(
            self.syntax_grammar,
            preceding_auxiliary_context,
            auxiliary_uses,
        );

        // Having computed the successor item sets for each symbol, add a new
        // parse state for each of these item sets, and add a corresponding Shift
        // action to this state.
        let mut terminal_successors = self.successor_sets.take_all();
        // Non-terminals come last in symbol order.
        let non_terminal_successors = terminal_successors.split_off(
            terminal_successors
                .partition_point(|(symbol, _)| symbol.non_terminal_index().is_none()),
        );
        for (symbol, next_item_set) in terminal_successors {
            preceding_symbols.push(symbol);
            let next_state_id =
                self.add_parse_state(&preceding_symbols, auxiliary_context, next_item_set);
            preceding_symbols.pop();

            let entry = self.parse_table.states[state_id as usize]
                .terminal_entries
                .entry(symbol);
            if let Entry::Occupied(e) = &entry
                && !e.get().actions.is_empty()
            {
                lookaheads_with_conflicts.insert(symbol);
            }

            entry
                .or_insert_with(ParseTableEntry::new)
                .actions
                .push(ParseAction::Shift {
                    state: next_state_id,
                    is_repetition: false,
                });
        }

        for (symbol, next_item_set) in non_terminal_successors {
            preceding_symbols.push(symbol);
            let next_state_id =
                self.add_parse_state(&preceding_symbols, auxiliary_context, next_item_set);
            preceding_symbols.pop();
            self.parse_table.states[state_id as usize]
                .nonterminal_entries
                .insert(symbol, GotoAction::Goto(next_state_id));
        }

        // For any symbol with multiple actions, perform conflict resolution.
        // This will either
        // * choose one action over the others using precedence or associativity
        // * keep multiple actions if this conflict has been whitelisted in the grammar
        // * fail, terminating the parser generation process
        if !lookaheads_with_conflicts.is_empty() {
            // Only fnished items and items past their first step can take part in a
            // conflict. Most of a closure is neither, so find those items once per state.
            let candidates = item_set
                .entries
                .iter()
                .filter(|entry| entry.item.step_index > 0 || entry.item.is_done())
                .collect::<Vec<_>>();
            for symbol in lookaheads_with_conflicts.iter() {
                self.handle_conflict(
                    &candidates,
                    state_id,
                    &preceding_symbols,
                    auxiliary_context,
                    symbol,
                )?;
            }
        }

        // Add actions for the grammar's `extra` symbols.
        let state = &mut self.parse_table.states[state_id as usize];
        let is_end_of_non_terminal_extra = state.is_end_of_non_terminal_extra();

        // If this state represents the end of a non-terminal extra rule, then make sure that
        // it doesn't have other successor states. Non-terminal extra rules must have
        // unambiguous endings.
        if is_end_of_non_terminal_extra {
            if state.terminal_entries.len() > 1 {
                let parent_symbols = item_set
                    .entries
                    .iter()
                    .filter_map(|ParseItemSetEntry { item, .. }| {
                        if !item.is_augmented() && item.step_index > 0 {
                            Some(item.variable_index)
                        } else {
                            None
                        }
                    })
                    .collect::<FxHashSet<_>>();
                let parent_symbol_names = parent_symbols
                    .iter()
                    .map(|&variable_index| {
                        self.str_pool
                            .resolve(self.syntax_grammar.variables[variable_index as usize].name)
                            .into()
                    })
                    .collect();

                Err(AmbiguousExtraError {
                    parent_symbols: parent_symbol_names,
                })?;
            }
        }
        // Add actions for the start tokens of each non-terminal extra rule.
        else {
            for (terminal, state_id) in &self.non_terminal_extra_states {
                state
                    .terminal_entries
                    .entry(*terminal)
                    .or_insert(ParseTableEntry {
                        reusable: true,
                        actions: ActionList::One(ParseAction::Shift {
                            state: *state_id,
                            is_repetition: false,
                        }),
                    });
            }

            // Add ShiftExtra actions for the terminal extra tokens. These actions
            // are added to every state except for those at the ends of non-terminal
            // extras.
            for extra_token in &self.syntax_grammar.extra_symbols {
                match extra_token.view() {
                    SymbolView::NonTerminal(_) => {
                        state
                            .nonterminal_entries
                            .insert(*extra_token, GotoAction::ShiftExtra);
                    }
                    SymbolView::Terminal(_) | SymbolView::External(_) => {
                        state
                            .terminal_entries
                            .entry(*extra_token)
                            .or_insert(ParseTableEntry {
                                reusable: true,
                                actions: ActionList::One(ParseAction::ShiftExtra),
                            });
                    }
                    SymbolView::End | SymbolView::EndOfNonTerminalExtra => unreachable!(),
                }
            }
        }

        if let Some(keyword_capture_token) = self.syntax_grammar.word_token {
            let reserved_word_set_id = item_set
                .entries
                .iter()
                .filter_map(|entry| {
                    if let Some(next_step) = entry.item.step(self.syntax_grammar) {
                        if next_step.symbol() == keyword_capture_token {
                            Some(ReservedWordSetId(u32::from(next_step.reserved)))
                        } else {
                            None
                        }
                    } else if self
                        .item_set_builder
                        .lookaheads
                        .get(entry.lookaheads)
                        .contains(keyword_capture_token)
                    {
                        Some(entry.following_reserved_word_set)
                    } else {
                        None
                    }
                })
                .max();
            if let Some(reserved_word_set_id) = reserved_word_set_id {
                state.reserved_words =
                    self.syntax_grammar.reserved_word_sets[reserved_word_set_id.0 as usize].clone();
            }
        }

        Ok(())
    }

    fn handle_conflict(
        &mut self,
        candidates: &[&ParseItemSetEntry],
        state_id: ParseStateId,
        preceding_symbols: &SymbolSequence,
        auxiliary_context: Option<AuxiliaryContextId>,
        conflicting_lookahead: Symbol,
    ) -> BuildTableResult<()> {
        let entry = self.parse_table.states[state_id as usize]
            .terminal_entries
            .get_mut(&conflicting_lookahead)
            .unwrap();
        let reduction_info = self.reduction_infos.get(conflicting_lookahead);

        // Determine which items in the set conflict with each other, and the
        // precedences associated with SHIFT vs REDUCE actions. There won't
        // be multiple REDUCE actions with different precedences; that is
        // sorted out ahead of time in `add_actions`. But there can still be
        // REDUCE-REDUCE conflicts where all actions have the *same*
        // precedence, and there can still be SHIFT/REDUCE conflicts.
        let mut considered_associativity = false;
        let mut shift_precedence = Vec::<(Precedence, Symbol)>::new();
        let mut conflicting_items = BTreeSet::new();
        for ParseItemSetEntry {
            item, lookaheads, ..
        } in candidates
        {
            if let Some(step) = item.step(self.syntax_grammar) {
                if item.step_index > 0
                    && self
                        .item_set_builder
                        .first_set(step.symbol())
                        .contains(conflicting_lookahead)
                {
                    if item.variable_index != u32::MAX {
                        conflicting_items.insert(item);
                    }

                    let p = (
                        item.precedence(self.syntax_grammar),
                        Symbol::non_terminal(item.variable_index as usize),
                    );
                    if let Err(i) = shift_precedence.binary_search(&p) {
                        shift_precedence.insert(i, p);
                    }
                }
            } else if self
                .item_set_builder
                .lookaheads
                .get(*lookaheads)
                .contains(conflicting_lookahead)
                && item.variable_index != u32::MAX
            {
                conflicting_items.insert(item);
            }
        }

        if let ParseAction::Shift { is_repetition, .. } = entry.actions.last_mut().unwrap() {
            // If all of the items in the conflict have the same parent symbol,
            // and that parent symbols is auxiliary, then this is just the intentional
            // ambiguity associated with a repeat rule. Resolve that class of ambiguity
            // by leaving it in the parse table, but marking the SHIFT action with
            // an `is_repetition` flag.
            let conflicting_variable_index =
                conflicting_items.iter().next().unwrap().variable_index;
            if self.syntax_grammar.variables[conflicting_variable_index as usize].is_auxiliary()
                && conflicting_items
                    .iter()
                    .all(|item| item.variable_index == conflicting_variable_index)
            {
                *is_repetition = true;
                return Ok(());
            }

            // If the SHIFT action has higher precedence, remove all the REDUCE actions.
            let mut shift_is_less = false;
            let mut shift_is_equal = false;
            let mut shift_is_more = false;
            for p in shift_precedence {
                match Self::compare_precedence(
                    self.syntax_grammar,
                    p.0,
                    &[p.1],
                    reduction_info.precedence,
                    &reduction_info.symbols,
                ) {
                    Ordering::Greater => shift_is_more = true,
                    Ordering::Less => shift_is_less = true,
                    Ordering::Equal => shift_is_equal = true,
                }
            }

            if shift_is_more && !shift_is_less {
                entry.actions.keep_last();
            }
            // If the REDUCE actions have higher precedence, remove the SHIFT action.
            else if shift_is_less && !shift_is_more {
                // Exception: if one SHIFT interpretation ties the REDUCE actions in
                // precedence while another has lower precedence, and the REDUCE
                // actions are purely right associative, honor that right
                // associativity by shifting rather than reducing. The
                // lower-precedence interpretation coexists with the tying one, so on
                // its own it must not force a REDUCE that would flip the tie to left
                // associative.
                if shift_is_equal
                    && matches!(
                        (
                            reduction_info.has_left_assoc,
                            reduction_info.has_non_assoc,
                            reduction_info.has_right_assoc,
                        ),
                        (false, false, true)
                    )
                {
                    entry.actions.keep_last();
                } else {
                    entry.actions.pop();
                    conflicting_items.retain(|item| item.is_done());
                }
            }
            // If the SHIFT and REDUCE actions have the same precedence, consider
            // the REDUCE actions' associativity.
            else if !shift_is_less && !shift_is_more {
                considered_associativity = true;

                // If all Reduce actions are left associative, remove the SHIFT action.
                // If all Reduce actions are right associative, remove the REDUCE actions.
                match (
                    reduction_info.has_left_assoc,
                    reduction_info.has_non_assoc,
                    reduction_info.has_right_assoc,
                ) {
                    (true, false, false) => {
                        entry.actions.pop();
                        conflicting_items.retain(|item| item.is_done());
                    }
                    (false, false, true) => {
                        entry.actions.keep_last();
                    }
                    _ => {}
                }
            }
        }

        // If all of the actions but one have been eliminated, then there's no problem.
        let entry = self.parse_table.states[state_id as usize]
            .terminal_entries
            .get_mut(&conflicting_lookahead)
            .unwrap();
        if entry.actions.len() == 1 {
            return Ok(());
        }

        // Determine the set of parent symbols involved in this conflict.
        let mut actual_conflict = Vec::new();
        for item in &conflicting_items {
            let symbol = Symbol::non_terminal(item.variable_index as usize);
            if self.syntax_grammar.variables[item.variable_index as usize].is_auxiliary() {
                actual_conflict.extend(
                    self.auxiliary_contexts
                        .parents(
                            auxiliary_context,
                            NonTerminalIndex::new(item.variable_index),
                        )
                        .unwrap(),
                );
            } else {
                actual_conflict.push(symbol);
            }
        }
        actual_conflict.sort_unstable();
        actual_conflict.dedup();

        // If this set of symbols has been whitelisted, then there's no error.
        if self
            .syntax_grammar
            .expected_conflicts
            .contains(&actual_conflict)
        {
            self.actual_conflicts.remove(&actual_conflict);
            return Ok(());
        }

        let mut conflict_error = ConflictError {
            symbol_sequence: preceding_symbols
                .iter()
                .map(|&symbol| self.symbol_name(symbol))
                .collect(),
            conflicting_lookahead: self.symbol_name(conflicting_lookahead),
            ..Default::default()
        };

        let interpretations = conflicting_items
            .iter()
            .map(|item| {
                let preceding_symbols = preceding_symbols
                    .iter()
                    .take(preceding_symbols.len() - item.step_index as usize)
                    .map(|&symbol| self.symbol_name(symbol))
                    .collect();

                let variable_name = self
                    .str_pool
                    .resolve(self.syntax_grammar.variables[item.variable_index as usize].name)
                    .into();

                let production_step_symbols = item
                    .production(self.syntax_grammar)
                    .steps
                    .iter()
                    .map(|step| self.symbol_name(step.symbol()))
                    .collect();

                let precedence = match item.precedence(self.syntax_grammar) {
                    Precedence::None => None,
                    _ => Some(
                        prec_display(item.precedence(self.syntax_grammar), self.str_pool).into(),
                    ),
                };

                let associativity = item
                    .associativity(self.syntax_grammar)
                    .map(|assoc| format!("{assoc:?}").into());

                Interpretation {
                    preceding_symbols,
                    variable_name,
                    production_step_symbols,
                    step_index: item.step_index,
                    done: item.is_done(),
                    conflicting_lookahead: self.symbol_name(conflicting_lookahead),
                    precedence,
                    associativity,
                    requires_eof_lookahead: item
                        .production(self.syntax_grammar)
                        .requires_eof_lookahead,
                }
            })
            .collect::<Vec<_>>();
        conflict_error.possible_interpretations = interpretations;

        let mut shift_items = Vec::new();
        let mut reduce_items = Vec::new();
        for item in conflicting_items {
            if item.is_done() {
                reduce_items.push(item);
            } else {
                shift_items.push(item);
            }
        }
        shift_items.sort_unstable();
        reduce_items.sort_unstable();

        let get_rule_names = |items: &[&ParseItem]| -> Box<[Box<str>]> {
            let mut last_rule_id = None;
            let mut result = Vec::with_capacity(items.len());
            for item in items {
                if last_rule_id == Some(item.variable_index) {
                    continue;
                }
                last_rule_id = Some(item.variable_index);
                result.push(self.symbol_name(Symbol::non_terminal(item.variable_index as usize)));
            }

            result.into()
        };

        if actual_conflict.len() > 1 {
            if !shift_items.is_empty() {
                let names = get_rule_names(&shift_items);
                conflict_error
                    .possible_resolutions
                    .push(Resolution::Precedence { symbols: names });
            }

            for item in &reduce_items {
                let name = self.symbol_name(Symbol::non_terminal(item.variable_index as usize));
                conflict_error
                    .possible_resolutions
                    .push(Resolution::Precedence {
                        symbols: [name].into(),
                    });
            }
        }

        if considered_associativity {
            let names = get_rule_names(&reduce_items);
            conflict_error
                .possible_resolutions
                .push(Resolution::Associativity { symbols: names });
        }

        conflict_error
            .possible_resolutions
            .push(Resolution::AddConflict {
                symbols: actual_conflict
                    .iter()
                    .map(|&s| self.symbol_name(s))
                    .collect(),
            });

        self.actual_conflicts.insert(actual_conflict);

        Err(conflict_error)?
    }

    fn compare_precedence(
        grammar: &SyntaxGrammar,
        left: Precedence,
        left_symbols: &[Symbol],
        right: Precedence,
        right_symbols: &[Symbol],
    ) -> Ordering {
        let precedence_entry_matches =
            |entry: &PrecedenceEntry, precedence: Precedence, symbols: &[Symbol]| -> bool {
                match entry {
                    PrecedenceEntry::Name(n) => {
                        if let Precedence::Name(p) = precedence {
                            *n == p
                        } else {
                            false
                        }
                    }
                    PrecedenceEntry::Symbol(n) => symbols.iter().any(|s| match s.view() {
                        SymbolView::NonTerminal(index) => {
                            &grammar.variables[usize::from(index)].name == n
                        }
                        _ => false,
                    }),
                }
            };

        match (left, right) {
            // Integer precedences can be compared to other integer precedences,
            // and to the default precedence, which is zero.
            (Precedence::Integer(l), Precedence::Integer(r)) if l != 0 || r != 0 => l.cmp(&r),
            (Precedence::Integer(l), Precedence::None) if l != 0 => l.cmp(&0),
            (Precedence::None, Precedence::Integer(r)) if r != 0 => 0.cmp(&r),

            // Named precedences can be compared to other named precedences.
            _ => grammar
                .precedence_orderings
                .iter()
                .find_map(|list| {
                    let mut saw_left = false;
                    let mut saw_right = false;
                    for entry in list {
                        let matches_left = precedence_entry_matches(entry, left, left_symbols);
                        let matches_right = precedence_entry_matches(entry, right, right_symbols);
                        if matches_left {
                            saw_left = true;
                            if saw_right {
                                return Some(Ordering::Less);
                            }
                        } else if matches_right {
                            saw_right = true;
                            if saw_left {
                                return Some(Ordering::Greater);
                            }
                        }
                    }
                    None
                })
                .unwrap_or(Ordering::Equal),
        }
    }

    fn get_production_id(&mut self, item: &ParseItem) -> ProductionInfoId {
        debug_assert_ne!(item.prod_id, START_PRODUCTION_ID);
        if let Some(id) = self.production_info_ids_by_prod_id[item.prod_id as usize] {
            return id;
        }
        let mut production_info = ProductionInfo {
            alias_sequence: Vec::new(),
            field_map: BTreeMap::new(),
        };

        for (i, step) in item
            .production(self.syntax_grammar)
            .steps
            .iter()
            .enumerate()
        {
            production_info.alias_sequence.push(step.alias());
            if let Some(field_name) = step.field() {
                production_info
                    .field_map
                    .entry(field_name)
                    .or_default()
                    .push(FieldLocation {
                        index: i as u32,
                        inherited: false,
                    });
            }

            if let Some(index) = step.non_terminal_index()
                && !self.syntax_grammar.variables[usize::from(index)]
                    .kind
                    .is_visible()
            {
                let info = &self.variable_info[usize::from(index)];
                for &field_name in info.fields.keys() {
                    production_info
                        .field_map
                        .entry(field_name)
                        .or_default()
                        .push(FieldLocation {
                            index: i as u32,
                            inherited: true,
                        });
                }
            }
        }

        while production_info.alias_sequence.last() == Some(&None) {
            production_info.alias_sequence.pop();
        }

        if item.production(self.syntax_grammar).steps.len()
            > self.parse_table.max_aliased_production_length
        {
            self.parse_table.max_aliased_production_length =
                item.production(self.syntax_grammar).steps.len();
        }

        let id = if let Some(index) = self
            .parse_table
            .production_infos
            .iter()
            .position(|seq| *seq == production_info)
        {
            index
        } else {
            self.parse_table.production_infos.push(production_info);
            self.parse_table.production_infos.len() - 1
        } as ProductionInfoId;
        self.production_info_ids_by_prod_id[item.prod_id as usize] = Some(id);
        id
    }

    fn symbol_name(&self, symbol: Symbol) -> Box<str> {
        match symbol.view() {
            SymbolView::End | SymbolView::EndOfNonTerminalExtra => "EOF".to_string(),
            SymbolView::External(index) => self
                .str_pool
                .resolve(self.syntax_grammar.external_tokens[usize::from(index)].name)
                .to_string(),
            SymbolView::NonTerminal(index) => self
                .str_pool
                .resolve(self.syntax_grammar.variables[usize::from(index)].name)
                .to_string(),
            SymbolView::Terminal(index) => {
                let variable = &self.lexical_grammar.variables[usize::from(index)];
                if variable.kind == VariableType::Named {
                    self.str_pool.resolve(variable.name).to_string()
                } else {
                    format!("'{}'", self.str_pool.resolve(variable.name))
                }
            }
        }
        .into()
    }
}

pub fn build_parse_table<'a>(
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    item_set_builder: ParseItemSetBuilder<'a>,
    variable_info: &'a [VariableInfo],
    str_pool: &'a StrPool,
    diagnostics: &mut Vec<Diagnostic>,
) -> BuildTableResult<(ParseTable<ParseTableEntry>, ParseStateInfo<'a>)> {
    ParseTableBuilder::new(
        syntax_grammar,
        lexical_grammar,
        item_set_builder,
        variable_info,
        str_pool,
    )
    .build(diagnostics)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{grammars::SyntaxVariable, strpool::StrPool};

    #[test]
    fn test_auxiliary_context_lookup() {
        //   source_file: $ => seq(repeat('x'), $.block),
        //   block: $ => seq('{', repeat('y'), '}', repeat('x')),
        let variable = |kind| SyntaxVariable {
            name: StrPool::EMPTY_STR_ID,
            kind,
        };
        let grammar = SyntaxGrammar {
            variables: vec![
                variable(VariableType::Named),
                variable(VariableType::Named),
                variable(VariableType::Auxiliary),
                variable(VariableType::Auxiliary),
            ],
            ..SyntaxGrammar::default()
        };
        let [source_file, block, x_repeat, y_repeat] = [0, 1, 2, 3].map(NonTerminalIndex::new);

        // The contexts of three states along one path through the grammar:
        //
        //   source_file: • repeat('x') block
        //   block: '{' • repeat('y') '}' repeat('x')
        //   block: '{' repeat('y') '}' • repeat('x')
        let mut contexts = AuxiliarySymbolContexts::default();
        let first = contexts.push(&grammar, None, vec![(x_repeat, source_file)]);
        let second = contexts.push(&grammar, first, vec![(y_repeat, block)]);
        let third = contexts.push(&grammar, second, vec![(x_repeat, block)]);

        // The nearest context has the symbol.
        assert_eq!(
            contexts.parents(second, y_repeat),
            Some(&[block.into()][..])
        );
        // Only a predecessor has it.
        assert_eq!(
            contexts.parents(second, x_repeat),
            Some(&[source_file.into()][..])
        );
        // A more recent entry hides an earlier one.
        assert_eq!(contexts.parents(third, x_repeat), Some(&[block.into()][..]));
        // Nothing along the path recorded it.
        assert_eq!(contexts.parents(first, y_repeat), None);
    }
}
