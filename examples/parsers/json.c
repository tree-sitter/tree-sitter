#include "tree_sitter/parser.h"

#define STATE_COUNT 60
#define SYMBOL_COUNT 18

enum {
    ts_sym_value = 2,
    ts_sym_object = 3,
    ts_sym_array = 4,
    ts_sym_string = 5,
    ts_sym_number = 6,
    ts_sym_null = 7,
    ts_sym_true = 8,
    ts_sym_false = 9,
    ts_aux_sym_object_repeat0 = 10,
    ts_aux_sym_array_repeat0 = 11,
    ts_aux_sym_token0 = 12,
    ts_aux_sym_token1 = 13,
    ts_aux_sym_token2 = 14,
    ts_aux_sym_token3 = 15,
    ts_aux_sym_token4 = 16,
    ts_aux_sym_token5 = 17,
};

SYMBOL_NAMES = {
    [ts_sym_value] = "value",
    [ts_sym_object] = "object",
    [ts_sym_array] = "array",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym_string] = "string",
    [ts_sym_number] = "number",
    [ts_sym_null] = "null",
    [ts_sym_true] = "true",
    [ts_sym_false] = "false",
    [ts_aux_sym_object_repeat0] = "object_repeat0",
    [ts_aux_sym_array_repeat0] = "array_repeat0",
    [ts_aux_sym_token0] = "'{'",
    [ts_aux_sym_token1] = "':'",
    [ts_aux_sym_token2] = "','",
    [ts_aux_sym_token3] = "'}'",
    [ts_aux_sym_token4] = "'['",
    [ts_aux_sym_token5] = "']'",
};

UBIQUITOUS_SYMBOLS = {
};

