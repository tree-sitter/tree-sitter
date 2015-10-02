#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InitialSyntaxGrammar;

SyntaxGrammar flatten_grammar(const InitialSyntaxGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter
