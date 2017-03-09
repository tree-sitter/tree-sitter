#include "spec_helper.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/expand_tokens.h"
#include "helpers/rule_helpers.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_tokens;

describe("expand_tokens", []() {
  MetadataParams string_token_params;
  string_token_params.is_string = true;
  string_token_params.is_token = true;

  describe("string rules", [&]() {
    it("replaces strings with sequences of character sets", [&]() {
      LexicalGrammar grammar{
        {
          LexicalVariable{
            "rule_A",
            VariableTypeNamed,
            seq({
              i_sym(10),
              str("xyz"),
              i_sym(11),
            }),
            false
          }
        },
        {}
      };

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals(CompileError::none()));
      AssertThat(result.first.variables, Equals(vector<LexicalVariable>{
        LexicalVariable{
          "rule_A",
          VariableTypeNamed,
          seq({
            i_sym(10),
            metadata(seq({
              character({ 'x' }),
              character({ 'y' }),
              character({ 'z' }),
            }), string_token_params),
            i_sym(11),
          }),
          false
        }
      }));
    });

    it("handles strings containing non-ASCII UTF8 characters", [&]() {
      LexicalGrammar grammar{
        {
          LexicalVariable{
            "rule_A",
            VariableTypeNamed,
            str("\u03B1 \u03B2"),
            false
          },
        },
        {}
      };

      auto result = expand_tokens(grammar);

      AssertThat(result.first.variables, Equals(vector<LexicalVariable>{
        LexicalVariable{
          "rule_A",
          VariableTypeNamed,
          metadata(seq({
            character({ 945 }),
            character({ ' ' }),
            character({ 946 }),
          }), string_token_params),
          false
        }
      }));
    });
  });

  describe("regexp rules", [&]() {
    it("replaces regexps with the equivalent rule tree", [&]() {
      LexicalGrammar grammar{
        {
          LexicalVariable{
            "rule_A",
            VariableTypeNamed,
            seq({
              i_sym(10),
              pattern("x*"),
              i_sym(11),
            }),
            false
          }
        },
        {}
      };

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals(CompileError::none()));
      AssertThat(result.first.variables, Equals(vector<LexicalVariable>{
        LexicalVariable{
          "rule_A",
          VariableTypeNamed,
          seq({
            i_sym(10),
            repeat(character({ 'x' })),
            i_sym(11),
          }),
          false
        }
      }));
    });

    it("handles regexps containing non-ASCII UTF8 characters", [&]() {
      LexicalGrammar grammar{
        {
          LexicalVariable{
            "rule_A",
            VariableTypeNamed,
            pattern("[^\u03B1-\u03B4]*"),
            false
          }
        },
        {}
      };

      auto result = expand_tokens(grammar);

      AssertThat(result.first.variables, Equals(vector<LexicalVariable>{
        LexicalVariable{
          "rule_A",
          VariableTypeNamed,
          repeat(character({ 945, 946, 947, 948 }, false)),
          false
        }
      }));
    });

    it("returns an error when the grammar contains an invalid regex", [&]() {
      LexicalGrammar grammar{
        {
          LexicalVariable{
            "rule_A",
            VariableTypeNamed,
            seq({
              pattern("("),
              str("xyz"),
              pattern("["),
            }),
            false
          },
        },
        {}
      };

      auto result = expand_tokens(grammar);

      AssertThat(result.second, Equals(CompileError(TSCompileErrorTypeInvalidRegex, "unmatched open paren")));
    });
  });
});

END_TEST
