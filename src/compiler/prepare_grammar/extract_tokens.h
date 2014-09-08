#ifndef COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_

#include <utility>
#include "tree_sitter/compiler.h"

namespace tree_sitter {

class Grammar;
class SyntaxGrammar;
class LexicalGrammar;

namespace prepare_grammar {

std::tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *> extract_tokens(
    const Grammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
