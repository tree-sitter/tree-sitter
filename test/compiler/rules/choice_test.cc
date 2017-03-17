#include "test_helper.h"
#include "compiler/rule.h"

using namespace rules;

START_TEST

describe("Choice", []() {
  describe("constructing choices", [&]() {
    it("eliminates duplicate members", [&]() {
      Rule rule = Rule::choice({
        Rule::seq({ NamedSymbol{"one"}, NamedSymbol{"two"} }),
        NamedSymbol{"three"},
        Rule::seq({ NamedSymbol{"one"}, NamedSymbol{"two"} })
      });

      AssertThat(rule, Equals(Rule(Choice{{
        Rule::seq({ NamedSymbol{"one"}, NamedSymbol{"two"} }),
        NamedSymbol{"three"},
      }})));

      rule = Rule::choice({
        Blank{},
        Blank{},
        Rule::choice({
          Blank{},
          NamedSymbol{"four"}
        })
      });

      AssertThat(rule, Equals(Rule::choice({Blank{}, NamedSymbol{"four"}})));
    });

    it("eliminates duplicates within nested choices", [&]() {
      Rule rule = Rule::choice({
        Rule::seq({
          NamedSymbol{"one"},
          NamedSymbol{"two"}
        }),
        Rule::choice({
          NamedSymbol{"three"},
          Rule::seq({
            NamedSymbol{"one"},
            NamedSymbol{"two"}
          })
        })
      });

      AssertThat(rule, Equals(Rule(Choice{{
        Rule::seq({
          NamedSymbol{"one"},
          NamedSymbol{"two"},
        }),
        NamedSymbol{"three"},
      }})));
    });

    it("doesn't construct a choice if there's only one unique member", [&]() {
      Rule rule = Rule::choice({
        NamedSymbol{"one"},
        Rule::choice({
          NamedSymbol{"one"},
        })
      });

      AssertThat(rule, Equals(Rule(NamedSymbol{"one"})));
    });
  });
});

END_TEST
