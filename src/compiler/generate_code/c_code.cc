#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "compiler/generate_code/c_code.h"
#include "compiler/generate_code/helpers.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
    using std::string;
    using std::to_string;
    using std::map;
    using std::vector;
    using std::set;
    using std::pair;

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
            const map<rules::Symbol, string> symbol_names;
        public:
            CCodeGenerator(string name,
                           const ParseTable &parse_table,
                           const LexTable &lex_table,
                           const map<rules::Symbol, string> &symbol_names) :
                name(name),
                parse_table(parse_table),
                lex_table(lex_table),
                symbol_names(symbol_names)
                {}

            string code() {
                return join({
                    includes(),
                    state_and_symbol_counts(),
                    symbol_enum(),
                    symbol_names_list(),
                    hidden_symbols_list(),
                    lex_function(),
                    lex_states_list(),
                    parse_table_array(),
                    parser_export(),
                }, "\n\n") + "\n";
            }

        private:
            string symbol_id(rules::Symbol symbol) {
                if (symbol.is_built_in()) {
                    return (symbol == rules::ERROR()) ?
                        "ts_builtin_sym_error" :
                        "ts_builtin_sym_end";
                } else if (symbol.is_auxiliary()) {
                    return "ts_aux_sym_" + symbol.name;
                } else {
                    return "ts_sym_" + symbol.name;
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
                        return "ADVANCE(" + to_string(action.state_index) + ");";
                    case LexActionTypeAccept:
                        return "ACCEPT_TOKEN(" + symbol_id(action.symbol) + ");";
                    case LexActionTypeError:
                        return "LEX_ERROR();";
                }
            }

            string switch_on_lookahead_char(const LexState &parse_state) {
                string result = "";
                auto expected_inputs = parse_state.expected_inputs();
                for (auto pair : parse_state.actions)
                    if (!pair.first.is_empty())
                        result += _if(condition_for_character_rule(pair.first),
                                      code_for_lex_actions(pair.second, expected_inputs));
                result += code_for_lex_actions(parse_state.default_action, expected_inputs);
                return result;
            }

            string switch_on_lex_state() {
                string body = "";
                for (size_t i = 0; i < lex_table.states.size(); i++)
                    body += _case(std::to_string(i), switch_on_lookahead_char(lex_table.states[i]));
                body += _case("ts_lex_state_error", switch_on_lookahead_char(lex_table.error_state));
                body += _default("LEX_PANIC();");
                return _switch("lex_state", body);
            }

            string state_and_symbol_counts() {
                return join({
                    "STATE_COUNT = " + to_string(parse_table.states.size()) + ";",
                    "SYMBOL_COUNT = " + to_string(parse_table.symbols.size()) + ";"
                });
            }

            string symbol_enum() {
                string result = "enum {\n";
                size_t index = 2;
                for (auto symbol : parse_table.symbols)
                    if (!symbol.is_built_in())
                        result += indent(symbol_id(symbol)) + " = " + to_string(index++) + ",\n";
                return result + "};";
            }

            string symbol_names_list() {
                set<rules::Symbol> symbols(parse_table.symbols);
                symbols.insert(rules::END_OF_INPUT());
                symbols.insert(rules::ERROR());

                string result = "SYMBOL_NAMES = {\n";
                for (auto symbol : parse_table.symbols)
                    result += indent("[" + symbol_id(symbol) + "] = \"" + symbol_names.find(symbol)->second) + "\",\n";
                return result + "};";
            }

            string hidden_symbols_list() {
                string result = "HIDDEN_SYMBOLS = {";
                for (auto &symbol : parse_table.symbols)
                    if (symbol.is_hidden())
                        result += indent("\n[" + symbol_id(symbol) + "] = 1,");
                return result + "\n};";
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
                        return "[" + to_string(state_id++) + "] = " + to_string(state.lex_state_id) + ",";
                    }))),
                    "};"
                });
            }

            string parse_table_array() {
                size_t state_id = 0;
                return join({
                    "PARSE_TABLE = {",
                    indent(join(map_to_string<ParseState>(parse_table.states, [&](ParseState state) {
                        string result = "[" + to_string(state_id++) + "] = {\n";
                        for (auto &pair : state.actions)
                            result += indent("[" + symbol_id(pair.first) + "] = " + code_for_parse_action(pair.second) + ",") + "\n";
                        return result + "},\n";
                    }), "\n")),
                    "};"
                });
            }

            string parser_export() {
                return "EXPORT_PARSER(ts_parser_" + name + ");";
            }
        };

        string c_code(string name,
                      const ParseTable &parse_table,
                      const LexTable &lex_table,
                      const map<rules::Symbol, string> &symbol_names) {
            return CCodeGenerator(name, parse_table, lex_table, symbol_names).code();
        }
    }
}