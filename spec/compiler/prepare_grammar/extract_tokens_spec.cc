#include "compiler/compiler_spec_helper.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::extract_tokens;
using prepare_grammar::InternedGrammar;

describe("extract_tokens", []() {
  it("moves string rules into the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      { "rule_A", seq({ str("ab"), i_sym(0) }) }
    }, {}, {}});

    AssertThat(get<0>(result).rules, Equals(rule_list({
      { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
    })));
    AssertThat(get<0>(result).aux_rules, IsEmpty())

    AssertThat(get<1>(result).rules, IsEmpty())
    AssertThat(get<1>(result).aux_rules, Equals(rule_list({
      { "'ab'", str("ab") },
    })));
  });

  it("moves pattern rules into the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      { "rule_A", seq({ pattern("a+"), i_sym(0) }) }
    }, {}, {}});

    AssertThat(get<0>(result).rules, Equals(rule_list({
      { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
    })));
    AssertThat(get<0>(result).aux_rules, IsEmpty())

    AssertThat(get<1>(result).rules, IsEmpty())
    AssertThat(get<1>(result).aux_rules, Equals(rule_list({
      { "/a+/", pattern("a+") },
    })));
  });

  it("moves other rules marked as tokens into the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      { "rule_A", seq({
        token(seq({ pattern("."), choice({ str("a"), str("b") }) })),
        i_sym(0) }) }
    }, {}, {}});

    AssertThat(get<0>(result).rules, Equals(rule_list({
      { "rule_A", seq({ i_aux_token(0), i_sym(0) }) }
    })));
    AssertThat(get<0>(result).aux_rules, IsEmpty())

    AssertThat(get<1>(result).rules, IsEmpty())
    AssertThat(get<1>(result).aux_rules, Equals(rule_list({
      { "(seq /./ (choice 'a' 'b'))", token(seq({ pattern("."), choice({ str("a"), str("b") }) })) },
    })));
  });

  it("does not move blank rules", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      { "rule_A", choice({ i_sym(0), blank() }) },
    }, {}, {}});

    AssertThat(get<0>(result).rules, Equals(rule_list({
      { "rule_A", choice({ i_sym(0), blank() }) },
    })));
    AssertThat(get<0>(result).aux_rules, IsEmpty())

    AssertThat(get<1>(result).rules, IsEmpty())
    AssertThat(get<1>(result).aux_rules, IsEmpty())
  });

  it("does not create duplicate tokens in the lexical grammar", [&]() {
    auto result = extract_tokens(InternedGrammar{{
      { "rule_A", seq({ str("ab"), i_sym(0), str("ab") }) },
    }, {}, {}});

    AssertThat(get<0>(result).rules, Equals(rule_list({
        { "rule_A", seq({ i_aux_token(0), i_sym(0), i_aux_token(0) }) }
    })));
    AssertThat(get<0>(result).aux_rules, IsEmpty())

    AssertThat(get<1>(result).rules, IsEmpty())
    AssertThat(get<1>(result).aux_rules, Equals(rule_list({
        { "'ab'", str("ab") },
    })))
  });

  it("updates the grammar's expected conflict symbols", [&]() {
    auto result = extract_tokens(InternedGrammar{
      {
        { "rule_A", str("ok") },
        { "rule_B", repeat(i_sym(0)) },
        { "rule_C", repeat(seq({ i_sym(0), i_sym(0) })) },
      },
      { str(" ") },
      { { Symbol(1), Symbol(2) } }
    });

    AssertThat(get<0>(result).rules.size(), Equals<size_t>(2));
    AssertThat(get<1>(result).rules.size(), Equals<size_t>(1));
    AssertThat(get<0>(result).expected_conflicts, Equals(set<set<Symbol>>({
      { Symbol(0), Symbol(1) },
    })));
  });

  describe("when an entire rule can be extracted", [&]() {
    it("moves the rule the lexical grammar when possible and updates referencing symbols", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        { "rule_A", i_sym(1) },
        { "rule_B", pattern("a|b") },
        { "rule_C", token(seq({ str("a"), str("b") })) },
      }, {}, {}});

      AssertThat(get<0>(result).rules, Equals(rule_list({
        { "rule_A", i_token(0) }
      })));
      AssertThat(get<0>(result).aux_rules, IsEmpty());

      AssertThat(get<1>(result).rules, Equals(rule_list({
        { "rule_B", pattern("a|b") },
        { "rule_C", token(seq({ str("a"), str("b") })) },
      })));
      AssertThat(get<1>(result).aux_rules, IsEmpty());
    });

    it("updates symbols whose indices need to change due to deleted rules", [&]() {
      auto result = extract_tokens(InternedGrammar{{
        { "rule_A", str("ab") },
        { "rule_B", i_sym(0) },
        { "rule_C", i_sym(1) },
      }, {}, {}});

      AssertThat(get<0>(result).rules, Equals(rule_list({
        { "rule_B", i_token(0) },
        { "rule_C", i_sym(0) },
      })));
      AssertThat(get<0>(result).aux_rules, IsEmpty());

      AssertThat(get<1>(result).rules, Equals(rule_list({
        { "rule_A", str("ab") },
      })));
      AssertThat(get<1>(result).aux_rules, IsEmpty());
    });
  });

  describe("handling ubiquitous tokens", [&]() {
    describe("ubiquitous tokens that are not symbols", [&]() {
      it("adds them to the lexical grammar's separators", [&]() {
        auto result = extract_tokens(InternedGrammar{{
          { "rule_A", str("x") },
        }, {
          pattern("\\s+"),
          str("y"),
        }, {}});

        AssertThat(get<2>(result), Equals<const GrammarError *>(nullptr));

        AssertThat(get<1>(result).separators, Equals(rule_vector({
          pattern("\\s+"),
          str("y"),
        })));

        AssertThat(get<0>(result).ubiquitous_tokens, IsEmpty());
      });
    });

    describe("ubiquitous tokens that point to moved rules", [&]() {
      it("updates them according to the new symbol numbers", [&]() {
        auto result = extract_tokens(InternedGrammar{ {
          { "rule_A", seq({ str("w"), i_sym(1) }) },
          { "rule_B", str("x") },
          { "rule_C", str("y") },
        }, {
          i_sym(2),
        }, {}});

        AssertThat(get<2>(result), Equals<const GrammarError *>(nullptr));

        AssertThat(get<0>(result).ubiquitous_tokens, Equals(set<Symbol>({
          { Symbol(1, SymbolOptionToken) },
        })));

        AssertThat(get<1>(result).separators, IsEmpty());
      });
    });

    describe("ubiquitous tokens that are visible", [&]() {
      it("preserves them in the syntactic grammar", [&]() {
        auto result = extract_tokens(InternedGrammar{{
          { "rule_A", str("ab") },
          { "rule_B", str("bc") },
        }, { i_sym(1) }, {}});

        AssertThat(get<2>(result), Equals<const GrammarError *>(nullptr));

        AssertThat(get<0>(result).ubiquitous_tokens, Equals(set<Symbol>({
            Symbol(1, SymbolOptionToken)
        })));

        AssertThat(get<1>(result).separators, IsEmpty());
      });
    });

    describe("ubiquitous tokens that are used in other grammar rules", [&]() {
      it("preserves them in the syntactic grammar", [&]() {
        auto result = extract_tokens(InternedGrammar{{
          { "rule_A", seq({ i_sym(1), str("ab") }) },
          { "_rule_B", str("bc") },
        }, { i_sym(1) }, {}});

        AssertThat(get<2>(result), Equals<const GrammarError *>(nullptr));

        AssertThat(get<0>(result).ubiquitous_tokens, Equals(set<Symbol>({
          Symbol(0, SymbolOptionToken),
        })));

        AssertThat(get<1>(result).separators, IsEmpty());
      });
    });

    describe("ubiquitous tokens that are non-token symbols", [&]() {
      it("returns an error", [&]() {
        auto result = extract_tokens(InternedGrammar{{
          { "rule_A", seq({ str("x"), i_sym(1) }), },
          { "rule_B", seq({ str("y"), str("z") }) },
        }, { i_sym(1) }, {}});

        AssertThat(get<2>(result), !Equals<const GrammarError *>(nullptr));
        AssertThat(get<2>(result), EqualsPointer(
          new GrammarError(GrammarErrorTypeInvalidUbiquitousToken,
                           "Not a token: rule_B")));
      });
    });

    describe("ubiquitous tokens that are not symbols", [&]() {
      it("returns an error", [&]() {
        auto result = extract_tokens(InternedGrammar{{
          { "rule_A", str("x") },
          { "rule_B", str("y") },
        }, { choice({ i_sym(1), blank() }) }, {}});

        AssertThat(get<2>(result), !Equals<const GrammarError *>(nullptr));
        AssertThat(get<2>(result), EqualsPointer(
          new GrammarError(GrammarErrorTypeInvalidUbiquitousToken,
                           "Not a token: (choice (sym 1) (blank))")));
      });
    });
  });
});

END_TEST
