#include "tree_sitter/parser.h"
#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/array.h"
#include "runtime/stack.h"
#include "runtime/length.h"
#include <assert.h>
#include <stdio.h>

#define MAX_LINK_COUNT 8
#define MAX_NODE_POOL_SIZE 50

#define INLINE static inline __attribute__((always_inline))

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
  unsigned error_cost;
  unsigned error_count;
  unsigned error_depth;
};

typedef struct {
  TreeArray trees;
  size_t tree_count;
  StackNode *node;
  bool is_pending;
} PopPath;

typedef struct {
  size_t goal_tree_count;
  bool found_error;
  bool found_valid_path;
} StackPopSession;

typedef Array(StackNode *) StackNodeArray;

typedef struct {
  StackNode *node;
  bool is_halted;
  unsigned push_count;
} StackHead;

struct Stack {
  Array(StackHead) heads;
  StackSliceArray slices;
  Array(PopPath) pop_paths;
  StackNodeArray node_pool;
  StackNode *base_node;
};

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
      if (self->links[i].tree)
        ts_tree_release(self->links[i].tree);
      stack_node_release(self->links[i].node, pool);
    }

    if (pool->size >= MAX_NODE_POOL_SIZE || !array_push(pool, self))
      ts_free(self);
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
    stack_node_retain(next);

    node->link_count = 1;
    node->links[0] = (StackLink){ next, tree, is_pending };

    node->error_count = next->error_count;
    node->error_cost = next->error_cost;
    node->error_depth = next->error_depth;

    if (tree) {
      ts_tree_retain(tree);
      node->error_cost += tree->error_cost;

      if (state == TS_STATE_ERROR) {
        if (!tree->extra) {
          node->error_cost += ERROR_COST_PER_SKIPPED_TREE +
                              ERROR_COST_PER_SKIPPED_CHAR *
                                (tree->padding.chars + tree->size.chars) +
                              ERROR_COST_PER_SKIPPED_LINE *
                                (tree->padding.rows + tree->size.rows);
        }
      } else {
        node->error_depth++;
      }
    } else {
      node->error_count++;
      node->error_depth = 0;
    }
  } else {
    node->error_count = 0;
    node->error_cost = 0;
    node->error_depth = 0;
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
    if (link.tree)
      ts_tree_retain(link.tree);

    self->links[self->link_count++] = (StackLink){
      link.node, link.tree, link.is_pending,
    };
  }
}

static StackVersion ts_stack__add_version(Stack *self, StackNode *node,
                                          unsigned push_count) {
  if (!array_push(&self->heads, ((StackHead){ node, false, push_count })))
    return STACK_VERSION_NONE;
  stack_node_retain(node);
  return (StackVersion)(self->heads.size - 1);
}

static bool ts_stack__add_slice(Stack *self, StackNode *node, TreeArray *trees,
                                unsigned push_count) {
  for (size_t i = self->slices.size - 1; i + 1 > 0; i--) {
    StackVersion version = self->slices.contents[i].version;
    if (self->heads.contents[version].node == node) {
      StackSlice slice = { *trees, version };
      return array_insert(&self->slices, i + 1, slice);
    }
  }

  StackVersion version = ts_stack__add_version(self, node, push_count);
  if (version == STACK_VERSION_NONE)
    return false;
  StackSlice slice = { *trees, version };
  return array_push(&self->slices, slice);
}

