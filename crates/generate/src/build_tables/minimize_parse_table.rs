use std::{cmp::Ordering, mem};

use rustc_hash::{FxHashMap, FxHashSet};

use log::debug;

use super::token_conflicts::TokenConflictMap;
use crate::{
    OptLevel,
    dedup::split_state_id_groups,
    grammars::{LexicalGrammar, SyntaxGrammar, VariableType},
    rules::{AliasMap, Symbol, SymbolType, TokenSet},
    strpool::StrPool,
    tables::{GotoAction, ParseAction, ParseState, ParseStateId, ParseTable, ParseTableEntry},
};

/// Index into [`SyntaxGrammar::variables`]. All nonterminal [`Symbol`]s share
/// the same `kind`, so storing the index alone is sufficient for ordering.
type NonterminalIndex = u32;

/// A [`Symbol`] packed into a `u64` for O(1) sort-key comparison.
///
/// Layout: high 3 bits = `kind` discriminant (5 variants fit in 3 bits), low 61 bits = `index`.
/// This preserves [`Symbol`]'s derived [`Ord`] ordering (kind first, then index) as a single
/// integer comparison, and halves each entry's size vs storing a full `(Symbol, _)` tuple.
#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
struct SymbolKey(u64);

const KEY_TAG_SHIFT: u32 = 61;
const KEY_INDEX_MASK: u64 = (1u64 << KEY_TAG_SHIFT) - 1;

impl SymbolKey {
    #[inline]
    fn new(sym: Symbol) -> Self {
        debug_assert!(
            u64::from(sym.index) <= KEY_INDEX_MASK,
            "symbol index too large"
        );
        Self((sym.kind as u64) << KEY_TAG_SHIFT | u64::from(sym.index))
    }

    #[inline]
    const fn symbol(self) -> Symbol {
        let kind = match self.0 >> KEY_TAG_SHIFT {
            0 => SymbolType::External,
            1 => SymbolType::End,
            2 => SymbolType::EndOfNonTerminalExtra,
            3 => SymbolType::Terminal,
            _ => SymbolType::NonTerminal,
        };
        Symbol {
            kind,
            index: self.index(),
        }
    }

    #[inline]
    const fn index(self) -> u32 {
        (self.0 & KEY_INDEX_MASK) as u32
    }

    #[inline]
    #[expect(dead_code)]
    const fn is_terminal(self) -> bool {
        (self.0 >> KEY_TAG_SHIFT) == SymbolType::Terminal as u64
    }

    #[inline]
    #[expect(dead_code)]
    const fn is_non_terminal(self) -> bool {
        (self.0 >> KEY_TAG_SHIFT) == SymbolType::NonTerminal as u64
    }
}

#[expect(
    clippy::too_many_arguments,
    reason = "all parameters are required for parse table minimization"
)]
pub fn minimize_parse_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    token_conflict_map: &TokenConflictMap,
    keywords: &TokenSet,
    str_pool: &StrPool,
    optimizations: OptLevel,
) {
    let mut minimizer = Minimizer {
        parse_table,
        syntax_grammar,
        lexical_grammar,
        token_conflict_map,
        keywords,
        simple_aliases,
        str_pool,
    };
    if optimizations.contains(OptLevel::MergeStates) {
        minimizer.merge_compatible_states();
    }
    minimizer.remove_unit_reductions();
    minimizer.remove_unused_states();
    minimizer.reorder_states_by_descending_size();
}

/// Word-aligned bitsets precomputed for `token_conflicts`, all indexed by terminal
/// index. `state_terminals` and `conflict_rows` are flattened two dimensional vectors:
/// row `i` spans `[i * row_words, (i + 1) * row_words)`.
struct ConflictBits {
    row_words: usize,
    /// Per state: which terminals have entries
    state_terminals: Vec<u64>,
    /// Per token: which terminals it lexically conflicts with
    conflict_rows: Vec<u64>,
    /// The keyword set.
    keywords: Vec<u64>,
    /// Tokens that are also external tokens.
    internal_external: Vec<u64>,
}

impl ConflictBits {
    #[inline]
    fn get_conflict_row(&self, token: usize) -> &[u64] {
        let base = token * self.row_words;
        &self.conflict_rows[base..base + self.row_words]
    }

