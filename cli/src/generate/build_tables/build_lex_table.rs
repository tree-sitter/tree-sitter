use super::coincident_tokens::CoincidentTokenIndex;
use super::item::TokenSet;
use super::token_conflicts::TokenConflictMap;
use crate::generate::grammars::{LexicalGrammar, SyntaxGrammar};
use crate::generate::nfa::{CharacterSet, NfaCursor};
use crate::generate::rules::Symbol;
use crate::generate::tables::{AdvanceAction, LexState, LexTable, ParseStateId, ParseTable};
use log::info;
use std::collections::hash_map::Entry;
use std::collections::{BTreeMap, HashMap, VecDeque};

pub(crate) fn build_lex_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    keywords: &TokenSet,
    coincident_token_index: &CoincidentTokenIndex,
    token_conflict_map: &TokenConflictMap,
    minimize: bool,
) -> (LexTable, LexTable) {
    let keyword_lex_table;
    if syntax_grammar.word_token.is_some() {
        let mut builder = LexTableBuilder::new(lexical_grammar);
        builder.add_state_for_tokens(keywords);
        keyword_lex_table = builder.table;
    } else {
        keyword_lex_table = LexTable::default();
    }

    let mut parse_state_ids_by_token_set: Vec<(TokenSet, Vec<ParseStateId>)> = Vec::new();
    for (i, state) in parse_table.states.iter().enumerate() {
        let tokens = state
            .terminal_entries
            .keys()
            .filter_map(|token| {
                if token.is_terminal() {
                    if keywords.contains(&token) {
                        syntax_grammar.word_token
                    } else {
                        Some(*token)
                    }
                } else if token.is_eof() {
                    Some(*token)
                } else {
                    None
                }
            })
            .collect();

        let mut did_merge = false;
        for entry in parse_state_ids_by_token_set.iter_mut() {
            if merge_token_set(
                &mut entry.0,
                &tokens,
                lexical_grammar,
                token_conflict_map,
                coincident_token_index,
            ) {
                did_merge = true;
                entry.1.push(i);
                break;
            }
        }

        if !did_merge {
            parse_state_ids_by_token_set.push((tokens, vec![i]));
        }
    }

    let mut builder = LexTableBuilder::new(lexical_grammar);
    for (tokens, parse_state_ids) in parse_state_ids_by_token_set {
        let lex_state_id = builder.add_state_for_tokens(&tokens);
        for id in parse_state_ids {
            parse_table.states[id].lex_state_id = lex_state_id;
        }
    }

    let mut table = builder.table;

    if minimize {
        minimize_lex_table(&mut table, parse_table);
    }

    (table, keyword_lex_table)
}

struct QueueEntry {
    state_id: usize,
    nfa_states: Vec<u32>,
    eof_valid: bool,
}

struct LexTableBuilder<'a> {
    lexical_grammar: &'a LexicalGrammar,
    cursor: NfaCursor<'a>,
    table: LexTable,
    state_queue: VecDeque<QueueEntry>,
    state_ids_by_nfa_state_set: HashMap<(Vec<u32>, bool), usize>,
}

impl<'a> LexTableBuilder<'a> {
    fn new(lexical_grammar: &'a LexicalGrammar) -> Self {
        Self {
            lexical_grammar,
            cursor: NfaCursor::new(&lexical_grammar.nfa, vec![]),
            table: LexTable::default(),
            state_queue: VecDeque::new(),
            state_ids_by_nfa_state_set: HashMap::new(),
        }
    }

    fn add_state_for_tokens(&mut self, tokens: &TokenSet) -> usize {
        let mut eof_valid = false;
        let nfa_states = tokens
            .iter()
            .filter_map(|token| {
                if token.is_terminal() {
                    Some(self.lexical_grammar.variables[token.index].start_state)
                } else {
                    eof_valid = true;
                    None
                }
            })
            .collect();
        let (state_id, is_new) = self.add_state(nfa_states, eof_valid);

        if is_new {
            info!(
                "entry point state: {}, tokens: {:?}",
                state_id,
                tokens
                    .iter()
                    .map(|t| &self.lexical_grammar.variables[t.index].name)
                    .collect::<Vec<_>>()
            );
        }

        while let Some(QueueEntry {
            state_id,
            nfa_states,
            eof_valid,
        }) = self.state_queue.pop_front()
        {
            self.populate_state(state_id, nfa_states, eof_valid);
        }
        state_id
    }

    fn add_state(&mut self, nfa_states: Vec<u32>, eof_valid: bool) -> (usize, bool) {
        self.cursor.reset(nfa_states);
        match self
            .state_ids_by_nfa_state_set
            .entry((self.cursor.state_ids.clone(), eof_valid))
        {
            Entry::Occupied(o) => (*o.get(), false),
            Entry::Vacant(v) => {
                let state_id = self.table.states.len();
                self.table.states.push(LexState::default());
                self.state_queue.push_back(QueueEntry {
                    state_id,
                    nfa_states: v.key().0.clone(),
                    eof_valid,
                });
                v.insert(state_id);
                (state_id, true)
            }
        }
    }

