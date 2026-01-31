use std::{
    collections::{BTreeMap, HashMap, HashSet},
    fmt::Write,
};

use crate::{
    build_tables::{build_tables, Tables},
    grammars::{InputGrammar, LexicalGrammar, SyntaxGrammar, VariableType},
    node_types::{self, ChildType, VariableInfo},
    prepare_grammar::prepare_grammar,
    rules::{Alias, AliasMap, Symbol, SymbolType},
    tables::ParseTable,
    GenerateError, OptLevel,
};

pub struct GrammarIntrospection {
    pub syntax_grammar: SyntaxGrammar,
    pub lexical_grammar: LexicalGrammar,
    pub simple_aliases: BTreeMap<Symbol, Alias>,
    pub variable_info: Vec<VariableInfo>,
    pub supertype_symbol_map: BTreeMap<Symbol, Vec<ChildType>>,
    pub tables: Tables,
    pub symbol_ids: HashMap<Symbol, (String, u16)>,
    pub alias_ids: HashMap<Alias, String>,
    pub unique_aliases: Vec<(Alias, u16)>,
}

pub fn introspect_grammar(
    input_grammar: &InputGrammar,
    report_symbol_name: Option<&str>,
    optimizations: OptLevel,
) -> Result<GrammarIntrospection, GenerateError> {
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(input_grammar)?;
    let variable_info =
        node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases)?;

    let supertype_symbol_map =
        node_types::get_supertype_symbol_map(&syntax_grammar, &simple_aliases, &variable_info);
    let tables = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
        &inlines,
        report_symbol_name,
        optimizations,
    )?;

    // Generate symbol IDs (both string and numeric) before rendering C code
    let (symbol_ids, alias_ids, unique_aliases) = generate_symbol_ids(
        &tables.parse_table,
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
    );

    Ok(GrammarIntrospection {
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        variable_info,
        supertype_symbol_map,
        tables,
        symbol_ids,
        alias_ids,
        unique_aliases,
    })
}

/// Generates symbol IDs and alias IDs for the given parse table and grammars.
///
/// This function must be called before `render_c_code` to generate the symbol mappings
/// that will be used in the generated C code.
///
/// # Arguments
///
/// * `parse_table` - The generated parse table for the language
/// * `syntax_grammar` - The syntax grammar extracted from the language's grammar
/// * `lexical_grammar` - The lexical grammar extracted from the language's grammar
/// * `default_aliases` - A map describing the global rename rules that should apply
///
/// # Returns
///
/// A tuple containing:
/// * `symbol_ids` - HashMap mapping each Symbol to (C identifier string, numeric ID)
/// * `alias_ids` - HashMap mapping each Alias to its C identifier string
/// * `unique_aliases` - Sorted vector of unique aliases
pub fn generate_symbol_ids(
    parse_table: &ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    default_aliases: &AliasMap,
) -> (
    HashMap<Symbol, (String, u16)>,
    HashMap<Alias, String>,
    Vec<(Alias, u16)>,
) {
    let mut symbol_ids = HashMap::new();
    let mut alias_ids = HashMap::new();
    let mut unique_aliases = Vec::new();
    let mut symbol_identifiers = HashSet::new();

    // Generate symbol IDs with numeric IDs
    // Symbol::end() gets 0, then other symbols get 1, 2, 3...
    let mut numeric_id = 0u16;
    for &symbol in &parse_table.symbols {
        assign_symbol_id(
            symbol,
            syntax_grammar,
            lexical_grammar,
            &mut symbol_ids,
            &mut symbol_identifiers,
            numeric_id,
        );
        numeric_id += 1;
    }

    symbol_ids.insert(
        Symbol::end_of_nonterminal_extra(),
        symbol_ids[&Symbol::end()].clone(),
    );

    // Build symbol map to find canonical symbols for aliases
    let mut symbol_map = HashMap::new();
    for symbol in &parse_table.symbols {
        let mut mapping = symbol;

        if let Some(alias) = default_aliases.get(symbol) {
            let kind = alias.kind();
            for other_symbol in &parse_table.symbols {
                if let Some(other_alias) = default_aliases.get(other_symbol) {
                    if other_symbol < mapping && other_alias == alias {
                        mapping = other_symbol;
                    }
                } else {
                    let (other_name, other_kind) =
                        metadata_for_symbol(*other_symbol, syntax_grammar, lexical_grammar);
                    if (other_name, other_kind) == (alias.value.as_str(), kind) {
                        mapping = other_symbol;
                        break;
                    }
                }
            }
        } else if symbol.is_terminal() {
            let metadata = metadata_for_symbol(*symbol, syntax_grammar, lexical_grammar);
            for other_symbol in &parse_table.symbols {
                let other_metadata =
                    metadata_for_symbol(*other_symbol, syntax_grammar, lexical_grammar);
                if other_metadata == metadata {
                    if let Some(mapped) = symbol_map.get(other_symbol) {
                        if mapped == symbol {
                            break;
                        }
                    }
                    mapping = other_symbol;
                    break;
                }
            }
        }

        symbol_map.insert(*symbol, *mapping);
    }

    // Generate alias IDs
    for production_info in &parse_table.production_infos {
        for alias in &production_info.alias_sequence {
            if let Some(alias) = &alias {
                // Find symbols that match this alias
                let matching_symbols: Vec<Symbol> = parse_table
                    .symbols
                    .iter()
                    .copied()
                    .filter(|symbol| {
                        default_aliases.get(symbol).map_or_else(
                            || {
                                let (name, kind) =
                                    metadata_for_symbol(*symbol, syntax_grammar, lexical_grammar);
                                name == alias.value && kind == alias.kind()
                            },
                            |default_alias| default_alias == alias,
                        )
                    })
                    .collect();

                // Some aliases match an existing symbol in the grammar.
                let alias_id = if let Some(existing_symbol) = matching_symbols.first() {
                    symbol_ids[&symbol_map[existing_symbol]].0.clone()
                }
                // Other aliases don't match any existing symbol, and need their own identifiers.
                else {
                    if let Err(i) = unique_aliases.binary_search(alias) {
                        unique_aliases.insert(i, alias.clone());
                    }

                    if alias.is_named {
                        format!("alias_sym_{}", sanitize_identifier(&alias.value))
                    } else {
                        format!("anon_alias_sym_{}", sanitize_identifier(&alias.value))
                    }
                };

                alias_ids.entry(alias.clone()).or_insert(alias_id);
            }
        }
    }

    (
        symbol_ids,
        alias_ids,
        unique_aliases
            .into_iter()
            .map(|alias| {
                let id = numeric_id;
                numeric_id += 1;
                (alias, id)
            })
            .collect(),
    )
}

