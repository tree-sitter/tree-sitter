#include "compiler/compiler_spec_helper.h"
#include "compiler/rules/metadata.h"
#include "compiler/build_tables/get_metadata.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("get_metadata(rule, key)", []() {
  MetadataKey key1 = MetadataKey(100);
  MetadataKey key2 = MetadataKey(101);
  rule_ptr rule;

  describe("with a rule without the metadata key", [&]() {
    it("returns the zero range", [&]() {
      rule = sym("x");
      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(0, 0)));

      rule = seq({ sym("x"), sym("y") });
      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(0, 0)));

      rule = metadata(seq({ sym("x"), sym("y") }), {{key2, 5}});
      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(0, 0)));
    });
  });

  describe("when given a metadata rule", [&]() {
    before_each([&]() {
      rule = make_shared<Metadata>(sym("x"), map<MetadataKey, int>({
        { key1, 1 },
        { key2, 2 },
      }));
    });

    it("returns the value for the given key", [&]() {
      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(1, 1)));
      AssertThat(get_metadata(rule, key2), Equals(MetadataRange(2, 2)));
    });

    it("returns 0 if the rule does not have the key", [&]() {
      AssertThat(get_metadata(rule, MetadataKey(0)), Equals(MetadataRange(0, 0)));
    });

    describe("when the rule contains another metadata rule", [&]() {
      it("also gets metadata from the inner metadata rule", [&]() {
        rule = make_shared<Metadata>(make_shared<Metadata>(sym("x"), map<MetadataKey, int>({
          { key1, 1 }
        })), map<MetadataKey, int>());

        AssertThat(get_metadata(rule, key1), Equals(MetadataRange(1, 1)));
      });
    });
  });

  describe("with a sequence starting with a metadata rule", [&]() {
    it("returns the metadata rule's value for the key", [&]() {
      rule = seq({
        metadata(sym("x"), {{key1, 5}}),
        sym("y")
      });

      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(5, 5)));
    });
  });

  describe("with a sequence whose starting value can be blank", [&]() {
    it("includes later elements of the sequence in the returned range", [&]() {
      rule = seq({
        repeat(metadata(sym("x"), {{key1, 3}})),
        choice({ metadata(sym("x"), {{key1, 5}}), blank() }),
        metadata(sym("x"), {{key1, 7}}),
        metadata(sym("x"), {{key1, 9}}),
      });

      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(3, 7)));
    });
  });

  describe("with a sequence whose starting value can be blank", [&]() {
    it("includes later elements of the sequence in the returned range", [&]() {
      rule = seq({
        repeat(metadata(sym("x"), {{key1, 3}})),
        choice({ metadata(sym("x"), {{key1, 5}}), blank() }),
        metadata(sym("x"), {{key1, 7}}),
        metadata(sym("x"), {{key1, 9}}),
      });

      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(3, 7)));
    });
  });

  describe("with a choice rule", [&]() {
    it("merges the ranges for the choices elements", [&]() {
      rule = choice({
        metadata(sym("a"), {{key1, 5}}),
        metadata(sym("b"), {{key1, 3}}),
        sym("c"),
        metadata(sym("d"), {{key1, 1}}),
      });

      AssertThat(get_metadata(rule, key1), Equals(MetadataRange(1, 5)));
    });
  });
});

END_TEST
