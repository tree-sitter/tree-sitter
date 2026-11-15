#include "tree_sitter/parser.h"

enum TokenType {
    AUTOMATIC_SEMICOLON,
    EMPTY,
};

void *tree_sitter_reuse_zero_width_last_leaf_external_scanner_create(void) {
    return NULL;
}

void tree_sitter_reuse_zero_width_last_leaf_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_reuse_zero_width_last_leaf_external_scanner_serialize(
    void *payload,
    char *buffer
) {
    return 0;
}

void tree_sitter_reuse_zero_width_last_leaf_external_scanner_deserialize(
    void *payload,
    const char *buffer,
    unsigned length
) {}

// A zero-width automatic semicolon when a newline comes right after the previous token. Looking no
// further keeps the next token out of this one's lookahead, so an edit there doesn't touch it.
// After a declaration's terminator, a zero-width `_empty` when the next line starts with a tab; its
// lookahead ends at the tab.
bool tree_sitter_reuse_zero_width_last_leaf_external_scanner_scan(
    void *payload,
    TSLexer *lexer,
    const bool *valid_symbols
) {
    if (lexer->lookahead != '\n') return false;
    lexer->mark_end(lexer);
    if (valid_symbols[AUTOMATIC_SEMICOLON]) {
        lexer->result_symbol = AUTOMATIC_SEMICOLON;
        return true;
    }
    if (!valid_symbols[EMPTY]) return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != '\t') return false;
    lexer->result_symbol = EMPTY;
    return true;
}
