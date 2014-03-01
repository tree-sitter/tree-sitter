#ifndef tree_sitter_runtime_h
#define tree_sitter_runtime_h

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdlib.h>

typedef int ts_symbol;
static const ts_symbol ts_builtin_sym_error = -1;
static const ts_symbol ts_builtin_sym_end = -2;
    
typedef struct ts_tree {
    ts_symbol symbol;
    size_t ref_count;
    union {
        struct {
            size_t count;
            struct ts_tree **contents;
        } children;
        struct {
            char lookahead_char;
            size_t expected_input_count;
            const ts_symbol *expected_inputs;
        } error;
    } data;
} ts_tree;

ts_tree * ts_tree_make_leaf(ts_symbol symbol, size_t size, size_t offset);
ts_tree * ts_tree_make_node(ts_symbol symbol, size_t child_count, ts_tree **children);
ts_tree * ts_tree_make_error(char lookahead_char, size_t expected_input_count, const ts_symbol *expected_inputs, size_t size, size_t offset);
void ts_tree_retain(ts_tree *tree);
void ts_tree_release(ts_tree *tree);
int ts_tree_equals(const ts_tree *tree1, const ts_tree *tree2);
char * ts_tree_string(const ts_tree *tree, const char **names);
char * ts_tree_error_string(const ts_tree *tree, const char **names);
size_t ts_tree_child_count(const ts_tree *tree);
ts_tree ** ts_tree_children(const ts_tree *tree);

typedef const ts_tree * ts_parse_fn(const char *);

typedef struct {
    ts_parse_fn *parse_fn;
    const char **symbol_names;
} ts_parse_config;

typedef struct ts_document ts_document;

ts_document * ts_document_make();
void ts_document_free(ts_document *);
void ts_document_set_parser(ts_document *document, ts_parse_config config);
void ts_document_set_input_string(ts_document *document, const char *text);
const ts_tree * ts_document_tree(const ts_document *document);
const char * ts_document_string(const ts_document *document);
    
#ifdef __cplusplus
}
#endif

#endif
