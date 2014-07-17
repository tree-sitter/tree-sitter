#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#include "tree_sitter/runtime.h"

struct TSTree {
    TSSymbol symbol;
    TSTreeOptions options;
    size_t ref_count;
    size_t offset;
    size_t size;
    union {
        struct {
            size_t child_count;
            struct TSTree **children;
        };
        struct {
            size_t expected_input_count;
            const TSSymbol *expected_inputs;
            char lookahead_char;
        };
    };
};

static inline int ts_tree_is_extra(const TSTree *tree) {
    return (tree->options & TSTreeOptionsExtra);
}

static inline int ts_tree_is_visible(const TSTree *tree) {
    return !(tree->options & TSTreeOptionsHidden);
}

static inline void ts_tree_set_extra(TSTree *tree) {
    tree->options = (TSTreeOptions)(tree->options | TSTreeOptionsExtra);
}

static inline int ts_tree_is_wrapper(const TSTree *tree) {
    return (tree->options & TSTreeOptionsWrapper);
}

#endif  // RUNTIME_TREE_H_
