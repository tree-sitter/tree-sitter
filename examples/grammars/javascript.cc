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
                    sym("for_statement"),
                    sym("var_declaration"),
                    sym("expression_statement") }) },
                { "expression_statement", seq({
                    sym("expression"),
                    sym("_terminator") }) },
                { "for_statement", seq({
                    sym("_for"),
                    str("("),
                    choice({
                        sym("var_declaration"),
                        sym("expression_statement"),
                    }),
                    sym("expression_statement"),
                    sym("expression"),
                    str(")"),
                    sym("statement") }) },
                { "if_statement", seq({
                    sym("_if"),
                    str("("),
                    err(sym("expression")),
                    str(")"),
                    sym("statement"),
                    optional(seq({
                        sym("_else"),
                        sym("statement") })) }) },
                { "statement_block", seq({
                    str("{"),
                    err(repeat(sym("statement"))),
                    str("}") }) },
                { "var_declaration", seq({
                    sym("_var"),
                    choice({
                        sym("assignment"),
                        sym("identifier") }),
                    sym("_terminator") }) },
                { "assignment", seq({
                    sym("identifier"),
                    str("="),
                    sym("expression") })},
                { "expression", choice({
                    sym("function_expression"),
                    sym("function_call"),
                    sym("property_access"),
                    sym("assignment"),
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
                { "_for", str("for") },
                { "_if", str("if") },
                { "_function", str("function") },
                { "_else", str("else") }, 
                { "null", str("null") },
                { "true", str("true") },
                { "false", str("false") },

                { "string", pattern("\"([^\"]|\\\\\")+\"") },
                { "identifier", pattern("[\\w_$]+") },
                { "number", pattern("\\d+(.\\d+)?") },
            });
        }
    }
}
