#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/array.h"
#include "runtime/stack.h"
#include "runtime/length.h"
#include <assert.h>
#include <stdio.h>

#define MAX_LINK_COUNT 8
#define MAX_NODE_POOL_SIZE 50
#define MAX_ITERATOR_COUNT 64

#define INLINE static inline __attribute__((always_inline))

typedef struct StackNode StackNode;

typedef struct {
  StackNode *node;
  Tree *tree;
  unsigned push_count;
  bool is_pending;
} StackLink;

struct StackNode {
  TSStateId state;
  Length position;
  StackLink links[MAX_LINK_COUNT];
  short unsigned int link_count;
  short unsigned int ref_count;
  unsigned error_cost;
  unsigned error_count;
};

typedef struct {
  TreeArray trees;
  uint32_t tree_count;
  StackNode *node;
  bool is_pending;
  unsigned push_count;
} Iterator;

typedef struct {
  uint32_t goal_tree_count;
  bool found_error;
  bool found_valid_path;
} StackPopSession;

typedef Array(StackNode *) StackNodeArray;

typedef struct {
  StackNode *node;
  bool is_halted;
  unsigned push_count;
  const TSExternalTokenState *external_token_state;
} StackHead;

struct Stack {
  Array(StackHead) heads;
  StackSliceArray slices;
  Array(Iterator) iterators;
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

    if (pool->size < MAX_NODE_POOL_SIZE) {
      array_push(pool, self);
    } else {
      ts_free(self);
    }
  }
}

static StackNode *stack_node_new(StackNode *next, Tree *tree, bool is_pending,
                                 TSStateId state, Length position,
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
    node->links[0] = (StackLink){
      .node = next, .tree = tree, .is_pending = is_pending, .push_count = 0,
    };

    node->error_count = next->error_count;
    node->error_cost = next->error_cost;

    if (tree) {
      ts_tree_retain(tree);
      node->error_cost += tree->error_cost;

      if (state == ERROR_STATE) {
        if (!tree->extra) {
          node->error_cost += ERROR_COST_PER_SKIPPED_TREE +
                              ERROR_COST_PER_SKIPPED_CHAR *
                                (tree->padding.chars + tree->size.chars) +
                              ERROR_COST_PER_SKIPPED_LINE *
                                (tree->padding.extent.row + tree->size.extent.row);
        }
      }
    } else {
      node->error_count++;
    }
  } else {
    node->error_count = 0;
    node->error_cost = 0;
  }

  return node;
}

static void stack_node_add_link(StackNode *self, StackLink link) {
  for (int i = 0; i < self->link_count; i++) {
    StackLink existing_link = self->links[i];
    if (existing_link.tree == link.tree ||
        (existing_link.tree && link.tree &&
         ts_tree_tokens_eq(existing_link.tree, link.tree))) {
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
      .node = link.node,
      .tree = link.tree,
      .is_pending = link.is_pending,
      .push_count = link.push_count,
    };
  }
}

static StackVersion ts_stack__add_version(Stack *self, StackNode *node,
                                          unsigned push_count,
                                          const TSExternalTokenState *external_token_state) {
  StackHead head = {
    .node = node,
    .is_halted = false,
    .push_count = push_count,
    .external_token_state = external_token_state,
  };
  array_push(&self->heads, head);
  stack_node_retain(node);
  return (StackVersion)(self->heads.size - 1);
}

static void ts_stack__add_slice(Stack *self, StackNode *node, TreeArray *trees,
                                unsigned push_count,
                                const TSExternalTokenState *external_token_state) {
  for (uint32_t i = self->slices.size - 1; i + 1 > 0; i--) {
    StackVersion version = self->slices.contents[i].version;
    if (self->heads.contents[version].node == node) {
      StackSlice slice = { *trees, version };
      array_insert(&self->slices, i + 1, slice);
      return;
    }
  }

  StackVersion version = ts_stack__add_version(self, node, push_count, external_token_state);
  StackSlice slice = { *trees, version };
  array_push(&self->slices, slice);
}

