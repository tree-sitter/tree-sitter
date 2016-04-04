#include "spec_helper.h"
#include "helpers/tree_helpers.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "runtime/stack.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/alloc.h"

enum {
  stateA = 1,
  stateB,
  stateC, stateD, stateE, stateF, stateG, stateH, stateI, stateJ
};

enum {
  symbol0, symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8,
  symbol9, symbol10
};

struct TreeSelectionSpy {
  TreeSelectionSpy() :
    call_count(0),
    tree_to_return(nullptr),
    arguments{nullptr, nullptr} {}
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

void free_slice_array(StackSliceArray *slices) {
  for (size_t i = 0; i < slices->size; i++) {
    StackSlice slice = slices->contents[i];

    bool matches_prior_trees = false;
    for (size_t j = 0; j < i; j++) {
      StackSlice prior_slice = slices->contents[j];
      if (slice.trees.contents == prior_slice.trees.contents) {
        matches_prior_trees = true;
        break;
      }
    }

    if (!matches_prior_trees) {
      for (size_t j = 0; j < slice.trees.size; j++)
        ts_tree_release(slice.trees.contents[j]);
      array_delete(&slice.trees);
    }
  }
}

struct StackEntry {
  TSStateId state;
  size_t depth;
};

vector<StackEntry> get_stack_entries(Stack *stack, StackVersion version) {
  vector<StackEntry> result;
  ts_stack_pop_until(
    stack,
    version,
    [](void *payload, TSStateId state, size_t tree_count, bool is_done, bool is_pending) {
      auto entries = static_cast<vector<StackEntry> *>(payload);
      StackEntry entry = {state, tree_count};
      if (find(entries->begin(), entries->end(), entry) == entries->end())
        entries->push_back(entry);
      return StackIterateContinue;
    }, &result);
  return result;
}

START_TEST

describe("Stack", [&]() {
  Stack *stack;
  const size_t tree_count = 11;
  TSTree *trees[tree_count];
  TreeSelectionSpy tree_selection_spy;
  TSLength tree_len = {2, 3, 0, 3};
  TSSymbolMetadata metadata = {true, true, true, true};

  before_each([&]() {
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
      AssertThat(ts_stack_version_count(stack), Equals(1));
      AssertThat(ts_stack_top_state(stack, 0), Equals(0));
      AssertThat(ts_stack_top_position(stack, 0), Equals(ts_length_zero()));

      // . <──0── A*
      ts_stack_push(stack, 0, trees[0], false, stateA);
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateA));
      AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len));

