#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/tree_vector.h"
#include "runtime/parse_stack.h"
#include "runtime/length.h"
#include <assert.h>

#define MAX_POP_PATH_COUNT 8
#define INITIAL_HEAD_CAPACITY 3
#define STARTING_TREE_CAPACITY 10

typedef struct ParseStackNode {
  ParseStackEntry entry;
  struct ParseStackNode *successors[MAX_POP_PATH_COUNT];
  short unsigned int successor_count;
  short unsigned int ref_count;
} ParseStackNode;

struct ParseStack {
  ParseStackNode **heads;
  int head_count;
  int head_capacity;
  ParseStackPopResult last_pop_results[MAX_POP_PATH_COUNT];
};

/*
 *  Section: Stack lifecycle
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
  free(this->heads);
  free(this);
}

/*
 *  Section: Reading from the stack
 */

TSStateId ts_parse_stack_top_state(const ParseStack *this, int head) {
  ParseStackEntry *entry = ts_parse_stack_head((ParseStack *)this, head);
  return entry ? entry->state : 0;
}

TSTree *ts_parse_stack_top_tree(const ParseStack *this, int head) {
  ParseStackEntry *entry = ts_parse_stack_head((ParseStack *)this, head);
  return entry ? entry->tree : NULL;
}

ParseStackEntry *ts_parse_stack_head(ParseStack *this, int head) {
  assert(head < this->head_count);
  ParseStackNode *node = this->heads[head];
  return node ? &node->entry : NULL;
}

int ts_parse_stack_head_count(const ParseStack *this) {
  return this->head_count;
}

int ts_parse_stack_entry_next_count(const ParseStackEntry *entry) {
  return ((const ParseStackNode *)entry)->successor_count;
}

ParseStackEntry *ts_parse_stack_entry_next(const ParseStackEntry *entry, int i) {
  return &((const ParseStackNode *)entry)->successors[i]->entry;
}

/*
 *  Section: Manipulating nodes (Private)
 */

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
    ts_tree_release(this->entry.tree);
    free(this);
    return true;
  } else {
    return false;
  }
}

static ParseStackNode *stack_node_new(ParseStackNode *next, TSStateId state, TSTree *tree) {
  ParseStackNode *this = malloc(sizeof(ParseStackNode));
  ts_tree_retain(tree);
  stack_node_retain(next);
  *this = (ParseStackNode) {
    .ref_count = 1,
    .successor_count = 1,
    .successors = {next, NULL, NULL},
    .entry = {
      .state = state,
      .tree = tree,
    },
  };
  return this;
}

static void stack_node_add_successor(ParseStackNode *this, ParseStackNode *successor) {
  for (int i = 0; i < this->successor_count; i++)
    if (this->successors[i] == successor)
      return;
  stack_node_retain(successor);
  this->successors[this->successor_count] = successor;
  this->successor_count++;
}

/*
 *  Section: Mutating the stack (Private)
 */

static int ts_parse_stack_add_head(ParseStack *this, ParseStackNode *node) {
  if (this->head_count == this->head_capacity) {
    this->head_capacity += 3;
    this->heads = realloc(this->heads, this->head_capacity * sizeof(ParseStackNode *));
  }
  int new_index = this->head_count++;
  this->heads[new_index] = node;
  stack_node_retain(node);
  return new_index;
}

static int ts_parse_stack_find_or_add_head(ParseStack *this, ParseStackNode *node) {
  for (int i = 0; i < this->head_count; i++)
    if (this->heads[i] == node) {
      return i;
    }
  return ts_parse_stack_add_head(this, node);
}

void ts_parse_stack_remove_head(ParseStack *this, int head_index) {
  stack_node_release(this->heads[head_index]);
  for (int i = head_index; i < this->head_count - 1; i++) {
    this->heads[head_index] = this->heads[head_index + 1];
  }
  this->head_count--;
}

static bool ts_parse_stack_merge_head(ParseStack *this, int head_index, TSStateId state, TSTree *tree) {
  for (int i =  0; i < head_index; i++) {
    ParseStackNode *head = this->heads[i];
    if (head->entry.state == state) {
      if (head->entry.tree == tree) {
        stack_node_add_successor(head, this->heads[head_index]);
        ts_parse_stack_remove_head(this, head_index);
        return true;
      } else {
        head->entry.tree = ts_tree_add_alternative(head->entry.tree, tree);
        stack_node_add_successor(head, this->heads[head_index]);
        ts_parse_stack_remove_head(this, head_index);
        return true;
      }
    }
  }
  return false;
}