INLINE StackPopResult stack__iter(Stack *self, StackVersion version,
                                  StackIterateCallback callback, void *payload) {
  array_clear(&self->slices);
  array_clear(&self->pop_paths);

  StackHead *head = array_get(&self->heads, version);
  PopPath pop_path = {
    .node = head->node,
    .trees = array_new(),
    .tree_count = 0,
    .is_pending = true,
  };
  if (!array_push(&self->pop_paths, pop_path))
    goto error;

  while (self->pop_paths.size > 0) {
    for (size_t i = 0, size = self->pop_paths.size; i < size; i++) {
      PopPath *path = &self->pop_paths.contents[i];
      StackNode *node = path->node;
      bool is_done = node == self->base_node;

      StackIterateAction action =
        callback(payload, node->state, &path->trees, path->tree_count, is_done,
                 path->is_pending);

      bool should_pop = action & StackIteratePop;
      bool should_stop = action & StackIterateStop || node->link_count == 0;

      if (should_pop) {
        TreeArray trees = path->trees;
        if (!should_stop)
          if (!ts_tree_array_copy(trees, &trees))
            goto error;
        array_reverse(&trees);
        if (!ts_stack__add_slice(self, node, &trees, head->push_count))
          goto error;
      }

      if (should_stop) {
        if (!should_pop)
          ts_tree_array_delete(&path->trees);
        array_erase(&self->pop_paths, i);
        i--, size--;
        continue;
      }

      for (size_t j = 1; j <= node->link_count; j++) {
        PopPath *next_path;
        StackLink link;
        if (j == node->link_count) {
          link = node->links[0];
          next_path = &self->pop_paths.contents[i];
        } else {
          link = node->links[j];
          if (!array_push(&self->pop_paths, self->pop_paths.contents[i]))
            goto error;
          next_path = array_back(&self->pop_paths);
          if (!ts_tree_array_copy(next_path->trees, &next_path->trees))
            goto error;
        }

        next_path->node = link.node;
        if (link.tree) {
          if (!link.tree->extra) {
            next_path->tree_count++;
            if (!link.is_pending)
              next_path->is_pending = false;
          }
          if (!array_push(&next_path->trees, link.tree))
            goto error;
          ts_tree_retain(link.tree);
        } else {
          next_path->is_pending = false;
        }
      }
    }
  }

  return (StackPopResult){ StackPopSucceeded, self->slices };

error:
  for (size_t i = 0; i < self->pop_paths.size; i++)
    ts_tree_array_delete(&self->pop_paths.contents[i].trees);
  array_clear(&self->slices);
  return (StackPopResult){.status = StackPopFailed };
}

