#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/parse_conflict_manager.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("ParseConflictManager", []() {
  SyntaxGrammar syntax_grammar{{
    SyntaxVariable("in_progress_rule1", VariableTypeNamed, { Production() }),
    SyntaxVariable("in_progress_rule2", VariableTypeNamed, { Production() }),
    SyntaxVariable("reduced_rule", VariableTypeNamed, { Production() }),
    SyntaxVariable("other_rule1", VariableTypeNamed, { Production() }),
    SyntaxVariable("other_rule2", VariableTypeNamed, { Production() }),
  }, { Symbol(2, true) }, {}};

  pair<bool, ConflictType> result;
  Symbol sym1(0);
  Symbol sym2(1);
  Symbol lookahead_sym(1, true);
  ParseConflictManager *conflict_manager;

  before_each([&]() {
    conflict_manager = new ParseConflictManager(syntax_grammar);
  });

  after_each([&]() {
    delete conflict_manager;
  });

  const Production &production = syntax_grammar.variables[0].productions[0];

  describe(".resolve", [&]() {
    describe("errors", [&]() {
      ParseAction error = ParseAction::Error();
      ParseAction non_error = ParseAction::Shift(2, { 0, 0 });

      it("favors non-errors and reports no conflict", [&]() {
        result = conflict_manager->resolve(non_error, error, sym1);
        AssertThat(result.first, IsTrue());
        AssertThat(result.second, Equals(ConflictTypeNone));

        result = conflict_manager->resolve(error, non_error, sym1);
        AssertThat(result.first, IsFalse());
        AssertThat(result.second, Equals(ConflictTypeNone));
      });
    });

    describe("shift-extra actions", [&]() {
      ParseAction shift_extra = ParseAction::Error();
      ParseAction other = ParseAction::Shift(2, { 0, 0 });

      it("favors other actions over shift-extra actions", [&]() {
        result = conflict_manager->resolve(other, shift_extra, sym1);
        AssertThat(result.first, IsTrue());
        AssertThat(result.second, Equals(ConflictTypeNone));

        result = conflict_manager->resolve(shift_extra, other, sym1);
        AssertThat(result.first, IsFalse());
        AssertThat(result.second, Equals(ConflictTypeNone));
      });
    });

    describe("shift/reduce conflicts", [&]() {
      describe("when the shift has higher precedence", [&]() {
        ParseAction shift = ParseAction::Shift(2, {3, 4});
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 2, AssociativityLeft, production);

        it("favors the shift and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(result.first, IsTrue());
          AssertThat(result.second, Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeResolved));
        });
      });

      describe("when the reduce has higher precedence", [&]() {
        ParseAction shift = ParseAction::Shift(2, {1, 2});
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 3, AssociativityLeft, production);

        it("favors the reduce and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(result.first, IsTrue());
          AssertThat(result.second, Equals(ConflictTypeResolved));
        });
      });

      describe("when the precedences are equal and the reduce's rule is left associative", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0, 0 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 0, AssociativityLeft, production);

        it("favors the reduce and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(result.first, IsTrue());
          AssertThat(result.second, Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeResolved));
        });
      });

      describe("when the precedences are equal and the reduce's rule is right-associative", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0, 0 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 0, AssociativityRight, production);

        it("favors the shift, and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(result.first, IsTrue());
          AssertThat(result.second, Equals(ConflictTypeResolved));
        });
      });

      describe("when the precedences are equal and the reduce's rule has no associativity", [&]() {
        it("reports an unresolved conflict", [&]() {
          ParseAction shift = ParseAction::Shift(2, { 0, 0 });
          ParseAction reduce = ParseAction::Reduce(Symbol(2), 1, 0, AssociativityNone, production);

          result = conflict_manager->resolve(reduce, shift, lookahead_sym);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeUnresolved));

          result = conflict_manager->resolve(shift, reduce, lookahead_sym);
          AssertThat(result.first, IsTrue());
        });
      });

      describe("when the shift has conflicting precedences compared to the reduce", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 1, 3 });
        ParseAction reduce = ParseAction::Reduce(Symbol(2), 1, 2, AssociativityLeft, production);

        it("returns false and reports an unresolved conflict", [&]() {
          result = conflict_manager->resolve(reduce, shift, lookahead_sym);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeUnresolved));

          result = conflict_manager->resolve(shift, reduce, lookahead_sym);
          AssertThat(result.first, IsTrue());
          AssertThat(result.second, Equals(ConflictTypeUnresolved));
        });
      });
    });

    describe("reduce/reduce conflicts", [&]() {
      describe("when one action has higher precedence", [&]() {
        ParseAction left = ParseAction::Reduce(sym2, 1, 0, AssociativityLeft, production);
        ParseAction right = ParseAction::Reduce(sym2, 1, 2, AssociativityLeft, production);

        it("favors that action", [&]() {
          result = conflict_manager->resolve(left, right, sym1);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(right, left, sym1);
          AssertThat(result.first, IsTrue());
          AssertThat(result.second, Equals(ConflictTypeResolved));
        });
      });

      describe("when the actions have the same precedence", [&]() {
        it("returns false and reports a conflict", [&]() {
          ParseAction left = ParseAction::Reduce(Symbol(2), 1, 0, AssociativityLeft, production);
          ParseAction right = ParseAction::Reduce(Symbol(3), 1, 0, AssociativityLeft, production);

          result = conflict_manager->resolve(right, left, lookahead_sym);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeUnresolved));

          result = conflict_manager->resolve(left, right, lookahead_sym);
          AssertThat(result.first, IsFalse());
          AssertThat(result.second, Equals(ConflictTypeUnresolved));
        });
      });
    });
  });
});

END_TEST
