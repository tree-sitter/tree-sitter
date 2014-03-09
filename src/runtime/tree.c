#include "tree_sitter/runtime.h"
#include <string.h>
#include <stdio.h>

static ts_tree * ts_tree_make(ts_symbol symbol, size_t size, size_t offset) {
    ts_tree *result = (ts_tree *)malloc(sizeof(ts_tree));
    result->ref_count = 1;
    result->symbol = symbol;
    result->size = size;
    result->offset = offset;
    return result;
}

ts_tree * ts_tree_make_leaf(ts_symbol symbol, size_t size, size_t offset) {
    ts_tree *result = ts_tree_make(symbol, size, offset);
    result->data.children.count = 0;
    result->data.children.contents = NULL;
    return result;
}

ts_tree * ts_tree_make_node(ts_symbol symbol, size_t child_count, ts_tree **children, size_t size, size_t offset) {
    for (size_t i = 0; i < child_count; i++)
        ts_tree_retain(children[i]);
    ts_tree *result = ts_tree_make(symbol, size, offset);
    result->data.children.count = child_count;
    result->data.children.contents = children;
    return result;
}

ts_tree * ts_tree_make_error(char lookahead_char, size_t expected_input_count, const ts_symbol *expected_inputs, size_t size, size_t offset) {
    ts_tree *result = ts_tree_make(ts_builtin_sym_error, size, offset);
    result->data.error.lookahead_char = lookahead_char;
    result->data.error.expected_input_count = expected_input_count;
    result->data.error.expected_inputs = expected_inputs;
    return result;
}

void ts_tree_retain(ts_tree *tree) {
    tree->ref_count++;
}

void ts_tree_release(ts_tree *tree) {
    tree->ref_count--;
    if (tree->ref_count == 0) {
        ts_tree **children = ts_tree_children(tree);
        if (children) {
            for (size_t i = 0; i < ts_tree_child_count(tree); i++)
                ts_tree_release(children[i]);
            free(children);
        }
        free(tree);
    }
}

int ts_tree_equals(const ts_tree *node1, const ts_tree *node2) {
    if (node1->symbol != node2->symbol) return 0;
    if (node1->symbol == ts_builtin_sym_error) {
        // check error equality
    } else {
        if (node1->data.children.count != node2->data.children.count)
            return 0;
        for (size_t i = 0; i < node1->data.children.count; i++) {
            ts_tree *child1 = node1->data.children.contents[i];
            ts_tree *child2 = node2->data.children.contents[i];
            if (!ts_tree_equals(child1, child2))
                return 0;
        }
    }
    return 1;
}

ts_tree ** ts_tree_children(const ts_tree *tree) {
    if (tree->symbol == ts_builtin_sym_error) return NULL;
    return tree->data.children.contents;
}

size_t ts_tree_child_count(const ts_tree *tree) {
    if (tree->symbol == ts_builtin_sym_error) return 0;
    return tree->data.children.count;
}

static const char *NULL_TREE_STRING = "(NULL)";
static const char *ERROR_TREE_STRING = "(ERROR)";

static size_t tree_write_to_string(const ts_tree *tree, const char **symbol_names, char *string, size_t limit) {
    if (!tree)
        return snprintf(string, limit, "%s", NULL_TREE_STRING);
    if (tree->symbol == ts_builtin_sym_error)
        return snprintf(string, limit, "%s", ERROR_TREE_STRING);
    
    size_t result = snprintf(string, limit, "(%s", symbol_names[tree->symbol]);
    char *cursor = string + result;
    for (size_t i = 0; i < tree->data.children.count; i++) {
        ts_tree *child = tree->data.children.contents[i];
        result += snprintf(cursor, limit, " ");
        result += tree_write_to_string(child, symbol_names, cursor + 1, limit);
        cursor = (limit > 0) ? string + result : string;
    }
    
    return result + snprintf(cursor, limit, ")");
}

static char SCRATCH_STRING[1];

char * ts_tree_string(const ts_tree *tree, const char **symbol_names) {
    size_t size = tree_write_to_string(tree, symbol_names, SCRATCH_STRING, 0) + 1;
    char *result = malloc(size * sizeof(char));
    tree_write_to_string(tree, symbol_names, result, size);
    return result;
}

char * ts_tree_error_string(const ts_tree *tree, const char **symbol_names) {
    return NULL;
}
