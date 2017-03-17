#include "test_helper.h"
#include "helpers/stream_methods.h"
#include "compiler/rule.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/lex_conflict_manager.h"
#include "compiler/build_tables/lex_item.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("LexConflictManager::resolve(new_action, old_action)", []() {
  LexConflictManager conflict_manager;
  bool update;
  Symbol sym1 = Symbol::terminal(0);
  Symbol sym2 = Symbol::terminal(1);
  Symbol sym3 = Symbol::terminal(2);
  Symbol sym4 = Symbol::terminal(3);
  LexItemSet item_set({ LexItem(sym4, Blank{} )});

  before_each([&]() {
    conflict_manager = LexConflictManager();
  });

  it("favors advance actions over empty accept token actions", [&]() {
    update = conflict_manager.resolve(item_set, AdvanceAction(2, {0, 0}, true), AcceptTokenAction());
    AssertThat(update, IsTrue());
  });

  describe("accept-token/accept-token conflicts", [&]() {
    describe("when the tokens' precedence values differ", [&]() {
      it("favors the token with higher precedence", [&]() {
        update = conflict_manager.resolve(AcceptTokenAction(sym2, 1, false), AcceptTokenAction(sym1, 2, false));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(AcceptTokenAction(sym1, 2, false), AcceptTokenAction(sym2, 1, false));
        AssertThat(update, IsTrue());
      });

      it("adds the preferred token as a possible homonym for the discarded one", [&]() {
        conflict_manager.resolve(AcceptTokenAction(sym2, 1, false), AcceptTokenAction(sym1, 2, false));
        AssertThat(conflict_manager.possible_homonyms[sym2.index], Contains(sym1.index));
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
        update = conflict_manager.resolve(item_set, AdvanceAction(1, { 1, 2 }, true), AcceptTokenAction(sym3, 3, true));
        AssertThat(update, IsFalse());
      });
    });

    describe("when the token to accept does not have a higher precedence", [&]() {
      it("favors the advance action", [&]() {
        update = conflict_manager.resolve(item_set, AdvanceAction(1, { 1, 2 }, true), AcceptTokenAction(sym3, 2, true));
        AssertThat(update, IsTrue());
      });
    });
  });
});

END_TEST
