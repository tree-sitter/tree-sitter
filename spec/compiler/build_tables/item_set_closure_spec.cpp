#include "spec_helper.h"
#include "build_tables/item_set_closure.h"
#include "build_tables/item_set_transitions.h"
#include "grammar.h"
#include "rules.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("computing closures of item sets", []() {
    Grammar grammar({
        { "E", choice({
            seq({
                sym("T"),
                sym("+"),
                sym("T") }),
            sym("T") }) },
        { "T", choice({
            seq({
                sym("F"),
                sym("*"),
                sym("F") }),
            sym("F") }) },
        { "F", choice({
                 sym("v"),
                 sym("n") }) }
    });
    
    it("computes the item set closure", [&]() {
        ParseItemSet item_set = item_set_closure(ParseItemSet({
            ParseItem("E", grammar.rule("E"), 0, "__END__")
        }), grammar);
        AssertThat(item_set, Equals(ParseItemSet({
            ParseItem("F", grammar.rule("F"), 0, "__END__"),
            ParseItem("F", grammar.rule("F"), 0, "+"),
            ParseItem("F", grammar.rule("F"), 0, "*"),
            ParseItem("T", grammar.rule("T"), 0, "__END__"),
            ParseItem("T", grammar.rule("T"), 0, "+"),
            ParseItem("E", grammar.rule("E"), 0, "__END__"),
        })));

        ParseItemSet next_item_set = *sym_transitions(item_set, grammar)[rules::Symbol("v")];
        AssertThat(next_item_set, Equals(ParseItemSet({
            ParseItem("F", rules::blank(), 1, "__END__"),
            ParseItem("F", rules::blank(), 1, "*"),
            ParseItem("F", rules::blank(), 1, "+"),
        })));
    });
});

END_TEST