use super::{
    char_tree::{CharacterTree, Comparator},
    grammars::{ExternalToken, LexicalGrammar, SyntaxGrammar, VariableType},
    rules::{Alias, AliasMap, Symbol, SymbolType},
    tables::{
        AdvanceAction, FieldLocation, GotoAction, LexState, LexTable, ParseAction, ParseTable,
        ParseTableEntry,
    },
};
use core::ops::Range;
use std::{
    cmp,
    collections::{HashMap, HashSet},
    fmt::Write,
    mem::swap,
};

const LARGE_CHARACTER_RANGE_COUNT: usize = 8;
const SMALL_STATE_THRESHOLD: usize = 64;
const ABI_VERSION_MIN: usize = 13;
const ABI_VERSION_MAX: usize = tree_sitter::LANGUAGE_VERSION;
const ABI_VERSION_WITH_PRIMARY_STATES: usize = 14;

macro_rules! add {
    ($this: tt, $($arg: tt)*) => {{
        $this.buffer.write_fmt(format_args!($($arg)*)).unwrap();
    }}
}

macro_rules! add_whitespace {
    ($this: tt) => {{
        for _ in 0..$this.indent_level {
            write!(&mut $this.buffer, "  ").unwrap();
        }
    }};
}

macro_rules! add_line {
    ($this: tt, $($arg: tt)*) => {
        add_whitespace!($this);
        $this.buffer.write_fmt(format_args!($($arg)*)).unwrap();
        $this.buffer += "\n";
    }
}

macro_rules! indent {
    ($this: tt) => {
        $this.indent_level += 1;
    };
}

macro_rules! dedent {
    ($this: tt) => {
        assert_ne!($this.indent_level, 0);
        $this.indent_level -= 1;
    };
}

struct Generator {
    buffer: String,
    indent_level: usize,
    language_name: String,
    parse_table: ParseTable,
    main_lex_table: LexTable,
    keyword_lex_table: LexTable,
    large_state_count: usize,
    keyword_capture_token: Option<Symbol>,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    default_aliases: AliasMap,
    symbol_order: HashMap<Symbol, usize>,
    symbol_ids: HashMap<Symbol, String>,
    alias_ids: HashMap<Alias, String>,
    unique_aliases: Vec<Alias>,
    symbol_map: HashMap<Symbol, Symbol>,
    field_names: Vec<String>,

    #[allow(unused)]
    abi_version: usize,
}

struct TransitionSummary {
    is_included: bool,
    ranges: Vec<Range<char>>,
    call_id: Option<usize>,
}

struct LargeCharacterSetInfo {
    ranges: Vec<Range<char>>,
    symbol: Symbol,
    index: usize,
}

