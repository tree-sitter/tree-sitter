use super::char_tree::{CharacterTree, Comparator};
use super::grammars::{ExternalToken, LexicalGrammar, SyntaxGrammar, VariableType};
use super::rules::{Alias, AliasMap, Symbol, SymbolType};
use super::tables::{
    AdvanceAction, FieldLocation, GotoAction, LexState, LexTable, ParseAction, ParseTable,
    ParseTableEntry,
};
use core::ops::Range;
use std::cmp;
use std::collections::{HashMap, HashSet};
use std::fmt::Write;
use std::mem::swap;

const LARGE_CHARACTER_RANGE_COUNT: usize = 8;
const SMALL_STATE_THRESHOLD: usize = 64;

macro_rules! add {
    ($gen_file: tt, $($arg: tt)*) => {{
        $gen_file.buffer.write_fmt(format_args!($($arg)*)).unwrap();
    }}
}

macro_rules! add_whitespace {
    ($gen_file: tt) => {{
        for _ in 0..$gen_file.indent_level {
            write!(&mut $gen_file.buffer, "  ").unwrap();
        }
    }};
}

macro_rules! add_line {
    ($gen_file: tt, $($arg: tt)*) => {
        add_whitespace!($gen_file);
        $gen_file.buffer.write_fmt(format_args!($($arg)*)).unwrap();
        $gen_file.buffer += "\n";
    }
}

macro_rules! indent {
    ($gen_file: tt) => {
        $gen_file.indent_level += 1;
    };
}

macro_rules! dedent {
    ($gen_file: tt) => {
        assert_ne!($gen_file.indent_level, 0);
        $gen_file.indent_level -= 1;
    };
}

struct GeneratorFile {
    buffer: String,
    indent_level: usize,
}

struct Generator {
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
    next_abi: bool,
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
    fn generate(mut self) -> (String, String) {
        let mut header_file = GeneratorFile {
            buffer: String::new(),
            indent_level: 0,
        };

        let mut impl_file = GeneratorFile {
            buffer: String::new(),
            indent_level: 0,
        };

        self.init();
        self.add_include_guard(&mut header_file);
        self.add_includes(&mut header_file, &mut impl_file);
        self.add_pragmas(&mut impl_file);
        self.add_stats(&mut impl_file);
        self.add_symbol_enum(&mut header_file);
        self.add_symbol_names_list(&mut impl_file);
        self.add_unique_symbol_map(&mut impl_file);
        self.add_symbol_metadata_list(&mut impl_file);

        if !self.field_names.is_empty() {
            self.add_field_name_enum(&mut header_file);
            self.add_field_name_names_list(&mut impl_file);
            self.add_field_sequences(&mut impl_file);
        }

        if !self.parse_table.production_infos.is_empty() {
            self.add_alias_sequences(&mut impl_file);
        }

        self.add_non_terminal_alias_map(&mut impl_file);

        let mut main_lex_table = LexTable::default();
        swap(&mut main_lex_table, &mut self.main_lex_table);
        self.add_lex_function(&mut impl_file, "ts_lex", main_lex_table, true);

        if self.keyword_capture_token.is_some() {
            let mut keyword_lex_table = LexTable::default();
            swap(&mut keyword_lex_table, &mut self.keyword_lex_table);
            self.add_lex_function(&mut impl_file, "ts_lex_keywords", keyword_lex_table, false);
        }

        self.add_lex_modes_list(&mut impl_file);

        if !self.syntax_grammar.external_tokens.is_empty() {
            self.add_external_token_enum(&mut header_file);
            self.add_external_scanner_symbol_map(&mut impl_file);
            self.add_external_scanner_states_list(&mut impl_file);
        }

        self.add_parse_table(&mut impl_file);
        self.add_parser_export(&mut header_file, &mut impl_file);
        self.add_include_guard_end(&mut header_file);

        (impl_file.buffer, header_file.buffer)
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

        self.symbol_map = self
            .parse_table
            .symbols
            .iter()
            .map(|symbol| {
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
                            mapping = other_symbol;
                            break;
                        }
                    }
                }

