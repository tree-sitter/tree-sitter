#include "compiler_spec_helper.h"
#include "compiler/build_tables/conflict_manager.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("resolving parse conflicts", []() {
    bool should_update;
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
        manager = new ConflictManager(parse_grammar, lex_grammar, {
            { Symbol("rule1"), "rule1" },
            { Symbol("rule2"), "rule2" },
            { Symbol("token1"), "token1" },
            { Symbol("token2"), "token2" },
        });
    });

    after_each([&]() {
        delete manager;
    });

    describe("lexical conflicts", [&]() {
        Symbol sym1("token1");
        Symbol sym2("token2");

        it("favors non-errors over lexical errors", [&]() {
            should_update = manager->resolve_lex_action(LexAction::Error(), LexAction::Advance(2));
            AssertThat(should_update, IsTrue());

            should_update = manager->resolve_lex_action(LexAction::Advance(2), LexAction::Error());
            AssertThat(should_update, IsFalse());
        });

        it("prefers tokens that are listed earlier in the grammar", [&]() {
            should_update = manager->resolve_lex_action(LexAction::Accept(sym1), LexAction::Accept(sym2));
            AssertThat(should_update, IsFalse());

            should_update = manager->resolve_lex_action(LexAction::Accept(sym2), LexAction::Accept(sym1));
            AssertThat(should_update, IsTrue());
        });
    });

    describe("syntactic conflicts", [&]() {
        Symbol sym1("rule1");
        Symbol sym2("rule2");

        it("favors non-errors over parse errors", [&]() {
            should_update = manager->resolve_parse_action(sym1, ParseAction::Error(), ParseAction::Shift(2));
            AssertThat(should_update, IsTrue());

            should_update = manager->resolve_parse_action(sym1, ParseAction::Shift(2), ParseAction::Error());
            AssertThat(should_update, IsFalse());
        });

        describe("shift/reduce conflicts", [&]() {
            it("records a conflict", [&]() {
                manager->resolve_parse_action(sym1, ParseAction::Reduce(sym2, 1), ParseAction::Shift(2));
                manager->resolve_parse_action(sym1, ParseAction::Shift(2), ParseAction::Reduce(sym2, 1));

                AssertThat(manager->conflicts()[0], Equals(Conflict("rule1: shift / reduce rule2")));
                AssertThat(manager->conflicts()[1], Equals(Conflict("rule1: shift / reduce rule2")));
            });

            it("favors the shift", [&]() {
                should_update = manager->resolve_parse_action(sym1, ParseAction::Reduce(sym2, 1), ParseAction::Shift(2));
                AssertThat(should_update, IsTrue());

                should_update = manager->resolve_parse_action(sym1, ParseAction::Shift(2), ParseAction::Reduce(sym2, 1));
                AssertThat(should_update, IsFalse());
            });
        });

        describe("reduce/reduce conflicts", [&]() {
            it("records a conflict", [&]() {
                manager->resolve_parse_action(sym1, ParseAction::Reduce(sym2, 1), ParseAction::Reduce(sym1, 1));
                manager->resolve_parse_action(sym1, ParseAction::Reduce(sym1, 1), ParseAction::Reduce(sym2, 1));
                
                AssertThat(manager->conflicts()[0], Equals(Conflict("rule1: reduce rule2 / reduce rule1")));
                AssertThat(manager->conflicts()[1], Equals(Conflict("rule1: reduce rule1 / reduce rule2")));
            });
            
            it("favors the symbol listed earlier in the grammar", [&]() {
                should_update = manager->resolve_parse_action(sym1, ParseAction::Reduce(sym2, 1), ParseAction::Reduce(sym1, 1));
                AssertThat(should_update, IsTrue());
                
                should_update = manager->resolve_parse_action(sym1, ParseAction::Reduce(sym1, 1), ParseAction::Reduce(sym2, 1));
                AssertThat(should_update, IsFalse());
            });
        });
    });
});

END_TEST