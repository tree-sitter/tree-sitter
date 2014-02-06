#include "spec_helper.h"
#include "rules.h"

using namespace rules;

START_TEST

describe("character sets", []() {
    describe("computing the complement", []() {
        it("works for the set containing only the null character", []() {
            CharacterSet set1({ '\0' });
            auto set2 = set1.complement();
            AssertThat(set2, Equals(CharacterSet({
                { 1, -1 },
            }, true)));
            AssertThat(set2.complement(), Equals(set1));
        });

        it("works for single character sets", []() {
            CharacterSet set1({ 'b' });
            auto set2 = set1.complement();
            AssertThat(set2, Equals(CharacterSet({
                { 0, 'a' },
                { 'c', -1 },
            })));
            AssertThat(set2.complement(), Equals(set1));
        });
    });
    
    describe("computing unions", []() {
        it("works for disjoint sets", []() {
            CharacterSet set({ {'a', 'z'} }, true);
            set.union_with(CharacterSet({ {'A', 'Z'} }, true));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'}, {'A', 'Z'}, })));
        });
        
        it("works for sets with adjacent ranges", []() {
            CharacterSet set({ {'a', 'r'} }, true);
            set.union_with(CharacterSet({ {'s', 'z'} }, true));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'} }, true)));

            set = CharacterSet({ 'c' });
            auto c = set.complement();
            set.union_with(c);
            AssertThat(set, Equals(CharacterSet({ {0, -1} }, true)));
        });
        
        it("works when the result becomes a continuous range", []() {
            CharacterSet set({ {'a', 'd'}, {'f', 'z'} }, true);
            set.union_with(CharacterSet({ {'d', 'f'} }, true));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'} }, true)));
        });
        
        it("does nothing for the set of all characters", []() {
            CharacterSet set({ {'\0', '\xff'} }, true);
            set.union_with(CharacterSet({ 'a' }));
            AssertThat(set, Equals(CharacterSet({ {'\0', '\xff'} }, true)));
        });
    });
});

END_TEST