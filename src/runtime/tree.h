#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#include "tree_sitter/runtime.h"

struct TSTree {
    ts_symbol symbol;
    size_t ref_count;
    size_t offset;
    size_t size;
    int is_extra;
    union {
        struct {
            size_t count;
            size_t immediate_count;
            struct TSTree **contents;
        } children;
        struct {
            char lookahead_char;
            size_t expected_input_count;
            const ts_symbol *expected_inputs;
        } error;
    } data;
};

#endif  // RUNTIME_TREE_H_
