#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_

#include <utility>
#include "compiler/rule.h"
#include "compiler/compile_error.h"

namespace tree_sitter {
namespace prepare_grammar {

struct ExpandTokenResult {
  rules::Rule rule;
  CompileError error;

  ExpandTokenResult(const rules::Rule &rule) : rule(rule) {}
  ExpandTokenResult(const CompileError &error) : error(error) {}
};

ExpandTokenResult expand_token(const rules::Rule &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
