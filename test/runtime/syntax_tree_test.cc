#include "test_helper.h"
#include "helpers/record_alloc.h"
#include "runtime/alloc.h"
#include "runtime/syntax_tree.h"
#include "helpers/load_language.h"
#include "helpers/random_helpers.h"
#include "helpers/point_helpers.h"

ostream &operator<<(ostream &stream, const TSNode2 &node) {
  stream << "{index: " << node.index << ", symbol: " << ts_node2_symbol(&node) << "}";
  return stream;
}

static LeafNodeParams leaf(TSSymbol symbol, Length size) {
  LeafNodeParams result = {};
  result.symbol = symbol;
  result.size = size;
  return result;
}

START_TEST

describe("SyntaxTree", [&]() {
  const TSLanguage *language = get_dummy_language();

  before_each([&]() {
    record_alloc::start();
  });

  after_each([&]() {
    TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  describe("construction", [&]() {
    it("can construct a tree out of a sequence of individual nodes", [&]() {
      TREE_BRANCHING_FACTOR = 3;

      // (symbol-8
      //   (symbol-5)
      //     (symbol-4)
      //     (symbol-3 (symbol-1) (symbol-2)))
      //   (symbol-6)
      //   (symbol-7))
      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(1u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(2u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {3, 2});
      ts_node_list_push_leaf(&list, leaf(4u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {5, 2});
      ts_node_list_push_leaf(&list, leaf(6u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(7u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {8, 3});
      SyntaxTree *tree = ts_node_list_to_tree(&list, language, NULL);
      ts_syntax_tree_check_invariants(tree);

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

      // (symbol-6
      //   (symbol-1)
      //   (symbol-4 (symbol-2) (symbol-3))
      //   (symbol-5))
      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(1u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(2u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(3u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {4, 2});
      ts_node_list_push_leaf(&list, leaf(5u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {6, 3});
      SyntaxTree *tree1 = ts_node_list_to_tree(&list, language, NULL);
      ts_syntax_tree_check_invariants(tree1);

      TreeCursor cursor = ts_tree_cursor_new(tree1);
      ts_tree_cursor_descend(&cursor);
      ts_tree_cursor_advance(&cursor);

      TSNode2 node_to_reuse = ts_tree_cursor_current_node(&cursor);
      AssertThat(ts_node2_symbol(&node_to_reuse), Equals(4u));
      AssertThat(ts_node2_child_count(&node_to_reuse), Equals(2u));

      // (symbol-6
      //   (symbol-11)
      //   (symbol-12)
      //   (symbol-4 (symbol-2) (symbol-3))
      //   (symbol-15))
      list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(11u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(12u, {1, {0, 1}}));
      ts_node_list_reuse(&list, &cursor);
      ts_node_list_push_leaf(&list, leaf(15u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {6, 4});
      SyntaxTree *tree2 = ts_node_list_to_tree(&list, language, tree1);
      ts_syntax_tree_check_invariants(tree2);

      TSNode2 root2 = ts_syntax_tree_root_node(tree2);
      AssertThat(ts_node2_symbol(&root2), Equals(6u));
      AssertThat(ts_node2_child_count(&root2), Equals(4u));

      TSNode2 child2 = ts_node2_child(&root2, 2);
      AssertThat(ts_node2_symbol(&child2), Equals(4u));
      AssertThat(ts_node2_child_count(&child2), Equals(2u));
      AssertThat(ts_node2_parent(&child2), Equals(root2));

      ts_tree_cursor_delete(&cursor);
      ts_syntax_tree_delete(tree1);
      ts_syntax_tree_delete(tree2);
    });

    it("does not mutate nodes in the existing tree when reusing them", [&]() {
      TREE_BRANCHING_FACTOR = 3;

      // (symbol-7
      //   (symbol-6
      //     (symbol-3 (symbol-1) (symbol-2))
      //     (symbol-4)
      //     (symbol-5)))
      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(1u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(2u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {3, 2});
      ts_node_list_push_leaf(&list, leaf(4u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(5u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {6, 3});
      ts_node_list_push_parent(&list, {7, 1});
      SyntaxTree *tree1 = ts_node_list_to_tree(&list, language, NULL);

      TSNode2 root1 = ts_syntax_tree_root_node(tree1);
      TSNode2 child1 = ts_node2_child(&root1, 0);
      TSNode2 grandchild1 = ts_node2_child(&child1, 0);
      AssertThat(ts_node2_symbol(&child1), Equals(6u));
      AssertThat(ts_node2_symbol(&grandchild1), Equals(3u));
      AssertThat(ts_node2_child_count(&grandchild1), Equals(2u));
      AssertThat(ts_node2_parent(&grandchild1), Equals(child1));

      TreeCursor cursor = ts_tree_cursor_new(tree1);
      ts_tree_cursor_descend(&cursor);
      ts_tree_cursor_descend(&cursor);
      AssertThat(ts_tree_cursor_current_node(&cursor), Equals(grandchild1));

      // The reused node and its children occupy an entire leaf in the syntax tree,
      // but the entire leaf cannot be reused because the reused node itself must
      // be copied so that its contextual fields like `next_sibling_node_count`
      // can be updated.
      //
      // (symbol-7
      //   (symbol-6
      //     (symbol-3 (symbol-1) (symbol-2))
      //     (symbol-14 (symbol-4))
      //     (symbol-15 (symbol-5))))
      list = ts_node_list_new();
      ts_node_list_reuse(&list, &cursor);
      ts_node_list_push_leaf(&list, leaf(4u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {14, 1});
      ts_node_list_push_leaf(&list, leaf(5u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {15, 1});
      ts_node_list_push_parent(&list, {6, 3});
      ts_node_list_push_parent(&list, {7, 1});
      SyntaxTree *tree2 = ts_node_list_to_tree(&list, language, tree1);

      TSNode2 root2 = ts_syntax_tree_root_node(tree2);
      TSNode2 child2 = ts_node2_child(&root2, 0);
      TSNode2 grandchild2 = ts_node2_child(&child2, 0);
      AssertThat(ts_node2_symbol(&child2), Equals(6u));
      AssertThat(ts_node2_symbol(&grandchild2), Equals(3u));
      AssertThat(ts_node2_child_count(&grandchild2), Equals(2u));
      AssertThat(ts_node2_parent(&grandchild2), Equals(child2));
      AssertThat(ts_node2_parent(&grandchild1), Equals(child1));

      ts_tree_cursor_delete(&cursor);
      ts_syntax_tree_delete(tree1);
      ts_syntax_tree_delete(tree2);
    });
  });

  describe("breakdown", [&]() {
    it("removes the last parent node and identifies all of its children", [&]() {
      TREE_BRANCHING_FACTOR = 3;

      // (symbol-14
      //   (symbol-8
      //     (symbol-3 (symbol-1) (symbol-2))
      //     (symbol-6 (symbol-4) (symbol-5))
      //     (symbol-7))
      //   (symbol-9)
      //   (symbol-13 (symbol-10) (symbol-11) (symbol-12)))
      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(1u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(2u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {3u, 2});
      ts_node_list_push_leaf(&list, leaf(4u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(5u, {2, {0, 2}}));
      ts_node_list_push_parent(&list, {6u, 2});
      ts_node_list_push_leaf(&list, leaf(7u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {8u, 3});
      ts_node_list_push_leaf(&list, leaf(9u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(10u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(11u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(12u, {1, {0, 1}}));
      ts_node_list_push_parent(&list, {13u, 3});
      ts_node_list_push_parent(&list, {14u, 3});
      SyntaxTree *tree = ts_node_list_to_tree(&list, language, NULL);
      ts_syntax_tree_check_invariants(tree);

      TreeCursor cursor = ts_tree_cursor_new(tree);
      ts_tree_cursor_descend(&cursor);
      TSNode2 node_to_reuse = ts_tree_cursor_current_node(&cursor);
      AssertThat(ts_node2_symbol(&node_to_reuse), Equals(8u));
      AssertThat(ts_node2_child_count(&node_to_reuse), Equals(3u));

      list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(12u, {1, {0, 1}}));
      ts_node_list_push_leaf(&list, leaf(13u, {1, {0, 1}}));
      ts_node_list_reuse(&list, &cursor);

      BreakdownResult children = array_new();
      NodeListIterator list_iter = ts_node_list_iterator_new();
      ts_node_list_breakdown(&list, &list_iter, &children);

      AssertThat(children.size, Equals(3u));
      AssertThat(children.contents[0].symbol, Equals(3u));
      AssertThat(children.contents[1].symbol, Equals(6u));
      AssertThat(children.contents[2].symbol, Equals(7u));
      AssertThat(children.contents[0].size, Equals<Length>({2, {0, 2}}));
      AssertThat(children.contents[1].size, Equals<Length>({3, {0, 3}}));
      AssertThat(children.contents[2].size, Equals<Length>({1, {0, 1}}));

      array_delete(&children);
      ts_node_list_delete(&list);
      ts_node_list_iterator_delete(&list_iter);
      ts_syntax_tree_delete(tree);
      ts_tree_cursor_delete(&cursor);
    });
  });

  describe("editing", [&]() {
    SyntaxTree *tree = nullptr;

    before_each([&]() {
      TREE_BRANCHING_FACTOR = 3;

      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, {2, {2, {0, 2}}, {3, {0, 3}}, false});
      ts_node_list_push_leaf(&list, {3, {2, {0, 2}}, {3, {0, 3}}, false});
      ts_node_list_push_leaf(&list, {4, {2, {0, 2}}, {3, {0, 3}}, false});
      ts_node_list_push_parent(&list, {1, 3});
      tree = ts_node_list_to_tree(&list, language, NULL);
      ts_syntax_tree_check_invariants(tree);
    });

    describe("edits within a tree's padding", [&]() {
      it("resizes the padding of the tree and its leftmost descendants", [&]() {
        TSInputEdit edit;
        edit.start_byte = 1;
        edit.bytes_removed = 0;
        edit.bytes_added = 1;
        edit.start_point = {0, 1};
        edit.extent_removed = {0, 0};
        edit.extent_added = {0, 1};
        tree = ts_syntax_tree_edit(tree, edit);
        ts_syntax_tree_check_invariants(tree);

        TSNode2 root = ts_syntax_tree_root_node(tree);
        AssertThat(ts_node2_has_changes(&root), IsTrue());
        AssertThat(ts_node2_start_point(&root), Equals<TSPoint>({0, 3}));
        AssertThat(ts_node2_end_point(&root), Equals<TSPoint>({0, 16}));

        TSNode2 child1 = ts_node2_child(&root, 0);
        AssertThat(ts_node2_has_changes(&child1), IsTrue());
        AssertThat(ts_node2_start_point(&child1), Equals<TSPoint>({0, 3}));
        AssertThat(ts_node2_end_point(&child1), Equals<TSPoint>({0, 6}));

        TSNode2 child2 = ts_node2_child(&root, 1);
        AssertThat(ts_node2_has_changes(&child2), IsFalse());
        AssertThat(ts_node2_start_point(&child2), Equals<TSPoint>({0, 8}));
        AssertThat(ts_node2_end_point(&child2), Equals<TSPoint>({0, 11}));

        ts_syntax_tree_delete(tree);
      });
    });

    describe("edits that start in a tree's padding but extend into its content", [&]() {
      it("shrinks the content to compensate for the expanded padding", [&]() {
        TSInputEdit edit;
        edit.start_byte = 1;
        edit.bytes_removed = 3;
        edit.bytes_added = 4;
        edit.start_point = {0, 1};
        edit.extent_removed = {0, 3};
        edit.extent_added = {0, 4};
        tree = ts_syntax_tree_edit(tree, edit);
        ts_syntax_tree_check_invariants(tree);

        TSNode2 root = ts_syntax_tree_root_node(tree);
        AssertThat(ts_node2_has_changes(&root), IsTrue());
        AssertThat(ts_node2_start_point(&root), Equals<TSPoint>({0, 5}));
        AssertThat(ts_node2_end_point(&root), Equals<TSPoint>({0, 16}));

        TSNode2 child1 = ts_node2_child(&root, 0);
        AssertThat(ts_node2_has_changes(&child1), IsTrue());
        AssertThat(ts_node2_start_point(&child1), Equals<TSPoint>({0, 5}));
        AssertThat(ts_node2_end_point(&child1), Equals<TSPoint>({0, 6}));

        ts_syntax_tree_delete(tree);
      });
    });

    describe("insertions at the edge of a tree's padding", [&]() {
      it("expands the tree's padding", [&]() {
        TSInputEdit edit;
        edit.start_byte = 2;
        edit.bytes_removed = 0;
        edit.bytes_added = 2;
        edit.start_point = {0, 2};
        edit.extent_removed = {0, 0};
        edit.extent_added = {0, 2};
        tree = ts_syntax_tree_edit(tree, edit);
        ts_syntax_tree_check_invariants(tree);

        TSNode2 root = ts_syntax_tree_root_node(tree);
        AssertThat(ts_node2_has_changes(&root), IsTrue());
        AssertThat(ts_node2_start_point(&root), Equals<TSPoint>({0, 4}));
        AssertThat(ts_node2_end_point(&root), Equals<TSPoint>({0, 17}));

        TSNode2 child1 = ts_node2_child(&root, 0);
        AssertThat(ts_node2_has_changes(&child1), IsTrue());
        AssertThat(ts_node2_start_point(&child1), Equals<TSPoint>({0, 4}));
        AssertThat(ts_node2_end_point(&child1), Equals<TSPoint>({0, 7}));

        ts_syntax_tree_delete(tree);
      });
    });

    describe("replacements starting at the edge of a tree's padding", [&]() {
      it("resizes the content and not the padding", [&]() {
        TSInputEdit edit;
        edit.start_byte = 2;
        edit.bytes_removed = 2;
        edit.bytes_added = 5;
        edit.start_point = {0, 2};
        edit.extent_removed = {0, 2};
        edit.extent_added = {0, 5};
        tree = ts_syntax_tree_edit(tree, edit);
        ts_syntax_tree_check_invariants(tree);

        TSNode2 root = ts_syntax_tree_root_node(tree);
        AssertThat(ts_node2_has_changes(&root), IsTrue());
        AssertThat(ts_node2_start_point(&root), Equals<TSPoint>({0, 2}));
        AssertThat(ts_node2_end_point(&root), Equals<TSPoint>({0, 18}));

        TSNode2 child1 = ts_node2_child(&root, 0);
        AssertThat(ts_node2_has_changes(&child1), IsTrue());
        AssertThat(ts_node2_start_point(&child1), Equals<TSPoint>({0, 2}));
        AssertThat(ts_node2_end_point(&child1), Equals<TSPoint>({0, 8}));

        ts_syntax_tree_delete(tree);
      });
    });

    describe("deletions that span more than one child node", [&]() {
      it("shrinks subsequent child nodes", [&]() {
        TSInputEdit edit;
        edit.start_byte = 1;
        edit.bytes_removed = 10;
        edit.bytes_added = 3;
        edit.start_point = {0, 1};
        edit.extent_removed = {0, 10};
        edit.extent_added = {0, 3};
        tree = ts_syntax_tree_edit(tree, edit);
        ts_syntax_tree_check_invariants(tree);

        TSNode2 root = ts_syntax_tree_root_node(tree);
        AssertThat(ts_node2_has_changes(&root), IsTrue());
        AssertThat(ts_node2_start_point(&root), Equals<TSPoint>({0, 4}));
        AssertThat(ts_node2_end_point(&root), Equals<TSPoint>({0, 8}));

        TSNode2 child1 = ts_node2_child(&root, 0);
        AssertThat(ts_node2_has_changes(&child1), IsTrue());
        AssertThat(ts_node2_start_point(&child1), Equals<TSPoint>({0, 4}));
        AssertThat(ts_node2_end_point(&child1), Equals<TSPoint>({0, 4}));

        TSNode2 child2 = ts_node2_child(&root, 1);
        AssertThat(ts_node2_has_changes(&child2), IsTrue());
        AssertThat(ts_node2_start_point(&child2), Equals<TSPoint>({0, 4}));
        AssertThat(ts_node2_end_point(&child2), Equals<TSPoint>({0, 4}));

        TSNode2 child3 = ts_node2_child(&root, 2);
        AssertThat(ts_node2_has_changes(&child3), IsTrue());
        AssertThat(ts_node2_start_point(&child3), Equals<TSPoint>({0, 5}));
        AssertThat(ts_node2_end_point(&child3), Equals<TSPoint>({0, 8}));

        ts_syntax_tree_delete(tree);
      });
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
