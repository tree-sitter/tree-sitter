#include "spec_helper.h"
#include "rules/pattern.h"
#include "rules/character_set.h"

using namespace rules;

START_TEST

describe("parsing pattern rules", []() {
    it("parses simple strings", [&]() {
        Pattern rule("abc");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character({ 'a' }),
                character({ 'b' }),
                character({ 'c' })
            })));
    });

    it("parses character classes", []() {
        Pattern rule("\\w-\\d");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character({ {'a', 'z'}, {'A', 'Z'} }),
                character({ '-' }),
                character({ {'0', '9'} })
            })));
    });

    it("parses choices", []() {
        Pattern rule("ab|cd|ef");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(choice({
                seq({
                    character({ 'a' }),
                    character({ 'b' }),
                }),
                seq({
                    character({ 'c' }),
                    character({ 'd' })
                }),
                seq({
                    character({ 'e' }),
                    character({ 'f' })
                })
            })));
    });
    
    it("parses character sets", []() {
        Pattern rule("[aAeE]");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(character({ 'a', 'A', 'e', 'E' })));
    });
    
    it("parses character ranges", []() {
        Pattern rule("[12a-dA-D3]");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(character({ {'1', '3'}, {'a', 'd'}, { 'A', 'D' }, })));
    });
    
    it("parses negated characters", []() {
        Pattern rule("[^a\\d]");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(character({ {'a'}, {'0', '9'} }, false)));
    });
    
    it("parses backslashes", []() {
        Pattern rule("\\\\");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(character({ '\\' })));
    });
    
    it("parses character groups in sequences", []() {
        Pattern rule("\"([^\"]|\\\\\")+\"");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character({ '"' }),
                repeat(choice({
                    character({ '"' }, false),
                    seq({ character({ '\\' }), character({ '"' }) })
                })),
                character({ '"' })
            })));
    });
    
    it("parses choices in sequences", []() {
        Pattern rule("(a|b)cd");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                choice({
                    character({ 'a' }),
                    character({ 'b' }),
                }),
                character({ 'c' }),
                character({ 'd' })
            })));
    });
    
    it("parses special characters when they are escaped", []() {
        Pattern rule("a\\(b");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(seq({
                character({ 'a' }),
                character({ '(' }),
                character({ 'b' })
            })));
    });
    
    it("parses repeating rules", []() {
        Pattern rule("(ab)+(cd)+");
        AssertThat(
            rule.to_rule_tree(),
            EqualsPointer(
                seq({
                    repeat(seq({
                        character({ 'a' }),
                        character({ 'b' })
                    })),
                    repeat(seq({
                        character({ 'c' }),
                        character({ 'd' })
                    })),
                })
            ));
    });
});

END_TEST
