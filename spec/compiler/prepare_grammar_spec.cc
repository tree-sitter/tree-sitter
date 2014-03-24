#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/rules/symbol.h"

START_TEST

using namespace rules;
using prepare_grammar::prepare_grammar;

describe("preparing a grammar", []() {
    describe("extracting tokens", []() {
        it("moves strings and patterns into a separate 'lexical' grammar", [&]() {
            pair<PreparedGrammar, PreparedGrammar> result = prepare_grammar(Grammar({
                { "rule1", seq({
                    str("ab"),
                    seq({
                        sym("rule2"),
                        sym("rule3") }),
                    str("ab") }) }
            }));

            AssertThat(result.first, Equals(PreparedGrammar({
                { "rule1", seq({
                    make_shared<Symbol>("token1", SymbolTypeAuxiliary),
                    seq({
                        sym("rule2"),
                        sym("rule3") }),
                    make_shared<Symbol>("token1", SymbolTypeAuxiliary) }) }
            }, {})));

            AssertThat(result.second, Equals(PreparedGrammar({}, {
                { "token1", str("ab") },
            })));
        });

        it("moves entire rules into the lexical grammar when possible, preserving their names", [&]() {
            auto result = prepare_grammar(Grammar({
                { "rule1", sym("rule2") },
                { "rule2", pattern("a|b") }
            }));

            AssertThat(result.first, Equals(PreparedGrammar({
                { "rule1", sym("rule2") }
            }, {})));

            AssertThat(result.second, Equals(PreparedGrammar({
                { "rule2", pattern("a|b") },
            }, {})));
        });

        it("does not extract blanks into tokens", [&]() {
            pair<PreparedGrammar, PreparedGrammar> result = prepare_grammar(Grammar({
                { "rule1", choice({ sym("rule2"), blank() }) },
            }));

            AssertThat(result.first, Equals(PreparedGrammar({
                { "rule1", choice({ sym("rule2"), blank() }) },
            }, {})));

            AssertThat(result.second, Equals(PreparedGrammar({}, {})));
        });
    });

    describe("expanding repeats", []() {
        it("replaces repeat rules with pairs of recursive rules", [&]() {
            PreparedGrammar result = prepare_grammar(Grammar({
                { "rule1", seq({
                    sym("x"),
                    repeat(seq({ sym("a"), sym("b") })),
                    sym("y")
                }) },
            })).first;

            AssertThat(result, Equals(PreparedGrammar({
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
    });
});

END_TEST