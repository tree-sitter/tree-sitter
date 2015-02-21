#include "tree_sitter/parser.h"

#define STATE_COUNT 32
#define SYMBOL_COUNT 20

enum {
    sym_expression = ts_builtin_sym_start,
    sym_sum,
    sym_difference,
    sym_product,
    sym_quotient,
    sym_exponent,
    sym_group,
    sym_number,
    sym_variable,
    sym_comment,
    aux_sym_STR_PLUS,
    aux_sym_STR_DASH,
    aux_sym_STR_STAR,
    aux_sym_STR_SLASH,
    aux_sym_STR_CARET,
    aux_sym_STR_LPAREN,
    aux_sym_STR_RPAREN,
};

static const char *ts_symbol_names[] = {
    [ts_builtin_sym_document] = "DOCUMENT",
    [sym_expression] = "expression",
    [sym_sum] = "sum",
    [sym_difference] = "difference",
    [sym_product] = "product",
    [sym_quotient] = "quotient",
    [sym_exponent] = "exponent",
    [sym_group] = "group",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [sym_number] = "number",
    [sym_variable] = "variable",
    [sym_comment] = "comment",
    [aux_sym_STR_PLUS] = "STR_+",
    [aux_sym_STR_DASH] = "STR_-",
    [aux_sym_STR_STAR] = "STR_*",
    [aux_sym_STR_SLASH] = "STR_/",
    [aux_sym_STR_CARET] = "STR_^",
    [aux_sym_STR_LPAREN] = "STR_(",
    [aux_sym_STR_RPAREN] = "STR_)",
};

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
    [aux_sym_STR_PLUS] = 1,
    [aux_sym_STR_DASH] = 1,
    [aux_sym_STR_STAR] = 1,
    [aux_sym_STR_SLASH] = 1,
    [aux_sym_STR_CARET] = 1,
    [aux_sym_STR_LPAREN] = 1,
    [aux_sym_STR_RPAREN] = 1,
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
            ACCEPT_TOKEN(aux_sym_STR_LPAREN);
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
        case 8:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 9:
            ACCEPT_TOKEN(aux_sym_STR_STAR);
        case 10:
            ACCEPT_TOKEN(aux_sym_STR_PLUS);
        case 11:
            ACCEPT_TOKEN(aux_sym_STR_DASH);
        case 12:
            ACCEPT_TOKEN(aux_sym_STR_SLASH);
        case 13:
            ACCEPT_TOKEN(aux_sym_STR_CARET);
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
            ACCEPT_TOKEN(aux_sym_STR_RPAREN);
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
                ADVANCE(8);
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
                ADVANCE(8);
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
    [1] = 7,
    [2] = 7,
    [3] = 1,
    [4] = 14,
    [5] = 14,
    [6] = 16,
    [7] = 1,
    [8] = 14,
    [9] = 16,
    [10] = 14,
    [11] = 1,
    [12] = 1,
    [13] = 1,
    [14] = 1,
    [15] = 1,
    [16] = 14,
    [17] = 14,
    [18] = 14,
    [19] = 14,
    [20] = 14,
    [21] = 7,
    [22] = 1,
    [23] = 1,
    [24] = 1,
    [25] = 1,
    [26] = 1,
    [27] = 7,
    [28] = 7,
    [29] = 7,
    [30] = 7,
    [31] = 7,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_expression] = SHIFT(1),
        [sym_sum] = SHIFT(2),
        [sym_difference] = SHIFT(2),
        [sym_product] = SHIFT(2),
        [sym_quotient] = SHIFT(2),
        [sym_exponent] = SHIFT(2),
        [sym_group] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_variable] = SHIFT(2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(3),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(22),
        [aux_sym_STR_DASH] = SHIFT(23),
        [aux_sym_STR_STAR] = SHIFT(24),
        [aux_sym_STR_SLASH] = SHIFT(25),
        [aux_sym_STR_CARET] = SHIFT(26),
    },
    [2] = {
        [ts_builtin_sym_end] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_CARET] = REDUCE(sym_expression, 1),
    },
    [3] = {
        [sym_expression] = SHIFT(4),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [ts_builtin_sym_error] = SHIFT(6),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [4] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(11),
        [aux_sym_STR_DASH] = SHIFT(12),
        [aux_sym_STR_STAR] = SHIFT(13),
        [aux_sym_STR_SLASH] = SHIFT(14),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = SHIFT(21),
    },
    [5] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_CARET] = REDUCE(sym_expression, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_expression, 1),
    },
    [6] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(21),
    },
    [7] = {
        [sym_expression] = SHIFT(8),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [ts_builtin_sym_error] = SHIFT(9),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [8] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(11),
        [aux_sym_STR_DASH] = SHIFT(12),
        [aux_sym_STR_STAR] = SHIFT(13),
        [aux_sym_STR_SLASH] = SHIFT(14),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = SHIFT(10),
    },
    [9] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(10),
    },
    [10] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE(sym_group, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_group, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_group, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_group, 3),
        [aux_sym_STR_CARET] = REDUCE(sym_group, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_group, 3),
    },
    [11] = {
        [sym_expression] = SHIFT(20),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [12] = {
        [sym_expression] = SHIFT(19),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [13] = {
        [sym_expression] = SHIFT(18),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [14] = {
        [sym_expression] = SHIFT(17),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [15] = {
        [sym_expression] = SHIFT(16),
        [sym_sum] = SHIFT(5),
        [sym_difference] = SHIFT(5),
        [sym_product] = SHIFT(5),
        [sym_quotient] = SHIFT(5),
        [sym_exponent] = SHIFT(5),
        [sym_group] = SHIFT(5),
        [sym_number] = SHIFT(5),
        [sym_variable] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(7),
    },
    [16] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_exponent, 3),
    },
    [17] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_quotient, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_quotient, 3),
        [aux_sym_STR_STAR] = SHIFT(13),
        [aux_sym_STR_SLASH] = SHIFT(14),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_quotient, 3),
    },
    [18] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_product, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_product, 3),
        [aux_sym_STR_STAR] = SHIFT(13),
        [aux_sym_STR_SLASH] = SHIFT(14),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_product, 3),
    },
    [19] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(11),
        [aux_sym_STR_DASH] = SHIFT(12),
        [aux_sym_STR_STAR] = SHIFT(13),
        [aux_sym_STR_SLASH] = SHIFT(14),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_difference, 3),
    },
    [20] = {
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(11),
        [aux_sym_STR_DASH] = SHIFT(12),
        [aux_sym_STR_STAR] = SHIFT(13),
        [aux_sym_STR_SLASH] = SHIFT(14),
        [aux_sym_STR_CARET] = SHIFT(15),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_sum, 3),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(sym_group, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE(sym_group, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_group, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_group, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_group, 3),
        [aux_sym_STR_CARET] = REDUCE(sym_group, 3),
    },
    [22] = {
        [sym_expression] = SHIFT(31),
        [sym_sum] = SHIFT(2),
        [sym_difference] = SHIFT(2),
        [sym_product] = SHIFT(2),
        [sym_quotient] = SHIFT(2),
        [sym_exponent] = SHIFT(2),
        [sym_group] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_variable] = SHIFT(2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(3),
    },
    [23] = {
        [sym_expression] = SHIFT(30),
        [sym_sum] = SHIFT(2),
        [sym_difference] = SHIFT(2),
        [sym_product] = SHIFT(2),
        [sym_quotient] = SHIFT(2),
        [sym_exponent] = SHIFT(2),
        [sym_group] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_variable] = SHIFT(2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(3),
    },
    [24] = {
        [sym_expression] = SHIFT(29),
        [sym_sum] = SHIFT(2),
        [sym_difference] = SHIFT(2),
        [sym_product] = SHIFT(2),
        [sym_quotient] = SHIFT(2),
        [sym_exponent] = SHIFT(2),
        [sym_group] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_variable] = SHIFT(2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(3),
    },
    [25] = {
        [sym_expression] = SHIFT(28),
        [sym_sum] = SHIFT(2),
        [sym_difference] = SHIFT(2),
        [sym_product] = SHIFT(2),
        [sym_quotient] = SHIFT(2),
        [sym_exponent] = SHIFT(2),
        [sym_group] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_variable] = SHIFT(2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(3),
    },
    [26] = {
        [sym_expression] = SHIFT(27),
        [sym_sum] = SHIFT(2),
        [sym_difference] = SHIFT(2),
        [sym_product] = SHIFT(2),
        [sym_quotient] = SHIFT(2),
        [sym_exponent] = SHIFT(2),
        [sym_group] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_variable] = SHIFT(2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(3),
    },
    [27] = {
        [ts_builtin_sym_end] = REDUCE_FRAGILE(sym_exponent, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_exponent, 3),
        [aux_sym_STR_CARET] = SHIFT(26),
    },
    [28] = {
        [ts_builtin_sym_end] = REDUCE_FRAGILE(sym_quotient, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_quotient, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_quotient, 3),
        [aux_sym_STR_STAR] = SHIFT(24),
        [aux_sym_STR_SLASH] = SHIFT(25),
        [aux_sym_STR_CARET] = SHIFT(26),
    },
    [29] = {
        [ts_builtin_sym_end] = REDUCE_FRAGILE(sym_product, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_product, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_product, 3),
        [aux_sym_STR_STAR] = SHIFT(24),
        [aux_sym_STR_SLASH] = SHIFT(25),
        [aux_sym_STR_CARET] = SHIFT(26),
    },
    [30] = {
        [ts_builtin_sym_end] = REDUCE_FRAGILE(sym_difference, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(22),
        [aux_sym_STR_DASH] = SHIFT(23),
        [aux_sym_STR_STAR] = SHIFT(24),
        [aux_sym_STR_SLASH] = SHIFT(25),
        [aux_sym_STR_CARET] = SHIFT(26),
    },
    [31] = {
        [ts_builtin_sym_end] = REDUCE_FRAGILE(sym_sum, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_PLUS] = SHIFT(22),
        [aux_sym_STR_DASH] = SHIFT(23),
        [aux_sym_STR_STAR] = SHIFT(24),
        [aux_sym_STR_SLASH] = SHIFT(25),
        [aux_sym_STR_CARET] = SHIFT(26),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_arithmetic);
