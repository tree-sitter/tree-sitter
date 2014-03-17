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

SYMBOL_NAMES = {
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

PARSE_TABLE() {
    START_TABLE(60)
    
    STATE(0, 15);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_value, 2)
    SHIFT(ts_sym_left_brace, 3)
    SHIFT(ts_sym_left_bracket, 55)
    END_STATE();
    
    STATE(1, 15);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_value, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(2, 15);
    SET_LEX_STATE(0);
    ACCEPT_INPUT(ts_builtin_sym_end)
    END_STATE();
    
    STATE(3, 15);
    SET_LEX_STATE(20);
    SHIFT(ts_sym_string, 4)
    SHIFT(ts_sym_right_brace, 51)
    SHIFT(ts_builtin_sym_error, 52)
    END_STATE();
    
    STATE(4, 15);
    SET_LEX_STATE(18);
    SHIFT(ts_sym_colon, 5)
    END_STATE();
    
    STATE(5, 15);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_value, 7)
    SHIFT(ts_sym_left_brace, 13)
    SHIFT(ts_sym_left_bracket, 19)
    END_STATE();
    
    STATE(6, 15);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_comma, ts_sym_value, 1, COLLAPSE({0}))
    REDUCE(ts_sym_right_brace, ts_sym_value, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(7, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 49)
    END_STATE();
    
    STATE(8, 15);
    SET_LEX_STATE(22);
    SHIFT(ts_sym_string, 9)
    SHIFT(ts_builtin_sym_error, 47)
    END_STATE();
    
    STATE(9, 15);
    SET_LEX_STATE(18);
    SHIFT(ts_sym_colon, 10)
    END_STATE();
    
    STATE(10, 15);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_value, 11)
    SHIFT(ts_sym_left_brace, 13)
    SHIFT(ts_sym_left_bracket, 19)
    END_STATE();
    
    STATE(11, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 12)
    END_STATE();
    
    STATE(12, 15);
    SET_LEX_STATE(4);
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 5, COLLAPSE({1, 0, 1, 0, 1}))
    END_STATE();
    
    STATE(13, 15);
    SET_LEX_STATE(20);
    SHIFT(ts_sym_string, 14)
    SHIFT(ts_sym_right_brace, 43)
    SHIFT(ts_builtin_sym_error, 44)
    END_STATE();
    
    STATE(14, 15);
    SET_LEX_STATE(18);
    SHIFT(ts_sym_colon, 15)
    END_STATE();
    
    STATE(15, 15);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_value, 16)
    SHIFT(ts_sym_left_brace, 13)
    SHIFT(ts_sym_left_bracket, 19)
    END_STATE();
    
    STATE(16, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 17)
    END_STATE();
    
    STATE(17, 15);
    SET_LEX_STATE(4);
    SHIFT(ts_sym_right_brace, 18)
    END_STATE();
    
    STATE(18, 15);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_comma, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_sym_right_brace, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(19, 15);
    SET_LEX_STATE(21);
    SHIFT(ts_sym_array, 20)
    SHIFT(ts_sym_number, 20)
    SHIFT(ts_sym_object, 20)
    SHIFT(ts_sym_string, 20)
    SHIFT(ts_sym_value, 21)
    SHIFT(ts_sym_left_brace, 25)
    SHIFT(ts_sym_left_bracket, 35)
    SHIFT(ts_sym_right_bracket, 42)
    SHIFT(ts_builtin_sym_error, 21)
    END_STATE();
    
    STATE(20, 15);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_comma, ts_sym_value, 1, COLLAPSE({0}))
    REDUCE(ts_sym_right_bracket, ts_sym_value, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(21, 15);
    SET_LEX_STATE(5);
    SHIFT(ts_sym_comma, 22)
    REDUCE(ts_sym_right_bracket, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper1, 40)
    END_STATE();
    
    STATE(22, 15);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 20)
    SHIFT(ts_sym_number, 20)
    SHIFT(ts_sym_object, 20)
    SHIFT(ts_sym_string, 20)
    SHIFT(ts_sym_value, 23)
    SHIFT(ts_sym_left_brace, 25)
    SHIFT(ts_sym_left_bracket, 35)
    SHIFT(ts_builtin_sym_error, 23)
    END_STATE();
    
    STATE(23, 15);
    SET_LEX_STATE(5);
    SHIFT(ts_sym_comma, 22)
    REDUCE(ts_sym_right_bracket, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper1, 24)
    END_STATE();
    
    STATE(24, 15);
    SET_LEX_STATE(7);
    REDUCE(ts_sym_right_bracket, ts_aux_sym_repeat_helper1, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(25, 15);
    SET_LEX_STATE(20);
    SHIFT(ts_sym_string, 26)
    SHIFT(ts_sym_right_brace, 31)
    SHIFT(ts_builtin_sym_error, 32)
    END_STATE();
    
    STATE(26, 15);
    SET_LEX_STATE(18);
    SHIFT(ts_sym_colon, 27)
    END_STATE();
    
    STATE(27, 15);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_value, 28)
    SHIFT(ts_sym_left_brace, 13)
    SHIFT(ts_sym_left_bracket, 19)
    END_STATE();
    
    STATE(28, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 29)
    END_STATE();
    
    STATE(29, 15);
    SET_LEX_STATE(4);
    SHIFT(ts_sym_right_brace, 30)
    END_STATE();
    
    STATE(30, 15);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_comma, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_sym_right_bracket, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(31, 15);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_comma, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_sym_right_bracket, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(32, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 33)
    END_STATE();
    
    STATE(33, 15);
    SET_LEX_STATE(4);
    SHIFT(ts_sym_right_brace, 34)
    END_STATE();
    
    STATE(34, 15);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_comma, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_sym_right_bracket, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(35, 15);
    SET_LEX_STATE(21);
    SHIFT(ts_sym_array, 20)
    SHIFT(ts_sym_number, 20)
    SHIFT(ts_sym_object, 20)
    SHIFT(ts_sym_string, 20)
    SHIFT(ts_sym_value, 36)
    SHIFT(ts_sym_left_brace, 25)
    SHIFT(ts_sym_left_bracket, 35)
    SHIFT(ts_sym_right_bracket, 39)
    SHIFT(ts_builtin_sym_error, 36)
    END_STATE();
    
    STATE(36, 15);
    SET_LEX_STATE(5);
    SHIFT(ts_sym_comma, 22)
    REDUCE(ts_sym_right_bracket, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper1, 37)
    END_STATE();
    
    STATE(37, 15);
    SET_LEX_STATE(7);
    SHIFT(ts_sym_right_bracket, 38)
    END_STATE();
    
    STATE(38, 15);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_comma, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_sym_right_bracket, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(39, 15);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_comma, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_sym_right_bracket, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(40, 15);
    SET_LEX_STATE(7);
    SHIFT(ts_sym_right_bracket, 41)
    END_STATE();
    
    STATE(41, 15);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_comma, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_sym_right_brace, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(42, 15);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_comma, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_sym_right_brace, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(43, 15);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_comma, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_sym_right_brace, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(44, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 45)
    END_STATE();
    
    STATE(45, 15);
    SET_LEX_STATE(4);
    SHIFT(ts_sym_right_brace, 46)
    END_STATE();
    
    STATE(46, 15);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_comma, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_sym_right_brace, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(47, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 48)
    END_STATE();
    
    STATE(48, 15);
    SET_LEX_STATE(4);
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(49, 15);
    SET_LEX_STATE(4);
    SHIFT(ts_sym_right_brace, 50)
    END_STATE();
    
    STATE(50, 15);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(51, 15);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(52, 15);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_comma, 8)
    REDUCE(ts_sym_right_brace, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper2, 53)
    END_STATE();
    
    STATE(53, 15);
    SET_LEX_STATE(4);
    SHIFT(ts_sym_right_brace, 54)
    END_STATE();
    
    STATE(54, 15);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(55, 15);
    SET_LEX_STATE(21);
    SHIFT(ts_sym_array, 20)
    SHIFT(ts_sym_number, 20)
    SHIFT(ts_sym_object, 20)
    SHIFT(ts_sym_string, 20)
    SHIFT(ts_sym_value, 56)
    SHIFT(ts_sym_left_brace, 25)
    SHIFT(ts_sym_left_bracket, 35)
    SHIFT(ts_sym_right_bracket, 59)
    SHIFT(ts_builtin_sym_error, 56)
    END_STATE();
    
    STATE(56, 15);
    SET_LEX_STATE(5);
    SHIFT(ts_sym_comma, 22)
    REDUCE(ts_sym_right_bracket, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_repeat_helper1, 57)
    END_STATE();
    
    STATE(57, 15);
    SET_LEX_STATE(7);
    SHIFT(ts_sym_right_bracket, 58)
    END_STATE();
    
    STATE(58, 15);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(59, 15);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    END_TABLE();
}

EXPORT_PARSER(ts_parser_json);
