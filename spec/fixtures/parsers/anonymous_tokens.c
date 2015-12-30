#include "tree_sitter/parser.h"

#define STATE_COUNT 3
#define SYMBOL_COUNT 7

enum {
    sym_program = ts_builtin_sym_start,
    anon_sym_LF,
    anon_sym_CR,
    aux_sym_SLASH_BSLASHd_SLASH,
    anon_sym_DQUOTEhello_DQUOTE,
};

static const char *ts_symbol_names[] = {
    [sym_program] = "program",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [anon_sym_LF] = "\n",
    [anon_sym_CR] = "\r",
    [aux_sym_SLASH_BSLASHd_SLASH] = "/\\d/",
    [anon_sym_DQUOTEhello_DQUOTE] = "\"hello\"",
};

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [sym_program] = {.visible = true, .named = true, .structural = true, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .structural = false, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .structural = true, .extra = false},
    [anon_sym_LF] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_CR] = {.visible = true, .named = false, .structural = true, .extra = false},
    [aux_sym_SLASH_BSLASHd_SLASH] = {.visible = false, .named = false, .structural = true, .extra = false},
    [anon_sym_DQUOTEhello_DQUOTE] = {.visible = true, .named = false, .structural = true, .extra = false},
};

static TSTree *ts_lex(TSLexer *lexer, TSStateId state, bool error_mode) {
    START_LEXER();
    switch (state) {
        case 0:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\r')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 3:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_CR);
        case 4:
            if (lookahead == 'h')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 'e')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'l')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'l')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'o')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(anon_sym_DQUOTEhello_DQUOTE);
        case 11:
            ACCEPT_TOKEN(aux_sym_SLASH_BSLASHd_SLASH);
        case 12:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == ' '))
                ADVANCE(12);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\r')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            LEX_ERROR();
        case 13:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(13);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 12,
    [1] = 13,
    [2] = 13,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = 2,
        [anon_sym_LF] = 4,
        [anon_sym_CR] = 4,
        [aux_sym_SLASH_BSLASHd_SLASH] = 4,
        [anon_sym_DQUOTEhello_DQUOTE] = 4,
    },
    [1] = {
        [ts_builtin_sym_end] = 6,
    },
    [2] = {
        [ts_builtin_sym_end] = 8,
    },
};

static TSParseActionEntry ts_parse_actions[] = {
    [0] = {.count = 1}, ERROR(),
    [2] = {.count = 1}, SHIFT(1, 0),
    [4] = {.count = 1}, SHIFT(2, 0),
    [6] = {.count = 1}, ACCEPT_INPUT(),
    [8] = {.count = 1}, REDUCE(sym_program, 1, 0),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_anonymous_tokens);
