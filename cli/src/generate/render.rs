use std::{
    cmp,
    collections::{HashMap, HashSet},
};

use super::{
    build_tables::Tables,
    grammars::{ExternalToken, LexicalGrammar, SyntaxGrammar, VariableType},
    nfa::CharacterSet,
    render_context::RenderContext,
    render_target::RenderTarget,
    rules::{Alias, AliasMap, Symbol, SymbolType},
    tables::{
        FieldLocation, GotoAction, LexState, LexTable, ParseTable, ParseTableEntry,
    },
};

const SMALL_STATE_THRESHOLD: usize = 64;
pub const ABI_VERSION_MIN: usize = 13;
pub const ABI_VERSION_MAX: usize = tree_sitter::LANGUAGE_VERSION;
pub const ABI_VERSION_WITH_PRIMARY_STATES: usize = 14;

pub struct Generator {
    pub language_name: String,
    pub parse_table: ParseTable,
    pub main_lex_table: LexTable,
    pub keyword_lex_table: LexTable,
    pub large_character_sets: Vec<(Option<Symbol>, CharacterSet)>,
    pub large_character_set_names: Vec<String>,
    pub large_state_count: usize,
    pub keyword_capture_token: Option<Symbol>,
    pub syntax_grammar: SyntaxGrammar,
    pub lexical_grammar: LexicalGrammar,
    pub default_aliases: AliasMap,
    pub symbol_order: HashMap<Symbol, usize>,
    pub symbol_ids: HashMap<Symbol, String>,
    pub alias_ids: HashMap<Alias, String>,
    pub unique_aliases: Vec<Alias>,
    pub symbol_map: HashMap<Symbol, Symbol>,
    pub field_names: Vec<String>,

    #[allow(unused)]
    pub abi_version: usize,
}

impl Generator {
    pub fn generate(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_language(self);

        self.add_symbol_enum(target);
        self.add_symbol_names_list(target);
        self.add_unique_symbol_map(target);
        self.add_symbol_metadata_list(target);

        if !self.field_names.is_empty() {
            self.add_field_name_enum(target);
            self.add_field_name_names_list(target);
            self.add_field_sequences(target);
        }

        if !self.parse_table.production_infos.is_empty() {
            self.add_alias_sequences(target);
        }

        self.add_non_terminal_alias_map(target);

        if self.abi_version >= ABI_VERSION_WITH_PRIMARY_STATES {
            self.add_primary_state_id_list(target);
        }

        // The required large character sets are determined through
        // generation of the lex functions. Isolate the text of the
        // lex functions so that it can be placed after the text of
        // the larget character sets.
        let prefix_text = target.buffer_ref().get_text();
        let mut used_large_set_indices : HashSet<usize> = HashSet::new();
        self.add_lex_function(target, "ts_lex", &self.main_lex_table, &mut used_large_set_indices);
        if self.keyword_capture_token.is_some() {
            self.add_lex_function(target, "ts_lex_keywords", &self.keyword_lex_table, &mut used_large_set_indices);
        }
        let lex_functions_text = target.buffer_ref().swap_text(prefix_text);

        // Once the lex functions are generated, and we've determined which large
        // character sets are actually used, we can generate the large character set
        // constants and append the lex functions text.
        for ix in used_large_set_indices.into_iter() {
            self.add_character_set(target, 
                &self.large_character_set_names[ix], 
                &self.large_character_sets[ix].1
            );
        }
        target.buffer_ref().append(lex_functions_text);

        self.add_lex_modes_list(target);
        self.add_parse_table(target);

        if !self.syntax_grammar.external_tokens.is_empty() {
            self.add_external_token_enum(target);
            self.add_external_scanner_symbol_map(target);
            self.add_external_scanner_states_list(target);
        }

        target.end_language(self);
    }

