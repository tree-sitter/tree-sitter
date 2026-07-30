use std::{
    collections::{VecDeque, hash_map::Entry},
    mem,
};

use rustc_hash::FxHashMap;

use log::debug;

use super::{coincident_tokens::CoincidentTokenIndex, token_conflicts::TokenConflictMap};
use crate::{
    dedup::split_state_id_groups,
    grammars::{LexicalGrammar, SyntaxGrammar},
    nfa::{CharacterSet, NfaCursor},
    rules::{Symbol, TokenSet},
    tables::{AdvanceAction, LexState, LexTable, ParseStateId, ParseTable},
};

pub const LARGE_CHARACTER_RANGE_COUNT: usize = 8;

pub struct LexTables {
    pub main_lex_table: LexTable,
    pub keyword_lex_table: LexTable,
    pub large_character_sets: Vec<(Option<Symbol>, CharacterSet)>,
}

struct TokenSetGroup {
    tokens: TokenSet,
    parse_state_ids: Vec<ParseStateId>,
    separator_consumption_chars: CharacterSet,
}

pub fn build_lex_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    keywords: &TokenSet,
    coincident_token_index: &CoincidentTokenIndex,
    token_conflict_map: &TokenConflictMap,
) -> LexTables {
    let keyword_lex_table = if syntax_grammar.word_token.is_some() {
        let mut builder = LexTableBuilder::new(lexical_grammar);
        builder.add_state_for_tokens(keywords);
        builder.table
    } else {
        LexTable::default()
    };

    let has_separator_consumption = token_conflict_map.has_any_separator_consumption();

    let mut groups = Vec::<TokenSetGroup>::new();
    for (i, state) in parse_table.states.iter().enumerate() {
        let tokens: TokenSet = state
            .terminal_entries
            .keys()
            .copied()
            .chain(state.reserved_words.iter())
            .filter_map(|token| {
                if token.is_terminal() {
                    if keywords.contains(&token) {
                        syntax_grammar.word_token
                    } else {
                        Some(token)
                    }
                } else if token.is_eof() {
                    Some(token)
                } else {
                    None
                }
            })
            .collect();
        let separator_consumption_chars = if has_separator_consumption {
            token_conflict_map.separator_consumption_chars_for(tokens.terminals())
        } else {
            CharacterSet::empty()
        };

        let mut did_merge = false;
        for group in &mut groups {
            // Sets that disagree on consuming separator characters must not
            // share a lex state, or the innocent one advances where it skips.
            if group.separator_consumption_chars == separator_consumption_chars
                && merge_token_set(
                    &mut group.tokens,
                    &tokens,
                    token_conflict_map,
                    coincident_token_index,
                )
            {
                did_merge = true;
                group.parse_state_ids.push(i);
                break;
            }
        }

        if !did_merge {
            groups.push(TokenSetGroup {
                tokens,
                parse_state_ids: vec![i],
                separator_consumption_chars,
            });
        }
    }

    let mut builder = LexTableBuilder::new(lexical_grammar);
    for group in groups {
        let lex_state_id = builder.add_state_for_tokens(&group.tokens);
        for id in group.parse_state_ids {
            parse_table.states[id].lex_state_id = lex_state_id;
        }
    }

    let mut main_lex_table = mem::take(&mut builder.table);
    minimize_lex_table(&mut main_lex_table, parse_table);
    sort_states(&mut main_lex_table, parse_table);

    let mut large_character_sets = Vec::new();
    for (variable_ix, _variable) in lexical_grammar.variables.iter().enumerate() {
        let symbol = Symbol::terminal(variable_ix);
        builder.reset();
        builder.add_state_for_tokens(&TokenSet::from_iter([symbol]));
        for state in &builder.table.states {
            let mut characters = CharacterSet::empty();
            for (chars, action) in &state.advance_actions {
                if action.in_main_token {
                    characters = characters.add(chars);
                    continue;
                }

                if chars.range_count() > LARGE_CHARACTER_RANGE_COUNT
                    && !large_character_sets.iter().any(|(_, set)| set == chars)
                {
                    large_character_sets.push((None, chars.clone()));
                }
            }

            if characters.range_count() > LARGE_CHARACTER_RANGE_COUNT
                && !large_character_sets
                    .iter()
                    .any(|(_, set)| *set == characters)
            {
                large_character_sets.push((Some(symbol), characters));
            }
        }
    }

    LexTables {
        main_lex_table,
        keyword_lex_table,
        large_character_sets,
    }
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
    state_ids_by_nfa_state_set: FxHashMap<(Vec<u32>, bool), usize>,
}

