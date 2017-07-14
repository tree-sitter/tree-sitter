#include "test_helper.h"
#include "helpers/read_test_entries.h"
#include "helpers/load_language.h"
#include "helpers/stderr_logger.h"
#include "helpers/file_helpers.h"
#include "helpers/tree_helpers.h"
#include "runtime/alloc.h"

START_TEST

string grammars_dir_path = "test/fixtures/test_grammars";
vector<string> test_languages = list_directory(grammars_dir_path);

for (auto &language_name : test_languages) {
  if (language_name == "readme.md") continue;

  describe(("test grammar: " + language_name).c_str(), [&]() {
    string directory_path = grammars_dir_path + "/" + language_name;
    string grammar_path = directory_path + "/grammar.json";
    string grammar_json = read_file(grammar_path);
    string expected_error_path = directory_path + "/expected_error.txt";
    const TSLanguage *language = nullptr;

    if (file_exists(expected_error_path)) {
      it("fails with the correct error message", [&]() {
        TSCompileResult compile_result = ts_compile_grammar(grammar_json.c_str());
        string expected_error = read_file(expected_error_path);
        AssertThat((void *)compile_result.error_message, !IsNull());
        AssertThat(compile_result.error_message, Equals(expected_error));
      });
      return;
    }

    for (auto &entry : read_test_language_corpus(language_name)) {
      it(("parses " + entry.description).c_str(), [&]() {
        if (!language) {
          string external_scanner_path = directory_path + "/scanner.c";
          if (!file_exists(external_scanner_path)) external_scanner_path = "";

          TSCompileResult compile_result = ts_compile_grammar(grammar_json.c_str());

          language = load_test_language(
            language_name,
            compile_result,
            external_scanner_path
          );
        }

        TSDocument *document = ts_document_new();
        ts_document_set_language(document, language);
        ts_document_set_input_string_with_length(document, entry.input.c_str(), entry.input.size());

        // ts_document_set_logger(document, stderr_logger_new(true));
        // ts_document_print_debugging_graphs(document, true);
        ts_document_parse(document);

        TSNode root_node = ts_document_root_node(document);
        assert_consistent_tree_sizes(root_node);
        const char *node_string = ts_node_string(root_node, document);
        string result(node_string);
        ts_free((void *)node_string);
        ts_document_free(document);

        AssertThat(result, Equals(entry.tree_string));
      });
    }
  });
}

END_TEST
