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

#ifdef _WIN32
#define inline __forceinline
#else
#define inline static inline __attribute__((always_inline))
#endif

typedef struct StackNode StackNode;

typedef struct {
  StackNode *node;
  Tree *tree;
  bool is_pending;
} StackLink;

struct StackNode {
  TSStateId state;
  Length position;
  StackLink links[MAX_LINK_COUNT];
  short unsigned int link_count;
  uint32_t ref_count;
  unsigned error_cost;
  unsigned depth;
};

typedef struct {
  StackNode *node;
  TreeArray trees;
  uint32_t tree_count;
  bool is_pending;
} Iterator;

typedef struct {
  void *payload;
  StackIterateCallback callback;
} StackIterateSession;

typedef Array(StackNode *) StackNodeArray;

typedef struct {
  StackNode *node;
  Tree *last_external_token;
  uint32_t push_count;
  bool is_halted;
  StackSummary *summary;
} StackHead;

struct Stack {
  Array(StackHead) heads;
  StackSliceArray slices;
  Array(Iterator) iterators;
  StackNodeArray node_pool;
  StackNode *base_node;
};

typedef StackIterateAction (*StackIterateInternalCallback)(void *, const Iterator *);

static void stack_node_retain(StackNode *self) {
  if (!self)
    return;
  assert(self->ref_count > 0);
  self->ref_count++;
  assert(self->ref_count != 0);
}

static void stack_node_release(StackNode *self, StackNodeArray *pool) {
recur:
  assert(self->ref_count != 0);
  self->ref_count--;
  if (self->ref_count > 0) return;

  StackNode *first_predecessor = NULL;
  if (self->link_count > 0) {
    for (unsigned i = self->link_count - 1; i > 0; i--) {
      if (self->links[i].tree) ts_tree_release(self->links[i].tree);
      stack_node_release(self->links[i].node, pool);
    }
    if (self->links[0].tree) ts_tree_release(self->links[0].tree);
    first_predecessor = self->links[0].node;
  }

  if (pool->size < MAX_NODE_POOL_SIZE) {
    array_push(pool, self);
  } else {
    ts_free(self);
  }

  if (first_predecessor) {
    self = first_predecessor;
    goto recur;
  }
}

static StackNode *stack_node_new(StackNode *previous_node, Tree *tree, bool is_pending,
                                 TSStateId state, StackNodeArray *pool) {
  StackNode *node = pool->size > 0 ?
    array_pop(pool) :
    ts_malloc(sizeof(StackNode));
  *node = (StackNode){.ref_count = 1, .link_count = 0, .state = state, .depth = 0};

  if (previous_node) {
    stack_node_retain(previous_node);

    node->link_count = 1;
    node->links[0] = (StackLink){
      .node = previous_node,
      .tree = tree,
      .is_pending = is_pending,
    };

    node->position = previous_node->position;
    node->error_cost = previous_node->error_cost;

    if (tree) {
      node->depth = previous_node->depth;
      if (!tree->extra) node->depth++;
      ts_tree_retain(tree);
      node->error_cost += tree->error_cost;
      node->position = length_add(node->position, ts_tree_total_size(tree));
      if (state == ERROR_STATE && !tree->extra) {
        node->error_cost +=
          ERROR_COST_PER_SKIPPED_TREE * ((tree->visible || tree->child_count == 0) ? 1 : tree->visible_child_count) +
          ERROR_COST_PER_SKIPPED_CHAR * tree->size.chars +
          ERROR_COST_PER_SKIPPED_LINE * tree->size.extent.row;
        if (previous_node->links[0].tree) {
          node->error_cost +=
            ERROR_COST_PER_SKIPPED_CHAR * tree->padding.chars +
            ERROR_COST_PER_SKIPPED_LINE * tree->padding.extent.row;
        }
      }
    }
  } else {
    node->position = length_zero();
    node->error_cost = 0;
  }

  return node;
}

