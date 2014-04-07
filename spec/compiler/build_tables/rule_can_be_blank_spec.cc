#include "compiler_spec_helper.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/metadata.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using build_tables::rule_can_be_blank;

START_TEST

describe("checking if rules can be blank", [&]() {
    rule_ptr rule;

    it("returns false for basic rules", [&]() {
        AssertThat(rule_can_be_blank(sym("x")), IsFalse());
        AssertThat(rule_can_be_blank(str("x")), IsFalse());
        AssertThat(rule_can_be_blank(pattern("x")), IsFalse());
    });

    it("returns true for blanks", [&]() {
        AssertThat(rule_can_be_blank(blank()), IsTrue());
    });

    it("returns true for repeats", [&]() {
        AssertThat(rule_can_be_blank(repeat(str("x"))), IsTrue());
    });

    it("returns true for choices iff one or more sides can be blank", [&]() {
        rule = choice({ sym("x"), blank() });
        AssertThat(rule_can_be_blank(rule), IsTrue());

        rule = choice({ blank(), sym("x") });
        AssertThat(rule_can_be_blank(rule), IsTrue());

        rule = choice({ sym("x"), sym("y") });
        AssertThat(rule_can_be_blank(rule), IsFalse());
    });

    it("returns true for sequences iff both sides can be blank", [&]() {
        rule = seq({ blank(), str("x") });
        AssertThat(rule_can_be_blank(rule), IsFalse());

        rule = seq({ str("x"), blank() });
        AssertThat(rule_can_be_blank(rule), IsFalse());

        rule = seq({ blank(), choice({ sym("x"), blank() }) });
        AssertThat(rule_can_be_blank(rule), IsTrue());
    });

    it("ignores metadata rules", [&]() {
        rule = make_shared<rules::Metadata>(blank(), map<rules::MetadataKey, int>());
        AssertThat(rule_can_be_blank(rule), IsTrue());

        rule = make_shared<rules::Metadata>(sym("one"), map<rules::MetadataKey, int>());
        AssertThat(rule_can_be_blank(rule), IsFalse());
    });

    describe("checking recursively (by expanding non-terminals)", [&]() {
        PreparedGrammar grammar({
            { "A", choice({
                seq({ sym("A"), sym("x") }),
                blank() }) },
            { "B", choice({
                seq({ sym("B"), sym("y") }),
                sym("z") }) },
        }, {});

        it("terminates for left-recursive rules that can be blank", [&]() {
            rule = sym("A");
            AssertThat(rule_can_be_blank(rule, grammar), IsTrue());
        });

        it("terminates for left-recursive rules that can't be blank", [&]() {
            rule = sym("B");
            AssertThat(rule_can_be_blank(rule, grammar), IsFalse());
        });
    });
});

END_TEST