#ifndef COMPILER_PREPARE_GRAMMAR_NORMALIZE_RULES_H_
#define COMPILER_PREPARE_GRAMMAR_NORMALIZE_RULES_H_

#include "compiler/lexical_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

LexicalGrammar normalize_rules(const LexicalGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_NORMALIZE_RULES_H_
