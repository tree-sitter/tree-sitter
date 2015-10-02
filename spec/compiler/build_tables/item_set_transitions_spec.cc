#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/item_set_transitions.h"
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
      SyntaxVariable("A", VariableTypeNamed, {
        Production({
          {Symbol(11, true), 0, AssociativityNone, 101},
          {Symbol(12, true), 0, AssociativityNone, 102},
          {Symbol(13, true), 0, AssociativityNone, 103},
          {Symbol(1), 0, AssociativityNone, 104},
          {Symbol(14, true), 0, AssociativityNone, 105},
        })
      }),
      SyntaxVariable("B", VariableTypeNamed, {
        Production({
          {Symbol(15, true), 0, AssociativityNone, 106},
        })
      })
    }, {}, {}};

    ParseItemSet set1({
      {
        ParseItem(Symbol(0), 0, 2, 103),
        set<Symbol>({ Symbol(16, true) })
      }
    });

    AssertThat(sym_transitions(set1, grammar), Equals(map<Symbol, ParseItemSet>({
      {
        Symbol(13, true),
        ParseItemSet({
          {
            ParseItem(Symbol(0), 0, 3, 104),
            set<Symbol>({ Symbol(16, true) })
          },
          {
            ParseItem(Symbol(1), 0, 0, 106),
            set<Symbol>({ Symbol(14, true) })
          },
        })
      },
    })));
  });
});

END_TEST
