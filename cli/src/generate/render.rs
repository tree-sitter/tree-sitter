use super::grammars::{ExternalToken, LexicalGrammar, SyntaxGrammar, VariableType};
use super::nfa::CharacterSet;
use super::rules::{Alias, AliasMap, Symbol, SymbolType};
use super::tables::{
    AdvanceAction, FieldLocation, GotoAction, LexState, LexTable, ParseAction, ParseTable,
    ParseTableEntry,
};
use core::ops::Range;
use std::cmp;
use std::collections::{BTreeMap, HashMap, HashSet};
use std::fmt::Write;
use std::mem::swap;

// Currently, the library supports a new ABI version that has not yet been
// stabilized, and the parser generation does not use it by default.
const STABLE_LANGUAGE_VERSION: usize = tree_sitter::LANGUAGE_VERSION - 1;

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

const SMALL_STATE_THRESHOLD: usize = 64;

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
    simple_aliases: AliasMap,
    symbol_order: HashMap<Symbol, usize>,
    symbol_ids: HashMap<Symbol, String>,
    alias_ids: HashMap<Alias, String>,
    alias_map: BTreeMap<Alias, Option<Symbol>>,
    field_names: Vec<String>,
    next_abi: bool,
}

impl Generator {
    fn generate(mut self) -> String {
        self.init();
        self.add_includes();
        self.add_pragmas();
        self.add_stats();
        self.add_symbol_enum();
        self.add_symbol_names_list();
        self.add_symbol_metadata_list();

        if !self.field_names.is_empty() {
            self.add_field_name_enum();
            self.add_field_name_names_list();
            self.add_field_sequences();
        }

        if !self.parse_table.production_infos.is_empty() {
            self.add_alias_sequences();
        }

        let mut main_lex_table = LexTable::default();
        swap(&mut main_lex_table, &mut self.main_lex_table);
        self.add_lex_function("ts_lex", main_lex_table);

        if self.keyword_capture_token.is_some() {
            let mut keyword_lex_table = LexTable::default();
            swap(&mut keyword_lex_table, &mut self.keyword_lex_table);
            self.add_lex_function("ts_lex_keywords", keyword_lex_table);
        }

        self.add_lex_modes_list();

        if !self.syntax_grammar.external_tokens.is_empty() {
            self.add_external_token_enum();
            self.add_external_scanner_symbol_map();
            self.add_external_scanner_states_list();
        }

        self.add_parse_table();
        self.add_parser_export();

        self.buffer
    }

    fn init(&mut self) {
        let mut symbol_identifiers = HashSet::new();
        for i in 0..self.parse_table.symbols.len() {
            self.assign_symbol_id(self.parse_table.symbols[i], &mut symbol_identifiers);
        }

        let mut field_names = Vec::new();
        for production_info in &self.parse_table.production_infos {
            for field_name in production_info.field_map.keys() {
                field_names.push(field_name);
            }

            for alias in &production_info.alias_sequence {
                if let Some(alias) = &alias {
                    let alias_kind = if alias.is_named {
                        VariableType::Named
                    } else {
                        VariableType::Anonymous
                    };
                    let matching_symbol = self.parse_table.symbols.iter().cloned().find(|symbol| {
                        let (name, kind) = self.metadata_for_symbol(*symbol);
                        name == alias.value && kind == alias_kind
                    });
                    let alias_id = if let Some(symbol) = matching_symbol {
                        self.symbol_ids[&symbol].clone()
                    } else if alias.is_named {
                        format!("alias_sym_{}", self.sanitize_identifier(&alias.value))
                    } else {
                        format!("anon_alias_sym_{}", self.sanitize_identifier(&alias.value))
                    };
                    self.alias_ids.entry(alias.clone()).or_insert(alias_id);
                    self.alias_map
                        .entry(alias.clone())
                        .or_insert(matching_symbol);
                }
            }
        }

        field_names.sort_unstable();
        field_names.dedup();
        self.field_names = field_names.into_iter().cloned().collect();

        // If we are opting in to the new unstable language ABI, then use the concept of
        // "small parse states". Otherwise, use the same representation for all parse
        // states.
        if self.next_abi {
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
        } else {
            self.large_state_count = self.parse_table.states.len();
        }
    }

