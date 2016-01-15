#include "spec_helper.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/symbol.h"

using namespace rules;

START_TEST

describe("Repeat", []() {
  describe("constructing repeats", [&]() {
    it("doesn't create redundant repeats", [&]() {
      auto sym = make_shared<Symbol>(1);
      auto repeat = Repeat::build(sym);
      auto outer_repeat = Repeat::build(repeat);

      AssertThat(repeat, !Equals(sym));
      AssertThat(outer_repeat, Equals(repeat));
    });
  });
});

END_TEST