/// Helper function to sanitize identifiers for C code generation.
pub fn sanitize_identifier(name: &str) -> String {
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
                        write!(result, "u{:04x}", c as u32).unwrap();
                        break 'special_chars;
                    }
                    '\u{10000}'..='\u{10FFFF}' => {
                        write!(result, "U{:08x}", c as u32).unwrap();
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

/// Helper function to get metadata for a symbol.
pub fn metadata_for_symbol<'a>(
    symbol: Symbol,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
) -> (&'a str, VariableType) {
    match symbol.kind {
        SymbolType::End | SymbolType::EndOfNonTerminalExtra => ("end", VariableType::Hidden),
        SymbolType::NonTerminal => {
            let variable = &syntax_grammar.variables[symbol.index];
            (&variable.name as &str, variable.kind)
        }
        SymbolType::Terminal => {
            let variable = &lexical_grammar.variables[symbol.index];
            (&variable.name as &str, variable.kind)
        }
        SymbolType::External => {
            let token = &syntax_grammar.external_tokens[symbol.index];
            (&token.name as &str, token.kind)
        }
    }
}

/// Helper function to assign a symbol ID.
fn assign_symbol_id(
    symbol: Symbol,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    symbol_ids: &mut HashMap<Symbol, (String, u16)>,
    used_identifiers: &mut HashSet<String>,
    numeric_id: u16,
) {
    let mut id;
    if symbol == Symbol::end() {
        id = "ts_builtin_sym_end".to_string();
    } else {
        let (name, kind) = metadata_for_symbol(symbol, syntax_grammar, lexical_grammar);
        id = match kind {
            VariableType::Auxiliary => format!("aux_sym_{}", sanitize_identifier(name)),
            VariableType::Anonymous => format!("anon_sym_{}", sanitize_identifier(name)),
            VariableType::Hidden | VariableType::Named => {
                format!("sym_{}", sanitize_identifier(name))
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
    symbol_ids.insert(symbol, (id, numeric_id));
}
