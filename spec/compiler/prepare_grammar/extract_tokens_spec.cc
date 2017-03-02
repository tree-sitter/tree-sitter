#include "spec_helper.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "helpers/rule_helpers.h"
#include "helpers/equals_pointer.h"
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
        Variable{"rule_A", VariableTypeNamed, repeat1(seq({
          str("ab"),
          pattern("cd*"),
          choice({
            i_sym(1),
            i_sym(2),
            token(repeat1(choice({ str("ef"), str("gh") }))),
          }),
        }))},
        Variable{"rule_B", VariableTypeNamed, pattern("ij+")},
        Variable{"rule_C", VariableTypeNamed, choice({ str("kl"), blank() })},
        Variable{"rule_D", VariableTypeNamed, repeat1(i_sym(3))},
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
      Variable{"rule_A", VariableTypeNamed, repeat1(seq({

        // This string is now the first token in the lexical grammar.
        i_token(0),

        // This pattern is now the second rule in the lexical grammar.
        i_token(1),

        choice({
          // Rule 1, which this symbol pointed to, has been moved to the
          // lexical grammar.
          i_token(3),

          // This symbol's index has been decremented, because a previous rule
          // was moved to the lexical grammar.
          i_sym(1),

          // This token rule is now the third rule in the lexical grammar.
          i_token(2),
        }),
      }))},

      Variable{"rule_C", VariableTypeNamed, choice({ i_token(4), blank() })},
      Variable{"rule_D", VariableTypeNamed, repeat1(i_sym(2))},
    }));

    AssertThat(lexical_grammar.variables, Equals(vector<LexicalVariable>({
      // Strings become anonymous rules.
      LexicalVariable{"ab", VariableTypeAnonymous, str("ab"), true},

      // Patterns become hidden rules.
      LexicalVariable{"/cd*/", VariableTypeAuxiliary, pattern("cd*"), false},

      // Rules marked as tokens become hidden rules.
      LexicalVariable{"/(ef|gh)*/", VariableTypeAuxiliary, repeat1(choice({
        str("ef"),
        str("gh")
      })), false},

      // This named rule was moved wholesale to the lexical grammar.
      LexicalVariable{"rule_B", VariableTypeNamed, pattern("ij+"), false},

      // Strings become anonymous rules.
      LexicalVariable{"kl", VariableTypeAnonymous, str("kl"), true},
    })));
  });

  it("does not create duplicate tokens in the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        Variable{"rule_A", VariableTypeNamed, seq({
          str("ab"),
          i_sym(0),
          str("ab"),
        })},
      },
      {},
      {},
      {}
    });

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);

    AssertThat(syntax_grammar.variables, Equals(vector<Variable> {
      Variable {"rule_A", VariableTypeNamed, seq({ i_token(0), i_sym(0), i_token(0) })},
    }));

    AssertThat(lexical_grammar.variables, Equals(vector<LexicalVariable> {
      LexicalVariable {"ab", VariableTypeAnonymous, str("ab"), true},
    }))
  });

  it("does not move entire rules into the lexical grammar if their content is used elsewhere in the grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      Variable{"rule_A", VariableTypeNamed, seq({ i_sym(1), str("ab") })},
      Variable{"rule_B", VariableTypeNamed, str("cd")},
      Variable{"rule_C", VariableTypeNamed, seq({ str("ef"), str("cd") })},
    }, {}, {}, {}});

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);

    AssertThat(syntax_grammar.variables, Equals(vector<Variable>({
      Variable{"rule_A", VariableTypeNamed, seq({ i_sym(1), i_token(0) })},
      Variable{"rule_B", VariableTypeNamed, i_token(1)},
      Variable{"rule_C", VariableTypeNamed, seq({ i_token(2), i_token(1) })},
    })));

    AssertThat(lexical_grammar.variables, Equals(vector<LexicalVariable> {
      LexicalVariable {"ab", VariableTypeAnonymous, str("ab"), true},
      LexicalVariable {"cd", VariableTypeAnonymous, str("cd"), true},
      LexicalVariable {"ef", VariableTypeAnonymous, str("ef"), true},
    }));
  });

  it("renumbers the grammar's expected conflict symbols based on any moved rules", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        Variable{"rule_A", VariableTypeNamed, str("ok")},
        Variable{"rule_B", VariableTypeNamed, repeat(i_sym(0))},
        Variable{"rule_C", VariableTypeNamed, repeat(seq({ i_sym(0), i_sym(0) }))},
      },
      {
        str(" ")
      },
      {
        { Symbol(1, Symbol::NonTerminal), Symbol(2, Symbol::NonTerminal) }
      },
      {}
    });

    InitialSyntaxGrammar &syntax_grammar = get<0>(result);

    AssertThat(syntax_grammar.variables.size(), Equals<size_t>(2));
    AssertThat(syntax_grammar.expected_conflicts, Equals(set<set<Symbol>>({
      { Symbol(0, Symbol::NonTerminal), Symbol(1, Symbol::NonTerminal) },
    })));
  });

  describe("handling extra tokens", [&]() {
    it("adds inline extra tokens to the lexical grammar's separators", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{"rule_A", VariableTypeNamed, str("x")},
        },
        {
          str("y"),
          pattern("\\s+"),
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError::none()));

      AssertThat(get<1>(result).separators.size(), Equals<size_t>(2));
      AssertThat(get<1>(result).separators[0], EqualsPointer(str("y")));
      AssertThat(get<1>(result).separators[1], EqualsPointer(pattern("\\s+")));

      AssertThat(get<0>(result).extra_tokens, IsEmpty());
    });

    it("handles inline extra tokens that match tokens in the grammar", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{"rule_A", VariableTypeNamed, str("x")},
          Variable{"rule_B", VariableTypeNamed, str("y")},
        },
        {
          str("y"),
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError::none()));
      AssertThat(get<1>(result).separators.size(), Equals<size_t>(0));
      AssertThat(get<0>(result).extra_tokens, Equals(set<Symbol>({ Symbol(1, Symbol::Terminal) })));
    });

    it("updates extra symbols according to the new symbol numbers", [&]() {
      auto result = extract_tokens(InternedGrammar{
        {
          Variable{"rule_A", VariableTypeNamed, seq({ str("w"), str("x"), i_sym(1) })},
          Variable{"rule_B", VariableTypeNamed, str("y")},
          Variable{"rule_C", VariableTypeNamed, str("z")},
        },
        {
          i_sym(2),
        },
        {},
        {}
      });

      AssertThat(get<2>(result), Equals(CompileError::none()));

      AssertThat(get<0>(result).extra_tokens, Equals(set<Symbol>({
        { Symbol(3, Symbol::Terminal) },
      })));

      AssertThat(get<1>(result).separators, IsEmpty());
    });

    it("returns an error if any extra tokens are non-token symbols", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        Variable{"rule_A", VariableTypeNamed, seq({ str("x"), i_sym(1) })},
        Variable{"rule_B", VariableTypeNamed, seq({ str("y"), str("z") })},
      }, { i_sym(1) }, {}, {}});

      AssertThat(get<2>(result), !Equals(CompileError::none()));
      AssertThat(get<2>(result), Equals(
        CompileError(TSCompileErrorTypeInvalidExtraToken,
                         "Not a token: rule_B")));
    });

    it("returns an error if any extra tokens are non-token rules", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        Variable{"rule_A", VariableTypeNamed, str("x")},
        Variable{"rule_B", VariableTypeNamed, str("y")},
      }, { choice({ i_sym(1), blank() }) }, {}, {}});

      AssertThat(get<2>(result), !Equals(CompileError::none()));
      AssertThat(get<2>(result), Equals(CompileError(
        TSCompileErrorTypeInvalidExtraToken,
        "Not a token: (choice (non-terminal 1) (blank))"
      )));
    });
  });

  it("returns an error if an external token has the same name as a non-terminal rule", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        Variable{"rule_A", VariableTypeNamed, seq({ str("x"), i_sym(1) })},
        Variable{"rule_B", VariableTypeNamed, seq({ str("y"), str("z") })},
      },
      {},
      {},
      {
        ExternalToken {"rule_A", VariableTypeNamed, Symbol(0, Symbol::NonTerminal)}
      }
    });

    AssertThat(get<2>(result), Equals(CompileError(
      TSCompileErrorTypeInvalidExternalToken,
      "Name 'rule_A' cannot be used for both an external token and a non-terminal rule"
    )));
  });
});

END_TEST
