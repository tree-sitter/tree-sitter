#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/merge_transitions.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("merge_transition", []() {
  typedef map<CharacterSet, int> int_map;

  auto do_merge = [&](int_map *left, const pair<CharacterSet, int> &new_pair) {
    merge_transition<int>(left, new_pair, [](int *l, const int *r) {
      *l = *l | *r;
    });
  };

  describe("when none of the transitions intersect", [&]() {
    it("returns the union of the two sets of transitions", [&]() {
      int_map map({
        { CharacterSet().include('a').include('c'), 1 },
        { CharacterSet().include('x').include('y'), 2 },
        { CharacterSet().include('1').include('9'), 4 },
      });

      do_merge(&map, { CharacterSet().include(' '), 8 });
      do_merge(&map, { CharacterSet().include('\t'), 16 });

      AssertThat(map, Equals(int_map({
        { CharacterSet().include('a').include('c'), 1 },
        { CharacterSet().include('x').include('y'), 2 },
        { CharacterSet().include('1').include('9'), 4 },
        { CharacterSet().include(' '), 8 },
        { CharacterSet().include('\t'), 16 },
      })));
    });
  });

  describe("when transitions intersect", [&]() {
    it("merges the intersecting transitions using the provided function", [&]() {
      int_map map({
        { CharacterSet().include('a', 'f').include('A', 'F'), 1 },
        { CharacterSet().include('0', '9'), 2 },
      });

      do_merge(&map, { CharacterSet().include('c'), 4 });
      do_merge(&map, { CharacterSet().include('3'), 8 });

      AssertThat(map, Equals(int_map({
        {
          CharacterSet()
            .include('a', 'b')
            .include('d', 'f')
            .include('A', 'F'),
          1
        },
        {
          CharacterSet().include('c'),
          5
        },
        {
          CharacterSet().include('0', '2').include('4', '9'),
          2
        },
        {
          CharacterSet().include('3'),
          10
        },
      })));
    });
  });

  describe("when two of the right transitions intersect the same left transition", [&]() {
    it("splits the left-hand transition correctly", [&]() {
      int_map map1({
        { CharacterSet().include('a').include('c'), 1 },
      });

      do_merge(&map1, { CharacterSet().include('a'), 2 });
      do_merge(&map1, { CharacterSet().include('c'), 4 });

      AssertThat(map1, Equals(int_map({
        { CharacterSet().include('a'), 3 },
        { CharacterSet().include('c'), 5 },
      })));
    });
  });
});

END_TEST
