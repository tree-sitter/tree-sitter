#include "runtime/alloc.h"
#include "runtime/node.h"
#include "runtime/tree.h"
#include "runtime/parser.h"
#include "runtime/string_input.h"
#include "runtime/document.h"
#include "runtime/tree_path.h"

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
  if (language->version != TREE_SITTER_LANGUAGE_VERSION) return;
  ts_document_invalidate(self);
  parser_set_language(&self->parser, language);
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

void ts_document_set_input_string_with_length(TSDocument *self, const char *text, uint32_t length) {
  ts_document_invalidate(self);
  TSInput input = ts_string_input_make_with_length(text, length);
  ts_document_set_input(self, input);
  if (input.payload) {
    self->owns_input = true;
  }
}

void ts_document_edit(TSDocument *self, TSInputEdit edit) {
  if (!self->tree)
    return;

  uint32_t max_bytes = ts_tree_total_bytes(self->tree);
  if (edit.start_byte > max_bytes)
    return;
  if (edit.bytes_removed > max_bytes - edit.start_byte)
    edit.bytes_removed = max_bytes - edit.start_byte;

  ts_tree_edit(self->tree, &edit);
}

void ts_document_parse(TSDocument *self) {
  return ts_document_parse_with_options(self, (TSParseOptions){
    .halt_on_error = false,
    .changed_ranges = NULL,
    .changed_range_count = NULL,
  });
}

void ts_document_parse_and_get_changed_ranges(TSDocument *self, TSRange **ranges,
                                              uint32_t *range_count) {
  return ts_document_parse_with_options(self, (TSParseOptions){
    .halt_on_error = false,
    .changed_ranges = ranges,
    .changed_range_count = range_count,
  });
}

void ts_document_parse_with_options(TSDocument *self, TSParseOptions options) {
  if (options.changed_ranges && options.changed_range_count) {
    *options.changed_ranges = NULL;
    *options.changed_range_count = 0;
  }

  if (!self->input.read || !self->parser.language)
    return;

  Tree *reusable_tree = self->valid ? self->tree : NULL;
  if (reusable_tree && !reusable_tree->has_changes)
    return;

  Tree *tree = parser_parse(&self->parser, self->input, reusable_tree, options.halt_on_error);

  if (self->tree) {
    Tree *old_tree = self->tree;
    self->tree = tree;

    if (options.changed_ranges && options.changed_range_count) {
      tree_path_init(&self->parser.tree_path1, old_tree);
      tree_path_init(&self->parser.tree_path2, tree);
      tree_path_get_changes(&self->parser.tree_path1, &self->parser.tree_path2,
                            options.changed_ranges, options.changed_range_count);
    }

    ts_tree_release(old_tree);
  }

  self->tree = tree;
  self->parse_count++;
  self->valid = true;
}

void ts_document_invalidate(TSDocument *self) {
  self->valid = false;
}

TSNode ts_document_root_node(const TSDocument *self) {
  TSNode result = ts_node_make(self->tree, 0, 0, 0);
  while (result.data && !((Tree *)result.data)->visible)
    result = ts_node_named_child(result, 0);
  return result;
}

uint32_t ts_document_parse_count(const TSDocument *self) {
  return self->parse_count;
}
