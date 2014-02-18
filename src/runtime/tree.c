#include "tree_sitter/runtime.h"
#include <stdio.h>
#include <string.h>

TSTree * TSTreeMake(TSSymbol value, size_t child_count, TSTree **children) {
    TSTree *result = malloc(sizeof(TSTree));
    result->value = value;
    result->child_count = child_count;
    result->children = children;
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

char * TSTreeWriteToString(const TSTree *tree, const char **symbol_names, char *string) {
    if (!tree) {
        sprintf(string, "#<null tree>");
    }
    char *result = string;
    const char *name = symbol_names[tree->value];
    sprintf(result, "(%s", name);
    result += strlen(name) + 1;
    for (int i = 0; i < tree->child_count; i++) {
        result[0] = ' ';
        result++;
        result = TSTreeWriteToString(tree->children[i], symbol_names, result);
    }
    result[0] = ')';
    result++;
    return result;
}

char * TSTreeToString(const TSTree *tree, const char **symbol_names) {
    char *string = calloc(200, sizeof(char));
    TSTreeWriteToString(tree, symbol_names, string);
    return string;
}
