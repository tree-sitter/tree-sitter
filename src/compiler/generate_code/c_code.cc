#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "compiler/generate_code/c_code.h"
#include "compiler/lex_table.h"
#include "compiler/parse_table.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"
#include "compiler/util/string_helpers.h"
#include "tree_sitter/runtime.h"

namespace tree_sitter {
namespace generate_code {

using std::function;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using util::escape_char;
using rules::Symbol;

static const map<char, string> REPLACEMENTS({
  { '~', "TILDE" },
  { '`', "BQUOTE" },
  { '!', "BANG" },
  { '@', "AT" },
  { '#', "POUND" },
  { '$', "DOLLAR" },
  { '%', "PERCENT" },
  { '^', "CARET" },
  { '&', "AMP" },
  { '*', "STAR" },
  { '(', "LPAREN" },
  { ')', "RPAREN" },
  { '-', "DASH" },
  { '+', "PLUS" },
  { '=', "EQ" },
  { '{', "LBRACE" },
  { '}', "RBRACE" },
  { '[', "LBRACK" },
  { ']', "RBRACK" },
  { '\\', "BSLASH" },
  { '|', "PIPE" },
  { ':', "COLON" },
  { ';', "SEMI" },
  { '"', "DQUOTE" },
  { '\'', "SQUOTE" },
  { '<', "LT" },
  { '>', "GT" },
  { ',', "COMMA" },
  { '.', "DOT" },
  { '?', "QMARK" },
  { '/', "SLASH" },
  { '\n', "LF" },
  { '\r', "CR" },
  { '\t', "TAB" },
});

class CCodeGenerator {
  string buffer;
  size_t indent_level;

  const string name;
  const ParseTable parse_table;
  const LexTable lex_table;
  const SyntaxGrammar syntax_grammar;
  const LexicalGrammar lexical_grammar;
  map<string, string> sanitized_names;
  vector<pair<size_t, ParseTableEntry>> parse_table_entries;
  vector<set<Symbol::Index>> external_scanner_states;
  size_t next_parse_action_list_index;

 public:
  CCodeGenerator(string name, const ParseTable &parse_table,
                 const LexTable &lex_table, const SyntaxGrammar &syntax_grammar,
                 const LexicalGrammar &lexical_grammar)
      : indent_level(0),
        name(name),
        parse_table(parse_table),
        lex_table(lex_table),
        syntax_grammar(syntax_grammar),
        lexical_grammar(lexical_grammar),
        next_parse_action_list_index(0) {}

  string code() {
    buffer = "";

    add_includes();
    add_warning_pragma();
    add_stats();
    add_symbol_enum();
    add_symbol_names_list();
    add_symbol_metadata_list();
    add_lex_function();
    add_lex_modes_list();

    if (!syntax_grammar.external_tokens.empty()) {
      add_external_token_enum();
      add_external_scanner_symbol_map();
      add_external_scanner_states_list();
    }

    add_parse_table();
    add_parser_export();

    return buffer;
  }

 private:
  void add_includes() {
    add("#include <tree_sitter/parser.h>");
    line();
  }

