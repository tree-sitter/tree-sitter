#include "spec_helper.h"
#include "helpers/tree_helpers.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "runtime/stack.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/alloc.h"

enum {
  stateA, stateB, stateC, stateD, stateE, stateF, stateG, stateH, stateI, stateJ
};

enum {
  symbol0, symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8,
  symbol9, symbol10
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
int tree_selection_spy_callback(void *data, TSTree *left, TSTree *right) {
  TreeSelectionSpy *spy = (TreeSelectionSpy *)data;
  spy->call_count++;
  spy->arguments[0] = left;
  spy->arguments[1] = right;
  if (spy->tree_to_return == left)
    return -1;
  else
    return 1;
}

void free_pop_results(StackPopResultArray *pop_results) {
  for (size_t i = 0; i < pop_results->size; i++) {
    StackPopResult pop_result = pop_results->contents[i];

    bool matches_prior_trees = false;
    for (size_t j = 0; j < i; j++) {
      StackPopResult prior_result = pop_results->contents[j];
      if (pop_result.trees.contents == prior_result.trees.contents) {
        matches_prior_trees = true;
        break;
      }
    }

    if (!matches_prior_trees) {
      for (size_t j = 0; j < pop_result.trees.size; j++)
        ts_tree_release(pop_result.trees.contents[j]);
      array_delete(&pop_result.trees);
    }
  }
}

START_TEST

describe("Stack", [&]() {
  Stack *stack;
  const size_t tree_count = 11;
  TSTree *trees[tree_count];
  TreeSelectionSpy tree_selection_spy{0, NULL, {NULL, NULL}};
  TSLength tree_len = {2, 3, 0, 3};
  TSSymbolMetadata metadata = {true, true, true, true};

  before_each([&]()   {
    record_alloc::start();

    stack = ts_stack_new();

    ts_stack_set_tree_selection_callback(stack,
      &tree_selection_spy,
      tree_selection_spy_callback
    );

    for (size_t i = 0; i < tree_count; i++)
      trees[i] = ts_tree_make_leaf(i, ts_length_zero(), tree_len, {
        true, true, false, true,
      });
  });

  after_each([&]() {
    ts_stack_delete(stack);
    for (size_t i = 0; i < tree_count; i++)
      ts_tree_release(trees[i]);

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  describe("pushing entries to the stack", [&]() {
    it("adds entries to the stack", [&]() {
      AssertThat(ts_stack_head_count(stack), Equals(1));
      AssertThat(ts_stack_head(stack, 0), Equals<const StackEntry *>(nullptr));

      /*
       *  . <--0-- A*
       */
      ts_stack_push(stack, 0, trees[0], stateA);
      const StackEntry *entry1 = ts_stack_head(stack, 0);
      AssertThat(*entry1, Equals<StackEntry>({stateA, tree_len}));
      AssertThat(ts_stack_entry_next_count(entry1), Equals(1));
      AssertThat(ts_stack_entry_next(entry1, 0), Equals<const StackEntry *>(nullptr));

      /*
       *  . <--0-- A <--1-- B*
       */
      ts_stack_push(stack, 0, trees[1], stateB);
      const StackEntry *entry2 = ts_stack_head(stack, 0);
      AssertThat(*entry2, Equals<StackEntry>({stateB, tree_len * 2}));
      AssertThat(ts_stack_entry_next_count(entry2), Equals(1));
      AssertThat(ts_stack_entry_next(entry2, 0), Equals(entry1));

      /*
       *  . <--0-- A <--1-- B <--2-- C*
       */
      ts_stack_push(stack, 0, trees[2], stateC);
      const StackEntry *entry3 = ts_stack_head(stack, 0);
      AssertThat(*entry3, Equals<StackEntry>({stateC, tree_len * 3}));
      AssertThat(ts_stack_entry_next_count(entry3), Equals(1));
      AssertThat(ts_stack_entry_next(entry3, 0), Equals(entry2));
    });
  });

  describe("popping nodes from the stack", [&]() {
    before_each([&]() {
      /*
       *  . <--0-- A <--1-- B <--2-- C*
       */
      ts_stack_push(stack, 0, trees[0], stateA);
      ts_stack_push(stack, 0, trees[1], stateB);
      ts_stack_push(stack, 0, trees[2], stateC);
    });

    it("removes the given number of nodes from the stack", [&]() {
      /*
       *  . <--0-- A*
       */
      StackPopResultArray results = ts_stack_pop(stack, 0, 2, false);
      AssertThat(results.size, Equals<size_t>(1));

      StackPopResult result = results.contents[0];
      AssertThat(result.trees, Equals(vector<TSTree *>({ trees[1], trees[2] })));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateA, tree_len}));
      free_pop_results(&results);

      /*
       *  .
       */
      results = ts_stack_pop(stack, 0, 1, false);
      AssertThat(results.size, Equals<size_t>(1));

      result = results.contents[0];
      AssertThat(result.trees, Equals(vector<TSTree *>({ trees[0] })));
      AssertThat(ts_stack_head(stack, 0), Equals<const StackEntry *>(nullptr));

      free_pop_results(&results);
    });

    it("does not count 'extra' trees toward the count", [&]() {
      trees[1]->extra = true;

      /*
       *  .
       */
      StackPopResultArray results = ts_stack_pop(stack, 0, 2, false);
      AssertThat(results.size, Equals<size_t>(1));

      StackPopResult result = results.contents[0];
      AssertThat(result.trees, Equals(vector<TSTree *>({ trees[0], trees[1], trees[2] })));
      AssertThat(ts_stack_head(stack, 0), Equals<const StackEntry *>(nullptr));

      free_pop_results(&results);
    });

    it("pops the entire stack when given a negative count", [&]() {
      /*
       *  .
       */
      StackPopResultArray results = ts_stack_pop(stack, 0, -1, false);
      AssertThat(results.size, Equals<size_t>(1));

      StackPopResult result = results.contents[0];
      AssertThat(result.trees, Equals(vector<TSTree *>({ trees[0], trees[1], trees[2] })));

      free_pop_results(&results);
    });
  });

  describe("splitting the stack", [&]() {
    it("creates a new independent head with the same entries", [&]() {
      /*
       *  . <--0-- A <--1-- B <--2-- C*
       */
      ts_stack_push(stack, 0, trees[0], stateA);
      ts_stack_push(stack, 0, trees[1], stateB);
      ts_stack_push(stack, 0, trees[2], stateC);

      /*
       *  . <--0-- A <--1-- B <--2-- C*
       *                             ↑
       *                             `-*
       */
      int new_index = ts_stack_split(stack, 0);
      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(new_index, Equals(1));
      AssertThat(ts_stack_top_state(stack, 1), Equals(stateC));

      /*
       *  . <--0-- A <--1-- B <--2-- C <--3-- D*
       *                    ↑
       *                    `-*
       */
      ts_stack_push(stack, 0, trees[3], stateD);
      StackPopResultArray pop_results = ts_stack_pop(stack, 1, 1, false);

      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateD, tree_len * 4}));
      AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({stateB, tree_len * 2}));
      AssertThat(pop_results.size, Equals<size_t>(1));
      StackPopResult pop_result = pop_results.contents[0];
      AssertThat(pop_result.trees.size, Equals<size_t>(1));
      free_pop_results(&pop_results);

      /*
       *  . <--0-- A <--1-- B <--2-- C <--3-- D*
       *                    ↑
       *                    `---4--- E <--5-- F*
       */
      ts_stack_push(stack, 1, trees[4], stateE);
      ts_stack_push(stack, 1, trees[5], stateF);

      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateD, tree_len * 4}));
      AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({stateF, tree_len * 4}));
    });
  });

  describe("pushing the same state onto two different heads of the stack", [&]() {
    before_each([&]() {
      /*
       *  . <--0-- A <--1-- B <--2-- C <--3-- D*
       *                    ↑
       *                    `---4--- E <--5-- F*
       */
      ts_stack_push(stack, 0, trees[0], stateA);
      ts_stack_push(stack, 0, trees[1], stateB);
      ts_stack_split(stack, 0);
      ts_stack_push(stack, 0, trees[2], stateC);
      ts_stack_push(stack, 0, trees[3], stateD);
      ts_stack_push(stack, 1, trees[4], stateE);
      ts_stack_push(stack, 1, trees[5], stateF);

      AssertThat(ts_stack_head_count(stack), Equals(2));
      AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateD, tree_len * 4}));
      AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({stateF, tree_len * 4}));
    });

    it("merges the heads", [&]() {
      /*
       *  . <--0-- A <--1-- B <--2-- C <--3-- D <--6-- G*
       *                    ^                          |
       *                    `---4--- E <--5-- F <--7---'
       */
      AssertThat(ts_stack_push(stack, 0, trees[6], stateG), Equals(StackPushResultContinued));
      AssertThat(ts_stack_push(stack, 1, trees[7], stateG), Equals(StackPushResultMerged));

      AssertThat(ts_stack_head_count(stack), Equals(1));
      const StackEntry *entry1 = ts_stack_head(stack, 0);
      AssertThat(*entry1, Equals<StackEntry>({stateG, tree_len * 5}));
      AssertThat(ts_stack_entry_next_count(entry1), Equals(2));
      AssertThat(*ts_stack_entry_next(entry1, 0), Equals<StackEntry>({stateD, tree_len * 4}));
      AssertThat(*ts_stack_entry_next(entry1, 1), Equals<StackEntry>({stateF, tree_len * 4}));
    });

    describe("when the merged nodes share a successor", [&]() {
      it("recursively merges the successor nodes", [&]() {
        /*
         *  . <--0-- A <--1-- B <--2-- C <--3-- D <--6-- G <--7--H*
         *                    ↑
         *                    `---4--- E <--5-- F <--8-- G*
         */
        AssertThat(ts_stack_push(stack, 0, trees[6], stateG), Equals(StackPushResultContinued));
        AssertThat(ts_stack_push(stack, 0, trees[7], stateH), Equals(StackPushResultContinued));
        AssertThat(ts_stack_push(stack, 1, trees[6], stateG), Equals(StackPushResultContinued));

        /*
         *  . <--0-- A <--1-- B <--2-- C <--3-- D <--6-- G <--7--H*
         *                    ↑                          |
         *                    `---4--- E <--5-- F <--8---'
         */
        AssertThat(ts_stack_push(stack, 1, trees[7], stateH), Equals(StackPushResultMerged));

        AssertThat(ts_stack_head_count(stack), Equals(1));
        StackEntry *head = ts_stack_head(stack, 0);
        AssertThat(*head, Equals<StackEntry>({stateH, tree_len * 6}))
        AssertThat(ts_stack_entry_next_count(head), Equals(1));

        StackEntry *next = ts_stack_entry_next(head, 0);
        AssertThat(*next, Equals<StackEntry>({stateG, tree_len * 5}))
        AssertThat(ts_stack_entry_next_count(next), Equals(2));
      });
    });

    describe("when the first head is only one node deep", [&]() {
      it("creates a node with one null successor and one non-null successor", [&]() {
        ts_tree_retain(trees[2]);
        ts_tree_retain(trees[3]);
        TSTree *parent = ts_tree_make_node(5, 2, tree_array({ trees[2], trees[3] }), metadata);

        /*
         *  . <--2-- B <--3-- C
         *  ^                 |
         *  `--------5--------'
         */
        ts_stack_clear(stack);
        ts_stack_split(stack, 0);
        AssertThat(ts_stack_push(stack, 0, parent, stateC), Equals(StackPushResultContinued));
        AssertThat(ts_stack_push(stack, 1, trees[2], stateB), Equals(StackPushResultContinued));
        AssertThat(ts_stack_push(stack, 1, trees[3], stateC), Equals(StackPushResultMerged));

        AssertThat(ts_stack_head_count(stack), Equals(1));
        StackEntry *head = ts_stack_head(stack, 0);
        AssertThat(*head, Equals<StackEntry>({stateC, tree_len * 2}));

        AssertThat(ts_stack_entry_next_count(head), Equals(2));
        AssertThat(ts_stack_entry_next(head, 0), Equals<StackEntry *>(nullptr));
        AssertThat(*ts_stack_entry_next(head, 1), Equals<StackEntry>({stateB, tree_len}));

        ts_tree_release(parent);
      });
    });
  });

  describe("popping from a stack head that has been merged", [&]() {
    before_each([&]() {
      /*
       *  . <--0-- A <--1-- B <--2-- C <--3-- D <--4-- E*
       *                    ^                          |
       *                    `---5--- F <--6-- G <--7---'
       */
      ts_stack_push(stack, 0, trees[0], stateA);
      ts_stack_push(stack, 0, trees[1], stateB);
      ts_stack_split(stack, 0);
      ts_stack_push(stack, 0, trees[2], stateC);
      ts_stack_push(stack, 0, trees[3], stateD);
      ts_stack_push(stack, 0, trees[4], stateE);
      ts_stack_push(stack, 1, trees[5], stateF);
      ts_stack_push(stack, 1, trees[6], stateG);
      ts_stack_push(stack, 1, trees[7], stateE);

      AssertThat(ts_stack_head_count(stack), Equals(1));
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateE));
      AssertThat(ts_stack_entry_next_count(ts_stack_head(stack, 0)), Equals(2));
    });

    describe("when there are two paths that lead to two different heads", [&]() {
      it("returns an entry for each revealed head", [&]() {
        /*
         *  . <--0-- A <--1-- B <--2-- C*
         *                    ^
         *                    `---5--- F*
         */
        StackPopResultArray results = ts_stack_pop(stack, 0, 2, false);

        AssertThat(results.size, Equals<size_t>(2));
        StackPopResult result1 = results.contents[0];
        AssertThat(result1.head_index, Equals(0));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateC));
        AssertThat(result1.trees, Equals(vector<TSTree *>({ trees[3], trees[4] })));

        StackPopResult result2 = results.contents[1];
        AssertThat(result2.head_index, Equals(1));
        AssertThat(ts_stack_top_state(stack, 1), Equals(stateF));
        AssertThat(result2.trees, Equals(vector<TSTree *>({ trees[6], trees[7] })));

        AssertThat(ts_stack_head_count(stack), Equals(2));
        AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateC, tree_len * 3}));
        AssertThat(*ts_stack_head(stack, 1), Equals<StackEntry>({stateF, tree_len * 3}));

        free_pop_results(&results);
      });
    });

    describe("when there is one path, leading to one head", [&]() {
      it("returns a single entry", [&]() {
        /*
         *  . <--0-- A <--1-- B <--2-- C <--3-- D <--4-- E <--8--H*
         *                    ^                          |
         *                    `---5--- F <--6-- G <--7---'
         */
        AssertThat(ts_stack_push(stack, 0, trees[8], stateH), Equals(StackPushResultContinued));
        AssertThat(ts_stack_head_count(stack), Equals(1));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateH));

        /*
         *  . <--0-- A <--1-- B <--2-- C <--3-- D <--4-- E*
         *                    ^                          |
         *                    `---5--- F <--6-- G <--7---'
         */
        StackPopResultArray results = ts_stack_pop(stack, 0, 1, false);
        AssertThat(results.size, Equals<size_t>(1));
        StackPopResult result1 = results.contents[0];
        AssertThat(result1.head_index, Equals(0));
        AssertThat(result1.trees, Equals(vector<TSTree *>({ trees[8] })));

        AssertThat(ts_stack_head_count(stack), Equals(1));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateE));

        free_pop_results(&results);
      });
    });

    describe("when there are two paths that converge at the same head", [&]() {
      describe("when the first path is preferred by the callback", [&]() {
        it("returns one entry for that head, with the first path of trees", [&]() {
          tree_selection_spy.tree_to_return = trees[2];

          /*
           *  . <--0-- A <--1-- B*
           */
          StackPopResultArray results = ts_stack_pop(stack, 0, 3, false);
          AssertThat(ts_stack_head_count(stack), Equals(1));
          AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateB, tree_len * 2}));

          AssertThat(results.size, Equals<size_t>(1));
          StackPopResult result1 = results.contents[0];
          AssertThat(result1.head_index, Equals(0));
          AssertThat(result1.trees, Equals(vector<TSTree *>({ trees[2], trees[3], trees[4] })));

          free_pop_results(&results);
        });
      });

      describe("when the second path is preferred by the callback", [&]() {
        it("returns one entry for that head, with the second path of trees", [&]() {
          tree_selection_spy.tree_to_return = trees[4];

          /*
           *  . <--0-- A <--1-- B*
           */
          StackPopResultArray results = ts_stack_pop(stack, 0, 3, false);
          AssertThat(ts_stack_head_count(stack), Equals(1));
          AssertThat(*ts_stack_head(stack, 0), Equals<StackEntry>({stateB, tree_len * 2}));

          AssertThat(results.size, Equals<size_t>(1));
          StackPopResult result1 = results.contents[0];
          AssertThat(result1.head_index, Equals(0));
          AssertThat(result1.trees, Equals(vector<TSTree *>({ trees[5], trees[6], trees[7] })))

          free_pop_results(&results);
        });
      });
    });
  });

  describe("popping from a stack head that has been 3-way merged", [&]() {
    before_each([&]() {
      /*
       *  . <--0-- A <--1-- B <--2-- C <--3-- D <--10-- I
       *           ^                          |
       *           `---4--- E <--5-- F <--6---'
       *           |                          |
       *           `---7--- G <--8-- H <--9---'
       */
      ts_stack_clear(stack);
      ts_stack_push(stack, 0, trees[0], stateA);
      ts_stack_split(stack, 0);
      ts_stack_split(stack, 1);
      ts_stack_push(stack, 0, trees[1], stateB);
      ts_stack_push(stack, 0, trees[2], stateC);
      ts_stack_push(stack, 0, trees[3], stateD);
      ts_stack_push(stack, 1, trees[4], stateE);
      ts_stack_push(stack, 1, trees[5], stateF);
      ts_stack_push(stack, 1, trees[6], stateD);
      ts_stack_push(stack, 1, trees[7], stateG);
      ts_stack_push(stack, 1, trees[8], stateH);
      ts_stack_push(stack, 1, trees[9], stateD);
      AssertThat(ts_stack_head_count(stack), Equals(1));
      AssertThat(ts_stack_entry_next_count(ts_stack_head(stack, 0)), Equals(3));
      ts_stack_push(stack, 0, trees[10], stateI);
      AssertThat(ts_stack_entry_next_count(ts_stack_head(stack, 0)), Equals(1));
    });

    describe("when there are three different paths that lead to three different heads", [&]() {
      it("returns three entries with different arrays of trees", [&]() {
        /*
         *  . <--0-- A <--1-- B <--2-- C*
         *           ^
         *           `---4--- E <--5-- F*
         *           |
         *           `---7--- G <--8-- H*
         */
        StackPopResultArray results = ts_stack_pop(stack, 0, 2, false);
        AssertThat(ts_stack_head_count(stack), Equals(3));

        AssertThat(results.size, Equals<size_t>(3));

        StackPopResult result1 = results.contents[0];
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateC));
        AssertThat(result1.head_index, Equals(0));
        AssertThat(result1.trees, Equals(vector<TSTree *>({ trees[3], trees[10] })))

        StackPopResult result2 = results.contents[1];
        AssertThat(ts_stack_top_state(stack, 1), Equals(stateF));
        AssertThat(result2.head_index, Equals(1));
        AssertThat(result2.trees, Equals(vector<TSTree *>({ trees[6], trees[10] })))

        StackPopResult result3 = results.contents[2];
        AssertThat(ts_stack_top_state(stack, 2), Equals(stateH));
        AssertThat(result3.head_index, Equals(2));
        AssertThat(result3.trees, Equals(vector<TSTree *>({ trees[9], trees[10] })))

        free_pop_results(&results);
      });
    });
  });
});

END_TEST

bool operator==(const StackEntry &left, const StackEntry &right) {
  return left.state == right.state && ts_length_eq(left.position, right.position);
}

std::ostream &operator<<(std::ostream &stream, const StackEntry &entry) {
  return stream << "{" << entry.state << ", " << entry.position << "}";
}

std::ostream &operator<<(std::ostream &stream, const TreeArray &array) {
  stream << "[";
  bool first = true;
  for (size_t i = 0; i < array.size; i++) {
    if (!first)
      stream << ", ";
    first = false;
    stream << array.contents[i];
  }
  return stream << "]";
}
