#include "tree_sitter/parser.h"

STATE_COUNT = 134;
SYMBOL_COUNT = 21;

enum {
    ts_sym__operand1 = 2,
    ts_sym__operand2 = 3,
    ts_sym__operand3 = 4,
    ts_sym_difference = 5,
    ts_sym_exponent = 6,
    ts_sym_expression = 7,
    ts_sym_grouping = 8,
    ts_sym_number = 9,
    ts_sym_product = 10,
    ts_sym_quotient = 11,
    ts_sym_sum = 12,
    ts_sym_variable = 13,
    ts_aux_sym_token1 = 14,
    ts_aux_sym_token2 = 15,
    ts_aux_sym_token3 = 16,
    ts_aux_sym_token4 = 17,
    ts_aux_sym_token5 = 18,
    ts_aux_sym_token6 = 19,
    ts_aux_sym_token7 = 20,
};

SYMBOL_NAMES = {
    [ts_sym__operand1] = "_operand1",
    [ts_sym__operand2] = "_operand2",
    [ts_sym__operand3] = "_operand3",
    [ts_sym_difference] = "difference",
    [ts_sym_exponent] = "exponent",
    [ts_sym_expression] = "expression",
    [ts_sym_grouping] = "grouping",
    [ts_sym_number] = "number",
    [ts_sym_product] = "product",
    [ts_sym_quotient] = "quotient",
    [ts_sym_sum] = "sum",
    [ts_sym_variable] = "variable",
    [ts_aux_sym_token1] = "'('",
    [ts_aux_sym_token2] = "')'",
    [ts_aux_sym_token3] = "'+'",
    [ts_aux_sym_token4] = "'-'",
    [ts_aux_sym_token5] = "'*'",
    [ts_aux_sym_token6] = "'/'",
    [ts_aux_sym_token7] = "'^'",
    [ts_builtin_sym_end] = "end",
    [ts_builtin_sym_error] = "error",
};

