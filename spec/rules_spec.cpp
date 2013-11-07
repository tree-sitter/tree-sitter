#include "spec_helper.h"
#include "rules.h"
#include "transition_map.h"

Describe(Rules) {
    Describe(transitions) {
        rules::Symbol symbol1 = rules::Symbol(1);
        rules::Symbol symbol2 = rules::Symbol(2);
        rules::Symbol symbol3 = rules::Symbol(3);
        rules::Symbol symbol4 = rules::Symbol(3);
        
        It(handles_symbols) {
            AssertThat(
                symbol1.transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>(
                    { symbol1.copy() },
                    { new rules::Blank() }
                )));
        }
        
        It(handles_characters) {
            rules::Char char1 = rules::Char('a');
            AssertThat(
                char1.transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>(
                    { char1.copy() },
                    { new rules::Blank() }
                )));
        }

        It(handles_choices) {
            AssertThat(
                rules::Choice(symbol1, symbol2).transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>(
                    { symbol1.copy(), symbol2.copy() },
                    { new rules::Blank(), new rules::Blank() }
                )));
        }

        It(handles_sequences) {
            AssertThat(
                rules::Seq(symbol1, symbol2).transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>(
                    { symbol1.copy() },
                    { symbol2.copy() }
                )));
        }
        
        It(handles_long_sequences) {
            AssertThat(
                rules::Seq(
                    rules::Seq(symbol1, symbol2),
                    rules::Seq(symbol3, symbol4)).transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>(
                    { symbol1.copy() },
                    { new rules::Seq(symbol2, rules::Seq(symbol3, symbol4)) }
                )));
        }

        It(handles_choices_with_common_starting_symbols) {
            AssertThat(
                rules::Choice(
                    rules::Seq(symbol1, symbol2),
                    rules::Seq(symbol1, symbol3)).transitions(),
                EqualsTransitionMap(TransitionMap<rules::Rule>(
                    { symbol1.copy() },
                    { new rules::Choice(symbol2, symbol3) }
                )));
        }
    };
};
