#include "spec_helper.h"

using namespace tree_sitter::lr;

START_TEST

describe("items", []() {
    describe("construction", [&]() {
        it("finds the item at the start of a rule", [&]() {
            Grammar grammar = test_grammars::arithmetic();
            Item item = Item::at_beginning_of_rule("expression", grammar);
            AssertThat(item, Equals(Item("expression", grammar.rule("expression"), 0)));
        });
    });
    
    describe("transitions", [&]() {
        it("computes the possible advancements", [&]() {
            auto char1 = rules::character('a');
            auto char2 = rules::character('b');
            Item item = Item("my-rule", rules::seq({ char1, char2 }), 2);

            AssertThat(
                item.transitions(),
                Equals(transition_map<rules::Rule, Item>({
                    { char1, make_shared<Item>("my-rule", char2, 3) }
                })));
        });
    });
});

END_TEST