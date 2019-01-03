use super::item::LookaheadSet;
use super::token_conflicts::TokenConflictMap;
use crate::grammars::{LexicalGrammar, SyntaxGrammar};
use crate::nfa::NfaCursor;
use crate::tables::{AdvanceAction, LexState, LexTable, ParseTable};
use std::collections::hash_map::Entry;
use std::collections::{BTreeMap, HashMap, VecDeque};

pub(crate) fn build_lex_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    keywords: &LookaheadSet,
) -> (LexTable, LexTable) {
    let keyword_lex_table;
    if syntax_grammar.word_token.is_some() {
        let mut builder = LexTableBuilder::new(lexical_grammar);
        builder.add_state_for_tokens(keywords);
        keyword_lex_table = builder.table;
    } else {
        keyword_lex_table = LexTable::default();
    }

    let mut builder = LexTableBuilder::new(lexical_grammar);
    for (i, state) in parse_table.states.iter_mut().enumerate() {
        info!("populate lex state for parse state {}", i);
        let tokens = LookaheadSet::with(state.terminal_entries.keys().filter_map(|token| {
            if token.is_terminal() {
                if keywords.contains(&token) {
                    syntax_grammar.word_token
                } else {
                    Some(*token)
                }
            } else {
                None
            }
        }));
        state.lex_state_id = builder.add_state_for_tokens(&tokens);
    }

    let mut table = builder.table;
    shrink_lex_table(&mut table, parse_table);

    (table, keyword_lex_table)
}

struct LexTableBuilder<'a> {
    lexical_grammar: &'a LexicalGrammar,
    cursor: NfaCursor<'a>,
    table: LexTable,
    state_queue: VecDeque<(usize, Vec<u32>)>,
    state_ids_by_nfa_state_set: HashMap<Vec<u32>, usize>,
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

    fn add_state_for_tokens(&mut self, tokens: &LookaheadSet) -> usize {
        let nfa_states = tokens
            .iter()
            .map(|token| self.lexical_grammar.variables[token.index].start_state)
            .collect();
        let (state_id, is_new) = self.add_state(nfa_states);

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

        while let Some((state_id, nfa_states)) = self.state_queue.pop_back() {
            self.populate_state(state_id, nfa_states);
        }
        state_id
    }

    fn add_state(&mut self, nfa_states: Vec<u32>) -> (usize, bool) {
        self.cursor.reset(nfa_states);
        match self
            .state_ids_by_nfa_state_set
            .entry(self.cursor.state_ids.clone())
        {
            Entry::Occupied(o) => (*o.get(), false),
            Entry::Vacant(v) => {
                let state_id = self.table.states.len();
                self.table.states.push(LexState::default());
                self.state_queue.push_back((state_id, v.key().clone()));
                v.insert(state_id);
                (state_id, true)
            }
        }
    }

    fn populate_state(&mut self, state_id: usize, nfa_states: Vec<u32>) {
        self.cursor.force_reset(nfa_states);

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

        for (chars, advance_precedence, next_states, is_sep) in self.cursor.grouped_successors() {
            info!(
                "populate state: {}, characters: {:?}, precedence: {:?}",
                state_id, chars, advance_precedence
            );
            if let Some((_, completed_precedence)) = completion {
                if advance_precedence < completed_precedence {
                    continue;
                }
            }
            let (next_state_id, _) = self.add_state(next_states);
            self.table.states[state_id].advance_actions.push((
                chars,
                AdvanceAction {
                    state: next_state_id,
                    in_main_token: !is_sep,
                },
            ));
        }

        if let Some((completion_index, _)) = completion {
            self.table.states[state_id].accept_action = Some(completion_index);
        }
    }
}

fn shrink_lex_table(table: &mut LexTable, parse_table: &mut ParseTable) {
    let mut state_replacements = BTreeMap::new();
    let mut done = false;
    while !done {
        done = true;
        for (i, state_i) in table.states.iter().enumerate() {
            if state_replacements.contains_key(&i) {
                continue;
            }
            for (j, state_j) in table.states.iter().enumerate() {
                if state_replacements.contains_key(&j) {
                    continue;
                }
                if j == i {
                    break;
                }
                if state_i == state_j {
                    info!("replace state {} with state {}", i, j);
                    state_replacements.insert(i, j);
                    done = false;
                }
            }
        }
        for state in table.states.iter_mut() {
            for advance_action in state.advance_actions.iter_mut() {
                if let Some(new_state_id) = state_replacements.get(&advance_action.1.state) {
                    advance_action.1.state = *new_state_id;
                }
            }
        }
    }

    let final_state_replacements = (0..table.states.len()).into_iter().map(|state_id| {
        let replacement = state_replacements.get(&state_id).cloned().unwrap_or(state_id);
        let prior_removed = state_replacements.iter().take_while(|i| *i.0 < replacement).count();
        replacement - prior_removed
    }).collect::<Vec<_>>();

    for state in parse_table.states.iter_mut() {
        state.lex_state_id = final_state_replacements[state.lex_state_id];
    }

    for state in table.states.iter_mut() {
        for advance_action in state.advance_actions.iter_mut() {
            advance_action.1.state = final_state_replacements[advance_action.1.state];
        }
    }

    let mut i = 0;
    table.states.retain(|_| {
        let result = !state_replacements.contains_key(&i);
        i += 1;
        result
    });
}