/*
 *  Section: Mutating the stack (Public)
 */

bool ts_parse_stack_push(ParseStack *this, int head_index, TSStateId state, TSTree *tree) {
  assert(head_index < this->head_count);
  if (ts_parse_stack_merge_head(this, head_index, state, tree))
    return true;
  this->heads[head_index] = stack_node_new(this->heads[head_index], state, tree);
  return false;
}

void ts_parse_stack_add_alternative(ParseStack *this, int head_index, TSTree *tree) {
  assert(head_index < this->head_count);
  ParseStackEntry *entry = &this->heads[head_index]->entry;
  entry->tree = ts_tree_add_alternative(entry->tree, tree);
}

int ts_parse_stack_split(ParseStack *this, int head_index) {
  assert(head_index < this->head_count);
  return ts_parse_stack_add_head(this, this->heads[head_index]);
}

ParseStackPopResultList ts_parse_stack_pop(ParseStack *this, int head_index, int child_count, bool count_extra) {
  ParseStackNode *previous_head = this->heads[head_index];

  int path_count = 1;
  int capacity = (child_count == -1) ? STARTING_TREE_CAPACITY : child_count;
  size_t tree_counts_by_path[MAX_POP_PATH_COUNT] = {child_count};
  ParseStackNode *nodes_by_path[MAX_POP_PATH_COUNT] = {previous_head};
  TreeVector trees_by_path[MAX_POP_PATH_COUNT] = {tree_vector_new(capacity)};
  bool is_shared_by_path[MAX_POP_PATH_COUNT] = {false};

  /*
   *  Reduce along every possible path in parallel. Stop when the given number
   *  of child trees have been collected along every path.
   */
  bool all_paths_done = false;
  while (!all_paths_done) {
    all_paths_done = true;
    int current_path_count = path_count;
    for (int path = 0; path < current_path_count; path++) {
      ParseStackNode *node = nodes_by_path[path];
      if (!node || (trees_by_path[path].size == tree_counts_by_path[path]))
        continue;
      all_paths_done = false;

      /*
       *  Children that are 'extra' do not count towards the total child count.
       */
      if (ts_tree_is_extra(node->entry.tree) && !count_extra)
        tree_counts_by_path[path]++;

      /*
       *  If a node has more than one successor, create new paths for each of
       *  the additional successors.
       */
      if (is_shared_by_path[path]) {
        trees_by_path[path] = tree_vector_copy(&trees_by_path[path]);
        is_shared_by_path[path] = false;
      }
      tree_vector_push(&trees_by_path[path], node->entry.tree);

      for (int i = 0; i < node->successor_count; i++) {
        int next_path;
        if (i > 0) {
          if (path_count == MAX_POP_PATH_COUNT) break;
          next_path = path_count;
          tree_counts_by_path[next_path] = tree_counts_by_path[path];
          trees_by_path[next_path] = trees_by_path[path];
          is_shared_by_path[next_path] = true;
          path_count++;
        } else {
          next_path = path;
        }

        nodes_by_path[next_path] = node->successors[i];
      }
    }
  }

  for (int path = 0; path < path_count; path++) {
    tree_vector_reverse(&trees_by_path[path]);
    int index = -1;
    if (path == 0) {
      stack_node_retain(nodes_by_path[path]);
      this->heads[head_index] = nodes_by_path[path];
      index = head_index;
    } else {
      index = ts_parse_stack_find_or_add_head(this, nodes_by_path[path]);
    }

    this->last_pop_results[path] = (ParseStackPopResult) {
      .index = index,
      .tree_count = trees_by_path[path].size,
      .trees = trees_by_path[path].contents,
    };
  }

  stack_node_release(previous_head);
  return (ParseStackPopResultList) {
    .size = path_count,
    .contents = this->last_pop_results,
  };
}

void ts_parse_stack_shrink(ParseStack *this, int head_index, int count) {
  ParseStackNode *head = this->heads[head_index];
  ParseStackNode *new_head = head;
  for (int i = 0; i < count; i++) {
    if (new_head->successor_count == 0) break;
    new_head = new_head->successors[0];
  }
  stack_node_retain(new_head);
  stack_node_release(head);
  this->heads[head_index] = new_head;
}

void ts_parse_stack_clear(ParseStack *this) {
  for (int i = 0; i < this->head_count; i++)
    stack_node_release(this->heads[i]);
  this->head_count = 1;
  this->heads[0] = NULL;
}
