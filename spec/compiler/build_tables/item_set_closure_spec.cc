#include "compiler/compiler_spec_helper.h"
#include "compiler/syntax_grammar.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/item_set_transitions.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("item_set_closure", []() {
  SyntaxGrammar grammar({
    {
      "rule0",
      {
        Production({
          {Symbol(1), 0, 100},
          {Symbol(11, SymbolOptionToken), 0, 101}
        }, 107),
      }
    },
    {
      "rule1",
      {
        Production({
          {Symbol(12, SymbolOptionToken), 0, 102},
          {Symbol(13, SymbolOptionToken), 0, 103}
        }, 108),
        Production({
          {Symbol(2), 0, 104},
        }, 109)
      }
    },
    {
      "rule2",
      {
        Production({
          {Symbol(14, SymbolOptionToken), 0, 105},
          {Symbol(15, SymbolOptionToken), 0, 106}
        }, 110)
      }
    },
  }, {}, set<Symbol>());

  it("adds items at the beginnings of referenced rules", [&]() {
    ParseItemSet item_set = item_set_closure(
      ParseItem(Symbol(0), 0, 100, 0),
      set<Symbol>({ Symbol(10, SymbolOptionToken) }),
      grammar);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 100, 0),
        set<Symbol>({ Symbol(10, SymbolOptionToken) })
      },
      {
        ParseItem(Symbol(1), 0, 102, 0),
        set<Symbol>({ Symbol(11, SymbolOptionToken) })
      },
      {
        ParseItem(Symbol(1), 1, 104, 0),
        set<Symbol>({ Symbol(11, SymbolOptionToken) })
      },
      {
        ParseItem(Symbol(2), 0, 105, 0),
        set<Symbol>({ Symbol(11, SymbolOptionToken) })
      },
    })));
  });
});

END_TEST
