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
        { "C", choice({ i_sym(0), i_sym(1) }) },
    }, {});

    it("includes all of the starting non-terminals for the item, and their following terminals", [&]() {
        ParseItem item(Symbol(2), choice({
            seq({ i_sym(0), choice({ i_token(0), i_token(1) }) }),
            seq({ i_sym(1), i_token(2) }),
        }), 0);

        AssertThat(follow_sets(item, { Symbol(10, SymbolOptionToken) }, grammar), Equals(map<Symbol, set<Symbol>>({
            { Symbol(0), set<Symbol>({
                Symbol(0, SymbolOptionToken),
                Symbol(1, SymbolOptionToken) }) },
            { Symbol(1), set<Symbol>({
                Symbol(2, SymbolOptionToken) }) },
        })));
    });

    it("does not include terminals at the beginning of the item", [&]() {
        ParseItem item(Symbol(2), choice({
            seq({ i_sym(0), choice({ i_token(0), i_token(1) }) }),
            seq({ i_token(2), i_token(3) }),
        }), 0);

        AssertThat(follow_sets(item, { Symbol(10, SymbolOptionToken) }, grammar), Equals(map<Symbol, set<Symbol>>({
            { Symbol(0), set<Symbol>({
                Symbol(0, SymbolOptionToken),
                Symbol(1, SymbolOptionToken) }) },
        })));
    });

    it("includes the item's lookahead symbol if the rule after the non-terminal might be blank", [&]() {
        ParseItem item(Symbol(2), choice({
            seq({ i_sym(0), choice({ i_token(0), blank() }) }),
        }), 0);

        AssertThat(follow_sets(item, { Symbol(10, SymbolOptionToken) }, grammar), Equals(map<Symbol, set<Symbol>>({
            { Symbol(0), set<Symbol>({
                Symbol(0, SymbolOptionToken),
                Symbol(10, SymbolOptionToken) }) },
        })));
    });
});

END_TEST
