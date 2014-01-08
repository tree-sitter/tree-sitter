#ifndef __tree_sitter_tree_h__
#define __tree_sitter_tree_h__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
typedef size_t TSSymbol;
typedef struct TSTree {
    TSSymbol value;
    struct TSTree **children;
    size_t child_count;
    size_t ref_count;
} TSTree;

TSTree * TSTreeMake(TSSymbol value, size_t child_count, TSTree **children);
void TSTreeRetain(TSTree *tree);
void TSTreeRelease(TSTree *tree);

int TSTreeEquals(const TSTree *tree1, const TSTree *tree2);
char * TSTreeToString(const TSTree *tree, const char **names);
    
#ifdef __cplusplus
}
#endif
#endif
