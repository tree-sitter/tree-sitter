#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

extern const Grammar arithmetic = Grammar({
  { "program", sym("_expression") },

  { "_expression", choice({
    sym("sum"),
    sym("difference"),
    sym("product"),
    sym("quotient"),
    sym("exponent"),
    sym("group"),
    sym("number"),
    sym("variable") }) },

  { "sum", infix_op("+", "_expression", 1) },

  { "difference", infix_op("-", "_expression", 1) },

  { "product", infix_op("*", "_expression", 2) },

  { "quotient", infix_op("/", "_expression", 2) },

  { "exponent", infix_op("^", "_expression", 3) },

  { "group", in_parens(err(sym("_expression"))) },

  { "number", pattern("\\d+") },

  // [a-ZA-Zα-ω]+\d*
  { "variable", pattern("[a-zA-Z\u03b1-\u03c9]+\\d*") },

  { "comment", pattern("#.*") },
}).extra_tokens({
  sym("comment"),
  pattern("\\s"),
});

}  // namespace tree_sitter_examples
