#include "spec_helper.h"
#include "../../fixtures/grammars/arithmetic.h"

using namespace tree_sitter::lr;

Describe(items) {
    Describe(transitions) {
        Grammar grammar = test_grammars::arithmetic();
        
        It(finds_the_item_at_the_start_of_a_rule) {
            Item item = Item::at_beginning_of_rule("expression", grammar);
            AssertThat(item, Equals(Item("expression", grammar.rule("expression"), 0)));
        }
    };
};
