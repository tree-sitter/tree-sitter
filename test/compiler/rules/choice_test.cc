#include "test_helper.h"
#include "compiler/rule.h"

using namespace rules;

START_TEST

describe("Choice", []() {
  describe("constructing choices", [&]() {
    it("eliminates duplicate members", [&]() {
      Rule rule = Choice::build({
        Seq::build({ NamedSymbol{"one"}, NamedSymbol{"two"} }),
        NamedSymbol{"three"},
        Seq::build({ NamedSymbol{"one"}, NamedSymbol{"two"} })
      });

      AssertThat(rule, Equals(Rule(Choice{{
        Seq::build({ NamedSymbol{"one"}, NamedSymbol{"two"} }),
        NamedSymbol{"three"},
      }})));

      rule = Choice::build({
        Blank{},
        Blank{},
        Choice::build({
          Blank{},
          NamedSymbol{"four"}
        })
      });

      AssertThat(rule, Equals(*Choice::build({Blank{}, NamedSymbol{"four"}})));
    });

    it("eliminates duplicates within nested choices", [&]() {
      Rule rule = Choice::build({
        Seq::build({
          NamedSymbol{"one"},
          NamedSymbol{"two"}
        }),
        Choice::build({
          NamedSymbol{"three"},
          Seq::build({
            NamedSymbol{"one"},
            NamedSymbol{"two"}
          })
        })
      });

      AssertThat(rule, Equals(Rule(Choice{{
        Seq::build({
          NamedSymbol{"one"},
          NamedSymbol{"two"},
        }),
        NamedSymbol{"three"},
      }})));
    });

    it("doesn't construct a choice if there's only one unique member", [&]() {
      Rule rule = Choice::build({
        NamedSymbol{"one"},
        Choice::build({
          NamedSymbol{"one"},
        })
      });

      AssertThat(rule, Equals(Rule(NamedSymbol{"one"})));
    });
  });
});

END_TEST
