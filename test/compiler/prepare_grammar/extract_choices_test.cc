#include "test_helper.h"
#include "helpers/stream_methods.h"
#include "compiler/prepare_grammar/extract_choices.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_choices;

describe("extract_choices", []() {
  it("expands rules containing choices into multiple rules", [&]() {
    auto rule = Seq::build({
      Symbol::terminal(1),
      Choice::build({
        Symbol::terminal(2),
        Symbol::terminal(3),
        Symbol::terminal(4)
      }),
      Symbol::terminal(5)
    });

    auto result = extract_choices(rule);

    AssertThat(result, Equals(vector<Rule>({
      Seq::build({Symbol::terminal(1), Symbol::terminal(2), Symbol::terminal(5)}),
      Seq::build({Symbol::terminal(1), Symbol::terminal(3), Symbol::terminal(5)}),
      Seq::build({Symbol::terminal(1), Symbol::terminal(4), Symbol::terminal(5)}),
    })));
  });

  it("handles metadata rules", [&]() {
    auto rule = Metadata::prec(5, Choice::build({
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
    auto rule = Choice::build({
      Seq::build({
        Choice::build({
          Symbol::terminal(1),
          Symbol::terminal(2)
        }),
        Symbol::terminal(3)
      }),
      Symbol::terminal(4)
    });

    AssertThat(extract_choices(rule), Equals(vector<Rule>({
      Seq::build({Symbol::terminal(1), Symbol::terminal(3)}),
      Seq::build({Symbol::terminal(2), Symbol::terminal(3)}),
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
