#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "helpers/load_language.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"

START_TEST

describe("Node", []() {
  TSDocument *document;
  TSNode array_node;
  string input_string =
    "\n"
    "\n"
    "[\n"
    "  123,\n"
    "  false,\n"
    "  {\n"
    "    \"x\": null\n"
    "  }\n"
    "]";

  size_t array_index = input_string.find("[\n");
  size_t array_end_index = input_string.find("]") + 1;
  size_t number_index = input_string.find("123");
  size_t number_end_index = number_index + string("123").size();
  size_t false_index = input_string.find("false");
  size_t false_end_index = false_index + string("false").size();
  size_t object_index = input_string.find("{");
  size_t object_end_index = input_string.find("}") + 1;
  size_t string_index = input_string.find("\"x\"");
  size_t string_end_index = string_index + 3;
  size_t colon_index = input_string.find(":");
  size_t null_index = input_string.find("null");
  size_t null_end_index = null_index + string("null").size();

  before_each([&]() {
    record_alloc::start();

    document = ts_document_new();
    ts_document_set_language(document, load_real_language("json"));
    ts_document_set_input_string(document, input_string.c_str());
    ts_document_parse(document);

    array_node = ts_document_root_node(document);
    char *node_string = ts_node_string(array_node, document);
    AssertThat(node_string, Equals(
      "(array "
        "(number) "
        "(false) "
        "(object (pair (string) (null))))"));
    ts_free(node_string);
  });

  after_each([&]() {
    ts_document_free(document);

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  describe("named_child_count(), named_child(i)", [&]() {
    it("returns the named child node at the given index", [&]() {
      AssertThat(ts_node_type(array_node, document), Equals("array"));

      AssertThat(ts_node_named_child_count(array_node), Equals<size_t>(3));
      AssertThat(ts_node_start_byte(array_node), Equals(array_index));
      AssertThat(ts_node_end_byte(array_node), Equals(array_end_index));
      AssertThat(ts_node_start_char(array_node), Equals(array_index));
      AssertThat(ts_node_end_char(array_node), Equals(array_end_index));
      AssertThat(ts_node_start_point(array_node), Equals<TSPoint>({ 2, 0 }));
      AssertThat(ts_node_end_point(array_node), Equals<TSPoint>({ 8, 1 }));

      TSNode number_node = ts_node_named_child(array_node, 0);
      TSNode false_node = ts_node_named_child(array_node, 1);
      TSNode object_node = ts_node_named_child(array_node, 2);

      AssertThat(ts_node_type(number_node, document), Equals("number"));
      AssertThat(ts_node_type(false_node, document), Equals("false"));
      AssertThat(ts_node_type(object_node, document), Equals("object"));

      AssertThat(ts_node_start_byte(number_node), Equals(number_index));
      AssertThat(ts_node_end_byte(number_node), Equals(number_end_index));
      AssertThat(ts_node_start_char(number_node), Equals(number_index));
      AssertThat(ts_node_end_char(number_node), Equals(number_end_index));
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

      AssertThat(ts_node_type(pair_node, document), Equals("pair"));
      AssertThat(ts_node_start_byte(pair_node), Equals(string_index));
      AssertThat(ts_node_end_byte(pair_node), Equals(null_end_index));
      AssertThat(ts_node_start_point(pair_node), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(pair_node), Equals<TSPoint>({ 6, 13 }));
      AssertThat(ts_node_named_child_count(pair_node), Equals<size_t>(2));

      TSNode string_node = ts_node_named_child(pair_node, 0);
      TSNode null_node = ts_node_named_child(pair_node, 1);

      AssertThat(ts_node_type(string_node, document), Equals("string"));
      AssertThat(ts_node_type(null_node, document), Equals("null"));

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
      AssertThat(ts_node_parent(number_node), Equals(array_node));
      AssertThat(ts_node_parent(false_node), Equals(array_node));
      AssertThat(ts_node_parent(object_node), Equals(array_node));
      AssertThat(ts_node_parent(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("symbols()", [&]() {
    it("returns an iterator that yields each of the node's symbols", [&]() {
      const TSLanguage *language = ts_document_language(document);

      TSNode false_node = ts_node_descendant_for_char_range(array_node, false_index, false_index + 1);
      TSSymbolIterator iterator = ts_node_symbols(false_node);
      AssertThat(iterator.done, Equals(false));
      AssertThat(ts_language_symbol_name(language, iterator.value), Equals("false"));

      ts_symbol_iterator_next(&iterator);
      AssertThat(iterator.done, Equals(false));
      AssertThat(ts_language_symbol_name(language, iterator.value), Equals("_value"));

      ts_symbol_iterator_next(&iterator);
      AssertThat(iterator.done, Equals(true));

      TSNode comma_node = ts_node_descendant_for_char_range(array_node, number_end_index, number_end_index);
      iterator = ts_node_symbols(comma_node);
      AssertThat(iterator.done, Equals(false));
      AssertThat(ts_language_symbol_name(language, iterator.value), Equals(","));

      ts_symbol_iterator_next(&iterator);
      AssertThat(iterator.done, Equals(true));
    });
  });

  describe("child_count(), child(i)", [&]() {
    it("returns the child node at the given index, including anonymous nodes", [&]() {
      AssertThat(ts_node_child_count(array_node), Equals<size_t>(7));
      TSNode child1 = ts_node_child(array_node, 0);
      TSNode child2 = ts_node_child(array_node, 1);
      TSNode child3 = ts_node_child(array_node, 2);
      TSNode child4 = ts_node_child(array_node, 3);
      TSNode child5 = ts_node_child(array_node, 4);
      TSNode child6 = ts_node_child(array_node, 5);
      TSNode child7 = ts_node_child(array_node, 6);

      AssertThat(ts_node_type(array_node, document), Equals("array"));
      AssertThat(ts_node_type(child1, document), Equals("["));
      AssertThat(ts_node_type(child2, document), Equals("number"));
      AssertThat(ts_node_type(child3, document), Equals(","));
      AssertThat(ts_node_type(child4, document), Equals("false"));
      AssertThat(ts_node_type(child5, document), Equals(","));
      AssertThat(ts_node_type(child6, document), Equals("object"));
      AssertThat(ts_node_type(child7, document), Equals("]"));

      AssertThat(ts_node_is_named(array_node), IsTrue());
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

      AssertThat(ts_node_type(left_brace, document), Equals("{"));
      AssertThat(ts_node_type(pair, document), Equals("pair"));
      AssertThat(ts_node_type(right_brace, document), Equals("}"));

      AssertThat(ts_node_type(grandchild2, document), Equals("string"));
      AssertThat(ts_node_type(grandchild3, document), Equals(":"));
      AssertThat(ts_node_type(grandchild4, document), Equals("null"));

      AssertThat(ts_node_parent(grandchild2), Equals(pair));
      AssertThat(ts_node_parent(grandchild3), Equals(pair));
      AssertThat(ts_node_parent(grandchild4), Equals(pair));
      AssertThat(ts_node_parent(left_brace), Equals(child6));
      AssertThat(ts_node_parent(pair), Equals(child6));
      AssertThat(ts_node_parent(right_brace), Equals(child6));
      AssertThat(ts_node_parent(child1), Equals(array_node));
      AssertThat(ts_node_parent(child2), Equals(array_node));
      AssertThat(ts_node_parent(child3), Equals(array_node));
      AssertThat(ts_node_parent(child4), Equals(array_node));
      AssertThat(ts_node_parent(child5), Equals(array_node));
      AssertThat(ts_node_parent(child6), Equals(array_node));
      AssertThat(ts_node_parent(child7), Equals(array_node));
      AssertThat(ts_node_parent(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("next_sibling(), prev_sibling()", [&]() {
    it("returns the node's next and previous sibling, including anonymous nodes", [&]() {
      TSNode bracket_node1 = ts_node_child(array_node, 0);
      TSNode number_node = ts_node_child(array_node, 1);
      TSNode array_comma_node1 = ts_node_child(array_node, 2);
      TSNode false_node = ts_node_child(array_node, 3);
      TSNode array_comma_node2 = ts_node_child(array_node, 4);
      TSNode object_node = ts_node_child(array_node, 5);
      TSNode brace_node1 = ts_node_child(object_node, 0);
      TSNode pair_node = ts_node_child(object_node, 1);
      TSNode string_node = ts_node_child(pair_node, 0);
      TSNode colon_node = ts_node_child(pair_node, 1);
      TSNode null_node = ts_node_child(pair_node, 2);
      TSNode brace_node2 = ts_node_child(object_node, 2);
      TSNode bracket_node2 = ts_node_child(array_node, 6);

      AssertThat(ts_node_next_sibling(bracket_node1), Equals(number_node));
      AssertThat(ts_node_next_sibling(number_node), Equals(array_comma_node1));
      AssertThat(ts_node_next_sibling(array_comma_node1), Equals(false_node));
      AssertThat(ts_node_next_sibling(false_node), Equals(array_comma_node2));
      AssertThat(ts_node_next_sibling(array_comma_node2), Equals(object_node));
      AssertThat(ts_node_next_sibling(object_node), Equals(bracket_node2));
      AssertThat(ts_node_next_sibling(bracket_node2).data, Equals<void *>(nullptr));

      AssertThat(ts_node_prev_sibling(bracket_node1).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_sibling(number_node), Equals(bracket_node1));
      AssertThat(ts_node_prev_sibling(array_comma_node1), Equals(number_node));
      AssertThat(ts_node_prev_sibling(false_node), Equals(array_comma_node1));
      AssertThat(ts_node_prev_sibling(array_comma_node2), Equals(false_node));
      AssertThat(ts_node_prev_sibling(object_node), Equals(array_comma_node2));
      AssertThat(ts_node_prev_sibling(bracket_node2), Equals(object_node));

      AssertThat(ts_node_next_sibling(brace_node1), Equals(pair_node));
      AssertThat(ts_node_next_sibling(pair_node), Equals(brace_node2));
      AssertThat(ts_node_next_sibling(brace_node2).data, Equals<void *>(nullptr));

      AssertThat(ts_node_prev_sibling(brace_node1).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_sibling(pair_node), Equals(brace_node1));
      AssertThat(ts_node_prev_sibling(brace_node2), Equals(pair_node));

      AssertThat(ts_node_next_sibling(string_node), Equals(colon_node));
      AssertThat(ts_node_next_sibling(colon_node), Equals(null_node));
      AssertThat(ts_node_next_sibling(null_node).data, Equals<void *>(nullptr));

      AssertThat(ts_node_prev_sibling(string_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_sibling(colon_node), Equals(string_node));
      AssertThat(ts_node_prev_sibling(null_node), Equals(colon_node));
    });

    it("returns null when the node has no parent", [&]() {
      AssertThat(ts_node_next_named_sibling(array_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_named_sibling(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("next_named_sibling(), prev_named_sibling()", [&]() {
    it("returns the node's next and previous siblings", [&]() {
      TSNode number_node = ts_node_named_child(array_node, 0);
      TSNode false_node = ts_node_named_child(array_node, 1);
      TSNode object_node = ts_node_named_child(array_node, 2);
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
      AssertThat(ts_node_next_named_sibling(array_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_named_sibling(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("named_descendant_for_char_range(start, end)", [&]() {
    describe("when there is a leaf node that spans the given range exactly", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_named_descendant_for_char_range(array_node, string_index, string_end_index - 1);
        AssertThat(ts_node_type(leaf, document), Equals("string"));
        AssertThat(ts_node_start_byte(leaf), Equals(string_index));
        AssertThat(ts_node_end_byte(leaf), Equals(string_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 6, 7 }));

        leaf = ts_node_named_descendant_for_char_range(array_node, number_index, number_end_index - 1);
        AssertThat(ts_node_type(leaf, document), Equals("number"));
        AssertThat(ts_node_start_byte(leaf), Equals(number_index));
        AssertThat(ts_node_end_byte(leaf), Equals(number_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 3, 2 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 3, 5 }));
      });
    });

    describe("when there is a leaf node that extends beyond the given range", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_named_descendant_for_char_range(array_node, string_index, string_index + 1);
        AssertThat(ts_node_type(leaf, document), Equals("string"));
        AssertThat(ts_node_start_byte(leaf), Equals(string_index));
        AssertThat(ts_node_end_byte(leaf), Equals(string_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 6, 7 }));

        leaf = ts_node_named_descendant_for_char_range(array_node, string_index + 1, string_index + 2);
        AssertThat(ts_node_type(leaf, document), Equals("string"));
        AssertThat(ts_node_start_byte(leaf), Equals(string_index));
        AssertThat(ts_node_end_byte(leaf), Equals(string_end_index));
        AssertThat(ts_node_start_point(leaf), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(leaf), Equals<TSPoint>({ 6, 7 }));
      });
    });

    describe("when there is no leaf node that spans the given range", [&]() {
      it("returns the smallest node that does span the range", [&]() {
        TSNode pair_node = ts_node_named_descendant_for_char_range(array_node, string_index, string_index + 3);
        AssertThat(ts_node_type(pair_node, document), Equals("pair"));
        AssertThat(ts_node_start_byte(pair_node), Equals(string_index));
        AssertThat(ts_node_end_byte(pair_node), Equals(null_end_index));
        AssertThat(ts_node_start_point(pair_node), Equals<TSPoint>({ 6, 4 }));
        AssertThat(ts_node_end_point(pair_node), Equals<TSPoint>({ 6, 13 }));
      });

      it("does not return invisible nodes (repeats)", [&]() {
        TSNode node = ts_node_named_descendant_for_char_range(array_node, number_end_index, number_end_index + 1);
        AssertThat(ts_node_type(node, document), Equals("array"));
        AssertThat(ts_node_start_byte(node), Equals(array_index));
        AssertThat(ts_node_end_byte(node), Equals(array_end_index));
        AssertThat(ts_node_start_point(node), Equals<TSPoint>({ 2, 0 }));
        AssertThat(ts_node_end_point(node), Equals<TSPoint>({ 8, 1 }));
      });
    });
  });

  describe("descendant_for_char_range(start, end)", [&]() {
    it("returns the smallest node that spans the given range", [&]() {
      TSNode node1 = ts_node_descendant_for_char_range(array_node, colon_index, colon_index);
      AssertThat(ts_node_type(node1, document), Equals(":"));
      AssertThat(ts_node_start_byte(node1), Equals(colon_index));
      AssertThat(ts_node_end_byte(node1), Equals(colon_index + 1));
      AssertThat(ts_node_start_point(node1), Equals<TSPoint>({ 6, 7 }));
      AssertThat(ts_node_end_point(node1), Equals<TSPoint>({ 6, 8 }));

      TSNode node2 = ts_node_descendant_for_char_range(array_node, string_index + 2, string_index + 4);
      AssertThat(ts_node_type(node2, document), Equals("pair"));
      AssertThat(ts_node_start_byte(node2), Equals(string_index));
      AssertThat(ts_node_end_byte(node2), Equals(null_end_index));
      AssertThat(ts_node_start_point(node2), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(node2), Equals<TSPoint>({ 6, 13 }));
    });
  });

  describe("descendant_for_byte_range(start, end)", [&]() {
    it("returns the smallest concrete node that spans the given range", [&]() {
      ts_document_set_input_string(document, "[\"αβγδ\", \"αβγδ\"]");
      ts_document_parse(document);
      TSNode array_node = ts_document_root_node(document);

      TSNode node1 = ts_node_descendant_for_char_range(array_node, 7, 7);
      AssertThat(ts_node_type(node1, document), Equals(","));

      TSNode node2 = ts_node_descendant_for_byte_range(array_node, 6, 10);
      AssertThat(ts_node_type(node2, document), Equals("string"));
      AssertThat(ts_node_start_byte(node2), Equals<size_t>(1));
      AssertThat(ts_node_end_byte(node2), Equals<size_t>(11));
    });
  });

  describe("descendant_for_point_range(start, end)", [&]() {
    it("returns the smallest concrete node that spans the given range", [&]() {
      TSNode node1 = ts_node_descendant_for_point_range(array_node, {6, 7}, {6, 7});
      AssertThat(ts_node_type(node1, document), Equals(":"));
      AssertThat(ts_node_start_byte(node1), Equals(colon_index));
      AssertThat(ts_node_end_byte(node1), Equals(colon_index + 1));
      AssertThat(ts_node_start_point(node1), Equals<TSPoint>({ 6, 7 }));
      AssertThat(ts_node_end_point(node1), Equals<TSPoint>({ 6, 8 }));

      TSNode node2 = ts_node_descendant_for_point_range(array_node, {6, 6}, {6, 8});
      AssertThat(ts_node_type(node2, document), Equals("pair"));
      AssertThat(ts_node_start_byte(node2), Equals(string_index));
      AssertThat(ts_node_end_byte(node2), Equals(null_end_index));
      AssertThat(ts_node_start_point(node2), Equals<TSPoint>({ 6, 4 }));
      AssertThat(ts_node_end_point(node2), Equals<TSPoint>({ 6, 13 }));
    });
  });
});

END_TEST
