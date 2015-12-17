#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/tree_helpers.h"
#include "runtime/stack.h"
#include "runtime/tree.h"
#include "runtime/length.h"

enum {
  stateA, stateB, stateC, stateD, stateE, stateF, stateG, stateH, stateI, stateJ
};

enum {
  symbol0, symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8
};

struct TreeSelectionSpy {
  int call_count;
  TSTree *tree_to_return;
  const TSTree *arguments[2];
};

TSLength operator*(const TSLength &length, size_t factor) {
  return {length.bytes * factor, length.chars * factor, 0, length.columns * factor};
}

extern "C"
TSTree * tree_selection_spy_callback(void *data, TSTree *left, TSTree *right) {
  TreeSelectionSpy *spy = (TreeSelectionSpy *)data;
  spy->call_count++;
  spy->arguments[0] = left;
  spy->arguments[1] = right;
  return spy->tree_to_return;
}

START_TEST


describe("Stack", [&]() {
  Stack *stack;
  const size_t tree_count = 10;
  TSTree *trees[tree_count];
  TreeSelectionSpy tree_selection_spy{0, NULL, {NULL, NULL}};
  TSLength tree_len = {2, 3, 0, 3};
  TSSymbolMetadata metadata = {true, true, true, true};

  before_each([&]() {
    stack = ts_stack_new();

    ts_stack_set_tree_selection_callback(stack, {
      &tree_selection_spy,
      tree_selection_spy_callback
    });

    for (size_t i = 0; i < tree_count; i++)
      trees[i] = ts_tree_make_leaf(i, ts_length_zero(), tree_len, {});
  });

  after_each([&]() {
    ts_stack_delete(stack);
    for (size_t i = 0; i < tree_count; i++)
      ts_tree_release(trees[i]);
  });

  describe("pushing entries to the stack", [&]() {
    it("adds entries to the stack", [&]() {
      AssertThat(ts_stack_head_count(stack), Equals(1));
      AssertThat(ts_stack_head(stack, 0), Equals<const StackEntry *>(nullptr));

      /*
       *  A0.
       */
      ts_stack_push(stack, 0, stateA, trees[0]);
      const StackEntry *entry1 = ts_stack_head(stack, 0);
      AssertThat(*entry1, Equals<StackEntry>({trees[0], stateA, tree_len}));
      AssertThat(ts_stack_entry_next_count(entry1), Equals(1));
      AssertThat(ts_stack_entry_next(entry1, 0), Equals<const StackEntry *>(nullptr));

      /*
       *  A0__B1.
       */
      ts_stack_push(stack, 0, stateB, trees[1]);
      const StackEntry *entry2 = ts_stack_head(stack, 0);
      AssertThat(*entry2, Equals<StackEntry>({trees[1], stateB, tree_len * 2}));
      AssertThat(ts_stack_entry_next_count(entry2), Equals(1));
      AssertThat(ts_stack_entry_next(entry2, 0), Equals(entry1));

      /*
       *  A0__B1__C2.
       */
      ts_stack_push(stack, 0, stateC, trees[2]);
      const StackEntry *entry3 = ts_stack_head(stack, 0);
      AssertThat(*entry3, Equals<StackEntry>({trees[2], stateC, tree_len * 3}));
      AssertThat(ts_stack_entry_next_count(entry3), Equals(1));
      AssertThat(ts_stack_entry_next(entry3, 0), Equals(entry2));
    });
  });

  describe("popping nodes from the stack", [&]() {
    before_each([&]() {
      /*
       *  A0__B1__C2.
       */
      ts_stack_push(stack, 0, stateA, trees[0]);
      ts_stack_push(stack, 0, stateB, trees[1]);
      ts_stack_push(stack, 0, stateC, trees[2]);
    });

    it("removes the given number of nodes from the stack", [&]() {
      /*
       *  A0.
       */
      Vector pop = ts_stack_pop(stack, 0, 2, false);
      StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
      AssertThat(pop.size, Equals<size_t>(1));
      AssertThat(pop1.tree_count, Equals<size_t>(2));
      AssertThat(pop1.trees[0], Equals(trees[1]));
      AssertThat(pop1.trees[1], Equals(trees[2]));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[0], stateA, tree_len}));

      /*
       *  .
       */
      pop = ts_stack_pop(stack, 0, 1, false);
      pop1 = *(StackPopResult *)vector_get(&pop, 0);
      AssertThat(pop.size, Equals<size_t>(1));
      AssertThat(pop1.tree_count, Equals<size_t>(1));
      AssertThat(pop1.trees[0], Equals(trees[0]));
      AssertThat(ts_stack_head(stack, 0), Equals<const StackEntry *>(nullptr));
    });

    it("does not count 'extra' trees toward the count", [&]() {
      ts_tree_set_extra(trees[1]);

      Vector pop = ts_stack_pop(stack, 0, 2, false);
      StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
      AssertThat(pop.size, Equals<size_t>(1));
      AssertThat(pop1.tree_count, Equals<size_t>(3));
      AssertThat(pop1.trees[0], Equals(trees[0]));
      AssertThat(pop1.trees[1], Equals(trees[1]));
      AssertThat(pop1.trees[2], Equals(trees[2]));
      AssertThat(ts_stack_head(stack, 0), Equals<const StackEntry *>(nullptr));
    });

    it("pops the entire stack when given a negative count", [&]() {
      Vector pop = ts_stack_pop(stack, 0, -1, false);

      AssertThat(pop.size, Equals<size_t>(1));
      StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
      AssertThat(pop1.tree_count, Equals<size_t>(3));
      AssertThat(pop1.trees[0], Equals(trees[0]));
      AssertThat(pop1.trees[1], Equals(trees[1]));
      AssertThat(pop1.trees[2], Equals(trees[2]));
    });
  });

  describe("splitting the stack", [&]() {
    it("creates a new independent head with the same entries", [&]() {
      /*
       *  A0__B1__C2.
       */
      ts_stack_push(stack, 0, stateA, trees[0]);
      ts_stack_push(stack, 0, stateB, trees[1]);
      ts_stack_push(stack, 0, stateC, trees[2]);

      int new_index = ts_stack_split(stack, 0);
      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(new_index, Equals(1));

      /*
       *  A0__B1__C2__D3.
       *       \.
       */
      ts_stack_push(stack, 0, stateD, trees[3]);
      ts_stack_pop(stack, 1, 1, false);

      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[3], stateD, tree_len * 4}));
      AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({trees[1], stateB, tree_len * 2}));

      /*
       *  A0__B1__C2__D3.
       *       \__E4__F3.
       */
      ts_stack_push(stack, 1, stateE, trees[4]);
      ts_stack_push(stack, 1, stateF, trees[3]);

      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[3], stateD, tree_len * 4}));
      AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({trees[3], stateF, tree_len * 4}));
    });
  });

  describe("pushing the same state onto two different heads of the stack", [&]() {
    before_each([&]() {
      /*
       *  A0__B1__C2__D3.
       *       \__E4__F5.
       */
      ts_stack_push(stack, 0, stateA, trees[0]);
      ts_stack_push(stack, 0, stateB, trees[1]);
      ts_stack_split(stack, 0);
      ts_stack_push(stack, 0, stateC, trees[2]);
      ts_stack_push(stack, 0, stateD, trees[3]);
      ts_stack_push(stack, 1, stateE, trees[4]);
      ts_stack_push(stack, 1, stateF, trees[5]);

      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[3], stateD, tree_len * 4}));
      AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({trees[5], stateF, tree_len * 4}));
    });

    describe("when the trees are identical", [&]() {
      it("merges the heads", [&]() {
        /*
         *  A0__B1__C2__D3__G6.
         *       \__E4__F5__/
         */
        bool merged = ts_stack_push(stack, 0, stateG, trees[6]);
        AssertThat(merged, IsFalse());
        merged = ts_stack_push(stack, 1, stateG, trees[6]);
        AssertThat(merged, IsTrue());

        AssertThat(ts_stack_head_count(stack), Equals(1));
        const StackEntry *entry1 = ts_stack_head(stack, 0);
        AssertThat(*entry1, Equals<StackEntry>({trees[6], stateG, tree_len * 5}));
        AssertThat(ts_stack_entry_next_count(entry1), Equals(2));
        AssertThat(*ts_stack_entry_next(entry1, 0), Equals<StackEntry>({trees[3], stateD, tree_len * 4}));
        AssertThat(*ts_stack_entry_next(entry1, 1), Equals<StackEntry>({trees[5], stateF, tree_len * 4}));
      });
    });

    describe("when the trees are different", [&]() {
      before_each([&]() {
        tree_selection_spy.tree_to_return = trees[7];
        AssertThat(tree_selection_spy.call_count, Equals(0));
      });

      it("merges the heads, selecting the tree with the tree selection callback", [&]() {
        /*
         *  A0__B1__C2__D3__G(6|7)
         *       \__E4__F5____/
         */
        bool merged = ts_stack_push(stack, 0, stateG, trees[6]);
        AssertThat(merged, IsFalse());
        merged = ts_stack_push(stack, 1, stateG, trees[7]);
        AssertThat(merged, IsTrue());

        AssertThat(ts_stack_head_count(stack), Equals(1));
        AssertThat(tree_selection_spy.call_count, Equals(1));
        AssertThat(tree_selection_spy.arguments[0], Equals(trees[6]));
        AssertThat(tree_selection_spy.arguments[1], Equals(trees[7]));
        AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[7], stateG, tree_len * 5}));
      });
    });

    describe("when successor nodes of the merged nodes have the same state", [&]() {
      it("recursively merges those successor nodes", [&]() {
        /*
         *  A0__B1__C2__D3__G6__H7.
         *       \__E4__F5__G6.
         */
        bool merged = ts_stack_push(stack, 0, stateG, trees[6]);
        AssertThat(merged, IsFalse());
        merged = ts_stack_push(stack, 0, stateH, trees[7]);
        AssertThat(merged, IsFalse());
        merged = ts_stack_push(stack, 1, stateG, trees[6]);
        AssertThat(merged, IsFalse());

        /*
         *  A0__B1__C2__D3__G6__H7.
         *       \__E4__F5_/
         */
        merged = ts_stack_push(stack, 1, stateH, trees[7]);
        AssertThat(merged, IsTrue());

        AssertThat(ts_stack_head_count(stack), Equals(1));
        StackEntry *head = ts_stack_head(stack, 0);
        AssertThat(*head, Equals<StackEntry>({trees[7], stateH, tree_len * 6}))
        AssertThat(ts_stack_entry_next_count(head), Equals(1));

        StackEntry *next = ts_stack_entry_next(head, 0);
        AssertThat(*next, Equals<StackEntry>({trees[6], stateG, tree_len * 5}))
        AssertThat(ts_stack_entry_next_count(next), Equals(2));
      });
    });

    describe("when the first head is only one node deep", [&]() {
      it("adds it as an additional successor node to The Null node", [&]() {
        /*
         *    .__C5.
         *  B2.__/
         */
        ts_stack_clear(stack);
        ts_stack_split(stack, 0);
        TSTree *parent = ts_tree_make_node(5, 2, tree_array({ trees[2], trees[3] }), metadata);

        ts_stack_push(stack, 0, stateC, parent);

        tree_selection_spy.tree_to_return = parent;
        tree_selection_spy.call_count = 0;

        bool merged = ts_stack_push(stack, 1, stateB, trees[2]);
        AssertThat(merged, IsFalse());
        merged = ts_stack_push(stack, 1, stateC, trees[3]);
        AssertThat(merged, IsTrue());
        AssertThat(tree_selection_spy.call_count, Equals(1));

        AssertThat(ts_stack_head_count(stack), Equals(1));
        StackEntry *head = ts_stack_head(stack, 0);
        AssertThat(*head, Equals<StackEntry>({parent, stateC, tree_len * 2}));

        AssertThat(ts_stack_entry_next_count(head), Equals(2));
        AssertThat(ts_stack_entry_next(head, 0), Equals<StackEntry *>(nullptr));
        AssertThat(*ts_stack_entry_next(head, 1), Equals<StackEntry>({trees[2], stateB, tree_len}));
      });
    });
  });

  describe("popping from a stack head that has been merged", [&]() {
    before_each([&]() {
      /*
       *  A0__B1__C2__D3__G6.
       *       \__E4__F5__/
       */
      ts_stack_push(stack, 0, stateA, trees[0]);
      ts_stack_push(stack, 0, stateB, trees[1]);
      ts_stack_split(stack, 0);
      ts_stack_push(stack, 0, stateC, trees[2]);
      ts_stack_push(stack, 0, stateD, trees[3]);
      ts_stack_push(stack, 0, stateG, trees[6]);
      ts_stack_push(stack, 1, stateE, trees[4]);
      ts_stack_push(stack, 1, stateF, trees[5]);
      ts_stack_push(stack, 1, stateG, trees[6]);

      AssertThat(ts_stack_head_count(stack), Equals(1));
      AssertThat(ts_stack_entry_next_count(ts_stack_head(stack, 0)), Equals(2));
    });

    describe("when there are two paths that lead to two different heads", [&]() {
      it("returns an entry for each revealed head", [&]() {
        /*
         *  A0__B1__C2.
         *       \__E4.
         */
        Vector pop = ts_stack_pop(stack, 0, 2, false);

        AssertThat(pop.size, Equals<size_t>(2));
        StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
        AssertThat(pop1.head_index, Equals(0));
        AssertThat(pop1.tree_count, Equals<size_t>(2));
        AssertThat(pop1.trees[0], Equals(trees[3]));
        AssertThat(pop1.trees[1], Equals(trees[6]));

        StackPopResult pop2 = *(StackPopResult *)vector_get(&pop, 1);
        AssertThat(pop2.head_index, Equals(1));
        AssertThat(pop2.tree_count, Equals<size_t>(2));
        AssertThat(pop2.trees[0], Equals(trees[5]));
        AssertThat(pop2.trees[1], Equals(trees[6]));

        AssertThat(ts_stack_head_count(stack), Equals(2));
        AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[2], stateC, tree_len * 3}));
        AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({trees[4], stateE, tree_len * 3}));
      });
    });

    describe("when there is one path, leading to one head", [&]() {
      it("returns a single entry", [&]() {
        /*
         *  A0__B1__C2__D3__G6__H7.
         *       \__E4__F5__/
         */
        bool merged = ts_stack_push(stack, 0, stateH, trees[7]);
        AssertThat(merged, IsFalse());
        AssertThat(ts_stack_head_count(stack), Equals(1));

        /*
         *  A0__B1__C2__D3__G6.
         *       \__E4__F5__/
         */
        Vector pop = ts_stack_pop(stack, 0, 1, false);

        AssertThat(pop.size, Equals<size_t>(1));
        AssertThat(ts_stack_head_count(stack), Equals(1));
      });
    });

    describe("when there is one path that leads to two different heads", [&]() {
      it("returns two entries with the same array of trees", [&]() {
        /*
         *  A0__B1__C2__D3__G6__H7.
         *       \__E4__F5__/
         */
        ts_stack_push(stack, 0, stateH, trees[7]);


        /*
         *  A0__B1__C2__D3.
         *       \__E4__F5.
         */
        Vector pop = ts_stack_pop(stack, 0, 2, false);
        AssertThat(ts_stack_head_count(stack), Equals(2));

        AssertThat(pop.size, Equals<size_t>(2));
        StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
        AssertThat(pop1.head_index, Equals(0));
        AssertThat(pop1.tree_count, Equals<size_t>(2));
        AssertThat(pop1.trees[0], Equals(trees[6]));
        AssertThat(pop1.trees[1], Equals(trees[7]));

        StackPopResult pop2 = *(StackPopResult *)vector_get(&pop, 1);
        AssertThat(pop2.head_index, Equals(1));
        AssertThat(pop2.tree_count, Equals<size_t>(2));
        AssertThat(pop2.trees[0], Equals(trees[6]));
        AssertThat(pop2.trees[1], Equals(trees[7]));
      });
    });

    describe("when there are two paths that converge at the same head", [&]() {
      it("returns two entries for that head", [&]() {
        /*
         *  A0__B1.
         */
        Vector pop = ts_stack_pop(stack, 0, 3, false);
        AssertThat(ts_stack_head_count(stack), Equals(1));
        AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({trees[1], stateB, tree_len * 2}));

        AssertThat(pop.size, Equals<size_t>(2));
        StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
        AssertThat(pop1.tree_count, Equals<size_t>(3));
        AssertThat(pop1.head_index, Equals(0));
        AssertThat(pop1.trees[0], Equals(trees[2]));

        StackPopResult pop2 = *(StackPopResult *)vector_get(&pop, 1);
        AssertThat(pop2.tree_count, Equals<size_t>(3));
        AssertThat(pop2.head_index, Equals(0));
        AssertThat(pop2.trees[0], Equals(trees[4]));
      });
    });
  });

  describe("popping from a stack head that has been 3-way merged", [&]() {
    before_each([&]() {
      /*
       *  A0__B1__C2__D3__I8__J9.
       *       \__E4__F5__/
       *       \__G6__H7__/
       */
      ts_stack_clear(stack);
      ts_stack_push(stack, 0, stateA, trees[0]);
      ts_stack_push(stack, 0, stateB, trees[1]);
      ts_stack_split(stack, 0);
      ts_stack_split(stack, 1);
      ts_stack_push(stack, 0, stateC, trees[2]);
      ts_stack_push(stack, 1, stateE, trees[4]);
      ts_stack_push(stack, 2, stateG, trees[6]);
      ts_stack_push(stack, 0, stateD, trees[3]);
      ts_stack_push(stack, 1, stateF, trees[5]);
      ts_stack_push(stack, 2, stateH, trees[7]);
      ts_stack_push(stack, 0, stateI, trees[8]);
      ts_stack_push(stack, 1, stateI, trees[8]);
      ts_stack_push(stack, 1, stateI, trees[8]);
      ts_stack_push(stack, 0, stateJ, trees[9]);

      AssertThat(ts_stack_head_count(stack), Equals(1));
      StackEntry *head = ts_stack_head(stack, 0);
      AssertThat(ts_stack_entry_next_count(head), Equals(1));
      AssertThat(ts_stack_entry_next_count(ts_stack_entry_next(head, 0)), Equals(3));
    });

    describe("when there is one path that leads to three different heads", [&]() {
      it("returns three entries with the same array of trees", [&]() {
        /*
         *  A0__B1__C2__D3.
         *       \__E4__F5.
         *       \__G6__H7.
         */
        Vector pop = ts_stack_pop(stack, 0, 2, false);
        AssertThat(ts_stack_head_count(stack), Equals(3));

        AssertThat(pop.size, Equals<size_t>(3));

        StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
        AssertThat(ts_stack_top_tree(stack, 0), Equals(trees[3]));
        AssertThat(pop1.head_index, Equals(0));
        AssertThat(pop1.tree_count, Equals<size_t>(2));
        AssertThat(pop1.trees[0], Equals(trees[8]));
        AssertThat(pop1.trees[1], Equals(trees[9]));

        StackPopResult pop2 = *(StackPopResult *)vector_get(&pop, 1);
        AssertThat(ts_stack_top_tree(stack, 1), Equals(trees[5]));
        AssertThat(pop2.head_index, Equals(1));
        AssertThat(pop2.tree_count, Equals<size_t>(2));
        AssertThat(pop2.trees, Equals(pop1.trees));

        StackPopResult pop3 = *(StackPopResult *)vector_get(&pop, 2);
        AssertThat(ts_stack_top_tree(stack, 2), Equals(trees[7]));
        AssertThat(pop3.head_index, Equals(2));
        AssertThat(pop3.tree_count, Equals<size_t>(2));
        AssertThat(pop3.trees, Equals(pop1.trees));
      });
    });

    describe("when there are three different paths that lead to three different heads", [&]() {
      it("returns three entries with different arrays of trees", [&]() {
        /*
         *  A0__B1__C2.
         *       \__E4.
         *       \__G6.
         */
        Vector pop = ts_stack_pop(stack, 0, 3, false);
        AssertThat(ts_stack_head_count(stack), Equals(3));

        AssertThat(pop.size, Equals<size_t>(3));

        StackPopResult pop1 = *(StackPopResult *)vector_get(&pop, 0);
        AssertThat(ts_stack_top_tree(stack, 0), Equals(trees[2]));
        AssertThat(pop1.head_index, Equals(0));
        AssertThat(pop1.tree_count, Equals<size_t>(3));
        AssertThat(pop1.trees[0], Equals(trees[3]));
        AssertThat(pop1.trees[1], Equals(trees[8]));
        AssertThat(pop1.trees[2], Equals(trees[9]));

        StackPopResult pop2 = *(StackPopResult *)vector_get(&pop, 1);
        AssertThat(ts_stack_top_tree(stack, 1), Equals(trees[4]));
        AssertThat(pop2.head_index, Equals(1));
        AssertThat(pop2.tree_count, Equals<size_t>(3));
        AssertThat(pop2.trees[0], Equals(trees[5]));
        AssertThat(pop2.trees[1], Equals(trees[8]));
        AssertThat(pop2.trees[2], Equals(trees[9]));

        StackPopResult pop3 = *(StackPopResult *)vector_get(&pop, 2);
        AssertThat(ts_stack_top_tree(stack, 2), Equals(trees[6]));
        AssertThat(pop3.head_index, Equals(2));
        AssertThat(pop3.tree_count, Equals<size_t>(3));
        AssertThat(pop3.trees[0], Equals(trees[7]));
        AssertThat(pop3.trees[1], Equals(trees[8]));
        AssertThat(pop3.trees[2], Equals(trees[9]));
      });
    });
  });
});

END_TEST

bool operator==(const StackEntry &left, const StackEntry &right) {
  return left.state == right.state && ts_tree_eq(left.tree, right.tree) && ts_length_eq(left.position, right.position);
}

std::ostream &operator<<(std::ostream &stream, const StackEntry &entry) {
  return stream << "{" << entry.state << ", " << entry.tree << ", " << entry.position << "}";
}
