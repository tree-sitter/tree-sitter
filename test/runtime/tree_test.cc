#include "test_helper.h"
#include <future>
#include "runtime/alloc.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "helpers/spy_logger.h"
#include "helpers/stderr_logger.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"
#include "helpers/random_helpers.h"
#include "helpers/read_test_entries.h"
#include "helpers/encoding_helpers.h"
#include "helpers/tree_helpers.h"

TSPoint point(uint32_t row, uint32_t column) {
  TSPoint result = {row, column};
  return result;
}

START_TEST

describe("Tree", [&]() {
  TSParser *parser;
  SpyInput *input;
  TSTree *tree;

  before_each([&]() {
    record_alloc::start(true);
    parser = ts_parser_new();
    tree = nullptr;
    input = nullptr;
  });

  after_each([&]() {
    if (tree) ts_tree_delete(tree);
    if (input) delete input;
    ts_parser_delete(parser);
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto assert_root_node = [&](const string &expected) {
    TSNode node = ts_tree_root_node(tree);
    char *node_string = ts_node_string(node);
    string actual(node_string);
    ts_free(node_string);
    AssertThat(actual, Equals(expected));
  };

  describe("copy()", [&]() {
    it("returns a tree that can be safely used while the current tree is edited", [&]() {
      const TSLanguage *language = load_real_language("javascript");
      ts_parser_set_language(parser, language);
      string source_code = examples_for_language("javascript")[0].input;

      input = new SpyInput(source_code, 32);
      TSTree *original_tree = ts_parser_parse(parser, nullptr, input->input());

      vector<future<TSTree *>> new_trees;
      for (unsigned i = 0; i < 8; i++) {
        TSTree *tree_copy = ts_tree_copy(original_tree);
        new_trees.push_back(std::async([i, tree_copy, &source_code, language]() {
          Generator random(TREE_SITTER_SEED + i);

          TSTree *tree = tree_copy;
          TSParser *parser = ts_parser_new();
          ts_parser_set_language(parser, language);
          SpyInput *input = new SpyInput(source_code, 1024);

          for (unsigned j = 0; j < 10; j++) {
            random.sleep_some();

            size_t edit_position = random(utf8_char_count(input->content));
            size_t deletion_size = random(utf8_char_count(input->content) - edit_position);
            string inserted_text = random.words(random(4) + 1);

            TSInputEdit edit = input->replace(edit_position, deletion_size, inserted_text);
            ts_tree_edit(tree, &edit);

            TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
            ts_tree_delete(tree);
            tree = new_tree;
          }

          ts_parser_delete(parser);
          delete input;

          return tree;
        }));
      }

      ts_tree_delete(original_tree);

      for (auto &future : new_trees) {
        future.wait();
        TSTree *new_tree = future.get();
        assert_consistent_tree_sizes(ts_tree_root_node(new_tree));
        ts_tree_delete(new_tree);
      }
    });
  });

  describe("get_changed_ranges()", [&]() {
    before_each([&]() {
      ts_parser_set_language(parser, load_real_language("javascript"));
      input = new SpyInput("{a: null};\n", 3);
      tree = ts_parser_parse(parser, nullptr, input->input());

      assert_root_node(
        "(program (expression_statement (object (pair (property_identifier) (null)))))"
      );
    });

    auto get_changed_ranges_for_edit = [&](function<TSInputEdit()> fn) -> vector<TSRange> {
      TSInputEdit edit = fn();
      ts_tree_edit(tree, &edit);

      uint32_t range_count = 0;
      TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
      TSRange *ranges = ts_tree_get_changed_ranges(tree, new_tree, &range_count);
      ts_tree_delete(tree);
      tree = new_tree;

      vector<TSRange> result;
      for (size_t i = 0; i < range_count; i++) {
        result.push_back(ranges[i]);
      }

      ts_free(ranges);
      return result;
    };

    it("reports changes when one token has been updated", [&]() {
      // Replace `null` with `nothing`
      auto ranges = get_changed_ranges_for_edit([&]() {
        return input->replace(input->content.find("ull"), 1, "othing");
      });
      AssertThat(ranges, Equals(vector<TSRange>({
        range_for_substring(input->content, "nothing"),
      })));

      // Replace `nothing` with `null` again
      ranges = get_changed_ranges_for_edit([&]() {
        return input->undo();
      });
      AssertThat(ranges, Equals(vector<TSRange>({
        range_for_substring(input->content, "null"),
      })));
    });

    it("reports no changes when leading whitespace has changed (regression)", [&]() {
      input->chars_per_chunk = 80;

      // Insert leading whitespace
      auto ranges = get_changed_ranges_for_edit([&]() {
        return input->replace(0, 0, "\n");
      });
      assert_root_node(
        "(program (expression_statement (object (pair (property_identifier) (null)))))"
      );
      AssertThat(ranges, IsEmpty());

      // Remove leading whitespace
      ranges = get_changed_ranges_for_edit([&]() {
        return input->undo();
      });
      assert_root_node(
        "(program (expression_statement (object (pair (property_identifier) (null)))))"
      );
      AssertThat(ranges, IsEmpty());

      // Insert leading whitespace again
      ranges = get_changed_ranges_for_edit([&]() {
        return input->replace(0, 0, "\n");
      });
      assert_root_node(
        "(program (expression_statement (object (pair (property_identifier) (null)))))"
      );
      AssertThat(ranges, IsEmpty());
    });

    it("reports changes when tokens have been appended", [&]() {
      // Add a second key-value pair
      auto ranges = get_changed_ranges_for_edit([&]() {
        return input->replace(input->content.find("}"), 0, ", b: false");
      });
      AssertThat(ranges, Equals(vector<TSRange>({
        range_for_substring(input->content, ", b: false"),
      })));

      // Add a third key-value pair in between the first two
      ranges = get_changed_ranges_for_edit([&]() {
        return input->replace(input->content.find(", b"), 0, ", c: 1");
      });
      assert_root_node(
        "(program (expression_statement (object "
          "(pair (property_identifier) (null)) "
          "(pair (property_identifier) (number)) "
          "(pair (property_identifier) (false)))))"
      );
      AssertThat(ranges, Equals(vector<TSRange>({
        range_for_substring(input->content, ", c: 1, b: false"),
      })));

      // Delete the middle pair.
      ranges = get_changed_ranges_for_edit([&]() {
        return input->undo();
      });
      assert_root_node(
        "(program (expression_statement (object "
          "(pair (property_identifier) (null)) "
          "(pair (property_identifier) (false)))))"
      );
      AssertThat(ranges, IsEmpty());

      // Delete the second pair.
      ranges = get_changed_ranges_for_edit([&]() {
        return input->undo();
      });
      assert_root_node(
        "(program (expression_statement (object "
          "(pair (property_identifier) (null)))))"
      );
      AssertThat(ranges, IsEmpty());
    });

    it("reports changes when trees have been wrapped", [&]() {
      // Wrap the object in an assignment expression.
      auto ranges = get_changed_ranges_for_edit([&]() {
        return input->replace(input->content.find("null"), 0, "b === ");
      });
      assert_root_node(
        "(program (expression_statement (object "
          "(pair (property_identifier) (binary_expression (identifier) (null))))))"
      );
      AssertThat(ranges, Equals(vector<TSRange>({
        range_for_substring(input->content, "b === null"),
      })));
    });
  });
});

END_TEST
