#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/item_set_transitions.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("computing closures of item sets", []() {
    PreparedGrammar grammar({
        { "E", seq({
            i_sym(1),
            i_token(11) }) },
        { "T", seq({
            i_token(12),
            i_token(13) }) },
    }, {});

    it("adds items at the beginnings of referenced rules", [&]() {
        ParseItemSet item_set = item_set_closure(
            ParseItem(ISymbol(0), grammar.rule(ISymbol(0)), 0, ISymbol(10, SymbolOptionToken)),
            grammar);

        AssertThat(item_set, Equals(ParseItemSet({
            ParseItem(ISymbol(1), grammar.rule(ISymbol(1)), 0, ISymbol(11, SymbolOptionToken)),
            ParseItem(ISymbol(0), grammar.rule(ISymbol(0)), 0, ISymbol(10, SymbolOptionToken)),
        })));
    });
});

END_TEST