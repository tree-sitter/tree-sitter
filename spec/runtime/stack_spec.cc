#include "runtime/runtime_spec_helper.h"
#include "runtime/tree.h"
#include "runtime/stack.h"

START_TEST

enum { sym1, sym2, hidden_sym };
int hidden_symbols[] = { 0, 0, 1 };

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
            node1 = ts_tree_make_leaf(sym1, 5, 1, 0);
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

    describe("reducing a symbol", [&]() {
        TSTree **nodes;

        before_each([&]() {
            nodes = tree_array({
                ts_tree_make_leaf(sym1, 5, 1, 0),
                ts_tree_make_leaf(sym1, 5, 1, 0),
                ts_tree_make_leaf(hidden_sym, 5, 1, 0),
                ts_tree_make_leaf(sym1, 5, 1, 0),
            });

            for (TSStateId i = 0; i < 4; i++)
                ts_stack_push(&stack, 10 + i, nodes[i]);
        });

        after_each([&]() {
            for (TSStateId i = 0; i < 4; i++)
                ts_tree_release(nodes[i]);
            free(nodes);
        });

        it("pops the given number of nodes off the stack", [&]() {
            AssertThat(stack.size, Equals<size_t>(4));
            ts_stack_reduce(&stack, sym2, 3, hidden_symbols, 0);
            AssertThat(stack.size, Equals<size_t>(1));
        });

        it("returns a node with the given symbol", [&]() {
            TSTree *node = ts_stack_reduce(&stack, sym2, 3, hidden_symbols, 0);
            AssertThat(node->symbol, Equals(sym2));
        });

        it("removes any hidden nodes from its regular list of children", [&]() {
            TSTree *expected_children[3] = {
                stack.entries[1].node,
                stack.entries[2].node,
                stack.entries[3].node,
            };

            TSTree *node = ts_stack_reduce(&stack, sym2, 3, hidden_symbols, 0);
            size_t child_count;
            TSTree **children = ts_tree_children(node, &child_count);

            AssertThat(child_count, Equals<size_t>(3));
            for (size_t i = 0; i < 2; i++)
                AssertThat(children[i], Equals(expected_children[i]));
        });
    });
});

END_TEST
