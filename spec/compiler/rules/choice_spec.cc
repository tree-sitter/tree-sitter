#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/choice.h"

using namespace rules;

START_TEST

describe("Choice", []() {
  describe("constructing choices", [&]() {
    it("eliminates duplicate members", [&]() {
      auto rule = Choice::Build({
        seq({ sym("one"), sym("two") }),
        sym("three"),
        seq({ sym("one"), sym("two") })
      });

      AssertThat(rule, EqualsPointer(choice({
        seq({ sym("one"), sym("two") }),
        sym("three"),
      })));
    });

    it("eliminates duplicates within nested choices", [&]() {
      auto rule = Choice::Build({
        seq({ sym("one"), sym("two") }),
        Choice::Build({
          sym("three"),
          seq({ sym("one"), sym("two") })
        })
      });

      AssertThat(rule, EqualsPointer(choice({
        seq({ sym("one"), sym("two") }),
        sym("three"),
      })));
    });

    it("doesn't construct a choice if there's only one unique member", [&]() {
      auto rule = Choice::Build({
        sym("one"),
        Choice::Build({
          sym("one"),
        })
      });

      AssertThat(rule, EqualsPointer(sym("one")));
    });
  });
});

END_TEST
