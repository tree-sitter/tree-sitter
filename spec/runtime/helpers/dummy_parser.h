#ifndef HELPERS_DUMMY_PARSER_H_
#define HELPERS_DUMMY_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser/lr_parser.h"

enum {
    dummy_sym1 = 2,
    dummy_sym2 = 3,
    dummy_sym3 = 4,
};

struct test_parser {
    size_t state_count;
    size_t symbol_count;
    const TSParseAction **parse_table;
    const TSStateId *lex_states;
    const int *hidden_symbols;
};

extern struct test_parser dummy_parser;

#ifdef __cplusplus
}
#endif

#endif  // HELPERS_DUMMY_PARSER_H_
