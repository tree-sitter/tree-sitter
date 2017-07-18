#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/load_language.h"

START_TEST

describe("Language", []() {
  describe("symbol_name(TSSymbol symbol)", [&]() {
    it("returns the correct name for renamed nodes", [&]() {
      TSCompileResult compile_result = ts_compile_grammar(R"JSON({
        "name": "renamed_rules",

        "rules": {
          "a": {
            "type": "RENAME",
            "value": "c",
            "content": {
              "type": "SYMBOL",
              "name": "b"
            }
          },

          "b": {
            "type": "STRING",
            "value": "b"
          }
        }
      })JSON");

      TSDocument *document = ts_document_new();
      const TSLanguage *language =  load_test_language("renamed_rules", compile_result);
      ts_document_set_language(document, language);
      ts_document_set_input_string(document, "b");
      ts_document_parse(document);

      TSNode root_node = ts_document_root_node(document);
      char *string = ts_node_string(root_node, document);
      AssertThat(string, Equals("(a (c))"));

      TSNode renamed_node = ts_node_child(root_node, 0);
      AssertThat(ts_node_type(renamed_node, document), Equals("c"));

      TSSymbol renamed_symbol = ts_node_symbol(renamed_node);
      AssertThat(ts_language_symbol_count(language), IsGreaterThan(renamed_symbol));
      AssertThat(ts_language_symbol_name(language, renamed_symbol), Equals("c"));
      AssertThat(ts_language_symbol_type(language, renamed_symbol), Equals(TSSymbolTypeRegular));

      ts_free(string);
      ts_document_free(document);
    });
  });
});

END_TEST
