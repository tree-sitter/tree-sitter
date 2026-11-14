use std::{
    cmp::Ordering,
    hash::{BuildHasher as _, Hash, Hasher},
    mem,
};

use hashbrown::HashTable;
use log::{Level, debug, log_enabled};
use rustc_hash::{FxBuildHasher, FxHashMap, FxHashSet, FxHasher};

use super::{SymbolIndexer, token_conflicts::TokenConflictMap};
use crate::{
    OptLevel,
    grammars::{LexicalGrammar, SyntaxGrammar, VariableType},
    rules::{AliasMap, Symbol, SymbolView, TokenSet},
    strpool::StrPool,
    tables::{
        ActionList, ActionListId, GotoAction, ParseAction, ParseState, ParseStateEntries,
        ParseStateId, ParseTable,
    },
};

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
        indexer: SymbolIndexer::new(syntax_grammar, lexical_grammar),
        token_conflict_map,
        keywords,
        has_reserved_words: syntax_grammar
            .reserved_word_sets
            .iter()
            .any(|set| !set.is_empty()),
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

/// The id of a set in [`TokenSets`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
struct TokenSetId(u32);

/// Sets of tokens, as bitsets by [`SymbolIndexer::index`]. Each distinct set is stored once, under
/// an id.
struct TokenSets {
    /// How many `u64`s each set has.
    words: u32,
    /// The distinct sets, `words` each, by id.
    sets: Vec<u64>,
    /// The ids of the sets in `sets`.
    set_ids: HashTable<TokenSetId>,
}

impl TokenSets {
    const fn new(words: u32) -> Self {
        Self {
            words,
            sets: Vec::new(),
            set_ids: HashTable::new(),
        }
    }

    /// The set with id `id` in `sets`, whose sets have `words` words each.
    fn slice(sets: &[u64], words: u32, id: TokenSetId) -> &[u64] {
        let start = id.0 as usize * words as usize;
        &sets[start..start + words as usize]
    }

    /// The set with id `id`.
    fn get(&self, id: TokenSetId) -> &[u64] {
        Self::slice(&self.sets, self.words, id)
    }

    /// Whether the set with id `id` has the token at `position`.
    fn contains(&self, id: TokenSetId, position: usize) -> bool {
        Self::has_bit(self.get(id), position)
    }

    /// The id of `set`, adding it if it's new.
    fn intern(&mut self, set: &[u64]) -> TokenSetId {
        let hash = FxBuildHasher.hash_one(set);
        if let Some(&id) = self.set_ids.find(hash, |&id| self.get(id) == set) {
            return id;
        }
        let id = TokenSetId((self.sets.len() / self.words as usize) as u32);
        self.sets.extend_from_slice(set);
        self.set_ids.insert_unique(hash, id, |&id| {
            FxBuildHasher.hash_one(Self::slice(&self.sets, self.words, id))
        });
        id
    }

    /// The id of `set`, which started out as the set with id `id`: `id` itself if it hasn't
    /// changed.
    fn reintern(&mut self, id: TokenSetId, set: &[u64]) -> TokenSetId {
        if self.get(id) == set {
            id
        } else {
            self.intern(set)
        }
    }

    const fn set_bit(bits: &mut [u64], index: usize) {
        bits[index / 64] |= 1 << (index % 64);
    }

    const fn has_bit(bits: &[u64], index: usize) -> bool {
        bits[index / 64] & (1 << (index % 64)) != 0
    }

    /// Whether `set` is a subset of `superset`.
    fn is_subset(set: &[u64], superset: &[u64]) -> bool {
        set.iter()
            .zip(superset)
            .all(|(word, super_word)| word & !super_word == 0)
    }
}

/// The tokens that can be added to each state, as bitsets by [`SymbolIndexer::index`].
///
/// A token can be added to a state unless:
/// - it's an [external token](SymbolView::External), which changes what the external scanner is
///   told is valid, or [`Symbol::EndOfNonTerminalExtra`], which stops the state from lexing.
/// - it's [both internal and external][internal-external]: having it tells the external scanner
///   that its external twin is valid.
/// - it conflicts lexically with one of the state's [terminals](SymbolView::Terminal). A
///   [keyword](Minimizer::keywords) doesn't conflict with the [word
///   token](SyntaxGrammar::word_token), nor the word token with a keyword. [`Symbol::End`] is
///   checked with the conflicts of terminal 0.
///
/// None of these apply to a token the state already has, and the last doesn't apply to a token
/// the state [reserves](ParseState::reserved_words).
///
/// [internal-external]: crate::grammars::ExternalToken::corresponding_internal_token
struct TakeableTokens {
    /// How many `u64`s each set has.
    words: u32,
    /// The tokens blocked in every state, whatever its terminals, even where it reserves them: the
    /// external tokens, [`Symbol::EndOfNonTerminalExtra`], and the tokens that are both internal
    /// and external.
    unconditional: Vec<u64>,
    /// By terminal index: the tokens that can't be added to a state with that terminal.
    blocked_by_terminal: Vec<u64>,
}

