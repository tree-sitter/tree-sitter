#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/character_set.h"
#include "compiler/build_tables/does_match_any_line.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("does_match_any_line(rule)", []() {
  it("returns true for rules that match any sequence of characters on a line", [&]() {
    rule_ptr rule = character({}, false);
    AssertThat(does_match_any_line(rule), IsFalse());

    rule = repeat(character({}, false));
    AssertThat(does_match_any_line(rule), IsTrue());

    rule = repeat(character({}, false));
    AssertThat(does_match_any_line(rule), IsTrue());

    rule = choice({ repeat(character({}, false)), str("x") });
    AssertThat(does_match_any_line(rule), IsTrue());

    rule = repeat(choice({ character({}, false), str("x") }));
    AssertThat(does_match_any_line(rule), IsTrue());

    rule = choice({ str("y"), str("x") });
    AssertThat(does_match_any_line(rule), IsFalse());

    rule = seq({ repeat(character({}, false)), repeat(character({}, false)) });
    AssertThat(does_match_any_line(rule), IsTrue());

    rule = seq({ repeat(character({}, false)), str("x") });
    AssertThat(does_match_any_line(rule), IsFalse());

    rule = repeat(character({0, '\n'}, false));
    AssertThat(does_match_any_line(rule), IsTrue());
  });
});

END_TEST
