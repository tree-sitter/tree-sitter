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
    ts_aux_sym_end,
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
    "end",
    "repeat_helper1",
    "repeat_helper2",
};

LEX_FN() {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == '\0')
                ADVANCE(1);
            LEX_ERROR(1, EXPECT({"<EOF>"}));
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_end);
        case 2:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(3);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(4);
            LEX_ERROR(2, EXPECT({",", "}"}));
        case 3:
            ACCEPT_TOKEN(ts_sym_comma);
        case 4:
            ACCEPT_TOKEN(ts_sym_right_brace);
        case 5:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(4);
            LEX_ERROR(1, EXPECT({"}"}));
        case 6:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(3);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(7);
            LEX_ERROR(2, EXPECT({",", "]"}));
        case 7:
            ACCEPT_TOKEN(ts_sym_right_bracket);
        case 8:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(7);
            LEX_ERROR(1, EXPECT({"]"}));
        case 9:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(16);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(17);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(18);
            LEX_ERROR(4, EXPECT({"\"", "0-9", "[", "{"}));
        case 10:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR(1, EXPECT({"<ANY>"}));
        case 11:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR(1, EXPECT({"<ANY>"}));
        case 12:
            ACCEPT_TOKEN(ts_sym_string);
        case 13:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(14);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR(1, EXPECT({"<ANY>"}));
        case 14:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_string);
        case 15:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            LEX_ERROR(1, EXPECT({"\""}));
        case 16:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(16);
            ACCEPT_TOKEN(ts_sym_number);
        case 17:
            ACCEPT_TOKEN(ts_sym_left_bracket);
        case 18:
            ACCEPT_TOKEN(ts_sym_left_brace);
        case 19:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(20);
            LEX_ERROR(1, EXPECT({":"}));
        case 20:
            ACCEPT_TOKEN(ts_sym_colon);
        case 21:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(4);
            LEX_ERROR(2, EXPECT({"\"", "}"}));
        case 22:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(16);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(17);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(18);
            LEX_ERROR(5, EXPECT({"\"", "0-9", "[", "]", "{"}));
        case 23:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            LEX_ERROR(1, EXPECT({"\""}));
        default:
            LEX_PANIC();
    }
    FINISH_LEXER();
}

PARSE_FN() {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            SET_LEX_STATE(9);
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
                    SHIFT(44);
                default:
                    PARSE_PANIC();
            }
        case 1:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 2:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    ACCEPT_INPUT();
                default:
                    PARSE_PANIC();
            }
        case 3:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(4);
                case ts_sym_right_brace:
                    SHIFT(43);
                default:
                    PARSE_PANIC();
            }
        case 4:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(5);
                default:
                    PARSE_PANIC();
            }
        case 5:
            SET_LEX_STATE(9);
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
                    PARSE_PANIC();
            }
        case 6:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 7:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(41);
                default:
                    PARSE_PANIC();
            }
        case 8:
            SET_LEX_STATE(23);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(9);
                default:
                    PARSE_PANIC();
            }
        case 9:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(10);
                default:
                    PARSE_PANIC();
            }
        case 10:
            SET_LEX_STATE(9);
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
                    PARSE_PANIC();
            }
        case 11:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(12);
                default:
                    PARSE_PANIC();
            }
        case 12:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 5, COLLAPSE({1, 0, 1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 13:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(14);
                case ts_sym_right_brace:
                    SHIFT(40);
                default:
                    PARSE_PANIC();
            }
        case 14:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(15);
                default:
                    PARSE_PANIC();
            }
        case 15:
            SET_LEX_STATE(9);
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
                    PARSE_PANIC();
            }
        case 16:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(17);
                default:
                    PARSE_PANIC();
            }
        case 17:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(18);
                default:
                    PARSE_PANIC();
            }
        case 18:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 19:
            SET_LEX_STATE(22);
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
                    SHIFT(32);
                case ts_sym_right_bracket:
                    SHIFT(39);
                default:
                    PARSE_PANIC();
            }
        case 20:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_value, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 21:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(37);
                default:
                    PARSE_PANIC();
            }
        case 22:
            SET_LEX_STATE(9);
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
                    SHIFT(32);
                default:
                    PARSE_PANIC();
            }
        case 23:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(24);
                default:
                    PARSE_PANIC();
            }
        case 24:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 25:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_string:
                    SHIFT(26);
                case ts_sym_right_brace:
                    SHIFT(31);
                default:
                    PARSE_PANIC();
            }
        case 26:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_colon:
                    SHIFT(27);
                default:
                    PARSE_PANIC();
            }
        case 27:
            SET_LEX_STATE(9);
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
                    PARSE_PANIC();
            }
        case 28:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(8);
                case ts_sym_right_brace:
                    REDUCE(ts_aux_sym_repeat_helper2, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper2:
                    SHIFT(29);
                default:
                    PARSE_PANIC();
            }
        case 29:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(30);
                default:
                    PARSE_PANIC();
            }
        case 30:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 31:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 32:
            SET_LEX_STATE(22);
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
                    SHIFT(33);
                case ts_sym_left_brace:
                    SHIFT(25);
                case ts_sym_left_bracket:
                    SHIFT(32);
                case ts_sym_right_bracket:
                    SHIFT(36);
                default:
                    PARSE_PANIC();
            }
        case 33:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(34);
                default:
                    PARSE_PANIC();
            }
        case 34:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    SHIFT(35);
                default:
                    PARSE_PANIC();
            }
        case 35:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 36:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                case ts_sym_right_bracket:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 37:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    SHIFT(38);
                default:
                    PARSE_PANIC();
            }
        case 38:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 39:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 40:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                case ts_sym_right_brace:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 41:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_brace:
                    SHIFT(42);
                default:
                    PARSE_PANIC();
            }
        case 42:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 43:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_object, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 44:
            SET_LEX_STATE(22);
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
                    SHIFT(45);
                case ts_sym_left_brace:
                    SHIFT(25);
                case ts_sym_left_bracket:
                    SHIFT(32);
                case ts_sym_right_bracket:
                    SHIFT(48);
                default:
                    PARSE_PANIC();
            }
        case 45:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_comma:
                    SHIFT(22);
                case ts_sym_right_bracket:
                    REDUCE(ts_aux_sym_repeat_helper1, 0, COLLAPSE({}));
                case ts_aux_sym_repeat_helper1:
                    SHIFT(46);
                default:
                    PARSE_PANIC();
            }
        case 46:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_right_bracket:
                    SHIFT(47);
                default:
                    PARSE_PANIC();
            }
        case 47:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_PANIC();
            }
        case 48:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_array, 2, COLLAPSE({1, 1}));
                default:
                    PARSE_PANIC();
            }
        default:
            PARSE_PANIC();
    }
    FINISH_PARSER();
}

EXPORT_PARSER(ts_parse_config_json);
