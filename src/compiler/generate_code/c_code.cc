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
#include "compiler/rules/built_in_symbols.h"
#include "compiler/util/string_helpers.h"

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

static Variable EOF_ENTRY("end", VariableTypeNamed, rule_ptr());

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
  vector<pair<size_t, vector<ParseAction>>> parse_actions;
  vector<pair<size_t, set<rules::Symbol>>> in_progress_symbols;
  size_t next_parse_action_list_index;
  size_t next_in_progress_symbol_list_index;

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
        next_parse_action_list_index(0),
        next_in_progress_symbol_list_index(0) {}

  string code() {
    buffer = "";

    add_includes();
    add_state_and_symbol_counts();
    add_symbol_enum();
    add_symbol_names_list();
    add_symbol_node_types_list();
    add_lex_function();
    add_lex_states_list();
    add_recovery_parse_states_list();
    add_parse_table();
    add_parser_export();

    return buffer;
  }

 private:
  void add_includes() {
    add("#include \"tree_sitter/parser.h\"");
    line();
  }

  void add_state_and_symbol_counts() {
    line("#define STATE_COUNT " + to_string(parse_table.states.size()));
    line("#define SYMBOL_COUNT " + to_string(parse_table.symbols.size()));
    line();
  }

  void add_symbol_enum() {
    line("enum {");
    indent([&]() {
      bool at_start = true;
      for (const auto &entry : parse_table.symbols) {
        const rules::Symbol &symbol = entry.first;
        if (!symbol.is_built_in()) {
          if (at_start)
            line(symbol_id(symbol) + " = ts_builtin_sym_start,");
          else
            line(symbol_id(symbol) + ",");
          at_start = false;
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

  void add_symbol_node_types_list() {
    line("static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {");
    indent([&]() {
      for (const auto &entry : parse_table.symbols) {
        const rules::Symbol &symbol = entry.first;
        line("[" + symbol_id(symbol) + "] = {");

        switch (symbol_type(symbol)) {
          case VariableTypeNamed:
            add(".visible = true, .named = true");
            break;
          case VariableTypeAnonymous:
            add(".visible = true, .named = false");
            break;
          case VariableTypeHidden:
          case VariableTypeAuxiliary:
            add(".visible = false, .named = false");
            break;
        }

        add(", ");

        if (entry.second.structural)
          add(".structural = true");
        else
          add(".structural = false");

        add(", ");

        if (syntax_grammar.extra_tokens.count(symbol))
          add(".extra = true");
        else
          add(".extra = false");

        add("},");
      }
    });
    line("};");
    line();
  }

  void add_lex_function() {
    line(
      "static TSTree *ts_lex(TSLexer *lexer, TSStateId state, bool error_mode) "
      "{");
    indent([&]() {
      line("START_LEXER();");
      _switch("state", [&]() {
        size_t i = 0;
        for (const LexState &state : lex_table.states)
          _case(to_string(i++), [&]() { add_lex_state(state); });
        _default([&]() { line("LEX_ERROR();"); });
      });
    });
    line("}");
    line();
  }

  void add_lex_states_list() {
    line("static TSStateId ts_lex_states[STATE_COUNT] = {");
    indent([&]() {
      size_t state_id = 0;
      for (const auto &state : parse_table.states)
        line("[" + to_string(state_id++) + "] = " +
             to_string(state.lex_state_id) + ",");
    });
    line("};");
    line();
  }

  void add_recovery_parse_states_list() {
    line("static TSParseAction ts_recovery_actions[SYMBOL_COUNT] = {");
    indent([&]() {
      for (const auto &entry : parse_table.error_state.actions) {
        const rules::Symbol &symbol = entry.first;
        if (!entry.second.empty()) {
          ParseStateId state = entry.second[0].state_index;
          line("[" + symbol_id(symbol) + "] = RECOVER(" + to_string(state) +
               "),");
        }
      }
    });
    line("};");
    line();
  }

  void add_parse_table() {
    add_parse_action_list_id({ ParseAction::Error() });

    size_t state_id = 0;
    line("#pragma GCC diagnostic push");
    line("#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"");
    line();
    line("static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {");

    indent([&]() {
      for (const auto &state : parse_table.states) {
        line("[" + to_string(state_id++) + "] = {");
        indent([&]() {
          for (const auto &pair : state.actions) {
            line("[" + symbol_id(pair.first) + "] = ");
            add(to_string(add_parse_action_list_id(pair.second)));
            add(",");
          }
        });
        line("},");
      }
    });

    line("};");
    line();
    add_parse_action_list();
    line();
    line("#pragma GCC diagnostic pop");
    line();
  }

  void add_parser_export() {
    line("EXPORT_LANGUAGE(ts_language_" + name + ");");
    line();
  }

  void add_lex_state(const LexState &lex_state) {
    if (lex_state.is_token_start)
      line("START_TOKEN();");

    for (const auto &pair : lex_state.advance_actions)
      if (!pair.first.is_empty())
        _if([&]() { add_character_set_condition(pair.first); },
            [&]() { add_advance_action(pair.second); });

    if (lex_state.accept_action.is_present())
      add_accept_token_action(lex_state.accept_action);
    else
      line("LEX_ERROR();");
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
          line();
          add_padding();
        }

        add("(");
        add_character_range_condition(range);
        add(")");

        first = false;
      }
    }
  }

  void add_character_range_condition(const rules::CharacterRange &range) {
    string lookahead("lookahead");
    if (range.min == range.max) {
      add(lookahead + " == " + escape_char(range.min));
    } else {
      add(escape_char(range.min) + string(" <= ") + lookahead + " && " +
          lookahead + " <= " + escape_char(range.max));
    }
  }

  void add_advance_action(const AdvanceAction &action) {
    line("ADVANCE(" + to_string(action.state_index) + ");");
  }

  void add_accept_token_action(const AcceptTokenAction &action) {
    if (action.is_fragile)
      line("ACCEPT_FRAGILE_TOKEN(" + symbol_id(action.symbol) + ");");
    else
      line("ACCEPT_TOKEN(" + symbol_id(action.symbol) + ");");
  }

  void add_parse_action_list() {
    line("static TSParseActionEntry ts_parse_actions[] = {");

    indent([&]() {
      for (const auto &pair : parse_actions) {
        size_t index = pair.first;
        line("[" + to_string(index) + "] = {.count = " +
             to_string(pair.second.size()) + "},");

        for (const ParseAction &action : pair.second) {
          add(" ");
          switch (action.type) {
            case ParseActionTypeError:
              add("ERROR()");
              break;
            case ParseActionTypeAccept:
              add("ACCEPT_INPUT()");
              break;
            case ParseActionTypeShift:
              if (action.extra) {
                add("SHIFT_EXTRA()");
              } else {
                add("SHIFT(" + to_string(action.state_index) + ", ");
                add_action_flags(action);
                add(")");
              }
              break;
            case ParseActionTypeReduce:
              if (action.extra) {
                add("REDUCE_EXTRA(" + symbol_id(action.symbol) + ")");
              } else {
                add("REDUCE(" + symbol_id(action.symbol) + ", " +
                    to_string(action.consumed_symbol_count) + ", ");
                add_action_flags(action);
                add(")");
              }
              break;
            default: {}
          }
          add(",");
        }
      }
    });

    line("};");
  }

  size_t add_parse_action_list_id(const vector<ParseAction> &actions) {
    for (const auto &pair : parse_actions) {
      if (pair.second == actions) {
        return pair.first;
      }
    }

    size_t result = next_parse_action_list_index;
    parse_actions.push_back({ next_parse_action_list_index, actions });
    next_parse_action_list_index += 1 + actions.size();
    return result;
  }

  size_t add_in_progress_symbol_list_id(const set<rules::Symbol> &symbols) {
    for (const auto &pair : in_progress_symbols) {
      if (pair.second == symbols) {
        return pair.first;
      }
    }

    size_t result = next_in_progress_symbol_list_index;
    in_progress_symbols.push_back({ result, symbols });
    next_in_progress_symbol_list_index += 1 + symbols.size();
    return result;
  }

  void add_action_flags(const ParseAction &action) {
    if (action.fragile && action.can_hide_split)
      add("FRAGILE|CAN_HIDE_SPLIT");
    else if (action.fragile)
      add("FRAGILE");
    else if (action.can_hide_split)
      add("CAN_HIDE_SPLIT");
    else
      add("0");
  }

  // Helper functions

  string symbol_id(const rules::Symbol &symbol) {
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

  string symbol_name(const rules::Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT())
      return "END";
    return entry_for_symbol(symbol).first;
  }

  VariableType symbol_type(const rules::Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT())
      return VariableTypeHidden;
    return entry_for_symbol(symbol).second;
  }

  pair<string, VariableType> entry_for_symbol(const rules::Symbol &symbol) {
    if (symbol.is_token) {
      const Variable &variable = lexical_grammar.variables[symbol.index];
      return { variable.name, variable.type };
    } else {
      const SyntaxVariable &variable = syntax_grammar.variables[symbol.index];
      return { variable.name, variable.type };
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
      add("    ");
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
  return CCodeGenerator(name, parse_table, lex_table, syntax_grammar,
                        lexical_grammar)
    .code();
}

}  // namespace generate_code
}  // namespace tree_sitter
