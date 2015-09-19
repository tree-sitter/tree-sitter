#include "tree_sitter/parser.h"
#include "runtime/node.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/parser.h"
#include "runtime/string_input.h"
#include "runtime/document.h"

TSDocument *ts_document_make() {
  TSDocument *document = calloc(sizeof(TSDocument), 1);
  document->parser = ts_parser_make();
  return document;
}

void ts_document_free(TSDocument *document) {
  ts_parser_destroy(&document->parser);
  if (document->tree)
    ts_tree_release(document->tree);
  free(document);
}

const TSLanguage *ts_document_language(TSDocument *document) {
  return document->parser.language;
}

void ts_document_set_language(TSDocument *document, const TSLanguage *language) {
  document->parser.language = language;
  document->tree = NULL;
}

TSDebugger ts_document_debugger(const TSDocument *document) {
  return ts_parser_debugger(&document->parser);
}

void ts_document_set_debugger(TSDocument *document, TSDebugger debugger) {
  ts_parser_set_debugger(&document->parser, debugger);
}

TSInput ts_document_input(TSDocument *document) {
  return document->input;
}

void ts_document_set_input(TSDocument *document, TSInput input) {
  document->input = input;
}

void ts_document_set_input_string(TSDocument *document, const char *text) {
  ts_document_set_input(document, ts_string_input_make(text));
}

void ts_document_edit(TSDocument *document, TSInputEdit edit) {
  size_t max_chars = ts_tree_total_size(document->tree).chars;
  if (edit.position > max_chars)
    edit.position = max_chars;
  if (edit.chars_removed > max_chars - edit.position)
    edit.chars_removed = max_chars - edit.position;

  ts_tree_edit(document->tree, edit);
}

void ts_document_parse(TSDocument *document) {
  if (document->input.read_fn && document->parser.language) {
    TSTree *tree =
      ts_parser_parse(&document->parser, document->input, document->tree);
    if (document->tree)
      ts_tree_release(document->tree);
    document->tree = tree;
    ts_tree_retain(tree);
    document->parse_count++;
  }
}

TSNode ts_document_root_node(const TSDocument *document) {
  TSNode result = ts_node_make(document->tree, ts_length_zero());
  while (result.data && !ts_tree_is_visible(result.data))
    result = ts_node_named_child(result, 0);
  return result;
}

size_t ts_document_parse_count(const TSDocument *document) {
  return document->parse_count;
}
