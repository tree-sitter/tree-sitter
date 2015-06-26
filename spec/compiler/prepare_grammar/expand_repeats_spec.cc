#include "compiler/compiler_spec_helper.h"
#include "compiler/syntax_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_repeats;

describe("expand_repeats", []() {
  it("replaces repeat rules with pairs of recursive rules", [&]() {
    SyntaxGrammar grammar({
        { "rule0", repeat(i_token(0)) },
    }, {}, set<Symbol>(), set<set<Symbol>>());

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(rule_list({
        { "rule0", choice({ i_aux_sym(0), blank() }) },
    })));

    AssertThat(match.aux_rules, Equals(rule_list({
        { "rule0_repeat0", seq({
            i_token(0),
            choice({ i_aux_sym(0), blank() }) }) },
    })));
  });

  it("replaces repeats inside of sequences", [&]() {
    SyntaxGrammar grammar({
        { "rule0", seq({
            i_token(10),
            repeat(i_token(11)) }) },
    }, {}, set<Symbol>(), set<set<Symbol>>());

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(rule_list({
        { "rule0", seq({
            i_token(10),
            choice({ i_aux_sym(0), blank() }) }) },
    })));

    AssertThat(match.aux_rules, Equals(rule_list({
        { "rule0_repeat0", seq({
            i_token(11),
            choice({ i_aux_sym(0), blank() }) }) },
    })));
  });

  it("replaces repeats inside of choices", [&]() {
    SyntaxGrammar grammar({
        { "rule0", choice({ i_token(10), repeat(i_token(11)) }) },
    }, {}, set<Symbol>(), set<set<Symbol>>());

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(rule_list({
        { "rule0", choice({ i_token(10), i_aux_sym(0), blank() }) },
    })));

    AssertThat(match.aux_rules, Equals(rule_list({
        { "rule0_repeat0", seq({
            i_token(11),
            choice({ i_aux_sym(0), blank() }) }) },
    })));
  });

  it("does not create redundant auxiliary rules", [&]() {
    SyntaxGrammar grammar({
        { "rule0", choice({
            seq({ i_token(1), repeat(i_token(4)) }),
            seq({ i_token(2), repeat(i_token(4)) }) }) },
        { "rule1", seq({ i_token(3), repeat(i_token(4)) }) },
    }, {}, set<Symbol>(), set<set<Symbol>>());

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(rule_list({
        { "rule0", choice({
            seq({ i_token(1), choice({ i_aux_sym(0), blank() }) }),
            seq({ i_token(2), choice({ i_aux_sym(0), blank() }) }) }) },
        { "rule1", seq({ i_token(3), choice({ i_aux_sym(0), blank() }) }) },
    })));

    AssertThat(match.aux_rules, Equals(rule_list({
        { "rule0_repeat0", seq({
            i_token(4),
            choice({ i_aux_sym(0), blank() }) }) },
    })));
  });

  it("can replace multiple repeats in the same rule", [&]() {
    SyntaxGrammar grammar({
        { "rule0", seq({
            repeat(i_token(10)),
            repeat(i_token(11)) }) },
    }, {}, set<Symbol>(), set<set<Symbol>>());

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(rule_list({
        { "rule0", seq({
            choice({ i_aux_sym(0), blank() }),
            choice({ i_aux_sym(1), blank() }) }) },
    })));

    AssertThat(match.aux_rules, Equals(rule_list({
        { "rule0_repeat0", seq({
            i_token(10),
            choice({ i_aux_sym(0), blank() }) }) },
        { "rule0_repeat1", seq({
            i_token(11),
            choice({ i_aux_sym(1), blank() }) }) },
    })));
  });

  it("can replace repeats in multiple rules", [&]() {
    SyntaxGrammar grammar({
        { "rule0", repeat(i_token(10)) },
        { "rule1", repeat(i_token(11)) },
    }, {}, set<Symbol>(), set<set<Symbol>>());

    auto match = expand_repeats(grammar);

    AssertThat(match.rules, Equals(rule_list({
        { "rule0", choice({ i_aux_sym(0), blank() }) },
        { "rule1", choice({ i_aux_sym(1), blank() }) },
    })));

    AssertThat(match.aux_rules, Equals(rule_list({
        { "rule0_repeat0", seq({
            i_token(10),
            choice({ i_aux_sym(0), blank() }) }) },
        { "rule1_repeat0", seq({
            i_token(11),
            choice({ i_aux_sym(1), blank() }) }) },
    })));
  });
});

END_TEST