impl<'a> LexTableBuilder<'a> {
    fn new(lexical_grammar: &'a LexicalGrammar) -> Self {
        Self {
            lexical_grammar,
            cursor: NfaCursor::new(&lexical_grammar.nfa, vec![]),
            table: LexTable::default(),
            state_queue: VecDeque::new(),
            state_ids_by_nfa_state_set: FxHashMap::default(),
        }
    }

    fn reset(&mut self) {
        self.table = LexTable::default();
        self.state_queue.clear();
        self.state_ids_by_nfa_state_set.clear();
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
            debug!(
                "entry point state: {state_id}, tokens: {:?}",
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
            if let Some((prev_id, prev_precedence)) = completion
                && TokenConflictMap::prefer_token(
                    self.lexical_grammar,
                    (prev_precedence, prev_id),
                    (prec, id),
                )
            {
                continue;
            }
            completion = Some((id, prec));
        }

        let (transitions, has_sep) = self.cursor.transitions_and_any_sep();

        // If EOF is a valid lookahead token, add a transition predicated on the null
        // character that leads to the empty set of NFA states.
        if eof_valid {
            let (next_state_id, _) = self.add_state(Vec::new(), false);
            self.table.states[state_id].eof_action = Some(AdvanceAction {
                state: next_state_id,
                in_main_token: true,
            });
        }

        for transition in transitions {
            if let Some((completed_id, completed_precedence)) = completion
                && !TokenConflictMap::prefer_transition(
                    self.lexical_grammar,
                    &transition,
                    completed_id,
                    completed_precedence,
                    has_sep,
                )
            {
                continue;
            }

            let (next_state_id, _) =
                self.add_state(transition.states, eof_valid && transition.is_separator);
            self.table.states[state_id].advance_actions.push((
                transition.characters,
                AdvanceAction {
                    state: next_state_id,
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

fn check_token_conflicts(
    i: usize,
    set_without_terminal: &TokenSet,
    token_conflict_map: &TokenConflictMap,
    coincident_token_index: &CoincidentTokenIndex,
) -> bool {
    let wpr = token_conflict_map.row_words;
    let row_start = i * wpr;
    let set_bits = set_without_terminal.terminal_bits_words();

    // Does terminal i conflict with or match-prefix any terminal in the set?
    let conflict_row = &token_conflict_map.conflict_or_prefix_bits[row_start..row_start + wpr];
    for (&c, &s) in conflict_row.iter().zip(set_bits) {
        if c & s != 0 {
            return true;
        }
    }

    // Does terminal i overlap (in either direction) with any non-coincident terminal in the set?
    let overlap_row = &token_conflict_map.overlap_either_bits[row_start..row_start + wpr];
    let coincident_row = &coincident_token_index.row_bits[row_start..row_start + wpr];
    for ((&o, &s), &c) in overlap_row.iter().zip(set_bits).zip(coincident_row) {
        if o & s & !c != 0 {
            return true;
        }
    }

    false
}

fn merge_token_set(
    tokens: &mut TokenSet,
    other: &TokenSet,
    token_conflict_map: &TokenConflictMap,
    coincident_token_index: &CoincidentTokenIndex,
) -> bool {
    if tokens
        .terminals()
        .filter(|terminal| !other.contains_terminal(terminal.index))
        .any(|terminal| {
            check_token_conflicts(
                terminal.index,
                other,
                token_conflict_map,
                coincident_token_index,
            )
        })
    {
        return false;
    }

    if other
        .terminals()
        .filter(|terminal| !tokens.contains_terminal(terminal.index))
        .any(|terminal| {
            check_token_conflicts(
                terminal.index,
                tokens,
                token_conflict_map,
                coincident_token_index,
            )
        })
    {
        return false;
    }

    tokens.insert_all(other);
    true
}

fn minimize_lex_table(table: &mut LexTable, parse_table: &mut ParseTable) {
    // Initially group the states by their accept action and their
    // valid lookahead characters.
    let mut state_ids_by_signature = FxHashMap::default();
    for (i, state) in table.states.iter().enumerate() {
        let signature = (
            i == 0,
            state.accept_action,
            state.eof_action.is_some(),
            state
                .advance_actions
                .iter()
                .map(|(characters, action)| (characters.clone(), action.in_main_token))
                .collect::<Vec<_>>(),
        );
        state_ids_by_signature
            .entry(signature)
            .or_insert(Vec::new())
            .push(i);
    }
    let mut state_ids_by_group_id = state_ids_by_signature
        .into_iter()
        .map(|e| e.1)
        .collect::<Vec<_>>();
    state_ids_by_group_id.sort();
    let error_group_index = state_ids_by_group_id
        .iter()
        .position(|g| g.contains(&0))
        .unwrap();
    state_ids_by_group_id.swap(error_group_index, 0);

    let mut group_ids_by_state_id = vec![0; table.states.len()];
    for (group_id, state_ids) in state_ids_by_group_id.iter().enumerate() {
        for state_id in state_ids {
            group_ids_by_state_id[*state_id] = group_id;
        }
    }

    while split_state_id_groups(
        &table.states,
        &mut state_ids_by_group_id,
        &mut group_ids_by_state_id,
        1,
        lex_states_differ,
    ) {}

    let mut new_states = Vec::with_capacity(state_ids_by_group_id.len());
    for state_ids in &state_ids_by_group_id {
        let mut new_state = LexState::default();
        mem::swap(&mut new_state, &mut table.states[state_ids[0]]);

        for (_, advance_action) in &mut new_state.advance_actions {
            advance_action.state = group_ids_by_state_id[advance_action.state];
        }
        if let Some(eof_action) = &mut new_state.eof_action {
            eof_action.state = group_ids_by_state_id[eof_action.state];
        }
        new_states.push(new_state);
    }

    for state in &mut parse_table.states {
        state.lex_state_id = group_ids_by_state_id[state.lex_state_id];
    }

    table.states = new_states;
}

fn lex_states_differ(left: &LexState, right: &LexState, group_ids_by_state_id: &[usize]) -> bool {
    left.advance_actions
        .iter()
        .zip(right.advance_actions.iter())
        .any(|(left, right)| {
            group_ids_by_state_id[left.1.state] != group_ids_by_state_id[right.1.state]
        })
}

fn sort_states(table: &mut LexTable, parse_table: &mut ParseTable) {
    // Get a mapping of old state index -> new_state_index
    let mut old_ids_by_new_id = (0..table.states.len()).collect::<Vec<_>>();
    old_ids_by_new_id[1..].sort_by_key(|id| &table.states[*id]);

    // Get the inverse mapping
    let mut new_ids_by_old_id = vec![0; old_ids_by_new_id.len()];
    for (id, old_id) in old_ids_by_new_id.iter().enumerate() {
        new_ids_by_old_id[*old_id] = id;
    }

    // Reorder the parse states and update their references to reflect
    // the new ordering.
    table.states = old_ids_by_new_id
        .iter()
        .map(|old_id| {
            let mut state = LexState::default();
            mem::swap(&mut state, &mut table.states[*old_id]);
            for (_, advance_action) in &mut state.advance_actions {
                advance_action.state = new_ids_by_old_id[advance_action.state];
            }
            if let Some(eof_action) = &mut state.eof_action {
                eof_action.state = new_ids_by_old_id[eof_action.state];
            }
            state
        })
        .collect();

    // Update the parse table's lex state references
    for state in &mut parse_table.states {
        state.lex_state_id = new_ids_by_old_id[state.lex_state_id];
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        OptLevel,
        grammars::{InputGrammar, Variable, VariableType},
        node_types::get_variable_info,
        prepare_grammar::prepare_grammar,
        rules::Rule,
        tables::ParseState,
    };

    #[test]
    fn test_separator_chars_skipped_when_no_token_consumes_them() {
        let input_grammar = InputGrammar {
            name: "token_with_separator_prefix".to_string(),
            extra_symbols: vec![Rule::pattern("[ \\t]", "")],
            variables: vec![
                named_variable(
                    "program",
                    Rule::choice(vec![Rule::named("error_statement"), Rule::named("entry")]),
                ),
                named_variable(
                    "error_statement",
                    Rule::seq(vec![
                        Rule::string("error"),
                        Rule::string("make"),
                        Rule::choice(vec![Rule::named("flag"), Rule::Blank]),
                        Rule::named("record"),
                    ]),
                ),
                named_variable("flag", Rule::string("-f")),
                named_variable(
                    "entry",
                    Rule::seq(vec![
                        Rule::token(Rule::seq(vec![
                            Rule::pattern("\\s*", ""),
                            Rule::string(":"),
                        ])),
                        Rule::string("x"),
                    ]),
                ),
                named_variable(
                    "record",
                    Rule::seq(vec![Rule::string("{"), Rule::string("}")]),
                ),
            ],
            ..Default::default()
        };

        let (tables, lexical_grammar) = build_tables_for(&input_grammar);

        let token = |name: &str| {
            Symbol::terminal(
                lexical_grammar
                    .variables
                    .iter()
                    .position(|v| v.name == name)
                    .unwrap(),
            )
        };
        let make = token("make");
        let ws_colon = token("entry_token1");

        let space_action = |parse_state: &ParseState| {
            tables.main_lex_table.states[parse_state.lex_state_id]
                .advance_actions
                .iter()
                .find_map(|(chars, action)| chars.contains(' ').then_some(action.in_main_token))
                .unwrap()
        };

        let mut innocent_states = 0;
        for state in &tables.parse_table.states {
            if state.terminal_entries.contains_key(&make)
                && !state.terminal_entries.contains_key(&ws_colon)
            {
                innocent_states += 1;
                assert!(
                    !space_action(state),
                    "expected a skip on ' ' in a parse state expecting `make`",
                );
            }
        }
        assert!(innocent_states > 0);

        // A state owning the consuming token keeps its consume transition.
        let owner = tables
            .parse_table
            .states
            .iter()
            .find(|state| state.terminal_entries.contains_key(&ws_colon))
            .unwrap();
        assert!(space_action(owner));
    }

    fn build_tables_for(
        input_grammar: &InputGrammar,
    ) -> (crate::build_tables::Tables, LexicalGrammar) {
        let mut diagnostics = Vec::new();
        let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
            prepare_grammar(input_grammar, &mut diagnostics).unwrap();
        let variable_info =
            get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases).unwrap();
        let tables = crate::build_tables::build_tables(
            &syntax_grammar,
            &lexical_grammar,
            &simple_aliases,
            &variable_info,
            &inlines,
            None,
            OptLevel::default(),
            &mut diagnostics,
        )
        .unwrap();
        (tables, lexical_grammar)
    }

    fn named_variable(name: &str, rule: Rule) -> Variable {
        Variable {
            name: name.to_string(),
            kind: VariableType::Named,
            rule,
        }
    }

    #[test]
    fn test_clean_grammar_scores_no_consumption_at_any_parse_state() {
        let input_grammar = InputGrammar {
            name: "clean_grammar".to_string(),
            extra_symbols: vec![Rule::pattern("\\s", "")],
            variables: vec![named_variable(
                "program",
                Rule::seq(vec![Rule::string("make"), Rule::string(":")]),
            )],
            ..Default::default()
        };

        let (tables, lexical_grammar) = build_tables_for(&input_grammar);
        let token_conflict_map = TokenConflictMap::new(
            &lexical_grammar,
            vec![TokenSet::new(); lexical_grammar.variables.len()],
        );

        // Empty everywhere means neither gate can refuse a merge the old rules
        // accept.
        assert!(!token_conflict_map.has_any_separator_consumption());
        for state in &tables.parse_table.states {
            assert_eq!(
                token_conflict_map.separator_consumption_chars_for(
                    state
                        .terminal_entries
                        .keys()
                        .copied()
                        .chain(state.reserved_words.iter())
                ),
                CharacterSet::empty(),
            );
        }
    }

    #[test]
    fn test_states_with_divergent_separator_prefixes_do_not_share_lex_states() {
        let input_grammar = InputGrammar {
            name: "tokens_with_divergent_separator_prefixes".to_string(),
            extra_symbols: vec![Rule::pattern("\\s", "")],
            variables: vec![
                named_variable(
                    "program",
                    Rule::choice(vec![Rule::named("a"), Rule::named("b"), Rule::named("c")]),
                ),
                named_variable(
                    "a",
                    Rule::seq(vec![
                        Rule::string("1"),
                        Rule::choice(vec![Rule::named("ap"), Rule::string("make")]),
                    ]),
                ),
                named_variable(
                    "b",
                    Rule::seq(vec![
                        Rule::string("2"),
                        Rule::choice(vec![Rule::named("bq"), Rule::string("zz")]),
                    ]),
                ),
                named_variable("c", Rule::seq(vec![Rule::string("3"), Rule::named("tabz")])),
                named_variable("ap", Rule::token(Rule::string(" p"))),
                named_variable("bq", Rule::token(Rule::string(" \nq"))),
                named_variable("tabz", Rule::token(Rule::string("\tz"))),
            ],
            ..Default::default()
        };

        let (tables, lexical_grammar) = build_tables_for(&input_grammar);
        let token = |name: &str| {
            Symbol::terminal(
                lexical_grammar
                    .variables
                    .iter()
                    .position(|v| v.name == name)
                    .unwrap(),
            )
        };
        let space_p = token("ap");
        let make = token("make");
        let space_newline_q = token("bq");

        // `' p'` and `' \nq'` share a first character but diverge at depth 2,
        // so their states must differ. State 0 owns both and is excluded.
        let state_owning = |own: Symbol, foreign: Symbol| {
            tables
                .parse_table
                .states
                .iter()
                .enumerate()
                .find(|(i, state)| {
                    *i != 0
                        && state.terminal_entries.contains_key(&own)
                        && !state.terminal_entries.contains_key(&foreign)
                })
                .unwrap()
                .1
        };
        let first_context = state_owning(space_p, space_newline_q);
        let second_context = state_owning(space_newline_q, space_p);
        assert!(first_context.terminal_entries.contains_key(&make));
        assert_ne!(first_context.lex_state_id, second_context.lex_state_id);
    }

    #[test]
    fn test_minimization_does_not_union_divergent_separator_consumption() {
        let input_grammar = InputGrammar {
            name: "separator_prefix_reduce_lookahead".to_string(),
            extra_symbols: vec![Rule::pattern("[ \\t\\n]", "")],
            variables: vec![
                named_variable(
                    "program",
                    Rule::choice(vec![
                        Rule::seq(vec![
                            Rule::string("a"),
                            Rule::named("item"),
                            Rule::token(Rule::seq(vec![
                                Rule::pattern("\\s*", ""),
                                Rule::string(":"),
                            ])),
                            Rule::string("x"),
                        ]),
                        Rule::seq(vec![
                            Rule::string("b"),
                            Rule::named("item"),
                            Rule::string("y"),
                        ]),
                    ]),
                ),
                named_variable(
                    "item",
                    Rule::seq(vec![Rule::string("i"), Rule::string("j")]),
                ),
            ],
            ..Default::default()
        };

        let (tables, lexical_grammar) = build_tables_for(&input_grammar);
        let token = |name: &str| {
            Symbol::terminal(
                lexical_grammar
                    .variables
                    .iter()
                    .position(|v| v.name == name)
                    .unwrap(),
            )
        };
        let ws_colon = token("program_token1");
        let y = token("y");

        // A merged same-core state would own both the `\s*:` token and `y`,
        // importing consumption into `y`'s positions. State 0 is excluded.
        assert!(
            !tables
                .parse_table
                .states
                .iter()
                .enumerate()
                .any(|(i, state)| i != 0
                    && state.terminal_entries.contains_key(&ws_colon)
                    && state.terminal_entries.contains_key(&y)),
            "a minimized parse state owns both the `\\s*:` token and `y`",
        );
    }
}
