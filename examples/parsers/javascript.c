#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 35

enum {
    ts_sym__IF,
    ts_sym__VAR,
    ts_sym__terminator,
    ts_sym_array,
    ts_sym_assignment,
    ts_sym_expression,
    ts_sym_false,
    ts_sym_identifier,
    ts_sym_if_statement,
    ts_sym_literal,
    ts_sym_null,
    ts_sym_number,
    ts_sym_object,
    ts_sym_program,
    ts_sym_statement,
    ts_sym_statement_block,
    ts_sym_string,
    ts_sym_true,
    ts_aux_sym_repeat_helper1,
    ts_aux_sym_repeat_helper2,
    ts_aux_sym_repeat_helper3,
    ts_aux_sym_repeat_helper4,
    ts_aux_sym_token1,
    ts_aux_sym_token10,
    ts_aux_sym_token11,
    ts_aux_sym_token2,
    ts_aux_sym_token3,
    ts_aux_sym_token4,
    ts_aux_sym_token5,
    ts_aux_sym_token6,
    ts_aux_sym_token7,
    ts_aux_sym_token8,
    ts_aux_sym_token9,
};

SYMBOL_NAMES = {
    "_IF",
    "_VAR",
    "_terminator",
    "array",
    "assignment",
    "expression",
    "false",
    "identifier",
    "if_statement",
    "literal",
    "null",
    "number",
    "object",
    "program",
    "statement",
    "statement_block",
    "string",
    "true",
    "repeat_helper1",
    "repeat_helper2",
    "repeat_helper3",
    "repeat_helper4",
    "token1",
    "token10",
    "token11",
    "token2",
    "token3",
    "token4",
    "token5",
    "token6",
    "token7",
    "token8",
    "token9",
};

HIDDEN_SYMBOL_FLAGS = {
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
};

LEX_FN() {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(1);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 2:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(18);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(34);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(42);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(49);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(50);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 3:
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (LOOKAHEAD_CHAR() == 's')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_sym_false);
        case 8:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(15);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(17);
            LEX_ERROR();
        case 9:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 10:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_sym_string);
        case 12:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(13);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 13:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 14:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 15:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(16);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 16:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(12);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 17:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            LEX_ERROR();
        case 18:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(21);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 21:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 23:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(21);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 25:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 26:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r') ||
                ('t' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 's')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'd') ||
                ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            ACCEPT_TOKEN(ts_sym__IF);
        case 33:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__IF);
        case 34:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't') ||
                ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(35);
            if ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'u')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(36);
            if ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'l')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(37);
            if ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'l')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            ACCEPT_TOKEN(ts_sym_null);
        case 39:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(38);
            LEX_ERROR();
        case 40:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(39);
            LEX_ERROR();
        case 41:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(40);
            LEX_ERROR();
        case 42:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(43);
            if ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't') ||
                ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(44);
            if ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'u')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'd') ||
                ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(45);
            if ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            ACCEPT_TOKEN(ts_sym_true);
        case 47:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(46);
            LEX_ERROR();
        case 48:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(47);
            LEX_ERROR();
        case 49:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(48);
            LEX_ERROR();
        case 50:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(52);
            LEX_ERROR();
        case 52:
            ACCEPT_TOKEN(ts_sym__VAR);
        case 53:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__VAR);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 56:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(18);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(34);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(42);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(49);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(50);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(55);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 58:
            if (LOOKAHEAD_CHAR() == '\n')
                ADVANCE(59);
            if (LOOKAHEAD_CHAR() == ';')
                ADVANCE(60);
            LEX_ERROR();
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 60:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 61:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(62);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(63);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 64:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(63);
            LEX_ERROR();
        case 65:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(62);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 66:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 67:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(18);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(63);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(34);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(42);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(49);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 68:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(18);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(34);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(42);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(49);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 69:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 71:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 72:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            LEX_ERROR();
        case 73:
            if (LOOKAHEAD_CHAR() == '=')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 75:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(18);
            LEX_ERROR();
        case 76:
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 77:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(78);
            LEX_ERROR();
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 79:
            LEX_ERROR();
        case ts_lex_state_error:
            if (LOOKAHEAD_CHAR() == '\n')
                ADVANCE(59);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(8);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(18);
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(78);
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(1);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(62);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(70);
            if (LOOKAHEAD_CHAR() == ';')
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == '=')
                ADVANCE(74);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(63);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(34);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(42);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(49);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(50);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(55);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(57);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

