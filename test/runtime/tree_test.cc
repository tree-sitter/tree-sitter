#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "helpers/spy_logger.h"
#include "helpers/stderr_logger.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"

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
    parser = ts_parser_new();
  });

  after_each([&]() {
    ts_parser_delete(parser);
  });

  auto assert_root_node = [&](const string &expected) {
    TSNode node = ts_tree_root_node(tree);
    char *node_string = ts_node_string(node);
    string actual(node_string);
    ts_free(node_string);
    AssertThat(actual, Equals(expected));
  };

  describe("get_changed_ranges()", [&]() {
    before_each([&]() {
      ts_parser_set_language(parser, load_real_language("javascript"));
      input = new SpyInput("{a: null};\n", 3);
      tree = ts_parser_parse(parser, nullptr, input->input());

      assert_root_node(
        "(program (expression_statement (object (pair (property_identifier) (null)))))"
      );
    });

    after_each([&]() {
      ts_tree_delete(tree);
      delete input;
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
        TSRange{
          point(0, input->content.find("nothing")),
          point(0, input->content.find("}"))
        },
      })));

      // Replace `nothing` with `null` again
      ranges = get_changed_ranges_for_edit([&]() {
        return input->undo();
      });
      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          point(0, input->content.find("null")),
          point(0, input->content.find("}"))
        },
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
        TSRange{
          point(0, input->content.find(",")),
          point(0, input->content.find("}"))
        },
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
        TSRange{
          point(0, input->content.find(", c")),
          point(0, input->content.find(", b"))
        },
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
        TSRange{
          point(0, input->content.find("b ===")),
          point(0, input->content.find("}"))
        },
      })));
    });
  });
});

END_TEST
