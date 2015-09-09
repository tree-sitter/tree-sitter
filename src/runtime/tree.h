#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "tree_sitter/parser.h"

typedef struct {
  TSNodeType type : 4;
  bool extra : 1;
  bool fragile_left : 1;
  bool fragile_right : 1;
} TSTreeOptions;

struct TSTree {
  struct {
    struct TSTree *parent;
    size_t index;
    TSLength offset;
  } context;
  size_t child_count;
  size_t visible_child_count;
  size_t named_child_count;
  union {
    struct TSTree **children;
    char lookahead_char;
  };
  TSLength padding;
  TSLength size;
  TSSymbol symbol;
  TSTreeOptions options;
  unsigned short int ref_count;
};

typedef struct {
  TSTree *tree;
  TSLength offset;
} TSTreeChild;

static inline bool ts_tree_is_extra(const TSTree *tree) {
  return tree->options.extra;
}

static inline bool ts_tree_is_visible(const TSTree *tree) {
  return tree->options.type != TSNodeTypeHidden;
}

static inline void ts_tree_set_extra(TSTree *tree) {
  tree->options.extra = true;
}

static inline void ts_tree_set_fragile_left(TSTree *tree) {
  tree->options.fragile_left = true;
}

static inline void ts_tree_set_fragile_right(TSTree *tree) {
  tree->options.fragile_right = true;
}

static inline bool ts_tree_is_fragile_left(TSTree *tree) {
  return tree->options.fragile_left;
}

static inline bool ts_tree_is_fragile_right(TSTree *tree) {
  return tree->options.fragile_right;
}

TSTree *ts_tree_make_leaf(TSSymbol, TSLength, TSLength, TSNodeType);
TSTree *ts_tree_make_node(TSSymbol, size_t, TSTree **, TSNodeType);
TSTree *ts_tree_make_error(TSLength size, TSLength padding, char lookahead_char);
void ts_tree_retain(TSTree *tree);
void ts_tree_release(TSTree *tree);
bool ts_tree_eq(const TSTree *tree1, const TSTree *tree2);
char *ts_tree_string(const TSTree *tree, const char **names);
char *ts_tree_error_string(const TSTree *tree, const char **names);
TSLength ts_tree_total_size(const TSTree *tree);
void ts_tree_prepend_children(TSTree *, size_t, TSTree **);

static inline bool ts_tree_is_empty(TSTree *tree) {
  return ts_tree_total_size(tree).bytes == 0;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
