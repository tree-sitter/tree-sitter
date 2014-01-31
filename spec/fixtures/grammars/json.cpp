#include "test_grammars.h"
#include "rules.h"

using namespace tree_sitter;
using namespace rules;

static rule_ptr comma_sep(const rule_ptr &rule) {
    return seq({
        rule,
        choice({
            repeat(seq({ str(","), rule })),
            blank()
        })
    });
}

namespace test_grammars {
    Grammar json() {
        return Grammar({
            { "value", choice({
                sym("object"),
                sym("array"),
                sym("string"), 
                sym("number") }) },
            { "object", seq({
                str("{"),
                comma_sep(seq({
                    sym("string"),
                    str(":"),
                    sym("value") })),
                str("}"), }) },
            { "array", seq({
                str("["),
                comma_sep(sym("value")),
                str("]"), }) },
            { "string", pattern("\"[^\"]+\"") },
            { "number", pattern("\\d+") }
        });
    }
}
