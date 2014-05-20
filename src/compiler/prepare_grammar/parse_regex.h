#ifndef COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_
#define COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_

#include "tree_sitter/compiler.h"
#include <string>
#include <utility>

namespace tree_sitter {
    namespace prepare_grammar {
        std::pair<rules::rule_ptr, const GrammarError *>
        parse_regex(const std::string &);
    }
}


#endif  // COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_