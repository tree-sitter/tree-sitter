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

typedef struct Tree {
  struct {
    struct Tree *parent;
    uint32_t index;
    Length offset;
  } context;

  uint32_t child_count;
  union {
    struct {
      uint32_t visible_child_count;
      uint32_t named_child_count;
      struct Tree **children;
    };
    TSExternalTokenState external_token_state;
    int32_t lookahead_char;
  };

  Length padding;
  Length size;
  uint32_t bytes_scanned;

  TSSymbol symbol;
  TSStateId parse_state;
  unsigned error_cost;

  struct {
    TSSymbol symbol;
    TSLexMode lex_mode;
  } first_leaf;

  unsigned short ref_count;
  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool fragile_left : 1;
  bool fragile_right : 1;
  bool has_changes : 1;
  bool has_external_tokens : 1;
  bool has_external_token_state : 1;
} Tree;

typedef struct {
  Tree *tree;
  Length position;
  uint32_t child_index;
} TreePathEntry;

typedef Array(Tree *) TreeArray;

typedef Array(TreePathEntry) TreePath;

bool ts_tree_array_copy(TreeArray, TreeArray *);
void ts_tree_array_delete(TreeArray *);
uint32_t ts_tree_array_essential_count(const TreeArray *);
TreeArray ts_tree_array_remove_last_n(TreeArray *, uint32_t);
TreeArray ts_tree_array_remove_trailing_extras(TreeArray *);

Tree *ts_tree_make_leaf(TSSymbol, Length, Length, TSSymbolMetadata);
Tree *ts_tree_make_node(TSSymbol, uint32_t, Tree **, TSSymbolMetadata);
Tree *ts_tree_make_copy(Tree *child);
Tree *ts_tree_make_error_node(TreeArray *);
Tree *ts_tree_make_error(Length, Length, int32_t);
void ts_tree_retain(Tree *tree);
void ts_tree_release(Tree *tree);
bool ts_tree_eq(const Tree *tree1, const Tree *tree2);
bool ts_tree_tokens_eq(const Tree *, const Tree *);
int ts_tree_compare(const Tree *tree1, const Tree *tree2);

uint32_t ts_tree_start_column(const Tree *self);
uint32_t ts_tree_end_column(const Tree *self);
void ts_tree_set_children(Tree *, uint32_t, Tree **);
void ts_tree_assign_parents(Tree *, TreePath *);
void ts_tree_edit(Tree *, const TSInputEdit *edit);
char *ts_tree_string(const Tree *, const TSLanguage *, bool include_all);
void ts_tree_print_dot_graph(const Tree *, const TSLanguage *, FILE *);
const TSExternalTokenState *ts_tree_last_external_token_state(const Tree *);

static inline uint32_t ts_tree_total_bytes(const Tree *self) {
  return self->padding.bytes + self->size.bytes;
}

static inline Length ts_tree_total_size(const Tree *self) {
  return length_add(self->padding, self->size);
}

static inline TSPoint ts_tree_total_extent(const Tree *self) {
  return point_add(self->padding.extent, self->size.extent);
}

static inline bool ts_tree_is_fragile(const Tree *tree) {
  return tree->fragile_left || tree->fragile_right ||
         ts_tree_total_bytes(tree) == 0;
}

bool ts_external_token_state_eq(const TSExternalTokenState *, const TSExternalTokenState *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
