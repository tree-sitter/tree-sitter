#include "spec_helper.h"
#include "runtime.h"

START_TEST

enum { cat, dog, pig };
static const char *names[] = { "cat", "dog", "pig" };

describe("trees", []() {
    TSTree *tree1, *parent1;
    
    before_each([&]() {
        tree1 = TSTreeMake(cat, 0, NULL);
        parent1 = TSTreeMake(dog, 1, &tree1);
    });
    
    after_each([&]() {
        TSTreeRelease(tree1);
        TSTreeRelease(parent1);
    });

    describe("equality", [&]() {
        it("returns true for identical trees", [&]() {
            TSTree *tree2 = TSTreeMake(cat, 0, NULL);
            AssertThat(TSTreeEquals(tree1, tree2), Equals(1));
            
            TSTree *parent2 = TSTreeMake(dog, 1, &tree2);
            AssertThat(TSTreeEquals(parent1, parent2), Equals(1));
            
            TSTreeRelease(tree2);
            TSTreeRelease(parent2);
        });
        
        it("returns false for different trees", [&]() {
            TSTree *different_tree = TSTreeMake(pig, 0, NULL);
            AssertThat(TSTreeEquals(tree1, different_tree), Equals(0));
            
            TSTree *different_parent = TSTreeMake(dog, 1, &different_tree);
            AssertThat(TSTreeEquals(parent1, different_parent), Equals(0));
            
            TSTree *parent_with_same_type = TSTreeMake(cat, 1, &different_parent);
            AssertThat(TSTreeEquals(parent_with_same_type, tree1), Equals(0));
            AssertThat(TSTreeEquals(tree1, parent_with_same_type), Equals(0));
            
            TSTreeRelease(different_tree);
            TSTreeRelease(different_parent);
            TSTreeRelease(parent_with_same_type);
        });
    });
    
    describe("serialization", [&]() {
        it("returns a readable string", [&]() {
            AssertThat(string(TSTreeToString(tree1, names)), Equals("(cat)"));
            AssertThat(string(TSTreeToString(parent1, names)), Equals("(dog (cat))"));
        });
    });
});

END_TEST