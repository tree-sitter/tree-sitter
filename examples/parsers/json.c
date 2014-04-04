#include "tree_sitter/parser.h"

STATE_COUNT = 60;
SYMBOL_COUNT = 18;

enum {
    ts_sym_array = 2,
    ts_sym_false = 3,
    ts_sym_null = 4,
    ts_sym_number = 5,
    ts_sym_object = 6,
    ts_sym_string = 7,
    ts_sym_true = 8,
    ts_sym_value = 9,
    ts_aux_sym_repeat_helper1 = 10,
    ts_aux_sym_repeat_helper2 = 11,
    ts_aux_sym_token1 = 12,
    ts_aux_sym_token2 = 13,
    ts_aux_sym_token3 = 14,
    ts_aux_sym_token4 = 15,
    ts_aux_sym_token5 = 16,
    ts_aux_sym_token6 = 17,
};

SYMBOL_NAMES = {
    [ts_sym_array] = "array",
    [ts_sym_false] = "false",
    [ts_sym_null] = "null",
    [ts_sym_number] = "number",
    [ts_sym_object] = "object",
    [ts_sym_string] = "string",
    [ts_sym_true] = "true",
    [ts_sym_value] = "value",
    [ts_aux_sym_repeat_helper1] = "repeat_helper1",
    [ts_aux_sym_repeat_helper2] = "repeat_helper2",
    [ts_aux_sym_token1] = "'{'",
    [ts_aux_sym_token2] = "':'",
    [ts_aux_sym_token3] = "','",
    [ts_aux_sym_token4] = "'}'",
    [ts_aux_sym_token5] = "'['",
    [ts_aux_sym_token6] = "']'",
    [ts_builtin_sym_end] = "end",
    [ts_builtin_sym_error] = "error",
};

