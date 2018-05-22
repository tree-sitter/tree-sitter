#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "helpers/load_language.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"

START_TEST

string json_string = R"JSON(

[
  123,
  false,
  {
    "x": null
  }
]
)JSON";

size_t array_index = json_string.find("[\n");
size_t array_end_index = json_string.find("]") + 1;
size_t number_index = json_string.find("123");
size_t number_end_index = number_index + string("123").size();
size_t false_index = json_string.find("false");
size_t false_end_index = false_index + string("false").size();
size_t object_index = json_string.find("{");
size_t object_end_index = json_string.find("}") + 1;
size_t string_index = json_string.find("\"x\"");
size_t string_end_index = string_index + 3;
size_t colon_index = json_string.find(":");
size_t null_index = json_string.find("null");
size_t null_end_index = null_index + string("null").size();

string grammar_with_aliases_and_extras = R"JSON({
  "name": "aliases_and_extras",

  "extras": [
    {"type": "PATTERN", "value": "\\s+"},
    {"type": "SYMBOL", "name": "comment"},
  ],

  "rules": {
    "a": {
      "type": "SEQ",
      "members": [
        {"type": "SYMBOL", "name": "b"},
        {
          "type": "ALIAS",
          "value": "B",
          "named": true,
          "content": {"type": "SYMBOL", "name": "b"}
        },
        {
          "type": "ALIAS",
          "value": "C",
          "named": true,
          "content": {"type": "SYMBOL", "name": "_c"}
        }
      ]
    },

    "b": {"type": "STRING", "value": "b"},

    "_c": {"type": "STRING", "value": "c"},

    "comment": {"type": "STRING", "value": "..."}
  }
})JSON";

const TSLanguage *language_with_aliases_and_extras = load_test_language(
  "aliases_and_extras",
  ts_compile_grammar(grammar_with_aliases_and_extras.c_str())
);

