use super::item::LookaheadSet;
use super::token_conflicts::TokenConflictMap;
use crate::grammars::{LexicalGrammar, SyntaxGrammar};
use crate::nfa::NfaCursor;
use crate::rules::Symbol;
use crate::tables::{AdvanceAction, LexState, LexTable, ParseTable};
use std::collections::hash_map::Entry;
use std::collections::{HashMap, VecDeque};

pub(crate) fn build_lex_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    keywords: &LookaheadSet,
) -> (LexTable, LexTable) {
    let keyword_lex_table;
    if syntax_grammar.word_token.is_some() {
        let mut builder = LexTableBuilder::new(lexical_grammar);
        builder.add_state_for_tokens(keywords.iter());
        keyword_lex_table = builder.table;
    } else {
        keyword_lex_table = LexTable::default();
    }

    let mut builder = LexTableBuilder::new(lexical_grammar);
    for state in parse_table.states.iter_mut() {
        let tokens = state.terminal_entries.keys().filter_map(|token| {
            if token.is_terminal() {
                if keywords.contains(&token) {
                    syntax_grammar.word_token
                } else {
                    Some(*token)
                }
            } else {
                None
            }
        });
        state.lex_state_id = builder.add_state_for_tokens(tokens);
    }

    (builder.table, keyword_lex_table)
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

    fn add_state_for_tokens(&mut self, tokens: impl Iterator<Item = Symbol>) -> usize {
        let nfa_states = tokens
            .map(|token| self.lexical_grammar.variables[token.index].start_state)
            .collect();
        let result = self.add_state(nfa_states);
        while let Some((state_id, nfa_states)) = self.state_queue.pop_front() {
            self.populate_state(state_id, nfa_states);
        }
        result
    }

    fn add_state(&mut self, nfa_states: Vec<u32>) -> usize {
        match self.state_ids_by_nfa_state_set.entry(nfa_states) {
            Entry::Occupied(o) => *o.get(),
            Entry::Vacant(v) => {
                let state_id = self.table.states.len();
                self.table.states.push(LexState::default());
                self.state_queue.push_back((state_id, v.key().clone()));
                v.insert(state_id);
                state_id
            }
        }
    }

    fn populate_state(&mut self, state_id: usize, nfa_states: Vec<u32>) {
        self.cursor.reset(nfa_states);

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
            if let Some((_, completed_precedence)) = completion {
                if advance_precedence < completed_precedence {
                    continue;
                }
            }
            let next_state_id = self.add_state(next_states);
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
