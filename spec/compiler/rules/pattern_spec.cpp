#include "spec_helper.h"
#include "rules.h"
#include "transition_map.h"

using namespace tree_sitter::rules;

START_TEST

describe("parsing pattern rules", []() {
    it("parses simple strings", [&]() {
        Pattern rule("abc");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                character('a'),
                character('b'),
                character('c')
            })->to_string()));
    });

    it("parses character classes", []() {
        Pattern rule("\\w-\\d");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                character(CharClassWord),
                character('-'),
                character(CharClassDigit)
            })->to_string()));
    });

    it("parses choices", []() {
        Pattern rule("ab|cd|ef");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(choice({
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
            })->to_string()));
    });
    
    it("parses choices in sequences", []() {
        Pattern rule("(a|b)cd");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                choice({
                    character('a'),
                    character('b'),
                }),
                character('c'),
                character('d')
            })->to_string()));
    });
    
    it("parses special characters when they are escaped", []() {
        Pattern rule("a\\(b");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                character('a'),
                character('('),
                character('b')
            })->to_string()));
    });
    
    it("parses repeating rules", []() {
        Pattern rule("(ab)+(cd)+");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(
                seq({
                    repeat(seq({
                        character('a'),
                        character('b')
                    })),
                    repeat(seq({
                        character('c'),
                        character('d')
                    })),
                })->to_string()
            ));
    });
});

END_TEST