HIDDEN_SYMBOLS = {
    [ts_aux_sym_object_repeat0] = 1,
    [ts_aux_sym_array_repeat0] = 1,
    [ts_aux_sym_token0] = 1,
    [ts_aux_sym_token1] = 1,
    [ts_aux_sym_token2] = 1,
    [ts_aux_sym_token3] = 1,
    [ts_aux_sym_token4] = 1,
    [ts_aux_sym_token5] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 0:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\"')
                ADVANCE(1);
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
        case 1:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            if (lookahead == '\\')
                ADVANCE(4);
            LEX_ERROR();
        case 2:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(ts_sym_string);
        case 4:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(4);
            LEX_ERROR();
        case 5:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym_string);
        case 6:
            if (lookahead == '.')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            ACCEPT_TOKEN(ts_sym_number);
        case 7:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            ACCEPT_TOKEN(ts_sym_number);
        case 9:
            ACCEPT_TOKEN(ts_aux_sym_token4);
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
            ACCEPT_TOKEN(ts_sym_false);
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
            ACCEPT_TOKEN(ts_sym_null);
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
            ACCEPT_TOKEN(ts_sym_true);
        case 23:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 24:
            START_TOKEN();
            if (lookahead == '\0')
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
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(26);
            if (lookahead == '\"')
                ADVANCE(1);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 28:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(28);
            if (lookahead == ',')
                ADVANCE(29);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 30:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(30);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 31:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == '\"')
                ADVANCE(1);
            LEX_ERROR();
        case 32:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == ':')
                ADVANCE(33);
            LEX_ERROR();
        case 33:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 34:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(34);
            if (lookahead == '\"')
                ADVANCE(1);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(35);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            LEX_ERROR();
        case 35:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 36:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(36);
            if (lookahead == ',')
                ADVANCE(29);
            if (lookahead == ']')
                ADVANCE(35);
            LEX_ERROR();
        case 37:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == ']')
                ADVANCE(35);
            LEX_ERROR();
        case 38:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(25);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(1);
            if (lookahead == ',')
                ADVANCE(29);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(35);
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
            if (lookahead == '\0')
                ADVANCE(25);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(1);
            if (lookahead == ',')
                ADVANCE(29);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(35);
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
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 0,
    [1] = 24,
    [2] = 24,
    [3] = 26,
    [4] = 28,
    [5] = 30,
    [6] = 24,
    [7] = 31,
    [8] = 28,
    [9] = 30,
    [10] = 32,
    [11] = 0,
    [12] = 28,
    [13] = 30,
    [14] = 28,
    [15] = 26,
    [16] = 28,
    [17] = 30,
    [18] = 28,
    [19] = 32,
    [20] = 0,
    [21] = 28,
    [22] = 30,
    [23] = 28,
    [24] = 34,
    [25] = 36,
    [26] = 37,
    [27] = 28,
    [28] = 0,
    [29] = 36,
    [30] = 37,
    [31] = 36,
    [32] = 26,
    [33] = 28,
    [34] = 30,
    [35] = 36,
    [36] = 32,
    [37] = 0,
    [38] = 28,
    [39] = 30,
    [40] = 36,
    [41] = 36,
    [42] = 34,
    [43] = 36,
    [44] = 37,
    [45] = 36,
    [46] = 36,
    [47] = 28,
    [48] = 28,
    [49] = 32,
    [50] = 0,
    [51] = 28,
    [52] = 30,
    [53] = 24,
    [54] = 24,
    [55] = 34,
    [56] = 36,
    [57] = 37,
    [58] = 24,
    [59] = 24,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_value] = SHIFT(1),
        [ts_sym_object] = SHIFT(2),
        [ts_sym_array] = SHIFT(2),
        [ts_sym_string] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_null] = SHIFT(2),
        [ts_sym_true] = SHIFT(2),
        [ts_sym_false] = SHIFT(2),
        [ts_aux_sym_token0] = SHIFT(3),
        [ts_aux_sym_token4] = SHIFT(55),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [2] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_value, 1),
    },
    [3] = {
        [ts_builtin_sym_error] = SHIFT(4),
        [ts_sym_string] = SHIFT(49),
        [ts_aux_sym_token3] = SHIFT(54),
    },
    [4] = {
        [ts_aux_sym_object_repeat0] = SHIFT(5),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [5] = {
        [ts_aux_sym_token3] = SHIFT(6),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 4),
    },
    [7] = {
        [ts_builtin_sym_error] = SHIFT(8),
        [ts_sym_string] = SHIFT(10),
    },
    [8] = {
        [ts_aux_sym_object_repeat0] = SHIFT(9),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [9] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [10] = {
        [ts_aux_sym_token1] = SHIFT(11),
    },
    [11] = {
        [ts_sym_value] = SHIFT(12),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_false] = SHIFT(14),
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token4] = SHIFT(24),
    },
    [12] = {
        [ts_aux_sym_object_repeat0] = SHIFT(13),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [13] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [14] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_value, 1),
    },
    [15] = {
        [ts_builtin_sym_error] = SHIFT(16),
        [ts_sym_string] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(48),
    },
    [16] = {
        [ts_aux_sym_object_repeat0] = SHIFT(17),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [17] = {
        [ts_aux_sym_token3] = SHIFT(18),
    },
    [18] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
    },
    [19] = {
        [ts_aux_sym_token1] = SHIFT(20),
    },
    [20] = {
        [ts_sym_value] = SHIFT(21),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_false] = SHIFT(14),
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token4] = SHIFT(24),
    },
    [21] = {
        [ts_aux_sym_object_repeat0] = SHIFT(22),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [22] = {
        [ts_aux_sym_token3] = SHIFT(23),
    },
    [23] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
    },
    [24] = {
        [ts_sym_value] = SHIFT(25),
        [ts_sym_object] = SHIFT(31),
        [ts_sym_array] = SHIFT(31),
        [ts_builtin_sym_error] = SHIFT(25),
        [ts_sym_string] = SHIFT(31),
        [ts_sym_number] = SHIFT(31),
        [ts_sym_null] = SHIFT(31),
        [ts_sym_true] = SHIFT(31),
        [ts_sym_false] = SHIFT(31),
        [ts_aux_sym_token0] = SHIFT(32),
        [ts_aux_sym_token4] = SHIFT(42),
        [ts_aux_sym_token5] = SHIFT(47),
    },
    [25] = {
        [ts_aux_sym_array_repeat0] = SHIFT(26),
        [ts_aux_sym_token2] = SHIFT(28),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [26] = {
        [ts_aux_sym_token5] = SHIFT(27),
    },
    [27] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
    },
    [28] = {
        [ts_sym_value] = SHIFT(29),
        [ts_sym_object] = SHIFT(31),
        [ts_sym_array] = SHIFT(31),
        [ts_builtin_sym_error] = SHIFT(29),
        [ts_sym_string] = SHIFT(31),
        [ts_sym_number] = SHIFT(31),
        [ts_sym_null] = SHIFT(31),
        [ts_sym_true] = SHIFT(31),
        [ts_sym_false] = SHIFT(31),
        [ts_aux_sym_token0] = SHIFT(32),
        [ts_aux_sym_token4] = SHIFT(42),
    },
    [29] = {
        [ts_aux_sym_array_repeat0] = SHIFT(30),
        [ts_aux_sym_token2] = SHIFT(28),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [30] = {
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [31] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_value, 1),
    },
    [32] = {
        [ts_builtin_sym_error] = SHIFT(33),
        [ts_sym_string] = SHIFT(36),
        [ts_aux_sym_token3] = SHIFT(41),
    },
    [33] = {
        [ts_aux_sym_object_repeat0] = SHIFT(34),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [34] = {
        [ts_aux_sym_token3] = SHIFT(35),
    },
    [35] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
    },
    [36] = {
        [ts_aux_sym_token1] = SHIFT(37),
    },
    [37] = {
        [ts_sym_value] = SHIFT(38),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_false] = SHIFT(14),
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token4] = SHIFT(24),
    },
    [38] = {
        [ts_aux_sym_object_repeat0] = SHIFT(39),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [39] = {
        [ts_aux_sym_token3] = SHIFT(40),
    },
    [40] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
    },
    [41] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
    },
    [42] = {
        [ts_sym_value] = SHIFT(43),
        [ts_sym_object] = SHIFT(31),
        [ts_sym_array] = SHIFT(31),
        [ts_builtin_sym_error] = SHIFT(43),
        [ts_sym_string] = SHIFT(31),
        [ts_sym_number] = SHIFT(31),
        [ts_sym_null] = SHIFT(31),
        [ts_sym_true] = SHIFT(31),
        [ts_sym_false] = SHIFT(31),
        [ts_aux_sym_token0] = SHIFT(32),
        [ts_aux_sym_token4] = SHIFT(42),
        [ts_aux_sym_token5] = SHIFT(46),
    },
    [43] = {
        [ts_aux_sym_array_repeat0] = SHIFT(44),
        [ts_aux_sym_token2] = SHIFT(28),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [44] = {
        [ts_aux_sym_token5] = SHIFT(45),
    },
    [45] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
    },
    [46] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
    },
    [47] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
    },
    [48] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
    },
    [49] = {
        [ts_aux_sym_token1] = SHIFT(50),
    },
    [50] = {
        [ts_sym_value] = SHIFT(51),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_false] = SHIFT(14),
        [ts_aux_sym_token0] = SHIFT(15),
        [ts_aux_sym_token4] = SHIFT(24),
    },
    [51] = {
        [ts_aux_sym_object_repeat0] = SHIFT(52),
        [ts_aux_sym_token2] = SHIFT(7),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [52] = {
        [ts_aux_sym_token3] = SHIFT(53),
    },
    [53] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 6),
    },
    [54] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 2),
    },
    [55] = {
        [ts_sym_value] = SHIFT(56),
        [ts_sym_object] = SHIFT(31),
        [ts_sym_array] = SHIFT(31),
        [ts_builtin_sym_error] = SHIFT(56),
        [ts_sym_string] = SHIFT(31),
        [ts_sym_number] = SHIFT(31),
        [ts_sym_null] = SHIFT(31),
        [ts_sym_true] = SHIFT(31),
        [ts_sym_false] = SHIFT(31),
        [ts_aux_sym_token0] = SHIFT(32),
        [ts_aux_sym_token4] = SHIFT(42),
        [ts_aux_sym_token5] = SHIFT(59),
    },
    [56] = {
        [ts_aux_sym_array_repeat0] = SHIFT(57),
        [ts_aux_sym_token2] = SHIFT(28),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [57] = {
        [ts_aux_sym_token5] = SHIFT(58),
    },
    [58] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 4),
    },
    [59] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 2),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_json);
