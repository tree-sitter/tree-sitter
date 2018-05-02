#include "runtime/alloc.h"
#include "runtime/language.h"
#include "runtime/error_costs.h"
#include "runtime/syntax_tree.h"
#include "runtime/array.h"
#include "runtime/stack2.h"
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
  NodeList node_list;
  bool is_pending;
} StackLink;

struct StackNode {
  StackLink links[MAX_LINK_COUNT];
  uint16_t link_count;
  TSStateId state;
  Length position;
  uint32_t ref_count;
  uint32_t error_cost;
  uint32_t node_count;
  uint32_t visible_root_count;
  uint32_t named_root_count;
  int32_t dynamic_precedence;
};

typedef Array(LeafNodeParams) ExtraTokenArray;
typedef Array(ExtraTokenArray) ExtraTokensPool;

typedef struct {
  StackNode *node;
  Array(NodeList) node_lists;
  uint32_t depth;
  bool is_pending;
} Iterator;

typedef struct {
  void *payload;
  StackIterateCallback callback;
} StackIterateSession;

typedef Array(StackNode *) StackNodePool;

typedef enum {
  StackStatusActive,
  StackStatusPaused,
  StackStatusHalted,
} StackStatus;

typedef struct {
  StackNode *node;
  StackSummary *summary;
  NodeList node_list;
  ExtraTokenArray trailing_extras;
  unsigned node_count_at_last_error;
  TSSymbol lookahead_when_paused;
  StackStatus status;
} StackHead;

struct Stack {
  Array(StackHead) heads;
  Array(Iterator) iterators;
  ExtraTokensPool extra_token_array_pool;
  StackNodePool node_pool;
  StackNode *base_node;
};

typedef unsigned StackAction;
enum {
  StackActionNone,
  StackActionStop = 1,
  StackActionPop = 2,
};

typedef StackAction (*StackCallback)(void *, const Iterator *);

// StackNode

static void stack_node_retain(StackNode *self) {
  if (!self) return;
  assert(self->ref_count > 0);
  self->ref_count++;
  assert(self->ref_count != 0);
}

