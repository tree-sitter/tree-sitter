#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_tokens;

describe("extracting tokens from a grammar", []() {
    it("moves strings into the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule0", seq({ str("ab"), i_sym(0) }) }
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule0", seq({ i_aux_token(0), i_sym(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "token0", str("ab") },
        })));
    });

    it("moves patterns into the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule0", seq({ pattern("a+"), i_sym(0) }) }
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule0", seq({ i_aux_token(0), i_sym(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "token0", pattern("a+") },
        })));
    });

    it("does not extract blanks into tokens", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule1", choice({ i_sym(0), blank() }) },
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule1", choice({ i_sym(0), blank() }) },
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {})));
    });

    it("does not create duplicate tokens in the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule0", seq({ str("ab"), i_sym(0), str("ab") }) },
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule0", seq({ i_aux_token(0), i_sym(0), i_aux_token(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "token0", str("ab") },
        })));
    });

    it("moves entire rules into the lexical grammar when possible, updating referencing symbols", [&]() {
        auto result = extract_tokens(PreparedGrammar({
            { "rule0", i_sym(1) },
            { "rule1", pattern("a|b") },
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule0", i_token(0) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({
            { "rule1", pattern("a|b") },
        }, {})));
    });

    it("updates symbols whose indices need to change due to deleted rules", [&]() {
        auto result = extract_tokens(PreparedGrammar({
            { "rule0", str("ab") },
            { "rule1", i_sym(0) },
            { "rule2", i_sym(1) },
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule1", i_token(0) },
            { "rule2", i_sym(0) },
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({
            { "rule0", str("ab") },
        }, {})));
    });
});

END_TEST