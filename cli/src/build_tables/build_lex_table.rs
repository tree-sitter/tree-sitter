use super::item::TokenSet;
use super::token_conflicts::TokenConflictMap;
use crate::grammars::{LexicalGrammar, SyntaxGrammar};
use crate::nfa::{CharacterSet, NfaCursor, NfaTransition};
use crate::rules::Symbol;
use crate::tables::{AdvanceAction, LexState, LexTable, ParseTable};
use std::collections::hash_map::Entry;
use std::collections::{BTreeMap, HashMap, VecDeque};

pub(crate) fn build_lex_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    keywords: &TokenSet,
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

    let mut builder = LexTableBuilder::new(lexical_grammar);
    for state in parse_table.states.iter_mut() {
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
        state.lex_state_id = builder.add_state_for_tokens(&tokens);
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

        info!(
            "lex state: {}, completion: {:?}",
            state_id,
            completion.map(|(id, prec)| (&self.lexical_grammar.variables[id].name, prec))
        );

        let transitions = self.cursor.transitions();
        info!("lex state: {}, transitions: {:?}", state_id, transitions);

        // If EOF is a valid lookahead token, add a transition predicated on the null
        // character that leads to the empty set of NFA states.
        if eof_valid {
            let (next_state_id, _) = self.add_state(Vec::new(), false);
            info!("lex state: {}, successor: EOF", state_id);
            self.table.states[state_id].advance_actions.push((
                CharacterSet::empty().add_char('\0'),
                AdvanceAction {
                    state: Some(next_state_id),
                    in_main_token: true,
                },
            ));
        }

        for NfaTransition {
            characters,
            precedence,
            states,
            is_separator,
        } in transitions
        {
            if let Some((_, completed_precedence)) = completion {
                if precedence < completed_precedence
                    || (precedence == completed_precedence && is_separator)
                {
                    continue;
                }
            }
            let (next_state_id, _) = self.add_state(states, eof_valid && is_separator);
            let next_state = if next_state_id == state_id {
                None
            } else {
                Some(next_state_id)
            };
            self.table.states[state_id].advance_actions.push((
                characters,
                AdvanceAction {
                    state: next_state,
                    in_main_token: !is_separator,
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
