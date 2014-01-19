#include "spec_helper.h"
#include "build_tables/first_set.h"
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
        { "C", seq({
            choice({
                sym("x"),
                blank() }),
            sym("y") }) }
    });
    
    describe("for a rule starting with a non-terminal B", [&]() {
        it("includes FIRST(B)", [&]() {
            auto terminals = first_set(grammar.rules.find("A")->second, grammar);
            AssertThat(terminals, Equals(set<Symbol>({
                Symbol("y")
            })));
        });
    });

    describe("for a sequence xy", [&]() {
        it("includes FIRST(y) when x can be blank", [&]() {
            auto terminals = first_set(grammar.rules.find("C")->second, grammar);
            AssertThat(terminals, Equals(set<Symbol>({
                Symbol("x"),
                Symbol("y")
            })));
        });
    });
});

END_TEST