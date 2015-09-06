#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/first_symbols.h"
#include "compiler/rules/metadata.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("first_symbols", []() {
  SyntaxGrammar null_grammar;

  describe("for a sequence AB", [&]() {
    it("ignores B when A cannot be blank", [&]() {
      auto rule = seq({ i_token(0), i_token(1) });

      AssertThat(first_symbols(rule, null_grammar), Equals(set<Symbol>({
        Symbol(0, true),
      })));
    });

    it("includes first_symbols(B) when A can be blank", [&]() {
      auto rule = seq({
        choice({
          i_token(0),
          blank() }),
        i_token(1) });

      AssertThat(first_symbols(rule, null_grammar), Equals(set<Symbol>({
        Symbol(0, true),
        Symbol(1, true)
      })));
    });

    it("includes first_symbols(A's right hand side) when A is a non-terminal", [&]() {
      auto rule = choice({
        seq({
          i_token(0),
          i_token(1) }),
        i_sym(0) });

      SyntaxGrammar grammar{{
        {
          "rule0",
          seq({
            i_token(2),
            i_token(3),
            i_token(4),
          }),
          RuleEntryTypeNamed
        }
      }, {}, {}};

      AssertThat(first_symbols(rule, grammar), Equals(set<Symbol>({
        Symbol(0),
        Symbol(0, true),
        Symbol(2, true),
      })));
    });

    it("includes first_symbols(B) when A is a non-terminal and its expansion can be blank", [&]() {
      auto rule = seq({
        i_sym(0),
        i_token(1) });

      SyntaxGrammar grammar{{
        {
          "rule0",
          choice({
            i_token(0),
            blank(),
          }),
          RuleEntryTypeNamed
        },
      }, {}, {}};

      AssertThat(first_symbols(rule, grammar), Equals(set<Symbol>({
        Symbol(0),
        Symbol(0, true),
        Symbol(1, true),
      })));
    });
  });

  describe("when there are left-recursive rules", [&]() {
    it("terminates", [&]() {
      SyntaxGrammar grammar{{
        {
          "rule0",
          choice({
            seq({ i_sym(0), i_token(10) }),
            i_token(11),
          }),
          RuleEntryTypeNamed
        },
      }, {}, {}};

      auto rule = i_sym(0);

      AssertThat(first_symbols(rule, grammar), Equals(set<Symbol>({
        Symbol(0),
        Symbol(11, true)
      })));
    });
  });

  it("ignores metadata rules", [&]() {
    auto rule = make_shared<Metadata>(i_token(3), map<rules::MetadataKey, int>());

    AssertThat(first_symbols(rule, null_grammar), Equals(set<Symbol>({
      Symbol(3, true),
    })));
  });
});

END_TEST
