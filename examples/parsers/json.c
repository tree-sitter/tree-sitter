#include "tree_sitter/parser.h"

#define STATE_COUNT 60
#define SYMBOL_COUNT 18

enum {
    ts_sym_value = ts_start_sym,
    ts_sym_object,
    ts_sym_array,
    ts_sym_string,
    ts_sym_number,
    ts_sym_null,
    ts_sym_true,
    ts_sym_false,
    ts_aux_sym_object_repeat0,
    ts_aux_sym_array_repeat0,
    ts_aux_sym_token0,
    ts_aux_sym_token1,
    ts_aux_sym_token2,
    ts_aux_sym_token3,
    ts_aux_sym_token4,
    ts_aux_sym_token5,
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
        case 1:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == '[')
                ADVANCE(10);
            if (lookahead == 'f')
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(20);
            if (lookahead == '{')
                ADVANCE(24);
            LEX_ERROR();
        case 2:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(5);
            LEX_ERROR();
        case 3:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_sym_string);
        case 5:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(5);
            LEX_ERROR();
        case 6:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym_string);
        case 7:
            if (lookahead == '.')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym_number);
        case 8:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_number);
        case 10:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 11:
            if (lookahead == 'a')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 'l')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 's')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            if (lookahead == 'e')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            ACCEPT_TOKEN(ts_sym_false);
        case 16:
            if (lookahead == 'u')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'l')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            if (lookahead == 'l')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_sym_null);
        case 20:
            if (lookahead == 'r')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 'u')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if (lookahead == 'e')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(ts_sym_true);
        case 24:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 25:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(26);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(25);
            LEX_ERROR();
        case 26:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 27:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(27);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 29:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(29);
            if (lookahead == ',')
                ADVANCE(30);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case 30:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 31:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case 32:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == '\"')
                ADVANCE(2);
            LEX_ERROR();
        case 33:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == ':')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 35:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(35);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == '[')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(36);
            if (lookahead == 'f')
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(20);
            if (lookahead == '{')
                ADVANCE(24);
            LEX_ERROR();
        case 36:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 37:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == ',')
                ADVANCE(30);
            if (lookahead == ']')
                ADVANCE(36);
            LEX_ERROR();
        case 38:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == ']')
                ADVANCE(36);
            LEX_ERROR();
        case 39:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(26);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(39);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(36);
            if (lookahead == 'f')
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(20);
            if (lookahead == '{')
                ADVANCE(24);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(26);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(39);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(36);
            if (lookahead == 'f')
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(20);
            if (lookahead == '{')
                ADVANCE(24);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 1,
    [1] = 25,
    [2] = 25,
    [3] = 27,
    [4] = 29,
    [5] = 31,
    [6] = 25,
    [7] = 32,
    [8] = 29,
    [9] = 31,
    [10] = 33,
    [11] = 1,
    [12] = 29,
    [13] = 31,
    [14] = 29,
    [15] = 27,
    [16] = 29,
    [17] = 31,
    [18] = 29,
    [19] = 33,
    [20] = 1,
    [21] = 29,
    [22] = 31,
    [23] = 29,
    [24] = 35,
    [25] = 37,
    [26] = 38,
    [27] = 29,
    [28] = 1,
    [29] = 37,
    [30] = 38,
    [31] = 37,
    [32] = 27,
    [33] = 29,
    [34] = 31,
    [35] = 37,
    [36] = 33,
    [37] = 1,
    [38] = 29,
    [39] = 31,
    [40] = 37,
    [41] = 37,
    [42] = 35,
    [43] = 37,
    [44] = 38,
    [45] = 37,
    [46] = 37,
    [47] = 29,
    [48] = 29,
    [49] = 33,
    [50] = 1,
    [51] = 29,
    [52] = 31,
    [53] = 25,
    [54] = 25,
    [55] = 35,
    [56] = 37,
    [57] = 38,
    [58] = 25,
    [59] = 25,
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