static void stack_node_release(StackNode *self, StackNodePool *pool) {
recur:
  assert(self->ref_count != 0);
  self->ref_count--;
  if (self->ref_count > 0) return;

  StackNode *first_predecessor = NULL;
  if (self->link_count > 0) {
    for (unsigned i = self->link_count - 1; i > 0; i--) {
      ts_node_list_delete(&self->links[i].node_list);
      stack_node_release(self->links[i].node, pool);
    }
    ts_node_list_delete(&self->links[0].node_list);
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

static StackNode *stack_node_new(StackNodePool *pool, StackNode *previous_node,
                                 bool is_pending, Length size, TSStateId state) {
  StackNode *node = pool->size > 0 ?
    array_pop(pool) :
    ts_malloc(sizeof(StackNode));
  *node = (StackNode){
    .ref_count = 1,
    .link_count = 0,
    .state = state
  };

  if (previous_node) {
    node->link_count = 1;
    node->links[0] = (StackLink){
      .node = previous_node,
      .is_pending = is_pending,
    };

    node->position = length_add(previous_node->position, size);
    node->error_cost = previous_node->error_cost;
    node->dynamic_precedence = previous_node->dynamic_precedence;
    node->node_count = previous_node->node_count;
  } else {
    node->position = length_zero();
    node->error_cost = 0;
  }

  return node;
}

static void stack_node_add_link(StackNode *self, StackLink link) {
  if (link.node == self) return;

  if (self->link_count == MAX_LINK_COUNT) return;

  stack_node_retain(link.node);
  self->links[self->link_count++] = link;
}

// StackHead

static void stack_head_delete(StackHead *self, StackNodePool *pool,
                              ExtraTokensPool *extra_tokens_pool) {
  if (self->node) {
    stack_node_release(self->node, pool);
  }
  if (self->node_list.last) {
    ts_node_list_delete(&self->node_list);
  }
  if (self->trailing_extras.contents) {
    array_push(extra_tokens_pool, self->trailing_extras);
  }
}

static void stack_head_flush_trailing_extras(StackHead *self, StackNodePool *node_pool) {
  if (self->trailing_extras.size > 0) {
    Length size = length_zero();
    for (unsigned i = 0; i < self->trailing_extras.size; i++) {
      LeafNodeParams *token = &self->trailing_extras.contents[i];
      size = length_add(size, token->padding);
      size = length_add(size, token->size);
      ts_node_list_push_leaf(&self->node_list, *token);
    }
    array_clear(&self->trailing_extras);
    self->node = stack_node_new(node_pool, self->node, false, size, self->node->state);
  }
}

// Stack - Lifecycle

Stack *ts_stack2_new(TreePool *tree_pool) {
  Stack *self = ts_calloc(1, sizeof(Stack));

  array_init(&self->heads);
  array_init(&self->iterators);
  array_init(&self->node_pool);
  array_reserve(&self->heads, 4);
  array_reserve(&self->iterators, 4);
  array_reserve(&self->node_pool, MAX_NODE_POOL_SIZE);

  self->base_node = stack_node_new(&self->node_pool, NULL, false, length_zero(), 1);
  ts_stack2_clear(self);

  return self;
}

void ts_stack2_delete(Stack *self) {
  if (self->iterators.contents) {
    array_delete(&self->iterators);
  }

  stack_node_release(self->base_node, &self->node_pool);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    stack_head_delete(&self->heads.contents[i], &self->node_pool, &self->extra_token_array_pool);
  }

  if (self->node_pool.contents) {
    for (uint32_t i = 0; i < self->node_pool.size; i++) {
      ts_free(self->node_pool.contents[i]);
    }
    array_delete(&self->node_pool);
  }

  if (self->extra_token_array_pool.contents) {
    for (uint32_t i = 0; i < self->extra_token_array_pool.size; i++) {
      array_delete(&self->extra_token_array_pool.contents[i]);
    }
    array_delete(&self->extra_token_array_pool);
  }

  array_delete(&self->heads);
  ts_free(self);
}

// Stack - Mutations

void ts_stack2_push_leaf(Stack *self, StackVersion version, TSStateId state,
                         LeafNodeParams params) {
  StackHead *head = array_get(&self->heads, version);
  if (params.extra) {
    array_push(&head->trailing_extras, params);
  } else {
    stack_head_flush_trailing_extras(head, &self->node_pool);
    ts_node_list_push_leaf(&head->node_list, params);
    Length size = length_add(params.padding, params.size);
    head->node = stack_node_new(&self->node_pool, head->node, false, size, state);
  }
}

void ts_stack2_push_existing(Stack *self, StackVersion version, TSStateId state,
                             TreeCursor *cursor) {
  StackHead *head = array_get(&self->heads, version);
  stack_head_flush_trailing_extras(head, &self->node_pool);
  Length previous_position = ts_tree_cursor_position(cursor);
  ts_node_list_reuse(&head->node_list, cursor);
  Length size = length_sub(ts_tree_cursor_position(cursor), previous_position);
  head->node = stack_node_new(&self->node_pool, head->node, false, size, state);
}

inline void ts_stack2__add_popped_version(Stack *self, StackVersion original_version,
                                          unsigned previous_version_count, Iterator *iterator) {
  for (unsigned i = previous_version_count; i < self->heads.size; i++) {
    if (self->heads.contents[i].node == iterator->node) {
      // TODO compare node lists and keep only the one with the lowest error
      // cost or highest dynamic precedence.
      for (unsigned j = 0; j < iterator->node_lists.size; j++) {
        ts_node_list_delete(&iterator->node_lists.contents[j]);
      }
      return;
    }
  }

  StackHead *original_head = &self->heads.contents[original_version];
  array_push(&self->heads, ((StackHead) {
    .node = iterator->node,
    .node_count_at_last_error = original_head->node_count_at_last_error,
    .status = StackStatusActive,
    .lookahead_when_paused = 0,
  }));
  stack_node_retain(iterator->node);
}

inline bool stack__iter(Stack *self, StackVersion version, StackCallback callback, void *payload) {
  unsigned previous_version_count = self->heads.size;
  StackHead *head = array_get(&self->heads, version);
  array_clear(&self->iterators);
  array_push(&self->iterators, ((Iterator) {
    .node = head->node,
    .node_lists = array_new(),
    .depth = 0,
    .is_pending = true,
  }));

  // Walk every possible path down the given version of the stack.
  while (self->iterators.size > 0) {
    for (uint32_t i = 0, size = self->iterators.size; i < size; i++) {
      Iterator *iterator = &self->iterators.contents[i];
      StackNode *node = iterator->node;

      // Call the callback to decide whether to stop and whether to add a
      // new version pointing at the current node.
      StackAction action = callback(payload, iterator);
      bool should_pop = action & StackActionPop;
      bool should_stop = action & StackActionStop || node->link_count == 0;

      if (should_pop) {
        ts_stack2__add_popped_version(self, version, previous_version_count, iterator);
      }

      if (should_stop) {
        if (!should_pop) {
          for (unsigned j = 0; j < iterator->node_lists.size; j++) {
            ts_node_list_delete(&iterator->node_lists.contents[j]);
          }
        }

        if (iterator->node_lists.contents) array_delete(&iterator->node_lists);
        array_erase(&self->iterators, i);
        i--, size--;
        continue;
      }

      // Follow each of the current node's links.
      for (uint32_t j = 1; j <= node->link_count; j++) {
        Iterator *current_iterator = &self->iterators.contents[i];

        // Update the current iterator based on the first link. Add new iterators
        // for the remaining links.
        StackLink *link;
        Iterator *next_iterator;
        if (j == node->link_count) {
          link = &node->links[0];
          next_iterator = current_iterator;
        } else {
          if (self->iterators.size >= MAX_ITERATOR_COUNT) continue;
          link = &node->links[j];
          array_push(&self->iterators, *current_iterator);
          next_iterator = array_back(&self->iterators);
          array_copy(&next_iterator->node_lists);
        }

        if (link->node->state != next_iterator->node->state) {
          next_iterator->depth++;
        }
        next_iterator->node = link->node;
        if (link->node_list.last) {
          array_push(&next_iterator->node_lists, ts_node_list_copy(&link->node_list));
        }
        if (!link->is_pending) {
          next_iterator->is_pending = false;
        }
      }
    }
  }

  // If any new versions were created, overwrite the current version with
  // the first newly-created version.
  if (self->heads.size > previous_version_count) {
    StackHead *head = &self->heads.contents[version];
    ExtraTokenArray trailing_extras = head->trailing_extras;
    NodeList node_list = head->node_list;
    ts_stack2_renumber_version(self, previous_version_count, version);

    for (unsigned i = previous_version_count; i < self->heads.size; i++) {
      StackHead *head = &self->heads.contents[i];
      head->node_list = ts_node_list_copy(&node_list);
      if (trailing_extras.size > 0) {
        head->trailing_extras = self->extra_token_array_pool.size > 0
          ? array_pop(&self->extra_token_array_pool)
          : (ExtraTokenArray) array_new();
        array_assign(&head->trailing_extras, &trailing_extras);
      }
    }

    return true;
  }

  return false;
}

inline StackAction reduce_callback(void *payload, const Iterator *iterator) {
  unsigned *goal_depth = payload;
  if (iterator->depth == *goal_depth) {
    return StackActionPop | StackActionStop;
  } else {
    return StackActionNone;
  }
}

void ts_stack2_reduce(Stack *self, StackVersion version,
                      InternalNodeParams params, StateArray *states) {
  array_clear(states);
  unsigned previous_version_count = self->heads.size;
  Length old_position = self->heads.contents[version].node->position;
  if (stack__iter(self, version, reduce_callback, &params.child_count)) {
    for (unsigned i = previous_version_count; i <= self->heads.size; i++) {
      StackHead *head = i == self->heads.size
        ? &self->heads.contents[version]
        : &self->heads.contents[i];
      TSStateId state = head->node->state;
      Length position = head->node->position;
      Length size = length_sub(old_position, position);
      head->node = stack_node_new(&self->node_pool, head->node, false, size, state);
      array_push(states, &head->node->state);
    }
  }
}

inline StackAction pop_pending_callback(void *payload, const Iterator *iterator) {
  if (iterator->depth >= 1) {
    if (iterator->is_pending) {
      return StackActionPop | StackActionStop;
    } else {
      return StackActionStop;
    }
  } else {
    return StackActionNone;
  }
}

void ts_stack2_pop_pending(Stack *self, StackVersion version) {
}

// Stack - Queries

typedef struct {
  StackSummary *summary;
  unsigned max_depth;
} SummarizeStackSession;

inline StackAction summarize_stack_callback(void *payload, const Iterator *iterator) {
  SummarizeStackSession *session = payload;
  TSStateId state = iterator->node->state;
  if (iterator->depth > session->max_depth) return StackActionStop;
  for (unsigned i = session->summary->size - 1; i + 1 > 0; i--) {
    StackSummaryEntry entry = session->summary->contents[i];
    if (entry.depth < iterator->depth) break;
    if (entry.depth == iterator->depth && entry.state == state) return StackActionNone;
  }
  array_push(session->summary, ((StackSummaryEntry){
    .position = iterator->node->position,
    .depth = iterator->depth,
    .state = state,
  }));
  return StackActionNone;
}

void ts_stack2_record_summary(Stack *self, StackVersion version, unsigned max_depth) {
  SummarizeStackSession session = {
    .summary = ts_malloc(sizeof(StackSummary)),
    .max_depth = max_depth
  };
  array_init(session.summary);
  stack__iter(self, version, summarize_stack_callback, &session);
  self->heads.contents[version].summary = session.summary;
}

StackSummary *ts_stack2_get_summary(Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->summary;
}

uint32_t ts_stack2_version_count(const Stack *self) {
  return self->heads.size;
}

TSStateId ts_stack2_state(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->state;
}

Length ts_stack2_position(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->position;
}

uint32_t ts_stack2_node_count_since_error(const Stack *self, StackVersion version) {
  StackHead *head = array_get(&self->heads, version);
  if (head->node->node_count < head->node_count_at_last_error) {
    head->node_count_at_last_error = head->node->node_count;
  }
  return head->node->node_count - head->node_count_at_last_error;
}

int32_t ts_stack2_dynamic_precedence(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->dynamic_precedence;
}

uint32_t ts_stack2_error_cost(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->node->error_cost;
}

// Stack - Version management

void ts_stack2_clear(Stack *self) {
  stack_node_retain(self->base_node);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    stack_head_delete(&self->heads.contents[i], &self->node_pool, &self->extra_token_array_pool);
  }
  array_clear(&self->heads);
  array_push(&self->heads, ((StackHead){
    .node = self->base_node,
    .status = StackStatusActive,
    .trailing_extras = array_new(),
    .lookahead_when_paused = 0,
  }));
}

