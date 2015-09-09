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
  TSDebugTypeLex,
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

typedef struct {
  const void *data;
  TSLength offset;
} TSNode;

typedef unsigned short TSSymbol;
typedef struct TSLanguage TSLanguage;
typedef struct TSDocument TSDocument;

TSLength ts_node_pos(TSNode);
TSLength ts_node_size(TSNode);
TSSymbol ts_node_sym(TSNode);
TSNode ts_node_child(TSNode, size_t);
size_t ts_node_child_count(TSNode);
TSNode ts_node_concrete_child(TSNode, size_t);
size_t ts_node_concrete_child_count(TSNode);
TSNode ts_node_find_for_pos(TSNode, size_t);
TSNode ts_node_find_for_range(TSNode, size_t, size_t);
TSNode ts_node_find_concrete_for_pos(TSNode, size_t);
TSNode ts_node_find_concrete_for_range(TSNode, size_t, size_t);
TSNode ts_node_parent(TSNode);
TSNode ts_node_next_sibling(TSNode);
TSNode ts_node_prev_sibling(TSNode);
TSNode ts_node_next_concrete_sibling(TSNode);
TSNode ts_node_prev_concrete_sibling(TSNode);
const char *ts_node_name(TSNode, const TSDocument *);
const char *ts_node_string(TSNode, const TSDocument *);
bool ts_node_eq(TSNode, TSNode);
bool ts_node_is_concrete(TSNode);

TSDocument *ts_document_make();
void ts_document_free(TSDocument *);
void ts_document_set_language(TSDocument *, const TSLanguage *);
void ts_document_set_input(TSDocument *, TSInput);
void ts_document_set_input_string(TSDocument *, const char *);
void ts_document_edit(TSDocument *, TSInputEdit);
TSDebugger ts_document_get_debugger(const TSDocument *);
void ts_document_set_debugger(TSDocument *, TSDebugger);
TSNode ts_document_root_node(const TSDocument *);

#define ts_builtin_sym_error 0
#define ts_builtin_sym_end 1
#define ts_builtin_sym_start 2

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
