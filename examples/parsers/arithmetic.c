#include "tree_sitter/parser.h"

enum {
    ts_sym_expression,
    ts_sym_factor,
    ts_sym_number,
    ts_sym_plus,
    ts_sym_term,
    ts_sym_times,
    ts_sym_variable,
    ts_aux_sym_end,
    ts_aux_sym_token1,
    ts_aux_sym_token2,
};

SYMBOL_NAMES {
    "expression",
    "factor",
    "number",
    "plus",
    "term",
    "times",
    "variable",
    "end",
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
    FINISH_LEXER();
}

PARSE_FN() {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(1);
                case ts_sym_factor:
                    SHIFT(2);
                case ts_sym_number:
                    SHIFT(34);
                case ts_sym_term:
                    SHIFT(35);
                case ts_sym_variable:
                    SHIFT(34);
                case ts_aux_sym_token1:
                    SHIFT(49);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 1:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    ACCEPT_INPUT();
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_end}));
            }
        case 2:
            SET_LEX_STATE(13);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_term, 1, COLLAPSE({0}));
                case ts_sym_times:
                    SHIFT(3);
                case ts_aux_sym_end:
                    REDUCE(ts_sym_term, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_plus, ts_sym_times, ts_aux_sym_end}));
            }
        case 3:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_factor:
                    SHIFT(4);
                case ts_sym_number:
                    SHIFT(5);
                case ts_sym_variable:
                    SHIFT(5);
                case ts_aux_sym_token1:
                    SHIFT(6);
                default:
                    PARSE_ERROR(4, EXPECT({ts_sym_factor, ts_sym_number, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 4:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_term, 3, COLLAPSE({0, 0, 0}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_end}));
            }
        case 5:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_end}));
            }
        case 6:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(7);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 7:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(8);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 8:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_end}));
            }
        case 9:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_term, 1, COLLAPSE({0}));
                case ts_sym_times:
                    SHIFT(10);
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_term, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_plus, ts_sym_times, ts_aux_sym_token2}));
            }
        case 10:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_factor:
                    SHIFT(11);
                case ts_sym_number:
                    SHIFT(12);
                case ts_sym_variable:
                    SHIFT(12);
                case ts_aux_sym_token1:
                    SHIFT(13);
                default:
                    PARSE_ERROR(4, EXPECT({ts_sym_factor, ts_sym_number, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 11:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_term, 3, COLLAPSE({0, 0, 0}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_token2}));
            }
        case 12:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_token2}));
            }
        case 13:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(14);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 14:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(15);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 15:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_token2}));
            }
        case 16:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_plus, ts_sym_times, ts_aux_sym_token2}));
            }
        case 17:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    SHIFT(18);
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_expression, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_token2}));
            }
        case 18:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_factor:
                    SHIFT(19);
                case ts_sym_number:
                    SHIFT(29);
                case ts_sym_term:
                    SHIFT(30);
                case ts_sym_variable:
                    SHIFT(29);
                case ts_aux_sym_token1:
                    SHIFT(31);
                default:
                    PARSE_ERROR(5, EXPECT({ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 19:
            SET_LEX_STATE(12);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_times:
                    SHIFT(20);
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_term, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_times, ts_aux_sym_token2}));
            }
        case 20:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_factor:
                    SHIFT(21);
                case ts_sym_number:
                    SHIFT(22);
                case ts_sym_variable:
                    SHIFT(22);
                case ts_aux_sym_token1:
                    SHIFT(23);
                default:
                    PARSE_ERROR(4, EXPECT({ts_sym_factor, ts_sym_number, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 21:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 22:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 23:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(24);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 24:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(25);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 25:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 26:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(27);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 27:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(28);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 28:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_plus, ts_sym_times, ts_aux_sym_token2}));
            }
        case 29:
            SET_LEX_STATE(12);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_times, ts_aux_sym_token2}));
            }
        case 30:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_expression, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 31:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(32);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 32:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(33);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 33:
            SET_LEX_STATE(12);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_aux_sym_token2:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_times, ts_aux_sym_token2}));
            }
        case 34:
            SET_LEX_STATE(13);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_plus, ts_sym_times, ts_aux_sym_end}));
            }
        case 35:
            SET_LEX_STATE(1);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    SHIFT(36);
                case ts_aux_sym_end:
                    REDUCE(ts_sym_expression, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_plus, ts_aux_sym_end}));
            }
        case 36:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_factor:
                    SHIFT(37);
                case ts_sym_number:
                    SHIFT(44);
                case ts_sym_term:
                    SHIFT(45);
                case ts_sym_variable:
                    SHIFT(44);
                case ts_aux_sym_token1:
                    SHIFT(46);
                default:
                    PARSE_ERROR(5, EXPECT({ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 37:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_times:
                    SHIFT(38);
                case ts_aux_sym_end:
                    REDUCE(ts_sym_term, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_times, ts_aux_sym_end}));
            }
        case 38:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_factor:
                    SHIFT(39);
                case ts_sym_number:
                    SHIFT(40);
                case ts_sym_variable:
                    SHIFT(40);
                case ts_aux_sym_token1:
                    SHIFT(41);
                default:
                    PARSE_ERROR(4, EXPECT({ts_sym_factor, ts_sym_number, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 39:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_end}));
            }
        case 40:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_end}));
            }
        case 41:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(42);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 42:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(43);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 43:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_end}));
            }
        case 44:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_times, ts_aux_sym_end}));
            }
        case 45:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_end:
                    REDUCE(ts_sym_expression, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_end}));
            }
        case 46:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(47);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 47:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(48);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 48:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({ts_sym_times, ts_aux_sym_end}));
            }
        case 49:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_expression:
                    SHIFT(50);
                case ts_sym_factor:
                    SHIFT(9);
                case ts_sym_number:
                    SHIFT(16);
                case ts_sym_term:
                    SHIFT(17);
                case ts_sym_variable:
                    SHIFT(16);
                case ts_aux_sym_token1:
                    SHIFT(26);
                default:
                    PARSE_ERROR(6, EXPECT({ts_sym_expression, ts_sym_factor, ts_sym_number, ts_sym_term, ts_sym_variable, ts_aux_sym_token1}));
            }
        case 50:
            SET_LEX_STATE(3);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_sym_token2:
                    SHIFT(51);
                default:
                    PARSE_ERROR(1, EXPECT({ts_aux_sym_token2}));
            }
        case 51:
            SET_LEX_STATE(13);
            switch (LOOKAHEAD_SYM()) {
                case ts_sym_plus:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_sym_times:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_aux_sym_end:
                    REDUCE(ts_sym_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(3, EXPECT({ts_sym_plus, ts_sym_times, ts_aux_sym_end}));
            }
        default:
            PARSE_PANIC();
    }
    FINISH_PARSER();
}

EXPORT_PARSER(ts_parse_config_arithmetic);
