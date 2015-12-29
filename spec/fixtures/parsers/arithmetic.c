#include "tree_sitter/parser.h"

#define STATE_COUNT 33
#define SYMBOL_COUNT 20

enum {
    sym_program = ts_builtin_sym_start,
    sym__expression,
    sym_sum,
    sym_difference,
    sym_product,
    sym_quotient,
    sym_exponent,
    sym_group,
    anon_sym_PLUS,
    anon_sym_DASH,
    anon_sym_STAR,
    anon_sym_SLASH,
    anon_sym_CARET,
    anon_sym_LPAREN,
    anon_sym_RPAREN,
    sym_number,
    sym_variable,
    sym_comment,
};

static const char *ts_symbol_names[] = {
    [sym_program] = "program",
    [sym__expression] = "_expression",
    [sym_sum] = "sum",
    [sym_difference] = "difference",
    [sym_product] = "product",
    [sym_quotient] = "quotient",
    [sym_exponent] = "exponent",
    [sym_group] = "group",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [anon_sym_PLUS] = "+",
    [anon_sym_DASH] = "-",
    [anon_sym_STAR] = "*",
    [anon_sym_SLASH] = "/",
    [anon_sym_CARET] = "^",
    [anon_sym_LPAREN] = "(",
    [anon_sym_RPAREN] = ")",
    [sym_number] = "number",
    [sym_variable] = "variable",
    [sym_comment] = "comment",
};

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [sym_program] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_sum] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_difference] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_product] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_quotient] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_exponent] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_group] = {.visible = true, .named = true, .structural = true, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .structural = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .structural = true, .extra = false},
    [anon_sym_PLUS] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_DASH] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_SLASH] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_CARET] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .structural = true, .extra = false},
    [sym_number] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_variable] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_comment] = {.visible = true, .named = true, .structural = false, .extra = true},
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
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            LEX_ERROR();
        case 2:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(2);
            ACCEPT_TOKEN(sym_comment);
        case 3:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 4:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            ACCEPT_TOKEN(sym_number);
        case 5:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(5);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            ACCEPT_TOKEN(sym_variable);
        case 6:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(6);
            if (lookahead == '#')
                ADVANCE(2);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 8:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(8);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(9);
            if (lookahead == '+')
                ADVANCE(10);
            if (lookahead == '-')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(12);
            if (lookahead == '^')
                ADVANCE(13);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 10:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 11:
            ACCEPT_TOKEN(anon_sym_DASH);
        case 12:
            ACCEPT_TOKEN(anon_sym_SLASH);
        case 13:
            ACCEPT_TOKEN(anon_sym_CARET);
        case 14:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(14);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(15);
            if (lookahead == '*')
                ADVANCE(9);
            if (lookahead == '+')
                ADVANCE(10);
            if (lookahead == '-')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(12);
            if (lookahead == '^')
                ADVANCE(13);
            LEX_ERROR();
        case 15:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 16:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(16);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(15);
            LEX_ERROR();
        case 17:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(17);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(15);
            if (lookahead == '*')
                ADVANCE(9);
            if (lookahead == '+')
                ADVANCE(10);
            if (lookahead == '-')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(12);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(13);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(17);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(15);
            if (lookahead == '*')
                ADVANCE(9);
            if (lookahead == '+')
                ADVANCE(10);
            if (lookahead == '-')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(12);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(13);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 6,
    [2] = 8,
    [3] = 8,
    [4] = 1,
    [5] = 14,
    [6] = 14,
    [7] = 16,
    [8] = 1,
    [9] = 14,
    [10] = 16,
    [11] = 14,
    [12] = 1,
    [13] = 1,
    [14] = 1,
    [15] = 1,
    [16] = 1,
    [17] = 14,
    [18] = 14,
    [19] = 14,
    [20] = 14,
    [21] = 14,
    [22] = 8,
    [23] = 1,
    [24] = 1,
    [25] = 1,
    [26] = 1,
    [27] = 1,
    [28] = 8,
    [29] = 8,
    [30] = 8,
    [31] = 8,
    [32] = 8,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = 2,
        [sym__expression] = 4,
        [sym_sum] = 6,
        [sym_difference] = 6,
        [sym_product] = 6,
        [sym_quotient] = 6,
        [sym_exponent] = 6,
        [sym_group] = 6,
        [anon_sym_LPAREN] = 8,
        [sym_number] = 6,
        [sym_variable] = 6,
        [sym_comment] = 10,
    },
    [1] = {
        [ts_builtin_sym_end] = 12,
        [sym_comment] = 14,
    },
    [2] = {
        [ts_builtin_sym_end] = 16,
        [anon_sym_PLUS] = 18,
        [anon_sym_DASH] = 20,
        [anon_sym_STAR] = 22,
        [anon_sym_SLASH] = 24,
        [anon_sym_CARET] = 26,
        [sym_comment] = 14,
    },
    [3] = {
        [ts_builtin_sym_end] = 28,
        [anon_sym_PLUS] = 28,
        [anon_sym_DASH] = 28,
        [anon_sym_STAR] = 28,
        [anon_sym_SLASH] = 28,
        [anon_sym_CARET] = 28,
        [sym_comment] = 14,
    },
    [4] = {
        [sym__expression] = 30,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [ts_builtin_sym_error] = 34,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [5] = {
        [anon_sym_PLUS] = 38,
        [anon_sym_DASH] = 40,
        [anon_sym_STAR] = 42,
        [anon_sym_SLASH] = 44,
        [anon_sym_CARET] = 46,
        [anon_sym_RPAREN] = 48,
        [sym_comment] = 14,
    },
    [6] = {
        [anon_sym_PLUS] = 28,
        [anon_sym_DASH] = 28,
        [anon_sym_STAR] = 28,
        [anon_sym_SLASH] = 28,
        [anon_sym_CARET] = 28,
        [anon_sym_RPAREN] = 28,
        [sym_comment] = 14,
    },
    [7] = {
        [anon_sym_RPAREN] = 48,
        [sym_comment] = 14,
    },
    [8] = {
        [sym__expression] = 50,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [ts_builtin_sym_error] = 52,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [9] = {
        [anon_sym_PLUS] = 38,
        [anon_sym_DASH] = 40,
        [anon_sym_STAR] = 42,
        [anon_sym_SLASH] = 44,
        [anon_sym_CARET] = 46,
        [anon_sym_RPAREN] = 54,
        [sym_comment] = 14,
    },
    [10] = {
        [anon_sym_RPAREN] = 54,
        [sym_comment] = 14,
    },
    [11] = {
        [anon_sym_PLUS] = 56,
        [anon_sym_DASH] = 56,
        [anon_sym_STAR] = 56,
        [anon_sym_SLASH] = 56,
        [anon_sym_CARET] = 56,
        [anon_sym_RPAREN] = 56,
        [sym_comment] = 14,
    },
    [12] = {
        [sym__expression] = 58,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [13] = {
        [sym__expression] = 60,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [14] = {
        [sym__expression] = 62,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [15] = {
        [sym__expression] = 64,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [16] = {
        [sym__expression] = 66,
        [sym_sum] = 32,
        [sym_difference] = 32,
        [sym_product] = 32,
        [sym_quotient] = 32,
        [sym_exponent] = 32,
        [sym_group] = 32,
        [anon_sym_LPAREN] = 36,
        [sym_number] = 32,
        [sym_variable] = 32,
        [sym_comment] = 14,
    },
    [17] = {
        [anon_sym_PLUS] = 68,
        [anon_sym_DASH] = 68,
        [anon_sym_STAR] = 68,
        [anon_sym_SLASH] = 68,
        [anon_sym_CARET] = 68,
        [anon_sym_RPAREN] = 68,
        [sym_comment] = 14,
    },
    [18] = {
        [anon_sym_PLUS] = 70,
        [anon_sym_DASH] = 70,
        [anon_sym_STAR] = 70,
        [anon_sym_SLASH] = 70,
        [anon_sym_CARET] = 46,
        [anon_sym_RPAREN] = 70,
        [sym_comment] = 14,
    },
    [19] = {
        [anon_sym_PLUS] = 72,
        [anon_sym_DASH] = 72,
        [anon_sym_STAR] = 72,
        [anon_sym_SLASH] = 72,
        [anon_sym_CARET] = 46,
        [anon_sym_RPAREN] = 72,
        [sym_comment] = 14,
    },
    [20] = {
        [anon_sym_PLUS] = 74,
        [anon_sym_DASH] = 74,
        [anon_sym_STAR] = 42,
        [anon_sym_SLASH] = 44,
        [anon_sym_CARET] = 46,
        [anon_sym_RPAREN] = 74,
        [sym_comment] = 14,
    },
    [21] = {
        [anon_sym_PLUS] = 76,
        [anon_sym_DASH] = 76,
        [anon_sym_STAR] = 42,
        [anon_sym_SLASH] = 44,
        [anon_sym_CARET] = 46,
        [anon_sym_RPAREN] = 76,
        [sym_comment] = 14,
    },
    [22] = {
        [ts_builtin_sym_end] = 56,
        [anon_sym_PLUS] = 56,
        [anon_sym_DASH] = 56,
        [anon_sym_STAR] = 56,
        [anon_sym_SLASH] = 56,
        [anon_sym_CARET] = 56,
        [sym_comment] = 14,
    },
    [23] = {
        [sym__expression] = 78,
        [sym_sum] = 6,
        [sym_difference] = 6,
        [sym_product] = 6,
        [sym_quotient] = 6,
        [sym_exponent] = 6,
        [sym_group] = 6,
        [anon_sym_LPAREN] = 8,
        [sym_number] = 6,
        [sym_variable] = 6,
        [sym_comment] = 14,
    },
    [24] = {
        [sym__expression] = 80,
        [sym_sum] = 6,
        [sym_difference] = 6,
        [sym_product] = 6,
        [sym_quotient] = 6,
        [sym_exponent] = 6,
        [sym_group] = 6,
        [anon_sym_LPAREN] = 8,
        [sym_number] = 6,
        [sym_variable] = 6,
        [sym_comment] = 14,
    },
    [25] = {
        [sym__expression] = 82,
        [sym_sum] = 6,
        [sym_difference] = 6,
        [sym_product] = 6,
        [sym_quotient] = 6,
        [sym_exponent] = 6,
        [sym_group] = 6,
        [anon_sym_LPAREN] = 8,
        [sym_number] = 6,
        [sym_variable] = 6,
        [sym_comment] = 14,
    },
    [26] = {
        [sym__expression] = 84,
        [sym_sum] = 6,
        [sym_difference] = 6,
        [sym_product] = 6,
        [sym_quotient] = 6,
        [sym_exponent] = 6,
        [sym_group] = 6,
        [anon_sym_LPAREN] = 8,
        [sym_number] = 6,
        [sym_variable] = 6,
        [sym_comment] = 14,
    },
    [27] = {
        [sym__expression] = 86,
        [sym_sum] = 6,
        [sym_difference] = 6,
        [sym_product] = 6,
        [sym_quotient] = 6,
        [sym_exponent] = 6,
        [sym_group] = 6,
        [anon_sym_LPAREN] = 8,
        [sym_number] = 6,
        [sym_variable] = 6,
        [sym_comment] = 14,
    },
    [28] = {
        [ts_builtin_sym_end] = 68,
        [anon_sym_PLUS] = 68,
        [anon_sym_DASH] = 68,
        [anon_sym_STAR] = 68,
        [anon_sym_SLASH] = 68,
        [anon_sym_CARET] = 68,
        [sym_comment] = 14,
    },
    [29] = {
        [ts_builtin_sym_end] = 70,
        [anon_sym_PLUS] = 70,
        [anon_sym_DASH] = 70,
        [anon_sym_STAR] = 70,
        [anon_sym_SLASH] = 70,
        [anon_sym_CARET] = 26,
        [sym_comment] = 14,
    },
    [30] = {
        [ts_builtin_sym_end] = 72,
        [anon_sym_PLUS] = 72,
        [anon_sym_DASH] = 72,
        [anon_sym_STAR] = 72,
        [anon_sym_SLASH] = 72,
        [anon_sym_CARET] = 26,
        [sym_comment] = 14,
    },
    [31] = {
        [ts_builtin_sym_end] = 74,
        [anon_sym_PLUS] = 74,
        [anon_sym_DASH] = 74,
        [anon_sym_STAR] = 22,
        [anon_sym_SLASH] = 24,
        [anon_sym_CARET] = 26,
        [sym_comment] = 14,
    },
    [32] = {
        [ts_builtin_sym_end] = 76,
        [anon_sym_PLUS] = 76,
        [anon_sym_DASH] = 76,
        [anon_sym_STAR] = 22,
        [anon_sym_SLASH] = 24,
        [anon_sym_CARET] = 26,
        [sym_comment] = 14,
    },
};

static TSParseActionEntry ts_parse_actions[] = {
    [0] = {.count = 1}, ERROR(),
    [2] = {.count = 1}, SHIFT(1, 0),
    [4] = {.count = 1}, SHIFT(2, 0),
    [6] = {.count = 1}, SHIFT(3, 0),
    [8] = {.count = 1}, SHIFT(4, 0),
    [10] = {.count = 1}, SHIFT_EXTRA(),
    [12] = {.count = 1}, ACCEPT_INPUT(),
    [14] = {.count = 1}, SHIFT_EXTRA(),
    [16] = {.count = 1}, REDUCE(sym_program, 1, 0),
    [18] = {.count = 1}, SHIFT(23, 0),
    [20] = {.count = 1}, SHIFT(24, 0),
    [22] = {.count = 1}, SHIFT(25, 0),
    [24] = {.count = 1}, SHIFT(26, 0),
    [26] = {.count = 1}, SHIFT(27, 0),
    [28] = {.count = 1}, REDUCE(sym__expression, 1, 0),
    [30] = {.count = 1}, SHIFT(5, 0),
    [32] = {.count = 1}, SHIFT(6, 0),
    [34] = {.count = 1}, SHIFT(7, 0),
    [36] = {.count = 1}, SHIFT(8, 0),
    [38] = {.count = 1}, SHIFT(12, 0),
    [40] = {.count = 1}, SHIFT(13, 0),
    [42] = {.count = 1}, SHIFT(14, 0),
    [44] = {.count = 1}, SHIFT(15, 0),
    [46] = {.count = 1}, SHIFT(16, 0),
    [48] = {.count = 1}, SHIFT(22, 0),
    [50] = {.count = 1}, SHIFT(9, 0),
    [52] = {.count = 1}, SHIFT(10, 0),
    [54] = {.count = 1}, SHIFT(11, 0),
    [56] = {.count = 1}, REDUCE(sym_group, 3, 0),
    [58] = {.count = 1}, SHIFT(21, 0),
    [60] = {.count = 1}, SHIFT(20, 0),
    [62] = {.count = 1}, SHIFT(19, 0),
    [64] = {.count = 1}, SHIFT(18, 0),
    [66] = {.count = 1}, SHIFT(17, 0),
    [68] = {.count = 1}, REDUCE(sym_exponent, 3, 0),
    [70] = {.count = 1}, REDUCE(sym_quotient, 3, FRAGILE),
    [72] = {.count = 1}, REDUCE(sym_product, 3, FRAGILE),
    [74] = {.count = 1}, REDUCE(sym_difference, 3, FRAGILE),
    [76] = {.count = 1}, REDUCE(sym_sum, 3, FRAGILE),
    [78] = {.count = 1}, SHIFT(32, 0),
    [80] = {.count = 1}, SHIFT(31, 0),
    [82] = {.count = 1}, SHIFT(30, 0),
    [84] = {.count = 1}, SHIFT(29, 0),
    [86] = {.count = 1}, SHIFT(28, 0),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_arithmetic);
