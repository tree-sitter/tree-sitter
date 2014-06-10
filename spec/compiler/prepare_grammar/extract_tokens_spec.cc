#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_tokens;

describe("extracting tokens from a grammar", []() {
    it("moves string rules into the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule_A", seq({ str("ab"), i_sym(0) }) }
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "'ab'", str("ab") },
        })));
    });

    it("moves pattern rules into the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule_A", seq({ pattern("a+"), i_sym(0) }) }
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "/a+/", pattern("a+") },
        })));
    });

    it("moves other rules marked as tokens into the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule_A", seq({
                token(seq({ pattern("."), choice({ str("a"), str("b") }) })),
                i_sym(0) }) }
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "(seq /./ (choice 'a' 'b'))", token(seq({ pattern("."), choice({ str("a"), str("b") }) })) },
        })));
    });

    it("does not extract blanks", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule_A", choice({ i_sym(0), blank() }) },
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", choice({ i_sym(0), blank() }) },
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {})));
    });

    it("does not create duplicate tokens in the lexical grammar", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({
            { "rule_A", seq({ str("ab"), i_sym(0), str("ab") }) },
        }, {}));

        AssertThat(result.first, Equals(PreparedGrammar({
            { "rule_A", seq({ i_aux_token(0), i_sym(0), i_aux_token(0) }) }
        }, {})));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "'ab'", str("ab") },
        })));
    });

    it("extracts tokens from the grammar's auxiliary rules", [&]() {
        pair<PreparedGrammar, PreparedGrammar> result = extract_tokens(PreparedGrammar({}, {
            { "rule_A", seq({ str("ab"), i_sym(0) }) }
        }));

        AssertThat(result.first, Equals(PreparedGrammar({}, {
            { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
        })));

        AssertThat(result.second, Equals(PreparedGrammar({}, {
            { "'ab'", str("ab") },
        })));
    });

    describe("when an entire rule can be extracted", [&]() {
        it("moves the rule the lexical grammar when possible and updates referencing symbols", [&]() {
            auto result = extract_tokens(PreparedGrammar({
                { "rule_A", i_sym(1) },
                { "rule_B", pattern("a|b") },
                { "rule_C", token(seq({ str("a"), str("b") })) },
            }, {}));

            AssertThat(result.first, Equals(PreparedGrammar({
                { "rule_A", i_token(0) }
            }, {})));

            AssertThat(result.second, Equals(PreparedGrammar({
                { "rule_B", pattern("a|b") },
                { "rule_C", token(seq({ str("a"), str("b") })) },
            }, {})));
        });

        it("updates symbols whose indices need to change due to deleted rules", [&]() {
            auto result = extract_tokens(PreparedGrammar({
                { "rule_A", str("ab") },
                { "rule_B", i_sym(0) },
                { "rule_C", i_sym(1) },
            }, {}));

            AssertThat(result.first, Equals(PreparedGrammar({
                { "rule_B", i_token(0) },
                { "rule_C", i_sym(0) },
            }, {})));

            AssertThat(result.second, Equals(PreparedGrammar({
                { "rule_A", str("ab") },
            }, {})));
        });

        it("updates the grammar's ubiquitous_tokens", [&]() {
            auto result = extract_tokens(PreparedGrammar({
                { "rule_A", str("ab") },
                { "rule_B", i_sym(0) },
                { "rule_C", i_sym(1) },
            }, {}).ubiquitous_tokens({ Symbol(0) }));

            AssertThat(result.first.ubiquitous_tokens(), Equals(vector<Symbol>({
                { Symbol(0, SymbolOptionToken) }
            })));
        });

        it("extracts entire auxiliary rules", [&]() {
            auto result = extract_tokens(PreparedGrammar({}, {
                { "rule_A", str("ab") },
                { "rule_B", i_aux_sym(0) },
                { "rule_C", i_aux_sym(1) },
            }));

            AssertThat(result.first, Equals(PreparedGrammar({}, {
                { "rule_B", i_aux_token(0) },
                { "rule_C", i_aux_sym(0) },
            })));

            AssertThat(result.second, Equals(PreparedGrammar({}, {
                { "rule_A", str("ab") },
            })));
        });
    });
});

END_TEST