#include "spec_helper.h"
#include "rules.h"
#include "transition_map.h"

Describe(Rules) {
    Describe(construction) {
        rules::rule_ptr symbol1 = rules::sym("1");
        rules::rule_ptr symbol2 = rules::sym("2");
        rules::rule_ptr symbol3 = rules::sym("3");

        It(constructs_binary_trees) {
            AssertThat(
                rules::seq({ symbol1, symbol2, symbol3 })->to_string(),
                Equals(std::string("(seq (seq (sym '1') (sym '2')) (sym '3'))")));

            AssertThat(
                rules::choice({ symbol1, symbol2, symbol3 })->to_string(),
                Equals(std::string("(choice (choice (sym '1') (sym '2')) (sym '3'))")));
        }
    };
    
    Describe(transitions) {
        rules::rule_ptr symbol1 = rules::sym("1");
        rules::rule_ptr symbol2 = rules::sym("2");
        rules::rule_ptr symbol3 = rules::sym("3");
        rules::rule_ptr symbol4 = rules::sym("3");
        rules::rule_ptr char1 = rules::character('a');

        It(handles_symbols) {
            AssertThat(
                symbol1->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { symbol1, rules::blank() }
                })));
        }

        It(handles_characters) {
            AssertThat(
                char1->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { char1, rules::blank() }
                })));
        }

        It(handles_choices) {
            AssertThat(
                rules::choice({ symbol1, symbol2 })->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { symbol1, rules::blank() },
                    { symbol2, rules::blank() }
                })));
        }

        It(handles_sequences) {
            AssertThat(
                rules::seq({ symbol1, symbol2 })->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { symbol1, symbol2 }
                })));
        }

        It(handles_long_sequences) {
            AssertThat(
                rules::seq({
                    symbol1,
                    symbol2,
                    symbol3,
                    symbol4
                })->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { symbol1, rules::seq({ symbol2, symbol3, symbol4 }) }
                })));
        }

        It(handles_choices_with_common_starting_symbols) {
            AssertThat(
                rules::choice({
                    rules::seq({ symbol1, symbol2 }),
                    rules::seq({ symbol1, symbol3 }) })->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { symbol1, rules::choice({ symbol2, symbol3 }) }
                })));
        }

        It(handles_strings) {
            AssertThat(
                rules::str("bad")->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    {
                        rules::character('b'),
                        rules::seq({ rules::character('a'), rules::character('d') })
                    }
                })));
        }

        It(handles_patterns) {
            AssertThat(
                rules::pattern("a|b")->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                    { rules::character('a'), rules::blank() },
                    { rules::character('b'), rules::blank() }
                })));
        }
        
        It(handles_repeats) {
            rules::rule_ptr repeat = rules::repeat(rules::str("ab"));
            AssertThat(
                repeat->transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>({
                {
                    rules::character('a'),
                    rules::seq({
                        rules::character('b'),
                        rules::choice({
                            repeat,
                            rules::blank()
                        })
                    })
                }})));
        }
    };
};
