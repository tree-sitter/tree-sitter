#include "tree_sitter/parser.h"
#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/array.h"
#include "runtime/stack.h"
#include "runtime/length.h"
#include <assert.h>
#include <stdio.h>

#define MAX_LINK_COUNT 8
#define STARTING_TREE_CAPACITY 10
#define MAX_NODE_POOL_SIZE 50

#define ALWAYS_INLINE __attribute__((always_inline))

typedef struct StackNode StackNode;

typedef struct {
  StackNode *node;
  TSTree *tree;
  bool is_pending;
} StackLink;

struct StackNode {
  TSStateId state;
  TSLength position;
  StackLink links[MAX_LINK_COUNT];
  short unsigned int link_count;
  short unsigned int ref_count;
};

typedef struct {
  TreeArray trees;
  size_t essential_tree_count;
  StackNode *node;
  bool is_done;
  bool is_pending;
} PopPath;

typedef struct {
  size_t goal_tree_count;
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
    for (int i = 0; i < self->link_count; i++) {
      ts_tree_release(self->links[i].tree);
      stack_node_release(self->links[i].node, pool);
    }

    if (pool->size >= MAX_NODE_POOL_SIZE)
      ts_free(self);
    else
      array_push(pool, self);
  }
}

static StackNode *stack_node_new(StackNode *next, TSTree *tree, bool is_pending,
                                 TSStateId state, TSLength position,
                                 StackNodeArray *pool) {
  StackNode *node;
  if (pool->size > 0)
    node = array_pop(pool);
  else if (!(node = ts_malloc(sizeof(StackNode))))
    return NULL;

  *node = (StackNode){
    .ref_count = 1,
    .link_count = 0,
    .links = {},
    .state = state,
    .position = position,
  };

  if (next) {
    ts_tree_retain(tree);
    stack_node_retain(next);
    node->link_count = 1;
    node->links[0] = (StackLink){ next, tree, is_pending };
  }

  return node;
}

