/*
 * Fuzz tree-sitter's query language parser and execution engine.
 *
 * Tree-sitter queries use S-expression patterns to match syntax tree nodes.
 * This exercises the query compiler and pattern matcher.
 *
 * Build:
 *   clang -g -fsanitize=fuzzer,address -I../lib/include \
 *     -DFUZZ_HAS_JSON fuzz_query.c ../libtree-sitter.a \
 *     <path-to>/libtree-sitter-json.a -o fuzz_query
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tree_sitter/api.h"

#ifdef FUZZ_HAS_JSON
extern const TSLanguage *tree_sitter_json(void);
#endif
#ifdef FUZZ_HAS_JAVASCRIPT
extern const TSLanguage *tree_sitter_javascript(void);
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4 || size > 32768)
    return 0;

  uint8_t lang_sel = data[0] % 2;
  uint8_t split_pct = data[1];
  data += 2;
  size -= 2;

  size_t split = (size * split_pct) / 256;
  if (split < 1) split = 1;
  if (split >= size) split = size - 1;

  const char *query_src = (const char *)data;
  uint32_t query_len = (uint32_t)split;
  const char *source = (const char *)(data + split);
  uint32_t source_len = (uint32_t)(size - split);

  const TSLanguage *language = NULL;
  (void)lang_sel;
#ifdef FUZZ_HAS_JSON
  language = tree_sitter_json();
#elif defined(FUZZ_HAS_JAVASCRIPT)
  language = tree_sitter_javascript();
#else
  return 0;
#endif

  uint32_t error_offset = 0;
  TSQueryError error_type = TSQueryErrorNone;
  TSQuery *query = ts_query_new(language, query_src, query_len,
                                &error_offset, &error_type);
  if (!query) return 0;

  (void)ts_query_pattern_count(query);
  (void)ts_query_capture_count(query);
  (void)ts_query_string_count(query);

  TSParser *parser = ts_parser_new();
  if (!parser) { ts_query_delete(query); return 0; }
  if (!ts_parser_set_language(parser, language)) {
    ts_parser_delete(parser); ts_query_delete(query); return 0;
  }

  TSTree *tree = ts_parser_parse_string(parser, NULL, source, source_len);
  if (tree) {
    TSNode root = ts_tree_root_node(tree);
    if (!ts_node_is_null(root)) {
      TSQueryCursor *cursor = ts_query_cursor_new();
      if (cursor) {
        ts_query_cursor_exec(cursor, query, root);
        TSQueryMatch match;
        uint32_t match_count = 0;
        while (ts_query_cursor_next_match(cursor, &match) && match_count < 64) {
          for (uint16_t i = 0; i < match.capture_count && i < 16; i++) {
            TSNode node = match.captures[i].node;
            (void)ts_node_type(node);
            (void)ts_node_start_byte(node);
          }
          match_count++;
        }
        ts_query_cursor_delete(cursor);
      }
    }
    ts_tree_delete(tree);
  }

  ts_parser_delete(parser);
  ts_query_delete(query);
  return 0;
}
