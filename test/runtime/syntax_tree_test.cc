#include "test_helper.h"
#include "helpers/record_alloc.h"
#include "runtime/alloc.h"
#include "runtime/syntax_tree.h"
#include "helpers/random_helpers.h"
#include "helpers/point_helpers.h"

ostream &operator<<(ostream &stream, const TSNode2 &node) {
  stream << "{index: " << node.index << ", symbol: " << ts_node2_symbol(&node) << "}";
  return stream;
}

static TSLanguage test_language() {
  static const char *symbol_names[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten"
  };

  static const TSSymbolMetadata symbol_metadata[] = {
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
    {true, true},
  };

  TSLanguage result;
  result.symbol_names = symbol_names;
  result.symbol_metadata = symbol_metadata;
  return result;
};

START_TEST

describe("SyntaxTree", [&]() {
  TSLanguage language = test_language();

  before_each([&]() {
    record_alloc::start();
  });

  after_each([&]() {
    TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  describe("node_list_to_tree()", [&]() {
    it("can construct a tree out of a sequence of individual nodes", [&]() {
      TREE_BRANCHING_FACTOR = 3;

      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, 1, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 2, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 3, 2);
      ts_node_list_push_leaf(&list, 4, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 5, 2);
      ts_node_list_push_leaf(&list, 6, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 7, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 8, 3);
      SyntaxTree *tree = ts_node_list_to_tree(&list, &language, NULL);

      TSNode2 root = ts_syntax_tree_root_node(tree);
      AssertThat(ts_node2_symbol(&root), Equals(8u));
      AssertThat(ts_node2_child_count(&root), Equals(3u));

      TSNode2 child1 = ts_node2_child(&root, 0);
      AssertThat(ts_node2_symbol(&child1), Equals(5u));
      AssertThat(ts_node2_child_count(&child1), Equals(2u));

      TSNode2 child2 = ts_node2_child(&root, 1);
      AssertThat(ts_node2_symbol(&child2), Equals(6u));
      AssertThat(ts_node2_child_count(&child2), Equals(0u));

      TSNode2 child3 = ts_node2_child(&root, 2);
      AssertThat(ts_node2_symbol(&child3), Equals(7u));
      AssertThat(ts_node2_child_count(&child3), Equals(0u));

      AssertThat(ts_node2_parent(&child1), Equals(root));
      AssertThat(ts_node2_parent(&child2), Equals(root));
      AssertThat(ts_node2_parent(&child3), Equals(root));

      ts_syntax_tree_delete(tree);
    });

    it("can construct a tree by reusing parts of an existing tree", [&]() {
      TREE_BRANCHING_FACTOR = 3;

      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, 1, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 2, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 3, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 4, 2);
      ts_node_list_push_leaf(&list, 5, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 6, 3);
      SyntaxTree *tree1 = ts_node_list_to_tree(&list, &language, NULL);

      TSNode2 root1 = ts_syntax_tree_root_node(tree1);
      TSNode2 node_to_reuse = ts_node2_child(&root1, 1);
      AssertThat(ts_node2_child_count(&node_to_reuse), Equals(2u));

      list = ts_node_list_new();
      ts_node_list_push_leaf(&list, 11, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 12, length_zero(), {1, {0, 1}});
      ts_node_list_reuse(&list, node_to_reuse);
      ts_node_list_push_leaf(&list, 15, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 6, 4);
      SyntaxTree *tree2 = ts_node_list_to_tree(&list, &language, tree1);

      TSNode2 root2 = ts_syntax_tree_root_node(tree2);
      AssertThat(ts_node2_symbol(&root2), Equals(6u));
      AssertThat(ts_node2_child_count(&root2), Equals(4u));

      TSNode2 child2 = ts_node2_child(&root2, 2);
      AssertThat(ts_node2_symbol(&child2), Equals(4u));
      AssertThat(ts_node2_child_count(&child2), Equals(2u));
      AssertThat(ts_node2_parent(&child2), Equals(root2));

      ts_syntax_tree_delete(tree1);
      ts_syntax_tree_delete(tree2);
    });

    it("does not mutate nodes in the existing tree when reusing them", [&]() {
      TREE_BRANCHING_FACTOR = 3;

      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, 1, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 2, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 3, 2);
      ts_node_list_push_leaf(&list, 4, length_zero(), {1, {0, 1}});
      ts_node_list_push_leaf(&list, 5, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 6, 3);
      ts_node_list_push_parent(&list, 7, 1);
      SyntaxTree *tree1 = ts_node_list_to_tree(&list, &language, NULL);

      TSNode2 root1 = ts_syntax_tree_root_node(tree1);
      TSNode2 child1 = ts_node2_child(&root1, 0);
      TSNode2 grandchild1 = ts_node2_child(&child1, 0);
      AssertThat(ts_node2_symbol(&child1), Equals(6u));
      AssertThat(ts_node2_symbol(&grandchild1), Equals(3u));
      AssertThat(ts_node2_child_count(&grandchild1), Equals(2u));
      AssertThat(ts_node2_parent(&grandchild1), Equals(child1));

      // The reused node and its children occupy an entire leaf in the syntax tree,
      // but the entire leaf cannot be reused because the reused node itself must
      // be copied so that its contextual fields like `next_sibling_node_count`
      // can be updated.
      list = ts_node_list_new();
      ts_node_list_reuse(&list, grandchild1);
      ts_node_list_push_leaf(&list, 4, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 14, 1);
      ts_node_list_push_leaf(&list, 5, length_zero(), {1, {0, 1}});
      ts_node_list_push_parent(&list, 15, 1);
      ts_node_list_push_parent(&list, 6, 3);
      ts_node_list_push_parent(&list, 7, 1);
      SyntaxTree *tree2 = ts_node_list_to_tree(&list, &language, tree1);

      TSNode2 root2 = ts_syntax_tree_root_node(tree2);
      TSNode2 child2 = ts_node2_child(&root2, 0);
      TSNode2 grandchild2 = ts_node2_child(&child2, 0);
      AssertThat(ts_node2_symbol(&child2), Equals(6u));
      AssertThat(ts_node2_symbol(&grandchild2), Equals(3u));
      AssertThat(ts_node2_child_count(&grandchild2), Equals(2u));
      AssertThat(ts_node2_parent(&grandchild2), Equals(child2));
      AssertThat(ts_node2_parent(&grandchild1), Equals(child1));

      ts_syntax_tree_delete(tree1);
      ts_syntax_tree_delete(tree2);
    });
  });

});

END_TEST

bool operator==(const TSNode2 &left, const TSNode2 &right) {
  return (
    left.index == right.index &&
    ts_node2_symbol(&left) == ts_node2_symbol(&right)
  );
}
