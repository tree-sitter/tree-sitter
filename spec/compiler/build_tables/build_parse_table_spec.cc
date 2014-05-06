#include "compiler_spec_helper.h"
#include "compiler/build_tables/build_parse_table.h"
#include "compiler/parse_table.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/built_in_symbols.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("building parse tables", []() {
    PreparedGrammar parse_grammar({
        { "rule0", choice({ i_sym(1), i_sym(2) }) },
        { "rule1", i_token(0) },
        { "rule2", i_token(1) },
    }, {}, PreparedGrammarOptions({
        // ubiquitous_tokens
        { Symbol(2, SymbolOptionToken) }
    }));

    PreparedGrammar lex_grammar({
        { "token0", pattern("[a-c]") },
        { "token1", pattern("[b-d]") },
    }, {});

    it("first looks for the start rule and its item set closure", [&]() {
        auto result = build_parse_table(parse_grammar, lex_grammar);

        AssertThat(result.first.states[0].actions, Equals(map<Symbol, ParseAction>({
            // start item
            { Symbol(0), ParseAction::Shift(1, { 0 }) },

            // expanded from the item set closure of the start item
            { Symbol(1), ParseAction::Shift(2, { 0 }) },
            { Symbol(2), ParseAction::Shift(2, { 0 }) },
            { Symbol(0, SymbolOptionToken), ParseAction::Shift(3, { 0 }) },
            { Symbol(1, SymbolOptionToken), ParseAction::Shift(4, { 0 }) },

            // for the ubiquitous_token 'token2'
            { Symbol(2, SymbolOptionToken), ParseAction::Shift(0, { 0 }) },
        })));
    });

    it("accepts the input when EOF occurs after the start rule", [&]() {
        auto result = build_parse_table(parse_grammar, lex_grammar);

        AssertThat(result.first.states[1].actions, Equals(map<Symbol, ParseAction>({
            { END_OF_INPUT(), ParseAction::Accept() },

            // for the ubiquitous_token 'token2'
            { Symbol(2, SymbolOptionToken), ParseAction::Shift(1, { 0 }) },
        })));
    });

    it("reduces a rule once it has been consumed", [&]() {
        auto result = build_parse_table(parse_grammar, lex_grammar);

        AssertThat(result.first.states[2].actions, Equals(map<Symbol, ParseAction>({
            { END_OF_INPUT(), ParseAction::Reduce(Symbol(0), 1, 0) },

            // for the ubiquitous_token 'token2'
            { Symbol(2, SymbolOptionToken), ParseAction::Shift(2, { 0 }) },
        })));
    });
});


END_TEST