  void add_warning_pragma() {
    line("#pragma GCC diagnostic push");
    line("#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"");
    line();
  }

  void add_stats() {
    size_t token_count = 0;
    for (const auto &entry : parse_table.symbols) {
      const Symbol &symbol = entry.first;
      if (symbol.is_terminal()) {
        token_count++;
      } else if (symbol.is_external()) {
        const ExternalToken &external_token = syntax_grammar.external_tokens[symbol.index];
        if (external_token.corresponding_internal_token == rules::NONE()) {
          token_count++;
        }
      }
    }

    line("#define LANGUAGE_VERSION " + to_string(TREE_SITTER_LANGUAGE_VERSION));
    line("#define STATE_COUNT " + to_string(parse_table.states.size()));
    line("#define SYMBOL_COUNT " + to_string(parse_table.symbols.size()));
    line("#define TOKEN_COUNT " + to_string(token_count));
    line("#define EXTERNAL_TOKEN_COUNT " + to_string(syntax_grammar.external_tokens.size()));
    line();
  }

  void add_symbol_enum() {
    line("enum {");
    indent([&]() {
      size_t i = 1;
      for (const auto &entry : parse_table.symbols) {
        const Symbol &symbol = entry.first;
        if (!symbol.is_built_in()) {
          line(symbol_id(symbol) + " = " + to_string(i) + ",");
          i++;
        }
      }
    });
    line("};");
    line();
  }

  void add_symbol_names_list() {
    line("static const char *ts_symbol_names[] = {");
    indent([&]() {
      for (const auto &entry : parse_table.symbols)
        line("[" + symbol_id(entry.first) + "] = \"" +
             sanitize_name_for_string(symbol_name(entry.first)) + "\",");
    });
    line("};");
    line();
  }

  void add_symbol_metadata_list() {
    line("static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {");
    indent([&]() {
      for (const auto &entry : parse_table.symbols) {
        const Symbol &symbol = entry.first;
        line("[" + symbol_id(symbol) + "] = {");
        indent([&]() {
          switch (symbol_type(symbol)) {
            case VariableTypeNamed:
              line(".visible = true,");
              line(".named = true,");
              break;
            case VariableTypeAnonymous:
              line(".visible = true,");
              line(".named = false,");
              break;
            case VariableTypeHidden:
              line(".visible = false,");
              line(".named = true,");
              break;
            case VariableTypeAuxiliary:
              line(".visible = false,");
              line(".named = false,");
              break;
          }

          line(".structural = " + _boolean(entry.second.structural) + ",");
          line(".extra = " + _boolean(entry.second.extra) + ",");
        });

        line("},");
      }
    });
    line("};");
    line();
  }

  void add_lex_function() {
    line("static bool ts_lex(TSLexer *lexer, TSStateId state) {");
    indent([&]() {
      line("START_LEXER();");
      _switch("state", [&]() {
        size_t i = 0;
        for (const LexState &state : lex_table.states) {
          _case(to_string(i++), [&]() { add_lex_state(state); });
        }
        _default([&]() { line("return false;"); });
      });
    });
    line("}");
    line();
  }

  void add_lex_modes_list() {
    add_external_scanner_state({});

    map<Symbol::Index, Symbol::Index> external_tokens_by_corresponding_internal_token;
    for (size_t i = 0, n = lexical_grammar.variables.size(); i < n; i++) {
      for (size_t j = 0; j < syntax_grammar.external_tokens.size(); j++) {
        const ExternalToken &external_token = syntax_grammar.external_tokens[j];
        if (external_token.corresponding_internal_token.index == Symbol::Index(i)) {
          external_tokens_by_corresponding_internal_token.insert({i, j});
          break;
        }
      }
    }

    line("static TSLexMode ts_lex_modes[STATE_COUNT] = {");
    indent([&]() {
      size_t state_id = 0;

      for (const auto &state : parse_table.states) {
        line("[" + to_string(state_id++) + "] = {.lex_state = ");
        add(to_string(state.lex_state_id));

        bool needs_external_scanner = false;
        set<Symbol::Index> external_token_indices;
        for (const auto &pair : state.terminal_entries) {
          Symbol symbol = pair.first;
          if (symbol.is_external()) {
            needs_external_scanner = true;
            external_token_indices.insert(symbol.index);
          } else if (symbol.is_terminal()) {
            auto corresponding_external_token =
              external_tokens_by_corresponding_internal_token.find(symbol.index);
            if (corresponding_external_token != external_tokens_by_corresponding_internal_token.end()) {
              external_token_indices.insert(corresponding_external_token->second);
            }
          }
        }

        if (needs_external_scanner) {
          add(", .external_lex_state = " + add_external_scanner_state(external_token_indices));
        }

        add("},");
      }
    });
    line("};");
    line();
  }

  string add_external_scanner_state(set<Symbol::Index> external_token_ids) {
    for (size_t i = 0, n = external_scanner_states.size(); i < n; i++)
      if (external_scanner_states[i] == external_token_ids)
        return to_string(i);
    external_scanner_states.push_back(external_token_ids);
    return to_string(external_scanner_states.size() - 1);
  }

  void add_external_token_enum() {
    line("enum {");
    indent([&]() {
      for (size_t i = 0; i < syntax_grammar.external_tokens.size(); i++)
        line(external_token_id(i) + ",");
    });
    line("};");
    line();
  }

  void add_external_scanner_symbol_map() {
    line("static TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {");
    indent([&]() {
      for (size_t i = 0; i < syntax_grammar.external_tokens.size(); i++) {
        line("[" + external_token_id(i) + "] = " + symbol_id(Symbol::external(i)) + ",");
      }
    });
    line("};");
    line();
  }

  void add_external_scanner_states_list() {
    line("static bool ts_external_scanner_states[");
    add(to_string(external_scanner_states.size()));
    add("][EXTERNAL_TOKEN_COUNT] = {");
    indent([&]() {
      size_t i = 0;
      for (const auto &valid_external_lookaheads : external_scanner_states) {
        if (!valid_external_lookaheads.empty()) {
          line("[" + to_string(i) + "] = {");
          indent([&]() {
            for (Symbol::Index id : valid_external_lookaheads) {
              line("[" + external_token_id(id) + "] = true,");
            }
          });
          line("},");
        }
        i++;
      }
    });
    line("};");
    line();
  }

  void add_parse_table() {
    add_parse_action_list_id(ParseTableEntry{ {}, false, false });

    size_t state_id = 0;
    line("static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {");

    indent([&]() {
      for (const auto &state : parse_table.states) {
        line("[" + to_string(state_id++) + "] = {");
        indent([&]() {
          for (const auto &entry : state.nonterminal_entries) {
            line("[" + symbol_id(Symbol::non_terminal(entry.first)) + "] = STATE(");
            add(to_string(entry.second));
            add("),");
          }
          for (const auto &entry : state.terminal_entries) {
            line("[" + symbol_id(entry.first) + "] = ACTIONS(");
            add(to_string(add_parse_action_list_id(entry.second)));
            add("),");
          }
        });
        line("},");
      }
    });

    line("};");
    line();
    add_parse_action_list();
    line();
  }

  void add_parser_export() {
    string language_function_name = "tree_sitter_" + name;
    string external_scanner_name = language_function_name + "_external_scanner";

    if (!syntax_grammar.external_tokens.empty()) {
      line("void *" + external_scanner_name + "_create();");
      line("void " + external_scanner_name + "_destroy();");
      line("void " + external_scanner_name + "_reset(void *);");
      line("bool " + external_scanner_name + "_scan(void *, TSLexer *, const bool *);");
      line("bool " + external_scanner_name + "_serialize(void *, TSExternalTokenState);");
      line("void " + external_scanner_name + "_deserialize(void *, const TSExternalTokenState);");
      line();
    }

    line("const TSLanguage *" + language_function_name + "() {");
    indent([&]() {
      line("GET_LANGUAGE(");
      if (syntax_grammar.external_tokens.empty()) {
        add(");");
      } else {
        indent([&]() {
          line("(const bool *)ts_external_scanner_states,");
          line("ts_external_scanner_symbol_map,");
          line(external_scanner_name + "_create,");
          line(external_scanner_name + "_destroy,");
          line(external_scanner_name + "_reset,");
          line(external_scanner_name + "_scan,");
          line(external_scanner_name + "_serialize,");
          line(external_scanner_name + "_deserialize,");
        });
        line(");");
      }
    });
    line("}");
    line();
  }

  void add_lex_state(const LexState &lex_state) {
    if (lex_state.accept_action.is_present()) {
      add_accept_token_action(lex_state.accept_action);
    }

    for (const auto &pair : lex_state.advance_actions) {
      if (!pair.first.is_empty()) {
        _if([&]() { add_character_set_condition(pair.first); },
            [&]() { add_advance_action(pair.second); });
      }
    }

    line("END_STATE();");
  }

  void add_character_set_condition(const rules::CharacterSet &rule) {
    if (rule.includes_all) {
      add("!(");
      add_character_range_conditions(rule.excluded_ranges());
      add(")");
    } else {
      add_character_range_conditions(rule.included_ranges());
    }
  }

  void add_character_range_conditions(const vector<rules::CharacterRange> &ranges) {
    if (ranges.size() == 1) {
      add_character_range_condition(*ranges.begin());
    } else {
      bool first = true;
      for (const auto &range : ranges) {
        if (!first) {
          add(" ||");
          line("  ");
        }

        add("(");
        add_character_range_condition(range);
        add(")");

        first = false;
      }
    }
  }

  void add_character_range_condition(const rules::CharacterRange &range) {
    if (range.min == range.max) {
      add("lookahead == " + escape_char(range.min));
    } else {
      add(escape_char(range.min) + string(" <= lookahead && lookahead <= ") +
          escape_char(range.max));
    }
  }

  void add_advance_action(const AdvanceAction &action) {
    if (action.in_main_token) {
      line("ADVANCE(" + to_string(action.state_index) + ");");
    } else {
      line("SKIP(" + to_string(action.state_index) + ");");
    }
  }

  void add_accept_token_action(const AcceptTokenAction &action) {
    line("ACCEPT_TOKEN(" + symbol_id(action.symbol) + ");");
  }

  void add_parse_action_list() {
    line("static TSParseActionEntry ts_parse_actions[] = {");

    indent([&]() {
      for (const auto &pair : parse_table_entries) {
        size_t index = pair.first;
        line("[" + to_string(index) + "] = {.count = " +
             to_string(pair.second.actions.size()) + ", .reusable = " +
             _boolean(pair.second.reusable) + ", .depends_on_lookahead = " +
             _boolean(pair.second.depends_on_lookahead) + "},");

        for (const ParseAction &action : pair.second.actions) {
          add(" ");
          switch (action.type) {
            case ParseActionTypeError:
              break;
            case ParseActionTypeAccept:
              add("ACCEPT_INPUT()");
              break;
            case ParseActionTypeShift:
              if (action.extra) {
                add("SHIFT_EXTRA()");
              } else {
                add("SHIFT(" + to_string(action.state_index) + ")");
              }
              break;
            case ParseActionTypeReduce:
              if (action.fragile) {
                add("REDUCE_FRAGILE(" + symbol_id(action.symbol) + ", " +
                    to_string(action.consumed_symbol_count) + ")");
              } else {
                add("REDUCE(" + symbol_id(action.symbol) + ", " +
                    to_string(action.consumed_symbol_count) + ")");
              }
              break;
            case ParseActionTypeRecover:
              add("RECOVER(" + to_string(action.state_index) + ")");
              break;
            default: {}
          }
          add(",");
        }
      }
    });

    line("};");
  }

  size_t add_parse_action_list_id(const ParseTableEntry &entry) {
    for (const auto &pair : parse_table_entries) {
      if (pair.second == entry) {
        return pair.first;
      }
    }

    size_t result = next_parse_action_list_index;
    parse_table_entries.push_back({ next_parse_action_list_index, entry });
    next_parse_action_list_index += 1 + entry.actions.size();
    return result;
  }

  // Helper functions

  string external_token_id(Symbol::Index index) {
    return "ts_external_token_" + sanitize_name(syntax_grammar.external_tokens[index].name);
  }

  string symbol_id(const Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT())
      return "ts_builtin_sym_end";

    auto entry = entry_for_symbol(symbol);
    string name = sanitize_name(entry.first);

    switch (entry.second) {
      case VariableTypeAuxiliary:
        return "aux_sym_" + name;
      case VariableTypeAnonymous:
        return "anon_sym_" + name;
      default:
        return "sym_" + name;
    }
  }

