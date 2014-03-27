#include "compiler/generate_code/helpers.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
    using std::string;
    using std::vector;
    
    namespace generate_code {
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
            util::str_replace(&input, "\n", "\n" + tab);
            return tab + input;
        }
        
        string character_code(char character) {
            switch (character) {
                case '\0':
                    return "\\0";
                case '"':
                    return "\\\"";
                case '\n':
                    return "\\n";
                case '\\':
                    return "\\\\";
                default:
                    return string() + character;
            }
        }
    }
}