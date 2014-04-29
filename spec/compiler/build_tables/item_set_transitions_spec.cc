#include "compiler_spec_helper.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("lexical item set transitions", []() {
    PreparedGrammar grammar({}, {});

    describe("when two items in the set have transitions on the same character", [&]() {
        it("merges the transitions by computing the union of the two item sets", [&]() {
            LexItemSet set1({
                LexItem(Symbol(1), pattern("[a-f]")),
                LexItem(Symbol(2), pattern("[e-x]")) });

            AssertThat(char_transitions(set1, grammar), Equals(map<CharacterSet, LexItemSet>({
                { CharacterSet({ {'a', 'd'} }), LexItemSet({
                    LexItem(Symbol(1), blank()) }) },
                { CharacterSet({ {'e', 'f'} }), LexItemSet({
                    LexItem(Symbol(1), blank()),
                    LexItem(Symbol(2), blank()) }) },
                { CharacterSet({ {'g', 'x'} }), LexItemSet({
                    LexItem(Symbol(2), blank()) }) },
            })));
        });
    });
});

describe("syntactic item set transitions", [&]() {
    PreparedGrammar grammar({
        { "A", blank() },
        { "B", i_token(21) },
    }, {});
    
    it("computes the closure of the new item sets", [&]() {
        ParseItemSet set1({
            ParseItem(Symbol(0), seq({ i_token(22), i_sym(1) }), 3, Symbol(23, SymbolOptionToken)),
        });
        
        SymTransitions sym_transitions;
        
        AssertThat(sym_transitions(set1, grammar), Equals(map<Symbol, ParseItemSet>({
            { Symbol(22, SymbolOptionToken), ParseItemSet({
                ParseItem(Symbol(0), i_sym(1), 4, Symbol(23, SymbolOptionToken)),
                ParseItem(Symbol(1), i_token(21), 0, Symbol(23, SymbolOptionToken))
            }) },
        })));
    });
});

END_TEST