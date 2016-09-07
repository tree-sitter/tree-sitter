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

TSDebugger ts_document_debugger(const TSDocument *self) {
  return self->parser.lexer.debugger;
}

void ts_document_set_debugger(TSDocument *self, TSDebugger debugger) {
  self->parser.lexer.debugger = debugger;
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

  size_t max_chars = ts_tree_total_chars(self->tree);
  if (edit.position > max_chars)
    edit.position = max_chars;
  if (edit.chars_removed > max_chars - edit.position)
    edit.chars_removed = max_chars - edit.position;

  ts_tree_edit(self->tree, edit);
}

int ts_document_parse(TSDocument *self) {
  if (!self->input.read_fn || !self->parser.language)
    return -1;

  TSTree *reusable_tree = self->valid ? self->tree : NULL;
  if (reusable_tree && !reusable_tree->has_changes)
    return 0;

  TSTree *tree = parser_parse(&self->parser, self->input, reusable_tree);
  if (!tree)
    return -1;

  if (self->tree)
    ts_tree_release(self->tree);
  self->tree = tree;
  self->parse_count++;
  self->valid = true;
  return 0;
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
