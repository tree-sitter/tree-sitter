#include "test_helper.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/expand_tokens.h"
#include "helpers/stream_methods.h"

START_TEST

using namespace rules;
using prepare_grammar::expand_token;
using prepare_grammar::ExpandTokenResult;

describe("expand_tokens", []() {
  MetadataParams string_token_params;
  string_token_params.is_string = true;
  string_token_params.is_token = true;

  describe("string rules", [&]() {
    it("replaces strings with sequences of character sets", [&]() {
      AssertThat(
        expand_token(Rule::seq({
          String{"a"},
          String{"bcd"},
          String{"e"}
        })).rule,
        Equals(Rule::seq({
          CharacterSet{{ 'a' }},
          Rule::seq({
            CharacterSet{{ 'b' }},
            CharacterSet{{ 'c' }},
            CharacterSet{{ 'd' }},
          }),
          CharacterSet{{ 'e' }},
        })));
    });

    it("handles strings containing non-ASCII UTF8 characters", [&]() {
      AssertThat(
        expand_token(String{"\u03B1 \u03B2"}).rule,
        Equals(Rule::seq({
          CharacterSet{{ 945 }},
          CharacterSet{{ ' ' }},
          CharacterSet{{ 946 }},
        }))
      );
    });
  });

  describe("regexp rules", [&]() {
    it("replaces regexps with the equivalent rule tree", [&]() {
      AssertThat(
        expand_token(Rule::seq({
          String{"a"},
          Pattern{"x+"},
          String{"b"},
        })).rule,
        Equals(Rule::seq({
          CharacterSet{{'a'}},
          Repeat{CharacterSet{{ 'x' }}},
          CharacterSet{{'b'}},
        }))
      );
    });

    it("handles regexps containing non-ASCII UTF8 characters", [&]() {
      AssertThat(
        expand_token(Pattern{"[^\u03B1-\u03B4]+"}).rule,
        Equals(Rule(Repeat{
          CharacterSet().include_all().exclude(945, 948)
        }))
      );
    });

    it("returns an error when the grammar contains an invalid regex", [&]() {
      AssertThat(
        expand_token(Rule::seq({
          Pattern{"("},
          String{"xyz"},
          Pattern{"["},
        })).error,
        Equals(CompileError(
          TSCompileErrorTypeInvalidRegex,
          "unmatched open paren"
        ))
      );
    });
  });
});

END_TEST
