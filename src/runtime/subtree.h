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

typedef struct {
  union {
    char *long_data;
    char short_data[sizeof(char *) + sizeof(uint32_t)];
  };
  uint32_t length;
} TSExternalTokenState;

typedef struct Subtree Subtree;

typedef Array(Subtree *) SubtreeArray;

struct Subtree {
  Length padding;
  Length size;
  volatile uint32_t ref_count;
  uint32_t bytes_scanned;
  uint32_t error_cost;
  uint32_t node_count;
  uint32_t repeat_depth;
  uint32_t child_count;
  int32_t dynamic_precedence;

  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool fragile_left : 1;
  bool fragile_right : 1;
  bool has_changes : 1;
  bool has_external_tokens : 1;
  bool is_missing : 1;
  TSSymbol symbol;
  TSStateId parse_state;
  struct {
    TSSymbol symbol;
    TSLexMode lex_mode;
  } first_leaf;

  union {
    struct {
      SubtreeArray children;
      uint32_t visible_child_count;
      uint32_t named_child_count;
      uint16_t alias_sequence_id;
    };
    struct {
      uint32_t _2;
      TSExternalTokenState external_token_state;
    };
    struct {
      uint32_t _1;
      int32_t lookahead_char;
    };
  };
};

typedef struct {
  SubtreeArray free_trees;
  SubtreeArray tree_stack;
} SubtreePool;

void ts_external_token_state_init(TSExternalTokenState *, const char *, unsigned);
const char *ts_external_token_state_data(const TSExternalTokenState *);

bool ts_subtree_array_copy(SubtreeArray, SubtreeArray *);
void ts_subtree_array_delete(SubtreePool *, SubtreeArray *);
SubtreeArray ts_subtree_array_remove_trailing_extras(SubtreeArray *);
void ts_subtree_array_reverse(SubtreeArray *);

void ts_subtree_pool_init(SubtreePool *);
void ts_subtree_pool_delete(SubtreePool *);
Subtree *ts_subtree_pool_allocate(SubtreePool *);
void ts_subtree_pool_free(SubtreePool *, Subtree *);

Subtree *ts_subtree_make_leaf(SubtreePool *, TSSymbol, Length, Length, const TSLanguage *);
Subtree *ts_subtree_make_node(SubtreePool *, TSSymbol, SubtreeArray *, unsigned, const TSLanguage *);
Subtree *ts_subtree_make_copy(SubtreePool *, Subtree *child);
Subtree *ts_subtree_make_error_node(SubtreePool *, SubtreeArray *, const TSLanguage *);
Subtree *ts_subtree_make_error(SubtreePool *, Length, Length, int32_t, const TSLanguage *);
Subtree *ts_subtree_make_missing_leaf(SubtreePool *, TSSymbol, const TSLanguage *);
void ts_subtree_retain(Subtree *tree);
void ts_subtree_release(SubtreePool *, Subtree *tree);
bool ts_subtree_eq(const Subtree *tree1, const Subtree *tree2);
int ts_subtree_compare(const Subtree *tree1, const Subtree *tree2);
void ts_subtree_set_children(Subtree *, SubtreeArray *, const TSLanguage *);
void ts_subtree_balance(Subtree *, SubtreePool *, const TSLanguage *);
Subtree *ts_subtree_edit(Subtree *, const TSInputEdit *edit, SubtreePool *);
char *ts_subtree_string(const Subtree *, const TSLanguage *, bool include_all);
void ts_subtree_print_dot_graph(const Subtree *, const TSLanguage *, FILE *);
Subtree *ts_subtree_last_external_token(Subtree *);
bool ts_subtree_external_token_state_eq(const Subtree *, const Subtree *);

static inline uint32_t ts_subtree_total_bytes(const Subtree *self) {
  return self->padding.bytes + self->size.bytes;
}

static inline uint32_t ts_subtree_total_rows(const Subtree *self) {
  return self->padding.extent.row + self->size.extent.row;
}

static inline Length ts_subtree_total_size(const Subtree *self) {
  return length_add(self->padding, self->size);
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
