#ifndef TREE_SITTER_RUNTIME_H_
#define TREE_SITTER_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  size_t bytes;
  size_t chars;
} TSLength;

typedef struct {
  void *data;
  const char *(*read_fn)(void *data, size_t *bytes_read);
  int (*seek_fn)(void *data, TSLength position);
  void (*release_fn)(void *data);
} TSInput;

typedef enum {
  TSDebugTypeParse,
  TSDebugTypeLex
} TSDebugType;

typedef struct {
  void *data;
  void (*debug_fn)(void *data, TSDebugType, const char *);
  void (*release_fn)(void *data);
} TSDebugger;

typedef struct {
  size_t position;
  size_t chars_inserted;
  size_t chars_removed;
} TSInputEdit;

typedef unsigned short TSSymbol;
typedef struct TSLanguage TSLanguage;

typedef struct TSNode TSNode;
TSLength ts_node_pos(const TSNode *);
TSLength ts_node_size(const TSNode *);
TSSymbol ts_node_sym(const TSNode *);
TSNode *ts_node_child(TSNode *, size_t);
size_t ts_node_child_count(const TSNode *);
TSNode *ts_node_find_for_pos(TSNode *, size_t);
TSNode *ts_node_find_for_range(TSNode *, size_t, size_t);
TSNode *ts_node_parent(TSNode *node);
TSNode *ts_node_next_sibling(TSNode *node);
TSNode *ts_node_prev_sibling(TSNode *node);
const char *ts_node_name(const TSNode *);
const char *ts_node_string(const TSNode *);
void ts_node_retain(TSNode *node);
void ts_node_release(TSNode *node);
bool ts_node_eq(const TSNode *, const TSNode *);

typedef struct TSDocument TSDocument;
TSDocument *ts_document_make();
void ts_document_free(TSDocument *);
void ts_document_set_language(TSDocument *, const TSLanguage *);
void ts_document_set_input(TSDocument *, TSInput);
void ts_document_set_input_string(TSDocument *, const char *);
void ts_document_edit(TSDocument *, TSInputEdit);
TSDebugger ts_document_get_debugger(const TSDocument *);
void ts_document_set_debugger(TSDocument *, TSDebugger);
TSNode *ts_document_root_node(const TSDocument *);

#define ts_builtin_sym_error 0
#define ts_builtin_sym_end 1
#define ts_builtin_sym_document 2
#define ts_builtin_sym_start 3

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
