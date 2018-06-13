#include "test_helper.h"
#include "helpers/read_test_entries.h"
#include "helpers/load_language.h"
#include "helpers/stderr_logger.h"
#include "helpers/file_helpers.h"
#include "helpers/tree_helpers.h"
#include "runtime/alloc.h"
#include "helpers/record_alloc.h"

START_TEST

if (TREE_SITTER_SEED == -1) return;

string grammars_dir_path = join_path({"test", "fixtures", "test_grammars"});
vector<string> test_languages = list_directory(grammars_dir_path);

for (auto &language_name : test_languages) {
  if (language_name == "readme.md") continue;

  describe(("test grammar: " + language_name).c_str(), [&]() {
    string directory_path = join_path({grammars_dir_path, language_name});
    string grammar_path = join_path({directory_path, "grammar.json"});
    string expected_error_path = join_path({directory_path, "expected_error.txt"});

    string grammar_json = read_file(grammar_path);
    const TSLanguage *language = nullptr;

    if (file_exists(expected_error_path)) {
      it("fails with the correct error message", [&]() {
        TSCompileResult compile_result = ts_compile_grammar(grammar_json.c_str(), nullptr);
        string expected_error = read_file(expected_error_path);
        AssertThat((void *)compile_result.error_message, !Equals<void *>(nullptr));
        AssertThat(compile_result.error_message, Equals(expected_error));
      });
      return;
    }

    for (auto &entry : read_test_language_corpus(language_name)) {
      it(("parses " + entry.description).c_str(), [&]() {
        record_alloc::start();

        if (!language) {
          string external_scanner_path = join_path({directory_path, "scanner.c"});
          if (!file_exists(external_scanner_path)) external_scanner_path = "";

          TSCompileResult compile_result = ts_compile_grammar(grammar_json.c_str(), nullptr);

          language = load_test_language(
            language_name,
            compile_result,
            external_scanner_path
          );
        }

        TSParser *parser = ts_parser_new();
        ts_parser_set_language(parser, language);

        if (getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS")) {
          ts_parser_print_dot_graphs(parser, stderr);
        }

        TSTree *tree = ts_parser_parse_string(parser, nullptr, entry.input.c_str(), entry.input.size());

        TSNode root_node = ts_tree_root_node(tree);
        AssertThat(ts_node_end_byte(root_node), Equals(entry.input.size()));
        assert_consistent_tree_sizes(root_node);

        const char *node_string = ts_node_string(root_node);
        string result(node_string);
        ts_free((void *)node_string);
        AssertThat(result, Equals(entry.tree_string));

        ts_tree_delete(tree);
        ts_parser_delete(parser);
        AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
      });
    }
  });
}

END_TEST
