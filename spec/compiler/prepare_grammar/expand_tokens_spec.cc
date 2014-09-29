#include "compiler/compiler_spec_helper.h"
#include "compiler/prepared_grammar.h"
#include "compiler/helpers/containers.h"
#include "compiler/prepare_grammar/expand_tokens.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_tokens;

describe("expand_tokens", []() {
  describe("string rules", [&]() {
    it("replaces strings with sequences of character sets", [&]() {
      LexicalGrammar grammar({
          { "rule_A", seq({
              i_sym(10),
              str("xyz"),
              i_sym(11) }) },
      }, {});

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals((const GrammarError *)nullptr));
      AssertThat(result.first.rules, Equals(rule_list({
          { "rule_A", seq({
              i_sym(10),
              seq({ character({ 'x' }), character({ 'y' }), character({ 'z' }) }),
              i_sym(11) }) },
      })));
    });

    it("handles strings containing non-ASCII UTF8 characters", [&]() {
      LexicalGrammar grammar({
          // α β
          { "rule_A", str("\u03B1 \u03B2") },
      }, {});

      auto result = expand_tokens(grammar);

      AssertThat(result.first.rules, Equals(rule_list({
          { "rule_A", seq({
              character({ 945 }),
              character({ ' ' }),
              character({ 946 }) }) }
      })));
    });
  });

  describe("regexp rules", [&]() {
    it("replaces regexps with the equivalent rule tree", [&]() {
      LexicalGrammar grammar({
          { "rule_A", seq({
              i_sym(10),
              pattern("x*"),
              i_sym(11) }) },
      }, {});

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals((const GrammarError *)nullptr));
      AssertThat(result.first.rules, Equals(rule_list({
          { "rule_A", seq({
              i_sym(10),
              repeat(character({ 'x' })),
              i_sym(11) }) },
      })));
    });

    it("handles regexps containing non-ASCII UTF8 characters", [&]() {
      LexicalGrammar grammar({
          // [^α-δ]
          { "rule_A", pattern("[^\u03B1-\u03B4]*") },
      }, {});

      auto result = expand_tokens(grammar);

      AssertThat(result.first.rules, Equals(rule_list({
          { "rule_A", repeat(character({ 945, 946, 947, 948 }, false)) }
      })));
    });

    it("returns an error when the grammar contains an invalid regex", [&]() {
      LexicalGrammar grammar({
          { "rule_A", seq({
              pattern("("),
              str("xyz"),
              pattern("[") }) },
      }, {});

      auto result = expand_tokens(grammar);

      AssertThat(result.second, EqualsPointer(new GrammarError(GrammarErrorTypeRegex, "unmatched open paren")));
    });
  });
});

END_TEST