HIDDEN_SYMBOLS = {
    [ts_aux_sym_repeat_helper1] = 1,
    [ts_aux_sym_repeat_helper2] = 1,
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
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(4);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 5:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(5);
            if (lookahead == '}')
                ADVANCE(4);
            LEX_ERROR();
        case 6:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 8:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(8);
            if (lookahead == ']')
                ADVANCE(7);
            LEX_ERROR();
        case 9:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(9);
            if (lookahead == '\"')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(18);
            if (lookahead == 'f')
                ADVANCE(19);
            if (lookahead == 'n')
                ADVANCE(24);
            if (lookahead == 't')
                ADVANCE(28);
            if (lookahead == '{')
                ADVANCE(32);
            LEX_ERROR();
        case 10:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(13);
            LEX_ERROR();
        case 11:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\"')
                ADVANCE(12);
            if (lookahead == '\\')
                ADVANCE(13);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_sym_string);
        case 13:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\"')
                ADVANCE(14);
            if (lookahead == '\\')
                ADVANCE(13);
            LEX_ERROR();
        case 14:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\"')
                ADVANCE(12);
            if (lookahead == '\\')
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_string);
        case 15:
            if (lookahead == '.')
                ADVANCE(16);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_number);
        case 16:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(17);
            ACCEPT_TOKEN(ts_sym_number);
        case 18:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 19:
            if (lookahead == 'a')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (lookahead == 'l')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 's')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if (lookahead == 'e')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(ts_sym_false);
        case 24:
            if (lookahead == 'u')
                ADVANCE(25);
            LEX_ERROR();
        case 25:
            if (lookahead == 'l')
                ADVANCE(26);
            LEX_ERROR();
        case 26:
            if (lookahead == 'l')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            ACCEPT_TOKEN(ts_sym_null);
        case 28:
            if (lookahead == 'r')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            if (lookahead == 'u')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            if (lookahead == 'e')
                ADVANCE(31);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(ts_sym_true);
        case 32:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 33:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == ':')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 35:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(35);
            if (lookahead == '\"')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(4);
            LEX_ERROR();
        case 36:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(36);
            if (lookahead == '\"')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(18);
            if (lookahead == ']')
                ADVANCE(7);
            if (lookahead == 'f')
                ADVANCE(19);
            if (lookahead == 'n')
                ADVANCE(24);
            if (lookahead == 't')
                ADVANCE(28);
            if (lookahead == '{')
                ADVANCE(32);
            LEX_ERROR();
        case 37:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 38:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(10);
            if (lookahead == ',')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            if (lookahead == ':')
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(18);
            if (lookahead == ']')
                ADVANCE(7);
            if (lookahead == 'f')
                ADVANCE(19);
            if (lookahead == 'n')
                ADVANCE(24);
            if (lookahead == 't')
                ADVANCE(28);
            if (lookahead == '{')
                ADVANCE(32);
            if (lookahead == '}')
                ADVANCE(4);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(10);
            if (lookahead == ',')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            if (lookahead == ':')
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(18);
            if (lookahead == ']')
                ADVANCE(7);
            if (lookahead == 'f')
                ADVANCE(19);
            if (lookahead == 'n')
                ADVANCE(24);
            if (lookahead == 't')
                ADVANCE(28);
            if (lookahead == '{')
                ADVANCE(32);
            if (lookahead == '}')
                ADVANCE(4);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 9,
    [1] = 0,
    [2] = 0,
    [3] = 35,
    [4] = 33,
    [5] = 9,
    [6] = 2,
    [7] = 2,
    [8] = 5,
    [9] = 0,
    [10] = 37,
    [11] = 33,
    [12] = 9,
    [13] = 2,
    [14] = 5,
    [15] = 35,
    [16] = 33,
    [17] = 9,
    [18] = 2,
    [19] = 5,
    [20] = 2,
    [21] = 36,
    [22] = 6,
    [23] = 6,
    [24] = 8,
    [25] = 2,
    [26] = 9,
    [27] = 6,
    [28] = 8,
    [29] = 35,
    [30] = 33,
    [31] = 9,
    [32] = 2,
    [33] = 5,
    [34] = 6,
    [35] = 6,
    [36] = 2,
    [37] = 5,
    [38] = 6,
    [39] = 36,
    [40] = 6,
    [41] = 8,
    [42] = 6,
    [43] = 6,
    [44] = 2,
    [45] = 2,
    [46] = 2,
    [47] = 5,
    [48] = 2,
    [49] = 2,
    [50] = 5,
    [51] = 0,
    [52] = 2,
    [53] = 5,
    [54] = 0,
    [55] = 36,
    [56] = 6,
    [57] = 8,
    [58] = 0,
    [59] = 0,
};

