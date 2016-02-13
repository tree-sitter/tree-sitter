#include "spec_helper.h"
#include "helpers/stream_methods.h"
#include "compiler/build_tables/symbols_by_first_symbol.h"
#include "compiler/syntax_grammar.h"

using namespace rules;
using build_tables::symbols_by_first_symbol;

START_TEST

describe("symbols_by_first_symbol", [&]() {
  SyntaxGrammar grammar{{

    // starts with token-11 and token-13
    SyntaxVariable("rule-0", VariableTypeNamed, vector<Production>({
      Production({
        ProductionStep(Symbol(11, true), 0, rules::AssociativityNone),
        ProductionStep(Symbol(12, true), 0, rules::AssociativityNone),
      }),
      Production({
        ProductionStep(Symbol(13, true), 0, rules::AssociativityNone),
        ProductionStep(Symbol(14, true), 0, rules::AssociativityNone),
      }),
    })),

    // starts with rule-0, which implies token-11 and token-13
    SyntaxVariable("rule-1", VariableTypeNamed, vector<Production>({
      Production({
        ProductionStep(Symbol(0), 0, rules::AssociativityNone),
        ProductionStep(Symbol(12, true), 0, rules::AssociativityNone),
      }),
    })),

    // starts with token-15 and rule-1, which implies token-11 and token-13
    SyntaxVariable("rule-2", VariableTypeNamed, vector<Production>({
      Production({
        ProductionStep(Symbol(1), 0, rules::AssociativityNone),
      }),
      Production({
        ProductionStep(Symbol(15, true), 0, rules::AssociativityNone),
      }),
    })),

    // starts with token-15
    SyntaxVariable("rule-3", VariableTypeNamed, vector<Production>({
      Production({
        ProductionStep(Symbol(15, true), 0, rules::AssociativityNone),
      }),
    }))
  }, {}, {}};

  it("gives the set of non-terminals that can start with any given terminal", [&]() {
    auto result = symbols_by_first_symbol(grammar);

    AssertThat(result, Equals(map<Symbol, set<Symbol>>({
      {
        Symbol(11, true), {
          Symbol(11, true),
          Symbol(0),
          Symbol(1),
          Symbol(2),
        }
      },
      {
        Symbol(13, true), {
          Symbol(13, true),
          Symbol(0),
          Symbol(1),
          Symbol(2),
        }
      },
      {
        Symbol(15, true), {
          Symbol(15, true),
          Symbol(2),
          Symbol(3)
        }
      },
    })));
  });
});

END_TEST
