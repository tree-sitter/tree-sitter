#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/parse_stack.h"
#include <assert.h>

static const size_t INITIAL_HEAD_CAPACITY = 3;

struct ParseStack {
  ParseStackNode **heads;
  int head_count;
  int head_capacity;
};

/*
 *  Section: Lifecycle
 */

ParseStack *ts_parse_stack_new() {
  ParseStack *this = malloc(sizeof(ParseStack));
  *this = (ParseStack) {
    .heads = calloc(INITIAL_HEAD_CAPACITY, sizeof(ParseStackNode *)),
    .head_count = 1,
    .head_capacity = INITIAL_HEAD_CAPACITY,
  };
  return this;
}

void ts_parse_stack_delete(ParseStack *this) {
  if (this->heads)
    free(this->heads);
  free(this);
}

/*
 *  Section: Reading
 */

ParseStackNode *ts_parse_stack_head(const ParseStack *this, int head_index) {
  assert(head_index < this->head_count);
  return this->heads[head_index];
}

int ts_parse_stack_head_count(const ParseStack *this) {
  return this->head_count;
}

/*
 *  Section: Updating
 */

static ParseStackNode *stack_node_new(ParseStackNode *, TSStateId, TSTree *);
static void stack_node_retain(ParseStackNode *);
static bool stack_node_release(ParseStackNode *);
static void stack_node_add_successor(ParseStackNode *, ParseStackNode *);
static void parse_stack_remove_head(ParseStack *, int);
static bool parse_stack_merge_head(ParseStack *, int, TSStateId, TSTree *);

bool ts_parse_stack_shift(ParseStack *this, int head_index, TSStateId state, TSTree *tree) {
  assert(head_index < this->head_count);
  if (parse_stack_merge_head(this, head_index, state, tree))
    return true;
  this->heads[head_index] = stack_node_new(this->heads[head_index], state, tree);
  return false;
}

bool ts_parse_stack_reduce(ParseStack *this, int head_index, TSStateId state,
                           TSSymbol symbol, int child_count) {
  ParseStackNode *head = this->heads[head_index];

  /*
   *  Walk down the stack to determine which symbols will be reduced.
   *  The child node count is known ahead of time, but some children
   *  may be ubiquitous tokens, which don't count.
   */
  ParseStackNode *next_node = head;
  for (int i = 0; i < child_count; i++) {
    TSTree *child = next_node->tree;
    if (ts_tree_is_extra(child))
      child_count++;
    next_node = next_node->successors[0];
    if (!next_node)
      break;
  }

  TSTree **children = malloc(child_count * sizeof(TSTree *));
  next_node = head;
  for (int i = 0; i < child_count; i++) {
    children[child_count - i - 1] = next_node->tree;
    next_node = next_node->successors[0];
  }

  TSTree *parent = ts_tree_make_node(symbol, child_count, children, false);
  if (parse_stack_merge_head(this, head_index, state, parent)) {
    ts_tree_release(parent);
    return true;
  }

  stack_node_retain(next_node);
  stack_node_release(this->heads[head_index]);
  this->heads[head_index] = stack_node_new(next_node, state, parent);
  return false;
}

int ts_parse_stack_split(ParseStack *this, int head_index) {
  assert(head_index < this->head_count);
  if (this->head_count == this->head_capacity) {
    this->head_capacity += 3;
    this->heads = realloc(this->heads, this->head_capacity * sizeof(ParseStackNode *));
  }
  int new_index = this->head_count++;
  this->heads[new_index] = this->heads[head_index];
  stack_node_retain(this->heads[new_index]);
  return new_index;
}

/*
 *  Section: Private
 */

static ParseStackNode *stack_node_new(ParseStackNode *next, TSStateId state, TSTree *tree) {
  ParseStackNode *this = malloc(sizeof(ParseStackNode));
  *this = (ParseStackNode) {
    .ref_count = 1,
    .successor_count = 1,
    .successors = {next, NULL, NULL},
    .state = state,
    .tree = tree,
  };
  return this;
}

static void stack_node_retain(ParseStackNode *this) {
  if (!this) return;
  assert(this->ref_count != 0);
  this->ref_count++;
}

static bool stack_node_release(ParseStackNode *this) {
  if (!this) return false;
  assert(this->ref_count != 0);
  this->ref_count--;
  if (this->ref_count == 0) {
    for (int i = 0; i < this->successor_count; i++)
      stack_node_release(this->successors[i]);
    ts_tree_release(this->tree);
    free(this);
    return true;
  } else {
    return false;
  }
}

static void stack_node_add_successor(ParseStackNode *this, ParseStackNode *successor) {
  stack_node_retain(successor);
  this->successors[this->successor_count] = successor;
  this->successor_count++;
}

static bool parse_stack_merge_head(ParseStack *this, int head_index, TSStateId state, TSTree *tree) {
  for (int i =  0; i < head_index; i++) {
    ParseStackNode *head = this->heads[i];
    if (head->state == state && ts_tree_eq(head->tree, tree)) {
      stack_node_add_successor(head, this->heads[head_index]);
      parse_stack_remove_head(this, head_index);
      return true;
    }
  }
  return false;
}

static void parse_stack_remove_head(ParseStack *this, int head_index) {
  stack_node_release(this->heads[head_index]);
  for (int i = head_index; i < this->head_count - 1; i++) {
    this->heads[head_index] = this->heads[head_index + 1];
  }
  this->head_count--;
}
