#include "spec_helper.h"
#include "prepare_grammar/perform.h"
#include "rules/symbol.h"

START_TEST

using namespace rules;
using prepare_grammar::perform;

describe("preparing a grammar", []() {
    describe("extracting tokens", []() {
        it("moves sub-rules that don't contain symbols into a separate 'lexical' grammar", [&]() {
            pair<Grammar, Grammar> result = perform(Grammar("rule1", {
                { "rule1", seq({
                    character({ 'a' }),
                    character({ 'b' }),
                    seq({
                        sym("rule2"),
                        sym("rule3") }),
                    seq({
                        character({ 'a' }),
                        character({ 'b' }) }) }) }
            }));
            
            AssertThat(result.first, Equals(Grammar("rule1", {
                { "rule1", seq({
                    make_shared<Symbol>("token1", SymbolTypeAuxiliary),
                    seq({
                        sym("rule2"),
                        sym("rule3") }),
                    make_shared<Symbol>("token1", SymbolTypeAuxiliary) }) }
            })));
            
            AssertThat(result.second, Equals(Grammar("", map<const string, const rule_ptr>(), {
                { "token1", rules::seq({
                    rules::character({ 'a' }),
                    rules::character({ 'b' }) }) },
            })));
        });
        
        it("moves entire rules into the lexical grammar when possible, preserving their names", [&]() {
            auto result = perform(Grammar("rule1", {
                { "rule1", sym("rule2") },
                { "rule2", seq({
                    character({ 'a' }),
                    character({ 'b' }) }) }
            }));
            
            AssertThat(result.first, Equals(Grammar("rule1", {
                { "rule1", sym("rule2") }
            })));
            
            AssertThat(result.second, Equals(Grammar("", {
                { "rule2", seq({
                    character({ 'a' }),
                    character({ 'b' }) }) },
            })));
        });
        
        it("moves parts of auxiliary rules into auxiliary lexical rules", []() {
            auto result = perform(Grammar("rule1", map<const string, const rule_ptr>(), {
                { "rule1", sym("rule2") },
                { "rule2", seq({
                    character({ 'a' }),
                    character({ 'b' }) }) }
            }));

            AssertThat(result.first, Equals(Grammar("rule1", map<const string, const rule_ptr>(), {
                { "rule1", sym("rule2") }
            })));
            
            AssertThat(result.second, Equals(Grammar("", map<const string, const rule_ptr>(), {
                { "rule2", seq({
                    character({ 'a' }),
                    character({ 'b' }) }) },
            })));
        });
        
        it("does not extract blanks into tokens", [&]() {
            pair<Grammar, Grammar> result = perform(Grammar("rule1", {
                { "rule1", choice({ sym("rule2"), blank() }) },
            }));
            
            AssertThat(result.first, Equals(Grammar("rule1", {
                { "rule1", choice({ sym("rule2"), blank() }) },
            })));
            
            AssertThat(result.second, Equals(Grammar("", map<const string, const rule_ptr>())));
        });
    });

    describe("expanding repeats", []() {
        it("replaces repeat rules with pairs of recursive rules", [&]() {
            Grammar result = perform(Grammar("rule1", {
                { "rule1", seq({
                    sym("x"),
                    repeat(seq({ sym("a"), sym("b") })),
                    sym("y")
                }) },
            })).first;
            
            AssertThat(result, Equals(Grammar("rule1", {
                { "rule1", seq({
                    sym("x"),
                    make_shared<Symbol>("repeat_helper1", SymbolTypeAuxiliary),
                    sym("y")
                }) },
            }, {
                { "repeat_helper1", choice({
                    seq({
                        seq({ sym("a"), sym("b") }),
                        make_shared<Symbol>("repeat_helper1", SymbolTypeAuxiliary),
                    }),
                    blank(),
                }) }
            })));
        });
        
        it("does not replace repeat rules that can be moved into the lexical grammar", [&]() {
            pair<Grammar, Grammar> result = perform(Grammar("rule1", {
                { "rule1", seq({
                    sym("x"),
                    repeat(seq({ str("a"), str("b") })),
                    sym("y")
                }) },
            }));
            
            AssertThat(result.first, Equals(Grammar("rule1", {
                { "rule1", seq({
                    sym("x"),
                    make_shared<Symbol>("token1", SymbolTypeAuxiliary),
                    sym("y")
                }) },
            })));
            
            AssertThat(result.second, Equals(Grammar("", map<const string, const rule_ptr>(), {
                { "token1", repeat(seq({ str("a"), str("b") })) },
            })));
        });
    });
});

END_TEST