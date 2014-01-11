#include "spec_helper.h"
#include "rule_transitions.h"

using build_tables::rule_transitions;

START_TEST

describe("rule transitions", []() {
    rules::rule_ptr symbol1 = rules::sym("1");
    rules::rule_ptr symbol2 = rules::sym("2");
    rules::rule_ptr symbol3 = rules::sym("3");
    rules::rule_ptr symbol4 = rules::sym("4");
    rules::rule_ptr char1 = rules::character('a');
    
    it("handles symbols", [&]() {
        AssertThat(
            rule_transitions(symbol1),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { symbol1, rules::blank() }
            })));
    });
    
    it("handles characters", [&]() {
        AssertThat(
            rule_transitions(char1),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { char1, rules::blank() }
            })));
    });
    
    it("handles character classes", [&]() {
        auto rule = rules::character(CharClassDigit);
        AssertThat(
            rule_transitions(rule),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { rule, rules::blank() }
            })));
    });
    
    it("handles choices", [&]() {
        AssertThat(
            rule_transitions(rules::choice({ symbol1, symbol2 })),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { symbol1, rules::blank() },
                { symbol2, rules::blank() }
            })));
    });
    
    it("handles sequences", [&]() {
        AssertThat(
            rule_transitions(rules::seq({ symbol1, symbol2 })),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { symbol1, symbol2 }
            })));
    });
    
    it("handles_long_sequences", [&]() {
        AssertThat(
            rule_transitions(rules::seq({
                symbol1,
                symbol2,
                symbol3,
                symbol4
            })),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { symbol1, rules::seq({ symbol2, symbol3, symbol4 }) }
            })));
    });
    
    it("handles choices with common starting symbols", [&]() {
        AssertThat(
            rule_transitions(
                rules::choice({
                    rules::seq({ symbol1, symbol2 }),
                    rules::seq({ symbol1, symbol3 }) })),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { symbol1, rules::choice({ symbol2, symbol3 }) }
            })));
    });
    
    it("handles strings", [&]() {
        AssertThat(
            rule_transitions(rules::str("bad")),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { rules::character('b'), rules::seq({ rules::character('a'), rules::character('d') })
            }
        })));
    });
    
    it("handles patterns", [&]() {
        AssertThat(
            rule_transitions(rules::pattern("a|b")),
            Equals(transition_map<rules::Rule, rules::Rule>({
                { rules::character('a'), rules::blank() },
                { rules::character('b'), rules::blank() }
            })));
    });
    
    it("handles repeats", [&]() {
        rules::rule_ptr repeat = rules::repeat(rules::str("ab"));
        AssertThat(
            rule_transitions(repeat),
            Equals(transition_map<rules::Rule, rules::Rule>({
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
        
        repeat = rules::repeat(rules::str("a"));
        AssertThat(
            rule_transitions(repeat),
            Equals(transition_map<rules::Rule, rules::Rule>({
            {
                rules::character('a'),
                rules::choice({
                    repeat,
                    rules::blank()
                })
            }})));
    });
});

END_TEST
