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
using std::move;
using std::pair;
using std::set;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using util::escape_char;
using rules::Symbol;
using rules::Alias;

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
  const LexTable main_lex_table;
  const LexTable keyword_lex_table;
  Symbol keyword_capture_token;
  const SyntaxGrammar syntax_grammar;
  const LexicalGrammar lexical_grammar;
  unordered_map<Symbol, Alias> simple_aliases;
  map<Symbol, string> symbol_ids;
  vector<pair<size_t, ParseTableEntry>> parse_table_entries;
  vector<set<Symbol::Index>> external_scanner_states;
  size_t next_parse_action_list_index;
  set<Alias> unique_aliases;

 public:
  CCodeGenerator(
    string name, ParseTable &&parse_table, LexTable &&main_lex_table,
    LexTable &&keyword_lex_table, Symbol keyword_capture_token,
    SyntaxGrammar &&syntax_grammar, LexicalGrammar &&lexical_grammar,
    unordered_map<Symbol, Alias> &&simple_aliases
  ) : indent_level(0),
      name(name),
      parse_table(move(parse_table)),
      main_lex_table(move(main_lex_table)),
      keyword_lex_table(move(keyword_lex_table)),
      keyword_capture_token(keyword_capture_token),
      syntax_grammar(move(syntax_grammar)),
      lexical_grammar(move(lexical_grammar)),
      simple_aliases(move(simple_aliases)),
      next_parse_action_list_index(0) {}

  string code() {
    buffer = "";

    add_includes();
    add_pragmas();
    add_stats();
    add_symbol_enum();
    add_symbol_names_list();
    add_symbol_metadata_list();

    if (parse_table.alias_sequences.size() > 1) {
      add_alias_sequences();
    }

    add_lex_function("ts_lex", main_lex_table);

    if (keyword_capture_token != rules::NONE()) {
      add_lex_function("ts_lex_keywords", keyword_lex_table);
    }

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

  void add_pragmas() {
    line("#if defined(__GNUC__) || defined(__clang__)");
    line("#pragma GCC diagnostic push");
    line("#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"");
    line("#endif");
    line();

    // Compiling large lexer functions can be very slow, especially when
    // using Visual Studio on Windows. Disabling optimizations is not
    // ideal, but only a very small fraction of overall parse time is
    // spent lexing, so the performance impact of this is pretty small.
    if (main_lex_table.states.size() > 500) {
      line("#ifdef _MSC_VER");
      line("#pragma optimize(\"\", off)");
      line("#endif");
      line();
    }
  }

  void add_stats() {
    size_t token_count = 0;
    for (const Symbol &symbol : parse_table.symbols) {
      if (symbol.is_terminal()) {
        token_count++;
      } else if (symbol.is_external()) {
        const ExternalToken &external_token = syntax_grammar.external_tokens[symbol.index];
        if (external_token.corresponding_internal_token == rules::NONE()) {
          token_count++;
        }
      }
    }

    for (const AliasSequence &alias_sequence : parse_table.alias_sequences) {
      for (const Alias &alias : alias_sequence) {
        if (!alias.value.empty()) {
          unique_aliases.insert(alias);
        }
      }
    }

    unordered_set<string> symbol_id_values;
    symbol_ids[rules::END_OF_INPUT()] = "ts_builtin_sym_end";

    for (const Symbol &symbol : parse_table.symbols) {
      if (!symbol.is_built_in()) {
        assign_symbol_id(symbol, &symbol_id_values);
      }
    }

    for (size_t i = 0; i < syntax_grammar.external_tokens.size(); i++) {
      Symbol symbol = Symbol::external(i);
      if (!symbol_ids.count(symbol)) {
        const ExternalToken &external_token = syntax_grammar.external_tokens[i];
        if (external_token.corresponding_internal_token == rules::NONE()) {
          assign_symbol_id(Symbol::external(i), &symbol_id_values);
        } else {
          symbol_ids[Symbol::external(i)] = symbol_ids[external_token.corresponding_internal_token];
        }
      }
    }

    line("#define LANGUAGE_VERSION " + to_string(TREE_SITTER_LANGUAGE_VERSION));
    line("#define STATE_COUNT " + to_string(parse_table.states.size()));
    line("#define SYMBOL_COUNT " + to_string(parse_table.symbols.size()));
    line("#define ALIAS_COUNT " + to_string(unique_aliases.size()));
    line("#define TOKEN_COUNT " + to_string(token_count));
    line("#define EXTERNAL_TOKEN_COUNT " + to_string(syntax_grammar.external_tokens.size()));
    line("#define MAX_ALIAS_SEQUENCE_LENGTH " + to_string(parse_table.max_alias_sequence_length));
    line();
  }

  void assign_symbol_id(const Symbol &symbol, unordered_set<string> *symbol_id_values) {
    auto entry = entry_for_symbol(symbol);

    string symbol_id;
    switch (entry.second) {
      case VariableTypeAuxiliary:
        symbol_id = "aux_sym_" + sanitize_name(entry.first);
        break;
      case VariableTypeAnonymous:
        symbol_id = "anon_sym_" + sanitize_name(entry.first);
        break;
      default:
        symbol_id = "sym_" + sanitize_name(entry.first);
        break;
    }

    unsigned suffix_number = 1;
    string unique_symbol_id = symbol_id;
    while (symbol_id_values->count(unique_symbol_id)) {
      suffix_number++;
      unique_symbol_id = symbol_id + to_string(suffix_number);
    }

    symbol_id_values->insert(unique_symbol_id);
    symbol_ids[symbol] = unique_symbol_id;
  }

  void add_symbol_enum() {
    line("enum {");
    indent([&]() {
      size_t i = 1;
      for (const Symbol &symbol : parse_table.symbols) {
        if (!symbol.is_built_in()) {
          line(symbol_id(symbol) + " = " + to_string(i) + ",");
          i++;
        }
      }

      for (const Alias &alias : unique_aliases) {
        line(alias_id(alias) + " = " + to_string(i) + ",");
        i++;
      }
    });
    line("};");
    line();
  }

  void add_symbol_names_list() {
    line("static const char *ts_symbol_names[] = {");
    indent([&]() {
      for (const Symbol &symbol : parse_table.symbols) {
        line(
          "[" + symbol_id(symbol) + "] = \"" +
          sanitize_name_for_string(symbol_name(symbol)) + "\","
        );
      }

      for (const Alias &alias : unique_aliases) {
        line(
          "[" + alias_id(alias) + "] = \"" +
          sanitize_name_for_string(alias.value) + "\","
        );
      }
    });
    line("};");
    line();
  }

  void add_alias_sequences() {
    line(
      "static TSSymbol ts_alias_sequences[" +
      to_string(parse_table.alias_sequences.size()) +
      "][MAX_ALIAS_SEQUENCE_LENGTH] = {"
    );

    indent([&]() {
      for (unsigned i = 1, n = parse_table.alias_sequences.size(); i < n; i++) {
        const AliasSequence &sequence = parse_table.alias_sequences[i];
        line("[" + to_string(i) + "] = {");
        indent([&]() {
          for (unsigned j = 0, n = sequence.size(); j < n; j++) {
            if (!sequence[j].value.empty()) {
              line("[" + to_string(j) + "] = " + alias_id(sequence[j]) + ",");
            }
          }
        });
        line("},");
      }
    });
    line("};");
    line();
  }

  void add_symbol_metadata_list() {
    line("static const TSSymbolMetadata ts_symbol_metadata[] = {");
    indent([&]() {
      for (const Symbol &symbol : parse_table.symbols) {
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
        });

        line("},");
      }

      for (const Alias &alias : unique_aliases) {
        line("[" + alias_id(alias) + "] = {");
        indent([&]() {
          line(".visible = true,");
          line(".named = " + _boolean(alias.is_named) + ",");
        });
        line("},");
      }
    });
    line("};");
    line();
  }

  void add_lex_function(string name, const LexTable &lex_table) {
    line("static bool " + name + "(TSLexer *lexer, TSStateId state) {");
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

        set<Symbol::Index> external_token_indices;
        for (const auto &pair : state.terminal_entries) {
          Symbol symbol = pair.first;
          if (symbol.is_external()) {
            external_token_indices.insert(symbol.index);
          } else if (symbol.is_terminal()) {
            auto corresponding_external_token =
              external_tokens_by_corresponding_internal_token.find(symbol.index);
            if (corresponding_external_token != external_tokens_by_corresponding_internal_token.end()) {
              external_token_indices.insert(corresponding_external_token->second);
            }
          }
        }

        if (!external_token_indices.empty()) {
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
    add_parse_action_list_id(ParseTableEntry{ {}, false });

    size_t state_id = 0;
    line("static uint16_t ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {");

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
      line("void " + external_scanner_name + "_destroy(void *);");
      line("bool " + external_scanner_name + "_scan(void *, TSLexer *, const bool *);");
      line("unsigned " + external_scanner_name + "_serialize(void *, char *);");
      line("void " + external_scanner_name + "_deserialize(void *, const char *, unsigned);");
      line();
    }

    line("#ifdef _WIN32");
    line("#define extern __declspec(dllexport)");
    line("#endif");
    line();

    line("extern const TSLanguage *" + language_function_name + "() {");
    indent([&]() {
      line("static TSLanguage language = {");
      indent([&]() {
        line(".version = LANGUAGE_VERSION,");
        line(".symbol_count = SYMBOL_COUNT,");
        line(".alias_count = ALIAS_COUNT,");
        line(".token_count = TOKEN_COUNT,");
        line(".symbol_metadata = ts_symbol_metadata,");
        line(".parse_table = (const unsigned short *)ts_parse_table,");
        line(".parse_actions = ts_parse_actions,");
        line(".lex_modes = ts_lex_modes,");
        line(".symbol_names = ts_symbol_names,");

        if (parse_table.alias_sequences.size() > 1) {
          line(".alias_sequences = (const TSSymbol *)ts_alias_sequences,");
        }

        line(".max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,");
        line(".lex_fn = ts_lex,");

        if (keyword_capture_token != rules::NONE()) {
          line(".keyword_lex_fn = ts_lex_keywords,");
          line(".keyword_capture_token = " + symbol_id(keyword_capture_token) + ",");
        }

        line(".external_token_count = EXTERNAL_TOKEN_COUNT,");

        if (!syntax_grammar.external_tokens.empty()) {
          line(".external_scanner = {");
          indent([&]() {
            line("(const bool *)ts_external_scanner_states,");
            line("ts_external_scanner_symbol_map,");
            line(external_scanner_name + "_create,");
            line(external_scanner_name + "_destroy,");
            line(external_scanner_name + "_scan,");
            line(external_scanner_name + "_serialize,");
            line(external_scanner_name + "_deserialize,");
          });
          line("},");
        }
      });

      line("};");
      line("return &language;");
    });
    line("}");
    line();
  }

  void add_lex_state(const LexState &lex_state) {
    if (lex_state.accept_action.is_present()) {
      add_accept_token_action(lex_state.accept_action);
    }

    set<uint32_t> ruled_out_characters;
    for (const auto &pair : lex_state.advance_actions) {
      if (pair.first.is_empty()) continue;

      size_t current_length = buffer.size();

      line("if (");
      if (add_character_set_condition(pair.first, ruled_out_characters)) {
        add(")");
        indent([&]() { add_advance_action(pair.second); });
        ruled_out_characters.insert(pair.first.included_chars.begin(), pair.first.included_chars.end());
      } else {
        buffer.resize(current_length);
        add_advance_action(pair.second);
      }
    }

    line("END_STATE();");
  }

  bool add_character_set_condition(const rules::CharacterSet &rule, const set<uint32_t> &ruled_out_characters) {
    if (rule.includes_all) {
      return add_character_range_conditions(rule.excluded_ranges(), ruled_out_characters, true);
    } else {
      return add_character_range_conditions(rule.included_ranges(), ruled_out_characters, false);
    }
  }

  bool add_character_range_conditions(const vector<rules::CharacterRange> &ranges,
                                      const set<uint32_t> &ruled_out_characters,
                                      bool is_negated) {
    bool first = true;
    for (auto iter = ranges.begin(), end = ranges.end(); iter != end;) {
      auto range = *iter;

      bool range_is_ruled_out = true;
      for (uint32_t c = range.min; c <= range.max; c++) {
        if (!ruled_out_characters.count(c)) {
          range_is_ruled_out = false;
          break;
        }
      }

      if (range_is_ruled_out) {
        ++iter;
        continue;
      }

      auto next_iter = iter + 1;
      while (next_iter != end) {
        bool can_join_ranges = true;
        for (uint32_t character = range.max + 1; character < next_iter->min; character++) {
          if (!ruled_out_characters.count(character)) {
            can_join_ranges = false;
            break;
          }
        }

        if (can_join_ranges) {
          range.max = next_iter->max;
          ++next_iter;
        } else {
          break;
        }
      }

      if (!first) {
        add(is_negated ? " &&" : " ||");
        line("    ");
      }

      add_character_range_condition(range, is_negated);
      first = false;
      iter = next_iter;
    }

    return !first;
  }

  void add_character_range_condition(const rules::CharacterRange &range, bool is_negated) {
    auto min = escape_char(range.min);
    auto max = escape_char(range.max);
    if (is_negated) {
      if (range.max == range.min) {
        add("lookahead != " + min);
      } else if (range.max == range.min + 1) {
        add("lookahead != " + min + " &&");
        line("    lookahead != " + max);
      } else {
        add("(lookahead < " + min + " || lookahead > " + max + ")");
      }
    } else {
      if (range.max == range.min) {
        add("lookahead == " + min);
      } else if (range.max == range.min + 1) {
        add("lookahead == " + min + " ||");
        line("    lookahead == " + max);
      } else {
        add("(" + min + " <= lookahead && lookahead <= " + max + ")");
      }
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
        line(
          "[" + to_string(index) + "] = {"
            ".count = " + to_string(pair.second.actions.size()) + ", "
            ".reusable = " + _boolean(pair.second.reusable) +
          "},"
        );

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
              } else if (action.repetition) {
                add("SHIFT_REPEAT(" + to_string(action.state_index) + ")");
              } else {
                add("SHIFT(" + to_string(action.state_index) + ")");
              }
              break;
            case ParseActionTypeReduce:
              add("REDUCE(");
              add(symbol_id(action.symbol));
              add(", ");
              add(to_string(action.consumed_symbol_count));

              if (action.dynamic_precedence != 0) {
                add(", .dynamic_precedence = " + to_string(action.dynamic_precedence));
              }

              if (action.alias_sequence_id != 0) {
                add(", .alias_sequence_id = " + to_string(action.alias_sequence_id));
              }

              add(")");
              break;
            case ParseActionTypeRecover:
              add("RECOVER()");
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
    return symbol_ids[symbol];
  }

  string alias_id(const Alias &alias) {
    if (alias.is_named) {
      return "alias_sym_" + sanitize_name(alias.value);
    } else {
      return "anon_alias_sym_" + sanitize_name(alias.value);
    }
  }

  string symbol_name(const Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT()) {
      return "END";
    }

    auto simple_alias_entry = simple_aliases.find(symbol);
    if (simple_alias_entry != simple_aliases.end()) {
      return simple_alias_entry->second.value;
    }

    return entry_for_symbol(symbol).first;
  }

  VariableType symbol_type(const Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT()) {
      return VariableTypeHidden;
    }

    auto simple_alias_entry = simple_aliases.find(symbol);
    if (simple_alias_entry != simple_aliases.end()) {
      return simple_alias_entry->second.is_named ? VariableTypeNamed : VariableTypeAnonymous;
    }

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

  string sanitize_name_for_string(string name) {
    util::str_replace(&name, "\\", "\\\\");
    util::str_replace(&name, "\n", "\\n");
    util::str_replace(&name, "\r", "\\r");
    util::str_replace(&name, "\"", "\\\"");
    return name;
  }

  string sanitize_name(const string &name) {
    string result;
    for (char c : name) {
      if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
          ('0' <= c && c <= '9') || (c == '_')) {
        result += c;
      } else {
        auto replacement = REPLACEMENTS.find(c);
        size_t i = result.size();
        if (replacement != REPLACEMENTS.end()) {
          if (i > 0 && result[i - 1] != '_')
            result += "_";
          result += replacement->second;
        }
      }
    }
    return result;
  }

  string _boolean(bool value) {
    return value ? "true" : "false";
  }

  bool has_sanitized_name(const Symbol &symbol, string name) {
    for (const auto &pair : symbol_ids) {
      if (pair.second == name) {
        return true;
      }
    }
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

string c_code(
  string name, ParseTable &&parse_table, LexTable &&lex_table,
  LexTable &&keyword_lex_table, Symbol keyword_capture_token,
  SyntaxGrammar &&syntax_grammar, LexicalGrammar &&lexical_grammar,
  unordered_map<Symbol, Alias> &&simple_aliases
) {
  return CCodeGenerator(
    name,
    move(parse_table),
    move(lex_table),
    move(keyword_lex_table),
    keyword_capture_token,
    move(syntax_grammar),
    move(lexical_grammar),
    move(simple_aliases)
  ).code();
}

}  // namespace generate_code
}  // namespace tree_sitter
