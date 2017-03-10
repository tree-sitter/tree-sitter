#include "test_helper.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "helpers/rule_helpers.h"
#include "helpers/stream_methods.h"

START_TEST

using namespace rules;
using prepare_grammar::InitialSyntaxGrammar;
using prepare_grammar::expand_repeats;

describe("expand_repeats", []() {
  it("replaces repeat rules with pairs of recursive rules", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, repeat1(i_token(0))},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, i_sym(1)},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(1), i_token(0) }),
        i_token(0),
      })},
    }));
  });

  it("replaces repeats inside of sequences", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, seq({
          i_token(10),
          repeat1(i_token(11)),
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, seq({
        i_token(10),
        i_sym(1),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(1), i_token(11) }),
        i_token(11)
      })},
    }));
  });

  it("replaces repeats inside of choices", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, choice({
          i_token(10),
          repeat1(i_token(11))
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, choice({
        i_token(10),
        i_sym(1),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(1), i_token(11) }),
        i_token(11),
      })},
    }));
  });

  it("does not create redundant auxiliary rules", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, choice({
          seq({ i_token(1), repeat1(i_token(4)) }),
          seq({ i_token(2), repeat1(i_token(4)) }),
        })},
        Variable{"rule1", VariableTypeNamed, seq({
          i_token(3),
          repeat1(i_token(4))
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, choice({
        seq({ i_token(1), i_sym(2) }),
        seq({ i_token(2), i_sym(2) }),
      })},
      Variable{"rule1", VariableTypeNamed, seq({
        i_token(3),
        i_sym(2),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(2), i_token(4) }),
        i_token(4),
      })},
    }));
  });

  it("can replace multiple repeats in the same rule", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, seq({
          repeat1(i_token(10)),
          repeat1(i_token(11)),
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, seq({
        i_sym(1),
        i_sym(2),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(1), i_token(10) }),
        i_token(10),
      })},
      Variable{"rule0_repeat2", VariableTypeAuxiliary, choice({
        seq({ i_sym(2), i_token(11) }),
        i_token(11),
      })},
    }));
  });

  it("can replace repeats in multiple rules", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, repeat1(i_token(10))},
        Variable{"rule1", VariableTypeNamed, repeat1(i_token(11))},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, i_sym(2)},
      Variable{"rule1", VariableTypeNamed, i_sym(3)},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(2), i_token(10) }),
        i_token(10),
      })},
      Variable{"rule1_repeat1", VariableTypeAuxiliary, choice({
        seq({ i_sym(3), i_token(11) }),
        i_token(11),
      })},
    }));
  });
});

END_TEST
