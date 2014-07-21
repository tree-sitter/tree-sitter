#ifndef COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_

#include <utility>
#include "compiler/prepare_grammar/interned_grammar.h"

namespace tree_sitter {

class SyntaxGrammar;
class LexicalGrammar;

namespace prepare_grammar {

std::pair<SyntaxGrammar, LexicalGrammar> extract_tokens(
    const InternedGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
