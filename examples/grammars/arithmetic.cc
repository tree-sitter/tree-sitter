#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;
    using std::string;

    static rule_ptr infix_op(string op, int precedence) {
        return prec(precedence, seq({
            sym("expression"),
            str(op),
            sym("expression") }));
    }

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

        { "sum", infix_op("+", 1) },
        { "difference", infix_op("-", 1) },
        { "product", infix_op("*", 2) },
        { "quotient", infix_op("/", 2) },
        { "exponent", infix_op("^", 3) },
        { "group", seq({
            str("("),
            err(sym("expression")),
            str(")") }) },

        { "number", pattern("\\d+") },
        { "variable", pattern("\\a[\\w_]*") },
    });
}