    fn init(&mut self) {
        let mut symbol_identifiers = HashSet::new();
        for i in 0..self.parse_table.symbols.len() {
            self.assign_symbol_id(self.parse_table.symbols[i], &mut symbol_identifiers);
        }
        self.symbol_ids.insert(
            Symbol::end_of_nonterminal_extra(),
            self.symbol_ids[&Symbol::end()].clone(),
        );

        self.symbol_map = HashMap::new();

        for symbol in &self.parse_table.symbols {
            let mut mapping = symbol;

            // There can be multiple symbols in the grammar that have the same name and kind,
            // due to simple aliases. When that happens, ensure that they map to the same
            // public-facing symbol. If one of the symbols is not aliased, choose that one
            // to be the public-facing symbol. Otherwise, pick the symbol with the lowest
            // numeric value.
            if let Some(alias) = self.default_aliases.get(symbol) {
                let kind = alias.kind();
                for other_symbol in &self.parse_table.symbols {
                    if let Some(other_alias) = self.default_aliases.get(other_symbol) {
                        if other_symbol < mapping && other_alias == alias {
                            mapping = other_symbol;
                        }
                    } else if self.metadata_for_symbol(*other_symbol) == (&alias.value, kind) {
                        mapping = other_symbol;
                        break;
                    }
                }
            }
            // Two anonymous tokens with different flags but the same string value
            // should be represented with the same symbol in the public API. Examples:
            // * "<" and token(prec(1, "<"))
            // * "(" and token.immediate("(")
            else if symbol.is_terminal() {
                let metadata = self.metadata_for_symbol(*symbol);
                for other_symbol in &self.parse_table.symbols {
                    let other_metadata = self.metadata_for_symbol(*other_symbol);
                    if other_metadata == metadata {
                        if let Some(mapped) = self.symbol_map.get(other_symbol) {
                            if mapped == symbol {
                                break;
                            }
                        }
                        mapping = other_symbol;
                        break;
                    }
                }
            }

            self.symbol_map.insert(*symbol, *mapping);
        }

        for production_info in &self.parse_table.production_infos {
            // Build a list of all field names
            for field_name in production_info.field_map.keys() {
                if let Err(i) = self.field_names.binary_search(field_name) {
                    self.field_names.insert(i, field_name.clone());
                }
            }

            for alias in &production_info.alias_sequence {
                // Generate a mapping from aliases to C identifiers.
                if let Some(alias) = &alias {
                    let existing_symbol = self.parse_table.symbols.iter().copied().find(|symbol| {
                        self.default_aliases.get(symbol).map_or_else(
                            || {
                                let (name, kind) = self.metadata_for_symbol(*symbol);
                                name == alias.value && kind == alias.kind()
                            },
                            |default_alias| default_alias == alias,
                        )
                    });

                    // Some aliases match an existing symbol in the grammar.
                    let alias_id = if let Some(existing_symbol) = existing_symbol {
                        self.symbol_ids[&self.symbol_map[&existing_symbol]].clone()
                    }
                    // Other aliases don't match any existing symbol, and need their own
                    // identifiers.
                    else {
                        if let Err(i) = self.unique_aliases.binary_search(alias) {
                            self.unique_aliases.insert(i, alias.clone());
                        }

                        if alias.is_named {
                            format!("alias_sym_{}", self.sanitize_identifier(&alias.value))
                        } else {
                            format!("anon_alias_sym_{}", self.sanitize_identifier(&alias.value))
                        }
                    };

                    self.alias_ids.entry(alias.clone()).or_insert(alias_id);
                }
            }
        }

        for (ix, (symbol, _)) in self.large_character_sets.iter().enumerate() {
            let count = self.large_character_sets[0..ix]
                .iter()
                .filter(|(sym, _)| sym == symbol)
                .count()
                + 1;
            let constant_name = if let Some(symbol) = symbol {
                format!("{}_character_set_{}", self.symbol_ids[symbol], count)
            } else {
                format!("extras_character_set_{count}")
            };
            self.large_character_set_names.push(constant_name);
        }

        // Determine which states should use the "small state" representation, and which should
        // use the normal array representation.
        let threshold = cmp::min(SMALL_STATE_THRESHOLD, self.parse_table.symbols.len() / 2);
        self.large_state_count = self
            .parse_table
            .states
            .iter()
            .enumerate()
            .take_while(|(i, s)| {
                *i <= 1 || s.terminal_entries.len() + s.nonterminal_entries.len() > threshold
            })
            .count();

        for (i, symbol) in self.parse_table.symbols.iter().enumerate() {
            self.symbol_order.insert(*symbol, i);
        }
    }

    fn add_symbol_enum(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_symbol_enum();
        let mut i = 1;
        for symbol in &self.parse_table.symbols {
            if *symbol != Symbol::end() {
                target.add_symbol_enum_item(&self.symbol_ids[symbol], i);
                i += 1;
            }
        }
        for alias in &self.unique_aliases {
            target.add_symbol_enum_item(&self.alias_ids[alias], i);
            i += 1;
        }
        target.end_symbol_enum();
    }

    fn add_symbol_names_list(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_symbol_names_list();
        for symbol in &self.parse_table.symbols {
            let text = self.sanitize_string(
                self.default_aliases
                    .get(symbol)
                    .map_or(self.metadata_for_symbol(*symbol).0, |alias| {
                        alias.value.as_str()
                    }),
            );
            target.add_symbol_names_list_item(&self.symbol_ids[symbol], &text);
        }
        for alias in &self.unique_aliases {
            target.add_symbol_names_list_item(&self.alias_ids[alias], &self.sanitize_string(&alias.value));
        }
        target.end_symbol_names_list();
    }

    fn add_unique_symbol_map(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_symbol_map();
        for symbol in &self.parse_table.symbols {
            target.add_symbol_map_item(&self.symbol_ids[symbol], &self.symbol_ids[&self.symbol_map[symbol]]);
        }
        for alias in &self.unique_aliases {
            target.add_symbol_map_item(&self.alias_ids[alias], &self.alias_ids[alias]);
        }
        target.end_symbol_map();
    }

