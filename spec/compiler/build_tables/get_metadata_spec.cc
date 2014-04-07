#include "compiler_spec_helper.h"
#include "compiler/rules/metadata.h"
#include "compiler/build_tables/get_metadata.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("getting metadata for rules", []() {
    MetadataKey key1 = MetadataKey(100);
    MetadataKey key2 = MetadataKey(101);

    describe("when given a metadata rule", [&]() {
        auto rule = make_shared<Metadata>(sym("x"), map<MetadataKey, int>({
            { key1, 1 },
            { key2, 2 },
        }));

        it("returns the value for the given key", [&]() {
            AssertThat(get_metadata(rule, key1), Equals(1));
            AssertThat(get_metadata(rule, key2), Equals(2));
        });

        it("returns 0 if the rule does not have the key", [&]() {
            AssertThat(get_metadata(rule, MetadataKey(3)), Equals(0));
        });
    });

    describe("when given a non-metadata rule", [&]() {
        it("returns 0", [&]() {
            auto rule = sym("x");
            AssertThat(get_metadata(rule, key1), Equals(0));
        });
    });

    it("works for metadata rules preceded by other rules that can be blank", [&]() {
        auto rule = seq({
            repeat(sym("x")),
            make_shared<Metadata>(sym("x"), map<MetadataKey, int>({
                { key1, 1 },
                { key2, 2 },
            })),
        });

        AssertThat(get_metadata(rule, key2), Equals(2));
    });

    it("works for choices containing metadata rule", [&]() {
        auto rule = choice({
            sym("x"),
            make_shared<Metadata>(sym("x"), map<MetadataKey, int>({
                { key1, 1 },
                { key2, 2 },
            })),
        });

        AssertThat(get_metadata(rule, key2), Equals(1));
    });

    it("works for repetitions containing metadata rules", [&]() {
        auto rule = repeat(make_shared<Metadata>(sym("x"), map<MetadataKey, int>({
            { key1, 1 },
            { key2, 2 },
        })));
        AssertThat(get_metadata(rule, key2), Equals(2));
    });

    it("returns 0 for metadata rules preceded by rules that can't be blank", [&]() {
        auto rule = seq({
            sym("x"),
            make_shared<Metadata>(sym("y"), map<MetadataKey, int>({
                { key1, 1 },
                { key2, 2 },
            })),
        });
        AssertThat(get_metadata(rule, key2), Equals(0));
    });
});

END_TEST
