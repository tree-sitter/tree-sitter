#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepared_grammar.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_tokens;
using prepare_grammar::InternedGrammar;

describe("extracting tokens from a grammar", []() {
    it("moves string rules into the lexical grammar", [&]() {
        pair<SyntaxGrammar, LexicalGrammar> result = extract_tokens(InternedGrammar{
            {
                { "rule_A", seq({ str("ab"), i_sym(0) }) }
            },
            {},
            {}
        });

        AssertThat(result.first.rules, Equals(rule_list({
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        })));
        AssertThat(result.first.aux_rules, IsEmpty())
        AssertThat(result.second.rules, IsEmpty())
        AssertThat(result.second.aux_rules, Equals(rule_list({
            { "'ab'", str("ab") },
        })));
    });

    it("moves pattern rules into the lexical grammar", [&]() {
        pair<SyntaxGrammar, LexicalGrammar> result = extract_tokens(InternedGrammar{
            {
                { "rule_A", seq({ pattern("a+"), i_sym(0) }) }
            },
            {},
            {}
        });

        AssertThat(result.first.rules, Equals(rule_list({
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        })));
        AssertThat(result.first.aux_rules, IsEmpty())
        AssertThat(result.second.rules, IsEmpty())
        AssertThat(result.second.aux_rules, Equals(rule_list({
            { "/a+/", pattern("a+") },
        })));
    });

    it("moves other rules marked as tokens into the lexical grammar", [&]() {
        pair<SyntaxGrammar, LexicalGrammar> result = extract_tokens(InternedGrammar{
            {
                { "rule_A", seq({
                    token(seq({ pattern("."), choice({ str("a"), str("b") }) })),
                    i_sym(0) }) }
            },
            {},
            {}
        });

        AssertThat(result.first.rules, Equals(rule_list({
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        })));
        AssertThat(result.first.aux_rules, IsEmpty())
        AssertThat(result.second.rules, IsEmpty())
        AssertThat(result.second.aux_rules, Equals(rule_list({
            { "(seq /./ (choice 'a' 'b'))", token(seq({ pattern("."), choice({ str("a"), str("b") }) })) },
        })));
    });

    it("does not extract blanks", [&]() {
        pair<SyntaxGrammar, LexicalGrammar> result = extract_tokens(InternedGrammar{
            {
                { "rule_A", choice({ i_sym(0), blank() }) },
            },
            {},
            {}
        });

        AssertThat(result.first.rules, Equals(rule_list({
            { "rule_A", choice({ i_sym(0), blank() }) },
        })));
        AssertThat(result.first.aux_rules, IsEmpty())
        AssertThat(result.second.rules, IsEmpty())
        AssertThat(result.second.aux_rules, IsEmpty())
    });

    it("does not create duplicate tokens in the lexical grammar", [&]() {
        pair<SyntaxGrammar, LexicalGrammar> result = extract_tokens(InternedGrammar{
            {
                { "rule_A", seq({ str("ab"), i_sym(0), str("ab") }) },
            },
            {},
            {}
        });

        AssertThat(result.first.rules, Equals(rule_list({
            { "rule_A", seq({ i_aux_token(0), i_sym(0), i_aux_token(0) }) }
        })));
        AssertThat(result.first.aux_rules, IsEmpty())
        AssertThat(result.second.rules, IsEmpty())
        AssertThat(result.second.aux_rules, Equals(rule_list({
            { "'ab'", str("ab") },
        })))
    });

    describe("when an entire rule can be extracted", [&]() {
        it("moves the rule the lexical grammar when possible and updates referencing symbols", [&]() {
            auto result = extract_tokens(InternedGrammar{
                {
                    { "rule_A", i_sym(1) },
                    { "rule_B", pattern("a|b") },
                    { "rule_C", token(seq({ str("a"), str("b") })) },
                },
                {},
                {}
            });

            AssertThat(result.first.rules, Equals(rule_list({
                { "rule_A", i_token(0) }
            })));
            AssertThat(result.first.aux_rules, IsEmpty());
            AssertThat(result.second.rules, Equals(rule_list({
                { "rule_B", pattern("a|b") },
                { "rule_C", token(seq({ str("a"), str("b") })) },
            })));
            AssertThat(result.second.aux_rules, IsEmpty());
        });

        it("updates symbols whose indices need to change due to deleted rules", [&]() {
            auto result = extract_tokens(InternedGrammar{
                {
                    { "rule_A", str("ab") },
                    { "rule_B", i_sym(0) },
                    { "rule_C", i_sym(1) },
                },
                {},
                {}
            });

            AssertThat(result.first.rules, Equals(rule_list({
                { "rule_B", i_token(0) },
                { "rule_C", i_sym(0) },
            })));
            AssertThat(result.first.aux_rules, IsEmpty());
            AssertThat(result.second.rules, Equals(rule_list({
                { "rule_A", str("ab") },
            })));
            AssertThat(result.second.aux_rules, IsEmpty());
        });

        it("updates the grammar's ubiquitous_tokens", [&]() {
            auto result = extract_tokens(InternedGrammar{
                {
                    { "rule_A", str("ab") },
                    { "rule_B", i_sym(0) },
                    { "rule_C", i_sym(1) },
                },
                { Symbol(0) },
                {}
            });

            AssertThat(result.first.ubiquitous_tokens, Equals(vector<Symbol>({
                { Symbol(0, SymbolOptionToken) }
            })));
        });
    });
});

END_TEST
