use std::collections::HashMap;
use std::ops::RangeInclusive;
use std::io::Write;

use super::{
    nfa::CharacterSet,
    render_buffer::RenderBuffer,
    render_context::RenderContext,
    render_target::RenderTarget,
    render::ABI_VERSION_WITH_PRIMARY_STATES,
    rules::{Symbol, TokenSet},
    tables::{AdvanceAction, FieldLocation, ParseAction, ParseState},
};


pub struct RenderTargetSwift {
    buffer: RenderBuffer
}

impl RenderTargetSwift {
    pub fn new() -> Self {
        Self {
            buffer: RenderBuffer::new(2),
        }
    }
}

impl RenderTarget for RenderTargetSwift {
    fn begin_language(&mut self, context: &dyn RenderContext) {
        // add_line!(self, "struct TestLang {{");
        indent!(self);

        add_line!(self, "fileprivate static let ts_language_version = {}", context.get_abi_version());
        add_line!(self, "fileprivate static let ts_state_count = {}", context.get_state_count());
        add_line!(self, "fileprivate static let ts_large_state_count = {}", context.get_large_state_count());
        add_line!(self, "fileprivate static let ts_symbol_count = {}", context.get_symbol_count());
        add_line!(self, "fileprivate static let ts_alias_count = {}", context.get_alias_count());
        add_line!(self, "fileprivate static let ts_token_count = {}", context.get_token_count());
        add_line!(self, "fileprivate static let ts_external_token_count = {}", context.get_external_token_count());
        add_line!(self, "fileprivate static let ts_field_count = {}", context.get_field_count());
        add_line!(self, "fileprivate static let ts_max_alias_sequence_length = {}", context.get_max_alias_sequence_length());
        add_line!(self, "fileprivate static let ts_production_id_count = {}", context.get_production_id_count());
        add_line!(self, "");
        add_line!(self, "fileprivate static func ACTIONS(_ i: UInt16) -> UInt16 {{ i }}");
        add_line!(self, "fileprivate static func STATE(_ i: UInt16) -> UInt16 {{ i }}");
        add_line!(self, "");
    }

    fn begin_symbol_enum(&mut self) {
        self.add_symbol_enum_item("ts_builtin_sym_end", 0);
    }
    fn add_symbol_enum_item(&mut self, name: &str, index: usize) {
        add_line!(self, "fileprivate static let {name} : TSSymbol = {index}");
    }
    fn end_symbol_enum(&mut self) {
        add_line!(self, "");
    }

    fn begin_symbol_names_list(&mut self) {
        add_line!(self, "static let symbolNames : [StaticString] = [");
        indent!(self);
    }
    fn add_symbol_names_list_item(&mut self, _name: &str, text: &str) {
        add_line!(self, "\"{text}\",");
    }
    fn end_symbol_names_list(&mut self) {
        dedent!(self);
        add_line!(self, "]");
        add_line!(self, "fileprivate static let ts_symbol_names = UnsafeBufferPointer.arrayOfAsciiCSrings(symbolNames)");
        add_line!(self, "");
    }

