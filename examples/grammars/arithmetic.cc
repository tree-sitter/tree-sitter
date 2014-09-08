#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

using tree_sitter::Grammar;
using namespace tree_sitter::rules;

extern const Grammar arithmetic = Grammar({
    { "expression", choice({
      sym("sum"),
      sym("difference"),
      sym("product"),
      sym("quotient"),
      sym("exponent"),
      sym("group"),
      sym("number"),
      sym("variable") }) },

    { "sum", infix_op("+", "expression", 1) },
    { "difference", infix_op("-", "expression", 1) },
    { "product", infix_op("*", "expression", 2) },
    { "quotient", infix_op("/", "expression", 2) },
    { "exponent", infix_op("^", "expression", 3) },
    { "group", in_parens(err(sym("expression"))) },

    { "number", pattern("\\d+") },
    { "variable", pattern("\\a[\\w_]*") },

    { "comment", pattern("#.*") },
}).ubiquitous_tokens({
    sym("comment"),
    pattern("\\s"),
});

}  // namespace tree_sitter_examples
