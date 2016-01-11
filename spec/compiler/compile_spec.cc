#include "compiler/compiler_spec_helper.h"
#include "compiler/compile.h"

using namespace rules;

START_TEST

describe("compile_grammar", []() {
  describe("when the grammar's start symbol is a token", [&]() {
    it("does not fail", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "the_grammar",
          "rules": {
            "rule1": {
              "type": "STRING",
              "value": "hello"
            }
          }
        }
      )JSON");

      AssertThat(string(result.error_message), IsEmpty());
      AssertThat(string(result.code), !IsEmpty());
    });
  });

  describe("when the grammar's start symbol is blank", [&]() {
    it("does not fail", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "the_grammar",
          "rules": {
            "rule1": {
              "type": "BLANK"
            }
          }
        }
      )JSON");

      AssertThat(string(result.error_message), IsEmpty());
      AssertThat(string(result.code), !IsEmpty());
    });
  });
});

END_TEST
