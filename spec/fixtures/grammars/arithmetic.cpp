#include "arithmetic.h"
#include "rules.h"

using namespace tree_sitter;
using namespace tree_sitter::rules;

namespace test_grammars {
    Grammar arithmetic() {
        return Grammar({
            { "expression", choice({
                seq({
                    sym("term"),
                    character('+'),
                    sym("term") }),
                sym("term") }) },
            { "term", choice({
                seq({
                    sym("factor"),
                    character('*'),
                    sym("factor") }),
                sym("factor") }) },
            { "factor", choice({
                sym("variable"),
                sym("number"),
                seq({
                    character('('),
                    sym("expression"),
                    character(')') }) }) },
            { "number", pattern("\\d+") },
            { "variable", pattern("\\w+") },
        });
    }
}
