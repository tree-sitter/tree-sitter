#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;

    extern const Grammar json({
        { "value", choice({
            sym("object"),
            sym("array"),
            sym("string"),
            sym("number"),
            sym("true"),
            sym("false"),
            sym("null"), }) },
        { "object", in_braces(comma_sep(err(seq({
            sym("string"),
            str(":"),
            sym("value") })))) },
        { "array", in_brackets(comma_sep(err(sym("value")))) },
        { "string", pattern("\"([^\"]|\\\\\")+\"") },
        { "number", pattern("\\d+(\\.\\d+)?") },
        { "null", str("null") },
        { "true", str("true") },
        { "false", str("false") },
    });
}
