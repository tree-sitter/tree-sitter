#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_tokens;
using prepare_grammar::InternedGrammar;

describe("extract_tokens", []() {
  it("moves strings, patterns, and sub-rules marked as tokens into the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      {
        "rule_A",
        repeat(seq({
          str("ab"),
          pattern("cd*"),
          choice({
            i_sym(1),
            i_sym(2),
            token(repeat(choice({ str("ef"), str("gh") }))),
          }),
        })),
        RuleEntryTypeNamed,
      },
      {
        "rule_B",
        pattern("ij+"),
        RuleEntryTypeNamed,
      },
      {
        "rule_C",
        choice({ str("kl"), blank() }),
        RuleEntryTypeNamed,
      },
      {
        "rule_D",
        repeat(i_sym(3)),
        RuleEntryTypeNamed,
      }
    }, {}, {}});

    SyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);
    const GrammarError *error = get<2>(result);

    AssertThat(error, Equals<const GrammarError *>(nullptr));

    AssertThat(syntax_grammar.rules, Equals(vector<RuleEntry>({
      {
        "rule_A",
        repeat(seq({

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
        })),
        RuleEntryTypeNamed,
      },
      {
        "rule_C",
        choice({ i_token(4), blank() }),
        RuleEntryTypeNamed,
      },
      {
        "rule_D",
        repeat(i_sym(2)),
        RuleEntryTypeNamed,
      }
    })));

    AssertThat(lexical_grammar.rules, Equals(vector<RuleEntry>({

      // Strings become anonymous rules.
      {
        "ab",
        str("ab"),
        RuleEntryTypeAnonymous,
      },

      // Patterns become hidden rules.
      {
        "/cd*/",
        pattern("cd*"),
        RuleEntryTypeAuxiliary,
      },

      // Rules marked as tokens become hidden rules.
      {
        "/(ef|gh)*/",
        repeat(choice({ str("ef"), str("gh") })),
        RuleEntryTypeAuxiliary,
      },

      // This named rule was moved wholesale to the lexical grammar.
      {
        "rule_B",
        pattern("ij+"),
        RuleEntryTypeNamed,
      },

      // Strings become anonymous rules.
      {
        "kl",
        str("kl"),
        RuleEntryTypeAnonymous,
      },

    })));
  });

  it("does not create duplicate tokens in the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      {
        "rule_A",
        seq({
          str("ab"),
          i_sym(0),
          str("ab"),
        }),
        RuleEntryTypeNamed,
      },
    }, {}, {}});

    SyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);

    AssertThat(syntax_grammar.rules, Equals(vector<RuleEntry>({
      {
        "rule_A",
        seq({ i_token(0), i_sym(0), i_token(0) }),
        RuleEntryTypeNamed
      }
    })));

    AssertThat(lexical_grammar.rules, Equals(vector<RuleEntry>({
      {
        "ab",
        str("ab"),
        RuleEntryTypeAnonymous
      },
    })))
  });

  it("does not move entire rules into the lexical grammar if their content is used elsewhere in the grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      {
        "rule_A",
        seq({ i_sym(1), str("ab") }),
        RuleEntryTypeNamed,
      },
      {
        "rule_B",
        str("cd"),
        RuleEntryTypeNamed,
      },
      {
        "rule_C",
        seq({ str("ef"), str("cd") }),
        RuleEntryTypeNamed,
      },
    }, {}, {}});

    SyntaxGrammar &syntax_grammar = get<0>(result);
    LexicalGrammar &lexical_grammar = get<1>(result);

    AssertThat(syntax_grammar.rules, Equals(vector<RuleEntry>({
      {
        "rule_A",
        seq({ i_sym(1), i_token(0) }),
        RuleEntryTypeNamed
      },
      {
        "rule_B",
        i_token(1),
        RuleEntryTypeNamed
      },
      {
        "rule_C",
        seq({ i_token(2), i_token(1) }),
        RuleEntryTypeNamed
      },
    })));

    AssertThat(lexical_grammar.rules, Equals(vector<RuleEntry>({
      {
        "ab",
        str("ab"),
        RuleEntryTypeAnonymous
      },
      {
        "cd",
        str("cd"),
        RuleEntryTypeAnonymous
      },
      {
        "ef",
        str("ef"),
        RuleEntryTypeAnonymous
      },
    })));
  });

  it("renumbers the grammar's expected conflict symbols based on any moved rules", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      {
        "rule_A",
        str("ok"),
        RuleEntryTypeNamed,
      },
      {
        "rule_B",
        repeat(i_sym(0)),
        RuleEntryTypeNamed,
      },
      {
        "rule_C",
        repeat(seq({ i_sym(0), i_sym(0) })),
        RuleEntryTypeNamed,
      },
    }, { str(" ") }, { { Symbol(1), Symbol(2) } }});

    SyntaxGrammar &syntax_grammar = get<0>(result);

    AssertThat(syntax_grammar.rules.size(), Equals<size_t>(2));
    AssertThat(syntax_grammar.expected_conflicts, Equals(set<set<Symbol>>({
      { Symbol(0), Symbol(1) },
    })));
  });

  describe("handling ubiquitous tokens", [&]() {
    it("adds inline ubiquitous tokens to the lexical grammar's separators", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        {
          "rule_A",
          str("x"),
          RuleEntryTypeNamed,
        },
      }, {
        pattern("\\s+"),
        str("y"),
      }, {}});

      AssertThat(get<2>(result), Equals<const GrammarError *>(nullptr));

      AssertThat(get<1>(result).separators.size(), Equals<size_t>(2));
      AssertThat(get<1>(result).separators[0], EqualsPointer(pattern("\\s+")));
      AssertThat(get<1>(result).separators[1], EqualsPointer(str("y")));

      AssertThat(get<0>(result).ubiquitous_tokens, IsEmpty());
    });

    it("updates ubiquitous symbols according to the new symbol numbers", [&]() {
      auto result = extract_tokens(InternedGrammar{ {
        {
          "rule_A",
          seq({ str("w"), str("x"), i_sym(1) }),
          RuleEntryTypeNamed
        },
        {
          "rule_B",
          str("y"),
          RuleEntryTypeNamed
        },
        {
          "rule_C",
          str("z"),
          RuleEntryTypeNamed
        },
      }, {
        i_sym(2),
      }, {}});

      AssertThat(get<2>(result), Equals<const GrammarError *>(nullptr));

      AssertThat(get<0>(result).ubiquitous_tokens, Equals(set<Symbol>({
        { Symbol(3, true) },
      })));

      AssertThat(get<1>(result).separators, IsEmpty());
    });

    it("returns an error if any ubiquitous tokens are non-token symbols", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        {
          "rule_A",
          seq({ str("x"), i_sym(1) }),
          RuleEntryTypeNamed,
        },
        {
          "rule_B",
          seq({ str("y"), str("z") }),
          RuleEntryTypeNamed,
        },
      }, { i_sym(1) }, {}});

      AssertThat(get<2>(result), !Equals<const GrammarError *>(nullptr));
      AssertThat(get<2>(result), EqualsPointer(
        new GrammarError(GrammarErrorTypeInvalidUbiquitousToken,
                         "Not a token: rule_B")));
    });

    it("returns an error if any ubiquitous tokens are non-token rules", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        {
          "rule_A",
          str("x"),
          RuleEntryTypeNamed,
        },
        {
          "rule_B",
          str("y"),
          RuleEntryTypeNamed,
        },
      }, { choice({ i_sym(1), blank() }) }, {}});

      AssertThat(get<2>(result), !Equals<const GrammarError *>(nullptr));
      AssertThat(get<2>(result), EqualsPointer(
        new GrammarError(GrammarErrorTypeInvalidUbiquitousToken,
                         "Not a token: (choice (sym 1) (blank))")));
    });
  });
});

END_TEST
