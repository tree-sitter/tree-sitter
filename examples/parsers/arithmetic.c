#include "tree_sitter/parser.h"

enum {
    ts_sym_expression,
    ts_sym_factor,
    ts_sym_number,
    ts_sym_plus,
    ts_sym_term,
    ts_sym_times,
    ts_sym_variable,
    ts_aux_sym_token1,
    ts_aux_sym_token2,
};

SYMBOL_NAMES = {
    "expression",
    "factor",
    "number",
    "plus",
    "term",
    "times",
    "variable",
    "token1",
    "token2",
};

LEX_FN() {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            LEX_ERROR();
        case 1:
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_sym_plus);
        case 3:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 5:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(4);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 6:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(4);
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_sym_times);
        case 8:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(9);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(10);
            if (('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 10:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_number);
        case 11:
            if (('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_variable);
        case 12:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(4);
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(7);
            LEX_ERROR();
        case 13:
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 14:
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(7);
            LEX_ERROR();
        case ts_lex_state_error:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(4);
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(2);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(10);
            if (('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

PARSE_TABLE() {
    START_TABLE(52)
    
    STATE(0, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 1)
    SHIFT(ts_sym_factor, 2)
    SHIFT(ts_sym_number, 34)
    SHIFT(ts_sym_term, 35)
    SHIFT(ts_sym_variable, 34)
    SHIFT(ts_aux_sym_token1, 49)
    END_STATE();
    
    STATE(1, 11);
    SET_LEX_STATE(0);
    ACCEPT_INPUT(ts_builtin_sym_end)
    END_STATE();
    
    STATE(2, 11);
    SET_LEX_STATE(13);
    REDUCE(ts_sym_plus, ts_sym_term, 1, COLLAPSE({0}))
    SHIFT(ts_sym_times, 3)
    REDUCE(ts_builtin_sym_end, ts_sym_term, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(3, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_factor, 4)
    SHIFT(ts_sym_number, 5)
    SHIFT(ts_sym_variable, 5)
    SHIFT(ts_aux_sym_token1, 6)
    END_STATE();
    
    STATE(4, 11);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_plus, ts_sym_term, 3, COLLAPSE({0, 0, 0}))
    REDUCE(ts_builtin_sym_end, ts_sym_term, 3, COLLAPSE({0, 0, 0}))
    END_STATE();
    
    STATE(5, 11);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_plus, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(6, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 7)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 7)
    END_STATE();
    
    STATE(7, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 8)
    END_STATE();
    
    STATE(8, 11);
    SET_LEX_STATE(1);
    REDUCE(ts_sym_plus, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(9, 11);
    SET_LEX_STATE(6);
    REDUCE(ts_sym_plus, ts_sym_term, 1, COLLAPSE({0}))
    SHIFT(ts_sym_times, 10)
    REDUCE(ts_aux_sym_token2, ts_sym_term, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(10, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_factor, 11)
    SHIFT(ts_sym_number, 12)
    SHIFT(ts_sym_variable, 12)
    SHIFT(ts_aux_sym_token1, 13)
    END_STATE();
    
    STATE(11, 11);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_plus, ts_sym_term, 3, COLLAPSE({0, 0, 0}))
    REDUCE(ts_aux_sym_token2, ts_sym_term, 3, COLLAPSE({0, 0, 0}))
    END_STATE();
    
    STATE(12, 11);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_plus, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(13, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 14)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 14)
    END_STATE();
    
    STATE(14, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 15)
    END_STATE();
    
    STATE(15, 11);
    SET_LEX_STATE(5);
    REDUCE(ts_sym_plus, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(16, 11);
    SET_LEX_STATE(6);
    REDUCE(ts_sym_plus, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_sym_times, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(17, 11);
    SET_LEX_STATE(5);
    SHIFT(ts_sym_plus, 18)
    REDUCE(ts_aux_sym_token2, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(18, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_factor, 19)
    SHIFT(ts_sym_number, 29)
    SHIFT(ts_sym_term, 30)
    SHIFT(ts_sym_variable, 29)
    SHIFT(ts_aux_sym_token1, 31)
    END_STATE();
    
    STATE(19, 11);
    SET_LEX_STATE(12);
    SHIFT(ts_sym_times, 20)
    REDUCE(ts_aux_sym_token2, ts_sym_term, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(20, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_factor, 21)
    SHIFT(ts_sym_number, 22)
    SHIFT(ts_sym_variable, 22)
    SHIFT(ts_aux_sym_token1, 23)
    END_STATE();
    
    STATE(21, 11);
    SET_LEX_STATE(3);
    REDUCE(ts_aux_sym_token2, ts_sym_term, 3, COLLAPSE({0, 0, 0}))
    END_STATE();
    
    STATE(22, 11);
    SET_LEX_STATE(3);
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(23, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 24)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 24)
    END_STATE();
    
    STATE(24, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 25)
    END_STATE();
    
    STATE(25, 11);
    SET_LEX_STATE(3);
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(26, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 27)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 27)
    END_STATE();
    
    STATE(27, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 28)
    END_STATE();
    
    STATE(28, 11);
    SET_LEX_STATE(6);
    REDUCE(ts_sym_plus, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_sym_times, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(29, 11);
    SET_LEX_STATE(12);
    REDUCE(ts_sym_times, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(30, 11);
    SET_LEX_STATE(3);
    REDUCE(ts_aux_sym_token2, ts_sym_expression, 3, COLLAPSE({0, 0, 0}))
    END_STATE();
    
    STATE(31, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 32)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 32)
    END_STATE();
    
    STATE(32, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 33)
    END_STATE();
    
    STATE(33, 11);
    SET_LEX_STATE(12);
    REDUCE(ts_sym_times, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(34, 11);
    SET_LEX_STATE(13);
    REDUCE(ts_sym_plus, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_sym_times, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(35, 11);
    SET_LEX_STATE(1);
    SHIFT(ts_sym_plus, 36)
    REDUCE(ts_builtin_sym_end, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(36, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_factor, 37)
    SHIFT(ts_sym_number, 44)
    SHIFT(ts_sym_term, 45)
    SHIFT(ts_sym_variable, 44)
    SHIFT(ts_aux_sym_token1, 46)
    END_STATE();
    
    STATE(37, 11);
    SET_LEX_STATE(14);
    SHIFT(ts_sym_times, 38)
    REDUCE(ts_builtin_sym_end, ts_sym_term, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(38, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_factor, 39)
    SHIFT(ts_sym_number, 40)
    SHIFT(ts_sym_variable, 40)
    SHIFT(ts_aux_sym_token1, 41)
    END_STATE();
    
    STATE(39, 11);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_term, 3, COLLAPSE({0, 0, 0}))
    END_STATE();
    
    STATE(40, 11);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(41, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 42)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 42)
    END_STATE();
    
    STATE(42, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 43)
    END_STATE();
    
    STATE(43, 11);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(44, 11);
    SET_LEX_STATE(14);
    REDUCE(ts_sym_times, ts_sym_factor, 1, COLLAPSE({0}))
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(45, 11);
    SET_LEX_STATE(0);
    REDUCE(ts_builtin_sym_end, ts_sym_expression, 3, COLLAPSE({0, 0, 0}))
    END_STATE();
    
    STATE(46, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 47)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 47)
    END_STATE();
    
    STATE(47, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 48)
    END_STATE();
    
    STATE(48, 11);
    SET_LEX_STATE(14);
    REDUCE(ts_sym_times, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(49, 11);
    SET_LEX_STATE(8);
    SHIFT(ts_sym_expression, 50)
    SHIFT(ts_sym_factor, 9)
    SHIFT(ts_sym_number, 16)
    SHIFT(ts_sym_term, 17)
    SHIFT(ts_sym_variable, 16)
    SHIFT(ts_aux_sym_token1, 26)
    SHIFT(ts_builtin_sym_error, 50)
    END_STATE();
    
    STATE(50, 11);
    SET_LEX_STATE(3);
    SHIFT(ts_aux_sym_token2, 51)
    END_STATE();
    
    STATE(51, 11);
    SET_LEX_STATE(13);
    REDUCE(ts_sym_plus, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_sym_times, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_factor, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    END_TABLE();
}

EXPORT_PARSER(ts_parser_arithmetic);
