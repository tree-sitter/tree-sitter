#ifndef COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_
#define COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_

#include <string>
#include <utility>
#include "compiler/rule.h"
#include "compiler/compile_error.h"

namespace tree_sitter {
namespace prepare_grammar {

std::pair<rules::Rule, CompileError> parse_regex(const std::string &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_PARSE_REGEX_H_