    fn add_field_name_enum(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_field_enum();
        for (i, field_name) in self.field_names.iter().enumerate() {
            target.add_field_enum_item(&self.field_id(field_name), i + 1);
        }
        target.end_field_enum();
    }

    fn add_field_name_names_list(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_field_names();
        for field_name in &self.field_names {
            target.add_field_name_item(&self.field_id(field_name), field_name)
        }
        target.end_field_names();
    }

    fn add_symbol_metadata_list(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_symbol_metadata();
        for symbol in &self.parse_table.symbols {
            let (visible, named, supertype) = if let Some(Alias { is_named, .. }) = self.default_aliases.get(symbol) {
                (true, *is_named, false)
            } else {
                match self.metadata_for_symbol(*symbol).1 {
                    VariableType::Named => (true, true, false),
                    VariableType::Anonymous => (true, false, false),
                    VariableType::Hidden => (false, true, self.syntax_grammar.supertype_symbols.contains(symbol)),
                    VariableType::Auxiliary => (false, false, false)
                }
            };
            target.add_symbol_metadata_item(&self.symbol_ids[symbol], visible, named, supertype);
        };
        for alias in &self.unique_aliases {
            target.add_symbol_metadata_item(&self.alias_ids[alias], true, alias.is_named, false);
        };
        target.end_symbol_metadata();
    }

    fn add_alias_sequences(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_alias_sequences();
        for (i, production_info) in self.parse_table.production_infos.iter().enumerate() {
            let alias_ids = production_info.alias_sequence.iter().map(
                |alias| if let Some(alias) = alias { Some(&self.alias_ids[alias]) } else { None }
            );
            target.add_alias_sequences_item(i, alias_ids.collect());
        }
        target.end_alias_sequences();
    }

    fn add_non_terminal_alias_map(&self, target: &mut Box<dyn RenderTarget>) {
        let alias_ids_by_symbol = self.get_symbol_and_alias_list_pairs();
        target.begin_non_terminal_alias_map();
        for (symbol, alias_ids) in alias_ids_by_symbol {
            let symbol_id = &self.symbol_ids[&symbol];
            let public_symbol_id = &self.symbol_ids[&self.symbol_map[&symbol]];
            target.add_non_terminal_alias_map_item(symbol_id, 1 + alias_ids.len(), public_symbol_id, alias_ids);
        }
        target.end_non_terminal_alias_map();
    }

    /// Produces a list of the "primary state" for every state in the grammar.
    fn add_primary_state_id_list(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_primary_state_ids();
        let first_state_for_each_core_id: HashMap<usize, usize> = self.get_first_state_for_each_core_id();
        for (idx, state) in self.parse_table.states.iter().enumerate() {
            target.add_primary_state_ids_item(idx, first_state_for_each_core_id[&state.core_id]);
        }
        target.end_primary_state_ids();
    }

    fn add_field_sequences(&self, target: &mut Box<dyn RenderTarget>) {
        let (field_map_ids, flat_field_maps) = self.get_field_info();

        target.begin_field_map_slices();
        for (production_id, (row_id, length)) in field_map_ids.into_iter().enumerate() {
            if length > 0 {
                target.add_field_map_slices_item(production_id, row_id, length);
            }
        }
        target.end_field_map_slices();

        target.begin_field_map_entries();
        for (row_index, field_pairs) in flat_field_maps.into_iter().skip(1) {
            target.add_field_map_entries_item(row_index, field_pairs);
        }
        target.end_field_map_entries();
    }

