#include "spec_helper.h"
#include "rules.h"

using namespace rules;

START_TEST

describe("parsing pattern rules", []() {
    it("parses simple strings", [&]() {
        Pattern rule("abc");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character('a'),
                character('b'),
                character('c')
            })));
    });

    it("parses character classes", []() {
        Pattern rule("\\w-\\d");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character(CharClassWord),
                character('-'),
                character(CharClassDigit)
            })));
    });

    it("parses choices", []() {
        Pattern rule("ab|cd|ef");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(choice({
                seq({
                    character('a'),
                    character('b'),
                }),
                seq({
                    character('c'),
                    character('d')
                }),
                seq({
                    character('e'),
                    character('f')
                })
            })));
    });
    
    it("parses choices in sequences", []() {
        Pattern rule("(a|b)cd");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                choice({
                    character('a'),
                    character('b'),
                }),
                character('c'),
                character('d')
            })));
    });
    
    it("parses special characters when they are escaped", []() {
        Pattern rule("a\\(b");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character('a'),
                character('('),
                character('b')
            })));
    });
    
    it("parses repeating rules", []() {
        Pattern rule("(ab)+(cd)+");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(
                seq({
                    repeat(seq({
                        character('a'),
                        character('b')
                    })),
                    repeat(seq({
                        character('c'),
                        character('d')
                    })),
                })
            ));
    });
});

END_TEST
