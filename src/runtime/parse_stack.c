#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/tree_vector.h"
#include "runtime/parse_stack.h"
#include "runtime/length.h"
#include <assert.h>

static const size_t INITIAL_HEAD_CAPACITY = 3;

struct ParseStack {
  ParseStackNode **heads;
  int head_count;
  int head_capacity;
};

/*
 *  Section: Lifecycle
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
  if (this->heads)
    free(this->heads);
  free(this);
}

/*
 *  Section: Reading
 */

ParseStackNode *ts_parse_stack_head(const ParseStack *this, int head_index) {
  assert(head_index < this->head_count);
  return this->heads[head_index];
}

int ts_parse_stack_head_count(const ParseStack *this) {
  return this->head_count;
}

/*
 *  Section: Updating
 */

static ParseStackNode *stack_node_new(ParseStackNode *, TSStateId, TSTree *);
static void stack_node_retain(ParseStackNode *);
static bool stack_node_release(ParseStackNode *);
static void stack_node_add_successor(ParseStackNode *, ParseStackNode *);
static void parse_stack_remove_head(ParseStack *, int);
static bool parse_stack_merge_head(ParseStack *, int, TSStateId, TSTree *);

bool ts_parse_stack_shift(ParseStack *this, int head_index, TSStateId state, TSTree *tree) {
  assert(head_index < this->head_count);
  if (parse_stack_merge_head(this, head_index, state, tree))
    return true;
  this->heads[head_index] = stack_node_new(this->heads[head_index], state, tree);
  return false;
}

#define MAX_PATH_COUNT 8

bool ts_parse_stack_reduce(ParseStack *this, int head_index, TSStateId state,
                           TSSymbol symbol, int child_count) {
  int path_count = 1;
  ParseStackNode *nodes_by_path[MAX_PATH_COUNT] = {this->heads[head_index]};
  TreeVector children_by_path[MAX_PATH_COUNT] = {tree_vector_new(child_count)};
  size_t child_counts_by_path[MAX_PATH_COUNT] = {child_count};

  /*
   *  Reduce along every possible path in parallel. Stop when the given number
   *  of child trees have been collected along every path.
   */
  bool all_paths_done = false;
  while (!all_paths_done) {
    all_paths_done = true;
    int current_path_count = path_count;
    for (int path = 0; path < current_path_count; path++) {
      if (children_by_path[path].size == child_counts_by_path[path])
        continue;
      else
        all_paths_done = false;

      /*
       *  Children that are 'extra' do not count towards the total child count.
       */
      ParseStackNode *node = nodes_by_path[path];
      if (ts_tree_is_extra(node->tree))
        child_counts_by_path[path]++;

      /*
       *  If a node has more than one successor, create new paths for each of
       *  the additional successors.
       */
      tree_vector_push(&children_by_path[path], node->tree);

      for (int i = 0; i < node->successor_count; i++) {
        int next_path;
        if (i > 0) {
          if (path_count == MAX_PATH_COUNT) break;
          next_path = path_count;
          child_counts_by_path[next_path] = child_counts_by_path[path];
          children_by_path[next_path] = tree_vector_copy(&children_by_path[path]);
          path_count++;
        } else {
          next_path = path;
        }

        nodes_by_path[next_path] = node->successors[i];
      }
    }
  }

  TSTree *parent;
  if (path_count > 1) {
    TSTree **trees_by_path = malloc(path_count * sizeof(TSTree *));
    for (int path = 0; path < path_count; path++) {
      stack_node_retain(nodes_by_path[path]);
      tree_vector_reverse(&children_by_path[path]);
      trees_by_path[path] = ts_tree_make_node(
        symbol,
        child_counts_by_path[path],
        children_by_path[path].contents,
        false
      );
      parent = ts_tree_make_ambiguity(path_count, trees_by_path);
    }
  } else {
    stack_node_retain(nodes_by_path[0]);
    tree_vector_reverse(&children_by_path[0]);
    parent = ts_tree_make_node(
      symbol,
      child_counts_by_path[0],
      children_by_path[0].contents,
      false
    );
  }

  stack_node_release(this->heads[head_index]);
  this->heads[head_index] = nodes_by_path[0];

  if (parse_stack_merge_head(this, head_index, state, parent))
    return true;

  this->heads[head_index] = stack_node_new(nodes_by_path[0], state, parent);
  for (int i = 1; i < path_count; i++) {
    stack_node_add_successor(this->heads[head_index], nodes_by_path[i]);
  }

  return false;
}

int ts_parse_stack_split(ParseStack *this, int head_index) {
  assert(head_index < this->head_count);
  if (this->head_count == this->head_capacity) {
    this->head_capacity += 3;
    this->heads = realloc(this->heads, this->head_capacity * sizeof(ParseStackNode *));
  }
  int new_index = this->head_count++;
  this->heads[new_index] = this->heads[head_index];
  stack_node_retain(this->heads[new_index]);
  return new_index;
}

/*
 *  Section: Private
 */

static ParseStackNode *stack_node_new(ParseStackNode *next, TSStateId state, TSTree *tree) {
  ParseStackNode *this = malloc(sizeof(ParseStackNode));
  *this = (ParseStackNode) {
    .ref_count = 1,
    .successor_count = 1,
    .successors = {next, NULL, NULL},
    .state = state,
    .tree = tree,
  };
  return this;
}

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
    ts_tree_release(this->tree);
    free(this);
    return true;
  } else {
    return false;
  }
}

static void stack_node_add_successor(ParseStackNode *this, ParseStackNode *successor) {
  stack_node_retain(successor);
  for (int i = 0; i < this->successor_count; i++)
    if (this->successors[i] == successor)
      return;
  this->successors[this->successor_count] = successor;
  this->successor_count++;
}

static bool parse_stack_merge_head(ParseStack *this, int head_index, TSStateId state, TSTree *tree) {
  for (int i =  0; i < head_index; i++) {
    ParseStackNode *head = this->heads[i];
    if (head->state == state) {
      if (head->tree == tree) {
        stack_node_add_successor(head, this->heads[head_index]);
        parse_stack_remove_head(this, head_index);
        return true;
      }

      if (head->tree->symbol == tree->symbol &&
          ts_length_eq(head->tree->size, tree->size)) {
        TSTree **options = malloc(2 * sizeof(TSTree *));
        options[0] = head->tree;
        options[1] = tree;
        head->tree = ts_tree_make_ambiguity(2, options);
        stack_node_add_successor(head, this->heads[head_index]);
        parse_stack_remove_head(this, head_index);
        return true;
      }
    }
  }
  return false;
}

static void parse_stack_remove_head(ParseStack *this, int head_index) {
  stack_node_release(this->heads[head_index]);
  for (int i = head_index; i < this->head_count - 1; i++) {
    this->heads[head_index] = this->heads[head_index + 1];
  }
  this->head_count--;
}