void ts_stack2_remove_version(Stack *self, StackVersion version) {
  stack_head_delete(array_get(&self->heads, version), &self->node_pool, &self->extra_token_array_pool);
  array_erase(&self->heads, version);
}

void ts_stack2_renumber_version(Stack *self, StackVersion v1, StackVersion v2) {
  assert(v2 < v1);
  assert((uint32_t)v1 < self->heads.size);
  StackHead *source_head = &self->heads.contents[v1];
  StackHead *target_head = &self->heads.contents[v2];
  if (target_head->summary && !source_head->summary) {
    source_head->summary = target_head->summary;
    target_head->summary = NULL;
  }
  stack_head_delete(target_head, &self->node_pool, &self->extra_token_array_pool);
  *target_head = *source_head;
  array_erase(&self->heads, v1);
}

void ts_stack2_swap_versions(Stack *self, StackVersion v1, StackVersion v2) {
  StackHead temporary_head = self->heads.contents[v1];
  self->heads.contents[v1] = self->heads.contents[v2];
  self->heads.contents[v2] = temporary_head;
}

StackVersion ts_stack2_copy_version(Stack *self, StackVersion version) {
  assert(version < self->heads.size);
  array_push(&self->heads, self->heads.contents[version]);
  StackHead *head = array_back(&self->heads);
  stack_node_retain(head->node);
  head->summary = NULL;
  return self->heads.size - 1;
}

