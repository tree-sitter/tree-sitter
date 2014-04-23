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
        ParseItem item(ISymbol(2), choice({
            seq({ i_sym(0), choice({ i_token(0), i_token(1) }) }),
            seq({ i_sym(1), i_token(2) }),
        }), 0, ISymbol(10, SymbolOptionToken));

        AssertThat(follow_sets(item, grammar), Equals(map<ISymbol, set<ISymbol>>({
            { ISymbol(0), set<ISymbol>({
                ISymbol(0, SymbolOptionToken),
                ISymbol(1, SymbolOptionToken) }) },
            { ISymbol(1), set<ISymbol>({
                ISymbol(2, SymbolOptionToken) }) },
        })));
    });

    it("does not include terminals at the beginning of the item", [&]() {
        ParseItem item(ISymbol(2), choice({
            seq({ i_sym(0), choice({ i_token(0), i_token(1) }) }),
            seq({ i_token(2), i_token(3) }),
        }), 0, ISymbol(10, SymbolOptionToken));

        AssertThat(follow_sets(item, grammar), Equals(map<ISymbol, set<ISymbol>>({
            { ISymbol(0), set<ISymbol>({
                ISymbol(0, SymbolOptionToken),
                ISymbol(1, SymbolOptionToken) }) },
        })));
    });

    it("includes the item's lookahead terminal if the rule after the non-terminal might be blank", [&]() {
        ParseItem item(ISymbol(2), choice({
            seq({ i_sym(0), choice({ i_token(0), blank() }) }),
        }), 0, ISymbol(10, SymbolOptionToken));

        AssertThat(follow_sets(item, grammar), Equals(map<ISymbol, set<ISymbol>>({
            { ISymbol(0), set<ISymbol>({
                ISymbol(0, SymbolOptionToken),
                ISymbol(10, SymbolOptionToken) }) },
        })));
    });
});

END_TEST
