#include "tree_sitter/parser.h"

#define STATE_COUNT 69
#define SYMBOL_COUNT 19

enum {
    ts_sym_value = ts_builtin_sym_start,
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

static const char *ts_symbol_names[] = {
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
    [ts_aux_sym_object_repeat0] = "object_repeat0",
    [ts_aux_sym_array_repeat0] = "array_repeat0",
    [ts_aux_sym_1] = "'{'",
    [ts_aux_sym_2] = "':'",
    [ts_aux_sym_3] = "','",
    [ts_aux_sym_4] = "'}'",
    [ts_aux_sym_5] = "'['",
    [ts_aux_sym_6] = "']'",
};

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
    [ts_aux_sym_object_repeat0] = 1,
    [ts_aux_sym_array_repeat0] = 1,
    [ts_aux_sym_1] = 1,
    [ts_aux_sym_2] = 1,
    [ts_aux_sym_3] = 1,
    [ts_aux_sym_4] = 1,
    [ts_aux_sym_5] = 1,
    [ts_aux_sym_6] = 1,
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
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(ts_sym_string);
        case 4:
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            LEX_ERROR();
        case 5:
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
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
            if (lookahead == 0)
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
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
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
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
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
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
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
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
    [15] = 30,
    [16] = 32,
    [17] = 30,
    [18] = 33,
    [19] = 34,
    [20] = 30,
    [21] = 1,
    [22] = 33,
    [23] = 33,
    [24] = 26,
    [25] = 28,
    [26] = 30,
    [27] = 33,
    [28] = 32,
    [29] = 33,
    [30] = 33,
    [31] = 33,
    [32] = 34,
    [33] = 33,
    [34] = 1,
    [35] = 33,
    [36] = 36,
    [37] = 37,
    [38] = 33,
    [39] = 33,
    [40] = 34,
    [41] = 1,
    [42] = 33,
    [43] = 36,
    [44] = 36,
    [45] = 33,
    [46] = 36,
    [47] = 33,
    [48] = 33,
    [49] = 36,
    [50] = 30,
    [51] = 30,
    [52] = 36,
    [53] = 30,
    [54] = 30,
    [55] = 32,
    [56] = 24,
    [57] = 24,
    [58] = 33,
    [59] = 34,
    [60] = 24,
    [61] = 1,
    [62] = 33,
    [63] = 36,
    [64] = 24,
    [65] = 24,
    [66] = 36,
    [67] = 24,
    [68] = 24,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
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
        [ts_builtin_sym_error] = SHIFT(58),
        [ts_sym_string] = SHIFT(59),
        [ts_aux_sym_4] = SHIFT(60),
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
        [ts_aux_sym_array_repeat0] = SHIFT(55),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = SHIFT(56),
    },
    [6] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_value, 1),
    },
    [7] = {
        [ts_builtin_sym_error] = SHIFT(18),
        [ts_sym_string] = SHIFT(19),
        [ts_aux_sym_4] = SHIFT(20),
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
        [ts_aux_sym_6] = SHIFT(14),
    },
    [11] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 2),
    },
    [12] = {
        [ts_aux_sym_6] = SHIFT(17),
    },
    [13] = {
        [ts_sym_value] = SHIFT(15),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(15),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
    },
    [14] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 3),
    },
    [15] = {
        [ts_aux_sym_array_repeat0] = SHIFT(16),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 2),
    },
    [16] = {
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [17] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_array, 4),
    },
    [18] = {
        [ts_aux_sym_object_repeat0] = SHIFT(52),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = SHIFT(53),
    },
    [19] = {
        [ts_aux_sym_2] = SHIFT(21),
    },
    [20] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 2),
    },
    [21] = {
        [ts_sym_value] = SHIFT(22),
        [ts_sym_object] = SHIFT(23),
        [ts_sym_array] = SHIFT(23),
        [ts_sym_string] = SHIFT(23),
        [ts_sym_number] = SHIFT(23),
        [ts_sym_null] = SHIFT(23),
        [ts_sym_true] = SHIFT(23),
        [ts_sym_false] = SHIFT(23),
        [ts_aux_sym_1] = SHIFT(24),
        [ts_aux_sym_5] = SHIFT(25),
    },
    [22] = {
        [ts_aux_sym_object_repeat0] = SHIFT(49),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = SHIFT(50),
    },
    [23] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_value, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_value, 1),
    },
    [24] = {
        [ts_builtin_sym_error] = SHIFT(31),
        [ts_sym_string] = SHIFT(32),
        [ts_aux_sym_4] = SHIFT(33),
    },
    [25] = {
        [ts_sym_value] = SHIFT(26),
        [ts_sym_object] = SHIFT(6),
        [ts_sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(26),
        [ts_sym_string] = SHIFT(6),
        [ts_sym_number] = SHIFT(6),
        [ts_sym_null] = SHIFT(6),
        [ts_sym_true] = SHIFT(6),
        [ts_sym_false] = SHIFT(6),
        [ts_aux_sym_1] = SHIFT(7),
        [ts_aux_sym_5] = SHIFT(8),
        [ts_aux_sym_6] = SHIFT(27),
    },
    [26] = {
        [ts_aux_sym_array_repeat0] = SHIFT(28),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_6] = SHIFT(29),
    },
    [27] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 2),
    },
    [28] = {
        [ts_aux_sym_6] = SHIFT(30),
    },
    [29] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 3),
    },
    [30] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_array, 4),
    },
    [31] = {
        [ts_aux_sym_object_repeat0] = SHIFT(46),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = SHIFT(47),
    },
    [32] = {
        [ts_aux_sym_2] = SHIFT(34),
    },
    [33] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 2),
    },
    [34] = {
        [ts_sym_value] = SHIFT(35),
        [ts_sym_object] = SHIFT(23),
        [ts_sym_array] = SHIFT(23),
        [ts_sym_string] = SHIFT(23),
        [ts_sym_number] = SHIFT(23),
        [ts_sym_null] = SHIFT(23),
        [ts_sym_true] = SHIFT(23),
        [ts_sym_false] = SHIFT(23),
        [ts_aux_sym_1] = SHIFT(24),
        [ts_aux_sym_5] = SHIFT(25),
    },
    [35] = {
        [ts_aux_sym_object_repeat0] = SHIFT(36),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = SHIFT(38),
    },
    [36] = {
        [ts_aux_sym_4] = SHIFT(45),
    },
    [37] = {
        [ts_builtin_sym_error] = SHIFT(39),
        [ts_sym_string] = SHIFT(40),
    },
    [38] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 5),
    },
    [39] = {
        [ts_aux_sym_object_repeat0] = SHIFT(44),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 2),
    },
    [40] = {
        [ts_aux_sym_2] = SHIFT(41),
    },
    [41] = {
        [ts_sym_value] = SHIFT(42),
        [ts_sym_object] = SHIFT(23),
        [ts_sym_array] = SHIFT(23),
        [ts_sym_string] = SHIFT(23),
        [ts_sym_number] = SHIFT(23),
        [ts_sym_null] = SHIFT(23),
        [ts_sym_true] = SHIFT(23),
        [ts_sym_false] = SHIFT(23),
        [ts_aux_sym_1] = SHIFT(24),
        [ts_aux_sym_5] = SHIFT(25),
    },
    [42] = {
        [ts_aux_sym_object_repeat0] = SHIFT(43),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 4),
    },
    [43] = {
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [44] = {
        [ts_aux_sym_4] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [45] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 6),
    },
    [46] = {
        [ts_aux_sym_4] = SHIFT(48),
    },
    [47] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 3),
    },
    [48] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_object, 4),
    },
    [49] = {
        [ts_aux_sym_4] = SHIFT(51),
    },
    [50] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 5),
    },
    [51] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 6),
    },
    [52] = {
        [ts_aux_sym_4] = SHIFT(54),
    },
    [53] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 3),
    },
    [54] = {
        [ts_aux_sym_3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_object, 4),
    },
    [55] = {
        [ts_aux_sym_6] = SHIFT(57),
    },
    [56] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 3),
    },
    [57] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_array, 4),
    },
    [58] = {
        [ts_aux_sym_object_repeat0] = SHIFT(66),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = SHIFT(67),
    },
    [59] = {
        [ts_aux_sym_2] = SHIFT(61),
    },
    [60] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 2),
    },
    [61] = {
        [ts_sym_value] = SHIFT(62),
        [ts_sym_object] = SHIFT(23),
        [ts_sym_array] = SHIFT(23),
        [ts_sym_string] = SHIFT(23),
        [ts_sym_number] = SHIFT(23),
        [ts_sym_null] = SHIFT(23),
        [ts_sym_true] = SHIFT(23),
        [ts_sym_false] = SHIFT(23),
        [ts_aux_sym_1] = SHIFT(24),
        [ts_aux_sym_5] = SHIFT(25),
    },
    [62] = {
        [ts_aux_sym_object_repeat0] = SHIFT(63),
        [ts_aux_sym_3] = SHIFT(37),
        [ts_aux_sym_4] = SHIFT(64),
    },
    [63] = {
        [ts_aux_sym_4] = SHIFT(65),
    },
    [64] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 5),
    },
    [65] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 6),
    },
    [66] = {
        [ts_aux_sym_4] = SHIFT(68),
    },
    [67] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 3),
    },
    [68] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_object, 4),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_json);
