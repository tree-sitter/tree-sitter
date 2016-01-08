#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

static rule_ptr terminated(rule_ptr rule) {
  return seq({ rule, choice({
    sym("_line_break"),
    str(";") }) });
}

extern const Grammar golang{{
  { "program", seq({
    sym("package_directive"),
    repeat(sym("imports_block")),
    repeat(sym("_declaration")) }) },

  { "package_directive", seq({
    str("package"),
    sym("package_name") }) },

  { "imports_block", seq({
    str("import"),
    choice({
      in_parens(err(repeat(sym("package_import")))),
      sym("package_import") }) }) },

  { "package_import", sym("string") },

  { "_declaration", choice({
    sym("type_declaration"),
    sym("var_declaration"),
    sym("func_declaration") }) },

  /*
   *  Declarations
   */

  { "type_declaration", terminated(seq({
    str("type"),
    sym("type_name"),
    sym("_type_expression") })) },

  { "var_declaration", terminated(seq({
    str("var"),
    sym("var_name"),
    choice({
      seq({
        optional(sym("_type_expression")),
        str("="),
        sym("_expression") }),
      sym("_type_expression") }) })) },

  { "func_declaration", terminated(seq({
    str("func"),
    sym("var_name"),
    sym("_func_signature"),
    sym("block_statement") })) },

  { "block_statement", in_braces(err(repeat(sym("_statement")))) },

  { "_type_expression", choice({
    sym("pointer_type"),
    sym("slice_type"),
    sym("map_type"),
    sym("interface_type"),
    sym("struct_type"),
    sym("type_name") }) },

  /*
   * Type expressions
   */

  { "pointer_type", seq({
    str("*"),
    sym("_type_expression") }) },

  { "map_type", seq({
    str("map"),
    in_brackets(sym("_type_expression")),
    sym("_type_expression") }) },

  { "slice_type", seq({
    in_brackets(blank()),
    sym("_type_expression") }) },

  { "struct_type", seq({
    str("struct"),
    in_braces(repeat(seq({
      sym("var_name"),
      sym("_type_expression") }))) }) },

  { "interface_type", seq({
    str("interface"),
    in_braces(repeat(seq({
      sym("var_name"),
      sym("_func_signature") }))) }) },

  /*
   * Statements
   */

  { "_statement", choice({
    sym("expression_statement"),
    sym("return_statement"),
    sym("var_declaration"),
    sym("short_var_declaration"),
    sym("range_statement"),
    sym("if_statement") }) },

  { "return_statement", terminated(seq({
    str("return"),
    comma_sep(sym("_expression")) })) },

  { "short_var_declaration", terminated(seq({
    comma_sep(sym("var_name")),
    str(":="),
    sym("_expression") })) },

  { "range_statement", seq({
    str("for"),
    sym("var_name"),
    optional(seq({ str(","), sym("var_name") })),
    str(":="),
    str("range"),
    sym("_expression"),
    sym("block_statement") }) },

  { "if_statement", seq({
    str("if"),
    sym("_expression"),
    sym("block_statement"),
    optional(seq({
      str("else"),
      choice({
        sym("if_statement"),
        sym("block_statement") }) })) }) },

  { "expression_statement", terminated(sym("_expression")) },

  /*
   * Value expressions
   */

  { "_expression", choice({
    sym("call_expression"),
    sym("selector_expression"),
    sym("math_op"),
    sym("bool_op"),
    sym("number"),
    sym("string"),
    sym("var_name") }) },

  { "call_expression", seq({
    sym("_expression"),
    in_parens(comma_sep(sym("_expression"))) }) },

  { "selector_expression", seq({
    sym("_expression"),
    str("."),
    sym("var_name") }) },

  { "math_op", choice({
    infix_op("*", "_expression", 2),
    infix_op("/", "_expression", 2),
    infix_op("+", "_expression", 1),
    infix_op("-", "_expression", 1) }) },

  { "bool_op", choice({
    infix_op("||", "_expression", 1),
    infix_op("&&", "_expression", 2),
    infix_op("==", "_expression", 3),
    infix_op("<=", "_expression", 3),
    infix_op("<", "_expression", 3),
    infix_op(">=", "_expression", 3),
    infix_op(">", "_expression", 3),
    prefix_op("!", "_expression", 4) }) },

  { "_func_signature", prec(10, seq({
    in_parens(comma_sep(seq({
      comma_sep1(sym("var_name")),
      sym("_type_expression") }))),
    choice({
      in_parens(choice({
        comma_sep1(seq({ sym("var_name"), sym("type_name") })),
        comma_sep1(sym("type_name")) })),
      sym("type_name"),
    blank() }) })) },

  { "_line_break", str("\n") },

  { "string", delimited("\"") },

  { "package_name", sym("_identifier") },

  { "var_name", sym("_identifier") },

  { "type_name", sym("_identifier") },

  { "_identifier", pattern("\\a[\\w_]*") },

  { "number", pattern("\\d+(\\.\\d+)?") },

  { "comment", pattern("//[^\n]*") },

}, {
  sym("comment"),
  sym("_line_break"),
  pattern("[ \t\r]"),
}, {}};

}  // namespace tree_sitter_examples
