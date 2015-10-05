#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/syntax_grammar.h"
#include "compiler/helpers/rule_helpers.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("parse_item_set_transitions(ParseItemSet, SyntaxGrammar)", [&]() {
  it("computes the closure of the new item sets", [&]() {
    SyntaxGrammar grammar{{
      SyntaxVariable("rule_0", VariableTypeNamed, {
        Production({
          {Symbol(11, true), 0, AssociativityNone, 101},
          {Symbol(12, true), 0, AssociativityNone, 102},
          {Symbol(1), 0, AssociativityNone, 103},
          {Symbol(13, true), 0, AssociativityNone, 104},
        })
      }),
      SyntaxVariable("rule_1", VariableTypeNamed, {
        Production({
          {Symbol(2), 0, AssociativityNone, 105},
          {Symbol(14, true), 0, AssociativityNone, 106},
        })
      }),
      SyntaxVariable("rule_2", VariableTypeNamed, {
        Production({
          {Symbol(15, true), 0, AssociativityNone, 105},
        })
      })
    }, {}, {}};

    ParseItemSet set1({
      {
        ParseItem(Symbol(0), 0, 2, 103),
        LookaheadSet({ Symbol(16, true) })
      },
      {
        ParseItem(Symbol(1), 0, 0, 106),
        LookaheadSet({ Symbol(17, true) })
      },
      {
        ParseItem(Symbol(2), 0, 1, 106),
        LookaheadSet({ Symbol(17, true) })
      }
    });

    AssertThat(set1.transitions(grammar), Equals(map<Symbol, ParseItemSet>({
      {
        Symbol(1),
        ParseItemSet({
          {
            ParseItem(Symbol(0), 0, 3, 104),
            LookaheadSet({ Symbol(16, true) })
          }
        })
      },

      {
        Symbol(2),
        ParseItemSet({
          {
            ParseItem(Symbol(1), 0, 1, 106),
            LookaheadSet({ Symbol(17, true) })
          },
        })
      },
    })));
  });
});

END_TEST
