#include "compiler/compiler_spec_helper.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"

START_TEST

using namespace rules;
using prepare_grammar::InitialSyntaxGrammar;
using prepare_grammar::expand_repeats;

describe("expand_repeats", []() {
  it("replaces repeat rules with pairs of recursive rules", [&]() {
    InitialSyntaxGrammar grammar{{
      Variable("rule0", VariableTypeNamed, repeat(i_token(0))),
    }, {}, {}};

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>({
      Variable("rule0", VariableTypeNamed, choice({ i_sym(1), blank() })),
      Variable("rule0_repeat1", VariableTypeAuxiliary, seq({
        i_token(0),
        choice({ i_sym(1), blank() })
      })),
    })));
  });

  it("replaces repeats inside of sequences", [&]() {
    InitialSyntaxGrammar grammar{{
      Variable("rule0", VariableTypeNamed, seq({
        i_token(10),
        repeat(i_token(11)),
      })),
    }, {}, {}};

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>({
      Variable("rule0", VariableTypeNamed, seq({
        i_token(10),
        choice({ i_sym(1), blank() })
      })),
      Variable("rule0_repeat1", VariableTypeAuxiliary, seq({
        i_token(11),
        choice({ i_sym(1), blank() })
      })),
    })));
  });

  it("replaces repeats inside of choices", [&]() {
    InitialSyntaxGrammar grammar{{
      Variable("rule0", VariableTypeNamed, choice({
        i_token(10),
        repeat(i_token(11))
      })),
    }, {}, {}};

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>({
      Variable("rule0", VariableTypeNamed, choice({ i_token(10), i_sym(1), blank() })),
      Variable("rule0_repeat1", VariableTypeAuxiliary, seq({
        i_token(11),
        choice({ i_sym(1), blank() }),
      })),
    })));
  });

  it("does not create redundant auxiliary rules", [&]() {
    InitialSyntaxGrammar grammar{{
      Variable("rule0", VariableTypeNamed, choice({
        seq({ i_token(1), repeat(i_token(4)) }),
        seq({ i_token(2), repeat(i_token(4)) }),
      })),
      Variable("rule1", VariableTypeNamed, seq({
        i_token(3),
        repeat(i_token(4))
      })),
    }, {}, {}};

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>({
      Variable("rule0", VariableTypeNamed, choice({
        seq({ i_token(1), choice({ i_sym(2), blank() }) }),
        seq({ i_token(2), choice({ i_sym(2), blank() }) }),
      })),
      Variable("rule1", VariableTypeNamed, seq({
        i_token(3),
        choice({ i_sym(2), blank() })
      })),
      Variable("rule0_repeat1", VariableTypeAuxiliary, seq({
        i_token(4),
        choice({ i_sym(2), blank() }),
      })),
    })));
  });

  it("can replace multiple repeats in the same rule", [&]() {
    InitialSyntaxGrammar grammar{{
      Variable("rule0", VariableTypeNamed, seq({
        repeat(i_token(10)),
        repeat(i_token(11)),
      })),
    }, {}, {}};

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>({
      Variable("rule0", VariableTypeNamed, seq({
        choice({ i_sym(1), blank() }),
        choice({ i_sym(2), blank() }),
      })),
      Variable("rule0_repeat1", VariableTypeAuxiliary, seq({
        i_token(10),
        choice({ i_sym(1), blank() }),
      })),
      Variable("rule0_repeat2", VariableTypeAuxiliary, seq({
        i_token(11),
        choice({ i_sym(2), blank() }),
      })),
    })));
  });

  it("can replace repeats in multiple rules", [&]() {
    InitialSyntaxGrammar grammar{{
      Variable("rule0", VariableTypeNamed, repeat(i_token(10))),
      Variable("rule1", VariableTypeNamed, repeat(i_token(11))),
    }, {}, {}};

    auto result = expand_repeats(grammar);

    AssertThat(result.variables, Equals(vector<Variable>({
      Variable("rule0", VariableTypeNamed, choice({
        i_sym(2),
        blank(),
      })),
      Variable("rule1", VariableTypeNamed, choice({
        i_sym(3),
        blank(),
      })),
      Variable("rule0_repeat1", VariableTypeAuxiliary, seq({
        i_token(10),
        choice({ i_sym(2), blank() }),
      })),
      Variable("rule1_repeat1", VariableTypeAuxiliary, seq({
        i_token(11),
        choice({ i_sym(3), blank() })
      })),
    })));
  });
});

END_TEST
