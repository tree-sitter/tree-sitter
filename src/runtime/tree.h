#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "tree_sitter/parser.h"
#include "runtime/length.h"

#define TSTREE_LEX_STATE_INDEPENDENT (unsigned short)(-1)

struct TSTree {
  struct {
    struct TSTree *parent;
    size_t index;
    TSLength offset;
    TSStateId lex_state;
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
    bool visible : 1;
    bool named : 1;
    bool extra : 1;
    bool fragile_left : 1;
    bool fragile_right : 1;
    bool has_changes : 1;
  } options;
  unsigned short int ref_count;
};

TSTree *ts_tree_make_leaf(TSSymbol, TSLength, TSLength, TSSymbolMetadata);
TSTree *ts_tree_make_node(TSSymbol, size_t, TSTree **, TSSymbolMetadata);
TSTree *ts_tree_make_copy(TSTree *child);
TSTree *ts_tree_make_error(TSLength, TSLength, char);
void ts_tree_retain(TSTree *tree);
void ts_tree_release(TSTree *tree);
bool ts_tree_eq(const TSTree *tree1, const TSTree *tree2);
int ts_tree_compare(const TSTree *tree1, const TSTree *tree2);
char *ts_tree_string(const TSTree *tree, const char **names,
                     bool include_anonymous);

size_t ts_tree_start_column(const TSTree *self);
size_t ts_tree_end_column(const TSTree *self);
void ts_tree_set_children(TSTree *, size_t, TSTree **);
void ts_tree_assign_parents(TSTree *);
void ts_tree_edit(TSTree *, TSInputEdit);

static inline size_t ts_tree_total_chars(const TSTree *self) {
  return self->padding.chars + self->size.chars;
}

static inline TSLength ts_tree_total_size(const TSTree *self) {
  return ts_length_add(self->padding, self->size);
}

static inline TSPoint ts_tree_extent(const TSTree *tree) {
  TSPoint result;
  result.row = tree->size.rows;
  result.column = tree->size.columns;
  return result;
}

static inline bool ts_tree_is_extra(const TSTree *tree) {
  return tree->options.extra;
}

static inline bool ts_tree_is_visible(const TSTree *tree) {
  return tree->options.visible;
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

static inline void ts_tree_set_fragile(TSTree *tree) {
  ts_tree_set_fragile_left(tree);
  ts_tree_set_fragile_right(tree);
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
