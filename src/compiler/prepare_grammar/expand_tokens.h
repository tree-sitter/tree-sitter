#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_

#include <utility>
#include "tree_sitter/compiler.h"

namespace tree_sitter {

class LexicalGrammar;

namespace prepare_grammar {

std::pair<LexicalGrammar, const GrammarError *> expand_tokens(
  const LexicalGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
