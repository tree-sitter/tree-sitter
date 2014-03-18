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
        public:
            CCodeGenerator(string name, const ParseTable &parse_table, const LexTable &lex_table) :
                name(name),
                parse_table(parse_table),
                lex_table(lex_table)
                {}

            string symbol_id(rules::Symbol symbol) {
                if (symbol.is_built_in()) {
                    if (symbol == rules::ERROR)
                        return "ts_builtin_sym_error";
                    else
                        return "ts_builtin_sym_end";
                } else if (symbol.is_auxiliary()) {
                    return "ts_aux_sym_" + symbol.name;
                } else {
                    return "ts_sym_" + symbol.name;
                }
            }

            string character_code(char character) {
                switch (character) {
                    case '\0':
                        return "\\0";
                    case '"':
                        return "\\\"";
                    case '\\':
                        return "\\\\";
                    default:
                        return string() + character;
                }
            }

            string condition_for_character_range(const rules::CharacterRange &range) {
                string lookahead("LOOKAHEAD_CHAR()");
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

            string collapse_flags(vector<bool> flags) {
                string result;
                bool started = false;
                for (auto flag : flags) {
                    if (started) result += ", ";
                    result += (flag ? "1" : "0");
                    started = true;
                }
                return result;
            }

            string code_for_parse_actions(const rules::Symbol &symbol, const set<ParseAction> &actions) {
                string sym_id = symbol_id(symbol);
                auto action = actions.begin();
                switch (action->type) {
                    case ParseActionTypeAccept:
                        return "ACCEPT_INPUT(" + sym_id + ")";
                    case ParseActionTypeShift:
                        return "SHIFT(" + sym_id + ", " + to_string(action->state_index) + ")";
                    case ParseActionTypeReduce:
                        return "REDUCE(" +
                            sym_id + ", " +
                            symbol_id(action->symbol) + ", " +
                            to_string(action->child_flags.size()) + ", " +
                            "COLLAPSE({" + collapse_flags(action->child_flags) + "}))";
                    default:
                        return "";
                }
            }

            string parse_error_call(const set<rules::Symbol> &expected_inputs) {
                string result = "PARSE_ERROR(" + to_string(expected_inputs.size()) + ", EXPECT({";
                bool started = false;
                for (auto &symbol : expected_inputs) {
                    if (started) result += ", ";
                    started = true;
                    result += symbol_id(symbol);
                }
                result += "}));";
                return result;
            }

            string code_for_lex_actions(const set<LexAction> &actions,
                                        const set<rules::CharacterSet> &expected_inputs) {
                auto action = actions.begin();
                if (action == actions.end()) {
                    return "LEX_ERROR();";
                } else {
                    switch (action->type) {
                        case LexActionTypeAdvance:
                            return "ADVANCE(" + to_string(action->state_index) + ");";
                        case LexActionTypeAccept:
                            return "ACCEPT_TOKEN(" + symbol_id(action->symbol) + ");";
                        case LexActionTypeError:
                            return "";
                    }
                }
            }

            string switch_on_lookahead_char(const LexState &parse_state) {
                string result = "";
                auto expected_inputs = parse_state.expected_inputs();
                for (auto pair : parse_state.actions)
                    result += _if(condition_for_character_rule(pair.first),
                                  code_for_lex_actions(pair.second, expected_inputs));
                result += code_for_lex_actions(parse_state.default_actions, expected_inputs);
                return result;
            }

            string switch_on_lex_state() {
                string body = "";
                for (size_t i = 0; i < lex_table.states.size(); i++)
                    body += _case(std::to_string(i), switch_on_lookahead_char(lex_table.states[i]));
                body += _case("ts_lex_state_error", switch_on_lookahead_char(lex_table.error_state));
                body += _default("LEX_PANIC();");
                return _switch("LEX_STATE()", body);
            }
            
            string symbol_count() {
                return "#define TS_SYMBOL_COUNT " + to_string(parse_table.symbols.size());
            }

            string symbol_enum() {
                string result = "enum {\n";
                for (auto symbol : parse_table.symbols)
                    if (!symbol.is_built_in())
                        result += indent(symbol_id(symbol)) + ",\n";
                return result + "};";
            }

            string rule_names_list() {
                string result = "SYMBOL_NAMES = {\n";
                for (auto symbol : parse_table.symbols)
                    if (!symbol.is_built_in())
                        result += indent(string("\"") + symbol.name) + "\",\n";
                return result + "};";
            }

            string includes() {
                return "#include \"tree_sitter/parser.h\"";
            }

            string recover_case(ParseStateId state, set<rules::Symbol> symbols) {
                string result = "RECOVER(" +
                    to_string(state) + ", " +
                    to_string(symbols.size()) + ", EXPECT({";
                bool started = false;
                for (auto &symbol : symbols) {
                    if (started) {
                        result += ", ";
                    }
                    result += symbol_id(symbol);
                    started = true;
                }
                return result + "}));";
            }

            string recover_function() {
                string cases;
                for (auto &pair : parse_table.error_table) {
                    auto pair_for_state = pair.second;
                    cases += _case(to_string(pair.first),
                                   recover_case(pair_for_state.first, pair_for_state.second));
                }
                cases += _default(recover_case(0, set<rules::Symbol>()));

                return join({
                    "RECOVER_FN() {",
                    indent(_switch("state", cases)),
                    "}"
                });
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

            string parse_table_row_for_state(const ParseState &state) {
                string result("SET_LEX_STATE(" + to_string(state.lex_state_id) + ");");
                for (auto &pair : state.actions) {
                    result += "\n" + code_for_parse_actions(pair.first, pair.second);
                }
                return result;
            }

            string parse_table_function() {
                size_t state_id = 0;
                return join({
                    "PARSE_TABLE() {",
                    indent(join({
                        "START_TABLE(" + to_string(parse_table.states.size()) + ")",
                        join(map_to_string<ParseState>(parse_table.states, [&](ParseState state) -> string {
                            return join({
                                "STATE(" + to_string(state_id++) + ");",
                                parse_table_row_for_state(state),
                                "END_STATE();"
                            });
                        }), "\n\n"),
                        "END_TABLE();",
                    }, "\n\n")),
                    "}"
                });
            }

            string parser_export() {
                return "EXPORT_PARSER(ts_parser_" + name + ");";
            }

            string code() {
                return join({
                    includes(),
                    symbol_count(),
                    symbol_enum(),
                    rule_names_list(),
                    lex_function(),
                    parse_table_function(),
                    parser_export(),
                }, "\n\n") + "\n";
            }
        };

        string c_code(string name, const ParseTable &parse_table, const LexTable &lex_table) {
            return CCodeGenerator(name, parse_table, lex_table).code();
        }
    }
}