    fn add_includes(&mut self) {
        add_line!(self, "#include <tree_sitter/parser.h>");
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

        if self.next_abi {
            add_line!(
                self,
                "#define LANGUAGE_VERSION {}",
                tree_sitter::LANGUAGE_VERSION
            );
        } else {
            add_line!(self, "#define LANGUAGE_VERSION {}", STABLE_LANGUAGE_VERSION);
        }

        add_line!(
            self,
            "#define STATE_COUNT {}",
            self.parse_table.states.len()
        );

        if self.next_abi {
            add_line!(self, "#define LARGE_STATE_COUNT {}", self.large_state_count);
        }

        add_line!(
            self,
            "#define SYMBOL_COUNT {}",
            self.parse_table.symbols.len()
        );
        add_line!(
            self,
            "#define ALIAS_COUNT {}",
            self.alias_map.iter().filter(|e| e.1.is_none()).count()
        );
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
        add_line!(self, "");
    }

    fn add_symbol_enum(&mut self) {
        add_line!(self, "enum {{");
        indent!(self);
        self.symbol_order.insert(Symbol::end(), 0);
        let mut i = 1;
        for symbol in self.parse_table.symbols.iter() {
            if *symbol != Symbol::end() {
                self.symbol_order.insert(*symbol, i);
                add_line!(self, "{} = {},", self.symbol_ids[&symbol], i);
                i += 1;
            }
        }
        for (alias, symbol) in &self.alias_map {
            if symbol.is_none() {
                add_line!(self, "{} = {},", self.alias_ids[&alias], i);
                i += 1;
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_symbol_names_list(&mut self) {
        add_line!(self, "static const char *ts_symbol_names[] = {{");
        indent!(self);
        for symbol in self.parse_table.symbols.iter() {
            let name = self.sanitize_string(
                self.simple_aliases
                    .get(symbol)
                    .map(|alias| alias.value.as_str())
                    .unwrap_or(self.metadata_for_symbol(*symbol).0),
            );
            add_line!(self, "[{}] = \"{}\",", self.symbol_ids[&symbol], name);
        }
        for (alias, symbol) in &self.alias_map {
            if symbol.is_none() {
                add_line!(
                    self,
                    "[{}] = \"{}\",",
                    self.alias_ids[&alias],
                    self.sanitize_string(&alias.value)
                );
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_field_name_enum(&mut self) {
        add_line!(self, "enum {{");
        indent!(self);
        for (i, field_name) in self.field_names.iter().enumerate() {
            add_line!(self, "{} = {},", self.field_id(field_name), i + 1);
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_field_name_names_list(&mut self) {
        add_line!(self, "static const char *ts_field_names[] = {{");
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
            if let Some(Alias { is_named, .. }) = self.simple_aliases.get(symbol) {
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
        for (alias, matching_symbol) in &self.alias_map {
            if matching_symbol.is_none() {
                add_line!(self, "[{}] = {{", self.alias_ids[&alias]);
                indent!(self);
                add_line!(self, ".visible = true,");
                add_line!(self, ".named = {},", alias.is_named);
                dedent!(self);
                add_line!(self, "}},");
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_alias_sequences(&mut self) {
        add_line!(
            self,
            "static TSSymbol ts_alias_sequences[{}][MAX_ALIAS_SEQUENCE_LENGTH] = {{",
            self.parse_table.production_infos.len()
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
            if !production_info.field_map.is_empty() {
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
            } else {
                field_map_ids.push((0, 0));
            }
        }

        add_line!(
            self,
            "static const TSFieldMapSlice ts_field_map_slices[] = {{",
        );
        indent!(self);
        for (production_id, (row_id, length)) in field_map_ids.into_iter().enumerate() {
            if length > 0 {
                add_line!(
                    self,
                    "[{}] = {{.index = {}, .length = {}}},",
                    production_id,
                    row_id,
                    length
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
            add_line!(self, "[{}] =", row_index);
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

    fn add_lex_function(&mut self, name: &str, lex_table: LexTable) {
        add_line!(
            self,
            "static bool {}(TSLexer *lexer, TSStateId state) {{",
            name
        );
        indent!(self);
        add_line!(self, "START_LEXER();");

        if self.next_abi {
            add_line!(self, "eof = lexer->eof(lexer);");
        } else {
            add_line!(self, "eof = lookahead == 0;");
        }

        add_line!(self, "switch (state) {{");
        indent!(self);

        for (i, state) in lex_table.states.into_iter().enumerate() {
            add_line!(self, "case {}:", i);
            indent!(self);
            self.add_lex_state(state);
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

    fn add_lex_state(&mut self, state: LexState) {
        if let Some(accept_action) = state.accept_action {
            add_line!(self, "ACCEPT_TOKEN({});", self.symbol_ids[&accept_action]);
        }

        if let Some(eof_action) = state.eof_action {
            add_line!(self, "if (eof) ADVANCE({});", eof_action.state);
        }

        let mut ruled_out_characters = HashSet::new();
        for (characters, action) in state.advance_actions {
            let previous_length = self.buffer.len();

            add_whitespace!(self);
            add!(self, "if (");
            if self.add_character_set_condition(&characters, &ruled_out_characters) {
                add!(self, ") ");
                self.add_advance_action(&action);
                if let CharacterSet::Include(chars) = characters {
                    ruled_out_characters.extend(chars.iter().map(|c| *c as u32));
                }
            } else {
                self.buffer.truncate(previous_length);
                self.add_advance_action(&action);
            }
            add!(self, "\n");
        }

        add_line!(self, "END_STATE();");
    }

    fn add_character_set_condition(
        &mut self,
        characters: &CharacterSet,
        ruled_out_characters: &HashSet<u32>,
    ) -> bool {
        match characters {
            CharacterSet::Include(chars) => {
                let ranges = Self::get_ranges(chars, ruled_out_characters);
                self.add_character_range_conditions(ranges, false)
            }
            CharacterSet::Exclude(chars) => {
                let ranges = Some('\0'..'\0')
                    .into_iter()
                    .chain(Self::get_ranges(chars, ruled_out_characters));
                self.add_character_range_conditions(ranges, true)
            }
        }
    }

    fn add_character_range_conditions(
        &mut self,
        ranges: impl Iterator<Item = Range<char>>,
        is_negated: bool,
    ) -> bool {
        let line_break = "\n          ";
        let mut did_add = false;
        for range in ranges {
            if is_negated {
                if did_add {
                    add!(self, " &&{}", line_break);
                }
                if range.end == range.start {
                    add!(self, "lookahead != ");
                    self.add_character(range.start);
                } else if range.end as u32 == range.start as u32 + 1 {
                    add!(self, "lookahead != ");
                    self.add_character(range.start);
                    add!(self, " &&{}lookahead != ", line_break);
                    self.add_character(range.end);
                } else {
                    add!(self, "(lookahead < ");
                    self.add_character(range.start);
                    add!(self, " || ");
                    self.add_character(range.end);
                    add!(self, " < lookahead)");
                }
            } else {
                if did_add {
                    add!(self, " ||{}", line_break);
                }
                if range.end == range.start {
                    add!(self, "lookahead == ");
                    self.add_character(range.start);
                } else if range.end as u32 == range.start as u32 + 1 {
                    add!(self, "lookahead == ");
                    self.add_character(range.start);
                    add!(self, " ||{}lookahead == ", line_break);
                    self.add_character(range.end);
                } else {
                    add!(self, "(");
                    self.add_character(range.start);
                    add!(self, " <= lookahead && lookahead <= ");
                    self.add_character(range.end);
                    add!(self, ")");
                }
            }
            did_add = true;
        }
        did_add
    }

    fn get_ranges<'a>(
        chars: &'a Vec<char>,
        ruled_out_characters: &'a HashSet<u32>,
    ) -> impl Iterator<Item = Range<char>> + 'a {
        let mut prev_range: Option<Range<char>> = None;
        chars
            .iter()
            .map(|c| (*c, false))
            .chain(Some(('\0', true)))
            .filter_map(move |(c, done)| {
                if done {
                    return prev_range.clone();
                }
                if ruled_out_characters.contains(&(c as u32)) {
                    return None;
                }
                if let Some(range) = prev_range.clone() {
                    let mut prev_range_successor = range.end as u32 + 1;
                    while prev_range_successor < c as u32 {
                        if !ruled_out_characters.contains(&prev_range_successor) {
                            prev_range = Some(c..c);
                            return Some(range);
                        }
                        prev_range_successor += 1;
                    }
                    prev_range = Some(range.start..c);
                    None
                } else {
                    prev_range = Some(c..c);
                    None
                }
            })
    }

    fn add_advance_action(&mut self, action: &AdvanceAction) {
        if action.in_main_token {
            add!(self, "ADVANCE({});", action.state);
        } else {
            add!(self, "SKIP({})", action.state);
        }
    }

    fn add_lex_modes_list(&mut self) {
        add_line!(self, "static TSLexMode ts_lex_modes[STATE_COUNT] = {{");
        indent!(self);
        for (i, state) in self.parse_table.states.iter().enumerate() {
            if state.is_non_terminal_extra
                && state.terminal_entries.len() == 1
                && *state.terminal_entries.iter().next().unwrap().0 == Symbol::end()
            {
                add_line!(self, "[{}] = {{-1}},", i,);
            } else if state.external_lex_state_id > 0 {
                add_line!(
                    self,
                    "[{}] = {{.lex_state = {}, .external_lex_state = {}}},",
                    i,
                    state.lex_state_id,
                    state.external_lex_state_id
                );
            } else {
                add_line!(self, "[{}] = {{.lex_state = {}}},", i, state.lex_state_id);
            }
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_external_token_enum(&mut self) {
        add_line!(self, "enum {{");
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
            "static TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {{"
        );
        indent!(self);
        for i in 0..self.syntax_grammar.external_tokens.len() {
            let token = &self.syntax_grammar.external_tokens[i];
            let id_token = token
                .corresponding_internal_token
                .unwrap_or(Symbol::external(i));
            add_line!(
                self,
                "[{}] = {},",
                self.external_token_id(&token),
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
            "static bool ts_external_scanner_states[{}][EXTERNAL_TOKEN_COUNT] = {{",
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
        let mut parse_table_entries = Vec::new();
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
            "static uint16_t ts_parse_table[{}][SYMBOL_COUNT] = {{",
            if self.next_abi {
                "LARGE_STATE_COUNT"
            } else {
                "STATE_COUNT"
            }
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
                add_line!(
                    self,
                    "[{}] = ACTIONS({}),",
                    self.symbol_ids[symbol],
                    entry_id
                );
            }
            dedent!(self);
            add_line!(self, "}},");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");

        if self.large_state_count < self.parse_table.states.len() {
            add_line!(self, "static uint16_t ts_small_parse_table[] = {{");
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

                add_line!(self, "[{}] = {},", index, values_with_symbols.len());
                indent!(self);

                for ((value, kind), symbols) in values_with_symbols.iter_mut() {
                    if *kind == SymbolType::NonTerminal {
                        add_line!(self, "STATE({}), {},", value, symbols.len());
                    } else {
                        add_line!(self, "ACTIONS({}), {},", value, symbols.len());
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

            add_line!(self, "static uint32_t ts_small_parse_table_map[] = {{");
            indent!(self);
            for i in self.large_state_count..self.parse_table.states.len() {
                add_line!(
                    self,
                    "[SMALL_STATE({})] = {},",
                    i,
                    small_state_indices[i - self.large_state_count]
                );
            }
            dedent!(self);
            add_line!(self, "}};");
            add_line!(self, "");
        }

        self.add_parse_action_list(parse_table_entries);
    }

    fn add_parse_action_list(&mut self, parse_table_entries: Vec<(usize, ParseTableEntry)>) {
        add_line!(self, "static TSParseActionEntry ts_parse_actions[] = {{");
        indent!(self);
        for (i, entry) in parse_table_entries {
            add!(
                self,
                "  [{}] = {{.count = {}, .reusable = {}}},",
                i,
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
                            add!(self, "SHIFT_REPEAT({})", state);
                        } else {
                            add!(self, "SHIFT({})", state);
                        }
                    }
                    ParseAction::Reduce {
                        symbol,
                        child_count,
                        dynamic_precedence,
                        production_id,
                        ..
                    } => {
                        add!(self, "REDUCE({}, {}", self.symbol_ids[&symbol], child_count);
                        if dynamic_precedence != 0 {
                            add!(self, ", .dynamic_precedence = {}", dynamic_precedence);
                        }
                        if production_id != 0 {
                            add!(self, ", .production_id = {}", production_id);
                        }
                        add!(self, ")");
                    }
                }
                add!(self, ",")
            }
            add!(self, "\n");
        }
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_parser_export(&mut self) {
        let language_function_name = format!("tree_sitter_{}", self.language_name);
        let external_scanner_name = format!("{}_external_scanner", language_function_name);

        if !self.syntax_grammar.external_tokens.is_empty() {
            add_line!(self, "void *{}_create(void);", external_scanner_name);
            add_line!(self, "void {}_destroy(void *);", external_scanner_name);
            add_line!(
                self,
                "bool {}_scan(void *, TSLexer *, const bool *);",
                external_scanner_name
            );
            add_line!(
                self,
                "unsigned {}_serialize(void *, char *);",
                external_scanner_name
            );
            add_line!(
                self,
                "void {}_deserialize(void *, const char *, unsigned);",
                external_scanner_name
            );
            add_line!(self, "");
        }

        add_line!(self, "#ifdef _WIN32");
        add_line!(self, "#define extern __declspec(dllexport)");
        add_line!(self, "#endif");
        add_line!(self, "");

        add_line!(
            self,
            "extern const TSLanguage *{}(void) {{",
            language_function_name
        );
        indent!(self);
        add_line!(self, "static TSLanguage language = {{");
        indent!(self);
        add_line!(self, ".version = LANGUAGE_VERSION,");
        add_line!(self, ".symbol_count = SYMBOL_COUNT,");
        add_line!(self, ".alias_count = ALIAS_COUNT,");
        add_line!(self, ".token_count = TOKEN_COUNT,");

        if self.next_abi {
            add_line!(self, ".large_state_count = LARGE_STATE_COUNT,");
        }

        add_line!(self, ".symbol_metadata = ts_symbol_metadata,");
        add_line!(
            self,
            ".parse_table = (const unsigned short *)ts_parse_table,"
        );

        if self.large_state_count < self.parse_table.states.len() {
            add_line!(
                self,
                ".small_parse_table = (const uint16_t *)ts_small_parse_table,"
            );
            add_line!(
                self,
                ".small_parse_table_map = (const uint32_t *)ts_small_parse_table_map,"
            );
        }

        add_line!(self, ".parse_actions = ts_parse_actions,");
        add_line!(self, ".lex_modes = ts_lex_modes,");
        add_line!(self, ".symbol_names = ts_symbol_names,");

        if !self.parse_table.production_infos.is_empty() {
            add_line!(
                self,
                ".alias_sequences = (const TSSymbol *)ts_alias_sequences,"
            );
        }

        add_line!(self, ".field_count = FIELD_COUNT,");

        if !self.field_names.is_empty() {
            add_line!(self, ".field_names = ts_field_names,");
            add_line!(
                self,
                ".field_map_slices = (const TSFieldMapSlice *)ts_field_map_slices,"
            );
            add_line!(
                self,
                ".field_map_entries = (const TSFieldMapEntry *)ts_field_map_entries,"
            );
        }

        add_line!(
            self,
            ".max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,"
        );
        add_line!(self, ".lex_fn = ts_lex,");

        if let Some(keyword_capture_token) = self.keyword_capture_token {
            add_line!(self, ".keyword_lex_fn = ts_lex_keywords,");
            add_line!(
                self,
                ".keyword_capture_token = {},",
                self.symbol_ids[&keyword_capture_token]
            );
        }

        add_line!(self, ".external_token_count = EXTERNAL_TOKEN_COUNT,");

        if !self.syntax_grammar.external_tokens.is_empty() {
            add_line!(self, ".external_scanner = {{");
            indent!(self);
            add_line!(self, "(const bool *)ts_external_scanner_states,");
            add_line!(self, "ts_external_scanner_symbol_map,");
            add_line!(self, "{}_create,", external_scanner_name);
            add_line!(self, "{}_destroy,", external_scanner_name);
            add_line!(self, "{}_scan,", external_scanner_name);
            add_line!(self, "{}_serialize,", external_scanner_name);
            add_line!(self, "{}_deserialize,", external_scanner_name);
            dedent!(self);
            add_line!(self, "}},");
        }
        dedent!(self);

        add_line!(self, "}};");
        add_line!(self, "return &language;");
        dedent!(self);
        add_line!(self, "}}");
    }

    fn get_parse_action_list_id(
        &self,
        entry: &ParseTableEntry,
        parse_table_entries: &mut Vec<(usize, ParseTableEntry)>,
        next_parse_action_list_index: &mut usize,
    ) -> usize {
        if let Some((index, _)) = parse_table_entries.iter().find(|(_, e)| *e == *entry) {
            return *index;
        }

        let result = *next_parse_action_list_index;
        parse_table_entries.push((result, entry.clone()));
        *next_parse_action_list_index += 1 + entry.actions.len();
        result
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

    fn field_id(&self, field_name: &String) -> String {
        format!("field_{}", field_name)
    }

    fn metadata_for_symbol(&self, symbol: Symbol) -> (&str, VariableType) {
        match symbol.kind {
            SymbolType::End => ("end", VariableType::Hidden),
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
            if ('a' <= c && c <= 'z')
                || ('A' <= c && c <= 'Z')
                || ('0' <= c && c <= '9')
                || c == '_'
            {
                result.push(c);
            } else {
                let replacement = match c {
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
                    _ => continue,
                };
                if !result.is_empty() && !result.ends_with("_") {
                    result.push('_');
                }
                result += replacement;
            }
        }
        result
    }

    fn sanitize_string(&self, name: &str) -> String {
        let mut result = String::with_capacity(name.len());
        for c in name.chars() {
            match c {
                '\"' => result += "\\\"",
                '\\' => result += "\\\\",
                '\t' => result += "\\t",
                '\n' => result += "\\n",
                '\r' => result += "\\r",
                _ => result.push(c),
            }
        }
        result
    }

    fn add_character(&mut self, c: char) {
        if c.is_ascii() {
            match c {
                '\0' => add!(self, "0"),
                '\'' => add!(self, "'\\''"),
                '\\' => add!(self, "'\\\\'"),
                '\t' => add!(self, "'\\t'"),
                '\n' => add!(self, "'\\n'"),
                '\r' => add!(self, "'\\r'"),
                _ => add!(self, "'{}'", c),
            }
        } else {
            add!(self, "{}", c as u32)
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
/// * `simple_aliases` - A map describing the global rename rules that should apply.
///    the keys are symbols that are *always* aliased in the same way, and the values
///    are the aliases that are applied to those symbols.
/// * `next_abi` - A boolean indicating whether to opt into the new, unstable parse
///    table format. This is mainly used for testing, when developing Tree-sitter itself.
pub(crate) fn render_c_code(
    name: &str,
    parse_table: ParseTable,
    main_lex_table: LexTable,
    keyword_lex_table: LexTable,
    keyword_capture_token: Option<Symbol>,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    simple_aliases: AliasMap,
    next_abi: bool,
) -> String {
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
        simple_aliases,
        symbol_ids: HashMap::new(),
        symbol_order: HashMap::new(),
        alias_ids: HashMap::new(),
        alias_map: BTreeMap::new(),
        field_names: Vec::new(),
        next_abi,
    }
    .generate()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_char_ranges() {
        struct Row {
            chars: Vec<char>,
            ruled_out_chars: Vec<char>,
            expected_ranges: Vec<Range<char>>,
        }

        let table = [
            Row {
                chars: vec!['a'],
                ruled_out_chars: vec![],
                expected_ranges: vec!['a'..'a'],
            },
            Row {
                chars: vec!['a', 'b', 'c', 'e', 'z'],
                ruled_out_chars: vec![],
                expected_ranges: vec!['a'..'c', 'e'..'e', 'z'..'z'],
            },
            Row {
                chars: vec!['a', 'b', 'c', 'e', 'h', 'z'],
                ruled_out_chars: vec!['d', 'f', 'g'],
                expected_ranges: vec!['a'..'h', 'z'..'z'],
            },
        ];

        for Row {
            chars,
            ruled_out_chars,
            expected_ranges,
        } in table.iter()
        {
            let ruled_out_chars = ruled_out_chars
                .into_iter()
                .map(|c: &char| *c as u32)
                .collect();
            let ranges = Generator::get_ranges(chars, &ruled_out_chars).collect::<Vec<_>>();
            assert_eq!(ranges, *expected_ranges);
        }
    }
}
