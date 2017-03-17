#include "test_helper.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "helpers/stream_methods.h"

using namespace rules;
using prepare_grammar::InitialSyntaxGrammar;
using prepare_grammar::expand_repeats;

START_TEST

describe("expand_repeats", []() {
  it("replaces repeat rules with pairs of recursive rules", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, Repeat{Symbol::terminal(0)}},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, Symbol::non_terminal(1)},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(1), Symbol::terminal(0) }),
        Symbol::terminal(0),
      })},
    }));
  });

  it("replaces repeats inside of sequences", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, Rule::seq({
          Symbol::terminal(10),
          Repeat{Symbol::terminal(11)},
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, Rule::seq({
        Symbol::terminal(10),
        Symbol::non_terminal(1),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(1), Symbol::terminal(11) }),
        Symbol::terminal(11)
      })},
    }));
  });

  it("replaces repeats inside of choices", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, Rule::choice({
          Symbol::terminal(10),
          Repeat{Symbol::terminal(11)}
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, Rule::choice({
        Symbol::terminal(10),
        Symbol::non_terminal(1),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(1), Symbol::terminal(11) }),
        Symbol::terminal(11),
      })},
    }));
  });

  it("does not create redundant auxiliary rules", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, Rule::choice({
          Rule::seq({ Symbol::terminal(1), Repeat{Symbol::terminal(4)} }),
          Rule::seq({ Symbol::terminal(2), Repeat{Symbol::terminal(4)} }),
        })},
        Variable{"rule1", VariableTypeNamed, Rule::seq({
          Symbol::terminal(3),
          Repeat{Symbol::terminal(4)}
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, Rule::choice({
        Rule::seq({ Symbol::terminal(1), Symbol::non_terminal(2) }),
        Rule::seq({ Symbol::terminal(2), Symbol::non_terminal(2) }),
      })},
      Variable{"rule1", VariableTypeNamed, Rule::seq({
        Symbol::terminal(3),
        Symbol::non_terminal(2),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(2), Symbol::terminal(4) }),
        Symbol::terminal(4),
      })},
    }));
  });

  it("can replace multiple repeats in the same rule", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, Rule::seq({
          Repeat{Symbol::terminal(10)},
          Repeat{Symbol::terminal(11)},
        })},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, Rule::seq({
        Symbol::non_terminal(1),
        Symbol::non_terminal(2),
      })},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(1), Symbol::terminal(10) }),
        Symbol::terminal(10),
      })},
      Variable{"rule0_repeat2", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(2), Symbol::terminal(11) }),
        Symbol::terminal(11),
      })},
    }));
  });

  it("can replace repeats in multiple rules", [&]() {
    InitialSyntaxGrammar grammar{
      {
        Variable{"rule0", VariableTypeNamed, Repeat{Symbol::terminal(10)}},
        Variable{"rule1", VariableTypeNamed, Repeat{Symbol::terminal(11)}},
      },
      {}, {}, {}
    };

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>{
      Variable{"rule0", VariableTypeNamed, Symbol::non_terminal(2)},
      Variable{"rule1", VariableTypeNamed, Symbol::non_terminal(3)},
      Variable{"rule0_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(2), Symbol::terminal(10) }),
        Symbol::terminal(10),
      })},
      Variable{"rule1_repeat1", VariableTypeAuxiliary, Rule::choice({
        Rule::seq({ Symbol::non_terminal(3), Symbol::terminal(11) }),
        Symbol::terminal(11),
      })},
    }));
  });
});

END_TEST