impl TakeableTokens {
    fn new(minimizer: &Minimizer) -> Self {
        let indexer = minimizer.indexer;
        let words = (indexer.token_count() as usize).div_ceil(64);
        let n_terminals = minimizer.lexical_grammar.variables.len();
        let word_token = minimizer
            .syntax_grammar
            .word_token
            .and_then(Symbol::terminal_index)
            .map(usize::from);
        let is_keyword = |index: usize| minimizer.keywords.contains(Symbol::terminal(index));
        // Whether a keyword is checked against the word token, or the word token against a
        // keyword. Their conflicts are expected and handled by keyword extraction.
        let is_keyword_pair = |new: usize, existing: usize| {
            word_token.is_some_and(|word| {
                (existing == word && is_keyword(new)) || (new == word && is_keyword(existing))
            })
        };

        let mut blocked_by_terminal = vec![0; n_terminals * words];
        for (existing, row) in blocked_by_terminal.chunks_exact_mut(words).enumerate() {
            for new in 0..n_terminals {
                if minimizer.token_conflict_map.does_conflict(new, existing)
                    && !is_keyword_pair(new, existing)
                {
                    TokenSets::set_bit(row, indexer.index(Symbol::terminal(new)));
                }
            }
            // TODO: During the 0.29 release cycle, once no token can match the end of input (see
            // `ADVANCE_MAP` in `render.rs`), `End` conflicts with nothing: remove this check and
            // its mention in `TakeableTokens`'s doc comment.
            if minimizer.token_conflict_map.does_conflict(0, existing) {
                TokenSets::set_bit(row, indexer.index(Symbol::End));
            }
        }

        // The external tokens take the first positions (see `SymbolIndexer`), so their bits are
        // the low `external_count` bits.
        let external_count = minimizer.syntax_grammar.external_tokens.len();
        debug_assert_eq!(indexer.index(Symbol::End), external_count);
        let mut unconditional = vec![0; words];
        unconditional[..external_count / 64].fill(u64::MAX);
        if !external_count.is_multiple_of(64) {
            unconditional[external_count / 64] |= (1 << (external_count % 64)) - 1;
        }
        TokenSets::set_bit(
            &mut unconditional,
            indexer.index(Symbol::EndOfNonTerminalExtra),
        );
        for external in &minimizer.syntax_grammar.external_tokens {
            if let Some(internal) = external
                .corresponding_internal_token
                .filter(|token| token.terminal_index().is_some())
            {
                TokenSets::set_bit(&mut unconditional, indexer.index(internal));
            }
        }

        Self {
            words: words as u32,
            unconditional,
            blocked_by_terminal,
        }
    }

    /// Writes the tokens that can be added to `state`, or that it has, to `set`.
    fn compute(&self, minimizer: &Minimizer, state: &ParseState, set: &mut [u64]) {
        let indexer = minimizer.indexer;
        let words = self.words as usize;
        // Collect the tokens that can't be added, then flip.
        set.copy_from_slice(&self.unconditional);
        for index in state
            .terminal_entries
            .iter()
            .filter_map(|(sym, _)| sym.terminal_index().map(usize::from))
        {
            let start = index * words;
            let row = &self.blocked_by_terminal[start..start + words];
            for (word, blocked) in set.iter_mut().zip(row) {
                *word |= blocked;
            }
        }
        for symbol in state.reserved_words.iter() {
            let position = indexer.index(symbol);
            if !TokenSets::has_bit(&self.unconditional, position) {
                set[position / 64] &= !(1 << (position % 64));
            }
        }
        for word in set.iter_mut() {
            *word = !*word;
        }
        for (symbol, _) in state.terminal_entries.iter() {
            TokenSets::set_bit(set, indexer.index(*symbol));
        }
        // Clear the bits past the last token.
        let token_count = indexer.token_count() as usize;
        if !token_count.is_multiple_of(64) {
            set[words - 1] &= (1 << (token_count % 64)) - 1;
        }
    }

    /// Why `token` can't be added to a group whose terminal entries are `entries`, for logging.
    fn conflict(
        &self,
        minimizer: &Minimizer,
        token: Symbol,
        entries: &[(Symbol, ActionListId)],
    ) -> Conflict {
        let position = minimizer.indexer.index(token);
        match token.view() {
            SymbolView::EndOfNonTerminalExtra => return Conflict::EndOfNonTerminalExtra,
            SymbolView::External(_) => return Conflict::ExternalToken,
            _ if TokenSets::has_bit(&self.unconditional, position) => {
                return Conflict::InternalExternalToken;
            }
            _ => {}
        }
        let words = self.words as usize;
        entries
            .iter()
            .filter_map(|(symbol, _)| symbol.terminal_index().map(usize::from))
            .find(|&index| {
                TokenSets::has_bit(
                    &self.blocked_by_terminal[index * words..(index + 1) * words],
                    position,
                )
            })
            .map_or(Conflict::Untakeable, Conflict::Lexical)
    }
}

/// A group's reserved and allowed words, as sets in [`TokenSets`]. See
/// [`StateMerger::reserved_ids`].
#[derive(Clone, Copy)]
struct WordSetIds {
    /// The words that some state of the group reserves without having an entry for them.
    reserved: TokenSetId,
    /// The words that each state accepting the word token reserves or has an entry for. A state
    /// that doesn't accept it allows every word.
    allowed: TokenSetId,
}

/// Merges compatible states, bottom-up.
///
/// Each state starts in a group of its own. For each core in turn, each of its groups is merged
/// into the first earlier group of that core it's compatible with. Merging two groups also
/// merges the groups that they shift or go to on each symbol they share, recursively, so a merge
/// only happens if all of those pairs are compatible too.
///
/// Two groups are compatible if they:
/// - agree on each token they share (apart from shift targets)
/// - can each take the tokens that only the other has
/// - don't reserve a word that the other accepts as an identifier (see
///   [`StateMerger::reserved_ids`]).
struct StateMerger<'m, 'a> {
    minimizer: &'m Minimizer<'a>,
    /// The parse table's states, taken out of it while merging. A root's entries are its
    /// group's: the entries of all of its states, sorted by symbol. A state whose group has
    /// merged into another has no entries left.
    ///
    /// Where several of a group's states have an entry for a symbol, the group keeps the one
    /// that was already in the root's list. The others can only differ in the states they shift
    /// or go to, which have been merged into the same groups, so they all become the same entry
    /// once [`Minimizer::merge_compatible_states`] replaces states with groups. Their `reusable`
    /// flags can't differ either, as `mark_fragile_tokens` only clears them after minimization.
    states: &'m mut Vec<ParseState>,
    /// Each state's parent in its group, by state id. A group's root is its own parent, and is
    /// the group's lowest state.
    parents: Vec<ParseStateId>,