static bool stack__tree_is_equivalent(const Tree *left, const Tree *right) {
  return left == right || (
    left &&
    right &&
    left->child_count == 0 && right->child_count == 0 &&
    left->symbol == right->symbol &&
    left->padding.bytes == right->padding.bytes &&
    left->size.bytes == right->size.bytes &&
    left->extra == right->extra &&
    ts_tree_external_token_state_eq(left, right));
}

static void stack_node_add_link(StackNode *self, StackLink link) {
  for (int i = 0; i < self->link_count; i++) {
    StackLink existing_link = self->links[i];
    if (stack__tree_is_equivalent(existing_link.tree, link.tree)) {
      if (existing_link.node == link.node) return;
      if (existing_link.node->state == link.node->state) {
        for (int j = 0; j < link.node->link_count; j++) {
          stack_node_add_link(existing_link.node, link.node->links[j]);
        }
        return;
      }
    }
  }

  if (self->link_count < MAX_LINK_COUNT) {
    stack_node_retain(link.node);
    if (link.tree) ts_tree_retain(link.tree);
    self->links[self->link_count++] = link;
  }
}

static void stack_head_delete(StackHead *self, StackNodeArray *pool) {
  if (self->node) {
    if (self->last_external_token) {
      ts_tree_release(self->last_external_token);
    }
    if (self->summary) {
      array_delete(self->summary);
      ts_free(self->summary);
    }
    stack_node_release(self->node, pool);
  }
}

static StackVersion ts_stack__add_version(Stack *self, StackVersion original_version,
                                          StackNode *node, Tree *last_external_token) {
  StackHead head = {
    .node = node,
    .push_count = self->heads.contents[original_version].push_count,
    .last_external_token = last_external_token,
    .is_halted = false,
  };
  array_push(&self->heads, head);
  stack_node_retain(node);
  if (last_external_token) ts_tree_retain(last_external_token);
  return (StackVersion)(self->heads.size - 1);
}

static void ts_stack__add_slice(Stack *self, StackVersion original_version, StackNode *node,
                                TreeArray *trees, Tree *last_external_token) {
  for (uint32_t i = self->slices.size - 1; i + 1 > 0; i--) {
    StackVersion version = self->slices.contents[i].version;
    if (self->heads.contents[version].node == node) {
      StackSlice slice = {*trees, version};
      array_insert(&self->slices, i + 1, slice);
      return;
    }
  }

  StackVersion version = ts_stack__add_version(self, original_version, node, last_external_token);
  StackSlice slice = { *trees, version };
  array_push(&self->slices, slice);
}

inline StackPopResult stack__iter(Stack *self, StackVersion version,
                                  StackIterateInternalCallback callback, void *payload,
                                  bool include_trees) {
  array_clear(&self->slices);
  array_clear(&self->iterators);

  StackHead *head = array_get(&self->heads, version);
  Tree *last_external_token = head->last_external_token;
  Iterator iterator = {
    .node = head->node,
    .trees = array_new(),
    .tree_count = 0,
    .is_pending = true,
  };
  array_push(&self->iterators, iterator);

  while (self->iterators.size > 0) {
    for (uint32_t i = 0, size = self->iterators.size; i < size; i++) {
      Iterator *iterator = &self->iterators.contents[i];
      StackNode *node = iterator->node;

      StackIterateAction action = callback(payload, iterator);
      bool should_pop = action & StackIteratePop;
      bool should_stop = action & StackIterateStop || node->link_count == 0;

      if (should_pop) {
        TreeArray trees = iterator->trees;
        if (!should_stop)
          ts_tree_array_copy(trees, &trees);
        ts_tree_array_reverse(&trees);
        ts_stack__add_slice(
          self,
          version,
          node,
          &trees,
          last_external_token
        );
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
          Iterator current_iterator = self->iterators.contents[i];
          array_push(&self->iterators, current_iterator);
          next_iterator = array_back(&self->iterators);
          ts_tree_array_copy(next_iterator->trees, &next_iterator->trees);
        }

        next_iterator->node = link.node;
        if (link.tree) {
          if (include_trees) {
            array_push(&next_iterator->trees, link.tree);
            ts_tree_retain(link.tree);
          }

          if (!link.tree->extra) {
            next_iterator->tree_count++;
            if (!link.is_pending) {
              next_iterator->is_pending = false;
            }
          }
        } else {
          next_iterator->tree_count++;
          next_iterator->is_pending = false;
        }
      }
    }
  }

  return (StackPopResult){self->slices};
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

  self->base_node = stack_node_new(NULL, NULL, false, 1, &self->node_pool);
  ts_stack_clear(self);

  return self;
}

