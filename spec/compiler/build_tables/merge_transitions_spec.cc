#include "compiler_spec_helper.h"
#include "compiler/build_tables/merge_transitions.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("merging character set transitions", []() {
    typedef map<CharacterSet, int> int_map;
    
    auto bitwise = [](int l, int r) -> int {
        return l + r;
    };
    
    describe("when two of the right transitions intersect one of the left transitions", [&]() {
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