#include "spec_helper.h"
#include "rules.h"
#include "transition_map.h"

using namespace tree_sitter::rules;

Describe(pattern_rules) {
    It(parses_simple_strings) {
        Pattern rule("abc");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                character('a'),
                character('b'),
                character('c')
            })->to_string()));
    };

    It(parses_character_classes) {
        Pattern rule("\\w-\\d");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                character(CharClassWord),
                character('-'),
                character(CharClassDigit)
            })->to_string()));
    };

    It(parses_choices) {
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
    };
    
    It(parses_choices_in_sequences) {
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
    };
    
    It(parses_special_characters_when_they_are_escaped) {
        Pattern rule("a\\(b");
        AssertThat(
            rule.to_rule_tree()->to_string(),
            Equals(seq({
                character('a'),
                character('('),
                character('b')
            })->to_string()));
    }
    
    It(parses_repeating_rules) {
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
    }
};