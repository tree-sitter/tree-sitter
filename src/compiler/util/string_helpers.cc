#include "compiler/util/string_helpers.h"

namespace tree_sitter {
    using std::string;

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
    }
}