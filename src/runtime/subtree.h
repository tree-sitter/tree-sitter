#ifndef RUNTIME_SUBTREE_H_
#define RUNTIME_SUBTREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include "runtime/length.h"
#include "runtime/array.h"
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"

extern TSStateId TS_TREE_STATE_NONE;

typedef struct {
  union {
    char *long_data;
    char short_data[24];
  };
  uint32_t length;
} ExternalScannerState;

typedef struct Subtree Subtree;

struct Subtree {
  volatile uint32_t ref_count;
  Length padding;
  Length size;
  uint32_t bytes_scanned;
  uint32_t error_cost;
  uint32_t child_count;
  TSSymbol symbol;
  TSStateId parse_state;

  bool is_small : 1;
  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool fragile_left : 1;
  bool fragile_right : 1;
  bool has_changes : 1;
  bool has_external_tokens : 1;
  bool is_missing : 1;
  bool is_keyword : 1;

  union {
    // Non-terminal subtrees (`child_count > 0`)
    struct {
      const Subtree **children;
      uint32_t visible_child_count;
      uint32_t named_child_count;
      uint32_t node_count;
      uint32_t repeat_depth;
      int32_t dynamic_precedence;
      uint16_t alias_sequence_id;
      struct {
        TSSymbol symbol;
        TSStateId parse_state;
      } first_leaf;
    };

    // External terminal subtrees (`child_count == 0 && has_external_tokens`)
    ExternalScannerState external_scanner_state;

    // Error terminal subtrees (`child_count == 0 && symbol == ts_builtin_sym_error`)
    int32_t lookahead_char;
  };
};

typedef Array(const Subtree *) SubtreeArray;
typedef Array(Subtree *) MutableSubtreeArray;

typedef struct {
  MutableSubtreeArray free_trees;
  MutableSubtreeArray free_small_trees;
  MutableSubtreeArray tree_stack;
} SubtreePool;

void ts_external_scanner_state_init(ExternalScannerState *, const char *, unsigned);
const char *ts_external_scanner_state_data(const ExternalScannerState *);

void ts_subtree_array_copy(SubtreeArray, SubtreeArray *);
void ts_subtree_array_delete(SubtreePool *, SubtreeArray *);
SubtreeArray ts_subtree_array_remove_trailing_extras(SubtreeArray *);
void ts_subtree_array_reverse(SubtreeArray *);

SubtreePool ts_subtree_pool_new(uint32_t capacity);
void ts_subtree_pool_delete(SubtreePool *);
Subtree *ts_subtree_pool_allocate(SubtreePool *, bool);
void ts_subtree_pool_free(SubtreePool *, Subtree *);

Subtree *ts_subtree_new_leaf(
  SubtreePool *, TSSymbol, Length, Length, uint32_t,
  TSStateId, bool, bool, const TSLanguage *
);
Subtree *ts_subtree_new_node(SubtreePool *, TSSymbol, SubtreeArray *, unsigned, const TSLanguage *);
Subtree *ts_subtree_new_copy(SubtreePool *, const Subtree *);
Subtree *ts_subtree_new_error_node(SubtreePool *, SubtreeArray *, const TSLanguage *);
Subtree *ts_subtree_new_error(SubtreePool *, Length, Length, int32_t, const TSLanguage *);
Subtree *ts_subtree_new_missing_leaf(SubtreePool *, TSSymbol, Length, const TSLanguage *);
Subtree *ts_subtree_make_mut(SubtreePool *, const Subtree *);
void ts_subtree_retain(const Subtree *tree);
void ts_subtree_release(SubtreePool *, const Subtree *tree);
bool ts_subtree_eq(const Subtree *tree1, const Subtree *tree2);
int ts_subtree_compare(const Subtree *tree1, const Subtree *tree2);
void ts_subtree_set_children(Subtree *, const Subtree **, uint32_t, const TSLanguage *);
void ts_subtree_balance(const Subtree *, SubtreePool *, const TSLanguage *);
const Subtree *ts_subtree_edit(const Subtree *, const TSInputEdit *edit, SubtreePool *);
char *ts_subtree_string(const Subtree *, const TSLanguage *, bool include_all);
void ts_subtree_print_dot_graph(const Subtree *, const TSLanguage *, FILE *);
const Subtree *ts_subtree_last_external_token(const Subtree *);
bool ts_subtree_external_scanner_state_eq(const Subtree *, const Subtree *);

static inline uint32_t ts_subtree_total_bytes(const Subtree *self) {
  return self->padding.bytes + self->size.bytes;
}

static inline Length ts_subtree_total_size(const Subtree *self) {
  return length_add(self->padding, self->size);
}

static inline TSSymbol ts_subtree_leaf_symbol(const Subtree *self) {
  return self->child_count > 0 ? self->first_leaf.symbol : self->symbol;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_SUBTREE_H_
