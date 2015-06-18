#include "runtime/runtime_spec_helper.h"
#include "runtime/parse_stack.h"
#include "runtime/tree.h"
#include "runtime/length.h"

enum {
  stateA, stateB, stateC, stateD, stateE, stateF, stateG, stateH
};

enum {
  symbol0 = ts_builtin_sym_start,
  symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7
};

START_TEST

describe("ParseStack", [&]() {
  ParseStack *stack;
  const size_t tree_count = 8;
  TSTree *trees[tree_count];

  before_each([&]() {
    stack = ts_parse_stack_new();
    TSLength len = ts_length_make(2, 2);
    for (size_t i = 0; i < tree_count; i++)
      trees[i] = ts_tree_make_leaf(ts_builtin_sym_start + i, len, len, false);
  });

  after_each([&]() {
    ts_parse_stack_delete(stack);
    for (size_t i = 0; i < tree_count; i++)
      ts_tree_release(trees[i]);
  });

  describe("push(head_index, state, tree)", [&]() {
    it("adds entries to the stack", [&]() {
      AssertThat(ts_parse_stack_head_count(stack), Equals(1));
      AssertThat(ts_parse_stack_head(stack, 0), Equals<const ParseStackEntry *>(nullptr));

      /*
       *  A0.
       */
      ts_parse_stack_push(stack, 0, stateA, trees[0]);
      const ParseStackEntry *entry1 = ts_parse_stack_head(stack, 0);
      AssertThat(*entry1, Equals<ParseStackEntry>({trees[0], stateA}));
      AssertThat(ts_parse_stack_entry_next_count(entry1), Equals(1));
      AssertThat(ts_parse_stack_entry_next(entry1, 0), Equals<const ParseStackEntry *>(nullptr));

      /*
       *  A0__B1.
       */
      ts_parse_stack_push(stack, 0, stateB, trees[1]);
      const ParseStackEntry *entry2 = ts_parse_stack_head(stack, 0);
      AssertThat(*entry2, Equals<ParseStackEntry>({trees[1], stateB}));
      AssertThat(ts_parse_stack_entry_next_count(entry2), Equals(1));
      AssertThat(ts_parse_stack_entry_next(entry2, 0), Equals(entry1));

      /*
       *  A0__B1__C2.
       */
      ts_parse_stack_push(stack, 0, stateC, trees[2]);
      const ParseStackEntry *entry3 = ts_parse_stack_head(stack, 0);
      AssertThat(*entry3, Equals<ParseStackEntry>({trees[2], stateC}));
      AssertThat(ts_parse_stack_entry_next_count(entry3), Equals(1));
      AssertThat(ts_parse_stack_entry_next(entry3, 0), Equals(entry2));
    });
  });

  describe("pop(head_index, count, should_count_extra)", [&]() {
    ParseStackPopResultList pop;

    before_each([&]() {
      /*
       *  A0__B1__C2.
       */
      ts_parse_stack_push(stack, 0, stateA, trees[0]);
      ts_parse_stack_push(stack, 0, stateB, trees[1]);
      ts_parse_stack_push(stack, 0, stateC, trees[2]);
    });

    it("removes the given number of nodes from the stack", [&]() {
      /*
       *  A0.
       */
      pop = ts_parse_stack_pop(stack, 0, 2, false);
      AssertThat(pop.size, Equals(1));
      AssertThat(pop.contents[0].tree_count, Equals(2));
      AssertThat(pop.contents[0].trees[0], Equals(trees[1]));
      AssertThat(pop.contents[0].trees[1], Equals(trees[2]));
      AssertThat(*ts_parse_stack_head(stack, 0), Equals<ParseStackEntry>({trees[0], stateA}));

      /*
       *  .
       */
      pop = ts_parse_stack_pop(stack, 0, 1, false);
      AssertThat(pop.size, Equals(1));
      AssertThat(pop.contents[0].tree_count, Equals(1));
      AssertThat(pop.contents[0].trees[0], Equals(trees[0]));
      AssertThat(ts_parse_stack_head(stack, 0), Equals<const ParseStackEntry *>(nullptr));
    });

    it("does not count 'extra' trees toward the count", [&]() {
      ts_tree_set_extra(trees[1]);

      pop = ts_parse_stack_pop(stack, 0, 2, false);
      AssertThat(pop.size, Equals(1));
      AssertThat(pop.contents[0].tree_count, Equals(3));
      AssertThat(pop.contents[0].trees[0], Equals(trees[0]));
      AssertThat(pop.contents[0].trees[1], Equals(trees[1]));
      AssertThat(pop.contents[0].trees[2], Equals(trees[2]));
      AssertThat(ts_parse_stack_head(stack, 0), Equals<const ParseStackEntry *>(nullptr));
    });

    it("pops the entire stack when given a negative count", [&]() {
      pop = ts_parse_stack_pop(stack, 0, -1, false);

      AssertThat(pop.size, Equals(1));
      AssertThat(pop.contents[0].tree_count, Equals(3));
      AssertThat(pop.contents[0].trees[0], Equals(trees[0]));
      AssertThat(pop.contents[0].trees[1], Equals(trees[1]));
      AssertThat(pop.contents[0].trees[2], Equals(trees[2]));
    });
  });

  describe("split(head_index)", [&]() {
    it("creates a new independent head with the same entries", [&]() {
      /*
       *  A0__B1__C2.
       */
      ts_parse_stack_push(stack, 0, stateA, trees[0]);
      ts_parse_stack_push(stack, 0, stateB, trees[1]);
      ts_parse_stack_push(stack, 0, stateC, trees[2]);

      int new_index = ts_parse_stack_split(stack, 0);
      AssertThat(ts_parse_stack_head_count(stack), Equals(2));
      AssertThat(new_index, Equals(1));

      /*
       *  A0__B1__C2__D3.
       *       \.
       */
      ts_parse_stack_push(stack, 0, stateD, trees[3]);
      ts_parse_stack_pop(stack, 1, 1, false);

      AssertThat(ts_parse_stack_head_count(stack), Equals(2));
      AssertThat(*ts_parse_stack_head(stack, 0), Equals<ParseStackEntry>({trees[3], stateD}));
      AssertThat(*ts_parse_stack_head(stack, 1), Equals<ParseStackEntry>({trees[1], stateB}));

      /*
       *  A0__B1__C2__D3.
       *       \__E4__F3.
       */
      ts_parse_stack_push(stack, 1, stateE, trees[4]);
      ts_parse_stack_push(stack, 1, stateF, trees[3]);

      AssertThat(ts_parse_stack_head_count(stack), Equals(2));
      AssertThat(*ts_parse_stack_head(stack, 0), Equals<ParseStackEntry>({trees[3], stateD}));
      AssertThat(*ts_parse_stack_head(stack, 1), Equals<ParseStackEntry>({trees[3], stateF}));
    });

    describe("when same state is pushed onto two heads", [&]() {
      bool merged;

      before_each([&]() {
        /*
         *  A0__B1__C2.
         */
        ts_parse_stack_push(stack, 0, stateA, trees[0]);
        ts_parse_stack_push(stack, 0, stateB, trees[1]);
        ts_parse_stack_push(stack, 0, stateC, trees[2]);

        /*
         *  A0__B1__C2__D3.
         *       \__E4__F5.
         */
        ts_parse_stack_split(stack, 0);
        ts_parse_stack_push(stack, 0, stateD, trees[3]);
        ts_parse_stack_pop(stack, 1, 1, false);
        ts_parse_stack_push(stack, 1, stateE, trees[4]);
        ts_parse_stack_push(stack, 1, stateF, trees[5]);

        AssertThat(ts_parse_stack_head_count(stack), Equals(2));
        AssertThat(*ts_parse_stack_head(stack, 0), Equals<ParseStackEntry>({trees[3], stateD}));
        AssertThat(*ts_parse_stack_head(stack, 1), Equals<ParseStackEntry>({trees[5], stateF}));
      });

      describe("when the trees are identical", [&]() {
        it("merges the heads, and removes nodes along both heads on subsequent pop operations", [&]() {
          /*
           *  A0__B1__C2__D3__G6.
           *       \__E4__F5__/
           */
          merged = ts_parse_stack_push(stack, 0, stateG, trees[6]);
          AssertThat(merged, IsFalse());
          merged = ts_parse_stack_push(stack, 1, stateG, trees[6]);
          AssertThat(merged, IsTrue());

          AssertThat(ts_parse_stack_head_count(stack), Equals(1));
          const ParseStackEntry *entry1 = ts_parse_stack_head(stack, 0);
          AssertThat(*entry1, Equals<ParseStackEntry>({trees[6], stateG}));
          AssertThat(ts_parse_stack_entry_next_count(entry1), Equals(2));
          AssertThat(*ts_parse_stack_entry_next(entry1, 0), Equals<ParseStackEntry>({trees[3], stateD}));
          AssertThat(*ts_parse_stack_entry_next(entry1, 1), Equals<ParseStackEntry>({trees[5], stateF}));

          /*
           *  A0__B1__C2.
           *       \__E4.
           */
          ParseStackPopResultList pop = ts_parse_stack_pop(stack, 0, 2, false);

          AssertThat(pop.size, Equals(2));
          AssertThat(pop.contents[0].tree_count, Equals(2));
          AssertThat(pop.contents[0].trees[0], Equals(trees[3]));
          AssertThat(pop.contents[0].trees[1], Equals(trees[6]));
          AssertThat(pop.contents[1].tree_count, Equals(2));
          AssertThat(pop.contents[1].trees[0], Equals(trees[5]));
          AssertThat(pop.contents[1].trees[1], Equals(trees[6]));

          AssertThat(ts_parse_stack_head_count(stack), Equals(2));
          AssertThat(*ts_parse_stack_head(stack, 0), Equals<ParseStackEntry>({trees[2], stateC}));
          AssertThat(*ts_parse_stack_head(stack, 1), Equals<ParseStackEntry>({trees[4], stateE}));
        });
      });

      describe("when the trees are different", [&]() {
        it("merges the heads by creating an ambiguity node", [&]() {
          /*
           *  A0__B1__C2__D3__G(6|7)
           *       \__E4__F5____/
           */
          merged = ts_parse_stack_push(stack, 0, stateG, trees[6]);
          AssertThat(merged, IsFalse());
          merged = ts_parse_stack_push(stack, 1, stateG, trees[7]);
          AssertThat(merged, IsTrue());

          AssertThat(ts_parse_stack_head_count(stack), Equals(1));
          AssertThat(*ts_parse_stack_head(stack, 0), Equals<ParseStackEntry>({
            ts_tree_make_ambiguity(2, tree_array({ trees[6], trees[7] })),
            stateG
          }));
        });
      });
    });
  });
});

END_TEST

bool operator==(const ParseStackEntry &left, const ParseStackEntry &right) {
  return left.state == right.state && ts_tree_eq(left.tree, right.tree);
}

std::ostream &operator<<(std::ostream &stream, const ParseStackEntry &entry) {
  return stream << "{" << entry.state << ", " << entry.tree << "}";
}