void ts_stack_delete(Stack *self) {
  if (self->slices.contents)
    array_delete(&self->slices);
  if (self->iterators.contents)
    array_delete(&self->iterators);
  stack_node_release(self->base_node, &self->node_pool);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    stack_head_delete(&self->heads.contents[i], &self->node_pool);
  }
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

void ts_stack_decrease_push_count(Stack *self, StackVersion version, unsigned decrement) {
  array_get(&self->heads, version)->push_count -= decrement;
}

Tree *ts_stack_last_external_token(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->last_external_token;
}

void ts_stack_set_last_external_token(Stack *self, StackVersion version, Tree *token) {
  StackHead *head = array_get(&self->heads, version);
  if (token) ts_tree_retain(token);
  if (head->last_external_token) ts_tree_release(head->last_external_token);
  head->last_external_token = token;
}

ErrorStatus ts_stack_error_status(const Stack *self, StackVersion version) {
  StackHead *head = array_get(&self->heads, version);
  return (ErrorStatus){
    .cost = head->node->error_cost,
    .recovering = head->node->state == ERROR_STATE,
    .push_count = head->push_count,
  };
}

void ts_stack_push(Stack *self, StackVersion version, Tree *tree, bool pending, TSStateId state) {
  StackHead *head = array_get(&self->heads, version);
  StackNode *new_node = stack_node_new(head->node, tree, pending, state, &self->node_pool);
  if (state == ERROR_STATE) {
    head->push_count = 0;
  } else if (!tree->extra) {
    head->push_count++;
  }
  stack_node_release(head->node, &self->node_pool);
  head->node = new_node;
}

inline StackIterateAction iterate_callback(void *payload, const Iterator *iterator) {
  StackIterateSession *session = payload;
  return session->callback(session->payload, iterator->node->state, &iterator->trees, iterator->tree_count);
}

StackPopResult ts_stack_iterate(Stack *self, StackVersion version,
                                StackIterateCallback callback, void *payload) {
  StackIterateSession session = {payload, callback};
  return stack__iter(self, version, iterate_callback, &session, true);
}

inline StackIterateAction pop_count_callback(void *payload, const Iterator *iterator) {
  unsigned *goal_tree_count = payload;
  if (iterator->tree_count == *goal_tree_count) {
    return StackIteratePop | StackIterateStop;
  } else {
    return StackIterateNone;
  }
}

StackPopResult ts_stack_pop_count(Stack *self, StackVersion version, uint32_t count) {
  return stack__iter(self, version, pop_count_callback, &count, true);
}

inline StackIterateAction pop_pending_callback(void *payload, const Iterator *iterator) {
  if (iterator->tree_count >= 1) {
    if (iterator->is_pending) {
      return StackIteratePop | StackIterateStop;
    } else {
      return StackIterateStop;
    }
  } else {
    return StackIterateNone;
  }
}

StackPopResult ts_stack_pop_pending(Stack *self, StackVersion version) {
  StackPopResult pop = stack__iter(self, version, pop_pending_callback, NULL, true);
  if (pop.slices.size > 0) {
    ts_stack_renumber_version(self, pop.slices.contents[0].version, version);
    pop.slices.contents[0].version = version;
  }
  return pop;
}