    pub fn add_lex_function(&self, target: &mut Box<dyn RenderTarget>, name: &str, lex_table: &LexTable, used_large_set_indices: &mut HashSet<usize>) {
        target.begin_lex_function(name);
        for (i, state) in lex_table.states.iter().enumerate() {
            target.begin_lex_function_case(i);

            if let Some(accept_action) = state.accept_action {
                target.add_lex_function_case_accept_token(&self.symbol_ids[&accept_action]);
            }
    
            if let Some(eof_action) = &state.eof_action {
                target.add_lex_function_case_advance_eof(eof_action.state);
            }
    
            let mut chars_copy = CharacterSet::empty();
            let mut large_set = CharacterSet::empty();
            let mut ruled_out_chars = CharacterSet::empty();
    
            // The transitions in a lex state are sorted with the single-characte
            // transitions first. If there are many single-character transitions,
            // then implement them using an array of (lookahead character, state)
            // pairs, instead of individual if statements, in order to reduce compile
            // time.
            let leading_simple_transition_count = Generator::get_leading_simple_transition_count(state);
            if leading_simple_transition_count > 0 {
                let simple_transitions = &state.advance_actions[0..leading_simple_transition_count];
                target.add_lex_function_case_advance_map(simple_transitions);
                for (chars, _action) in simple_transitions {
                    ruled_out_chars = ruled_out_chars.add(chars);
                }
            }
    
            for (chars, action) in &state.advance_actions[leading_simple_transition_count..] {
                // The lex state's advance actions are represented with disjoint
                // sets of characters. When translating these disjoint sets into a
                // sequence of checks, we don't need to re-check conditions that
                // have already been checked due to previous transitions.
                //
                // Note that this simplification may result in an empty character set.
                // That means that the transition is guaranteed (nothing further needs to
                // be checked), not that this transition is impossible.
                let simplified_chars = chars.simplify_ignoring(&ruled_out_chars);
    
                // For large character sets, find the best matching character set from
                // a pre-selected list of large character sets, which are based on the
                // state transitions for invidual tokens. This transition may not exactly
                // match one of the pre-selected character sets. In that case, determine
                // the additional checks that need to be performed to match this transition.
                let mut best_large_char_set: Option<(usize, CharacterSet, CharacterSet)> = None;
                if simplified_chars.range_count() >= super::build_tables::LARGE_CHARACTER_RANGE_COUNT {
                    for (ix, (_, set)) in self.large_character_sets.iter().enumerate() {
                        chars_copy.assign(&simplified_chars);
                        large_set.assign(set);
                        let intersection = chars_copy.remove_intersection(&mut large_set);
                        if !intersection.is_empty() {
                            let additions = chars_copy.simplify_ignoring(&ruled_out_chars);
                            let removals = large_set.simplify_ignoring(&ruled_out_chars);
                            let total_range_count = additions.range_count() + removals.range_count();
                            if total_range_count >= simplified_chars.range_count() {
                                continue;
                            }
                            if let Some((_, best_additions, best_removals)) = &best_large_char_set {
                                let best_range_count =
                                    best_additions.range_count() + best_removals.range_count();
                                if best_range_count < total_range_count {
                                    continue;
                                }
                            }
                            best_large_char_set = Some((ix, additions, removals));
                        }
                    }
                }
    
                // Add this transition's character set to the set of ruled out characters,
                // which don't need to be checked for subsequent transitions in this state.
                ruled_out_chars = ruled_out_chars.add(chars);
    
                // Note the large character set which is chosen along with its name and whether 
                // it contains the null character (in which case its contribution to the condition
                // must check for eof).
                let mut large: Option<(&CharacterSet, &String, bool)> = None;
                let mut asserted_chars = simplified_chars;
                let mut negated_chars = CharacterSet::empty();
                if let Some((char_set_ix, additions, removals)) = best_large_char_set {
                    asserted_chars = additions;
                    negated_chars = removals;
                    large = Some((
                        &self.large_character_sets[char_set_ix].1,
                        &self.large_character_set_names[char_set_ix],
                        self.large_character_sets[char_set_ix].1.contains('\0')
                    ));
                    used_large_set_indices.insert(char_set_ix);
                };
    
                // If the character set contains the max character, than it probably
                // corresponds to a negated character class in a regex, so it will be more
                // concise and readable to express it in terms of negated ranges.
                let asserted_chars_are_inclusive = !asserted_chars.contains(char::MAX);
                if !asserted_chars_are_inclusive {
                    asserted_chars = asserted_chars.negate().add_char('\0');
                };
    
                target.add_lex_function_case_advance(
                    large, 
                    &asserted_chars, 
                    asserted_chars_are_inclusive, 
                    &negated_chars, 
                    action
                );
            }
            target.end_lex_function_case();
        }
        target.end_lex_function();
    }

    fn add_character_set(&self, target: &mut Box<dyn RenderTarget>, name: &str, characters: &CharacterSet) {
        target.begin_character_set(name);
        let mut ix : usize = 0;
        for range in characters.ranges() {
            target.add_character_set_item(ix, range);
            ix += 1;
        }
        target.end_character_set(ix);
    }

    fn add_lex_modes_list(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_lex_modes();
        for (i, state) in self.parse_table.states.iter().enumerate() {
            target.add_lex_modes_item(i, state);
        }
        target.end_lex_modes();
    }

    fn add_external_token_enum(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_external_token_enum();
        for i in 0..self.syntax_grammar.external_tokens.len() {
            target.add_external_token_enum_item(&self.external_token_id(&self.syntax_grammar.external_tokens[i]), i);
        }
        target.end_external_token_enum();
    }

    fn add_external_scanner_symbol_map(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_external_scanner_symbol_map();
        for i in 0..self.syntax_grammar.external_tokens.len() {
            let token = &self.syntax_grammar.external_tokens[i];
            let id_token = token
                .corresponding_internal_token
                .unwrap_or_else(|| Symbol::external(i));
            target.add_external_scanner_symbol_map_item(&self.external_token_id(token), &self.symbol_ids[&id_token]);
        }
        target.end_external_scanner_symbol_map();
    }

    fn add_external_scanner_states_list(&self, target: &mut Box<dyn RenderTarget>) {
        target.begin_external_scanner_states(self.parse_table.external_lex_states.len());
        for i in 0..self.parse_table.external_lex_states.len() {
            if !self.parse_table.external_lex_states[i].is_empty() {
                target.add_external_scanner_states_item(self, 
                    i, 
                    &self.parse_table.external_lex_states[i]
                );
            }
        }
        target.end_external_scanner_states();
    }

