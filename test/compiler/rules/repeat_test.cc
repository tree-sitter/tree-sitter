#include "test_helper.h"
#include "compiler/rule.h"

using namespace rules;

START_TEST

describe("Repeat", []() {
  describe("constructing repeats", [&]() {
    it("doesn't create redundant repeats", [&]() {
      Rule symbol = Symbol::non_terminal(1);
      Rule repeat = Repeat::build(Rule(symbol));
      Rule outer_repeat = Repeat::build(Rule(repeat));

      AssertThat(repeat, !Equals(symbol));
      AssertThat(outer_repeat, Equals(repeat));
    });
  });
});

END_TEST
