#include "tree_sitter/parser.h"

#define STATE_COUNT 69
#define SYMBOL_COUNT 18

enum {
    sym__value = ts_builtin_sym_start,
    sym_object,
    sym_array,
    aux_sym_object_repeat1,
    aux_sym_array_repeat1,
    anon_sym_LBRACE,
    anon_sym_COLON,
    anon_sym_COMMA,
    anon_sym_RBRACE,
    anon_sym_LBRACK,
    anon_sym_RBRACK,
    sym_string,
    sym_number,
    sym_null,
    sym_true,
    sym_false,
};

static const char *ts_symbol_names[] = {
    [sym__value] = "_value",
    [sym_object] = "object",
    [sym_array] = "array",
    [aux_sym_object_repeat1] = "object_repeat1",
    [aux_sym_array_repeat1] = "array_repeat1",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [anon_sym_LBRACE] = "{",
    [anon_sym_COLON] = ":",
    [anon_sym_COMMA] = ",",
    [anon_sym_RBRACE] = "}",
    [anon_sym_LBRACK] = "[",
    [anon_sym_RBRACK] = "]",
    [sym_string] = "string",
    [sym_number] = "number",
    [sym_null] = "null",
    [sym_true] = "true",
    [sym_false] = "false",
};

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [sym__value] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_object] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_array] = {.visible = true, .named = true, .structural = true, .extra = false},
    [aux_sym_object_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_array_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .structural = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .structural = true, .extra = false},
    [anon_sym_LBRACE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_COLON] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_COMMA] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RBRACE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LBRACK] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RBRACK] = {.visible = true, .named = false, .structural = true, .extra = false},
    [sym_string] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_number] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_null] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_true] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_false] = {.visible = true, .named = true, .structural = true, .extra = false},
};

