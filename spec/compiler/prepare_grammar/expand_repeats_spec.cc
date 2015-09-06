#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_repeats;

describe("expand_repeats", []() {
  it("replaces repeat rules with pairs of recursive rules", [&]() {
    SyntaxGrammar grammar{{
      {
        "rule0",
        repeat(i_token(0)),
        RuleEntryTypeNamed,
      },
    }, {}, {}};

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(eq_vector<RuleEntry>({
      {
        "rule0",
        choice({ i_sym(1), blank() }),
        RuleEntryTypeNamed,
      },
      {
        "rule0_repeat1",
        seq({
          i_token(0),
          choice({ i_sym(1), blank() })
        }),
        RuleEntryTypeHidden
      },
    })));
  });

  it("replaces repeats inside of sequences", [&]() {
    SyntaxGrammar grammar{{
      {
        "rule0",
        seq({
          i_token(10),
          repeat(i_token(11)),
        }),
        RuleEntryTypeNamed,
      },
    }, {}, {}};

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(eq_vector<RuleEntry>({
      {
        "rule0",
        seq({
          i_token(10),
          choice({ i_sym(1), blank() })
        }),
        RuleEntryTypeNamed
      },
      {
        "rule0_repeat1",
        seq({
          i_token(11),
          choice({ i_sym(1), blank() })
        }),
        RuleEntryTypeHidden
      },
    })));
  });

  it("replaces repeats inside of choices", [&]() {
    SyntaxGrammar grammar{{
      {
        "rule0",
        choice({ i_token(10), repeat(i_token(11)) }),
        RuleEntryTypeNamed
      },
    }, {}, {}};

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(eq_vector<RuleEntry>({
      {
        "rule0",
        choice({ i_token(10), i_sym(1), blank() }),
        RuleEntryTypeNamed
      },
      {
        "rule0_repeat1",
        seq({
          i_token(11),
          choice({ i_sym(1), blank() }),
        }),
        RuleEntryTypeHidden
      },
    })));
  });

  it("does not create redundant auxiliary rules", [&]() {
    SyntaxGrammar grammar{{
      {
        "rule0",
        choice({
          seq({ i_token(1), repeat(i_token(4)) }),
          seq({ i_token(2), repeat(i_token(4)) }),
        }),
        RuleEntryTypeNamed
      },
      {
        "rule1",
        seq({ i_token(3), repeat(i_token(4)) }),
        RuleEntryTypeNamed
      },
    }, {}, {}};

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(eq_vector<RuleEntry>({
      {
        "rule0",
        choice({
          seq({ i_token(1), choice({ i_sym(2), blank() }) }),
          seq({ i_token(2), choice({ i_sym(2), blank() }) }),
        }),
        RuleEntryTypeNamed
      },
      {
        "rule1",
        seq({ i_token(3), choice({ i_sym(2), blank() }) }),
        RuleEntryTypeNamed
      },
      {
        "rule0_repeat1",
        seq({
          i_token(4),
          choice({ i_sym(2), blank() }),
        }),
        RuleEntryTypeHidden
      },
    })));
  });

  it("can replace multiple repeats in the same rule", [&]() {
    SyntaxGrammar grammar{{
      {
        "rule0",
        seq({
          repeat(i_token(10)),
          repeat(i_token(11)),
        }),
        RuleEntryTypeNamed
      },
    }, {}, {}};

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(eq_vector<RuleEntry>({
      {
        "rule0",
        seq({
          choice({ i_sym(1), blank() }),
          choice({ i_sym(2), blank() }),
        }),
        RuleEntryTypeNamed
      },
      {
        "rule0_repeat1",
        seq({
          i_token(10),
          choice({ i_sym(1), blank() }),
        }),
        RuleEntryTypeHidden
      },
      {
        "rule0_repeat2",
        seq({
          i_token(11),
          choice({ i_sym(2), blank() }),
        }),
        RuleEntryTypeHidden
      },
    })));
  });

  it("can replace repeats in multiple rules", [&]() {
    SyntaxGrammar grammar{{
      {
        "rule0",
        repeat(i_token(10)),
        RuleEntryTypeNamed,
      },
      {
        "rule1",
        repeat(i_token(11)),
        RuleEntryTypeNamed,
      },
    }, {}, {}};

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(eq_vector<RuleEntry>({
      {
        "rule0",
        choice({ i_sym(2), blank() }),
        RuleEntryTypeNamed
      },
      {
        "rule1",
        choice({ i_sym(3), blank() }),
        RuleEntryTypeNamed
      },
      {
        "rule0_repeat1",
        seq({
          i_token(10),
          choice({ i_sym(2), blank() }),
        }),
        RuleEntryTypeHidden
      },
      {
        "rule1_repeat1",
        seq({
          i_token(11),
          choice({ i_sym(3), blank() })
        }),
        RuleEntryTypeHidden
      },
    })));
  });
});

END_TEST
