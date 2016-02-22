#include "tree_sitter/parser.h"
#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/array.h"
#include "runtime/stack.h"
#include "runtime/length.h"
#include <assert.h>
#include <stdio.h>

#define MAX_SUCCESSOR_COUNT 8
#define INITIAL_HEAD_CAPACITY 3
#define STARTING_TREE_CAPACITY 10
#define MAX_NODE_POOL_SIZE 50

typedef struct StackNode {
  StackEntry entry;
  struct StackNode *successors[MAX_SUCCESSOR_COUNT];
  short unsigned int successor_count;
  short unsigned int ref_count;
} StackNode;

typedef struct {
  size_t goal_tree_count;
  StackNode *node;
  TreeArray trees;
  bool is_shared;
} PopPath;

struct Stack {
  Array(StackNode *) heads;
  StackPopResultArray pop_results;
  Array(PopPath) pop_paths;
  Array(StackNode *) node_pool;
  void *tree_selection_payload;
  TreeSelectionFunction tree_selection_function;
};

/*
 *  Section: Stack lifecycle
 */

static int ts_stack__default_tree_selection(void *p, TSTree *t1, TSTree *t2) {
  return 0;
}

Stack *ts_stack_new() {
  Stack *self = ts_calloc(1, sizeof(Stack));
  if (!self)
    goto error;

  array_init(&self->heads);
  array_init(&self->pop_results);
  array_init(&self->pop_paths);
  array_init(&self->node_pool);
  self->tree_selection_payload = NULL;
  self->tree_selection_function = ts_stack__default_tree_selection;

  if (!array_grow(&self->heads, 4))
    goto error;

  if (!array_grow(&self->pop_results, 4))
    goto error;

  if (!array_grow(&self->pop_paths, 4))
    goto error;

  if (!array_grow(&self->node_pool, 20))
    goto error;

  array_push(&self->heads, NULL);

  return self;

error:
  if (self) {
    if (self->heads.contents)
      array_delete(&self->heads);
    if (self->pop_results.contents)
      array_delete(&self->pop_results);
    if (self->pop_paths.contents)
      array_delete(&self->pop_paths);
    if (self->node_pool.contents)
      array_delete(&self->node_pool);
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
  StackNode *node = self->heads.contents[head];
  return node ? &node->entry : NULL;
}

int ts_stack_head_count(const Stack *self) {
  return self->heads.size;
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

static bool stack_node_release(Stack *self, StackNode *node) {
  if (!node)
    return false;
  assert(node->ref_count != 0);
  node->ref_count--;
  if (node->ref_count == 0) {
    for (int i = 0; i < node->successor_count; i++)
      stack_node_release(self, node->successors[i]);
    ts_tree_release(node->entry.tree);

    if (self->node_pool.size >= MAX_NODE_POOL_SIZE)
      ts_free(node);
    else
      array_push(&self->node_pool, node);

    return true;
  } else {
    return false;
  }
}

static StackNode *stack_node_new(Stack *self, StackNode *next, TSStateId state,
                                 TSTree *tree) {
  assert(tree->ref_count > 0);
  StackNode *node;
  if (self->node_pool.size == 0) {
    node = ts_malloc(sizeof(StackNode));
    if (!node)
      return NULL;
  } else {
    node = array_pop(&self->node_pool);
  }

  ts_tree_retain(tree);
  stack_node_retain(next);
  TSLength position = ts_tree_total_size(tree);
  if (next)
    position = ts_length_add(next->entry.position, position);
  *node = (StackNode){
    .ref_count = 1,
    .successor_count = 1,
    .successors = { next, NULL, NULL },
    .entry = {.state = state, .tree = tree, .position = position },
  };
  return node;
}

static void ts_stack__add_alternative_tree(Stack *self, StackNode *node,
                                           TSTree *tree) {
  if (tree != node->entry.tree) {
    int comparison = self->tree_selection_function(self->tree_selection_payload,
                                                   node->entry.tree, tree);

    if (comparison > 0) {
      ts_tree_retain(tree);
      ts_tree_release(node->entry.tree);
      node->entry.tree = tree;
    }
  }
}

static void ts_stack__clear_pop_result(Stack *self, StackPopResult *result) {
  for (size_t i = 0; i < result->trees.size; i++)
    ts_tree_release(result->trees.contents[i]);
  array_delete(&result->trees);
}

static void ts_stack__add_alternative_pop_result(Stack *self,
                                                 StackPopResult *result,
                                                 StackPopResult *new_result) {
  bool should_update = false;
  if (result->trees.size < new_result->trees.size) {
    should_update = true;
  } else if (result->trees.size == new_result->trees.size) {
    for (size_t i = 0; i < result->trees.size; i++) {
      TSTree *tree = result->trees.contents[i];
      TSTree *new_tree = new_result->trees.contents[i];
      int comparison = self->tree_selection_function(
        self->tree_selection_payload, tree, new_tree);
      if (comparison < 0) {
        break;
      } else if (comparison > 0) {
        should_update = true;
        break;
      }
    }
  }

  if (should_update) {
    ts_stack__clear_pop_result(self, result);
    result->trees = new_result->trees;
    result->trees.size = new_result->trees.size;
  } else {
    ts_stack__clear_pop_result(self, new_result);
  }
}

static void ts_stack__add_node_successor(Stack *self, StackNode *node,
                                         StackNode *new_successor) {
  for (int i = 0; i < node->successor_count; i++) {
    StackNode *successor = node->successors[i];
    if (successor == new_successor)
      return;
    if (!successor)
      continue;

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
  if (array_push(&self->heads, node)) {
    stack_node_retain(node);
    return self->heads.size - 1;
  } else {
    return -1;
  }
}

static int ts_stack__find_head(Stack *self, StackNode *node) {
  for (size_t i = 0; i < self->heads.size; i++) {
    if (self->heads.contents[i] == node)
      return i;
  }
  return -1;
}

void ts_stack_remove_head(Stack *self, int head_index) {
  StackNode *node = *array_get(&self->heads, head_index);
  stack_node_release(self, node);
  array_erase(&self->heads, head_index);
}

/*
 *  Section: Mutating the stack (Public)
 */

StackPushResult ts_stack_push(Stack *self, int head_index, TSStateId state,
                              TSTree *tree) {
  TSLength position = ts_tree_total_size(tree);
  StackNode *current_head = *array_get(&self->heads, head_index);
  if (current_head)
    position = ts_length_add(current_head->entry.position, position);

  for (int i = 0; i < head_index; i++) {
    StackNode *prior_node = self->heads.contents[i];
    StackEntry prior_entry = prior_node->entry;
    if (prior_entry.state == state &&
        ts_length_eq(prior_entry.position, position)) {
      ts_stack__add_alternative_tree(self, prior_node, tree);
      ts_stack__add_node_successor(self, prior_node, current_head);
      ts_stack_remove_head(self, head_index);
      return StackPushResultMerged;
    }
  }

  StackNode *new_head = stack_node_new(self, current_head, state, tree);
  if (!new_head)
    return StackPushResultFailed;

  stack_node_release(self, current_head);
  self->heads.contents[head_index] = new_head;
  return StackPushResultContinued;
}

int ts_stack_split(Stack *self, int head_index) {
  StackNode *head = self->heads.contents[head_index];
  return ts_stack__add_head(self, head);
}

StackPopResultArray ts_stack_pop(Stack *self, int head_index, int child_count,
                                 bool count_extra) {
  array_clear(&self->pop_results);
  array_clear(&self->pop_paths);

  StackNode *previous_head = *array_get(&self->heads, head_index);
  int capacity = (child_count == -1) ? STARTING_TREE_CAPACITY : child_count;
  PopPath initial_path = {
    .goal_tree_count = child_count, .node = previous_head, .is_shared = false,
  };
  array_init(&initial_path.trees);

  if (!array_grow(&initial_path.trees, capacity))
    goto error;

  if (!array_push(&self->pop_paths, initial_path))
    goto error;

  /*
   *  Reduce along every possible path in parallel. Stop when the given number
   *  of child trees have been collected along every path.
   */
  bool all_paths_done = false;
  while (!all_paths_done) {
    all_paths_done = true;

    for (size_t i = 0; i < self->pop_paths.size; i++) {
      PopPath *path = &self->pop_paths.contents[i];
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
        path->trees = (TreeArray)array_copy(&path->trees);
        for (size_t j = 0; j < path->trees.size; j++)
          ts_tree_retain(path->trees.contents[j]);
        path->is_shared = false;
      }

      ts_tree_retain(node->entry.tree);
      if (!array_push(&path->trees, node->entry.tree))
        goto error;

      path->node = path->node->successors[0];
      for (int j = 1; j < node->successor_count; j++) {
        if (!array_push(&self->pop_paths, *path))
          goto error;

        PopPath *next_path = array_back(&self->pop_paths);
        next_path->node = node->successors[j];
        next_path->is_shared = true;
      }
    }
  }

  for (size_t i = 0; i < self->pop_paths.size; i++) {
    PopPath *path = &self->pop_paths.contents[i];

    if (!path->is_shared)
      array_reverse(&path->trees);

    StackPopResult result = {
      .trees = path->trees,
      .head_index = -1,
    };

    if (i == 0) {
      stack_node_retain(path->node);
      self->heads.contents[head_index] = path->node;
      result.head_index = head_index;
    } else {
      result.head_index = ts_stack__find_head(self, path->node);
      if (result.head_index == -1) {
        result.head_index = ts_stack__add_head(self, path->node);
        if (result.head_index == -1)
          goto error;
      } else {
        bool merged_result = false;
        for (size_t j = 0; j < self->pop_results.size; j++) {
          StackPopResult *prior_result = &self->pop_results.contents[j];
          if (prior_result->head_index == result.head_index) {
            ts_stack__add_alternative_pop_result(self, prior_result, &result);
            merged_result = true;
            break;
          }
        }
        if (merged_result)
          continue;
      }
    }

    if (!array_push(&self->pop_results, result))
      goto error;
  }

  stack_node_release(self, previous_head);
  return self->pop_results;

error:
  array_delete(&initial_path.trees);
  StackPopResultArray result;
  array_init(&result);
  return result;
}

void ts_stack_shrink(Stack *self, int head_index, int count) {
  StackNode *head = *array_get(&self->heads, head_index);
  StackNode *new_head = head;
  for (int i = 0; i < count; i++) {
    if (new_head->successor_count == 0)
      break;
    new_head = new_head->successors[0];
  }
  stack_node_retain(new_head);
  stack_node_release(self, head);
  self->heads.contents[head_index] = new_head;
}

void ts_stack_clear(Stack *self) {
  for (size_t i = 0; i < self->heads.size; i++)
    stack_node_release(self, self->heads.contents[i]);
  array_clear(&self->heads);
  array_push(&self->heads, NULL);
}

void ts_stack_set_tree_selection_callback(Stack *self, void *payload,
                                          TreeSelectionFunction function) {
  self->tree_selection_payload = payload;
  self->tree_selection_function = function;
}

void ts_stack_delete(Stack *self) {
  if (self->pop_paths.contents)
    array_delete(&self->pop_results);
  if (self->pop_paths.contents)
    array_delete(&self->pop_paths);
  ts_stack_clear(self);
  if (self->node_pool.contents) {
    for (size_t i = 0; i < self->node_pool.size; i++)
      ts_free(self->node_pool.contents[i]);
    array_delete(&self->node_pool);
  }
  array_delete(&self->heads);
  ts_free(self);
}
