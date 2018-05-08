#include "test_helper.h"
#include "helpers/point_helpers.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "helpers/load_language.h"
#include "runtime/stack2.h"
#include "runtime/length.h"
#include "runtime/alloc.h"

struct StackEntry2 {
  TSStateId state;
  uint32_t depth;
};

vector<StackEntry2> get_stack2_entries(Stack *stack, StackVersion version) {
  vector<StackEntry2> result;
  ts_stack2_iterate(
    stack,
    version,
    [](void *payload, TSStateId state, uint32_t depth) {
      auto entries = static_cast<vector<StackEntry2> *>(payload);
      entries->push_back({state, depth});
    }, &result);
  return result;
}

static LeafNodeParams leaf(TSSymbol symbol, Length size) {
  LeafNodeParams result = {};
  result.symbol = symbol;
  result.size = size;
  return result;
}

static LeafNodeParams extra_leaf(TSSymbol symbol, Length size) {
  LeafNodeParams result = leaf(symbol, size);
  result.extra = true;
  return result;
}

START_TEST

describe("Stack2", [&]() {
  const TSLanguage *language = get_dummy_language();
  Stack *stack;
  StateArray states;
  Length size = {3, {0, 3}};

  before_each([&]() {
    record_alloc::start();
    states = array_new();
    stack = ts_stack2_new();
  });

  after_each([&]() {
    array_delete(&states);
    ts_stack2_delete(stack);
    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  describe("push_leaf", [&]() {
    it("pushes a new state and position onto the stack", [&]() {
      AssertThat(ts_stack2_version_count(stack), Equals<size_t>(1));
      AssertThat(ts_stack2_state(stack, 0), Equals(1u));
      AssertThat(ts_stack2_position(stack, 0), Equals(length_zero()));

      ts_stack2_push_leaf(stack, 0, 10u, leaf(1u, size));
      AssertThat(ts_stack2_state(stack, 0), Equals(10u));
      AssertThat(ts_stack2_position(stack, 0), Equals(size));

      ts_stack2_push_leaf(stack, 0, 11u, leaf(2u, size * 2));
      AssertThat(ts_stack2_state(stack, 0), Equals(11u));
      AssertThat(ts_stack2_position(stack, 0), Equals(size * 3));

      ts_stack2_push_leaf(stack, 0, 12u, leaf(3u, size));
      AssertThat(ts_stack2_state(stack, 0), Equals(12u));
      AssertThat(ts_stack2_position(stack, 0), Equals(size * 4));
    });
  });

  describe("push_existing", [&]() {
    it("pushes a node of an existing tree", [&]() {
      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(1u, size));
      ts_node_list_push_leaf(&list, leaf(2u, size));
      ts_node_list_push_parent(&list, {3u, 2});
      ts_node_list_push_leaf(&list, leaf(4u, size));
      ts_node_list_push_parent(&list, {5u, 2});
      ts_node_list_push_leaf(&list, leaf(6u, size));
      ts_node_list_push_leaf(&list, leaf(7u, size));
      ts_node_list_push_parent(&list, {8u, 3});
      SyntaxTree *old_tree = ts_node_list_to_tree(&list, language, NULL);

      TreeCursor cursor = ts_tree_cursor_new(old_tree);
      ts_tree_cursor_descend(&cursor);
      ts_stack2_push_existing(stack, 0, 10u, &cursor);

      AssertThat(ts_stack2_state(stack, 0), Equals(10u));
      AssertThat(ts_stack2_position(stack, 0), Equals(size * 3u));

      ts_syntax_tree_delete(old_tree);
      ts_tree_cursor_delete(&cursor);
    });
  });

  describe("reduce", [&]() {
    it("pops the given number of nodes off the stack and pushes a new parent node", [&]() {
      ts_stack2_push_leaf(stack, 0, 10u, leaf(1u, size));
      ts_stack2_push_leaf(stack, 0, 11u, leaf(2u, size));
      ts_stack2_push_leaf(stack, 0, 12u, leaf(3u, size));
      ts_stack2_push_leaf(stack, 0, 13u, leaf(4u, size));
      AssertThat(get_stack2_entries(stack, 0), Equals<vector<StackEntry2>>({
        {13u, 0u},
        {12u, 1u},
        {11u, 2u},
        {10u, 3u},
        {1u, 4u},
      }));

      ts_stack2_reduce(stack, 0, {5u, 3u}, &states);
      AssertThat(states.size, Equals(1u));
      AssertThat(ts_stack2_version_count(stack), Equals(1u));

      // It provides pointers to the new node's state so that it can be assigned.
      *states.contents[0] = 14u;
      AssertThat(get_stack2_entries(stack, 0), Equals<vector<StackEntry2>>({
        {14u, 0u},
        {10u, 1u},
        {1u, 2u},
      }));
    });

    it("does not count *extra* tokens toward the child count", [&]() {
      ts_stack2_push_leaf(stack, 0, 10u, leaf(1u, size));
      ts_stack2_push_leaf(stack, 0, 11u, leaf(2u, size));
      ts_stack2_push_leaf(stack, 0, 11u, extra_leaf(3u, size));
      ts_stack2_push_leaf(stack, 0, 12u, leaf(4u, size));
      ts_stack2_push_leaf(stack, 0, 12u, extra_leaf(3u, size));
      ts_stack2_push_leaf(stack, 0, 12u, extra_leaf(3u, size));
      AssertThat(get_stack2_entries(stack, 0), Equals<vector<StackEntry2>>({
        {12u, 0u},
        {11u, 1u},
        {11u, 1u},
        {10u, 2u},
        {1u, 3u},
      }));

      ts_stack2_reduce(stack, 0, {5u, 2u}, &states);
      AssertThat(states.size, Equals(1u));
      AssertThat(ts_stack2_version_count(stack), Equals(1u));

      *states.contents[0] = 14u;
      AssertThat(get_stack2_entries(stack, 0), Equals<vector<StackEntry2>>({
        {14u, 0u},
        {10u, 1u},
        {1u, 2u},
      }));
    });
  });

  describe("breakdown", [&]() {
    it("pops the last parent node and pushes each of its children", [&]() {
      NodeList list = ts_node_list_new();
      ts_node_list_push_leaf(&list, leaf(1u, size));
      ts_node_list_push_leaf(&list, leaf(2u, size));
      ts_node_list_push_parent(&list, {3u, 2});
      ts_node_list_push_leaf(&list, leaf(4u, size));
      ts_node_list_push_parent(&list, {5u, 2});
      ts_node_list_push_leaf(&list, leaf(6u, size));
      ts_node_list_push_leaf(&list, leaf(7u, size));
      ts_node_list_push_parent(&list, {8u, 3});
      SyntaxTree *old_tree = ts_node_list_to_tree(&list, language, NULL);

      TreeCursor cursor = ts_tree_cursor_new(old_tree);
      ts_tree_cursor_descend(&cursor);
      ts_stack2_push_existing(stack, 0, 10u, &cursor);

      BreakdownResult *result = ts_stack2_breakdown(stack, 0, &states);
      AssertThat(result->size, Equals(2u));
      AssertThat(result->contents[0].symbol, Equals(3u));
      AssertThat(result->contents[1].symbol, Equals(4u));
      *states.contents[0] = 14;
      *states.contents[1] = 15;

      AssertThat(get_stack2_entries(stack, 0), Equals<vector<StackEntry2>>({
        {15u, 0u},
        {14u, 1u},
        {1u, 2u},
      }));

      AssertThat(ts_stack2_state(stack, 0), Equals(15u));
      AssertThat(ts_stack2_position(stack, 0), Equals(size * 3u));

      ts_syntax_tree_delete(old_tree);
      ts_tree_cursor_delete(&cursor);
    });
  });
});

END_TEST

bool operator==(const StackEntry2 &left, const StackEntry2 &right) {
  return left.state == right.state && left.depth == right.depth;
}

std::ostream &operator<<(std::ostream &stream, const StackEntry2 &entry) {
  return stream << "{" << entry.state << ", " << entry.depth << "}";
}
