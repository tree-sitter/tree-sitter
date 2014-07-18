#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "tree_sitter/parser.h"

struct TSNode {
    size_t ref_count;
    size_t position;
    size_t index;
    const TSTree *content;
    struct TSNode *parent;
    TSParserConfig *config;
};

TSNode * ts_node_make(TSTree *tree, TSNode *parent, size_t position, TSParserConfig *config);

#endif
