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

END_TEST