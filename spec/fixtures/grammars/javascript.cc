#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

static rule_ptr terminated(rule_ptr rule) {
  return seq({ rule, choice({
    sym("_line_break"),
    str(";") }) });
}

enum {
  PREC_COMMA = -1,
  PREC_ASSIGN = 0,
  PREC_BLOCK = 1,
  PREC_TERNARY = 2,
  PREC_OR = 3,
  PREC_AND = 4,
  PREC_REL = 5,
  PREC_ADD = 6,
  PREC_MULT = 7,
  PREC_TYPE = 8,
  PREC_NOT = 9,
  PREC_SIGN = 10,
  PREC_INC = 11,
  PREC_SHORT_NEW = 12,
  PREC_CALL = 13,
  PREC_FULL_NEW = 14,
  PREC_MEMBER = 15,
  PREC_ARGS = 16,
};

extern const Grammar javascript = Grammar({
  { "program", repeat(sym("_statement")) },

  /*
   *  Statements
   */

  { "_statement", choice({
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

  { "expression_statement", terminated(err(sym("_expression"))) },

  { "var_declaration", terminated(seq({
    str("var"),
    comma_sep1(err(choice({
      sym("identifier"),
      sym("var_assignment") }))) })) },

  { "statement_block", prec(PREC_BLOCK,
    in_braces(err(repeat(sym("_statement"))))) },

  { "if_statement", prec(0, seq({
    str("if"),
    sym("_paren_expression"),
    sym("_statement"),
    optional(seq({
      str("else"),
      sym("_statement") })) }), AssociativityRight) },

  { "switch_statement", seq({
    str("switch"),
    sym("_paren_expression"),
    str("{"),
    repeat(choice({ sym("case"), sym("default") })),
    str("}") }) },

  { "for_statement", seq({
    str("for"),
    str("("),
    choice({
      sym("var_declaration"),
      seq({ sym("_expression"), str(";") }),
      str(";") }),
    optional(err(sym("_expression"))), str(";"),
    optional(err(sym("_expression"))),
    str(")"),
    sym("_statement") }) },

  { "for_in_statement", seq({
    str("for"),
    str("("),
    optional(str("var")),
    prec(PREC_REL, seq({
      sym("identifier"),
      str("in"),
      sym("_expression") })),
    str(")"),
    sym("_statement") }) },

  { "while_statement", seq({
    str("while"),
    sym("_paren_expression"),
    sym("_statement") }) },

  // { "do_statement", seq({
  //   str("do"),
  //   sym("_statement"),
  //   str("while"),
  //   sym("_paren_expression") })},

  { "try_statement", seq({
    str("try"),
    sym("statement_block"),
    optional(sym("catch")),
    optional(sym("finally")) }) },

  { "return_statement", terminated(seq({
    str("return"),
    optional(sym("_expression")) })) },

  { "throw_statement", terminated(seq({
    str("throw"),
    sym("_expression") })) },

  { "break_statement", terminated(str("break")) },

  { "delete_statement", terminated(seq({
    str("delete"),
    choice({ sym("member_access"), sym("subscript_access") }) })) },

  /*
   *  Statement components
   */

  { "case", seq({
    str("case"),
    sym("_expression"),
    str(":"),
    repeat(sym("_statement")) }) },

  { "default", seq({
    str("default"),
    str(":"),
    repeat(sym("_statement")) }) },

  { "catch", seq({
    str("catch"),
    str("("),
    err(sym("identifier")),
    str(")"),
    sym("statement_block") }) },

  { "finally", seq({
    str("finally"),
    sym("statement_block") }) },

  { "var_assignment", seq({
    sym("identifier"),
    str("="),
    sym("_expression") }) },

  { "_paren_expression", in_parens(err(sym("_expression"))) },

  /*
   *  Expressions
   */

  { "_expression", choice({
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

  { "array", in_brackets(comma_sep(err(sym("_expression")))) },

  { "function_expression", seq({
    str("function"),
    optional(sym("identifier")),
    str("("),
    optional(sym("formal_parameters")),
    str(")"),
    sym("statement_block") }) },

  { "function_call", prec(PREC_CALL, seq({
    sym("_expression"),
    sym("arguments") })) },

  { "constructor_call", choice({
    prec(PREC_SHORT_NEW, seq({
      str("new"),
      sym("_expression") }), AssociativityRight),
    prec(PREC_MEMBER, seq({
      str("new"),
      sym("_expression"),
      sym("arguments") }), AssociativityRight) }) },

  { "member_access", prec(PREC_MEMBER, seq({
    sym("_expression"),
    str("."),
    sym("identifier") })) },

  { "subscript_access", prec(PREC_MEMBER, seq({
    sym("_expression"),
    str("["),
    err(sym("_expression")),
    str("]") })) },

  { "assignment", prec(PREC_ASSIGN, seq({
    choice({
      sym("identifier"),
      sym("member_access"),
      sym("subscript_access") }),
    str("="),
    sym("_expression") }), AssociativityRight) },

  { "math_assignment", prec(PREC_ASSIGN, seq({
    choice({
      sym("identifier"),
      sym("member_access"),
      sym("subscript_access") }),
    choice({ str("+="), str("-="), str("*="), str("/=") }),
    sym("_expression") }), AssociativityRight) },

  { "ternary", prec(PREC_TERNARY, seq({
    sym("_expression"),
    str("?"),
    sym("_expression"),
    str(":"),
    sym("_expression") }), AssociativityRight) },

  { "bool_op", choice({
    infix_op("||", "_expression", PREC_OR),
    infix_op("&&", "_expression", PREC_AND),
    prefix_op("!", "_expression", PREC_NOT) }) },

  { "comma_op", infix_op(",", "_expression", PREC_COMMA) },

  { "math_op", choice({

    // prefix_op("+", "_expression", PREC_SIGN),
    // prefix_op("-", "_expression", PREC_SIGN),

    postfix_op("++", "_expression", PREC_INC),
    postfix_op("--", "_expression", PREC_INC),
    infix_op("*", "_expression", PREC_MULT),
    infix_op("/", "_expression", PREC_MULT),
    infix_op("+", "_expression", PREC_ADD),
    infix_op("-", "_expression", PREC_ADD) }) },

  // { "bitwise_op", choice({
    // infix_op("&", "_expression", PREC_MULT),
    // infix_op("|", "_expression", PREC_MULT),
    // infix_op("<<", "_expression", PREC_MULT),
    // infix_op(">>", "_expression", PREC_MULT) }) },

  { "rel_op", choice({

    // infix_op("==", "_expression", PREC_REL),
    // infix_op("!=", "_expression", PREC_REL),
    // infix_op("<=", "_expression", PREC_REL),
    // infix_op(">=", "_expression", PREC_REL),

    infix_op("===", "_expression", PREC_REL),
    infix_op("!==", "_expression", PREC_REL),
    infix_op("<", "_expression", PREC_REL),
    infix_op(">", "_expression", PREC_REL) }) },

  { "type_op", choice({
    prec(PREC_REL, seq({
      choice({ sym("_expression"), sym("identifier") }),
      str("in"),
      sym("_expression") })),
    infix_op("instanceof", "_expression", PREC_REL),
    prefix_op("typeof", "_expression", PREC_TYPE) }) },

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

  { "null", str("null") },
  { "undefined", str("undefined") },
  { "true", str("true") },
  { "false", str("false") },
  { "_line_break", str("\n") },

  /*
   *  Expression components
   */

  { "formal_parameters", comma_sep1(sym("identifier")) },

  { "arguments", prec(PREC_ARGS, seq({
    str("("),
    comma_sep(err(sym("_expression"))),
    str(")") })) },

  { "pair", seq({
    choice({ sym("string"), sym("identifier") }),
    str(":"),
    sym("_expression") }) },

}).ubiquitous_tokens({
  sym("comment"),
  sym("_line_break"),
  pattern("[ \t\r]"),
});

}  // namespace tree_sitter_examples
