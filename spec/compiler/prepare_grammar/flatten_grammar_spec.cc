#include "spec_helper.h"
#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/syntax_grammar.h"
#include "helpers/rule_helpers.h"
#include "helpers/stream_methods.h"

START_TEST

using namespace rules;
using prepare_grammar::flatten_rule;

describe("flatten_grammar", []() {
  it("associates each symbol with the precedence and associativity binding it to its successor", [&]() {
    SyntaxVariable result = flatten_rule(Variable(
      "test",
      VariableTypeNamed,
      seq({
        i_sym(1),
        prec_left(101, seq({
          i_sym(2),
          choice({
            prec_right(102, seq({
              i_sym(3),
              i_sym(4)
            })),
            i_sym(5),
          }),
          i_sym(6),
        })),
        i_sym(7),
      })
    ));

    AssertThat(result.name, Equals("test"));
    AssertThat(result.type, Equals(VariableTypeNamed));
    AssertThat(result.productions, Equals(vector<Production>({
      Production({
        {Symbol(1), 0, AssociativityNone},
        {Symbol(2), 101, AssociativityLeft},
        {Symbol(3), 102, AssociativityRight},
        {Symbol(4), 101, AssociativityLeft},
        {Symbol(6), 0, AssociativityNone},
        {Symbol(7), 0, AssociativityNone},
      }),
      Production({
        {Symbol(1), 0, AssociativityNone},
        {Symbol(2), 101, AssociativityLeft},
        {Symbol(5), 101, AssociativityLeft},
        {Symbol(6), 0, AssociativityNone},
        {Symbol(7), 0, AssociativityNone},
      })
    })))
  });

  it("uses the last assigned precedence", [&]() {
    SyntaxVariable result = flatten_rule(Variable(
      "test1",
      VariableTypeNamed,
      prec_left(101, seq({
        i_sym(1),
        i_sym(2),
      }))
    ));

    AssertThat(result.productions, Equals(vector<Production>({
      Production({
        {Symbol(1), 101, AssociativityLeft},
        {Symbol(2), 101, AssociativityLeft},
      })
    })))

    result = flatten_rule(Variable(
      "test2",
      VariableTypeNamed,
      prec_left(101, seq({
        i_sym(1),
      }))
    ));

    AssertThat(result.productions, Equals(vector<Production>({
      Production({
        {Symbol(1), 101, AssociativityLeft},
      })
    })))
  });
});

END_TEST
