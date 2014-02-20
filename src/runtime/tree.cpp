#include "tree_sitter/runtime.h"
#include <string>
#include <string.h>

using std::string;

TSTree * TSTreeMake(TSSymbol value, size_t child_count, TSTree **children) {
    TSTree *result = new TSTree();
    result->value = value;
    result->child_count = child_count;
    result->children = children;
    result->ref_count = 0;
    for (int i = 0; i < child_count; i++)
        TSTreeRetain(children[i]);
    return result;
}

void TSTreeRetain(TSTree *tree) {
    tree->ref_count++;
}

void TSTreeRelease(TSTree *tree) {
    tree->ref_count--;
    if (tree->ref_count == 0) {
        for (int i = 0; i < tree->child_count; i++)
            TSTreeRelease(tree->children[i]);
        free(tree);
    }
}

int TSTreeEquals(const TSTree *node1, const TSTree *node2) {
    if (node1->value != node2->value) return 0;
    if (node1->child_count != node2->child_count) return 0;
    for (int i = 0; i < node1->child_count; i++) {
        TSTree *child1 = node1->children[i];
        TSTree *child2 = node2->children[i];
        if (!TSTreeEquals(child1, child2)) return 0;
    }
    return 1;
}

static string __tree_to_string(const TSTree *tree, const char **symbol_names) {
    if (!tree) return "#<null-tree>";
    string result = string("(") + symbol_names[tree->value];
    for (int i = 0; i < tree->child_count; i++)
        result += " " + __tree_to_string(tree->children[i], symbol_names);
    return result + ")";
}

char * TSTreeToString(const TSTree *tree, const char **symbol_names) {
    string value(__tree_to_string(tree, symbol_names));
    char *result = (char *)malloc(value.size());
    strcpy(result, value.c_str());
    return result;
}
