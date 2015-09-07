#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/expand_tokens.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_tokens;

describe("expand_tokens", []() {
  describe("string rules", [&]() {
    it("replaces strings with sequences of character sets", [&]() {
      LexicalGrammar grammar{{
        {
          "rule_A",
          seq({
            i_sym(10),
            str("xyz"),
            i_sym(11),
          }),
          RuleEntryTypeNamed
        },
      }, {}};

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals((const GrammarError *)nullptr));
      AssertThat(result.first.rules, Equals(vector<RuleEntry>({
        {
          "rule_A",
          seq({
            i_sym(10),
            metadata(seq({
              character({ 'x' }),
              character({ 'y' }),
              character({ 'z' }),
            }), {
              {PRECEDENCE, 1},
              {IS_TOKEN, 1},
            }),
            i_sym(11),
          }),
          RuleEntryTypeNamed
        },
      })));
    });

    it("handles strings containing non-ASCII UTF8 characters", [&]() {
      LexicalGrammar grammar{{
        {
          "rule_A",
          str("\u03B1 \u03B2"), // α β
          RuleEntryTypeNamed
        },
      }, {}};

      auto result = expand_tokens(grammar);

      AssertThat(result.first.rules, Equals(vector<RuleEntry>({
        {
          "rule_A",
          metadata(seq({
            character({ 945 }),
            character({ ' ' }),
            character({ 946 }),
          }), {
            {PRECEDENCE, 1},
            {IS_TOKEN, 1},
          }),
          RuleEntryTypeNamed
        }
      })));
    });
  });

  describe("regexp rules", [&]() {
    it("replaces regexps with the equivalent rule tree", [&]() {
      LexicalGrammar grammar{{
        {
          "rule_A",
          seq({
            i_sym(10),
            pattern("x*"),
            i_sym(11),
          }),
          RuleEntryTypeNamed
        },
      }, {}};

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals((const GrammarError *)nullptr));
      AssertThat(result.first.rules, Equals(vector<RuleEntry>({
        {
          "rule_A",
          seq({
            i_sym(10),
            repeat(character({ 'x' })),
            i_sym(11),
          }),
          RuleEntryTypeNamed
        },
      })));
    });

    it("handles regexps containing non-ASCII UTF8 characters", [&]() {
      LexicalGrammar grammar{{
        {
          "rule_A",
          pattern("[^\u03B1-\u03B4]*"), // [^α-δ]
          RuleEntryTypeNamed
        },
      }, {}};

      auto result = expand_tokens(grammar);

      AssertThat(result.first.rules, Equals(vector<RuleEntry>({
        {
          "rule_A",
          repeat(character({ 945, 946, 947, 948 }, false)),
          RuleEntryTypeNamed
        }
      })));
    });

    it("returns an error when the grammar contains an invalid regex", [&]() {
      LexicalGrammar grammar{{
        {
          "rule_A",
          seq({
            pattern("("),
            str("xyz"),
            pattern("["),
          }),
          RuleEntryTypeNamed
        },
      }, {}};

      auto result = expand_tokens(grammar);

      AssertThat(result.second, EqualsPointer(new GrammarError(GrammarErrorTypeRegex, "unmatched open paren")));
    });
  });
});

END_TEST
