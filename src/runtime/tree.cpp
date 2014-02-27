#include "tree_sitter/runtime.h"
#include <string>
#include <string.h>

using std::string;
using std::to_string;

ts_tree * ts_tree_make_leaf(ts_symbol symbol) {
    ts_tree *result = new ts_tree();
    result->ref_count = 0;
    result->symbol = symbol;
    result->data.children = {
        .count = 0,
        .contents = NULL
    };
    return result;
}

ts_tree * ts_tree_make_node(ts_symbol symbol, size_t child_count, ts_tree **children) {
    ts_tree *result = new ts_tree();
    result->ref_count = 0;
    result->symbol = symbol;
    result->data.children = {
        .count = child_count,
        .contents = children
    };
    for (int i = 0; i < child_count; i++)
        ts_tree_retain(children[i]);
    return result;
}

ts_tree * ts_tree_make_error(char lookahead_char, size_t expected_input_count, const ts_symbol *expected_inputs) {
    ts_tree *result = new ts_tree();
    result->symbol = ts_builtin_sym_error;
    result->data.error = {
        .lookahead_char = lookahead_char,
        .expected_input_count = expected_input_count,
    };
    return result;
}

void ts_tree_retain(ts_tree *tree) {
    tree->ref_count++;
}

void ts_tree_release(ts_tree *tree) {
    tree->ref_count--;
    if (tree->ref_count == 0) {
        ts_tree **children = tree->data.children.contents;
        for (int i = 0; i < ts_tree_child_count(tree); i++)
            ts_tree_release(children[i]);
//        free(children);
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
        for (int i = 0; i < node1->data.children.count; i++) {
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

static string __tree_to_string(const ts_tree *tree, const char **symbol_names) {
    if (!tree) return "#<null-tree>";
    if (tree->symbol == ts_builtin_sym_error) return "(ERROR)";
    string result = string("(") + symbol_names[tree->symbol];
    for (int i = 0; i < tree->data.children.count; i++)
        result += " " + __tree_to_string(tree->data.children.contents[i], symbol_names);
    return result + ")";
}

char * ts_tree_string(const ts_tree *tree, const char **symbol_names) {
    string value(__tree_to_string(tree, symbol_names));
    char *result = (char *)malloc(value.size());
    strcpy(result, value.c_str());
    return result;
}

char * ts_tree_error_string(const ts_tree *tree, const char **symbol_names) {
    string result = string("Unexpected character '") + tree->data.error.lookahead_char + "'. Expected:";
    for (int i = 0; i < tree->data.error.expected_input_count; i++) {
        ts_symbol symbol = tree->data.error.expected_inputs[i];
        result += string(" ") + symbol_names[symbol];
    }
    
    char *stuff = (char *)malloc(result.size() * sizeof(char));
    strcpy(stuff, result.c_str());
    return stuff;
}
