#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/syntax_grammar.h"
#include "compiler/helpers/rule_helpers.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("ParseItemSet::transitions())", [&]() {
  it("returns a map of symbols to ParseItemSets that would result from consuming those symbols", [&]() {
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

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet set1({
      {
        ParseItem(Symbol(0), production(0, 0), 2),
        LookaheadSet({ Symbol(16, true) })
      },
      {
        ParseItem(Symbol(1), production(1, 0), 0),
        LookaheadSet({ Symbol(17, true) })
      },
      {
        ParseItem(Symbol(2), production(2, 0), 1),
        LookaheadSet({ Symbol(17, true) })
      }
    });

    AssertThat(set1.transitions(), Equals(map<Symbol, ParseItemSet>({
      {
        Symbol(1),
        ParseItemSet({
          {
            ParseItem(Symbol(0), production(0, 0), 3),
            LookaheadSet({ Symbol(16, true) })
          }
        })
      },

      {
        Symbol(2),
        ParseItemSet({
          {
            ParseItem(Symbol(1), production(1, 0), 1),
            LookaheadSet({ Symbol(17, true) })
          },
        })
      },
    })));
  });
});

END_TEST
