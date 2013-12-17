#include "c_code.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::string;
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
        
        string indent(std::string input) {
            string tab = "    ";
            str_replace(input, "\n", "\n" + tab);
            return tab + input;
        }
        
        string _switch(string condition, string body) {
            return "switch (" + condition + ") {\n" +
            indent(body) +
            "}";
        }
        
        string _case(string value, string body) {
            return "case " + value + ":\n" +
            indent(body) + "\n";
        }

        string _default(string body) {
            return "default:\n" +
            indent(body) + "\n";
        }
        
        class CCodeGenerator {
            const Grammar grammar;
            const ParseTable parse_table;
            const unordered_map<string, size_t> symbol_ids;
        public:
            static unordered_map<string, size_t> get_symbol_ids(vector<string> rule_names) {
                size_t i = 0;
                unordered_map<string, size_t> result;
                for (string name : rule_names) {
                    result[name] = i;
                    i++;
                }
                result[ParseTable::END_OF_INPUT] = i;
                return result;
            }
            
            CCodeGenerator(const Grammar &grammar, const ParseTable &parse_table) :
                grammar(grammar),
                parse_table(parse_table),
                symbol_ids(get_symbol_ids(grammar.rule_names()))
                {}
            
            string symbol_id(string symbol_name) {
                return "ts_symbol_type_" + symbol_name;
            }
            
            string code_for_actions(const unordered_set<ParseAction> &actions) {
                auto action = *actions.begin();
                switch (action.type) {
                    case ParseActionTypeAccept:
                        return "ACCEPT();";
                    case ParseActionTypeShift:
                        return "SHIFT(" + std::to_string(action.state_index) + ");";
                    case ParseActionTypeReduce:
                        return "REDUCE(" + symbol_id(action.symbol_name) + ", " + std::to_string(action.child_symbol_count) + ");";
                    default:
                        return "";
                }
            }
            
            string switch_on_lookahead(const ParseState &parse_state) {
                string body = "";
                for (auto pair : parse_state.actions)
                    body += _case(symbol_id(pair.first), code_for_actions(pair.second));
                body += _default("ERROR();");
                return _switch("LOOKAHEAD()", body);
            }
            
            string switch_on_current_state(const ParseTable &parse_table) {
                string body = "";
                for (int i = 0; i < parse_table.states.size(); i++)
                    body += _case(std::to_string(i), switch_on_lookahead(parse_table.states[i]));
                body += _default("ERROR();");
                return _switch("PARSE_STATE()", body);
            }
            
            string symbol_enum() {
                string result = "typedef enum {\n";
                for (string rule_name : grammar.rule_names())
                    result += indent(symbol_id(rule_name)) + ",\n";
                result += indent(symbol_id(ParseTable::END_OF_INPUT));
                return result + "\n"
                "} ts_symbol_type;\n";
            }
            
            string parse_function() {
                return 
                "TSTree ts_parse_arithmetic(const char *input) {\n" +
                indent("START_PARSER();") + "\n" +
                indent(switch_on_current_state(parse_table)) + "\n" +
                indent("FINISH_PARSER();") + "\n"
                "}";
            }
            
            string code() {
                return 
                "#include \"runtime.h\"\n"
                "#include <stdlib.h>\n"
                "\n\n" +
                symbol_enum() +
                "\n\n" +
                parse_function() +
                "\n";
            }
        };
        
        string c_code(const Grammar &grammar, const ParseTable &parse_table) {
            return CCodeGenerator(grammar, parse_table).code();
        }
    }
}