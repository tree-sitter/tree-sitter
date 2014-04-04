#include "compiler_spec_helper.h"
#include "compiler/build_tables/merge_transitions.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("merging character set transitions", []() {
    typedef map<CharacterSet, int> int_map;
    
    auto bitwise = [](int l, int r) -> int {
        return l | r;
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
            
            AssertThat(merge_char_transitions<int>(map1, map2, bitwise), Equals(int_map({
                { CharacterSet({ 'a', 'c' }), 1 },
                { CharacterSet({ 'x', 'y' }), 2 },
                { CharacterSet({ '1', '9' }), 4 },
                { CharacterSet({ ' ' }), 8 },
                { CharacterSet({ '\t' }), 16 },
            })));
            
            AssertThat(merge_char_transitions<int>(map2, map1, bitwise), Equals(merge_char_transitions<int>(map1, map2, bitwise)));
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
            
            AssertThat(merge_char_transitions<int>(map1, map2, bitwise), Equals(int_map({
                { CharacterSet({ {'a', 'b'}, {'d', 'f'},  {'A', 'F'} }), 1 },
                { CharacterSet({ {'c'} }), 5 },
                { CharacterSet({ {'0', '2'}, {'4', '9'} }), 2 },
                { CharacterSet({ '3' }), 10 },
            })));
            
            AssertThat(merge_char_transitions<int>(map2, map1, bitwise), Equals(merge_char_transitions<int>(map1, map2, bitwise)));
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
            
            AssertThat(merge_char_transitions<int>(map1, map2, bitwise), Equals(int_map({
                { CharacterSet({ 'a' }), 3 },
                { CharacterSet({ 'c' }), 5 },
            })));
            
            AssertThat(merge_char_transitions<int>(map2, map1, bitwise), Equals(merge_char_transitions<int>(map1, map2, bitwise)));
        });
    });
});

END_TEST