#ifndef COMPILER_GENERATE_CODE_HELPERS_H_
#define COMPILER_GENERATE_CODE_HELPERS_H_

#include <string>
#include <vector>

namespace tree_sitter {
    using std::string;
    using std::vector;

    namespace generate_code {
        string indent(string input);
        string join(vector<string> lines, string separator);
        string join(vector<string> lines);
        string escape_string(string input);
    }
}

#endif  // COMPILER_GENERATE_CODE_HELPERS_H_