                (*symbol, *mapping)
            })
            .collect();

        for production_info in &self.parse_table.production_infos {
            // Build a list of all field names
            for field_name in production_info.field_map.keys() {
                if let Err(i) = self.field_names.binary_search(&field_name) {
                    self.field_names.insert(i, field_name.clone());
                }
            }

            for alias in &production_info.alias_sequence {
                // Generate a mapping from aliases to C identifiers.
                if let Some(alias) = &alias {
                    let existing_symbol = self.parse_table.symbols.iter().cloned().find(|symbol| {
                        if let Some(default_alias) = self.default_aliases.get(symbol) {
                            default_alias == alias
                        } else {
                            let (name, kind) = self.metadata_for_symbol(*symbol);
                            name == alias.value && kind == alias.kind()
                        }
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

    fn add_includes(&mut self, header_file: &mut GeneratorFile, impl_file: &mut GeneratorFile) {
        add_line!(header_file, "#include <tree_sitter/parser.h>");
        add_line!(header_file, "");
        add_line!(impl_file, "#include \"parser.h\"");
        add_line!(impl_file, "");
    }

    fn add_pragmas(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "#if defined(__GNUC__) || defined(__clang__)");
        add_line!(gen_file, "#pragma GCC diagnostic push");
        add_line!(
            gen_file,
            "#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\""
        );
        add_line!(gen_file, "#endif");
        add_line!(gen_file, "");

        // Compiling large lexer functions can be very slow. Disabling optimizations
        // is not ideal, but only a very small fraction of overall parse time is
        // spent lexing, so the performance impact of this is negligible.
        if self.main_lex_table.states.len() > 300 {
            add_line!(gen_file, "#ifdef _MSC_VER");
            add_line!(gen_file, "#pragma optimize(\"\", off)");
            add_line!(gen_file, "#elif defined(__clang__)");
            add_line!(gen_file, "#pragma clang optimize off");
            add_line!(gen_file, "#elif defined(__GNUC__)");
            add_line!(gen_file, "#pragma GCC optimize (\"O0\")");
            add_line!(gen_file, "#endif");
            add_line!(gen_file, "");
        }
    }

    fn add_stats(&mut self, gen_file: &mut GeneratorFile) {
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

        add_line!(
            gen_file,
            "#define LANGUAGE_VERSION {}",
            if self.next_abi {
                tree_sitter::LANGUAGE_VERSION
            } else {
                tree_sitter::LANGUAGE_VERSION - 1
            }
        );

        add_line!(
            gen_file,
            "#define STATE_COUNT {}",
            self.parse_table.states.len()
        );
        add_line!(gen_file, "#define LARGE_STATE_COUNT {}", self.large_state_count);

        add_line!(
            gen_file,
            "#define SYMBOL_COUNT {}",
            self.parse_table.symbols.len()
        );
        add_line!(gen_file, "#define ALIAS_COUNT {}", self.unique_aliases.len(),);
        add_line!(gen_file, "#define TOKEN_COUNT {}", token_count);
        add_line!(
            gen_file,
            "#define EXTERNAL_TOKEN_COUNT {}",
            self.syntax_grammar.external_tokens.len()
        );
        add_line!(gen_file, "#define FIELD_COUNT {}", self.field_names.len());
        add_line!(
            gen_file,
            "#define MAX_ALIAS_SEQUENCE_LENGTH {}",
            self.parse_table.max_aliased_production_length
        );
        add_line!(
            gen_file,
            "#define PRODUCTION_ID_COUNT {}",
            self.parse_table.production_infos.len()
        );
        add_line!(gen_file, "");
    }

    fn add_symbol_enum(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "enum {{");
        indent!(gen_file);
        self.symbol_order.insert(Symbol::end(), 0);
        let mut i = 1;
        for symbol in self.parse_table.symbols.iter() {
            if *symbol != Symbol::end() {
                self.symbol_order.insert(*symbol, i);
                add_line!(gen_file, "{} = {},", self.symbol_ids[&symbol], i);
                i += 1;
            }
        }
        for alias in &self.unique_aliases {
            add_line!(gen_file, "{} = {},", self.alias_ids[&alias], i);
            i += 1;
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_symbol_names_list(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "static const char * const ts_symbol_names[] = {{");
        indent!(gen_file);
        for symbol in self.parse_table.symbols.iter() {
            let name = self.sanitize_string(
                self.default_aliases
                    .get(symbol)
                    .map(|alias| alias.value.as_str())
                    .unwrap_or(self.metadata_for_symbol(*symbol).0),
            );
            add_line!(gen_file, "[{}] = \"{}\",", self.symbol_ids[&symbol], name);
        }
        for alias in &self.unique_aliases {
            add_line!(
                gen_file,
                "[{}] = \"{}\",",
                self.alias_ids[&alias],
                self.sanitize_string(&alias.value)
            );
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_unique_symbol_map(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "static const TSSymbol ts_symbol_map[] = {{");
        indent!(gen_file);
        for symbol in &self.parse_table.symbols {
            add_line!(
                gen_file,
                "[{}] = {},",
                self.symbol_ids[symbol],
                self.symbol_ids[&self.symbol_map[symbol]],
            );
        }

        for alias in &self.unique_aliases {
            add_line!(
                gen_file,
                "[{}] = {},",
                self.alias_ids[&alias],
                self.alias_ids[&alias],
            );
        }

        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_field_name_enum(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "enum {{");
        indent!(gen_file);
        for (i, field_name) in self.field_names.iter().enumerate() {
            add_line!(gen_file, "{} = {},", self.field_id(field_name), i + 1);
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_field_name_names_list(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "static const char * const ts_field_names[] = {{");
        indent!(gen_file);
        add_line!(gen_file, "[0] = NULL,");
        for field_name in &self.field_names {
            add_line!(
                gen_file,
                "[{}] = \"{}\",",
                self.field_id(field_name),
                field_name
            );
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_symbol_metadata_list(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(
            gen_file,
            "static const TSSymbolMetadata ts_symbol_metadata[] = {{"
        );
        indent!(gen_file);
        for symbol in &self.parse_table.symbols {
            add_line!(gen_file, "[{}] = {{", self.symbol_ids[&symbol]);
            indent!(gen_file);
            if let Some(Alias { is_named, .. }) = self.default_aliases.get(symbol) {
                add_line!(gen_file, ".visible = true,");
                add_line!(gen_file, ".named = {},", is_named);
            } else {
                match self.metadata_for_symbol(*symbol).1 {
                    VariableType::Named => {
                        add_line!(gen_file, ".visible = true,");
                        add_line!(gen_file, ".named = true,");
                    }
                    VariableType::Anonymous => {
                        add_line!(gen_file, ".visible = true,");
                        add_line!(gen_file, ".named = false,");
                    }
                    VariableType::Hidden => {
                        add_line!(gen_file, ".visible = false,");
                        add_line!(gen_file, ".named = true,");
                        if self.syntax_grammar.supertype_symbols.contains(symbol) {
                            add_line!(gen_file, ".supertype = true,");
                        }
                    }
                    VariableType::Auxiliary => {
                        add_line!(gen_file, ".visible = false,");
                        add_line!(gen_file, ".named = false,");
                    }
                }
            }
            dedent!(gen_file);
            add_line!(gen_file, "}},");
        }
        for alias in &self.unique_aliases {
            add_line!(gen_file, "[{}] = {{", self.alias_ids[&alias]);
            indent!(gen_file);
            add_line!(gen_file, ".visible = true,");
            add_line!(gen_file, ".named = {},", alias.is_named);
            dedent!(gen_file);
            add_line!(gen_file, "}},");
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_alias_sequences(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(
            gen_file,
            "static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {{",
        );
        indent!(gen_file);
        for (i, production_info) in self.parse_table.production_infos.iter().enumerate() {
            if production_info.alias_sequence.is_empty() {
                // Work around MSVC's intolerance of empty array initializers by
                // explicitly zero-initializing the first element.
                if i == 0 {
                    add_line!(gen_file, "[0] = {{0}},");
                }
                continue;
            }

            add_line!(gen_file, "[{}] = {{", i);
            indent!(gen_file);
            for (j, alias) in production_info.alias_sequence.iter().enumerate() {
                if let Some(alias) = alias {
                    add_line!(gen_file, "[{}] = {},", j, self.alias_ids[&alias]);
                }
            }
            dedent!(gen_file);
            add_line!(gen_file, "}},");
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_non_terminal_alias_map(&mut self, gen_file: &mut GeneratorFile) {
        let mut alias_ids_by_symbol = HashMap::new();
        for variable in &self.syntax_grammar.variables {
            for production in &variable.productions {
                for step in &production.steps {
                    if let Some(alias) = &step.alias {
                        if step.symbol.is_non_terminal()
                            && Some(alias) != self.default_aliases.get(&step.symbol)
                        {
                            if self.symbol_ids.contains_key(&step.symbol) {
                                if let Some(alias_id) = self.alias_ids.get(&alias) {
                                    let alias_ids = alias_ids_by_symbol
                                        .entry(step.symbol)
                                        .or_insert(Vec::new());
                                    if let Err(i) = alias_ids.binary_search(&alias_id) {
                                        alias_ids.insert(i, alias_id);
                                    }
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
            gen_file,
            "static const uint16_t ts_non_terminal_alias_map[] = {{"
        );
        indent!(gen_file);
        for (symbol, alias_ids) in alias_ids_by_symbol {
            let symbol_id = &self.symbol_ids[symbol];
            let public_symbol_id = &self.symbol_ids[&self.symbol_map[&symbol]];
            add_line!(gen_file, "{}, {},", symbol_id, 1 + alias_ids.len());
            indent!(gen_file);
            add_line!(gen_file, "{},", public_symbol_id);
            for alias_id in alias_ids {
                add_line!(gen_file, "{},", alias_id);
            }
            dedent!(gen_file);
        }
        add_line!(gen_file, "0,");
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_field_sequences(&mut self, gen_file: &mut GeneratorFile) {
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
            gen_file,
            "static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {{",
        );
        indent!(gen_file);
        for (production_id, (row_id, length)) in field_map_ids.into_iter().enumerate() {
            if length > 0 {
                add_line!(
                    gen_file,
                    "[{}] = {{.index = {}, .length = {}}},",
                    production_id,
                    row_id,
                    length
                );
            }
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");

        add_line!(
            gen_file,
            "static const TSFieldMapEntry ts_field_map_entries[] = {{",
        );
        indent!(gen_file);
        for (row_index, field_pairs) in flat_field_maps.into_iter().skip(1) {
            add_line!(gen_file, "[{}] =", row_index);
            indent!(gen_file);
            for (field_name, location) in field_pairs {
                add_whitespace!(gen_file);
                add!(gen_file, "{{{}, {}", self.field_id(&field_name), location.index);
                if location.inherited {
                    add!(gen_file, ", .inherited = true");
                }
                add!(gen_file, "}},\n");
            }
            dedent!(gen_file);
        }

        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_lex_function(
        &mut self,
        gen_file: &mut GeneratorFile,
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
                            ranges.insert(0, '\0'..'\0')
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
        let mut sorted_large_char_sets: Vec<_> = large_character_sets.iter().map(|e| e).collect();
        sorted_large_char_sets.sort_unstable_by_key(|info| (info.symbol, info.index));
        for info in sorted_large_char_sets {
            add_line!(
                gen_file,
                "static inline bool {}_character_set_{}(int32_t c) {{",
                self.symbol_ids[&info.symbol],
                info.index
            );
            indent!(gen_file);
            add_whitespace!(gen_file);
            add!(gen_file, "return ");
            let tree = CharacterTree::from_ranges(&info.ranges);
            self.add_character_tree(gen_file, tree.as_ref());
            add!(gen_file, ";\n");
            dedent!(gen_file);
            add_line!(gen_file, "}}");
            add_line!(gen_file, "");
        }

        add_line!(
            gen_file,
            "static bool {}(TSLexer *lexer, TSStateId state) {{",
            name
        );
        indent!(gen_file);

        add_line!(gen_file, "START_LEXER();");
        add_line!(gen_file, "eof = lexer->eof(lexer);");
        add_line!(gen_file, "switch (state) {{");

        indent!(gen_file);
        for (i, state) in lex_table.states.into_iter().enumerate() {
            add_line!(gen_file, "case {}:", i);
            indent!(gen_file);
            self.add_lex_state(gen_file, state, &state_transition_summaries[i], &large_character_sets);
            dedent!(gen_file);
        }

        add_line!(gen_file, "default:");
        indent!(gen_file);
        add_line!(gen_file, "return false;");
        dedent!(gen_file);

        dedent!(gen_file);
        add_line!(gen_file, "}}");

        dedent!(gen_file);
        add_line!(gen_file, "}}");
        add_line!(gen_file, "");
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
        return None;
    }

    fn add_lex_state(
        &mut self,
        gen_file: &mut GeneratorFile,
        state: LexState,
        transition_info: &Vec<TransitionSummary>,
        large_character_sets: &Vec<LargeCharacterSetInfo>,
    ) {
        if let Some(accept_action) = state.accept_action {
            add_line!(gen_file, "ACCEPT_TOKEN({});", self.symbol_ids[&accept_action]);
        }

        if let Some(eof_action) = state.eof_action {
            add_line!(gen_file, "if (eof) ADVANCE({});", eof_action.state);
        }

        for (i, (_, action)) in state.advance_actions.into_iter().enumerate() {
            let transition = &transition_info[i];
            add_whitespace!(gen_file);

            // If there is a helper function for this transition's character
            // set, then generate a call to that helper function.
            if let Some(call_id) = transition.call_id {
                let info = &large_character_sets[call_id];
                add!(gen_file, "if (");
                if !transition.is_included {
                    add!(gen_file, "!");
                }
                add!(
                    gen_file,
                    "{}_character_set_{}(lookahead)) ",
                    self.symbol_ids[&info.symbol],
                    info.index
                );
                self.add_advance_action(gen_file, &action);
                add!(gen_file, "\n");
                continue;
            }

            // Otherwise, generate code to compare the lookahead character
            // with all of the character ranges.
            if transition.ranges.len() > 0 {
                add!(gen_file, "if (");
                self.add_character_range_conditions(gen_file, &transition.ranges, transition.is_included, 2);
                add!(gen_file, ") ");
            }
            self.add_advance_action(gen_file, &action);
            add!(gen_file, "\n");
        }

        add_line!(gen_file, "END_STATE();");
    }

    fn add_character_range_conditions(
        &mut self,
        gen_file: &mut GeneratorFile,
        ranges: &[Range<char>],
        is_included: bool,
        indent_count: usize,
    ) {
        let mut line_break = "\n".to_string();
        for _ in 0..gen_file.indent_level + indent_count {
            line_break.push_str("  ");
        }

        for (i, range) in ranges.iter().enumerate() {
            if is_included {
                if i > 0 {
                    add!(gen_file, " ||{}", line_break);
                }
                if range.end == range.start {
                    add!(gen_file, "lookahead == ");
                    self.add_character(gen_file, range.start);
                } else if range.end as u32 == range.start as u32 + 1 {
                    add!(gen_file, "lookahead == ");
                    self.add_character(gen_file, range.start);
                    add!(gen_file, " ||{}lookahead == ", line_break);
                    self.add_character(gen_file, range.end);
                } else {
                    add!(gen_file, "(");
                    self.add_character(gen_file, range.start);
                    add!(gen_file, " <= lookahead && lookahead <= ");
                    self.add_character(gen_file, range.end);
                    add!(gen_file, ")");
                }
            } else {
                if i > 0 {
                    add!(gen_file, " &&{}", line_break);
                }
                if range.end == range.start {
                    add!(gen_file, "lookahead != ");
                    self.add_character(gen_file, range.start);
                } else if range.end as u32 == range.start as u32 + 1 {
                    add!(gen_file, "lookahead != ");
                    self.add_character(gen_file, range.start);
                    add!(gen_file, " &&{}lookahead != ", line_break);
                    self.add_character(gen_file, range.end);
                } else {
                    if range.start != '\0' {
                        add!(gen_file, "(lookahead < ");
                        self.add_character(gen_file, range.start);
                        add!(gen_file, " || ");
                        self.add_character(gen_file, range.end);
                        add!(gen_file, " < lookahead)");
                    } else {
                        add!(gen_file, "lookahead > ");
                        self.add_character(gen_file, range.end);
                    }
                }
            }
        }
    }

    fn add_character_tree(&mut self, gen_file: &mut GeneratorFile, tree: Option<&CharacterTree>) {
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
                    add!(gen_file, "(");
                }

                add!(gen_file, "c {} ", op);
                self.add_character(gen_file, *value);

                if !simple {
                    if alternative.is_none() {
                        add!(gen_file, " && ");
                        self.add_character_tree(gen_file, consequence);
                    } else if consequence == Some(&CharacterTree::Yes) {
                        add!(gen_file, " || ");
                        self.add_character_tree(gen_file, alternative);
                    } else {
                        add!(gen_file, "\n");
                        indent!(gen_file);
                        add_whitespace!(gen_file);
                        add!(gen_file, "? ");
                        self.add_character_tree(gen_file, consequence);
                        add!(gen_file, "\n");
                        add_whitespace!(gen_file);
                        add!(gen_file, ": ");
                        self.add_character_tree(gen_file, alternative);
                        dedent!(gen_file);
                    }
                }

                if !simple {
                    add!(gen_file, ")");
                }
            }
            Some(CharacterTree::Yes) => {
                add!(gen_file, "true");
            }
            None => {
                add!(gen_file, "false");
            }
        }
    }

    fn add_advance_action(&mut self, gen_file: &mut GeneratorFile, action: &AdvanceAction) {
        if action.in_main_token {
            add!(gen_file, "ADVANCE({});", action.state);
        } else {
            add!(gen_file, "SKIP({})", action.state);
        }
    }

    fn add_lex_modes_list(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(
            gen_file,
            "static const TSLexMode ts_lex_modes[STATE_COUNT] = {{"
        );
        indent!(gen_file);
        for (i, state) in self.parse_table.states.iter().enumerate() {
            if state.is_end_of_non_terminal_extra() {
                add_line!(gen_file, "[{}] = {{(TSStateId)(-1)}},", i,);
            } else if state.external_lex_state_id > 0 {
                add_line!(
                    gen_file,
                    "[{}] = {{.lex_state = {}, .external_lex_state = {}}},",
                    i,
                    state.lex_state_id,
                    state.external_lex_state_id
                );
            } else {
                add_line!(gen_file, "[{}] = {{.lex_state = {}}},", i, state.lex_state_id);
            }
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_external_token_enum(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(gen_file, "enum {{");
        indent!(gen_file);
        for i in 0..self.syntax_grammar.external_tokens.len() {
            add_line!(
                gen_file,
                "{} = {},",
                self.external_token_id(&self.syntax_grammar.external_tokens[i]),
                i
            );
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_external_scanner_symbol_map(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(
            gen_file,
            "static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {{"
        );
        indent!(gen_file);
        for i in 0..self.syntax_grammar.external_tokens.len() {
            let token = &self.syntax_grammar.external_tokens[i];
            let id_token = token
                .corresponding_internal_token
                .unwrap_or(Symbol::external(i));
            add_line!(
                gen_file,
                "[{}] = {},",
                self.external_token_id(&token),
                self.symbol_ids[&id_token],
            );
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_external_scanner_states_list(&mut self, gen_file: &mut GeneratorFile) {
        add_line!(
            gen_file,
            "static const bool ts_external_scanner_states[{}][EXTERNAL_TOKEN_COUNT] = {{",
            self.parse_table.external_lex_states.len(),
        );
        indent!(gen_file);
        for i in 0..self.parse_table.external_lex_states.len() {
            if !self.parse_table.external_lex_states[i].is_empty() {
                add_line!(gen_file, "[{}] = {{", i);
                indent!(gen_file);
                for token in self.parse_table.external_lex_states[i].iter() {
                    add_line!(
                        gen_file,
                        "[{}] = true,",
                        self.external_token_id(&self.syntax_grammar.external_tokens[token.index])
                    );
                }
                dedent!(gen_file);
                add_line!(gen_file, "}},");
            }
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_parse_table(&mut self, gen_file: &mut GeneratorFile) {
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
            gen_file,
            "static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {{",
        );
        indent!(gen_file);

        let mut terminal_entries = Vec::new();
        let mut nonterminal_entries = Vec::new();

        for (i, state) in self
            .parse_table
            .states
            .iter()
            .enumerate()
            .take(self.large_state_count)
        {
            add_line!(gen_file, "[{}] = {{", i);
            indent!(gen_file);

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
                    gen_file,
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
                    gen_file,
                    "[{}] = ACTIONS({}),",
                    self.symbol_ids[symbol],
                    entry_id
                );
            }
            dedent!(gen_file);
            add_line!(gen_file, "}},");
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");

        if self.large_state_count < self.parse_table.states.len() {
            add_line!(gen_file, "static const uint16_t ts_small_parse_table[] = {{");
            indent!(gen_file);

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

                add_line!(gen_file, "[{}] = {},", index, values_with_symbols.len());
                indent!(gen_file);

                for ((value, kind), symbols) in values_with_symbols.iter_mut() {
                    if *kind == SymbolType::NonTerminal {
                        add_line!(gen_file, "STATE({}), {},", value, symbols.len());
                    } else {
                        add_line!(gen_file, "ACTIONS({}), {},", value, symbols.len());
                    }

                    symbols.sort_unstable();
                    indent!(gen_file);
                    for symbol in symbols {
                        add_line!(gen_file, "{},", self.symbol_ids[symbol]);
                    }
                    dedent!(gen_file);
                }

                dedent!(gen_file);

                index += 1 + values_with_symbols
                    .iter()
                    .map(|(_, symbols)| 2 + symbols.len())
                    .sum::<usize>();
            }

            dedent!(gen_file);
            add_line!(gen_file, "}};");
            add_line!(gen_file, "");

            add_line!(
                gen_file,
                "static const uint32_t ts_small_parse_table_map[] = {{"
            );
            indent!(gen_file);
            for i in self.large_state_count..self.parse_table.states.len() {
                add_line!(
                    gen_file,
                    "[SMALL_STATE({})] = {},",
                    i,
                    small_state_indices[i - self.large_state_count]
                );
            }
            dedent!(gen_file);
            add_line!(gen_file, "}};");
            add_line!(gen_file, "");
        }

        self.add_parse_action_list(gen_file, parse_table_entries);
    }

    fn add_parse_action_list(&mut self, gen_file: &mut GeneratorFile, parse_table_entries: Vec<(usize, ParseTableEntry)>) {
        add_line!(
            gen_file,
            "static const TSParseActionEntry ts_parse_actions[] = {{"
        );
        indent!(gen_file);
        for (i, entry) in parse_table_entries {
            add!(
                gen_file,
                "  [{}] = {{.entry = {{.count = {}, .reusable = {}}}}},",
                i,
                entry.actions.len(),
                entry.reusable
            );
            for action in entry.actions {
                add!(gen_file, " ");
                match action {
                    ParseAction::Accept => add!(gen_file, " ACCEPT_INPUT()"),
                    ParseAction::Recover => add!(gen_file, "RECOVER()"),
                    ParseAction::ShiftExtra => add!(gen_file, "SHIFT_EXTRA()"),
                    ParseAction::Shift {
                        state,
                        is_repetition,
                    } => {
                        if is_repetition {
                            add!(gen_file, "SHIFT_REPEAT({})", state);
                        } else {
                            add!(gen_file, "SHIFT({})", state);
                        }
                    }
                    ParseAction::Reduce {
                        symbol,
                        child_count,
                        dynamic_precedence,
                        production_id,
                        ..
                    } => {
                        add!(gen_file, "REDUCE({}, {}", self.symbol_ids[&symbol], child_count);
                        if dynamic_precedence != 0 {
                            add!(gen_file, ", .dynamic_precedence = {}", dynamic_precedence);
                        }
                        if production_id != 0 {
                            add!(gen_file, ", .production_id = {}", production_id);
                        }
                        add!(gen_file, ")");
                    }
                }
                add!(gen_file, ",")
            }
            add!(gen_file, "\n");
        }
        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "");
    }

    fn add_parser_export(&mut self, header_file: &mut GeneratorFile, gen_file: &mut GeneratorFile) {
        let language_function_name = format!("tree_sitter_{}", self.language_name);
        let external_scanner_name = format!("{}_external_scanner", language_function_name);
        let extern_macro_name = format!("TS{}EXTERN", self.language_name.to_uppercase());
        let language_function_signature = format!("{} const TSLanguage *{}(void)", extern_macro_name, language_function_name);

        add_line!(gen_file, "#ifdef __cplusplus");
        add_line!(gen_file, r#"extern "C" {{"#);
        add_line!(gen_file, "#endif");

        if !self.syntax_grammar.external_tokens.is_empty() {
            add_line!(gen_file, "void *{}_create(void);", external_scanner_name);
            add_line!(gen_file, "void {}_destroy(void *);", external_scanner_name);
            add_line!(
                gen_file,
                "bool {}_scan(void *, TSLexer *, const bool *);",
                external_scanner_name
            );
            add_line!(
                gen_file,
                "unsigned {}_serialize(void *, char *);",
                external_scanner_name
            );
            add_line!(
                gen_file,
                "void {}_deserialize(void *, const char *, unsigned);",
                external_scanner_name
            );
            add_line!(gen_file, "");
        }

        add_line!(header_file, "#ifdef _WIN32");
        add_line!(header_file, "#define {} __declspec(dllexport)", extern_macro_name);
        add_line!(header_file, "#else");
        add_line!(header_file, "#define {} extern", extern_macro_name);
        add_line!(header_file, "#endif");
        add_line!(header_file, "");
        add_line!(header_file, "{};", language_function_signature);
        add_line!(header_file, "");

        add_line!(gen_file, "{} {{", language_function_signature);
        indent!(gen_file);
        add_line!(gen_file, "static const TSLanguage language = {{");
        indent!(gen_file);
        add_line!(gen_file, ".version = LANGUAGE_VERSION,");

        // Quantities
        add_line!(gen_file, ".symbol_count = SYMBOL_COUNT,");
        add_line!(gen_file, ".alias_count = ALIAS_COUNT,");
        add_line!(gen_file, ".token_count = TOKEN_COUNT,");
        add_line!(gen_file, ".external_token_count = EXTERNAL_TOKEN_COUNT,");
        add_line!(gen_file, ".state_count = STATE_COUNT,");
        add_line!(gen_file, ".large_state_count = LARGE_STATE_COUNT,");
        if self.next_abi {
            add_line!(gen_file, ".production_id_count = PRODUCTION_ID_COUNT,");
        }
        add_line!(gen_file, ".field_count = FIELD_COUNT,");
        add_line!(
            gen_file,
            ".max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,"
        );

        // Parse table
        add_line!(gen_file, ".parse_table = &ts_parse_table[0][0],");
        if self.large_state_count < self.parse_table.states.len() {
            add_line!(gen_file, ".small_parse_table = ts_small_parse_table,");
            add_line!(gen_file, ".small_parse_table_map = ts_small_parse_table_map,");
        }
        add_line!(gen_file, ".parse_actions = ts_parse_actions,");

        // Metadata
        add_line!(gen_file, ".symbol_names = ts_symbol_names,");
        if !self.field_names.is_empty() {
            add_line!(gen_file, ".field_names = ts_field_names,");
            add_line!(gen_file, ".field_map_slices = ts_field_map_slices,");
            add_line!(gen_file, ".field_map_entries = ts_field_map_entries,");
        }
        add_line!(gen_file, ".symbol_metadata = ts_symbol_metadata,");
        add_line!(gen_file, ".public_symbol_map = ts_symbol_map,");
        add_line!(gen_file, ".alias_map = ts_non_terminal_alias_map,");
        if !self.parse_table.production_infos.is_empty() {
            add_line!(gen_file, ".alias_sequences = &ts_alias_sequences[0][0],");
        }

        // Lexing
        add_line!(gen_file, ".lex_modes = ts_lex_modes,");
        add_line!(gen_file, ".lex_fn = ts_lex,");
        if let Some(keyword_capture_token) = self.keyword_capture_token {
            add_line!(gen_file, ".keyword_lex_fn = ts_lex_keywords,");
            add_line!(
                gen_file,
                ".keyword_capture_token = {},",
                self.symbol_ids[&keyword_capture_token]
            );
        }

        if !self.syntax_grammar.external_tokens.is_empty() {
            add_line!(gen_file, ".external_scanner = {{");
            indent!(gen_file);
            add_line!(gen_file, "&ts_external_scanner_states[0][0],");
            add_line!(gen_file, "ts_external_scanner_symbol_map,");
            add_line!(gen_file, "{}_create,", external_scanner_name);
            add_line!(gen_file, "{}_destroy,", external_scanner_name);
            add_line!(gen_file, "{}_scan,", external_scanner_name);
            add_line!(gen_file, "{}_serialize,", external_scanner_name);
            add_line!(gen_file, "{}_deserialize,", external_scanner_name);
            dedent!(gen_file);
            add_line!(gen_file, "}},");
        }

        dedent!(gen_file);
        add_line!(gen_file, "}};");
        add_line!(gen_file, "return &language;");
        dedent!(gen_file);
        add_line!(gen_file, "}}");
        add_line!(gen_file, "#ifdef __cplusplus");
        add_line!(gen_file, "}}");
        add_line!(gen_file, "#endif");
    }

    fn add_include_guard(&mut self, header_file: &mut GeneratorFile) {
        let header_macro_name = format!("TREE_SITTER_{}_PARSER_H_", self.language_name.to_uppercase());
        add_line!(header_file, "#ifndef {}", header_macro_name);
        add_line!(header_file, "#define {}", header_macro_name);
        add_line!(header_file, "");
    }

    fn add_include_guard_end(&mut self, header_file: &mut GeneratorFile) {
        add_line!(header_file, "#endif");
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
                '?' => result += "\\?",
                '\\' => result += "\\\\",
                '\u{000c}' => result += "\\f",
                '\n' => result += "\\n",
                '\r' => result += "\\r",
                '\t' => result += "\\t",
                _ => result.push(c),
            }
        }
        result
    }

    fn add_character(&mut self, gen_file: &mut GeneratorFile, c: char) {
        match c {
            '\'' => add!(gen_file, "'\\''"),
            '\\' => add!(gen_file, "'\\\\'"),
            '\u{000c}' => add!(gen_file, "'\\f'"),
            '\n' => add!(gen_file, "'\\n'"),
            '\t' => add!(gen_file, "'\\t'"),
            '\r' => add!(gen_file, "'\\r'"),
            _ => {
                if c == ' ' || c.is_ascii_graphic() {
                    add!(gen_file, "'{}'", c)
                } else {
                    add!(gen_file, "{}", c as u32)
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
    default_aliases: AliasMap,
    next_abi: bool,
) -> (String, String) {
    Generator {
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
        next_abi,
    }
    .generate()
}
