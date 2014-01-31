#include "parser.h"
#include <ctype.h>

enum ts_symbol {
    ts_symbol_plus,
    ts_aux_token2,
    ts_symbol_number,
    ts_symbol_term,
    ts_symbol_factor,
    ts_aux_token1,
    ts_symbol_times,
    ts_symbol_expression,
    ts_symbol_variable,
    ts_symbol___END__,
};

static const char *ts_symbol_names[] = {
    "plus",
    "token2",
    "number",
    "term",
    "factor",
    "token1",
    "times",
    "expression",
    "variable",
    "__END__",
};

static void ts_lex(TSParser *parser) {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if ((LOOKAHEAD_CHAR() == '\0'))
                ADVANCE(1);
            LEX_ERROR(1, EXPECT({"<EOF>"}));
        case 1:
            ACCEPT_TOKEN(ts_symbol___END__);
        case 2:
            if ((LOOKAHEAD_CHAR() == '*'))
                ADVANCE(3);
            if ((LOOKAHEAD_CHAR() == '\0'))
                ADVANCE(1);
            LEX_ERROR(2, EXPECT({"'*'", "<EOF>"}));
        case 3:
            ACCEPT_TOKEN(ts_symbol_times);
        case 4:
            if ((LOOKAHEAD_CHAR() == ')'))
                ADVANCE(5);
            LEX_ERROR(1, EXPECT({"')'"}));
        case 5:
            ACCEPT_TOKEN(ts_aux_token2);
        case 6:
            if ((LOOKAHEAD_CHAR() == ')'))
                ADVANCE(5);
            if ((LOOKAHEAD_CHAR() == '*'))
                ADVANCE(3);
            LEX_ERROR(2, EXPECT({"')'", "'*'"}));
        case 7:
            if ((LOOKAHEAD_CHAR() == ')'))
                ADVANCE(5);
            if ((LOOKAHEAD_CHAR() == '*'))
                ADVANCE(3);
            if ((LOOKAHEAD_CHAR() == '+'))
                ADVANCE(8);
            LEX_ERROR(3, EXPECT({"')'", "'*'", "'+'"}));
        case 8:
            ACCEPT_TOKEN(ts_symbol_plus);
        case 9:
            if ((LOOKAHEAD_CHAR() == ')'))
                ADVANCE(5);
            if ((LOOKAHEAD_CHAR() == '+'))
                ADVANCE(8);
            LEX_ERROR(2, EXPECT({"')'", "'+'"}));
        case 10:
            if (('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z'))
                ADVANCE(13);
            if ((LOOKAHEAD_CHAR() == '('))
                ADVANCE(12);
            if ((isdigit(LOOKAHEAD_CHAR())))
                ADVANCE(11);
            LEX_ERROR(4, EXPECT({"'A'-'Z'", "'a'-'z'", "'('", "<digit>"}));
        case 11:
            if ((isdigit(LOOKAHEAD_CHAR())))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_symbol_number);
        case 12:
            ACCEPT_TOKEN(ts_aux_token1);
        case 13:
            if (('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_symbol_variable);
        case 14:
            if ((LOOKAHEAD_CHAR() == '+'))
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '\0'))
                ADVANCE(1);
            LEX_ERROR(2, EXPECT({"'+'", "<EOF>"}));
        case 15:
            if ((LOOKAHEAD_CHAR() == '+'))
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '*'))
                ADVANCE(3);
            if ((LOOKAHEAD_CHAR() == '\0'))
                ADVANCE(1);
            LEX_ERROR(3, EXPECT({"'+'", "'*'", "<EOF>"}));
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
                case ts_symbol_factor:
                    SHIFT(52);
                case ts_symbol_expression:
                    SHIFT(1);
                case ts_aux_token1:
                    SHIFT(49);
                case ts_symbol_number:
                    SHIFT(48);
                case ts_symbol_variable:
                    SHIFT(47);
                case ts_symbol_term:
                    SHIFT(2);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 1:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    ACCEPT_INPUT();
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 2:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_expression, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    SHIFT(3);
                default:
                    PARSE_ERROR(2, EXPECT({"plus", "__END__"}));
            }
        case 3:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(39);
                case ts_aux_token1:
                    SHIFT(7);
                case ts_symbol_number:
                    SHIFT(6);
                case ts_symbol_variable:
                    SHIFT(5);
                case ts_symbol_term:
                    SHIFT(4);
                default:
                    PARSE_ERROR(5, EXPECT({"term", "variable", "number", "token1", "factor"}));
            }
        case 4:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_expression, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 5:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "times"}));
            }
        case 6:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "times"}));
            }
        case 7:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(37);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 8:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_expression, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    SHIFT(9);
                default:
                    PARSE_ERROR(2, EXPECT({"plus", "token2"}));
            }
        case 9:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(29);
                case ts_aux_token1:
                    SHIFT(13);
                case ts_symbol_number:
                    SHIFT(12);
                case ts_symbol_variable:
                    SHIFT(11);
                case ts_symbol_term:
                    SHIFT(10);
                default:
                    PARSE_ERROR(5, EXPECT({"term", "variable", "number", "token1", "factor"}));
            }
        case 10:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_expression, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 11:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"times", "token2"}));
            }
        case 12:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"times", "token2"}));
            }
        case 13:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(27);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 14:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({"plus", "times", "token2"}));
            }
        case 15:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({"plus", "times", "token2"}));
            }
        case 16:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(17);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 17:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(18);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 18:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(3, EXPECT({"plus", "times", "token2"}));
            }
        case 19:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(20);
                default:
                    PARSE_ERROR(3, EXPECT({"times", "plus", "token2"}));
            }
        case 20:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(26);
                case ts_aux_token1:
                    SHIFT(23);
                case ts_symbol_number:
                    SHIFT(22);
                case ts_symbol_variable:
                    SHIFT(21);
                default:
                    PARSE_ERROR(4, EXPECT({"variable", "number", "token1", "factor"}));
            }
        case 21:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"plus", "token2"}));
            }
        case 22:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"plus", "token2"}));
            }
        case 23:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(24);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 24:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(25);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 25:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"plus", "token2"}));
            }
        case 26:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(2, EXPECT({"plus", "token2"}));
            }
        case 27:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(28);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 28:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"times", "token2"}));
            }
        case 29:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(30);
                default:
                    PARSE_ERROR(2, EXPECT({"times", "token2"}));
            }
        case 30:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(36);
                case ts_aux_token1:
                    SHIFT(33);
                case ts_symbol_number:
                    SHIFT(32);
                case ts_symbol_variable:
                    SHIFT(31);
                default:
                    PARSE_ERROR(4, EXPECT({"variable", "number", "token1", "factor"}));
            }
        case 31:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 32:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 33:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(34);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 34:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(35);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 35:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 36:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 37:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(38);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 38:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "times"}));
            }
        case 39:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(40);
                default:
                    PARSE_ERROR(2, EXPECT({"times", "__END__"}));
            }
        case 40:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(46);
                case ts_aux_token1:
                    SHIFT(43);
                case ts_symbol_number:
                    SHIFT(42);
                case ts_symbol_variable:
                    SHIFT(41);
                default:
                    PARSE_ERROR(4, EXPECT({"variable", "number", "token1", "factor"}));
            }
        case 41:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 42:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 43:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(44);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 44:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(45);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 45:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 46:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 47:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({"__END__", "plus", "times"}));
            }
        case 48:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(3, EXPECT({"__END__", "plus", "times"}));
            }
        case 49:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(50);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 50:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(51);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 51:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_times:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(3, EXPECT({"__END__", "plus", "times"}));
            }
        case 52:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 1, COLLAPSE({0}));
                case ts_symbol_times:
                    SHIFT(53);
                default:
                    PARSE_ERROR(3, EXPECT({"times", "__END__", "plus"}));
            }
        case 53:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(59);
                case ts_aux_token1:
                    SHIFT(56);
                case ts_symbol_number:
                    SHIFT(55);
                case ts_symbol_variable:
                    SHIFT(54);
                default:
                    PARSE_ERROR(4, EXPECT({"variable", "number", "token1", "factor"}));
            }
        case 54:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "plus"}));
            }
        case 55:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "plus"}));
            }
        case 56:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_factor:
                    SHIFT(19);
                case ts_symbol_expression:
                    SHIFT(57);
                case ts_aux_token1:
                    SHIFT(16);
                case ts_symbol_number:
                    SHIFT(15);
                case ts_symbol_variable:
                    SHIFT(14);
                case ts_symbol_term:
                    SHIFT(8);
                default:
                    PARSE_ERROR(6, EXPECT({"term", "variable", "number", "token1", "expression", "factor"}));
            }
        case 57:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(58);
                default:
                    PARSE_ERROR(1, EXPECT({"token2"}));
            }
        case 58:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_factor, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "plus"}));
            }
        case 59:
            SET_LEX_STATE(14);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_plus:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                case ts_symbol___END__:
                    REDUCE(ts_symbol_term, 3, COLLAPSE({0, 0, 0}));
                default:
                    PARSE_ERROR(2, EXPECT({"__END__", "plus"}));
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
