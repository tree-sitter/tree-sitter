#ifndef TREE_SITTER_RUNTIME_H_
#define TREE_SITTER_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define TREE_SITTER_LANGUAGE_VERSION 8

typedef unsigned short TSSymbol;
typedef struct TSLanguage TSLanguage;
typedef struct TSParser TSParser;
typedef struct TSTree TSTree;

typedef enum {
  TSInputEncodingUTF8,
  TSInputEncodingUTF16,
} TSInputEncoding;

typedef enum {
  TSSymbolTypeRegular,
  TSSymbolTypeAnonymous,
  TSSymbolTypeAuxiliary,
} TSSymbolType;

typedef struct {
  uint32_t row;
  uint32_t column;
} TSPoint;

typedef struct {
  TSPoint start;
  TSPoint end;
} TSRange;

typedef struct {
  void *payload;
  const char *(*read)(void *payload, uint32_t *bytes_read);
  int (*seek)(void *payload, uint32_t byte_index, TSPoint position);
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
  uint32_t start_byte;
  uint32_t bytes_removed;
  uint32_t bytes_added;
  TSPoint start_point;
  TSPoint extent_removed;
  TSPoint extent_added;
} TSInputEdit;

typedef struct {
  uint32_t context[4];
  const void *id;
  const void *tree;
} TSNode;

typedef struct {
  uint32_t context[2];
  const void *id;
  const void *tree;
} TSTreeCursor;

TSParser *ts_parser_new();
void ts_parser_delete(TSParser *);
const TSLanguage *ts_parser_language(const TSParser *);
bool ts_parser_set_language(TSParser *, const TSLanguage *);
TSLogger ts_parser_logger(const TSParser *);
void ts_parser_set_logger(TSParser *, TSLogger);
void ts_parser_print_dot_graphs(TSParser *, FILE *);
void ts_parser_halt_on_error(TSParser *, bool);
TSTree *ts_parser_parse(TSParser *, const TSTree *, TSInput);
TSTree *ts_parser_parse_string(TSParser *, const TSTree *, const char *, uint32_t);

TSTree *ts_tree_copy(const TSTree *);
void ts_tree_delete(TSTree *);
TSNode ts_tree_root_node(const TSTree *);
void ts_tree_edit(TSTree *, const TSInputEdit *);
TSRange *ts_tree_get_changed_ranges(const TSTree *, const TSTree *, uint32_t *);
void ts_tree_print_dot_graph(const TSTree *, FILE *);

uint32_t ts_node_start_byte(TSNode);
TSPoint ts_node_start_point(TSNode);
uint32_t ts_node_end_byte(TSNode);
TSPoint ts_node_end_point(TSNode);
TSSymbol ts_node_symbol(TSNode);
const char *ts_node_type(TSNode);
char *ts_node_string(TSNode);
bool ts_node_eq(TSNode, TSNode);
bool ts_node_is_null(TSNode);
bool ts_node_is_named(TSNode);
bool ts_node_is_missing(TSNode);
bool ts_node_has_changes(TSNode);
bool ts_node_has_error(TSNode);
TSNode ts_node_parent(TSNode);
TSNode ts_node_child(TSNode, uint32_t);
TSNode ts_node_named_child(TSNode, uint32_t);
uint32_t ts_node_child_count(TSNode);
uint32_t ts_node_named_child_count(TSNode);
TSNode ts_node_next_sibling(TSNode);
TSNode ts_node_next_named_sibling(TSNode);
TSNode ts_node_prev_sibling(TSNode);
TSNode ts_node_prev_named_sibling(TSNode);
TSNode ts_node_first_child_for_byte(TSNode, uint32_t);
TSNode ts_node_first_named_child_for_byte(TSNode, uint32_t);
TSNode ts_node_descendant_for_byte_range(TSNode, uint32_t, uint32_t);
TSNode ts_node_named_descendant_for_byte_range(TSNode, uint32_t, uint32_t);
TSNode ts_node_descendant_for_point_range(TSNode, TSPoint, TSPoint);
TSNode ts_node_named_descendant_for_point_range(TSNode, TSPoint, TSPoint);

TSTreeCursor ts_tree_cursor_new(const TSTree *);
void ts_tree_cursor_delete(TSTreeCursor *);
bool ts_tree_cursor_goto_first_child(TSTreeCursor *);
int64_t ts_tree_cursor_goto_first_child_for_byte(TSTreeCursor *, uint32_t);
bool ts_tree_cursor_goto_next_sibling(TSTreeCursor *);
bool ts_tree_cursor_goto_parent(TSTreeCursor *);
TSNode ts_tree_cursor_current_node(TSTreeCursor *);

uint32_t ts_language_symbol_count(const TSLanguage *);
const char *ts_language_symbol_name(const TSLanguage *, TSSymbol);
TSSymbolType ts_language_symbol_type(const TSLanguage *, TSSymbol);
uint32_t ts_language_version(const TSLanguage *);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
