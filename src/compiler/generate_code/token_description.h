#ifndef COMPILER_GENERATE_CODE_TOKEN_DESCRIPTION_H_
#define COMPILER_GENERATE_CODE_TOKEN_DESCRIPTION_H_

#include <string>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace generate_code {
        std::string token_description(const rules::rule_ptr &);
    }
}

#endif  // COMPILER_GENERATE_CODE_TOKEN_DESCRIPTION_H_