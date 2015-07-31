#include "runtime/runtime_spec_helper.h"

extern "C" TSLanguage * ts_language_json();

START_TEST

describe("Node", []() {
  TSDocument *document;
  TSNode root;

  before_each([&]() {
    document = ts_document_make();
    ts_document_set_language(document, ts_language_json());
    ts_document_set_input_string(document, "  [123, false, {\"x\": null}]");
    root = ts_document_root_node(document);
    AssertThat(ts_node_string(root, document), Equals(
      "(DOCUMENT (array "
        "(number) "
        "(false) "
        "(object (string) (null))))"));
  });

  after_each([&]() {
    ts_document_free(document);
  });

  describe("child_count()", [&]() {
    it("returns the number of visible child nodes", [&]() {
      TSNode array = ts_node_child(root, 0);
      AssertThat(ts_node_child_count(array), Equals<size_t>(3));
    });
  });

  describe("child(i)", [&]() {
    it("returns the child node at the given index", [&]() {
      TSNode parent = ts_node_child(root, 0);
      TSNode child1 = ts_node_child(parent, 0);
      TSNode child2 = ts_node_child(parent, 1);
      TSNode child3 = ts_node_child(parent, 2);

      AssertThat(ts_node_name(parent, document), Equals("array"));
      AssertThat(ts_node_name(child1, document), Equals("number"));
      AssertThat(ts_node_name(child2, document), Equals("false"));
      AssertThat(ts_node_name(child3, document), Equals("object"));

      AssertThat(ts_node_pos(parent).bytes, Equals<size_t>(2));
      AssertThat(ts_node_size(parent).bytes, Equals<size_t>(25));

      AssertThat(ts_node_pos(child1).bytes, Equals<size_t>(3));
      AssertThat(ts_node_size(child1).bytes, Equals<size_t>(3));

      AssertThat(ts_node_pos(child2).bytes, Equals<size_t>(8));
      AssertThat(ts_node_size(child2).bytes, Equals<size_t>(5));

      AssertThat(ts_node_pos(child3).bytes, Equals<size_t>(15));
      AssertThat(ts_node_size(child3).bytes, Equals<size_t>(11));
    });
  });

  describe("parent()", [&]() {
    it("returns the node's parent node", [&]() {
      TSNode array = ts_node_child(root, 0);
      TSNode child1 = ts_node_child(array, 0);
      TSNode child2 = ts_node_child(array, 1);
      TSNode child3 = ts_node_child(array, 2);

      AssertThat(ts_node_parent(child1), Equals(array));
      AssertThat(ts_node_parent(child2), Equals(array));
      AssertThat(ts_node_parent(child3), Equals(array));
      AssertThat(ts_node_parent(array), Equals(root));
    });

    it("returns null if the node has no parent", [&]() {
      AssertThat(ts_node_parent(root).data, Equals<void *>(nullptr));
    });
  });

  describe("next_sibling() and prev_sibling()", [&]() {
    it("returns the node's next and previous siblings", [&]() {
      TSNode array = ts_node_child(root, 0);
      TSNode number1 = ts_node_child(array, 0);
      TSNode number2 = ts_node_child(array, 1);
      TSNode number3 = ts_node_child(array, 2);

      AssertThat(ts_node_next_sibling(number1), Equals(number2));
      AssertThat(ts_node_next_sibling(number2), Equals(number3));
      AssertThat(ts_node_prev_sibling(number3), Equals(number2));
      AssertThat(ts_node_prev_sibling(number2), Equals(number1));
    });

    it("returns null when the node has no parent", [&]() {
      TSNode array = ts_node_child(root, 0);
      AssertThat(ts_node_next_sibling(root).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_sibling(root).data, Equals<void *>(nullptr));
      AssertThat(ts_node_next_sibling(array).data, Equals<void *>(nullptr));
      AssertThat(ts_node_prev_sibling(array).data, Equals<void *>(nullptr));
    });
  });

  describe("find_for_range(start, end)", [&]() {
    describe("when there is a leaf node that spans the given range exactly", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_find_for_range(root, 16, 18);
        AssertThat(ts_node_name(leaf, document), Equals("string"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(16));
      });
    });

    describe("when there is a leaf node that extends beyond the given range", [&]() {
      it("returns that leaf node", [&]() {
        TSNode leaf = ts_node_find_for_range(root, 16, 17);
        AssertThat(ts_node_name(leaf, document), Equals("string"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(16));

        leaf = ts_node_find_for_range(root, 17, 18);
        AssertThat(ts_node_name(leaf, document), Equals("string"));
        AssertThat(ts_node_size(leaf).bytes, Equals<size_t>(3));
        AssertThat(ts_node_pos(leaf).bytes, Equals<size_t>(16));
      });
    });

    describe("when there is no leaf node that spans the given range", [&]() {
      it("returns the smallest node that does span the range", [&]() {
        TSNode node = ts_node_find_for_range(root, 16, 19);
        AssertThat(ts_node_name(node, document), Equals("object"));
        AssertThat(ts_node_size(node).bytes, Equals<size_t>(11));
        AssertThat(ts_node_pos(node).bytes, Equals<size_t>(15));
      });
    });
  });

  describe("find_for_pos(position)", [&]() {
    it("finds the smallest node that spans the given position", [&]() {
      TSNode node = ts_node_find_for_pos(root, 10);
      AssertThat(ts_node_name(node, document), Equals("false"));
      AssertThat(ts_node_pos(node).bytes, Equals<size_t>(8));
      AssertThat(ts_node_size(node).bytes, Equals<size_t>(5));
    });
  });
});

END_TEST

bool operator==(const TSNode &left, const TSNode &right) {
  return ts_node_eq(left, right);
}
