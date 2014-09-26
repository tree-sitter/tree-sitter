#include "runtime/runtime_spec_helper.h"
#include "runtime/length.h"
#include "runtime/tree.h"
#include "runtime/stack.h"

START_TEST

enum { sym1, sym2, hidden_sym };

describe("stacks", [&]() {
  TSStack stack;

  before_each([&]() {
    stack = ts_stack_make();
  });

  after_each([&]() {
    ts_stack_delete(&stack);
  });

  it("starts out empty", [&]() {
    AssertThat(stack.size, Equals<size_t>(0));
    AssertThat(ts_stack_top_state(&stack), Equals(0));
    AssertThat(ts_stack_top_node(&stack), Equals((TSTree *)nullptr));
  });

  describe("pushing a symbol", [&]() {
    TSTree *node1;

    before_each([&]() {
      node1 = ts_tree_make_leaf(
          sym1,
          ts_length_make(0, 0),
          ts_length_make(1, 1),
          0);

      ts_stack_push(&stack, 5, node1);
    });

    after_each([&]() {
      ts_tree_release(node1);
    });

    it("adds the symbol to the stack", [&]() {
      AssertThat(stack.size, Equals<size_t>(1));
      AssertThat(ts_stack_top_state(&stack), Equals(5));
      AssertThat(ts_stack_top_node(&stack), Equals(node1));
    });
  });
});

END_TEST
