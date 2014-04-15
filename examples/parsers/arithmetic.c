#include "tree_sitter/parser.h"

#define STATE_COUNT 32
#define SYMBOL_COUNT 18

enum {
    ts_sym_difference = 2,
    ts_sym_exponent = 3,
    ts_sym_expression = 4,
    ts_sym_group = 5,
    ts_sym_number = 6,
    ts_sym_product = 7,
    ts_sym_quotient = 8,
    ts_sym_sum = 9,
    ts_sym_variable = 10,
    ts_aux_sym_token1 = 11,
    ts_aux_sym_token2 = 12,
    ts_aux_sym_token3 = 13,
    ts_aux_sym_token4 = 14,
    ts_aux_sym_token5 = 15,
    ts_aux_sym_token6 = 16,
    ts_aux_sym_token7 = 17,
};

SYMBOL_NAMES = {
    [ts_sym_difference] = "difference",
    [ts_sym_exponent] = "exponent",
    [ts_sym_expression] = "expression",
    [ts_sym_group] = "group",
    [ts_sym_number] = "number",
    [ts_sym_product] = "product",
    [ts_sym_quotient] = "quotient",
    [ts_sym_sum] = "sum",
    [ts_sym_variable] = "variable",
    [ts_aux_sym_token1] = "'+'",
    [ts_aux_sym_token2] = "'-'",
    [ts_aux_sym_token3] = "'*'",
    [ts_aux_sym_token4] = "'/'",
    [ts_aux_sym_token5] = "'^'",
    [ts_aux_sym_token6] = "'('",
    [ts_aux_sym_token7] = "')'",
    [ts_builtin_sym_end] = "EOF",
    [ts_builtin_sym_error] = "ERROR",
};

