#include "test_helper.h"
#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/syntax_grammar.h"
#include "helpers/stream_methods.h"

START_TEST

using namespace rules;
using prepare_grammar::flatten_rule;

describe("flatten_grammar", []() {
  it("associates each symbol with the precedence and associativity binding it to its successor", [&]() {
    SyntaxVariable result = flatten_rule({
      "test",
      VariableTypeNamed,
      Rule::seq({
        Symbol::non_terminal(1),
        Metadata::prec_left(101, Rule::seq({
          Symbol::non_terminal(2),
          Rule::choice({
            Metadata::prec_right(102, Rule::seq({
              Symbol::non_terminal(3),
              Symbol::non_terminal(4)
            })),
            Symbol::non_terminal(5),
          }),
          Symbol::non_terminal(6),
        })),
        Symbol::non_terminal(7),
      })
    });

    AssertThat(result.name, Equals("test"));
    AssertThat(result.type, Equals(VariableTypeNamed));
    AssertThat(result.productions, Equals(vector<Production>({
      Production({
        {Symbol::non_terminal(1), 0, AssociativityNone},
        {Symbol::non_terminal(2), 101, AssociativityLeft},
        {Symbol::non_terminal(3), 102, AssociativityRight},
        {Symbol::non_terminal(4), 101, AssociativityLeft},
        {Symbol::non_terminal(6), 0, AssociativityNone},
        {Symbol::non_terminal(7), 0, AssociativityNone},
      }),
      Production({
        {Symbol::non_terminal(1), 0, AssociativityNone},
        {Symbol::non_terminal(2), 101, AssociativityLeft},
        {Symbol::non_terminal(5), 101, AssociativityLeft},
        {Symbol::non_terminal(6), 0, AssociativityNone},
        {Symbol::non_terminal(7), 0, AssociativityNone},
      })
    })))
  });

  it("uses the last assigned precedence", [&]() {
    SyntaxVariable result = flatten_rule({
      "test1",
      VariableTypeNamed,
      Metadata::prec_left(101, Rule::seq({
        Symbol::non_terminal(1),
        Symbol::non_terminal(2),
      }))
    });

    AssertThat(result.productions, Equals(vector<Production>({
      Production({
        {Symbol::non_terminal(1), 101, AssociativityLeft},
        {Symbol::non_terminal(2), 101, AssociativityLeft},
      })
    })))

    result = flatten_rule({
      "test2",
      VariableTypeNamed,
      Metadata::prec_left(101, Rule::seq({
        Symbol::non_terminal(1),
      }))
    });

    AssertThat(result.productions, Equals(vector<Production>({
      Production({
        {Symbol::non_terminal(1), 101, AssociativityLeft},
      })
    })))
  });
});

END_TEST
