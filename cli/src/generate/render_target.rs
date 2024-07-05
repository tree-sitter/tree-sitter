use std::io::Write;
use std::collections::HashMap;
use std::ops::RangeInclusive;
use super::nfa::CharacterSet;
use super::render_buffer::RenderBuffer;
use super::render_context::RenderContext;
use super::rules::{Symbol, TokenSet};
use super::tables::{AdvanceAction, FieldLocation, ParseAction, ParseState};


/// Macros available to RenderTarget implementations as an economical syntax for code generation.

#[macro_export]
macro_rules! add {
    ($this: tt, $($arg: tt)*) => {{
        $this.buffer_ref().write_fmt(format_args!($($arg)*)).unwrap();
    }}
}

#[macro_export]
macro_rules! add_whitespace {
    ($this:tt) => {{
        $this.buffer_ref().add_whitespace();
    }};
}

#[macro_export]
macro_rules! add_newline {
    ($this:tt) => {{
        $this.buffer_ref().add_newline();
    }};
}

#[macro_export]
macro_rules! add_line {
    ($this: tt, $($arg: tt)*) => {{
        let buffer = $this.buffer_ref();
        buffer.add_whitespace();
        buffer.write_fmt(format_args!($($arg)*)).unwrap();
        buffer.add_newline();
    }}
}

#[macro_export]
macro_rules! indent {
    ($this:tt) => {
        $this.buffer_ref().indent(1);
    };
}

#[macro_export]
macro_rules! dedent {
    ($this:tt) => {
        $this.buffer_ref().dedent(1);
    };
}


/// The RenderTarget trait specifies the methods invoked by Generator for the purpose of code generation.

pub trait RenderTarget {
    /// Initiate the generation process for a language with the given name.
    fn begin_language(&mut self, context: &dyn RenderContext);

    /// Define the enum type associating symbol names (including aliases) to indices, beginning with ts_builtin_sym_end = 0.
    fn begin_symbol_enum(&mut self);
    fn add_symbol_enum_item(&mut self, name: &str, index: usize);
    fn end_symbol_enum(&mut self);

    /// Define ts_symbol_names -- i.e. the association of symbol indices to string types, which are either non-terminal names or terminal literals. Both symbol name and index are given for convenience.
    fn begin_symbol_names_list(&mut self);
    fn add_symbol_names_list_item(&mut self, name: &str, text: &str);
    fn end_symbol_names_list(&mut self);

    /// Define ts_symbol_map...
    fn begin_symbol_map(&mut self);
    fn add_symbol_map_item(&mut self, src_name: &str, trg_name: &str);
    fn end_symbol_map(&mut self);

    /// Define ts_symbol_metadata...
    fn begin_symbol_metadata(&mut self);
    fn add_symbol_metadata_item(&mut self, name: &str, visible: bool, named: bool, supertype: bool);
    fn end_symbol_metadata(&mut self);

    /// Define the enum associating field names to indices (beginning at 1).
    fn begin_field_enum(&mut self);
    fn add_field_enum_item(&mut self, name: &str, index: usize);
    fn end_field_enum(&mut self);

    /// Define ts_field_names
    fn begin_field_names(&mut self);
    fn add_field_name_item(&mut self, name: &str, text: &str);
    fn end_field_names(&mut self);

    /// Define ts_field_map_slices
    fn begin_field_map_slices(&mut self);
    fn add_field_map_slices_item(&mut self, production_id: usize, row_id: usize, length: usize);
    fn end_field_map_slices(&mut self);

    /// Define ts_field_map_entries
    fn begin_field_map_entries(&mut self);
    fn add_field_map_entries_item(&mut self, row_index: usize, field_pairs: Vec<(String, FieldLocation)>);
    fn end_field_map_entries(&mut self);

    /// Define ts_alias_sequences
    fn begin_alias_sequences(&mut self);
    fn add_alias_sequences_item(&mut self, index: usize, alias_ids: Vec<Option<&String>>);
    fn end_alias_sequences(&mut self);
    
    /// Define ts_non_terminal_alias_map (null-terminated)
    fn begin_non_terminal_alias_map(&mut self);
    fn add_non_terminal_alias_map_item(&mut self, symbol_id: &str, count: usize, public_symbol_id: &str, alias_ids: Vec<&String>);
    fn end_non_terminal_alias_map(&mut self);
    
