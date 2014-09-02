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

extern const Grammar golang = Grammar({
    { "program", seq({
      sym("package_directive"),
      repeat(sym("imports_block")),
      repeat(sym("declaration")) }) },
    { "package_directive", seq({
      keyword("package"),
      sym("package_name") }) },
    { "imports_block", seq({
      keyword("import"),
      choice({
        in_parens(err(repeat(sym("package_import")))),
        sym("package_import") }) }) },
    { "package_import", sym("string") },
    { "declaration", choice({
      sym("type_declaration"),
      sym("var_declaration"),
      sym("func_declaration") }) },

    // Declarations
    { "type_declaration", terminated(seq({
        keyword("type"),
        sym("type_name"),
        sym("type_expression") })) },
    { "var_declaration", terminated(seq({
          keyword("var"),
          sym("var_name"),
          choice({
            seq({
              optional(sym("type_expression")),
              str("="),
              sym("expression") }),
            sym("type_expression") }) })) },
    { "func_declaration", terminated(seq({
          keyword("func"),
          sym("var_name"),
          sym("_func_signature"),
          sym("block_statement") })) },
    { "block_statement", in_braces(err(repeat(sym("statement")))) },
    { "type_expression", choice({
        sym("pointer_type"),
        sym("slice_type"),
        sym("map_type"),
        sym("interface_type"),
        sym("struct_type"),
        sym("type_name") }) },

    // Type expressions
    { "pointer_type", seq({
        keyword("*"),
        sym("type_expression") }) },
    { "map_type", seq({
        keyword("map"),
        in_brackets(sym("type_expression")),
        sym("type_expression") }) },
    { "slice_type", seq({
        in_brackets(blank()),
        sym("type_expression") }) },
    { "struct_type", seq({
        keyword("struct"),
        in_braces(repeat(seq({
              sym("var_name"),
              sym("type_expression") }))) }) },
    { "interface_type", seq({
        keyword("interface"),
        in_braces(repeat(seq({
              sym("var_name"),
              sym("_func_signature") }))) }) },

    // Statements
    { "statement", choice({
        sym("expression_statement"),
        sym("return_statement"),
        sym("declaration_statement"),
        sym("range_statement"),
        sym("if_statement") }) },
    { "return_statement", terminated(seq({
          keyword("return"),
          comma_sep(sym("expression")) })) },
    { "declaration_statement", choice({
        sym("var_declaration"),
        terminated(seq({
            comma_sep(sym("var_name")),
            str(":="),
            sym("expression") })) }) },
    { "range_statement", seq({
        keyword("for"),
        sym("var_name"),
        optional(seq({ str(","), sym("var_name") })),
        str(":="),
        keyword("range"),
        sym("expression"),
        sym("block_statement") }) },
    { "if_statement", seq({
        keyword("if"),
        sym("expression"),
        sym("block_statement"),
        optional(seq({
            keyword("else"),
            choice({
              sym("if_statement"),
              sym("block_statement") }) })) }) },
    { "expression_statement", terminated(sym("expression")) },

    // Value expressions
    { "expression", choice({
        sym("call_expression"),
        sym("selector_expression"),
        sym("math_op"),
        sym("bool_op"),
        sym("number"),
        sym("string"),
        sym("var_name") }) },
    { "call_expression", seq({
        sym("expression"),
        in_parens(comma_sep(sym("expression"))) }) },
    { "selector_expression", seq({
        sym("expression"),
        str("."),
        sym("var_name") }) },
    { "math_op", choice({
        infix_op("*", "expression", 2),
        infix_op("/", "expression", 2),
        infix_op("+", "expression", 1),
        infix_op("-", "expression", 1) }) },
    { "bool_op", choice({
        infix_op("||", "expression", 1),
        infix_op("&&", "expression", 2),
        infix_op("==", "expression", 3),
        infix_op("<=", "expression", 3),
        infix_op("<", "expression", 3),
        infix_op(">=", "expression", 3),
        infix_op(">", "expression", 3),
        prefix_op("!", "expression", 4) }) },
    { "_func_signature", seq({
        in_parens(comma_sep(seq({
              comma_sep1(sym("var_name")),
              sym("type_expression") }))),
        choice({
          in_parens(choice({
              comma_sep1(seq({ sym("var_name"), sym("type_name") })),
              comma_sep1(sym("type_name")) })),
          sym("type_name"),
          blank() }) }) },

    { "_line_break", str("\n") },

    { "string", delimited("\"") },
    { "package_name", sym("_identifier") },
    { "var_name", sym("_identifier") },
    { "type_name", sym("_identifier") },
    { "_identifier", pattern("\\a[\\w_]*") },
    { "number", pattern("\\d+(\\.\\d+)?") },
    { "comment", keypattern("//[^\n]*") },
})
    .ubiquitous_tokens({ "comment", "_line_break" })
    .separators({ ' ', '\t', '\r' });

}  // namespace tree_sitter_examples
