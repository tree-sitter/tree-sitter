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
            LEX_ERROR();
        case 1:
            if (lookahead == ')')
                ADVANCE(2);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 3:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 5:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 6:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '/')
                ADVANCE(8);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 8:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 9:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '/')
                ADVANCE(8);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 11:
            if (lookahead == '(')
                ADVANCE(12);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 13:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_number);
        case 14:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_number);
        case 15:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(16);
            ACCEPT_TOKEN(ts_sym_variable);
        case 16:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(16);
            ACCEPT_TOKEN(ts_sym_variable);
        case 17:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 18:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 19:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '/')
                ADVANCE(8);
            LEX_ERROR();
        case 20:
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '/')
                ADVANCE(8);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 21:
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 22:
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '/')
                ADVANCE(8);
            LEX_ERROR();
        case 23:
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '/')
                ADVANCE(8);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 24:
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            LEX_ERROR();
        case 25:
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case 26:
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '/')
                ADVANCE(8);
            LEX_ERROR();
        case 27:
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '/')
                ADVANCE(8);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '(')
                ADVANCE(12);
            if (lookahead == ')')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(4);
            if (lookahead == '-')
                ADVANCE(5);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '^')
                ADVANCE(10);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 11,
    [1] = 24,
    [2] = 11,
    [3] = 0,
    [4] = 22,
    [5] = 11,
    [6] = 0,
    [7] = 21,
    [8] = 11,
    [9] = 0,
    [10] = 0,
    [11] = 11,
    [12] = 3,
    [13] = 11,
    [14] = 1,
    [15] = 19,
    [16] = 11,
    [17] = 1,
    [18] = 18,
    [19] = 11,
    [20] = 1,
    [21] = 1,
    [22] = 11,
    [23] = 6,
    [24] = 11,
    [25] = 3,
    [26] = 17,
    [27] = 11,
    [28] = 3,
    [29] = 3,
    [30] = 11,
    [31] = 9,
    [32] = 11,
    [33] = 6,
    [34] = 6,
    [35] = 11,
    [36] = 1,
    [37] = 6,
    [38] = 1,
    [39] = 6,
    [40] = 9,
    [41] = 3,
    [42] = 11,
    [43] = 1,
    [44] = 9,
    [45] = 1,
    [46] = 3,
    [47] = 3,
    [48] = 17,
    [49] = 11,
    [50] = 1,
    [51] = 17,
    [52] = 11,
    [53] = 3,
    [54] = 1,
    [55] = 1,
    [56] = 1,
    [57] = 18,
    [58] = 11,
    [59] = 1,
    [60] = 18,
    [61] = 11,
    [62] = 1,
    [63] = 20,
    [64] = 11,
    [65] = 19,
    [66] = 19,
    [67] = 11,
    [68] = 1,
    [69] = 19,
    [70] = 19,
    [71] = 20,
    [72] = 1,
    [73] = 11,
    [74] = 1,
    [75] = 20,
    [76] = 11,
    [77] = 1,
    [78] = 1,
    [79] = 0,
    [80] = 0,
    [81] = 21,
    [82] = 11,
    [83] = 1,
    [84] = 21,
    [85] = 11,
    [86] = 0,
    [87] = 23,
    [88] = 11,
    [89] = 22,
    [90] = 22,
    [91] = 11,
    [92] = 1,
    [93] = 22,
    [94] = 22,
    [95] = 23,
    [96] = 0,
    [97] = 11,
    [98] = 1,
    [99] = 23,
    [100] = 11,
    [101] = 0,
    [102] = 26,
    [103] = 11,
    [104] = 24,
    [105] = 25,
    [106] = 11,
    [107] = 24,
    [108] = 24,
    [109] = 11,
    [110] = 1,
    [111] = 24,
    [112] = 24,
    [113] = 25,
    [114] = 11,
    [115] = 1,
    [116] = 25,
    [117] = 11,
    [118] = 24,
    [119] = 27,
    [120] = 11,
    [121] = 26,
    [122] = 26,
    [123] = 11,
    [124] = 1,
    [125] = 26,
    [126] = 0,
    [127] = 26,
    [128] = 0,
    [129] = 27,
    [130] = 24,
    [131] = 11,
    [132] = 1,
    [133] = 27,
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
        [ts_builtin_sym_end] = REDUCE(ts_sym_difference, 1),
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
        [ts_builtin_sym_end] = REDUCE(ts_sym_product, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_difference, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_product, 1),
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
        [ts_aux_sym_token4] = REDUCE(ts_sym_product, 1),
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