    /// For each root, the id in `sets` of the tokens that every state in its group has or
    /// can take.
    takeable_ids: Vec<TokenSetId>,
    /// For each root, the id in `sets` of the tokens that some state in its group has.
    token_ids: Vec<TokenSetId>,
    sets: TokenSets,
    takeable: TakeableTokens,

    /// For each root, if the grammar has reserved words and a word token: its group's reserved
    /// and allowed words.
    ///
    /// Two states can't merge if one accepts the word token and the other reserves a word that
    /// neither has an entry for and the first doesn't reserve (`reserved_words_conflict`). Over
    /// groups, that's when one group's reserved words aren't all allowed by the other.
    reserved_ids: Vec<WordSetIds>,

    /// Pairs of roots, lowest first, whose groups were found not to merge by comparing their
    /// actions. Groups that can't merge still can't once either has grown, so these are skipped
    /// from then on. Failures that bitsets show cheaply aren't remembered.
    incompatible: FxHashSet<(ParseStateId, ParseStateId)>,

    /// Scratch for [`Self::try_merge`]: the pairs of states whose groups must still be merged.
    pending: Vec<(ParseStateId, ParseStateId)>,
    /// Scratch for [`Self::try_merge`], by state id: the root each root has been merged into so
    /// far, or itself.
    tentative_parents: Vec<ParseStateId>,
    /// Scratch for [`Self::try_merge`], by state id: the next root in each root's tentative group,
    /// which is a circular list.
    tentative_next: Vec<ParseStateId>,
    /// Scratch for [`Self::try_merge`]: the roots whose tentative entries have been set.
    touched: Vec<ParseStateId>,
    /// Scratch for [`Self::commit_tentative_merges`]: the entries a group gains from another.
    terminal_scratch: Vec<(Symbol, ActionListId)>,
    nonterminal_scratch: Vec<(Symbol, GotoAction)>,
    /// Scratch for [`Self::commit_tentative_merges`]: the sets it builds for a merged group before
    /// interning them, `words` each, one after another: the tokens that every state in the group
    /// can take, the tokens that some state has, and its reserved and allowed words.
    set_scratch: Vec<u64>,
}

impl<'m, 'a> StateMerger<'m, 'a> {
    fn new(minimizer: &'m Minimizer<'a>, states: &'m mut Vec<ParseState>) -> Self {
        let takeable = TakeableTokens::new(minimizer);
        let mut sets = TokenSets::new(takeable.words);
        // States with the same tokens and reserved words can take the same tokens.
        let mut ids_by_tokens =
            HashTable::<(ParseStateId, (TokenSetId, TokenSetId, Option<WordSetIds>))>::new();
        let word_token = minimizer
            .syntax_grammar
            .word_token
            .filter(|_| minimizer.has_reserved_words);
        // Every word, for a state that doesn't accept the word token. Its bits past the last token
        // are set too, which is harmless: it's only ever intersected or tested as a superset.
        let all_words = sets.intern(&vec![u64::MAX; sets.words as usize]);
        let hash_tokens = |state: &ParseState| {
            let mut hasher = FxHasher::default();
            for symbol in state.terminal_entries.keys() {
                symbol.hash(&mut hasher);
            }
            state.reserved_words.hash(&mut hasher);
            hasher.finish()
        };
        let same_tokens = |state: &ParseState, other: &ParseState| {
            state
                .terminal_entries
                .keys()
                .eq(other.terminal_entries.keys())
                && state.reserved_words == other.reserved_words
        };
        let state_count = states.len();
        let mut set = vec![0; sets.words as usize];
        let mut tokens = vec![0; sets.words as usize];
        let mut takeable_ids = Vec::with_capacity(state_count);
        let mut token_ids = Vec::with_capacity(state_count);
        let mut reserved_ids = Vec::new();
        for state in states.iter() {
            let hash = hash_tokens(state);
            let ids = if let Some(&(_, ids)) = ids_by_tokens.find(hash, |&(other, _)| {
                same_tokens(state, &states[other as usize])
            }) {
                ids
            } else {
                takeable.compute(minimizer, state, &mut set);
                let takeable_id = sets.intern(&set);
                tokens.fill(0);
                for (symbol, _) in state.terminal_entries.iter() {
                    TokenSets::set_bit(&mut tokens, minimizer.indexer.index(*symbol));
                }
                let token_id = sets.intern(&tokens);
                let word_ids = word_token.map(|word_token| {
                    set.fill(0);
                    for word in state.reserved_words.iter() {
                        TokenSets::set_bit(&mut set, minimizer.indexer.index(word));
                    }
                    let allowed = if state.terminal_entries.contains_key(word_token) {
                        let allowed = set.iter().zip(&tokens).map(|(word, token)| word | token);
                        sets.intern(&allowed.collect::<Vec<_>>())
                    } else {
                        all_words
                    };
                    for (word, token) in set.iter_mut().zip(&tokens) {
                        *word &= !token;
                    }
                    WordSetIds {
                        reserved: sets.intern(&set),
                        allowed,
                    }
                });
                let ids = (takeable_id, token_id, word_ids);
                ids_by_tokens.insert_unique(hash, (state.id, ids), |&(other, _)| {
                    hash_tokens(&states[other as usize])
                });
                ids
            };
            let (takeable_id, token_id, word_ids) = ids;
            takeable_ids.push(takeable_id);
            token_ids.push(token_id);
            if let Some(word_ids) = word_ids {
                reserved_ids.push(word_ids);
            }
        }

        Self {
            minimizer,
            states,
            parents: (0..state_count as ParseStateId).collect(),
            takeable_ids,
            token_ids,
            sets,
            takeable,
            reserved_ids,
            incompatible: FxHashSet::default(),
            pending: Vec::new(),
            tentative_parents: (0..state_count as ParseStateId).collect(),
            tentative_next: (0..state_count as ParseStateId).collect(),
            touched: Vec::new(),
            terminal_scratch: Vec::new(),
            nonterminal_scratch: Vec::new(),
            set_scratch: Vec::new(),
        }
    }

