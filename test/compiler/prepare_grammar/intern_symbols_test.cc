#include "test_helper.h"
#include "compiler/prepare_grammar/intern_symbols.h"
#include "compiler/grammar.h"
#include "compiler/rule.h"
#include "helpers/stream_methods.h"

START_TEST

using namespace rules;
using prepare_grammar::intern_symbols;
using prepare_grammar::InternedExternalToken;

describe("intern_symbols", []() {
  it("replaces named symbols with numerically-indexed symbols", [&]() {
    InputGrammar grammar{
      {
        {"x", VariableTypeNamed, Rule::choice({ NamedSymbol{"y"}, NamedSymbol{"_z"} })},
        {"y", VariableTypeNamed, NamedSymbol{"_z"}},
        {"_z", VariableTypeNamed, String{"stuff"}}
      },
      {}, {}, {}, {}
    };

    auto result = intern_symbols(grammar);

    AssertThat(result.second, Equals(CompileError::none()));
    AssertThat(result.first.variables, Equals(vector<Variable>{
      {"x", VariableTypeNamed, Rule::choice({ Symbol::non_terminal(1), Symbol::non_terminal(2) })},
      {"y", VariableTypeNamed, Symbol::non_terminal(2)},
      {"_z", VariableTypeHidden, String{"stuff"}},
    }));
  });

  describe("when there are symbols that reference undefined rules", [&]() {
    it("returns an error", []() {
      InputGrammar grammar{
        {
          {"x", VariableTypeNamed, NamedSymbol{"y"}},
        },
        {}, {}, {}, {}
      };

      auto result = intern_symbols(grammar);

      AssertThat(result.second.message, Equals("Undefined rule 'y'"));
    });
  });

  it("translates the grammar's optional 'extra_tokens' to numerical symbols", [&]() {
    InputGrammar grammar{
      {
        {"x", VariableTypeNamed, Rule::choice({ NamedSymbol{"y"}, NamedSymbol{"z"} })},
        {"y", VariableTypeNamed, NamedSymbol{"z"}},
        {"z", VariableTypeNamed, String{"stuff"}}
      },
      {
        NamedSymbol{"z"}
      },
      {}, {}, {}
    };

    auto result = intern_symbols(grammar);

    AssertThat(result.second, Equals(CompileError::none()));
    AssertThat(result.first.extra_tokens.size(), Equals<size_t>(1));
    AssertThat(result.first.extra_tokens, Equals(vector<Rule>({ Symbol::non_terminal(2) })));
  });

  it("records any rule names that match external token names", [&]() {
    InputGrammar grammar{
      {
        {"x", VariableTypeNamed, Rule::choice({ NamedSymbol{"y"}, NamedSymbol{"z"} })},
        {"y", VariableTypeNamed, NamedSymbol{"z"}},
        {"z", VariableTypeNamed, String{"stuff"}},
      },
      {},
      {},
      {
        InputExternalToken{
          NamedSymbol{"w"},
          false,
        },
        InputExternalToken{
          NamedSymbol{"z"},
          false,
        },
      },
      {}
    };

    auto result = intern_symbols(grammar);

    AssertThat(result.first.external_tokens, Equals(vector<InternedExternalToken>{
      InternedExternalToken{
        "w",
        VariableTypeNamed,
        Symbol::external(0),
        false
      },
      InternedExternalToken{
        "z",
        VariableTypeNamed,
        Symbol::non_terminal(2),
        false
      },
    }))
  });
});

END_TEST
