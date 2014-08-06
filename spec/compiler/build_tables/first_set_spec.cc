#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/first_set.h"
#include "compiler/rules/metadata.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("computing FIRST sets", []() {
  const SyntaxGrammar null_grammar;

  describe("for a sequence AB", [&]() {
    it("ignores B when A cannot be blank", [&]() {
      auto rule = seq({ i_token(0), i_token(1) });

      AssertThat(first_set(rule, null_grammar), Equals(set<Symbol>({
          Symbol(0, SymbolOptionToken),
      })));
    });

    it("includes FIRST(B) when A can be blank", [&]() {
      auto rule = seq({
          choice({
              i_token(0),
              blank() }),
          i_token(1) });

      AssertThat(first_set(rule, null_grammar), Equals(set<Symbol>({
          Symbol(0, SymbolOptionToken),
          Symbol(1, SymbolOptionToken)
      })));
    });

    it("includes FIRST(A's right hand side) when A is a non-terminal", [&]() {
      auto rule = choice({
          seq({
              i_token(0),
              i_token(1) }),
          i_sym(0) });

      SyntaxGrammar grammar({
          { "rule0", seq({
              i_token(2),
              i_token(3),
              i_token(4) }) }
      }, {});

      AssertThat(first_set(rule, grammar), Equals(set<Symbol>({
          Symbol(0, SymbolOptionToken),
          Symbol(2, SymbolOptionToken),
      })));
    });

    it("includes FIRST(B) when A is a non-terminal and its expansion can be blank", [&]() {
      auto rule = seq({
          i_sym(0),
          i_token(1) });

      SyntaxGrammar grammar({
          { "rule0", choice({
              i_token(0),
              blank() }) }
      }, {});

      AssertThat(first_set(rule, grammar), Equals(set<Symbol>({
          Symbol(0, SymbolOptionToken),
          Symbol(1, SymbolOptionToken),
      })));
    });
  });

  describe("when there are left-recursive rules", [&]() {
    it("terminates", [&]() {
      SyntaxGrammar grammar({
          { "rule0", choice({
              seq({ i_sym(0), i_token(10) }),
              i_token(11),
          }) },
      }, {});

      auto rule = i_sym(0);

      AssertThat(first_set(rule, grammar), Equals(set<Symbol>({
          Symbol(11, SymbolOptionToken)
      })));
    });
  });

  it("ignores metadata rules", [&]() {
    auto rule = make_shared<Metadata>(i_token(3), map<rules::MetadataKey, int>());

    AssertThat(first_set(rule, null_grammar), Equals(set<Symbol>({
        Symbol(3, SymbolOptionToken),
    })));
  });
});

END_TEST