INLINE StackPopResult stack__iter(Stack *self, StackVersion version,
                                  StackIterateCallback callback, void *payload) {
  array_clear(&self->slices);
  array_clear(&self->iterators);

  StackHead *head = array_get(&self->heads, version);
  unsigned push_count = head->push_count;
  const TSExternalTokenState *external_token_state = head->external_token_state;
  Iterator iterator = {
    .node = head->node,
    .trees = array_new(),
    .tree_count = 0,
    .is_pending = true,
    .push_count = 0,
  };
  array_push(&self->iterators, iterator);

  while (self->iterators.size > 0) {
    for (uint32_t i = 0, size = self->iterators.size; i < size; i++) {
      Iterator *iterator = &self->iterators.contents[i];
      StackNode *node = iterator->node;
      bool is_done = node == self->base_node;

      StackIterateAction action =
        callback(payload, node->state, &iterator->trees, iterator->tree_count,
                 is_done, iterator->is_pending);

      bool should_pop = action & StackIteratePop;
      bool should_stop = action & StackIterateStop || node->link_count == 0;

      if (should_pop) {
        TreeArray trees = iterator->trees;
        if (!should_stop)
          ts_tree_array_copy(trees, &trees);
        array_reverse(&trees);
        ts_stack__add_slice(self, node, &trees, push_count + iterator->push_count,
                            external_token_state);
      }

      if (should_stop) {
        if (!should_pop)
          ts_tree_array_delete(&iterator->trees);
        array_erase(&self->iterators, i);
        i--, size--;
        continue;
      }

      for (uint32_t j = 1; j <= node->link_count; j++) {
        Iterator *next_iterator;
        StackLink link;
        if (j == node->link_count) {
          link = node->links[0];
          next_iterator = &self->iterators.contents[i];
        } else {
          if (self->iterators.size >= MAX_ITERATOR_COUNT) continue;
          link = node->links[j];
          array_push(&self->iterators, self->iterators.contents[i]);
          next_iterator = array_back(&self->iterators);
          ts_tree_array_copy(next_iterator->trees, &next_iterator->trees);
        }

        next_iterator->node = link.node;
        next_iterator->push_count += link.push_count;
        if (link.tree) {
          if (!link.tree->extra) {
            next_iterator->tree_count++;
            if (!link.is_pending)
              next_iterator->is_pending = false;
          }
          array_push(&next_iterator->trees, link.tree);
          ts_tree_retain(link.tree);
        } else {
          next_iterator->is_pending = false;
        }
      }
    }
  }

  return (StackPopResult){ false, self->slices };
}

Stack *ts_stack_new() {
  Stack *self = ts_calloc(1, sizeof(Stack));

  array_init(&self->heads);
  array_init(&self->slices);
  array_init(&self->iterators);
  array_init(&self->node_pool);
  array_grow(&self->heads, 4);
  array_grow(&self->slices, 4);
  array_grow(&self->iterators, 4);
  array_grow(&self->node_pool, MAX_NODE_POOL_SIZE);

  self->base_node =
    stack_node_new(NULL, NULL, false, 1, length_zero(), &self->node_pool);
  stack_node_retain(self->base_node);
  array_push(&self->heads, ((StackHead){
    self->base_node,
    false,
    0,
    NULL
  }));

  return self;
}

void ts_stack_delete(Stack *self) {
  if (self->slices.contents)
    array_delete(&self->slices);
  if (self->iterators.contents)
    array_delete(&self->iterators);
  stack_node_release(self->base_node, &self->node_pool);
  for (uint32_t i = 0; i < self->heads.size; i++)
    stack_node_release(self->heads.contents[i].node, &self->node_pool);
  array_clear(&self->heads);
  if (self->node_pool.contents) {
    for (uint32_t i = 0; i < self->node_pool.size; i++)
      ts_free(self->node_pool.contents[i]);
    array_delete(&self->node_pool);
  }
  array_delete(&self->heads);
  ts_free(self);
}

uint32_t ts_stack_version_count(const Stack *self) {
  return self->heads.size;
}

TSStateId ts_stack_top_state(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->state;
}

Length ts_stack_top_position(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->position;
}

unsigned ts_stack_push_count(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->push_count;
}

void ts_stack_decrease_push_count(Stack *self, StackVersion version,
                                  unsigned decrement) {
  array_get(&self->heads, version)->push_count -= decrement;
}

const TSExternalTokenState *ts_stack_external_token_state(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->external_token_state;
}

