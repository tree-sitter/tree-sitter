use std::{
    collections::HashMap,
    io::Write,
    ops::RangeInclusive,
};

use super::{
    nfa::CharacterSet,
    render_buffer::RenderBuffer,
    render_context::RenderContext,
    render_target::RenderTarget,
    render::ABI_VERSION_WITH_PRIMARY_STATES,
    rules::{Symbol, TokenSet},
    tables::{
        AdvanceAction, FieldLocation, ParseAction, ParseState,
    },
};


pub struct RenderTargetC {
    pub buffer: RenderBuffer,
}


impl RenderTargetC {
    pub fn new(indent_width: usize) -> Self {
        Self {
            buffer: RenderBuffer::new(indent_width),
        }
    }

    fn field_id(&self, field_name: &str) -> String {
        format!("field_{field_name}")
    }
}

impl RenderTarget for RenderTargetC {
    fn begin_language(&mut self, generator: &dyn RenderContext) {
        // add_includes
        add_line!(self, "#include \"tree_sitter/parser.h\"");
        add_line!(self, "");

        // add_pragmas
        add_line!(self, "#if defined(__GNUC__) || defined(__clang__)");
        add_line!(
            self,
            "#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\""
        );
        add_line!(self, "#endif");
        add_line!(self, "");

        // Compiling large lexer functions can be very slow. Disabling optimizations
        // is not ideal, but only a very small fraction of overall parse time is
        // spent lexing, so the performance impact of this is negligible.
        if generator.get_main_lex_table_state_count() > 300 {
            add_line!(self, "#ifdef _MSC_VER");
            add_line!(self, "#pragma optimize(\"\", off)");
            add_line!(self, "#elif defined(__clang__)");
            add_line!(self, "#pragma clang optimize off");
            add_line!(self, "#elif defined(__GNUC__)");
            add_line!(self, "#pragma GCC optimize (\"O0\")");
            add_line!(self, "#endif");
            add_line!(self, "");
        }

        // add_stats
        add_line!(self, "#define LANGUAGE_VERSION {}", generator.get_abi_version());
        add_line!(
            self,
            "#define STATE_COUNT {}",
            generator.get_state_count()
        );
        add_line!(self, "#define LARGE_STATE_COUNT {}", generator.get_large_state_count());

        add_line!(
            self,
            "#define SYMBOL_COUNT {}",
            generator.get_symbol_count()
        );
        add_line!(self, "#define ALIAS_COUNT {}", generator.get_alias_count());
        add_line!(self, "#define TOKEN_COUNT {}", generator.get_token_count());
        add_line!(
            self,
            "#define EXTERNAL_TOKEN_COUNT {}",
            generator.get_external_token_count()
        );
        add_line!(self, "#define FIELD_COUNT {}", generator.get_field_count());
        add_line!(
            self,
            "#define MAX_ALIAS_SEQUENCE_LENGTH {}",
            generator.get_max_alias_sequence_length()
        );
        add_line!(
            self,
            "#define PRODUCTION_ID_COUNT {}",
            generator.get_production_id_count()
        );
        add_line!(self, "");
    }

