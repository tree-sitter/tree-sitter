#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/tree_helpers.h"

extern "C" TSLanguage * ts_language_json();

START_TEST

describe("Node", []() {
  TSDocument *document;
  TSNode array_node;

  before_each([&]() {
    document = ts_document_make();
    ts_document_set_language(document, ts_language_json());
    ts_document_set_input_string(document, "  [123, false, {\"x\": null}]");
    ts_document_parse(document);

    array_node = ts_document_root_node(document);
    AssertThat(ts_node_string(array_node, document), Equals(
      "(array "
        "(number) "
        "(false) "
        "(object (string) (null)))"));
  });

  after_each([&]() {
    ts_document_free(document);
  });

  describe("child_count(), child(i)", [&]() {
    it("returns the named child node at the given index", [&]() {
      AssertThat(ts_node_named_child_count(array_node), Equals<size_t>(3));

      TSNode child1 = ts_node_named_child(array_node, 0);
      TSNode child2 = ts_node_named_child(array_node, 1);
      TSNode child3 = ts_node_named_child(array_node, 2);

      AssertThat(ts_node_name(array_node, document), Equals("array"));
      AssertThat(ts_node_name(child1, document), Equals("number"));
      AssertThat(ts_node_name(child2, document), Equals("false"));
      AssertThat(ts_node_name(child3, document), Equals("object"));

      AssertThat(ts_node_pos(array_node).bytes, Equals<size_t>(2));
      AssertThat(ts_node_size(array_node).bytes, Equals<size_t>(25));

      AssertThat(ts_node_start_point(array_node).row, Equals<size_t>(0));
      AssertThat(ts_node_start_point(array_node).column, Equals<size_t>(2));

      AssertThat(ts_node_end_point(array_node).row, Equals<size_t>(0));
      AssertThat(ts_node_end_point(array_node).column, Equals<size_t>(27));

      AssertThat(ts_node_pos(child1).bytes, Equals<size_t>(3));
      AssertThat(ts_node_size(child1).bytes, Equals<size_t>(3));

      AssertThat(ts_node_pos(child2).bytes, Equals<size_t>(8));
      AssertThat(ts_node_size(child2).bytes, Equals<size_t>(5));

      AssertThat(ts_node_pos(child3).bytes, Equals<size_t>(15));
      AssertThat(ts_node_size(child3).bytes, Equals<size_t>(11));

      AssertThat(ts_node_named_child_count(child3), Equals<size_t>(2));

      TSNode grandchild1 = ts_node_named_child(child3, 0);
      TSNode grandchild2 = ts_node_named_child(child3, 1);

      AssertThat(ts_node_name(grandchild1, document), Equals("string"));
      AssertThat(ts_node_name(grandchild2, document), Equals("null"));

      AssertThat(ts_node_parent(child1), Equals(array_node));
      AssertThat(ts_node_parent(child2), Equals(array_node));
      AssertThat(ts_node_parent(child3), Equals(array_node));
      AssertThat(ts_node_parent(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("concrete_child_count(), concrete_child(i)", [&]() {
    it("returns the child node at the given index, including anonymous nodes", [&]() {
      AssertThat(ts_node_child_count(array_node), Equals<size_t>(7));
      TSNode child1 = ts_node_child(array_node, 0);
      TSNode child2 = ts_node_child(array_node, 1);
      TSNode child3 = ts_node_child(array_node, 2);
      TSNode child4 = ts_node_child(array_node, 3);
      TSNode child5 = ts_node_child(array_node, 4);
      TSNode child6 = ts_node_child(array_node, 5);
      TSNode child7 = ts_node_child(array_node, 6);

      AssertThat(ts_node_name(array_node, document), Equals("array"));
      AssertThat(ts_node_name(child1, document), Equals("["));
      AssertThat(ts_node_name(child2, document), Equals("number"));
      AssertThat(ts_node_name(child3, document), Equals(","));
      AssertThat(ts_node_name(child4, document), Equals("false"));
      AssertThat(ts_node_name(child5, document), Equals(","));
      AssertThat(ts_node_name(child6, document), Equals("object"));
      AssertThat(ts_node_name(child7, document), Equals("]"));

      AssertThat(ts_node_is_named(array_node), IsTrue());
      AssertThat(ts_node_is_named(child1), IsFalse());
      AssertThat(ts_node_is_named(child2), IsTrue());
      AssertThat(ts_node_is_named(child3), IsFalse());
      AssertThat(ts_node_is_named(child4), IsTrue());
      AssertThat(ts_node_is_named(child5), IsFalse());
      AssertThat(ts_node_is_named(child6), IsTrue());
      AssertThat(ts_node_is_named(child7), IsFalse());

      AssertThat(ts_node_pos(child1).bytes, Equals<size_t>(2));
      AssertThat(ts_node_size(child1).bytes, Equals<size_t>(1));

      AssertThat(ts_node_pos(child3).bytes, Equals<size_t>(6));
      AssertThat(ts_node_size(child3).bytes, Equals<size_t>(1));

      AssertThat(ts_node_pos(child5).bytes, Equals<size_t>(13));
      AssertThat(ts_node_size(child5).bytes, Equals<size_t>(1));

      AssertThat(ts_node_pos(child7).bytes, Equals<size_t>(26));
      AssertThat(ts_node_size(child7).bytes, Equals<size_t>(1));

      AssertThat(ts_node_child_count(child6), Equals<size_t>(5))

      TSNode grandchild1 = ts_node_child(child6, 0);
      TSNode grandchild2 = ts_node_child(child6, 1);
      TSNode grandchild3 = ts_node_child(child6, 2);
      TSNode grandchild4 = ts_node_child(child6, 3);
      TSNode grandchild5 = ts_node_child(child6, 4);

      AssertThat(ts_node_name(grandchild1, document), Equals("{"));
      AssertThat(ts_node_name(grandchild2, document), Equals("string"));
      AssertThat(ts_node_name(grandchild3, document), Equals(":"));
      AssertThat(ts_node_name(grandchild4, document), Equals("null"));
      AssertThat(ts_node_name(grandchild5, document), Equals("}"));

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

  describe("next_concrete_sibling(), prev_concrete_sibling()", [&]() {
    it("returns the node's next and previous sibling, including anonymous nodes", [&]() {
      TSNode bracket_node1 = ts_node_child(array_node, 0);
      TSNode number_node = ts_node_child(array_node, 1);
      TSNode array_comma_node1 = ts_node_child(array_node, 2);
      TSNode false_node = ts_node_child(array_node, 3);
      TSNode array_comma_node2 = ts_node_child(array_node, 4);
      TSNode object_node = ts_node_child(array_node, 5);
      TSNode brace_node1 = ts_node_child(object_node, 0);
      TSNode string_node = ts_node_child(object_node, 1);
      TSNode colon_node = ts_node_child(object_node, 2);
      TSNode null_node = ts_node_child(object_node, 3);
      TSNode brace_node2 = ts_node_child(object_node, 4);
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

      AssertThat(ts_node_next_sibling(brace_node1), Equals(string_node));
      AssertThat(ts_node_next_sibling(string_node), Equals(colon_node));
      AssertThat(ts_node_next_sibling(colon_node), Equals(null_node));
      AssertThat(ts_node_next_sibling(null_node), Equals(brace_node2));
      AssertThat(ts_node_next_sibling(brace_node2).data, Equals<void *>(nullptr));

      AssertThat(ts_node_prev_sibling(brace_node1).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_sibling(string_node), Equals(brace_node1));
      AssertThat(ts_node_prev_sibling(colon_node), Equals(string_node));
      AssertThat(ts_node_prev_sibling(null_node), Equals(colon_node));
      AssertThat(ts_node_prev_sibling(brace_node2), Equals(null_node));
    });

    it("returns null when the node has no parent", [&]() {
      AssertThat(ts_node_next_named_sibling(array_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_named_sibling(array_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_next_named_sibling(array_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_named_sibling(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("next_concrete_sibling(), prev_concrete_sibling()", [&]() {
    it("returns the node's next and previous siblings", [&]() {
      TSNode number_node = ts_node_named_child(array_node, 0);
      TSNode false_node = ts_node_named_child(array_node, 1);
      TSNode object_node = ts_node_named_child(array_node, 2);
      TSNode string_node = ts_node_named_child(object_node, 0);
      TSNode null_node = ts_node_named_child(object_node, 1);

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
      AssertThat(ts_node_next_named_sibling(array_node).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_named_sibling(array_node).data, Equals<void *>(nullptr));
    });
  });

  describe("find_for_range(start, end)", [&]() {
    describe("when there is a leaf node that spans the given range exactly", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_named_descendent_for_range(array_node, 16, 18);
        AssertThat(ts_node_name(leaf, document), Equals("string"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(16));

        leaf = ts_node_named_descendent_for_range(array_node, 3, 5);
        AssertThat(ts_node_name(leaf, document), Equals("number"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(3));
      });
    });

    describe("when there is a leaf node that extends beyond the given range", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_named_descendent_for_range(array_node, 16, 17);
        AssertThat(ts_node_name(leaf, document), Equals("string"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(16));

        leaf = ts_node_named_descendent_for_range(array_node, 17, 18);
        AssertThat(ts_node_name(leaf, document), Equals("string"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(16));
      });
    });

    describe("when there is no leaf node that spans the given range", [&]() {
      it("returns the smallest node that does span the range", [&]() {
        TSNode node = ts_node_named_descendent_for_range(array_node, 16, 19);
        AssertThat(ts_node_name(node, document), Equals("object"));
        AssertThat(ts_node_size(node).bytes, Equals<size_t>(11));
        AssertThat(ts_node_pos(node).bytes, Equals<size_t>(15));
      });

      it("does not return invisible nodes (repeats)", [&]() {
        TSNode node = ts_node_named_descendent_for_range(array_node, 6, 7);
        AssertThat(ts_node_name(node, document), Equals("array"));
        AssertThat(ts_node_size(node).bytes, Equals<size_t>(25));
        AssertThat(ts_node_pos(node).bytes, Equals<size_t>(2));
      });
    });
  });

  describe("find_concrete_for_range(start, end)", [&]() {
    it("returns the smallest concrete node that spans the given range", [&]() {
      TSNode node1 = ts_node_descendent_for_range(array_node, 19, 19);
      AssertThat(ts_node_name(node1, document), Equals(":"));
      AssertThat(ts_node_pos(node1).bytes, Equals<size_t>(19));
      AssertThat(ts_node_size(node1).bytes, Equals<size_t>(1));

      TSNode node2 = ts_node_descendent_for_range(array_node, 18, 20);
      AssertThat(ts_node_name(node2, document), Equals("object"));
      AssertThat(ts_node_pos(node2).bytes, Equals<size_t>(15));
      AssertThat(ts_node_size(node2).bytes, Equals<size_t>(11));
    });
  });
});

END_TEST