static void stack_node_add_link(StackNode *self, StackLink link) {
  for (int i = 0; i < self->link_count; i++) {
    StackLink existing_link = self->links[i];
    if (existing_link.tree == link.tree) {
      if (existing_link.node == link.node)
        return;
      if (existing_link.node->state == link.node->state) {
        for (int j = 0; j < link.node->link_count; j++)
          stack_node_add_link(existing_link.node, link.node->links[j]);
        return;
      }
    }
  }

  if (self->link_count < MAX_LINK_COUNT) {
    stack_node_retain(link.node);
    ts_tree_retain(link.tree);
    self->links[self->link_count++] = (StackLink){
      link.node, link.tree, link.is_pending,
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
    stack_node_new(NULL, NULL, false, 0, ts_length_zero(), &self->node_pool);
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

TSStateId ts_stack_top_state(const Stack *self, StackVersion version) {
  return (*array_get(&self->heads, version))->state;
}

TSLength ts_stack_top_position(const Stack *self, StackVersion version) {
  return (*array_get(&self->heads, version))->position;
}

size_t ts_stack_version_count(const Stack *self) {
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

static StackVersion ts_stack__add_version(Stack *self, StackNode *node) {
  if (!array_push(&self->heads, node))
    return STACK_VERSION_NONE;
  stack_node_retain(node);
  return (StackVersion)(self->heads.size - 1);
}

void ts_stack_remove_version(Stack *self, StackVersion version) {
  StackNode *node = *array_get(&self->heads, version);
  stack_node_release(node, &self->node_pool);
  array_erase(&self->heads, version);
}

/*
 *  Section: Mutating the stack (Public)
 */

bool ts_stack_push(Stack *self, StackVersion version, TSTree *tree,
                   bool is_pending, TSStateId state) {
  StackNode *node = *array_get(&self->heads, version);
  TSLength position = ts_length_add(node->position, ts_tree_total_size(tree));
  StackNode *new_node =
    stack_node_new(node, tree, is_pending, state, position, &self->node_pool);
  if (!new_node)
    return false;
  stack_node_release(node, &self->node_pool);
  self->heads.contents[version] = new_node;
  return true;
}

void ts_stack_merge(Stack *self) {
  for (size_t i = 0; i < self->heads.size; i++) {
    StackNode *node = self->heads.contents[i];
    for (size_t j = 0; j < i; j++) {
      StackNode *prior_node = self->heads.contents[j];
      if (prior_node->state == node->state &&
          prior_node->position.chars == node->position.chars) {
        for (size_t k = 0; k < node->link_count; k++) {
          StackLink link = node->links[k];
          stack_node_add_link(prior_node, link);
        }
        ts_stack_remove_version(self, i--);
        break;
      }
    }
  }
}

void ts_stack_renumber_version(Stack *self, StackVersion v1, StackVersion v2) {
  assert(v2 < v1);
  assert((size_t)v1 < self->heads.size);
  stack_node_release(self->heads.contents[v2], &self->node_pool);
  self->heads.contents[v2] = self->heads.contents[v1];
  array_erase(&self->heads, v1);
}

static inline ALWAYS_INLINE StackPopResult
  stack__pop(Stack *self, StackVersion version, StackIterateCallback callback,
             void *payload) {
  array_clear(&self->slices);
  array_clear(&self->pop_paths);
  PopPath pop_path = {
    .node = *array_get(&self->heads, version),
    .trees = array_new(),
    .essential_tree_count = 0,
    .is_done = false,
    .is_pending = true,
  };
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
      size_t link_count = node->link_count;
      switch (callback(payload, node->state, path->essential_tree_count,
                       node == self->base_node, path->is_pending && depth > 0)) {
        case StackIteratePop:
          path->is_done = true;
          continue;
        case StackIterateAbort:
          link_count = 0;
          break;
        default:
          break;
      }

      if (!link_count) {
        ts_tree_array_delete(&path->trees);
        array_erase(&self->pop_paths, i--);
        size--;
        continue;
      }

      all_paths_done = false;

      for (size_t j = 1; j <= link_count; j++) {
        PopPath *next_path;
        StackLink link;
        if (j == link_count) {
          link = node->links[0];
          next_path = &self->pop_paths.contents[i];
        } else {
          link = node->links[j];
          if (!array_push(&self->pop_paths, self->pop_paths.contents[i]))
            goto error;
          next_path = array_back(&self->pop_paths);
          next_path->trees = ts_tree_array_copy(&next_path->trees);
        }

        next_path->node = link.node;
        if (!array_push(&next_path->trees, link.tree))
          goto error;
        if (!link.tree->extra &&
            link.tree->symbol != ts_builtin_sym_error)
          next_path->essential_tree_count++;
        if (!link.is_pending)
          next_path->is_pending = false;
        ts_tree_retain(link.tree);
      }
    }
  }

  for (size_t i = 0; i < self->pop_paths.size; i++) {
    PopPath *path = &self->pop_paths.contents[i];
    if (!path->is_done)
      continue;

    StackSlice slice = {.trees = path->trees, .version = STACK_VERSION_NONE };
    array_reverse(&slice.trees);

    bool merged = false;
    for (size_t j = 0; j < self->slices.size; j++) {
      StackSlice *prior_slice = &self->slices.contents[j];
      StackNode *prior_node = self->heads.contents[prior_slice->version];
      if (prior_node == path->node) {
        ts_stack__merge_slice(self, prior_slice, &slice);
        merged = true;
        break;
      }
    }

    if (!merged) {
      slice.version = ts_stack__add_version(self, path->node);
      if (slice.version == STACK_VERSION_NONE)
        goto error;
      if (!array_push(&self->slices, slice))
        goto error;
    }
  }

  return (StackPopResult){.status = StackPopSucceeded, .slices = self->slices };

error:
  for (size_t i = 0; i < self->pop_paths.size; i++)
    array_delete(&self->pop_paths.contents[i].trees);
  array_clear(&self->slices);
  return (StackPopResult){.status = StackPopFailed };
}

StackPopResult ts_stack_pop_until(Stack *self, StackVersion version,
                                  StackIterateCallback callback, void *payload) {
  return stack__pop(self, version, callback, payload);
}

static inline ALWAYS_INLINE StackIterateAction
  stack__pop_count_callback(void *payload, TSStateId state, size_t tree_count,
                            bool is_done, bool is_pending) {
  StackPopSession *pop_session = (StackPopSession *)payload;
  if (pop_session->found_error)
    return StackIterateAbort;
  if (tree_count == pop_session->goal_tree_count)
    return StackIteratePop;
  if (state == ts_parse_state_error) {
    pop_session->found_error = true;
    return StackIteratePop;
  }
  return StackIterateContinue;
}

StackPopResult ts_stack_pop_count(Stack *self, StackVersion version,
                                  size_t count) {
  StackPopSession session = {.goal_tree_count = count, .found_error = false };

  StackPopResult pop =
    stack__pop(self, version, stack__pop_count_callback, &session);

  if (pop.status && session.found_error) {
    pop.status = StackPopStoppedAtError;
    array_reverse(&pop.slices);
    while (pop.slices.size > 1) {
      StackSlice slice = array_pop(&pop.slices);
      ts_tree_array_delete(&slice.trees);
      ts_stack_remove_version(self, slice.version);
    }
  }

  return pop;
}

static inline ALWAYS_INLINE StackIterateAction
  stack__pop_pending_callback(void *payload, TSStateId state, size_t tree_count,
                              bool is_done, bool is_pending) {
  if (tree_count >= 1)
    return is_pending ? StackIteratePop : StackIterateAbort;
  else
    return StackIterateContinue;
}

StackPopResult ts_stack_pop_pending(Stack *self, StackVersion version) {
  StackPopResult pop = stack__pop(self, version, stack__pop_pending_callback, NULL);
  if (pop.slices.size > 0) {
    ts_stack_renumber_version(self, pop.slices.contents[0].version, version);
    pop.slices.contents[0].version = version;
  }
  return pop;
}

static inline ALWAYS_INLINE StackIterateAction
  stack__pop_all_callback(void *payload, TSStateId state, size_t tree_count,
                          bool is_done, bool is_pending) {
  return is_done ? StackIteratePop : StackIterateContinue;
}

TreeArray ts_stack_pop_all(Stack *self, StackVersion version) {
  StackPopResult pop = stack__pop(self, version, stack__pop_all_callback, NULL);
  if (pop.status != StackPopSucceeded)
    return (TreeArray)array_new();
  assert(pop.slices.size == 1);
  ts_stack_renumber_version(self, pop.slices.contents[0].version, version);
  return pop.slices.contents[0].trees;
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

int ts_stack_print_dot_graph(Stack *self, const char **symbol_names, FILE *f) {
  fprintf(f, "digraph stack {\n");
  fprintf(f, "rankdir=\"RL\";\n");

  Array(StackNode *)visited_nodes;
  array_init(&visited_nodes);

  array_clear(&self->pop_paths);
  for (size_t i = 0; i < self->heads.size; i++) {
    StackNode *node = self->heads.contents[i];
    size_t color_count = sizeof(COLORS) / sizeof(COLORS[0]);
    const char *color = COLORS[i % color_count];
    fprintf(f, "node_%p [color=%s];\n", node, color);
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

      fprintf(f, "node_%p [label=", node);
      if (node->state == ts_parse_state_error)
        fprintf(f, "\"?\"");
      else
        fprintf(f, "%d", node->state);
      fprintf(f, "];\n");

      for (int j = 0; j < node->link_count; j++) {
        StackLink link = node->links[j];
        fprintf(f, "node_%p -> node_%p [", node, link.node);
        if (link.is_pending)
          fprintf(f, "style=dashed ");
        fprintf(f, "label=\"");

        if (link.tree->symbol == ts_builtin_sym_error) {
          fprintf(f, "ERROR");
        } else {
          const char *name = symbol_names[link.tree->symbol];
          for (const char *c = name; *c; c++) {
            if (*c == '\"' || *c == '\\')
              fprintf(f, "\\");
            fprintf(f, "%c", *c);
          }
        }

        fprintf(f, "\"];\n");

        if (j == 0) {
          path->node = link.node;
        } else {
          if (!array_push(&self->pop_paths, *path))
            goto error;
          PopPath *next_path = array_back(&self->pop_paths);
          next_path->node = link.node;
        }
      }

      if (!array_push(&visited_nodes, node))
        goto error;
    }
  }

  fprintf(f, "}\n");

  array_delete(&visited_nodes);

error:
  return -1;
}
