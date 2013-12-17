#include "runtime.h"
#include <stdlib.h>


typedef enum {
    ts_symbol_type_expression,
    ts_symbol_type_term,
    ts_symbol_type_right_paren,
    ts_symbol_type_number,
    ts_symbol_type_factor,
    ts_symbol_type_variable,
    ts_symbol_type_plus,
    ts_symbol_type_times,
    ts_symbol_type_left_paren,
    ts_symbol_type___END__
} ts_symbol_type;


TSTree ts_parse_arithmetic(const char *input) {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_left_paren:
                    SHIFT(9);
                case ts_symbol_type_variable:
                    SHIFT(8);
                case ts_symbol_type_factor:
                    SHIFT(5);
                case ts_symbol_type_number:
                    SHIFT(8);
                case ts_symbol_type_term:
                    SHIFT(2);
                case ts_symbol_type_expression:
                    SHIFT(1);
                default:
                    ERROR();
            }
        case 1:
            switch (LOOKAHEAD()) {
                case ts_symbol_type___END__:
                    ACCEPT();
                default:
                    ERROR();
            }
        case 2:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_plus:
                    SHIFT(3);
                default:
                    ERROR();
            }
        case 3:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_variable:
                    SHIFT(8);
                case ts_symbol_type_factor:
                    SHIFT(5);
                case ts_symbol_type_left_paren:
                    SHIFT(9);
                case ts_symbol_type_number:
                    SHIFT(8);
                case ts_symbol_type_term:
                    SHIFT(4);
                default:
                    ERROR();
            }
        case 4:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_expression:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_term:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_right_paren:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_number:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_factor:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_variable:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_times:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_plus:
                    REDUCE(ts_symbol_type_expression, 3);
                case ts_symbol_type_left_paren:
                    REDUCE(ts_symbol_type_expression, 3);
                default:
                    ERROR();
            }
        case 5:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_times:
                    SHIFT(6);
                default:
                    ERROR();
            }
        case 6:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_left_paren:
                    SHIFT(9);
                case ts_symbol_type_number:
                    SHIFT(8);
                case ts_symbol_type_variable:
                    SHIFT(8);
                case ts_symbol_type_factor:
                    SHIFT(7);
                default:
                    ERROR();
            }
        case 7:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_expression:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_term:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_right_paren:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_number:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_factor:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_variable:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_times:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_plus:
                    REDUCE(ts_symbol_type_term, 3);
                case ts_symbol_type_left_paren:
                    REDUCE(ts_symbol_type_term, 3);
                default:
                    ERROR();
            }
        case 8:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_expression:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_term:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_right_paren:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_number:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_factor:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_variable:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_times:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_plus:
                    REDUCE(ts_symbol_type_factor, 1);
                case ts_symbol_type_left_paren:
                    REDUCE(ts_symbol_type_factor, 1);
                default:
                    ERROR();
            }
        case 9:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_left_paren:
                    SHIFT(9);
                case ts_symbol_type_variable:
                    SHIFT(8);
                case ts_symbol_type_factor:
                    SHIFT(5);
                case ts_symbol_type_number:
                    SHIFT(8);
                case ts_symbol_type_term:
                    SHIFT(2);
                case ts_symbol_type_expression:
                    SHIFT(10);
                default:
                    ERROR();
            }
        case 10:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_right_paren:
                    SHIFT(11);
                default:
                    ERROR();
            }
        case 11:
            switch (LOOKAHEAD()) {
                case ts_symbol_type_expression:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_term:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_right_paren:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_number:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_factor:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_variable:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_times:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_plus:
                    REDUCE(ts_symbol_type_factor, 3);
                case ts_symbol_type_left_paren:
                    REDUCE(ts_symbol_type_factor, 3);
                default:
                    ERROR();
            }
        default:
            ERROR();
    }
    FINISH_PARSER();
}