    fn add_parse_table(&self, target: &mut Box<dyn RenderTarget>) {
        let mut parse_table_entries = HashMap::new();
        let mut next_parse_action_list_index = 0;

        self.get_parse_action_list_id(
            &ParseTableEntry {
                actions: Vec::new(),
                reusable: false,
            },
            &mut parse_table_entries,
            &mut next_parse_action_list_index,
        );

        target.begin_parse_table();

        let mut terminal_entries = Vec::new();
        let mut nonterminal_entries = Vec::new();

        for (i, state) in self
            .parse_table
            .states
            .iter()
            .enumerate()
            .take(self.large_state_count)
        {
            target.begin_parse_table_section(i);

            // Ensure the entries are in a deterministic order, since they are
            // internally represented as a hash map.
            terminal_entries.clear();
            nonterminal_entries.clear();
            terminal_entries.extend(state.terminal_entries.iter());
            nonterminal_entries.extend(state.nonterminal_entries.iter());
            terminal_entries.sort_unstable_by_key(|e| self.symbol_order.get(e.0));
            nonterminal_entries.sort_unstable_by_key(|k| k.0);

            for (symbol, action) in &nonterminal_entries {
                target.add_parse_table_state_item(&self.symbol_ids[symbol],
                    match action {
                        GotoAction::Goto(state) => *state,
                        GotoAction::ShiftExtra => i,
                    }
                );
            }

            for (symbol, entry) in &terminal_entries {
                let entry_id = self.get_parse_action_list_id(
                    entry,
                    &mut parse_table_entries,
                    &mut next_parse_action_list_index,
                );
                target.add_parse_table_actions_item(entry_id, &self.symbol_ids[symbol]);
            }
            target.end_parse_table_section();
        }
        target.end_parse_table();

        if self.large_state_count < self.parse_table.states.len() {
            target.begin_small_parse_table();

            let mut index = 0;
            let mut small_state_indices = Vec::new();
            let mut symbols_by_value = HashMap::<(usize, SymbolType), Vec<Symbol>>::new();
            for state in self.parse_table.states.iter().skip(self.large_state_count) {
                small_state_indices.push(index);
                symbols_by_value.clear();

                terminal_entries.clear();
                terminal_entries.extend(state.terminal_entries.iter());
                terminal_entries.sort_unstable_by_key(|e| self.symbol_order.get(e.0));

                // In a given parse state, many lookahead symbols have the same actions.
                // So in the "small state" representation, group symbols by their action
                // in order to avoid repeating the action.
                for (symbol, entry) in &terminal_entries {
                    let entry_id = self.get_parse_action_list_id(
                        entry,
                        &mut parse_table_entries,
                        &mut next_parse_action_list_index,
                    );
                    symbols_by_value
                        .entry((entry_id, SymbolType::Terminal))
                        .or_default()
                        .push(**symbol);
                }
                for (symbol, action) in &state.nonterminal_entries {
                    let state_id = match action {
                        GotoAction::Goto(i) => *i,
                        GotoAction::ShiftExtra => {
                            self.large_state_count + small_state_indices.len() - 1
                        }
                    };
                    symbols_by_value
                        .entry((state_id, SymbolType::NonTerminal))
                        .or_default()
                        .push(*symbol);
                }

                let mut values_with_symbols = symbols_by_value.drain().collect::<Vec<_>>();
                values_with_symbols.sort_unstable_by_key(|((value, kind), symbols)| {
                    (symbols.len(), *kind, *value, symbols[0])
                });

                target.begin_small_parse_table_section(index, values_with_symbols.len());
                for ((value, kind), symbols) in &mut values_with_symbols {
                    if *kind == SymbolType::NonTerminal {
                        target.add_small_parse_table_state_item(*value, symbols.len());
                    } else {
                        target.add_small_parse_table_actions_item(*value, symbols.len()); 
                    }

                    symbols.sort_unstable();
                    for symbol in symbols {
                        target.add_small_parse_table_symbol_item(&self.symbol_ids[symbol]);
                    }
                }
                target.end_small_parse_table_section();

                index += 1 + values_with_symbols
                    .iter()
                    .map(|(_, symbols)| 2 + symbols.len())
                    .sum::<usize>();
            }

            target.end_small_parse_table();

            target.begin_small_parse_table_map();
            for i in self.large_state_count..self.parse_table.states.len() {
                target.add_small_parse_table_map_item(i, small_state_indices[i - self.large_state_count])
            }
            target.end_small_parse_table_map();
        }

        let mut parse_table_entries = parse_table_entries
            .into_iter()
            .map(|(entry, i)| (i, entry))
            .collect::<Vec<_>>();
        parse_table_entries.sort_by_key(|(index, _)| *index);
        self.add_parse_action_list(target, parse_table_entries);
    }

