#include "runtime_spec_helper.h"

START_TEST

enum {
    cat = 2,
    dog = 3,
    pig = 4,
};

static const char *names[] = { "error", "end", "cat", "dog", "pig" };

describe("trees", []() {
    ts_tree *tree1, *tree2, *parent1;

    before_each([&]() {
        tree1 = ts_tree_make_leaf(cat, 5, 2);
        tree2 = ts_tree_make_leaf(cat, 3, 1);
        parent1 = ts_tree_make_node(dog, 2, 2, tree_array({
            tree1, tree2, // children
            tree1, tree2, // immediate_children
        }));
    });

    after_each([&]() {
        ts_tree_release(tree1);
        ts_tree_release(tree2);
        ts_tree_release(parent1);
    });
    
    describe("making a parent node", [&]() {
        it("computes its offset and size based on its child nodes", [&]() {
            AssertThat(ts_tree_size(parent1), Equals(9));
        });
        
        it("computes its offset based on its first child", [&]() {
            AssertThat(ts_tree_offset(parent1), Equals(2));
        });
    });

    describe("equality", [&]() {
        it("returns true for identical trees", [&]() {
            ts_tree *tree1_copy = ts_tree_make_leaf(cat, 5, 2);
            AssertThat(ts_tree_equals(tree1, tree1_copy), Equals(1));
            ts_tree *tree2_copy = ts_tree_make_leaf(cat, 3, 1);
            AssertThat(ts_tree_equals(tree2, tree2_copy), Equals(1));

            ts_tree *parent2 = ts_tree_make_node(dog, 2, 2, tree_array({
                tree1_copy, tree2_copy,
                tree1_copy, tree2_copy,
            }));
            AssertThat(ts_tree_equals(parent1, parent2), Equals(1));

            ts_tree_release(tree1_copy);
            ts_tree_release(tree2_copy);
            ts_tree_release(parent2);
        });

        it("returns false for trees with different symbols", [&]() {
            ts_tree *different_tree = ts_tree_make_leaf(pig, 0, 0);
            AssertThat(ts_tree_equals(tree1, different_tree), Equals(0));
            ts_tree_release(different_tree);
        });

        it("returns false for trees with different children", [&]() {
            ts_tree *different_tree = ts_tree_make_leaf(pig, 0, 0);
            ts_tree *different_parent = ts_tree_make_node(dog, 2, 2, tree_array({
                different_tree, different_tree,
                tree2, tree2,
            }));

            AssertThat(ts_tree_equals(different_parent, parent1), Equals(0));
            AssertThat(ts_tree_equals(parent1, different_parent), Equals(0));

            ts_tree_release(different_tree);
            ts_tree_release(different_parent);
        });
    });

    describe("serialization", [&]() {
        it("returns a readable string", [&]() {
            AssertThat(string(ts_tree_string(tree1, names)), Equals("(cat)"));
            AssertThat(string(ts_tree_string(parent1, names)), Equals("(dog (cat) (cat))"));
        });
    });
});

END_TEST