describe("Node", [&]() {
  TSParser *parser;
  TSTree *tree;
  TSNode root_node;
  TSNode NULL_NODE = {};

  before_each([&]() {
    record_alloc::start();

    parser = ts_parser_new();
    ts_parser_set_language(parser, load_real_language("json"));
    tree = ts_parser_parse_string(parser, nullptr, json_string.c_str(), json_string.size());
    root_node = ts_node_child(ts_tree_root_node(tree), 0);
  });

  after_each([&]() {
    ts_parser_delete(parser);
    ts_tree_delete(tree);

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  it("parses the example as expected (precondition)", [&]() {
    char *node_string = ts_node_string(root_node);
    AssertThat(node_string, Equals(
      "(array "
        "(number) "
        "(false) "
        "(object (pair (string) (null))))"));
    ts_free(node_string);
  });

  describe("named_child_count(), named_child(i)", [&]() {
    it("returns the named child node at the given index", [&]() {
      AssertThat(ts_node_type(root_node), Equals("array"));

      AssertThat(ts_node_named_child_count(root_node), Equals<size_t>(3));
      AssertThat(ts_node_start_byte(root_node), Equals(array_index));
      AssertThat(ts_node_end_byte(root_node), Equals(array_end_index));
      AssertThat(ts_node_start_point(root_node), Equals<TSPoint>({ 2, 0 }));
      AssertThat(ts_node_end_point(root_node), Equals<TSPoint>({ 8, 1 }));

      TSNode number_node = ts_node_named_child(root_node, 0);
      TSNode false_node = ts_node_named_child(root_node, 1);
      TSNode object_node = ts_node_named_child(root_node, 2);

      AssertThat(ts_node_type(number_node), Equals("number"));
      AssertThat(ts_node_type(false_node), Equals("false"));
      AssertThat(ts_node_type(object_node), Equals("object"));

      AssertThat(ts_node_start_byte(number_node), Equals(number_index));
      AssertThat(ts_node_end_byte(number_node), Equals(number_end_index));
      AssertThat(ts_node_start_point(number_node), Equals<TSPoint>({ 3, 2 }));
      AssertThat(ts_node_end_point(number_node), Equals<TSPoint>({ 3, 5 }));

      AssertThat(ts_node_start_byte(false_node), Equals(false_index));
      AssertThat(ts_node_end_byte(false_node), Equals(false_end_index));
      AssertThat(ts_node_start_point(false_node), Equals<TSPoint>({ 4, 2 }));
      AssertThat(ts_node_end_point(false_node), Equals<TSPoint>({ 4, 7 }));

      AssertThat(ts_node_start_byte(object_node), Equals(object_index));
      AssertThat(ts_node_end_byte(object_node), Equals(object_end_index));
      AssertThat(ts_node_start_point(object_node), Equals<TSPoint>({ 5, 2 }));
      AssertThat(ts_node_end_point(object_node), Equals<TSPoint>({ 7, 3 }));
      AssertThat(ts_node_named_child_count(object_node), Equals<size_t>(1));

      TSNode pair_node = ts_node_named_child(object_node, 0);

      AssertThat(ts_node_type(pair_node), Equals("pair"));
      AssertThat(ts_node_start_byte(pair_node), Equals(string_index));
      AssertThat(ts_node_end_byte(pair_node), Equals(null_end_index));
      AssertThat(ts_node_start_point(pair_node), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(pair_node), Equals<TSPoint>({ 6, 13 }));
      AssertThat(ts_node_named_child_count(pair_node), Equals<size_t>(2));

      TSNode string_node = ts_node_named_child(pair_node, 0);
      TSNode null_node = ts_node_named_child(pair_node, 1);

      AssertThat(ts_node_type(string_node), Equals("string"));
      AssertThat(ts_node_type(null_node), Equals("null"));

      AssertThat(ts_node_start_byte(string_node), Equals(string_index));
      AssertThat(ts_node_end_byte(string_node), Equals(string_end_index));
      AssertThat(ts_node_start_point(string_node), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(string_node), Equals<TSPoint>({ 6, 7 }));

      AssertThat(ts_node_start_byte(null_node), Equals(null_index));
      AssertThat(ts_node_end_byte(null_node), Equals(null_end_index));
      AssertThat(ts_node_start_point(null_node), Equals<TSPoint>({ 6, 9 }));
      AssertThat(ts_node_end_point(null_node), Equals<TSPoint>({ 6, 13 }));

      AssertThat(ts_node_parent(string_node), Equals(pair_node));
      AssertThat(ts_node_parent(null_node), Equals(pair_node));
      AssertThat(ts_node_parent(pair_node), Equals(object_node));
      AssertThat(ts_node_parent(number_node), Equals(root_node));
      AssertThat(ts_node_parent(false_node), Equals(root_node));
      AssertThat(ts_node_parent(object_node), Equals(root_node));
      AssertThat(ts_node_parent(ts_tree_root_node(tree)), Equals(NULL_NODE));
    });

    it("works correctly when the node contains aliased children and extras", [&]() {
      ts_parser_set_language(parser, language_with_aliases_and_extras);
      ts_tree_delete(tree);
      tree = ts_parser_parse_string(parser, nullptr, "b ... b ... c", 13);
      root_node = ts_tree_root_node(tree);

      char *node_string = ts_node_string(root_node);
      AssertThat(node_string, Equals("(a (b) (comment) (B) (comment) (C))"));
      ts_free(node_string);

      AssertThat(ts_node_named_child_count(root_node), Equals(5u));
      AssertThat(ts_node_type(ts_node_named_child(root_node, 0)), Equals("b"));
      AssertThat(ts_node_type(ts_node_named_child(root_node, 1)), Equals("comment"));
      AssertThat(ts_node_type(ts_node_named_child(root_node, 2)), Equals("B"));
      AssertThat(ts_node_type(ts_node_named_child(root_node, 3)), Equals("comment"));
      AssertThat(ts_node_type(ts_node_named_child(root_node, 4)), Equals("C"));

      AssertThat(
        ts_node_symbol(ts_node_named_child(root_node, 0)),
        !Equals(ts_node_symbol(ts_node_named_child(root_node, 2)))
      );
    });
  });

  describe("first_child_for_byte(byte_offset)", [&]() {
    it("returns the first child that extends beyond the given byte offset", [&]() {
      TSNode child;

      child = ts_node_first_child_for_byte(root_node, array_index);
      AssertThat(ts_node_type(child), Equals("["));
      child = ts_node_first_child_for_byte(root_node, number_index);
      AssertThat(ts_node_type(child), Equals("number"));
      child = ts_node_first_child_for_byte(root_node, number_end_index);
      AssertThat(ts_node_type(child), Equals(","));
      child = ts_node_first_child_for_byte(root_node, number_end_index + 1);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_child_for_byte(root_node, false_index - 1);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_child_for_byte(root_node, false_index);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_child_for_byte(root_node, false_index + 1);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_child_for_byte(root_node, false_end_index);
      AssertThat(ts_node_type(child), Equals(","));
      child = ts_node_first_child_for_byte(root_node, false_end_index);
      AssertThat(ts_node_type(child), Equals(","));
      child = ts_node_first_child_for_byte(root_node, object_index);
      AssertThat(ts_node_type(child), Equals("object"));
      child = ts_node_first_child_for_byte(root_node, object_index + 1);
      AssertThat(ts_node_type(child), Equals("object"));
      child = ts_node_first_child_for_byte(root_node, object_end_index);
      AssertThat(ts_node_type(child), Equals("]"));
    });
  });

  describe("first_named_child_for_byte(byte_offset)", [&]() {
    it("returns the first named child that extends beyond the given byte offset", [&]() {
      TSNode child;

      child = ts_node_first_named_child_for_byte(root_node, array_index);
      AssertThat(ts_node_type(child), Equals("number"));
      child = ts_node_first_named_child_for_byte(root_node, number_index);
      AssertThat(ts_node_type(child), Equals("number"));
      child = ts_node_first_named_child_for_byte(root_node, number_end_index);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_named_child_for_byte(root_node, number_end_index + 1);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_named_child_for_byte(root_node, false_index - 1);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_named_child_for_byte(root_node, false_index);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_named_child_for_byte(root_node, false_index + 1);
      AssertThat(ts_node_type(child), Equals("false"));
      child = ts_node_first_named_child_for_byte(root_node, false_end_index);
      AssertThat(ts_node_type(child), Equals("object"));
      child = ts_node_first_named_child_for_byte(root_node, object_index);
      AssertThat(ts_node_type(child), Equals("object"));
      child = ts_node_first_named_child_for_byte(root_node, object_index + 1);
      AssertThat(ts_node_type(child), Equals("object"));
      child = ts_node_first_named_child_for_byte(root_node, object_end_index);
      AssertThat(child, Equals(NULL_NODE));
    });
  });

  describe("child_count(), child(i)", [&]() {
    it("returns the child node at the given index, including anonymous nodes", [&]() {
      AssertThat(ts_node_child_count(root_node), Equals<size_t>(7));
      TSNode child1 = ts_node_child(root_node, 0);
      TSNode child2 = ts_node_child(root_node, 1);
      TSNode child3 = ts_node_child(root_node, 2);
      TSNode child4 = ts_node_child(root_node, 3);
      TSNode child5 = ts_node_child(root_node, 4);
      TSNode child6 = ts_node_child(root_node, 5);
      TSNode child7 = ts_node_child(root_node, 6);

      AssertThat(ts_node_type(root_node), Equals("array"));
      AssertThat(ts_node_type(child1), Equals("["));
      AssertThat(ts_node_type(child2), Equals("number"));
      AssertThat(ts_node_type(child3), Equals(","));
      AssertThat(ts_node_type(child4), Equals("false"));
      AssertThat(ts_node_type(child5), Equals(","));
      AssertThat(ts_node_type(child6), Equals("object"));
      AssertThat(ts_node_type(child7), Equals("]"));

      AssertThat(ts_node_is_named(root_node), IsTrue());
      AssertThat(ts_node_is_named(child1), IsFalse());
      AssertThat(ts_node_is_named(child2), IsTrue());
      AssertThat(ts_node_is_named(child3), IsFalse());
      AssertThat(ts_node_is_named(child4), IsTrue());
      AssertThat(ts_node_is_named(child5), IsFalse());
      AssertThat(ts_node_is_named(child6), IsTrue());
      AssertThat(ts_node_is_named(child7), IsFalse());

      AssertThat(ts_node_start_byte(child1), Equals(array_index));
      AssertThat(ts_node_end_byte(child1), Equals(array_index + 1));
      AssertThat(ts_node_start_point(child1), Equals<TSPoint>({ 2, 0 }));
      AssertThat(ts_node_end_point(child1), Equals<TSPoint>({ 2, 1 }));

      AssertThat(ts_node_start_byte(child3), Equals(number_end_index));
      AssertThat(ts_node_end_byte(child3), Equals(number_end_index + 1));
      AssertThat(ts_node_start_point(child3), Equals<TSPoint>({ 3, 5 }));
      AssertThat(ts_node_end_point(child3), Equals<TSPoint>({ 3, 6 }));

      AssertThat(ts_node_start_byte(child5), Equals(false_end_index));
      AssertThat(ts_node_end_byte(child5), Equals(false_end_index + 1));
      AssertThat(ts_node_start_point(child5), Equals<TSPoint>({ 4, 7 }));
      AssertThat(ts_node_end_point(child5), Equals<TSPoint>({ 4, 8 }));

      AssertThat(ts_node_start_byte(child7), Equals(array_end_index - 1));
      AssertThat(ts_node_end_byte(child7), Equals(array_end_index));
      AssertThat(ts_node_start_point(child7), Equals<TSPoint>({ 8, 0 }));
      AssertThat(ts_node_end_point(child7), Equals<TSPoint>({ 8, 1 }));

      AssertThat(ts_node_child_count(child6), Equals<size_t>(3))

      TSNode left_brace = ts_node_child(child6, 0);
      TSNode pair = ts_node_child(child6, 1);
      TSNode right_brace = ts_node_child(child6, 2);

      TSNode grandchild2 = ts_node_child(pair, 0);
      TSNode grandchild3 = ts_node_child(pair, 1);
      TSNode grandchild4 = ts_node_child(pair, 2);

      AssertThat(ts_node_type(left_brace), Equals("{"));
      AssertThat(ts_node_type(pair), Equals("pair"));
      AssertThat(ts_node_type(right_brace), Equals("}"));

      AssertThat(ts_node_type(grandchild2), Equals("string"));
      AssertThat(ts_node_type(grandchild3), Equals(":"));
      AssertThat(ts_node_type(grandchild4), Equals("null"));

      AssertThat(ts_node_parent(grandchild2), Equals(pair));
      AssertThat(ts_node_parent(grandchild3), Equals(pair));
      AssertThat(ts_node_parent(grandchild4), Equals(pair));
      AssertThat(ts_node_parent(left_brace), Equals(child6));
      AssertThat(ts_node_parent(pair), Equals(child6));
      AssertThat(ts_node_parent(right_brace), Equals(child6));
      AssertThat(ts_node_parent(child1), Equals(root_node));
      AssertThat(ts_node_parent(child2), Equals(root_node));
      AssertThat(ts_node_parent(child3), Equals(root_node));
      AssertThat(ts_node_parent(child4), Equals(root_node));
      AssertThat(ts_node_parent(child5), Equals(root_node));
      AssertThat(ts_node_parent(child6), Equals(root_node));
      AssertThat(ts_node_parent(child7), Equals(root_node));
      AssertThat(ts_node_parent(ts_tree_root_node(tree)), Equals(NULL_NODE));
    });
  });

  describe("next_sibling(), prev_sibling()", [&]() {
    it("returns the node's next and previous sibling, including anonymous nodes", [&]() {
      TSNode bracket_node1 = ts_node_child(root_node, 0);
      TSNode number_node = ts_node_child(root_node, 1);
      TSNode array_comma_node1 = ts_node_child(root_node, 2);
      TSNode false_node = ts_node_child(root_node, 3);
      TSNode array_comma_node2 = ts_node_child(root_node, 4);
      TSNode object_node = ts_node_child(root_node, 5);
      TSNode brace_node1 = ts_node_child(object_node, 0);
      TSNode pair_node = ts_node_child(object_node, 1);
      TSNode string_node = ts_node_child(pair_node, 0);
      TSNode colon_node = ts_node_child(pair_node, 1);
      TSNode null_node = ts_node_child(pair_node, 2);
      TSNode brace_node2 = ts_node_child(object_node, 2);
      TSNode bracket_node2 = ts_node_child(root_node, 6);

      AssertThat(ts_node_parent(bracket_node1), Equals(root_node));
      AssertThat(ts_node_next_sibling(bracket_node1), Equals(number_node));
      AssertThat(ts_node_next_sibling(number_node), Equals(array_comma_node1));
      AssertThat(ts_node_next_sibling(array_comma_node1), Equals(false_node));
      AssertThat(ts_node_next_sibling(false_node), Equals(array_comma_node2));
      AssertThat(ts_node_next_sibling(array_comma_node2), Equals(object_node));
      AssertThat(ts_node_next_sibling(object_node), Equals(bracket_node2));
      AssertThat(ts_node_next_sibling(bracket_node2), Equals(NULL_NODE));

      AssertThat(ts_node_prev_sibling(bracket_node1), Equals(NULL_NODE));
      AssertThat(ts_node_prev_sibling(number_node), Equals(bracket_node1));
      AssertThat(ts_node_prev_sibling(array_comma_node1), Equals(number_node));
      AssertThat(ts_node_prev_sibling(false_node), Equals(array_comma_node1));
      AssertThat(ts_node_prev_sibling(array_comma_node2), Equals(false_node));
      AssertThat(ts_node_prev_sibling(object_node), Equals(array_comma_node2));
      AssertThat(ts_node_prev_sibling(bracket_node2), Equals(object_node));

      AssertThat(ts_node_next_sibling(brace_node1), Equals(pair_node));
      AssertThat(ts_node_next_sibling(pair_node), Equals(brace_node2));
      AssertThat(ts_node_next_sibling(brace_node2), Equals(NULL_NODE));

      AssertThat(ts_node_prev_sibling(brace_node1), Equals(NULL_NODE));
      AssertThat(ts_node_prev_sibling(pair_node), Equals(brace_node1));
      AssertThat(ts_node_prev_sibling(brace_node2), Equals(pair_node));

      AssertThat(ts_node_next_sibling(string_node), Equals(colon_node));
      AssertThat(ts_node_next_sibling(colon_node), Equals(null_node));
      AssertThat(ts_node_next_sibling(null_node), Equals(NULL_NODE));

      AssertThat(ts_node_prev_sibling(string_node), Equals(NULL_NODE));
      AssertThat(ts_node_prev_sibling(colon_node), Equals(string_node));
      AssertThat(ts_node_prev_sibling(null_node), Equals(colon_node));
    });

    it("returns null when the node has no parent", [&]() {
      AssertThat(ts_node_next_named_sibling(root_node), Equals(NULL_NODE));
      AssertThat(ts_node_prev_named_sibling(root_node), Equals(NULL_NODE));
    });
  });

  describe("next_named_sibling(), prev_named_sibling()", [&]() {
    it("returns the node's next and previous siblings", [&]() {
      TSNode number_node = ts_node_named_child(root_node, 0);
      TSNode false_node = ts_node_named_child(root_node, 1);
      TSNode object_node = ts_node_named_child(root_node, 2);
      TSNode pair_node = ts_node_named_child(object_node, 0);
      TSNode string_node = ts_node_named_child(pair_node, 0);
      TSNode null_node = ts_node_named_child(pair_node, 1);

      AssertThat(ts_node_next_named_sibling(number_node), Equals(false_node));
      AssertThat(ts_node_next_named_sibling(false_node), Equals(object_node));
      AssertThat(ts_node_next_named_sibling(string_node), Equals(null_node));
      AssertThat(ts_node_prev_named_sibling(object_node), Equals(false_node));
      AssertThat(ts_node_prev_named_sibling(false_node), Equals(number_node));
      AssertThat(ts_node_prev_named_sibling(null_node), Equals(string_node));
    });

    it("returns null when the node has no parent", [&]() {
      AssertThat(ts_node_next_named_sibling(root_node), Equals(NULL_NODE));
      AssertThat(ts_node_prev_named_sibling(root_node), Equals(NULL_NODE));
    });
  });

  describe("named_descendant_for_byte_range(start, end)", [&]() {
    describe("when there is a leaf node that spans the given range exactly", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_named_descendant_for_byte_range(root_node, string_index, string_end_index - 1);
        AssertThat(ts_node_type(leaf), Equals("string"));
        AssertThat(ts_node_start_byte(leaf), Equals(string_index));
        AssertThat(ts_node_end_byte(leaf), Equals(string_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 6, 7 }));

        leaf = ts_node_named_descendant_for_byte_range(root_node, number_index, number_end_index - 1);
        AssertThat(ts_node_type(leaf), Equals("number"));
        AssertThat(ts_node_start_byte(leaf), Equals(number_index));
        AssertThat(ts_node_end_byte(leaf), Equals(number_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 3, 2 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 3, 5 }));
      });
    });

    describe("when there is a leaf node that extends beyond the given range", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_named_descendant_for_byte_range(root_node, string_index, string_index + 1);
        AssertThat(ts_node_type(leaf), Equals("string"));
        AssertThat(ts_node_start_byte(leaf), Equals(string_index));
        AssertThat(ts_node_end_byte(leaf), Equals(string_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 6, 7 }));

        leaf = ts_node_named_descendant_for_byte_range(root_node, string_index + 1, string_index + 2);
        AssertThat(ts_node_type(leaf), Equals("string"));
        AssertThat(ts_node_start_byte(leaf), Equals(string_index));
        AssertThat(ts_node_end_byte(leaf), Equals(string_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 6, 7 }));
      });
    });

    describe("when there is no leaf node that spans the given range", [&]() {
      it("returns the smallest node that does span the range", [&]() {
        TSNode pair_node = ts_node_named_descendant_for_byte_range(root_node, string_index, string_index + 3);
        AssertThat(ts_node_type(pair_node), Equals("pair"));
        AssertThat(ts_node_start_byte(pair_node), Equals(string_index));
        AssertThat(ts_node_end_byte(pair_node), Equals(null_end_index));
        AssertThat(ts_node_start_point(pair_node), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(pair_node), Equals<TSPoint>({ 6, 13 }));
      });

      it("does not return invisible nodes (repeats)", [&]() {
        TSNode node = ts_node_named_descendant_for_byte_range(root_node, number_end_index, number_end_index + 1);
        AssertThat(ts_node_type(node), Equals("array"));
        AssertThat(ts_node_start_byte(node), Equals(array_index));
        AssertThat(ts_node_end_byte(node), Equals(array_end_index));
        AssertThat(ts_node_start_point(node), Equals<TSPoint>({ 2, 0 }));
        AssertThat(ts_node_end_point(node), Equals<TSPoint>({ 8, 1 }));
      });
    });
  });

  describe("descendant_for_byte_range(start, end)", [&]() {
    it("returns the smallest node that spans the given byte offsets", [&]() {
      TSNode node1 = ts_node_descendant_for_byte_range(root_node, colon_index, colon_index);
      AssertThat(ts_node_type(node1), Equals(":"));
      AssertThat(ts_node_start_byte(node1), Equals(colon_index));
      AssertThat(ts_node_end_byte(node1), Equals(colon_index + 1));
      AssertThat(ts_node_start_point(node1), Equals<TSPoint>({ 6, 7 }));
      AssertThat(ts_node_end_point(node1), Equals<TSPoint>({ 6, 8 }));

      TSNode node2 = ts_node_descendant_for_byte_range(root_node, string_index + 2, string_index + 4);
      AssertThat(ts_node_type(node2), Equals("pair"));
      AssertThat(ts_node_start_byte(node2), Equals(string_index));
      AssertThat(ts_node_end_byte(node2), Equals(null_end_index));
      AssertThat(ts_node_start_point(node2), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(node2), Equals<TSPoint>({ 6, 13 }));
    });

    it("works in the presence of multi-byte characters", [&]() {
      string input_string = "[\"αβγδ\", \"αβγδ\"]";

      ts_tree_delete(tree);
      tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
      TSNode root_node = ts_tree_root_node(tree);

      uint32_t comma_position = input_string.find(",");
      TSNode node1 = ts_node_descendant_for_byte_range(root_node, comma_position, comma_position);
      AssertThat(ts_node_type(node1), Equals(","));

      TSNode node2 = ts_node_descendant_for_byte_range(root_node, 6, 10);
      AssertThat(ts_node_type(node2), Equals("string"));
      AssertThat(ts_node_start_byte(node2), Equals<size_t>(1));
      AssertThat(ts_node_end_byte(node2), Equals<size_t>(11));
    });
  });

  describe("descendant_for_point_range(start, end)", [&]() {
    it("returns the smallest concrete node that spans the given range", [&]() {
      TSNode node1 = ts_node_descendant_for_point_range(root_node, {6, 7}, {6, 7});
      AssertThat(ts_node_type(node1), Equals(":"));
      AssertThat(ts_node_start_byte(node1), Equals(colon_index));
      AssertThat(ts_node_end_byte(node1), Equals(colon_index + 1));
      AssertThat(ts_node_start_point(node1), Equals<TSPoint>({ 6, 7 }));
      AssertThat(ts_node_end_point(node1), Equals<TSPoint>({ 6, 8 }));

      TSNode node2 = ts_node_descendant_for_point_range(root_node, {6, 6}, {6, 8});
      AssertThat(ts_node_type(node2), Equals("pair"));
      AssertThat(ts_node_start_byte(node2), Equals(string_index));
      AssertThat(ts_node_end_byte(node2), Equals(null_end_index));
      AssertThat(ts_node_start_point(node2), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(node2), Equals<TSPoint>({ 6, 13 }));
    });
  });
});

