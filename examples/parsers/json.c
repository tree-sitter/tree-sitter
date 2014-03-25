#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 18

enum {
    ts_sym_array,
    ts_sym_false,
    ts_sym_null,
    ts_sym_number,
    ts_sym_object,
    ts_sym_string,
    ts_sym_true,
    ts_sym_value,
    ts_aux_sym_repeat_helper1,
    ts_aux_sym_repeat_helper2,
    ts_aux_sym_token1,
    ts_aux_sym_token2,
    ts_aux_sym_token3,
    ts_aux_sym_token4,
    ts_aux_sym_token5,
    ts_aux_sym_token6,
};

SYMBOL_NAMES = {
    "array",
    "false",
    "null",
    "number",
    "object",
    "string",
    "true",
    "value",
    "repeat_helper1",
    "repeat_helper2",
    "token1",
    "token2",
    "token3",
    "token4",
    "token5",
    "token6",
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
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token4);
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
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 7:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(6);
            LEX_ERROR();
        case 8:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(24);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(30);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(34);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            LEX_ERROR();
        case 9:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(16);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(18);
            LEX_ERROR();
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
            LEX_ERROR();
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
            LEX_ERROR();
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
            LEX_ERROR();
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
            LEX_ERROR();
        case 16:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(17);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR();
        case 17:
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
        case 18:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 19:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(20);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 20:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_number);
        case 22:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_number);
        case 23:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(20);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 25:
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(26);
            LEX_ERROR();
        case 26:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            if (LOOKAHEAD_CHAR() == 's')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(ts_sym_false);
        case 30:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(31);
            LEX_ERROR();
        case 31:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(32);
            LEX_ERROR();
        case 32:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(33);
            LEX_ERROR();
        case 33:
            ACCEPT_TOKEN(ts_sym_null);
        case 34:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(35);
            LEX_ERROR();
        case 35:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(36);
            LEX_ERROR();
        case 36:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(37);
            LEX_ERROR();
        case 37:
            ACCEPT_TOKEN(ts_sym_true);
        case 38:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 39:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(40);
            LEX_ERROR();
        case 40:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 41:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(3);
            LEX_ERROR();
        case 42:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(24);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(30);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(34);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            LEX_ERROR();
        case 43:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            LEX_ERROR();
        case ts_lex_state_error:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(2);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(40);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(24);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(30);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(34);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(3);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

