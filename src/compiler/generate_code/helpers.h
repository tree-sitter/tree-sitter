#ifndef COMPILER_GENERATE_CODE_HELPERS_H_
#define COMPILER_GENERATE_CODE_HELPERS_H_

#include <string>
#include <vector>

namespace tree_sitter {
    namespace generate_code {
        std::string indent(std::string input);
        std::string join(std::vector<std::string> lines, std::string separator);
        std::string join(std::vector<std::string> lines);
        std::string character_code(char character);
    }
}

#endif  // COMPILER_GENERATE_CODE_HELPERS_H_
