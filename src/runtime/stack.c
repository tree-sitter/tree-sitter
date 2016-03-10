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

#if __has_attribute(always_inline)
#define ALWAYS_INLINE __attribute__((always_inline))
#else
#define ALWAYS_INLINE
#endif

typedef struct StackNode StackNode;

typedef struct {
  StackNode *node;
  TSTree *tree;
} StackLink;

struct StackNode {
  TSStateId state;
  TSLength position;
  StackLink successors[MAX_SUCCESSOR_COUNT];
  short unsigned int successor_count;
  short unsigned int ref_count;
};

typedef struct {
  TreeArray trees;
  size_t extra_count;
  StackNode *node;
  bool is_done;
} PopPath;

typedef struct {
  int goal_tree_count;
  bool found_error;
} StackPopSession;

typedef Array(StackNode *) StackNodeArray;

struct Stack {
  Array(StackNode *) heads;
  StackSliceArray slices;
  Array(PopPath) pop_paths;
  StackNodeArray node_pool;
  void *tree_selection_payload;
  TreeSelectionFunction tree_selection_function;
  StackNode *base_node;
};

static const char *COLORS[] = {
  "red", "blue", "orange", "green", "purple",
};

/*
 *  Section: Manipulating nodes (Private)
 */

static void stack_node_retain(StackNode *self) {
  if (!self)
    return;
  assert(self->ref_count != 0);
  self->ref_count++;
}

static void stack_node_release(StackNode *self, StackNodeArray *pool) {
  if (!self)
    return;
  assert(self->ref_count != 0);
  self->ref_count--;
  if (self->ref_count == 0) {
    for (int i = 0; i < self->successor_count; i++) {
      ts_tree_release(self->successors[i].tree);
      stack_node_release(self->successors[i].node, pool);
    }

    if (pool->size >= MAX_NODE_POOL_SIZE)
      ts_free(self);
    else
      array_push(pool, self);
  }
}

static StackNode *stack_node_new(StackNode *next, TSTree *tree, TSStateId state,
                                 TSLength position, StackNodeArray *pool) {
  StackNode *node;
  if (pool->size > 0)
    node = array_pop(pool);
  else if (!(node = ts_malloc(sizeof(StackNode))))
    return NULL;

  *node = (StackNode){
    .ref_count = 1,
    .successor_count = 0,
    .successors = {},
    .state = state,
    .position = position,
  };

  if (next) {
    ts_tree_retain(tree);
    stack_node_retain(next);
    node->successor_count = 1, node->successors[0] = (StackLink){ next, tree };
  }

  return node;
}

static void stack_node_add_successor(StackNode *self, TSTree *new_tree,
                                     StackNode *new_node) {
  for (int i = 0; i < self->successor_count; i++) {
    StackLink successor = self->successors[i];
    if (successor.tree == new_tree) {
      if (successor.node == new_node)
        return;
      if (successor.node && new_node &&
          successor.node->state == new_node->state) {
        for (int j = 0; j < new_node->successor_count; j++) {
          stack_node_add_successor(successor.node, new_node->successors[j].tree,
                                   new_node->successors[j].node);
        }
        return;
      }
    }
  }

  if (self->successor_count < MAX_SUCCESSOR_COUNT) {
    stack_node_retain(new_node);
    ts_tree_retain(new_tree);
    self->successors[self->successor_count++] = (StackLink){
      new_node, new_tree,
    };
  }
}

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
  array_init(&self->slices);
  array_init(&self->pop_paths);
  array_init(&self->node_pool);
  self->tree_selection_payload = NULL;
  self->tree_selection_function = ts_stack__default_tree_selection;

  if (!array_grow(&self->heads, 4))
    goto error;

  if (!array_grow(&self->slices, 4))
    goto error;

  if (!array_grow(&self->pop_paths, 4))
    goto error;

  if (!array_grow(&self->node_pool, 20))
    goto error;

  self->base_node =
    stack_node_new(NULL, NULL, 0, ts_length_zero(), &self->node_pool);
  stack_node_retain(self->base_node);
  if (!self->base_node)
    goto error;

  array_push(&self->heads, self->base_node);

  return self;

