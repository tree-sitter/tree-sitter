#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;

    static rule_ptr comma_sep(const rule_ptr &rule) {
        return choice({
            seq({ rule, repeat(seq({ str(","), rule })) }),
            blank(),
        });
    }

    extern const Grammar json({
        { "value", choice({
            sym("object"),
            sym("array"),
            sym("string"),
            sym("number"),
            sym("true"),
            sym("false"),
            sym("null"), }) },
        { "object", seq({
            str("{"),
            comma_sep(err(seq({
                sym("string"),
                str(":"),
                sym("value") }))),
            str("}"), }) },
        { "array", seq({
            str("["),
            comma_sep(err(sym("value"))),
            str("]"), }) },
        { "string", pattern("\"([^\"]|\\\\\")+\"") },
        { "number", pattern("\\d+(.\\d+)?") },
        { "null", str("null") },
        { "true", str("true") },
        { "false", str("false") },
    });
}
