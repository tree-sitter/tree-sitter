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
            set.add_set(CharacterSet({ {'A', 'Z'} }, true));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'}, {'A', 'Z'}, })));
        });
        
        it("works for sets with adjacent ranges", []() {
            CharacterSet set({ {'a', 'r'} }, true);
            set.add_set(CharacterSet({ {'s', 'z'} }, true));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'} }, true)));

            set = CharacterSet({ 'c' });
            auto c = set.complement();
            set.add_set(c);
            AssertThat(set, Equals(CharacterSet({ {0, -1} }, true)));
        });
        
        it("works when the result becomes a continuous range", []() {
            CharacterSet set({ {'a', 'd'}, {'f', 'z'} }, true);
            set.add_set(CharacterSet({ {'c', 'g'} }, true));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'} }, true)));
        });
        
        it("does nothing for the set of all characters", []() {
            CharacterSet set({ 'a' });
            set.add_set(set.complement());
            AssertThat(set, Equals(CharacterSet({ {'\0', '\xff'} }, true)));
        });
    });
    
    describe("computing differences", []() {
        it("works for disjoint sets", []() {
            CharacterSet set1({ {'a','z'} }, true);
            set1.remove_set(CharacterSet({ {'A','Z'} }, true));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'z'} }, true)));
        });
        
        it("works when one set spans the other", []() {
            CharacterSet set1({ {'a','z'} }, true);
            set1.remove_set(CharacterSet({ {'d','s'} }, true));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'c'}, {'t', 'z'} })));
        });
        
        it("works for sets that overlap", []() {
            CharacterSet set1({ {'a','s'} }, true);
            set1.remove_set(CharacterSet({ {'m','z'} }, true));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'l'} }, true)));

            CharacterSet set2({ {'m','z'} }, true);
            set2.remove_set(CharacterSet({ {'a','s'} }, true));
            AssertThat(set2, Equals(CharacterSet({ {'t', 'z'} }, true)));
        });
        
        it("works for sets with multiple ranges", []() {
            CharacterSet set1({ {'a','d'}, {'m', 'z'} });
            set1.remove_set(CharacterSet({ {'c','o'}, {'s','x'} }));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'b'}, {'p','r'}, {'y','z'} })));
        });
    });
});

END_TEST