PARSE_TABLE() {
    START_TABLE(113)
    
    STATE(0);
    SET_LEX_STATE(2);
    SHIFT(ts_sym__IF, 1)
    SHIFT(ts_sym__VAR, 14)
    SHIFT(ts_sym_array, 17)
    SHIFT(ts_sym_assignment, 105)
    SHIFT(ts_sym_expression, 105)
    SHIFT(ts_sym_false, 17)
    SHIFT(ts_sym_identifier, 19)
    SHIFT(ts_sym_if_statement, 108)
    SHIFT(ts_sym_literal, 19)
    SHIFT(ts_sym_null, 17)
    SHIFT(ts_sym_number, 17)
    SHIFT(ts_sym_object, 17)
    SHIFT(ts_sym_program, 109)
    SHIFT(ts_sym_statement, 110)
    SHIFT(ts_sym_string, 17)
    SHIFT(ts_sym_true, 17)
    SHIFT(ts_aux_sym_repeat_helper1, 112)
    SHIFT(ts_aux_sym_token10, 20)
    SHIFT(ts_aux_sym_token5, 69)
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 0)
    END_STATE();
    
    STATE(1);
    SET_LEX_STATE(77);
    SHIFT(ts_aux_sym_token3, 2)
    END_STATE();
    
    STATE(2);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 3)
    SHIFT(ts_sym_expression, 4)
    SHIFT(ts_sym_false, 3)
    SHIFT(ts_sym_identifier, 87)
    SHIFT(ts_sym_literal, 87)
    SHIFT(ts_sym_null, 3)
    SHIFT(ts_sym_number, 3)
    SHIFT(ts_sym_object, 3)
    SHIFT(ts_sym_string, 3)
    SHIFT(ts_sym_true, 3)
    SHIFT(ts_aux_sym_token10, 88)
    SHIFT(ts_aux_sym_token5, 93)
    END_STATE();
    
    STATE(3);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_literal, 1)
    END_STATE();
    
    STATE(4);
    SET_LEX_STATE(0);
    SHIFT(ts_aux_sym_token4, 5)
    END_STATE();
    
    STATE(5);
    SET_LEX_STATE(76);
    SHIFT(ts_sym_statement_block, 6)
    SHIFT(ts_aux_sym_token5, 7)
    END_STATE();
    
    STATE(6);
    SET_LEX_STATE(2);
    REDUCE(ts_sym__IF, ts_sym_if_statement, 5)
    REDUCE(ts_sym__VAR, ts_sym_if_statement, 5)
    REDUCE(ts_sym_false, ts_sym_if_statement, 5)
    REDUCE(ts_sym_identifier, ts_sym_if_statement, 5)
    REDUCE(ts_sym_null, ts_sym_if_statement, 5)
    REDUCE(ts_sym_number, ts_sym_if_statement, 5)
    REDUCE(ts_sym_string, ts_sym_if_statement, 5)
    REDUCE(ts_sym_true, ts_sym_if_statement, 5)
    REDUCE(ts_aux_sym_token10, ts_sym_if_statement, 5)
    REDUCE(ts_aux_sym_token5, ts_sym_if_statement, 5)
    REDUCE(ts_builtin_sym_end, ts_sym_if_statement, 5)
    END_STATE();
    
    STATE(7);
    SET_LEX_STATE(56);
    SHIFT(ts_sym__IF, 8)
    SHIFT(ts_sym__VAR, 14)
    SHIFT(ts_sym_array, 17)
    SHIFT(ts_sym_assignment, 79)
    SHIFT(ts_sym_expression, 79)
    SHIFT(ts_sym_false, 17)
    SHIFT(ts_sym_identifier, 19)
    SHIFT(ts_sym_if_statement, 82)
    SHIFT(ts_sym_literal, 19)
    SHIFT(ts_sym_null, 17)
    SHIFT(ts_sym_number, 17)
    SHIFT(ts_sym_object, 17)
    SHIFT(ts_sym_statement, 83)
    SHIFT(ts_sym_string, 17)
    SHIFT(ts_sym_true, 17)
    SHIFT(ts_aux_sym_repeat_helper2, 103)
    SHIFT(ts_aux_sym_token10, 20)
    SHIFT(ts_aux_sym_token5, 69)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0)
    END_STATE();
    
    STATE(8);
    SET_LEX_STATE(77);
    SHIFT(ts_aux_sym_token3, 9)
    END_STATE();
    
    STATE(9);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 3)
    SHIFT(ts_sym_expression, 10)
    SHIFT(ts_sym_false, 3)
    SHIFT(ts_sym_identifier, 87)
    SHIFT(ts_sym_literal, 87)
    SHIFT(ts_sym_null, 3)
    SHIFT(ts_sym_number, 3)
    SHIFT(ts_sym_object, 3)
    SHIFT(ts_sym_string, 3)
    SHIFT(ts_sym_true, 3)
    SHIFT(ts_aux_sym_token10, 88)
    SHIFT(ts_aux_sym_token5, 93)
    END_STATE();
    
    STATE(10);
    SET_LEX_STATE(0);
    SHIFT(ts_aux_sym_token4, 11)
    END_STATE();
    
    STATE(11);
    SET_LEX_STATE(76);
    SHIFT(ts_sym_statement_block, 12)
    SHIFT(ts_aux_sym_token5, 13)
    END_STATE();
    
    STATE(12);
    SET_LEX_STATE(56);
    REDUCE(ts_sym__IF, ts_sym_if_statement, 5)
    REDUCE(ts_sym__VAR, ts_sym_if_statement, 5)
    REDUCE(ts_sym_false, ts_sym_if_statement, 5)
    REDUCE(ts_sym_identifier, ts_sym_if_statement, 5)
    REDUCE(ts_sym_null, ts_sym_if_statement, 5)
    REDUCE(ts_sym_number, ts_sym_if_statement, 5)
    REDUCE(ts_sym_string, ts_sym_if_statement, 5)
    REDUCE(ts_sym_true, ts_sym_if_statement, 5)
    REDUCE(ts_aux_sym_token10, ts_sym_if_statement, 5)
    REDUCE(ts_aux_sym_token5, ts_sym_if_statement, 5)
    REDUCE(ts_aux_sym_token6, ts_sym_if_statement, 5)
    END_STATE();
    
    STATE(13);
    SET_LEX_STATE(56);
    SHIFT(ts_sym__IF, 8)
    SHIFT(ts_sym__VAR, 14)
    SHIFT(ts_sym_array, 17)
    SHIFT(ts_sym_assignment, 79)
    SHIFT(ts_sym_expression, 79)
    SHIFT(ts_sym_false, 17)
    SHIFT(ts_sym_identifier, 19)
    SHIFT(ts_sym_if_statement, 82)
    SHIFT(ts_sym_literal, 19)
    SHIFT(ts_sym_null, 17)
    SHIFT(ts_sym_number, 17)
    SHIFT(ts_sym_object, 17)
    SHIFT(ts_sym_statement, 83)
    SHIFT(ts_sym_string, 17)
    SHIFT(ts_sym_true, 17)
    SHIFT(ts_aux_sym_repeat_helper2, 85)
    SHIFT(ts_aux_sym_token10, 20)
    SHIFT(ts_aux_sym_token5, 69)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0)
    END_STATE();
    
    STATE(14);
    SET_LEX_STATE(75);
    SHIFT(ts_sym_identifier, 15)
    END_STATE();
    
    STATE(15);
    SET_LEX_STATE(73);
    SHIFT(ts_aux_sym_token7, 16)
    END_STATE();
    
    STATE(16);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 17)
    SHIFT(ts_sym_expression, 18)
    SHIFT(ts_sym_false, 17)
    SHIFT(ts_sym_identifier, 19)
    SHIFT(ts_sym_literal, 19)
    SHIFT(ts_sym_null, 17)
    SHIFT(ts_sym_number, 17)
    SHIFT(ts_sym_object, 17)
    SHIFT(ts_sym_string, 17)
    SHIFT(ts_sym_true, 17)
    SHIFT(ts_aux_sym_token10, 20)
    SHIFT(ts_aux_sym_token5, 69)
    END_STATE();
    
    STATE(17);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_literal, 1)
    REDUCE(ts_aux_sym_token2, ts_sym_literal, 1)
    END_STATE();
    
    STATE(18);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_assignment, 4)
    REDUCE(ts_aux_sym_token2, ts_sym_assignment, 4)
    END_STATE();
    
    STATE(19);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_expression, 1)
    REDUCE(ts_aux_sym_token2, ts_sym_expression, 1)
    END_STATE();
    
    STATE(20);
    SET_LEX_STATE(67);
    SHIFT(ts_sym_array, 21)
    SHIFT(ts_sym_expression, 22)
    SHIFT(ts_sym_false, 21)
    SHIFT(ts_sym_identifier, 28)
    SHIFT(ts_sym_literal, 28)
    SHIFT(ts_sym_null, 21)
    SHIFT(ts_sym_number, 21)
    SHIFT(ts_sym_object, 21)
    SHIFT(ts_sym_string, 21)
    SHIFT(ts_sym_true, 21)
    SHIFT(ts_aux_sym_token10, 29)
    SHIFT(ts_aux_sym_token11, 68)
    SHIFT(ts_aux_sym_token5, 34)
    SHIFT(ts_builtin_sym_error, 22)
    END_STATE();
    
    STATE(21);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_literal, 1)
    REDUCE(ts_aux_sym_token9, ts_sym_literal, 1)
    END_STATE();
    
    STATE(22);
    SET_LEX_STATE(61);
    SHIFT(ts_aux_sym_repeat_helper4, 23)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0)
    SHIFT(ts_aux_sym_token9, 25)
    END_STATE();
    
    STATE(23);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_token11, 24)
    END_STATE();
    
    STATE(24);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_array, 4)
    REDUCE(ts_aux_sym_token2, ts_sym_array, 4)
    END_STATE();
    
    STATE(25);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 21)
    SHIFT(ts_sym_expression, 26)
    SHIFT(ts_sym_false, 21)
    SHIFT(ts_sym_identifier, 28)
    SHIFT(ts_sym_literal, 28)
    SHIFT(ts_sym_null, 21)
    SHIFT(ts_sym_number, 21)
    SHIFT(ts_sym_object, 21)
    SHIFT(ts_sym_string, 21)
    SHIFT(ts_sym_true, 21)
    SHIFT(ts_aux_sym_token10, 29)
    SHIFT(ts_aux_sym_token5, 34)
    SHIFT(ts_builtin_sym_error, 26)
    END_STATE();
    
    STATE(26);
    SET_LEX_STATE(61);
    SHIFT(ts_aux_sym_repeat_helper4, 27)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0)
    SHIFT(ts_aux_sym_token9, 25)
    END_STATE();
    
    STATE(27);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 3)
    END_STATE();
    
    STATE(28);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_expression, 1)
    REDUCE(ts_aux_sym_token9, ts_sym_expression, 1)
    END_STATE();
    
    STATE(29);
    SET_LEX_STATE(67);
    SHIFT(ts_sym_array, 21)
    SHIFT(ts_sym_expression, 30)
    SHIFT(ts_sym_false, 21)
    SHIFT(ts_sym_identifier, 28)
    SHIFT(ts_sym_literal, 28)
    SHIFT(ts_sym_null, 21)
    SHIFT(ts_sym_number, 21)
    SHIFT(ts_sym_object, 21)
    SHIFT(ts_sym_string, 21)
    SHIFT(ts_sym_true, 21)
    SHIFT(ts_aux_sym_token10, 29)
    SHIFT(ts_aux_sym_token11, 33)
    SHIFT(ts_aux_sym_token5, 34)
    SHIFT(ts_builtin_sym_error, 30)
    END_STATE();
    
    STATE(30);
    SET_LEX_STATE(61);
    SHIFT(ts_aux_sym_repeat_helper4, 31)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0)
    SHIFT(ts_aux_sym_token9, 25)
    END_STATE();
    
    STATE(31);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_token11, 32)
    END_STATE();
    
    STATE(32);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 4)
    REDUCE(ts_aux_sym_token9, ts_sym_array, 4)
    END_STATE();
    
    STATE(33);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 2)
    REDUCE(ts_aux_sym_token9, ts_sym_array, 2)
    END_STATE();
    
    STATE(34);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_string, 35)
    SHIFT(ts_aux_sym_token6, 64)
    SHIFT(ts_builtin_sym_error, 65)
    END_STATE();
    
    STATE(35);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token8, 36)
    END_STATE();
    
    STATE(36);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 37)
    SHIFT(ts_sym_expression, 38)
    SHIFT(ts_sym_false, 37)
    SHIFT(ts_sym_identifier, 46)
    SHIFT(ts_sym_literal, 46)
    SHIFT(ts_sym_null, 37)
    SHIFT(ts_sym_number, 37)
    SHIFT(ts_sym_object, 37)
    SHIFT(ts_sym_string, 37)
    SHIFT(ts_sym_true, 37)
    SHIFT(ts_aux_sym_token10, 47)
    SHIFT(ts_aux_sym_token5, 52)
    END_STATE();
    
    STATE(37);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_literal, 1)
    REDUCE(ts_aux_sym_token9, ts_sym_literal, 1)
    END_STATE();
    
    STATE(38);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 39)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(39);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 40)
    END_STATE();
    
    STATE(40);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 6)
    REDUCE(ts_aux_sym_token9, ts_sym_object, 6)
    END_STATE();
    
    STATE(41);
    SET_LEX_STATE(72);
    SHIFT(ts_sym_string, 42)
    SHIFT(ts_builtin_sym_error, 62)
    END_STATE();
    
    STATE(42);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token8, 43)
    END_STATE();
    
    STATE(43);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 37)
    SHIFT(ts_sym_expression, 44)
    SHIFT(ts_sym_false, 37)
    SHIFT(ts_sym_identifier, 46)
    SHIFT(ts_sym_literal, 46)
    SHIFT(ts_sym_null, 37)
    SHIFT(ts_sym_number, 37)
    SHIFT(ts_sym_object, 37)
    SHIFT(ts_sym_string, 37)
    SHIFT(ts_sym_true, 37)
    SHIFT(ts_aux_sym_token10, 47)
    SHIFT(ts_aux_sym_token5, 52)
    END_STATE();
    
    STATE(44);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 45)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(45);
    SET_LEX_STATE(66);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 5)
    END_STATE();
    
    STATE(46);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_expression, 1)
    REDUCE(ts_aux_sym_token9, ts_sym_expression, 1)
    END_STATE();
    
    STATE(47);
    SET_LEX_STATE(67);
    SHIFT(ts_sym_array, 21)
    SHIFT(ts_sym_expression, 48)
    SHIFT(ts_sym_false, 21)
    SHIFT(ts_sym_identifier, 28)
    SHIFT(ts_sym_literal, 28)
    SHIFT(ts_sym_null, 21)
    SHIFT(ts_sym_number, 21)
    SHIFT(ts_sym_object, 21)
    SHIFT(ts_sym_string, 21)
    SHIFT(ts_sym_true, 21)
    SHIFT(ts_aux_sym_token10, 29)
    SHIFT(ts_aux_sym_token11, 51)
    SHIFT(ts_aux_sym_token5, 34)
    SHIFT(ts_builtin_sym_error, 48)
    END_STATE();
    
    STATE(48);
    SET_LEX_STATE(61);
    SHIFT(ts_aux_sym_repeat_helper4, 49)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0)
    SHIFT(ts_aux_sym_token9, 25)
    END_STATE();
    
    STATE(49);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_token11, 50)
    END_STATE();
    
    STATE(50);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_array, 4)
    REDUCE(ts_aux_sym_token9, ts_sym_array, 4)
    END_STATE();
    
    STATE(51);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_array, 2)
    REDUCE(ts_aux_sym_token9, ts_sym_array, 2)
    END_STATE();
    
    STATE(52);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_string, 53)
    SHIFT(ts_aux_sym_token6, 58)
    SHIFT(ts_builtin_sym_error, 59)
    END_STATE();
    
    STATE(53);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token8, 54)
    END_STATE();
    
    STATE(54);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 37)
    SHIFT(ts_sym_expression, 55)
    SHIFT(ts_sym_false, 37)
    SHIFT(ts_sym_identifier, 46)
    SHIFT(ts_sym_literal, 46)
    SHIFT(ts_sym_null, 37)
    SHIFT(ts_sym_number, 37)
    SHIFT(ts_sym_object, 37)
    SHIFT(ts_sym_string, 37)
    SHIFT(ts_sym_true, 37)
    SHIFT(ts_aux_sym_token10, 47)
    SHIFT(ts_aux_sym_token5, 52)
    END_STATE();
    
    STATE(55);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 56)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(56);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 57)
    END_STATE();
    
    STATE(57);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_object, 6)
    REDUCE(ts_aux_sym_token9, ts_sym_object, 6)
    END_STATE();
    
    STATE(58);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_object, 2)
    REDUCE(ts_aux_sym_token9, ts_sym_object, 2)
    END_STATE();
    
    STATE(59);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 60)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(60);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 61)
    END_STATE();
    
    STATE(61);
    SET_LEX_STATE(65);
    REDUCE(ts_aux_sym_token6, ts_sym_object, 4)
    REDUCE(ts_aux_sym_token9, ts_sym_object, 4)
    END_STATE();
    
    STATE(62);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 63)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(63);
    SET_LEX_STATE(66);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 3)
    END_STATE();
    
    STATE(64);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 2)
    REDUCE(ts_aux_sym_token9, ts_sym_object, 2)
    END_STATE();
    
    STATE(65);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 66)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(66);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 67)
    END_STATE();
    
    STATE(67);
    SET_LEX_STATE(61);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 4)
    REDUCE(ts_aux_sym_token9, ts_sym_object, 4)
    END_STATE();
    
    STATE(68);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_array, 2)
    REDUCE(ts_aux_sym_token2, ts_sym_array, 2)
    END_STATE();
    
    STATE(69);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_string, 70)
    SHIFT(ts_aux_sym_token6, 75)
    SHIFT(ts_builtin_sym_error, 76)
    END_STATE();
    
    STATE(70);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token8, 71)
    END_STATE();
    
    STATE(71);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 37)
    SHIFT(ts_sym_expression, 72)
    SHIFT(ts_sym_false, 37)
    SHIFT(ts_sym_identifier, 46)
    SHIFT(ts_sym_literal, 46)
    SHIFT(ts_sym_null, 37)
    SHIFT(ts_sym_number, 37)
    SHIFT(ts_sym_object, 37)
    SHIFT(ts_sym_string, 37)
    SHIFT(ts_sym_true, 37)
    SHIFT(ts_aux_sym_token10, 47)
    SHIFT(ts_aux_sym_token5, 52)
    END_STATE();
    
    STATE(72);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 73)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(73);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 74)
    END_STATE();
    
    STATE(74);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 6)
    REDUCE(ts_aux_sym_token2, ts_sym_object, 6)
    END_STATE();
    
    STATE(75);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 2)
    REDUCE(ts_aux_sym_token2, ts_sym_object, 2)
    END_STATE();
    
    STATE(76);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 77)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(77);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 78)
    END_STATE();
    
    STATE(78);
    SET_LEX_STATE(58);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 4)
    REDUCE(ts_aux_sym_token2, ts_sym_object, 4)
    END_STATE();
    
    STATE(79);
    SET_LEX_STATE(58);
    SHIFT(ts_sym__terminator, 80)
    SHIFT(ts_aux_sym_token1, 81)
    SHIFT(ts_aux_sym_token2, 81)
    END_STATE();
    
    STATE(80);
    SET_LEX_STATE(56);
    REDUCE(ts_sym__IF, ts_sym_statement, 2)
    REDUCE(ts_sym__VAR, ts_sym_statement, 2)
    REDUCE(ts_sym_false, ts_sym_statement, 2)
    REDUCE(ts_sym_identifier, ts_sym_statement, 2)
    REDUCE(ts_sym_null, ts_sym_statement, 2)
    REDUCE(ts_sym_number, ts_sym_statement, 2)
    REDUCE(ts_sym_string, ts_sym_statement, 2)
    REDUCE(ts_sym_true, ts_sym_statement, 2)
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 2)
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 2)
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 2)
    END_STATE();
    
    STATE(81);
    SET_LEX_STATE(56);
    REDUCE(ts_sym__IF, ts_sym__terminator, 1)
    REDUCE(ts_sym__VAR, ts_sym__terminator, 1)
    REDUCE(ts_sym_false, ts_sym__terminator, 1)
    REDUCE(ts_sym_identifier, ts_sym__terminator, 1)
    REDUCE(ts_sym_null, ts_sym__terminator, 1)
    REDUCE(ts_sym_number, ts_sym__terminator, 1)
    REDUCE(ts_sym_string, ts_sym__terminator, 1)
    REDUCE(ts_sym_true, ts_sym__terminator, 1)
    REDUCE(ts_aux_sym_token10, ts_sym__terminator, 1)
    REDUCE(ts_aux_sym_token5, ts_sym__terminator, 1)
    REDUCE(ts_aux_sym_token6, ts_sym__terminator, 1)
    END_STATE();
    
    STATE(82);
    SET_LEX_STATE(56);
    REDUCE(ts_sym__IF, ts_sym_statement, 1)
    REDUCE(ts_sym__VAR, ts_sym_statement, 1)
    REDUCE(ts_sym_false, ts_sym_statement, 1)
    REDUCE(ts_sym_identifier, ts_sym_statement, 1)
    REDUCE(ts_sym_null, ts_sym_statement, 1)
    REDUCE(ts_sym_number, ts_sym_statement, 1)
    REDUCE(ts_sym_string, ts_sym_statement, 1)
    REDUCE(ts_sym_true, ts_sym_statement, 1)
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 1)
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 1)
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 1)
    END_STATE();
    
    STATE(83);
    SET_LEX_STATE(56);
    SHIFT(ts_sym__IF, 8)
    SHIFT(ts_sym__VAR, 14)
    SHIFT(ts_sym_array, 17)
    SHIFT(ts_sym_assignment, 79)
    SHIFT(ts_sym_expression, 79)
    SHIFT(ts_sym_false, 17)
    SHIFT(ts_sym_identifier, 19)
    SHIFT(ts_sym_if_statement, 82)
    SHIFT(ts_sym_literal, 19)
    SHIFT(ts_sym_null, 17)
    SHIFT(ts_sym_number, 17)
    SHIFT(ts_sym_object, 17)
    SHIFT(ts_sym_statement, 83)
    SHIFT(ts_sym_string, 17)
    SHIFT(ts_sym_true, 17)
    SHIFT(ts_aux_sym_repeat_helper2, 84)
    SHIFT(ts_aux_sym_token10, 20)
    SHIFT(ts_aux_sym_token5, 69)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0)
    END_STATE();
    
    STATE(84);
    SET_LEX_STATE(66);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 2)
    END_STATE();
    
    STATE(85);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 86)
    END_STATE();
    
    STATE(86);
    SET_LEX_STATE(56);
    REDUCE(ts_sym__IF, ts_sym_statement_block, 3)
    REDUCE(ts_sym__VAR, ts_sym_statement_block, 3)
    REDUCE(ts_sym_false, ts_sym_statement_block, 3)
    REDUCE(ts_sym_identifier, ts_sym_statement_block, 3)
    REDUCE(ts_sym_null, ts_sym_statement_block, 3)
    REDUCE(ts_sym_number, ts_sym_statement_block, 3)
    REDUCE(ts_sym_string, ts_sym_statement_block, 3)
    REDUCE(ts_sym_true, ts_sym_statement_block, 3)
    REDUCE(ts_aux_sym_token10, ts_sym_statement_block, 3)
    REDUCE(ts_aux_sym_token5, ts_sym_statement_block, 3)
    REDUCE(ts_aux_sym_token6, ts_sym_statement_block, 3)
    END_STATE();
    
    STATE(87);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_expression, 1)
    END_STATE();
    
    STATE(88);
    SET_LEX_STATE(67);
    SHIFT(ts_sym_array, 21)
    SHIFT(ts_sym_expression, 89)
    SHIFT(ts_sym_false, 21)
    SHIFT(ts_sym_identifier, 28)
    SHIFT(ts_sym_literal, 28)
    SHIFT(ts_sym_null, 21)
    SHIFT(ts_sym_number, 21)
    SHIFT(ts_sym_object, 21)
    SHIFT(ts_sym_string, 21)
    SHIFT(ts_sym_true, 21)
    SHIFT(ts_aux_sym_token10, 29)
    SHIFT(ts_aux_sym_token11, 92)
    SHIFT(ts_aux_sym_token5, 34)
    SHIFT(ts_builtin_sym_error, 89)
    END_STATE();
    
    STATE(89);
    SET_LEX_STATE(61);
    SHIFT(ts_aux_sym_repeat_helper4, 90)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0)
    SHIFT(ts_aux_sym_token9, 25)
    END_STATE();
    
    STATE(90);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_token11, 91)
    END_STATE();
    
    STATE(91);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_array, 4)
    END_STATE();
    
    STATE(92);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_array, 2)
    END_STATE();
    
    STATE(93);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_string, 94)
    SHIFT(ts_aux_sym_token6, 99)
    SHIFT(ts_builtin_sym_error, 100)
    END_STATE();
    
    STATE(94);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token8, 95)
    END_STATE();
    
    STATE(95);
    SET_LEX_STATE(68);
    SHIFT(ts_sym_array, 37)
    SHIFT(ts_sym_expression, 96)
    SHIFT(ts_sym_false, 37)
    SHIFT(ts_sym_identifier, 46)
    SHIFT(ts_sym_literal, 46)
    SHIFT(ts_sym_null, 37)
    SHIFT(ts_sym_number, 37)
    SHIFT(ts_sym_object, 37)
    SHIFT(ts_sym_string, 37)
    SHIFT(ts_sym_true, 37)
    SHIFT(ts_aux_sym_token10, 47)
    SHIFT(ts_aux_sym_token5, 52)
    END_STATE();
    
    STATE(96);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 97)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(97);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 98)
    END_STATE();
    
    STATE(98);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_object, 6)
    END_STATE();
    
    STATE(99);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_object, 2)
    END_STATE();
    
    STATE(100);
    SET_LEX_STATE(65);
    SHIFT(ts_aux_sym_repeat_helper3, 101)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0)
    SHIFT(ts_aux_sym_token9, 41)
    END_STATE();
    
    STATE(101);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 102)
    END_STATE();
    
    STATE(102);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token4, ts_sym_object, 4)
    END_STATE();
    
    STATE(103);
    SET_LEX_STATE(66);
    SHIFT(ts_aux_sym_token6, 104)
    END_STATE();
    
    STATE(104);
    SET_LEX_STATE(2);
    REDUCE(ts_sym__IF, ts_sym_statement_block, 3)
    REDUCE(ts_sym__VAR, ts_sym_statement_block, 3)
    REDUCE(ts_sym_false, ts_sym_statement_block, 3)
    REDUCE(ts_sym_identifier, ts_sym_statement_block, 3)
    REDUCE(ts_sym_null, ts_sym_statement_block, 3)
    REDUCE(ts_sym_number, ts_sym_statement_block, 3)
    REDUCE(ts_sym_string, ts_sym_statement_block, 3)
    REDUCE(ts_sym_true, ts_sym_statement_block, 3)
    REDUCE(ts_aux_sym_token10, ts_sym_statement_block, 3)
    REDUCE(ts_aux_sym_token5, ts_sym_statement_block, 3)
    REDUCE(ts_builtin_sym_end, ts_sym_statement_block, 3)
    END_STATE();
    
    STATE(105);
    SET_LEX_STATE(58);
    SHIFT(ts_sym__terminator, 106)
    SHIFT(ts_aux_sym_token1, 107)
    SHIFT(ts_aux_sym_token2, 107)
    END_STATE();
    
    STATE(106);
    SET_LEX_STATE(2);
    REDUCE(ts_sym__IF, ts_sym_statement, 2)
    REDUCE(ts_sym__VAR, ts_sym_statement, 2)
    REDUCE(ts_sym_false, ts_sym_statement, 2)
    REDUCE(ts_sym_identifier, ts_sym_statement, 2)
    REDUCE(ts_sym_null, ts_sym_statement, 2)
    REDUCE(ts_sym_number, ts_sym_statement, 2)
    REDUCE(ts_sym_string, ts_sym_statement, 2)
    REDUCE(ts_sym_true, ts_sym_statement, 2)
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 2)
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 2)
    REDUCE(ts_builtin_sym_end, ts_sym_statement, 2)
    END_STATE();
    
    STATE(107);
    SET_LEX_STATE(2);
    REDUCE(ts_sym__IF, ts_sym__terminator, 1)
    REDUCE(ts_sym__VAR, ts_sym__terminator, 1)
    REDUCE(ts_sym_false, ts_sym__terminator, 1)
    REDUCE(ts_sym_identifier, ts_sym__terminator, 1)
    REDUCE(ts_sym_null, ts_sym__terminator, 1)
    REDUCE(ts_sym_number, ts_sym__terminator, 1)
    REDUCE(ts_sym_string, ts_sym__terminator, 1)
    REDUCE(ts_sym_true, ts_sym__terminator, 1)
    REDUCE(ts_aux_sym_token10, ts_sym__terminator, 1)
    REDUCE(ts_aux_sym_token5, ts_sym__terminator, 1)
    REDUCE(ts_builtin_sym_end, ts_sym__terminator, 1)
    END_STATE();
    
    STATE(108);
    SET_LEX_STATE(2);
    REDUCE(ts_sym__IF, ts_sym_statement, 1)
    REDUCE(ts_sym__VAR, ts_sym_statement, 1)
    REDUCE(ts_sym_false, ts_sym_statement, 1)
    REDUCE(ts_sym_identifier, ts_sym_statement, 1)
    REDUCE(ts_sym_null, ts_sym_statement, 1)
    REDUCE(ts_sym_number, ts_sym_statement, 1)
    REDUCE(ts_sym_string, ts_sym_statement, 1)
    REDUCE(ts_sym_true, ts_sym_statement, 1)
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 1)
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 1)
    REDUCE(ts_builtin_sym_end, ts_sym_statement, 1)
    END_STATE();
    
    STATE(109);
    SET_LEX_STATE(79);
    ACCEPT_INPUT(ts_builtin_sym_end)
    END_STATE();
    
    STATE(110);
    SET_LEX_STATE(2);
    SHIFT(ts_sym__IF, 1)
    SHIFT(ts_sym__VAR, 14)
    SHIFT(ts_sym_array, 17)
    SHIFT(ts_sym_assignment, 105)
    SHIFT(ts_sym_expression, 105)
    SHIFT(ts_sym_false, 17)
    SHIFT(ts_sym_identifier, 19)
    SHIFT(ts_sym_if_statement, 108)
    SHIFT(ts_sym_literal, 19)
    SHIFT(ts_sym_null, 17)
    SHIFT(ts_sym_number, 17)
    SHIFT(ts_sym_object, 17)
    SHIFT(ts_sym_statement, 110)
    SHIFT(ts_sym_string, 17)
    SHIFT(ts_sym_true, 17)
    SHIFT(ts_aux_sym_repeat_helper1, 111)
    SHIFT(ts_aux_sym_token10, 20)
    SHIFT(ts_aux_sym_token5, 69)
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 0)
    END_STATE();
    
    STATE(111);
    SET_LEX_STATE(79);
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 2)
    END_STATE();
    
    STATE(112);
    SET_LEX_STATE(79);
    REDUCE(ts_builtin_sym_end, ts_sym_program, 1)
    END_STATE();
    
    END_TABLE();
}

EXPORT_PARSER(ts_parser_javascript);
