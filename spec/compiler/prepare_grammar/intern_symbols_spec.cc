#include "compiler/compiler_spec_helper.h"
#include "compiler/prepare_grammar/intern_symbols.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/symbol.h"

START_TEST

using namespace rules;
using prepare_grammar::intern_symbols;

describe("intern_symbols", []() {
  it("replaces named symbols with numerically-indexed symbols", [&]() {
    Grammar grammar({
      { "x", choice({ sym("y"), sym("_z") }) },
      { "y", sym("_z") },
      { "_z", str("stuff") }
    });

    auto result = intern_symbols(grammar);

    AssertThat(result.second, Equals((GrammarError *)nullptr));
    AssertThat(result.first.variables, Equals(vector<Variable>({
      Variable("x", VariableTypeNamed, choice({ i_sym(1), i_sym(2) })),
      Variable("y", VariableTypeNamed, i_sym(2)),
      Variable("_z", VariableTypeHidden, str("stuff")),
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

  it("translates the grammar's optional 'extra_tokens' to numerical symbols", [&]() {
    auto grammar = Grammar({
      { "x", choice({ sym("y"), sym("z") }) },
      { "y", sym("z") },
      { "z", str("stuff") }
    }).extra_tokens({ sym("z") });

    auto result = intern_symbols(grammar);

    AssertThat(result.second, Equals((GrammarError *)nullptr));
    AssertThat(result.first.extra_tokens.size(), Equals<size_t>(1));
    AssertThat(*result.first.extra_tokens.begin(), EqualsPointer(i_sym(2)));
  });
});

END_TEST
