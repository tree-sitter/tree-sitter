#ifndef COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_
#define COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_

#include <string>
#include <utility>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace prepare_grammar {

std::pair<rule_ptr, const GrammarError *> parse_regex(const std::string &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_
