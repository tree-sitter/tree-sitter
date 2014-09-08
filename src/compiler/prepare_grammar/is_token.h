#ifndef COMPILER_PREPARE_GRAMMAR_IS_TOKEN_H_
#define COMPILER_PREPARE_GRAMMAR_IS_TOKEN_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace prepare_grammar {

bool is_token(const rules::rule_ptr &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_IS_TOKEN_H_
