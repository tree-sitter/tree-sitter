#include "spec_helper.h"
#include "rule_transitions.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("rule transitions", []() {
    auto symbol1 = sym("1");
    auto symbol2 = sym("2");
    auto symbol3 = sym("3");
    auto symbol4 = sym("4");
    auto char1 = character({ 'a' });
    
    it("handles symbols", [&]() {
        AssertThat(
            sym_transitions(symbol1),
            Equals(transition_map<Symbol, Rule>({
                { symbol1, blank() }
            })));
    });
    
    it("handles choices", [&]() {
        AssertThat(
            sym_transitions(choice({ symbol1, symbol2 })),
            Equals(transition_map<Symbol, Rule>({
                { symbol1, blank() },
                { symbol2, blank() }
            })));
    });
    
    it("handles sequences", [&]() {
        AssertThat(
            sym_transitions(seq({ symbol1, symbol2 })),
            Equals(transition_map<Symbol, Rule>({
                { symbol1, symbol2 }
            })));
    });
    
    it("handles long sequences", [&]() {
        AssertThat(
            sym_transitions(seq({
                symbol1,
                symbol2,
                symbol3,
                symbol4
            })),
            Equals(transition_map<Symbol, Rule>({
                { symbol1, seq({ symbol2, symbol3, symbol4 }) }
            })));
    });
    
    it("handles sequences whose left sides can be blank", [&]() {
        AssertThat(
            sym_transitions(seq({
                choice({
                    symbol1,
                    blank(),
                }),
                seq({
                    symbol1,
                    symbol2
                })
            })), Equals(transition_map<Symbol, Rule>({
                { symbol1, choice({ seq({ symbol1, symbol2 }), symbol2, }) }
            })));
    });
    
    it("handles choices with common starting symbols", [&]() {
        AssertThat(
            sym_transitions(
                choice({
                    seq({ symbol1, symbol2 }),
                    seq({ symbol1, symbol3 }) })),
            Equals(transition_map<Symbol, Rule>({
                { symbol1, choice({ symbol2, symbol3 }) }
            })));
    });
    
    it("handles characters", [&]() {
        AssertThat(
            char_transitions(char1),
            Equals(transition_map<CharacterSet, Rule>({
                { char1, blank() }
            })));
    });
    
    it("handles strings", [&]() {
        AssertThat(
            char_transitions(str("bad")),
            Equals(transition_map<CharacterSet, Rule>({
                { character({ 'b' }, true), seq({ character('a'), character('d') }) }
            })));
    });
    
    it("handles patterns", [&]() {
        AssertThat(
            char_transitions(pattern("a|b")),
            Equals(transition_map<CharacterSet, Rule>({
                { character({ 'a' }, true), blank() },
                { character({ 'b' }, true), blank() }
            })));
    });
    
    it("handles repeats", [&]() {
        rule_ptr rule = repeat(str("ab"));
        AssertThat(
            char_transitions(rule),
            Equals(transition_map<CharacterSet, Rule>({
            {
                character({ 'a' }, true),
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
            char_transitions(rule),
            Equals(transition_map<CharacterSet, Rule>({
            {
                character({ 'a' }, true),
                choice({
                    rule,
                    blank()
                })
            }})));
    });

    describe("regression tests (somewhat redundant, should maybe be deleted later)", []() {
        it("handles sequences that start with repeating characters", [&]() {
            auto rule = seq({
                choice({
                    repeat(character({ '"' }, false)),
                    blank(),
                }),
                character('"'),
            });
            
            AssertThat(char_transitions(rule), Equals(transition_map<CharacterSet, Rule>({
                { character({ '"' }, false), seq({
                    choice({
                        repeat(character({ '"' }, false)),
                        blank(),
                    }),
                    character('"'), }) },
                { character({ '"' }, true), blank() },
            })));
        });
    });
});

describe("checking if rules can be blank", [&]() {
    it("handles sequences", [&]() {
        rule_ptr rule = seq({
            choice({
                str("x"),
                blank(),
            }),
            str("y"),
        });
        
        AssertThat(rule_can_be_blank(rule), Equals(false));
    });
});

END_TEST
