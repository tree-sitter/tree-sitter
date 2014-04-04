#include "compiler_spec_helper.h"
#include "compiler/rules/metadata.h"
#include "compiler/build_tables/check_metadata.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("checking if rules have metadata", []() {
    MetadataValue value = MetadataValue(1 << 3);

    it("returns true for a compatible metadata rule", [&]() {
        auto rule = make_shared<Metadata>(sym("x"), MetadataValue(value | 1));
        AssertThat(check_metadata(rule, value), IsTrue());
    });

    it("returns false for an incompatible metadata rule", [&]() {
        auto rule = make_shared<Metadata>(sym("x"), MetadataValue(1 << 2));
        AssertThat(check_metadata(rule, value), IsFalse());
    });

    it("returns false for a non-metadata rule", [&]() {
        auto rule = sym("x");
        AssertThat(check_metadata(rule, value), IsFalse());
    });

    it("returns true for a compatible metadata rule preceded by rules that can be blank", [&]() {
        auto rule = seq({
            repeat(sym("x")),
            make_shared<Metadata>(sym("x"), MetadataValue(value | 1)),
        });

        AssertThat(check_metadata(rule, value), IsTrue());
    });

    it("returns true for a choice including a compatible metadata rule", [&]() {
        auto rule = choice({
            sym("x"),
            make_shared<Metadata>(sym("x"), MetadataValue(value | 1)),
        });

        AssertThat(check_metadata(rule, value), IsTrue());
    });

    it("returns true for a repetition containing a compatible metadata rule", [&]() {
        auto rule = repeat(make_shared<Metadata>(sym("x"), MetadataValue(value | 1)));
        AssertThat(check_metadata(rule, value), IsTrue());
    });

    it("returns true for a metadata rule preceded by rules that cannot be blank", [&]() {
        auto rule = seq({
            sym("x"),
            make_shared<Metadata>(sym("x"), MetadataValue(value | 1)),
        });
        AssertThat(check_metadata(rule, value), IsFalse());
    });
});

END_TEST
