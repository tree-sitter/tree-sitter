#include "tree_sitter/parser.h"
#include "runtime/alloc.h"
#include "runtime/node.h"
#include "runtime/tree.h"
#include "runtime/parser.h"
#include "runtime/string_input.h"
#include "runtime/document.h"

TSDocument *ts_document_new() {
  TSDocument *self = ts_calloc(1, sizeof(TSDocument));
  if (!self)
    goto error;

  if (!parser_init(&self->parser))
    goto error;

  return self;

error:
  if (self)
    ts_free(self);
  return NULL;
}

void ts_document_free(TSDocument *self) {
  parser_destroy(&self->parser);
  if (self->tree)
    ts_tree_release(self->tree);
  ts_document_set_input(self,
                        (TSInput){ NULL, NULL, NULL, TSInputEncodingUTF8 });
  ts_free(self);
}

const TSLanguage *ts_document_language(TSDocument *self) {
  return self->parser.language;
}

void ts_document_set_language(TSDocument *self, const TSLanguage *language) {
  ts_document_invalidate(self);
  self->parser.language = language;
  if (self->tree) {
    ts_tree_release(self->tree);
    self->tree = NULL;
  }
}

TSLogger ts_document_logger(const TSDocument *self) {
  return self->parser.lexer.logger;
}

void ts_document_set_logger(TSDocument *self, TSLogger logger) {
  self->parser.lexer.logger = logger;
}

void ts_document_print_debugging_graphs(TSDocument *self, bool should_print) {
  self->parser.print_debugging_graphs = should_print;
}

TSInput ts_document_input(TSDocument *self) {
  return self->input;
}

void ts_document_set_input(TSDocument *self, TSInput input) {
  if (self->owns_input)
    ts_free(self->input.payload);
  self->input = input;
  self->owns_input = false;
}

void ts_document_set_input_string(TSDocument *self, const char *text) {
  ts_document_invalidate(self);
  TSInput input = ts_string_input_make(text);
  ts_document_set_input(self, input);
  if (input.payload) {
    self->owns_input = true;
  }
}

void ts_document_edit(TSDocument *self, TSInputEdit edit) {
  if (!self->tree)
    return;

  size_t max_bytes = ts_tree_total_bytes(self->tree);
  if (edit.start_byte > max_bytes)
    return;
  if (edit.bytes_removed > max_bytes - edit.start_byte)
    edit.bytes_removed = max_bytes - edit.start_byte;

  ts_tree_edit(self->tree, &edit);
}

typedef Array(TSRange) RangeArray;

#define NAME(t) ((t) ? (ts_language_symbol_name(doc->parser.language, ((TSTree *)(t))->symbol)) : "<NULL>")
// #define PRINT(msg, ...) for (size_t k = 0; k < depth; k++) { printf("    "); } printf(msg "\n", __VA_ARGS__);
#define PRINT(msg, ...)

static bool push_diff(RangeArray *results, TSNode *node, bool *extend_last_change) {
  TSPoint start = ts_node_start_point(*node);
  TSPoint end = ts_node_end_point(*node);
  if (*extend_last_change) {
    TSRange *last_range = array_back(results);
    last_range->end = end;
    return true;
  }
  *extend_last_change = true;
  return array_push(results, ((TSRange){start, end}));
}

