#include "tree_sitter/runtime.h"
#include <string.h>
#include <stdio.h>

struct ts_tree {
    ts_symbol symbol;
    size_t ref_count;
    size_t offset;
    size_t size;
    union {
        struct {
            size_t count;
            size_t immediate_count;
            struct ts_tree **contents;
        } children;
        struct {
            char lookahead_char;
            size_t expected_input_count;
            const ts_symbol *expected_inputs;
        } error;
    } data;
};

static ts_tree * ts_tree_make(ts_symbol symbol, size_t size, size_t offset) {
    ts_tree *result = malloc(sizeof(ts_tree));
    *result = (ts_tree) {
        .ref_count = 1,
        .symbol = symbol,
        .size = size,
        .offset = offset,
    };
    return result;
}

ts_tree * ts_tree_make_leaf(ts_symbol symbol, size_t size, size_t offset) {
    ts_tree *result = ts_tree_make(symbol, size, offset);
    result->data.children.count = 0;
    result->data.children.immediate_count = 0;
    result->data.children.contents = NULL;
    return result;
}

ts_tree * ts_tree_make_node(ts_symbol symbol, size_t child_count, size_t immediate_child_count, ts_tree **children) {
    ts_tree **immediate_children = children + child_count;
    size_t size = 0, offset = 0;
    for (size_t i = 0; i < immediate_child_count; i++) {
        ts_tree *child = immediate_children[i];
        ts_tree_retain(child);
        if (i == 0) {
            offset = ts_tree_offset(child);
            size = ts_tree_size(child);
        } else {
            size += ts_tree_offset(child) + ts_tree_size(child);
        }
    }
    ts_tree *result = ts_tree_make(symbol, size, offset);
    result->data.children.count = child_count;
    result->data.children.immediate_count = immediate_child_count;
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

ts_symbol ts_tree_symbol(const ts_tree *tree) {
    return tree->symbol;
}

void ts_tree_retain(ts_tree *tree) {
    tree->ref_count++;
}

size_t ts_tree_offset(const ts_tree *tree) {
    return tree->offset;
}

size_t ts_tree_size(const ts_tree *tree) {
    return tree->size;
}

size_t ts_tree_total_size(const ts_tree *tree) {
    return ts_tree_offset(tree) + ts_tree_size(tree);
}

ts_tree ** ts_tree_immediate_children(const ts_tree *tree, size_t *count) {
    if (!tree || tree->symbol == ts_builtin_sym_error) {
        if (count) *count = 0;
        return NULL;
    }
    if (count) *count = tree->data.children.immediate_count;
    return tree->data.children.contents + tree->data.children.count;
}

void ts_tree_release(ts_tree *tree) {
    tree->ref_count--;
    if (tree->ref_count == 0) {
        size_t count;
        ts_tree **children = ts_tree_immediate_children(tree, &count);
        for (size_t i = 0; i < count; i++)
            ts_tree_release(children[i]);
        free(tree->data.children.contents);
        free(tree);
    }
}

int ts_tree_equals(const ts_tree *node1, const ts_tree *node2) {
    if (node1->symbol != node2->symbol) return 0;
    if (node1->symbol == ts_builtin_sym_error) {
        // check error equality
    } else {
        size_t count1, count2;
        ts_tree **children1 = ts_tree_children(node1, &count1);
        ts_tree **children2 = ts_tree_children(node2, &count2);
        if (count1 != count2) return 0;
        for (size_t i = 0; i < count1; i++)
            if (!ts_tree_equals(children1[i], children2[i])) return 0;
    }
    return 1;
}

ts_tree ** ts_tree_children(const ts_tree *tree, size_t *count) {
    if (!tree || tree->symbol == ts_builtin_sym_error) {
        if (count) *count = 0;
        return NULL;
    }
    if (count) *count = tree->data.children.count;
    return tree->data.children.contents;
}

static size_t write_lookahead_to_string(char *string, size_t limit, char lookahead) {
    switch (lookahead) {
        case '\0':
            return snprintf(string, limit, "<EOF>");
        default:
            return snprintf(string, limit, "'%c'", lookahead);
    }
}

static size_t tree_write_to_string(const ts_tree *tree, const char **symbol_names, char *string, size_t limit) {
    char *cursor = string;
    char **destination = (limit > 0) ? &cursor : &string;

    if (!tree)
        return snprintf(*destination, limit, "(NULL)");
    if (tree->symbol == ts_builtin_sym_error) {
        cursor += snprintf(*destination, limit, "(ERROR ");
        cursor += write_lookahead_to_string(*destination, limit, tree->data.error.lookahead_char);
        cursor += snprintf(*destination, limit, ")");
        return cursor - string;
    }

    cursor += snprintf(*destination, limit, "(%s", symbol_names[tree->symbol]);
    size_t count;
    ts_tree **children = ts_tree_children(tree, &count);
    for (size_t i = 0; i < count; i++) {
        cursor += snprintf(*destination, limit, " ");
        cursor += tree_write_to_string(children[i], symbol_names, *destination, limit);
    }
    cursor += snprintf(*destination, limit, ")");

    return cursor - string;
}

char * ts_tree_string(const ts_tree *tree, const char **symbol_names) {
    static char SCRATCH_STRING[1];
    size_t size = tree_write_to_string(tree, symbol_names, SCRATCH_STRING, 0) + 1;
    char *result = malloc(size * sizeof(char));
    tree_write_to_string(tree, symbol_names, result, size);
    return result;
}

char * ts_tree_error_string(const ts_tree *tree, const char **symbol_names) {
    return NULL;
}
