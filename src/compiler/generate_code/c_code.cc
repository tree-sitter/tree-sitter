#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "compiler/generate_code/c_code.h"
#include "compiler/util/string_helpers.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::string;
    using std::to_string;
    using std::map;
    using std::vector;
    using std::set;
    using std::pair;
    using util::join;
    using util::indent;
    using util::character_code;

    namespace generate_code {
        string _switch(string condition, string body) {
            return join({
                "switch (" + condition + ") {",
                indent(body),
                "}"
            });
        }

        string _case(string value, string body) {
            return join({
                "case " + value + ":",
                indent(body), ""
            });
        }

        string _default(string body) {
            return join({
                "default:",
                indent(body)
            });
        }

        string _if(string condition, string body) {
            return join({
                "if (" + condition + ")",
                indent(body), ""
            });
        }

        class CCodeGenerator {
            const string name;
            const ParseTable parse_table;
            const LexTable lex_table;
            const PreparedGrammar syntax_grammar;
            const PreparedGrammar lexical_grammar;
            map<string, string> sanitized_names;

        public:
            CCodeGenerator(string name,
                           const ParseTable &parse_table,
                           const LexTable &lex_table,
                           const PreparedGrammar &syntax_grammar,
                           const PreparedGrammar &lexical_grammar) :
                name(name),
                parse_table(parse_table),
                lex_table(lex_table),
                syntax_grammar(syntax_grammar),
                lexical_grammar(lexical_grammar) {}

            string code() {
                return join({
                    includes(),
                    state_and_symbol_counts(),
                    symbol_enum(),
                    symbol_names_list(),
                    ubiquitous_symbols_list(),
                    hidden_symbols_list(),
                    lex_function(),
                    lex_states_list(),
                    parse_table_array(),
                    parser_export(),
                }, "\n\n") + "\n";
            }

        private:
            const PreparedGrammar & grammar_for_symbol(const rules::Symbol &symbol) {
                return symbol.is_token() ? lexical_grammar : syntax_grammar;
            }
            
            string sanitize_name(string name) {
                auto existing = sanitized_names.find(name);
                if (existing != sanitized_names.end())
                    return existing->second;

                string stripped_name;
                for (char c : name) {
                    if (('a' <= c && c <= 'z') ||
                        ('A' <= c && c <= 'Z') ||
                        ('0' <= c && c <= '9') ||
                        (c == '_')) {
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

            string symbol_id(const rules::Symbol &symbol) {
                if (symbol.is_built_in()) {
                    return (symbol == rules::ERROR()) ?
                        "ts_builtin_sym_error" :
                        "ts_builtin_sym_end";
                } else {
                    string name = sanitize_name(grammar_for_symbol(symbol).rule_name(symbol));
                    if (symbol.is_auxiliary())
                        return "ts_aux_sym_" + name;
                    else
                        return "ts_sym_" + name;
                }
            }

            string lex_state_index(size_t i) {
                return to_string(i + 1);
            }

            string symbol_name(const rules::Symbol &symbol) {
                if (symbol.is_built_in()) {
                    return (symbol == rules::ERROR()) ? "error" : "end";
                } else if (symbol.is_token() && symbol.is_auxiliary()) {
                    return grammar_for_symbol(symbol).rule_name(symbol);
                } else {
                    return grammar_for_symbol(symbol).rule_name(symbol);
                }
            }

            string condition_for_character_range(const rules::CharacterRange &range) {
                string lookahead("lookahead");
                if (range.min == range.max) {
                    return lookahead + " == '" + character_code(range.min) + "'";
                } else {
                    return string("'") + character_code(range.min) + string("' <= ") + lookahead +
                    " && " + lookahead + " <= '" + character_code(range.max) + "'";
                }
            }

            string condition_for_character_set(const rules::CharacterSet &set) {
                vector<string> parts;
                if (set.ranges.size() == 1) {
                    return condition_for_character_range(*set.ranges.begin());
                } else {
                    for (auto &match : set.ranges)
                        parts.push_back("(" + condition_for_character_range(match) + ")");
                    return join(parts, " ||\n    ");
                }
            }

            string condition_for_character_rule(const rules::CharacterSet &rule) {
                vector<string> parts;
                pair<rules::CharacterSet, bool> representation = rule.most_compact_representation();
                if (representation.second)
                    return condition_for_character_set(representation.first);
                else
                    return "!(" + condition_for_character_set(rule.complement()) + ")";
            }

            string code_for_parse_action(const ParseAction &action) {
                switch (action.type) {
                    case ParseActionTypeAccept:
                        return "ACCEPT_INPUT()";
                    case ParseActionTypeShift:
                        return "SHIFT(" + to_string(action.state_index) + ")";
                    case ParseActionTypeReduce:
                        return "REDUCE(" +
                            symbol_id(action.symbol) + ", " +
                            to_string(action.consumed_symbol_count) + ")";
                    default:
                        return "";
                }
            }

            string code_for_lex_actions(const LexAction &action,
                                        const set<rules::CharacterSet> &expected_inputs) {
                switch (action.type) {
                    case LexActionTypeAdvance:
                        return "ADVANCE(" + lex_state_index(action.state_index) + ");";
                    case LexActionTypeAccept:
                        return "ACCEPT_TOKEN(" + symbol_id(action.symbol) + ");";
                    case LexActionTypeError:
                        return "LEX_ERROR();";
                    default:
                        return "";
                }
            }

            string code_for_lex_state(const LexState &lex_state) {
                string result = "";
                auto expected_inputs = lex_state.expected_inputs();
                if (lex_state.is_token_start)
                    result += "START_TOKEN();" "\n";
                for (auto pair : lex_state.actions)
                    if (!pair.first.is_empty())
                        result += _if(condition_for_character_rule(pair.first),
                                      code_for_lex_actions(pair.second, expected_inputs));
                result += code_for_lex_actions(lex_state.default_action, expected_inputs);
                return result;
            }

            string switch_on_lex_state() {
                string body = "";
                for (size_t i = 0; i < lex_table.states.size(); i++)
                    body += _case(lex_state_index(i), code_for_lex_state(lex_table.states[i]));
                body += _case("ts_lex_state_error", code_for_lex_state(lex_table.error_state));
                body += _default("LEX_PANIC();");
                return _switch("lex_state", body);
            }

            string state_and_symbol_counts() {
                return join({
                    "#define STATE_COUNT " + to_string(parse_table.states.size()),
                    "#define SYMBOL_COUNT " + to_string(parse_table.symbols.size())
                });
            }

            string symbol_enum() {
                string result = "enum {\n";
                bool at_start = true;
                for (auto symbol : parse_table.symbols)
                    if (!symbol.is_built_in()) {
                        if (at_start)
                            result += indent(symbol_id(symbol)) + " = ts_start_sym,\n";
                        else
                            result += indent(symbol_id(symbol)) + ",\n";
                        at_start = false;
                    }
                return result + "};";
            }

            string symbol_names_list() {
                set<rules::Symbol> symbols(parse_table.symbols);
                symbols.insert(rules::END_OF_INPUT());
                symbols.insert(rules::ERROR());

                string result = "SYMBOL_NAMES = {\n";
                for (auto symbol : parse_table.symbols)
                    result += indent("[" + symbol_id(symbol) + "] = \"" + symbol_name(symbol)) + "\",\n";
                return result + "};";
            }

            string ubiquitous_symbols_list() {
                string result = "UBIQUITOUS_SYMBOLS = {\n";
                for (auto &symbol : syntax_grammar.options.ubiquitous_tokens)
                    result += indent("[" + symbol_id(symbol) + "] = 1,") + "\n";
                return result + "};";
            }

            string hidden_symbols_list() {
                string result = "HIDDEN_SYMBOLS = {\n";
                for (auto &symbol : parse_table.symbols)
                    if (!symbol.is_built_in() && (symbol.is_auxiliary() || grammar_for_symbol(symbol).rule_name(symbol)[0] == '_'))
                        result += indent("[" + symbol_id(symbol) + "] = 1,") + "\n";
                return result + "};";
            }

            string includes() {
                return "#include \"tree_sitter/parser.h\"";
            }

            string lex_function() {
                return join({
                    "LEX_FN() {",
                    indent("START_LEXER();"),
                    indent(switch_on_lex_state()),
                    "}"
                });
            }

            template<typename T>
            vector<string> map_to_string(const vector<T> &inputs, std::function<string(T)> f) {
                vector<string> result;
                for (auto &item : inputs)
                    result.push_back(f(item));
                return result;
            }

            string lex_states_list() {
                size_t state_id = 0;
                return join({
                    "LEX_STATES = {",
                    indent(join(map_to_string<ParseState>(parse_table.states, [&](ParseState state) {
                        return "[" + to_string(state_id++) + "] = " + lex_state_index(state.lex_state_id) + ",";
                    }))),
                    "};"
                });
            }

            string parse_table_array() {
                size_t state_id = 0;
                return join({
                    "#pragma GCC diagnostic push",
                    "#pragma GCC diagnostic ignored \"-Wmissing-field-initializers\"",
                    "",
                    "PARSE_TABLE = {",
                    indent(join(map_to_string<ParseState>(parse_table.states, [&](ParseState state) {
                        string result = "[" + to_string(state_id++) + "] = {\n";
                        for (auto &pair : state.actions)
                            result += indent("[" + symbol_id(pair.first) + "] = " + code_for_parse_action(pair.second) + ",") + "\n";
                        return result + "},";
                    }), "\n")),
                    "};",
                    "",
                    "#pragma GCC diagnostic pop"
                });
            }

            string parser_export() {
                return "EXPORT_PARSER(ts_parser_" + name + ");";
            }
        };

        string c_code(string name,
                      const ParseTable &parse_table,
                      const LexTable &lex_table,
                      const PreparedGrammar &syntax_grammar,
                      const PreparedGrammar &lexical_grammar) {
            return CCodeGenerator(name, parse_table, lex_table, syntax_grammar, lexical_grammar).code();
        }
    }
}
