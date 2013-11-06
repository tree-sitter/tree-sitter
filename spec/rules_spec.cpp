#include "rules.h"
#include "transition_map.h"
#include <igloo/igloo_alt.h>

using namespace std;
using namespace igloo;
using namespace tree_sitter;
using namespace tree_sitter::rules;

Describe(Rules) {
    Describe(transitions) {
        Symbol symbol1 = Symbol(1);
        Symbol symbol2 = Symbol(2);
        Symbol symbol3 = Symbol(3);
        Symbol symbol4 = Symbol(3);
        
        It(handles_symbols) {
            AssertThat(
                symbol1.transitions(),
                EqualsContainer(TransitionMap<Rule>(
                    { symbol1.copy() },
                    { new Blank() }
                ), TransitionMap<Rule>::elements_equal));
        }

        It(handles_choices) {
            AssertThat(
                Choice(symbol1, symbol2).transitions(),
                EqualsContainer(TransitionMap<Rule>(
                    { symbol1.copy(), symbol2.copy() },
                    { new Blank(), new Blank() }
                ), TransitionMap<Rule>::elements_equal));
        }

        It(handles_sequences) {
            AssertThat(
                Seq(symbol1, symbol2).transitions(),
                EqualsContainer(TransitionMap<Rule>(
                    { symbol1.copy() },
                    { symbol2.copy() }
                ), TransitionMap<Rule>::elements_equal));
        }
        
        It(handles_long_sequences) {
            AssertThat(
                Seq(Seq(symbol1, symbol2), Seq(symbol3, symbol4)).transitions(),
                EqualsContainer(TransitionMap<Rule>(
                    { symbol1.copy() },
                    { new Seq(symbol2, Seq(symbol3, symbol4)) }
                ), TransitionMap<Rule>::elements_equal));
        }

        It(handles_choices_with_common_starting_symbols) {
            AssertThat(
                Choice(
                    Seq(symbol1, symbol2),
                    Seq(symbol1, symbol3)).transitions(),
                EqualsContainer(TransitionMap<Rule>(
                    { symbol1.copy() },
                    { new Choice(symbol2, symbol3) }
                ), TransitionMap<Rule>::elements_equal));
        }
    };
};
