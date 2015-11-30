#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/vector.h"
#include "runtime/stack.h"
#include "runtime/length.h"
#include <assert.h>

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
  TreeSelectionCallback tree_selection_callback;
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

Stack *ts_stack_new(TreeSelectionCallback tree_selection_callback) {
  Stack *self = malloc(sizeof(Stack));
  *self = (Stack){
    .heads = calloc(INITIAL_HEAD_CAPACITY, sizeof(StackNode *)),
    .head_count = 1,
    .head_capacity = INITIAL_HEAD_CAPACITY,
    .tree_selection_callback = tree_selection_callback,
    .pop_results = vector_new(sizeof(StackPopResult), 4),
    .pop_paths = vector_new(sizeof(PopPath), 4),
  };
  return self;
}

void ts_stack_delete(Stack *self) {
  vector_delete(&self->pop_results);
  vector_delete(&self->pop_paths);
  free(self->heads);
  free(self);
}

/*
 *  Section: Reading from the stack
 */

TSStateId ts_stack_top_state(const Stack *self, int head) {
  StackEntry *entry = ts_stack_head((Stack *)self, head);
  return entry ? entry->state : 0;
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
    free(self);
    return true;
  } else {
    return false;
  }
}

static StackNode *stack_node_new(StackNode *next, TSStateId state, TSTree *tree) {
  StackNode *self = malloc(sizeof(StackNode));
  assert(tree->ref_count > 0);
  ts_tree_retain(tree);
  stack_node_retain(next);
  *self = (StackNode){
    .ref_count = 1,
    .successor_count = 1,
    .successors = { next, NULL, NULL },
    .entry =
      {
        .state = state, .tree = tree,
      },
  };
  return self;
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
      if (successor->entry.tree != new_successor->entry.tree) {
        successor->entry.tree = self->tree_selection_callback.callback(
          self->tree_selection_callback.data, successor->entry.tree,
          new_successor->entry.tree);
        ts_tree_retain(successor->entry.tree);
      }
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
      realloc(self->heads, self->head_capacity * sizeof(StackNode *));
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
                                 TSTree *tree) {
  for (int i = 0; i < head_index; i++) {
    StackNode *head = self->heads[i];
    if (head->entry.state == state) {
      if (head->entry.tree != tree) {
        head->entry.tree = self->tree_selection_callback.callback(
          self->tree_selection_callback.data, head->entry.tree, tree);
        ts_tree_retain(head->entry.tree);
      }
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

bool ts_stack_push(Stack *self, int head_index, TSStateId state, TSTree *tree) {
  assert(head_index < self->head_count);
  if (ts_stack__merge_head(self, head_index, state, tree))
    return true;
  self->heads[head_index] = stack_node_new(self->heads[head_index], state, tree);
  return false;
}

void ts_stack_add_alternative(Stack *self, int head_index, TSTree *tree) {
  assert(head_index < self->head_count);
  StackEntry *entry = &self->heads[head_index]->entry;
  entry->tree = self->tree_selection_callback.callback(
    self->tree_selection_callback.data, entry->tree, tree);
}

int ts_stack_split(Stack *self, int head_index) {
  assert(head_index < self->head_count);
  return ts_stack__add_head(self, self->heads[head_index]);
}

Vector ts_stack_pop(Stack *self, int head_index, int child_count,
                    bool count_extra) {
  StackNode *previous_head = self->heads[head_index];
  int capacity = (child_count == -1) ? STARTING_TREE_CAPACITY : child_count;
  PopPath initial_path = {
    .goal_tree_count = child_count,
    .node = previous_head,
    .trees = vector_new(sizeof(TSTree *), capacity),
    .is_shared = false,
  };

  vector_clear(&self->pop_results);
  vector_clear(&self->pop_paths);
  vector_push(&self->pop_paths, &initial_path);

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
      if (ts_tree_is_extra(node->entry.tree) && !count_extra)
        path->goal_tree_count++;

      /*
       *  If a node has more than one successor, create new paths for each of
       *  the additional successors.
       */
      if (path->is_shared) {
        path->trees = vector_copy(&path->trees);
        path->is_shared = false;
      }

      ts_tree_retain(node->entry.tree);
      vector_push(&path->trees, &node->entry.tree);

      path->node = path->node->successors[0];
      for (int j = 1; j < node->successor_count; j++) {
        PopPath path_copy = *path;
        vector_push(&self->pop_paths, &path_copy);
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

    vector_push(&self->pop_results, &result);
  }

  stack_node_release(previous_head);
  return self->pop_results;
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
