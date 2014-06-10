#ifndef COMPILER_PREPARE_GRAMMAR_TOKEN_DESCRIPTION_H_
#define COMPILER_PREPARE_GRAMMAR_TOKEN_DESCRIPTION_H_

#include <string>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace prepare_grammar {
        std::string token_description(const rules::rule_ptr &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_TOKEN_DESCRIPTION_H_