inline StackIterateAction pop_error_callback(void *payload, const Iterator *iterator) {
  if (iterator->trees.size > 0) {
    bool *found_error = payload;
    if (!*found_error && iterator->trees.contents[0]->symbol == ts_builtin_sym_error) {
      *found_error = true;
      return StackIteratePop | StackIterateStop;
    } else {
      return StackIterateStop;
    }
  } else {
    return StackIterateNone;
  }
}

StackPopResult ts_stack_pop_error(Stack *self, StackVersion version) {
  StackNode *node = array_get(&self->heads, version)->node;
  for (unsigned i = 0; i < node->link_count; i++) {
    if (node->links[i].tree && node->links[i].tree->symbol == ts_builtin_sym_error) {
      bool found_error = false;
      return stack__iter(self, version, pop_error_callback, &found_error, true);
    }
  }
  return (StackPopResult){.slices = array_new()};
}

inline StackIterateAction pop_all_callback(void *payload, const Iterator *iterator) {
  return iterator->node->link_count == 0 ? StackIteratePop : StackIterateNone;
}

StackPopResult ts_stack_pop_all(Stack *self, StackVersion version) {
  return stack__iter(self, version, pop_all_callback, NULL, true);
}

typedef struct {
  StackSummary *summary;
  unsigned max_depth;
} SummarizeStackSession;

inline StackIterateAction summarize_stack_callback(void *payload, const Iterator *iterator) {
  SummarizeStackSession *session = payload;
  TSStateId state = iterator->node->state;
  unsigned depth = iterator->tree_count;
  if (depth > session->max_depth) return StackIterateStop;
  for (unsigned i = session->summary->size - 1; i + 1 > 0; i--) {
    StackSummaryEntry entry = session->summary->contents[i];
    if (entry.depth < depth) break;
    if (entry.depth == depth && entry.state == state) return StackIterateNone;
  }
  array_push(session->summary, ((StackSummaryEntry){.depth = depth, .state = state}));
  return StackIterateNone;
}

void ts_stack_record_summary(Stack *self, StackVersion version, unsigned max_depth) {
  SummarizeStackSession session = {
    .summary = ts_malloc(sizeof(StackSummary)),
    .max_depth = max_depth
  };
  array_init(session.summary);
  stack__iter(self, version, summarize_stack_callback, &session, false);
  self->heads.contents[version].summary = session.summary;
}

StackSummary *ts_stack_get_summary(Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->summary;
}

unsigned ts_stack_depth_since_error(Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->depth;
}

void ts_stack_remove_version(Stack *self, StackVersion version) {
  stack_head_delete(array_get(&self->heads, version), &self->node_pool);
  array_erase(&self->heads, version);
}

void ts_stack_renumber_version(Stack *self, StackVersion v1, StackVersion v2) {
  assert(v2 < v1);
  assert((uint32_t)v1 < self->heads.size);
  stack_head_delete(&self->heads.contents[v2], &self->node_pool);
  self->heads.contents[v2] = self->heads.contents[v1];
  array_erase(&self->heads, v1);
}

void ts_stack_swap_versions(Stack *self, StackVersion v1, StackVersion v2) {
  StackHead temporary_head = self->heads.contents[v1];
  self->heads.contents[v1] = self->heads.contents[v2];
  self->heads.contents[v2] = temporary_head;
}

StackVersion ts_stack_copy_version(Stack *self, StackVersion version) {
  assert(version < self->heads.size);
  array_push(&self->heads, self->heads.contents[version]);
  StackHead *head = array_back(&self->heads);
  stack_node_retain(head->node);
  if (head->last_external_token) ts_tree_retain(head->last_external_token);
  head->summary = NULL;
  return self->heads.size - 1;
}

