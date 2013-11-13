#include "arithmetic.h"
#include "rules.h"

using namespace tree_sitter;
using namespace tree_sitter::rules;

namespace test_grammars {
    Grammar arithmetic() {
        return Grammar({
            "expression",
            "term",
            "factor",
            "number",
            "variable",
            "plus",
            "times",
            "left_paren",
            "right_paren"
        }, {
            choice({
                seq({
                    sym("term"),
                    sym("plus"),
                    sym("term") }),
                sym("term") }),
            choice({
                seq({
                    sym("factor"),
                    sym("times"),
                    sym("factor") }),
                sym("factor") }),
            choice({
                sym("variable"),
                sym("number"),
                seq({
                    sym("left_paren"),
                    sym("expression"),
                    sym("right_paren") }) }),
            pattern("\\d+"),
            pattern("\\w+"),
            str("+"),
            str("*"),
            str("("),
            str(")")
        });
    }
}
