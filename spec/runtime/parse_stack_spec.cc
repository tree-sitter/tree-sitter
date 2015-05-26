#include "runtime/runtime_spec_helper.h"
#include "runtime/parse_stack.h"
#include "runtime/tree.h"
#include "runtime/length.h"

enum { stateA, stateB, stateC, stateD, stateE, stateF, stateG, };
enum { symbol0, symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, };
const char *names[] = { "zero", "one", "two", "three", "four", "five", "six", };

START_TEST

describe("ParseStack", [&]() {
  ParseStack *stack;
  const size_t tree_count = 6;
  TSTree *trees[tree_count];

  before_each([&]() {
    stack = ts_parse_stack_new();
    TSLength len = ts_length_make(2, 2);
    for (size_t i = 0; i < tree_count; i++)
      trees[i] = ts_tree_make_leaf(i, len, len, false);
  });

  after_each([&]() {
    ts_parse_stack_delete(stack);
    for (size_t i = 0; i < tree_count; i++)
      ts_tree_release(trees[i]);
  });

  it("starts with a single null head", [&]() {
    AssertThat(ts_parse_stack_head_count(stack), Equals(1));
    AssertThat(ts_parse_stack_head(stack, 0), Equals<ParseStackNode *>(NULL));
  });

  describe("shift(head_index, state, tree)", [&]() {
    it("pushes a node with the given state and tree onto the given head", [&]() {
      ts_parse_stack_shift(stack, 0, 100, trees[0]);
      ts_parse_stack_shift(stack, 0, 101, trees[1]);
      ts_parse_stack_shift(stack, 0, 102, trees[2]);

      ParseStackNode *head = ts_parse_stack_head(stack, 0);
      AssertThat(head->state, Equals(102));
      AssertThat(head->tree, Equals(trees[2]));
      AssertThat(head->successor_count, Equals(1));

      head = head->successors[0];
      AssertThat(head->state, Equals(101));
      AssertThat(head->tree, Equals(trees[1]));
      AssertThat(head->successor_count, Equals(1));

      head = head->successors[0];
      AssertThat(head->state, Equals(100));
      AssertThat(head->tree, Equals(trees[0]));
      AssertThat(head->successor_count, Equals(1));

      head = head->successors[0];
      AssertThat(head, Equals<ParseStackNode *>(NULL));
    });
  });

  describe("reduce(head_index, state, symbol, child_count)", [&]() {
    before_each([&]() {
      ts_parse_stack_shift(stack, 0, 100, trees[0]);
      ts_parse_stack_shift(stack, 0, 101, trees[1]);
      ts_parse_stack_shift(stack, 0, 102, trees[2]);
    });

    it("replaces the given number of nodes with a single parent node", [&]() {
      ts_parse_stack_reduce(stack, 0, 103, symbol4, 2);

      ParseStackNode *head = ts_parse_stack_head(stack, 0);
      AssertThat(head->state, Equals(103));
      AssertThat(head->tree, Fulfills(EqualsTree(
        ts_tree_make_node(symbol4, 2, tree_array({ trees[1], trees[2] }), false),
        names)));
      AssertThat(head->successor_count, Equals(1));

      head = head->successors[0];
      AssertThat(head->state, Equals(100));
      AssertThat(head->tree, Equals(trees[0]));
      AssertThat(head->successor_count, Equals(1));
    });

    describe("when one of the reduced children is an 'extra' tree", [&]() {
      before_each([&]() {
        ts_tree_set_extra(trees[1]);
      });

      it("does not count that child toward the number of children to replace", [&]() {
        ts_parse_stack_reduce(stack, 0, 103, symbol4, 2);

        ParseStackNode *head = ts_parse_stack_head(stack, 0);
        AssertThat(head->state, Equals(103));
        AssertThat(head->tree, Fulfills(EqualsTree(
          ts_tree_make_node(symbol4, 3, tree_array({ trees[0], trees[1], trees[2] }), false),
          names)));
        AssertThat(head->successor_count, Equals(1));

        head = head->successors[0];
        AssertThat(head, Equals<ParseStackNode *>(NULL));
      });
    });
  });

  describe("split(head_index)", [&]() {
    bool merged;

    before_each([&]() {
      //  A0__B1__C2
      ts_parse_stack_shift(stack, 0, stateA, trees[0]);
      ts_parse_stack_shift(stack, 0, stateB, trees[1]);
      ts_parse_stack_shift(stack, 0, stateC, trees[2]);

      int new_index = ts_parse_stack_split(stack, 0);
      AssertThat(new_index, Equals(1));
      AssertThat(ts_parse_stack_head_count(stack), Equals(2));
    });

    it("creates a new head pointing to the same node as the given head", [&]() {
      //  A0__B1__C2__D3
      //   \__E4__F3
      ts_parse_stack_shift(stack, 0, stateD, trees[3]);
      ts_parse_stack_reduce(stack, 1, stateE, symbol4, 2);
      merged = ts_parse_stack_shift(stack, 1, stateF, trees[3]);

      AssertThat(merged, IsFalse());
      AssertThat(ts_parse_stack_head_count(stack), Equals(2));

      ParseStackNode *head1 = ts_parse_stack_head(stack, 0);
      AssertThat(head1->state, Equals(stateD));
      AssertThat(head1->tree, Equals(trees[3]));
      AssertThat(head1->successor_count, Equals(1));

      ParseStackNode *head2 = ts_parse_stack_head(stack, 1);
      AssertThat(head2->state, Equals(stateF));
      AssertThat(head2->tree, Equals(trees[3]));
      AssertThat(head2->successor_count, Equals(1));
    });

    it("re-joins the heads when the same state and tree are shifted onto both heads", [&]() {
      //  A0__B1__C2__D3
      //   \____E4____/
      ts_parse_stack_shift(stack, 0, stateD, trees[3]);
      ts_parse_stack_reduce(stack, 1, stateE, symbol4, 2);
      TSTree *tree4 = ts_parse_stack_head(stack, 1)->tree;
      merged = ts_parse_stack_shift(stack, 1, stateD, trees[3]);

      AssertThat(merged, IsTrue());
      AssertThat(ts_parse_stack_head_count(stack), Equals(1));

      ParseStackNode *head = ts_parse_stack_head(stack, 0);
      AssertThat(head->state, Equals(stateD));
      AssertThat(head->tree, Equals(trees[3]));
      AssertThat(head->successor_count, Equals(2));

      ParseStackNode *successor1 = head->successors[0];
      AssertThat(successor1->state, Equals(stateC));
      AssertThat(successor1->tree, Equals(trees[2]))
      AssertThat(successor1->successor_count, Equals(1));

      ParseStackNode *successor2 = head->successors[1];
      AssertThat(successor2->state, Equals(stateE));
      AssertThat(successor2->tree, Equals(tree4))
      AssertThat(successor2->successor_count, Equals(1));
    });

    it("re-joins the heads when the same state and tree are reduced onto both heads", [&]() {
      //  A0__B1__C2__F4
      //       \__D3__E4
      ts_parse_stack_reduce(stack, 0, stateD, symbol3, 1);
      ts_parse_stack_shift(stack, 0, stateE, trees[4]);
      ts_parse_stack_shift(stack, 1, stateF, trees[4]);

      AssertThat(ts_parse_stack_head_count(stack), Equals(2));
      ParseStackNode *head1 = ts_parse_stack_head(stack, 0);
      AssertThat(head1->state, Equals(stateE));
      AssertThat(head1->tree, Equals(trees[4]));
      AssertThat(head1->successor_count, Equals(1));

      ParseStackNode *head2 = ts_parse_stack_head(stack, 1);
      AssertThat(head2->state, Equals(stateF));
      AssertThat(head2->tree, Equals(trees[4]));
      AssertThat(head2->successor_count, Equals(1));

      //  A0__B1__C2__G5
      //       \__D3__/
      merged = ts_parse_stack_reduce(stack, 0, stateG, symbol5, 1);
      AssertThat(merged, IsFalse());
      merged = ts_parse_stack_reduce(stack, 1, stateG, symbol5, 1);
      AssertThat(merged, IsTrue());

      AssertThat(ts_parse_stack_head_count(stack), Equals(1));
      ParseStackNode *head = ts_parse_stack_head(stack, 0);
      AssertThat(head->state, Equals(stateG));
      AssertThat(head->tree, Fulfills(EqualsTree(
        ts_tree_make_node(symbol5, 1, tree_array({ trees[4] }), false),
        names)));
      AssertThat(head->successor_count, Equals(2));
    });
  });
});

END_TEST