static bool ts_tree_get_changes(TSDocument *doc, TSTree *old, TSNode *new_node,
                                size_t depth, RangeArray *results,
                                bool *extend_last_change) {
  TSTree *new = (TSTree *)(new_node->data);

  PRINT("At %lu, ('%s', %lu) vs ('%s', %lu) {",
    ts_node_start_byte(*new_node),
    NAME(old), old->size.bytes,
    NAME(new), new->size.bytes);

  if (old->visible) {
    if (old == new || (old->symbol == new->symbol &&
        old->size.bytes == new->size.bytes && !old->has_changes)) {
      *extend_last_change = false;
      PRINT("}", NULL);
      return true;
    }

    if (old->symbol != new->symbol) {
      PRINT("}", NULL);
      return push_diff(results, new_node, extend_last_change);
    }

    TSNode child = ts_node_child(*new_node, 0);
    if (child.data) {
      *new_node = child;
    } else {
      PRINT("}", NULL);
      return true;
    }
  }

  depth++;
  size_t old_child_start;
  size_t old_child_end = ts_node_start_byte(*new_node) - old->padding.bytes;

  for (size_t j = 0; j < old->child_count; j++) {
    TSTree *old_child = old->children[j];
    if (old_child->padding.bytes == 0 && old_child->size.bytes == 0)
      continue;

    old_child_start = old_child_end + old_child->padding.bytes;
    old_child_end = old_child_start + old_child->size.bytes;

    while (true) {
      size_t new_child_start = ts_node_start_byte(*new_node);
      if (new_child_start < old_child_start) {
        PRINT("skip new:('%s', %lu), old:('%s', %lu), old_parent:%s",
          NAME(new_node->data), ts_node_start_byte(*new_node), NAME(old_child),
          old_child_start, NAME(old));

        if (!push_diff(results, new_node, extend_last_change))
          return false;

        TSNode next = ts_node_next_sibling(*new_node);
        if (next.data) {
          PRINT("advance before diff ('%s', %lu) -> ('%s', %lu)",
            NAME(new_node->data), ts_node_start_byte(*new_node), NAME(next.data),
            ts_node_start_byte(next));

          *new_node = next;
        } else {
          break;
        }
      } else if (new_child_start == old_child_start) {
        if (!ts_tree_get_changes(doc, old_child, new_node, depth, results, extend_last_change))
          return false;

        if (old_child->visible) {
          TSNode next = ts_node_next_sibling(*new_node);
          if (next.data) {
            PRINT("advance after diff ('%s', %lu) -> ('%s', %lu)",
              NAME(new_node->data), ts_node_start_byte(*new_node), NAME(next.data),
              ts_node_start_byte(next));
            *new_node = next;
          }
        }
        break;
      } else {
        break;
      }
    }
  }

  depth--;
  if (old->visible) {
    *new_node = ts_node_parent(*new_node);
  }

  PRINT("}", NULL);
  return true;
}

int ts_document_parse_and_get_changed_ranges(TSDocument *self, TSRange **ranges, size_t *range_count) {
  if (ranges) *ranges = NULL;
  if (range_count) *range_count = 0;

  if (!self->input.read || !self->parser.language)
    return -1;

  TSTree *reusable_tree = self->valid ? self->tree : NULL;
  if (reusable_tree && !reusable_tree->has_changes)
    return 0;

  TSTree *tree = parser_parse(&self->parser, self->input, reusable_tree);
  if (!tree)
    return -1;

  if (self->tree) {
    TSTree *old_tree = self->tree;
    self->tree = tree;
    TSNode new_root = ts_document_root_node(self);

    // ts_tree_print_dot_graph(old_tree, self->parser.language, stderr);
    // ts_tree_print_dot_graph(tree, self->parser.language, stderr);

    if (ranges && range_count) {
      bool extend_last_change = false;
      RangeArray result = {0, 0, 0};
      if (!ts_tree_get_changes(self, old_tree, &new_root, 0, &result, &extend_last_change))
        return -1;
      *ranges = result.contents;
      *range_count = result.size;
    }

    ts_tree_release(old_tree);
  }

  self->tree = tree;
  self->parse_count++;
  self->valid = true;
  return 0;
}

int ts_document_parse(TSDocument *self) {
  return ts_document_parse_and_get_changed_ranges(self, NULL, NULL);
}

void ts_document_invalidate(TSDocument *self) {
  self->valid = false;
}

TSNode ts_document_root_node(const TSDocument *self) {
  TSNode result = ts_node_make(self->tree, 0, 0, 0);
  while (result.data && !((TSTree *)result.data)->visible)
    result = ts_node_named_child(result, 0);
  return result;
}

size_t ts_document_parse_count(const TSDocument *self) {
  return self->parse_count;
}
