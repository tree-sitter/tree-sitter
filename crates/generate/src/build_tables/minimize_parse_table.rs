use std::{cmp::Ordering, mem};

use rustc_hash::{FxHashMap, FxHashSet};

use log::debug;

use super::token_conflicts::TokenConflictMap;
use crate::{
    OptLevel,
    dedup::split_state_id_groups,
    grammars::{LexicalGrammar, SyntaxGrammar, VariableType},
    rules::{AliasMap, Symbol, SymbolType, TokenSet},
    tables::{GotoAction, ParseAction, ParseState, ParseStateId, ParseTable, ParseTableEntry},
};

/// Index into [`SyntaxGrammar::variables`]. All nonterminal [`Symbol`]s share
/// the same `kind`, so storing the index alone is sufficient for ordering.
type NonterminalIndex = usize;

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
        debug_assert!(sym.index as u64 <= KEY_INDEX_MASK, "symbol index too large");
        Self((sym.kind as u64) << KEY_TAG_SHIFT | sym.index as u64)
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
    const fn index(self) -> usize {
        (self.0 & KEY_INDEX_MASK) as usize
    }

    #[inline]
    const fn is_terminal(self) -> bool {
        (self.0 >> KEY_TAG_SHIFT) == SymbolType::Terminal as u64
    }

    #[expect(dead_code)]
    #[inline]
    const fn is_non_terminal(self) -> bool {
        (self.0 >> KEY_TAG_SHIFT) == SymbolType::NonTerminal as u64
    }
}

pub fn minimize_parse_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    token_conflict_map: &TokenConflictMap,
    keywords: &TokenSet,
    optimizations: OptLevel,
) {
    let mut minimizer = Minimizer {
        parse_table,
        syntax_grammar,
        lexical_grammar,
        token_conflict_map,
        keywords,
        simple_aliases,
    };
    if optimizations.contains(OptLevel::MergeStates) {
        minimizer.merge_compatible_states();
    }
    minimizer.remove_unit_reductions();
    minimizer.remove_unused_states();
    minimizer.reorder_states_by_descending_size();
}

struct Minimizer<'a> {
    parse_table: &'a mut ParseTable,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    token_conflict_map: &'a TokenConflictMap<'a>,
    keywords: &'a TokenSet,
    simple_aliases: &'a AliasMap,
}

