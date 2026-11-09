#include "tree_sitter/parser.h"

enum {
    NEWLINE,
    BANG,
};

void *tree_sitter_reuse_before_extra_non_terminal_external_scanner_create(void) { return NULL; }

void tree_sitter_reuse_before_extra_non_terminal_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_reuse_before_extra_non_terminal_external_scanner_serialize(
    void *payload, char *buffer
) {
    return 0;
}

void tree_sitter_reuse_before_extra_non_terminal_external_scanner_deserialize(
    void *payload, const char *buffer, unsigned length
) {}

bool tree_sitter_reuse_before_extra_non_terminal_external_scanner_scan(
    void *payload, TSLexer *lexer, const bool *valid_symbols
) {
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
        lexer->advance(lexer, true);
    }

    // A newline is a token only where one is valid, elsewhere it's whitespace.
    if (valid_symbols[NEWLINE] && lexer->lookahead == '\n') {
        lexer->advance(lexer, false);
        lexer->result_symbol = NEWLINE;
        return true;
    }

    if (valid_symbols[BANG] && lexer->lookahead == '!') {
        lexer->advance(lexer, false);
        lexer->result_symbol = BANG;
        return true;
    }

    return false;
}
