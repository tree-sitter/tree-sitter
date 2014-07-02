#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/build_tables/lex_conflict_manager.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("resolving parse conflicts", []() {
    bool update;

    SyntaxGrammar parse_grammar({
        { "rule1", seq({ sym("rule2"), sym("token2") }) },
        { "rule2", sym("token1") },
    }, {}, set<rules::Symbol>());

    LexicalGrammar lex_grammar({
        { "token1", pattern("[a-c]") },
        { "token2", pattern("[b-d]") },
        { "token3", keyword("stuff") },
    }, {}, set<char>());

    describe("lexical conflicts", [&]() {
        Symbol sym1(0, SymbolOptionToken);
        Symbol sym2(1, SymbolOptionToken);
        Symbol sym3(2, SymbolOptionToken);

        LexConflictManager *manager;

        before_each([&]() {
            manager = new LexConflictManager(lex_grammar);
        });

        after_each([&]() {
            delete manager;
        });

        it("favors non-errors over lexical errors", [&]() {
            update = manager->resolve_lex_action(LexAction::Error(), LexAction::Advance(2, {0}));
            AssertThat(update, IsTrue());

            update = manager->resolve_lex_action(LexAction::Advance(2, {0}), LexAction::Error());
            AssertThat(update, IsFalse());
        });

        describe("accept-token/advance conflicts", [&]() {
            describe("when the the accept-token has higher precedence", [&]() {
                it("prefers the accept", [&]() {
                    update = manager->resolve_lex_action(LexAction::Accept(sym3, 0), LexAction::Advance(1, { -1 }));
                    AssertThat(update, IsFalse());

                    update = manager->resolve_lex_action(LexAction::Advance(1, { -1 }), LexAction::Accept(sym3, 2));
                    AssertThat(update, IsTrue());
                });
            });

            describe("when the the actions have the same precedence", [&]() {
                it("prefers the advance", [&]() {
                    update = manager->resolve_lex_action(LexAction::Accept(sym3, 0), LexAction::Advance(1, { 0 }));
                    AssertThat(update, IsTrue());

                    update = manager->resolve_lex_action(LexAction::Advance(1, { 0 }), LexAction::Accept(sym3, 0));
                    AssertThat(update, IsFalse());
                });
            });

            describe("when the advance has conflicting precedences compared to the accept", [&]() {
                it("prefers the advance", [&]() {
                    update = manager->resolve_lex_action(LexAction::Accept(sym3, 0), LexAction::Advance(1, { -2, 2 }));
                    AssertThat(update, IsTrue());

                    update = manager->resolve_lex_action(LexAction::Advance(1, { -2, 2 }), LexAction::Accept(sym3, 0));
                    AssertThat(update, IsFalse());
                });

                it_skip("records a conflict", [&]() {
                    manager->resolve_lex_action(LexAction::Accept(sym3, 0), LexAction::Advance(1, { -2, 2 }));
                });
            });
        });

        describe("accept-token/accept-token conflicts", [&]() {
            describe("when one token has a higher precedence than the other", [&]() {
                it("prefers the token with the higher precedence", [&]() {
                    update = manager->resolve_lex_action(LexAction::Accept(sym3, 2), LexAction::Accept(sym2, 0));
                    AssertThat(update, IsFalse());

                    update = manager->resolve_lex_action(LexAction::Accept(sym2, 0), LexAction::Accept(sym3, 2));
                    AssertThat(update, IsTrue());
                });
            });

            describe("when both tokens have the same precedence", [&]() {
                it("prefers the token listed earlier in the grammar", [&]() {
                    update = manager->resolve_lex_action(LexAction::Accept(sym1, 0), LexAction::Accept(sym2, 0));
                    AssertThat(update, IsFalse());

                    update = manager->resolve_lex_action(LexAction::Accept(sym2, 0), LexAction::Accept(sym1, 0));
                    AssertThat(update, IsTrue());
                });
            });
        });
    });

    describe("syntactic conflicts", [&]() {
        Symbol sym1(0);
        Symbol sym2(1);
        ParseConflictManager *manager;

        before_each([&]() {
            manager = new ParseConflictManager(parse_grammar, lex_grammar);
        });

        after_each([&]() {
            delete manager;
        });

        it("favors non-errors over parse errors", [&]() {
            update = manager->resolve_parse_action(sym1, ParseAction::Error(), ParseAction::Shift(2, { 0 }));
            AssertThat(update, IsTrue());

            update = manager->resolve_parse_action(sym1, ParseAction::Shift(2, { 0 }), ParseAction::Error());
            AssertThat(update, IsFalse());
        });

        describe("shift/reduce conflicts", [&]() {
            describe("when the shift has higher precedence", [&]() {
                ParseAction shift = ParseAction::Shift(2, { 3 });
                ParseAction reduce = ParseAction::Reduce(sym2, 1, 1);

                it("does not record a conflict", [&]() {
                    manager->resolve_parse_action(sym1, shift, reduce);
                    manager->resolve_parse_action(sym1, reduce, shift);
                    AssertThat(manager->conflicts(), IsEmpty());
                });

                it("favors the shift", [&]() {
                    AssertThat(manager->resolve_parse_action(sym1, shift, reduce), IsFalse());
                    AssertThat(manager->resolve_parse_action(sym1, reduce, shift), IsTrue());
                });
            });

            describe("when the reduce has higher precedence", [&]() {
                ParseAction shift = ParseAction::Shift(2, { 1 });
                ParseAction reduce = ParseAction::Reduce(sym2, 1, 3);

                it("does not record a conflict", [&]() {
                    manager->resolve_parse_action(sym1, reduce, shift);
                    manager->resolve_parse_action(sym1, shift, reduce);
                    AssertThat(manager->conflicts(), IsEmpty());
                });

                it("favors the reduce", [&]() {
                    AssertThat(manager->resolve_parse_action(sym1, reduce, shift), IsFalse());
                    AssertThat(manager->resolve_parse_action(sym1, shift, reduce), IsTrue());
                });
            });

            describe("when the precedences are equal", [&]() {
                ParseAction shift = ParseAction::Shift(2, { 0 });
                ParseAction reduce = ParseAction::Reduce(sym2, 1, 0);

                it("records a conflict", [&]() {
                    manager->resolve_parse_action(sym1, reduce, shift);
                    manager->resolve_parse_action(sym1, shift, reduce);
                    AssertThat(manager->conflicts(), Equals(vector<Conflict>({
                        Conflict("rule1: shift (precedence 0) / reduce rule2 (precedence 0)")
                    })));
                });

                it("favors the shift", [&]() {
                    AssertThat(manager->resolve_parse_action(sym1, shift, reduce), IsFalse());
                    AssertThat(manager->resolve_parse_action(sym1, reduce, shift), IsTrue());
                });
            });

            describe("when the shift has conflicting precedences compared to the reduce", [&]() {
                ParseAction shift = ParseAction::Shift(2, { 0, 1, 3 });
                ParseAction reduce = ParseAction::Reduce(sym2, 1, 2);

                it("records a conflict", [&]() {
                    manager->resolve_parse_action(sym1, reduce, shift);
                    manager->resolve_parse_action(sym1, shift, reduce);
                    AssertThat(manager->conflicts(), Equals(vector<Conflict>({
                        Conflict("rule1: shift (precedence 0, 1, 3) / reduce rule2 (precedence 2)")
                    })));
                });

                it("favors the shift", [&]() {
                    AssertThat(manager->resolve_parse_action(sym1, shift, reduce), IsFalse());
                    AssertThat(manager->resolve_parse_action(sym1, reduce, shift), IsTrue());
                });
            });
        });

        describe("reduce/reduce conflicts", [&]() {
            describe("when one action has higher precedence", [&]() {
                ParseAction left = ParseAction::Reduce(sym2, 1, 0);
                ParseAction right = ParseAction::Reduce(sym2, 1, 3);

                it("favors that action", [&]() {
                    AssertThat(manager->resolve_parse_action(sym1, left, right), IsTrue());
                    AssertThat(manager->resolve_parse_action(sym1, right, left), IsFalse());
                });

                it("does not record a conflict", [&]() {
                    manager->resolve_parse_action(sym1, left, right);
                    manager->resolve_parse_action(sym1, right, left);
                    AssertThat(manager->conflicts(), IsEmpty());
                });
            });

            describe("when the actions have the same precedence", [&]() {
                ParseAction left = ParseAction::Reduce(sym1, 1, 0);
                ParseAction right = ParseAction::Reduce(sym2, 1, 0);

                it("favors the symbol listed earlier in the grammar", [&]() {
                    AssertThat(manager->resolve_parse_action(sym1, right, left), IsTrue());
                    AssertThat(manager->resolve_parse_action(sym1, left, right), IsFalse());
                });

                it("records a conflict", [&]() {
                    manager->resolve_parse_action(sym1, left, right);
                    manager->resolve_parse_action(sym1, right, left);
                    AssertThat(manager->conflicts(), Equals(vector<Conflict>({
                        Conflict("rule1: reduce rule2 (precedence 0) / reduce rule1 (precedence 0)"),
                        Conflict("rule1: reduce rule1 (precedence 0) / reduce rule2 (precedence 0)")
                    })));
                });
            });
        });
    });
});

END_TEST
