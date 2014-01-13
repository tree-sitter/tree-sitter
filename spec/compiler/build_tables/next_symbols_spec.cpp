#include "spec_helper.h"
#include "build_tables/next_symbols.h"
#include "grammar.h"
#include "rules.h"

using std::set;
using namespace build_tables;
using namespace rules;

START_TEST

describe("computing FIRST sets", []() {
    Grammar grammar({
        { "A", choice({
            seq({
                sym("B"),
                sym("x"),
                sym("B") }),
            sym("B") }) },
        { "B", choice({
            seq({
                sym("y"),
                sym("z"),
                sym("y") }),
            sym("y") }) },
    });
    
    describe("for a rule", [&]() {
        it("searches the tree for terminals", [&]() {
            auto terminals = next_terminals(grammar.rules.find("A")->second, grammar);
            AssertThat(terminals, Equals(set<Symbol>({
                Symbol("y")
            })));
        });
    });
});

END_TEST