#include "runtime_spec_helper.h"

static ts_tree ** tree_array(vector<ts_tree *> trees) {
    ts_tree ** result = (ts_tree **)calloc(trees.size(), sizeof(ts_tree *));
    for (size_t i = 0; i < trees.size(); i++)
        result[i] = trees[i];
    return result;
}

START_TEST

enum { cat = 2, dog = 3, pig = 4 };
static const char *names[] = { "error", "end", "cat", "dog", "pig" };

describe("trees", []() {
    ts_tree *tree1, *parent1;

    before_each([&]() {
        tree1 = ts_tree_make_leaf(cat, 0, 0);
        parent1 = ts_tree_make_node(dog, 1, 1, tree_array({ tree1, tree1 }), 0, 0);
    });

    after_each([&]() {
        ts_tree_release(tree1);
        ts_tree_release(parent1);
    });

    describe("equality", [&]() {
        it("returns true for identical trees", [&]() {
            ts_tree *tree2 = ts_tree_make_leaf(cat, 0, 0);
            AssertThat(ts_tree_equals(tree1, tree2), Equals(1));

            ts_tree *parent2 = ts_tree_make_node(dog, 1, 1, tree_array({ tree2, tree2 }), 0, 0);
            AssertThat(ts_tree_equals(parent1, parent2), Equals(1));

            ts_tree_release(tree2);
            ts_tree_release(parent2);
        });

        it("returns false for trees with different symbols", [&]() {
            ts_tree *tree2 = ts_tree_make_leaf(pig, 0, 0);
            AssertThat(ts_tree_equals(tree1, tree2), Equals(0));
            ts_tree_release(tree2);
        });

        it("returns false for trees with different children", [&]() {
            ts_tree *tree2 = ts_tree_make_leaf(pig, 0, 0);
            ts_tree *parent2 = ts_tree_make_node(dog, 1, 1, tree_array({ tree2, tree2 }), 0, 0);
            AssertThat(ts_tree_equals(parent2, parent1), Equals(0));
            AssertThat(ts_tree_equals(parent1, parent2), Equals(0));
            ts_tree_release(tree2);
            ts_tree_release(parent2);
        });
    });

    describe("serialization", [&]() {
        it("returns a readable string", [&]() {
            AssertThat(string(ts_tree_string(tree1, names)), Equals("(cat)"));
            AssertThat(string(ts_tree_string(parent1, names)), Equals("(dog (cat))"));
        });
    });
});

END_TEST
