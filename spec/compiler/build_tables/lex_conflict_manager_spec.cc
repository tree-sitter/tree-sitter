#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/lex_conflict_manager.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("LexConflictManager", []() {
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
    update = conflict_manager.resolve(LexAction::Advance(2, {0}), LexAction::Error());
    AssertThat(update, IsTrue());

    update = conflict_manager.resolve(LexAction::Error(), LexAction::Advance(2, {0}));
    AssertThat(update, IsFalse());
  });

  describe("accept-token/advance conflicts", [&]() {
    it("prefers the advance", [&]() {
      update = conflict_manager.resolve(LexAction::Advance(1, { 0 }), LexAction::Accept(sym3, 3));
      AssertThat(update, IsTrue());

      update = conflict_manager.resolve(LexAction::Accept(sym3, 3), LexAction::Advance(1, { 0 }));
      AssertThat(update, IsFalse());
    });
  });

  describe("accept-token/accept-token conflicts", [&]() {
    describe("when one token has a higher precedence than the other", [&]() {
      it("prefers the token with the higher precedence", [&]() {
        update = conflict_manager.resolve(LexAction::Accept(sym2, 0), LexAction::Accept(sym3, 2));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(LexAction::Accept(sym3, 2), LexAction::Accept(sym2, 0));
        AssertThat(update, IsTrue());
      });
    });

    describe("when both tokens have the same precedence", [&]() {
      it("prefers the token listed earlier in the grammar", [&]() {
        update = conflict_manager.resolve(LexAction::Accept(sym2, 0), LexAction::Accept(sym1, 0));
        AssertThat(update, IsFalse());

        update = conflict_manager.resolve(LexAction::Accept(sym1, 0), LexAction::Accept(sym2, 0));
        AssertThat(update, IsTrue());
      });
    });
  });
});

END_TEST