HIDDEN_SYMBOLS = {
    [ts_sym__operand1] = 1,
    [ts_sym__operand2] = 1,
    [ts_sym__operand3] = 1,
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(3);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 4:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(4);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            LEX_ERROR();
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
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '/')
                ADVANCE(9);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 9:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 10:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '/')
                ADVANCE(9);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 12:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(12);
            if (lookahead == '(')
                ADVANCE(13);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 13:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 14:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_number);
        case 15:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_variable);
        case 16:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 17:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(17);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 18:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(18);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '/')
                ADVANCE(9);
            LEX_ERROR();
        case 19:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(19);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '/')
                ADVANCE(9);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 20:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(20);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 21:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(21);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '/')
                ADVANCE(9);
            LEX_ERROR();
        case 22:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(22);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '/')
                ADVANCE(9);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 23:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(23);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            LEX_ERROR();
        case 24:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(24);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 25:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(25);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '/')
                ADVANCE(9);
            LEX_ERROR();
        case 26:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(26);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '/')
                ADVANCE(9);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case 27:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(27);
            if (lookahead == '(')
                ADVANCE(13);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '/')
                ADVANCE(9);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(27);
            if (lookahead == '(')
                ADVANCE(13);
            if (lookahead == ')')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(5);
            if (lookahead == '-')
                ADVANCE(6);
            if (lookahead == '/')
                ADVANCE(9);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '^')
                ADVANCE(11);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 12,
    [1] = 23,
    [2] = 12,
    [3] = 0,
    [4] = 21,
    [5] = 12,
    [6] = 0,
    [7] = 20,
    [8] = 12,
    [9] = 0,
    [10] = 0,
    [11] = 12,
    [12] = 4,
    [13] = 12,
    [14] = 2,
    [15] = 18,
    [16] = 12,
    [17] = 2,
    [18] = 17,
    [19] = 12,
    [20] = 2,
    [21] = 2,
    [22] = 12,
    [23] = 7,
    [24] = 12,
    [25] = 4,
    [26] = 16,
    [27] = 12,
    [28] = 4,
    [29] = 4,
    [30] = 12,
    [31] = 10,
    [32] = 12,
    [33] = 7,
    [34] = 7,
    [35] = 12,
    [36] = 2,
    [37] = 7,
    [38] = 2,
    [39] = 7,
    [40] = 10,
    [41] = 4,
    [42] = 12,
    [43] = 2,
    [44] = 10,
    [45] = 2,
    [46] = 4,
    [47] = 4,
    [48] = 16,
    [49] = 12,
    [50] = 2,
    [51] = 16,
    [52] = 12,
    [53] = 4,
    [54] = 2,
    [55] = 2,
    [56] = 2,
    [57] = 17,
    [58] = 12,
    [59] = 2,
    [60] = 17,
    [61] = 12,
    [62] = 2,
    [63] = 19,
    [64] = 12,
    [65] = 18,
    [66] = 18,
    [67] = 12,
    [68] = 2,
    [69] = 18,
    [70] = 18,
    [71] = 19,
    [72] = 2,
    [73] = 12,
    [74] = 2,
    [75] = 19,
    [76] = 12,
    [77] = 2,
    [78] = 2,
    [79] = 0,
    [80] = 0,
    [81] = 20,
    [82] = 12,
    [83] = 2,
    [84] = 20,
    [85] = 12,
    [86] = 0,
    [87] = 22,
    [88] = 12,
    [89] = 21,
    [90] = 21,
    [91] = 12,
    [92] = 2,
    [93] = 21,
    [94] = 21,
    [95] = 22,
    [96] = 0,
    [97] = 12,
    [98] = 2,
    [99] = 22,
    [100] = 12,
    [101] = 0,
    [102] = 25,
    [103] = 12,
    [104] = 23,
    [105] = 24,
    [106] = 12,
    [107] = 23,
    [108] = 23,
    [109] = 12,
    [110] = 2,
    [111] = 23,
    [112] = 23,
    [113] = 24,
    [114] = 12,
    [115] = 2,
    [116] = 24,
    [117] = 12,
    [118] = 23,
    [119] = 26,
    [120] = 12,
    [121] = 25,
    [122] = 25,
    [123] = 12,
    [124] = 2,
    [125] = 25,
    [126] = 0,
    [127] = 25,
    [128] = 0,
    [129] = 26,
    [130] = 23,
    [131] = 12,
    [132] = 2,
    [133] = 26,
};

