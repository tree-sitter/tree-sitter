#include "parser.h"
#include <ctype.h>

enum ts_symbol {
    ts_symbol_number,
    ts_symbol_string,
    ts_symbol_object,
    ts_symbol_repeat_helper2,
    ts_symbol_repeat_helper1,
    ts_symbol_3,
    ts_symbol_6,
    ts_symbol_7,
    ts_symbol_4,
    ts_symbol___END__,
    ts_symbol_array,
    ts_symbol_2,
    ts_symbol_5,
    ts_symbol_1,
    ts_symbol_value,
};

static const char *ts_symbol_names[] = {
    "number",
    "string",
    "object",
    "repeat_helper2",
    "repeat_helper1",
    "3",
    "6",
    "7",
    "4",
    "__END__",
    "array",
    "2",
    "5",
    "1",
    "value",
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
            ACCEPT_TOKEN(ts_symbol_2);
        case 3:
            ACCEPT_TOKEN(ts_symbol_7);
        case 4:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(5);
            LEX_ERROR(1, EXPECT({"']'"}));
        case 5:
            ACCEPT_TOKEN(ts_symbol_3);
        case 6:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(7);
            LEX_ERROR(1, EXPECT({"'}'"}));
        case 7:
            ACCEPT_TOKEN(ts_symbol_6);
        case 8:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(9);
            LEX_ERROR(4, EXPECT({"'['", "'{'", "<digit>", "'\"'"}));
        case 9:
            ACCEPT_TOKEN(ts_symbol_1);
        case 10:
            ACCEPT_TOKEN(ts_symbol_4);
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
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(16);
            LEX_ERROR(1, EXPECT({"':'"}));
        case 16:
            ACCEPT_TOKEN(ts_symbol_5);
        case 17:
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
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(31);
                case ts_symbol_4:
                    SHIFT(25);
                case ts_symbol_number:
                    SHIFT(31);
                case ts_symbol_1:
                    SHIFT(2);
                case ts_symbol_string:
                    SHIFT(31);
                case ts_symbol_object:
                    SHIFT(31);
                case ts_symbol_value:
                    SHIFT(1);
                default:
                    PARSE_ERROR(7, EXPECT({"value", "object", "string", "number", "1", "4", "array"}));
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
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(19);
                case ts_symbol_string:
                    SHIFT(19);
                case ts_symbol_object:
                    SHIFT(19);
                case ts_symbol_value:
                    SHIFT(22);
                case ts_symbol_4:
                    SHIFT(8);
                case ts_symbol_number:
                    SHIFT(19);
                case ts_symbol_1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"1", "number", "4", "value", "object", "string", "array"}));
            }
        case 3:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(19);
                case ts_symbol_string:
                    SHIFT(19);
                case ts_symbol_object:
                    SHIFT(19);
                case ts_symbol_value:
                    SHIFT(4);
                case ts_symbol_4:
                    SHIFT(8);
                case ts_symbol_number:
                    SHIFT(19);
                case ts_symbol_1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"1", "number", "4", "value", "object", "string", "array"}));
            }
        case 4:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    SHIFT(7);
                case ts_symbol_2:
                    SHIFT(5);
                case ts_symbol_repeat_helper1:
                    SHIFT(5);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "2", "7"}));
            }
        case 5:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_3:
                    SHIFT(6);
                default:
                    PARSE_ERROR(1, EXPECT({"3"}));
            }
        case 6:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    REDUCE(ts_symbol_array, 4);
                case ts_symbol_2:
                    REDUCE(ts_symbol_array, 4);
                default:
                    PARSE_ERROR(2, EXPECT({"2", "7"}));
            }
        case 7:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(19);
                case ts_symbol_string:
                    SHIFT(19);
                case ts_symbol_object:
                    SHIFT(19);
                case ts_symbol_value:
                    SHIFT(20);
                case ts_symbol_4:
                    SHIFT(8);
                case ts_symbol_number:
                    SHIFT(19);
                case ts_symbol_1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"1", "number", "4", "value", "object", "string", "array"}));
            }
        case 8:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(9);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 9:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_5:
                    SHIFT(10);
                default:
                    PARSE_ERROR(1, EXPECT({"5"}));
            }
        case 10:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(19);
                case ts_symbol_string:
                    SHIFT(19);
                case ts_symbol_object:
                    SHIFT(19);
                case ts_symbol_value:
                    SHIFT(11);
                case ts_symbol_4:
                    SHIFT(8);
                case ts_symbol_number:
                    SHIFT(19);
                case ts_symbol_1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"1", "number", "4", "value", "object", "string", "array"}));
            }
        case 11:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    SHIFT(14);
                case ts_symbol_2:
                    SHIFT(12);
                case ts_symbol_repeat_helper2:
                    SHIFT(12);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "2", "7"}));
            }
        case 12:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_6:
                    SHIFT(13);
                default:
                    PARSE_ERROR(1, EXPECT({"6"}));
            }
        case 13:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    REDUCE(ts_symbol_object, 6);
                case ts_symbol_2:
                    REDUCE(ts_symbol_object, 6);
                default:
                    PARSE_ERROR(2, EXPECT({"2", "7"}));
            }
        case 14:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(15);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 15:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_5:
                    SHIFT(16);
                default:
                    PARSE_ERROR(1, EXPECT({"5"}));
            }
        case 16:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(19);
                case ts_symbol_string:
                    SHIFT(19);
                case ts_symbol_object:
                    SHIFT(19);
                case ts_symbol_value:
                    SHIFT(17);
                case ts_symbol_4:
                    SHIFT(8);
                case ts_symbol_number:
                    SHIFT(19);
                case ts_symbol_1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"1", "number", "4", "value", "object", "string", "array"}));
            }
        case 17:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    SHIFT(14);
                case ts_symbol_2:
                    SHIFT(18);
                case ts_symbol_repeat_helper2:
                    SHIFT(18);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "2", "7"}));
            }
        case 18:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_6:
                    REDUCE(ts_symbol_repeat_helper2, 5);
                default:
                    PARSE_ERROR(1, EXPECT({"6"}));
            }
        case 19:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    REDUCE(ts_symbol_value, 1);
                case ts_symbol_2:
                    REDUCE(ts_symbol_value, 1);
                default:
                    PARSE_ERROR(2, EXPECT({"2", "7"}));
            }
        case 20:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    SHIFT(7);
                case ts_symbol_2:
                    SHIFT(21);
                case ts_symbol_repeat_helper1:
                    SHIFT(21);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "2", "7"}));
            }
        case 21:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_3:
                    REDUCE(ts_symbol_repeat_helper1, 3);
                default:
                    PARSE_ERROR(1, EXPECT({"3"}));
            }
        case 22:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    SHIFT(7);
                case ts_symbol_2:
                    SHIFT(23);
                case ts_symbol_repeat_helper1:
                    SHIFT(23);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper1", "2", "7"}));
            }
        case 23:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_3:
                    SHIFT(24);
                default:
                    PARSE_ERROR(1, EXPECT({"3"}));
            }
        case 24:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_array, 4);
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 25:
            SET_LEX_STATE(17);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_string:
                    SHIFT(26);
                default:
                    PARSE_ERROR(1, EXPECT({"string"}));
            }
        case 26:
            SET_LEX_STATE(15);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_5:
                    SHIFT(27);
                default:
                    PARSE_ERROR(1, EXPECT({"5"}));
            }
        case 27:
            SET_LEX_STATE(8);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_array:
                    SHIFT(19);
                case ts_symbol_string:
                    SHIFT(19);
                case ts_symbol_object:
                    SHIFT(19);
                case ts_symbol_value:
                    SHIFT(28);
                case ts_symbol_4:
                    SHIFT(8);
                case ts_symbol_number:
                    SHIFT(19);
                case ts_symbol_1:
                    SHIFT(3);
                default:
                    PARSE_ERROR(7, EXPECT({"1", "number", "4", "value", "object", "string", "array"}));
            }
        case 28:
            SET_LEX_STATE(2);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_7:
                    SHIFT(14);
                case ts_symbol_2:
                    SHIFT(29);
                case ts_symbol_repeat_helper2:
                    SHIFT(29);
                default:
                    PARSE_ERROR(3, EXPECT({"repeat_helper2", "2", "7"}));
            }
        case 29:
            SET_LEX_STATE(6);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_6:
                    SHIFT(30);
                default:
                    PARSE_ERROR(1, EXPECT({"6"}));
            }
        case 30:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_object, 6);
                default:
                    PARSE_ERROR(1, EXPECT({"__END__"}));
            }
        case 31:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    REDUCE(ts_symbol_value, 1);
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