impl Minimizer<'_> {
    fn remove_unit_reductions(&mut self) {
        let mut aliased_symbols = FxHashSet::default();
        for variable in &self.syntax_grammar.variables {
            for production in &variable.productions {
                for step in &production.steps {
                    if step.alias.is_some() {
                        aliased_symbols.insert(step.symbol);
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
                            && self.syntax_grammar.variables[symbol.index].kind
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
                unit_reduction_symbols_by_state.insert(i, *symbol);
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
        state_ids_by_group_id.resize(core_count, Vec::new());
        for (i, state) in self.parse_table.states.iter().enumerate() {
            state_ids_by_group_id[state.core_id].push(i);
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

        split_state_id_groups(
            &self.parse_table.states,
            &mut state_ids_by_group_id,
            &mut group_ids_by_state_id,
            0,
            |left, right, groups| self.states_conflict(left, right, groups, &entry_maps),
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
            let mut parse_state = mem::take(&mut self.parse_table.states[state_ids[0]]);

            // Extend the new state with all of the actions from the other old states
            // in the group.
            for state_id in &state_ids[1..] {
                let other_parse_state = mem::take(&mut self.parse_table.states[*state_id]);

                parse_state
                    .terminal_entries
                    .extend(other_parse_state.terminal_entries);
                parse_state
                    .nonterminal_entries
                    .extend(other_parse_state.nonterminal_entries);
                parse_state
                    .reserved_words
                    .insert_all(&other_parse_state.reserved_words);
                for symbol in parse_state.terminal_entries.keys() {
                    parse_state.reserved_words.remove(symbol);
                }
            }

            // Update the new state's outgoing references using the new grouping.
            parse_state.update_referenced_states(|state_id, _| group_ids_by_state_id[state_id]);
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
    ) -> bool {
        let entries1 = &entry_maps[state1.id];
        let entries2 = &entry_maps[state2.id];
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
                        &token,
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
                    if self.token_conflicts(state1.id, state2.id, state2, entries2, token) {
                        return true;
                    }
                    i += 1;
                }
                Ordering::Greater => {
                    // SAFETY: Greater is only reachable when j < len2.
                    let e2 = unsafe { entries2.get_unchecked(j) };
                    let token = e2.0.symbol();
                    if self.token_conflicts(state1.id, state2.id, state1, entries1, token) {
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
        nonterminal_maps: &[Vec<(usize, GotoAction)>],
    ) -> bool {
        let shifts1 = &shift_maps[state1.id];
        let shifts2 = &shift_maps[state2.id];
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
                    let group1 = group_ids_by_state_id[s1];
                    let group2 = group_ids_by_state_id[s2];
                    if group1 != group2 {
                        debug!(
                            "split states {} {} - successors for {} are split: {s1} {s2}",
                            state1.id,
                            state2.id,
                            self.symbol_name(&k1.symbol()),
                        );
                        return true;
                    }
                    i += 1;
                    j += 1;
                }
            }
        }

        let nonterms1 = &nonterminal_maps[state1.id];
        let nonterms2 = &nonterminal_maps[state2.id];
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
                            let group1 = group_ids_by_state_id[s1];
                            let group2 = group_ids_by_state_id[s2];
                            if group1 != group2 {
                                debug!(
                                    "split states {} {} - successors for {} are split: {s1} {s2}",
                                    state1.id, state2.id, self.syntax_grammar.variables[idx1].name,
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
        token: &Symbol,
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
                let group1 = group_ids_by_state_id[*s1];
                let group2 = group_ids_by_state_id[*s2];
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
        right_entry_map: &[(SymbolKey, &ParseTableEntry)],
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
                self.symbol_name(&new_token),
            );
            return true;
        }

        if right_state.reserved_words.contains(&new_token) {
            return false;
        }

        // Do not add tokens which are both internal and external. Their validity could
        // influence the behavior of the external scanner.
        if self
            .syntax_grammar
            .external_tokens
            .iter()
            .any(|external| external.corresponding_internal_token == Some(new_token))
        {
            debug!(
                "split states {left_id} {right_id} - internal/external token {}",
                self.symbol_name(&new_token),
            );
            return true;
        }

        // Hoist loop-invariant word-token comparisons.
        let word_token = self.syntax_grammar.word_token;
        let word_key = word_token.map(SymbolKey::new);
        let new_token_key = SymbolKey::new(new_token);
        let new_token_is_word = word_key == Some(new_token_key);
        let new_token_is_keyword = word_token.is_some() && self.keywords.contains(&new_token);

        // Do not add a token if it conflicts with an existing token.
        // Iterate the pre-sorted Vec instead of IndexMap keys for cache-friendlier access.
        for &(key, _) in right_entry_map {
            if !key.is_terminal() {
                continue;
            }
            if new_token_is_keyword && word_key == Some(key) {
                continue;
            }
            if new_token_is_word && self.keywords.contains(&key.symbol()) {
                continue;
            }

            if self
                .token_conflict_map
                .does_conflict(new_token.index, key.index())
            {
                debug!(
                    "split states {} {} - token {} conflicts with {}",
                    left_id,
                    right_id,
                    self.symbol_name(&new_token),
                    self.symbol_name(&key.symbol()),
                );
                return true;
            }
        }

        false
    }

    fn symbol_name(&self, symbol: &Symbol) -> &String {
        if symbol.is_non_terminal() {
            &self.syntax_grammar.variables[symbol.index].name
        } else if symbol.is_external() {
            &self.syntax_grammar.external_tokens[symbol.index].name
        } else {
            &self.lexical_grammar.variables[symbol.index].name
        }
    }

    fn remove_unused_states(&mut self) {
        let mut state_usage_map = vec![false; self.parse_table.states.len()];

        state_usage_map[0] = true;
        state_usage_map[1] = true;

        for state in &self.parse_table.states {
            for referenced_state in state.referenced_states() {
                state_usage_map[referenced_state] = true;
            }
        }
        let mut removed_predecessor_count = 0;
        let mut state_replacement_map = vec![0; self.parse_table.states.len()];
        for state_id in 0..self.parse_table.states.len() {
            state_replacement_map[state_id] = state_id - removed_predecessor_count;
            if !state_usage_map[state_id] {
                removed_predecessor_count += 1;
            }
        }
        let mut state_id = 0;
        let mut original_state_id = 0;
        while state_id < self.parse_table.states.len() {
            if state_usage_map[original_state_id] {
                self.parse_table.states[state_id].update_referenced_states(|other_state_id, _| {
                    state_replacement_map[other_state_id]
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
            new_ids_by_old_id[*old_id] = id;
        }

        // Reorder the parse states and update their references to reflect
        // the new ordering.
        self.parse_table.states = old_ids_by_new_id
            .iter()
            .map(|old_id| {
                let mut state = ParseState::default();
                mem::swap(&mut state, &mut self.parse_table.states[*old_id]);
                state.update_referenced_states(|id, _| new_ids_by_old_id[id]);
                state
            })
            .collect();
    }
}
