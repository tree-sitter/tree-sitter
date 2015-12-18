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

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = ACTIONS(SHIFT(1, 0)),
        [sym__expression] = ACTIONS(SHIFT(2, 0)),
        [sym_sum] = ACTIONS(SHIFT(3, 0)),
        [sym_difference] = ACTIONS(SHIFT(3, 0)),
        [sym_product] = ACTIONS(SHIFT(3, 0)),
        [sym_quotient] = ACTIONS(SHIFT(3, 0)),
        [sym_exponent] = ACTIONS(SHIFT(3, 0)),
        [sym_group] = ACTIONS(SHIFT(3, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4, 0)),
        [sym_number] = ACTIONS(SHIFT(3, 0)),
        [sym_variable] = ACTIONS(SHIFT(3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(23, 0)),
        [anon_sym_DASH] = ACTIONS(SHIFT(24, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(25, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(26, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym__expression] = ACTIONS(SHIFT(5, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(7, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [anon_sym_PLUS] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_DASH] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(22, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(22, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym__expression] = ACTIONS(SHIFT(9, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(10, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [anon_sym_PLUS] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_DASH] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(11, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(11, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym__expression] = ACTIONS(SHIFT(21, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym__expression] = ACTIONS(SHIFT(20, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [sym__expression] = ACTIONS(SHIFT(19, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym__expression] = ACTIONS(SHIFT(18, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__expression] = ACTIONS(SHIFT(17, 0)),
        [sym_sum] = ACTIONS(SHIFT(6, 0)),
        [sym_difference] = ACTIONS(SHIFT(6, 0)),
        [sym_product] = ACTIONS(SHIFT(6, 0)),
        [sym_quotient] = ACTIONS(SHIFT(6, 0)),
        [sym_exponent] = ACTIONS(SHIFT(6, 0)),
        [sym_group] = ACTIONS(SHIFT(6, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8, 0)),
        [sym_number] = ACTIONS(SHIFT(6, 0)),
        [sym_variable] = ACTIONS(SHIFT(6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_difference, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_difference, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_difference, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_sum, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_sum, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_sum, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_group, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym__expression] = ACTIONS(SHIFT(32, 0)),
        [sym_sum] = ACTIONS(SHIFT(3, 0)),
        [sym_difference] = ACTIONS(SHIFT(3, 0)),
        [sym_product] = ACTIONS(SHIFT(3, 0)),
        [sym_quotient] = ACTIONS(SHIFT(3, 0)),
        [sym_exponent] = ACTIONS(SHIFT(3, 0)),
        [sym_group] = ACTIONS(SHIFT(3, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4, 0)),
        [sym_number] = ACTIONS(SHIFT(3, 0)),
        [sym_variable] = ACTIONS(SHIFT(3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym__expression] = ACTIONS(SHIFT(31, 0)),
        [sym_sum] = ACTIONS(SHIFT(3, 0)),
        [sym_difference] = ACTIONS(SHIFT(3, 0)),
        [sym_product] = ACTIONS(SHIFT(3, 0)),
        [sym_quotient] = ACTIONS(SHIFT(3, 0)),
        [sym_exponent] = ACTIONS(SHIFT(3, 0)),
        [sym_group] = ACTIONS(SHIFT(3, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4, 0)),
        [sym_number] = ACTIONS(SHIFT(3, 0)),
        [sym_variable] = ACTIONS(SHIFT(3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym__expression] = ACTIONS(SHIFT(30, 0)),
        [sym_sum] = ACTIONS(SHIFT(3, 0)),
        [sym_difference] = ACTIONS(SHIFT(3, 0)),
        [sym_product] = ACTIONS(SHIFT(3, 0)),
        [sym_quotient] = ACTIONS(SHIFT(3, 0)),
        [sym_exponent] = ACTIONS(SHIFT(3, 0)),
        [sym_group] = ACTIONS(SHIFT(3, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4, 0)),
        [sym_number] = ACTIONS(SHIFT(3, 0)),
        [sym_variable] = ACTIONS(SHIFT(3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym__expression] = ACTIONS(SHIFT(29, 0)),
        [sym_sum] = ACTIONS(SHIFT(3, 0)),
        [sym_difference] = ACTIONS(SHIFT(3, 0)),
        [sym_product] = ACTIONS(SHIFT(3, 0)),
        [sym_quotient] = ACTIONS(SHIFT(3, 0)),
        [sym_exponent] = ACTIONS(SHIFT(3, 0)),
        [sym_group] = ACTIONS(SHIFT(3, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4, 0)),
        [sym_number] = ACTIONS(SHIFT(3, 0)),
        [sym_variable] = ACTIONS(SHIFT(3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym__expression] = ACTIONS(SHIFT(28, 0)),
        [sym_sum] = ACTIONS(SHIFT(3, 0)),
        [sym_difference] = ACTIONS(SHIFT(3, 0)),
        [sym_product] = ACTIONS(SHIFT(3, 0)),
        [sym_quotient] = ACTIONS(SHIFT(3, 0)),
        [sym_exponent] = ACTIONS(SHIFT(3, 0)),
        [sym_group] = ACTIONS(SHIFT(3, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4, 0)),
        [sym_number] = ACTIONS(SHIFT(3, 0)),
        [sym_variable] = ACTIONS(SHIFT(3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_exponent, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_quotient, 3, FRAGILE)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_product, 3, FRAGILE)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_difference, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_difference, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_difference, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(25, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(26, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_sum, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_sum, 3, FRAGILE)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_sum, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(25, 0)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(26, 0)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_arithmetic);
