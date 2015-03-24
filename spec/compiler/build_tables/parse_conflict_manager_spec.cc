#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/syntax_grammar.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("ParseConflictManager", []() {
  SyntaxGrammar syntax_grammar({
    { "in_progress_rule1", i_token(0) },
    { "in_progress_rule2", i_token(0) },
    { "reduced_rule", i_token(0) },
    { "other_rule1", i_token(0) },
    { "other_rule2", i_token(0) },
  }, {}, { Symbol(2, SymbolOptionToken) });

  LexicalGrammar lexical_grammar({
    { "other_token", pattern("[a-b]") },
    { "lookahead_token", pattern("[c-d]") },
  }, {});

  tuple<bool, ConflictType, string> result;
  Symbol sym1(0);
  Symbol sym2(1);
  Symbol lookahead_sym(1, SymbolOptionToken);
  ParseConflictManager *conflict_manager;

  before_each([&]() {
    conflict_manager = new ParseConflictManager(syntax_grammar, lexical_grammar);
  });

  after_each([&]() {
    delete conflict_manager;
  });

  describe(".get_production_id", [&]() {
    it("returns different IDs for different productions", [&]() {
      int id1 = conflict_manager->get_production_id(vector<Symbol>({ Symbol(1), Symbol(2) }));
      AssertThat(id1, Equals(0));

      int id2 = conflict_manager->get_production_id(vector<Symbol>({ Symbol(1), Symbol(2), Symbol(3) }));
      AssertThat(id2, Equals(1));

      int id3 = conflict_manager->get_production_id(vector<Symbol>({ Symbol(1) }));
      AssertThat(id3, Equals(2));

      int id4 = conflict_manager->get_production_id(vector<Symbol>({ Symbol(1), Symbol(2) }));
      AssertThat(id4, Equals(id1));
    });
  });

  describe(".resolve", [&]() {
    describe("errors", [&]() {
      ParseAction error = ParseAction::Error();
      ParseAction non_error = ParseAction::Shift(2, { 0 });

      it("favors non-errors and reports no conflict", [&]() {
        result = conflict_manager->resolve(non_error, error, sym1);
        AssertThat(get<0>(result), IsTrue());
        AssertThat(get<1>(result), Equals(ConflictTypeNone));

        result = conflict_manager->resolve(error, non_error, sym1);
        AssertThat(get<0>(result), IsFalse());
        AssertThat(get<1>(result), Equals(ConflictTypeNone));
      });
    });

    describe("shift/reduce conflicts", [&]() {
      describe("when the shift has higher precedence", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 3 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 1, AssociativityLeft, 0);

        it("favors the shift and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));
        });
      });

      describe("when the reduce has higher precedence", [&]() {
        ParseAction shift = ParseAction::Shift(2, {
          {1, AssociativityLeft}
        });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 3, AssociativityLeft, 0);

        it("favors the reduce and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));
        });
      });

      describe("when the precedences are equal and the reduce's rule is left associative", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 0, AssociativityLeft, 0);

        it("favors the reduce and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));
        });
      });

      describe("when the precedences are equal and the reduce's rule is right-associative", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0 });
        ParseAction reduce = ParseAction::Reduce(sym2, 1, 0, AssociativityRight, 0);

        it("favors the shift, and reports the conflict as resolved", [&]() {
          result = conflict_manager->resolve(reduce, shift, sym1);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(shift, reduce, sym1);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));
        });
      });

      describe("when the precedences are equal and the reduce's rule has no associativity", [&]() {
        it("reports an unresolved conflict", [&]() {
          ParseAction shift = ParseAction::Shift(2, { 0 });
          ParseAction reduce = ParseAction::Reduce(Symbol(2), 1, 0, AssociativityUnspecified, 0);

          reduce.production_id = conflict_manager->get_production_id(vector<Symbol>({
            Symbol(3),
            Symbol(4),
          }));

          result = conflict_manager->resolve(reduce, shift, lookahead_sym);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeError));
          AssertThat(get<2>(result), Equals(
            "Lookahead: lookahead_token\n"
            "Possible Actions:\n"
            "* Shift (Precedence 0)\n"
            "* Reduce other_rule1 other_rule2 -> reduced_rule (Precedence 0)"
          ));

          result = conflict_manager->resolve(shift, reduce, lookahead_sym);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<2>(result), Equals(
            "Lookahead: lookahead_token\n"
            "Possible Actions:\n"
            "* Shift (Precedence 0)\n"
            "* Reduce other_rule1 other_rule2 -> reduced_rule (Precedence 0)"
          ));
        });
      });

      describe("when the shift has conflicting precedences compared to the reduce", [&]() {
        ParseAction shift = ParseAction::Shift(2, { 0, 1, 3 });
        ParseAction reduce = ParseAction::Reduce(Symbol(2), 1, 2, AssociativityLeft, 0);

        it("returns false and reports an unresolved conflict", [&]() {
          reduce.production_id = conflict_manager->get_production_id(vector<Symbol>({
            Symbol(3),
            Symbol(4),
          }));

          result = conflict_manager->resolve(reduce, shift, lookahead_sym);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeError));

          result = conflict_manager->resolve(shift, reduce, lookahead_sym);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<1>(result), Equals(ConflictTypeError));
          AssertThat(get<2>(result), Equals(
            "Lookahead: lookahead_token\n"
            "Possible Actions:\n"
            "* Shift (Precedences 0, 3)\n"
            "* Reduce other_rule1 other_rule2 -> reduced_rule (Precedence 2)"
          ));
        });
      });
    });

    describe("reduce/reduce conflicts", [&]() {
      describe("when one action has higher precedence", [&]() {
        ParseAction left = ParseAction::Reduce(sym2, 1, 0, AssociativityLeft, 0);
        ParseAction right = ParseAction::Reduce(sym2, 1, 3, AssociativityLeft, 0);

        it("favors that action", [&]() {
          result = conflict_manager->resolve(left, right, sym1);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));

          result = conflict_manager->resolve(right, left, sym1);
          AssertThat(get<0>(result), IsTrue());
          AssertThat(get<1>(result), Equals(ConflictTypeResolved));
        });
      });

      describe("when the actions have the same precedence", [&]() {
        it("returns false and reports a conflict", [&]() {
          ParseAction left = ParseAction::Reduce(Symbol(2), 1, 0, AssociativityLeft, 0);
          ParseAction right = ParseAction::Reduce(Symbol(3), 1, 0, AssociativityLeft, 0);

          left.production_id = conflict_manager->get_production_id(vector<Symbol>({
            Symbol(3),
            Symbol(4),
          }));

          right.production_id = conflict_manager->get_production_id(vector<Symbol>({
            Symbol(4),
          }));

          result = conflict_manager->resolve(right, left, lookahead_sym);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeError));
          AssertThat(get<2>(result), Equals(
            "Lookahead: lookahead_token\n"
            "Possible Actions:\n"
            "* Reduce other_rule1 other_rule2 -> reduced_rule (Precedence 0)\n"
            "* Reduce other_rule2 -> other_rule1 (Precedence 0)"
          ));

          result = conflict_manager->resolve(left, right, lookahead_sym);
          AssertThat(get<0>(result), IsFalse());
          AssertThat(get<1>(result), Equals(ConflictTypeError));
          AssertThat(get<2>(result), Equals(
            "Lookahead: lookahead_token\n"
            "Possible Actions:\n"
            "* Reduce other_rule2 -> other_rule1 (Precedence 0)\n"
            "* Reduce other_rule1 other_rule2 -> reduced_rule (Precedence 0)"
          ));
        });
      });
    });
  });
});

END_TEST
