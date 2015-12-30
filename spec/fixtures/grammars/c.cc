#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

// http://slps.github.io/zoo/c/iso-9899-tc3.html

extern const Grammar c = Grammar({
  { "translation_unit", repeat(choice({
    sym("preproc_define"),
    sym("preproc_call"),
    sym("function_definition"),
    sym("declaration") })) },

  { "preproc_define", seq({
    str("#define"),
    sym("identifier"),
    optional(sym("preproc_arg")),
    str("\n") }) },

  { "preproc_call", seq({
    sym("preproc_directive"),
    sym("preproc_arg") }) },

  { "preproc_arg", token(prec(-1, repeat1(choice({
    str("\\\n"),
    pattern(".") })))) },

  { "preproc_directive", pattern("#\a\\w*") },

  { "function_definition", seq({
    optional(sym("declaration_specifiers")),
    sym("_type_specifier"),
    sym("_declarator"),
    sym("compound_statement") }) },

  { "declaration_specifiers", repeat1(choice({
    sym("storage_class_specifier"),
    sym("type_qualifier") })) },

  { "storage_class_specifier", choice({
    str("typedef"),
    str("extern"),
    str("static"),
    str("auto"),
    str("register") }) },

  { "_type_specifier", choice({
    sym("struct_specifier"),
    sym("numeric_type_specifier"),
    sym("identifier"),
    sym("macro_type"), }) },

  { "numeric_type_specifier", seq({
    repeat1(choice({
      str("signed"),
      str("unsigned"),
      str("long"),
      str("short") })),
    sym("identifier") }) },

  { "struct_specifier", seq({
    str("struct"),
    optional(sym("identifier")),
    seq({
      str("{"),
      repeat(sym("struct_declaration")),
      str("}") }) }) },

  { "type_name", seq({
    repeat(sym("type_qualifier")),
    sym("_type_specifier"),
    optional(sym("_abstract_declarator")) }) },

  { "struct_declaration", seq({
    sym("_type_specifier"),
    sym("_declarator") }) },

  { "parameter_declaration", seq({
    optional(sym("declaration_specifiers")),
    sym("_type_specifier"),
    sym("_declarator") }) },

  { "declaration", seq({
    err(seq({
      optional(sym("declaration_specifiers")),
      sym("_type_specifier"),
      comma_sep1(choice({
        sym("_declarator"),
        sym("_init_declarator") })) })),
    str(";") }) },

  { "_init_declarator", seq({
    sym("_declarator"),
    str("="),
    sym("initializer") }) },

  { "initializer", choice({
    sym("_expression"),
    seq({
      str("{"),
      sym("initializer_list"),
      optional(str(",")),
      str("}") }) }) },

  { "initializer_list", choice({
    seq({
      optional(sym("designation")),
      sym("initializer") }),
    seq({
      sym("initializer_list"),
      str(","),
      optional(sym("designation")),
      sym("initializer") }) }) },

  { "designation", seq({
    repeat1(choice({
      seq({
        str("["),
        sym("_expression"),
        str("]") }),
      seq({
        str("."),
        sym("identifier") }) })),
    str("=") }) },

  { "_declarator", choice({
    sym("pointer_declarator"),
    sym("function_declarator"),
    sym("array_declarator"),
    sym("identifier"),
    seq({ str("("), sym("_declarator"), str(")") }) }) },

  { "_abstract_declarator", choice({
    sym("abstract_pointer_declarator"),
    sym("abstract_function_declarator"),
    sym("abstract_array_declarator"),
    prec(1, seq({ str("("), sym("_abstract_declarator"), str(")") })) }) },

  { "pointer_declarator", seq({
    str("*"),
    sym("_declarator") }) },

  { "abstract_pointer_declarator", seq({
    str("*"),
    optional(sym("_abstract_declarator")) }) },

  { "function_declarator", prec(1, seq({
    sym("_declarator"),
    str("("),
    comma_sep(sym("parameter_declaration")),
    str(")") })) },

  { "abstract_function_declarator", prec(1, seq({
    sym("_abstract_declarator"),
    str("("),
    comma_sep(sym("parameter_declaration")),
    str(")") })) },

  { "array_declarator", prec(1, seq({
    sym("_declarator"),
    str("["),
    optional(sym("_expression")),
    str("]") })) },

  { "abstract_array_declarator", prec(1, seq({
    sym("_abstract_declarator"),
    str("["),
    optional(sym("_expression")),
    str("]") })) },

  { "type_qualifier", choice({
    str("const"),
    str("restrict"),
    str("volatile") }) },

  { "compound_statement", seq({
    str("{"),
    err(repeat(choice({ sym("declaration"), sym("_statement") }))),
    str("}") }) },

  { "_expression", choice({
    sym("cast_expression"),
    sym("math_expression"),
    sym("call_expression"),
    sym("pointer_expression"),
    sym("assignment_expression"),
    sym("string"),
    sym("identifier"),
    sym("number"),
    prec(1, seq({ str("("), sym("_expression"), str(")") })) }) },

  { "cast_expression", prec(4, seq({
    str("("),
    sym("type_name"),
    str(")"),
    sym("_expression") })) },

  { "math_expression", choice({
    prec_left(1, seq({ sym("_expression"), str("+"), sym("_expression") })),
    prec_left(2, seq({ sym("_expression"), str("*"), sym("_expression") })) }) },

  { "call_expression", prec(3, seq({
    sym("_expression"),
    str("("),
    comma_sep(sym("_expression")),
    str(")") })) },

  { "pointer_expression", seq({
    choice({
      str("*"),
      str("&") }),
    sym("_expression") }) },

  { "assignment_expression", prec_right(-1, seq({
    sym("_expression"),
    str("="),
    sym("_expression") })) },

  { "_statement", choice({
    sym("for_statement"),
    sym("expression_statement"),
    sym("compound_statement") }) },

  { "for_statement", seq({
    str("for"),
    str("("),
    choice({
      sym("declaration"),
      seq({ optional(sym("_expression")), str(";") }) }),
    optional(sym("_expression")),
    str(";"),
    comma_sep(sym("_expression")),
    str(")"),
    sym("_statement") }) },

  { "expression_statement", seq({
    sym("_expression"),
    str(";") }) },

  { "string", delimited("\"") },

  { "identifier", pattern("\\a[\\w_]*") },

  { "number", pattern("\\d+(\\.\\d+)?") },

  { "macro_type", seq({
    sym("identifier"),
    str("("),
    sym("_type_specifier"),
    str(")") }) },

  { "comment", token(choice({
    pattern("//[^\n]*"),
    seq({
      str("/*"),
      repeat(choice({
        pattern("[^\\*]"),
        pattern("\\*[^/]") })),
      str("*/") }) })) },
}).extra_tokens({
  sym("comment"),
  pattern("[ \t\r\n]"),
}).expected_conflicts({
  { "_type_specifier", "_expression" },
  { "_type_specifier", "_expression", "macro_type" },
  { "_type_specifier", "macro_type" },
});

}  // namespace tree_sitter_examples
