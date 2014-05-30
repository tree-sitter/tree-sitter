#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/expand_tokens.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_tokens;

describe("expanding token rules", []() {
    it("replaces regex patterns with their expansion", [&]() {
        PreparedGrammar grammar({
            { "rule_A", seq({
                i_sym(10),
                pattern("x*"),
                i_sym(11) }) },
        }, {});

        auto result = expand_tokens(grammar);

        AssertThat(result.second, Equals((const GrammarError *)nullptr));
        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", seq({
                i_sym(10),
                repeat(character({ 'x' })),
                i_sym(11) }) },
        }, {})));
    });

    it("replaces string rules with a sequence of characters", [&]() {
        PreparedGrammar grammar({
            { "rule_A", seq({
                i_sym(10),
                str("xyz"),
                i_sym(11) }) },
        }, {});

        auto result = expand_tokens(grammar);

        AssertThat(result.second, Equals((const GrammarError *)nullptr));
        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", seq({
                i_sym(10),
                seq({ character({ 'x' }), character({ 'y' }), character({ 'z' }) }),
                i_sym(11) }) },
        }, {})));
    });

    it("returns an error when the grammar contains an invalid regex", [&]() {
        PreparedGrammar grammar({
            { "rule_A", seq({
                pattern("("),
                str("xyz"),
                pattern("[") }) },
        }, {});

        auto result = expand_tokens(grammar);

        AssertThat(result.second, EqualsPointer(new GrammarError(GrammarErrorTypeRegex, "unmatched open paren")));
    });
});

END_TEST