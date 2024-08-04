#include "tree_sitter/alloc.h"
#include "tree_sitter/parser.h"

#include <string.h>
#include <wctype.h>

enum TokenType {
    EQUALS_BEGIN,
    EQUALS_END,
    DASHES,
};

// FIXME: support different characters
typedef struct {
    uint32_t length;
    wchar_t suffix;
    bool initialized;
} Scanner;

#define MIN_LENGTH 3

#define at_eol(lexer) ((lexer)->lookahead == '\r' || (lexer)->lookahead == '\n')

static inline void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

static inline bool scan(TSLexer *lexer, Scanner *scanner, char chr, int symbol) {
    uint32_t length;

    for (length = 0; !lexer->eof(lexer) && lexer->lookahead == chr; ++length) {
        advance(lexer);
    }

    if (length < MIN_LENGTH) return false;

    for (length = 0; !lexer->eof(lexer) && !at_eol(lexer); ++length) {
        if (symbol == EQUALS_BEGIN && !scanner->initialized)
            scanner->suffix = lexer->lookahead;
        if (scanner->suffix != lexer->lookahead)
            return false;

        advance(lexer);
    }

    if (symbol == EQUALS_BEGIN && !scanner->initialized)
        scanner->length = length;

    if (scanner->length != length) return symbol == DASHES;

    if (lexer->lookahead == '\r') advance(lexer);
    if (lexer->lookahead == '\n') advance(lexer);

    lexer->result_symbol = symbol;
    return true;
}

void *tree_sitter_test_external_scanner_create(void) {
    Scanner *scanner = ts_malloc(sizeof(Scanner));
    scanner->length = 0;
    scanner->suffix = '\0';
    scanner->initialized = false;
    return scanner;
}

unsigned tree_sitter_test_external_scanner_serialize(void *payload, char *buffer) {
    Scanner *scanner = (Scanner *)payload;

    if (scanner->length + 1 > TREE_SITTER_SERIALIZATION_BUFFER_SIZE)
        return 0;

    memset(buffer, true, 1);
    memset(buffer + 1, scanner->suffix, scanner->length);
    return scanner->length + 1;
}

void tree_sitter_test_external_scanner_deserialize(void *payload, const char *buffer, uint32_t length) {
    if (length == 0) return;

    Scanner *scanner = (Scanner *)payload;
    scanner->length = length - 1;
    scanner->suffix = buffer[1];
    scanner->initialized = buffer[0];
}

bool tree_sitter_test_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
    Scanner *scanner = (Scanner *)payload;

    if (valid_symbols[EQUALS_BEGIN])
        return scan(lexer, scanner, '=', EQUALS_BEGIN);

    if (valid_symbols[EQUALS_END])
        return scan(lexer, scanner, '=', EQUALS_END);

    if (valid_symbols[DASHES])
        return scan(lexer, scanner, '-', DASHES);

    return false;
}

void tree_sitter_test_external_scanner_destroy(void *payload) {
    Scanner *scanner = (Scanner *)payload;
    ts_free(scanner);
}
