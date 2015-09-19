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
  void *payload;
  const char *(*read_fn)(void *payload, size_t *bytes_read);
  int (*seek_fn)(void *payload, TSLength position);
} TSInput;

typedef enum {
  TSDebugTypeParse,
  TSDebugTypeLex,
} TSDebugType;

typedef struct {
  void *payload;
  void (*debug_fn)(void *payload, TSDebugType, const char *);
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
TSSymbol ts_node_symbol(TSNode);
const char *ts_node_name(TSNode, const TSDocument *);
const char *ts_node_string(TSNode, const TSDocument *);
bool ts_node_eq(TSNode, TSNode);
bool ts_node_is_named(TSNode);
bool ts_node_has_changes(TSNode);
TSNode ts_node_parent(TSNode);
TSNode ts_node_child(TSNode, size_t);
TSNode ts_node_named_child(TSNode, size_t);
size_t ts_node_child_count(TSNode);
size_t ts_node_named_child_count(TSNode);
TSNode ts_node_next_sibling(TSNode);
TSNode ts_node_next_named_sibling(TSNode);
TSNode ts_node_prev_sibling(TSNode);
TSNode ts_node_prev_named_sibling(TSNode);
TSNode ts_node_descendent_for_range(TSNode, size_t, size_t);
TSNode ts_node_named_descendent_for_range(TSNode, size_t, size_t);

TSDocument *ts_document_make();
void ts_document_free(TSDocument *);
const TSLanguage *ts_document_language(TSDocument *);
void ts_document_set_language(TSDocument *, const TSLanguage *);
TSInput ts_document_input(TSDocument *);
void ts_document_set_input(TSDocument *, TSInput);
void ts_document_set_input_string(TSDocument *, const char *);
TSDebugger ts_document_debugger(const TSDocument *);
void ts_document_set_debugger(TSDocument *, TSDebugger);
void ts_document_parse(TSDocument *);
void ts_document_edit(TSDocument *, TSInputEdit);
TSNode ts_document_root_node(const TSDocument *);
size_t ts_document_parse_count(const TSDocument *);

#define ts_builtin_sym_error 0
#define ts_builtin_sym_end 1
#define ts_builtin_sym_start 2

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