    /// Merges the states, and returns the states of each group in order of their lowest state,
    /// and the group of each state.
    fn merge(mut self) -> (Vec<Vec<ParseStateId>>, Vec<ParseStateId>) {
        let state_count = self.states.len();
        let core_count = 1 + self.states.iter().map(|state| state.core_id).max().unwrap() as usize;
        let mut state_ids_by_core = vec![Vec::new(); core_count];
        for state in self.states.iter() {
            state_ids_by_core[state.core_id as usize].push(state.id);
        }

        // The roots of the current core's groups so far, lowest first.
        let mut kept = Vec::new();
        for state_ids in &state_ids_by_core {
            kept.clear();
            for &state_id in state_ids {
                // A merge can join two of the core's groups, leaving the higher root behind.
                kept.retain(|&kept_root| self.parents[kept_root as usize] == kept_root);
                // The state may already be in one of the core's groups, merged as the successor
                // of an earlier state.
                let root = self.find_root(state_id);
                if kept.contains(&root) {
                    continue;
                }
                let merged = kept
                    .iter()
                    .any(|&kept_root| self.try_merge(kept_root, root));
                if !merged {
                    kept.push(root);
                }
            }
        }

        let mut state_ids_by_group_id = Vec::new();
        let mut group_ids_by_state_id = Vec::with_capacity(state_count);
        for state_id in 0..state_count as ParseStateId {
            let root = self.find_root(state_id);
            let group_id = if root == state_id {
                state_ids_by_group_id.push(Vec::new());
                state_ids_by_group_id.len() as ParseStateId - 1
            } else {
                // INVARIANT: a root is its group's lowest state, so it already has a group id.
                group_ids_by_state_id[root as usize]
            };
            state_ids_by_group_id[group_id as usize].push(state_id);
            group_ids_by_state_id.push(group_id);
        }
        (state_ids_by_group_id, group_ids_by_state_id)
    }

    /// The root of `state_id`'s group.
    fn find_root(&mut self, mut state_id: ParseStateId) -> ParseStateId {
        loop {
            let parent = self.parents[state_id as usize];
            if parent == state_id {
                return state_id;
            }
            // Point the state at its grandparent, to shorten later searches.
            let grandparent = self.parents[parent as usize];
            self.parents[state_id as usize] = grandparent;
            state_id = grandparent;
        }
    }

    /// The root of `state_id`'s group, without shortening the path.
    fn root(&self, mut state_id: ParseStateId) -> ParseStateId {
        while self.parents[state_id as usize] != state_id {
            state_id = self.parents[state_id as usize];
        }
        state_id
    }

    /// Whether the groups of `root1` and `root2` can each take the tokens only the other has.
    fn can_take_tokens(&self, root1: ParseStateId, root2: ParseStateId) -> bool {
        let takes = |root: ParseStateId, other: ParseStateId| {
            TokenSets::is_subset(
                self.sets.get(self.token_ids[root as usize]),
                self.sets.get(self.takeable_ids[other as usize]),
            )
        };
        takes(root1, root2) && takes(root2, root1)
    }

    /// Whether merging the groups of `root1` and `root2` would reserve a word that one of
    /// their states accepts as an identifier. See [`Self::reserved_ids`].
    fn reserved_words_conflict(&self, root1: ParseStateId, root2: ParseStateId) -> bool {
        let forbids = |root: ParseStateId, other: ParseStateId| {
            let reserved = self.reserved_ids[root as usize].reserved;
            let allowed = self.reserved_ids[other as usize].allowed;
            !TokenSets::is_subset(self.sets.get(reserved), self.sets.get(allowed))
        };
        forbids(root1, root2) || forbids(root2, root1)
    }

    /// Queues the groups of `state1` and `state2` to be merged, unless they can be seen not to
    /// merge already: a check is cheaper here than after the rest of the merge.
    fn push_pending(
        &self,
        state1: ParseStateId,
        state2: ParseStateId,
        pending: &mut Vec<(ParseStateId, ParseStateId)>,
    ) -> bool {
        let (root1, root2) = (self.root(state1), self.root(state2));
        if root1 == root2 {
            return true;
        }
        if self.incompatible.contains(&ordered(root1, root2)) || !self.can_take_tokens(root1, root2)
        {
            return false;
        }
        pending.push((state1, state2));
        true
    }

    /// The root of `state_id`'s group, counting the merges `try_merge` has made so far.
    fn find_tentative_root(&mut self, state_id: ParseStateId) -> ParseStateId {
        let mut root = self.find_root(state_id);
        while self.tentative_parents[root as usize] != root {
            root = self.tentative_parents[root as usize];
        }
        root
    }

    /// The terminal entries of the group of `root`.
    fn terminal_entries(&self, root: ParseStateId) -> &[(Symbol, ActionListId)] {
        self.states[root as usize].terminal_entries.as_slice()
    }

    /// The non-terminal entries of the group of `root`.
    fn nonterminal_entries(&self, root: ParseStateId) -> &[(Symbol, GotoAction)] {
        self.states[root as usize].nonterminal_entries.as_slice()
    }

