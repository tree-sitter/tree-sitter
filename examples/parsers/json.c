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
    ts_aux_sym_1,
    ts_aux_sym_2,
    ts_aux_sym_3,
    ts_aux_sym_4,
    ts_aux_sym_5,
    ts_aux_sym_6,
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
    [ts_aux_sym_1] = "'{'",
    [ts_aux_sym_2] = "':'",
    [ts_aux_sym_3] = "','",
    [ts_aux_sym_4] = "'}'",
    [ts_aux_sym_5] = "'['",
    [ts_aux_sym_6] = "']'",
};

HIDDEN_SYMBOLS = {
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
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(2);
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
            ACCEPT_TOKEN(ts_aux_sym_5);
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
            ACCEPT_TOKEN(ts_aux_sym_1);
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
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 28:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(28);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 30:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(30);
            if (lookahead == ',')
                ADVANCE(31);
            if (lookahead == ']')
                ADVANCE(29);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 32:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(29);
            LEX_ERROR();
        case 33:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == ',')
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 34:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(34);
            if (lookahead == ':')
                ADVANCE(35);
            LEX_ERROR();
        case 35:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 36:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 37:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '\"')
                ADVANCE(2);
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
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(35);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
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
            if (lookahead == '\0')
                ADVANCE(25);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(35);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
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
    [0] = 1,
    [1] = 24,
    [2] = 24,
    [3] = 26,
    [4] = 28,
    [5] = 30,
    [6] = 30,
    [7] = 26,
    [8] = 28,
    [9] = 24,
    [10] = 30,
    [11] = 30,
    [12] = 32,
    [13] = 1,
    [14] = 30,
    [15] = 32,
    [16] = 30,
    [17] = 33,
    [18] = 34,
    [19] = 30,
    [20] = 1,
    [21] = 33,
    [22] = 33,
    [23] = 26,
    [24] = 28,
    [25] = 30,
    [26] = 33,
    [27] = 32,
    [28] = 33,
    [29] = 33,
    [30] = 34,
    [31] = 33,
    [32] = 1,
    [33] = 33,
    [34] = 36,
    [35] = 37,
    [36] = 33,
    [37] = 34,
    [38] = 1,
    [39] = 33,
    [40] = 36,
    [41] = 36,
    [42] = 33,
    [43] = 36,
    [44] = 33,
    [45] = 36,
    [46] = 30,
    [47] = 36,
    [48] = 30,
    [49] = 32,
    [50] = 24,
    [51] = 33,
    [52] = 34,
    [53] = 24,
    [54] = 1,
    [55] = 33,
    [56] = 36,
    [57] = 24,
    [58] = 36,
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
        [ts_aux_sym_1] = SHIFT(3),
        [ts_aux_sym_5] = SHIFT(4),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [2] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_value, 1),
    },
    [3] = {
        [ts_builtin_sym_error] = SHIFT(51),
        [ts_sym_string] = SHIFT(52),
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
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(9),
    },
    [5] = {
        [ts_aux_sym_array_repeat0] = SHIFT(49),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [6] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_value, 1),
    },
    [7] = {
        [ts_builtin_sym_error] = SHIFT(17),
        [ts_sym_string] = SHIFT(18),
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
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(11),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 2),
    },
    [10] = {
        [ts_aux_sym_array_repeat0] = SHIFT(12),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [11] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 2),
    },
    [12] = {
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
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
    },
    [14] = {
        [ts_aux_sym_array_repeat0] = SHIFT(15),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [15] = {
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [16] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 4),
    },
    [17] = {
        [ts_aux_sym_object_repeat0] = SHIFT(47),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [18] = {
        [ts_aux_sym_2] = SHIFT(20),
    },
    [19] = {
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
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [21] = {
        [ts_aux_sym_object_repeat0] = SHIFT(45),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [22] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_value, 1),
    },
    [23] = {
        [ts_builtin_sym_error] = SHIFT(29),
        [ts_sym_string] = SHIFT(30),
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
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(26),
    },
    [25] = {
        [ts_aux_sym_array_repeat0] = SHIFT(27),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [26] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 2),
    },
    [27] = {
        [ts_aux_sym_6] = SHIFT(28),
    },
    [28] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 4),
    },
    [29] = {
        [ts_aux_sym_object_repeat0] = SHIFT(43),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [30] = {
        [ts_aux_sym_2] = SHIFT(32),
    },
    [31] = {
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
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [33] = {
        [ts_aux_sym_object_repeat0] = SHIFT(34),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [34] = {
        [ts_aux_sym_4] = SHIFT(42),
    },
    [35] = {
        [ts_builtin_sym_error] = SHIFT(36),
        [ts_sym_string] = SHIFT(37),
    },
    [36] = {
        [ts_aux_sym_object_repeat0] = SHIFT(41),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [37] = {
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
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [39] = {
        [ts_aux_sym_object_repeat0] = SHIFT(40),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [40] = {
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [41] = {
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [42] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 6),
    },
    [43] = {
        [ts_aux_sym_4] = SHIFT(44),
    },
    [44] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 4),
    },
    [45] = {
        [ts_aux_sym_4] = SHIFT(46),
    },
    [46] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 6),
    },
    [47] = {
        [ts_aux_sym_4] = SHIFT(48),
    },
    [48] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 4),
    },
    [49] = {
        [ts_aux_sym_6] = SHIFT(50),
    },
    [50] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 4),
    },
    [51] = {
        [ts_aux_sym_object_repeat0] = SHIFT(58),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [52] = {
        [ts_aux_sym_2] = SHIFT(54),
    },
    [53] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 2),
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
        [ts_aux_sym_1] = SHIFT(23),
        [ts_aux_sym_5] = SHIFT(24),
    },
    [55] = {
        [ts_aux_sym_object_repeat0] = SHIFT(56),
        [ts_aux_sym_3] = SHIFT(35),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 0),
    },
    [56] = {
        [ts_aux_sym_4] = SHIFT(57),
    },
    [57] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 6),
    },
    [58] = {
        [ts_aux_sym_4] = SHIFT(59),
    },
    [59] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 4),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_json);
