#ifndef COMPILER_PREPARE_GRAMMAR_EXTRACT_SIMPLE_ALIASES_H_
#define COMPILER_PREPARE_GRAMMAR_EXTRACT_SIMPLE_ALIASES_H_

#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include <unordered_map>

namespace tree_sitter {

struct SyntaxGrammar;
struct LexicalGrammar;

namespace prepare_grammar {

std::unordered_map<rules::Symbol, rules::Alias>
extract_simple_aliases(SyntaxGrammar *, LexicalGrammar *);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXTRACT_SIMPLE_ALIASES_H_
