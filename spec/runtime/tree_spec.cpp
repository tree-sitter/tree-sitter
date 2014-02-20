#include "spec_helper.h"

START_TEST

enum { cat, dog, pig };
static const char *names[] = { "cat", "dog", "pig" };

describe("trees", []() {
    ts_tree *tree1, *parent1;
    
    before_each([&]() {
        tree1 = ts_tree_make(cat, 0, NULL);
        parent1 = ts_tree_make(dog, 1, &tree1);
    });
    
    after_each([&]() {
        ts_tree_release(tree1);
        ts_tree_release(parent1);
    });

    describe("equality", [&]() {
        it("returns true for identical trees", [&]() {
            ts_tree *tree2 = ts_tree_make(cat, 0, NULL);
            AssertThat(ts_tree_equals(tree1, tree2), Equals(1));
            
            ts_tree *parent2 = ts_tree_make(dog, 1, &tree2);
            AssertThat(ts_tree_equals(parent1, parent2), Equals(1));
            
            ts_tree_release(tree2);
            ts_tree_release(parent2);
        });
        
        it("returns false for different trees", [&]() {
            ts_tree *different_tree = ts_tree_make(pig, 0, NULL);
            AssertThat(ts_tree_equals(tree1, different_tree), Equals(0));
            
            ts_tree *different_parent = ts_tree_make(dog, 1, &different_tree);
            AssertThat(ts_tree_equals(parent1, different_parent), Equals(0));
            
            ts_tree *parent_with_same_type = ts_tree_make(cat, 1, &different_parent);
            AssertThat(ts_tree_equals(parent_with_same_type, tree1), Equals(0));
            AssertThat(ts_tree_equals(tree1, parent_with_same_type), Equals(0));
            
            ts_tree_release(different_tree);
            ts_tree_release(different_parent);
            ts_tree_release(parent_with_same_type);
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