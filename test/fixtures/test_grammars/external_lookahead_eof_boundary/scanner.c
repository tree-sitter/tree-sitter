#include "tree_sitter/parser.h"

enum {
    OPEN_DELIM,
    CLOSE_DELIM,
    UNCLOSED_DELIM,
};

void *tree_sitter_external_lookahead_eof_boundary_external_scanner_create(void) { return NULL; }

void tree_sitter_external_lookahead_eof_boundary_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_external_lookahead_eof_boundary_external_scanner_serialize(
    void *payload, char *buffer
) {
    return 0;
}

void tree_sitter_external_lookahead_eof_boundary_external_scanner_deserialize(
    void *payload, const char *buffer, unsigned length
) {}

bool tree_sitter_external_lookahead_eof_boundary_external_scanner_scan(
    void *payload, TSLexer *lexer, const bool *valid_symbols
) {
    if (lexer->lookahead != '`') return false;

    lexer->advance(lexer, false);
    lexer->mark_end(lexer);

    // Mid-span: emit the closer.
    if (valid_symbols[CLOSE_DELIM]) {
        lexer->result_symbol = CLOSE_DELIM;
        return true;
    }

    // At an opener: peek past mark_end for a matching '`'. The eof()
    // probe makes the result depend on the current included ranges.
    if (valid_symbols[OPEN_DELIM]) {
        while (!lexer->eof(lexer)) {
            if (lexer->lookahead == '`') {
                lexer->result_symbol = OPEN_DELIM;
                return true;
            }
            lexer->advance(lexer, false);
        }
        if (valid_symbols[UNCLOSED_DELIM]) {
            lexer->result_symbol = UNCLOSED_DELIM;
            return true;
        }
    }

    return false;
}
