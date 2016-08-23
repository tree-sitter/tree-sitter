#include "spec_helper.h"
#include "runtime/alloc.h"
#include "helpers/load_language.h"

START_TEST

describe("compile_grammar", []() {
  TSDocument *document;

  before_each([&]() {
    document = ts_document_make();
  });

  after_each([&]() {
    ts_document_free(document);
  });

  auto assert_root_node = [&](const string &expected_string) {
    TSNode root_node = ts_document_root_node(document);
    char *node_string = ts_node_string(root_node, document);
    AssertThat(node_string, Equals(expected_string));
    ts_free(node_string);
  };

  describe("when the grammar's start symbol is a token", [&]() {
    it("parses the token", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "test_language",
          "rules": {
            "first_rule": {"type": "STRING", "value": "the-value"}
          }
        }
      )JSON");

      ts_document_set_language(document, load_language("test_language", result));

      ts_document_set_input_string(document, "the-value");
      ts_document_parse(document);
      assert_root_node("(first_rule)");
    });
  });

  describe("when the grammar's start symbol is blank", [&]() {
    it("parses the empty string", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "test_language",
          "rules": {
            "first_rule": {"type": "BLANK"}
          }
        }
      )JSON");

      ts_document_set_language(document, load_language("test_language", result));

      ts_document_set_input_string(document, "");
      ts_document_parse(document);
      assert_root_node("(first_rule)");
    });
  });

  describe("when the grammar contains anonymous tokens with escaped characters", [&]() {
    it("escapes the escaped characters properly in the generated parser", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "test_language",
          "rules": {
            "first_rule": {
              "type": "CHOICE",
              "members": [
                {"type": "STRING", "value": "\n"},
                {"type": "STRING", "value": "\r"},
                {"type": "STRING", "value": "'hello'"},
                {"type": "PATTERN", "value": "\\d+"}
              ]
            }
          }
        }
      )JSON");

      ts_document_set_language(document, load_language("test_language", result));

      ts_document_set_input_string(document, "1234");
      ts_document_parse(document);
      assert_root_node("(first_rule)");

      ts_document_set_input_string(document, "\n");
      ts_document_parse(document);
      assert_root_node("(first_rule)");

      ts_document_set_input_string(document, "'hello'");
      ts_document_parse(document);
      assert_root_node("(first_rule)");
    });
  });

  describe("the 'aliases' field in the grammar", [&]() {
    it("can be used to make different rules take the same name", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "test_language",

          "aliases": {
            "second_rule": "first_rule",
            "third_rule": "first_rule"
          },

          "rules": {
            "start_rule": {
              "type": "SEQ",
              "members": [
                {"type": "SYMBOL", "name": "first_rule"},
                {"type": "SYMBOL", "name": "second_rule"},
                {"type": "SYMBOL", "name": "third_rule"}
              ]
            },

            "first_rule": { "type": "STRING", "value": "a" },
            "second_rule": { "type": "STRING", "value": "b" },
            "third_rule": { "type": "STRING", "value": "c" }
          }
        }
      )JSON");

      ts_document_set_language(document, load_language("test_language", result));
      ts_document_set_input_string(document, "abc");
      ts_document_parse(document);
      assert_root_node("(start_rule (first_rule) (first_rule) (first_rule))");
    });
  });

  describe("the grammar in the README", [&]() {
    it("works", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "arithmetic",

          // Things that can appear anywhere in the language, like comments
          // and whitespace, are expressed as 'extras'.
          "extras": [
            {"type": "PATTERN", "value": "\\s"},
            {"type": "SYMBOL", "name": "comment"}
          ],

          "rules": {

            // The first rule listed in the grammar becomes the 'start rule'.
            "expression": {
              "type": "CHOICE",
              "members": [
                {"type": "SYMBOL", "name": "sum"},
                {"type": "SYMBOL", "name": "product"},
                {"type": "SYMBOL", "name": "number"},
                {"type": "SYMBOL", "name": "variable"},
                {
                  "type": "SEQ",
                  "members": [
                    {"type": "STRING", "value": "("},

                    // Error recovery is controlled by wrapping rule subtrees
                    // in an 'ERROR' rule.
                    {
                      "type": "ERROR",
                      "content": {"type": "SYMBOL", "name": "expression"}
                    },

                    {"type": "STRING", "value": ")"}
                  ]
                }
              ]
            },

            // Tokens like '+' and '*' are described directly within the
            // grammar's rules, as opposed to in a seperate lexer description.
            "sum": {
              "type": "PREC_LEFT",
              "value": 1,
              "content": {
                "type": "SEQ",
                "members": [
                  {"type": "SYMBOL", "name": "expression"},
                  {"type": "STRING", "value": "+"},
                  {"type": "SYMBOL", "name": "expression"}
                ]
              }
            },

            // Ambiguities can be resolved at compile time by assigning precedence
            // values to rule subtrees.
            "product": {
              "type": "PREC_LEFT",
              "value": 2,
              "content": {
                "type": "SEQ",
                "members": [
                  {"type": "SYMBOL", "name": "expression"},
                  {"type": "STRING", "value": "*"},
                  {"type": "SYMBOL", "name": "expression"}
                ]
              }
            },

            // Tokens can be specified using ECMAScript regexps.
            "number": {"type": "PATTERN", "value": "\\d+"},
            "comment": {"type": "PATTERN", "value": "#.*"},
            "variable": {"type": "PATTERN", "value": "[a-zA-Z]\\w*"}
          }
        }
      )JSON");

      const TSLanguage *language = load_language("arithmetic", result);

      ts_document_set_language(document, language);
      ts_document_set_input_string(document, "a + b * c");
      ts_document_parse(document);

      assert_root_node(
        "(expression (sum "
          "(expression (variable)) "
          "(expression (product "
             "(expression (variable)) "
             "(expression (variable))))))");
    });
  });
});

END_TEST
