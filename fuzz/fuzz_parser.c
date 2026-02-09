/*
 * Fuzz tree-sitter's incremental parser with arbitrary source code.
 *
 * Exercises the core parser by feeding arbitrary bytes as source code,
 * then performs tree traversal and incremental re-parsing operations.
 *
 * Build (standalone, after building libtree-sitter):
 *   clang -g -fsanitize=fuzzer,address -I../lib/include \
 *     fuzz_parser.c ../libtree-sitter.a -o fuzz_parser
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tree_sitter/api.h"

/* Link against grammar libraries for richer coverage.
 * Define FUZZ_HAS_JSON, FUZZ_HAS_HTML, FUZZ_HAS_JAVASCRIPT at compile
 * time and link the corresponding grammar .a files. */
#ifdef FUZZ_HAS_JSON
extern const TSLanguage *tree_sitter_json(void);
#endif
#ifdef FUZZ_HAS_HTML
extern const TSLanguage *tree_sitter_html(void);
#endif
#ifdef FUZZ_HAS_JAVASCRIPT
extern const TSLanguage *tree_sitter_javascript(void);
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2 || size > 65536)
    return 0;

  uint8_t lang_selector = data[0];
  const char *source = (const char *)(data + 1);
  uint32_t source_len = (uint32_t)(size - 1);

  const TSLanguage *language = NULL;
  int lang_count = 0;
#ifdef FUZZ_HAS_JSON
  lang_count++;
#endif
#ifdef FUZZ_HAS_HTML
  lang_count++;
#endif
#ifdef FUZZ_HAS_JAVASCRIPT
  lang_count++;
#endif
  if (lang_count == 0) return 0;

  int sel = lang_selector % lang_count;
  int idx = 0;
#ifdef FUZZ_HAS_JSON
  if (idx++ == sel) language = tree_sitter_json();
#endif
#ifdef FUZZ_HAS_HTML
  if (idx++ == sel) language = tree_sitter_html();
#endif
#ifdef FUZZ_HAS_JAVASCRIPT
  if (idx++ == sel) language = tree_sitter_javascript();
#endif
  if (!language) return 0;

  TSParser *parser = ts_parser_new();
  if (!parser) return 0;
  if (!ts_parser_set_language(parser, language)) {
    ts_parser_delete(parser);
    return 0;
  }

  TSTree *tree = ts_parser_parse_string(parser, NULL, source, source_len);
  if (tree) {
    TSNode root = ts_tree_root_node(tree);
    if (!ts_node_is_null(root)) {
      (void)ts_node_type(root);
      (void)ts_node_symbol(root);
      (void)ts_node_child_count(root);
      (void)ts_node_has_error(root);
      char *sexp = ts_node_string(root);
      free(sexp);

      /* Walk children */
      uint32_t cc = ts_node_child_count(root);
      for (uint32_t i = 0; i < cc && i < 32; i++) {
        TSNode child = ts_node_child(root, i);
        if (!ts_node_is_null(child)) {
          (void)ts_node_type(child);
          (void)ts_node_has_error(child);
        }
      }

      /* Tree cursor walk */
      TSTreeCursor cursor = ts_tree_cursor_new(root);
      int depth = 0;
      int went_down = 1;
      while (depth >= 0 && depth < 100) {
        TSNode n = ts_tree_cursor_current_node(&cursor);
        (void)ts_node_type(n);
        (void)ts_tree_cursor_current_field_name(&cursor);
        if (went_down && ts_tree_cursor_goto_first_child(&cursor)) {
          depth++; went_down = 1;
        } else if (ts_tree_cursor_goto_next_sibling(&cursor)) {
          went_down = 1;
        } else if (ts_tree_cursor_goto_parent(&cursor)) {
          depth--; went_down = 0;
        } else break;
      }
      ts_tree_cursor_delete(&cursor);
    }

    /* Incremental re-parse */
    if (source_len > 4) {
      TSInputEdit edit = {
        .start_byte = 0, .old_end_byte = source_len / 2,
        .new_end_byte = source_len / 2 + 1,
        .start_point = {0, 0}, .old_end_point = {0, source_len / 2},
        .new_end_point = {0, source_len / 2 + 1},
      };
      ts_tree_edit(tree, &edit);
      TSTree *new_tree = ts_parser_parse_string(parser, tree, source, source_len);
      if (new_tree) ts_tree_delete(new_tree);
    }
    ts_tree_delete(tree);
  }

  ts_parser_delete(parser);
  return 0;
}
