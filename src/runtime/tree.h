#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "tree_sitter/parser.h"

typedef enum {
  TSTreeOptionsHidden = 1 << 0,
  TSTreeOptionsExtra = 1 << 1,
  TSTreeOptionsWrapper = 1 << 2,
  TSTreeOptionsFragileLeft = 1 << 3,
  TSTreeOptionsFragileRight = 1 << 4,
} TSTreeOptions;

struct TSTree {
  TSSymbol symbol;
  TSTreeOptions options;
  TSLength padding;
  TSLength size;
  size_t child_count;
  union {
    struct {
      struct TSTree **children;
      size_t visible_child_count;
    };
    char lookahead_char;
  };
  unsigned short int ref_count;
};

typedef struct {
  TSTree *tree;
  TSLength offset;
} TSTreeChild;

static inline bool ts_tree_is_extra(const TSTree *tree) {
  return !!(tree->options & TSTreeOptionsExtra);
}

static inline bool ts_tree_is_visible(const TSTree *tree) {
  return !(tree->options & TSTreeOptionsHidden);
}

static inline bool ts_tree_is_wrapper(const TSTree *tree) {
  return !!(tree->options & TSTreeOptionsWrapper);
}

static inline void ts_tree_set_options(TSTree *tree, TSTreeOptions options) {
  tree->options = (TSTreeOptions)(tree->options | options);
}

static inline void ts_tree_set_extra(TSTree *tree) {
  ts_tree_set_options(tree, TSTreeOptionsExtra);
}

static inline void ts_tree_set_fragile_left(TSTree *tree) {
  ts_tree_set_options(tree, TSTreeOptionsFragileLeft);
}

static inline void ts_tree_set_fragile_right(TSTree *tree) {
  ts_tree_set_options(tree, TSTreeOptionsFragileRight);
}

static inline bool ts_tree_is_fragile_left(TSTree *tree) {
  return tree->options & TSTreeOptionsFragileLeft;
}

static inline bool ts_tree_is_fragile_right(TSTree *tree) {
  return tree->options & TSTreeOptionsFragileRight;
}

TSTree *ts_tree_make_leaf(TSSymbol, TSLength, TSLength, bool);
TSTree *ts_tree_make_node(TSSymbol, size_t, TSTree **, bool);
TSTree *ts_tree_make_error(TSLength size, TSLength padding, char lookahead_char);
void ts_tree_retain(TSTree *tree);
void ts_tree_release(TSTree *tree);
bool ts_tree_eq(const TSTree *tree1, const TSTree *tree2);
char *ts_tree_string(const TSTree *tree, const char **names);
char *ts_tree_error_string(const TSTree *tree, const char **names);
TSTree **ts_tree_children(const TSTree *tree, size_t *count);
TSTreeChild *ts_tree_visible_children(const TSTree *tree, size_t *count);
TSLength ts_tree_total_size(const TSTree *tree);

static inline bool ts_tree_is_empty(TSTree *tree) {
  return ts_tree_total_size(tree).bytes == 0;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
