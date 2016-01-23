#include "spec_helper.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/lex_conflict_manager.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("LexConflictManager::resolve(new_action, old_action)", []() {
  LexConflictManager conflict_manager;
  bool update;
  Symbol sym1(0, true);
  Symbol sym2(1, true);
  Symbol sym3(2, true);

  it("favors advance actions over empty accept token actions", [&]() {
    update = conflict_manager.resolve(AdvanceAction(2, {0, 0}), AcceptTokenAction());
    AssertThat(update, IsTrue());
  });

  describe("accept-token/accept-token conflicts", [&]() {
    describe("when one tokens' precedence values differ", [&]() {
      it("favors the token with higher precedence", [&]() {
        update = conflict_manager.resolve(AcceptTokenAction(sym2, 1, false), AcceptTokenAction(sym1, 2, false));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(AcceptTokenAction(sym1, 2, false), AcceptTokenAction(sym2, 1, false));
        AssertThat(update, IsTrue());
      });

      it("adds the discarded token to the 'fragile tokens' set", [&]() {
        update = conflict_manager.resolve(AcceptTokenAction(sym2, 1, false), AcceptTokenAction(sym1, 2, false));
        AssertThat(conflict_manager.fragile_tokens, Contains(sym2));
      });
    });

    describe("when one token is string-based and the other is regexp-based", [&]() {
      it("favors the string-based token", [&]() {
        update = conflict_manager.resolve(AcceptTokenAction(sym1, 0, false), AcceptTokenAction(sym2, 0, true));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(AcceptTokenAction(sym2, 0, true), AcceptTokenAction(sym1, 0, false));
        AssertThat(update, IsTrue());
      });
    });

    describe("when the tokens have equal precedence", [&]() {
      it("favors the token listed earlier in the grammar", [&]() {
        update = conflict_manager.resolve(AcceptTokenAction(sym2, 0, false), AcceptTokenAction(sym1, 0, false));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(AcceptTokenAction(sym1, 0, false), AcceptTokenAction(sym2, 0, false));
        AssertThat(update, IsTrue());
      });
    });
  });

  describe("advance/accept-token conflicts", [&]() {
    describe("when the token to accept has higher precedence", [&]() {
      it("prefers the accept-token action", [&]() {
        update = conflict_manager.resolve(AdvanceAction(1, { 1, 2 }), AcceptTokenAction(sym3, 3, true));
        AssertThat(update, IsFalse());
      });
    });

    describe("when the token to accept does not have a higher precedence", [&]() {
      it("favors the advance action", [&]() {
        update = conflict_manager.resolve(AdvanceAction(1, { 1, 2 }), AcceptTokenAction(sym3, 2, true));
        AssertThat(update, IsTrue());
      });
    });
  });
});

END_TEST