PARSE_TABLE = {
    [0] = {
        [ts_sym__operand1] = SHIFT(1),
        [ts_sym__operand2] = SHIFT(102),
        [ts_sym__operand3] = SHIFT(119),
        [ts_sym_difference] = SHIFT(126),
        [ts_sym_exponent] = SHIFT(127),
        [ts_sym_expression] = SHIFT(128),
        [ts_sym_grouping] = SHIFT(129),
        [ts_sym_number] = SHIFT(129),
        [ts_sym_product] = SHIFT(130),
        [ts_sym_quotient] = SHIFT(130),
        [ts_sym_sum] = SHIFT(126),
        [ts_sym_variable] = SHIFT(129),
        [ts_aux_sym_token1] = SHIFT(131),
    },
    [1] = {
        [ts_aux_sym_token3] = SHIFT(2),
        [ts_aux_sym_token4] = SHIFT(100),
        [ts_builtin_sym_end] = REDUCE(ts_sym_sum, 1),
    },
    [2] = {
        [ts_sym__operand1] = SHIFT(3),
        [ts_sym__operand2] = SHIFT(4),
        [ts_sym__operand3] = SHIFT(87),
        [ts_sym_exponent] = SHIFT(94),
        [ts_sym_grouping] = SHIFT(95),
        [ts_sym_number] = SHIFT(95),
        [ts_sym_product] = SHIFT(96),
        [ts_sym_quotient] = SHIFT(96),
        [ts_sym_variable] = SHIFT(95),
        [ts_aux_sym_token1] = SHIFT(97),
    },
    [3] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_sum, 3),
    },
    [4] = {
        [ts_aux_sym_token5] = SHIFT(5),
        [ts_aux_sym_token6] = SHIFT(85),
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 1),
    },
    [5] = {
        [ts_sym__operand2] = SHIFT(6),
        [ts_sym__operand3] = SHIFT(7),
        [ts_sym_exponent] = SHIFT(80),
        [ts_sym_grouping] = SHIFT(81),
        [ts_sym_number] = SHIFT(81),
        [ts_sym_variable] = SHIFT(81),
        [ts_aux_sym_token1] = SHIFT(82),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_product, 3),
    },
    [7] = {
        [ts_aux_sym_token7] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 1),
    },
    [8] = {
        [ts_sym__operand3] = SHIFT(9),
        [ts_sym_grouping] = SHIFT(10),
        [ts_sym_number] = SHIFT(10),
        [ts_sym_variable] = SHIFT(10),
        [ts_aux_sym_token1] = SHIFT(11),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
    },
    [10] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [11] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(78),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(78),
    },
    [12] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_sum, 1),
        [ts_aux_sym_token3] = SHIFT(13),
        [ts_aux_sym_token4] = SHIFT(76),
    },
    [13] = {
        [ts_sym__operand1] = SHIFT(14),
        [ts_sym__operand2] = SHIFT(15),
        [ts_sym__operand3] = SHIFT(63),
        [ts_sym_exponent] = SHIFT(70),
        [ts_sym_grouping] = SHIFT(71),
        [ts_sym_number] = SHIFT(71),
        [ts_sym_product] = SHIFT(72),
        [ts_sym_quotient] = SHIFT(72),
        [ts_sym_variable] = SHIFT(71),
        [ts_aux_sym_token1] = SHIFT(73),
    },
    [14] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_sum, 3),
    },
    [15] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_quotient, 1),
        [ts_aux_sym_token5] = SHIFT(16),
        [ts_aux_sym_token6] = SHIFT(61),
    },
    [16] = {
        [ts_sym__operand2] = SHIFT(17),
        [ts_sym__operand3] = SHIFT(18),
        [ts_sym_exponent] = SHIFT(56),
        [ts_sym_grouping] = SHIFT(57),
        [ts_sym_number] = SHIFT(57),
        [ts_sym_variable] = SHIFT(57),
        [ts_aux_sym_token1] = SHIFT(58),
    },
    [17] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_product, 3),
    },
    [18] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(19),
    },
    [19] = {
        [ts_sym__operand3] = SHIFT(20),
        [ts_sym_grouping] = SHIFT(21),
        [ts_sym_number] = SHIFT(21),
        [ts_sym_variable] = SHIFT(21),
        [ts_aux_sym_token1] = SHIFT(22),
    },
    [20] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
    },
    [21] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
    },
    [22] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(54),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(54),
    },
    [23] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_quotient, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_quotient, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_quotient, 1),
        [ts_aux_sym_token5] = SHIFT(24),
        [ts_aux_sym_token6] = SHIFT(52),
    },
    [24] = {
        [ts_sym__operand2] = SHIFT(25),
        [ts_sym__operand3] = SHIFT(26),
        [ts_sym_exponent] = SHIFT(47),
        [ts_sym_grouping] = SHIFT(48),
        [ts_sym_number] = SHIFT(48),
        [ts_sym_variable] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(49),
    },
    [25] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_product, 3),
    },
    [26] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(27),
    },
    [27] = {
        [ts_sym__operand3] = SHIFT(28),
        [ts_sym_grouping] = SHIFT(29),
        [ts_sym_number] = SHIFT(29),
        [ts_sym_variable] = SHIFT(29),
        [ts_aux_sym_token1] = SHIFT(30),
    },
    [28] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 3),
    },
    [29] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
    },
    [30] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(45),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(45),
    },
    [31] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(32),
    },
    [32] = {
        [ts_sym__operand3] = SHIFT(33),
        [ts_sym_grouping] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_variable] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(35),
    },
    [33] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 3),
    },
    [34] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
    },
    [35] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(38),
    },
    [36] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
    },
    [37] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand2, 1),
    },
    [38] = {
        [ts_aux_sym_token2] = SHIFT(39),
    },
    [39] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
    },
    [40] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
    },
    [41] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand1, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand1, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand1, 1),
    },
    [42] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(43),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(43),
    },
    [43] = {
        [ts_aux_sym_token2] = SHIFT(44),
    },
    [44] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
    },
    [45] = {
        [ts_aux_sym_token2] = SHIFT(46),
    },
    [46] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
    },
    [47] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand2, 1),
    },
    [48] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
    },
    [49] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(50),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(50),
    },
    [50] = {
        [ts_aux_sym_token2] = SHIFT(51),
    },
    [51] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
    },
    [52] = {
        [ts_sym__operand2] = SHIFT(53),
        [ts_sym__operand3] = SHIFT(26),
        [ts_sym_exponent] = SHIFT(47),
        [ts_sym_grouping] = SHIFT(48),
        [ts_sym_number] = SHIFT(48),
        [ts_sym_variable] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(49),
    },
    [53] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_quotient, 3),
    },
    [54] = {
        [ts_aux_sym_token2] = SHIFT(55),
    },
    [55] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
    },
    [56] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand2, 1),
    },
    [57] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
    },
    [58] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(59),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(59),
    },
    [59] = {
        [ts_aux_sym_token2] = SHIFT(60),
    },
    [60] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
    },
    [61] = {
        [ts_sym__operand2] = SHIFT(62),
        [ts_sym__operand3] = SHIFT(18),
        [ts_sym_exponent] = SHIFT(56),
        [ts_sym_grouping] = SHIFT(57),
        [ts_sym_number] = SHIFT(57),
        [ts_sym_variable] = SHIFT(57),
        [ts_aux_sym_token1] = SHIFT(58),
    },
    [62] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_quotient, 3),
    },
    [63] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(64),
    },
    [64] = {
        [ts_sym__operand3] = SHIFT(65),
        [ts_sym_grouping] = SHIFT(66),
        [ts_sym_number] = SHIFT(66),
        [ts_sym_variable] = SHIFT(66),
        [ts_aux_sym_token1] = SHIFT(67),
    },
    [65] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 3),
    },
    [66] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
    },
    [67] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(68),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(68),
    },
    [68] = {
        [ts_aux_sym_token2] = SHIFT(69),
    },
    [69] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
    },
    [70] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand2, 1),
    },
    [71] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
    },
    [72] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym__operand1, 1),
    },
    [73] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(74),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(74),
    },
    [74] = {
        [ts_aux_sym_token2] = SHIFT(75),
    },
    [75] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
    },
    [76] = {
        [ts_sym__operand1] = SHIFT(77),
        [ts_sym__operand2] = SHIFT(15),
        [ts_sym__operand3] = SHIFT(63),
        [ts_sym_exponent] = SHIFT(70),
        [ts_sym_grouping] = SHIFT(71),
        [ts_sym_number] = SHIFT(71),
        [ts_sym_product] = SHIFT(72),
        [ts_sym_quotient] = SHIFT(72),
        [ts_sym_variable] = SHIFT(71),
        [ts_aux_sym_token1] = SHIFT(73),
    },
    [77] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_difference, 3),
    },
    [78] = {
        [ts_aux_sym_token2] = SHIFT(79),
    },
    [79] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [80] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand2, 1),
    },
    [81] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [82] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(83),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(83),
    },
    [83] = {
        [ts_aux_sym_token2] = SHIFT(84),
    },
    [84] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [85] = {
        [ts_sym__operand2] = SHIFT(86),
        [ts_sym__operand3] = SHIFT(7),
        [ts_sym_exponent] = SHIFT(80),
        [ts_sym_grouping] = SHIFT(81),
        [ts_sym_number] = SHIFT(81),
        [ts_sym_variable] = SHIFT(81),
        [ts_aux_sym_token1] = SHIFT(82),
    },
    [86] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 3),
    },
    [87] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(88),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 1),
    },
    [88] = {
        [ts_sym__operand3] = SHIFT(89),
        [ts_sym_grouping] = SHIFT(90),
        [ts_sym_number] = SHIFT(90),
        [ts_sym_variable] = SHIFT(90),
        [ts_aux_sym_token1] = SHIFT(91),
    },
    [89] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
    },
    [90] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [91] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(92),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(92),
    },
    [92] = {
        [ts_aux_sym_token2] = SHIFT(93),
    },
    [93] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [94] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand2, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand2, 1),
    },
    [95] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [96] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand1, 1),
    },
    [97] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(98),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(98),
    },
    [98] = {
        [ts_aux_sym_token2] = SHIFT(99),
    },
    [99] = {
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [100] = {
        [ts_sym__operand1] = SHIFT(101),
        [ts_sym__operand2] = SHIFT(4),
        [ts_sym__operand3] = SHIFT(87),
        [ts_sym_exponent] = SHIFT(94),
        [ts_sym_grouping] = SHIFT(95),
        [ts_sym_number] = SHIFT(95),
        [ts_sym_product] = SHIFT(96),
        [ts_sym_quotient] = SHIFT(96),
        [ts_sym_variable] = SHIFT(95),
        [ts_aux_sym_token1] = SHIFT(97),
    },
    [101] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_difference, 3),
    },
    [102] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_quotient, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_quotient, 1),
        [ts_aux_sym_token5] = SHIFT(103),
        [ts_aux_sym_token6] = SHIFT(117),
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 1),
    },
    [103] = {
        [ts_sym__operand2] = SHIFT(104),
        [ts_sym__operand3] = SHIFT(105),
        [ts_sym_exponent] = SHIFT(112),
        [ts_sym_grouping] = SHIFT(113),
        [ts_sym_number] = SHIFT(113),
        [ts_sym_variable] = SHIFT(113),
        [ts_aux_sym_token1] = SHIFT(114),
    },
    [104] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_product, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_product, 3),
    },
    [105] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 1),
    },
    [106] = {
        [ts_sym__operand3] = SHIFT(107),
        [ts_sym_grouping] = SHIFT(108),
        [ts_sym_number] = SHIFT(108),
        [ts_sym_variable] = SHIFT(108),
        [ts_aux_sym_token1] = SHIFT(109),
    },
    [107] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
    },
    [108] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [109] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(110),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(110),
    },
    [110] = {
        [ts_aux_sym_token2] = SHIFT(111),
    },
    [111] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [112] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand2, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand2, 1),
    },
    [113] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [114] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(115),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(115),
    },
    [115] = {
        [ts_aux_sym_token2] = SHIFT(116),
    },
    [116] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [117] = {
        [ts_sym__operand2] = SHIFT(118),
        [ts_sym__operand3] = SHIFT(105),
        [ts_sym_exponent] = SHIFT(112),
        [ts_sym_grouping] = SHIFT(113),
        [ts_sym_number] = SHIFT(113),
        [ts_sym_variable] = SHIFT(113),
        [ts_aux_sym_token1] = SHIFT(114),
    },
    [118] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_quotient, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 3),
    },
    [119] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 1),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 1),
    },
    [120] = {
        [ts_sym__operand3] = SHIFT(121),
        [ts_sym_grouping] = SHIFT(122),
        [ts_sym_number] = SHIFT(122),
        [ts_sym_variable] = SHIFT(122),
        [ts_aux_sym_token1] = SHIFT(123),
    },
    [121] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_exponent, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
    },
    [122] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [123] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(124),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(124),
    },
    [124] = {
        [ts_aux_sym_token2] = SHIFT(125),
    },
    [125] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
    [126] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
    },
    [127] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand2, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand2, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand2, 1),
    },
    [128] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [129] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym__operand3, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym__operand3, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand3, 1),
    },
    [130] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__operand1, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym__operand1, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym__operand1, 1),
    },
    [131] = {
        [ts_sym__operand1] = SHIFT(12),
        [ts_sym__operand2] = SHIFT(23),
        [ts_sym__operand3] = SHIFT(31),
        [ts_sym_difference] = SHIFT(36),
        [ts_sym_exponent] = SHIFT(37),
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_grouping] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_product] = SHIFT(41),
        [ts_sym_quotient] = SHIFT(41),
        [ts_sym_sum] = SHIFT(36),
        [ts_sym_variable] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(42),
        [ts_builtin_sym_error] = SHIFT(132),
    },
    [132] = {
        [ts_aux_sym_token2] = SHIFT(133),
    },
    [133] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_grouping, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_grouping, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_grouping, 3),
    },
};

EXPORT_PARSER(ts_parser_arithmetic);
