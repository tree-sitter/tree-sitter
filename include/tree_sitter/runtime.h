#ifndef TREE_SITTER_RUNTIME_H_
#define TREE_SITTER_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef unsigned short TSSymbol;
typedef struct TSLanguage TSLanguage;
typedef struct TSDocument TSDocument;

typedef enum {
  TSInputEncodingUTF8,
  TSInputEncodingUTF16,
} TSInputEncoding;

typedef struct {
  void *payload;
  const char *(*read)(void *payload, uint32_t *bytes_read);
  int (*seek)(void *payload, uint32_t character_index, uint32_t byte_index);
  TSInputEncoding encoding;
} TSInput;

typedef enum {
  TSLogTypeParse,
  TSLogTypeLex,
} TSLogType;

typedef struct {
  void *payload;
  void (*log)(void *payload, TSLogType, const char *);
} TSLogger;

typedef struct {
  uint32_t row;
  uint32_t column;
} TSPoint;

typedef struct {
  uint32_t start_byte;
  uint32_t bytes_removed;
  uint32_t bytes_added;
  TSPoint start_point;
  TSPoint extent_removed;
  TSPoint extent_added;
} TSInputEdit;

typedef struct {
  TSPoint start;
  TSPoint end;
} TSRange;

typedef struct {
  const void *data;
  uint32_t offset[3];
} TSNode;

typedef struct {
  TSSymbol value;
  bool done;
  void *data;
} TSSymbolIterator;

uint32_t ts_node_start_char(TSNode);
uint32_t ts_node_start_byte(TSNode);
TSPoint ts_node_start_point(TSNode);
uint32_t ts_node_end_char(TSNode);
uint32_t ts_node_end_byte(TSNode);
TSPoint ts_node_end_point(TSNode);
TSSymbol ts_node_symbol(TSNode);
TSSymbolIterator ts_node_symbols(TSNode);
void ts_symbol_iterator_next(TSSymbolIterator *);
const char *ts_node_type(TSNode, const TSDocument *);
char *ts_node_string(TSNode, const TSDocument *);
bool ts_node_eq(TSNode, TSNode);
bool ts_node_is_named(TSNode);
bool ts_node_has_changes(TSNode);
TSNode ts_node_parent(TSNode);
TSNode ts_node_child(TSNode, uint32_t);
TSNode ts_node_named_child(TSNode, uint32_t);
uint32_t ts_node_child_count(TSNode);
uint32_t ts_node_named_child_count(TSNode);
TSNode ts_node_next_sibling(TSNode);
TSNode ts_node_next_named_sibling(TSNode);
TSNode ts_node_prev_sibling(TSNode);
TSNode ts_node_prev_named_sibling(TSNode);
TSNode ts_node_descendant_for_char_range(TSNode, uint32_t, uint32_t);
TSNode ts_node_named_descendant_for_char_range(TSNode, uint32_t, uint32_t);
TSNode ts_node_descendant_for_byte_range(TSNode, uint32_t, uint32_t);
TSNode ts_node_named_descendant_for_byte_range(TSNode, uint32_t, uint32_t);
TSNode ts_node_descendant_for_point_range(TSNode, TSPoint, TSPoint);
TSNode ts_node_named_descendant_for_point_range(TSNode, TSPoint, TSPoint);

TSDocument *ts_document_new();
void ts_document_free(TSDocument *);
const TSLanguage *ts_document_language(TSDocument *);
void ts_document_set_language(TSDocument *, const TSLanguage *);
TSInput ts_document_input(TSDocument *);
void ts_document_set_input(TSDocument *, TSInput);
void ts_document_set_input_string(TSDocument *, const char *);
TSLogger ts_document_logger(const TSDocument *);
void ts_document_set_logger(TSDocument *, TSLogger);
void ts_document_print_debugging_graphs(TSDocument *, bool);
void ts_document_edit(TSDocument *, TSInputEdit);
void ts_document_parse(TSDocument *);
void ts_document_parse_and_get_changed_ranges(TSDocument *, TSRange **, uint32_t *);
void ts_document_invalidate(TSDocument *);
TSNode ts_document_root_node(const TSDocument *);
uint32_t ts_document_parse_count(const TSDocument *);

uint32_t ts_language_symbol_count(const TSLanguage *);
const char *ts_language_symbol_name(const TSLanguage *, TSSymbol);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
