#include "test_helper.h"
#include "compiler/rules/choice.h"
#include "helpers/rule_helpers.h"
#include "helpers/equals_pointer.h"

using namespace rules;

START_TEST

describe("Choice", []() {
  describe("constructing choices", [&]() {
    it("eliminates duplicate members", [&]() {
      auto rule = Choice::build({
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
      auto rule = Choice::build({
        seq({ sym("one"), sym("two") }),
        Choice::build({
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
      auto rule = Choice::build({
        sym("one"),
        Choice::build({
          sym("one"),
        })
      });

      AssertThat(rule, EqualsPointer(sym("one")));
    });
  });
});

END_TEST
