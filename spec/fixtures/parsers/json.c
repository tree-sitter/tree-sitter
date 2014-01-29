#include "parser.h"
#include <ctype.h>

enum ts_symbol {
    ts_symbol_number,
    ts_symbol_string,
    ts_aux_repeat_helper1,
    ts_aux_token7,
    ts_symbol_array,
    ts_aux_token4,
    ts_aux_token5,
    ts_aux_token3,
    ts_aux_token2,
    ts_aux_token1,
    ts_aux_repeat_helper2,
    ts_aux_token6,
    ts_symbol_value,
    ts_symbol_object,
    ts_symbol___END__,
};

static const char *ts_symbol_names[] = {
    "number",
    "string",
    "repeat_helper1",
    "token7",
    "array",
    "token4",
    "token5",
    "token3",
    "token2",
    "token1",
    "repeat_helper2",
    "token6",
    "value",
    "object",
    "__END__",
};

static void ts_lex(TSParser *parser) {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == '\0')
                ADVANCE(1);
            LEX_ERROR(1, EXPECT({"''"}));
        case 1:
            ACCEPT_TOKEN(ts_symbol___END__);
        case 2:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(3);
            ACCEPT_TOKEN(ts_aux_token3);
        case 3:
            ACCEPT_TOKEN(ts_aux_token2);
        case 4:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(5);
            LEX_ERROR(1, EXPECT({"']'"}));
        case 5:
            ACCEPT_TOKEN(ts_aux_token4);
        case 6:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(5);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(3);
            LEX_ERROR(2, EXPECT({"','", "']'"}));
        case 7:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(8);
            LEX_ERROR(1, EXPECT({"'}'"}));
        case 8:
            ACCEPT_TOKEN(ts_aux_token7);
        case 9:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(8);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(3);
            LEX_ERROR(2, EXPECT({"','", "'}'"}));
        case 10:
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(16);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(15);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(11);
            LEX_ERROR(4, EXPECT({"<digit>", "'\"'", "'['", "'{'"}));
        case 11:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_symbol_number);
        case 12:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(13);
            LEX_ERROR(1, EXPECT({"<word>"}));
        case 13:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(14);
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(13);
            LEX_ERROR(2, EXPECT({"<word>", "'\"'"}));
        case 14:
            ACCEPT_TOKEN(ts_symbol_string);
        case 15:
            ACCEPT_TOKEN(ts_aux_token1);
        case 16:
            ACCEPT_TOKEN(ts_aux_token5);
        case 17:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(18);
            LEX_ERROR(1, EXPECT({"':'"}));
        case 18:
            ACCEPT_TOKEN(ts_aux_token6);
        case 19:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            LEX_ERROR(1, EXPECT({"'\"'"}));
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
                case ts_symbol_number:
                    SHIFT(81);
                case ts_aux_token5:
                    SHIFT(70);
                case ts_symbol_array:
                    SHIFT(79);
                case ts_symbol_object:
                    SHIFT(78);
                case ts_aux_token1:
                    SHIFT(2);
                case ts_symbol_string:
                    SHIFT(80);
                case ts_symbol_value:
                    SHIFT(1);
                default:
                    PARSE_ERROR(7, EXPECT({"value", "string", "token1", "object", "array", "token5", "number"}));
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
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(65);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 3:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(4);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 4:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(9);
                case ts_aux_token3:
                    SHIFT(7);
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
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(8);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 8:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 9:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(64);
                case ts_aux_token5:
                    SHIFT(51);
                case ts_symbol_array:
                    SHIFT(62);
                case ts_symbol_object:
                    SHIFT(61);
                case ts_symbol_string:
                    SHIFT(63);
                case ts_symbol_value:
                    SHIFT(59);
                case ts_aux_token1:
                    SHIFT(10);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 10:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(11);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 11:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(9);
                case ts_aux_token3:
                    SHIFT(14);
                case ts_aux_repeat_helper2:
                    SHIFT(12);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 12:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(13);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 13:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 14:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(15);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 15:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 16:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(17);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 17:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(18);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 18:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(19);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 19:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(24);
                case ts_aux_token3:
                    SHIFT(22);
                case ts_aux_repeat_helper1:
                    SHIFT(20);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 20:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(21);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 21:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 22:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(23);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 23:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 24:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(25);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 25:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(26);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 26:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(50);
                case ts_aux_token5:
                    SHIFT(37);
                case ts_symbol_array:
                    SHIFT(48);
                case ts_symbol_object:
                    SHIFT(47);
                case ts_symbol_string:
                    SHIFT(49);
                case ts_symbol_value:
                    SHIFT(45);
                case ts_aux_token1:
                    SHIFT(27);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 27:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(28);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 28:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(9);
                case ts_aux_token3:
                    SHIFT(31);
                case ts_aux_repeat_helper2:
                    SHIFT(29);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 29:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(30);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 30:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 31:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(32);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 32:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 33:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 34:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 35:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 36:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token3:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token3"}));
            }
        case 37:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(38);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 38:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(39);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 39:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(40);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 40:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(24);
                case ts_aux_token3:
                    SHIFT(43);
                case ts_aux_repeat_helper1:
                    SHIFT(41);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 41:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(42);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 42:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 43:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(44);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 44:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 45:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(24);
                case ts_aux_token7:
                    REDUCE(ts_aux_repeat_helper1, 4, COLLAPSE({1, 0, 1, 0}));
                case ts_aux_repeat_helper1:
                    SHIFT(46);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token7", "token2"}));
            }
        case 46:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_aux_repeat_helper1, 5, COLLAPSE({1, 0, 1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 47:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 48:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 49:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 50:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token7"}));
            }
        case 51:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(52);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 52:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(53);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 53:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(54);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 54:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(24);
                case ts_aux_token3:
                    SHIFT(57);
                case ts_aux_repeat_helper1:
                    SHIFT(55);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 55:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(56);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 56:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 57:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(58);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 58:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 59:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_aux_repeat_helper2, 2, COLLAPSE({1, 0}));
                case ts_aux_token2:
                    SHIFT(9);
                case ts_aux_repeat_helper2:
                    SHIFT(60);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token2", "token4"}));
            }
        case 60:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_aux_repeat_helper2, 3, COLLAPSE({1, 0, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 61:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 62:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 63:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 64:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                case ts_aux_token2:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(2, EXPECT({"token2", "token4"}));
            }
        case 65:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(9);
                case ts_aux_token3:
                    SHIFT(68);
                case ts_aux_repeat_helper2:
                    SHIFT(66);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "token3", "token2"}));
            }
        case 66:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(67);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 67:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 68:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token4:
                    SHIFT(69);
                default:
                    PARSE_ERROR(1, EXPECT({"token4"}));
            }
        case 69:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_array, 4, COLLAPSE({1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 70:
            SET_LEX_STATE(19);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(71);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 71:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token6:
                    SHIFT(72);
                default:
                    PARSE_ERROR(1, EXPECT({"token6"}));
            }
        case 72:
            SET_LEX_STATE(10);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_number:
                    SHIFT(36);
                case ts_aux_token5:
                    SHIFT(16);
                case ts_symbol_array:
                    SHIFT(34);
                case ts_symbol_object:
                    SHIFT(33);
                case ts_symbol_string:
                    SHIFT(35);
                case ts_symbol_value:
                    SHIFT(73);
                case ts_aux_token1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"token1", "value", "string", "object", "array", "token5", "number"}));
            }
        case 73:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token2:
                    SHIFT(24);
                case ts_aux_token3:
                    SHIFT(76);
                case ts_aux_repeat_helper1:
                    SHIFT(74);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "token3", "token2"}));
            }
        case 74:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(75);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 75:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 76:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_aux_token7:
                    SHIFT(77);
                default:
                    PARSE_ERROR(1, EXPECT({"token7"}));
            }
        case 77:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 78:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 79:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 80:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_value, 1, COLLAPSE({0}));
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 81:
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