    /// Define ts_primary_state_ids
    fn begin_primary_state_ids(&mut self);
    fn add_primary_state_ids_item(&mut self, index: usize, primary_state: usize);
    fn end_primary_state_ids(&mut self);
    
    // Define ts_lex_modes
    fn begin_lex_modes(&mut self);
    fn add_lex_modes_item(&mut self, index: usize, parse_state: &ParseState);
    fn end_lex_modes(&mut self);

    // Define ts_external_scanner_symbol_identifiers
    fn begin_external_token_enum(&mut self);
    fn add_external_token_enum_item(&mut self, name: &str, index: usize);
    fn end_external_token_enum(&mut self);

    // Define ts_external_scanner_symbol_map
    fn begin_external_scanner_symbol_map(&mut self);
    fn add_external_scanner_symbol_map_item(&mut self, src_name: &str, trg_name: &str);
    fn end_external_scanner_symbol_map(&mut self);

    // Define ts_external_scanner_states
    fn begin_external_scanner_states(&mut self, external_lext_state_count: usize);
    fn add_external_scanner_states_item(&mut self, context: &dyn RenderContext, index: usize, token_set: &TokenSet);
    fn end_external_scanner_states(&mut self);
    
    // Define ts_parse_table
    fn begin_parse_table(&mut self);
    fn begin_parse_table_section(&mut self, index: usize);
    fn add_parse_table_state_item(&mut self, symbol_id: &String, state: usize);
    fn add_parse_table_actions_item(&mut self, entry_index: usize, symbol_id: &String);
    fn end_parse_table_section(&mut self);
    fn end_parse_table(&mut self);
    
    // Define ts_small_parse_table
    fn begin_small_parse_table(&mut self);
    fn begin_small_parse_table_section(&mut self, index: usize, count: usize);
    fn add_small_parse_table_state_item(&mut self, value: usize, count: usize);
    fn add_small_parse_table_actions_item(&mut self, value: usize, count: usize);
    fn add_small_parse_table_symbol_item(&mut self, symbol_id: &String);
    fn end_small_parse_table_section(&mut self);
    fn end_small_parse_table(&mut self);
    
    // Define ts_small_parse_table_map
    fn begin_small_parse_table_map(&mut self);
    fn add_small_parse_table_map_item(&mut self, src_index: usize, trg_index: usize);
    fn end_small_parse_table_map(&mut self);

    // Define ts_parse_actions
    fn begin_parse_actions(&mut self);
    fn begin_parse_actions_entry(&mut self, index: usize, count: usize, reusable: bool);
    fn add_parse_actions_action(&mut self, action: &ParseAction, symbol_ids: &HashMap<Symbol, String>);
    fn end_parse_actions_entry(&mut self);
    fn end_parse_actions(&mut self);

    // Define ts_lex et.al.
    fn begin_lex_function(&mut self, name: &str);
    fn begin_lex_function_case(&mut self, index: usize) {
        add_line!(self, "case {index}:");
        indent!(self);
    }
    fn add_lex_function_case_accept_token(&mut self, symbol_id: &String) {
        add_line!(self, "ACCEPT_TOKEN({symbol_id});");
    }
    fn add_lex_function_case_advance_eof(&mut self, state: usize);
    fn add_lex_function_case_advance_map(&mut self, transitions: &[(CharacterSet, AdvanceAction)]);
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
        for _ in 0..self.buffer_ref().indent_level + 2 {
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
                        add!(self, "lookahead == 0"); // '0' unnecessary?
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
    fn end_lex_function_case(&mut self);
    fn end_lex_function(&mut self);

    fn begin_character_set(&mut self, name: &str);
    fn add_character_set_item(&mut self, index: usize, range: RangeInclusive<char>);
    fn end_character_set(&mut self, count: usize);

    /// Complete the language generation process.
    fn end_language(&mut self, context: &dyn RenderContext);

    /// Both macros and default rendering implementations require mutable access to a RenderBuffer.
    fn buffer_ref(&mut self) -> &mut RenderBuffer;
}
