#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;

    extern const Grammar arithmetic({
        { "expression", choice({
            sym("sum"),
            sym("difference"),
            sym("product"),
            sym("quotient"),
            sym("exponent"),
            sym("group"),
            sym("number"),
            sym("variable") }) },

        { "sum", infix(1, "+") },
        { "difference", infix(1, "-") },
        { "product", infix(2, "*") },
        { "quotient", infix(2, "/") },
        { "exponent", infix(3, "^") },
        { "group", in_parens(err(sym("expression"))) },

        { "number", pattern("\\d+") },
        { "variable", pattern("\\a[\\w_]*") },
    });
}
