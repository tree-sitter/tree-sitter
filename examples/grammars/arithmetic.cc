#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace examples {
        using namespace tree_sitter::rules;
        
        Grammar arithmetic() {
            return Grammar("expression", {
                { "expression", choice({
                    seq({
                        sym("term"),
                        sym("plus"),
                        sym("term") }),
                    sym("term") }) },
                { "term", choice({
                    seq({
                        sym("factor"),
                        sym("times"),
                        sym("factor") }),
                    sym("factor") }) },
                { "factor", choice({
                    sym("variable"),
                    sym("number"),
                    seq({
                        str("("),
                        err(sym("expression")),
                        str(")") }) }) },
                { "plus", str("+") },
                { "times", str("*") },
                { "number", pattern("\\d+") },
                { "variable", pattern("[a-zA-Z]+") },
            });
        }
    }
}