bool ts_stack2_merge(Stack *self, StackVersion version1, StackVersion version2) {
  if (!ts_stack2_can_merge(self, version1, version2)) return false;
  StackHead *head1 = &self->heads.contents[version1];
  StackHead *head2 = &self->heads.contents[version2];
  for (uint32_t i = 0; i < head2->node->link_count; i++) {
    stack_node_add_link(head1->node, head2->node->links[i]);
  }
  if (head1->node->state == ERROR_STATE) {
    head1->node_count_at_last_error = head1->node->node_count;
  }
  ts_stack2_remove_version(self, version2);
  return true;
}

bool ts_stack2_can_merge(Stack *self, StackVersion version1, StackVersion version2) {
  StackHead *head1 = &self->heads.contents[version1];
  StackHead *head2 = &self->heads.contents[version2];
  return
    head1->status == StackStatusActive &&
    head2->status == StackStatusActive &&
    head1->node->state == head2->node->state &&
    head1->node->position.bytes == head2->node->position.bytes &&
    head1->node->error_cost == head2->node->error_cost;
}

void ts_stack2_halt(Stack *self, StackVersion version) {
  array_get(&self->heads, version)->status = StackStatusHalted;
}

void ts_stack2_pause(Stack *self, StackVersion version, TSSymbol lookahead) {
  StackHead *head = array_get(&self->heads, version);
  head->status = StackStatusPaused;
  head->lookahead_when_paused = lookahead;
  head->node_count_at_last_error = head->node->node_count;
}

