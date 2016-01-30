#include "tree_sitter/parser.h"
#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/vector.h"
#include "runtime/stack.h"
#include "runtime/length.h"
#include <assert.h>
#include <stdio.h>

#define MAX_SUCCESSOR_COUNT 8
#define INITIAL_HEAD_CAPACITY 3
#define STARTING_TREE_CAPACITY 10

typedef struct StackNode {
  StackEntry entry;
  struct StackNode *successors[MAX_SUCCESSOR_COUNT];
  short unsigned int successor_count;
  short unsigned int ref_count;
} StackNode;

struct Stack {
  StackNode **heads;
  int head_count;
  int head_capacity;
  Vector pop_results;
  Vector pop_paths;
  void *tree_selection_payload;
  TreeSelectionFunction tree_selection_function;
};

typedef struct {
  size_t goal_tree_count;
  StackNode *node;
  Vector trees;
  bool is_shared;
} PopPath;

/*
 *  Section: Stack lifecycle
 */

static TSTree *ts_stack__default_tree_selection(void *p, TSTree *t1, TSTree *t2) {
  return t1;
}

Stack *ts_stack_new() {
  Stack *self = ts_calloc(1, sizeof(Stack));
  if (!self)
    goto error;

  self->head_count = 1;
  self->head_capacity = INITIAL_HEAD_CAPACITY;
  self->heads = ts_calloc(INITIAL_HEAD_CAPACITY, sizeof(StackNode *));
  if (!self->heads)
    goto error;

  self->pop_results = vector_new(sizeof(StackPopResult), 4);
  if (!vector_valid(&self->pop_results))
    goto error;

  self->pop_paths = vector_new(sizeof(PopPath), 4);
  if (!vector_valid(&self->pop_paths))
    goto error;

  self->tree_selection_payload = NULL;
  self->tree_selection_function = ts_stack__default_tree_selection;
  return self;

error:
  if (self) {
    if (self->heads)
      ts_free(self->heads);
    if (self->pop_results.contents)
      vector_delete(&self->pop_results);
    if (self->pop_paths.contents)
      vector_delete(&self->pop_paths);
    ts_free(self);
  }
  return NULL;
}

/*
 *  Section: Reading from the stack
 */

TSStateId ts_stack_top_state(const Stack *self, int head) {
  StackEntry *entry = ts_stack_head((Stack *)self, head);
  return entry ? entry->state : 0;
}

TSLength ts_stack_top_position(const Stack *self, int head) {
  StackEntry *entry = ts_stack_head((Stack *)self, head);
  return entry ? entry->position : ts_length_zero();
}

TSTree *ts_stack_top_tree(const Stack *self, int head) {
  StackEntry *entry = ts_stack_head((Stack *)self, head);
  return entry ? entry->tree : NULL;
}

StackEntry *ts_stack_head(Stack *self, int head) {
  assert(head < self->head_count);
  StackNode *node = self->heads[head];
  return node ? &node->entry : NULL;
}

int ts_stack_head_count(const Stack *self) {
  return self->head_count;
}

int ts_stack_entry_next_count(const StackEntry *entry) {
  return ((const StackNode *)entry)->successor_count;
}

StackEntry *ts_stack_entry_next(const StackEntry *entry, int i) {
  return &((const StackNode *)entry)->successors[i]->entry;
}

/*
 *  Section: Manipulating nodes (Private)
 */

static void stack_node_retain(StackNode *self) {
  if (!self)
    return;
  assert(self->ref_count != 0);
  self->ref_count++;
}

static bool stack_node_release(StackNode *self) {
  if (!self)
    return false;
  assert(self->ref_count != 0);
  self->ref_count--;
  if (self->ref_count == 0) {
    for (int i = 0; i < self->successor_count; i++)
      stack_node_release(self->successors[i]);
    ts_tree_release(self->entry.tree);
    ts_free(self);
    return true;
  } else {
    return false;
  }
}

