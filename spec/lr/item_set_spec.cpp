#include "spec_helper.h"

Describe(item_sets) {
    Describe(transitions) {
        Grammar grammar = Grammar({
            "one",
            "two"
        }, {
            rules::sym("one"),
            rules::sym("two")
        });
        
        rules::rule_ptr rule = grammar.rules[string("one")];
        lr::Item item = lr::Item(string("one"), rule, 0);

        It(works) {
            lr::ItemSet item_set = lr::ItemSet(item, grammar);
            item_set.transitions();
        }
    };
};