  string symbol_name(const Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT())
      return "END";
    return entry_for_symbol(symbol).first;
  }

  VariableType symbol_type(const Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT())
      return VariableTypeHidden;
    return entry_for_symbol(symbol).second;
  }

  pair<string, VariableType> entry_for_symbol(const Symbol &symbol) {
    switch (symbol.type) {
      case Symbol::NonTerminal: {
        const SyntaxVariable &variable = syntax_grammar.variables[symbol.index];
        return { variable.name, variable.type };
      }
      case Symbol::Terminal: {
        const LexicalVariable &variable = lexical_grammar.variables[symbol.index];
        return { variable.name, variable.type };
      }
      case Symbol::External:
      default: {
        const ExternalToken &token = syntax_grammar.external_tokens[symbol.index];
        return { token.name, token.type };
      }
    }
  }

  // C-code generation functions

  void _switch(string condition, function<void()> body) {
    line("switch (" + condition + ") {");
    indent(body);
    line("}");
  }

  void _case(string value, function<void()> body) {
    line("case " + value + ":");
    indent(body);
  }

  void _default(function<void()> body) {
    line("default:");
    indent(body);
  }

  void _if(function<void()> condition, function<void()> body) {
    line("if (");
    indent(condition);
    add(")");
    indent(body);
  }

