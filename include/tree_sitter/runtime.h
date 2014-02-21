#ifndef tree_sitter_runtime_h
#define tree_sitter_runtime_h

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdlib.h>

typedef struct {
    size_t position;
    char lookahead_char;
    size_t expected_input_count;
    const char **expected_inputs;
} ts_error;

const char * ts_error_string(const ts_error *error);

typedef size_t ts_symbol;
    
typedef struct ts_tree {
    ts_symbol value;
    struct ts_tree **children;
    size_t child_count;
    size_t ref_count;
} ts_tree;

ts_tree * ts_tree_make(ts_symbol value, size_t child_count, ts_tree **children);
void ts_tree_retain(ts_tree *tree);
void ts_tree_release(ts_tree *tree);
int ts_tree_equals(const ts_tree *tree1, const ts_tree *tree2);
char * ts_tree_string(const ts_tree *tree, const char **names);

typedef struct {
    ts_error error;
    ts_tree *tree;
} ts_parse_result;

typedef ts_parse_result ts_parse_fn(const char *);

typedef struct {
    ts_parse_fn *parse_fn;
    const char **symbol_names;
} ts_parse_config;

typedef struct ts_document ts_document;

ts_document * ts_document_make();
void ts_document_free(ts_document *);
void ts_document_set_parser(ts_document *document, ts_parse_config config);
void ts_document_set_text(ts_document *document, const char *text);
ts_tree * ts_document_tree(const ts_document *document);
const char * ts_document_string(const ts_document *document);
    
#ifdef __cplusplus
}
#endif

#endif
