#include "c_code.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using namespace tree_sitter::lr;

namespace tree_sitter {
    namespace code_gen {
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
        
        string indent(string input) {
            string tab = "    ";
            str_replace(input, "\n", "\n" + tab);
            return tab + input;
        }
        
        string _switch(string condition, string body) {
            return "switch (" + condition + ") {\n" +
            indent(body) + "\n"
            "}";
        }
        
        string _case(string value, string body) {
            return "case " + value + ":\n" +
            indent(body) + "\n";
        }

        string _default(string body) {
            return "default:\n" +
            indent(body);
        }
        
        string _if(string condition, string body) {
            return string("if (") + condition + ")\n" +
            indent(body) + "\n";
        }
        
        class CCodeGenerator {
            const Grammar grammar;
            const ParseTable parse_table;
            const LexTable lex_table;
        public:
            CCodeGenerator(const Grammar &grammar, const ParseTable &parse_table, const LexTable &lex_table) :
                grammar(grammar),
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
            
            string code_for_parse_actions(const unordered_set<ParseAction> &actions) {
                auto action = actions.begin();
                if (action == actions.end()) {
                    return "PARSE_ERROR();";
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

            string code_for_lex_actions(const unordered_set<LexAction> &actions) {
                auto action = actions.begin();
                if (action == actions.end()) {
                    return "LEX_ERROR();";
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

            string switch_on_lookahead_sym(const ParseState &parse_state) {
                string body = "";
                for (auto pair : parse_state.actions)
                    body += _case(symbol_id(pair.first), code_for_parse_actions(pair.second));
                body += _default(code_for_parse_actions(parse_state.default_actions));
                return _switch("LOOKAHEAD_SYM()", body);
            }

            string switch_on_lookahead_char(const LexState &parse_state) {
                string result = "";
                for (auto pair : parse_state.actions)
                    result += _if(condition_for_char_match(pair.first), code_for_lex_actions(pair.second));
                result += code_for_lex_actions(parse_state.default_actions);
                return result;
            }

            string switch_on_parse_state() {
                string body = "";
                for (int i = 0; i < parse_table.states.size(); i++)
                    body += _case(std::to_string(i), switch_on_lookahead_sym(parse_table.states[i]));
                body += _default("PARSE_ERROR();");
                return _switch("PARSE_STATE()", body);
            }

            string switch_on_lex_state() {
                string body = "";
                for (int i = 0; i < lex_table.states.size(); i++)
                    body += _case(std::to_string(i), switch_on_lookahead_char(lex_table.states[i]));
                body += _default("LEX_ERROR();");
                return _switch("LEX_STATE()", body);
            }
            
            string symbol_enum() {
                string result = "typedef enum {\n";
                for (string rule_name : grammar.rule_names())
                    result += indent(symbol_id(rule_name)) + ",\n";
                result += indent(symbol_id(ParseTable::END_OF_INPUT));
                return result + "\n"
                "} ts_symbol;\n";
            }
            
            string includes() {
                return string(
                    "#include \"runtime.h\"\n"
                    "#include <stdlib.h>\n"
                    "#include <ctype.h>");
            }
            
            string parse_function() {
                return 
                "TSTree ts_parse_arithmetic(const char *input) {\n" +
                indent("START_PARSER();") + "\n" +
                indent(switch_on_parse_state()) + "\n" +
                indent("FINISH_PARSER();") + "\n"
                "}";
            }

            string lex_function() {
                return 
                "static void ts_lex(TSParser *parser) {\n" +
                indent("START_LEXER();") + "\n" +
                indent(switch_on_lex_state()) + "\n" +
                indent("FINISH_LEXER();") + "\n"
                "}";
            }
            
            string code() {
                return
                includes() + "\n\n" +
                symbol_enum() + "\n\n" +
                lex_function() + "\n\n" +
                parse_function() + "\n";
            }
        };
        
        string c_code(const Grammar &grammar, const ParseTable &parse_table, const LexTable &lex_table) {
            return CCodeGenerator(grammar, parse_table, lex_table).code();
        }
    }
}