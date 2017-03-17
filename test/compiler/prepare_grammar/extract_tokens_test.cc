#include "test_helper.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "helpers/stream_methods.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_tokens;
using prepare_grammar::InternedGrammar;
using prepare_grammar::InitialSyntaxGrammar;

describe("extract_tokens", []() {
  it("moves strings, patterns, and sub-rules marked as tokens into the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        Variable{
          "rule_A",
          VariableTypeNamed,
          Repeat{Rule::seq({
            String{"ab"},
            Pattern{"cd+"},
            Rule::choice({
              Symbol::non_terminal(1),
              Symbol::non_terminal(2),
              Metadata::token(Repeat{Rule::choice({
                String{"ef"},
                String{"g"}
              })}),
            }),
          })}
        },
        Variable{
          "rule_B",
          VariableTypeNamed,
          Pattern{"h+"}
        },
        Variable{
          "rule_C",
          VariableTypeNamed,
          Rule::choice({ String{"i"}, Blank{} })
        },
        Variable{
          "rule_D",
          VariableTypeNamed,
          Repeat{Symbol::non_terminal(3)}
        },
      },
      {},
      {},
      {}
    });

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);
    CompileError error = get<2>(result);

    AssertThat(error, Equals(CompileError::none()));

    AssertThat(syntax_grammar.variables, Equals(vector<Variable>{
      Variable{
        "rule_A",
        VariableTypeNamed,
        Repeat{Rule::seq({

          // This string is now the first token in the lexical grammar.
          Symbol::terminal(0),

          // This pattern is now the second rule in the lexical grammar.
          Symbol::terminal(1),

          Rule::choice({
            // Rule 1, which this symbol pointed to, has been moved to the
            // lexical grammar.
            Symbol::terminal(3),

            // This symbol's index has been decremented, because a previous rule
            // was moved to the lexical grammar.
            Symbol::non_terminal(1),

            // This token rule is now the third rule in the lexical grammar.
            Symbol::terminal(2),
          }),
        })}
      },

      Variable{
        "rule_C",
        VariableTypeNamed,
        Rule::choice({Symbol::terminal(4), Blank{}})
      },

      Variable{
        "rule_D",
        VariableTypeNamed,
        Repeat{Symbol::non_terminal(2)}
      },
    }));

    AssertThat(lexical_grammar.variables, Equals(vector<LexicalVariable>({
      // Strings become anonymous rules.
      LexicalVariable{
        "ab",
        VariableTypeAnonymous,
        Seq{CharacterSet{{'a'}}, CharacterSet{{'b'}}},
        true
      },

      // Patterns become hidden rules.
      LexicalVariable{
        "/cd+/",
        VariableTypeAuxiliary,
        Seq{CharacterSet{{'c'}}, Repeat{CharacterSet{{'d'}}}},
        false
      },

      // Rules marked as tokens become hidden rules.
      LexicalVariable{
        "/(ef|g)+/",
        VariableTypeAuxiliary,
        Repeat{Rule::choice({
          Seq{CharacterSet{{'e'}}, CharacterSet{{'f'}}},
          CharacterSet{{'g'}},
        })},
        false
      },

      // This named rule was moved wholesale to the lexical grammar.
      LexicalVariable{
        "rule_B",
        VariableTypeNamed,
        Repeat{CharacterSet{{'h'}}},
        false
      },

      // Strings become anonymous rules.
      LexicalVariable{
        "i",
        VariableTypeAnonymous,
        CharacterSet{{'i'}},
        true
      },
    })));
  });

  it("does not create duplicate tokens in the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        {
          "rule_A",
          VariableTypeNamed,
          Rule::seq({
            String{"ab"},
            Symbol::non_terminal(1),
            String{"ab"},
          })
        },
      },
      {},
      {},
      {}
    });

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);

    AssertThat(syntax_grammar.variables, Equals(vector<Variable> {
      Variable{
        "rule_A",
        VariableTypeNamed,
        Rule::seq({
          Symbol::terminal(0),
          Symbol::non_terminal(1),
          Symbol::terminal(0)
        })
      },
    }));

    AssertThat(lexical_grammar.variables, Equals(vector<LexicalVariable> {
      LexicalVariable{
        "ab",
        VariableTypeAnonymous,
        Seq{CharacterSet{{'a'}}, CharacterSet{{'b'}}},
        true
      },
    }))
  });

  it("does not move entire rules into the lexical grammar if their content is used elsewhere in the grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      Variable{
        "rule_A",
        VariableTypeNamed,
        Rule::seq({ Symbol::non_terminal(1), String{"ab"} })
      },
      Variable{
        "rule_B",
        VariableTypeNamed,
        String{"cd"}
      },
      Variable{
        "rule_C",
        VariableTypeNamed,
        Rule::seq({ String{"ef"}, String{"cd"} })
      },
    }, {}, {}, {}});

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);

    AssertThat(syntax_grammar.variables, Equals(vector<Variable>({
      Variable{
        "rule_A",
        VariableTypeNamed,
        Rule::seq({ Symbol::non_terminal(1), Symbol::terminal(0) })
      },
      Variable{
        "rule_B",
        VariableTypeNamed,
        Symbol::terminal(1)
      },
      Variable{
        "rule_C",
        VariableTypeNamed,
        Rule::seq({ Symbol::terminal(2), Symbol::terminal(1) })
      },
    })));

    AssertThat(lexical_grammar.variables, Equals(vector<LexicalVariable> {
      LexicalVariable{
        "ab",
        VariableTypeAnonymous,
        Seq{CharacterSet{{'a'}}, CharacterSet{{'b'}}},
        true
      },
      LexicalVariable{
        "cd",
        VariableTypeAnonymous,
        Seq{CharacterSet{{'c'}}, CharacterSet{{'d'}}},
        true
      },
      LexicalVariable{
        "ef",
        VariableTypeAnonymous,
        Seq{CharacterSet{{'e'}}, CharacterSet{{'f'}}},
        true
      },
    }));
  });

  it("renumbers the grammar's expected conflict symbols based on any moved rules", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        Variable{
          "rule_A",
          VariableTypeNamed,
          String{"ok"}
        },
        Variable{
          "rule_B",
          VariableTypeNamed,
          Repeat{Symbol::non_terminal(0)}
        },
        Variable{
          "rule_C",
          VariableTypeNamed,
          Repeat{Seq{Symbol::non_terminal(0), Symbol::non_terminal(0)}}
        },
      },
      {
        String{" "}
      },
      {
        { Symbol::non_terminal(1), Symbol::non_terminal(2) }
      },
      {}
    });

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);

    AssertThat(syntax_grammar.variables.size(), Equals<size_t>(2));
    AssertThat(syntax_grammar.expected_conflicts, Equals(set<set<Symbol>>({
      { Symbol::non_terminal(0), Symbol::non_terminal(1) },
    })));
  });

  describe("handling extra tokens", [&]() {
    it("adds inline extra tokens to the lexical grammar's separators", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{"rule_A", VariableTypeNamed, String{"x"}},
        },
        {
          String{"y"},
          Pattern{" "},
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError::none()));

      AssertThat(get<1>(result).separators.size(), Equals<size_t>(2));
      AssertThat(get<1>(result).separators[0], Equals(Rule(CharacterSet{{'y'}})));
      AssertThat(get<1>(result).separators[1], Equals(Rule(CharacterSet{{' '}})));

      AssertThat(get<0>(result).extra_tokens, IsEmpty());
    });

    it("handles inline extra tokens that match tokens in the grammar", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{"rule_A", VariableTypeNamed, String{"x"}},
          Variable{"rule_B", VariableTypeNamed, String{"y"}},
        },
        {
          String{"y"},
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError::none()));
      AssertThat(get<1>(result).separators.size(), Equals<size_t>(0));
      AssertThat(get<0>(result).extra_tokens, Equals(set<Symbol>({ Symbol::terminal(1) })));
    });

    it("updates extra symbols according to the new symbol numbers", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{
            "rule_A",
            VariableTypeNamed,
            Rule::seq({ String{"w"}, String{"x"}, Symbol::non_terminal(1) })
          },
          Variable{
            "rule_B",
            VariableTypeNamed,
            String{"y"}
          },
          Variable{
            "rule_C",
            VariableTypeNamed,
            String{"z"}
          },
        },
        {
          Symbol::non_terminal(2),
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError::none()));

      AssertThat(get<0>(result).extra_tokens, Equals(set<Symbol>({
        { Symbol::terminal(3) },
      })));

      AssertThat(get<1>(result).separators, IsEmpty());
    });

    it("returns an error if any extra tokens are non-token symbols", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{
            "rule_A",
            VariableTypeNamed,
            Rule::seq({ String{"x"}, Symbol::non_terminal(1) })
          },
          Variable{
            "rule_B",
            VariableTypeNamed,
            Rule::seq({ String{"y"}, String{"z"} })
          },
        },
        {
          Symbol::non_terminal(1)
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError(
        TSCompileErrorTypeInvalidExtraToken,
        "Non-token symbol rule_B can't be used as an extra token"
      )));
    });

    it("returns an error if any extra tokens are non-token rules", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          {"rule_A", VariableTypeNamed, String{"x"}},
          {"rule_B", VariableTypeNamed, String{"y"}},
        },
        {
          Rule::choice({ Symbol::non_terminal(1), Blank{} })
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError(
        TSCompileErrorTypeInvalidExtraToken,
        "Non-token rule expression can't be used as an extra token"
      )));
    });
  });

  it("returns an error if an external token has the same name as a non-terminal rule", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        {
          "rule_A",
          VariableTypeNamed,
          Rule::seq({ String{"x"}, Symbol::non_terminal(1) })
        },
        {
          "rule_B",
          VariableTypeNamed,
          Rule::seq({ String{"y"}, String{"z"} })
        },
      },
      {},
      {},
      {
        Variable{"rule_A", VariableTypeNamed, Symbol::non_terminal(0)}
      }
    });

    AssertThat(get<2>(result), Equals(CompileError(
      TSCompileErrorTypeInvalidExternalToken,
      "Name 'rule_A' cannot be used for both an external token and a non-terminal rule"
    )));
  });
});

END_TEST