  string sanitize_name_for_string(string name) {
    util::str_replace(&name, "\\", "\\\\");
    util::str_replace(&name, "\n", "\\n");
    util::str_replace(&name, "\r", "\\r");
    util::str_replace(&name, "\"", "\\\"");
    return name;
  }

  string sanitize_name(string name) {
    auto existing = sanitized_names.find(name);
    if (existing != sanitized_names.end())
      return existing->second;

    string stripped_name;
    for (char c : name) {
      if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
          ('0' <= c && c <= '9') || (c == '_')) {
        stripped_name += c;
      } else {
        auto replacement = REPLACEMENTS.find(c);
        size_t i = stripped_name.size();
        if (replacement != REPLACEMENTS.end()) {
          if (i > 0 && stripped_name[i - 1] != '_')
            stripped_name += "_";
          stripped_name += replacement->second;
        }
      }
    }

    for (size_t extra_number = 0;; extra_number++) {
      string suffix = extra_number ? to_string(extra_number) : "";
      string unique_name = stripped_name + suffix;
      if (unique_name == "")
        continue;
      if (!has_sanitized_name(unique_name)) {
        sanitized_names.insert({ name, unique_name });
        return unique_name;
      }
    }
  }

  string _boolean(bool value) {
    return value ? "true" : "false";
  }

  bool has_sanitized_name(string name) {
    for (const auto &pair : sanitized_names)
      if (pair.second == name)
        return true;
    return false;
  }

  // General code generation functions

  void line() {
    line("");
  }

  void line(string input) {
    add("\n");
    if (!input.empty()) {
      add_padding();
      add(input);
    }
  }

  void add_padding() {
    for (size_t i = 0; i < indent_level; i++)
      add("  ");
  }

  void indent(function<void()> body) {
    indent_level++;
    body();
    indent_level--;
  }

  void add(string input) {
    buffer += input;
  }
};

string c_code(string name, const ParseTable &parse_table,
              const LexTable &lex_table, const SyntaxGrammar &syntax_grammar,
              const LexicalGrammar &lexical_grammar) {
  return CCodeGenerator(
    name,
    parse_table,
    lex_table,
    syntax_grammar,
    lexical_grammar
  ).code();
}

}  // namespace generate_code
}  // namespace tree_sitter
