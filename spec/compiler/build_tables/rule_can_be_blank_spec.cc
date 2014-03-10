#include "compiler_spec_helper.h"
#include "compiler/build_tables/rule_can_be_blank.h"

using namespace rules;
using build_tables::rule_can_be_blank;

START_TEST

describe("checking if rules can be blank", [&]() {
    it("handles sequences", [&]() {
        rule_ptr rule = seq({
            choice({
                str("x"),
                blank(),
            }),
            str("y"),
        });

        AssertThat(rule_can_be_blank(rule), Equals(false));
    });
});

END_TEST