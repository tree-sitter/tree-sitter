#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/load_language.h"

START_TEST

describe("Language", []() {
  describe("symbol_name(TSSymbol symbol)", [&]() {
    it("returns the correct name for aliased nodes", [&]() {
      TSCompileResult compile_result = ts_compile_grammar(R"JSON({
        "name": "aliased_rules",

        "rules": {
          "a": {
            "type": "ALIAS",
            "value": "c",
            "named": true,
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
      const TSLanguage *language =  load_test_language("aliased_rules", compile_result);
      ts_document_set_language(document, language);
      ts_document_set_input_string(document, "b");
      ts_document_parse(document);

      TSNode root_node = ts_document_root_node(document);
      char *string = ts_node_string(root_node, document);
      AssertThat(string, Equals("(a (c))"));

      TSNode aliased_node = ts_node_child(root_node, 0);
      AssertThat(ts_node_type(aliased_node, document), Equals("c"));

      TSSymbol aliased_symbol = ts_node_symbol(aliased_node);
      AssertThat(ts_language_symbol_count(language), IsGreaterThan(aliased_symbol));
      AssertThat(ts_language_symbol_name(language, aliased_symbol), Equals("c"));
      AssertThat(ts_language_symbol_type(language, aliased_symbol), Equals(TSSymbolTypeRegular));

      ts_free(string);
      ts_document_free(document);
    });
  });
});

END_TEST
