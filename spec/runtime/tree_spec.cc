#include "runtime/runtime_spec_helper.h"
#include "runtime/tree.h"
#include "runtime/length.h"

START_TEST

enum {
    cat = ts_builtin_sym_start,
    dog,
    pig,
};

static const char *names[] = {
  "ERROR",
  "END",
  "cat",
  "dog",
  "pig",
};

describe("Tree", []() {
  TSTree *tree1, *tree2, *parent1;

  before_each([&]() {
    tree1 = ts_tree_make_leaf(
      cat,
      ts_length_make(5, 4),
      ts_length_make(2, 1),
      TSNodeTypeNormal);

    tree2 = ts_tree_make_leaf(
      cat,
      ts_length_make(3, 3),
      ts_length_make(1, 1),
      TSNodeTypeNormal);

    parent1 = ts_tree_make_node(
      dog,
      2,
      tree_array({ tree1, tree2, }),
      TSNodeTypeNormal);
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
        parent = ts_tree_make_node(pig, 2, tree_array({
          tree1,
          tree2,
        }), TSNodeTypeNormal);
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
        parent = ts_tree_make_node(pig, 2, tree_array({
          tree1,
          tree2,
        }), TSNodeTypeNormal);
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
        parent = ts_tree_make_node(pig, 2, tree_array({
          tree1,
          tree2,
        }), TSNodeTypeNormal);
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

  describe("equality", [&]() {
    it("returns true for identical trees", [&]() {
      TSTree *tree1_copy = ts_tree_make_leaf(
        cat,
        ts_length_make(5, 4),
        ts_length_make(2, 1),
        TSNodeTypeNormal);

      AssertThat(ts_tree_eq(tree1, tree1_copy), IsTrue());

      TSTree *tree2_copy = ts_tree_make_leaf(
        cat,
        ts_length_make(3, 3),
        ts_length_make(1, 1),
        TSNodeTypeNormal);

      AssertThat(ts_tree_eq(tree2, tree2_copy), IsTrue());

      TSTree *parent2 = ts_tree_make_node(dog, 2, tree_array({
        tree1_copy, tree2_copy,
      }), TSNodeTypeNormal);

      AssertThat(ts_tree_eq(parent1, parent2), IsTrue());

      ts_tree_release(tree1_copy);
      ts_tree_release(tree2_copy);
      ts_tree_release(parent2);
    });

    it("returns false for trees with different symbols", [&]() {
      TSTree *different_tree = ts_tree_make_leaf(
        tree1->symbol + 1,
        tree1->size,
        tree1->padding,
        TSNodeTypeNormal);

      AssertThat(ts_tree_eq(tree1, different_tree), IsFalse());
      ts_tree_release(different_tree);
    });

    it("returns false for trees with different children", [&]() {
      TSTree *different_tree = ts_tree_make_leaf(
        tree1->symbol + 1,
        tree1->size,
        tree1->padding,
        TSNodeTypeNormal);

      TSTree *different_parent = ts_tree_make_node(dog, 2, tree_array({
          different_tree, different_tree,
      }), TSNodeTypeNormal);

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

bool operator==(TSLength left, TSLength right) {
  return ts_length_eq(left, right);
}
