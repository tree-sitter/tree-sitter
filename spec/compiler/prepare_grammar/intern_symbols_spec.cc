#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/intern_symbols.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/symbol.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::intern_symbols;

describe("interning symbols in a grammar", []() {
  it("replaces named symbols with numerically-indexed symbols", [&]() {
    Grammar grammar({
        { "x", choice({ sym("y"), sym("z") }) },
        { "y", sym("z") },
        { "z", str("stuff") }
    });

    auto result = intern_symbols(grammar);

    AssertThat(result.second, Equals((GrammarError *)nullptr));
    AssertThat(result.first.rules, Equals(rule_list({
        { "x", choice({ i_sym(1), i_sym(2) }) },
        { "y", i_sym(2) },
        { "z", str("stuff") },
    })));
  });

  describe("when there are symbols that reference undefined rules", [&]() {
    it("returns an error", []() {
      Grammar grammar({
          { "x", sym("y") },
      });

      auto result = intern_symbols(grammar);

      AssertThat(result.second->message, Equals("Undefined rule 'y'"));
    });
  });

  it("translates the grammar's optional 'ubiquitous_tokens' to numerical symbols", [&]() {
    auto grammar = Grammar({
        { "x", choice({ sym("y"), sym("z") }) },
        { "y", sym("z") },
        { "z", str("stuff") }
    }).ubiquitous_tokens({ "z" });

    auto result = intern_symbols(grammar);

    AssertThat(result.second, Equals((GrammarError *)nullptr));
    AssertThat(result.first.ubiquitous_tokens, Equals(set<Symbol>({
        Symbol(2)
    })));
  });
});

END_TEST
