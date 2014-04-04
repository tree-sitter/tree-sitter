#include "compiler_spec_helper.h"
#include "compiler/rules/character_set.h"

using namespace rules;

START_TEST

describe("character sets", []() {
    unsigned char max_char = 255;

    describe("computing the complement", [&]() {
        it("works for the set containing only the null character", [&]() {
            CharacterSet set1({ '\0' });
            auto set2 = set1.complement();
            AssertThat(set2, Equals(CharacterSet({
                { 1, max_char }
            })));
            AssertThat(set2.complement(), Equals(set1));
        });

        it("works for single character sets", [&]() {
            CharacterSet set1({ 'b' });
            auto set2 = set1.complement();
            AssertThat(set2, Equals(CharacterSet({
                { 0, 'a' },
                { 'c', max_char },
            })));
            AssertThat(set2.complement(), Equals(set1));
        });
    });

    describe("computing unions", [&]() {
        it("works for disjoint sets", [&]() {
            CharacterSet set({ {'a', 'z'} });
            set.add_set(CharacterSet({ {'A', 'Z'} }));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'}, {'A', 'Z'} })));
        });

        it("works for sets with adjacent ranges", [&]() {
            CharacterSet set({ CharacterRange('a', 'r') });
            set.add_set(CharacterSet({ CharacterRange('s', 'z') }));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'} })));
        });

        it("becomes the complete set when the complement is added", [&]() {
            CharacterSet set({ 'c' });
            auto complement = set.complement();
            set.add_set(complement);
            AssertThat(set, Equals(CharacterSet({ {0, max_char} })));
        });

        it("works when the result becomes a continuous range", []() {
            CharacterSet set({ {'a', 'd'}, {'f', 'z'} });
            set.add_set(CharacterSet({ {'c', 'g'} }));
            AssertThat(set, Equals(CharacterSet({ {'a', 'z'} })));
        });

        it("does nothing for the set of all characters", [&]() {
            CharacterSet set({ 'a' });
            set.add_set(set.complement());
            AssertThat(set, Equals(CharacterSet({ {'\0', max_char} })));
        });
    });

    describe("subtracting sets", []() {
        CharacterSet intersection;

        it("works for disjoint sets", [&]() {
            CharacterSet set1({ {'a', 'z'} });
            intersection = set1.remove_set(CharacterSet({ {'A', 'Z'} }));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'z'} })));
            AssertThat(intersection, Equals(CharacterSet()));
        });

        it("works when one set is a proper subset of the other", [&]() {
            CharacterSet set1({ {'a','z'} });
            intersection = set1.remove_set(CharacterSet({ {'d', 's'} }));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'c'}, {'t', 'z'} })));
            AssertThat(intersection, Equals(CharacterSet({ {'d', 's'} })));
        });

        it("works for a set that overlaps the right side", [&]() {
            CharacterSet set1({ {'a','s'} });
            intersection = set1.remove_set(CharacterSet({ {'m', 'z'} }));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'l'} })));
            AssertThat(intersection, Equals(CharacterSet({ {'m', 's'} })));
        });

        it("works for a set that overlaps the left side", [&]() {
            CharacterSet set2({ {'m','z'} });
            intersection = set2.remove_set(CharacterSet({ {'a', 's'} }));
            AssertThat(set2, Equals(CharacterSet({ {'t', 'z'} })));
            AssertThat(intersection, Equals(CharacterSet({ {'m', 's'} })));
        });

        it("works for sets with multiple ranges", [&]() {
            CharacterSet set1({ {'a', 'd'}, {'m', 'z'} });
            intersection = set1.remove_set(CharacterSet({ {'c', 'o'}, {'s', 'x'} }));
            AssertThat(set1, Equals(CharacterSet({ {'a', 'b'}, {'p', 'r'}, {'y', 'z'} })));
            AssertThat(intersection, Equals(CharacterSet({ {'c', 'd'}, {'m', 'o'}, {'s', 'x'} })));
        });

        it("works when the result is empty", [&]() {
            CharacterSet set1({ 'd' });
            intersection = set1.remove_set(CharacterSet({ 'a', 'd', 'x' }));
            AssertThat(set1, Equals(CharacterSet()));
            AssertThat(intersection, Equals(CharacterSet({ 'd' })));
        });
    });
});

END_TEST
