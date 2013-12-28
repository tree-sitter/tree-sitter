#include "runtime.h"
#include <ctype.h>

typedef enum {
    ts_symbol_expression,
    ts_symbol_term,
    ts_symbol_right_paren,
    ts_symbol_number,
    ts_symbol_factor,
    ts_symbol_variable,
    ts_symbol_plus,
    ts_symbol_times,
    ts_symbol_left_paren,
    ts_symbol___END__
} ts_symbol;

static void ts_lex(TSParser *parser) {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(11);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(4);
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(1);
            LEX_ERROR();
        case 1:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(2);
            LEX_ERROR();
        case 2:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(3);
            LEX_ERROR();
        case 3:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(1);
            LEX_ERROR();
        case 4:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(6);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_symbol_left_paren);
        case 12:
            ACCEPT_TOKEN(ts_symbol___START__);
        case 13:
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(ts_symbol_plus);
        case 15:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(11);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(4);
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(2);
            LEX_ERROR();
        case 17:
            ACCEPT_TOKEN(ts_symbol_expression);
        case 18:
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_symbol_times);
        case 20:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(11);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(4);
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(16);
            LEX_ERROR();
        case 21:
            ACCEPT_TOKEN(ts_symbol_term);
        case 22:
            ACCEPT_TOKEN(ts_symbol_factor);
        case 23:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(11);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(4);
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(16);
            LEX_ERROR();
        case 24:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(25);
            LEX_ERROR();
        case 25:
            ACCEPT_TOKEN(ts_symbol_right_paren);
        case 26:
            ACCEPT_TOKEN(ts_symbol_factor);
        default:
            LEX_ERROR();
    }
    FINISH_LEXER();
}

TSTree ts_parse_arithmetic(const char *input) {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_left_paren:
                    SHIFT(9);
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(5);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_term:
                    SHIFT(2);
                case ts_symbol_expression:
                    SHIFT(1);
                default:
                    PARSE_ERROR();
            }
        case 1:
            SET_LEX_STATE(12);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    ACCEPT_INPUT();
                default:
                    PARSE_ERROR();
            }
        case 2:
            SET_LEX_STATE(13);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    SHIFT(3);
                default:
                    PARSE_ERROR();
            }
        case 3:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(5);
                case ts_symbol_left_paren:
                    SHIFT(9);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_term:
                    SHIFT(4);
                default:
                    PARSE_ERROR();
            }
        case 4:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_expression, 3);
            }
        case 5:
            SET_LEX_STATE(18);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    SHIFT(6);
                default:
                    PARSE_ERROR();
            }
        case 6:
            SET_LEX_STATE(20);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_left_paren:
                    SHIFT(9);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(7);
                default:
                    PARSE_ERROR();
            }
        case 7:
            SET_LEX_STATE(21);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_term, 3);
            }
        case 8:
            SET_LEX_STATE(22);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_factor, 1);
            }
        case 9:
            SET_LEX_STATE(23);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_left_paren:
                    SHIFT(9);
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(5);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_term:
                    SHIFT(2);
                case ts_symbol_expression:
                    SHIFT(10);
                default:
                    PARSE_ERROR();
            }
        case 10:
            SET_LEX_STATE(24);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_right_paren:
                    SHIFT(11);
                default:
                    PARSE_ERROR();
            }
        case 11:
            SET_LEX_STATE(26);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_factor, 3);
            }
        default:
            PARSE_ERROR();
    }
    FINISH_PARSER();
}
