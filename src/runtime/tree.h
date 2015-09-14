#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "tree_sitter/parser.h"

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
  struct {
    TSNodeType type : 2;
    bool extra : 1;
    bool fragile_left : 1;
    bool fragile_right : 1;
    bool has_changes : 1;
  } options;
  unsigned short int ref_count;
};

TSTree *ts_tree_make_leaf(TSSymbol, TSLength, TSLength, TSNodeType);
TSTree *ts_tree_make_node(TSSymbol, size_t, TSTree **, TSNodeType);
TSTree *ts_tree_make_error(TSLength size, TSLength padding, char lookahead_char);
void ts_tree_retain(TSTree *tree);
void ts_tree_release(TSTree *tree);
bool ts_tree_eq(const TSTree *tree1, const TSTree *tree2);
char *ts_tree_string(const TSTree *tree, const char **names);
TSLength ts_tree_total_size(const TSTree *tree);
void ts_tree_prepend_children(TSTree *, size_t, TSTree **);
void ts_tree_edit(TSTree *, TSInputEdit);

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

static inline bool ts_tree_is_fragile_left(const TSTree *tree) {
  return tree->options.fragile_left;
}

static inline bool ts_tree_is_fragile_right(const TSTree *tree) {
  return tree->options.fragile_right;
}

static inline bool ts_tree_is_terminal(const TSTree *tree) {
  return tree->child_count == 0;
}

static inline bool ts_tree_has_changes(const TSTree *tree) {
  return tree->options.has_changes;
}

static inline bool ts_tree_is_empty(const TSTree *tree) {
  return ts_tree_total_size(tree).chars == 0;
}

static inline bool ts_tree_is_fragile(const TSTree *tree) {
  return ts_tree_is_empty(tree) || tree->options.fragile_left ||
         tree->options.fragile_right;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
