#include "tree_sitter/parser.h"

#define STATE_COUNT 60
#define SYMBOL_COUNT 20

enum {
    ts_sym_value = ts_builtin_sym_start,
    ts_sym_object,
    ts_sym_array,
    ts_sym_string,
    ts_sym_number,
    ts_sym_null,
    ts_sym_true,
    ts_sym_false,
    ts_sym__whitespace,
    ts_aux_sym_object_repeat0,
    ts_aux_sym_array_repeat0,
    ts_aux_sym_1,
    ts_aux_sym_2,
    ts_aux_sym_3,
    ts_aux_sym_4,
    ts_aux_sym_5,
    ts_aux_sym_6,
};

SYMBOL_NAMES = {
    [ts_builtin_sym_document] = "DOCUMENT",
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
    [ts_sym__whitespace] = "_whitespace",
    [ts_aux_sym_object_repeat0] = "object_repeat0",
    [ts_aux_sym_array_repeat0] = "array_repeat0",
    [ts_aux_sym_1] = "'{'",
    [ts_aux_sym_2] = "':'",
    [ts_aux_sym_3] = "','",
    [ts_aux_sym_4] = "'}'",
    [ts_aux_sym_5] = "'['",
    [ts_aux_sym_6] = "']'",
};

HIDDEN_SYMBOLS = {
    [ts_sym__whitespace] = 1,
    [ts_aux_sym_object_repeat0] = 1,
    [ts_aux_sym_array_repeat0] = 1,
    [ts_aux_sym_1] = 1,
    [ts_aux_sym_2] = 1,
    [ts_aux_sym_3] = 1,
    [ts_aux_sym_4] = 1,
    [ts_aux_sym_5] = 1,
    [ts_aux_sym_6] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 1:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            ACCEPT_TOKEN(ts_sym__whitespace);
        case 3:
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_sym_string);
        case 5:
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(5);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            LEX_ERROR();
        case 6:
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
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
            ACCEPT_TOKEN(ts_aux_sym_5);
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
            ACCEPT_TOKEN(ts_aux_sym_1);
        case 25:
            if (lookahead == 0)
                ADVANCE(26);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            LEX_ERROR();
        case 26:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 27:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 29:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == '[')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(20);
            if (lookahead == '{')
                ADVANCE(24);
            LEX_ERROR();
        case 30:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 31:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(30);
            LEX_ERROR();
        case 32:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 33:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == ']')
                ADVANCE(30);
            LEX_ERROR();
        case 34:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(32);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case 35:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == ':')
                ADVANCE(36);
            LEX_ERROR();
        case 36:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 37:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(28);
            LEX_ERROR();
        case 38:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == 0)
                ADVANCE(26);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == ',')
                ADVANCE(32);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(36);
            if (lookahead == '[')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(30);
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
            LEX_ERROR();
    }
}

LEX_STATES = {
    [0] = 1,
    [1] = 25,
    [2] = 25,
    [3] = 27,
    [4] = 29,
    [5] = 31,
    [6] = 31,
    [7] = 27,
    [8] = 29,
    [9] = 25,
    [10] = 31,
    [11] = 31,
    [12] = 33,
    [13] = 1,
    [14] = 31,
    [15] = 33,
    [16] = 31,
    [17] = 34,
    [18] = 35,
    [19] = 31,
    [20] = 1,
    [21] = 34,
    [22] = 34,
    [23] = 27,
    [24] = 29,
    [25] = 31,
    [26] = 34,
    [27] = 33,
    [28] = 34,
    [29] = 34,
    [30] = 35,
    [31] = 34,
    [32] = 1,
    [33] = 34,
    [34] = 37,
    [35] = 38,
    [36] = 34,
    [37] = 35,
    [38] = 1,
    [39] = 34,
    [40] = 37,
    [41] = 37,
    [42] = 34,
    [43] = 37,
    [44] = 34,
    [45] = 37,
    [46] = 31,
    [47] = 37,
    [48] = 31,
    [49] = 33,
    [50] = 25,
    [51] = 34,
    [52] = 35,
    [53] = 25,
    [54] = 1,
    [55] = 34,
    [56] = 37,
    [57] = 25,
    [58] = 37,
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
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(3),
        [ts_aux_sym_5] = SHIFT(4),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [2] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_value, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [3] = {
        [ts_builtin_sym_error] = SHIFT(51),
        [ts_sym_string] = SHIFT(52),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(53),
    },
    [4] = {
        [ts_sym_value] = SHIFT(5),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(5),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(9),
    },
    [5] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_array_repeat0] = SHIFT(49),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [6] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_value, 1),
    },
    [7] = {
        [ts_builtin_sym_error] = SHIFT(17),
        [ts_sym_string] = SHIFT(18),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(19),
    },
    [8] = {
        [ts_sym_value] = SHIFT(10),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(10),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(11),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 2),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [10] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_array_repeat0] = SHIFT(12),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [11] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 2),
    },
    [12] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(16),
    },
    [13] = {
        [ts_sym_value] = SHIFT(14),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(14),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
    },
    [14] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_array_repeat0] = SHIFT(15),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [15] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [16] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 4),
    },
    [17] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(47),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [18] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(20),
    },
    [19] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 2),
    },
    [20] = {
        [ts_sym_value] = SHIFT(21),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_array] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [21] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(45),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [22] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_value, 1),
    },
    [23] = {
        [ts_builtin_sym_error] = SHIFT(29),
        [ts_sym_string] = SHIFT(30),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(31),
    },
    [24] = {
        [ts_sym_value] = SHIFT(25),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(25),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(26),
    },
    [25] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_array_repeat0] = SHIFT(27),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [26] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 2),
    },
    [27] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(28),
    },
    [28] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 4),
    },
    [29] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(43),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [30] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(32),
    },
    [31] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 2),
    },
    [32] = {
        [ts_sym_value] = SHIFT(33),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_array] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [33] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(34),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [34] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(42),
    },
    [35] = {
        [ts_builtin_sym_error] = SHIFT(36),
        [ts_sym_string] = SHIFT(37),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [36] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(41),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [37] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(38),
    },
    [38] = {
        [ts_sym_value] = SHIFT(39),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_array] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [39] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(40),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [40] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [41] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [42] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 6),
    },
    [43] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(44),
    },
    [44] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 4),
    },
    [45] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(46),
    },
    [46] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 6),
    },
    [47] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(48),
    },
    [48] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 4),
    },
    [49] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(50),
    },
    [50] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 4),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [51] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(58),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [52] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(54),
    },
    [53] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 2),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [54] = {
        [ts_sym_value] = SHIFT(55),
        [ts_sym_object] = SHIFT(22),
        [ts_sym_array] = SHIFT(22),
        [ts_sym_string] = SHIFT(22),
        [ts_sym_number] = SHIFT(22),
        [ts_sym_null] = SHIFT(22),
        [ts_sym_true] = SHIFT(22),
        [ts_sym_false] = SHIFT(22),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [55] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_object_repeat0] = SHIFT(56),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [56] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(57),
    },
    [57] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 6),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
    [58] = {
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(59),
    },
    [59] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 4),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_json);
