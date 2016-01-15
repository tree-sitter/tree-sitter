#include "spec_helper.h"
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
          {Symbol(1), 0, AssociativityNone},
          {Symbol(11, true), 0, AssociativityNone},
        }),
      }),
      SyntaxVariable("rule1", VariableTypeNamed, {
        Production({
          {Symbol(12, true), 0, AssociativityNone},
          {Symbol(13, true), 0, AssociativityNone},
        }),
        Production({
          {Symbol(2), 0, AssociativityNone},
        })
      }),
      SyntaxVariable("rule2", VariableTypeNamed, {
        Production({
          {Symbol(14, true), 0, AssociativityNone},
          {Symbol(15, true), 0, AssociativityNone},
        })
      }),
    }, {}, {}};

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet item_set = item_set_closure(ParseItemSet({
      {
        ParseItem(Symbol(0), production(0, 0), 0),
        LookaheadSet({ Symbol(10, true) }),
      }
    }), grammar);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0), production(0, 0), 0),
        LookaheadSet({ Symbol(10, true) })
      },
      {
        ParseItem(Symbol(1), production(1, 0), 0),
        LookaheadSet({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(1), production(1, 1), 0),
        LookaheadSet({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(2), production(2, 0), 0),
        LookaheadSet({ Symbol(11, true) })
      },
    })));
  });

  it("handles rules with empty productions", [&]() {
    SyntaxGrammar grammar{{
      SyntaxVariable("rule0", VariableTypeNamed, {
        Production({
          {Symbol(1), 0, AssociativityNone},
          {Symbol(11, true), 0, AssociativityNone},
        }),
      }),
      SyntaxVariable("rule1", VariableTypeNamed, {
        Production({
          {Symbol(12, true), 0, AssociativityNone},
          {Symbol(13, true), 0, AssociativityNone},
        }),
        Production({})
      }),
    }, {}, {}};

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet item_set = item_set_closure(ParseItemSet({
      {
        ParseItem(Symbol(0), production(0, 0), 0),
        LookaheadSet({ Symbol(10, true) }),
      }
    }), grammar);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0), production(0, 0), 0),
        LookaheadSet({ Symbol(10, true) })
      },
      {
        ParseItem(Symbol(1), production(1, 0), 0),
        LookaheadSet({ Symbol(11, true) })
      },
      {
        ParseItem(Symbol(1), production(1, 1), 0),
        LookaheadSet({ Symbol(11, true) })
      },
    })));
  });
});

END_TEST
