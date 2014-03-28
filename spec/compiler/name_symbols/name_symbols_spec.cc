#include "compiler_spec_helper.h"
#include "compiler/name_symbols/name_symbols.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using name_symbols::name_symbols;

START_TEST

describe("assigning user-visible names to symbols", [&]() {
    PreparedGrammar lexical_grammar({
        { "some_given_name", str("the-string") },
    }, {
        { "some_generated_string_name", str("the-string") },
        { "some_generated_pattern_name", pattern("the-pattern") },
    });

    describe("for symbols that are not in the lexical grammar (syntactic rules)", [&]() {
        it("uses the symbol's normal name", [&]() {
            auto symbol = Symbol("some_syntactic_symbol");
            AssertThat(name_symbols::name_symbols({ symbol }, lexical_grammar), Equals(map<Symbol, string>({
                { symbol, "some_syntactic_symbol" }
            })));
        });
    });

    describe("for symbols that are in the lexical grammar", [&]() {
        it("uses symbols' normal names when they are given by the user", [&]() {
            auto symbol = Symbol("some_given_name");
            AssertThat(name_symbols::name_symbols({ symbol }, lexical_grammar), Equals(map<Symbol, string>({
                { symbol, "some_given_name" }
            })));
        });

        it("assigns names to string rules based on their string value", [&]() {
            auto symbol = Symbol("some_generated_string_name", rules::SymbolTypeAuxiliary);
            AssertThat(name_symbols::name_symbols({ symbol }, lexical_grammar), Equals(map<Symbol, string>({
                { symbol, "'the-string'" }
            })));
        });

        it("assigns names to pattern rules based on their pattern value", [&]() {
            auto symbol = Symbol("some_generated_pattern_name", rules::SymbolTypeAuxiliary);
            AssertThat(name_symbols::name_symbols({ symbol }, lexical_grammar), Equals(map<Symbol, string>({
                { symbol, "/the-pattern/" }
            })));
        });
    });
});

END_TEST