PARSE_TABLE = {
    [0] = {
        [ts_sym_array] = SHIFT(1),
        [ts_sym_false] = SHIFT(1),
        [ts_sym_null] = SHIFT(1),
        [ts_sym_number] = SHIFT(1),
        [ts_sym_object] = SHIFT(1),
        [ts_sym_string] = SHIFT(1),
        [ts_sym_true] = SHIFT(1),
        [ts_sym_value] = SHIFT(2),
        [ts_aux_sym_token1] = SHIFT(3),
        [ts_aux_sym_token5] = SHIFT(55),
    },
    [1] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_value, 1),
    },
    [2] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [3] = {
        [ts_sym_string] = SHIFT(4),
        [ts_aux_sym_token4] = SHIFT(51),
        [ts_builtin_sym_error] = SHIFT(52),
    },
    [4] = {
        [ts_aux_sym_token2] = SHIFT(5),
    },
    [5] = {
        [ts_sym_array] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_value] = SHIFT(7),
        [ts_aux_sym_token1] = SHIFT(15),
        [ts_aux_sym_token5] = SHIFT(21),
    },
    [6] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_value, 1),
    },
    [7] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(8),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [8] = {
        [ts_aux_sym_token4] = SHIFT(9),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 6),
    },
    [10] = {
        [ts_sym_string] = SHIFT(11),
        [ts_builtin_sym_error] = SHIFT(49),
    },
    [11] = {
        [ts_aux_sym_token2] = SHIFT(12),
    },
    [12] = {
        [ts_sym_array] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_value] = SHIFT(13),
        [ts_aux_sym_token1] = SHIFT(15),
        [ts_aux_sym_token5] = SHIFT(21),
    },
    [13] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(14),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [14] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 5),
    },
    [15] = {
        [ts_sym_string] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(46),
    },
    [16] = {
        [ts_aux_sym_token2] = SHIFT(17),
    },
    [17] = {
        [ts_sym_array] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_value] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(15),
        [ts_aux_sym_token5] = SHIFT(21),
    },
    [18] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(19),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [19] = {
        [ts_aux_sym_token4] = SHIFT(20),
    },
    [20] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
    },
    [21] = {
        [ts_sym_array] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_value] = SHIFT(23),
        [ts_aux_sym_token1] = SHIFT(29),
        [ts_aux_sym_token5] = SHIFT(39),
        [ts_aux_sym_token6] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(23),
    },
    [22] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_value, 1),
    },
    [23] = {
        [ts_aux_sym_repeat_helper2] = SHIFT(24),
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    [24] = {
        [ts_aux_sym_token6] = SHIFT(25),
    },
    [25] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
    },
    [26] = {
        [ts_sym_array] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_value] = SHIFT(27),
        [ts_aux_sym_token1] = SHIFT(29),
        [ts_aux_sym_token5] = SHIFT(39),
        [ts_builtin_sym_error] = SHIFT(27),
    },
    [27] = {
        [ts_aux_sym_repeat_helper2] = SHIFT(28),
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    [28] = {
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 3),
    },
    [29] = {
        [ts_sym_string] = SHIFT(30),
        [ts_aux_sym_token4] = SHIFT(35),
        [ts_builtin_sym_error] = SHIFT(36),
    },
    [30] = {
        [ts_aux_sym_token2] = SHIFT(31),
    },
    [31] = {
        [ts_sym_array] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_value] = SHIFT(32),
        [ts_aux_sym_token1] = SHIFT(15),
        [ts_aux_sym_token5] = SHIFT(21),
    },
    [32] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(33),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [33] = {
        [ts_aux_sym_token4] = SHIFT(34),
    },
    [34] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
    },
    [35] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
    },
    [36] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(37),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [37] = {
        [ts_aux_sym_token4] = SHIFT(38),
    },
    [38] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
    },
    [39] = {
        [ts_sym_array] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_value] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(29),
        [ts_aux_sym_token5] = SHIFT(39),
        [ts_aux_sym_token6] = SHIFT(43),
        [ts_builtin_sym_error] = SHIFT(40),
    },
    [40] = {
        [ts_aux_sym_repeat_helper2] = SHIFT(41),
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    [41] = {
        [ts_aux_sym_token6] = SHIFT(42),
    },
    [42] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
    },
    [43] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
    },
    [44] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
    },
    [45] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
    },
    [46] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(47),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [47] = {
        [ts_aux_sym_token4] = SHIFT(48),
    },
    [48] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
    },
    [49] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(50),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [50] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 3),
    },
    [51] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 2),
    },
    [52] = {
        [ts_aux_sym_repeat_helper1] = SHIFT(53),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [53] = {
        [ts_aux_sym_token4] = SHIFT(54),
    },
    [54] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 4),
    },
    [55] = {
        [ts_sym_array] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_value] = SHIFT(56),
        [ts_aux_sym_token1] = SHIFT(29),
        [ts_aux_sym_token5] = SHIFT(39),
        [ts_aux_sym_token6] = SHIFT(59),
        [ts_builtin_sym_error] = SHIFT(56),
    },
    [56] = {
        [ts_aux_sym_repeat_helper2] = SHIFT(57),
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    [57] = {
        [ts_aux_sym_token6] = SHIFT(58),
    },
    [58] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 4),
    },
    [59] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 2),
    },
};

EXPORT_PARSER(ts_parser_json);
