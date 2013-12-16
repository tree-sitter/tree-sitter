#include "arithmetic.h"
#include "rules.h"

using namespace tree_sitter;
using namespace tree_sitter::rules;

namespace test_grammars {
    Grammar arithmetic() {
        return Grammar({
            { "expression", choice({
                seq({
                    sym("term"),
                    sym("plus"),
                    sym("term") }),
                sym("term") }) },
            { "term", choice({
                seq({
                    sym("factor"),
                    sym("times"),
                    sym("factor") }),
                sym("factor") }) },
            { "factor", choice({
                sym("variable"),
                sym("number"),
                seq({
                    sym("left_paren"),
                    sym("expression"),
                    sym("right_paren") }) }) },
            { "number", pattern("\\d+") },
            { "variable", pattern("\\w+") },
            { "plus", str("+") },
            { "times", str("*") },
            { "left_paren", str("(") },
            { "right_paren", str(")") }
        });
    }
}