Stack *ts_stack_new() {
  Stack *self = ts_calloc(1, sizeof(Stack));
  if (!self)
    goto error;

  array_init(&self->heads);
  array_init(&self->slices);
  array_init(&self->pop_paths);
  array_init(&self->node_pool);

  if (!array_grow(&self->heads, 4))
    goto error;

  if (!array_grow(&self->slices, 4))
    goto error;

  if (!array_grow(&self->pop_paths, 4))
    goto error;

  if (!array_grow(&self->node_pool, MAX_NODE_POOL_SIZE))
    goto error;

  self->base_node =
    stack_node_new(NULL, NULL, false, 1, ts_length_zero(), &self->node_pool);
  stack_node_retain(self->base_node);
  if (!self->base_node)
    goto error;

  array_push(&self->heads, ((StackHead){ self->base_node, false, 0 }));

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

void ts_stack_delete(Stack *self) {
  if (self->slices.contents)
    array_delete(&self->slices);
  if (self->pop_paths.contents)
    array_delete(&self->pop_paths);
  stack_node_release(self->base_node, &self->node_pool);
  for (size_t i = 0; i < self->heads.size; i++)
    stack_node_release(self->heads.contents[i].node, &self->node_pool);
  array_clear(&self->heads);
  if (self->node_pool.contents) {
    for (size_t i = 0; i < self->node_pool.size; i++)
      ts_free(self->node_pool.contents[i]);
    array_delete(&self->node_pool);
  }
  array_delete(&self->heads);
  ts_free(self);
}

size_t ts_stack_version_count(const Stack *self) {
  return self->heads.size;
}

TSStateId ts_stack_top_state(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->state;
}

TSLength ts_stack_top_position(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->position;
}

unsigned ts_stack_push_count(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->push_count;
}

ErrorStatus ts_stack_error_status(const Stack *self, StackVersion version) {
  StackHead *head = array_get(&self->heads, version);
  return (ErrorStatus){
    .cost = head->node->error_cost,
    .count = head->node->error_count,
    .push_count = head->push_count,
  };
}

unsigned ts_stack_error_count(const Stack *self, StackVersion version) {
  StackNode *node = array_get(&self->heads, version)->node;
  return node->error_count;
}

bool ts_stack_push(Stack *self, StackVersion version, TSTree *tree,
                   bool is_pending, TSStateId state) {
  StackHead *head = array_get(&self->heads, version);
  StackNode *node = head->node;
  TSLength position = node->position;
  if (tree)
    position = ts_length_add(position, ts_tree_total_size(tree));
  StackNode *new_node =
    stack_node_new(node, tree, is_pending, state, position, &self->node_pool);
  if (!new_node)
    return false;
  stack_node_release(node, &self->node_pool);
  head->node = new_node;
  if (state == TS_STATE_ERROR)
    head->push_count = 0;
  else
    head->push_count++;
  return true;
}

StackPopResult ts_stack_iterate(Stack *self, StackVersion version,
                                StackIterateCallback callback, void *payload) {
  return stack__iter(self, version, callback, payload);
}

INLINE StackIterateAction pop_count_callback(void *payload, TSStateId state,
                                             TreeArray *trees, size_t tree_count,
                                             bool is_done, bool is_pending) {
  StackPopSession *pop_session = (StackPopSession *)payload;

  if (tree_count == pop_session->goal_tree_count) {
    pop_session->found_valid_path = true;
    return StackIteratePop | StackIterateStop;
  }

  if (state == TS_STATE_ERROR) {
    if (pop_session->found_valid_path || pop_session->found_error) {
      return StackIterateStop;
    } else {
      pop_session->found_error = true;
      return StackIteratePop | StackIterateStop;
    }
  }
  return StackIterateNone;
}

StackPopResult ts_stack_pop_count(Stack *self, StackVersion version,
                                  size_t count) {
  StackPopSession session = {
    .goal_tree_count = count, .found_error = false, .found_valid_path = false,
  };
  StackPopResult pop = stack__iter(self, version, pop_count_callback, &session);
  if (pop.status && session.found_error) {
    if (session.found_valid_path) {
      StackSlice error_slice = pop.slices.contents[0];
      ts_tree_array_delete(&error_slice.trees);
      array_erase(&pop.slices, 0);
      if (array_front(&pop.slices)->version != error_slice.version) {
        ts_stack_remove_version(self, error_slice.version);
        for (StackVersion i = 0; i < pop.slices.size; i++)
          pop.slices.contents[i].version--;
      }
    } else {
      pop.status = StackPopStoppedAtError;
    }
  }
  return pop;
}

INLINE StackIterateAction pop_pending_callback(void *payload, TSStateId state,
                                               TreeArray *trees,
                                               size_t tree_count, bool is_done,
                                               bool is_pending) {
  if (tree_count >= 1) {
    if (is_pending) {
      return StackIteratePop | StackIterateStop;
    } else {
      return StackIterateStop;
    }
  } else {
    return StackIterateNone;
  }
}

StackPopResult ts_stack_pop_pending(Stack *self, StackVersion version) {
  StackPopResult pop = stack__iter(self, version, pop_pending_callback, NULL);
  if (pop.slices.size > 0) {
    ts_stack_renumber_version(self, pop.slices.contents[0].version, version);
    pop.slices.contents[0].version = version;
  }
  return pop;
}

INLINE StackIterateAction pop_all_callback(void *payload, TSStateId state,
                                           TreeArray *trees, size_t tree_count,
                                           bool is_done, bool is_pending) {
  return is_done ? (StackIteratePop | StackIterateStop) : StackIterateNone;
}

StackPopResult ts_stack_pop_all(Stack *self, StackVersion version) {
  return stack__iter(self, version, pop_all_callback, NULL);
}

void ts_stack_remove_version(Stack *self, StackVersion version) {
  StackNode *node = array_get(&self->heads, version)->node;
  stack_node_release(node, &self->node_pool);
  array_erase(&self->heads, version);
}

void ts_stack_renumber_version(Stack *self, StackVersion v1, StackVersion v2) {
  assert(v2 < v1);
  assert((size_t)v1 < self->heads.size);
  stack_node_release(self->heads.contents[v2].node, &self->node_pool);
  self->heads.contents[v2] = self->heads.contents[v1];
  array_erase(&self->heads, v1);
}

StackVersion ts_stack_duplicate_version(Stack *self, StackVersion version) {
  assert(version < self->heads.size);
  if (!array_push(&self->heads, self->heads.contents[version]))
    return STACK_VERSION_NONE;
  stack_node_retain(array_back(&self->heads)->node);
  return self->heads.size - 1;
}

bool ts_stack_merge(Stack *self, StackVersion version, StackVersion new_version) {
  StackHead *head = &self->heads.contents[version];
  StackHead *new_head = &self->heads.contents[new_version];
  StackNode *node = head->node;
  StackNode *new_node = new_head->node;

  if (new_node->state == node->state &&
      new_node->position.chars == node->position.chars &&
      new_node->error_count == node->error_count &&
      new_node->error_cost == node->error_cost) {
    for (size_t j = 0; j < new_node->link_count; j++)
      stack_node_add_link(node, new_node->links[j]);
    if (new_head->push_count > head->push_count)
      head->push_count = new_head->push_count;
    ts_stack_remove_version(self, new_version);
    return true;
  } else {
    return false;
  }
}

void ts_stack_halt(Stack *self, StackVersion version) {
  array_get(&self->heads, version)->is_halted = true;
}

bool ts_stack_is_halted(Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->is_halted;
}

void ts_stack_clear(Stack *self) {
  stack_node_retain(self->base_node);
  for (size_t i = 0; i < self->heads.size; i++)
    stack_node_release(self->heads.contents[i].node, &self->node_pool);
  array_clear(&self->heads);
  array_push(&self->heads, ((StackHead){ self->base_node, false, 0 }));
}

bool ts_stack_print_dot_graph(Stack *self, const char **symbol_names, FILE *f) {
  bool was_recording_allocations = ts_toggle_allocation_recording(false);
  if (!f)
    f = stderr;

  fprintf(f, "digraph stack {\n");
  fprintf(f, "rankdir=\"RL\";\n");
  fprintf(f, "edge [arrowhead=none]\n");

  Array(StackNode *)visited_nodes = array_new();

  array_clear(&self->pop_paths);
  for (size_t i = 0; i < self->heads.size; i++) {
    StackHead *head = &self->heads.contents[i];
    if (head->is_halted)
      continue;
    fprintf(f, "node_head_%lu [shape=none, label=\"\"]\n", i);
    fprintf(
      f, "node_head_%lu -> node_%p [label=%lu, fontcolor=blue, weight=10000, "
      "labeltooltip=\"push_count: %u\"]\n",
      i, head->node, i, head->push_count);
    if (!array_push(&self->pop_paths, ((PopPath){.node = head->node })))
      goto error;
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

      fprintf(f, "node_%p [", node);
      if (node->state == TS_STATE_ERROR)
        fprintf(f, "label=\"?\"");
      else if (node->link_count == 1 && node->links[0].tree &&
               node->links[0].tree->extra)
        fprintf(f, "shape=point margin=0 label=\"\"");
      else
        fprintf(f, "label=\"%d\"", node->state);

      fprintf(f,
              " tooltip=\"position: %lu,%lu\nerror_count: %u\nerror_cost: %u\n"
              "error_depth: %u\"];\n",
              node->position.rows, node->position.columns, node->error_count,
              node->error_cost, node->error_depth);

      for (int j = 0; j < node->link_count; j++) {
        StackLink link = node->links[j];
        fprintf(f, "node_%p -> node_%p [", node, link.node);
        if (link.is_pending)
          fprintf(f, "style=dashed ");
        if (link.tree && link.tree->extra)
          fprintf(f, "fontcolor=gray ");

        if (!link.tree) {
          fprintf(f, "color=red");
        } else if (link.tree->symbol == ts_builtin_sym_error) {
          fprintf(f, "label=\"ERROR\"");
        } else {
          fprintf(f, "label=\"");
          if (!link.tree->named)
            fprintf(f, "'");
          const char *name = symbol_names[link.tree->symbol];
          for (const char *c = name; *c; c++) {
            if (*c == '\"' || *c == '\\')
              fprintf(f, "\\");
            fprintf(f, "%c", *c);
          }
          if (!link.tree->named)
            fprintf(f, "'");
          fprintf(f, "\" labeltooltip=\"error_cost: %u\"",
                  link.tree->error_cost);
        }

        fprintf(f, "];\n");

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
  ts_toggle_allocation_recording(was_recording_allocations);
  return true;

error:
  ts_toggle_allocation_recording(was_recording_allocations);
  if (visited_nodes.contents)
    array_delete(&visited_nodes);
  return false;
}
