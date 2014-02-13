#include "test_grammars.h"
#include "rules.h"

using namespace tree_sitter;
using namespace rules;

static rule_ptr comma_sep(const rule_ptr &rule) {
    return seq({
        rule,
        choice({
            repeat(seq({ aux_sym("comma"), rule })),
            blank(),
        }),
    });
}

namespace test_grammars {
    Grammar json() {
        return Grammar("value", {
            { "value", choice({
                sym("object"),
                sym("array"),
                sym("string"), 
                sym("number") }) },
            { "object", seq({
                aux_sym("left_brace"),
                comma_sep(seq({
                    sym("string"),
                    aux_sym("colon"),
                    sym("value") })),
                aux_sym("right_brace"), }) },
            { "array", seq({
                aux_sym("left_bracket"),
                comma_sep(sym("value")),
                aux_sym("right_bracket"), }) },
            { "string", seq({
                character('"'),
                repeat(choice({
                    pattern("[^\"]"),
                    str("\\\""),
                })),
                character('"') }) },
            { "number", pattern("\\d+") }
        }, {
            { "comma", str(",") },
            { "colon", str(":") },
            { "left_bracket", str("[") },
            { "right_bracket", str("]") },
            { "left_brace", str("{") },
            { "right_brace", str("}") },
        });
    }
}
