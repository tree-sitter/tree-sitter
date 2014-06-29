#ifndef TREE_SITTER_RUNTIME_H_
#define TREE_SITTER_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef unsigned short TSSymbol;
#define ts_builtin_sym_error 0
#define ts_builtin_sym_end 1
#define ts_start_sym 2

typedef struct TSTree TSTree;
TSTree * ts_tree_make_leaf(TSSymbol symbol, size_t size, size_t offset);
TSTree * ts_tree_make_node(TSSymbol symbol, size_t child_count, size_t immediate_child_count, TSTree **children);
TSTree * ts_tree_make_error(char lookahead_char, size_t expected_input_count, const TSSymbol *expected_inputs, size_t size, size_t offset);
void ts_tree_retain(TSTree *tree);
void ts_tree_release(TSTree *tree);
int ts_tree_equals(const TSTree *tree1, const TSTree *tree2);
char * ts_tree_string(const TSTree *tree, const char **names);
char * ts_tree_error_string(const TSTree *tree, const char **names);
TSTree ** ts_tree_children(const TSTree *tree, size_t *count);
TSTree ** ts_tree_immediate_children(const TSTree *tree, size_t *count);
size_t ts_tree_size(const TSTree *tree);
size_t ts_tree_offset(const TSTree *tree);
size_t ts_tree_total_size(const TSTree *tree);
TSSymbol ts_tree_symbol(const TSTree *tree);

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

typedef struct {
    const TSTree * (* parse_fn)(void *data, TSInput input, TSInputEdit *edit);
    void (* free_fn)(void *data);
    const char **symbol_names;
    void *data;
} TSParser;

typedef struct TSDocument TSDocument;
TSDocument * ts_document_make();
void ts_document_free(TSDocument *doc);
void ts_document_set_parser(TSDocument *doc, TSParser parser);
void ts_document_set_input(TSDocument *doc, TSInput input);
void ts_document_set_input_string(TSDocument *doc, const char *text);
void ts_document_edit(TSDocument *doc, TSInputEdit edit);
const TSTree * ts_document_tree(const TSDocument *doc);
const char * ts_document_string(const TSDocument *doc);
const char * ts_document_symbol_name(const TSDocument *document, const TSTree *tree);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
