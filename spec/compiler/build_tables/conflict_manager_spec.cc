#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/action_takes_precedence.h"
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
  }, {}, {});

  describe("LexConflictManager", [&]() {
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
      it("prefers the advance", [&]() {
        update = manager->resolve_lex_action(LexAction::Accept(sym3, 3), LexAction::Advance(1, { 0 }));
        AssertThat(update, IsTrue());

        update = manager->resolve_lex_action(LexAction::Advance(1, { 0 }), LexAction::Accept(sym3, 3));
        AssertThat(update, IsFalse());
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

  describe("action_takes_precedence", [&]() {
    pair<bool, bool> result;
    Symbol sym1(0);
    Symbol sym2(1);

    describe("errors", [&]() {
      ParseAction error = ParseAction::Error();
      ParseAction non_error = ParseAction::Shift(2, { 0 });

      it("favors non-errors", [&]() {
        result = action_takes_precedence(non_error, error, sym1, parse_grammar);
        AssertThat(result.first, IsTrue());

        result = action_takes_precedence(error, non_error, sym1, parse_grammar);
        AssertThat(result.first, IsFalse());
      });

      it("is not a conflict", [&]() {
        result = action_takes_precedence(non_error, error, sym1, parse_grammar);
        AssertThat(result.second, IsFalse());

        result = action_takes_precedence(error, non_error, sym1, parse_grammar);
        AssertThat(result.second, IsFalse());
      });
    });

    describe("shift/reduce conflicts", [&]() {
      describe("when the shift has higher precedence", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 3 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 1);

        it("is not a conflict", [&]() {
          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.second, IsFalse());

          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.second, IsFalse());
        });

        it("favors the shift", [&]() {
          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.first, IsTrue());

          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.first, IsFalse());
        });
      });

      describe("when the reduce has higher precedence", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 1 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 3);

        it("is not a conflict", [&]() {
          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.second, IsFalse());

          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.second, IsFalse());
        });

        it("favors the reduce", [&]() {
          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.first, IsFalse());

          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.first, IsTrue());
        });
      });

      describe("when the precedences are equal", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 0);

        it("is a conflict", [&]() {
          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.second, IsTrue());

          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.second, IsTrue());
        });

        it("favors the shift", [&]() {
          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.first, IsFalse());

          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.first, IsTrue());
        });
      });

      describe("when the shift has conflicting precedences compared to the reduce", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0, 1, 3 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 2);

        it("is a conflict", [&]() {
          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.second, IsTrue());

          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.second, IsTrue());
        });

        it("favors the shift", [&]() {
          result = action_takes_precedence(reduce, shift, sym1, parse_grammar);
          AssertThat(result.first, IsFalse());

          result = action_takes_precedence(shift, reduce, sym1, parse_grammar);
          AssertThat(result.first, IsTrue());
        });
      });
    });

    describe("reduce/reduce conflicts", [&]() {
      describe("when one action has higher precedence", [&]() {
        ParseAction left = ParseAction::Reduce(sym2, 1, 0);
        ParseAction right = ParseAction::Reduce(sym2, 1, 3);

        it("favors that action", [&]() {
          result = action_takes_precedence(left, right, sym1, parse_grammar);
          AssertThat(result.first, IsFalse());

          result = action_takes_precedence(right, left, sym1, parse_grammar);
          AssertThat(result.first, IsTrue());
        });

        it("is not a conflict", [&]() {
          result = action_takes_precedence(left, right, sym1, parse_grammar);
          AssertThat(result.second, IsFalse());

          result = action_takes_precedence(right, left, sym1, parse_grammar);
          AssertThat(result.second, IsFalse());
        });
      });

      describe("when the actions have the same precedence", [&]() {
        ParseAction left = ParseAction::Reduce(sym1, 1, 0);
        ParseAction right = ParseAction::Reduce(sym2, 1, 0);

        it("favors the symbol listed earlier in the grammar", [&]() {
          result = action_takes_precedence(left, right, sym1, parse_grammar);
          AssertThat(result.first, IsTrue());

          result = action_takes_precedence(right, left, sym1, parse_grammar);
          AssertThat(result.first, IsFalse());
        });

        it("records a conflict", [&]() {
          result = action_takes_precedence(left, right, sym1, parse_grammar);
          AssertThat(result.second, IsTrue());

          result = action_takes_precedence(right, left, sym1, parse_grammar);
          AssertThat(result.second, IsTrue());
        });
      });
    });
  });
});

END_TEST
