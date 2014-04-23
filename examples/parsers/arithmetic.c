#include "tree_sitter/parser.h"

#define STATE_COUNT 32
#define SYMBOL_COUNT 18

enum {
    ts_sym_expression = 2,
    ts_sym_sum = 3,
    ts_sym_difference = 4,
    ts_sym_product = 5,
    ts_sym_quotient = 6,
    ts_sym_exponent = 7,
    ts_sym_group = 8,
    ts_sym_number = 9,
    ts_sym_variable = 10,
    ts_aux_sym_token0 = 11,
    ts_aux_sym_token1 = 12,
    ts_aux_sym_token2 = 13,
    ts_aux_sym_token3 = 14,
    ts_aux_sym_token4 = 15,
    ts_aux_sym_token5 = 16,
    ts_aux_sym_token6 = 17,
};

SYMBOL_NAMES = {
    [ts_sym_expression] = "expression",
    [ts_sym_sum] = "sum",
    [ts_sym_difference] = "difference",
    [ts_sym_product] = "product",
    [ts_sym_quotient] = "quotient",
    [ts_sym_exponent] = "exponent",
    [ts_sym_group] = "group",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym_number] = "number",
    [ts_sym_variable] = "variable",
    [ts_aux_sym_token0] = "'+'",
    [ts_aux_sym_token1] = "'-'",
    [ts_aux_sym_token2] = "'*'",
    [ts_aux_sym_token3] = "'/'",
    [ts_aux_sym_token4] = "'^'",
    [ts_aux_sym_token5] = "'('",
    [ts_aux_sym_token6] = "')'",
};

