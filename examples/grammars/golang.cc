#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using tree_sitter::GrammarOptions;
    using namespace tree_sitter::rules;

    extern const Grammar golang({
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
        { "declaration", seq({
            choice({
                sym("type_declaration"),
                sym("var_declaration"),
                sym("func_declaration") }),
            blank() }) },

        // Declarations
        { "type_declaration", seq({
            keyword("type"),
            sym("type_name"),
            sym("type_expression") }) },
        { "var_declaration", seq({
            keyword("var"),
            sym("var_name"),
            str("="),
            sym("expression") }) },
        { "func_declaration", seq({
            keyword("func"),
            sym("var_name"),
            sym("_func_signature"),
            sym("statement_block") }) },
        { "statement_block", in_braces(blank()) },
        { "type_expression", choice({
            sym("pointer_type"),
            sym("slice_type"),
            sym("map_type"),
            sym("interface_type"),
            sym("struct_type"),
            sym("type_name") }) },

        // Type expressions
        { "pointer_type", seq({
            str("*"),
            sym("type_expression") }) },
        { "map_type", seq({
            keyword("map"),
            str("["),
            sym("type_expression"),
            str("]"),
            sym("type_expression") }) },
        { "slice_type", seq({
            str("["),
            str("]"),
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

        // Value expressions
        { "expression", choice({
            sym("math_op"),
            sym("bool_op"),
            sym("number"),
            sym("string"),
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

        { "string", delimited("\"") },
        { "package_name", sym("_identifier") },
        { "var_name", sym("_identifier") },
        { "type_name", sym("_identifier") },
        { "_identifier", pattern("\\a[\\w_]*") },
        { "number", pattern("\\d+(\\.\\d+)?") },
        { "comment", pattern("//[^\n]*") },
    }, GrammarOptions({
        { "comment" },
    }));
}
