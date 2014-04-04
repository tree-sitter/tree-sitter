#include "compiler_spec_helper.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("item set transitions", []() {
    PreparedGrammar grammar({}, {});

    describe("when two items in the set have transitions on the same character", [&]() {
        it("merges the transitions by computing the union of the two item sets", [&]() {
            LexItemSet set1({
                LexItem(Symbol("A"), pattern("[a-f]")),
                LexItem(Symbol("B"), pattern("[e-x]")) });
            
            AssertThat(char_transitions(set1, grammar), Equals(map<CharacterSet, LexItemSet>({
                { CharacterSet({ {'a', 'd'} }), LexItemSet({
                    LexItem(Symbol("A"), blank()) }) },
                { CharacterSet({ {'e', 'f'} }), LexItemSet({
                    LexItem(Symbol("A"), blank()),
                    LexItem(Symbol("B"), blank()) }) },
                { CharacterSet({ {'g', 'x'} }), LexItemSet({
                    LexItem(Symbol("B"), blank()) }) },
            })));
        });
    });
});

END_TEST