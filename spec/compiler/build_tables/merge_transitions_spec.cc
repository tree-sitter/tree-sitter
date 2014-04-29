#include "compiler_spec_helper.h"
#include "compiler/build_tables/merge_transitions.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("merging character set transitions", []() {
    typedef map<CharacterSet, int> int_map;

    auto merge_result = [&](int_map left, int_map right) -> int_map {
        merge_char_transitions<int>(&left, right, [](const int *l, const int *r) -> int {
            return *l | *r;
        });
        return left;
    };

    describe("when none of the transitions intersect", [&]() {
        it("returns the union of the two sets of transitions", [&]() {
            int_map map1({
                { CharacterSet({ 'a', 'c' }), 1 },
                { CharacterSet({ 'x', 'y' }), 2 },
                { CharacterSet({ '1', '9' }), 4 },
            });

            int_map map2({
                { CharacterSet({ ' ' }), 8 },
                { CharacterSet({ '\t' }), 16 },
            });

            AssertThat(merge_result(map1, map2), Equals(int_map({
                { CharacterSet({ 'a', 'c' }), 1 },
                { CharacterSet({ 'x', 'y' }), 2 },
                { CharacterSet({ '1', '9' }), 4 },
                { CharacterSet({ ' ' }), 8 },
                { CharacterSet({ '\t' }), 16 },
            })));

            AssertThat(merge_result(map2, map1), Equals(merge_result(map1, map2)));
        });
    });

    describe("when transitions intersect", [&]() {
        it("merges the intersecting transitions using the provided function", [&]() {
            int_map map1({
                { CharacterSet({ {'a', 'f'}, {'A', 'F'} }), 1 },
                { CharacterSet({ {'0', '9'} }), 2 },
            });

            int_map map2({
                { CharacterSet({ 'c' }), 4 },
                { CharacterSet({ '3' }), 8 },
            });

            AssertThat(merge_result(map1, map2), Equals(int_map({
                { CharacterSet({ {'a', 'b'}, {'d', 'f'},  {'A', 'F'} }), 1 },
                { CharacterSet({ {'c'} }), 5 },
                { CharacterSet({ {'0', '2'}, {'4', '9'} }), 2 },
                { CharacterSet({ '3' }), 10 },
            })));

            AssertThat(merge_result(map2, map1), Equals(merge_result(map1, map2)));
        });
    });

    describe("when two of the right transitions intersect the same left transition", [&]() {
        it("splits the left-hand transition correctly", [&]() {
            int_map map1({
                { CharacterSet({ 'a', 'c' }), 1 },
            });

            int_map map2({
                { CharacterSet({ 'a' }), 2 },
                { CharacterSet({ 'c' }), 4 },
            });

            AssertThat(merge_result(map1, map2), Equals(int_map({
                { CharacterSet({ 'a' }), 3 },
                { CharacterSet({ 'c' }), 5 },
            })));

            AssertThat(merge_result(map2, map1), Equals(merge_result(map1, map2)));
        });
    });
});

END_TEST