describe("TreeCursor", [&]() {
  TSParser *parser;
  TSTree *tree;
  TSTreeCursor cursor;

  before_each([&]() {
    record_alloc::start();

    parser = ts_parser_new();
    ts_parser_set_language(parser, load_real_language("json"));
    tree = ts_parser_parse_string(parser, nullptr, json_string.c_str(), json_string.size());
    cursor = ts_tree_cursor_new(tree);
  });

  after_each([&]() {
    ts_tree_delete(tree);
    ts_tree_cursor_delete(&cursor);
    ts_parser_delete(parser);

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  it("can walk the tree", [&]() {
    TSNode node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("value"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));

    AssertThat(ts_tree_cursor_goto_first_child(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("array"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));

    AssertThat(ts_tree_cursor_goto_first_child(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("["));
    AssertThat(ts_node_start_byte(node), Equals(array_index));

    // Cannot descend into a node with no children
    AssertThat(ts_tree_cursor_goto_first_child(&cursor), IsFalse());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("["));
    AssertThat(ts_node_start_byte(node), Equals(array_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("number"));
    AssertThat(ts_node_start_byte(node), Equals(number_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals(","));
    AssertThat(ts_node_start_byte(node), Equals(number_end_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("false"));
    AssertThat(ts_node_start_byte(node), Equals(false_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals(","));
    AssertThat(ts_node_start_byte(node), Equals(false_end_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("object"));
    AssertThat(ts_node_start_byte(node), Equals(object_index));

    AssertThat(ts_tree_cursor_goto_first_child(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("{"));
    AssertThat(ts_node_start_byte(node), Equals(object_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("pair"));
    AssertThat(ts_node_start_byte(node), Equals(string_index));

    AssertThat(ts_tree_cursor_goto_first_child(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("string"));
    AssertThat(ts_node_start_byte(node), Equals(string_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals(":"));
    AssertThat(ts_node_start_byte(node), Equals(string_end_index));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("null"));
    AssertThat(ts_node_start_byte(node), Equals(null_index));

    // Cannot move beyond a node with no next sibling
    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsFalse());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("null"));
    AssertThat(ts_node_start_byte(node), Equals(null_index));

    AssertThat(ts_tree_cursor_goto_parent(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("pair"));
    AssertThat(ts_node_start_byte(node), Equals(string_index));

    AssertThat(ts_tree_cursor_goto_parent(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("object"));
    AssertThat(ts_node_start_byte(node), Equals(object_index));

    AssertThat(ts_tree_cursor_goto_parent(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("array"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));

    AssertThat(ts_tree_cursor_goto_parent(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("value"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));

    // The root node doesn't have a parent.
    AssertThat(ts_tree_cursor_goto_parent(&cursor), IsFalse());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("value"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));
  });

  it("can find the first child of a given node which spans the given byte offset", [&]() {
    int64_t child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, 1);
    TSNode node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("array"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));
    AssertThat(child_index, Equals(0));

    child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, array_index);
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("["));
    AssertThat(ts_node_start_byte(node), Equals(array_index));
    AssertThat(child_index, Equals(0));

    ts_tree_cursor_goto_parent(&cursor);
    child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, array_index + 1);
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("number"));
    AssertThat(ts_node_start_byte(node), Equals(number_index));
    AssertThat(child_index, Equals(1));

    ts_tree_cursor_goto_parent(&cursor);
    child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, number_index + 1);
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("number"));
    AssertThat(ts_node_start_byte(node), Equals(number_index));
    AssertThat(child_index, Equals(1));

    ts_tree_cursor_goto_parent(&cursor);
    child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, false_index - 1);
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("false"));
    AssertThat(ts_node_start_byte(node), Equals(false_index));
    AssertThat(child_index, Equals(3));

    ts_tree_cursor_goto_parent(&cursor);
    child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, object_end_index - 1);
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("object"));
    AssertThat(ts_node_start_byte(node), Equals(object_index));
    AssertThat(child_index, Equals(5));

    // There is no child past the end of the array
    ts_tree_cursor_goto_parent(&cursor);
    child_index = ts_tree_cursor_goto_first_child_for_byte(&cursor, array_end_index);
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("array"));
    AssertThat(ts_node_start_byte(node), Equals(array_index));
    AssertThat(child_index, Equals(-1));
  });

  it("walks the tree correctly when the node contains aliased children and extras", [&]() {
    ts_parser_set_language(parser, language_with_aliases_and_extras);
    ts_tree_cursor_delete(&cursor);
    ts_tree_delete(tree);

    tree = ts_parser_parse_string(parser, nullptr, "b ... b ... c", 13);
    cursor = ts_tree_cursor_new(tree);

    TSNode node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("a"));

    AssertThat(ts_tree_cursor_goto_first_child(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("b"));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("comment"));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("B"));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("comment"));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsTrue());
    node = ts_tree_cursor_current_node(&cursor);
    AssertThat(ts_node_type(node), Equals("C"));

    AssertThat(ts_tree_cursor_goto_next_sibling(&cursor), IsFalse());
    AssertThat(ts_tree_cursor_goto_parent(&cursor), IsTrue());
    AssertThat(ts_tree_cursor_goto_first_child_for_byte(&cursor, 0), Equals(0));
  });
});

END_TEST
