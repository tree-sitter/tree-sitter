#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;

    static rule_ptr comma_sep(const rule_ptr &element) {
        return choice({
            seq({ element, repeat(seq({ str(","), element })) }),
            blank(),
        });
    }

    extern const Grammar golang({
        { "program", seq({
            sym("package_directive"),
            repeat(sym("imports_block")),
            repeat(sym("declaration")) }) },
        { "package_directive", seq({
            sym("_package"),
            sym("package_name") }) },
        { "imports_block", seq({
            sym("_import"),
            choice({
                seq({
                    str("("),
                    err(repeat(sym("package_import"))),
                    str(")")
                }),
                sym("package_import")
            })
        }) },
        { "package_import", sym("string") },
        { "declaration", seq({
            choice({
                sym("type_declaration"),
                sym("var_declaration"),
                sym("func_declaration") }),
            blank() }) },

        // Declarations
        { "type_declaration", seq({
            sym("_type"),
            sym("type_name"),
            sym("type_expression") }) },
        { "var_declaration", seq({
            sym("_var"),
            sym("var_name"),
            str("="),
            sym("expression"),
        }) },
        { "func_declaration", seq({
            sym("_func"),
            sym("var_name"),
            sym("_func_signature"),
            sym("statement_block"),
        }) },
        { "statement_block", seq({
            str("{"),
            str("}"),
        }) },
        { "expression", choice({
            sym("number"),
        }) },
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
            sym("_map"),
            str("["),
            sym("type_expression"),
            str("]"),
            sym("type_expression") }) },
        { "slice_type", seq({
            str("["),
            str("]"),
            sym("type_expression") }) },
        { "struct_type", seq({
            sym("_struct"),
            str("{"),
            repeat(seq({
                sym("var_name"),
                sym("type_expression") })),
            str("}") }) },
        { "interface_type", seq({
            sym("_interface"),
            str("{"),
            repeat(seq({
                sym("var_name"),
                sym("_func_signature") })),
            str("}") }) },

        // Value expressions
        { "_func_signature", seq({
            str("("),
            comma_sep(seq({
                comma_sep(sym("var_name")),
                sym("type_expression"),
            })),
            str(")"),
            choice({
                seq({
                    str("("),
                    choice({
                        comma_sep(seq({ sym("var_name"), sym("type_name") })),
                        comma_sep(sym("type_name")),
                    }),
                    str(")") }),
                sym("type_name"),
                blank() })}) },

        // Keywords
        { "_map", str("map") },
        { "_interface", str("interface") },
        { "_struct", str("struct") },
        { "_package", str("package") },
        { "_import", str("import") },
        { "_var", str("var") },
        { "_func", str("func") },
        { "_type", str("type") },

        { "string", pattern("\"([^\"]|\\\\\")+\"") },
        { "package_name", sym("_identifier") },
        { "var_name", sym("_identifier") },
        { "type_name", sym("_identifier") },
        { "_identifier", pattern("\\a[\\w_]*") },
        { "number", pattern("\\d+(.\\d+)?") },
    });
}
