#include "tree_sitter/parser.h"

enum {
    ts_sym_array,
    ts_sym_number,
    ts_sym_object,
    ts_sym_string,
    ts_sym_value,
    ts_sym_colon,
    ts_sym_comma,
    ts_sym_left_brace,
    ts_sym_left_bracket,
    ts_sym_right_brace,
    ts_sym_right_bracket,
    ts_aux_sym_repeat_helper1,
    ts_aux_sym_repeat_helper2,
};

SYMBOL_NAMES {
    "array",
    "number",
    "object",
    "string",
    "value",
    "colon",
    "comma",
    "left_brace",
    "left_bracket",
    "right_brace",
    "right_bracket",
    "repeat_helper1",
    "repeat_helper2",
};

RECOVER_FN() {
    switch (state) {
        case 3:
            RECOVER(52, 2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
        case 8:
            RECOVER(47, 2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
        case 13:
            RECOVER(44, 2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
        case 19:
            RECOVER(21, 2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
        case 22:
            RECOVER(23, 2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
        case 25:
            RECOVER(32, 2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
        case 35:
            RECOVER(36, 2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
        case 55:
            RECOVER(56, 2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
        default:
            RECOVER(0, 0, EXPECT({}));
    }
}

LEX_FN() {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            LEX_ERROR();
        case 1:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(2);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(3);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_sym_comma);
        case 3:
            ACCEPT_TOKEN(ts_sym_right_brace);
        case 4:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(3);
            LEX_ERROR();
        case 5:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(2);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            ACCEPT_TOKEN(ts_sym_right_bracket);
        case 7:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(6);
            LEX_ERROR();
        case 8:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(15);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(16);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(17);
            LEX_ERROR();
        case 9:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 10:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_sym_string);
        case 12:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(13);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 13:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 14:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 15:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_number);
        case 16:
            ACCEPT_TOKEN(ts_sym_left_bracket);
        case 17:
            ACCEPT_TOKEN(ts_sym_left_brace);
        case 18:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_sym_colon);
        case 20:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(3);
            LEX_ERROR();
        case 21:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(15);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(16);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(17);
            LEX_ERROR();
        case 22:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(ts_sym_comma);
        case 24:
            ACCEPT_TOKEN(ts_sym_colon);
        case 25:
            ACCEPT_TOKEN(ts_sym_left_bracket);
        case 26:
            ACCEPT_TOKEN(ts_sym_right_bracket);
        case 27:
            ACCEPT_TOKEN(ts_sym_left_brace);
        case 28:
            ACCEPT_TOKEN(ts_sym_right_brace);
        case ts_lex_state_error:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(23);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(15);
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(24);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(28);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

PARSE_FN() {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(1);
                case ts_sym_number:
                    SHIFT(1);
                case ts_sym_object:
                    SHIFT(1);
                case ts_sym_string:
                    SHIFT(1);
                case ts_sym_value:
                    SHIFT(2);
                case ts_sym_left_brace:
                    SHIFT(3);
                case ts_sym_left_bracket:
                    SHIFT(55);
                default:
                    PARSE_ERROR(7, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket}));
            }
        case 1:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        case 2:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    ACCEPT_INPUT();
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        case 3:
            SET_LEX_STATE(20);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(4);
                case ts_sym_right_brace:
                    SHIFT(51);
                case ts_builtin_sym_error:
                    SHIFT(52);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_string, ts_sym_right_brace, ts_builtin_sym_error}));
            }
        case 4:
            SET_LEX_STATE(18);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(5);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_colon}));
            }
        case 5:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(6);
                case ts_sym_number:
                    SHIFT(6);
                case ts_sym_object:
                    SHIFT(6);
                case ts_sym_string:
                    SHIFT(6);
                case ts_sym_value:
                    SHIFT(7);
                case ts_sym_left_brace:
                    SHIFT(13);
                case ts_sym_left_bracket:
                    SHIFT(19);
                default:
                    PARSE_ERROR(7, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket}));
            }
        case 6:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
            }
        case 7:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(49);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 8:
            SET_LEX_STATE(22);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(9);
                case ts_builtin_sym_error:
                    SHIFT(47);
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_string, ts_builtin_sym_error}));
            }
        case 9:
            SET_LEX_STATE(18);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(10);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_colon}));
            }
        case 10:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(6);
                case ts_sym_number:
                    SHIFT(6);
                case ts_sym_object:
                    SHIFT(6);
                case ts_sym_string:
                    SHIFT(6);
                case ts_sym_value:
                    SHIFT(11);
                case ts_sym_left_brace:
                    SHIFT(13);
                case ts_sym_left_bracket:
                    SHIFT(19);
                default:
                    PARSE_ERROR(7, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket}));
            }
        case 11:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(12);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 12:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 5, COLLAPSE({1, 0, 1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 13:
            SET_LEX_STATE(20);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(14);
                case ts_sym_right_brace:
                    SHIFT(43);
                case ts_builtin_sym_error:
                    SHIFT(44);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_string, ts_sym_right_brace, ts_builtin_sym_error}));
            }
        case 14:
            SET_LEX_STATE(18);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(15);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_colon}));
            }
        case 15:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(6);
                case ts_sym_number:
                    SHIFT(6);
                case ts_sym_object:
                    SHIFT(6);
                case ts_sym_string:
                    SHIFT(6);
                case ts_sym_value:
                    SHIFT(16);
                case ts_sym_left_brace:
                    SHIFT(13);
                case ts_sym_left_bracket:
                    SHIFT(19);
                default:
                    PARSE_ERROR(7, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket}));
            }
        case 16:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(17);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 17:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(18);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 18:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
            }
        case 19:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(20);
                case ts_sym_number:
                    SHIFT(20);
                case ts_sym_object:
                    SHIFT(20);
                case ts_sym_string:
                    SHIFT(20);
                case ts_sym_value:
                    SHIFT(21);
                case ts_sym_left_brace:
                    SHIFT(25);
                case ts_sym_left_bracket:
                    SHIFT(35);
                case ts_sym_right_bracket:
                    SHIFT(42);
                case ts_builtin_sym_error:
                    SHIFT(21);
                default:
                    PARSE_ERROR(9, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket, ts_sym_right_bracket, ts_builtin_sym_error}));
            }
        case 20:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
            }
        case 21:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(40);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_bracket, ts_aux_sym_repeat_helper1}));
            }
        case 22:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(20);
                case ts_sym_number:
                    SHIFT(20);
                case ts_sym_object:
                    SHIFT(20);
                case ts_sym_string:
                    SHIFT(20);
                case ts_sym_value:
                    SHIFT(23);
                case ts_sym_left_brace:
                    SHIFT(25);
                case ts_sym_left_bracket:
                    SHIFT(35);
                case ts_builtin_sym_error:
                    SHIFT(23);
                default:
                    PARSE_ERROR(8, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket, ts_builtin_sym_error}));
            }
        case 23:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(24);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_bracket, ts_aux_sym_repeat_helper1}));
            }
        case 24:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_bracket}));
            }
        case 25:
            SET_LEX_STATE(20);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(26);
                case ts_sym_right_brace:
                    SHIFT(31);
                case ts_builtin_sym_error:
                    SHIFT(32);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_string, ts_sym_right_brace, ts_builtin_sym_error}));
            }
        case 26:
            SET_LEX_STATE(18);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(27);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_colon}));
            }
        case 27:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(6);
                case ts_sym_number:
                    SHIFT(6);
                case ts_sym_object:
                    SHIFT(6);
                case ts_sym_string:
                    SHIFT(6);
                case ts_sym_value:
                    SHIFT(28);
                case ts_sym_left_brace:
                    SHIFT(13);
                case ts_sym_left_bracket:
                    SHIFT(19);
                default:
                    PARSE_ERROR(7, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket}));
            }
        case 28:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(29);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 29:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(30);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 30:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
            }
        case 31:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
            }
        case 32:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(33);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 33:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(34);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 34:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
            }
        case 35:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(20);
                case ts_sym_number:
                    SHIFT(20);
                case ts_sym_object:
                    SHIFT(20);
                case ts_sym_string:
                    SHIFT(20);
                case ts_sym_value:
                    SHIFT(36);
                case ts_sym_left_brace:
                    SHIFT(25);
                case ts_sym_left_bracket:
                    SHIFT(35);
                case ts_sym_right_bracket:
                    SHIFT(39);
                case ts_builtin_sym_error:
                    SHIFT(36);
                default:
                    PARSE_ERROR(9, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket, ts_sym_right_bracket, ts_builtin_sym_error}));
            }
        case 36:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(37);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_bracket, ts_aux_sym_repeat_helper1}));
            }
        case 37:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    SHIFT(38);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_bracket}));
            }
        case 38:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
            }
        case 39:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_bracket}));
            }
        case 40:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    SHIFT(41);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_bracket}));
            }
        case 41:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
            }
        case 42:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
            }
        case 43:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
            }
        case 44:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(45);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 45:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(46);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 46:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_comma, ts_sym_right_brace}));
            }
        case 47:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(48);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 48:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 49:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(50);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 50:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        case 51:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        case 52:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(53);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_brace, ts_aux_sym_repeat_helper2}));
            }
        case 53:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(54);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_brace}));
            }
        case 54:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    REDUCE(ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        case 55:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_array:
                    SHIFT(20);
                case ts_sym_number:
                    SHIFT(20);
                case ts_sym_object:
                    SHIFT(20);
                case ts_sym_string:
                    SHIFT(20);
                case ts_sym_value:
                    SHIFT(56);
                case ts_sym_left_brace:
                    SHIFT(25);
                case ts_sym_left_bracket:
                    SHIFT(35);
                case ts_sym_right_bracket:
                    SHIFT(59);
                case ts_builtin_sym_error:
                    SHIFT(56);
                default:
                    PARSE_ERROR(9, EXPECT({ts_sym_array, ts_sym_number, ts_sym_object, ts_sym_string, ts_sym_value, ts_sym_left_brace, ts_sym_left_bracket, ts_sym_right_bracket, ts_builtin_sym_error}));
            }
        case 56:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(57);
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_comma, ts_sym_right_bracket, ts_aux_sym_repeat_helper1}));
            }
        case 57:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    SHIFT(58);
                default:
                    PARSE_ERROR(1, EXPECT({ts_sym_right_bracket}));
            }
        case 58:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        case 59:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_builtin_sym_end:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_builtin_sym_end}));
            }
        default:
            PARSE_PANIC();
    }
    FINISH_PARSER();
}

EXPORT_PARSER(ts_parse_config_json);
