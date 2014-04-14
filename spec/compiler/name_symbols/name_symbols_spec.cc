#include "compiler_spec_helper.h"
#include "compiler/name_symbols/name_symbols.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/built_in_symbols.h"

using namespace rules;
using name_symbols::name_symbols;

START_TEST

describe("assigning user-visible names to symbols", [&]() {
    PreparedGrammar syntactic_grammar({
        { "some_syntactic_symbol", seq({
            make_shared<Symbol>("some_given_name", SymbolTypeNormal),
            make_shared<Symbol>("some_generated_string_name", SymbolTypeAuxiliary),
            make_shared<Symbol>("some_generated_pattern_name", SymbolTypeAuxiliary), }) },
    }, {});

    PreparedGrammar lexical_grammar({
        { "some_given_name", str("the-string") },
    }, {
        { "some_generated_string_name", str("the-string") },
        { "some_generated_pattern_name", pattern("the-pattern") },
    });

    map<Symbol, string> result = name_symbols::name_symbols(syntactic_grammar, lexical_grammar);

    describe("for symbols that are not in the lexical grammar (syntactic rules)", [&]() {
        it("uses the symbol's normal name", [&]() {
            auto symbol = Symbol("some_syntactic_symbol");
            AssertThat(result[symbol], Equals("some_syntactic_symbol"));
        });
    });

    describe("for symbols that are in the lexical grammar", [&]() {
        it("uses symbols' normal names when they are given by the user", [&]() {
            auto symbol = Symbol("some_given_name");
            AssertThat(result[symbol], Equals("some_given_name"));
        });

        it("assigns names to string rules based on their string value", [&]() {
            auto symbol = Symbol("some_generated_string_name", rules::SymbolTypeAuxiliary);
            AssertThat(result[symbol], Equals("'the-string'"));
        });

        it("assigns names to pattern rules based on their pattern value", [&]() {
            auto symbol = Symbol("some_generated_pattern_name", rules::SymbolTypeAuxiliary);
            AssertThat(result[symbol], Equals("/the-pattern/"));
        });
    });

    it("assigns names to the built-in symbols", [&]() {
        AssertThat(result[rules::END_OF_INPUT()], Equals("EOF"));
        AssertThat(result[rules::ERROR()], Equals("ERROR"));
    });
});

END_TEST