    fn begin_symbol_map(&mut self) {
        add_line!(self, "fileprivate static let ts_symbol_map = UnsafeBufferPointer<TSSymbol>.initialized(with: [");
        indent!(self);
    }
    fn add_symbol_map_item(&mut self, _src_name: &str, trg_name: &str) {
        add_line!(self, "{trg_name},");
    }
    fn end_symbol_map(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_symbol_metadata(&mut self) {
        add_line!(self, "fileprivate static let ts_symbol_metadata = UnsafeBufferPointer<TSSymbolMetadata>.initialized(with: [");
        indent!(self);
    }
    fn add_symbol_metadata_item(&mut self, name: &str, visible: bool, named: bool, supertype: bool) {
        add_whitespace!(self);
        add!(self, ".init(visible: {}, named: {}", visible.to_string(), named.to_string());
        if supertype {
            add!(self, ", supertype: true");
        }
        add!(self, "), // {name}");
        add_newline!(self);
    }
    fn end_symbol_metadata(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_field_enum(&mut self) {
    }
    fn add_field_enum_item(&mut self, name: &str, index: usize) {
        add_line!(self, "fileprivate static let {name} : TSFieldId = {index}");
    }
    fn end_field_enum(&mut self) {
        add_line!(self, "");
    }

    fn begin_field_names(&mut self) {
        add_line!(self, "static let fieldNames : [StaticString?] = [");
        indent!(self);
        add_line!(self, "nil,");
    }
    fn add_field_name_item(&mut self, _name: &str, text: &str) {
        add_line!(self, "\"{text}\",");
    }
    fn end_field_names(&mut self) {
        dedent!(self);
        add_line!(self, "]");
        add_line!(self, "fileprivate static let ts_field_names = UnsafeBufferPointer<UnsafePointer<CChar>?>.arrayOfAsciiCSrings(fieldNames)");
        add_line!(self, "");
    }
    
    fn begin_field_map_slices(&mut self) {
        add_line!(self, "fileprivate static let ts_field_map_slices = UnsafeBufferPointer<TSFieldMapSlice>.initialized(with: [");
        indent!(self);
        add_line!(self, ".init(),");
    }
    fn add_field_map_slices_item(&mut self, _production_id: usize, row_id: usize, length: usize) {
        add_line!(self, ".init(index: {row_id}, length: {length}),");
    }
    fn end_field_map_slices(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_field_map_entries(&mut self) {
        add_line!(self, "fileprivate static let ts_field_map_entries = UnsafeBufferPointer<TSFieldMapEntry>.initialized(with: [");
        indent!(self);
    }
    fn add_field_map_entries_item(&mut self, _row_index: usize, field_pairs: Vec<(String, FieldLocation)>) {
        for (field_name, location) in field_pairs {
            add_whitespace!(self);
            add!(self, ".init(field_{}, {}", field_name, location.index); // TODO: get field id from context
            if location.inherited {
                add!(self, ", inherited: true");
            }
            add!(self, "),");
            add_newline!(self);
        }
    }
    fn end_field_map_entries(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_alias_sequences(&mut self) {
        add_line!(self, "fileprivate static let ts_alias_sequences = UnsafeBufferPointer<TSSymbol>.initialized(rowCount: Int(ts_production_id_count), columnCount: Int(ts_max_alias_sequence_length), rowColumnValueTriples: [");
        indent!(self);
    }
    fn add_alias_sequences_item(&mut self, row_index: usize, alias_ids: Vec<Option<&String>>) {
        for (col_index, alias_id) in alias_ids.iter().enumerate() {
            if let Some(alias_id) = alias_id {
                add_line!(self, "({row_index}, {col_index}, {alias_id}),");
            }
        }
    }
    fn end_alias_sequences(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }
    
    fn begin_non_terminal_alias_map(&mut self) {
        add_line!(self, "fileprivate static let ts_non_terminal_alias_map = UnsafeBufferPointer<UInt16>.initialized(with: [");
        indent!(self);
    }
    fn add_non_terminal_alias_map_item(&mut self, symbol_id: &str, count: usize, public_symbol_id: &str, alias_ids: Vec<&String>) {
        add_whitespace!(self);
        add!(self, "{symbol_id}, {count}, {public_symbol_id},");
        for alias_id in alias_ids {
            add!(self, " {alias_id},");
        }
        add_newline!(self);
    }
    fn end_non_terminal_alias_map(&mut self) {
        add_line!(self, "0");
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }
    
    fn begin_primary_state_ids(&mut self) {
        add_line!(self, "fileprivate static let ts_primary_state_ids = UnsafeBufferPointer<TSStateId>.initialized(count: ts_state_count, indexValuePairs: [");
        indent!(self);
    }
    fn add_primary_state_ids_item(&mut self, index: usize, primary_state: usize) {
        add_line!(self, "({index}, {primary_state}),");
    }
    fn end_primary_state_ids(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }
    
    fn begin_lex_modes(&mut self) {
        add_line!(self, "fileprivate static let ts_lex_modes = UnsafeBufferPointer<TSLexMode>.initialized(count: ts_state_count, zero: .zero, indexValuePairs: [");
        indent!(self);
    }
    fn add_lex_modes_item(&mut self, index: usize, state: &ParseState) {
        add_whitespace!(self);
        add!(self, "({index}, ");
        if state.is_end_of_non_terminal_extra() {
            add!(self, ".endOfNonTerminalExtra");
        }
        else {
            add!(self, ".init(lex_state: {}", state.lex_state_id);
            if state.external_lex_state_id > 0 {
                add!(self, ", external_lex_state: {}", state.external_lex_state_id);
            }
            add!(self, ")");
        }
        add!(self, "),");
        add_newline!(self);
    }
    fn end_lex_modes(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_external_token_enum(&mut self) {
    }
    fn add_external_token_enum_item(&mut self, name: &str, index: usize) {
        add_line!(self, "fileprivate static let {name} : TSSymbol = {index}");
    }
    fn end_external_token_enum(&mut self) {
        add_line!(self, "");
    }

    fn begin_external_scanner_symbol_map(&mut self) {
        add_line!(self, "fileprivate static let ts_external_scanner_symbol_map = UnsafeBufferPointer<TSSymbol>.initialized(count: ts_external_token_count, indexValuePairs: [");
        indent!(self);
    }
    fn add_external_scanner_symbol_map_item(&mut self, src_name: &str, trg_name: &str) {
        add_line!(self, "(.{src_name}, .{trg_name}),");
    }
    fn end_external_scanner_symbol_map(&mut self) {
        indent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_external_scanner_states(&mut self, external_lex_state_count: usize) {
        add_line!(self, "fileprivate static let ts_external_scanner_states = UnsafeBufferPointer<Bool>.initialized(rowCount: {external_lex_state_count}, columnCount: ts_external_token_count, rowColumnValueTriples: [");
        indent!(self);
    }
    fn add_external_scanner_states_item(&mut self, context: &dyn RenderContext, index: usize, token_set: &TokenSet) {
        for token in token_set.iter() {
            let token_id = context.get_external_token_id(token.index);
            add_line!(self, "({index}, .{token_id}, true),");
        }
    }
    fn end_external_scanner_states(&mut self) {
       indent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }
    
    fn begin_parse_table(&mut self) {
        add_line!(self, "fileprivate static let ts_parse_table = UnsafeBufferPointer<UInt16>.initialized(rowCount: ts_large_state_count, columnCount: ts_symbol_count, columnValuesByRow: [");
        indent!(self);
    }
    fn begin_parse_table_section(&mut self, index: usize) {
        add_line!(self, "({index}, [");
        indent!(self);
    }
    fn add_parse_table_state_item(&mut self, symbol_id: &String, state: usize) {
        add_line!(self, "({symbol_id}, STATE({state})),");
    }
    fn add_parse_table_actions_item(&mut self, entry_index: usize, symbol_id: &String) {
        add_line!(self, "({symbol_id}, ACTIONS({entry_index})),");
    }
    fn end_parse_table_section(&mut self) {
        dedent!(self);
        add_line!(self, "]),");
    }
    fn end_parse_table(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }
    
    fn begin_small_parse_table(&mut self) {
        add_line!(self, "fileprivate static let ts_small_parse_table = UnsafeBufferPointer<UInt16>.initialized(with: [");
        indent!(self);
    }
    fn begin_small_parse_table_section(&mut self, index: usize, count: usize) {
        add_line!(self, "{count}, // {index}");
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
        add_line!(self, "])");
        add_line!(self, "");
    }
    
    fn begin_small_parse_table_map(&mut self) {
        add_line!(self, "fileprivate static let ts_small_parse_table_map = UnsafeBufferPointer<UInt32>.initialized(with: [");
        indent!(self);
    }
    fn add_small_parse_table_map_item(&mut self, src_index: usize, trg_index: usize) {
        add_line!(self, "{trg_index}, // SMALL_STATE({src_index})");
    }
    fn end_small_parse_table_map(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_parse_actions(&mut self) {
        add_line!(self, "fileprivate static let ts_parse_actions = UnsafeBufferPointer<TSParseActionEntry>.initialized(with: [");
        indent!(self);
    }
    fn begin_parse_actions_entry(&mut self, index: usize, count: usize, reusable: bool) {
        add_whitespace!(self);
        add!(self, "/* [{index}] = */ .entry(count: {count}, reusable: {reusable}),");
    }
    fn add_parse_actions_action(&mut self, action: &ParseAction, symbol_ids: &HashMap<Symbol, String>) {
        add!(self, " ");
        match action {
            ParseAction::Accept => add!(self, ".accept"),
            ParseAction::Recover => add!(self, ".recover"),
            ParseAction::ShiftExtra => add!(self, ".shift(extra: true)"),
            ParseAction::Shift { state, is_repetition } => {
                add!(self, ".shift({state}");
                if *is_repetition {
                    add!(self, ", repeat: true");
                }
                add!(self, ")");
            }
            ParseAction::Reduce {  symbol, child_count, dynamic_precedence, production_id, .. } => {
                add!(self, ".reduce({}, {child_count}", symbol_ids[symbol]);
                if *dynamic_precedence != 0 {
                    add!(self, ", dynamic_precedence: {dynamic_precedence}");
                }
                if *production_id != 0 {
                    add!(self, ", production_id: {production_id}");
                }
                add!(self, ")");
            }
        }
        add!(self, ",");
    }
    fn end_parse_actions_entry(&mut self) {
        add_newline!(self);
    }
    fn end_parse_actions(&mut self) {
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn begin_lex_function(&mut self, name: &str) {
        add_line!(self, "fileprivate static func {name}(_ lexer: UnsafeMutablePointer<TSLexer>?, _ state: TSStateId) -> Bool {{");
        add_line!(self, "  let lexer = UnsafeMutableRawPointer(mutating: lexer!).bindMemory(to: TSLexer.self, capacity: 1)");
        add_line!(self, "  var state = state");
        add_line!(self, "  var result = false");
        add_line!(self, "  var skip = false");
        add_line!(self, "  var eof = false");
        add_line!(self, "  var lookahead : Int32 = 0");
        add_line!(self, "");
        add_line!(self, "  func ACCEPT_TOKEN(_ symbol: TSSymbol) {{");
        add_line!(self, "    result = true");
        add_line!(self, "    lexer.pointee.result_symbol = symbol");
        add_line!(self, "    lexer.pointee.mark_end(lexer)");
        add_line!(self, "  }}");
        add_line!(self, "  func ADVANCE(_ next_state: TSStateId) {{ state = next_state }}");
        add_line!(self, "  func ADVANCE_MAP(_ pairs: [(char: Int32, next_state: TSStateId)]) -> Optional<TSStateId> {{");
        add_line!(self, "    for (char, next_state) in pairs {{");
        add_line!(self, "      if char == lookahead {{");
        add_line!(self, "        return next_state");
        add_line!(self, "      }}");
        add_line!(self, "    }}");
        add_line!(self, "    return nil");
        add_line!(self, "  }}");
        add_line!(self, "  func SKIP(_ next_state: TSStateId) {{ state = next_state; skip = true }}");
        add_line!(self, "");
        add_line!(self, "  while true {{");
        add_line!(self, "    skip = false");
        add_line!(self, "    lookahead = lexer.pointee.lookahead");
        add_line!(self, "    eof = lexer.pointee.eof(lexer)");
        add_line!(self, "    switch state {{");
        indent!(self); indent!(self); indent!(self);
    }
    fn end_lex_function(&mut self) {
        dedent!(self); dedent!(self); dedent!(self);
        add_line!(self, "    default:");
        add_line!(self, "      return false");
        add_line!(self, "    }}");
        add_line!(self, "    // next_state:");
        add_line!(self, "    lexer.pointee.advance(lexer, skip)");
        add_line!(self, "  }}");
        add_line!(self, "}}");
        add_line!(self, "");
    }
    fn add_lex_function_case_advance_eof(&mut self, state: usize) {
        add_line!(self, "if eof {{ ADVANCE({state}); break }}");
    }
    fn add_lex_function_case_advance_map(&mut self, transitions: &[(CharacterSet, AdvanceAction)]) {
        add_line!(self, "if let next = ADVANCE_MAP([");
        indent!(self);
        for (chars, action) in transitions {
            for range in chars.ranges() {
                assert!(*range.start() == *range.end()); // single-character range
                add_line!(self, "({}, {}),", *range.start() as u32, action.state);
            }
        }
        dedent!(self);
        add_line!(self, "]) {{ ADVANCE(next); break }}");
    }
    fn add_lex_function_case_advance_to(&mut self, state: usize, in_main_token: bool) {
        add!(self, "{{ {}({state}); break }}", if in_main_token {"ADVANCE"} else {"SKIP"});
    }
    fn end_lex_function_case(&mut self) {
        add_line!(self, "return result");
        dedent!(self);
    }
    fn add_character(&mut self, c: char) {
        add!(self, "{}", c as u32);
    }
    fn add_large_set_contains_check(&mut self, large_set_name: &String, range_count: usize) {
        add!(self, "set_contains({large_set_name}.baseAddress, {range_count}, lookahead)");
    }

    fn begin_character_set(&mut self, name: &str) {
        add_line!(self, "fileprivate static let {name} = UnsafeBufferPointer<TSCharacterRange>.initialized(with: [");
        indent!(self);
    }
    fn add_character_set_item(&mut self, index: usize, range: RangeInclusive<char>) {
        if index > 0 && index % 4 == 0 {
            add_newline!(self);
            add_whitespace!(self);
        }
        else {
            add!(self, " ");
        }
        add!(self, ".init(start: ");
        self.add_character(*range.start());
        add!(self, ", end: ");
        self.add_character(*range.end());
        add!(self, "),");
    }
    fn end_character_set(&mut self, count: usize) {
        if count % 4 != 0 {
            add_newline!(self);
        }
        dedent!(self);
        add_line!(self, "])");
        add_line!(self, "");
    }

    fn end_language(&mut self, context: &dyn RenderContext) {
        add_line!(self, "static let language = UnsafePointer<TSLanguage>.initialized {{ lang in");
        add_line!(self, "    lang.version = {}", context.get_abi_version());
        add_line!(self, "    lang.symbol_count = {}", context.get_symbol_count());
        add_line!(self, "    lang.alias_count = {}", context.get_alias_count());
        add_line!(self, "    lang.token_count = {}", context.get_token_count());
        add_line!(self, "    lang.external_token_count = {}", context.get_external_token_count());
        add_line!(self, "    lang.state_count = {}", context.get_state_count());
        add_line!(self, "    lang.large_state_count = {}", context.get_large_state_count());
        add_line!(self, "    lang.production_id_count = {}", context.get_production_id_count());
        add_line!(self, "    lang.field_count = {}", context.get_field_count());
        add_line!(self, "    lang.max_alias_sequence_length = {}", context.get_max_alias_sequence_length());
        add_line!(self, "    lang.parse_table = ts_parse_table.baseAddress");
        if context.get_large_state_count() < context.get_state_count() {
            add_line!(self, "    lang.small_parse_table = ts_small_parse_table.baseAddress");
            add_line!(self, "    lang.small_parse_table_map = ts_small_parse_table_map.baseAddress");
        }
        add_line!(self, "    lang.parse_actions = ts_parse_actions.baseAddress");
        add_line!(self, "    lang.symbol_names = ts_symbol_names.baseAddress");
        if context.get_field_count() > 0 {
            add_line!(self, "    lang.field_names = ts_field_names.baseAddress");
            add_line!(self, "    lang.field_map_slices = ts_field_map_slices.baseAddress");
            add_line!(self, "    lang.field_map_entries = ts_field_map_entries.baseAddress");
        }
        add_line!(self, "    lang.symbol_metadata = ts_symbol_metadata.baseAddress");
        add_line!(self, "    lang.public_symbol_map = ts_symbol_map.baseAddress");
        add_line!(self, "    lang.alias_map = ts_non_terminal_alias_map.baseAddress");
        if context.get_production_id_count() > 0 {
            add_line!(self, "    lang.alias_sequences = ts_alias_sequences.baseAddress");
        }
        add_line!(self, "    lang.lex_modes = ts_lex_modes.baseAddress");
        add_line!(self, "    lang.lex_fn = {{ts_lex($0,$1)}}");
        if let Some(keyword_capture_token_id) = &context.get_keyword_capture_token_id() {
            add_line!(self, "    lang.keyword_lex_fn = {{ts_lex_keywords($0,$1)}}");
            add_line!(self, "    lang.keyword_capture_token = {keyword_capture_token_id}");
        }
        if context.get_external_token_count() > 0 {
            // TODO: ...
        }
        if context.get_abi_version() >= ABI_VERSION_WITH_PRIMARY_STATES {
            add_line!(self, "    lang.primary_state_ids = ts_primary_state_ids.baseAddress");
        }
        add_line!(self, "}}");

        dedent!(self);
        // add_line!(self, "}}");
    }

    fn buffer_ref(&mut self) -> &mut RenderBuffer {
        &mut self.buffer
    }
}
