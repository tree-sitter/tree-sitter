#include "spec_helper.h"

using namespace tree_sitter::lr;

START_TEST

describe("items", []() {
    Grammar grammar = test_grammars::arithmetic();
    
    describe("transitions", [&]() {
        it("finds the item at the start of a rule", [&]() {
            Item item = Item::at_beginning_of_rule("expression", grammar);
            AssertThat(item, Equals(Item("expression", grammar.rule("expression"), 0)));
        });
    });
});

END_TEST