    fn add_parse_action_list(&self, target: &mut Box<dyn RenderTarget>, parse_table_entries: Vec<(usize, ParseTableEntry)>) {
        target.begin_parse_actions();
        for (i, entry) in parse_table_entries {
            target.begin_parse_actions_entry(i, entry.actions.len(), entry.reusable);
            for action in entry.actions {
                target.add_parse_actions_action(&action, &self.symbol_ids);
            }
            target.end_parse_actions_entry();
        }
        target.end_parse_actions();
    }

    /// The "primary state" for a given state is the first encountered state that behaves
    /// identically with respect to query analysis. We derive this by keeping track of the `core_id`
    /// for each state and treating the first state with a given `core_id` as primary.
    fn get_first_state_for_each_core_id(&self) -> HashMap<usize, usize> {
        let mut hash_map = HashMap::new();
        for (idx, state) in self.parse_table.states.iter().enumerate() {
            _ = hash_map
                .entry(state.core_id)
                .or_insert(idx);
        };
        hash_map
    }

    fn assign_symbol_id(&mut self, symbol: Symbol, used_identifiers: &mut HashSet<String>) {
        let mut id;
        if symbol == Symbol::end() {
            id = "ts_builtin_sym_end".to_string();
        } else {
            let (name, kind) = self.metadata_for_symbol(symbol);
            id = match kind {
                VariableType::Auxiliary => format!("aux_sym_{}", self.sanitize_identifier(name)),
                VariableType::Anonymous => format!("anon_sym_{}", self.sanitize_identifier(name)),
                VariableType::Hidden | VariableType::Named => {
                    format!("sym_{}", self.sanitize_identifier(name))
                }
            };

            let mut suffix_number = 1;
            let mut suffix = String::new();
            while used_identifiers.contains(&id) {
                id.drain(id.len() - suffix.len()..);
                suffix_number += 1;
                suffix = suffix_number.to_string();
                id += &suffix;
            }
        }

        used_identifiers.insert(id.clone());
        self.symbol_ids.insert(symbol, id);
    }
    
    pub fn get_parse_action_list_id(
        &self,
        entry: &ParseTableEntry,
        parse_table_entries: &mut HashMap<ParseTableEntry, usize>,
        next_parse_action_list_index: &mut usize,
    ) -> usize {
        if let Some(&index) = parse_table_entries.get(entry) {
            index
        } else {
            let result = *next_parse_action_list_index;
            parse_table_entries.insert(entry.clone(), result);
            *next_parse_action_list_index += 1 + entry.actions.len();
            result
        }
    }

    /// Calculate the field_map_ids and flat_field_maps required by add_field_sequences.
    fn get_field_info(&self) -> (Vec<(usize, usize)>, Vec<(usize, Vec<(String, FieldLocation)>)>) {
        let mut field_map_ids = Vec::new();
        let mut flat_field_maps = vec![];
        let mut next_flat_field_map_index = 0;
        let mut get_field_map_id = |flat_field_map: Vec<(String, FieldLocation)>| {
            if let Some((index, _)) = flat_field_maps.iter().find(|(_, e)| *e == *flat_field_map) {
                return *index;
            }
            let result = next_flat_field_map_index;
            next_flat_field_map_index += flat_field_map.len();
            flat_field_maps.push((result, flat_field_map));
            result
        };

        get_field_map_id(Vec::new());

        for production_info in &self.parse_table.production_infos {
            if production_info.field_map.is_empty() {
                field_map_ids.push((0, 0));
            } else {
                let mut flat_field_map = Vec::new();
                for (field_name, locations) in &production_info.field_map {
                    for location in locations {
                        flat_field_map.push((field_name.clone(), *location));
                    }
                }
                field_map_ids.push((
                    get_field_map_id(flat_field_map.clone()),
                    flat_field_map.len(),
                ));
            }
        };
        return (field_map_ids, flat_field_maps)
    }

    pub fn external_token_id(&self, token: &ExternalToken) -> String {
        format!(
            "ts_external_token_{}",
            self.sanitize_identifier(&token.name)
        )
    }

    pub fn field_id(&self, field_name: &str) -> String {
        format!("field_{field_name}")
    }

    pub fn metadata_for_symbol(&self, symbol: Symbol) -> (&str, VariableType) {
        match symbol.kind {
            SymbolType::End | SymbolType::EndOfNonTerminalExtra => ("end", VariableType::Hidden),
            SymbolType::NonTerminal => {
                let variable = &self.syntax_grammar.variables[symbol.index];
                (&variable.name, variable.kind)
            }
            SymbolType::Terminal => {
                let variable = &self.lexical_grammar.variables[symbol.index];
                (&variable.name, variable.kind)
            }
            SymbolType::External => {
                let token = &self.syntax_grammar.external_tokens[symbol.index];
                (&token.name, token.kind)
            }
        }
    }