void ts_stack_set_external_token_state(Stack *self, StackVersion version, const TSExternalTokenState *state) {
  array_get(&self->heads, version)->external_token_state = state;
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

bool ts_stack_push(Stack *self, StackVersion version, Tree *tree,
                   bool is_pending, TSStateId state) {
  StackHead *head = array_get(&self->heads, version);
  StackNode *node = head->node;
  Length position = node->position;
  if (tree)
    position = length_add(position, ts_tree_total_size(tree));
  StackNode *new_node =
    stack_node_new(node, tree, is_pending, state, position, &self->node_pool);
  if (!new_node)
    return false;
  stack_node_release(node, &self->node_pool);
  head->node = new_node;
  if (state == ERROR_STATE) {
    new_node->links[0].push_count = head->push_count;
    head->push_count = 0;
  } else
    head->push_count++;
  return true;
}

StackPopResult ts_stack_iterate(Stack *self, StackVersion version,
                                StackIterateCallback callback, void *payload) {
  return stack__iter(self, version, callback, payload);
}

INLINE StackIterateAction pop_count_callback(void *payload, TSStateId state,
                                             TreeArray *trees, uint32_t tree_count,
                                             bool is_done, bool is_pending) {
  StackPopSession *pop_session = (StackPopSession *)payload;

  if (tree_count == pop_session->goal_tree_count) {
    pop_session->found_valid_path = true;
    return StackIteratePop | StackIterateStop;
  }

  if (state == ERROR_STATE) {
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
                                  uint32_t count) {
  StackPopSession session = {
    .goal_tree_count = count, .found_error = false, .found_valid_path = false,
  };
  StackPopResult pop = stack__iter(self, version, pop_count_callback, &session);
  if (session.found_error) {
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
      pop.stopped_at_error = true;
    }
  }
  return pop;
}

INLINE StackIterateAction pop_pending_callback(void *payload, TSStateId state,
                                               TreeArray *trees,
                                               uint32_t tree_count, bool is_done,
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
                                           TreeArray *trees, uint32_t tree_count,
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
  assert((uint32_t)v1 < self->heads.size);
  stack_node_release(self->heads.contents[v2].node, &self->node_pool);
  self->heads.contents[v2] = self->heads.contents[v1];
  array_erase(&self->heads, v1);
}

StackVersion ts_stack_copy_version(Stack *self, StackVersion version) {
  assert(version < self->heads.size);
  array_push(&self->heads, self->heads.contents[version]);
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
      new_node->error_cost == node->error_cost &&
      ts_external_token_state_eq(new_head->external_token_state, head->external_token_state)) {
    for (uint32_t j = 0; j < new_node->link_count; j++)
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
  for (uint32_t i = 0; i < self->heads.size; i++)
    stack_node_release(self->heads.contents[i].node, &self->node_pool);
  array_clear(&self->heads);
  array_push(&self->heads, ((StackHead){
    self->base_node,
    false,
    0,
    NULL
  }));
}

bool ts_stack_print_dot_graph(Stack *self, const char **symbol_names, FILE *f) {
  bool was_recording_allocations = ts_toggle_allocation_recording(false);
  if (!f)
    f = stderr;

  fprintf(f, "digraph stack {\n");
  fprintf(f, "rankdir=\"RL\";\n");
  fprintf(f, "edge [arrowhead=none]\n");

  Array(StackNode *)visited_nodes = array_new();

  array_clear(&self->iterators);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    StackHead *head = &self->heads.contents[i];
    if (head->is_halted)
      continue;
    fprintf(f, "node_head_%u [shape=none, label=\"\"]\n", i);
    fprintf(
      f,
      "node_head_%u -> node_%p [label=%u, fontcolor=blue, weight=10000, "
      "labeltooltip=\"push_count: %u",
      i, head->node, i, head->push_count);

    if (head->external_token_state) {
      const TSExternalTokenState *s = head->external_token_state;
      fprintf(f,
        "\nexternal_token_state: "
        "%2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X",
        (*s)[0], (*s)[1], (*s)[2], (*s)[3], (*s)[4], (*s)[5], (*s)[6], (*s)[7],
        (*s)[8], (*s)[9], (*s)[10], (*s)[11], (*s)[12], (*s)[13], (*s)[14], (*s)[15]
      );
    }

    fprintf(f, "\"]\n");
    array_push(&self->iterators, ((Iterator){.node = head->node }));
  }

  bool all_iterators_done = false;
  while (!all_iterators_done) {
    all_iterators_done = true;

    for (uint32_t i = 0; i < self->iterators.size; i++) {
      Iterator *iterator = &self->iterators.contents[i];
      StackNode *node = iterator->node;

      for (uint32_t j = 0; j < visited_nodes.size; j++) {
        if (visited_nodes.contents[j] == node) {
          node = NULL;
          break;
        }
      }

      if (!node)
        continue;
      all_iterators_done = false;

      fprintf(f, "node_%p [", node);
      if (node->state == ERROR_STATE)
        fprintf(f, "label=\"?\"");
      else if (node->link_count == 1 && node->links[0].tree &&
               node->links[0].tree->extra)
        fprintf(f, "shape=point margin=0 label=\"\"");
      else
        fprintf(f, "label=\"%d\"", node->state);

      fprintf(f,
              " tooltip=\"position: %u,%u\nerror_count: %u\nerror_cost: %u\"];\n",
              node->position.extent.row, node->position.extent.column, node->error_count,
              node->error_cost);

      for (int j = 0; j < node->link_count; j++) {
        StackLink link = node->links[j];
        fprintf(f, "node_%p -> node_%p [", node, link.node);
        if (link.is_pending)
          fprintf(f, "style=dashed ");
        if (link.tree && link.tree->extra)
          fprintf(f, "fontcolor=gray ");

        if (!link.tree) {
          fprintf(f, "color=red, tooltip=\"push_count: %u\"", link.push_count);
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
          iterator->node = link.node;
        } else {
          array_push(&self->iterators, *iterator);
          Iterator *next_iterator = array_back(&self->iterators);
          next_iterator->node = link.node;
        }
      }

      array_push(&visited_nodes, node);
    }
  }

  fprintf(f, "}\n");

  array_delete(&visited_nodes);
  ts_toggle_allocation_recording(was_recording_allocations);
  return true;
}
