#include "compiler/generate_code/helpers.h"

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

        string escape_string(string input) {
            str_replace(input, "\"", "\\\"");
            return input;
        }
    }
}