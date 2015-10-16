#include "compiler/compiler_spec_helper.h"
#include "compiler/syntax_grammar.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/rules/built_in_symbols.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("item_set_closure", []() {
  it("adds items at the beginnings of referenced rules", [&]() {
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

    ParseItemSet item_set = item_set_closure(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 0, 100),
        LookaheadSet({ Symbol(10, true) }),
      }
    }), grammar);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 0, 100),
        LookaheadSet({ Symbol(10, true) })
      },
      {
        ParseItem(Symbol(1), 0, 0, 102),
        LookaheadSet({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(1), 1, 0, 104),
        LookaheadSet({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(2), 0, 0, 105),
        LookaheadSet({ Symbol(11, true) })
      },
    })));
  });

  it("handles rules with empty productions", [&]() {
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
        Production({})
      }),
    }, {}, {}};

    ParseItemSet item_set = item_set_closure(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 0, 100),
        LookaheadSet({ Symbol(10, true) }),
      }
    }), grammar);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0), 0, 0, 100),
        LookaheadSet({ Symbol(10, true) })
      },
      {
        ParseItem(Symbol(1), 0, 0, 102),
        LookaheadSet({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(1), 1, 0, 0),
        LookaheadSet({ Symbol(11, true) })
      },
    })));
  });
});

END_TEST
