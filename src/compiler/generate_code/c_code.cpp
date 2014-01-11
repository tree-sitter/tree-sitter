#include "c_code.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace tree_sitter {
    namespace generate_code {
        static void str_replace(string &input, const string &search, const string &replace) {
            size_t pos = 0;
            while (1) {
                pos = input.find(search, pos);
                if (pos == string::npos) break;
                input.erase(pos, search.length());
                input.insert(pos, replace);
                pos += replace.length();
            }
        }
        
        string join(vector<string> lines, string separator) {
            string result;
            bool started = false;
            for (auto line : lines) {
                if (started) result += separator;
                started = true;
                result += line;
            }
            return result;
        }
        
        string join(vector<string> lines) {
            return join(lines, "\n");
        }
        
        string indent(string input) {
            string tab = "    ";
            str_replace(input, "\n", "\n" + tab);
            return tab + input;
        }
        
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
            const vector<string> rule_names;
            const ParseTable parse_table;
            const LexTable lex_table;
        public:
            CCodeGenerator(vector<string> rule_names, const ParseTable &parse_table, const LexTable &lex_table) :
                rule_names(rule_names),
                parse_table(parse_table),
                lex_table(lex_table)
                {}
            
            string symbol_id(string symbol_name) {
                return "ts_symbol_" + symbol_name;
            }
            
            string condition_for_char_match(const CharMatch &char_match) {
                auto value = "LOOKAHEAD_CHAR()";
                switch (char_match.type) {
                    case CharMatchTypeClass:
                        switch (char_match.value.character_class) {
                            case CharClassDigit:
                                return string("isdigit(") + value + ")";
                            case CharClassWord:
                                return string("isalnum(") + value + ")";
                        }
                    case CharMatchTypeSpecific:
                        return string(value) + " == '" + char_match.value.character + "'";
                    default:
                        return "";
                }
            }
            
            string code_for_parse_actions(const unordered_set<ParseAction> &actions, const unordered_set<string> &expected_inputs) {
                auto action = actions.begin();
                if (action == actions.end()) {
                    return parse_error_call(expected_inputs);
                } else {
                    switch (action->type) {
                        case ParseActionTypeAccept:
                            return "ACCEPT_INPUT();";
                        case ParseActionTypeShift:
                            return "SHIFT(" + to_string(action->state_index) + ");";
                        case ParseActionTypeReduce:
                            return "REDUCE(" + symbol_id(action->symbol_name) + ", " + std::to_string(action->child_symbol_count) + ");";
                        default:
                            return "";
                    }
                }
            }
            
            string parse_error_call(const unordered_set<string> &expected_inputs) {
                string result = "PARSE_ERROR(" + to_string(expected_inputs.size()) + ", EXPECT({";
                bool started = false;
                for (auto symbol_name : expected_inputs) {
                    if (started) result += ", ";
                    started = true;
                    result += "\"" + symbol_name + "\"";
                }
                result += "}));";
                return result;
            }
            
            string lex_error_call(const unordered_set<CharMatch> &expected_inputs) {
                string result = "LEX_ERROR(" + to_string(expected_inputs.size()) + ", EXPECT({";
                bool started = false;
                for (auto match : expected_inputs) {
                    if (started) result += ", ";
                    started = true;
                    result += "\"" + CharMatchToString(match) + "\"";
                }
                result += "}));";
                return result;
            }

            string code_for_lex_actions(const unordered_set<LexAction> &actions, const unordered_set<CharMatch> &expected_inputs) {
                auto action = actions.begin();
                if (action == actions.end()) {
                    return lex_error_call(expected_inputs);
                } else {
                    switch (action->type) {
                        case LexActionTypeAdvance:
                            return "ADVANCE(" + to_string(action->state_index) + ");";
                        case LexActionTypeAccept:
                            return "ACCEPT_TOKEN(" + symbol_id(action->symbol_name) + ");";
                        case LexActionTypeError:
                            return "";
                    }
                }
            }

            string code_for_parse_state(const ParseState &parse_state) {
                string body = "";
                for (auto pair : parse_state.actions)
                    body += _case(symbol_id(pair.first), code_for_parse_actions(pair.second, parse_state.expected_inputs()));
                body += _default(code_for_parse_actions(parse_state.default_actions, parse_state.expected_inputs()));
                return
                    string("SET_LEX_STATE(") + to_string(parse_state.lex_state_index) + ");\n" +
                    _switch("LOOKAHEAD_SYM()", body);
            }

            string switch_on_lookahead_char(const LexState &parse_state) {
                string result = "";
                auto expected_inputs = parse_state.expected_inputs();
                for (auto pair : parse_state.actions)
                    result += _if(condition_for_char_match(pair.first), code_for_lex_actions(pair.second, expected_inputs));
                result += code_for_lex_actions(parse_state.default_actions, expected_inputs);
                return result;
            }

            string switch_on_parse_state() {
                string body = "";
                for (int i = 0; i < parse_table.states.size(); i++)
                    body += _case(std::to_string(i), code_for_parse_state(parse_table.states[i]));
                body += _default("PARSE_PANIC();");
                return _switch("PARSE_STATE()", body);
            }

            string switch_on_lex_state() {
                string body = "";
                for (int i = 0; i < lex_table.states.size(); i++)
                    body += _case(std::to_string(i), switch_on_lookahead_char(lex_table.states[i]));
                body += _default("LEX_PANIC();");
                return _switch("LEX_STATE()", body);
            }
            
            string symbol_enum() {
                string result = "enum ts_symbol {\n";
                for (string rule_name : rule_names)
                    result += indent(symbol_id(rule_name)) + ",\n";
                result += indent(symbol_id(ParseTable::END_OF_INPUT));
                return result + "\n};";
            }

            string rule_names_list() {
                string result = "static const char *ts_symbol_names[] = {\n";
                for (string rule_name : rule_names)
                    result += indent(string("\"") + rule_name) + "\",\n";
                result += indent(string("\"") + ParseTable::END_OF_INPUT + "\"");
                return result + "\n};";
            }

            string includes() {
                return join({
                    "#include \"parser.h\"",
                    "#include <ctype.h>"
                });
            }
            
            string lex_function() {
                return join({
                    "static void ts_lex(TSParser *parser) {",
                    indent("START_LEXER();"),
                    indent(switch_on_lex_state()),
                    indent("FINISH_LEXER();"),
                    "}"
                });
            }
            
            string parse_function() {
                return join({
                    "static TSParseResult ts_parse(const char *input) {",
                    indent("START_PARSER();"),
                    indent(switch_on_parse_state()),
                    indent("FINISH_PARSER();"),
                    "}"
                });
            }
            
            string parse_config_struct() {
                return join({
                    "TSParseConfig ts_parse_config_arithmetic = {",
                    indent(".parse_fn = ts_parse,"),
                    indent(".symbol_names = ts_symbol_names"),
                    "};"
                });
            }
            
            string code() {
                return join({
                    includes(),
                    symbol_enum(),
                    rule_names_list(),
                    lex_function(),
                    parse_function(),
                    parse_config_struct(),
                }, "\n\n") + "\n";
            }
        };
        
        string c_code(const vector<string> rule_names, const ParseTable &parse_table, const LexTable &lex_table) {
            return CCodeGenerator(rule_names, parse_table, lex_table).code();
        }
    }
}