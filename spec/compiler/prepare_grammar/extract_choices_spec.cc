#include "compiler/compiler_spec_helper.h"
#include "compiler/prepare_grammar/extract_choices.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_choices;

class rule_vector : public vector<rule_ptr> {
 public:
  bool operator==(const vector<rule_ptr> &other) const {
    if (this->size() != other.size()) return false;
    for (size_t i = 0; i < this->size(); i++) {
      auto rule = this->operator[](i);
      auto other_rule = other[i];
      if (!rule->operator==(*rule))
        return false;
    }
    return true;
  }

  rule_vector(const initializer_list<rule_ptr> &list) :
      vector<rule_ptr>(list) {}
};

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
