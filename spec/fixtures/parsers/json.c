#include "parser.h"
#include <ctype.h>

enum ts_symbol {
    ts_aux_token6,
    ts_symbol_number,
    ts_aux_repeat_helper1,
    ts_aux_token7,
    ts_aux_repeat_helper2,
    ts_aux_token5,
    ts_symbol_value,
    ts_symbol___END__,
    ts_aux_token3,
    ts_aux_token2,
    ts_symbol_string,
    ts_symbol_object,
    ts_aux_token4,
    ts_symbol_array,
    ts_aux_token1,
};

static const char *ts_symbol_names[] = {
    "token6",
    "number",
    "repeat_helper1",
    "token7",
    "repeat_helper2",
    "token5",
    "value",
    "__END__",
    "token3",
    "token2",
    "string",
    "object",
    "token4",
    "array",
    "token1",
};

static void ts_lex(TSParser *parser) {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if ((LOOKAHEAD_CHAR() == '\0'))
                ADVANCE(1);
            LEX_ERROR(1, EXPECT({"\0"}));
        case 1:
            ACCEPT_TOKEN(ts_symbol___END__);
        case 2:
            if ((LOOKAHEAD_CHAR() == ','))
                ADVANCE(3);
            ACCEPT_TOKEN(ts_aux_token3);
        case 3:
            ACCEPT_TOKEN(ts_aux_token2);
        case 4:
            if ((LOOKAHEAD_CHAR() == ']'))
                ADVANCE(5);
            LEX_ERROR(1, EXPECT({"]"}));
        case 5:
            ACCEPT_TOKEN(ts_aux_token4);
        case 6:
            if ((LOOKAHEAD_CHAR() == ']'))
                ADVANCE(5);
            if ((LOOKAHEAD_CHAR() == ','))
                ADVANCE(3);
            LEX_ERROR(2, EXPECT({",", "]"}));
        case 7:
            if ((LOOKAHEAD_CHAR() == '}'))
                ADVANCE(8);
            LEX_ERROR(1, EXPECT({"}"}));
        case 8:
            ACCEPT_TOKEN(ts_aux_token7);
        case 9:
            if ((LOOKAHEAD_CHAR() == '}'))
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == ','))
                ADVANCE(3);
            LEX_ERROR(2, EXPECT({",", "}"}));
        case 10:
            if ((LOOKAHEAD_CHAR() == '['))
                ADVANCE(15);
            if ((LOOKAHEAD_CHAR() == '{'))
                ADVANCE(16);
            if ((LOOKAHEAD_CHAR() == '\"'))
                ADVANCE(12);
            if (('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9'))
                ADVANCE(11);
            LEX_ERROR(4, EXPECT({"\"", "0-9", "[", "{"}));
        case 11:
            if (('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_symbol_number);
        case 12:
            if (!((LOOKAHEAD_CHAR() == '\"')))
                ADVANCE(13);
            LEX_ERROR(1, EXPECT({"<-!"}));
        case 13:
            if ((LOOKAHEAD_CHAR() == '\"'))
                ADVANCE(14);
            if (!((LOOKAHEAD_CHAR() == '\"')))
                ADVANCE(13);
            LEX_ERROR(1, EXPECT({"<-\""}));
        case 14:
            ACCEPT_TOKEN(ts_symbol_string);
        case 15:
            ACCEPT_TOKEN(ts_aux_token1);
        case 16:
            ACCEPT_TOKEN(ts_aux_token5);
        case 17:
            if ((LOOKAHEAD_CHAR() == ':'))
                ADVANCE(18);
            LEX_ERROR(1, EXPECT({":"}));
        case 18:
            ACCEPT_TOKEN(ts_aux_token6);
        case 19:
            if ((LOOKAHEAD_CHAR() == '\"'))
                ADVANCE(12);
            LEX_ERROR(1, EXPECT({"\""}));
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
                case ts_symbol_string:
                    SHIFT(53);
                case ts_aux_token1:
                    SHIFT(2);
                case ts_symbol_object:
                    SHIFT(53);
                case ts_symbol_value:
                    SHIFT(1);
                case ts_aux_token5:
                    SHIFT(47);
                case ts_symbol_number:
                    SHIFT(53);
                case ts_symbol_array:
                    SHIFT(53);
                default:
                    PARSE_ERROR(7, EXPECT({"array", "number", "token5", "value", "object", "token1", "string"}));
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
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(44);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 3:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(4);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 4:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(7);
                case ts_aux_token3:
                    SHIFT(5);
                case ts_aux_repeat_helper2:
                    SHIFT(5);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 5:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(6);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 6:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 7:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(43);
                case ts_aux_token1:
                    SHIFT(8);
                case ts_symbol_object:
                    SHIFT(43);
                case ts_symbol_number:
                    SHIFT(43);
                case ts_symbol_array:
                    SHIFT(43);
                case ts_symbol_value:
                    SHIFT(41);
                case ts_aux_token5:
                    SHIFT(35);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 8:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(9);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 9:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(7);
                case ts_aux_token3:
                    SHIFT(10);
                case ts_aux_repeat_helper2:
                    SHIFT(10);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 10:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(11);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 11:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 12:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(13);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 13:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(14);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 14:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(15);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 15:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(18);
                case ts_aux_token3:
                    SHIFT(16);
                case ts_aux_repeat_helper1:
                    SHIFT(16);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 16:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(17);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 17:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 18:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(19);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 19:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(20);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 20:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(34);
                case ts_aux_token1:
                    SHIFT(21);
                case ts_symbol_object:
                    SHIFT(34);
                case ts_symbol_number:
                    SHIFT(34);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_value:
                    SHIFT(32);
                case ts_aux_token5:
                    SHIFT(26);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 21:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(22);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 22:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(7);
                case ts_aux_token3:
                    SHIFT(23);
                case ts_aux_repeat_helper2:
                    SHIFT(23);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 23:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(24);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 24:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 25:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 26:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(27);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 27:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(28);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 28:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(29);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 29:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(18);
                case ts_aux_token3:
                    SHIFT(30);
                case ts_aux_repeat_helper1:
                    SHIFT(30);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 30:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(31);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 31:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 32:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_aux_repeat_helper1, 4, COLLAPSE({1, 0, 1, 0}));
                case ts_aux_token2:
                    SHIFT(18);
                case ts_aux_repeat_helper1:
                    SHIFT(33);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token2", "token7"}));
            }
        case 33:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_aux_repeat_helper1, 5, COLLAPSE({1, 0, 1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 34:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 35:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(36);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 36:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(37);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 37:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(38);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 38:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(18);
                case ts_aux_token3:
                    SHIFT(39);
                case ts_aux_repeat_helper1:
                    SHIFT(39);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 39:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(40);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 40:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 41:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(7);
                case ts_aux_token4:
                    REDUCE(ts_aux_repeat_helper2, 2, COLLAPSE({1, 0}));
                case ts_aux_repeat_helper2:
                    SHIFT(42);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token4", "token2"}));
            }
        case 42:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_aux_repeat_helper2, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 43:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 44:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(7);
                case ts_aux_token3:
                    SHIFT(45);
                case ts_aux_repeat_helper2:
                    SHIFT(45);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 45:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(46);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 46:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 47:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(48);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 48:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(49);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 49:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                case ts_aux_token1:
                    SHIFT(3);
                case ts_symbol_object:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(25);
                case ts_symbol_array:
                    SHIFT(25);
                case ts_symbol_value:
                    SHIFT(50);
                case ts_aux_token5:
                    SHIFT(12);
                default:
                    PARSE_ERROR(7, EXPECT({"token5", "value", "array", "number", "object", "token1", "string"}));
            }
        case 50:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(18);
                case ts_aux_token3:
                    SHIFT(51);
                case ts_aux_repeat_helper1:
                    SHIFT(51);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 51:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(52);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 52:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 53:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        default:
            PARSE_PANIC();
    }
    FINISH_PARSER();
}

TSParseConfig ts_parse_config_json = {
    .parse_fn = ts_parse,
    .symbol_names = ts_symbol_names
};