    /// Merges the groups of roots `root1` and `root2`, and the groups their shared symbols lead
    /// to, recursively, if they're all compatible. Returns whether they were.
    fn try_merge(&mut self, root1: ParseStateId, root2: ParseStateId) -> bool {
        // Most attempts fail on the groups' own tokens; check those before setting anything up.
        if self.incompatible.contains(&ordered(root1, root2)) || !self.can_take_tokens(root1, root2)
        {
            return false;
        }
        let mut pending = mem::take(&mut self.pending);
        pending.push((root1, root2));
        let mut compatible = true;

        'pending: while let Some((state1, state2)) = pending.pop() {
            let tentative_root1 = self.find_tentative_root(state1);
            let tentative_root2 = self.find_tentative_root(state2);
            if tentative_root1 == tentative_root2 {
                continue;
            }
            // The first pair was checked for tokens before this loop, and each later one before
            // `push_pending` pushed it. Where both sides are single groups, that's the pair
            // `compatible` compares.
            let tokens_checked = self.tentative_next[tentative_root1 as usize] == tentative_root1
                && self.tentative_next[tentative_root2 as usize] == tentative_root2;
            // Compatibility isn't transitive, so each group must be compatible with each group
            // it joins.
            let mut root1 = tentative_root1;
            loop {
                let mut root2 = tentative_root2;
                loop {
                    let pair = ordered(root1, root2);
                    if self.incompatible.contains(&pair) {
                        compatible = false;
                        break 'pending;
                    }
                    match self.compatible(root1, root2, tokens_checked, &mut pending) {
                        Compatibility::Compatible => {}
                        Compatibility::Cheaply => {
                            compatible = false;
                            break 'pending;
                        }
                        Compatibility::Costly => {
                            self.incompatible.insert(pair);
                            compatible = false;
                            break 'pending;
                        }
                    }
                    root2 = self.tentative_next[root2 as usize];
                    if root2 == tentative_root2 {
                        break;
                    }
                }
                root1 = self.tentative_next[root1 as usize];
                if root1 == tentative_root1 {
                    break;
                }
            }
            let (root, other) = ordered(tentative_root1, tentative_root2);
            self.tentative_parents[other as usize] = root;
            // Join the two circular lists.
            self.tentative_next.swap(root as usize, other as usize);
            self.touched.extend([root, other]);
        }
        if compatible {
            self.commit_tentative_merges();
        }
        for &root in &self.touched {
            self.tentative_parents[root as usize] = root;
            self.tentative_next[root as usize] = root;
        }
        self.touched.clear();
        pending.clear();
        self.pending = pending;
        compatible
    }

    /// Makes the merges `try_merge` found.
    fn commit_tentative_merges(&mut self) {
        let words = self.sets.words as usize;
        let mut set_scratch = mem::take(&mut self.set_scratch);
        set_scratch.resize(4 * words, 0);
        let (takeable, rest) = set_scratch.split_at_mut(words);
        let (tokens, rest) = rest.split_at_mut(words);
        let (reserved, allowed) = rest.split_at_mut(words);
        let mut terminal_scratch = mem::take(&mut self.terminal_scratch);
        let mut nonterminal_scratch = mem::take(&mut self.nonterminal_scratch);
        for i in 0..self.touched.len() {
            let root = self.touched[i];
            // skip roots that a later union placed under a lower one
            if self.tentative_parents[root as usize] != root
                // and roots that were already committed
                || self.tentative_next[root as usize] == root
            {
                continue;
            }
            let mut terminal_entries = mem::take(&mut self.states[root as usize].terminal_entries);
            let mut nonterminal_entries =
                mem::take(&mut self.states[root as usize].nonterminal_entries);
            takeable.copy_from_slice(self.sets.get(self.takeable_ids[root as usize]));
            tokens.copy_from_slice(self.sets.get(self.token_ids[root as usize]));
            if let Some(&word_ids) = self.reserved_ids.get(root as usize) {
                reserved.copy_from_slice(self.sets.get(word_ids.reserved));
                allowed.copy_from_slice(self.sets.get(word_ids.allowed));
            }
            let mut other = self.tentative_next[root as usize];
            while other != root {
                let other_tokens = self.sets.get(self.token_ids[other as usize]);
                // The group's terminal entries are its tokens, so the entries the other group adds
                // are those of the tokens only it has.
                terminal_scratch.clear();
                let other_entries = self.terminal_entries(other);
                for (index, (&word, &other_word)) in tokens.iter().zip(other_tokens).enumerate() {
                    let mut bits = other_word & !word;
                    while bits != 0 {
                        let position = index * 64 + bits.trailing_zeros() as usize;
                        bits &= bits - 1;
                        let symbol = self.minimizer.indexer.symbol(position);
                        // INVARIANT: the other group has an entry for each of its tokens.
                        let entry = other_entries
                            .binary_search_by_key(&symbol, |&(symbol, _)| symbol)
                            .unwrap();
                        terminal_scratch.push(other_entries[entry]);
                    }
                }
                debug_assert!(terminal_scratch.is_sorted_by_key(|&(symbol, _)| symbol));
                terminal_entries.insert_sorted(&terminal_scratch);
                nonterminal_entries
                    .merge_sorted(self.nonterminal_entries(other), &mut nonterminal_scratch);
                let other_takeable = self.sets.get(self.takeable_ids[other as usize]);
                for (word, other_word) in takeable.iter_mut().zip(other_takeable) {
                    *word &= other_word;
                }
                for (word, other_word) in tokens.iter_mut().zip(other_tokens) {
                    *word |= other_word;
                }
                if let Some(&other_ids) = self.reserved_ids.get(other as usize) {
                    let other_reserved = self.sets.get(other_ids.reserved);
                    for (word, other_word) in reserved.iter_mut().zip(other_reserved) {
                        *word |= other_word;
                    }
                    let other_allowed = self.sets.get(other_ids.allowed);
                    for (word, other_word) in allowed.iter_mut().zip(other_allowed) {
                        *word &= other_word;
                    }
                }
                // Nothing reads the entries of a state whose group has merged into another.
                let other_state = &mut self.states[other as usize];
                other_state.terminal_entries = ParseStateEntries::default();
                other_state.nonterminal_entries = ParseStateEntries::default();
                self.parents[other as usize] = root;

                other = self.tentative_next[other as usize];
            }
            // Each tentative group is committed once, at its root.
            self.tentative_next[root as usize] = root;
            let root_state = &mut self.states[root as usize];
            root_state.terminal_entries = terminal_entries;
            root_state.nonterminal_entries = nonterminal_entries;
            self.takeable_ids[root as usize] = self
                .sets
                .reintern(self.takeable_ids[root as usize], takeable);
            self.token_ids[root as usize] =
                self.sets.reintern(self.token_ids[root as usize], tokens);
            if let Some(&word_ids) = self.reserved_ids.get(root as usize) {
                self.reserved_ids[root as usize] = WordSetIds {
                    reserved: self.sets.reintern(word_ids.reserved, reserved),
                    allowed: self.sets.reintern(word_ids.allowed, allowed),
                };
            }
        }
        self.terminal_scratch = terminal_scratch;
        self.nonterminal_scratch = nonterminal_scratch;
        self.set_scratch = set_scratch;
    }

    /// Whether the groups of `root1` and `root2` are compatible, apart from what their shared
    /// symbols lead to: the pairs of states those are go onto `pending`, to be merged too. With
    /// `tokens_checked`, the caller has checked that they can take each other's tokens.
    fn compatible(
        &self,
        root1: ParseStateId,
        root2: ParseStateId,
        tokens_checked: bool,
        pending: &mut Vec<(ParseStateId, ParseStateId)>,
    ) -> Compatibility {
        // A shift into a non-terminal extra can pair a state with one of another core.
        let states = &self.states;
        if states[root1 as usize].core_id != states[root2 as usize].core_id {
            self.log_conflict(root1, root2, Symbol::End, Conflict::Cores);
            return Compatibility::Cheaply;
        }
        if !self.reserved_ids.is_empty() && self.reserved_words_conflict(root1, root2) {
            self.log_conflict(root1, root2, Symbol::End, Conflict::ReservedWords);
            return Compatibility::Cheaply;
        }

        // Each group must be able to take the tokens that only the other has.
        if !tokens_checked && !self.can_take_tokens(root1, root2) {
            self.log_token_conflict(root1, root2);
            return Compatibility::Cheaply;
        }

        // The tokens they share must have the same actions.
        let entries1 = self.terminal_entries(root1);
        let entries2 = self.terminal_entries(root2);
        let (mut i, mut j) = (0, 0);
        while let (Some(&(symbol1, id1)), Some(&(symbol2, id2))) =
            (entries1.get(i), entries2.get(j))
        {
            match symbol1.cmp(&symbol2) {
                Ordering::Less => i += 1,
                Ordering::Greater => j += 1,
                Ordering::Equal => {
                    if let Some(conflict) = self.action_lists_conflict(id1, id2, pending) {
                        self.log_conflict(root1, root2, symbol1, conflict);
                        return Compatibility::Costly;
                    }
                    i += 1;
                    j += 1;
                }
            }
        }

        let entries1 = self.nonterminal_entries(root1);
        let entries2 = self.nonterminal_entries(root2);
        let (mut i, mut j) = (0, 0);
        while let (Some(&(symbol1, action1)), Some(&(symbol2, action2))) =
            (entries1.get(i), entries2.get(j))
        {
            match symbol1.cmp(&symbol2) {
                Ordering::Less => i += 1,
                Ordering::Greater => j += 1,
                Ordering::Equal => {
                    match (action1, action2) {
                        (GotoAction::Goto(state1), GotoAction::Goto(state2)) => {
                            if !self.push_pending(state1, state2, pending) {
                                self.log_conflict(root1, root2, symbol1, Conflict::Successors);
                                return Compatibility::Costly;
                            }
                        }
                        (GotoAction::ShiftExtra, GotoAction::ShiftExtra) => {}
                        _ => {
                            self.log_conflict(root1, root2, symbol1, Conflict::UnequalGotos);
                            return Compatibility::Costly;
                        }
                    }
                    i += 1;
                    j += 1;
                }
            }
        }
        Compatibility::Compatible
    }

    /// Why two entries for the same token can't be merged, if they can't. The pairs of states
    /// they shift to go onto `pending`.
    fn action_lists_conflict(
        &self,
        id1: ActionListId,
        id2: ActionListId,
        pending: &mut Vec<(ParseStateId, ParseStateId)>,
    ) -> Option<Conflict> {
        if id1.index() == id2.index() {
            return None;
        }
        let action_lists = &self.minimizer.parse_table.action_lists;
        let actions1 = action_lists.get(id1);
        let actions2 = action_lists.get(id2);
        if actions1.len() != actions2.len() {
            return Some(Conflict::ActionCounts);
        }
        for (action1, action2) in actions1.iter().zip(actions2) {
            match (action1, action2) {
                (
                    ParseAction::Shift {
                        state: state1,
                        is_repetition: is_repetition1,
                    },
                    ParseAction::Shift {
                        state: state2,
                        is_repetition: is_repetition2,
                    },
                ) if is_repetition1 == is_repetition2 => {
                    if !self.push_pending(*state1, *state2, pending) {
                        return Some(Conflict::Successors);
                    }
                }
                (action1, action2) if action1 == action2 => {}
                _ => return Some(Conflict::UnequalActions),
            }
        }
        None
    }

    /// Logs why one of the groups of `root1` and `root2` can't take a token of the other.
    #[inline]
    fn log_token_conflict(&self, root1: ParseStateId, root2: ParseStateId) {
        if log_enabled!(Level::Debug) {
            self.log_token_conflict_cold(root1, root2);
        }
    }

    #[cold]
    #[inline(never)]
    fn log_token_conflict_cold(&self, root1: ParseStateId, root2: ParseStateId) {
        let indexer = self.minimizer.indexer;
        for (root, other) in [(root1, root2), (root2, root1)] {
            let takeable = self.takeable_ids[other as usize];
            if let Some(&(token, _)) = self
                .terminal_entries(root)
                .iter()
                .find(|(symbol, _)| !self.sets.contains(takeable, indexer.index(*symbol)))
            {
                let entries = self.terminal_entries(other);
                let conflict = self.takeable.conflict(self.minimizer, token, entries);
                self.log_conflict_cold(root1, root2, token, conflict);
                return;
            }
        }
    }

    /// Logs that the groups of `root1` and `root2` can't merge because of `conflict`, over
    /// `token`.
    #[inline]
    fn log_conflict(
        &self,
        root1: ParseStateId,
        root2: ParseStateId,
        symbol: Symbol,
        conflict: Conflict,
    ) {
        if log_enabled!(Level::Debug) {
            self.log_conflict_cold(root1, root2, symbol, conflict);
        }
    }

    #[cold]
    #[inline(never)]
    fn log_conflict_cold(
        &self,
        root1: ParseStateId,
        root2: ParseStateId,
        symbol: Symbol,
        conflict: Conflict,
    ) {
        let name = |symbol| self.minimizer.symbol_name(symbol);
        match conflict {
            Conflict::Cores => debug!("can't merge states {root1} {root2} - different cores"),
            Conflict::Successors => debug!(
                "can't merge states {root1} {root2} - successors for {} can't merge",
                name(symbol)
            ),
            Conflict::ActionCounts => debug!(
                "can't merge states {root1} {root2} - differing action counts for token {}",
                name(symbol)
            ),
            Conflict::UnequalActions => debug!(
                "can't merge states {root1} {root2} - unequal actions for {}",
                name(symbol)
            ),
            Conflict::UnequalGotos => debug!(
                "can't merge states {root1} {root2} - unequal gotos for {}",
                name(symbol)
            ),
            Conflict::ReservedWords => {
                debug!("can't merge states {root1} {root2} - incompatible reserved words");
            }
            Conflict::EndOfNonTerminalExtra => {
                debug!("can't merge states {root1} {root2} - end of non-terminal extra");
            }
            Conflict::ExternalToken => debug!(
                "can't merge states {root1} {root2} - external token {}",
                name(symbol)
            ),
            Conflict::InternalExternalToken => debug!(
                "can't merge states {root1} {root2} - internal/external token {}",
                name(symbol)
            ),
            Conflict::Untakeable => debug!(
                "can't merge states {root1} {root2} - token {} can't be added (this indicates a bug)",
                name(symbol)
            ),
            Conflict::Lexical(terminal) => debug!(
                "can't merge states {root1} {root2} - token {} conflicts with {}",
                name(symbol),
                name(Symbol::terminal(terminal)),
            ),
        }
    }
}

