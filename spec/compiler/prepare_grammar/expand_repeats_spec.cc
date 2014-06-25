#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_repeats;

describe("expanding repeat rules in a grammar", []() {
    it("replaces repeat rules with pairs of recursive rules", [&]() {
        SyntaxGrammar grammar({
            { "rule0", repeat(i_token(0)) },
        }, {}, {});

        auto match = expand_repeats(grammar);

        AssertThat(match.rules, Equals(rule_list({
            { "rule0", i_aux_sym(0) },
        })));

        AssertThat(match.aux_rules, Equals(rule_list({
            { "rule0_repeat0", choice({ seq({ i_token(0), i_aux_sym(0) }), blank() }) },
        })));
    });

    it("replaces repeats inside of sequences", [&]() {
        SyntaxGrammar grammar({
            { "rule0", seq({ i_token(10), repeat(i_token(11)) }) },
        }, {}, {});

        auto match = expand_repeats(grammar);

        AssertThat(match.rules, Equals(rule_list({
            { "rule0", seq({ i_token(10), i_aux_sym(0) }) },
        })));

        AssertThat(match.aux_rules, Equals(rule_list({
            { "rule0_repeat0", choice({
                seq({ i_token(11), i_aux_sym(0) }),
                blank() }) },
        })));
    });

    it("replaces repeats inside of choices", [&]() {
        SyntaxGrammar grammar({
            { "rule0", choice({ i_token(10), repeat(i_token(11)) }) },
        }, {}, {});

        auto match = expand_repeats(grammar);

        AssertThat(match.rules, Equals(rule_list({
            { "rule0", choice({ i_token(10), i_aux_sym(0) }) },
        })));

        AssertThat(match.aux_rules, Equals(rule_list({
            { "rule0_repeat0", choice({
                seq({ i_token(11), i_aux_sym(0) }),
                blank() }) },
        })));
    });

    it("can replace multiple repeats in the same rule", [&]() {
        SyntaxGrammar grammar({
            { "rule0", seq({ repeat(i_token(10)), repeat(i_token(11)) }) },
        }, {}, {});

        auto match = expand_repeats(grammar);

        AssertThat(match.rules, Equals(rule_list({
            { "rule0", seq({ i_aux_sym(0), i_aux_sym(1) }) },
        })));
        
        AssertThat(match.aux_rules, Equals(rule_list({
            { "rule0_repeat0", choice({
                seq({
                    i_token(10),
                    i_aux_sym(0) }),
                blank() }) },
            { "rule0_repeat1", choice({
                seq({
                    i_token(11),
                    i_aux_sym(1) }),
                blank() }) },
        })));
    });

    it("can replace repeats in multiple rules", [&]() {
        SyntaxGrammar grammar({
            { "rule0", repeat(i_token(10)) },
            { "rule1", repeat(i_token(11)) },
        }, {}, {});

        auto match = expand_repeats(grammar);

        AssertThat(match.rules, Equals(rule_list({
            { "rule0", i_aux_sym(0) },
            { "rule1", i_aux_sym(1) },
        })));

        AssertThat(match.aux_rules, Equals(rule_list({
            { "rule0_repeat0", choice({
                seq({ i_token(10), i_aux_sym(0) }),
                blank() }) },
            { "rule1_repeat0", choice({
                seq({ i_token(11), i_aux_sym(1) }),
                blank() }) },
        })));
    });
});

END_TEST
