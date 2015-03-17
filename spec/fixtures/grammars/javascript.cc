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

enum {
  PREC_COMMA = -1,
  PREC_ASSIGN,
  PREC_BLOCK,
  PREC_TERNARY,
  PREC_OR,
  PREC_AND,
  PREC_REL,
  PREC_ADD,
  PREC_MULT,
  PREC_TYPE,
  PREC_NOT,
  PREC_SIGN,
  PREC_INC,
  PREC_CALL,
  PREC_SHORT_NEW,
  PREC_FULL_NEW,
  PREC_MEMBER,
};

extern const Grammar javascript = Grammar({
    { "program", repeat(sym("statement")) },

    /*
     *  Statements
     */

    { "statement", choice({
        sym("expression_statement"),
        sym("var_declaration"),
        sym("statement_block"),
        sym("if_statement"),
        sym("switch_statement"),
        sym("for_statement"),
        sym("while_statement"),

        sym("for_in_statement"),
        // sym("do_statement"),

        sym("try_statement"),
        sym("return_statement"),
        sym("break_statement"),
        sym("throw_statement"),
        sym("delete_statement") }) },

    { "expression_statement", terminated(err(sym("expression"))) },

    { "var_declaration", terminated(seq({
        keyword("var"),
        comma_sep1(err(choice({
            sym("identifier"),
            sym("var_assignment") }))) })) },

    { "statement_block", left_assoc(PREC_BLOCK,
        in_braces(err(repeat(sym("statement"))))) },

    { "if_statement", right_assoc(0, seq({
        keyword("if"),
        sym("_paren_expression"),
        sym("statement"),
        optional(seq({
            keyword("else"),
            sym("statement") })) })) },

    { "switch_statement", seq({
        keyword("switch"),
        sym("_paren_expression"),
        str("{"),
        repeat(choice({ sym("case"), sym("default") })),
        str("}") }) },

    { "for_statement", seq({
        keyword("for"),
        str("("),
        choice({
            sym("var_declaration"),
            seq({ sym("expression"), str(";") }),
            str(";") }),
        optional(err(sym("expression"))), str(";"),
        optional(err(sym("expression"))),
        str(")"),
        sym("statement") }) },

    { "for_in_statement", seq({
        keyword("for"),
        str("("),
        optional(keyword("var")),
        left_assoc(PREC_REL, seq({
          sym("identifier"),
          keyword("in"),
          sym("expression") })),
        str(")"),
        sym("statement") }) },

    { "while_statement", seq({
        keyword("while"),
        sym("_paren_expression"),
        sym("statement") }) },

    // { "do_statement", seq({
        // keyword("do"),
        // sym("statement"),
        // keyword("while"),
        // sym("_paren_expression") })},

    { "try_statement", seq({
        keyword("try"),
        sym("statement_block"),
        optional(sym("catch")),
        optional(sym("finally")) }) },

    { "return_statement", terminated(seq({
        keyword("return"),
        optional(sym("expression")) })) },

    { "throw_statement", terminated(seq({
        keyword("throw"),
        sym("expression") })) },

    { "break_statement", terminated(keyword("break")) },

    { "delete_statement", terminated(seq({
        keyword("delete"),
        choice({ sym("member_access"), sym("subscript_access") }) })) },

    /*
     *  Statement components
     */

    { "case", seq({
        keyword("case"),
        sym("expression"),
        str(":"),
        repeat(sym("statement")) }) },

    { "default", seq({
        keyword("default"),
        str(":"),
        repeat(sym("statement")) }) },

    { "catch", seq({
        keyword("catch"),
        str("("),
        err(sym("identifier")),
        str(")"),
        sym("statement_block") }) },

    { "finally", seq({
        keyword("finally"),
        sym("statement_block") }) },

    { "var_assignment", seq({
        sym("identifier"),
        str("="),
        sym("expression") }) },

    { "_paren_expression", in_parens(err(sym("expression"))) },

    /*
     *  Expressions
     */

    { "expression", choice({
        sym("object"),
        sym("array"),
        sym("function_expression"),
        sym("function_call"),
        sym("constructor_call"),
        sym("member_access"),
        sym("subscript_access"),
        sym("assignment"),
        sym("math_assignment"),
        sym("ternary"),
        sym("bool_op"),
        sym("math_op"),
        // sym("comma_op"),

        // sym("bitwise_op"),

        sym("rel_op"),
        sym("type_op"),
        sym("null"),
        sym("number"),
        sym("undefined"),
        sym("regex"),
        sym("string"),
        sym("false"),
        sym("identifier"),
        sym("true"),
        sym("_paren_expression") }) },

    { "object", in_braces(comma_sep(err(sym("pair")))) },

    { "array", in_brackets(comma_sep(err(sym("expression")))) },

    { "function_expression", seq({
        keyword("function"),
        optional(sym("identifier")),
        str("("),
        optional(sym("formal_parameters")),
        str(")"),
        sym("statement_block") }) },

    { "function_call", left_assoc(PREC_CALL, seq({
        sym("expression"),
        str("("),
        optional(err(sym("arguments"))),
        str(")") })) },

    { "constructor_call", choice({
        left_assoc(PREC_SHORT_NEW, seq({
          keyword("new"),
          sym("expression") })),
        left_assoc(PREC_FULL_NEW, seq({
          keyword("new"),
          sym("expression"),
          str("("),
          err(optional(sym("arguments"))),
          str(")") })) }) },

    { "member_access", left_assoc(PREC_MEMBER, seq({
        sym("expression"),
        str("."),
        sym("identifier") })) },

    { "subscript_access", left_assoc(PREC_MEMBER, seq({
        sym("expression"),
        str("["),
        err(sym("expression")),
        str("]") })) },

    { "assignment", right_assoc(PREC_ASSIGN, seq({
        choice({
            sym("identifier"),
            sym("member_access"),
            sym("subscript_access") }),
        str("="),
        sym("expression") })) },

    { "math_assignment", right_assoc(PREC_ASSIGN, seq({
        choice({
            sym("identifier"),
            sym("member_access"),
            sym("subscript_access") }),
        choice({ str("+="), str("-="), str("*="), str("/=") }),
        sym("expression") })) },

    { "ternary", right_assoc(PREC_TERNARY, seq({
        sym("expression"),
        str("?"),
        sym("expression"),
        str(":"),
        sym("expression") })) },

    { "bool_op", choice({
        infix_op("||", "expression", PREC_OR),
        infix_op("&&", "expression", PREC_AND),
        prefix_op("!", "expression", PREC_NOT) }) },

    { "comma_op", infix_op(",", "expression", PREC_COMMA) },

    { "math_op", choice({

        // prefix_op("+", "expression", PREC_SIGN),
        // prefix_op("-", "expression", PREC_SIGN),

        postfix_op("++", "expression", PREC_INC),
        postfix_op("--", "expression", PREC_INC),
        infix_op("*", "expression", PREC_MULT),
        infix_op("/", "expression", PREC_MULT),
        infix_op("+", "expression", PREC_ADD),
        infix_op("-", "expression", PREC_ADD) }) },

    // { "bitwise_op", choice({
        // infix_op("&", "expression", PREC_MULT),
        // infix_op("|", "expression", PREC_MULT),
        // infix_op("<<", "expression", PREC_MULT),
        // infix_op(">>", "expression", PREC_MULT) }) },

    { "rel_op", choice({

        // infix_op("==", "expression", PREC_REL),
        // infix_op("!=", "expression", PREC_REL),
        // infix_op("<=", "expression", PREC_REL),
        // infix_op(">=", "expression", PREC_REL),

        infix_op("===", "expression", PREC_REL),
        infix_op("!==", "expression", PREC_REL),
        infix_op("<", "expression", PREC_REL),
        infix_op(">", "expression", PREC_REL) }) },

    { "type_op", choice({
        left_assoc(PREC_REL, seq({
          choice({ sym("expression"), sym("identifier") }),
          keyword("in"),
          sym("expression") })),
        infix_op("instanceof", "expression", PREC_REL),
        prefix_op("typeof", "expression", PREC_TYPE) }) },

    /*
     *  Primitives
     */

    { "comment", token(choice({
        seq({
            str("/*"),
            repeat(pattern("[^*]|(*[^/])")),
            str("*/") }),
        pattern("//[^\n]*") })) },

    { "string", token(choice({
        delimited("\""),
        delimited("'") })) },

    { "regex", token(seq({ delimited("/"), optional(str("g")) })) },

    { "number", pattern("\\d+(\\.\\d+)?") },

    { "identifier", pattern("[\\a_$][\\w_$]*") },

    { "null", keyword("null") },
    { "undefined", keyword("undefined") },
    { "true", keyword("true") },
    { "false", keyword("false") },
    { "_line_break", str("\n") },

    /*
     *  Expression components
     */

    { "formal_parameters", comma_sep1(sym("identifier")) },

    { "arguments", left_assoc(-5, comma_sep1(err(sym("expression")))) },

    { "pair", seq({
        choice({ sym("string"), sym("identifier") }),
        str(":"),
        sym("expression") }) },
}).ubiquitous_tokens({
    sym("comment"),
    sym("_line_break"),
    pattern("[ \t\r]"),
});

}  // namespace tree_sitter_examples
