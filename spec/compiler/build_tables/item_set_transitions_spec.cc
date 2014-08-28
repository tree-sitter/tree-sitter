#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/prepared_grammar.h"
#include "compiler/helpers/rule_helpers.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("lexical item set transitions", []() {
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

describe("syntactic item set transitions", [&]() {
  SyntaxGrammar grammar({
      { "A", blank() },
      { "B", i_token(21) },
  }, {}, set<Symbol>());

  it("computes the closure of the new item sets", [&]() {
    ParseItemSet set1({
        {
            ParseItem(Symbol(0), seq({ i_token(22), i_sym(1) }), 3),
            set<Symbol>({ Symbol(23, SymbolOptionToken) })
        },
    });

    AssertThat(sym_transitions(set1, grammar), Equals(map<Symbol, ParseItemSet>({
        {
            Symbol(22, SymbolOptionToken),
            ParseItemSet({
                {
                    ParseItem(Symbol(0), i_sym(1), 4),
                    set<Symbol>({ Symbol(23, SymbolOptionToken) }),
                },
                {
                    ParseItem(Symbol(1), i_token(21), 0),
                    set<Symbol>({ Symbol(23, SymbolOptionToken) })
                },
            })
        },
    })));
  });
});

END_TEST
