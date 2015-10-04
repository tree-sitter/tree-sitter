#include "compiler/compiler_spec_helper.h"
#include "compiler/syntax_grammar.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/rules/built_in_symbols.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("item_set_closure", []() {
  SyntaxGrammar grammar{{
    SyntaxVariable("rule0", VariableTypeNamed, {
      Production({
        {Symbol(1), 0, AssociativityNone, 100},
        {Symbol(11, true), 0, AssociativityNone, 101},
      }),
    }),
    SyntaxVariable("rule1", VariableTypeNamed, {
      Production({
        {Symbol(12, true), 0, AssociativityNone, 102},
        {Symbol(13, true), 0, AssociativityNone, 103},
      }),
      Production({
        {Symbol(2), 0, AssociativityNone, 104},
      })
    }),
    SyntaxVariable("rule2", VariableTypeNamed, {
      Production({
        {Symbol(14, true), 0, AssociativityNone, 105},
        {Symbol(15, true), 0, AssociativityNone, 106},
      })
    }),
  }, {}, {}};

  it("adds items at the beginnings of referenced rules", [&]() {
    ParseItemSet item_set = item_set_closure(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 0, 100),
        set<Symbol>({ Symbol(10, true) }),
      }
    }), grammar);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 0, 100),
        set<Symbol>({ Symbol(10, true) })
      },
      {
        ParseItem(Symbol(1), 0, 0, 102),
        set<Symbol>({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(1), 1, 0, 104),
        set<Symbol>({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(2), 0, 0, 105),
        set<Symbol>({ Symbol(11, true) })
      },
    })));
  });
});

END_TEST