    fn populate_state(&mut self, state_id: usize, nfa_states: Vec<u32>, eof_valid: bool) {
        self.cursor.force_reset(nfa_states);

        // The EOF state is represented as an empty list of NFA states.
        let mut completion = None;
        for (id, prec) in self.cursor.completions() {
            if let Some((prev_id, prev_precedence)) = completion {
                if TokenConflictMap::prefer_token(
                    self.lexical_grammar,
                    (prev_precedence, prev_id),
                    (prec, id),
                ) {
                    continue;
                }
            }
            completion = Some((id, prec));
        }

        let transitions = self.cursor.transitions();
        let has_sep = self.cursor.transition_chars().any(|(_, sep)| sep);

        // If EOF is a valid lookahead token, add a transition predicated on the null
        // character that leads to the empty set of NFA states.
        if eof_valid {
            let (next_state_id, _) = self.add_state(Vec::new(), false);
            self.table.states[state_id].advance_actions.push((
                CharacterSet::empty().add_char('\0'),
                AdvanceAction {
                    state: Some(next_state_id),
                    in_main_token: true,
                },
            ));
        }

        for transition in transitions {
            if let Some((completed_id, completed_precedence)) = completion {
                if !TokenConflictMap::prefer_transition(
                    &self.lexical_grammar,
                    &transition,
                    completed_id,
                    completed_precedence,
                    has_sep,
                ) {
                    continue;
                }
            }

            let (next_state_id, _) =
                self.add_state(transition.states, eof_valid && transition.is_separator);
            let next_state = if next_state_id == state_id {
                None
            } else {
                Some(next_state_id)
            };
            self.table.states[state_id].advance_actions.push((
                transition.characters,
                AdvanceAction {
                    state: next_state,
                    in_main_token: !transition.is_separator,
                },
            ));
        }

        if let Some((complete_id, _)) = completion {
            self.table.states[state_id].accept_action = Some(Symbol::terminal(complete_id));
        } else if self.cursor.state_ids.is_empty() {
            self.table.states[state_id].accept_action = Some(Symbol::end());
        }
    }
}

fn merge_token_set(
    tokens: &mut TokenSet,
    other: &TokenSet,
    lexical_grammar: &LexicalGrammar,
    token_conflict_map: &TokenConflictMap,
    coincident_token_index: &CoincidentTokenIndex,
) -> bool {
    for i in 0..lexical_grammar.variables.len() {
        let symbol = Symbol::terminal(i);
        let set_without_terminal = match (tokens.contains_terminal(i), other.contains_terminal(i)) {
            (true, false) => other,
            (false, true) => tokens,
            _ => continue,
        };

        for existing_token in set_without_terminal.terminals() {
            if token_conflict_map.does_conflict(i, existing_token.index)
                || !coincident_token_index.contains(symbol, existing_token)
            {
                return false;
            }
        }
    }

    tokens.insert_all(other);
    true
}

fn minimize_lex_table(table: &mut LexTable, parse_table: &mut ParseTable) {
    let mut state_replacements = BTreeMap::new();
    let mut done = false;
    while !done {
        done = true;
        for (i, state_i) in table.states.iter().enumerate() {
            if state_replacements.contains_key(&i) {
                continue;
            }
            for (j, state_j) in table.states.iter().enumerate() {
                if j == i {
                    break;
                }
                if state_replacements.contains_key(&j) {
                    continue;
                }
                if state_i == state_j {
                    info!("replace state {} with state {}", i, j);
                    state_replacements.insert(i, j);
                    done = false;
                    break;
                }
            }
        }
        for state in table.states.iter_mut() {
            for (_, advance_action) in state.advance_actions.iter_mut() {
                advance_action.state = advance_action
                    .state
                    .map(|s| state_replacements.get(&s).cloned().unwrap_or(s))
            }
        }
    }

    let final_state_replacements = (0..table.states.len())
        .into_iter()
        .map(|state_id| {
            let replacement = state_replacements
                .get(&state_id)
                .cloned()
                .unwrap_or(state_id);
            let prior_removed = state_replacements
                .iter()
                .take_while(|i| *i.0 < replacement)
                .count();
            replacement - prior_removed
        })
        .collect::<Vec<_>>();

    for state in parse_table.states.iter_mut() {
        state.lex_state_id = final_state_replacements[state.lex_state_id];
    }

    for state in table.states.iter_mut() {
        for (_, advance_action) in state.advance_actions.iter_mut() {
            advance_action.state = advance_action.state.map(|s| final_state_replacements[s]);
        }
    }

    let mut i = 0;
    table.states.retain(|_| {
        let result = !state_replacements.contains_key(&i);
        i += 1;
        result
    });
}
