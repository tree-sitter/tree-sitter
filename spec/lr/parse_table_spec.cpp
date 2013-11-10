#include "spec_helper.h"

Describe(parse_table_construction) {
    Grammar grammar = Grammar(
        {
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
            rules::choice({
                rules::seq({
                    rules::sym("term"),
                    rules::sym("plus"),
                    rules::sym("term") }),
                rules::sym("term") }),
            rules::choice({
                rules::seq({
                    rules::sym("factor"),
                    rules::sym("times"),
                    rules::sym("factor") }),
                rules::sym("factor") }),
            rules::choice({
                rules::sym("variable"),
                rules::sym("number"),
                rules::seq({
                    rules::sym("left_paren"),
                    rules::sym("expression"),
                    rules::sym("right_paren") }) }),
            rules::pattern("\\d+"),
            rules::pattern("\\w+"),
            rules::str("+"),
            rules::str("*"),
            rules::str("("),
            rules::str(")")
        }
    );
};
