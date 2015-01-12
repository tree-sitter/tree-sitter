#include "compiler/compiler_spec_helper.h"
#include "compiler/prepare_grammar/extract_choices.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_choices;

describe("extract_choices", []() {
  it("expands rules containing choices into multiple rules", [&]() {
    auto rule = seq({
        sym("a"),
        choice({ sym("b"), sym("c"), sym("d") }),
        sym("e")
    });

    AssertThat(extract_choices(rule), Equals(rule_vector({
        seq({ sym("a"), sym("b"), sym("e") }),
        seq({ sym("a"), sym("c"), sym("e") }),
        seq({ sym("a"), sym("d"), sym("e") }),
    })));
  });

  it("handles metadata rules", [&]() {
    auto rule = prec(5, choice({ sym("b"), sym("c"), sym("d") }));

    AssertThat(extract_choices(rule), Equals(rule_vector({
        prec(5, sym("b")),
        prec(5, sym("c")),
        prec(5, sym("d")),
    })));
  });

  it("handles nested choices", [&]() {
    auto rule = choice({
        seq({ choice({ sym("a"), sym("b") }), sym("c") }),
        sym("d")
    });

    AssertThat(extract_choices(rule), Equals(rule_vector({
      seq({ sym("a"), sym("c") }),
      seq({ sym("b"), sym("c") }),
      sym("d"),
    })));
  });

  it("handles repeats", [&]() {
    auto rule = repeat(choice({ sym("a"), sym("b") }));

    AssertThat(extract_choices(rule), Equals(rule_vector({
        repeat(sym("a")),
        repeat(sym("b")),
    })));
  });
});

END_TEST
