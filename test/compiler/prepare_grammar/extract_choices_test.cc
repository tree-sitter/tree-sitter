#include "test_helper.h"
#include "helpers/stream_methods.h"
#include "compiler/prepare_grammar/extract_choices.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_choices;

describe("extract_choices", []() {
  it("expands rules containing choices into multiple rules", [&]() {
    auto rule = Rule::seq({
      Symbol::terminal(1),
      Rule::choice({
        Symbol::terminal(2),
        Symbol::terminal(3),
        Symbol::terminal(4)
      }),
      Symbol::terminal(5)
    });

    auto result = extract_choices(rule);

    AssertThat(result, Equals(vector<Rule>({
      Rule::seq({Symbol::terminal(1), Symbol::terminal(2), Symbol::terminal(5)}),
      Rule::seq({Symbol::terminal(1), Symbol::terminal(3), Symbol::terminal(5)}),
      Rule::seq({Symbol::terminal(1), Symbol::terminal(4), Symbol::terminal(5)}),
    })));
  });

  it("handles metadata rules", [&]() {
    auto rule = Metadata::prec(5, Rule::choice({
      Symbol::terminal(2),
      Symbol::terminal(3),
      Symbol::terminal(4)
    }));

    AssertThat(extract_choices(rule), Equals(vector<Rule>({
      Metadata::prec(5, Symbol::terminal(2)),
      Metadata::prec(5, Symbol::terminal(3)),
      Metadata::prec(5, Symbol::terminal(4)),
    })));
  });

  it("handles nested choices", [&]() {
    auto rule = Rule::choice({
      Rule::seq({
        Rule::choice({
          Symbol::terminal(1),
          Symbol::terminal(2)
        }),
        Symbol::terminal(3)
      }),
      Symbol::terminal(4)
    });

    AssertThat(extract_choices(rule), Equals(vector<Rule>({
      Rule::seq({Symbol::terminal(1), Symbol::terminal(3)}),
      Rule::seq({Symbol::terminal(2), Symbol::terminal(3)}),
      Symbol::terminal(4),
    })));
  });

  it("handles single symbols", [&]() {
    AssertThat(extract_choices(Symbol::terminal(2)), Equals(vector<Rule>({
      Symbol::terminal(2)
    })));
  });

  it("handles blank rules", [&]() {
    AssertThat(extract_choices(Blank{}), Equals(vector<Rule>({
      Blank{},
    })));
  });
});

END_TEST
