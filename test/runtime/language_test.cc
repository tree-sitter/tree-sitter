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
      })JSON", nullptr);

      TSParser *parser = ts_parser_new();
      const TSLanguage *language =  load_test_language("aliased_rules", compile_result);
      ts_parser_set_language(parser, language);
      TSTree *tree = ts_parser_parse_string(parser, nullptr, "b", 1);

      TSNode root_node = ts_tree_root_node(tree);
      char *string = ts_node_string(root_node);
      AssertThat(string, Equals("(a (c))"));

      TSNode aliased_node = ts_node_child(root_node, 0);
      AssertThat(ts_node_type(aliased_node), Equals("c"));

      TSSymbol aliased_symbol = ts_node_symbol(aliased_node);
      AssertThat(ts_language_symbol_count(language), IsGreaterThan(aliased_symbol));
      AssertThat(ts_language_symbol_name(language, aliased_symbol), Equals("c"));
      AssertThat(ts_language_symbol_type(language, aliased_symbol), Equals(TSSymbolTypeRegular));

      ts_free(string);
      ts_parser_delete(parser);
      ts_tree_delete(tree);
    });
  });
});

END_TEST
