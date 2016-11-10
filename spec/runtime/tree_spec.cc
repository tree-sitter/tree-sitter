#include "spec_helper.h"
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

enum {
  cat = ts_builtin_sym_start,
  dog,
  eel,
  fox,
  goat,
  hog,
};

describe("Tree", []() {
  Tree *tree1, *tree2, *parent1;
  TSSymbolMetadata visible = {true, true, false, true};
  TSSymbolMetadata invisible = {false, false, false, true};

  before_each([&]() {
    tree1 = ts_tree_make_leaf(cat, {2, 1, {0, 1}}, {5, 4, {0, 4}}, visible);
    tree2 = ts_tree_make_leaf(cat, {1, 1, {0, 1}}, {3, 3, {0, 3}}, visible);

    ts_tree_retain(tree1);
    ts_tree_retain(tree2);
    parent1 = ts_tree_make_node(dog, 2, tree_array({
      tree1,
      tree2,
    }), visible);
  });

  after_each([&]() {
    ts_tree_release(tree1);
    ts_tree_release(tree2);
    ts_tree_release(parent1);
  });

  describe("make_leaf(sym, size, padding, is_hidden)", [&]() {
    it("does not record that it is fragile", [&]() {
      AssertThat(tree1->fragile_left, IsFalse());
      AssertThat(tree1->fragile_right, IsFalse());
    });
  });

  describe("make_error(size, padding, lookahead_char)", [&]() {
    it("records that it is fragile", [&]() {
      Tree *error_tree = ts_tree_make_error(
        length_zero(),
        length_zero(),
        'z');

      AssertThat(error_tree->fragile_left, IsTrue());
      AssertThat(error_tree->fragile_right, IsTrue());

      ts_tree_release(error_tree);
    });
  });

  describe("make_node(symbol, child_count, children, is_hidden)", [&]() {
    it("computes its size based on its child nodes", [&]() {
      AssertThat(parent1->size.bytes, Equals<size_t>(
        tree1->size.bytes + + tree2->padding.bytes + tree2->size.bytes));
      AssertThat(parent1->size.chars, Equals<size_t>(
        tree1->size.chars + + tree2->padding.chars + tree2->size.chars));
    });

    it("computes its padding based on its first child", [&]() {
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
        parent = ts_tree_make_node(eel, 2, tree_array({
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
        parent = ts_tree_make_node(eel, 2, tree_array({
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
        parent = ts_tree_make_node(eel, 2, tree_array({
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

  describe("edit(InputEdit)", [&]() {
    Tree *tree = nullptr;

    before_each([&]() {
      tree = ts_tree_make_node(cat, 3, tree_array({
        ts_tree_make_leaf(dog, {2, 2, {0, 2}}, {3, 3, {0, 3}}, visible),
        ts_tree_make_leaf(eel, {2, 2, {0, 2}}, {3, 3, {0, 3}}, visible),
        ts_tree_make_leaf(fox, {2, 2, {0, 2}}, {3, 3, {0, 3}}, visible),
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
  });

  describe("equality", [&]() {
    it("returns true for identical trees", [&]() {
      Tree *tree1_copy = ts_tree_make_leaf(cat, {2, 1, {1, 1}}, {5, 4, {1, 4}}, visible);
      AssertThat(ts_tree_eq(tree1, tree1_copy), IsTrue());

      Tree *tree2_copy = ts_tree_make_leaf(cat, {1, 1, {0, 1}}, {3, 3, {0, 3}}, visible);
      AssertThat(ts_tree_eq(tree2, tree2_copy), IsTrue());

      Tree *parent2 = ts_tree_make_node(dog, 2, tree_array({
        tree1_copy,
        tree2_copy,
      }), visible);

      AssertThat(ts_tree_eq(parent1, parent2), IsTrue());

      ts_tree_release(parent2);
    });

    it("returns false for trees with different symbols", [&]() {
      Tree *different_tree = ts_tree_make_leaf(
        tree1->symbol + 1,
        tree1->padding,
        tree1->size,
        visible);

      AssertThat(ts_tree_eq(tree1, different_tree), IsFalse());
      ts_tree_release(different_tree);
    });

    it("returns false for trees with different options", [&]() {
      Tree *tree1_copy = ts_tree_make_leaf(cat, tree1->padding, tree1->size, invisible);
      AssertThat(ts_tree_eq(tree1, tree1_copy), IsFalse());
      ts_tree_release(tree1_copy);
    });

    it("returns false for trees with different sizes", [&]() {
      Tree *tree1_copy = ts_tree_make_leaf(cat, {2, 1, {0, 1}}, tree1->size, invisible);
      AssertThat(ts_tree_eq(tree1, tree1_copy), IsFalse());
      ts_tree_release(tree1_copy);

      tree1_copy = ts_tree_make_leaf(cat, tree1->padding, {5, 4, {1, 10}}, invisible);
      AssertThat(ts_tree_eq(tree1, tree1_copy), IsFalse());
      ts_tree_release(tree1_copy);
    });

    it("returns false for trees with different children", [&]() {
      Tree *different_tree = ts_tree_make_leaf(
        tree1->symbol + 1,
        tree1->padding,
        tree1->size,
        visible);

      ts_tree_retain(different_tree);
      ts_tree_retain(tree2);
      Tree *different_parent = ts_tree_make_node(dog, 2, tree_array({
        different_tree, tree2,
      }), visible);

      AssertThat(ts_tree_eq(different_parent, parent1), IsFalse());
      AssertThat(ts_tree_eq(parent1, different_parent), IsFalse());

      ts_tree_release(different_tree);
      ts_tree_release(different_parent);
    });
  });
});

END_TEST
