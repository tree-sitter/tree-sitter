#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;

    extern const Grammar javascript({
        { "program", repeat(sym("statement")) },

        // Statements
        { "statement", choice({
            sym("comment"),
            sym("statement_block"),
            sym("if_statement"),
            sym("switch_statement"),
            sym("for_statement"),
            sym("break_statement"),
            sym("var_declaration"),
            sym("return_statement"),
            sym("delete_statement"),
            sym("expression_statement") }) },
        { "statement_block", in_braces(err(repeat(sym("statement")))) },
        { "for_statement", seq({
            keyword("for"),
            in_parens(seq({
                choice({
                    sym("var_declaration"),
                    sym("expression_statement") }),
                sym("expression_statement"),
                err(sym("expression")) })),
            sym("statement") }) },
        { "if_statement", seq({
            keyword("if"),
            in_parens(err(sym("expression"))),
            sym("statement"),
            optional(prec(1, seq({
                keyword("else"),
                sym("statement") }))) }) },
        { "switch_statement", seq({
            keyword("switch"),
            in_parens(err(sym("expression"))),
            in_braces(repeat(sym("switch_case"))) }) },
        { "switch_case", seq({
            choice({
                seq({
                    keyword("case"),
                    sym("expression") }),
                keyword("default") }),
            str(":"),
            repeat(sym("statement")) }) },
        { "break_statement", seq({
            keyword("break"),
            sym("_terminator") }) },
        { "var_declaration", seq({
            keyword("var"),
            choice({
                sym("assignment"),
                sym("identifier") }),
            sym("_terminator") }) },
        { "expression_statement", seq({
            err(sym("expression")),
            sym("_terminator") }) },
        { "return_statement", seq({
            keyword("return"),
            optional(sym("expression")),
            sym("_terminator") }) },
        { "delete_statement", seq({
            keyword("delete"),
            sym("property_access"),
            sym("_terminator") }) },

        // Expressions
        { "expression", choice({
            sym("function_expression"),
            sym("function_call"),
            sym("property_access"),
            sym("assignment"),
            sym("ternary"),
            sym("math_op"),
            sym("bool_op"),
            sym("object"),
            sym("array"),
            sym("regex"),
            sym("string"),
            sym("number"),
            sym("true"),
            sym("false"),
            sym("null"),
            sym("identifier"),
            in_parens(sym("expression")) }) },
        { "math_op", choice({
            prefix_op("+", "expression", 3),
            prefix_op("-", "expression", 3),
            infix_op("*", "expression", 2),
            infix_op("/", "expression", 2),
            infix_op("+", "expression", 1),
            infix_op("-", "expression", 1) }) },
        { "bool_op", choice({
            infix_op("||", "expression", 1),
            infix_op("&&", "expression", 2),
            infix_op("===", "expression", 3),
            infix_op("==", "expression", 3),
            infix_op("<=", "expression", 3),
            infix_op("<", "expression", 3),
            infix_op(">=", "expression", 3),
            infix_op(">", "expression", 3),
            prefix_op("!", "expression", 4) }) },
        { "ternary", seq({
            sym("expression"),
            str("?"),
            sym("expression"),
            str(":"),
            sym("expression") }) },
        { "assignment", prec(-1, seq({
            choice({
                sym("identifier"),
                sym("property_access") }),
            str("="),
            sym("expression") })) },
        { "function_expression", seq({
            keyword("function"),
            optional(sym("identifier")),
            sym("formal_parameters"),
            sym("statement_block") }) },
        { "function_call", seq({
            sym("expression"),
            in_parens(comma_sep(err(sym("expression")))) }) },
        { "property_access", seq({
            sym("expression"),
            choice({
                seq({
                    str("."),
                    sym("identifier") }),
                in_brackets(sym("expression")) }) }) },
        { "formal_parameters", in_parens(comma_sep(sym("identifier"))) },

        // Literals
        { "comment", pattern("//[^\n]*") },
        { "object", in_braces(comma_sep(err(seq({
                choice({ sym("string"), sym("identifier") }),
                str(":"),
                sym("expression") })))) },
        { "array", in_brackets(comma_sep(err(sym("expression")))) },
        { "_terminator", pattern("[;\n]") },
        { "regex", token(delimited("/")) },
        { "string", token(choice({
            delimited("\""),
            delimited("'") })) },
        { "identifier", pattern("[\\a_$][\\w_$]*") },
        { "number", pattern("\\d+(\\.\\d+)?") },
        { "null", keyword("null") },
        { "true", keyword("true") },
        { "false", keyword("false") },
    });
}
