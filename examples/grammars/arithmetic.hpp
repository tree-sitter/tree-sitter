#ifndef tree_sitter__grammars__arithmetic_h
#define tree_sitter__grammars__arithmetic_h

#include "tree_sitter/compiler.h"

namespace test_grammars {
    using tree_sitter::Grammar;
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
                    sym("expression"),
                    str(")") }) }) },
            { "plus", str("+") },
            { "times", str("*") },
            { "number", pattern("\\d+") },
            { "variable", pattern("[a-zA-Z]+") },
        });
    }
}

#endif