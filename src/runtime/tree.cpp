#include "tree_sitter/runtime.h"
#include <string>
#include <string.h>

using std::string;

ts_tree * ts_tree_make(ts_symbol value, size_t child_count, ts_tree **children) {
    ts_tree *result = new ts_tree();
    result->value = value;
    result->child_count = child_count;
    result->children = children;
    result->ref_count = 0;
    for (int i = 0; i < child_count; i++)
        ts_tree_retain(children[i]);
    return result;
}

void ts_tree_retain(ts_tree *tree) {
    tree->ref_count++;
}

void ts_tree_release(ts_tree *tree) {
    tree->ref_count--;
    if (tree->ref_count == 0) {
        for (int i = 0; i < tree->child_count; i++)
            ts_tree_release(tree->children[i]);
        free(tree);
    }
}

int ts_tree_equals(const ts_tree *node1, const ts_tree *node2) {
    if (node1->value != node2->value) return 0;
    if (node1->child_count != node2->child_count) return 0;
    for (int i = 0; i < node1->child_count; i++) {
        ts_tree *child1 = node1->children[i];
        ts_tree *child2 = node2->children[i];
        if (!ts_tree_equals(child1, child2)) return 0;
    }
    return 1;
}

static string __tree_to_string(const ts_tree *tree, const char **symbol_names) {
    if (!tree) return "#<null-tree>";
    string result = string("(") + symbol_names[tree->value];
    for (int i = 0; i < tree->child_count; i++)
        result += " " + __tree_to_string(tree->children[i], symbol_names);
    return result + ")";
}

char * ts_tree_string(const ts_tree *tree, const char **symbol_names) {
    string value(__tree_to_string(tree, symbol_names));
    char *result = (char *)malloc(value.size());
    strcpy(result, value.c_str());
    return result;
}
