#include "test_helper.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "runtime/tree.h"
#include "runtime/length.h"

void assert_consistent(const Tree *tree) {
  if (tree->child_count == 0)
    return;
  AssertThat(tree->children[0]->padding, Equals<Length>(tree->padding));

  Length total_children_size = length_zero();
  for (size_t i = 0; i < tree->child_count; i++) {
    Tree *child = tree->children[i];
    AssertThat(child->context.offset, Equals(total_children_size));
    assert_consistent(child);
    total_children_size = length_add(total_children_size, ts_tree_total_size(child));
  }

  AssertThat(total_children_size, Equals<Length>(ts_tree_total_size(tree)));
};

START_TEST

describe("Tree", []() {
  enum {
    symbol1 = 1,
    symbol2,
    symbol3,
    symbol4,
    symbol5,
    symbol6,
    symbol7,
    symbol8,
    symbol9,
  };

  TSSymbolMetadata visible = {true, true, false, true};
  TSSymbolMetadata invisible = {false, false, false, true};

  describe("make_leaf", [&]() {
    it("does not mark the tree as fragile", [&]() {
      Tree *tree = ts_tree_make_leaf(symbol1, {2, 1, {0, 1}}, {5, 4, {0, 4}}, visible);
      AssertThat(tree->fragile_left, IsFalse());
      AssertThat(tree->fragile_right, IsFalse());
    });
  });

  describe("make_error", [&]() {
    it("marks the tree as fragile", [&]() {
      Tree *error_tree = ts_tree_make_error(
        length_zero(),
        length_zero(),
        'z');

      AssertThat(error_tree->fragile_left, IsTrue());
      AssertThat(error_tree->fragile_right, IsTrue());

      ts_tree_release(error_tree);
    });
  });

  describe("make_node", [&]() {
    Tree *tree1, *tree2, *parent1;

    before_each([&]() {
      tree1 = ts_tree_make_leaf(symbol1, {2, 1, {0, 1}}, {5, 4, {0, 4}}, visible);
      tree2 = ts_tree_make_leaf(symbol2, {1, 1, {0, 1}}, {3, 3, {0, 3}}, visible);

      ts_tree_retain(tree1);
      ts_tree_retain(tree2);
      parent1 = ts_tree_make_node(symbol3, 2, tree_array({
        tree1,
        tree2,
      }), visible);
    });

    after_each([&]() {
      ts_tree_release(tree1);
      ts_tree_release(tree2);
      ts_tree_release(parent1);
    });

    it("computes its size and padding based on its child nodes", [&]() {
      AssertThat(parent1->size.bytes, Equals<size_t>(
        tree1->size.bytes + tree2->padding.bytes + tree2->size.bytes));
      AssertThat(parent1->size.chars, Equals<size_t>(
        tree1->size.chars + tree2->padding.chars + tree2->size.chars));

      AssertThat(parent1->padding.bytes, Equals<size_t>(tree1->padding.bytes));
      AssertThat(parent1->padding.chars, Equals<size_t>(tree1->padding.chars));
    });

    describe("when the first node is fragile on the left side", [&]() {
      Tree *parent;

      before_each([&]() {
        tree1->fragile_left = true;
        tree1->extra = true;

        ts_tree_retain(tree1);
        ts_tree_retain(tree2);
        parent = ts_tree_make_node(symbol3, 2, tree_array({
          tree1,
          tree2,
        }), visible);
      });

      after_each([&]() {
        ts_tree_release(parent);
      });

      it("records that it is fragile on the left side", [&]() {
        AssertThat(parent->fragile_left, IsTrue());
      });
    });

    describe("when the last node is fragile on the right side", [&]() {
      Tree *parent;

      before_each([&]() {
        tree2->fragile_right = true;
        tree2->extra = true;

        ts_tree_retain(tree1);
        ts_tree_retain(tree2);
        parent = ts_tree_make_node(symbol3, 2, tree_array({
          tree1,
          tree2,
        }), visible);
      });

      after_each([&]() {
        ts_tree_release(parent);
      });

      it("records that it is fragile on the right side", [&]() {
        AssertThat(parent->fragile_right, IsTrue());
      });
    });

    describe("when the outer nodes aren't fragile on their outer side", [&]() {
      Tree *parent;

      before_each([&]() {
        tree1->fragile_right = true;
        tree2->fragile_left = true;

        ts_tree_retain(tree1);
        ts_tree_retain(tree2);
        parent = ts_tree_make_node(symbol3, 2, tree_array({
          tree1,
          tree2,
        }), visible);
      });

      after_each([&]() {
        ts_tree_release(parent);
      });

      it("records that it is not fragile", [&]() {
        AssertThat(parent->fragile_left, IsFalse());
        AssertThat(parent->fragile_right, IsFalse());
      });
    });
  });

  describe("edit", [&]() {
    Tree *tree = nullptr;

    before_each([&]() {
      tree = ts_tree_make_node(symbol1, 3, tree_array({
        ts_tree_make_leaf(symbol2, {2, 2, {0, 2}}, {3, 3, {0, 3}}, visible),
        ts_tree_make_leaf(symbol3, {2, 2, {0, 2}}, {3, 3, {0, 3}}, visible),
        ts_tree_make_leaf(symbol4, {2, 2, {0, 2}}, {3, 3, {0, 3}}, visible),
      }), visible);

      AssertThat(tree->padding, Equals<Length>({2, 2, {0, 2}}));
      AssertThat(tree->size, Equals<Length>({13, 13, {0, 13}}));
    });

    after_each([&]() {
      ts_tree_release(tree);
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
        ts_tree_edit(tree, &edit);
        assert_consistent(tree);

        AssertThat(tree->has_changes, IsTrue());
        AssertThat(tree->padding, Equals<Length>({3, 0, {0, 3}}));
        AssertThat(tree->size, Equals<Length>({13, 13, {0, 13}}));

        AssertThat(tree->children[0]->has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<Length>({3, 0, {0, 3}}));
        AssertThat(tree->children[0]->size, Equals<Length>({3, 3, {0, 3}}));

        AssertThat(tree->children[1]->has_changes, IsFalse());
        AssertThat(tree->children[1]->padding, Equals<Length>({2, 2, {0, 2}}));
        AssertThat(tree->children[1]->size, Equals<Length>({3, 3, {0, 3}}));
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
        ts_tree_edit(tree, &edit);
        assert_consistent(tree);

        AssertThat(tree->has_changes, IsTrue());
        AssertThat(tree->padding, Equals<Length>({5, 0, {0, 5}}));
        AssertThat(tree->size, Equals<Length>({11, 0, {0, 11}}));

        AssertThat(tree->children[0]->has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<Length>({5, 0, {0, 5}}));
        AssertThat(tree->children[0]->size, Equals<Length>({1, 0, {0, 1}}));
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
        ts_tree_edit(tree, &edit);
        assert_consistent(tree);

        assert_consistent(tree);

        AssertThat(tree->has_changes, IsTrue());
        AssertThat(tree->padding, Equals<Length>({4, 0, {0, 4}}));
        AssertThat(tree->size, Equals<Length>({13, 13, {0, 13}}));

        AssertThat(tree->children[0]->has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<Length>({4, 0, {0, 4}}));
        AssertThat(tree->children[0]->size, Equals<Length>({3, 3, {0, 3}}));

        AssertThat(tree->children[1]->has_changes, IsFalse());
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
        ts_tree_edit(tree, &edit);
        assert_consistent(tree);

        AssertThat(tree->has_changes, IsTrue());
        AssertThat(tree->padding, Equals<Length>({2, 2, {0, 2}}));
        AssertThat(tree->size, Equals<Length>({16, 0, {0, 16}}));

        AssertThat(tree->children[0]->has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<Length>({2, 2, {0, 2}}));
        AssertThat(tree->children[0]->size, Equals<Length>({6, 0, {0, 6}}));

        AssertThat(tree->children[1]->has_changes, IsFalse());
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
        ts_tree_edit(tree, &edit);
        assert_consistent(tree);

        assert_consistent(tree);

        AssertThat(tree->has_changes, IsTrue());
        AssertThat(tree->padding, Equals<Length>({4, 0, {0, 4}}));
        AssertThat(tree->size, Equals<Length>({4, 0, {0, 4}}));

        AssertThat(tree->children[0]->has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<Length>({4, 0, {0, 4}}));
        AssertThat(tree->children[0]->size, Equals<Length>({0, 0, {0, 0}}));

        AssertThat(tree->children[1]->has_changes, IsTrue());
        AssertThat(tree->children[1]->padding, Equals<Length>({0, 0, {0, 0}}));
        AssertThat(tree->children[1]->size, Equals<Length>({0, 0, {0, 0}}));

        AssertThat(tree->children[2]->has_changes, IsTrue());
        AssertThat(tree->children[2]->padding, Equals<Length>({1, 0, {0, 1}}));
        AssertThat(tree->children[2]->size, Equals<Length>({3, 3, {0, 3}}));
      });
    });

    describe("edits within a tree's range of scanned bytes", [&]() {
      it("marks preceding trees as changed", [&]() {
        tree->children[0]->bytes_scanned = 7;

        TSInputEdit edit;
        edit.start_byte = 6;
        edit.bytes_removed = 1;
        edit.bytes_added = 1;
        edit.start_point = {0, 6};
        edit.extent_removed = {0, 1};
        edit.extent_added = {0, 1};
        ts_tree_edit(tree, &edit);
        assert_consistent(tree);

        AssertThat(tree->children[0]->has_changes, IsTrue());
      });
    });
  });

  describe("eq", [&]() {
    Tree *leaf;

    before_each([&]() {
      leaf = ts_tree_make_leaf(symbol1, {2, 1, {0, 1}}, {5, 4, {0, 4}}, visible);
    });

    after_each([&]() {
      ts_tree_release(leaf);
    });

    it("returns true for identical trees", [&]() {
      Tree *leaf_copy = ts_tree_make_leaf(symbol1, {2, 1, {1, 1}}, {5, 4, {1, 4}}, visible);
      AssertThat(ts_tree_eq(leaf, leaf_copy), IsTrue());

      Tree *parent = ts_tree_make_node(symbol2, 2, tree_array({
        leaf,
        leaf_copy,
      }), visible);
      ts_tree_retain(leaf);
      ts_tree_retain(leaf_copy);

      Tree *parent_copy = ts_tree_make_node(symbol2, 2, tree_array({
        leaf,
        leaf_copy,
      }), visible);
      ts_tree_retain(leaf);
      ts_tree_retain(leaf_copy);

      AssertThat(ts_tree_eq(parent, parent_copy), IsTrue());

      ts_tree_release(leaf_copy);
      ts_tree_release(parent);
      ts_tree_release(parent_copy);
    });

    it("returns false for trees with different symbols", [&]() {
      Tree *different_leaf = ts_tree_make_leaf(
        leaf->symbol + 1,
        leaf->padding,
        leaf->size,
        visible);

      AssertThat(ts_tree_eq(leaf, different_leaf), IsFalse());
      ts_tree_release(different_leaf);
    });

    it("returns false for trees with different options", [&]() {
      Tree *different_leaf = ts_tree_make_leaf(symbol1, leaf->padding, leaf->size, invisible);
      AssertThat(ts_tree_eq(leaf, different_leaf), IsFalse());
      ts_tree_release(different_leaf);
    });

    it("returns false for trees with different sizes", [&]() {
      Tree *different_leaf = ts_tree_make_leaf(symbol1, {2, 1, {0, 1}}, leaf->size, invisible);
      AssertThat(ts_tree_eq(leaf, different_leaf), IsFalse());
      ts_tree_release(different_leaf);

      different_leaf = ts_tree_make_leaf(symbol1, leaf->padding, {5, 4, {1, 10}}, invisible);
      AssertThat(ts_tree_eq(leaf, different_leaf), IsFalse());
      ts_tree_release(different_leaf);
    });

    it("returns false for trees with different children", [&]() {
      Tree *leaf2 = ts_tree_make_leaf(symbol2, {1, 1, {0, 1}}, {3, 3, {0, 3}}, visible);

      Tree *parent = ts_tree_make_node(symbol2, 2, tree_array({
        leaf,
        leaf2,
      }), visible);
      ts_tree_retain(leaf);
      ts_tree_retain(leaf2);

      Tree *different_parent = ts_tree_make_node(symbol2, 2, tree_array({
        leaf2,
        leaf,
      }), visible);
      ts_tree_retain(leaf2);
      ts_tree_retain(leaf);

      AssertThat(ts_tree_eq(different_parent, parent), IsFalse());
      AssertThat(ts_tree_eq(parent, different_parent), IsFalse());

      ts_tree_release(leaf2);
      ts_tree_release(parent);
      ts_tree_release(different_parent);
    });
  });

  describe("last_external_token_state", [&]() {
    Length padding = {1, 1, {0, 1}};
    Length size = {2, 2, {0, 2}};

    auto make_external = [](Tree *tree) {
      tree->has_external_tokens = true;
      tree->has_external_token_state = true;
      return tree;
    };

    it("returns the last serialized external token state in the given tree", [&]() {
      Tree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8, *tree9;

      tree1 = ts_tree_make_node(symbol1, 2, tree_array({
        (tree2 = ts_tree_make_node(symbol2, 3, tree_array({
          (tree3 = make_external(ts_tree_make_leaf(symbol3, padding, size, visible))),
          (tree4 = ts_tree_make_leaf(symbol4, padding, size, visible)),
          (tree5 = ts_tree_make_leaf(symbol5, padding, size, visible)),
        }), visible)),
        (tree6 = ts_tree_make_node(symbol6, 2, tree_array({
          (tree7 = ts_tree_make_node(symbol7, 1, tree_array({
            (tree8 = ts_tree_make_leaf(symbol8, padding, size, visible)),
          }), visible)),
          (tree9 = ts_tree_make_leaf(symbol9, padding, size, visible)),
        }), visible)),
      }), visible);

      auto state = ts_tree_last_external_token_state(tree1);
      AssertThat(state, Equals(&tree3->external_token_state));
    });
  });
});

END_TEST
