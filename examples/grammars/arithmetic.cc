#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;
    using std::string;

    static rule_ptr infix_op(string op, string rule_name) {
        return choice({
            seq({
                sym(rule_name),
                str(op),
                sym(rule_name) }),
            sym(rule_name) });
    }

    extern const Grammar arithmetic({
        { "expression", choice({
            sym("sum"),
            sym("difference") }) },
        { "_operand1", choice({
            sym("product"),
            sym("quotient") }) },
        { "_operand2", choice({
            sym("exponent") }) },
        { "_operand3", choice({
            sym("number"),
            sym("variable"),
            sym("grouping") }) },
        { "grouping", seq({
            str("("),
            err(sym("expression")),
            str(")") }) },

        { "sum", infix_op("+", "_operand1") },
        { "difference", infix_op("-", "_operand1") },
        { "product", infix_op("*", "_operand2") },
        { "quotient", infix_op("/", "_operand2") },
        { "exponent", infix_op("^", "_operand3") },

        { "number", pattern("\\d+") },
        { "variable", pattern("\\a[\\w_]*") },
    });
}
