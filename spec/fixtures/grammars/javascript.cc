#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

using tree_sitter::Grammar;
using namespace tree_sitter::rules;

static rule_ptr terminated(rule_ptr rule) {
  return seq({ rule, choice({
      sym("_line_break"),
      str(";") }) });
}

extern const Grammar javascript = Grammar({
    { "program", repeat(sym("statement")) },

    // Statements
    { "statement", choice({
        sym("statement_block"),
        sym("if_statement"),
        sym("try_statement"),
        sym("switch_statement"),
        sym("while_statement"),
        sym("for_statement"),
        sym("for_in_statement"),
        sym("break_statement"),
        sym("var_declaration"),
        sym("throw_statement"),
        sym("return_statement"),
        sym("delete_statement"),
        sym("expression_statement") }) },
    { "statement_block", in_braces(err(repeat(sym("statement")))) },
    { "for_statement", seq({
        keyword("for"),
        in_parens(err(seq({
            choice({
                sym("var_declaration"),
                sym("expression_statement") }),
            sym("expression_statement"),
                sym("expression") }))),
        sym("statement") }) },
    { "for_in_statement", seq({
        keyword("for"),
        in_parens(err(seq({
            optional(keyword("var")),
            sym("identifier"),
            keyword("in"),
            sym("expression") }))),
        sym("statement") }) },
    { "throw_statement", terminated(seq({
        keyword("throw"),
        sym("expression") })) },
    { "if_statement", seq({
        keyword("if"),
        in_parens(err(sym("expression"))),
        sym("statement"),
        optional(prec(1, seq({
            keyword("else"),
            sym("statement") }))) }) },
    { "while_statement", seq({
        keyword("while"),
        in_parens(err(sym("expression"))),
        sym("statement") }) },
    { "try_statement", seq({
        keyword("try"),
        sym("statement"),
        optional(sym("catch_clause")),
        optional(sym("finally_clause")) }) },
    { "catch_clause", seq({
        keyword("catch"),
        in_parens(err(sym("identifier"))),
        sym("statement") }) },
    { "finally_clause", seq({
        keyword("finally"),
        sym("statement") }) },
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
    { "break_statement", terminated(keyword("break")) },
    { "var_declaration", terminated(seq({
        keyword("var"),
        comma_sep(err(seq({
            sym("identifier"),
            optional(seq({
                str("="),
                sym("expression") })) }))) })) },
    { "expression_statement", terminated(err(sym("expression"))) },
    { "return_statement", terminated(seq({
        keyword("return"),
        optional(sym("expression")) })) },
    { "delete_statement", terminated(seq({
        keyword("delete"),
        sym("property_access") })) },

    // Expressions
    { "expression", choice({
        sym("function_expression"),
        sym("function_call"),
        sym("constructor_call"),
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
        sym("in_expression"),
        sym("instanceof_expression"),
        sym("typeof_expression"),
        in_parens(sym("expression")) }) },
    { "in_expression", infix_op("in", "expression", 3) },
    { "instanceof_expression", infix_op("instanceof", "expression", 3) },
    { "typeof_expression", prefix_op("typeof", "expression", 3) },
    { "math_op", choice({
        prefix_op("++", "expression", 3),
        prefix_op("--", "expression", 3),
        postfix_op("++", "expression", 3),
        postfix_op("--", "expression", 3),
        prefix_op("+", "expression", 3),
        prefix_op("-", "expression", 3),
        infix_op("*", "expression", 2),
        infix_op("/", "expression", 2),
        infix_op("&", "expression", 2),
        infix_op("|", "expression", 2),
        infix_op("^", "expression", 2),
        infix_op("+", "expression", 1),
        infix_op("-", "expression", 1) }) },
    { "bool_op", choice({
        infix_op("||", "expression", 1),
        infix_op("&&", "expression", 2),
        infix_op("===", "expression", 3),
        infix_op("==", "expression", 3),
        infix_op("!==", "expression", 3),
        infix_op("!=", "expression", 3),
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
        choice({
            str("="),
            str("+="),
            str("-="),
            str("*="),
            str("/=") }),
        sym("expression") })) },
    { "function_expression", seq({
        keyword("function"),
        optional(sym("identifier")),
        in_parens(sym("formal_parameters")),
        sym("statement_block") }) },
    { "function_call", seq({
        sym("expression"),
        in_parens(comma_sep(err(sym("expression")))) }) },
    { "constructor_call", seq({
        keyword("new"),
        sym("function_call") }) },
    { "property_access", seq({
        sym("expression"),
        prec(10, choice({
            seq({ str("."), sym("identifier") }),
            in_brackets(sym("expression")) })) }) },
    { "formal_parameters", comma_sep(sym("identifier")) },

    // Literals
    { "comment", token(choice({
        seq({
            str("/*"),
            repeat(pattern("[^*]|(*[^/])")),
            str("*/") }),
        pattern("//[^\n]*") })) },
    { "object", in_braces(comma_sep(err(seq({
        choice({ sym("string"), sym("identifier") }),
        str(":"),
        sym("expression") })))) },
    { "array", in_brackets(comma_sep(err(sym("expression")))) },
    { "regex", token(seq({ delimited("/"), optional(str("g")) })) },
    { "string", token(choice({
        delimited("\""),
        delimited("'") })) },
    { "_line_break", str("\n") },
    { "identifier", pattern("[\\a_$][\\w_$]*") },
    { "number", pattern("\\d+(\\.\\d+)?") },
    { "null", keyword("null") },
    { "true", keyword("true") },
    { "false", keyword("false") },
}).ubiquitous_tokens({
    sym("comment"),
    sym("_line_break"),
    pattern("[ \t\r]"),
});

}  // namespace tree_sitter_examples
