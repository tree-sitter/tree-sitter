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
                { "_terminator", choice({
                    str(";"),
                    str("\n") }) },
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
                    sym("literal"),
                    sym("identifier") }) },
                { "function_expression", seq({
                    sym("_function"),
                    sym("identifier"),
                    sym("formal_parameters"),
                    sym("statement_block") }) },
                { "function_call", seq({
                    sym("identifier"),
                    str("("),
                    comma_sep(sym("expression")),
                    str(")") }) }, 
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
                        sym("string"),
                        str(":"),
                        sym("expression") }))),
                    str("}"), }) },
                { "array", seq({
                    str("["),
                    comma_sep(err(sym("expression"))),
                    str("]") }) },

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