PARSE_TABLE() {
    START_TABLE(60)
    
    STATE(0);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_sym_value, 2)
    SHIFT(ts_aux_sym_token1, 3)
    SHIFT(ts_aux_sym_token5, 55)
    END_STATE();
    
    STATE(1);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_value, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(2);
    SET_LEX_STATE(0);
    ACCEPT_INPUT(ts_builtin_sym_end)
    END_STATE();
    
    STATE(3);
    SET_LEX_STATE(41);
    SHIFT(ts_sym_string, 4)
    SHIFT(ts_aux_sym_token4, 51)
    SHIFT(ts_builtin_sym_error, 52)
    END_STATE();
    
    STATE(4);
    SET_LEX_STATE(39);
    SHIFT(ts_aux_sym_token2, 5)
    END_STATE();
    
    STATE(5);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_false, 6)
    SHIFT(ts_sym_null, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_true, 6)
    SHIFT(ts_sym_value, 7)
    SHIFT(ts_aux_sym_token1, 15)
    SHIFT(ts_aux_sym_token5, 21)
    END_STATE();
    
    STATE(6);
    SET_LEX_STATE(1);
    REDUCE(ts_aux_sym_token3, ts_sym_value, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token4, ts_sym_value, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(7);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 8)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(8);
    SET_LEX_STATE(4);
    SHIFT(ts_aux_sym_token4, 9)
    END_STATE();
    
    STATE(9);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(10);
    SET_LEX_STATE(43);
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_builtin_sym_error, 49)
    END_STATE();
    
    STATE(11);
    SET_LEX_STATE(39);
    SHIFT(ts_aux_sym_token2, 12)
    END_STATE();
    
    STATE(12);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_false, 6)
    SHIFT(ts_sym_null, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_true, 6)
    SHIFT(ts_sym_value, 13)
    SHIFT(ts_aux_sym_token1, 15)
    SHIFT(ts_aux_sym_token5, 21)
    END_STATE();
    
    STATE(13);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 14)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(14);
    SET_LEX_STATE(4);
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 5, COLLAPSE({1, 0, 1, 0, 1}))
    END_STATE();
    
    STATE(15);
    SET_LEX_STATE(41);
    SHIFT(ts_sym_string, 16)
    SHIFT(ts_aux_sym_token4, 45)
    SHIFT(ts_builtin_sym_error, 46)
    END_STATE();
    
    STATE(16);
    SET_LEX_STATE(39);
    SHIFT(ts_aux_sym_token2, 17)
    END_STATE();
    
    STATE(17);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_false, 6)
    SHIFT(ts_sym_null, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_true, 6)
    SHIFT(ts_sym_value, 18)
    SHIFT(ts_aux_sym_token1, 15)
    SHIFT(ts_aux_sym_token5, 21)
    END_STATE();
    
    STATE(18);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 19)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(19);
    SET_LEX_STATE(4);
    SHIFT(ts_aux_sym_token4, 20)
    END_STATE();
    
    STATE(20);
    SET_LEX_STATE(1);
    REDUCE(ts_aux_sym_token3, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token4, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(21);
    SET_LEX_STATE(42);
    SHIFT(ts_sym_array, 22)
    SHIFT(ts_sym_false, 22)
    SHIFT(ts_sym_null, 22)
    SHIFT(ts_sym_number, 22)
    SHIFT(ts_sym_object, 22)
    SHIFT(ts_sym_string, 22)
    SHIFT(ts_sym_true, 22)
    SHIFT(ts_sym_value, 23)
    SHIFT(ts_aux_sym_token1, 29)
    SHIFT(ts_aux_sym_token5, 39)
    SHIFT(ts_aux_sym_token6, 44)
    SHIFT(ts_builtin_sym_error, 23)
    END_STATE();
    
    STATE(22);
    SET_LEX_STATE(5);
    REDUCE(ts_aux_sym_token3, ts_sym_value, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token6, ts_sym_value, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(23);
    SET_LEX_STATE(5);
    SHIFT(ts_aux_sym_repeat_helper2, 24)
    SHIFT(ts_aux_sym_token3, 26)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(24);
    SET_LEX_STATE(7);
    SHIFT(ts_aux_sym_token6, 25)
    END_STATE();
    
    STATE(25);
    SET_LEX_STATE(1);
    REDUCE(ts_aux_sym_token3, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token4, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(26);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 22)
    SHIFT(ts_sym_false, 22)
    SHIFT(ts_sym_null, 22)
    SHIFT(ts_sym_number, 22)
    SHIFT(ts_sym_object, 22)
    SHIFT(ts_sym_string, 22)
    SHIFT(ts_sym_true, 22)
    SHIFT(ts_sym_value, 27)
    SHIFT(ts_aux_sym_token1, 29)
    SHIFT(ts_aux_sym_token5, 39)
    SHIFT(ts_builtin_sym_error, 27)
    END_STATE();
    
    STATE(27);
    SET_LEX_STATE(5);
    SHIFT(ts_aux_sym_repeat_helper2, 28)
    SHIFT(ts_aux_sym_token3, 26)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(28);
    SET_LEX_STATE(7);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(29);
    SET_LEX_STATE(41);
    SHIFT(ts_sym_string, 30)
    SHIFT(ts_aux_sym_token4, 35)
    SHIFT(ts_builtin_sym_error, 36)
    END_STATE();
    
    STATE(30);
    SET_LEX_STATE(39);
    SHIFT(ts_aux_sym_token2, 31)
    END_STATE();
    
    STATE(31);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_array, 6)
    SHIFT(ts_sym_false, 6)
    SHIFT(ts_sym_null, 6)
    SHIFT(ts_sym_number, 6)
    SHIFT(ts_sym_object, 6)
    SHIFT(ts_sym_string, 6)
    SHIFT(ts_sym_true, 6)
    SHIFT(ts_sym_value, 32)
    SHIFT(ts_aux_sym_token1, 15)
    SHIFT(ts_aux_sym_token5, 21)
    END_STATE();
    
    STATE(32);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 33)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(33);
    SET_LEX_STATE(4);
    SHIFT(ts_aux_sym_token4, 34)
    END_STATE();
    
    STATE(34);
    SET_LEX_STATE(5);
    REDUCE(ts_aux_sym_token3, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(35);
    SET_LEX_STATE(5);
    REDUCE(ts_aux_sym_token3, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(36);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 37)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(37);
    SET_LEX_STATE(4);
    SHIFT(ts_aux_sym_token4, 38)
    END_STATE();
    
    STATE(38);
    SET_LEX_STATE(5);
    REDUCE(ts_aux_sym_token3, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(39);
    SET_LEX_STATE(42);
    SHIFT(ts_sym_array, 22)
    SHIFT(ts_sym_false, 22)
    SHIFT(ts_sym_null, 22)
    SHIFT(ts_sym_number, 22)
    SHIFT(ts_sym_object, 22)
    SHIFT(ts_sym_string, 22)
    SHIFT(ts_sym_true, 22)
    SHIFT(ts_sym_value, 40)
    SHIFT(ts_aux_sym_token1, 29)
    SHIFT(ts_aux_sym_token5, 39)
    SHIFT(ts_aux_sym_token6, 43)
    SHIFT(ts_builtin_sym_error, 40)
    END_STATE();
    
    STATE(40);
    SET_LEX_STATE(5);
    SHIFT(ts_aux_sym_repeat_helper2, 41)
    SHIFT(ts_aux_sym_token3, 26)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(41);
    SET_LEX_STATE(7);
    SHIFT(ts_aux_sym_token6, 42)
    END_STATE();
    
    STATE(42);
    SET_LEX_STATE(5);
    REDUCE(ts_aux_sym_token3, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(43);
    SET_LEX_STATE(5);
    REDUCE(ts_aux_sym_token3, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(44);
    SET_LEX_STATE(1);
    REDUCE(ts_aux_sym_token3, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token4, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(45);
    SET_LEX_STATE(1);
    REDUCE(ts_aux_sym_token3, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token4, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(46);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 47)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(47);
    SET_LEX_STATE(4);
    SHIFT(ts_aux_sym_token4, 48)
    END_STATE();
    
    STATE(48);
    SET_LEX_STATE(1);
    REDUCE(ts_aux_sym_token3, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token4, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(49);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 50)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(50);
    SET_LEX_STATE(4);
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(51);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(52);
    SET_LEX_STATE(1);
    SHIFT(ts_aux_sym_repeat_helper1, 53)
    SHIFT(ts_aux_sym_token3, 10)
    REDUCE(ts_aux_sym_token4, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(53);
    SET_LEX_STATE(4);
    SHIFT(ts_aux_sym_token4, 54)
    END_STATE();
    
    STATE(54);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(55);
    SET_LEX_STATE(42);
    SHIFT(ts_sym_array, 22)
    SHIFT(ts_sym_false, 22)
    SHIFT(ts_sym_null, 22)
    SHIFT(ts_sym_number, 22)
    SHIFT(ts_sym_object, 22)
    SHIFT(ts_sym_string, 22)
    SHIFT(ts_sym_true, 22)
    SHIFT(ts_sym_value, 56)
    SHIFT(ts_aux_sym_token1, 29)
    SHIFT(ts_aux_sym_token5, 39)
    SHIFT(ts_aux_sym_token6, 59)
    SHIFT(ts_builtin_sym_error, 56)
    END_STATE();
    
    STATE(56);
    SET_LEX_STATE(5);
    SHIFT(ts_aux_sym_repeat_helper2, 57)
    SHIFT(ts_aux_sym_token3, 26)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(57);
    SET_LEX_STATE(7);
    SHIFT(ts_aux_sym_token6, 58)
    END_STATE();
    
    STATE(58);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(59);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    END_TABLE();
}

EXPORT_PARSER(ts_parser_json);
