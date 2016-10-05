#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "tree_sitter/parser.h"
#include "tree_sitter/runtime.h"
#include "runtime/length.h"
#include "runtime/array.h"
#include <stdio.h>

extern TSStateId TS_TREE_STATE_NONE;

typedef struct TSTree {
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
    int32_t lookahead_char;
  };

  TSLength padding;
  TSLength size;

  TSSymbol symbol;
  TSStateId parse_state;
  unsigned error_cost;

  struct {
    TSSymbol symbol;
    TSStateId lex_state;
  } first_leaf;

  unsigned short ref_count;
  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool fragile_left : 1;
  bool fragile_right : 1;
  bool has_changes : 1;
} TSTree;

typedef Array(TSTree *) TreeArray;
bool ts_tree_array_copy(TreeArray, TreeArray *);
void ts_tree_array_delete(TreeArray *);
size_t ts_tree_array_essential_count(const TreeArray *);

TSTree *ts_tree_make_leaf(TSSymbol, TSLength, TSLength, TSSymbolMetadata);
TSTree *ts_tree_make_node(TSSymbol, size_t, TSTree **, TSSymbolMetadata);
TSTree *ts_tree_make_copy(TSTree *child);
TSTree *ts_tree_make_error_node(TreeArray *);
TSTree *ts_tree_make_error(TSLength, TSLength, char);
void ts_tree_retain(TSTree *tree);
void ts_tree_release(TSTree *tree);
bool ts_tree_eq(const TSTree *tree1, const TSTree *tree2);
int ts_tree_compare(const TSTree *tree1, const TSTree *tree2);

size_t ts_tree_start_column(const TSTree *self);
size_t ts_tree_end_column(const TSTree *self);
void ts_tree_set_children(TSTree *, size_t, TSTree **);
void ts_tree_assign_parents(TSTree *);
void ts_tree_edit(TSTree *, TSInputEdit);
char *ts_tree_string(const TSTree *, const TSLanguage *, bool include_all);
void ts_tree_print_dot_graph(const TSTree *, const TSLanguage *, FILE *);

static inline size_t ts_tree_total_chars(const TSTree *self) {
  return self->padding.chars + self->size.chars;
}

static inline TSLength ts_tree_total_size(const TSTree *self) {
  return ts_length_add(self->padding, self->size);
}

static inline bool ts_tree_is_fragile(const TSTree *tree) {
  return tree->fragile_left || tree->fragile_right ||
         ts_tree_total_chars(tree) == 0;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
