#ifndef TREE_SITTER_RUNTIME_H_
#define TREE_SITTER_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef unsigned short ts_symbol;
#define ts_builtin_sym_error 0
#define ts_builtin_sym_end 1
#define ts_start_sym 2

typedef struct ts_tree ts_tree;
ts_tree * ts_tree_make_leaf(ts_symbol symbol, size_t size, size_t offset);
ts_tree * ts_tree_make_node(ts_symbol symbol, size_t child_count, size_t immediate_child_count, ts_tree **children);
ts_tree * ts_tree_make_error(char lookahead_char, size_t expected_input_count, const ts_symbol *expected_inputs, size_t size, size_t offset);
void ts_tree_retain(ts_tree *tree);
void ts_tree_release(ts_tree *tree);
int ts_tree_equals(const ts_tree *tree1, const ts_tree *tree2);
char * ts_tree_string(const ts_tree *tree, const char **names);
char * ts_tree_error_string(const ts_tree *tree, const char **names);
ts_tree ** ts_tree_children(const ts_tree *tree, size_t *count);
ts_tree ** ts_tree_immediate_children(const ts_tree *tree, size_t *count);
size_t ts_tree_size(const ts_tree *tree);
size_t ts_tree_offset(const ts_tree *tree);
size_t ts_tree_total_size(const ts_tree *tree);
ts_symbol ts_tree_symbol(const ts_tree *tree);

typedef struct {
    void *data;
    const char * (* read_fn)(void *data, size_t *bytes_read);
    int (* seek_fn)(void *data, size_t position);
    void (* release_fn)(void *data);
} ts_input;

typedef struct {
    size_t position;
    size_t bytes_inserted;
    size_t bytes_removed;
} ts_input_edit;

typedef struct {
    const ts_tree * (* parse_fn)(void *data, ts_input input, ts_input_edit *edit);
    void (* free_fn)(void *data);
    const char **symbol_names;
    void *data;
} ts_parser;

const ts_tree * ts_parser_parse(ts_parser *, ts_input, ts_input_edit *edit);
void ts_parser_free(ts_parser *);

typedef struct ts_document ts_document;
ts_document * ts_document_make();
void ts_document_free(ts_document *doc);
void ts_document_set_parser(ts_document *doc, ts_parser parser);
void ts_document_set_input(ts_document *doc, ts_input input);
void ts_document_set_input_string(ts_document *doc, const char *text);
void ts_document_edit(ts_document *doc, ts_input_edit edit);
const ts_tree * ts_document_tree(const ts_document *doc);
const char * ts_document_string(const ts_document *doc);
const char * ts_document_symbol_name(const ts_document *document, const ts_tree *tree);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_RUNTIME_H_
