#include "spec_helper.h"
#include "transitions.h"

START_TEST

describe("Rules", []() {
    rules::rule_ptr symbol1 = rules::sym("1");
    rules::rule_ptr symbol2 = rules::sym("2");
    rules::rule_ptr symbol3 = rules::sym("3");
    
    describe("construction", [&]() {
        it("constructs binary trees", [&]() {
            AssertThat(
                rules::seq({ symbol1, symbol2, symbol3 }),
                EqualsPointer(
                    rules::seq({ rules::seq({ symbol1, symbol2 }), symbol3 })));

            AssertThat(
                rules::choice({ symbol1, symbol2, symbol3 }),
                EqualsPointer(
                    rules::choice({ rules::choice({ symbol1, symbol2 }), symbol3 })));
        });
    });
});

END_TEST