static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state) {
    START_LEXER();
    switch (lex_state) {
        case 1:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            LEX_ERROR();
        case 2:
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(sym_string);
        case 4:
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            LEX_ERROR();
        case 5:
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            ACCEPT_TOKEN(sym_string);
        case 6:
            if (lookahead == '.')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            ACCEPT_TOKEN(sym_number);
        case 7:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            ACCEPT_TOKEN(sym_number);
        case 9:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 10:
            if (lookahead == 'a')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'l')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 's')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 'e')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(sym_false);
        case 15:
            if (lookahead == 'u')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'l')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'l')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            ACCEPT_TOKEN(sym_null);
        case 19:
            if (lookahead == 'r')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (lookahead == 'u')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 'e')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            ACCEPT_TOKEN(sym_true);
        case 23:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 24:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(24);
            LEX_ERROR();
        case 25:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 26:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(26);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 28:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(28);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 30:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(30);
            if (lookahead == ',')
                ADVANCE(31);
            if (lookahead == ']')
                ADVANCE(29);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 32:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(29);
            LEX_ERROR();
        case 33:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == ',')
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 34:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(34);
            if (lookahead == ':')
                ADVANCE(35);
            LEX_ERROR();
        case 35:
            ACCEPT_TOKEN(anon_sym_COLON);
        case 36:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 37:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '\"')
                ADVANCE(2);
            LEX_ERROR();
        case 38:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(35);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(35);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 24,
    [2] = 24,
    [3] = 26,
    [4] = 28,
    [5] = 30,
    [6] = 30,
    [7] = 26,
    [8] = 28,
    [9] = 24,
    [10] = 30,
    [11] = 30,
    [12] = 32,
    [13] = 1,
    [14] = 30,
    [15] = 30,
    [16] = 32,
    [17] = 30,
    [18] = 33,
    [19] = 30,
    [20] = 34,
    [21] = 1,
    [22] = 33,
    [23] = 33,
    [24] = 26,
    [25] = 28,
    [26] = 30,
    [27] = 33,
    [28] = 32,
    [29] = 33,
    [30] = 33,
    [31] = 33,
    [32] = 33,
    [33] = 34,
    [34] = 1,
    [35] = 33,
    [36] = 36,
    [37] = 37,
    [38] = 33,
    [39] = 33,
    [40] = 34,
    [41] = 1,
    [42] = 33,
    [43] = 36,
    [44] = 36,
    [45] = 33,
    [46] = 36,
    [47] = 33,
    [48] = 33,
    [49] = 36,
    [50] = 30,
    [51] = 30,
    [52] = 36,
    [53] = 30,
    [54] = 30,
    [55] = 32,
    [56] = 24,
    [57] = 24,
    [58] = 33,
    [59] = 24,
    [60] = 34,
    [61] = 1,
    [62] = 33,
    [63] = 36,
    [64] = 24,
    [65] = 24,
    [66] = 36,
    [67] = 24,
    [68] = 24,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym__value] = 2,
        [sym_object] = 4,
        [sym_array] = 4,
        [anon_sym_LBRACE] = 6,
        [anon_sym_LBRACK] = 8,
        [sym_string] = 4,
        [sym_number] = 4,
        [sym_null] = 4,
        [sym_true] = 4,
        [sym_false] = 4,
    },
    [1] = {
        [ts_builtin_sym_end] = 10,
    },
    [2] = {
        [ts_builtin_sym_end] = 12,
    },
    [3] = {
        [ts_builtin_sym_error] = 14,
        [anon_sym_RBRACE] = 16,
        [sym_string] = 18,
    },
    [4] = {
        [sym__value] = 20,
        [sym_object] = 22,
        [sym_array] = 22,
        [ts_builtin_sym_error] = 20,
        [anon_sym_LBRACE] = 24,
        [anon_sym_LBRACK] = 26,
        [anon_sym_RBRACK] = 28,
        [sym_string] = 22,
        [sym_number] = 22,
        [sym_null] = 22,
        [sym_true] = 22,
        [sym_false] = 22,
    },
    [5] = {
        [aux_sym_array_repeat1] = 30,
        [anon_sym_COMMA] = 32,
        [anon_sym_RBRACK] = 34,
    },
    [6] = {
        [aux_sym_array_repeat1] = 12,
        [anon_sym_COMMA] = 12,
        [anon_sym_RBRACK] = 12,
    },
    [7] = {
        [ts_builtin_sym_error] = 36,
        [anon_sym_RBRACE] = 38,
        [sym_string] = 40,
    },
    [8] = {
        [sym__value] = 42,
        [sym_object] = 22,
        [sym_array] = 22,
        [ts_builtin_sym_error] = 42,
        [anon_sym_LBRACE] = 24,
        [anon_sym_LBRACK] = 26,
        [anon_sym_RBRACK] = 44,
        [sym_string] = 22,
        [sym_number] = 22,
        [sym_null] = 22,
        [sym_true] = 22,
        [sym_false] = 22,
    },
    [9] = {
        [ts_builtin_sym_end] = 46,
    },
    [10] = {
        [aux_sym_array_repeat1] = 48,
        [anon_sym_COMMA] = 32,
        [anon_sym_RBRACK] = 50,
    },
    [11] = {
        [aux_sym_array_repeat1] = 46,
        [anon_sym_COMMA] = 46,
        [anon_sym_RBRACK] = 46,
    },
    [12] = {
        [anon_sym_RBRACK] = 52,
    },
    [13] = {
        [sym__value] = 54,
        [sym_object] = 22,
        [sym_array] = 22,
        [ts_builtin_sym_error] = 54,
        [anon_sym_LBRACE] = 24,
        [anon_sym_LBRACK] = 26,
        [sym_string] = 22,
        [sym_number] = 22,
        [sym_null] = 22,
        [sym_true] = 22,
        [sym_false] = 22,
    },
    [14] = {
        [aux_sym_array_repeat1] = 56,
        [anon_sym_COMMA] = 56,
        [anon_sym_RBRACK] = 56,
    },
    [15] = {
        [aux_sym_array_repeat1] = 58,
        [anon_sym_COMMA] = 32,
        [anon_sym_RBRACK] = 60,
    },
    [16] = {
        [anon_sym_RBRACK] = 62,
    },
    [17] = {
        [aux_sym_array_repeat1] = 64,
        [anon_sym_COMMA] = 64,
        [anon_sym_RBRACK] = 64,
    },
    [18] = {
        [aux_sym_object_repeat1] = 66,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 70,
    },
    [19] = {
        [aux_sym_array_repeat1] = 72,
        [anon_sym_COMMA] = 72,
        [anon_sym_RBRACK] = 72,
    },
    [20] = {
        [anon_sym_COLON] = 74,
    },
    [21] = {
        [sym__value] = 76,
        [sym_object] = 78,
        [sym_array] = 78,
        [anon_sym_LBRACE] = 80,
        [anon_sym_LBRACK] = 82,
        [sym_string] = 78,
        [sym_number] = 78,
        [sym_null] = 78,
        [sym_true] = 78,
        [sym_false] = 78,
    },
    [22] = {
        [aux_sym_object_repeat1] = 84,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 86,
    },
    [23] = {
        [aux_sym_object_repeat1] = 12,
        [anon_sym_COMMA] = 12,
        [anon_sym_RBRACE] = 12,
    },
    [24] = {
        [ts_builtin_sym_error] = 88,
        [anon_sym_RBRACE] = 90,
        [sym_string] = 92,
    },
    [25] = {
        [sym__value] = 94,
        [sym_object] = 22,
        [sym_array] = 22,
        [ts_builtin_sym_error] = 94,
        [anon_sym_LBRACE] = 24,
        [anon_sym_LBRACK] = 26,
        [anon_sym_RBRACK] = 96,
        [sym_string] = 22,
        [sym_number] = 22,
        [sym_null] = 22,
        [sym_true] = 22,
        [sym_false] = 22,
    },
    [26] = {
        [aux_sym_array_repeat1] = 98,
        [anon_sym_COMMA] = 32,
        [anon_sym_RBRACK] = 100,
    },
    [27] = {
        [aux_sym_object_repeat1] = 46,
        [anon_sym_COMMA] = 46,
        [anon_sym_RBRACE] = 46,
    },
    [28] = {
        [anon_sym_RBRACK] = 102,
    },
    [29] = {
        [aux_sym_object_repeat1] = 56,
        [anon_sym_COMMA] = 56,
        [anon_sym_RBRACE] = 56,
    },
    [30] = {
        [aux_sym_object_repeat1] = 64,
        [anon_sym_COMMA] = 64,
        [anon_sym_RBRACE] = 64,
    },
    [31] = {
        [aux_sym_object_repeat1] = 104,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 106,
    },
    [32] = {
        [aux_sym_object_repeat1] = 72,
        [anon_sym_COMMA] = 72,
        [anon_sym_RBRACE] = 72,
    },
    [33] = {
        [anon_sym_COLON] = 108,
    },
    [34] = {
        [sym__value] = 110,
        [sym_object] = 78,
        [sym_array] = 78,
        [anon_sym_LBRACE] = 80,
        [anon_sym_LBRACK] = 82,
        [sym_string] = 78,
        [sym_number] = 78,
        [sym_null] = 78,
        [sym_true] = 78,
        [sym_false] = 78,
    },
    [35] = {
        [aux_sym_object_repeat1] = 112,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 114,
    },
    [36] = {
        [anon_sym_RBRACE] = 116,
    },
    [37] = {
        [ts_builtin_sym_error] = 118,
        [sym_string] = 120,
    },
    [38] = {
        [aux_sym_object_repeat1] = 122,
        [anon_sym_COMMA] = 122,
        [anon_sym_RBRACE] = 122,
    },
    [39] = {
        [aux_sym_object_repeat1] = 124,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 126,
    },
    [40] = {
        [anon_sym_COLON] = 128,
    },
    [41] = {
        [sym__value] = 130,
        [sym_object] = 78,
        [sym_array] = 78,
        [anon_sym_LBRACE] = 80,
        [anon_sym_LBRACK] = 82,
        [sym_string] = 78,
        [sym_number] = 78,
        [sym_null] = 78,
        [sym_true] = 78,
        [sym_false] = 78,
    },
    [42] = {
        [aux_sym_object_repeat1] = 132,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 134,
    },
    [43] = {
        [anon_sym_RBRACE] = 136,
    },
    [44] = {
        [anon_sym_RBRACE] = 138,
    },
    [45] = {
        [aux_sym_object_repeat1] = 140,
        [anon_sym_COMMA] = 140,
        [anon_sym_RBRACE] = 140,
    },
    [46] = {
        [anon_sym_RBRACE] = 142,
    },
    [47] = {
        [aux_sym_object_repeat1] = 144,
        [anon_sym_COMMA] = 144,
        [anon_sym_RBRACE] = 144,
    },
    [48] = {
        [aux_sym_object_repeat1] = 146,
        [anon_sym_COMMA] = 146,
        [anon_sym_RBRACE] = 146,
    },
    [49] = {
        [anon_sym_RBRACE] = 148,
    },
    [50] = {
        [aux_sym_array_repeat1] = 122,
        [anon_sym_COMMA] = 122,
        [anon_sym_RBRACK] = 122,
    },
    [51] = {
        [aux_sym_array_repeat1] = 140,
        [anon_sym_COMMA] = 140,
        [anon_sym_RBRACK] = 140,
    },
    [52] = {
        [anon_sym_RBRACE] = 150,
    },
    [53] = {
        [aux_sym_array_repeat1] = 144,
        [anon_sym_COMMA] = 144,
        [anon_sym_RBRACK] = 144,
    },
    [54] = {
        [aux_sym_array_repeat1] = 146,
        [anon_sym_COMMA] = 146,
        [anon_sym_RBRACK] = 146,
    },
    [55] = {
        [anon_sym_RBRACK] = 152,
    },
    [56] = {
        [ts_builtin_sym_end] = 56,
    },
    [57] = {
        [ts_builtin_sym_end] = 64,
    },
    [58] = {
        [aux_sym_object_repeat1] = 154,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 156,
    },
    [59] = {
        [ts_builtin_sym_end] = 72,
    },
    [60] = {
        [anon_sym_COLON] = 158,
    },
    [61] = {
        [sym__value] = 160,
        [sym_object] = 78,
        [sym_array] = 78,
        [anon_sym_LBRACE] = 80,
        [anon_sym_LBRACK] = 82,
        [sym_string] = 78,
        [sym_number] = 78,
        [sym_null] = 78,
        [sym_true] = 78,
        [sym_false] = 78,
    },
    [62] = {
        [aux_sym_object_repeat1] = 162,
        [anon_sym_COMMA] = 68,
        [anon_sym_RBRACE] = 164,
    },
    [63] = {
        [anon_sym_RBRACE] = 166,
    },
    [64] = {
        [ts_builtin_sym_end] = 122,
    },
    [65] = {
        [ts_builtin_sym_end] = 140,
    },
    [66] = {
        [anon_sym_RBRACE] = 168,
    },
    [67] = {
        [ts_builtin_sym_end] = 144,
    },
    [68] = {
        [ts_builtin_sym_end] = 146,
    },
};