bool ts_stack_merge(Stack *self, StackVersion version1, StackVersion version2) {
  if (ts_stack_can_merge(self, version1, version2)) {
    ts_stack_force_merge(self, version1, version2);
    return true;
  } else {
    return false;
  }
}

bool ts_stack_can_merge(Stack *self, StackVersion version1, StackVersion version2) {
  StackHead *head1 = &self->heads.contents[version1];
  StackHead *head2 = &self->heads.contents[version2];
  return
    !head1->is_halted && !head2->is_halted &&
    head1->node->state == head2->node->state &&
    head1->node->position.chars == head2->node->position.chars &&
    head1->node->depth == head2->node->depth &&
    ts_tree_external_token_state_eq(head1->last_external_token, head2->last_external_token);
}

void ts_stack_force_merge(Stack *self, StackVersion version1, StackVersion version2) {
  StackHead *head1 = &self->heads.contents[version1];
  StackHead *head2 = &self->heads.contents[version2];
  for (uint32_t i = 0; i < head2->node->link_count; i++) {
    stack_node_add_link(head1->node, head2->node->links[i]);
  }
  ts_stack_remove_version(self, version2);
}

void ts_stack_halt(Stack *self, StackVersion version) {
  array_get(&self->heads, version)->is_halted = true;
}

bool ts_stack_is_halted(Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->is_halted;
}

void ts_stack_clear(Stack *self) {
  stack_node_retain(self->base_node);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    stack_head_delete(&self->heads.contents[i], &self->node_pool);
  }
  array_clear(&self->heads);
  array_push(&self->heads, ((StackHead){
    .node = self->base_node,
    .last_external_token = NULL,
    .is_halted = false,
  }));
}

bool ts_stack_print_dot_graph(Stack *self, const char **symbol_names, FILE *f) {
  bool was_recording_allocations = ts_toggle_allocation_recording(false);
  if (!f)
    f = stderr;

  fprintf(f, "digraph stack {\n");
  fprintf(f, "rankdir=\"RL\";\n");
  fprintf(f, "edge [arrowhead=none]\n");

  Array(StackNode *) visited_nodes = array_new();

  array_clear(&self->iterators);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    if (ts_stack_is_halted(self, i)) continue;
    StackHead *head = &self->heads.contents[i];
    fprintf(f, "node_head_%u [shape=none, label=\"\"]\n", i);
    fprintf(
      f,
      "node_head_%u -> node_%p [label=%u, fontcolor=blue, weight=10000, "
      "labeltooltip=\"push_count: %u\ndepth: %u", i, head->node, i, head->push_count, head->node->depth
    );

    if (head->last_external_token) {
      TSExternalTokenState *state = &head->last_external_token->external_token_state;
      const char *data = ts_external_token_state_data(state);
      fprintf(f, "\nexternal_token_state:");
      for (uint32_t j = 0; j < state->length; j++) fprintf(f, " %2X", data[j]);
    }

    fprintf(f, "\"]\n");
    array_push(&self->iterators, ((Iterator){.node = head->node }));
  }

  bool all_iterators_done = false;
  while (!all_iterators_done) {
    all_iterators_done = true;

    for (uint32_t i = 0; i < self->iterators.size; i++) {
      Iterator iterator = self->iterators.contents[i];
      StackNode *node = iterator.node;

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

      fprintf(
        f,
        " tooltip=\"position: %u,%u\nerror_cost: %u\"];\n",
        node->position.extent.row, node->position.extent.column, node->error_cost
      );

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

        Iterator *next_iterator;
        if (j == 0) {
          next_iterator = &self->iterators.contents[i];
        } else {
          array_push(&self->iterators, iterator);
          next_iterator = array_back(&self->iterators);
        }
        next_iterator->node = link.node;
      }

      array_push(&visited_nodes, node);
    }
  }

  fprintf(f, "}\n");

  array_delete(&visited_nodes);
  ts_toggle_allocation_recording(was_recording_allocations);
  return true;
}
