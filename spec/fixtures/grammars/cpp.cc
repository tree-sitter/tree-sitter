#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

// http://slps.github.io/zoo/cpp/iso-n2723.html

extern const Grammar cpp = Grammar({
  { "translation_unit", repeat(sym("_declaration")) },

  { "_declaration", choice({
    sym("_block_declaration"),
    sym("function_definition") }) },

  { "_block_declaration", choice({
    sym("simple_declaration"),
    sym("namespace_alias_definition"), }) },

  { "function_definition", seq({
    repeat(sym("decl_specifier")),
    sym("type_specifier"),
    sym("declarator"),
    choice({
      sym("function_body"),
      seq({
        str("="),
        choice({
          str("default"),
          str("delete") }),
        str(";") }) }) }) },

  { "simple_declaration", seq({
    repeat(sym("decl_specifier")),
    sym("type_specifier"),
    comma_sep1(sym("init_declarator")),
    str(";") }) },

  { "namespace_alias_definition", seq({
    str("namespace"),
    sym("identifier"),
    str("="),
    sym("scoped_identifier") }) },

  { "scoped_identifier", seq({
    sym("identifier"),
    str("::"),
    choice({
      sym("identifier"),
      sym("scoped_identifier") }) }) },

  { "declarator", seq({
    repeat(sym("pointer_operator")),
    sym("direct_declarator") }) },

  { "abstract_declarator", seq({
    repeat(sym("pointer_operator")),
    sym("direct_abstract_declarator") }) },

  { "direct_declarator", choice({
    sym("identifier"),
    seq({
      str("("),
      sym("declarator"),
      str(")") }),
    seq({
      sym("direct_declarator"),
      str("("),
      comma_sep(sym("parameter_declaration")),
      str(")") }) }) },

  { "parameter_declaration", seq({
    repeat(sym("decl_specifier")),
    sym("type_specifier"),
    choice({
      sym("declarator"),
      sym("abstract_declarator") }) }) },

  { "direct_abstract_declarator", choice({
    seq({
      str("("),
      sym("abstract_declarator"),
      str(")") }) }) },

  { "cv_qualifier", choice({
    str("const"),
    str("volatile") }) },

  { "type_id", seq({
    sym("type_specifier"),
    optional(sym("abstract_declarator")) }) },

  { "pointer_operator", choice({
    seq({ str("*"), repeat(sym("cv_qualifier")) }),
    str("&"),
    str("&&") }) },

  { "type_name", choice({
    sym("identifier"),
    sym("template_call") }) },

  { "function_body", choice({
    // sym("function_try_block"),
    seq({
      optional(sym("constructor_initializer")),
      sym("compound_statement") }) }) },

  { "constructor_initializer", seq({
    str(":"),
    repeat(sym("member_initializer")),
    optional(str("...")) }) },

  { "member_initializer", seq({
    sym("identifier"),
    choice({
      // sym("braced_initializer_list"),
      seq({
        str("("),
        str("initializer_list"),
        str(")") }) }) }) },

  { "init_declarator", seq({
    sym("declarator"),
    optional(sym("initializer")) }) },

  { "decl_specifier", choice({
    sym("storage_class_specifier"),
    sym("function_specifier"),
    str("friend"),
    str("typedef"),
    str("constexpr") }) },

  { "storage_class_specifier", choice({
    str("register"),
    str("static"),
    str("thread_local"),
    str("extern"),
    str("mutable") }) },

  { "type_specifier", choice({
    sym("scoped_identifier"),
    sym("template_call"),
    sym("identifier") }) },

  { "compound_statement", seq({
    str("{"),
    repeat(sym("_statement")),
    str("}") }) },

  { "_statement", choice({
    sym("compound_statement"),
    sym("_block_declaration"),
    sym("expression_statement") }) },

  { "expression_statement", seq({
    optional(sym("_expression")),
    str(";") }) },

  { "initializer", choice({
    // sym("braced_initializer_list"),
    seq({
      str("="),
      sym("initializer_clause") }) }) },

  { "initializer_clause", choice({
    // sym("braced_initializer_list"),
    sym("_expression") }) },

  { "function_specifier", choice({
    str("inline"),
    str("virtual"),
    str("explicit") }) },

  { "_expression", choice({
    sym("relational_expression"),
    sym("call_expression"),
    sym("identifier"),
    sym("template_call"),
    sym("scoped_identifier"),
    sym("string"),
    sym("number") }) },

  { "call_expression", seq({
    sym("_expression"),
    str("("),
    comma_sep(sym("_expression")),
    str(")") }) },

  { "relational_expression", prec_left(seq({
    sym("_expression"),
    choice({
      str(">"),
      str(">="),
      str("=="),
      str("!="),
      str("<="),
      str("<") }),
    sym("_expression") })) },

  { "template_call", seq({
    choice({ sym("identifier"), sym("scoped_identifier") }),
    str("<"),
    choice({
      sym("_expression"),
      sym("type_id") }),
    str(">") }) },

  { "string", delimited("\"") },

  { "identifier", pattern("\\a[\\w_]*") },

  { "number", pattern("\\d+(\\.\\d+)?") },

  { "comment", pattern("//[^\n]*") },
}).ubiquitous_tokens({
  sym("comment"),
  pattern("[ \t\r\n]"),
}).expected_conflicts({
  { "type_specifier", "_expression" },
  { "template_call", "_expression" },
  { "template_call", "relational_expression" },
});

}  // namespace tree_sitter_examples