    fn begin_symbol_enum(&mut self) {
        add_line!(self, "enum ts_symbol_identifiers {{");
        indent!(self);
    }
    fn add_symbol_enum_item(&mut self, name: &str, index: usize) {
        add_line!(self, "{} = {},", name, index);
    }
    fn end_symbol_enum(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_symbol_names_list(&mut self) {
        add_line!(self, "static const char * const ts_symbol_names[] = {{");
        indent!(self);
    }
    fn add_symbol_names_list_item(&mut self, name: &str, text: &str) {
        add_line!(self, "[{}] = \"{}\",", name, text);
    }
    fn end_symbol_names_list(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_symbol_map(&mut self) {
        add_line!(self, "static const TSSymbol ts_symbol_map[] = {{");
        indent!(self);
    }
    fn add_symbol_map_item(&mut self, src_name: &str, trg_name: &str) {
        add_line!(self, "[{}] = {},", src_name, trg_name);
    }
    fn end_symbol_map(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_symbol_metadata(&mut self) {
        add_line!(self, "static const TSSymbolMetadata ts_symbol_metadata[] = {{");
        indent!(self);
    }
    fn add_symbol_metadata_item(&mut self, name: &str, visible: bool, named: bool, supertype: bool) {
        add_line!(self, "[{}] = {{", name);
        indent!(self);
        add_line!(self, ".visible = {},", if visible { "true" } else { "false" });
        add_line!(self, ".named = {},", if named { "true" } else { "false" });
        if supertype {
            add_line!(self, ".supertype = true,");
        }
        dedent!(self);
        add_line!(self, "}},");
    }
    fn end_symbol_metadata(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_field_enum(&mut self) {
        add_line!(self, "enum ts_field_identifiers {{");
        indent!(self);
    }
    fn add_field_enum_item(&mut self, name: &str, index: usize) {
        add_line!(self, "{} = {},", name, index);
    }
    fn end_field_enum(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_field_names(&mut self) {
        add_line!(self, "static const char * const ts_field_names[] = {{");
        indent!(self);
        add_line!(self, "[0] = NULL,");
    }
    fn add_field_name_item(&mut self, name: &str, text: &str) {
        add_line!(self, "[{}] = \"{}\",", name, text);
    }
    fn end_field_names(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_field_map_slices(&mut self) {
        add_line!(self, "static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {{");
        indent!(self);
    }
    fn add_field_map_slices_item(&mut self, production_id: usize, row_id: usize, length: usize) {
        add_line!(self, "[{production_id}] = {{.index = {row_id}, .length = {length}}},");
    }
    fn end_field_map_slices(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_field_map_entries(&mut self) {
        add_line!(self, "static const TSFieldMapEntry ts_field_map_entries[] = {{");
        indent!(self);
    }
    fn add_field_map_entries_item(&mut self, row_index: usize, field_pairs: Vec<(String, FieldLocation)>) {
        add_line!(self, "[{row_index}] =");
        indent!(self);
        for (field_name, location) in field_pairs {
            let field_id = self.field_id(&field_name);
            add_whitespace!(self);
            add!(self, "{{{}, {}", field_id, location.index);
            if location.inherited {
                add!(self, ", .inherited = true");
            }
            add!(self, "}},\n");
        }
        dedent!(self);
    }
    fn end_field_map_entries(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_alias_sequences(&mut self) {
        add_line!(self, "static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {{");
        indent!(self);
    }
    fn add_alias_sequences_item(&mut self, i: usize, alias_ids: Vec<Option<&String>>) {
        if alias_ids.is_empty() {
            // Work around MSVC's intolerance of empty array initializers by
            // explicitly zero-initializing the first element.
            if i == 0 {
                add_line!(self, "[0] = {{0}},");
            }
        } else {
            add_line!(self, "[{}] = {{", i);
            indent!(self);
            for (j, alias_id) in alias_ids.iter().enumerate() {
                if let Some(alias_id) = alias_id {
                    add_line!(self, "[{}] = {},", j, alias_id);
                }
            }
            dedent!(self);
            add_line!(self, "}},");
        }
    }
    fn end_alias_sequences(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_non_terminal_alias_map(&mut self) {
        add_line!(self, "static const uint16_t ts_non_terminal_alias_map[] = {{");
        indent!(self);
    }
    fn add_non_terminal_alias_map_item(&mut self, symbol_id: &str, count: usize, public_symbol_id: &str, alias_ids: Vec<&String>) {
        add_line!(self, "{symbol_id}, {},", count);
        indent!(self);
        add_line!(self, "{public_symbol_id},");
        for alias_id in alias_ids {
            add_line!(self, "{alias_id},");
        }
        dedent!(self);
    }
    fn end_non_terminal_alias_map(&mut self) {
        add_line!(self, "0,");
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_primary_state_ids(&mut self) {
        add_line!(self, "static const TSStateId ts_primary_state_ids[STATE_COUNT] = {{");
        indent!(self);
    }
    fn add_primary_state_ids_item(&mut self, idx: usize, primary_state: usize) {
        add_line!(self, "[{idx}] = {primary_state},");
    }
    fn end_primary_state_ids(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_lex_function(&mut self, name: &str) {
        add_line!(
            self,
            "static bool {name}(TSLexer *lexer, TSStateId state) {{",
        );
        indent!(self);

        add_line!(self, "START_LEXER();");
        add_line!(self, "eof = lexer->eof(lexer);");
        add_line!(self, "switch (state) {{");

        indent!(self);
    }
    fn begin_lex_function_case(&mut self, state_ix: usize) {
        add_line!(self, "case {state_ix}:");
        indent!(self);
    }
    fn add_lex_function_case_accept_token(&mut self, symbol_id: &String) {
        add_line!(self, "ACCEPT_TOKEN({symbol_id});");
    }
    fn add_lex_function_case_advance_eof(&mut self, state: usize) {
        add_line!(self, "if (eof) ADVANCE({state});");
    }
    fn add_lex_function_case_advance_map(&mut self, transitions: &[(CharacterSet, AdvanceAction)]) {
        add_line!(self, "ADVANCE_MAP(");
        indent!(self);
        for (chars, action) in transitions {
            for range in chars.ranges() {
                add_whitespace!(self);
                self.add_character(*range.start());
                add!(self, ", {},\n", action.state);
                if *range.end() > *range.start() {
                    add_whitespace!(self);
                    self.add_character(*range.end());
                    add!(self, ", {},\n", action.state);
                }
            }
        }
        dedent!(self);
        add_line!(self, ");");
    }
    fn add_lex_function_case_advance_to(&mut self, state: usize, in_main_token: bool) {
        if in_main_token {
            add!(self, "ADVANCE({state});");
        } else {
            add!(self, "SKIP({state});");
        }
    }
    fn add_lex_function_case_advance(&mut self, 
        large: Option<(&CharacterSet, &String, bool)>, 
        asserted_chars: &CharacterSet,
        asserted_chars_are_inclusive: bool,
        negated_chars: &CharacterSet,
        action: &AdvanceAction
    ) {
        add_whitespace!(self);
        let mut line_break = "\n".to_string();
        for _ in 0..self.buffer.indent_level + 2 {
            line_break.push_str("  ");
        }
        let has_positive_condition = large.is_some() || !asserted_chars.is_empty();
        let has_negative_condition = !negated_chars.is_empty();
        let has_condition = has_positive_condition || has_negative_condition;
        if has_condition {
            add!(self, "if (");
            if has_positive_condition && has_negative_condition {
                add!(self, "(");
            }
        }
        if let Some((large_set, large_set_name, check_eof)) = large {
            // If the character set contains the null character, check that we
            // are not at the end of the file.
            if check_eof {
                add!(self, "(!eof && ")
            }
            self.add_large_set_contains_check(large_set_name, large_set.range_count());
            if check_eof {
                add!(self, ")");
            }
        }
        if !asserted_chars.is_empty() {
            if large.is_some() {
                add!(self, " ||{line_break}");
            }
            self.add_character_range_conditions(&asserted_chars, asserted_chars_are_inclusive, &line_break);
        }
        if has_negative_condition {
            if has_positive_condition {
                add!(self, ") &&{line_break}");
            }
            self.add_character_range_conditions(&negated_chars, false, &line_break);
        }
        if has_condition {
            add!(self, ") ");
        }
        self.add_lex_function_case_advance_to(action.state, action.in_main_token);
        add!(self, "\n");
    }
    fn add_large_set_contains_check(&mut self, large_set_name: &String, range_count: usize) {
        add!(self, "set_contains({large_set_name}, {range_count}, lookahead)");
    }
    fn add_character_range_conditions(
        &mut self,
        characters: &CharacterSet,
        is_included: bool,
        line_break: &str,
    ) {
        for (i, range) in characters.ranges().enumerate() {
            let start = *range.start();
            let end = *range.end();
            if is_included {
                if i > 0 {
                    add!(self, " ||{line_break}");
                }

                if start == '\0' {
                    add!(self, "(!eof && ");
                    if end == '\0' {
                        add!(self, "lookahead == 0");
                    } else {
                        add!(self, "lookahead <= ");
                    }
                    self.add_character(end);
                    add!(self, ")");
                    continue;
                } else if end == start {
                    add!(self, "lookahead == ");
                    self.add_character(start);
                } else if end as u32 == start as u32 + 1 {
                    add!(self, "lookahead == ");
                    self.add_character(start);
                    add!(self, " ||{line_break}lookahead == ");
                    self.add_character(end);
                } else {
                    add!(self, "(");
                    self.add_character(start);
                    add!(self, " <= lookahead && lookahead <= ");
                    self.add_character(end);
                    add!(self, ")");
                }
            } else {
                if i > 0 {
                    add!(self, " &&{line_break}");
                }
                if end == start {
                    add!(self, "lookahead != ");
                    self.add_character(start);
                } else if end as u32 == start as u32 + 1 {
                    add!(self, "lookahead != ");
                    self.add_character(start);
                    add!(self, " &&{line_break}lookahead != ");
                    self.add_character(end);
                } else if start != '\0' {
                    add!(self, "(lookahead < ");
                    self.add_character(start);
                    add!(self, " || ");
                    self.add_character(end);
                    add!(self, " < lookahead)");
                } else {
                    add!(self, "lookahead > ");
                    self.add_character(end);
                }
            }
        }
    }
    fn end_lex_function_case(&mut self) {
        add_line!(self, "END_STATE();");
        dedent!(self);
    }
    fn end_lex_function(&mut self) {
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

    fn begin_character_set(&mut self, name: &str) {
        add_line!(
            self,
            "static TSCharacterRange {}[] = {{",
            name
        );
        indent!(self);
    }
    fn add_character_set_item(&mut self, ix: usize, range: RangeInclusive<char>) {
        let column = ix % 8;
        if column == 0 {
            if ix > 0 {
                add!(self, "\n");
            }
            add_whitespace!(self);
        } else {
            add!(self, " ");
        }
        add!(self, "{{");
        self.add_character(*range.start());
        add!(self, ", ");
        self.add_character(*range.end());
        add!(self, "}},");
    }
    fn end_character_set(&mut self, _count: usize) {
        add!(self, "\n");
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_lex_modes(&mut self) {
        add_line!(self, "static const TSLexMode ts_lex_modes[STATE_COUNT] = {{");
        indent!(self);
    }
    fn add_lex_modes_item(&mut self, index: usize, state: &ParseState) {
        if state.is_end_of_non_terminal_extra() {
            add_line!(self, "[{index}] = {{(TSStateId)(-1)}},");
        } else if state.external_lex_state_id > 0 {
            add_line!(
                self,
                "[{index}] = {{.lex_state = {}, .external_lex_state = {}}},",
                state.lex_state_id,
                state.external_lex_state_id
            );
        } else {
            add_line!(self, "[{index}] = {{.lex_state = {}}},", state.lex_state_id);
        }
    }
    fn end_lex_modes(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_external_token_enum(&mut self) {
        add_line!(self, "enum ts_external_scanner_symbol_identifiers {{");
        indent!(self);
    }
    fn add_external_token_enum_item(&mut self, name: &str, index: usize) {
        add_line!(self, "{} = {},", name, index);
    }
    fn end_external_token_enum(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_external_scanner_symbol_map(&mut self) {
        add_line!(self, "static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {{");
        indent!(self);
    }
    fn add_external_scanner_symbol_map_item(&mut self, src_name: &str, trg_name: &str) {
        add_line!(self, "[{}] = {},", src_name, trg_name);
    }
    fn end_external_scanner_symbol_map(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_external_scanner_states(&mut self, external_lext_state_count: usize) {
        add_line!(self, "static const bool ts_external_scanner_states[{}][EXTERNAL_TOKEN_COUNT] = {{", external_lext_state_count);
        indent!(self);
    }
    fn add_external_scanner_states_item(&mut self, context: &dyn RenderContext, index: usize, token_set: &TokenSet) {
        add_line!(self, "[{}] = {{", index);
        indent!(self);
        for token in token_set.iter() {
            let external_token_id = context.get_external_token_id(token.index);
            add_line!(self, "[{}] = true,", external_token_id);
        }
        dedent!(self);
        add_line!(self, "}},");
    }
    fn end_external_scanner_states(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_parse_table(&mut self) {
        add_line!(self, "static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {{");
        indent!(self);
    }
    fn begin_parse_table_section(&mut self, index: usize) {
        add_line!(self, "[{}] = {{", index);
        indent!(self);
    }
    fn add_parse_table_state_item(&mut self, symbol_id: &String, state: usize) {
        add_line!(self, "[{symbol_id}] = STATE({state}),");
    }
    fn add_parse_table_actions_item(&mut self, entry_index: usize, symbol_id: &String) {
        add_line!(self, "[{symbol_id}] = ACTIONS({entry_index}),");
    }
    fn end_parse_table_section(&mut self) {
        dedent!(self);
        add_line!(self, "}},");
    }
    fn end_parse_table(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_small_parse_table(&mut self) {
        add_line!(self, "static const uint16_t ts_small_parse_table[] = {{");
        indent!(self);
    }
    fn begin_small_parse_table_section(&mut self, index: usize, count: usize) {
        add_line!(self, "[{index}] = {count},");
        indent!(self);
    }
    fn add_small_parse_table_state_item(&mut self, value: usize, count: usize) {
        add_line!(self, "STATE({value}), {count},");
    }
    fn add_small_parse_table_actions_item(&mut self, value: usize, count: usize) {
        add_line!(self, "ACTIONS({value}), {count},");
    }
    fn add_small_parse_table_symbol_item(&mut self, symbol_id: &String) {
        indent!(self);
        add_line!(self, "{symbol_id},");
        dedent!(self);
    }
    fn end_small_parse_table_section(&mut self) {
        dedent!(self);
    }
    fn end_small_parse_table(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_small_parse_table_map(&mut self) {
        add_line!(self, "static const uint32_t ts_small_parse_table_map[] = {{");
        indent!(self);
    }
    fn add_small_parse_table_map_item(&mut self, src_index: usize, trg_index: usize) {
        add_line!(self, "[SMALL_STATE({src_index})] = {trg_index},");
    }
    fn end_small_parse_table_map(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn begin_parse_actions(&mut self) {
        add_line!(self, "static const TSParseActionEntry ts_parse_actions[] = {{");
        indent!(self);
    }
    fn begin_parse_actions_entry(&mut self, index: usize, count: usize, reusable: bool) {
        add!(
            self,
            "  [{index}] = {{.entry = {{.count = {}, .reusable = {}}}}},",
            count,
            reusable
        );
    }
    fn add_parse_actions_action(&mut self, action: &ParseAction, symbol_ids: &HashMap<Symbol, String>) {
        add!(self, " ");
        match action {
            ParseAction::Accept => add!(self, " ACCEPT_INPUT()"),
            ParseAction::Recover => add!(self, "RECOVER()"),
            ParseAction::ShiftExtra => add!(self, "SHIFT_EXTRA()"),
            ParseAction::Shift {
                state,
                is_repetition,
            } => {
                if *is_repetition {
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
                add!(
                    self,
                    "REDUCE({}, {child_count}, {dynamic_precedence}, {production_id})",
                    symbol_ids[symbol]
                );
            }
        }
        add!(self, ",");
    }
    fn end_parse_actions_entry(&mut self) {
        add!(self, "\n");
    }
    fn end_parse_actions(&mut self) {
        dedent!(self);
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn end_language(&mut self, context: &dyn RenderContext) {
        let language_function_name = format!("tree_sitter_{}", context.get_language_name());
        let external_scanner_name = format!("{language_function_name}_external_scanner");

        add_line!(self, "#ifdef __cplusplus");
        add_line!(self, r#"extern "C" {{"#);
        add_line!(self, "#endif");

        if context.get_external_token_count() > 0 {
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

        add_line!(self, "#ifdef TREE_SITTER_HIDE_SYMBOLS");
        add_line!(self, "#define TS_PUBLIC");
        add_line!(self, "#elif defined(_WIN32)");
        add_line!(self, "#define TS_PUBLIC __declspec(dllexport)");
        add_line!(self, "#else");
        add_line!(
            self,
            "#define TS_PUBLIC __attribute__((visibility(\"default\")))"
        );
        add_line!(self, "#endif");
        add_line!(self, "");

        add_line!(
            self,
            "TS_PUBLIC const TSLanguage *{language_function_name}(void) {{",
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
        if context.get_large_state_count() < context.get_state_count() {
            add_line!(self, ".small_parse_table = ts_small_parse_table,");
            add_line!(self, ".small_parse_table_map = ts_small_parse_table_map,");
        }
        add_line!(self, ".parse_actions = ts_parse_actions,");

        // Metadata
        add_line!(self, ".symbol_names = ts_symbol_names,");
        if context.get_field_count() > 0 {
            add_line!(self, ".field_names = ts_field_names,");
            add_line!(self, ".field_map_slices = ts_field_map_slices,");
            add_line!(self, ".field_map_entries = ts_field_map_entries,");
        }
        add_line!(self, ".symbol_metadata = ts_symbol_metadata,");
        add_line!(self, ".public_symbol_map = ts_symbol_map,");
        add_line!(self, ".alias_map = ts_non_terminal_alias_map,");
        if context.get_production_id_count() > 0 {
            add_line!(self, ".alias_sequences = &ts_alias_sequences[0][0],");
        }

        // Lexing
        add_line!(self, ".lex_modes = ts_lex_modes,");
        add_line!(self, ".lex_fn = ts_lex,");
        if let Some(keyword_capture_token_id) = &context.get_keyword_capture_token_id() {
            add_line!(self, ".keyword_lex_fn = ts_lex_keywords,");
            add_line!(
                self,
                ".keyword_capture_token = {},",
                keyword_capture_token_id
            );
        }

        if context.get_external_token_count() > 0 {
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

        if context.get_abi_version() >= ABI_VERSION_WITH_PRIMARY_STATES {
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

    fn add_character(&mut self, c: char) {
        match c {
            '\'' => add!(self, "'\\''"),
            '\\' => add!(self, "'\\\\'"),
            '\u{000c}' => add!(self, "'\\f'"),
            '\n' => add!(self, "'\\n'"),
            '\t' => add!(self, "'\\t'"),
            '\r' => add!(self, "'\\r'"),
            _ => {
                if c == '\0' {
                    add!(self, "0")
                } else if c == ' ' || c.is_ascii_graphic() {
                    add!(self, "'{c}'");
                } else {
                    add!(self, "0x{:02x}", c as u32);
                }
            }
        }
    }

    fn buffer_ref(&mut self) -> &mut RenderBuffer {
        &mut self.buffer
    }
}