      // . <──0── A <──1── B*
      ts_stack_push(stack, 0, trees[1], false, stateB);
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateB));
      AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len * 2));

      // . <──0── A <──1── B <──2── C*
      ts_stack_push(stack, 0, trees[2], false, stateC);
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateC));
      AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len * 3));

      AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
        {stateC, 0},
        {stateB, 1},
        {stateA, 2},
        {0, 3},
      })));
    });
  });

  describe("popping nodes from the stack", [&]() {
    before_each([&]() {
      // . <──0── A <──1── B <──2── C*
      ts_stack_push(stack, 0, trees[0], false, stateA);
      ts_stack_push(stack, 0, trees[1], false, stateB);
      ts_stack_push(stack, 0, trees[2], false, stateC);
    });

    it("removes the given number of nodes from the stack", [&]() {
      // . <──0── A*
      StackPopResult pop_result = ts_stack_pop_count(stack, 0, 2);
      AssertThat(pop_result.status, Equals(StackPopResult::StackPopSucceeded));
      AssertThat(pop_result.slices.size, Equals<size_t>(1));

      StackSlice slice = pop_result.slices.contents[0];
      AssertThat(slice.trees, Equals(vector<TSTree *>({ trees[1], trees[2] })));
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateA));
      free_slice_array(&pop_result.slices);

      // .*
      pop_result = ts_stack_pop_count(stack, 0, 1);
      AssertThat(pop_result.status, Equals(StackPopResult::StackPopSucceeded));
      AssertThat(pop_result.slices.size, Equals<size_t>(1));

      slice = pop_result.slices.contents[0];
      AssertThat(slice.trees, Equals(vector<TSTree *>({ trees[0] })));
      AssertThat(ts_stack_top_state(stack, 0), Equals(0));

      free_slice_array(&pop_result.slices);
    });

    it("does not count 'extra' trees toward the count", [&]() {
      trees[1]->extra = true;

      // .*
      StackPopResult pop_result = ts_stack_pop_count(stack, 0, 2);
      AssertThat(pop_result.status, Equals(StackPopResult::StackPopSucceeded));
      AssertThat(pop_result.slices.size, Equals<size_t>(1));

      StackSlice slice = pop_result.slices.contents[0];
      AssertThat(slice.trees, Equals(vector<TSTree *>({ trees[0], trees[1], trees[2] })));
      AssertThat(ts_stack_top_state(stack, 0), Equals(0));

      free_slice_array(&pop_result.slices);
    });

    it("pops the entire stack when given a negative count", [&]() {
      // .*
      StackPopResult pop_result = ts_stack_pop_count(stack, 0, -1);
      AssertThat(pop_result.status, Equals(StackPopResult::StackPopSucceeded));
      AssertThat(pop_result.slices.size, Equals<size_t>(1));

      StackSlice slice = pop_result.slices.contents[0];
      AssertThat(slice.trees, Equals(vector<TSTree *>({ trees[0], trees[1], trees[2] })));

      free_slice_array(&pop_result.slices);
    });

    describe("when an error state exists above the given depth", [&]() {
      it("stops popping nodes at the error", [&]() {
        // . <──0── A <──1── B <──2── C <──3── ERROR <──4── D*
        ts_stack_push(stack, 0, trees[3], false, ts_parse_state_error);
        ts_stack_push(stack, 0, trees[4], false, stateD);

        StackPopResult pop_result = ts_stack_pop_count(stack, 0, 3);
        AssertThat(pop_result.status, Equals(StackPopResult::StackPopStoppedAtError));

        AssertThat(ts_stack_version_count(stack), Equals(1));
        AssertThat(ts_stack_top_state(stack, 0), Equals(ts_parse_state_error));

        AssertThat(pop_result.slices.size, Equals<size_t>(1));
        StackSlice slice = pop_result.slices.contents[0];
        AssertThat(slice.version, Equals(0));
        AssertThat(slice.trees, Equals(vector<TSTree *>({ trees[4] })));

        free_slice_array(&pop_result.slices);
      });
    });

    describe("popping pending nodes from the stack", [&]() {
      it("removes the top node from the stack if it was pushed in pending mode", [&]() {
        ts_stack_push(stack, 0, trees[3], true, stateD);

        StackPopResult pop = ts_stack_pop_pending(stack, 0);
        AssertThat(pop.status, Equals(StackPopResult::StackPopSucceeded));
        AssertThat(pop.slices.size, Equals<size_t>(1));

        AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
          {stateC, 0},
          {stateB, 1},
          {stateA, 2},
          {0, 3},
        })));

        free_slice_array(&pop.slices);
      });

      it("does nothing if the top node was not pushed in pending mode", [&]() {
        ts_stack_push(stack, 0, trees[3], false, stateD);

        StackPopResult pop = ts_stack_pop_pending(stack, 0);
        AssertThat(pop.status, Equals(StackPopResult::StackPopSucceeded));
        AssertThat(pop.slices.size, Equals<size_t>(0));

        AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
          {stateD, 0},
          {stateC, 1},
          {stateB, 2},
          {stateA, 3},
          {0, 4},
        })));

        free_slice_array(&pop.slices);
      });
    });
  });

  describe("splitting the stack", [&]() {
    it("creates a new independent version with the same entries", [&]() {
      // . <──0── A <──1── B <──2── C*
      ts_stack_push(stack, 0, trees[0], false, stateA);
      ts_stack_push(stack, 0, trees[1], false, stateB);
      ts_stack_push(stack, 0, trees[2], false, stateC);

      // . <──0── A <──1── B <──2── C*
      //                            ↑
      //                            └─*
      int new_index = ts_stack_split(stack, 0);
      AssertThat(ts_stack_version_count(stack), Equals(2));
      AssertThat(new_index, Equals(1));
      AssertThat(ts_stack_top_state(stack, 1), Equals(stateC));

      // . <──0── A <──1── B <──2── C <──3── D*
      //                   ↑
      //                   └─*
      ts_stack_push(stack, 0, trees[3], false, stateD);
      StackPopResult pop_result = ts_stack_pop_count(stack, 1, 1);

      AssertThat(ts_stack_version_count(stack), Equals(2));
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateD));
      AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len * 4));
      AssertThat(ts_stack_top_state(stack, 1), Equals(stateB));
      AssertThat(ts_stack_top_position(stack, 1), Equals(tree_len * 2));

      AssertThat(pop_result.slices.size, Equals<size_t>(1));
      StackSlice slice = pop_result.slices.contents[0];
      AssertThat(slice.trees.size, Equals<size_t>(1));
      free_slice_array(&pop_result.slices);

      // . <──0── A <──1── B <──2── C <──3── D*
      //                   ↑
      //                   └───4─── E <──5── F*
      ts_stack_push(stack, 1, trees[4], false, stateE);
      ts_stack_push(stack, 1, trees[5], false, stateF);

      AssertThat(ts_stack_version_count(stack), Equals(2));
      AssertThat(ts_stack_top_state(stack, 0), Equals(stateD));
      AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len * 4));
      AssertThat(ts_stack_top_state(stack, 1), Equals(stateF));
      AssertThat(ts_stack_top_position(stack, 1), Equals(tree_len * 4));
    });
  });

  describe("pushing the same state onto two different versions of the stack", [&]() {
    before_each([&]() {
      // . <──0── A <──1── B <──2── C <──3── D*
      //                   ↑
      //                   └───4─── E <──5── F*
      ts_stack_push(stack, 0, trees[0], false, stateA);
      ts_stack_push(stack, 0, trees[1], false, stateB);
      ts_stack_split(stack, 0);
      ts_stack_push(stack, 0, trees[2], false, stateC);
      ts_stack_push(stack, 0, trees[3], false, stateD);
      ts_stack_push(stack, 1, trees[4], false, stateE);
      ts_stack_push(stack, 1, trees[5], false, stateF);

      AssertThat(ts_stack_version_count(stack), Equals(2));
      AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
        {stateD, 0},
        {stateC, 1},
        {stateB, 2},
        {stateA, 3},
        {0, 4},
      })));
      AssertThat(get_stack_entries(stack, 1), Equals(vector<StackEntry>({
        {stateF, 0},
        {stateE, 1},
        {stateB, 2},
        {stateA, 3},
        {0, 4},
      })));
    });

    it("merges the versions", [&]() {
      // . <──0── A <──1── B <──2── C <──3── D <──6── G*
      //                   ↑                          |
      //                   └───4─── E <──5── F <──7───┘
      AssertThat(ts_stack_push(stack, 0, trees[6], false, stateG), Equals(StackPushContinued));
      AssertThat(ts_stack_push(stack, 1, trees[7], false, stateG), Equals(StackPushMerged));

      AssertThat(ts_stack_version_count(stack), Equals(1));
      AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
        {stateG, 0},
        {stateD, 1},
        {stateF, 1},
        {stateC, 2},
        {stateE, 2},
        {stateB, 3},
        {stateA, 4},
        {0, 5},
      })));
    });

    describe("when the merged nodes share a successor", [&]() {
      it("recursively merges the successor nodes", [&]() {
        // . <──0── A <──1── B <──2── C <──3── D <──6── G <──7──H*
        //                   ↑
        //                   └───4─── E <──5── F <──8── G*
        AssertThat(ts_stack_push(stack, 0, trees[6], false, stateG), Equals(StackPushContinued));
        AssertThat(ts_stack_push(stack, 0, trees[7], false, stateH), Equals(StackPushContinued));
        AssertThat(ts_stack_push(stack, 1, trees[6], false, stateG), Equals(StackPushContinued));

        // . <──0── A <──1── B <──2── C <──3── D <──6── G <──7──H*
        //                   ↑                          |
        //                   └───4─── E <──5── F <──8───┘
        AssertThat(ts_stack_push(stack, 1, trees[7], false, stateH), Equals(StackPushMerged));

        AssertThat(ts_stack_version_count(stack), Equals(1));
        AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
          {stateH, 0},
          {stateG, 1},
          {stateD, 2},
          {stateF, 2},
          {stateC, 3},
          {stateE, 3},
          {stateB, 4},
          {stateA, 5},
          {0, 6},
        })));
      });
    });

    describe("when the first version is only one node deep", [&]() {
      it("creates a node with one null successor and one non-null successor", [&]() {
        ts_tree_retain(trees[2]);
        ts_tree_retain(trees[3]);
        TSTree *parent = ts_tree_make_node(5, 2, tree_array({ trees[2], trees[3] }), metadata);

        // . <──────5─────── C*
        // ↑                 |
        // └───2─── B ───3───┘
        ts_stack_clear(stack);
        ts_stack_split(stack, 0);
        AssertThat(ts_stack_push(stack, 0, parent, false, stateC), Equals(StackPushContinued));
        AssertThat(ts_stack_push(stack, 1, trees[2], false, stateB), Equals(StackPushContinued));
        AssertThat(ts_stack_push(stack, 1, trees[3], false, stateC), Equals(StackPushMerged));

        AssertThat(ts_stack_version_count(stack), Equals(1));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateC));
        AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
          {stateC, 0},
          {0, 1},
          {stateB, 1},
          {0, 2},
        })));

        ts_tree_release(parent);
      });
    });
  });

  describe("popping from a stack version that has been merged", [&]() {
    before_each([&]() {
      // . <──0── A <──1── B <──2── C <──3── D <──4── E*
      //                   ↑                          |
      //                   └───5─── F <──6── G <──7───┘
      ts_stack_push(stack, 0, trees[0], false, stateA);
      ts_stack_push(stack, 0, trees[1], false, stateB);
      ts_stack_split(stack, 0);
      ts_stack_push(stack, 0, trees[2], false, stateC);
      ts_stack_push(stack, 0, trees[3], false, stateD);
      ts_stack_push(stack, 0, trees[4], false, stateE);
      ts_stack_push(stack, 1, trees[5], false, stateF);
      ts_stack_push(stack, 1, trees[6], false, stateG);
      ts_stack_push(stack, 1, trees[7], false, stateE);

      AssertThat(ts_stack_version_count(stack), Equals(1));
      AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
        {stateE, 0},
        {stateD, 1},
        {stateG, 1},
        {stateC, 2},
        {stateF, 2},
        {stateB, 3},
        {stateA, 4},
        {0, 5},
      })));
    });

    describe("when there are two paths that lead to two different versions", [&]() {
      it("returns an entry for each revealed version", [&]() {
        // . <──0── A <──1── B <──2── C*
        //                   ↑
        //                   └───5─── F*
        StackPopResult pop_result = ts_stack_pop_count(stack, 0, 2);

        AssertThat(pop_result.slices.size, Equals<size_t>(2));
        StackSlice slice1 = pop_result.slices.contents[0];
        AssertThat(slice1.version, Equals(0));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateC));
        AssertThat(slice1.trees, Equals(vector<TSTree *>({ trees[3], trees[4] })));

        StackSlice slice2 = pop_result.slices.contents[1];
        AssertThat(slice2.version, Equals(1));
        AssertThat(ts_stack_top_state(stack, 1), Equals(stateF));
        AssertThat(slice2.trees, Equals(vector<TSTree *>({ trees[6], trees[7] })));

        AssertThat(ts_stack_version_count(stack), Equals(2));
        AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
          {stateC, 0},
          {stateB, 1},
          {stateA, 2},
          {0, 3},
        })));
        AssertThat(get_stack_entries(stack, 1), Equals(vector<StackEntry>({
          {stateF, 0},
          {stateB, 1},
          {stateA, 2},
          {0, 3},
        })));

        free_slice_array(&pop_result.slices);
      });
    });

    describe("when there is one path, leading to one version", [&]() {
      it("returns a single entry", [&]() {
        // . <──0── A <──1── B <──2── C <──3── D <──4── E <──8──H*
        //                   ↑                          |
        //                   └───5─── F <──6── G <──7───┘
        AssertThat(ts_stack_push(stack, 0, trees[8], false, stateH), Equals(StackPushContinued));
        AssertThat(ts_stack_version_count(stack), Equals(1));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateH));

        // . <──0── A <──1── B <──2── C <──3── D <──4── E*
        //                   ↑                          |
        //                   └───5─── F <──6── G <──7───┘
        StackPopResult pop_result = ts_stack_pop_count(stack, 0, 1);
        AssertThat(pop_result.slices.size, Equals<size_t>(1));
        StackSlice slice1 = pop_result.slices.contents[0];
        AssertThat(slice1.version, Equals(0));
        AssertThat(slice1.trees, Equals(vector<TSTree *>({ trees[8] })));

        AssertThat(ts_stack_version_count(stack), Equals(1));
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateE));

        free_slice_array(&pop_result.slices);
      });
    });

    describe("when there are two paths that converge at the same version", [&]() {
      describe("when the first path is preferred by the callback", [&]() {
        it("returns one entry for that version, with the first path of trees", [&]() {
          tree_selection_spy.tree_to_return = trees[2];

          // . <──0── A <──1── B*
          StackPopResult pop_result = ts_stack_pop_count(stack, 0, 3);
          AssertThat(ts_stack_version_count(stack), Equals(1));
          AssertThat(ts_stack_top_state(stack, 0), Equals(stateB));
          AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len * 2));

          AssertThat(pop_result.slices.size, Equals<size_t>(1));
          StackSlice slice1 = pop_result.slices.contents[0];
          AssertThat(slice1.version, Equals(0));
          AssertThat(slice1.trees, Equals(vector<TSTree *>({ trees[2], trees[3], trees[4] })));

          free_slice_array(&pop_result.slices);
        });
      });

      describe("when the second path is preferred by the callback", [&]() {
        it("returns one entry for that version, with the second path of trees", [&]() {
          tree_selection_spy.tree_to_return = trees[4];

          // . <──0── A <──1── B*
          StackPopResult pop_result = ts_stack_pop_count(stack, 0, 3);
          AssertThat(ts_stack_version_count(stack), Equals(1));
          AssertThat(ts_stack_top_state(stack, 0), Equals(stateB));
          AssertThat(ts_stack_top_position(stack, 0), Equals(tree_len * 2));

          AssertThat(pop_result.slices.size, Equals<size_t>(1));
          StackSlice slice1 = pop_result.slices.contents[0];
          AssertThat(slice1.version, Equals(0));
          AssertThat(slice1.trees, Equals(vector<TSTree *>({ trees[5], trees[6], trees[7] })))

          free_slice_array(&pop_result.slices);
        });
      });
    });
  });

  describe("popping from a stack version that has been 3-way merged", [&]() {
    before_each([&]() {
      // . <──0── A <──1── B <──2── C <──3── D <──10── I
      //          ↑                          |
      //          ├───4─── E <──5── F <──6───┤
      //          |                          |
      //          └───7─── G <──8── H <──9───┘
      ts_stack_clear(stack);
      ts_stack_push(stack, 0, trees[0], false, stateA);
      ts_stack_split(stack, 0);
      ts_stack_split(stack, 1);
      ts_stack_push(stack, 0, trees[1], false, stateB);
      ts_stack_push(stack, 0, trees[2], false, stateC);
      ts_stack_push(stack, 0, trees[3], false, stateD);
      ts_stack_push(stack, 1, trees[4], false, stateE);
      ts_stack_push(stack, 1, trees[5], false, stateF);
      ts_stack_push(stack, 1, trees[6], false, stateD);
      ts_stack_push(stack, 1, trees[7], false, stateG);
      ts_stack_push(stack, 1, trees[8], false, stateH);
      ts_stack_push(stack, 1, trees[9], false, stateD);
      ts_stack_push(stack, 0, trees[10], false, stateI);

      AssertThat(ts_stack_version_count(stack), Equals(1));
      AssertThat(get_stack_entries(stack, 0), Equals(vector<StackEntry>({
        {stateI, 0},
        {stateD, 1},
        {stateC, 2},
        {stateF, 2},
        {stateH, 2},
        {stateB, 3},
        {stateE, 3},
        {stateG, 3},
        {stateA, 4},
        {0, 5},
      })));
    });

    describe("when there are three different paths that lead to three different versions", [&]() {
      it("returns three entries with different arrays of trees", [&]() {
        // . <──0── A <──1── B <──2── C*
        //          ↑
        //          ├───4─── E <──5── F*
        //          |
        //          └───7─── G <──8── H*
        StackPopResult pop_result = ts_stack_pop_count(stack, 0, 2);
        AssertThat(ts_stack_version_count(stack), Equals(3));

        AssertThat(pop_result.slices.size, Equals<size_t>(3));

        StackSlice slice1 = pop_result.slices.contents[0];
        AssertThat(ts_stack_top_state(stack, 0), Equals(stateC));
        AssertThat(slice1.version, Equals(0));
        AssertThat(slice1.trees, Equals(vector<TSTree *>({ trees[3], trees[10] })))

        StackSlice slice2 = pop_result.slices.contents[1];
        AssertThat(ts_stack_top_state(stack, 1), Equals(stateF));
        AssertThat(slice2.version, Equals(1));
        AssertThat(slice2.trees, Equals(vector<TSTree *>({ trees[6], trees[10] })))

        StackSlice slice3 = pop_result.slices.contents[2];
        AssertThat(ts_stack_top_state(stack, 2), Equals(stateH));
        AssertThat(slice3.version, Equals(2));
        AssertThat(slice3.trees, Equals(vector<TSTree *>({ trees[9], trees[10] })))

        free_slice_array(&pop_result.slices);
      });
    });
  });
});

END_TEST

bool operator==(const StackEntry &left, const StackEntry &right) {
  return left.state == right.state && left.depth == right.depth;
}

std::ostream &operator<<(std::ostream &stream, const StackEntry &entry) {
  return stream << "{" << entry.state << ", " << entry.depth << "}";
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