HIDDEN_SYMBOLS = {
    [ts_aux_sym_token0] = 1,
    [ts_aux_sym_token1] = 1,
    [ts_aux_sym_token2] = 1,
    [ts_aux_sym_token3] = 1,
    [ts_aux_sym_token4] = 1,
    [ts_aux_sym_token5] = 1,
    [ts_aux_sym_token6] = 1,
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
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 5:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 6:
            ACCEPT_TOKEN(ts_aux_sym_token4);
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
            ACCEPT_TOKEN(ts_aux_sym_token6);
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
            ACCEPT_TOKEN(ts_aux_sym_token5);
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
    [2] = 10,
    [3] = 0,
    [4] = 10,
    [5] = 0,
    [6] = 10,
    [7] = 0,
    [8] = 10,
    [9] = 0,
    [10] = 10,
    [11] = 0,
    [12] = 0,
    [13] = 10,
    [14] = 7,
    [15] = 10,
    [16] = 7,
    [17] = 10,
    [18] = 7,
    [19] = 10,
    [20] = 7,
    [21] = 10,
    [22] = 7,
    [23] = 10,
    [24] = 7,
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
        [ts_sym_expression] = SHIFT(1),
        [ts_sym_sum] = SHIFT(12),
        [ts_sym_difference] = SHIFT(12),
        [ts_sym_product] = SHIFT(12),
        [ts_sym_quotient] = SHIFT(12),
        [ts_sym_exponent] = SHIFT(12),
        [ts_sym_group] = SHIFT(12),
        [ts_sym_number] = SHIFT(12),
        [ts_sym_variable] = SHIFT(12),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_aux_sym_token0] = SHIFT(2),
        [ts_aux_sym_token1] = SHIFT(4),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token3] = SHIFT(8),
        [ts_aux_sym_token4] = SHIFT(10),
    },
    [2] = {
        [ts_sym_expression] = SHIFT(3),
        [ts_sym_sum] = SHIFT(12),
        [ts_sym_difference] = SHIFT(12),
        [ts_sym_product] = SHIFT(12),
        [ts_sym_quotient] = SHIFT(12),
        [ts_sym_exponent] = SHIFT(12),
        [ts_sym_group] = SHIFT(12),
        [ts_sym_number] = SHIFT(12),
        [ts_sym_variable] = SHIFT(12),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [3] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_sum, 3),
        [ts_aux_sym_token0] = SHIFT(2),
        [ts_aux_sym_token1] = SHIFT(4),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token3] = SHIFT(8),
        [ts_aux_sym_token4] = SHIFT(10),
    },
    [4] = {
        [ts_sym_expression] = SHIFT(5),
        [ts_sym_sum] = SHIFT(12),
        [ts_sym_difference] = SHIFT(12),
        [ts_sym_product] = SHIFT(12),
        [ts_sym_quotient] = SHIFT(12),
        [ts_sym_exponent] = SHIFT(12),
        [ts_sym_group] = SHIFT(12),
        [ts_sym_number] = SHIFT(12),
        [ts_sym_variable] = SHIFT(12),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [5] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_difference, 3),
        [ts_aux_sym_token0] = SHIFT(2),
        [ts_aux_sym_token1] = SHIFT(4),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token3] = SHIFT(8),
        [ts_aux_sym_token4] = SHIFT(10),
    },
    [6] = {
        [ts_sym_expression] = SHIFT(7),
        [ts_sym_sum] = SHIFT(12),
        [ts_sym_difference] = SHIFT(12),
        [ts_sym_product] = SHIFT(12),
        [ts_sym_quotient] = SHIFT(12),
        [ts_sym_exponent] = SHIFT(12),
        [ts_sym_group] = SHIFT(12),
        [ts_sym_number] = SHIFT(12),
        [ts_sym_variable] = SHIFT(12),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [7] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token3] = SHIFT(8),
        [ts_aux_sym_token4] = SHIFT(10),
    },
    [8] = {
        [ts_sym_expression] = SHIFT(9),
        [ts_sym_sum] = SHIFT(12),
        [ts_sym_difference] = SHIFT(12),
        [ts_sym_product] = SHIFT(12),
        [ts_sym_quotient] = SHIFT(12),
        [ts_sym_exponent] = SHIFT(12),
        [ts_sym_group] = SHIFT(12),
        [ts_sym_number] = SHIFT(12),
        [ts_sym_variable] = SHIFT(12),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token3] = SHIFT(8),
        [ts_aux_sym_token4] = SHIFT(10),
    },
    [10] = {
        [ts_sym_expression] = SHIFT(11),
        [ts_sym_sum] = SHIFT(12),
        [ts_sym_difference] = SHIFT(12),
        [ts_sym_product] = SHIFT(12),
        [ts_sym_quotient] = SHIFT(12),
        [ts_sym_exponent] = SHIFT(12),
        [ts_sym_group] = SHIFT(12),
        [ts_sym_number] = SHIFT(12),
        [ts_sym_variable] = SHIFT(12),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [11] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = SHIFT(10),
    },
    [12] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
    },
    [13] = {
        [ts_sym_expression] = SHIFT(14),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_builtin_sym_error] = SHIFT(31),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [14] = {
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token1] = SHIFT(17),
        [ts_aux_sym_token2] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = SHIFT(30),
    },
    [15] = {
        [ts_sym_expression] = SHIFT(16),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [16] = {
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token1] = SHIFT(17),
        [ts_aux_sym_token2] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = REDUCE(ts_sym_sum, 3),
    },
    [17] = {
        [ts_sym_expression] = SHIFT(18),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [18] = {
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token1] = SHIFT(17),
        [ts_aux_sym_token2] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = REDUCE(ts_sym_difference, 3),
    },
    [19] = {
        [ts_sym_expression] = SHIFT(20),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [20] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token2] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = REDUCE(ts_sym_product, 3),
    },
    [21] = {
        [ts_sym_expression] = SHIFT(22),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [22] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token2] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = REDUCE(ts_sym_quotient, 3),
    },
    [23] = {
        [ts_sym_expression] = SHIFT(24),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [24] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 3),
    },
    [25] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
    },
    [26] = {
        [ts_sym_expression] = SHIFT(27),
        [ts_sym_sum] = SHIFT(25),
        [ts_sym_difference] = SHIFT(25),
        [ts_sym_product] = SHIFT(25),
        [ts_sym_quotient] = SHIFT(25),
        [ts_sym_exponent] = SHIFT(25),
        [ts_sym_group] = SHIFT(25),
        [ts_builtin_sym_error] = SHIFT(29),
        [ts_sym_number] = SHIFT(25),
        [ts_sym_variable] = SHIFT(25),
        [ts_aux_sym_token5] = SHIFT(26),
    },
    [27] = {
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token1] = SHIFT(17),
        [ts_aux_sym_token2] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(23),
        [ts_aux_sym_token6] = SHIFT(28),
    },
    [28] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_group, 3),
    },
    [29] = {
        [ts_aux_sym_token6] = SHIFT(28),
    },
    [30] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_group, 3),
    },
    [31] = {
        [ts_aux_sym_token6] = SHIFT(30),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_arithmetic);
