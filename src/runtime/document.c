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
  if (document->input.release_fn)
    document->input.release_fn(document->input.data);
  if (document->tree)
    ts_tree_release(document->tree);
  free(document);
}

static void ts_document__reparse(TSDocument *document, TSInputEdit *edit) {
  if (document->input.read_fn && document->parser.language) {
    TSTree *tree = ts_parser_parse(&document->parser, document->input, edit);
    if (document->tree)
      ts_tree_release(document->tree);
    document->tree = tree;
    ts_tree_retain(tree);
  }
}

void ts_document_set_language(TSDocument *document, const TSLanguage *language) {
  document->parser.language = language;
  ts_document__reparse(document, NULL);
}

TSDebugger ts_document_get_debugger(const TSDocument *document) {
  return ts_parser_get_debugger(&document->parser);
}

void ts_document_set_debugger(TSDocument *document, TSDebugger debugger) {
  ts_parser_set_debugger(&document->parser, debugger);
}

void ts_document_set_input(TSDocument *document, TSInput input) {
  document->input = input;
  ts_document__reparse(document, NULL);
}

void ts_document_edit(TSDocument *document, TSInputEdit edit) {
  ts_document__reparse(document, &edit);
}

const char *ts_document_symbol_name(const TSDocument *document,
                                    const TSTree *tree) {
  return document->parser.language->symbol_names[tree->symbol];
}

void ts_document_set_input_string(TSDocument *document, const char *text) {
  ts_document_set_input(document, ts_string_input_make(text));
}

TSNode ts_document_root_node(const TSDocument *document) {
  TSNode result = ts_node_make(document->tree, ts_length_zero());
  while (result.data && !ts_tree_is_visible(result.data))
    result = ts_node_child(result, 0);
  return result;
}