#[inline]
const fn ordered(a: ParseStateId, b: ParseStateId) -> (ParseStateId, ParseStateId) {
    if a < b { (a, b) } else { (b, a) }
}

/// Whether two groups of states can be merged, apart from their successors.
enum Compatibility {
    // Yes: they can be merged.
    Compatible,
    /// No: their cores, reserved words, or tokens differ (which bitsets show cheaply).
    Cheaply,
    /// No: comparing their actions shows it.
    Costly,
}

/// Why two states can't be merged: either their entries for a token differ, or a token that
/// only one of them has can't be added to the other.
#[derive(Clone, Copy)]
enum Conflict {
    /// They have different cores.
    Cores,
    /// The states they shift or go to on the token can't merge.
    Successors,
    /// Their entries have different numbers of actions.
    ActionCounts,
    /// Their entries have different actions.
    UnequalActions,
    /// One goes to a state after the non-terminal, and the other shifts it as an extra.
    UnequalGotos,
    /// Merging them would reserve a word that one of them accepts as an identifier.
    ReservedWords,
    /// The token ends a non-terminal extra, which stops a state from lexing.
    EndOfNonTerminalExtra,
    /// The token is external, which changes what the external scanner is told is valid.
    ExternalToken,
    /// The token is both internal and external: having it tells the external scanner that its
    /// external twin is valid.
    InternalExternalToken,
    /// The token conflicts lexically with this terminal, which the other group has.
    Lexical(usize),
    /// The token can't be added to the other group, but no other conflict explains why.
    /// [`TakeableTokens::conflict`] returns this as a fallback.
    Untakeable,
}

