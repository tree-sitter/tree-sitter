#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/rules/metadata.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("LexItem", []() {
  describe("is_token_start()", [&]() {
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

describe("lex_item_set_transitions", [&]() {
  describe("when two items in the set have transitions on the same character", [&]() {
    it("merges the transitions by computing the union of the two item sets", [&]() {
      LexItemSet set1({
        LexItem(Symbol(1), CharacterSet().include('a', 'f').copy()),
        LexItem(Symbol(2), CharacterSet().include('e', 'x').copy())
      });

      AssertThat(lex_item_set_transitions(set1), Equals(map<CharacterSet, LexItemSet>({
        {
          CharacterSet().include('a', 'd'),
          LexItemSet({
            LexItem(Symbol(1), blank()),
          })
        },
        {
          CharacterSet().include('e', 'f'),
          LexItemSet({
            LexItem(Symbol(1), blank()),
            LexItem(Symbol(2), blank()),
          })
        },
        {
          CharacterSet().include('g', 'x'),
          LexItemSet({
            LexItem(Symbol(2), blank()),
          })
        },
      })));
    });
  });
});

END_TEST
