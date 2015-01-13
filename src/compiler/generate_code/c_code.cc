#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "compiler/generate_code/c_code.h"
#include "compiler/lex_table.h"
#include "compiler/parse_table.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace generate_code {

using std::function;
using std::map;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using util::escape_char;

static const map<char, string> REPLACEMENTS({ { '~', "TILDE" },
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
                                              { '\n', "LB" },
                                              { '\r', "CR" },
                                              { '\t', "TAB" }, });

class CCodeGenerator {
  string buffer;
  size_t indent_level;

  const string name;
  const ParseTable parse_table;
  const LexTable lex_table;
  const SyntaxGrammar syntax_grammar;
  const LexicalGrammar lexical_grammar;
  map<string, string> sanitized_names;

 public:
  CCodeGenerator(string name, const ParseTable &parse_table,
                 const LexTable &lex_table, const SyntaxGrammar &syntax_grammar,
                 const LexicalGrammar &lexical_grammar)
      : indent_level(0),
        name(name),
        parse_table(parse_table),
        lex_table(lex_table),
        syntax_grammar(syntax_grammar),
        lexical_grammar(lexical_grammar) {}

  string code() {
    buffer = "";

    add_includes();
    add_state_and_symbol_counts();
    add_symbol_enum();
    add_symbol_names_list();
    add_hidden_symbols_list();
    add_lex_function();
    add_lex_states_list();
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
      for (const auto &symbol : parse_table.symbols)
        if (!symbol.is_built_in()) {
          if (at_start)
            line(symbol_id(symbol) + " = ts_builtin_sym_start,");
          else
            line(symbol_id(symbol) + ",");
          at_start = false;
        }
    });
    line("};");
    line();
  }

  void add_symbol_names_list() {
    line("static const char *ts_symbol_names[] = {");
    indent([&]() {
      for (const auto &symbol : parse_table.symbols)
        line("[" + symbol_id(symbol) + "] = \"" + symbol_name(symbol) + "\",");
    });
    line("};");
    line();
  }

  void add_hidden_symbols_list() {
    line("static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {");
    indent([&]() {
      for (const auto &symbol : parse_table.symbols)
        if (!symbol.is_built_in() &&
            (symbol.is_auxiliary() || rule_name(symbol)[0] == '_'))
          line("[" + symbol_id(symbol) + "] = 1,");
    });
    line("};");
    line();
  }

  void add_lex_function() {
    line("static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state) {");
    indent([&]() {
      line("START_LEXER();");
      _switch("lex_state", [&]() {
        for (size_t i = 0; i < lex_table.states.size(); i++)
          _case(lex_state_index(i),
                [&]() { add_lex_state(lex_table.states[i]); });
        _case("ts_lex_state_error",
              [&]() { add_lex_state(lex_table.error_state); });
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
             lex_state_index(state.lex_state_id) + ",");
    });
    line("};");
    line();
  }

  void add_parse_table() {
    size_t state_id = 0;
    line("#pragma GCC diagnostic push");
    line("#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"");
    line();
    line(
        "static const TSParseAction "
        "ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {");

    indent([&]() {
      for (const auto &state : parse_table.states) {
        line("[" + to_string(state_id++) + "] = {");
        indent([&]() {
          for (const auto &pair : state.actions) {
            line("[" + symbol_id(pair.first) + "] = ");
            add_parse_action(pair.second);
            add(",");
          }
        });
        line("},");
      }
    });

    line("};");
    line();
    line("#pragma GCC diagnostic pop");
    line();
  }

  void add_parser_export() {
    line("EXPORT_LANGUAGE(ts_language_" + name + ");");
    line();
  }

  void add_lex_state(const LexState &lex_state) {
    auto expected_inputs = lex_state.expected_inputs();
    if (lex_state.is_token_start)
      line("START_TOKEN();");
    for (const auto &pair : lex_state.actions)
      if (!pair.first.is_empty())
        _if([&]() { add_character_set_condition(pair.first); },
            [&]() { add_lex_actions(pair.second, expected_inputs); });
    add_lex_actions(lex_state.default_action, expected_inputs);
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

  void add_lex_actions(const LexAction &action,
                       const set<rules::CharacterSet> &expected_inputs) {
    switch (action.type) {
      case LexActionTypeAdvance:
        line("ADVANCE(" + lex_state_index(action.state_index) + ");");
        break;
      case LexActionTypeAccept:
        line("ACCEPT_TOKEN(" + symbol_id(action.symbol) + ");");
        break;
      case LexActionTypeError:
        line("LEX_ERROR();");
        break;
      default: {}
    }
  }

  void add_parse_action(const ParseAction &action) {
    switch (action.type) {
      case ParseActionTypeAccept:
        add("ACCEPT_INPUT()");
        break;
      case ParseActionTypeShift:
        add("SHIFT(" + to_string(action.state_index) + ")");
        break;
      case ParseActionTypeShiftExtra:
        add("SHIFT_EXTRA()");
        break;
      case ParseActionTypeReduce:
        add("REDUCE(" + symbol_id(action.symbol) + ", " +
            to_string(action.consumed_symbol_count) + ")");
        break;
      case ParseActionTypeReduceExtra:
        add("REDUCE_EXTRA(" + symbol_id(action.symbol) + ")");
        break;
      default: {}
    }
  }

  // Helper functions

  string lex_state_index(size_t i) { return to_string(i + 1); }

  string symbol_id(const rules::Symbol &symbol) {
    if (symbol.is_built_in()) {
      if (symbol == rules::ERROR())
        return "ts_builtin_sym_error";
      else if (symbol == rules::END_OF_INPUT())
        return "ts_builtin_sym_end";
      else
        return "ts_builtin_sym_document";
    } else {
      string name = sanitize_name(rule_name(symbol));
      if (symbol.is_auxiliary())
        return "aux_sym_" + name;
      else
        return "sym_" + name;
    }
  }

  string symbol_name(const rules::Symbol &symbol) {
    if (symbol.is_built_in()) {
      if (symbol == rules::ERROR())
        return "error";
      else if (symbol == rules::END_OF_INPUT())
        return "end";
      else
        return "DOCUMENT";
    } else {
      return rule_name(symbol);
    }
  }

  string rule_name(const rules::Symbol &symbol) {
    return symbol.is_token() ? lexical_grammar.rule_name(symbol)
                             : syntax_grammar.rule_name(symbol);
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

  string sanitize_name(string name) {
    auto existing = sanitized_names.find(name);
    if (existing != sanitized_names.end())
      return existing->second;

    string stripped_name;
    for (char c : name) {
      if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
          ('0' <= c && c <= '9') || (c == '_')) {
        stripped_name += c;
        continue;
      }

      auto replacement = REPLACEMENTS.find(c);
      if (replacement != REPLACEMENTS.end()) {
        if (stripped_name[stripped_name.size() - 1] != '_')
          stripped_name += "_";
        stripped_name += replacement->second;
        continue;
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

  void line() { line(""); }

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

  void add(string input) { buffer += input; }
};

string c_code(string name, const ParseTable &parse_table,
              const LexTable &lex_table, const SyntaxGrammar &syntax_grammar,
              const LexicalGrammar &lexical_grammar) {
  return CCodeGenerator(name, parse_table, lex_table, syntax_grammar,
                        lexical_grammar).code();
}

}  // namespace generate_code
}  // namespace tree_sitter