bool ts_stack2_is_active(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->status == StackStatusActive;
}

bool ts_stack2_is_halted(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->status == StackStatusHalted;
}

bool ts_stack2_is_paused(const Stack *self, StackVersion version) {
  return array_get(&self->heads, version)->status == StackStatusPaused;
}

TSSymbol ts_stack2_resume(Stack *self, StackVersion version) {
  StackHead *head = array_get(&self->heads, version);
  assert(head->status == StackStatusPaused);
  TSSymbol result = head->lookahead_when_paused;
  head->status = StackStatusActive;
  head->lookahead_when_paused = 0;
  return result;
}

// Stack - Debugging

inline StackAction iterate_callback(void *payload, const Iterator *iterator) {
  StackIterateSession *session = payload;
  session->callback(
    session->payload,
    iterator->node->state,
    iterator->depth
  );
  return StackActionNone;
}

void ts_stack2_iterate(Stack *self, StackVersion version,
                       StackIterateCallback callback, void *payload) {
  StackIterateSession session = {payload, callback};
  stack__iter(self, version, iterate_callback, &session);
}

bool ts_stack2_print_dot_graph(Stack *self, const TSLanguage *language, FILE *f) {
  bool was_recording_allocations = ts_toggle_allocation_recording(false);
  if (!f)
    f = stderr;

  fprintf(f, "digraph stack {\n");
  fprintf(f, "rankdir=\"RL\";\n");
  fprintf(f, "edge [arrowhead=none]\n");

  Array(StackNode *) visited_nodes = array_new();

  array_clear(&self->iterators);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    StackHead *head = &self->heads.contents[i];
    if (head->status == StackStatusHalted) continue;

    fprintf(f, "node_head_%u [shape=none, label=\"\"]\n", i);
    fprintf(f, "node_head_%u -> node_%p [", i, head->node);

    if (head->status == StackStatusPaused) {
      fprintf(f, "color=red ");
    }
    fprintf(f,
      "label=%u, fontcolor=blue, weight=10000, labeltooltip=\"node_count: %u\nerror_cost: %u",
      i,
      ts_stack2_node_count_since_error(self, i),
      ts_stack2_error_cost(self, i)
    );

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

      if (!node) continue;
      all_iterators_done = false;

      fprintf(f, "node_%p [", node);
      if (node->state == ERROR_STATE) {
        fprintf(f, "label=\"?\"");
      } else if (node->link_count == 1 && node->state == node->links[0].node->state) {
        fprintf(f, "shape=point margin=0 label=\"\"");
      } else {
        fprintf(f, "label=\"%d\"", node->state);
      }

      fprintf(
        f,
        " tooltip=\"position: %u,%u\nnode_count:%u\nerror_cost: %u\ndynamic_precedence: %d\"];\n",
        node->position.extent.row,
        node->position.extent.column,
        node->node_count,
        node->error_cost,
        node->dynamic_precedence
      );

      for (int j = 0; j < node->link_count; j++) {
        StackLink *link = &node->links[j];
        fprintf(f, "node_%p -> node_%p [", node, link->node);
        if (link->is_pending) fprintf(f, "style=dashed ");
        if (link->node->state == node->state) fprintf(f, "fontcolor=gray ");
        fprintf(f, "];\n");

        Iterator *next_iterator;
        if (j == 0) {
          next_iterator = &self->iterators.contents[i];
        } else {
          array_push(&self->iterators, iterator);
          next_iterator = array_back(&self->iterators);
        }
        next_iterator->node = link->node;
      }

      array_push(&visited_nodes, node);
    }
  }

  fprintf(f, "}\n");

  array_delete(&visited_nodes);
  ts_toggle_allocation_recording(was_recording_allocations);
  return true;
}
