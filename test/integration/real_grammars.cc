#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/load_language.h"
#include "helpers/read_test_entries.h"
#include "helpers/spy_input.h"
#include "helpers/stderr_logger.h"
#include "helpers/point_helpers.h"
#include "helpers/record_alloc.h"
#include "helpers/random_helpers.h"
#include "helpers/scope_sequence.h"
#include "helpers/tree_helpers.h"
#include <set>

START_TEST

if (TREE_SITTER_SEED == -1) return;

vector<string> test_languages({
  "javascript",
  "json",
  "html",
  "c",
  "cpp",
  "python",
  "bash",
});

for (auto &language_name : test_languages) {
  describe(("the " + language_name + " language").c_str(), [&]() {
    TSParser *parser;
    const bool debug_graphs_enabled = getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS");

    before_each([&]() {
      record_alloc::start();
      parser = ts_parser_new();
      ts_parser_set_language(parser, load_real_language(language_name));

      // ts_parser_set_logger(parser, stderr_logger_new(true));
      if (debug_graphs_enabled) {
        ts_parser_print_dot_graphs(parser, stderr);
      }
    });

    after_each([&]() {
      ts_parser_delete(parser);
      AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
    });

    for (auto &entry : read_real_language_corpus(language_name)) {
      SpyInput *input;

      it(("parses " + entry.description + ": initial parse").c_str(), [&]() {
        input = new SpyInput(entry.input, 4);
        if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

        TSTree *tree = ts_parser_parse(parser, nullptr, input->input());
        assert_consistent_tree_sizes(tree, input->content);

        TSNode root_node = ts_tree_root_node(tree);
        const char *node_string = ts_node_string(root_node);
        string result(node_string);
        ts_free((void *)node_string);
        AssertThat(result, Equals(entry.tree_string));

        ts_tree_delete(tree);
        delete input;
      });

      set<pair<size_t, size_t>> deletions;
      set<pair<size_t, string>> insertions;

      for (size_t i = 0; i < 60; i++) {
        size_t edit_position = default_generator(entry.input.size());
        size_t deletion_size = default_generator(entry.input.size() - edit_position);
        string inserted_text = default_generator.words(default_generator(4) + 1);

        if (insertions.insert({edit_position, inserted_text}).second) {
          it(("parses " + entry.description +
              ": repairing an insertion of \"" + inserted_text + "\"" +
              " at " + to_string(edit_position)).c_str(), [&]() {
            input = new SpyInput(entry.input, 3);
            if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

            input->replace(edit_position, 0, inserted_text);
            TSTree *tree = ts_parser_parse(parser, nullptr, input->input());
            assert_consistent_tree_sizes(tree, input->content);
            if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

            TSInputEdit edit = input->undo();
            ts_tree_edit(tree, &edit);
            assert_consistent_tree_sizes(tree, input->content);
            if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

            TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
            assert_consistent_tree_sizes(new_tree, input->content);

            uint32_t range_count;
            TSRange *ranges = ts_tree_get_changed_ranges(tree, new_tree, &range_count);

            ScopeSequence old_scope_sequence = build_scope_sequence(tree, input->content);
            ScopeSequence new_scope_sequence = build_scope_sequence(new_tree, input->content);
            verify_changed_ranges(
              old_scope_sequence, new_scope_sequence,
              input->content, ranges, range_count
            );
            ts_free(ranges);

            TSNode root_node = ts_tree_root_node(new_tree);
            const char *node_string = ts_node_string(root_node);
            string result(node_string);
            ts_free((void *)node_string);
            AssertThat(result, Equals(entry.tree_string));

            ts_tree_delete(tree);
            ts_tree_delete(new_tree);
            delete input;
          });
        }

        if (deletions.insert({edit_position, deletion_size}).second) {
          it(("parses " + entry.description +
              ": repairing a deletion of " +
              to_string(edit_position) + "-" + to_string(edit_position + deletion_size)).c_str(), [&]() {
            input = new SpyInput(entry.input, 3);
            if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

            input->replace(edit_position, deletion_size, "");
            TSTree *tree = ts_parser_parse(parser, nullptr, input->input());
            assert_consistent_tree_sizes(tree, input->content);
            if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

            TSInputEdit edit = input->undo();
            ts_tree_edit(tree, &edit);
            assert_consistent_tree_sizes(tree, input->content);
            if (debug_graphs_enabled) printf("%s\n\n", input->content.c_str());

            TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
            assert_consistent_tree_sizes(new_tree, input->content);

            uint32_t range_count;
            TSRange *ranges = ts_tree_get_changed_ranges(tree, new_tree, &range_count);

            ScopeSequence old_scope_sequence = build_scope_sequence(tree, input->content);
            ScopeSequence new_scope_sequence = build_scope_sequence(new_tree, input->content);
            verify_changed_ranges(
              old_scope_sequence, new_scope_sequence,
              input->content, ranges, range_count
            );
            ts_free(ranges);

            TSNode root_node = ts_tree_root_node(new_tree);
            const char *node_string = ts_node_string(root_node);
            string result(node_string);
            ts_free((void *)node_string);
            AssertThat(result, Equals(entry.tree_string));

            ts_tree_delete(tree);
            ts_tree_delete(new_tree);
            delete input;
          });
        }
      }
    }
  });
}

END_TEST
