#include "spec_helper.h"
#include "prepare_grammar/extract_tokens.h"

START_TEST

using prepare_grammar::extract_tokens;
using namespace rules;

describe("preparing a grammar", []() {
    it("extracts character-based subtrees into a separate grammar", [&]() {
        pair<Grammar, Grammar> result = extract_tokens(Grammar({
            { "rule1", seq({
                character('a'),
                character('b'),
                seq({
                    sym("rule2"),
                    sym("rule3") }),
                seq({
                    character('a'),
                    character('b') }) }) }
        }));
        
        AssertThat(result.first, Equals(Grammar({
            { "rule1", seq({
                aux_sym("token1"),
                seq({
                    sym("rule2"),
                    sym("rule3") }),
                aux_sym("token1") }) }
        })));

        AssertThat(result.second, Equals(Grammar("", {}, {
            { "token1", rules::seq({
                rules::character('a'),
                rules::character('b') }) },
        })));
    });
    
    it("turns entire rules into tokens when they contain no symbols", [&]() {
        auto result = extract_tokens(Grammar({
            { "rule1", sym("rule2") },
            { "rule2", seq({
                character('a'),
                character('b') }) }
        }));
        
        AssertThat(result.first, Equals(Grammar({
            { "rule1", sym("rule2") }
        })));
        
        AssertThat(result.second, Equals(Grammar("", {
            { "rule2", seq({
                character('a'),
                character('b') }) },
        })));
    });
    
    it("looks inside sequences, choices and repeats", [&]() {
        auto result = extract_tokens(Grammar({
            { "rule1", seq({
                choice({
                    repeat(choice({ str("stuff"), sym("a") })),
                    sym("b"),
                }),
                sym("c") }) }
        }));
        
        AssertThat(result.first, Equals(Grammar({
            { "rule1", seq({
                choice({
                    repeat(choice({ aux_sym("token1"), sym("a") })),
                    sym("b"),
                }),
                sym("c") }) }
        })));
        
        AssertThat(result.second, Equals(Grammar("", {}, {
            { "token1", str("stuff") },
        })));
    });
});

END_TEST