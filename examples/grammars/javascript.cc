#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace examples {
        using namespace tree_sitter::rules;

        static rule_ptr optional(const rule_ptr &rule) {
            return choice({ rule, blank() });
        }
        
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
                { "statement", choice({
                    sym("statement_block"),
                    sym("if_statement"),
                    seq({ sym("assignment"), sym("_terminator") }),
                    seq({ sym("expression"), sym("_terminator") }) }) },
                { "if_statement", seq({
                    sym("_if"),
                    str("("),
                    sym("expression"),
                    str(")"),
                    sym("statement"),
                    optional(seq({
                        sym("_else"),
                        sym("statement") })) }) },
                { "statement_block", seq({
                    str("{"),
                    repeat(sym("statement")),
                    str("}") }) },
                { "assignment", seq({
                    sym("_var"),
                    sym("identifier"),
                    str("="),
                    sym("expression") })},
                { "expression", choice({
                    sym("function_expression"),
                    sym("function_call"),
                    sym("property_access"),
                    sym("literal"),
                    sym("identifier") }) },
                { "function_expression", seq({
                    sym("_function"),
                    optional(sym("identifier")),
                    sym("formal_parameters"),
                    sym("statement_block") }) },
                { "function_call", seq({
                    sym("expression"),
                    str("("),
                    comma_sep(sym("expression")),
                    str(")") }) }, 
                { "property_access", seq({
                    sym("expression"),
                    str("."),
                    sym("identifier") }) },
                { "formal_parameters", seq({
                    str("("),
                    comma_sep(sym("identifier")),
                    str(")") })}, 
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
                        choice({ sym("string"), sym("identifier") }),
                        str(":"),
                        sym("expression") }))),
                    str("}"), }) },
                { "array", seq({
                    str("["),
                    comma_sep(err(sym("expression"))),
                    str("]") }) },

                { "_terminator", choice({
                    str(";"),
                    str("\n") }) },
                { "_var", str("var") },
                { "_if", str("if") },
                { "_function", str("function") },
                { "_else", str("else") }, 

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
