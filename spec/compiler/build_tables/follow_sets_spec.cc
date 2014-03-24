#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/follow_sets.h"

using std::set;
using namespace build_tables;
using namespace rules;

START_TEST

describe("computing FOLLOW sets", []() {
    const PreparedGrammar grammar({
        { "A", sym("a") },
        { "B", sym("b") },
    }, {});

    it("includes all of the starting non-terminals for the item, and their following terminals", [&]() {
        ParseItem item(Symbol("C"), choice({
            seq({ sym("A"), choice({ sym("x"), sym("y") }) }),
            seq({ sym("B"), sym("z") }),
        }), {}, Symbol("w"));

        AssertThat(follow_sets(item, grammar), Equals(map<Symbol, set<Symbol>>({
            { Symbol("A"), set<Symbol>({ Symbol("x"), Symbol("y") }) },
            { Symbol("B"), set<Symbol>({ Symbol("z") }) },
        })));
    });

    it("does not include terminals at the beginning of the item", [&]() {
        ParseItem item(Symbol("C"), choice({
            seq({ sym("A"), choice({ sym("x"), sym("y") }) }),
            seq({ sym("x"), sym("y") }),
        }), {}, Symbol("w"));

        AssertThat(follow_sets(item, grammar), Equals(map<Symbol, set<Symbol>>({
            { Symbol("A"), set<Symbol>({ Symbol("x"), Symbol("y") }) },
        })));
    });

    it("includes the item's lookahead terminal if the rule after the non-terminal might be blank", [&]() {
        ParseItem item(Symbol("C"), choice({
            seq({ sym("A"), choice({ sym("x"), blank() }) }),
        }), {}, Symbol("w"));

        AssertThat(follow_sets(item, grammar), Equals(map<Symbol, set<Symbol>>({
            { Symbol("A"), set<Symbol>({ Symbol("x"), Symbol("w") }) },
        })));
    });
});

END_TEST
