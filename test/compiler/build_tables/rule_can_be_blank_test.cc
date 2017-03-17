#include "test_helper.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rule.h"

using namespace rules;
using build_tables::rule_can_be_blank;

START_TEST

describe("rule_can_be_blank", [&]() {
  Rule rule;

  it("returns false for basic rules", [&]() {
    AssertThat(rule_can_be_blank(CharacterSet{{'x'}}), IsFalse());
  });

  it("returns true for blanks", [&]() {
    AssertThat(rule_can_be_blank(Blank{}), IsTrue());
  });

  it("returns true for repeats iff the content can be blank", [&]() {
    AssertThat(rule_can_be_blank(Repeat{CharacterSet{{'x'}}}), IsFalse());
    AssertThat(rule_can_be_blank(Repeat{Blank{}}), IsTrue());
  });

  it("returns true for choices iff one or more sides can be blank", [&]() {
    rule = Rule::choice({ CharacterSet{{'x'}}, Blank{} });
    AssertThat(rule_can_be_blank(rule), IsTrue());

    rule = Rule::choice({ Blank{}, CharacterSet{{'x'}} });
    AssertThat(rule_can_be_blank(rule), IsTrue());

    rule = Rule::choice({ CharacterSet{{'x'}}, CharacterSet{{'y'}} });
    AssertThat(rule_can_be_blank(rule), IsFalse());
  });

  it("returns true for sequences iff both sides can be blank", [&]() {
    rule = Rule::seq({ Blank{}, CharacterSet{{'x'}} });
    AssertThat(rule_can_be_blank(rule), IsFalse());

    rule = Rule::seq({ CharacterSet{{'x'}}, Blank{} });
    AssertThat(rule_can_be_blank(rule), IsFalse());

    rule = Rule::seq({ Blank{}, Rule::choice({ CharacterSet{{'x'}}, Blank{} }) });
    AssertThat(rule_can_be_blank(rule), IsTrue());
  });

  it("ignores metadata rules", [&]() {
    rule = Metadata::prec(1, Blank{});
    AssertThat(rule_can_be_blank(rule), IsTrue());

    rule = Metadata::prec(1, CharacterSet{{'x'}});
    AssertThat(rule_can_be_blank(rule), IsFalse());
  });
});

END_TEST
