#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

extern const Grammar json = Grammar({
    { "_value", choice({
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
        sym("_value") })))) },
    { "array", in_brackets(comma_sep(err(sym("_value")))) },
    { "string", pattern("\"([^\"]|\\\\\")*\"") },
    { "number", pattern("\\d+(\\.\\d+)?") },
    { "null", str("null") },
    { "true", str("true") },
    { "false", str("false") },
}).ubiquitous_tokens({
    pattern("\\s"),
});

}  // namespace tree_sitter_examples
