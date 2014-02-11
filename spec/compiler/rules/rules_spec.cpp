#include "spec_helper.h"

using namespace rules;

START_TEST

describe("constructing rules", []() {
    rule_ptr symbol1 = sym("1");
    rule_ptr symbol2 = sym("2");
    rule_ptr symbol3 = sym("3");
    
    it("constructs binary trees", [&]() {
        AssertThat(
            seq({ symbol1, symbol2, symbol3 }),
            EqualsPointer(seq({ seq({ symbol1, symbol2 }), symbol3 })));
        
        AssertThat(
            choice({ symbol1, symbol2, symbol3 }),
            EqualsPointer(choice({ choice({ symbol1, symbol2 }), symbol3 })));
    });
});

END_TEST