static StackNode *stack_node_new(StackNode *next, TSStateId state, TSTree *tree) {
  assert(tree->ref_count > 0);
  StackNode *self = ts_malloc(sizeof(StackNode));
  if (!self)
    return NULL;

  ts_tree_retain(tree);
  stack_node_retain(next);
  TSLength position = ts_tree_total_size(tree);
  if (next)
    position = ts_length_add(next->entry.position, position);
  *self = (StackNode){
    .ref_count = 1,
    .successor_count = 1,
    .successors = { next, NULL, NULL },
    .entry = {.state = state, .tree = tree, .position = position },
  };
  return self;
}

static void ts_stack__add_alternative_tree(Stack *self, StackNode *node,
                                           TSTree *tree) {
  if (tree != node->entry.tree) {
    TSTree *new_tree = self->tree_selection_function(
      self->tree_selection_payload, node->entry.tree, tree);

    if (new_tree != node->entry.tree) {
      ts_tree_retain(new_tree);
      ts_tree_release(node->entry.tree);
      node->entry.tree = new_tree;
    }
  }
}

static void ts_stack__add_node_successor(Stack *self, StackNode *node,
                                         StackNode *new_successor) {
  for (int i = 0; i < node->successor_count; i++) {
    StackNode *successor = node->successors[i];
    if (!successor)
      continue;
    if (successor == new_successor)
      return;

    if (successor->entry.state == new_successor->entry.state) {
      ts_stack__add_alternative_tree(self, successor, new_successor->entry.tree);
      for (int j = 0; j < new_successor->successor_count; j++)
        ts_stack__add_node_successor(self, successor,
                                     new_successor->successors[j]);
      return;
    }
  }

  stack_node_retain(new_successor);
  node->successors[node->successor_count] = new_successor;
  node->successor_count++;
}

/*
 *  Section: Mutating the stack (Private)
 */

static int ts_stack__add_head(Stack *self, StackNode *node) {
  if (self->head_count == self->head_capacity) {
    self->head_capacity += 3;
    self->heads =
      ts_realloc(self->heads, self->head_capacity * sizeof(StackNode *));
  }
  int new_index = self->head_count++;
  self->heads[new_index] = node;
  stack_node_retain(node);
  return new_index;
}

static int ts_stack__find_head(Stack *self, StackNode *node) {
  for (int i = 0; i < self->head_count; i++)
    if (self->heads[i] == node) {
      return i;
    }
  return -1;
}

void ts_stack_remove_head(Stack *self, int head_index) {
  stack_node_release(self->heads[head_index]);
  for (int i = head_index; i < self->head_count - 1; i++)
    self->heads[i] = self->heads[i + 1];
  self->head_count--;
}

static bool ts_stack__merge_head(Stack *self, int head_index, TSStateId state,
                                 TSTree *tree, TSLength position) {
  for (int i = 0; i < head_index; i++) {
    StackNode *head = self->heads[i];
    if (head->entry.state == state &&
        ts_length_eq(head->entry.position, position)) {
      ts_stack__add_alternative_tree(self, head, tree);
      ts_stack__add_node_successor(self, head, self->heads[head_index]);
      ts_stack_remove_head(self, head_index);
      return true;
    }
  }
  return false;
}

/*
 *  Section: Mutating the stack (Public)
 */

StackPushResult ts_stack_push(Stack *self, int head_index, TSStateId state,
                              TSTree *tree) {
  assert(head_index < self->head_count);
  assert(tree);

  TSLength position = ts_tree_total_size(tree);
  if (self->heads[head_index])
    position = ts_length_add(self->heads[head_index]->entry.position, position);

  if (ts_stack__merge_head(self, head_index, state, tree, position))
    return StackPushResultMerged;

  StackNode *new_head = stack_node_new(self->heads[head_index], state, tree);
  if (!new_head)
    return StackPushResultFailed;

  stack_node_release(self->heads[head_index]);
  self->heads[head_index] = new_head;
  return StackPushResultContinued;
}

void ts_stack_add_alternative(Stack *self, int head_index, TSTree *tree) {
  assert(head_index < self->head_count);
  StackNode *node = self->heads[head_index];
  ts_stack__add_alternative_tree(self, node, tree);
}