struct Minimizer<'a> {
    parse_table: &'a mut ParseTable,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    /// Gives each token its bit in [`TokenSets`].
    indexer: SymbolIndexer,
    token_conflict_map: &'a TokenConflictMap,
    keywords: &'a TokenSet,
    has_reserved_words: bool,
    simple_aliases: &'a AliasMap,
    str_pool: &'a StrPool,
}

impl Minimizer<'_> {
    fn remove_unit_reductions(&mut self) {
        let mut aliased_symbols = FxHashSet::default();
        // Include appended productions, where inlining can copy an alias onto
        // the symbols that replace the inlined step.
        for step in &self.syntax_grammar.steps {
            if step.alias().is_some() {
                aliased_symbols.insert(step.symbol());
            }
        }

        let mut unit_reduction_symbols_by_state = FxHashMap::default();
        for (i, state) in self.parse_table.states.iter().enumerate() {
            if state.has_eof_gated_reduce {
                continue;
            }
            let mut only_unit_reductions = true;
            let mut unit_reduction_symbol = None;
            for (_, id) in state.terminal_entries.iter() {
                for action in self.parse_table.action_lists.get(*id) {
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
                            && matches!(symbol.non_terminal_index(), Some(index)
                                    if self.syntax_grammar.variables[usize::from(index)].kind
                                        != VariableType::Named
                            )
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

        if unit_reduction_symbols_by_state.is_empty() {
            return;
        }

        let mut action_list_ids = FxHashMap::default();
        for state_index in 0..self.parse_table.states.len() {
            let mut done = false;
            while !done {
                done = true;
                let ParseTable {
                    states,
                    action_lists,
                    ..
                } = self.parse_table;
                let state = &mut states[state_index];

                state.update_nonterminal_references(|other_state_id, state| {
                    unit_reduction_symbols_by_state.get(&other_state_id).map_or(
                        other_state_id,
                        |symbol| {
                            done = false;
                            match state.nonterminal_entries.get(*symbol) {
                                Some(GotoAction::Goto(state_id)) => *state_id,
                                _ => other_state_id,
                            }
                        },
                    )
                });

                for i in 0..state.terminal_entries.len() {
                    let old_id = state.terminal_entries.get_index(i).unwrap().1;
                    let mut actions = ActionList::from_slice(action_lists.get(*old_id));
                    let mut changed = false;
                    for action in &mut *actions {
                        // A Shift onto a unit-reduction state (one whose only action reduces a
                        // single `symbol`) can skip it. Shift then reduce then goto is equivalent
                        // to shifting straight to the the goto target for `symbol` in this case.
                        if let ParseAction::Shift { state: target, .. } = action
                            && let Some(symbol) = unit_reduction_symbols_by_state.get(target)
                            && let Some(GotoAction::Goto(new_target)) =
                                state.nonterminal_entries.get(*symbol)
                            && *new_target != *target
                        {
                            *target = *new_target;
                            changed = true;
                            done = false;
                        }
                    }
                    if changed {
                        let index = action_lists.intern(&mut action_list_ids, actions);
                        *state.terminal_entries.get_index_mut(i).unwrap().1 =
                            ActionListId::new(index, old_id.reusable());
                    }
                }
            }
        }
    }

    fn merge_compatible_states(&mut self) {
        // The merger compares states' entries in symbol order.
        for state in &mut self.parse_table.states {
            state.terminal_entries.sort_by_symbol();
            state.nonterminal_entries.sort_by_symbol();
        }

        let mut states = mem::take(&mut self.parse_table.states);
        let (state_ids_by_group_id, group_ids_by_state_id) =
            StateMerger::new(self, &mut states).merge();
        self.parse_table.states = states;

        // The runtime needs the error and start states to hold ids 0 and 1. `merge`
        // numbers groups by their lowest state, and neither of the two shares its core.
        assert_eq!(group_ids_by_state_id[..2], [0, 1]);

        // Create a list of new parse states: one state for each group of old states. A group's
        // lowest state, its root, already has the group's entries.
        let mut new_states = Vec::with_capacity(state_ids_by_group_id.len());
        for state_ids in &state_ids_by_group_id {
            let mut parse_state = mem::take(&mut self.parse_table.states[state_ids[0] as usize]);
            for state_id in &state_ids[1..] {
                let other_parse_state = mem::take(&mut self.parse_table.states[*state_id as usize]);

                parse_state.has_eof_gated_reduce |= other_parse_state.has_eof_gated_reduce;
                parse_state
                    .reserved_words
                    .insert_all(&other_parse_state.reserved_words);
            }
            if state_ids.len() > 1 {
                for &symbol in parse_state.terminal_entries.keys() {
                    parse_state.reserved_words.remove(symbol);
                }
            }

            // Update the new state's outgoing references using the new grouping.
            parse_state.update_nonterminal_references(|state_id, _| {
                group_ids_by_state_id[state_id as usize]
            });
            new_states.push(parse_state);
        }

        self.parse_table.states = new_states;
        self.parse_table
            .remap_terminal_references(|state_id| group_ids_by_state_id[state_id as usize]);
    }

    fn symbol_name(&self, symbol: Symbol) -> &str {
        match symbol.view() {
            SymbolView::NonTerminal(index) => self
                .str_pool
                .resolve(self.syntax_grammar.variables[usize::from(index)].name),
            SymbolView::External(index) => self
                .str_pool
                .resolve(self.syntax_grammar.external_tokens[usize::from(index)].name),
            SymbolView::Terminal(index) => self
                .str_pool
                .resolve(self.lexical_grammar.variables[usize::from(index)].name),
            SymbolView::End => "<EOF>",
            SymbolView::EndOfNonTerminalExtra => "<END_OF_NONTERMINAL_EXTRA>",
        }
    }

    fn remove_unused_states(&mut self) {
        let mut state_usage_map = vec![false; self.parse_table.states.len()];

        state_usage_map[0] = true;
        state_usage_map[1] = true;

        for state in &self.parse_table.states {
            for referenced_state in state.referenced_states(&self.parse_table.action_lists) {
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
                self.parse_table.states[state_id].update_nonterminal_references(
                    |other_state_id, _| state_replacement_map[other_state_id as usize],
                );
                state_id += 1;
            } else {
                self.parse_table.states.remove(state_id);
            }
            original_state_id += 1;
        }
        self.parse_table
            .remap_terminal_references(|state_id| state_replacement_map[state_id as usize]);
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
                state.update_nonterminal_references(|id, _| new_ids_by_old_id[id as usize]);
                state
            })
            .collect();
        self.parse_table
            .remap_terminal_references(|id| new_ids_by_old_id[id as usize]);
    }
}