HIDDEN_SYMBOLS = {
    [ts_aux_sym_token1] = 1,
    [ts_aux_sym_token2] = 1,
    [ts_aux_sym_token3] = 1,
    [ts_aux_sym_token4] = 1,
    [ts_aux_sym_token5] = 1,
    [ts_aux_sym_token6] = 1,
    [ts_aux_sym_token7] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 0:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '*')
                ADVANCE(2);
            if (lookahead == '+')
                ADVANCE(3);
            if (lookahead == '-')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(6);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 5:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 6:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 7:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(7);
            if (lookahead == ')')
                ADVANCE(8);
            if (lookahead == '*')
                ADVANCE(2);
            if (lookahead == '+')
                ADVANCE(3);
            if (lookahead == '-')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(6);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 9:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(9);
            if (lookahead == ')')
                ADVANCE(8);
            LEX_ERROR();
        case 10:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 12:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym_number);
        case 13:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_variable);
        case 14:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(14);
            if (lookahead == '(')
                ADVANCE(11);
            if (lookahead == ')')
                ADVANCE(8);
            if (lookahead == '*')
                ADVANCE(2);
            if (lookahead == '+')
                ADVANCE(3);
            if (lookahead == '-')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(5);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '^')
                ADVANCE(6);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(14);
            if (lookahead == '(')
                ADVANCE(11);
            if (lookahead == ')')
                ADVANCE(8);
            if (lookahead == '*')
                ADVANCE(2);
            if (lookahead == '+')
                ADVANCE(3);
            if (lookahead == '-')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(5);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '^')
                ADVANCE(6);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 10,
    [1] = 0,
    [2] = 0,
    [3] = 10,
    [4] = 0,
    [5] = 10,
    [6] = 0,
    [7] = 10,
    [8] = 0,
    [9] = 10,
    [10] = 0,
    [11] = 10,
    [12] = 0,
    [13] = 10,
    [14] = 7,
    [15] = 7,
    [16] = 10,
    [17] = 7,
    [18] = 10,
    [19] = 7,
    [20] = 10,
    [21] = 7,
    [22] = 10,
    [23] = 7,
    [24] = 10,
    [25] = 7,
    [26] = 10,
    [27] = 7,
    [28] = 7,
    [29] = 9,
    [30] = 0,
    [31] = 9,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_difference] = SHIFT(1),
        [ts_sym_exponent] = SHIFT(1),
        [ts_sym_expression] = SHIFT(2),
        [ts_sym_group] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_product] = SHIFT(1),
        [ts_sym_quotient] = SHIFT(1),
        [ts_sym_sum] = SHIFT(1),
        [ts_sym_variable] = SHIFT(1),
        [ts_aux_sym_token6] = SHIFT(13),
    },
    [1] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
    },
    [2] = {
        [ts_aux_sym_token1] = SHIFT(3),
        [ts_aux_sym_token2] = SHIFT(5),
        [ts_aux_sym_token3] = SHIFT(7),
        [ts_aux_sym_token4] = SHIFT(9),
        [ts_aux_sym_token5] = SHIFT(11),
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [3] = {
        [ts_sym_difference] = SHIFT(1),
        [ts_sym_exponent] = SHIFT(1),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_group] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_product] = SHIFT(1),
        [ts_sym_quotient] = SHIFT(1),
        [ts_sym_sum] = SHIFT(1),
        [ts_sym_variable] = SHIFT(1),
        [ts_aux_sym_token6] = SHIFT(13),
    },
    [4] = {
        [ts_aux_sym_token1] = SHIFT(3),
        [ts_aux_sym_token2] = SHIFT(5),
        [ts_aux_sym_token3] = SHIFT(7),
        [ts_aux_sym_token4] = SHIFT(9),
        [ts_aux_sym_token5] = SHIFT(11),
        [ts_builtin_sym_end] = REDUCE(ts_sym_sum, 3),
    },
    [5] = {
        [ts_sym_difference] = SHIFT(1),
        [ts_sym_exponent] = SHIFT(1),
        [ts_sym_expression] = SHIFT(6),
        [ts_sym_group] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_product] = SHIFT(1),
        [ts_sym_quotient] = SHIFT(1),
        [ts_sym_sum] = SHIFT(1),
        [ts_sym_variable] = SHIFT(1),
        [ts_aux_sym_token6] = SHIFT(13),
    },
    [6] = {
        [ts_aux_sym_token1] = SHIFT(3),
        [ts_aux_sym_token2] = SHIFT(5),
        [ts_aux_sym_token3] = SHIFT(7),
        [ts_aux_sym_token4] = SHIFT(9),
        [ts_aux_sym_token5] = SHIFT(11),
        [ts_builtin_sym_end] = REDUCE(ts_sym_difference, 3),
    },
    [7] = {
        [ts_sym_difference] = SHIFT(1),
        [ts_sym_exponent] = SHIFT(1),
        [ts_sym_expression] = SHIFT(8),
        [ts_sym_group] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_product] = SHIFT(1),
        [ts_sym_quotient] = SHIFT(1),
        [ts_sym_sum] = SHIFT(1),
        [ts_sym_variable] = SHIFT(1),
        [ts_aux_sym_token6] = SHIFT(13),
    },
    [8] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token3] = SHIFT(7),
        [ts_aux_sym_token4] = SHIFT(9),
        [ts_aux_sym_token5] = SHIFT(11),
        [ts_builtin_sym_end] = REDUCE(ts_sym_product, 3),
    },
    [9] = {
        [ts_sym_difference] = SHIFT(1),
        [ts_sym_exponent] = SHIFT(1),
        [ts_sym_expression] = SHIFT(10),
        [ts_sym_group] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_product] = SHIFT(1),
        [ts_sym_quotient] = SHIFT(1),
        [ts_sym_sum] = SHIFT(1),
        [ts_sym_variable] = SHIFT(1),
        [ts_aux_sym_token6] = SHIFT(13),
    },
    [10] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token3] = SHIFT(7),
        [ts_aux_sym_token4] = SHIFT(9),
        [ts_aux_sym_token5] = SHIFT(11),
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 3),
    },
    [11] = {
        [ts_sym_difference] = SHIFT(1),
        [ts_sym_exponent] = SHIFT(1),
        [ts_sym_expression] = SHIFT(12),
        [ts_sym_group] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_product] = SHIFT(1),
        [ts_sym_quotient] = SHIFT(1),
        [ts_sym_sum] = SHIFT(1),
        [ts_sym_variable] = SHIFT(1),
        [ts_aux_sym_token6] = SHIFT(13),
    },
    [12] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token5] = SHIFT(11),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
    },
    [13] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(15),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
        [ts_builtin_sym_error] = SHIFT(31),
    },
    [14] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [15] = {
        [ts_aux_sym_token1] = SHIFT(16),
        [ts_aux_sym_token2] = SHIFT(18),
        [ts_aux_sym_token3] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(22),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = SHIFT(30),
    },
    [16] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(17),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
    },
    [17] = {
        [ts_aux_sym_token1] = SHIFT(16),
        [ts_aux_sym_token2] = SHIFT(18),
        [ts_aux_sym_token3] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(22),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = REDUCE(ts_sym_sum, 3),
    },
    [18] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(19),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
    },
    [19] = {
        [ts_aux_sym_token1] = SHIFT(16),
        [ts_aux_sym_token2] = SHIFT(18),
        [ts_aux_sym_token3] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(22),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = REDUCE(ts_sym_difference, 3),
    },
    [20] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(21),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
    },
    [21] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token3] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(22),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = REDUCE(ts_sym_product, 3),
    },
    [22] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(23),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
    },
    [23] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token3] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(22),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = REDUCE(ts_sym_quotient, 3),
    },
    [24] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(25),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
    },
    [25] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = REDUCE(ts_sym_exponent, 3),
    },
    [26] = {
        [ts_sym_difference] = SHIFT(14),
        [ts_sym_exponent] = SHIFT(14),
        [ts_sym_expression] = SHIFT(27),
        [ts_sym_group] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_product] = SHIFT(14),
        [ts_sym_quotient] = SHIFT(14),
        [ts_sym_sum] = SHIFT(14),
        [ts_sym_variable] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(26),
        [ts_builtin_sym_error] = SHIFT(29),
    },
    [27] = {
        [ts_aux_sym_token1] = SHIFT(16),
        [ts_aux_sym_token2] = SHIFT(18),
        [ts_aux_sym_token3] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(22),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token7] = SHIFT(28),
    },
    [28] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_group, 3),
    },
    [29] = {
        [ts_aux_sym_token7] = SHIFT(28),
    },
    [30] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_group, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_group, 3),
    },
    [31] = {
        [ts_aux_sym_token7] = SHIFT(30),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_arithmetic);
