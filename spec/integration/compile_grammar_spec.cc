#include "integration/integration_spec_helper.h"
#include "integration/helpers/load_language.h"

START_TEST

describe("compile_grammar", []() {
  TSDocument *document;

  before_each([&]() {
    document = ts_document_make();
  });

  after_each([&]() {
    ts_document_free(document);
  });

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
      TSNode root_node = ts_document_root_node(document);
      AssertThat(ts_node_string(root_node, document), Equals("(first_rule)"));
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
      TSNode root_node = ts_document_root_node(document);
      AssertThat(ts_node_string(root_node, document), Equals("(first_rule)"));
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
      TSNode root_node = ts_document_root_node(document);
      AssertThat(ts_node_string(root_node, document), Equals("(first_rule)"));

      ts_document_set_input_string(document, "\n");
      ts_document_parse(document);
      root_node = ts_document_root_node(document);
      AssertThat(ts_node_string(root_node, document), Equals("(first_rule)"));

      ts_document_set_input_string(document, "'hello'");
      ts_document_parse(document);
      root_node = ts_document_root_node(document);
      AssertThat(ts_node_string(root_node, document), Equals("(first_rule)"));
    });
  });

  describe("the grammar in the README", [&]() {
    it("works", [&]() {
      TSCompileResult result = ts_compile_grammar(R"JSON(
        {
          "name": "arithmetic",

          "extras": [
            {"type": "PATTERN", "value": "\\s"}
          ],

          "rules": {
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
                    {"type": "SYMBOL", "name": "expression"},
                    {"type": "STRING", "value": ")"}
                  ]
                }
              ]
            },

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

            "number": {"type": "PATTERN", "value": "\\d+"},
            "variable": {"type": "PATTERN", "value": "[a-zA-Z]\\w*"}
          }
        }
      )JSON");

      const TSLanguage *language = load_language("arithmetic", result);

      ts_document_set_language(document, language);
      ts_document_set_input_string(document, "a + b * c");
      ts_document_parse(document);

      TSNode root_node = ts_document_root_node(document);
      AssertThat(ts_node_string(root_node, document), Equals(
        "(expression (sum "
          "(expression (variable)) "
          "(expression (product "
             "(expression (variable)) "
             "(expression (variable))))))"));
    });
  });
});

END_TEST
