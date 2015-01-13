#ifndef COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_

#include <utility>
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {

class Grammar;
class GrammarError;

namespace prepare_grammar {

std::tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *> prepare_grammar(
    const Grammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
