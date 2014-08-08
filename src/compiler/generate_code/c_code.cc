#include <map>
#include <set>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include "compiler/generate_code/c_code.h"
#include "compiler/util/string_helpers.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
namespace generate_code {
using std::string;
using std::to_string;
using std::function;
using std::map;
using std::vector;
using std::set;
using std::pair;
using util::escape_char;

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

    includes();
    state_and_symbol_counts();
    symbol_enum();
    symbol_names_list();
    hidden_symbols_list();
    lex_function();
    lex_states_list();
    parse_table_array();
    parser_export();

    return buffer;
  }

 private:
  void includes() {
    add("#include \"tree_sitter/parser.h\"");
    line();
  }

  void state_and_symbol_counts() {
    line("#define STATE_COUNT " + to_string(parse_table.states.size()));
    line("#define SYMBOL_COUNT " + to_string(parse_table.symbols.size()));
    line();
  }

  void symbol_enum() {
    line("enum {");
    indent([&]() {
      bool at_start = true;
      for (auto symbol : parse_table.symbols)
        if (!symbol.is_built_in()) {
          if (at_start)
            line(symbol_id(symbol) + " = ts_start_sym,");
          else
            line(symbol_id(symbol) + ",");
          at_start = false;
        }
    });
    line("};");
    line();
  }

  void symbol_names_list() {
    set<rules::Symbol> symbols(parse_table.symbols);
    symbols.insert(rules::END_OF_INPUT());
    symbols.insert(rules::ERROR());

    line("SYMBOL_NAMES = {");
    indent([&]() {
      for (auto symbol : parse_table.symbols)
        line("[" + symbol_id(symbol) + "] = \"" + symbol_name(symbol) + "\",");
    });
    line("};");
    line();
  }

  void hidden_symbols_list() {
    line("HIDDEN_SYMBOLS = {");
    indent([&]() {
      for (auto &symbol : parse_table.symbols)
        if (!symbol.is_built_in() &&
            (symbol.is_auxiliary() || rule_name(symbol)[0] == '_'))
          line("[" + symbol_id(symbol) + "] = 1,");
    });
    line("};");
    line();
  }

  void lex_function() {
    line("LEX_FN() {");
    indent([&]() {
      line("START_LEXER();");
      switch_on_lex_state();
    });
    line("}");
    line();
  }

  void lex_states_list() {
    line("LEX_STATES = {");
    indent([&]() {
      size_t state_id = 0;
      for (auto &state : parse_table.states)
        line("[" + to_string(state_id++) + "] = " +
             lex_state_index(state.lex_state_id) + ",");
    });
    line("};");
    line();
  }

  void parse_table_array() {
    size_t state_id = 0;
    line("#pragma GCC diagnostic push");
    line("#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"");
    line();
    line("PARSE_TABLE = {");

    indent([&]() {
      for (auto &state : parse_table.states) {
        line("[" + to_string(state_id++) + "] = {");
        indent([&]() {
          for (auto &pair : state.actions) {
            line("[" + symbol_id(pair.first) + "] = ");
            code_for_parse_action(pair.second);
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

  void parser_export() {
    line("EXPORT_LANGUAGE(ts_language_" + name + ");");
    line();
  }

  string rule_name(const rules::Symbol &symbol) {
    return symbol.is_token() ? lexical_grammar.rule_name(symbol)
                             : syntax_grammar.rule_name(symbol);
  }

  string symbol_id(const rules::Symbol &symbol) {
    if (symbol.is_built_in()) {
      return (symbol == rules::ERROR()) ? "ts_builtin_sym_error"
                                        : "ts_builtin_sym_end";
    } else {
      string name = sanitize_name(rule_name(symbol));
      if (symbol.is_auxiliary())
        return "ts_aux_sym_" + name;
      else
        return "ts_sym_" + name;
    }
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
    for (auto &pair : sanitized_names)
      if (pair.second == name)
        return true;
    return false;
  }

  string lex_state_index(size_t i) { return to_string(i + 1); }

  string symbol_name(const rules::Symbol &symbol) {
    if (symbol.is_built_in()) {
      return (symbol == rules::ERROR()) ? "error" : "end";
    } else if (symbol.is_token() && symbol.is_auxiliary()) {
      return rule_name(symbol);
    } else {
      return rule_name(symbol);
    }
  }

  string condition_for_character_range(const rules::CharacterRange &range) {
    string lookahead("lookahead");
    if (range.min == range.max) {
      return lookahead + " == " + escape_char(range.min);
    } else {
      return escape_char(range.min) + string(" <= ") + lookahead + " && " +
             lookahead + " <= " + escape_char(range.max);
    }
  }

  void condition_for_character_set(const rules::CharacterSet &set) {
    if (set.ranges.size() == 1) {
      add(condition_for_character_range(*set.ranges.begin()));
    } else {
      bool first = true;
      for (auto &match : set.ranges) {
        string part = "(" + condition_for_character_range(match) + ")";
        if (first) {
          add(part);
        } else {
          add(" ||");
          line(part);
        }
        first = false;
      }
    }
  }

  void condition_for_character_rule(const rules::CharacterSet &rule) {
    pair<rules::CharacterSet, bool> representation =
        rule.most_compact_representation();
    if (representation.second) {
      condition_for_character_set(representation.first);
    } else {
      add("!(");
      condition_for_character_set(rule.complement());
      add(")");
    }
  }

  void code_for_parse_action(const ParseAction &action) {
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

  void code_for_lex_actions(const LexAction &action,
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

  void code_for_lex_state(const LexState &lex_state) {
    auto expected_inputs = lex_state.expected_inputs();
    if (lex_state.is_token_start)
      line("START_TOKEN();");
    for (auto pair : lex_state.actions)
      if (!pair.first.is_empty())
        _if([&]() { condition_for_character_rule(pair.first); },
            [&]() { code_for_lex_actions(pair.second, expected_inputs); });
    code_for_lex_actions(lex_state.default_action, expected_inputs);
  }

  void switch_on_lex_state() {
    _switch("lex_state", [&]() {
      for (size_t i = 0; i < lex_table.states.size(); i++)
        _case(lex_state_index(i),
              [&]() { code_for_lex_state(lex_table.states[i]); });
      _case("ts_lex_state_error",
            [&]() { code_for_lex_state(lex_table.error_state); });
      _default([&]() { line("LEX_PANIC();"); });
    });
  }

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

  void line() { line(""); }

  void line(string input) {
    add("\n");
    if (!input.empty()) {
      string space;
      for (size_t i = 0; i < indent_level; i++)
        space += "    ";
      add(space + input);
    }
  }

  void add(string input) { buffer += input; }

  void indent(function<void()> body) { indent(body, 1); }

  void indent(function<void()> body, size_t n) {
    indent_level += n;
    body();
    indent_level -= n;
  }
};

string c_code(string name, const ParseTable &parse_table,
              const LexTable &lex_table, const SyntaxGrammar &syntax_grammar,
              const LexicalGrammar &lexical_grammar) {
  return CCodeGenerator(name, parse_table, lex_table, syntax_grammar,
                        lexical_grammar).code();
}

}  // namespace generate_code
}  // namespace tree_sitter
