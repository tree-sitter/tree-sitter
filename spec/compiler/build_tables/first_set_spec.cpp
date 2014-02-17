#include "spec_helper.h"
#include "build_tables/first_set.h"

using std::set;
using namespace build_tables;
using namespace rules;

START_TEST

describe("computing FIRST sets", []() {
    const Grammar null_grammar("", {{ "something", blank() }});

    describe("for a sequence AB", [&]() {
        it("ignores B when A cannot be blank", [&]() {
            auto rule = seq({ sym("x"), sym("y") });
            
            AssertThat(first_set(rule, null_grammar), Equals(set<Symbol>({
                Symbol("x"),
            })));
        });

        it("includes FIRST(B) when A can be blank", [&]() {
            auto rule = seq({
                choice({
                    sym("x"),
                    blank() }),
                sym("y") });
            
            AssertThat(first_set(rule, null_grammar), Equals(set<Symbol>({
                Symbol("x"),
                Symbol("y")
            })));
        });
        
        it("includes FIRST(A's right hand side) when A is a non-terminal", [&]() {
            auto rule = choice({
                seq({
                    sym("A"),
                    sym("x"),
                    sym("A") }),
                sym("A") });
            
            Grammar grammar("A", {
                { "A", choice({
                    seq({
                        sym("y"),
                        sym("z"),
                        sym("y") }),
                    sym("y") }) }
            });
            
            AssertThat(first_set(rule, grammar), Equals(set<Symbol>({
                Symbol("y")
            })));
        });
        
        it("includes FIRST(B) when A is a non-terminal and its expansion can be blank", [&]() {
            Grammar grammar("A", {{ "A", choice({ sym("x"), blank() }) }});
            
            auto rule = seq({
                sym("A"),
                sym("y") });
            
            AssertThat(first_set(rule, grammar), Equals(set<Symbol>({
                Symbol("x"),
                Symbol("y")
            })));
        });
    });
});

END_TEST