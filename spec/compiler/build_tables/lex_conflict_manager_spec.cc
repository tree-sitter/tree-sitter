#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/lex_conflict_manager.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("LexConflictManager::resolve(new_action, old_action)", []() {
  LexicalGrammar lexical_grammar{{
    Variable("other_token", VariableTypeNamed, pattern("[a-b]")),
    Variable("lookahead_token", VariableTypeNamed, pattern("[c-d]"))
  }, {}};

  LexConflictManager conflict_manager(lexical_grammar);

  bool update;
  Symbol sym1(0, true);
  Symbol sym2(1, true);
  Symbol sym3(2, true);

  it("favors non-errors over lexical errors", [&]() {
    update = conflict_manager.resolve(LexAction::Advance(2, {0, 0}), LexAction::Error());
    AssertThat(update, IsTrue());

    update = conflict_manager.resolve(LexAction::Error(), LexAction::Advance(2, {0, 0}));
    AssertThat(update, IsFalse());
  });

  describe("accept-token/accept-token conflicts", [&]() {
    describe("when one tokens' precedence values differ", [&]() {
      it("favors the token with higher precedence", [&]() {
        update = conflict_manager.resolve(LexAction::Accept(sym2, 1, false), LexAction::Accept(sym1, 2, false));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(LexAction::Accept(sym1, 2, false), LexAction::Accept(sym2, 1, false));
        AssertThat(update, IsTrue());
      });
    });

    describe("when one token is string-based and the other is regexp-based", [&]() {
      it("favors the string-based token", [&]() {
        update = conflict_manager.resolve(LexAction::Accept(sym1, 0, false), LexAction::Accept(sym2, 0, true));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(LexAction::Accept(sym2, 0, true), LexAction::Accept(sym1, 0, false));
        AssertThat(update, IsTrue());
      });
    });

    describe("when the tokens have equal precedence", [&]() {
      it("favors the token listed earlier in the grammar", [&]() {
        update = conflict_manager.resolve(LexAction::Accept(sym2, 0, false), LexAction::Accept(sym1, 0, false));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(LexAction::Accept(sym1, 0, false), LexAction::Accept(sym2, 0, false));
        AssertThat(update, IsTrue());
      });
    });
  });

  describe("advance/accept-token conflicts", [&]() {
    describe("when the token to accept has higher precedence", [&]() {
      it("prefers the accept-token action", [&]() {
        update = conflict_manager.resolve(LexAction::Advance(1, { 1, 2 }), LexAction::Accept(sym3, 3, true));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(LexAction::Accept(sym3, 3, true), LexAction::Advance(1, { 1, 2 }));
        AssertThat(update, IsTrue());
      });
    });

    describe("when the token to accept does not have a higher precedence", [&]() {
      it("favors the advance action", [&]() {
        update = conflict_manager.resolve(LexAction::Advance(1, { 1, 2 }), LexAction::Accept(sym3, 2, true));
        AssertThat(update, IsTrue());

        update = conflict_manager.resolve(LexAction::Accept(sym3, 2, true), LexAction::Advance(1, { 1, 2 }));
        AssertThat(update, IsFalse());
      });
    });
  });
});

END_TEST
