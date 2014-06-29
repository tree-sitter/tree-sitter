#ifndef TREE_SITTER_PARSER_LEXER_H_
#define TREE_SITTER_PARSER_LEXER_H_

#include "tree_sitter/runtime.h"

#define ts_lex_state_error 0

typedef struct {
    TSInput input;
    const char *chunk;
    size_t chunk_start;
    size_t chunk_size;
    size_t position_in_chunk;
    size_t token_end_position;
    size_t token_start_position;
    int reached_end;
} ts_lexer;

static inline ts_lexer ts_lexer_make() {
    ts_lexer result;
    result.chunk = NULL;
    result.chunk_start = 0;
    result.chunk_size = 0;
    result.position_in_chunk = 0;
    result.token_start_position = 0;
    result.token_end_position = 0;
    result.reached_end = 0;
    return result;
}

static inline size_t ts_lexer_position(const ts_lexer *lexer) {
    return lexer->chunk_start + lexer->position_in_chunk;
}

static inline char ts_lexer_lookahead_char(const ts_lexer *lexer) {
    return lexer->chunk[lexer->position_in_chunk];
}

static inline int ts_lexer_advance(ts_lexer *lexer) {
    static const char *empty_chunk = "";
    if (lexer->position_in_chunk + 1 < lexer->chunk_size) {
        lexer->position_in_chunk++;
    } else {
        lexer->chunk_start += lexer->chunk_size;
        lexer->chunk = lexer->input.read_fn(lexer->input.data, &lexer->chunk_size);
        lexer->position_in_chunk = 0;
        if (lexer->reached_end) {
            return 0;
        }
        if (lexer->chunk_size == 0) {
            lexer->reached_end = 1;
            lexer->chunk = empty_chunk;
        }
    }
    return 1;
}

static inline void ts_lexer_start_token(ts_lexer *lexer) {
    lexer->token_start_position = ts_lexer_position(lexer);
}

static inline TSTree * ts_lexer_build_node(ts_lexer *lexer, TSSymbol symbol) {
    size_t current_position = ts_lexer_position(lexer);
    size_t size = current_position - lexer->token_start_position;
    size_t offset = lexer->token_start_position - lexer->token_end_position;
    lexer->token_end_position = current_position;
    return ts_tree_make_leaf(symbol, size, offset);
}

#endif