    fn get_symbol_and_alias_list_pairs<'a>(&'a self) -> Vec<(Symbol, Vec<&'a String>)> {
        // create a map of symbols to lists of alias names
        let mut alias_ids_by_symbol: HashMap<Symbol, Vec<&String>> = HashMap::new();
        for variable in &self.syntax_grammar.variables {
            for production in &variable.productions {
                for step in &production.steps {
                    if let Some(alias) = &step.alias {
                        if step.symbol.is_non_terminal()
                            && Some(alias) != self.default_aliases.get(&step.symbol)
                            && self.symbol_ids.contains_key(&step.symbol)
                        {
                            if let Some(alias_id) = self.alias_ids.get(alias) {
                                let alias_ids =
                                    alias_ids_by_symbol.entry(step.symbol).or_insert(Vec::new());
                                if let Err(i) = alias_ids.binary_search(&alias_id) {
                                    alias_ids.insert(i, alias_id);
                                }
                            }
                        }
                    }
                }
            }
        }
        // convert to a list of pairs, taking ownership of both key and value
        let mut pairs_of_symbol_and_alias_ids: Vec<(Symbol, Vec<&String>)> = 
            alias_ids_by_symbol.into_iter()
            .collect();
        pairs_of_symbol_and_alias_ids.sort_unstable_by_key(|e| e.0);
        pairs_of_symbol_and_alias_ids
    }

    pub fn get_leading_simple_transition_count(state: &LexState) -> usize {
        let mut leading_simple_transition_count = 0;
        let mut leading_simple_transition_range_count = 0;
        for (chars, action) in &state.advance_actions {
            if action.in_main_token
                && chars.ranges().all(|r| {
                    let start = *r.start() as u32;
                    let end = *r.end() as u32;
                    end <= start + 1 && end <= u16::MAX as u32
                })
            {
                leading_simple_transition_count += 1;
                leading_simple_transition_range_count += chars.range_count();
            } else {
                break;
            }
        };
        if leading_simple_transition_range_count >= 8 {
            leading_simple_transition_count
        } else {
            0
        }
    }

    fn sanitize_identifier(&self, name: &str) -> String {
        let mut result = String::with_capacity(name.len());
        for c in name.chars() {
            if c.is_ascii_alphanumeric() || c == '_' {
                result.push(c);
            } else {
                'special_chars: {
                    let replacement = match c {
                        ' ' if name.len() == 1 => "SPACE",
                        '~' => "TILDE",
                        '`' => "BQUOTE",
                        '!' => "BANG",
                        '@' => "AT",
                        '#' => "POUND",
                        '$' => "DOLLAR",
                        '%' => "PERCENT",
                        '^' => "CARET",
                        '&' => "AMP",
                        '*' => "STAR",
                        '(' => "LPAREN",
                        ')' => "RPAREN",
                        '-' => "DASH",
                        '+' => "PLUS",
                        '=' => "EQ",
                        '{' => "LBRACE",
                        '}' => "RBRACE",
                        '[' => "LBRACK",
                        ']' => "RBRACK",
                        '\\' => "BSLASH",
                        '|' => "PIPE",
                        ':' => "COLON",
                        ';' => "SEMI",
                        '"' => "DQUOTE",
                        '\'' => "SQUOTE",
                        '<' => "LT",
                        '>' => "GT",
                        ',' => "COMMA",
                        '.' => "DOT",
                        '?' => "QMARK",
                        '/' => "SLASH",
                        '\n' => "LF",
                        '\r' => "CR",
                        '\t' => "TAB",
                        '\0' => "NULL",
                        '\u{0001}' => "SOH",
                        '\u{0002}' => "STX",
                        '\u{0003}' => "ETX",
                        '\u{0004}' => "EOT",
                        '\u{0005}' => "ENQ",
                        '\u{0006}' => "ACK",
                        '\u{0007}' => "BEL",
                        '\u{0008}' => "BS",
                        '\u{000b}' => "VTAB",
                        '\u{000c}' => "FF",
                        '\u{000e}' => "SO",
                        '\u{000f}' => "SI",
                        '\u{0010}' => "DLE",
                        '\u{0011}' => "DC1",
                        '\u{0012}' => "DC2",
                        '\u{0013}' => "DC3",
                        '\u{0014}' => "DC4",
                        '\u{0015}' => "NAK",
                        '\u{0016}' => "SYN",
                        '\u{0017}' => "ETB",
                        '\u{0018}' => "CAN",
                        '\u{0019}' => "EM",
                        '\u{001a}' => "SUB",
                        '\u{001b}' => "ESC",
                        '\u{001c}' => "FS",
                        '\u{001d}' => "GS",
                        '\u{001e}' => "RS",
                        '\u{001f}' => "US",
                        '\u{007F}' => "DEL",
                        '\u{FEFF}' => "BOM",
                        '\u{0080}'..='\u{FFFF}' => {
                            result.push_str(&format!("u{:04x}", c as u32));
                            break 'special_chars;
                        }
                        '\u{10000}'..='\u{10FFFF}' => {
                            result.push_str(&format!("U{:08x}", c as u32));
                            break 'special_chars;
                        }
                        '0'..='9' | 'a'..='z' | 'A'..='Z' | '_' => unreachable!(),
                        ' ' => break 'special_chars,
                    };
                    if !result.is_empty() && !result.ends_with('_') {
                        result.push('_');
                    }
                    result += replacement;
                }
            }
        }
        result
    }

    pub fn sanitize_string(&self, name: &str) -> String {
        let mut result = String::with_capacity(name.len());
        for c in name.chars() {
            match c {
                '\"' => result += "\\\"",
                '?' => result += "\\?",
                '\\' => result += "\\\\",
                '\u{0007}' => result += "\\a",
                '\u{0008}' => result += "\\b",
                '\u{000b}' => result += "\\v",
                '\u{000c}' => result += "\\f",
                '\n' => result += "\\n",
                '\r' => result += "\\r",
                '\t' => result += "\\t",
                '\0' => result += "\\0",
                '\u{0001}'..='\u{001f}' => result += &format!("\\x{:02x}", c as u32),
                '\u{007F}'..='\u{FFFF}' => result += &format!("\\u{:04x}", c as u32),
                '\u{10000}'..='\u{10FFFF}' => {
                    result.push_str(&format!("\\U{:08x}", c as u32));
                }
                _ => result.push(c),
            }
        }
        result
    }
}