error:
  if (self) {
    if (self->heads.contents)
      array_delete(&self->heads);
    if (self->slices.contents)
      array_delete(&self->slices);
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

TSStateId ts_stack_top_state(const Stack *self, int head_index) {
  return (*array_get(&self->heads, head_index))->state;
}

TSLength ts_stack_top_position(const Stack *self, int head_index) {
  return (*array_get(&self->heads, head_index))->position;
}

int ts_stack_head_count(const Stack *self) {
  return self->heads.size;
}

static void ts_stack__merge_slice(Stack *self, StackSlice *slice,
                                  StackSlice *new_slice) {
  bool should_update = false;
  if (slice->trees.size < new_slice->trees.size) {
    should_update = true;
  } else if (slice->trees.size == new_slice->trees.size) {
    for (size_t i = 0; i < slice->trees.size; i++) {
      TSTree *tree = slice->trees.contents[i];
      TSTree *new_tree = new_slice->trees.contents[i];
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
    ts_tree_array_delete(&slice->trees);
    slice->trees = new_slice->trees;
    slice->trees.size = new_slice->trees.size;
  } else {
    ts_tree_array_delete(&new_slice->trees);
  }
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

static int ts_stack__index_of_head(Stack *self, StackNode *node) {
  for (size_t i = 0; i < self->heads.size; i++) {
    if (self->heads.contents[i] == node)
      return i;
  }
  return -1;
}

void ts_stack_remove_head(Stack *self, int head_index) {
  StackNode *node = *array_get(&self->heads, head_index);
  stack_node_release(node, &self->node_pool);
  array_erase(&self->heads, head_index);
}

/*
 *  Section: Mutating the stack (Public)
 */

StackPushResult ts_stack_push(Stack *self, int head_index, TSTree *tree,
                              TSStateId state) {
  StackNode *current_head = *array_get(&self->heads, head_index);
  TSLength position =
    ts_length_add(current_head->position, ts_tree_total_size(tree));

  for (int i = 0; i < head_index; i++) {
    StackNode *prior_node = self->heads.contents[i];
    if (prior_node->state == state &&
        prior_node->position.chars == position.chars) {
      stack_node_add_successor(prior_node, tree, current_head);
      ts_stack_remove_head(self, head_index);
      return StackPushMerged;
    }
  }

  StackNode *new_head =
    stack_node_new(current_head, tree, state, position, &self->node_pool);
  if (!new_head)
    return StackPushFailed;

  stack_node_release(current_head, &self->node_pool);
  self->heads.contents[head_index] = new_head;
  return StackPushContinued;
}

int ts_stack_split(Stack *self, int head_index) {
  StackNode *head = self->heads.contents[head_index];
  return ts_stack__add_head(self, head);
}

static inline ALWAYS_INLINE StackSliceArray stack__pop(
  Stack *self, int head_index, StackIterateCallback callback, void *payload) {
  array_clear(&self->slices);
  array_clear(&self->pop_paths);
  StackNode *initial_head = *array_get(&self->heads, head_index);

  PopPath pop_path = {
    .node = initial_head, .trees = array_new(), .extra_count = 0, .is_done = false,
  };
  if (!array_grow(&pop_path.trees, STARTING_TREE_CAPACITY))
    goto error;
  if (!array_push(&self->pop_paths, pop_path))
    goto error;

  bool all_paths_done = false;
  for (size_t depth = 0; !all_paths_done; depth++) {
    all_paths_done = true;
    for (size_t i = 0, size = self->pop_paths.size; i < size; i++) {
      PopPath *path = &self->pop_paths.contents[i];
      if (path->is_done)
        continue;

      StackNode *node = path->node;
      size_t successor_count = node->successor_count;
      switch (callback(payload, node->state, depth, path->extra_count)) {
        case StackIteratePop:
          path->is_done = true;
          continue;
        case StackIterateAbort:
          successor_count = 0;
          break;
        default:
          break;
      }

      if (!successor_count) {
        ts_tree_array_delete(&path->trees);
        array_erase(&self->pop_paths, i--);
        size--;
        continue;
      }

      all_paths_done = false;

      for (size_t j = 0; j < successor_count; j++) {
        StackLink successor = node->successors[j];

        PopPath *next_path;
        if (j == 0) {
          next_path = path;
        } else {
          if (!array_push(&self->pop_paths, *path))
            goto error;
          next_path = array_back(&self->pop_paths);
          next_path->trees.size--;
          next_path->trees = ts_tree_array_copy(&next_path->trees);
        }

        next_path->node = successor.node;
        if (!array_push(&next_path->trees, successor.tree))
          goto error;
        if (successor.tree->extra)
          next_path->extra_count++;
        ts_tree_retain(successor.tree);
      }
    }
  }

  for (size_t i = 0; i < self->pop_paths.size; i++) {
    PopPath *path = &self->pop_paths.contents[i];
    if (!path->is_done)
      continue;

    StackSlice slice = {.trees = path->trees, .head_index = -1 };
    array_reverse(&slice.trees);

    if (i == 0) {
      stack_node_retain(path->node);
      self->heads.contents[head_index] = path->node;
      slice.head_index = head_index;
    } else {
      slice.head_index = ts_stack__index_of_head(self, path->node);
      if (slice.head_index == -1) {
        if ((slice.head_index = ts_stack__add_head(self, path->node)) == -1)
          goto error;
      } else {
        bool merged = false;
        for (size_t j = 0; j < self->slices.size; j++) {
          StackSlice *prior_result = &self->slices.contents[j];
          if (prior_result->head_index == slice.head_index) {
            ts_stack__merge_slice(self, prior_result, &slice);
            merged = true;
            break;
          }
        }
        if (merged)
          continue;
      }
    }

    if (!array_push(&self->slices, slice))
      goto error;
  }

  if (self->slices.size)
    stack_node_release(initial_head, &self->node_pool);
  return self->slices;

error:
  for (size_t i = 0; i < self->pop_paths.size; i++)
    array_delete(&self->pop_paths.contents[i].trees);
  array_clear(&self->slices);
  return self->slices;
}

static inline ALWAYS_INLINE StackIterateAction stack__pop_count_callback(
  void *payload, TSStateId state, size_t depth, size_t extra_count) {
  StackPopSession *pop_session = (StackPopSession *)payload;
  if (pop_session->found_error)
    return StackIterateAbort;

  if (state == ts_parse_state_error && pop_session->goal_tree_count > 0) {
    pop_session->found_error = true;
    return StackIteratePop;
  }

  if ((int)(depth - extra_count) == pop_session->goal_tree_count)
    return StackIteratePop;

  if (state == 0 && depth > 0)
    return StackIteratePop;

  return StackIterateContinue;
}

StackPopResult ts_stack_pop_count(Stack *self, int head_index, int count) {
  StackPopSession session = {
    .goal_tree_count = count, .found_error = false,
  };

  StackSliceArray slices =
    stack__pop(self, head_index, stack__pop_count_callback, &session);
  int status;
  if (slices.size) {
    if (session.found_error)
      status = StackPopStoppedAtError;
    else
      status = StackPopSucceeded;
  } else {
    status = StackPopFailed;
  }

  return (StackPopResult){.status = status, .slices = slices };
}

StackPopResult ts_stack_pop_until(Stack *self, int head_index,
                                  StackIterateCallback callback, void *payload) {
  StackSliceArray slices = stack__pop(self, head_index, callback, payload);
  return (StackPopResult){.status = StackPopSucceeded, .slices = slices };
}

void ts_stack_shrink(Stack *self, int head_index, int count) {
  StackNode *head = *array_get(&self->heads, head_index);
  StackNode *new_head = head;
  for (int i = 0; i < count; i++) {
    if (new_head->successor_count == 0)
      break;
    new_head = new_head->successors[0].node;
  }
  stack_node_retain(new_head);
  stack_node_release(head, &self->node_pool);
  self->heads.contents[head_index] = new_head;
}

void ts_stack_clear(Stack *self) {
  stack_node_retain(self->base_node);
  for (size_t i = 0; i < self->heads.size; i++)
    stack_node_release(self->heads.contents[i], &self->node_pool);
  array_clear(&self->heads);
  array_push(&self->heads, self->base_node);
}

void ts_stack_set_tree_selection_callback(Stack *self, void *payload,
                                          TreeSelectionFunction function) {
  self->tree_selection_payload = payload;
  self->tree_selection_function = function;
}

void ts_stack_delete(Stack *self) {
  if (self->pop_paths.contents)
    array_delete(&self->slices);
  if (self->pop_paths.contents)
    array_delete(&self->pop_paths);
  stack_node_release(self->base_node, &self->node_pool);
  for (size_t i = 0; i < self->heads.size; i++)
    stack_node_release(self->heads.contents[i], &self->node_pool);
  array_clear(&self->heads);
  if (self->node_pool.contents) {
    for (size_t i = 0; i < self->node_pool.size; i++)
      ts_free(self->node_pool.contents[i]);
    array_delete(&self->node_pool);
  }
  array_delete(&self->heads);
  ts_free(self);
}

size_t ts_stack__write_dot_graph(Stack *self, char *string, size_t n,
                                 const char **symbol_names) {
  char *cursor = string;
  char **s = n > 0 ? &cursor : &string;
  cursor += snprintf(*s, n, "digraph stack {\n");
  cursor += snprintf(*s, n, "rankdir=\"RL\";\n");

  Array(StackNode *)visited_nodes;
  array_init(&visited_nodes);

  array_clear(&self->pop_paths);
  for (size_t i = 0; i < self->heads.size; i++) {
    StackNode *node = self->heads.contents[i];
    size_t color_count = sizeof(COLORS) / sizeof(COLORS[0]);
    const char *color = COLORS[i % color_count];
    cursor += snprintf(*s, n, "node_%p [color=%s];\n", node, color);
    array_push(&self->pop_paths, ((PopPath){.node = node }));
  }

  bool all_paths_done = false;
  while (!all_paths_done) {
    all_paths_done = true;

    for (size_t i = 0; i < self->pop_paths.size; i++) {
      PopPath *path = &self->pop_paths.contents[i];
      StackNode *node = path->node;

      for (size_t j = 0; j < visited_nodes.size; j++) {
        if (visited_nodes.contents[j] == node) {
          node = NULL;
          break;
        }
      }

      if (!node)
        continue;
      all_paths_done = false;

      cursor += snprintf(*s, n, "node_%p [label=", node);
      if (node->state == ts_parse_state_error)
        cursor += snprintf(*s, n, "\"?\"");
      else
        cursor += snprintf(*s, n, "%d", node->state);
      cursor += snprintf(*s, n, "];\n");

      for (int j = 0; j < node->successor_count; j++) {
        StackLink successor = node->successors[j];
        cursor +=
          snprintf(*s, n, "node_%p -> node_%p [label=\"", node, successor.node);

        if (successor.tree->symbol == ts_builtin_sym_error) {
          cursor += snprintf(*s, n, "ERROR");
        } else {
          const char *name = symbol_names[successor.tree->symbol];
          for (const char *c = name; *c; c++) {
            if (*c == '\"' || *c == '\\') {
              **s = '\\';
              cursor++;
            }
            **s = *c;
            cursor++;
          }
        }

        cursor += snprintf(*s, n, "\"];\n");

        if (j == 0) {
          path->node = successor.node;
        } else {
          if (!array_push(&self->pop_paths, *path))
            goto error;
          PopPath *next_path = array_back(&self->pop_paths);
          next_path->node = successor.node;
        }
      }

      if (!array_push(&visited_nodes, node))
        goto error;
    }
  }

  cursor += snprintf(*s, n, "}\n");

  array_delete(&visited_nodes);
  return cursor - string;

error:
  array_delete(&visited_nodes);
  return (size_t)-1;
}

char *ts_stack_dot_graph(Stack *self, const char **symbol_names) {
  static char SCRATCH[1];
  char *result = NULL;
  size_t size = ts_stack__write_dot_graph(self, SCRATCH, 0, symbol_names) + 1;
  if (size == (size_t)-1)
    goto error;

  result = ts_malloc(size * sizeof(char));
  if (!result)
    goto error;

  size = ts_stack__write_dot_graph(self, result, size, symbol_names);
  if (size == (size_t)-1)
    goto error;

  return result;

error:
  if (result)
    ts_free(result);
  return NULL;
}
