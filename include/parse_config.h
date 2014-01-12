#ifndef __tree_sitter_parse_config_h__
#define __tree_sitter_parse_config_h__
#ifdef __cplusplus
extern "C" {
#endif
    
#include "tree.h"

typedef enum {
    TSParseErrorTypeNone,
    TSParseErrorTypeLexical,
    TSParseErrorTypeSyntactic,
} TSParseErrorType;

typedef struct {
    TSParseErrorType type;
    const char **expected_inputs;
    size_t expected_input_count;
    size_t position;
    long lookahead_sym;
} TSParseError;

const char * TSParseErrorToString(const TSParseError *error, const char *input_string, const char **symbol_names);

typedef struct {
    TSParseError error;
    TSTree *tree;
} TSParseResult;

typedef TSParseResult TSParseFn(const char *);

typedef struct {
    TSParseFn *parse_fn;
    const char **symbol_names;
} TSParseConfig;

#ifdef __cplusplus
}
#endif
#endif
