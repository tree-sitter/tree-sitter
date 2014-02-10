#include "parser.h"
#include <ctype.h>

enum ts_symbol {
    ts_symbol_plus,
    ts_symbol_factor,
    ts_symbol_variable,
    ts_symbol_term,
    ts_symbol_expression,
    ts_aux_token1,
    ts_symbol_number,
    ts_symbol_times,
    ts_aux_token2,
    ts_symbol___END__,
};

static const char *ts_symbol_names[] = {
    "plus",
    "factor",
    "variable",
    "term",
    "expression",
    "token1",
    "number",
    "times",
    "token2",
    "__END__",
};

static void ts_lex(TSParser *parser) {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == '\0')
                ADVANCE(1);
            LEX_ERROR(1, EXPECT({"<EOF>"}));
        case 1:
            ACCEPT_TOKEN(ts_symbol___END__);
        case 2:
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(3);
            if (LOOKAHEAD_CHAR() == '\0')
                ADVANCE(1);
            LEX_ERROR(2, EXPECT({"<EOF>", "*"}));
        case 3:
            ACCEPT_TOKEN(ts_symbol_times);
        case 4:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(5);
            LEX_ERROR(1, EXPECT({")"}));
        case 5:
            ACCEPT_TOKEN(ts_aux_token2);
        case 6:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(5);
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(3);
            LEX_ERROR(1, EXPECT({")-*"}));
        case 7:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(5);
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(3);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(8);
            LEX_ERROR(1, EXPECT({")-+"}));
        case 8:
            ACCEPT_TOKEN(ts_symbol_plus);
        case 9:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(5);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(8);
            LEX_ERROR(2, EXPECT({")", "+"}));
        case 10:
            if (('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(13);
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(12);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(11);
            LEX_ERROR(4, EXPECT({"(", "0-9", "A-Z", "a-z"}));
        case 11:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_symbol_number);
        case 12:
            ACCEPT_TOKEN(ts_aux_token1);
        case 13:
            if (('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_symbol_variable);
        case 14:
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(8);
            if (LOOKAHEAD_CHAR() == '\0')
                ADVANCE(1);
            LEX_ERROR(2, EXPECT({"<EOF>", "+"}));
        case 15:
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(3);
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(8);
            if (LOOKAHEAD_CHAR() == '\0')
                ADVANCE(1);
            LEX_ERROR(2, EXPECT({"<EOF>", "*-+"}));
        default:
            LEX_PANIC();
    }
    FINISH_LEXER();
}

static TSParseResult ts_parse(const char *input) {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(42);
                case ts_symbol_number:
                    SHIFT(41);
                case ts_symbol_factor:
                    SHIFT(45);
                case ts_symbol_variable:
                    SHIFT(41);
                case ts_symbol_term:
                    SHIFT(2);
                case ts_symbol_expression:
                    SHIFT(1);
                default:
                    PARSE_PANIC();
            }
        case 1:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    ACCEPT_INPUT();
                default:
                    PARSE_PANIC();
            }
        case 2:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_expression, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    SHIFT(3);
                default:
                    PARSE_PANIC();
            }
        case 3:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(6);
                case ts_symbol_factor:
                    SHIFT(34);
                case ts_symbol_number:
                    SHIFT(5);
                case ts_symbol_variable:
                    SHIFT(5);
                case ts_symbol_term:
                    SHIFT(4);
                default:
                    PARSE_PANIC();
            }
        case 4:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_expression, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_PANIC();
            }
        case 5:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 6:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(32);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 7:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_expression, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    SHIFT(8);
                default:
                    PARSE_PANIC();
            }
        case 8:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(11);
                case ts_symbol_factor:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(10);
                case ts_symbol_variable:
                    SHIFT(10);
                case ts_symbol_term:
                    SHIFT(9);
                default:
                    PARSE_PANIC();
            }
        case 9:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_expression, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_PANIC();
            }
        case 10:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 11:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(23);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 12:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 13:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(14);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 14:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(15);
                default:
                    PARSE_PANIC();
            }
        case 15:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 16:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(17);
                default:
                    PARSE_PANIC();
            }
        case 17:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(19);
                case ts_symbol_factor:
                    SHIFT(22);
                case ts_symbol_number:
                    SHIFT(18);
                case ts_symbol_variable:
                    SHIFT(18);
                default:
                    PARSE_PANIC();
            }
        case 18:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 19:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(20);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 20:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(21);
                default:
                    PARSE_PANIC();
            }
        case 21:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 22:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_PANIC();
            }
        case 23:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(24);
                default:
                    PARSE_PANIC();
            }
        case 24:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 25:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(26);
                default:
                    PARSE_PANIC();
            }
        case 26:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(28);
                case ts_symbol_factor:
                    SHIFT(31);
                case ts_symbol_number:
                    SHIFT(27);
                case ts_symbol_variable:
                    SHIFT(27);
                default:
                    PARSE_PANIC();
            }
        case 27:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 28:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(29);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 29:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(30);
                default:
                    PARSE_PANIC();
            }
        case 30:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 31:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_PANIC();
            }
        case 32:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(33);
                default:
                    PARSE_PANIC();
            }
        case 33:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 34:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(35);
                default:
                    PARSE_PANIC();
            }
        case 35:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(37);
                case ts_symbol_factor:
                    SHIFT(40);
                case ts_symbol_number:
                    SHIFT(36);
                case ts_symbol_variable:
                    SHIFT(36);
                default:
                    PARSE_PANIC();
            }
        case 36:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 37:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(38);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 38:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(39);
                default:
                    PARSE_PANIC();
            }
        case 39:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 40:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_PANIC();
            }
        case 41:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 42:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(43);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 43:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(44);
                default:
                    PARSE_PANIC();
            }
        case 44:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 45:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(46);
                default:
                    PARSE_PANIC();
            }
        case 46:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(48);
                case ts_symbol_factor:
                    SHIFT(51);
                case ts_symbol_number:
                    SHIFT(47);
                case ts_symbol_variable:
                    SHIFT(47);
                default:
                    PARSE_PANIC();
            }
        case 47:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_PANIC();
            }
        case 48:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_expression:
                    SHIFT(49);
                case ts_symbol_factor:
                    SHIFT(16);
                case ts_symbol_variable:
                    SHIFT(12);
                case ts_symbol_term:
                    SHIFT(7);
                default:
                    PARSE_PANIC();
            }
        case 49:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(50);
                default:
                    PARSE_PANIC();
            }
        case 50:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_PANIC();
            }
        case 51:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_PANIC();
            }
        default:
            PARSE_PANIC();
    }
    FINISH_PARSER();
}

TSParseConfig ts_parse_config_arithmetic = {
    .parse_fn = ts_parse,
    .symbol_names = ts_symbol_names
};
