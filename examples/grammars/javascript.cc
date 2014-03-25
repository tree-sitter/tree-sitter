#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace examples {
        using namespace tree_sitter::rules;

        static rule_ptr comma_sep(const rule_ptr &element) {
            return choice({
                seq({
                    element,
                    repeat(seq({ str(","), element })),
                }),
                blank(),
            });
        }

        Grammar javascript() {
            return Grammar({
                { "program", repeat(sym("statement")) },
                { "_terminator", choice({
                    str(";"),
                    str("\n") }) },
                { "statement", choice({
                    sym("if_statement"),
                    seq({ sym("assignment"), sym("_terminator") }),
                    seq({ sym("expression"), sym("_terminator") }) }) },
                { "if_statement", seq({
                    sym("_IF"),
                    str("("),
                    sym("expression"),
                    str(")"),
                    sym("statement_block") }) },
                { "statement_block", seq({
                    str("{"),
                    repeat(sym("statement")),
                    str("}") }) },
                { "assignment", seq({
                    sym("_VAR"),
                    sym("identifier"),
                    str("="),
                    sym("expression") })},
                { "expression", choice({
                    sym("literal"),
                    sym("identifier") }) },
                { "literal", choice({
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
                        sym("expression") }))),
                    str("}"), }) },
                { "array", seq({
                    str("["),
                    comma_sep(err(sym("expression"))),
                    str("]") }) },
                { "_VAR", str("var") },
                { "_IF", str("if") },
                { "string", pattern("\"([^\"]|\\\\\")+\"") },
                { "identifier", pattern("[\\w_$]+") },
                { "number", pattern("\\d+(.\\d+)?") },
                { "null", str("null") },
                { "true", str("true") },
                { "false", str("false") },
            });
        }
    }
}