impl RenderContext for Generator {
    fn get_language_name(&self) -> &str {
        self.language_name.as_ref()
    }

    fn get_abi_version(&self) -> usize {
        self.abi_version
    }

    fn get_state_count(&self) -> usize {
        self.parse_table.states.len()
    }

    fn get_large_state_count(&self) -> usize {
        self.large_state_count
    }

    fn get_symbol_count(&self) -> usize {
        self.parse_table.symbols.len()
    }

    fn get_alias_count(&self) -> usize {
        self.unique_aliases.len()
    }

    fn get_token_count(&self) -> usize {
        self.parse_table
        .symbols
        .iter()
        .filter(|symbol| {
            if symbol.is_terminal() || symbol.is_eof() {
                true
            } else if symbol.is_external() {
                self.syntax_grammar.external_tokens[symbol.index]
                    .corresponding_internal_token
                    .is_none()
            } else {
                false
            }
        })
        .count()
    }

    fn get_external_token_count(&self) -> usize {
        self.syntax_grammar.external_tokens.len()
    }

    fn get_field_count(&self) -> usize {
        self.field_names.len()
    }

    fn get_max_alias_sequence_length(&self) -> usize {
        self.parse_table.max_aliased_production_length
    }

    fn get_production_id_count(&self) -> usize {
        self.parse_table.production_infos.len()
    }

    fn get_main_lex_table_state_count(&self) -> usize {
        self.main_lex_table.states.len()
    }

    fn get_keyword_capture_token_id(&self) -> Option<String> {
        self.keyword_capture_token.map(|t| self.symbol_ids[&t].clone())
    }

    fn get_external_token_id(&self, index: usize) -> String {
        self.external_token_id(&self.syntax_grammar.external_tokens[index])
    }
}


impl Generator {
    /// Create an instance which can be used to render a grammar with the given properties.
    ///
    /// # Arguments
    ///
    /// * `language_name` - A string slice containing the name of the language
    /// * `tables` - Contains the parse table, the lex tables and the keyword capture token
    /// * `syntax_grammar` - The syntax grammar extracted from the language's grammar
    /// * `lexical_grammar` - The lexical grammar extracted from the language's grammar
    /// * `default_aliases` - A map describing the global rename rules that should apply. the keys are
    ///   symbols that are *always* aliased in the same way, and the values are the aliases that are
    ///   applied to those symbols.
    /// * `abi_version` - The language ABI version that should be generated. Usually you want
    ///   Tree-sitter's current version, but right after making an ABI change, it may be useful to
    ///   generate code with the previous ABI.

    pub fn new(language_name: String, tables: Tables, syntax_grammar: SyntaxGrammar, lexical_grammar: LexicalGrammar, default_aliases: AliasMap, abi_version: usize) -> Self {
        assert!(
            (ABI_VERSION_MIN..=ABI_VERSION_MAX).contains(&abi_version),
            "This version of Tree-sitter can only generate parsers with ABI version {ABI_VERSION_MIN} - {ABI_VERSION_MAX}, not {abi_version}",
        );
        let mut instance = Self {
            language_name,
            large_state_count: 0,
            parse_table: tables.parse_table,
            main_lex_table: tables.main_lex_table,
            keyword_lex_table: tables.keyword_lex_table,
            keyword_capture_token: tables.word_token,
            large_character_sets: tables.large_character_sets,
            large_character_set_names: Vec::new(),
            syntax_grammar,
            lexical_grammar,
            default_aliases,
            symbol_ids: HashMap::new(),
            symbol_order: HashMap::new(),
            alias_ids: HashMap::new(),
            symbol_map: HashMap::new(),
            unique_aliases: Vec::new(),
            field_names: Vec::new(),
            abi_version,
        };
        instance.init();
        instance
    }
}
