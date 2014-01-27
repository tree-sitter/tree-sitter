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
            ParseItem(Symbol("E"), grammar.rule(Symbol("E")), 0, Symbol("__END__"))
        }), grammar);
        AssertThat(item_set, Equals(ParseItemSet({
            ParseItem(Symbol("F"), grammar.rule(Symbol("F")), 0, Symbol("__END__")),
            ParseItem(Symbol("F"), grammar.rule(Symbol("F")), 0, Symbol("+")),
            ParseItem(Symbol("F"), grammar.rule(Symbol("F")), 0, Symbol("*")),
            ParseItem(Symbol("T"), grammar.rule(Symbol("T")), 0, Symbol("__END__")),
            ParseItem(Symbol("T"), grammar.rule(Symbol("T")), 0, Symbol("+")),
            ParseItem(Symbol("E"), grammar.rule(Symbol("E")), 0, Symbol("__END__")),
        })));

        ParseItemSet next_item_set = *sym_transitions(item_set, grammar)[rules::Symbol("v")];
        AssertThat(next_item_set, Equals(ParseItemSet({
            ParseItem(Symbol("F"), rules::blank(), 1, Symbol("__END__")),
            ParseItem(Symbol("F"), rules::blank(), 1, Symbol("*")),
            ParseItem(Symbol("F"), rules::blank(), 1, Symbol("+")),
        })));
    });
});

END_TEST