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

TSInputEdit do_random_edit(Generator &random, SpyInput &input, TSTree *tree) {
  size_t choice = random(10);

  if (choice < 2) {
    // Insert text at end
    string inserted_text = random.words(1);
    return input.replace(input.content.size(), 0, inserted_text);
  } else if (choice < 5) {
    // Delete text from end
    size_t deletion_size = random(10);
    if (deletion_size > input.content.size()) deletion_size = input.content.size();
    return input.replace(input.content.size() - deletion_size, deletion_size, "");
  } else if (choice < 8) {
    // Insert at random position
    size_t position = random(input.content.size() + 1);
    string inserted_text = random.words(1 + random(3));
    return input.replace(position, 0, inserted_text);
  } else {
    // Replace at random position
    size_t position = random(input.content.size() + 1);
    size_t deletion_size = random(input.content.size() + 1 - position);
    string inserted_text = random.words(1 + random(4));
    return input.replace(position, deletion_size, inserted_text);
  }
}

START_TEST;

if (TREE_SITTER_SEED == -1) return;

vector<string> test_languages({
  "embedded-template",
  "javascript",
  "json",
  "html",
  "c",
  "cpp",
  "python",
  "bash",
});

for (auto &language_name : test_languages) {
  describe("the " + language_name + " language", [&]() {
    TSParser *parser;
    const bool debug_graphs_enabled = getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS");
    Generator random(0);

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
      it("parses " + entry.description + ": initial parse", [&]() {
        SpyInput input(entry.input, 4);
        if (debug_graphs_enabled) printf("%s\n\n", input.content.c_str());

        TSTree *tree = ts_parser_parse(parser, nullptr, input.input());
        assert_consistent_tree_sizes(tree, input.content);

        TSNode root_node = ts_tree_root_node(tree);
        const char *node_string = ts_node_string(root_node);
        string result(node_string);
        ts_free((void *)node_string);
        AssertThat(result, Equals(entry.tree_string));

        ts_tree_delete(tree);
      });

      for (unsigned i = 0; i < 20; i++) {
        unsigned int seed = TREE_SITTER_SEED + i;

        it("parses " + entry.description + ": " + "edit sequence " + to_string(seed), [&]() {
          random.reseed(seed);
          SpyInput input(entry.input, 3);
          unsigned edit_count = 1 + random(4);

          // Parse the input from the corpus.
          if (debug_graphs_enabled) printf("\n%s\n", input.content.c_str());
          TSTree *tree = ts_parser_parse(parser, nullptr, input.input());

          // Perform a random series of edits.
          for (unsigned j = 0; j < edit_count; j++) {
            TSInputEdit edit = do_random_edit(random, input, tree);
            ts_tree_edit(tree, &edit);
            if (debug_graphs_enabled) {
              ts_tree_print_dot_graph(tree, stderr);
              printf(
                "edit: %u - %u, %u - %u\n%s\n",
                edit.start_byte, edit.old_end_byte,
                edit.start_byte, edit.new_end_byte,
                input.content.c_str()
              );
            }
          }

          // Reparse the edited code incrementally.
          TSTree *new_tree = ts_parser_parse(parser, tree, input.input());
          assert_consistent_tree_sizes(new_tree, input.content);

          // Verify that the correct ranges have been marked as changed.
          uint32_t range_count;
          TSRange *ranges = ts_tree_get_changed_ranges(tree, new_tree, &range_count);
          ScopeSequence old_scope_sequence = build_scope_sequence(tree, input.content);
          ScopeSequence new_scope_sequence = build_scope_sequence(new_tree, input.content);
          verify_changed_ranges(
            old_scope_sequence, new_scope_sequence,
            input.content, ranges, range_count
          );
          ts_free(ranges);
          ts_tree_delete(tree);
          tree = new_tree;

          // Undo the random edits.
          while (input.can_undo()) {
            TSInputEdit edit = input.undo();
            ts_tree_edit(new_tree, &edit);
            if (debug_graphs_enabled) {
              ts_tree_print_dot_graph(tree, stderr);
              printf(
                "edit: %u - %u, %u - %u\n%s\n",
                edit.start_byte, edit.old_end_byte,
                edit.start_byte, edit.new_end_byte,
                input.content.c_str()
              );
            }
          }

          // Reparse the restored code incrementally.
          new_tree = ts_parser_parse(parser, tree, input.input());
          assert_consistent_tree_sizes(new_tree, input.content);

          // Verify that the correct ranges have been marked as changed.
          ranges = ts_tree_get_changed_ranges(tree, new_tree, &range_count);
          old_scope_sequence = build_scope_sequence(tree, input.content);
          new_scope_sequence = build_scope_sequence(new_tree, input.content);
          verify_changed_ranges(
            old_scope_sequence, new_scope_sequence,
            input.content, ranges, range_count
          );
          ts_free(ranges);
          ts_tree_delete(tree);
          tree = new_tree;

          // Verify that the final tree matches the expectation from the corpus.
          AssertThat(to_string(tree), Equals(entry.tree_string));
          ts_tree_delete(tree);
        });
      }
    }
  });
}

END_TEST;
