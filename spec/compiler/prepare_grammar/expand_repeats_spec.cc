#include "compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/rules/symbol.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_repeats;

describe("expanding repeat rules in a grammar", []() {
    it("replaces repeat rules with pairs of recursive rules", [&]() {
        PreparedGrammar grammar({
            { "rule0", repeat(i_token(0)) },
        }, {});
        
        AssertThat(expand_repeats(grammar), Equals(PreparedGrammar({
            { "rule0", i_aux_sym(0) },
        }, {
            { "rule0_repeat0", choice({
                seq({
                    i_token(0),
                    i_aux_sym(0) }),
                blank() }) },
        })));
    });
    
    it("replaces repeats inside of sequences", [&]() {
        PreparedGrammar grammar({
            { "rule0", seq({ i_token(10), repeat(i_token(11)) }) },
        }, {});
        
        AssertThat(expand_repeats(grammar), Equals(PreparedGrammar({
            { "rule0", seq({ i_token(10), i_aux_sym(0) }) },
        }, {
            { "rule0_repeat0", choice({
                seq({ i_token(11), i_aux_sym(0) }),
                blank() }) },
        })));
    });
    
    it("replaces repeats inside of choices", [&]() {
        PreparedGrammar grammar({
            { "rule0", choice({ i_token(10), repeat(i_token(11)) }) },
        }, {});
        
        AssertThat(expand_repeats(grammar), Equals(PreparedGrammar({
            { "rule0", choice({ i_token(10), i_aux_sym(0) }) },
        }, {
            { "rule0_repeat0", choice({
                seq({ i_token(11), i_aux_sym(0) }),
                blank() }) },
        })));
    });
    
    it("can replace multiple repeats in the same rule", [&]() {
        PreparedGrammar grammar({
            { "rule0", seq({ repeat(i_token(10)), repeat(i_token(11)) }) },
        }, {});
        
        AssertThat(expand_repeats(grammar), Equals(PreparedGrammar({
            { "rule0", seq({ i_aux_sym(0), i_aux_sym(1) }) },
        }, {
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
        PreparedGrammar grammar({
            { "rule0", repeat(i_token(10)) },
            { "rule1", repeat(i_token(11)) },
        }, {});
        
        AssertThat(expand_repeats(grammar), Equals(PreparedGrammar({
            { "rule0", i_aux_sym(0) },
            { "rule1", i_aux_sym(1) },
        }, {
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