static TSParseActionEntry ts_parse_actions[] = {
    [0] = {.count = 1}, ERROR(),
    [2] = {.count = 1}, SHIFT(1, 0),
    [4] = {.count = 1}, SHIFT(2, 0),
    [6] = {.count = 1}, SHIFT(3, 0),
    [8] = {.count = 1}, SHIFT(4, 0),
    [10] = {.count = 1}, ACCEPT_INPUT(),
    [12] = {.count = 1}, REDUCE(sym__value, 1, 0),
    [14] = {.count = 1}, SHIFT(58, 0),
    [16] = {.count = 1}, SHIFT(59, 0),
    [18] = {.count = 1}, SHIFT(60, 0),
    [20] = {.count = 1}, SHIFT(5, 0),
    [22] = {.count = 1}, SHIFT(6, 0),
    [24] = {.count = 1}, SHIFT(7, 0),
    [26] = {.count = 1}, SHIFT(8, 0),
    [28] = {.count = 1}, SHIFT(9, 0),
    [30] = {.count = 1}, SHIFT(55, 0),
    [32] = {.count = 1}, SHIFT(13, 0),
    [34] = {.count = 1}, SHIFT(56, 0),
    [36] = {.count = 1}, SHIFT(18, 0),
    [38] = {.count = 1}, SHIFT(19, 0),
    [40] = {.count = 1}, SHIFT(20, 0),
    [42] = {.count = 1}, SHIFT(10, 0),
    [44] = {.count = 1}, SHIFT(11, 0),
    [46] = {.count = 1}, REDUCE(sym_array, 2, 0),
    [48] = {.count = 1}, SHIFT(12, 0),
    [50] = {.count = 1}, SHIFT(14, 0),
    [52] = {.count = 1}, SHIFT(17, 0),
    [54] = {.count = 1}, SHIFT(15, 0),
    [56] = {.count = 1}, REDUCE(sym_array, 3, 0),
    [58] = {.count = 1}, SHIFT(16, 0),
    [60] = {.count = 1}, REDUCE(aux_sym_array_repeat1, 2, 0),
    [62] = {.count = 1}, REDUCE(aux_sym_array_repeat1, 3, 0),
    [64] = {.count = 1}, REDUCE(sym_array, 4, 0),
    [66] = {.count = 1}, SHIFT(52, 0),
    [68] = {.count = 1}, SHIFT(37, 0),
    [70] = {.count = 1}, SHIFT(53, 0),
    [72] = {.count = 1}, REDUCE(sym_object, 2, 0),
    [74] = {.count = 1}, SHIFT(21, 0),
    [76] = {.count = 1}, SHIFT(22, 0),
    [78] = {.count = 1}, SHIFT(23, 0),
    [80] = {.count = 1}, SHIFT(24, 0),
    [82] = {.count = 1}, SHIFT(25, 0),
    [84] = {.count = 1}, SHIFT(49, 0),
    [86] = {.count = 1}, SHIFT(50, 0),
    [88] = {.count = 1}, SHIFT(31, 0),
    [90] = {.count = 1}, SHIFT(32, 0),
    [92] = {.count = 1}, SHIFT(33, 0),
    [94] = {.count = 1}, SHIFT(26, 0),
    [96] = {.count = 1}, SHIFT(27, 0),
    [98] = {.count = 1}, SHIFT(28, 0),
    [100] = {.count = 1}, SHIFT(29, 0),
    [102] = {.count = 1}, SHIFT(30, 0),
    [104] = {.count = 1}, SHIFT(46, 0),
    [106] = {.count = 1}, SHIFT(47, 0),
    [108] = {.count = 1}, SHIFT(34, 0),
    [110] = {.count = 1}, SHIFT(35, 0),
    [112] = {.count = 1}, SHIFT(36, 0),
    [114] = {.count = 1}, SHIFT(38, 0),
    [116] = {.count = 1}, SHIFT(45, 0),
    [118] = {.count = 1}, SHIFT(39, 0),
    [120] = {.count = 1}, SHIFT(40, 0),
    [122] = {.count = 1}, REDUCE(sym_object, 5, 0),
    [124] = {.count = 1}, SHIFT(44, 0),
    [126] = {.count = 1}, REDUCE(aux_sym_object_repeat1, 2, 0),
    [128] = {.count = 1}, SHIFT(41, 0),
    [130] = {.count = 1}, SHIFT(42, 0),
    [132] = {.count = 1}, SHIFT(43, 0),
    [134] = {.count = 1}, REDUCE(aux_sym_object_repeat1, 4, 0),
    [136] = {.count = 1}, REDUCE(aux_sym_object_repeat1, 5, 0),
    [138] = {.count = 1}, REDUCE(aux_sym_object_repeat1, 3, 0),
    [140] = {.count = 1}, REDUCE(sym_object, 6, 0),
    [142] = {.count = 1}, SHIFT(48, 0),
    [144] = {.count = 1}, REDUCE(sym_object, 3, 0),
    [146] = {.count = 1}, REDUCE(sym_object, 4, 0),
    [148] = {.count = 1}, SHIFT(51, 0),
    [150] = {.count = 1}, SHIFT(54, 0),
    [152] = {.count = 1}, SHIFT(57, 0),
    [154] = {.count = 1}, SHIFT(66, 0),
    [156] = {.count = 1}, SHIFT(67, 0),
    [158] = {.count = 1}, SHIFT(61, 0),
    [160] = {.count = 1}, SHIFT(62, 0),
    [162] = {.count = 1}, SHIFT(63, 0),
    [164] = {.count = 1}, SHIFT(64, 0),
    [166] = {.count = 1}, SHIFT(65, 0),
    [168] = {.count = 1}, SHIFT(68, 0),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_json);