impl Generator {
    fn generate(mut self) -> String {
        self.init();
        self.add_includes();
        self.add_pragmas();
        self.add_stats();
        self.add_symbol_enum();
        self.add_symbol_names_list();
        self.add_unique_symbol_map();
        self.add_symbol_metadata_list();

        if !self.field_names.is_empty() {
            self.add_field_name_enum();
            self.add_field_name_names_list();
            self.add_field_sequences();
        }

        if !self.parse_table.production_infos.is_empty() {
            self.add_alias_sequences();
        }

        self.add_non_terminal_alias_map();

        if self.abi_version >= ABI_VERSION_WITH_PRIMARY_STATES {
            self.add_primary_state_id_list();
        }

        let mut main_lex_table = LexTable::default();
        swap(&mut main_lex_table, &mut self.main_lex_table);
        self.add_lex_function("ts_lex", main_lex_table, true);

        if self.keyword_capture_token.is_some() {
            let mut keyword_lex_table = LexTable::default();
            swap(&mut keyword_lex_table, &mut self.keyword_lex_table);
            self.add_lex_function("ts_lex_keywords", keyword_lex_table, false);
        }

        self.add_lex_modes_list();
        self.add_parse_table();

        if !self.syntax_grammar.external_tokens.is_empty() {
            self.add_external_token_enum();
            self.add_external_scanner_symbol_map();
            self.add_external_scanner_states_list();
        }

        self.add_parser_export();

        self.buffer
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
            // *  "<" and token(prec(1, "<"))
            // *  "(" and token.immediate("(")
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
                    let alias_id;
                    if let Some(existing_symbol) = existing_symbol {
                        alias_id = self.symbol_ids[&self.symbol_map[&existing_symbol]].clone();
                    }
                    // Other aliases don't match any existing symbol, and need their own identifiers.
                    else {
                        if let Err(i) = self.unique_aliases.binary_search(alias) {
                            self.unique_aliases.insert(i, alias.clone());
                        }

                        alias_id = if alias.is_named {
                            format!("alias_sym_{}", self.sanitize_identifier(&alias.value))
                        } else {
                            format!("anon_alias_sym_{}", self.sanitize_identifier(&alias.value))
                        };
                    }

                    self.alias_ids.entry(alias.clone()).or_insert(alias_id);
                }
            }
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
    }

    fn add_includes(&mut self) {
        add_line!(self, "#include \"tree_sitter/parser.h\"");
        add_line!(self, "");
    }

    fn add_pragmas(&mut self) {
        add_line!(self, "#if defined(__GNUC__) || defined(__clang__)");
        add_line!(self, "#pragma GCC diagnostic push");
        add_line!(
            self,
            "#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\""
        );
        add_line!(self, "#endif");
        add_line!(self, "");

        // Compiling large lexer functions can be very slow. Disabling optimizations
        // is not ideal, but only a very small fraction of overall parse time is
        // spent lexing, so the performance impact of this is negligible.
        if self.main_lex_table.states.len() > 300 {
            add_line!(self, "#ifdef _MSC_VER");
            add_line!(self, "#pragma optimize(\"\", off)");
            add_line!(self, "#elif defined(__clang__)");
            add_line!(self, "#pragma clang optimize off");
            add_line!(self, "#elif defined(__GNUC__)");
            add_line!(self, "#pragma GCC optimize (\"O0\")");
            add_line!(self, "#endif");
            add_line!(self, "");
        }
    }

    fn add_stats(&mut self) {
        let token_count = self
            .parse_table
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
            .count();

        add_line!(self, "#define LANGUAGE_VERSION {}", self.abi_version);
        add_line!(
            self,
            "#define STATE_COUNT {}",
            self.parse_table.states.len()
        );
        add_line!(self, "#define LARGE_STATE_COUNT {}", self.large_state_count);

        add_line!(
            self,
            "#define SYMBOL_COUNT {}",
            self.parse_table.symbols.len()
        );
        add_line!(self, "#define ALIAS_COUNT {}", self.unique_aliases.len());
        add_line!(self, "#define TOKEN_COUNT {}", token_count);
        add_line!(
            self,
            "#define EXTERNAL_TOKEN_COUNT {}",
            self.syntax_grammar.external_tokens.len()
        );
        add_line!(self, "#define FIELD_COUNT {}", self.field_names.len());
        add_line!(
            self,
            "#define MAX_ALIAS_SEQUENCE_LENGTH {}",
            self.parse_table.max_aliased_production_length
        );
        add_line!(
            self,
            "#define PRODUCTION_ID_COUNT {}",
            self.parse_table.production_infos.len()
        );
        add_line!(self, "");
    }

    fn add_symbol_enum(&mut self) {
        add_line!(self, "enum ts_symbol_identifiers {{");
        indent!(self);
        self.symbol_order.insert(Symbol::end(), 0);
        let mut i = 1;
        for symbol in &self.parse_table.symbols {
            if *symbol != Symbol::end() {
                self.symbol_order.insert(*symbol, i);
                add_line!(self, "{} = {},", self.symbol_ids[&symbol], i);
                i += 1;
            }
        }
        for alias in &self.unique_aliases {
            add_line!(self, "{} = {},", self.alias_ids[&alias], i);
            i += 1;
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_symbol_names_list(&mut self) {
        add_line!(self, "static const char * const ts_symbol_names[] = {{");
        indent!(self);
        for symbol in &self.parse_table.symbols {
            let name = self.sanitize_string(
                self.default_aliases
                    .get(symbol)
                    .map_or(self.metadata_for_symbol(*symbol).0, |alias| {
                        alias.value.as_str()
                    }),
            );
            add_line!(self, "[{}] = \"{}\",", self.symbol_ids[&symbol], name);
        }
        for alias in &self.unique_aliases {
            add_line!(
                self,
                "[{}] = \"{}\",",
                self.alias_ids[&alias],
                self.sanitize_string(&alias.value)
            );
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_unique_symbol_map(&mut self) {
        add_line!(self, "static const TSSymbol ts_symbol_map[] = {{");
        indent!(self);
        for symbol in &self.parse_table.symbols {
            add_line!(
                self,
                "[{}] = {},",
                self.symbol_ids[symbol],
                self.symbol_ids[&self.symbol_map[symbol]],
            );
        }

        for alias in &self.unique_aliases {
            add_line!(
                self,
                "[{}] = {},",
                self.alias_ids[&alias],
                self.alias_ids[&alias],
            );
        }

        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_field_name_enum(&mut self) {
        add_line!(self, "enum ts_field_identifiers {{");
        indent!(self);
        for (i, field_name) in self.field_names.iter().enumerate() {
            add_line!(self, "{} = {},", self.field_id(field_name), i + 1);
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_field_name_names_list(&mut self) {
        add_line!(self, "static const char * const ts_field_names[] = {{");
        indent!(self);
        add_line!(self, "[0] = NULL,");
        for field_name in &self.field_names {
            add_line!(
                self,
                "[{}] = \"{}\",",
                self.field_id(field_name),
                field_name
            );
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_symbol_metadata_list(&mut self) {
        add_line!(
            self,
            "static const TSSymbolMetadata ts_symbol_metadata[] = {{"
        );
        indent!(self);
        for symbol in &self.parse_table.symbols {
            add_line!(self, "[{}] = {{", self.symbol_ids[&symbol]);
            indent!(self);
            if let Some(Alias { is_named, .. }) = self.default_aliases.get(symbol) {
                add_line!(self, ".visible = true,");
                add_line!(self, ".named = {},", is_named);
            } else {
                match self.metadata_for_symbol(*symbol).1 {
                    VariableType::Named => {
                        add_line!(self, ".visible = true,");
                        add_line!(self, ".named = true,");
                    }
                    VariableType::Anonymous => {
                        add_line!(self, ".visible = true,");
                        add_line!(self, ".named = false,");
                    }
                    VariableType::Hidden => {
                        add_line!(self, ".visible = false,");
                        add_line!(self, ".named = true,");
                        if self.syntax_grammar.supertype_symbols.contains(symbol) {
                            add_line!(self, ".supertype = true,");
                        }
                    }
                    VariableType::Auxiliary => {
                        add_line!(self, ".visible = false,");
                        add_line!(self, ".named = false,");
                    }
                }
            }
            dedent!(self);
            add_line!(self, "}},");
        }
        for alias in &self.unique_aliases {
            add_line!(self, "[{}] = {{", self.alias_ids[&alias]);
            indent!(self);
            add_line!(self, ".visible = true,");
            add_line!(self, ".named = {},", alias.is_named);
            dedent!(self);
            add_line!(self, "}},");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_alias_sequences(&mut self) {
        add_line!(
            self,
            "static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {{",
        );
        indent!(self);
        for (i, production_info) in self.parse_table.production_infos.iter().enumerate() {
            if production_info.alias_sequence.is_empty() {
                // Work around MSVC's intolerance of empty array initializers by
                // explicitly zero-initializing the first element.
                if i == 0 {
                    add_line!(self, "[0] = {{0}},");
                }
                continue;
            }

            add_line!(self, "[{}] = {{", i);
            indent!(self);
            for (j, alias) in production_info.alias_sequence.iter().enumerate() {
                if let Some(alias) = alias {
                    add_line!(self, "[{}] = {},", j, self.alias_ids[&alias]);
                }
            }
            dedent!(self);
            add_line!(self, "}},");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_non_terminal_alias_map(&mut self) {
        let mut alias_ids_by_symbol = HashMap::new();
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

        let mut alias_ids_by_symbol = alias_ids_by_symbol.iter().collect::<Vec<_>>();
        alias_ids_by_symbol.sort_unstable_by_key(|e| e.0);

        add_line!(
            self,
            "static const uint16_t ts_non_terminal_alias_map[] = {{"
        );
        indent!(self);
        for (symbol, alias_ids) in alias_ids_by_symbol {
            let symbol_id = &self.symbol_ids[symbol];
            let public_symbol_id = &self.symbol_ids[&self.symbol_map[&symbol]];
            add_line!(self, "{symbol_id}, {},", 1 + alias_ids.len());
            indent!(self);
            add_line!(self, "{public_symbol_id},");
            for alias_id in alias_ids {
                add_line!(self, "{alias_id},");
            }
            dedent!(self);
        }
        add_line!(self, "0,");
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    /// Produces a list of the "primary state" for every state in the grammar.
    ///
    /// The "primary state" for a given state is the first encountered state that behaves
    /// identically with respect to query analysis. We derive this by keeping track of the `core_id`
    /// for each state and treating the first state with a given `core_id` as primary.
    fn add_primary_state_id_list(&mut self) {
        add_line!(
            self,
            "static const TSStateId ts_primary_state_ids[STATE_COUNT] = {{"
        );
        indent!(self);
        let mut first_state_for_each_core_id = HashMap::new();
        for (idx, state) in self.parse_table.states.iter().enumerate() {
            let primary_state = first_state_for_each_core_id
                .entry(state.core_id)
                .or_insert(idx);
            add_line!(self, "[{idx}] = {primary_state},");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_field_sequences(&mut self) {
        let mut flat_field_maps = vec![];
        let mut next_flat_field_map_index = 0;
        self.get_field_map_id(
            &Vec::new(),
            &mut flat_field_maps,
            &mut next_flat_field_map_index,
        );

        let mut field_map_ids = Vec::new();
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
                    self.get_field_map_id(
                        &flat_field_map,
                        &mut flat_field_maps,
                        &mut next_flat_field_map_index,
                    ),
                    flat_field_map.len(),
                ));
            }
        }

        add_line!(
            self,
            "static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {{",
        );
        indent!(self);
        for (production_id, (row_id, length)) in field_map_ids.into_iter().enumerate() {
            if length > 0 {
                add_line!(
                    self,
                    "[{production_id}] = {{.index = {row_id}, .length = {length}}},",
                );
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");

        add_line!(
            self,
            "static const TSFieldMapEntry ts_field_map_entries[] = {{",
        );
        indent!(self);
        for (row_index, field_pairs) in flat_field_maps.into_iter().skip(1) {
            add_line!(self, "[{row_index}] =");
            indent!(self);
            for (field_name, location) in field_pairs {
                add_whitespace!(self);
                add!(self, "{{{}, {}", self.field_id(&field_name), location.index);
                if location.inherited {
                    add!(self, ", .inherited = true");
                }
                add!(self, "}},\n");
            }
            dedent!(self);
        }

        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_lex_function(
        &mut self,
        name: &str,
        lex_table: LexTable,
        extract_helper_functions: bool,
    ) {
        let mut ruled_out_chars = HashSet::new();
        let mut large_character_sets = Vec::<LargeCharacterSetInfo>::new();

        // For each lex state, compute a summary of the code that needs to be
        // generated.
        let state_transition_summaries: Vec<Vec<TransitionSummary>> = lex_table
            .states
            .iter()
            .map(|state| {
                ruled_out_chars.clear();

                // For each state transition, compute the set of character ranges
                // that need to be checked.
                state
                    .advance_actions
                    .iter()
                    .map(|(chars, action)| {
                        let is_included = !chars.contains(std::char::MAX);
                        let mut ranges;
                        if is_included {
                            ranges = chars.simplify_ignoring(&ruled_out_chars);
                            ruled_out_chars.extend(chars.iter());
                        } else {
                            ranges = chars.clone().negate().simplify_ignoring(&ruled_out_chars);
                            ranges.insert(0, '\0'..'\0');
                        }

                        // Record any large character sets so that they can be extracted
                        // into helper functions, reducing code duplication.
                        let mut call_id = None;
                        if extract_helper_functions && ranges.len() > LARGE_CHARACTER_RANGE_COUNT {
                            let char_set_symbol = self
                                .symbol_for_advance_action(action, &lex_table)
                                .expect("No symbol for lex state");
                            let mut count_for_symbol = 0;
                            for (i, info) in large_character_sets.iter_mut().enumerate() {
                                if info.ranges == ranges {
                                    call_id = Some(i);
                                    break;
                                }
                                if info.symbol == char_set_symbol {
                                    count_for_symbol += 1;
                                }
                            }
                            if call_id.is_none() {
                                call_id = Some(large_character_sets.len());
                                large_character_sets.push(LargeCharacterSetInfo {
                                    symbol: char_set_symbol,
                                    index: count_for_symbol + 1,
                                    ranges: ranges.clone(),
                                });
                            }
                        }

                        TransitionSummary {
                            is_included,
                            ranges,
                            call_id,
                        }
                    })
                    .collect()
            })
            .collect();

        // Generate a helper function for each large character set.
        let mut sorted_large_char_sets = large_character_sets.iter().collect::<Vec<_>>();
        sorted_large_char_sets.sort_unstable_by_key(|info| (info.symbol, info.index));
        for info in sorted_large_char_sets {
            add_line!(
                self,
                "static inline bool {}_character_set_{}(int32_t c) {{",
                self.symbol_ids[&info.symbol],
                info.index
            );
            indent!(self);
            add_whitespace!(self);
            add!(self, "return ");
            let tree = CharacterTree::from_ranges(&info.ranges);
            self.add_character_tree(tree.as_ref());
            add!(self, ";\n");
            dedent!(self);
            add_line!(self, "}}");
            add_line!(self, "");
        }

        add_line!(
            self,
            "static bool {name}(TSLexer *lexer, TSStateId state) {{",
        );
        indent!(self);

        add_line!(self, "START_LEXER();");
        add_line!(self, "eof = lexer->eof(lexer);");
        add_line!(self, "switch (state) {{");

        indent!(self);
        for (i, state) in lex_table.states.into_iter().enumerate() {
            add_line!(self, "case {i}:");
            indent!(self);
            self.add_lex_state(state, &state_transition_summaries[i], &large_character_sets);
            dedent!(self);
        }

        add_line!(self, "default:");
        indent!(self);
        add_line!(self, "return false;");
        dedent!(self);

        dedent!(self);
        add_line!(self, "}}");

        dedent!(self);
        add_line!(self, "}}");
        add_line!(self, "");
    }

    fn symbol_for_advance_action(
        &self,
        action: &AdvanceAction,
        lex_table: &LexTable,
    ) -> Option<Symbol> {
        let mut state_ids = vec![action.state];
        let mut i = 0;
        while i < state_ids.len() {
            let id = state_ids[i];
            let state = &lex_table.states[id];
            if let Some(accept) = state.accept_action {
                return Some(accept);
            }
            for (_, action) in &state.advance_actions {
                if !state_ids.contains(&action.state) {
                    state_ids.push(action.state);
                }
            }
            i += 1;
        }
        None
    }

    fn add_lex_state(
        &mut self,
        state: LexState,
        transition_info: &[TransitionSummary],
        large_character_sets: &[LargeCharacterSetInfo],
    ) {
        if let Some(accept_action) = state.accept_action {
            add_line!(self, "ACCEPT_TOKEN({});", self.symbol_ids[&accept_action]);
        }

        if let Some(eof_action) = state.eof_action {
            add_line!(self, "if (eof) ADVANCE({});", eof_action.state);
        }

        for (i, (_, action)) in state.advance_actions.into_iter().enumerate() {
            let transition = &transition_info[i];
            add_whitespace!(self);

            // If there is a helper function for this transition's character
            // set, then generate a call to that helper function.
            if let Some(call_id) = transition.call_id {
                let info = &large_character_sets[call_id];
                add!(self, "if (");
                if !transition.is_included {
                    add!(self, "!");
                }
                add!(
                    self,
                    "{}_character_set_{}(lookahead)) ",
                    self.symbol_ids[&info.symbol],
                    info.index
                );
                self.add_advance_action(&action);
                add!(self, "\n");
                continue;
            }

            // Otherwise, generate code to compare the lookahead character
            // with all of the character ranges.
            if !transition.ranges.is_empty() {
                add!(self, "if (");
                self.add_character_range_conditions(&transition.ranges, transition.is_included, 2);
                add!(self, ") ");
            }
            self.add_advance_action(&action);
            add!(self, "\n");
        }

        add_line!(self, "END_STATE();");
    }

    fn add_character_range_conditions(
        &mut self,
        ranges: &[Range<char>],
        is_included: bool,
        indent_count: usize,
    ) {
        let mut line_break = "\n".to_string();
        for _ in 0..self.indent_level + indent_count {
            line_break.push_str("  ");
        }

        for (i, range) in ranges.iter().enumerate() {
            if is_included {
                if i > 0 {
                    add!(self, " ||{line_break}");
                }
                if range.start == '\0' {
                    add!(self, "!eof && ");
                }
                if range.end == range.start {
                    add!(self, "lookahead == ");
                    self.add_character(range.start);
                } else if range.end as u32 == range.start as u32 + 1 {
                    add!(self, "lookahead == ");
                    self.add_character(range.start);
                    add!(self, " ||{line_break}lookahead == ");
                    self.add_character(range.end);
                } else {
                    add!(self, "(");
                    self.add_character(range.start);
                    add!(self, " <= lookahead && lookahead <= ");
                    self.add_character(range.end);
                    add!(self, ")");
                }
            } else {
                if i > 0 {
                    add!(self, " &&{line_break}");
                }
                if range.end == range.start {
                    add!(self, "lookahead != ");
                    self.add_character(range.start);
                } else if range.end as u32 == range.start as u32 + 1 {
                    add!(self, "lookahead != ");
                    self.add_character(range.start);
                    add!(self, " &&{line_break}lookahead != ");
                    self.add_character(range.end);
                } else if range.start != '\0' {
                    add!(self, "(lookahead < ");
                    self.add_character(range.start);
                    add!(self, " || ");
                    self.add_character(range.end);
                    add!(self, " < lookahead)");
                } else {
                    add!(self, "lookahead > ");
                    self.add_character(range.end);
                }
            }
        }
    }

    fn add_character_tree(&mut self, tree: Option<&CharacterTree>) {
        match tree {
            Some(CharacterTree::Compare {
                value,
                operator,
                consequence,
                alternative,
            }) => {
                let op = match operator {
                    Comparator::Less => "<",
                    Comparator::LessOrEqual => "<=",
                    Comparator::Equal => "==",
                    Comparator::GreaterOrEqual => ">=",
                };
                let consequence = consequence.as_ref().map(Box::as_ref);
                let alternative = alternative.as_ref().map(Box::as_ref);

                let simple = alternative.is_none() && consequence == Some(&CharacterTree::Yes);

                if !simple {
                    add!(self, "(");
                }

                add!(self, "c {op} ");
                self.add_character(*value);

                if !simple {
                    if alternative.is_none() {
                        add!(self, " && ");
                        self.add_character_tree(consequence);
                    } else if consequence == Some(&CharacterTree::Yes) {
                        add!(self, " || ");
                        self.add_character_tree(alternative);
                    } else {
                        add!(self, "\n");
                        indent!(self);
                        add_whitespace!(self);
                        add!(self, "? ");
                        self.add_character_tree(consequence);
                        add!(self, "\n");
                        add_whitespace!(self);
                        add!(self, ": ");
                        self.add_character_tree(alternative);
                        dedent!(self);
                    }
                }

                if !simple {
                    add!(self, ")");
                }
            }
            Some(CharacterTree::Yes) => {
                add!(self, "true");
            }
            None => {
                add!(self, "false");
            }
        }
    }

    fn add_advance_action(&mut self, action: &AdvanceAction) {
        if action.in_main_token {
            add!(self, "ADVANCE({});", action.state);
        } else {
            add!(self, "SKIP({})", action.state);
        }
    }

    fn add_lex_modes_list(&mut self) {
        add_line!(
            self,
            "static const TSLexMode ts_lex_modes[STATE_COUNT] = {{"
        );
        indent!(self);
        for (i, state) in self.parse_table.states.iter().enumerate() {
            if state.is_end_of_non_terminal_extra() {
                add_line!(self, "[{i}] = {{(TSStateId)(-1)}},");
            } else if state.external_lex_state_id > 0 {
                add_line!(
                    self,
                    "[{i}] = {{.lex_state = {}, .external_lex_state = {}}},",
                    state.lex_state_id,
                    state.external_lex_state_id
                );
            } else {
                add_line!(self, "[{i}] = {{.lex_state = {}}},", state.lex_state_id);
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_external_token_enum(&mut self) {
        add_line!(self, "enum ts_external_scanner_symbol_identifiers {{");
        indent!(self);
        for i in 0..self.syntax_grammar.external_tokens.len() {
            add_line!(
                self,
                "{} = {},",
                self.external_token_id(&self.syntax_grammar.external_tokens[i]),
                i
            );
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_external_scanner_symbol_map(&mut self) {
        add_line!(
            self,
            "static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {{"
        );
        indent!(self);
        for i in 0..self.syntax_grammar.external_tokens.len() {
            let token = &self.syntax_grammar.external_tokens[i];
            let id_token = token
                .corresponding_internal_token
                .unwrap_or_else(|| Symbol::external(i));
            add_line!(
                self,
                "[{}] = {},",
                self.external_token_id(token),
                self.symbol_ids[&id_token],
            );
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_external_scanner_states_list(&mut self) {
        add_line!(
            self,
            "static const bool ts_external_scanner_states[{}][EXTERNAL_TOKEN_COUNT] = {{",
            self.parse_table.external_lex_states.len(),
        );
        indent!(self);
        for i in 0..self.parse_table.external_lex_states.len() {
            if !self.parse_table.external_lex_states[i].is_empty() {
                add_line!(self, "[{}] = {{", i);
                indent!(self);
                for token in self.parse_table.external_lex_states[i].iter() {
                    add_line!(
                        self,
                        "[{}] = true,",
                        self.external_token_id(&self.syntax_grammar.external_tokens[token.index])
                    );
                }
                dedent!(self);
                add_line!(self, "}},");
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_parse_table(&mut self) {
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

        add_line!(
            self,
            "static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {{",
        );
        indent!(self);

        let mut terminal_entries = Vec::new();
        let mut nonterminal_entries = Vec::new();

        for (i, state) in self
            .parse_table
            .states
            .iter()
            .enumerate()
            .take(self.large_state_count)
        {
            add_line!(self, "[{}] = {{", i);
            indent!(self);

            // Ensure the entries are in a deterministic order, since they are
            // internally represented as a hash map.
            terminal_entries.clear();
            nonterminal_entries.clear();
            terminal_entries.extend(state.terminal_entries.iter());
            nonterminal_entries.extend(state.nonterminal_entries.iter());
            terminal_entries.sort_unstable_by_key(|e| self.symbol_order.get(e.0));
            nonterminal_entries.sort_unstable_by_key(|k| k.0);

            for (symbol, action) in &nonterminal_entries {
                add_line!(
                    self,
                    "[{}] = STATE({}),",
                    self.symbol_ids[symbol],
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
                add_line!(self, "[{}] = ACTIONS({entry_id}),", self.symbol_ids[symbol]);
            }
            dedent!(self);
            add_line!(self, "}},");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");

        if self.large_state_count < self.parse_table.states.len() {
            add_line!(self, "static const uint16_t ts_small_parse_table[] = {{");
            indent!(self);

            let mut index = 0;
            let mut small_state_indices = Vec::new();
            let mut symbols_by_value: HashMap<(usize, SymbolType), Vec<Symbol>> = HashMap::new();
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

                add_line!(self, "[{index}] = {},", values_with_symbols.len());
                indent!(self);

                for ((value, kind), symbols) in &mut values_with_symbols {
                    if *kind == SymbolType::NonTerminal {
                        add_line!(self, "STATE({value}), {},", symbols.len());
                    } else {
                        add_line!(self, "ACTIONS({value}), {},", symbols.len());
                    }

                    symbols.sort_unstable();
                    indent!(self);
                    for symbol in symbols {
                        add_line!(self, "{},", self.symbol_ids[symbol]);
                    }
                    dedent!(self);
                }

                dedent!(self);

                index += 1 + values_with_symbols
                    .iter()
                    .map(|(_, symbols)| 2 + symbols.len())
                    .sum::<usize>();
            }

            dedent!(self);
            add_line!(self, "}};");
            add_line!(self, "");

            add_line!(
                self,
                "static const uint32_t ts_small_parse_table_map[] = {{"
            );
            indent!(self);
            for i in self.large_state_count..self.parse_table.states.len() {
                add_line!(
                    self,
                    "[SMALL_STATE({i})] = {},",
                    small_state_indices[i - self.large_state_count]
                );
            }
            dedent!(self);
            add_line!(self, "}};");
            add_line!(self, "");
        }

        let mut parse_table_entries = parse_table_entries
            .into_iter()
            .map(|(entry, i)| (i, entry))
            .collect::<Vec<_>>();
        parse_table_entries.sort_by_key(|(index, _)| *index);
        self.add_parse_action_list(parse_table_entries);
    }

    fn add_parse_action_list(&mut self, parse_table_entries: Vec<(usize, ParseTableEntry)>) {
        add_line!(
            self,
            "static const TSParseActionEntry ts_parse_actions[] = {{"
        );
        indent!(self);
        for (i, entry) in parse_table_entries {
            add!(
                self,
                "  [{i}] = {{.entry = {{.count = {}, .reusable = {}}}}},",
                entry.actions.len(),
                entry.reusable
            );
            for action in entry.actions {
                add!(self, " ");
                match action {
                    ParseAction::Accept => add!(self, " ACCEPT_INPUT()"),
                    ParseAction::Recover => add!(self, "RECOVER()"),
                    ParseAction::ShiftExtra => add!(self, "SHIFT_EXTRA()"),
                    ParseAction::Shift {
                        state,
                        is_repetition,
                    } => {
                        if is_repetition {
                            add!(self, "SHIFT_REPEAT({state})");
                        } else {
                            add!(self, "SHIFT({state})");
                        }
                    }
                    ParseAction::Reduce {
                        symbol,
                        child_count,
                        dynamic_precedence,
                        production_id,
                        ..
                    } => {
                        add!(self, "REDUCE({}, {child_count}", self.symbol_ids[&symbol]);
                        if dynamic_precedence != 0 {
                            add!(self, ", .dynamic_precedence = {dynamic_precedence}");
                        }
                        if production_id != 0 {
                            add!(self, ", .production_id = {production_id}");
                        }
                        add!(self, ")");
                    }
                }
                add!(self, ",");
            }
            add!(self, "\n");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_parser_export(&mut self) {
        let language_function_name = format!("tree_sitter_{}", self.language_name);
        let external_scanner_name = format!("{language_function_name}_external_scanner");

        add_line!(self, "#ifdef __cplusplus");
        add_line!(self, r#"extern "C" {{"#);
        add_line!(self, "#endif");

        if !self.syntax_grammar.external_tokens.is_empty() {
            add_line!(self, "void *{external_scanner_name}_create(void);");
            add_line!(self, "void {external_scanner_name}_destroy(void *);");
            add_line!(
                self,
                "bool {external_scanner_name}_scan(void *, TSLexer *, const bool *);",
            );
            add_line!(
                self,
                "unsigned {external_scanner_name}_serialize(void *, char *);",
            );
            add_line!(
                self,
                "void {external_scanner_name}_deserialize(void *, const char *, unsigned);",
            );
            add_line!(self, "");
        }

        add_line!(self, "#ifdef _WIN32");
        add_line!(self, "#define extern __declspec(dllexport)");
        add_line!(self, "#endif");
        add_line!(self, "");

        add_line!(
            self,
            "extern const TSLanguage *{language_function_name}(void) {{",
        );
        indent!(self);
        add_line!(self, "static const TSLanguage language = {{");
        indent!(self);
        add_line!(self, ".version = LANGUAGE_VERSION,");

        // Quantities
        add_line!(self, ".symbol_count = SYMBOL_COUNT,");
        add_line!(self, ".alias_count = ALIAS_COUNT,");
        add_line!(self, ".token_count = TOKEN_COUNT,");
        add_line!(self, ".external_token_count = EXTERNAL_TOKEN_COUNT,");
        add_line!(self, ".state_count = STATE_COUNT,");
        add_line!(self, ".large_state_count = LARGE_STATE_COUNT,");
        add_line!(self, ".production_id_count = PRODUCTION_ID_COUNT,");
        add_line!(self, ".field_count = FIELD_COUNT,");
        add_line!(
            self,
            ".max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,"
        );

        // Parse table
        add_line!(self, ".parse_table = &ts_parse_table[0][0],");
        if self.large_state_count < self.parse_table.states.len() {
            add_line!(self, ".small_parse_table = ts_small_parse_table,");
            add_line!(self, ".small_parse_table_map = ts_small_parse_table_map,");
        }
        add_line!(self, ".parse_actions = ts_parse_actions,");

        // Metadata
        add_line!(self, ".symbol_names = ts_symbol_names,");
        if !self.field_names.is_empty() {
            add_line!(self, ".field_names = ts_field_names,");
            add_line!(self, ".field_map_slices = ts_field_map_slices,");
            add_line!(self, ".field_map_entries = ts_field_map_entries,");
        }
        add_line!(self, ".symbol_metadata = ts_symbol_metadata,");
        add_line!(self, ".public_symbol_map = ts_symbol_map,");
        add_line!(self, ".alias_map = ts_non_terminal_alias_map,");
        if !self.parse_table.production_infos.is_empty() {
            add_line!(self, ".alias_sequences = &ts_alias_sequences[0][0],");
        }

        // Lexing
        add_line!(self, ".lex_modes = ts_lex_modes,");
        add_line!(self, ".lex_fn = ts_lex,");
        if let Some(keyword_capture_token) = self.keyword_capture_token {
            add_line!(self, ".keyword_lex_fn = ts_lex_keywords,");
            add_line!(
                self,
                ".keyword_capture_token = {},",
                self.symbol_ids[&keyword_capture_token]
            );
        }

        if !self.syntax_grammar.external_tokens.is_empty() {
            add_line!(self, ".external_scanner = {{");
            indent!(self);
            add_line!(self, "&ts_external_scanner_states[0][0],");
            add_line!(self, "ts_external_scanner_symbol_map,");
            add_line!(self, "{external_scanner_name}_create,");
            add_line!(self, "{external_scanner_name}_destroy,");
            add_line!(self, "{external_scanner_name}_scan,");
            add_line!(self, "{external_scanner_name}_serialize,");
            add_line!(self, "{external_scanner_name}_deserialize,");
            dedent!(self);
            add_line!(self, "}},");
        }

        if self.abi_version >= ABI_VERSION_WITH_PRIMARY_STATES {
            add_line!(self, ".primary_state_ids = ts_primary_state_ids,");
        }

        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "return &language;");
        dedent!(self);
        add_line!(self, "}}");
        add_line!(self, "#ifdef __cplusplus");
        add_line!(self, "}}");
        add_line!(self, "#endif");
    }

    fn get_parse_action_list_id(
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

    fn get_field_map_id(
        &self,
        flat_field_map: &Vec<(String, FieldLocation)>,
        flat_field_maps: &mut Vec<(usize, Vec<(String, FieldLocation)>)>,
        next_flat_field_map_index: &mut usize,
    ) -> usize {
        if let Some((index, _)) = flat_field_maps.iter().find(|(_, e)| *e == *flat_field_map) {
            return *index;
        }

        let result = *next_flat_field_map_index;
        flat_field_maps.push((result, flat_field_map.clone()));
        *next_flat_field_map_index += flat_field_map.len();
        result
    }

    fn external_token_id(&self, token: &ExternalToken) -> String {
        format!(
            "ts_external_token_{}",
            self.sanitize_identifier(&token.name)
        )
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

    fn field_id(&self, field_name: &str) -> String {
        format!("field_{field_name}")
    }

    fn metadata_for_symbol(&self, symbol: Symbol) -> (&str, VariableType) {
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

    fn sanitize_string(&self, name: &str) -> String {
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

    fn add_character(&mut self, c: char) {
        match c {
            '\'' => add!(self, "'\\''"),
            '\\' => add!(self, "'\\\\'"),
            '\u{000c}' => add!(self, "'\\f'"),
            '\n' => add!(self, "'\\n'"),
            '\t' => add!(self, "'\\t'"),
            '\r' => add!(self, "'\\r'"),
            _ => {
                if c == ' ' || c.is_ascii_graphic() {
                    add!(self, "'{c}'");
                } else {
                    add!(self, "{}", c as u32);
                }
            }
        }
    }
}

/// Returns a String of C code for the given components of a parser.
///
/// # Arguments
///
/// * `name` - A string slice containing the name of the language
/// * `parse_table` - The generated parse table for the language
/// * `main_lex_table` - The generated lexing table for the language
/// * `keyword_lex_table` - The generated keyword lexing table for the language
/// * `keyword_capture_token` - A symbol indicating which token is used
///    for keyword capture, if any.
/// * `syntax_grammar` - The syntax grammar extracted from the language's grammar
/// * `lexical_grammar` - The lexical grammar extracted from the language's grammar
/// * `default_aliases` - A map describing the global rename rules that should apply.
///    the keys are symbols that are *always* aliased in the same way, and the values
///    are the aliases that are applied to those symbols.
/// * `abi_version` - The language ABI version that should be generated. Usually
///    you want Tree-sitter's current version, but right after making an ABI
///    change, it may be useful to generate code with the previous ABI.
#[allow(clippy::too_many_arguments)]
pub fn render_c_code(
    name: &str,
    parse_table: ParseTable,
    main_lex_table: LexTable,
    keyword_lex_table: LexTable,
    keyword_capture_token: Option<Symbol>,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    default_aliases: AliasMap,
    abi_version: usize,
) -> String {
    assert!(
        (ABI_VERSION_MIN..=ABI_VERSION_MAX).contains(&abi_version),
        "This version of Tree-sitter can only generate parsers with ABI version {ABI_VERSION_MIN} - {ABI_VERSION_MAX}, not {abi_version}",
    );

    Generator {
        buffer: String::new(),
        indent_level: 0,
        language_name: name.to_string(),
        large_state_count: 0,
        parse_table,
        main_lex_table,
        keyword_lex_table,
        keyword_capture_token,
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
    }
    .generate()
}
