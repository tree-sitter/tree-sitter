#include "spec_helper.h"
#include "prepare_grammar/expand_repeats.h"

START_TEST

using prepare_grammar::expand_repeats;
using namespace rules;

describe("expanding repeat rules in a grammar", []() {
    it("replaces repeat rules with pairs of recursive rules", [&]() {
        Grammar result = expand_repeats(Grammar({
            { "rule1", seq({
                sym("x"),
                repeat(seq({ sym("a"), sym("b") })),
                sym("y")
            }) },
        }));
        
        AssertThat(result, Equals(Grammar("rule1", {
            { "rule1", seq({
                sym("x"),
                aux_sym("repeat_helper1"),
                sym("y")
            }) },
        }, {
            { "repeat_helper1", seq({
                seq({ sym("a"), sym("b") }),
                choice({
                    aux_sym("repeat_helper1") ,
                    blank()
                }),
            }) }
        })));
    });
});

END_TEST