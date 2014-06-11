#include "compiler/util/string_helpers.h"
#include <vector>

namespace tree_sitter {
    using std::string;
    using std::vector;
    using std::set;

    namespace util {
        void str_replace(string *input, const string &search, const string &replace) {
            size_t pos = 0;
            while (1) {
                pos = input->find(search, pos);
                if (pos == string::npos) break;
                input->erase(pos, search.length());
                input->insert(pos, replace);
                pos += replace.length();
            }
        }

        string escape_string(string input) {
            str_replace(&input, "\"", "\\\"");
            str_replace(&input, "\n", "\\n");
            return input;
        }
        
        string escape_char(char character) {
            switch (character) {
                case '\0':
                    return "\\0";
                case '"':
                    return "\\\"";
                case '\'':
                    return "\\'";
                case '\n':
                    return "\\n";
                case '\r':
                    return "\\r";
                case '\t':
                    return "\\t";
                case '\\':
                    return "\\\\";
                default:
                    return string() + character;
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
            util::str_replace(&input, "\n", "\n" + tab);
            return tab + input;
        }
    }
}
