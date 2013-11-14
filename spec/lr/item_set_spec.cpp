#include "spec_helper.h"
#include "../test_grammars/arithmetic.h"

using namespace tree_sitter::lr;

Describe(item_sets) {
    Grammar grammar = test_grammars::arithmetic();
    
    It(computes_the_closure_of_an_item_set_under_symbol_expansion) {
        Item item = Item::at_beginning_of_rule("term", grammar);
        ItemSet item_set = ItemSet({ item }).closure_in_grammar(grammar);
        
        AssertThat(
                   item_set,
                   EqualsContainer(ItemSet({
            Item("term", grammar.rule("term"), 0),
            Item("factor", grammar.rule("factor"), 0),
            Item("variable", grammar.rule("variable"), 0),
            Item("number", grammar.rule("number"), 0),
            Item("left_paren", grammar.rule("left_paren"), 0),
        })));
    }
};
