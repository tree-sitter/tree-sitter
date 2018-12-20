use crate::grammars::{LexicalGrammar, SyntaxGrammar, VariableType};
use crate::rules::{Alias, AliasMap, Symbol, SymbolType};
use crate::tables::{LexTable, ParseTable, ParseTableEntry};
use std::collections::{HashMap, HashSet};
use std::fmt::Write;

macro_rules! add_line {
    ($this: tt, $($arg: tt)*) => {
        for _ in 0..$this.indent_level {
            write!(&mut $this.buffer, "  ").unwrap();
        }
        $this.buffer.write_fmt(format_args!($($arg)*)).unwrap();
        $this.buffer += "\n";
    }
}

struct Generator {
    buffer: String,
    indent_level: usize,

    language_name: String,
    parse_table: ParseTable,
    main_lex_table: LexTable,
    keyword_lex_table: LexTable,
    keyword_capture_token: Option<Symbol>,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    simple_aliases: AliasMap,
    symbol_ids: HashMap<Symbol, String>,
    parse_table_entries: Vec<(usize, ParseTableEntry)>,
    next_parse_action_list_index: usize,
    unique_aliases: HashSet<Alias>,
}

impl Generator {
    fn generate(mut self) -> String {
        self.add_includes();
        self.add_pragmas();
        self.add_stats();
        self.add_symbol_enum();
        self.add_symbol_names_list();
        self.buffer
    }

    fn add_includes(&mut self) {
        add_line!(self, "#include <tree_sitter/parser.h>");
        add_line!(self, "");
    }

    fn add_pragmas(&mut self) {
        add_line!(self, "#if defined(__GNUC__) || defined(__clang__)");
        add_line!(self, "#pragma GCC diagnostic push");
        add_line!(self, "#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"");
        add_line!(self, "#endif");
        add_line!(self, "");

        // Compiling large lexer functions can be very slow, especially when
        // using Visual Studio on Windows. Disabling optimizations is not
        // ideal, but only a very small fraction of overall parse time is
        // spent lexing, so the performance impact of this is pretty small.
        if self.main_lex_table.states.len() > 500 {
            add_line!(self, "#ifdef _MSC_VER");
            add_line!(self, "#pragma optimize(\"\", off)");
            add_line!(self, "#endif");
            add_line!(self, "");
        }
    }

    fn add_stats(&mut self) {
        let mut token_count = 0;

        for symbol in &self.parse_table.symbols {
            if symbol.is_terminal() {
                token_count += 1;
            } else if symbol.is_external() {
                let external_token = &self.syntax_grammar.external_tokens[symbol.index];
                if external_token.corresponding_internal_token.is_none() {
                    token_count += 1;
                }
            }
        }

        for alias_sequence in &self.parse_table.alias_sequences {
            for entry in alias_sequence {
                if let Some(alias) = entry {
                    self.unique_aliases.insert(alias.clone());
                }
            }
        }

        let mut symbol_id_values = HashSet::new();
        for i in 0..self.parse_table.symbols.len() {
            self.assign_symbol_id(self.parse_table.symbols[i], &mut symbol_id_values);
        }

        add_line!(self, "#define LANGUAGE_VERSION {}", 6);
        add_line!(self, "#define STATE_COUNT {}", self.parse_table.states.len());
        add_line!(self, "#define SYMBOL_COUNT {}", self.parse_table.symbols.len());
        add_line!(self, "#define ALIAS_COUNT {}", self.unique_aliases.len());
        add_line!(self, "#define TOKEN_COUNT {}", token_count);
        add_line!(self, "#define EXTERNAL_TOKEN_COUNT {}", self.syntax_grammar.external_tokens.len());
        // add_line!(self, "#define MAX_ALIAS_SEQUENCE_LENGTH {}\n", self.parse_table.max_alias_sequence_length);
        add_line!(self, "");
    }

    fn add_symbol_enum(&mut self) {
        add_line!(self, "enum {{");
        self.indent();
        for i in 0..self.parse_table.symbols.len() {
            let symbol = self.parse_table.symbols[i];
            if symbol != Symbol::end() {
                add_line!(self, "{} = {}", self.symbol_ids[&symbol], i);
            }
        }
        self.dedent();
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn add_symbol_names_list(&mut self) {
        add_line!(self, "static const char *ts_symbol_names[] = {{");
        self.indent();
        self.dedent();
        add_line!(self, "}};");
        add_line!(self, "");
    }

    fn assign_symbol_id(&mut self, symbol: Symbol, used_ids: &mut HashSet<String>) {
        let mut id;
        if symbol == Symbol::end() {
            id = "ts_builtin_sym_end".to_string();
        } else {
            let (name, kind) = self.metadata_for_symbol(symbol);
            id = match kind {
                VariableType::Auxiliary => format!("aux_sym_{}", self.sanitize_name(name)),
                VariableType::Anonymous => format!("anon_sym_{}", self.sanitize_name(name)),
                VariableType::Hidden | VariableType::Named => {
                    format!("sym_{}", self.sanitize_name(name))
                }
            };

            let mut suffix_number = 1;
            let mut suffix = String::new();
            while used_ids.contains(&id) {
                id.drain(id.len() - suffix.len()..);
                suffix_number += 1;
                suffix = suffix_number.to_string();
                id += &suffix;
            }
        }

        used_ids.insert(id.clone());
        self.symbol_ids.insert(symbol, id);
    }

    fn metadata_for_symbol(&self, symbol: Symbol) -> (&str, VariableType) {
        match symbol.kind {
            SymbolType::End => ("end", VariableType::Auxiliary),
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

    fn sanitize_name(&self, name: &str) -> String {
        name.to_string()
    }

    fn indent(&mut self) {
        self.indent_level += 1;
    }

    fn dedent(&mut self) {
        self.indent_level -= 1;
    }
}

pub(crate) fn render_c_code(
    name: &str,
    parse_table: ParseTable,
    main_lex_table: LexTable,
    keyword_lex_table: LexTable,
    keyword_capture_token: Option<Symbol>,
    syntax_grammar: SyntaxGrammar,
    lexical_grammar: LexicalGrammar,
    simple_aliases: AliasMap,
) -> String {
    Generator {
        buffer: String::new(),
        indent_level: 0,
        language_name: name.to_string(),
        parse_table,
        main_lex_table,
        keyword_lex_table,
        keyword_capture_token,
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        symbol_ids: HashMap::new(),
        parse_table_entries: Vec::new(),
        next_parse_action_list_index: 0,
        unique_aliases: HashSet::new(),
    }
    .generate()
}
