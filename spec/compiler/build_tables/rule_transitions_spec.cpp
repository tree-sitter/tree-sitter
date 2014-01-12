#include "spec_helper.h"
#include "rule_transitions.h"

using build_tables::rule_transitions;
using namespace rules;

START_TEST

describe("rule transitions", []() {
    rule_ptr symbol1 = sym("1");
    rule_ptr symbol2 = sym("2");
    rule_ptr symbol3 = sym("3");
    rule_ptr symbol4 = sym("4");
    rule_ptr char1 = character('a');
    
    it("handles symbols", [&]() {
        AssertThat(
            rule_transitions(symbol1),
            Equals(transition_map<Rule, Rule>({
                { symbol1, blank() }
            })));
    });
    
    it("handles characters", [&]() {
        AssertThat(
            rule_transitions(char1),
            Equals(transition_map<Rule, Rule>({
                { char1, blank() }
            })));
    });
    
    it("handles character classes", [&]() {
        auto rule = character(CharClassDigit);
        AssertThat(
            rule_transitions(rule),
            Equals(transition_map<Rule, Rule>({
                { rule, blank() }
            })));
    });
    
    it("handles choices", [&]() {
        AssertThat(
            rule_transitions(choice({ symbol1, symbol2 })),
            Equals(transition_map<Rule, Rule>({
                { symbol1, blank() },
                { symbol2, blank() }
            })));
    });
    
    it("handles sequences", [&]() {
        AssertThat(
            rule_transitions(seq({ symbol1, symbol2 })),
            Equals(transition_map<Rule, Rule>({
                { symbol1, symbol2 }
            })));
    });
    
    it("handles_long_sequences", [&]() {
        AssertThat(
            rule_transitions(seq({
                symbol1,
                symbol2,
                symbol3,
                symbol4
            })),
            Equals(transition_map<Rule, Rule>({
                { symbol1, seq({ symbol2, symbol3, symbol4 }) }
            })));
    });
    
    it("handles choices with common starting symbols", [&]() {
        AssertThat(
            rule_transitions(
                choice({
                    seq({ symbol1, symbol2 }),
                    seq({ symbol1, symbol3 }) })),
            Equals(transition_map<Rule, Rule>({
                { symbol1, choice({ symbol2, symbol3 }) }
            })));
    });
    
    it("handles strings", [&]() {
        AssertThat(
            rule_transitions(str("bad")),
            Equals(transition_map<Rule, Rule>({
                { character('b'), seq({ character('a'), character('d') })
            }
        })));
    });
    
    it("handles patterns", [&]() {
        AssertThat(
            rule_transitions(pattern("a|b")),
            Equals(transition_map<Rule, Rule>({
                { character('a'), blank() },
                { character('b'), blank() }
            })));
    });
    
    it("handles repeats", [&]() {
        rule_ptr rule = repeat(str("ab"));
        AssertThat(
            rule_transitions(rule),
            Equals(transition_map<Rule, Rule>({
            {
                character('a'),
                seq({
                    character('b'),
                    choice({
                        rule,
                        blank()
                    })
                })
            }})));
        
        rule = repeat(str("a"));
        AssertThat(
            rule_transitions(rule),
            Equals(transition_map<Rule, Rule>({
            {
                character('a'),
                choice({
                    rule,
                    blank()
                })
            }})));
    });
});

END_TEST