    #[inline]
    fn get_state_row(&self, state: usize) -> &[u64] {
        let base = state * self.row_words;
        &self.state_terminals[base..base + self.row_words]
    }
}

struct Minimizer<'a> {
    parse_table: &'a mut ParseTable,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    token_conflict_map: &'a TokenConflictMap,
    keywords: &'a TokenSet,
    simple_aliases: &'a AliasMap,
    str_pool: &'a StrPool,
}

impl Minimizer<'_> {
    fn remove_unit_reductions(&mut self) {
        let mut aliased_symbols = FxHashSet::default();
        for i in 0..self.syntax_grammar.variables.len() {
            for prod_id in self.syntax_grammar.variable_prod_ids(i) {
                for step in self.syntax_grammar.production(prod_id).steps {
                    if step.alias().is_some() {
                        aliased_symbols.insert(step.symbol());
                    }
                }
            }
        }

        let mut unit_reduction_symbols_by_state = FxHashMap::default();
        for (i, state) in self.parse_table.states.iter().enumerate() {
            let mut only_unit_reductions = true;
            let mut unit_reduction_symbol = None;
            for (_, entry) in &state.terminal_entries {
                for action in &entry.actions {
                    match action {
                        ParseAction::ShiftExtra => continue,
                        ParseAction::Reduce {
                            child_count: 1,
                            production_id: 0,
                            symbol,
                            ..
                        } if !self.simple_aliases.contains_key(symbol)
                            && !self.syntax_grammar.supertype_symbols.contains(symbol)
                            && !self.syntax_grammar.extra_symbols.contains(symbol)
                            && !aliased_symbols.contains(symbol)
                            && self.syntax_grammar.variables[symbol.index as usize].kind
                                != VariableType::Named
                            && (unit_reduction_symbol.is_none()
                                || unit_reduction_symbol == Some(symbol)) =>
                        {
                            unit_reduction_symbol = Some(symbol);
                            continue;
                        }
                        _ => {}
                    }
                    only_unit_reductions = false;
                    break;
                }

                if !only_unit_reductions {
                    break;
                }
            }

            if let Some(symbol) = unit_reduction_symbol
                && only_unit_reductions
            {
                unit_reduction_symbols_by_state.insert(i as u32, *symbol);
            }
        }

        for state in &mut self.parse_table.states {
            let mut done = false;
            while !done {
                done = true;
                state.update_referenced_states(|other_state_id, state| {
                    unit_reduction_symbols_by_state.get(&other_state_id).map_or(
                        other_state_id,
                        |symbol| {
                            done = false;
                            match state.nonterminal_entries.get(symbol) {
                                Some(GotoAction::Goto(state_id)) => *state_id,
                                _ => other_state_id,
                            }
                        },
                    )
                });
            }
        }
    }

    fn merge_compatible_states(&mut self) {
        let core_count = 1 + self
            .parse_table
            .states
            .iter()
            .map(|state| state.core_id)
            .max()
            .unwrap();

        // Initially group the states by their parse item set core.
        let mut group_ids_by_state_id = Vec::with_capacity(self.parse_table.states.len());
        // Pre-allocate for the maximum possible number of groups (one per state) to
        // avoid reallocs as split_state_id_groups pushes new groups.
        let mut state_ids_by_group_id = Vec::with_capacity(self.parse_table.states.len());
        state_ids_by_group_id.resize(core_count as usize, Vec::new());
        for (i, state) in self.parse_table.states.iter().enumerate() {
            state_ids_by_group_id[state.core_id as usize].push(i as u32);
            group_ids_by_state_id.push(state.core_id);
        }

        // Precompute sorted terminal entry references for merge-join in states_conflict.
        // entry_maps[state_id][i] = (symbol_key, &ParseTableEntry)
        // Keys are packed u64s (symbol_key) for single-instruction comparison.
        // Storing a reference avoids the IndexMap::get_index call in states_conflict.
        let entry_maps = self
            .parse_table
            .states
            .iter()
            .map(|state| {
                let mut entries = state
                    .terminal_entries
                    .iter()
                    .map(|(sym, entry)| (SymbolKey::new(*sym), entry))
                    .collect::<Vec<(SymbolKey, &ParseTableEntry)>>();
                entries.sort_unstable_by_key(|&(key, _)| key);
                entries
            })
            .collect::<Vec<_>>();

        // Precompute word-aligned bitsets so `token_conflicts` can test a candidate
        // token against a whole state's terminals.
        //   - per state: which terminal indices have entries
        //   - per token: which terminal indices it lexically conflicts with
        //   - the keyword set as bits
        let n_terminals = self.lexical_grammar.variables.len();
        let row_words = n_terminals.div_ceil(64);
        let set = |bits: &mut [u64], index: usize| bits[index / 64] |= 1 << (index % 64);

        let mut state_terminals = vec![0u64; self.parse_table.states.len() * row_words];
        for (s, state) in self.parse_table.states.iter().enumerate() {
            let base = s * row_words;
            let row = &mut state_terminals[base..base + row_words];
            for symbol in state.terminal_entries.keys() {
                if symbol.is_terminal() {
                    set(row, symbol.index as usize);
                }
            }
        }

        let mut conflict_rows = vec![0u64; n_terminals * row_words];
        for i in 0..n_terminals {
            let base = i * row_words;
            let row = &mut conflict_rows[base..base + row_words];
            for j in 0..n_terminals {
                if self.token_conflict_map.does_conflict(i, j) {
                    set(row, j);
                }
            }
        }

        let mut keywords = vec![0u64; row_words];
        for symbol in self.keywords.iter() {
            if symbol.is_terminal() {
                set(&mut keywords, symbol.index as usize);
            }
        }

        let mut internal_external = vec![0u64; row_words];
        for external in &self.syntax_grammar.external_tokens {
            if let Some(token) = external.corresponding_internal_token {
                set(&mut internal_external, token.index as usize);
            }
        }

        let bits = ConflictBits {
            row_words,
            state_terminals,
            conflict_rows,
            keywords,
            internal_external,
        };

        split_state_id_groups(
            &self.parse_table.states,
            &mut state_ids_by_group_id,
            &mut group_ids_by_state_id,
            0,
            |left, right, groups| self.states_conflict(left, right, groups, &entry_maps, &bits),
        );

        // Precompute per-state sorted shift actions and nonterminal goto actions.
        // State actions are stable across loop iterations; only group assignments change.
        // Keys are packed u64s (symbol_key) for single-instruction comparison.
        let shift_maps = self
            .parse_table
            .states
            .iter()
            .map(|state| {
                let mut shifts = state
                    .terminal_entries
                    .iter()
                    .filter_map(|(sym, entry)| {
                        let action = entry.actions.last()?;
                        if let ParseAction::Shift { state: s, .. } = action {
                            Some((SymbolKey::new(*sym), *s))
                        } else {
                            None
                        }
                    })
                    .collect::<Vec<(SymbolKey, ParseStateId)>>();
                shifts.sort_unstable_by_key(|&(key, _)| key);
                shifts
            })
            .collect::<Vec<_>>();

        // Store only the symbol index: all nonterminal entries share the same kind,
        // so index alone is sufficient for sorting and comparison.
        let nonterminal_maps = self
            .parse_table
            .states
            .iter()
            .map(|state| {
                let mut entries = state
                    .nonterminal_entries
                    .iter()
                    .map(|(sym, action)| (sym.index, *action))
                    .collect::<Vec<(NonterminalIndex, GotoAction)>>();
                entries.sort_unstable_by_key(|&(idx, _)| idx);
                entries
            })
            .collect::<Vec<_>>();

        while split_state_id_groups(
            &self.parse_table.states,
            &mut state_ids_by_group_id,
            &mut group_ids_by_state_id,
            0,
            |left, right, groups| {
                self.state_successors_differ(left, right, groups, &shift_maps, &nonterminal_maps)
            },
        ) {}

        let error_group_index = state_ids_by_group_id
            .iter()
            .position(|g| g.contains(&0))
            .unwrap();
        let start_group_index = state_ids_by_group_id
            .iter()
            .position(|g| g.contains(&1))
            .unwrap();
        state_ids_by_group_id.swap(error_group_index, 0);
        state_ids_by_group_id.swap(start_group_index, 1);

        // Create a list of new parse states: one state for each group of old states.
        let mut new_states = Vec::with_capacity(state_ids_by_group_id.len());
        for state_ids in &state_ids_by_group_id {
            // Initialize the new state based on the first old state in the group.
            let mut parse_state = mem::take(&mut self.parse_table.states[state_ids[0] as usize]);

            // Extend the new state with all of the actions from the other old states
            // in the group.
            for state_id in &state_ids[1..] {
                let other_parse_state = mem::take(&mut self.parse_table.states[*state_id as usize]);

                parse_state
                    .terminal_entries
                    .extend(other_parse_state.terminal_entries);
                parse_state
                    .nonterminal_entries
                    .extend(other_parse_state.nonterminal_entries);
                parse_state
                    .reserved_words
                    .insert_all(&other_parse_state.reserved_words);
                for &symbol in parse_state.terminal_entries.keys() {
                    parse_state.reserved_words.remove(symbol);
                }
            }

            // Update the new state's outgoing references using the new grouping.
            parse_state
                .update_referenced_states(|state_id, _| group_ids_by_state_id[state_id as usize]);
            new_states.push(parse_state);
        }

        self.parse_table.states = new_states;
    }

    fn states_conflict(
        &self,
        state1: &ParseState,
        state2: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
        entry_maps: &[Vec<(SymbolKey, &ParseTableEntry)>],
        bits: &ConflictBits,
    ) -> bool {
        let entries1 = &entry_maps[state1.id as usize];
        let entries2 = &entry_maps[state2.id as usize];
        let len1 = entries1.len();
        let len2 = entries2.len();
        let mut i = 0;
        let mut j = 0;
        while i < len1 || j < len2 {
            // SAFETY: each branch only accesses entries1[i] when i < len1
            // and entries2[j] when j < len2, both of which hold by construction.
            let ord = if i < len1 && j < len2 {
                unsafe { entries1.get_unchecked(i) }
                    .0
                    .cmp(&unsafe { entries2.get_unchecked(j) }.0)
            } else if i < len1 {
                Ordering::Less
            } else {
                Ordering::Greater
            };
            match ord {
                Ordering::Equal => {
                    // SAFETY: Equal is only reachable when i < len1 && j < len2.
                    let e1 = unsafe { entries1.get_unchecked(i) };
                    let e2 = unsafe { entries2.get_unchecked(j) };
                    let token = e1.0.symbol();
                    if self.entries_conflict(
                        state1.id,
                        state2.id,
                        token,
                        e1.1,
                        e2.1,
                        group_ids_by_state_id,
                    ) {
                        return true;
                    }
                    i += 1;
                    j += 1;
                }
                Ordering::Less => {
                    // SAFETY: Less is only reachable when i < len1.
                    let e1 = unsafe { entries1.get_unchecked(i) };
                    let token = e1.0.symbol();
                    if self.token_conflicts(state1.id, state2.id, state2, bits, token) {
                        return true;
                    }
                    i += 1;
                }
                Ordering::Greater => {
                    // SAFETY: Greater is only reachable when j < len2.
                    let e2 = unsafe { entries2.get_unchecked(j) };
                    let token = e2.0.symbol();
                    if self.token_conflicts(state1.id, state2.id, state1, bits, token) {
                        return true;
                    }
                    j += 1;
                }
            }
        }
        false
    }

    fn state_successors_differ(
        &self,
        state1: &ParseState,
        state2: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
        shift_maps: &[Vec<(SymbolKey, ParseStateId)>],
        nonterminal_maps: &[Vec<(NonterminalIndex, GotoAction)>],
    ) -> bool {
        let shifts1 = &shift_maps[state1.id as usize];
        let shifts2 = &shift_maps[state2.id as usize];
        let mut i = 0;
        let mut j = 0;
        while i < shifts1.len() && j < shifts2.len() {
            // SAFETY: loop condition ensures i < shifts1.len() and j < shifts2.len().
            let (k1, s1) = *unsafe { shifts1.get_unchecked(i) };
            let (k2, s2) = *unsafe { shifts2.get_unchecked(j) };
            match k1.cmp(&k2) {
                Ordering::Less => i += 1,
                Ordering::Greater => j += 1,
                Ordering::Equal => {
                    let group1 = group_ids_by_state_id[s1 as usize];
                    let group2 = group_ids_by_state_id[s2 as usize];
                    if group1 != group2 {
                        debug!(
                            "split states {} {} - successors for {} are split: {s1} {s2}",
                            state1.id,
                            state2.id,
                            self.symbol_name(k1.symbol()),
                        );
                        return true;
                    }
                    i += 1;
                    j += 1;
                }
            }
        }

        let nonterms1 = &nonterminal_maps[state1.id as usize];
        let nonterms2 = &nonterminal_maps[state2.id as usize];
        let mut i = 0;
        let mut j = 0;
        while i < nonterms1.len() && j < nonterms2.len() {
            // SAFETY: loop condition ensures i < nonterms1.len() and j < nonterms2.len().
            let (idx1, s1) = *unsafe { nonterms1.get_unchecked(i) };
            let (idx2, s2) = *unsafe { nonterms2.get_unchecked(j) };
            match idx1.cmp(&idx2) {
                Ordering::Less => i += 1,
                Ordering::Greater => j += 1,
                Ordering::Equal => {
                    match (s1, s2) {
                        (GotoAction::ShiftExtra, GotoAction::ShiftExtra) => {}
                        (GotoAction::Goto(s1), GotoAction::Goto(s2)) => {
                            let group1 = group_ids_by_state_id[s1 as usize];
                            let group2 = group_ids_by_state_id[s2 as usize];
                            if group1 != group2 {
                                debug!(
                                    "split states {} {} - successors for {} are split: {s1} {s2}",
                                    state1.id,
                                    state2.id,
                                    self.str_pool
                                        .resolve(self.syntax_grammar.variables[idx1 as usize].name),
                                );
                                return true;
                            }
                        }
                        _ => return true,
                    }
                    i += 1;
                    j += 1;
                }
            }
        }

        false
    }

    fn entries_conflict(
        &self,
        state_id1: ParseStateId,
        state_id2: ParseStateId,
        token: Symbol,
        entry1: &ParseTableEntry,
        entry2: &ParseTableEntry,
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        // To be compatible, entries need to have the same actions.
        let actions1 = &entry1.actions;
        let actions2 = &entry2.actions;
        if actions1.len() != actions2.len() {
            debug!(
                "split states {state_id1} {state_id2} - differing action counts for token {}",
                self.symbol_name(token)
            );
            return true;
        }

        for (action1, action2) in actions1.iter().zip(actions2.iter()) {
            // Two shift actions are equivalent if their destinations are in the same group.
            if let (
                ParseAction::Shift {
                    state: s1,
                    is_repetition: is_repetition1,
                },
                ParseAction::Shift {
                    state: s2,
                    is_repetition: is_repetition2,
                },
            ) = (action1, action2)
            {
                let group1 = group_ids_by_state_id[*s1 as usize];
                let group2 = group_ids_by_state_id[*s2 as usize];
                if group1 == group2 && is_repetition1 == is_repetition2 {
                    continue;
                }
                debug!(
                    "split states {state_id1} {state_id2} - successors for {} are split: {s1} {s2}",
                    self.symbol_name(token),
                );
                return true;
            } else if action1 != action2 {
                debug!(
                    "split states {state_id1} {state_id2} - unequal actions for {}",
                    self.symbol_name(token),
                );
                return true;
            }
        }

        false
    }

    #[inline]
    fn token_conflicts(
        &self,
        left_id: ParseStateId,
        right_id: ParseStateId,
        right_state: &ParseState,
        bits: &ConflictBits,
        new_token: Symbol,
    ) -> bool {
        if new_token == Symbol::end_of_nonterminal_extra() {
            debug!("split states {left_id} {right_id} - end of non-terminal extra");
            return true;
        }

        // Do not add external tokens; they could conflict lexically with any of the state's
        // existing lookahead tokens.
        if new_token.is_external() {
            debug!(
                "split states {left_id} {right_id} - external token {}",
                self.symbol_name(new_token),
            );
            return true;
        }

        if right_state.reserved_words.contains(new_token) {
            return false;
        }

        // Do not add tokens which are both internal and external. Their validity could
        // influence the behavior of the external scanner. `bits.internal_external` is
        // indexed by terminal index only, so gate on the kind
        if new_token.is_terminal()
            && bits.internal_external[new_token.index as usize / 64]
                & (1 << (new_token.index as usize % 64))
                != 0
        {
            debug!(
                "split states {left_id} {right_id} - internal/external token {}",
                self.symbol_name(new_token),
            );
            return true;
        }

        let word_token = self.syntax_grammar.word_token;
        let new_token_is_word = word_token == Some(new_token);
        let new_token_is_keyword = word_token.is_some() && self.keywords.contains(new_token);
        // Do not add a token if it conflicts with an existing token. Test the candidate's
        // conflict row against the state's terminal bits, masking out the word/keyword
        // exemptions.
        let row = bits.get_conflict_row(new_token.index as usize);
        let right_terminal_bits = bits.get_state_row(right_state.id as usize);
        for (w, &row_word) in row.iter().enumerate() {
            let mut candidates = right_terminal_bits[w] & row_word;
            if new_token_is_keyword
                && let Some(word) = word_token
                && word.index as usize / 64 == w
            {
                candidates &= !(1u64 << (word.index as usize % 64));
            }
            if new_token_is_word {
                candidates &= !bits.keywords[w];
            }
            if candidates != 0 {
                debug!(
                    "split states {} {} - token {} conflicts with {}",
                    left_id,
                    right_id,
                    self.symbol_name(new_token),
                    self.symbol_name(Symbol::terminal(
                        w * 64 + candidates.trailing_zeros() as usize
                    )),
                );
                return true;
            }
        }

        false
    }

    fn symbol_name(&self, symbol: Symbol) -> &str {
        let symbol_index = symbol.index as usize;
        if symbol.is_non_terminal() {
            self.str_pool
                .resolve(self.syntax_grammar.variables[symbol_index].name)
        } else if symbol.is_external() {
            self.str_pool
                .resolve(self.syntax_grammar.external_tokens[symbol_index].name)
        } else {
            self.str_pool
                .resolve(self.lexical_grammar.variables[symbol_index].name)
        }
    }

    fn remove_unused_states(&mut self) {
        let mut state_usage_map = vec![false; self.parse_table.states.len()];

        state_usage_map[0] = true;
        state_usage_map[1] = true;

        for state in &self.parse_table.states {
            for referenced_state in state.referenced_states() {
                state_usage_map[referenced_state as usize] = true;
            }
        }
        let mut removed_predecessor_count = 0;
        let mut state_replacement_map = vec![0; self.parse_table.states.len()];
        for state_id in 0..self.parse_table.states.len() {
            state_replacement_map[state_id] = (state_id - removed_predecessor_count) as u32;
            if !state_usage_map[state_id] {
                removed_predecessor_count += 1;
            }
        }
        let mut state_id = 0;
        let mut original_state_id = 0;
        while state_id < self.parse_table.states.len() {
            if state_usage_map[original_state_id] {
                self.parse_table.states[state_id].update_referenced_states(|other_state_id, _| {
                    state_replacement_map[other_state_id as usize]
                });
                state_id += 1;
            } else {
                self.parse_table.states.remove(state_id);
            }
            original_state_id += 1;
        }
    }

    fn reorder_states_by_descending_size(&mut self) {
        // Get a mapping of old state index -> new_state_index
        let mut old_ids_by_new_id = (0..self.parse_table.states.len()).collect::<Vec<_>>();
        old_ids_by_new_id.sort_unstable_by_key(|i| {
            // Don't change states 0 (the error state) or 1 (the start state).
            if *i <= 1 {
                return *i as i64 - 1_000_000;
            }

            // Reorder all the other states by descending symbol count.
            let state = &self.parse_table.states[*i];
            -((state.terminal_entries.len() + state.nonterminal_entries.len()) as i64)
        });

        // Get the inverse mapping
        let mut new_ids_by_old_id = vec![0; old_ids_by_new_id.len()];
        for (id, old_id) in old_ids_by_new_id.iter().enumerate() {
            new_ids_by_old_id[*old_id] = id as u32;
        }

        // Reorder the parse states and update their references to reflect
        // the new ordering.
        self.parse_table.states = old_ids_by_new_id
            .iter()
            .map(|old_id| {
                let mut state = ParseState::default();
                mem::swap(&mut state, &mut self.parse_table.states[*old_id]);
                state.update_referenced_states(|id, _| new_ids_by_old_id[id as usize]);
                state
            })
            .collect();
    }
}
