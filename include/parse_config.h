#ifndef __tree_sitter_parse_config_h__
#define __tree_sitter_parse_config_h__

#include "tree.h"

typedef struct {
    const char *message;
    size_t position;
} TSParseError;

typedef struct {
    TSParseError error;
    TSTree *tree;
} TSParseResult;

typedef TSParseResult TSParseFn(const char *);

typedef struct {
    TSParseFn *parse_fn;
    const char **symbol_names;
} TSParseConfig;

#endif
