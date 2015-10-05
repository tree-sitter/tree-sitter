#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/syntax_grammar.h"
#include "compiler/helpers/rule_helpers.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("char_transitions(LexItemSet)", []() {
  describe("when two items in the set have transitions on the same character", [&]() {
    it("merges the transitions by computing the union of the two item sets", [&]() {
      LexItemSet set1({
        LexItem(Symbol(1), CharacterSet().include('a', 'f').copy()),
        LexItem(Symbol(2), CharacterSet().include('e', 'x').copy())
      });

      AssertThat(char_transitions(set1), Equals(map<CharacterSet, LexItemSet>({
        {
          CharacterSet().include('a', 'd'),
          LexItemSet({
            LexItem(Symbol(1), blank()),
          })
        },
        {
          CharacterSet().include('e', 'f'),
          LexItemSet({
            LexItem(Symbol(1), blank()),
            LexItem(Symbol(2), blank()),
          })
        },
        {
          CharacterSet().include('g', 'x'),
          LexItemSet({
            LexItem(Symbol(2), blank()),
          })
        },
      })));
    });
  });
});

describe("sym_transitions(ParseItemSet, InitialSyntaxGrammar)", [&]() {
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
        // Step 2 of rule_0's production: right before the reference to rule_1.
        ParseItem(Symbol(0), 0, 2, 103),
        LookaheadSet({ Symbol(16, true) })
      }
    });

    AssertThat(sym_transitions(set1, grammar), Equals(map<Symbol, ParseItemSet>({

      // Consume symbol 1 -> step 3 of rule_0's production
      {
        Symbol(1),
        ParseItemSet({
          {
            ParseItem(Symbol(0), 0, 3, 104),
            LookaheadSet({ Symbol(16, true) })
          }
        })
      },

      // Consume symbol 2 -> step 1 of rule_1's production
      {
        Symbol(2),
        ParseItemSet({
          {
            ParseItem(Symbol(1), 0, 1, 106),
            LookaheadSet({ Symbol(13, true) })
          },
        })
      },

      // Consume token 15 -> step 1 of rule_2's production
      {
        Symbol(15, true),
        ParseItemSet({
          {
            ParseItem(Symbol(2), 0, 1, 0),
            LookaheadSet({ Symbol(14, true) })
          },
        })
      },
    })));
  });
});

END_TEST
