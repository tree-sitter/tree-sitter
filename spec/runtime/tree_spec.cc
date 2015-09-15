#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/tree_helpers.h"
#include "runtime/tree.h"
#include "runtime/length.h"

START_TEST

enum {
  cat = ts_builtin_sym_start,
  dog,
  eel,
  fox,
  goat,
  hog,
};

static const char *names[] = {
  "ERROR",
  "END",
  "cat",
  "dog",
  "eel",
  "fox",
  "goat",
  "hog",
};

describe("Tree", []() {
  TSTree *tree1, *tree2, *parent1;

  before_each([&]() {
    tree1 = ts_tree_make_leaf(cat, {2, 1}, {5, 4}, TSNodeTypeNamed);
    tree2 = ts_tree_make_leaf(cat, {1, 1}, {3, 3}, TSNodeTypeNamed);
    parent1 = ts_tree_make_node(dog, 2, tree_array({
      tree1,
      tree2,
    }), TSNodeTypeNamed);
  });

  after_each([&]() {
    ts_tree_release(tree1);
    ts_tree_release(tree2);
    ts_tree_release(parent1);
  });

  describe("make_leaf(sym, size, padding, is_hidden)", [&]() {
    it("does not record that it is fragile", [&]() {
      AssertThat(ts_tree_is_fragile_left(tree1), IsFalse());
      AssertThat(ts_tree_is_fragile_right(tree1), IsFalse());
    });
  });

  describe("make_error(size, padding, lookahead_char)", [&]() {
    it("records that it is fragile", [&]() {
      TSTree *error_tree = ts_tree_make_error(
        ts_length_zero(),
        ts_length_zero(),
        'z');

      AssertThat(ts_tree_is_fragile_left(error_tree), IsTrue());
      AssertThat(ts_tree_is_fragile_right(error_tree), IsTrue());
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
      TSTree *parent;

      before_each([&]() {
        ts_tree_set_fragile_left(tree1);
        ts_tree_set_extra(tree1);
        parent = ts_tree_make_node(eel, 2, tree_array({
          tree1,
          tree2,
        }), TSNodeTypeNamed);
      });

      after_each([&]() {
        ts_tree_release(parent);
      });

      it("records that it is fragile on the left side", [&]() {
        AssertThat(ts_tree_is_fragile_left(parent), IsTrue());
      });
    });

    describe("when the last node is fragile on the right side", [&]() {
      TSTree *parent;

      before_each([&]() {
        ts_tree_set_fragile_right(tree2);
        ts_tree_set_extra(tree2);
        parent = ts_tree_make_node(eel, 2, tree_array({
          tree1,
          tree2,
        }), TSNodeTypeNamed);
      });

      after_each([&]() {
        ts_tree_release(parent);
      });

      it("records that it is fragile on the right side", [&]() {
        AssertThat(ts_tree_is_fragile_right(parent), IsTrue());
      });
    });

    describe("when the outer nodes aren't fragile on their outer side", [&]() {
      TSTree *parent;

      before_each([&]() {
        ts_tree_set_fragile_right(tree1);
        ts_tree_set_fragile_left(tree2);
        parent = ts_tree_make_node(eel, 2, tree_array({
          tree1,
          tree2,
        }), TSNodeTypeNamed);
      });

      after_each([&]() {
        ts_tree_release(parent);
      });

      it("records that it is not fragile", [&]() {
        AssertThat(ts_tree_is_fragile_left(parent), IsFalse());
        AssertThat(ts_tree_is_fragile_right(parent), IsFalse());
      });
    });
  });

  describe("edit(InputEdit)", [&]() {
    TSTree *tree = nullptr;

    before_each([&]() {
      tree = ts_tree_make_node(cat, 3, tree_array({
        ts_tree_make_leaf(dog, {2, 2}, {3, 3}, TSNodeTypeNamed),
        ts_tree_make_leaf(eel, {2, 2}, {3, 3}, TSNodeTypeNamed),
        ts_tree_make_leaf(fox, {2, 2}, {3, 3}, TSNodeTypeNamed),
      }), TSNodeTypeNamed);

      AssertThat(tree->padding, Equals<TSLength>({2, 2}));
      AssertThat(tree->size, Equals<TSLength>({13, 13}));
    });

    after_each([&]() {
      ts_tree_release(tree);
    });

    auto assert_consistent = [&](const TSTree *tree) {
      AssertThat(tree->children[0]->padding, Equals<TSLength>(tree->padding));

      TSLength total_children_size = ts_length_zero();
      for (size_t i = 0; i < tree->child_count; i++)
        total_children_size = ts_length_add(total_children_size, ts_tree_total_size(tree->children[i]));
      AssertThat(total_children_size, Equals<TSLength>(ts_tree_total_size(tree)));
    };

    describe("edits within a tree's padding", [&]() {
      it("resizes the padding of the tree and its leftmost descendants", [&]() {
        ts_tree_edit(tree, {1, 1, 0});

        assert_consistent(tree);

        AssertThat(tree->options.has_changes, IsTrue());
        AssertThat(tree->padding, Equals<TSLength>({0, 3}));
        AssertThat(tree->size, Equals<TSLength>({13, 13}));

        AssertThat(tree->children[0]->options.has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<TSLength>({0, 3}));
        AssertThat(tree->children[0]->size, Equals<TSLength>({3, 3}));

        AssertThat(tree->children[1]->options.has_changes, IsFalse());
        AssertThat(tree->children[1]->padding, Equals<TSLength>({2, 2}));
        AssertThat(tree->children[1]->size, Equals<TSLength>({3, 3}));
      });
    });

    describe("edits that start in a tree's padding but extend into its content", [&]() {
      it("shrinks the content to compensate for the expanded padding", [&]() {
        ts_tree_edit(tree, {1, 4, 3});

        assert_consistent(tree);

        AssertThat(tree->options.has_changes, IsTrue());
        AssertThat(tree->padding, Equals<TSLength>({0, 5}));
        AssertThat(tree->size, Equals<TSLength>({0, 11}));

        AssertThat(tree->children[0]->options.has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<TSLength>({0, 5}));
        AssertThat(tree->children[0]->size, Equals<TSLength>({0, 1}));
      });
    });

    describe("insertions at the edge of a tree's padding", [&]() {
      it("expands the tree's padding", [&]() {
        ts_tree_edit(tree, {2, 2, 0});

        assert_consistent(tree);

        AssertThat(tree->options.has_changes, IsTrue());
        AssertThat(tree->padding, Equals<TSLength>({0, 4}));
        AssertThat(tree->size, Equals<TSLength>({13, 13}));

        AssertThat(tree->children[0]->options.has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<TSLength>({0, 4}));
        AssertThat(tree->children[0]->size, Equals<TSLength>({3, 3}));

        AssertThat(tree->children[1]->options.has_changes, IsFalse());
      });
    });

    describe("replacements starting at the edge of a tree's padding", [&]() {
      it("resizes the content and not the padding", [&]() {
        ts_tree_edit(tree, {2, 5, 2});

        assert_consistent(tree);

        AssertThat(tree->options.has_changes, IsTrue());
        AssertThat(tree->padding, Equals<TSLength>({2, 2}));
        AssertThat(tree->size, Equals<TSLength>({0, 16}));

        AssertThat(tree->children[0]->options.has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<TSLength>({2, 2}));
        AssertThat(tree->children[0]->size, Equals<TSLength>({0, 6}));

        AssertThat(tree->children[1]->options.has_changes, IsFalse());
      });
    });

    describe("deletions that span more than one child node", [&]() {
      it("shrinks subsequent child nodes", [&]() {
        ts_tree_edit(tree, {1, 3, 10});

        assert_consistent(tree);

        AssertThat(tree->options.has_changes, IsTrue());
        AssertThat(tree->padding, Equals<TSLength>({0, 4}));
        AssertThat(tree->size, Equals<TSLength>({0, 4}));

        AssertThat(tree->children[0]->options.has_changes, IsTrue());
        AssertThat(tree->children[0]->padding, Equals<TSLength>({0, 4}));
        AssertThat(tree->children[0]->size, Equals<TSLength>({0, 0}));

        AssertThat(tree->children[1]->options.has_changes, IsTrue());
        AssertThat(tree->children[1]->padding, Equals<TSLength>({0, 0}));
        AssertThat(tree->children[1]->size, Equals<TSLength>({0, 0}));

        AssertThat(tree->children[2]->options.has_changes, IsTrue());
        AssertThat(tree->children[2]->padding, Equals<TSLength>({0, 1}));
        AssertThat(tree->children[2]->size, Equals<TSLength>({3, 3}));
      });
    });
  });

  describe("equality", [&]() {
    it("returns true for identical trees", [&]() {
      TSTree *tree1_copy = ts_tree_make_leaf(cat, {2, 1}, {5, 4}, TSNodeTypeNamed);
      AssertThat(ts_tree_eq(tree1, tree1_copy), IsTrue());

      TSTree *tree2_copy = ts_tree_make_leaf(cat, {1, 1}, {3, 3}, TSNodeTypeNamed);
      AssertThat(ts_tree_eq(tree2, tree2_copy), IsTrue());

      TSTree *parent2 = ts_tree_make_node(dog, 2, tree_array({
        tree1_copy,
        tree2_copy,
      }), TSNodeTypeNamed);

      AssertThat(ts_tree_eq(parent1, parent2), IsTrue());

      ts_tree_release(tree1_copy);
      ts_tree_release(tree2_copy);
      ts_tree_release(parent2);
    });

    it("returns false for trees with different symbols", [&]() {
      TSTree *different_tree = ts_tree_make_leaf(
        tree1->symbol + 1,
        tree1->padding,
        tree1->size,
        TSNodeTypeNamed);

      AssertThat(ts_tree_eq(tree1, different_tree), IsFalse());
      ts_tree_release(different_tree);
    });

    it("returns false for trees with different children", [&]() {
      TSTree *different_tree = ts_tree_make_leaf(
        tree1->symbol + 1,
        tree1->padding,
        tree1->size,
        TSNodeTypeNamed);

      TSTree *different_parent = ts_tree_make_node(dog, 2, tree_array({
          different_tree, different_tree,
      }), TSNodeTypeNamed);

      AssertThat(ts_tree_eq(different_parent, parent1), IsFalse());
      AssertThat(ts_tree_eq(parent1, different_parent), IsFalse());

      ts_tree_release(different_tree);
      ts_tree_release(different_parent);
    });
  });

  describe("serialization", [&]() {
    it("returns a readable string", [&]() {
      char *string1 = ts_tree_string(tree1, names);
      AssertThat(string(string1), Equals("(cat)"));
      free(string1);

      char *string2 = ts_tree_string(parent1, names);
      AssertThat(string(string2), Equals("(dog (cat) (cat))"));
      free(string2);
    });

    it("hides invisible nodes", [&]() {
      tree2->options.type = TSNodeTypeHidden;

      char *string1 = ts_tree_string(parent1, names);
      AssertThat(string(string1), Equals("(dog (cat))"));
      free(string1);
    });

    describe("when the root node is not visible", [&]() {
      it("still serializes it", [&]() {
        parent1->options.type = TSNodeTypeHidden;

        char *string1 = ts_tree_string(parent1, names);
        AssertThat(string(string1), Equals("(dog (cat) (cat))"));
        free(string1);

        tree1->options.type = TSNodeTypeHidden;

        char *string2 = ts_tree_string(tree1, names);
        AssertThat(string(string2), Equals("(cat)"));
        free(string2);
      });
    });
  });
});

END_TEST

ostream &operator<<(ostream &stream, const TSLength &length) {
  return stream << "{bytes:" << length.bytes << ", chars:" << length.chars << "}";
}

bool operator==(TSLength left, TSLength right) {
  return ts_length_eq(left, right);
}
