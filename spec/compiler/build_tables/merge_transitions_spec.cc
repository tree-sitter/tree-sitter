#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/merge_transitions.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("merging character set transitions", []() {
    typedef map<CharacterSet, int> int_map;

    auto do_merge = [&](int_map *left, const pair<CharacterSet, int> &new_pair) {
        merge_char_transition<int>(left, new_pair, [](int *l, const int *r) {
            *l = *l | *r;
        });
    };

    describe("when none of the transitions intersect", [&]() {
        it("returns the union of the two sets of transitions", [&]() {
            int_map map({
                { CharacterSet({ 'a', 'c' }), 1 },
                { CharacterSet({ 'x', 'y' }), 2 },
                { CharacterSet({ '1', '9' }), 4 },
            });

            do_merge(&map, { CharacterSet({ ' ' }), 8 });
            do_merge(&map, { CharacterSet({ '\t' }), 16 });

            AssertThat(map, Equals(int_map({
                { CharacterSet({ 'a', 'c' }), 1 },
                { CharacterSet({ 'x', 'y' }), 2 },
                { CharacterSet({ '1', '9' }), 4 },
                { CharacterSet({ ' ' }), 8 },
                { CharacterSet({ '\t' }), 16 },
            })));
        });
    });

    describe("when transitions intersect", [&]() {
        it("merges the intersecting transitions using the provided function", [&]() {
            int_map map({
                { CharacterSet({ {'a', 'f'}, {'A', 'F'} }), 1 },
                { CharacterSet({ {'0', '9'} }), 2 },
            });

            do_merge(&map, { CharacterSet({ 'c' }), 4 });
            do_merge(&map, { CharacterSet({ '3' }), 8 });

            AssertThat(map, Equals(int_map({
                { CharacterSet({ {'a', 'b'}, {'d', 'f'},  {'A', 'F'} }), 1 },
                { CharacterSet({ {'c'} }), 5 },
                { CharacterSet({ {'0', '2'}, {'4', '9'} }), 2 },
                { CharacterSet({ '3' }), 10 },
            })));
        });
    });

    describe("when two of the right transitions intersect the same left transition", [&]() {
        it("splits the left-hand transition correctly", [&]() {
            int_map map1({
                { CharacterSet({ 'a', 'c' }), 1 },
            });

            do_merge(&map1, { CharacterSet({ 'a' }), 2 });
            do_merge(&map1, { CharacterSet({ 'c' }), 4 });

            AssertThat(map1, Equals(int_map({
                { CharacterSet({ 'a' }), 3 },
                { CharacterSet({ 'c' }), 5 },
            })));
        });
    });
});

END_TEST
