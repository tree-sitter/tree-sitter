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
    [sym_program] = {.visible = true, .named = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .extra = false},
    [sym_sum] = {.visible = true, .named = true, .extra = false},
    [sym_difference] = {.visible = true, .named = true, .extra = false},
    [sym_product] = {.visible = true, .named = true, .extra = false},
    [sym_quotient] = {.visible = true, .named = true, .extra = false},
    [sym_exponent] = {.visible = true, .named = true, .extra = false},
    [sym_group] = {.visible = true, .named = true, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .extra = false},
    [anon_sym_PLUS] = {.visible = true, .named = false, .extra = false},
    [anon_sym_DASH] = {.visible = true, .named = false, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .extra = false},
    [anon_sym_SLASH] = {.visible = true, .named = false, .extra = false},
    [anon_sym_CARET] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .extra = false},
    [sym_number] = {.visible = true, .named = true, .extra = false},
    [sym_variable] = {.visible = true, .named = true, .extra = false},
    [sym_comment] = {.visible = true, .named = true, .extra = true},
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
                ADVANCE(6);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            ACCEPT_TOKEN(sym_variable);
        case 6:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            ACCEPT_TOKEN(sym_variable);
        case 7:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(8);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(7);
            if (lookahead == '#')
                ADVANCE(2);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 9:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(8);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(9);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(10);
            if (lookahead == '+')
                ADVANCE(11);
            if (lookahead == '-')
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(13);
            if (lookahead == '^')
                ADVANCE(14);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 11:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 12:
            ACCEPT_TOKEN(anon_sym_DASH);
        case 13:
            ACCEPT_TOKEN(anon_sym_SLASH);
        case 14:
            ACCEPT_TOKEN(anon_sym_CARET);
        case 15:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(15);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(10);
            if (lookahead == '+')
                ADVANCE(11);
            if (lookahead == '-')
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(13);
            if (lookahead == '^')
                ADVANCE(14);
            LEX_ERROR();
        case 16:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 17:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(17);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(16);
            LEX_ERROR();
        case 18:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(8);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(18);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(10);
            if (lookahead == '+')
                ADVANCE(11);
            if (lookahead == '-')
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(13);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(14);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(8);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(18);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(10);
            if (lookahead == '+')
                ADVANCE(11);
            if (lookahead == '-')
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(13);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z') ||
                (945 <= lookahead && lookahead <= 969))
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(14);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 7,
    [2] = 9,
    [3] = 9,
    [4] = 1,
    [5] = 15,
    [6] = 15,
    [7] = 17,
    [8] = 1,
    [9] = 15,
    [10] = 17,
    [11] = 15,
    [12] = 1,
    [13] = 1,
    [14] = 1,
    [15] = 1,
    [16] = 1,
    [17] = 15,
    [18] = 15,
    [19] = 15,
    [20] = 15,
    [21] = 15,
    [22] = 9,
    [23] = 1,
    [24] = 1,
    [25] = 1,
    [26] = 1,
    [27] = 1,
    [28] = 9,
    [29] = 9,
    [30] = 9,
    [31] = 9,
    [32] = 9,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = ACTIONS(SHIFT(1)),
        [sym__expression] = ACTIONS(SHIFT(2)),
        [sym_sum] = ACTIONS(SHIFT(3)),
        [sym_difference] = ACTIONS(SHIFT(3)),
        [sym_product] = ACTIONS(SHIFT(3)),
        [sym_quotient] = ACTIONS(SHIFT(3)),
        [sym_exponent] = ACTIONS(SHIFT(3)),
        [sym_group] = ACTIONS(SHIFT(3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4)),
        [sym_number] = ACTIONS(SHIFT(3)),
        [sym_variable] = ACTIONS(SHIFT(3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 1)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(23)),
        [anon_sym_DASH] = ACTIONS(SHIFT(24)),
        [anon_sym_STAR] = ACTIONS(SHIFT(25)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(26)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym__expression] = ACTIONS(SHIFT(5)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(7)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [anon_sym_PLUS] = ACTIONS(SHIFT(12)),
        [anon_sym_DASH] = ACTIONS(SHIFT(13)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym__expression] = ACTIONS(SHIFT(9)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(10)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [anon_sym_PLUS] = ACTIONS(SHIFT(12)),
        [anon_sym_DASH] = ACTIONS(SHIFT(13)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(11)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(11)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_group, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym__expression] = ACTIONS(SHIFT(21)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym__expression] = ACTIONS(SHIFT(20)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [sym__expression] = ACTIONS(SHIFT(19)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym__expression] = ACTIONS(SHIFT(18)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__expression] = ACTIONS(SHIFT(17)),
        [sym_sum] = ACTIONS(SHIFT(6)),
        [sym_difference] = ACTIONS(SHIFT(6)),
        [sym_product] = ACTIONS(SHIFT(6)),
        [sym_quotient] = ACTIONS(SHIFT(6)),
        [sym_exponent] = ACTIONS(SHIFT(6)),
        [sym_group] = ACTIONS(SHIFT(6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(8)),
        [sym_number] = ACTIONS(SHIFT(6)),
        [sym_variable] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_exponent, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_difference, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_difference, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_difference, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_sum, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_sum, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(14)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(15)),
        [anon_sym_CARET] = ACTIONS(SHIFT(16)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_sum, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_group, 3)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_group, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym__expression] = ACTIONS(SHIFT(32)),
        [sym_sum] = ACTIONS(SHIFT(3)),
        [sym_difference] = ACTIONS(SHIFT(3)),
        [sym_product] = ACTIONS(SHIFT(3)),
        [sym_quotient] = ACTIONS(SHIFT(3)),
        [sym_exponent] = ACTIONS(SHIFT(3)),
        [sym_group] = ACTIONS(SHIFT(3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4)),
        [sym_number] = ACTIONS(SHIFT(3)),
        [sym_variable] = ACTIONS(SHIFT(3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym__expression] = ACTIONS(SHIFT(31)),
        [sym_sum] = ACTIONS(SHIFT(3)),
        [sym_difference] = ACTIONS(SHIFT(3)),
        [sym_product] = ACTIONS(SHIFT(3)),
        [sym_quotient] = ACTIONS(SHIFT(3)),
        [sym_exponent] = ACTIONS(SHIFT(3)),
        [sym_group] = ACTIONS(SHIFT(3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4)),
        [sym_number] = ACTIONS(SHIFT(3)),
        [sym_variable] = ACTIONS(SHIFT(3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym__expression] = ACTIONS(SHIFT(30)),
        [sym_sum] = ACTIONS(SHIFT(3)),
        [sym_difference] = ACTIONS(SHIFT(3)),
        [sym_product] = ACTIONS(SHIFT(3)),
        [sym_quotient] = ACTIONS(SHIFT(3)),
        [sym_exponent] = ACTIONS(SHIFT(3)),
        [sym_group] = ACTIONS(SHIFT(3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4)),
        [sym_number] = ACTIONS(SHIFT(3)),
        [sym_variable] = ACTIONS(SHIFT(3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym__expression] = ACTIONS(SHIFT(29)),
        [sym_sum] = ACTIONS(SHIFT(3)),
        [sym_difference] = ACTIONS(SHIFT(3)),
        [sym_product] = ACTIONS(SHIFT(3)),
        [sym_quotient] = ACTIONS(SHIFT(3)),
        [sym_exponent] = ACTIONS(SHIFT(3)),
        [sym_group] = ACTIONS(SHIFT(3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4)),
        [sym_number] = ACTIONS(SHIFT(3)),
        [sym_variable] = ACTIONS(SHIFT(3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym__expression] = ACTIONS(SHIFT(28)),
        [sym_sum] = ACTIONS(SHIFT(3)),
        [sym_difference] = ACTIONS(SHIFT(3)),
        [sym_product] = ACTIONS(SHIFT(3)),
        [sym_quotient] = ACTIONS(SHIFT(3)),
        [sym_exponent] = ACTIONS(SHIFT(3)),
        [sym_group] = ACTIONS(SHIFT(3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(4)),
        [sym_number] = ACTIONS(SHIFT(3)),
        [sym_variable] = ACTIONS(SHIFT(3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_exponent, 3)),
        [anon_sym_CARET] = ACTIONS(REDUCE(sym_exponent, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_quotient, 3)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_product, 3)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE_FRAGILE(sym_difference, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_difference, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_difference, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(25)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(26)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE_FRAGILE(sym_sum, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_sum, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_sum, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(25)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(26)),
        [anon_sym_CARET] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_arithmetic);
