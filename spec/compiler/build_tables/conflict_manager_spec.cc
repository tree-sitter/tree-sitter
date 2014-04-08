#include "compiler_spec_helper.h"
#include "compiler/build_tables/conflict_manager.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("resolving parse conflicts", []() {
    LexAction lex_action;
    ParseAction parse_action;
    ConflictManager *manager;

    PreparedGrammar parse_grammar({
        { "rule1", seq({ sym("rule2"), sym("token2") }) },
        { "rule2", sym("token1") },
    }, {});

    PreparedGrammar lex_grammar({
        { "token1", pattern("[a-c]") },
        { "token2", pattern("[b-d]") },
    }, {});

    before_each([&]() {
        manager = new ConflictManager(parse_grammar, lex_grammar);
    });

    after_each([&]() {
        delete manager;
    });

    describe("lexical conflicts", [&]() {
        Symbol sym1("token1");
        Symbol sym2("token2");

        it("favors non-errors over lexical errors", [&]() {
            lex_action = manager->resolve_lex_action(LexAction::Error(), LexAction::Advance(2));
            AssertThat(lex_action, Equals(LexAction::Advance(2)));

            lex_action = manager->resolve_lex_action(LexAction::Advance(2), LexAction::Error());
            AssertThat(lex_action, Equals(LexAction::Advance(2)));
        });

        it("prefers tokens that are listed earlier in the grammar", [&]() {
            lex_action = manager->resolve_lex_action(LexAction::Accept(sym1), LexAction::Accept(sym2));
            AssertThat(lex_action, Equals(LexAction::Accept(sym1)));

            lex_action = manager->resolve_lex_action(LexAction::Accept(sym2), LexAction::Accept(sym1));
            AssertThat(lex_action, Equals(LexAction::Accept(sym1)));
        });
    });

    describe("syntactic conflicts", [&]() {
        Symbol sym1("rule1");
        Symbol sym2("rule2");

        it("favors non-errors over parse errors", [&]() {
            parse_action = manager->resolve_parse_action(sym1, ParseAction::Error(), ParseAction::Shift(2));
            AssertThat(parse_action, Equals(ParseAction::Shift(2)));

            parse_action = manager->resolve_parse_action(sym1, ParseAction::Shift(2), ParseAction::Error());
            AssertThat(parse_action, Equals(ParseAction::Shift(2)));
        });

        describe("shift/reduce conflicts", [&]() {
            it("records shift/reduce conflicts, favoring the shift", [&]() {
                manager->resolve_parse_action(sym1, ParseAction::Reduce(sym2, 1), ParseAction::Shift(2));
                manager->resolve_parse_action(sym1, ParseAction::Shift(2), ParseAction::Reduce(sym2, 1));

                AssertThat(manager->conflicts()[0], Equals(Conflict("rule1: shift / reduce rule2")));
                AssertThat(manager->conflicts()[1], Equals(Conflict("rule1: shift / reduce rule2")));
            });

            it("favors the shift", [&]() {
                parse_action = manager->resolve_parse_action(sym1, ParseAction::Reduce(sym2, 1), ParseAction::Shift(2));
                AssertThat(parse_action, Equals(ParseAction::Shift(2)));

                parse_action = manager->resolve_parse_action(sym1, ParseAction::Shift(2), ParseAction::Reduce(sym2, 1));
                AssertThat(parse_action, Equals(ParseAction::Shift(2)));
            });
        });

        it("records reduce/reduce conflicts, favoring the symbol listed earlier in the grammar", [&]() {

        });
    });
});

END_TEST