int ts_stack_split(Stack *self, int head_index) {
  assert(head_index < self->head_count);
  return ts_stack__add_head(self, self->heads[head_index]);
}

Vector ts_stack_pop(Stack *self, int head_index, int child_count,
                    bool count_extra) {
  vector_clear(&self->pop_results);
  vector_clear(&self->pop_paths);

  StackNode *previous_head = self->heads[head_index];
  int capacity = (child_count == -1) ? STARTING_TREE_CAPACITY : child_count;
  PopPath initial_path = {
    .goal_tree_count = child_count,
    .node = previous_head,
    .trees = vector_new(sizeof(TSTree *), capacity),
    .is_shared = false,
  };

  if (!vector_valid(&initial_path.trees))
    goto error;

  if (!vector_push(&self->pop_paths, &initial_path))
    goto error;

  /*
   *  Reduce along every possible path in parallel. Stop when the given number
   *  of child trees have been collected along every path.
   */
  bool all_paths_done = false;
  while (!all_paths_done) {
    all_paths_done = true;

    for (size_t i = 0; i < self->pop_paths.size; i++) {
      PopPath *path = vector_get(&self->pop_paths, i);
      StackNode *node = path->node;

      if (!node || path->trees.size == path->goal_tree_count)
        continue;

      all_paths_done = false;

      /*
       *  Children that are 'extra' do not count towards the total child count.
       */
      if (node->entry.tree->extra && !count_extra)
        path->goal_tree_count++;

      /*
       *  If a node has more than one successor, create new paths for each of
       *  the additional successors.
       */
      if (path->is_shared) {
        path->trees = vector_copy(&path->trees);
        for (size_t j = 0; j < path->trees.size; j++) {
          TSTree **tree = vector_get(&path->trees, j);
          ts_tree_retain(*tree);
        }

        path->is_shared = false;
      }

      ts_tree_retain(node->entry.tree);
      if (!vector_push(&path->trees, &node->entry.tree))
        goto error;

      path->node = path->node->successors[0];
      PopPath path_copy = *path;
      for (int j = 1; j < node->successor_count; j++) {
        if (!vector_push(&self->pop_paths, &path_copy))
          goto error;

        PopPath *next_path = vector_back(&self->pop_paths);
        next_path->node = node->successors[j];
        next_path->is_shared = true;
      }
    }
  }

  for (size_t i = 0; i < self->pop_paths.size; i++) {
    PopPath *path = vector_get(&self->pop_paths, i);

    if (!path->is_shared)
      vector_reverse(&path->trees);

    StackPopResult result = {
      .trees = path->trees.contents,
      .tree_count = path->trees.size,
      .head_index = -1,
    };

    if (i == 0) {
      stack_node_retain(path->node);
      self->heads[head_index] = path->node;
      result.head_index = head_index;
    } else {
      result.head_index = ts_stack__find_head(self, path->node);
      if (result.head_index == -1)
        result.head_index = ts_stack__add_head(self, path->node);
    }

    if (!vector_push(&self->pop_results, &result))
      goto error;
  }

  stack_node_release(previous_head);
  return self->pop_results;

error:
  return vector_new(0, 0);
}

void ts_stack_shrink(Stack *self, int head_index, int count) {
  StackNode *head = self->heads[head_index];
  StackNode *new_head = head;
  for (int i = 0; i < count; i++) {
    if (new_head->successor_count == 0)
      break;
    new_head = new_head->successors[0];
  }
  stack_node_retain(new_head);
  stack_node_release(head);
  self->heads[head_index] = new_head;
}

void ts_stack_clear(Stack *self) {
  for (int i = 0; i < self->head_count; i++)
    stack_node_release(self->heads[i]);
  self->head_count = 1;
  self->heads[0] = NULL;
}

void ts_stack_set_tree_selection_callback(Stack *self, void *payload,
                                          TreeSelectionFunction function) {
  self->tree_selection_payload = payload;
  self->tree_selection_function = function;
}

void ts_stack_delete(Stack *self) {
  vector_delete(&self->pop_results);
  vector_delete(&self->pop_paths);
  ts_stack_clear(self);
  ts_free(self->heads);
  ts_free(self);
}
