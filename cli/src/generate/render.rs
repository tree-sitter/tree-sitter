use std::{
    cmp,
    collections::{HashMap, HashSet},
};

use super::{
    build_tables::Tables,
    grammars::{ExternalToken, LexicalGrammar, SyntaxGrammar, VariableType},
    nfa::CharacterSet,
    render_target_c::RenderTargetC,
    rules::{Alias, AliasMap, Symbol, SymbolType},
    tables::{
        FieldLocation, LexTable, ParseTable, ParseTableEntry,
    },
};

const SMALL_STATE_THRESHOLD: usize = 64;
const ABI_VERSION_MIN: usize = 13;
const ABI_VERSION_MAX: usize = tree_sitter::LANGUAGE_VERSION;
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
    pub fn generate(&self, target: &mut RenderTargetC) {
        target.add_includes();
        target.add_pragmas(self);
        target.add_stats(self);
        target.add_symbol_enum(self);
        target.add_symbol_names_list(self);
        target.add_unique_symbol_map(self);
        target.add_symbol_metadata_list(self);

        if !self.field_names.is_empty() {
            target.add_field_name_enum(self);
            target.add_field_name_names_list(self);
            target.add_field_sequences(self);
        }

        if !self.parse_table.production_infos.is_empty() {
            target.add_alias_sequences(self);
        }

        target.add_non_terminal_alias_map(self);

        if self.abi_version >= ABI_VERSION_WITH_PRIMARY_STATES {
            target.add_primary_state_id_list(self);
        }

        // The required large character sets are determined through
        // generation of the lex functions. Isolate the text of the
        // lex functions so that it can be placed after the text of
        // the larget character sets.
        let prefix_text = target.buffer.get_text();
        let mut used_large_set_indices : HashSet<usize> = HashSet::new();
        target.add_lex_function(self, "ts_lex", &self.main_lex_table, &mut used_large_set_indices);
        if self.keyword_capture_token.is_some() {
            target.add_lex_function(self, "ts_lex_keywords", &self.keyword_lex_table, &mut used_large_set_indices);
        }
        let lex_functions_text = target.buffer.swap_text(prefix_text);

        // Once the lex functions are generated, and we've determined which large
        // character sets are actually used, we can generate the large character set
        // constants and append the lex functions text.
        for ix in used_large_set_indices.into_iter() {
            target.add_character_set(&self.large_character_set_names[ix], &self.large_character_sets[ix].1);
        }
        target.buffer.append(lex_functions_text);

        target.add_lex_modes_list(self);
        target.add_parse_table(self);

        if !self.syntax_grammar.external_tokens.is_empty() {
            target.add_external_token_enum(self);
            target.add_external_scanner_symbol_map(self);
            target.add_external_scanner_states_list(self);
        }

        target.add_parser_export(self);
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

    pub fn get_field_map_id(
        &self,
        flat_field_map: Vec<(String, FieldLocation)>,
        flat_field_maps: &mut Vec<(usize, Vec<(String, FieldLocation)>)>,
        next_flat_field_map_index: &mut usize,
    ) -> usize {
        if let Some((index, _)) = flat_field_maps.iter().find(|(_, e)| *e == *flat_field_map) {
            return *index;
        }

        let result = *next_flat_field_map_index;
        *next_flat_field_map_index += flat_field_map.len();
        flat_field_maps.push((result, flat_field_map));
        result
    }

    pub fn external_token_id(&self, token: &ExternalToken) -> String {
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
