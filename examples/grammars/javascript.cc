#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;

    static rule_ptr delimited(std::string delimiter) {
        return seq({
            str(delimiter),
            pattern("([^" + delimiter + "]|\\\\" + delimiter + ")+"),
            str(delimiter)
        });
    }

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
            sym("_for"),
            in_parens(seq({
                choice({
                    sym("var_declaration"),
                    sym("expression_statement") }),
                sym("expression_statement"),
                err(sym("expression")) })),
            sym("statement") }) },
        { "if_statement", seq({
            sym("_if"),
            in_parens(err(sym("expression"))),
            sym("statement"),
            optional(prec(1, seq({
                sym("_else"),
                sym("statement") }))) }) },
        { "switch_statement", seq({
            sym("_switch"),
            in_parens(err(sym("expression"))),
            in_braces(repeat(sym("switch_case"))) }) },
        { "switch_case", seq({
            choice({
                seq({
                    sym("_case"),
                    sym("expression") }),
                sym("_default") }),
            str(":"),
            repeat(sym("statement")) }) },
        { "break_statement", seq({
            sym("_break"),
            sym("_terminator") }) },
        { "var_declaration", seq({
            sym("_var"),
            choice({
                sym("assignment"),
                sym("identifier") }),
            sym("_terminator") }) },
        { "expression_statement", seq({
            err(sym("expression")),
            sym("_terminator") }) },
        { "return_statement", seq({
            sym("_return"),
            optional(sym("expression")),
            sym("_terminator") }) },
        { "delete_statement", seq({
            sym("_delete"),
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
            infix(2, "*"),
            infix(2, "/"),
            infix(1, "+"),
            infix(1, "-") }) },
        { "bool_op", choice({
            infix(3, "&&"),
            infix(2, "||"),
            infix(2, "==="),
            infix(2, "=="),
            infix(2, "<="),
            infix(4, "<"),
            infix(2, ">="),
            infix(2, ">"),
            prefix(4, "!") }) },
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
            sym("_function"),
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
        { "object", in_braces(comma_sep(err(seq({
                choice({ sym("string"), sym("identifier") }),
                str(":"),
                sym("expression") })))) },
        { "array", in_brackets(comma_sep(err(sym("expression")))) },

        // Keywords
        { "_delete", str("delete") },
        { "_return", str("return") },
        { "_break", str("break") },
        { "_case", str("case") },
        { "_default", str("default") },
        { "_else", str("else") },
        { "_for", str("for") },
        { "_function", str("function") },
        { "_if", str("if") },
        { "_switch", str("switch") },
        { "_var", str("var") },
        { "null", str("null") },
        { "true", str("true") },
        { "false", str("false") },

        { "comment", pattern("//[^\n]*") },
        { "_terminator", pattern("[;\n]") },
        { "regex", token(delimited("/")) },
        { "string", token(choice({
            delimited("\""),
            delimited("'") })) },
        { "identifier", pattern("[\\a_$][\\w_$]*") },
        { "number", pattern("\\d+(\\.\\d+)?") },
    });
}
