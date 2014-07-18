#ifndef TREE_SITTER_RUNTIME_H_
#define TREE_SITTER_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct {
    void *data;
    const char * (* read_fn)(void *data, size_t *bytes_read);
    int (* seek_fn)(void *data, size_t position);
    void (* release_fn)(void *data);
} TSInput;

typedef struct {
    size_t position;
    size_t bytes_inserted;
    size_t bytes_removed;
} TSInputEdit;

typedef unsigned short TSSymbol;

typedef struct TSNode TSNode;
typedef struct TSParser TSParser;
typedef struct TSDocument TSDocument;

size_t ts_node_pos(const TSNode *);
size_t ts_node_size(const TSNode *);
TSSymbol ts_node_sym(const TSNode *);
const char * ts_node_name(const TSNode *);
TSNode * ts_node_child(TSNode *, size_t);
TSNode * ts_node_leaf_at_pos(TSNode *, size_t);
TSNode * ts_node_parent(TSNode *node);
TSNode * ts_node_next_sibling(TSNode *node);
TSNode * ts_node_prev_sibling(TSNode *node);
void ts_node_retain(TSNode *node);
void ts_node_release(TSNode *node);
const char * ts_node_string(const TSNode *);
int ts_node_eq(const TSNode *, const TSNode *);

TSDocument * ts_document_make();
void ts_document_free(TSDocument *doc);
void ts_document_set_parser(TSDocument *doc, TSParser *parser);
void ts_document_set_input(TSDocument *doc, TSInput input);
void ts_document_set_input_string(TSDocument *doc, const char *text);
void ts_document_edit(TSDocument *doc, TSInputEdit edit);
const char * ts_document_string(const TSDocument *doc);
TSNode * ts_document_get_node(const TSDocument *document, size_t position);
TSNode * ts_document_root_node(const TSDocument *document);

#define ts_builtin_sym_error 0
#define ts_builtin_sym_end 1
#define ts_start_sym 2

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
