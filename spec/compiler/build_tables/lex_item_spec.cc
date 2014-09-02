#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/rules/metadata.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("lex items", []() {
  describe("determining if an item is the start of a token", [&]() {
    Symbol sym(1);
    rule_ptr token_start = make_shared<Metadata>(str("a"), map<MetadataKey, int>({
        { START_TOKEN, 1 }
    }));

    it("returns true for rules designated as token starts", [&]() {
      LexItem item(sym, token_start);
      AssertThat(item.is_token_start(), IsTrue());
    });

    it("returns false for rules not designated as token starts", [&]() {
      AssertThat(LexItem(sym, make_shared<Metadata>(str("a"), map<MetadataKey, int>({
          { START_TOKEN, 0 }
      }))).is_token_start(), IsFalse());
      AssertThat(LexItem(sym, str("a")).is_token_start(), IsFalse());
    });

    describe("when given a sequence containing a token start", [&]() {
      it("returns true when the rule before the token start may be blank", [&]() {
        LexItem item(sym, seq({ repeat(str("a")), token_start }));
        AssertThat(item.is_token_start(), IsTrue());
      });

      it("returns false when the rule before the token start cannot be blank", [&]() {
        LexItem item(sym, seq({ str("a"), token_start }));
        AssertThat(item.is_token_start(), IsFalse());
      });
    });
  });
});

END_TEST
