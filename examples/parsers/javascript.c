#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 35

enum {
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
    ts_sym_IF,
    ts_sym_VAR,
    ts_sym_terminator,
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
    "IF",
    "VAR",
    "terminator",
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

LEX_FN() {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == '\n')
                ADVANCE(1);
            if (LOOKAHEAD_CHAR() == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 3:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(21);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(32);
            if ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'i')
                ADVANCE(35);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(36);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(43);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(44);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(51);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(52);
            if ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'v')
                ADVANCE(57);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(58);
            LEX_ERROR();
        case 4:
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (LOOKAHEAD_CHAR() == 's')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_sym_false);
        case 9:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(16);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(18);
            LEX_ERROR();
        case 10:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR();
        case 11:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_sym_string);
        case 13:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(14);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR();
        case 14:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_string);
        case 15:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(11);
            LEX_ERROR();
        case 16:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(17);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(10);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            LEX_ERROR();
        case 17:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(11);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(13);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_string);
        case 18:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 19:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 21:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(22);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_number);
        case 22:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 25:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(22);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_number);
        case 26:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 27:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r') ||
                ('t' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 's')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'd') ||
                ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(33);
            if ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'f')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_IF);
        case 34:
            ACCEPT_TOKEN(ts_sym_IF);
        case 35:
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(34);
            LEX_ERROR();
        case 36:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't') ||
                ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(37);
            if ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'u')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(38);
            if ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'l')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(39);
            if ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'l')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            ACCEPT_TOKEN(ts_sym_null);
        case 41:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(40);
            LEX_ERROR();
        case 42:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(41);
            LEX_ERROR();
        case 43:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(42);
            LEX_ERROR();
        case 44:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(45);
            if ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't') ||
                ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(46);
            if ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'u')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'd') ||
                ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(47);
            if ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            ACCEPT_TOKEN(ts_sym_true);
        case 49:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(48);
            LEX_ERROR();
        case 50:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(49);
            LEX_ERROR();
        case 51:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(50);
            LEX_ERROR();
        case 52:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(53);
            if ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'a')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 53:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(54);
            if ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_VAR);
        case 55:
            ACCEPT_TOKEN(ts_sym_VAR);
        case 56:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(55);
            LEX_ERROR();
        case 57:
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(56);
            LEX_ERROR();
        case 58:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 59:
            LEX_ERROR();
        case 60:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(61);
            LEX_ERROR();
        case 61:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 62:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(21);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(32);
            if ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'i')
                ADVANCE(35);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(36);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(43);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(44);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(51);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(52);
            if ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'v')
                ADVANCE(57);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(58);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(63);
            LEX_ERROR();
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 64:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(65);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 66:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 67:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 68:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(65);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(63);
            LEX_ERROR();
        case 69:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(63);
            LEX_ERROR();
        case 70:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(21);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(66);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(36);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(43);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(44);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(51);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(58);
            LEX_ERROR();
        case 71:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(21);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(36);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(43);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(44);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(51);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(58);
            LEX_ERROR();
        case 72:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(73);
            LEX_ERROR();
        case 73:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 74:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(63);
            LEX_ERROR();
        case 75:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            LEX_ERROR();
        case 76:
            if (LOOKAHEAD_CHAR() == '=')
                ADVANCE(77);
            LEX_ERROR();
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 78:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            LEX_ERROR();
        case 79:
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(58);
            LEX_ERROR();
        case 80:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(81);
            LEX_ERROR();
        case 81:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 82:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(84);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 83:
            ACCEPT_TOKEN(ts_sym_IF);
        case 84:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_IF);
        case 85:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(88);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 86:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(87);
            LEX_ERROR();
        case 87:
            ACCEPT_TOKEN(ts_sym_VAR);
        case 88:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(89);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 89:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_VAR);
        case ts_lex_state_error:
            if (LOOKAHEAD_CHAR() == '\n')
                ADVANCE(1);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(81);
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(61);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(65);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(21);
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(73);
            if (LOOKAHEAD_CHAR() == ';')
                ADVANCE(2);
            if (LOOKAHEAD_CHAR() == '=')
                ADVANCE(77);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(26);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(66);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(82);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(36);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(43);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(44);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(51);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(85);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(58);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(63);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

PARSE_TABLE() {
    START_TABLE(113)
    
    STATE(0);
    SET_LEX_STATE(3);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 2)
    SHIFT(ts_sym_expression, 2)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_identifier, 5)
    SHIFT(ts_sym_if_statement, 6)
    SHIFT(ts_sym_literal, 5)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_program, 7)
    SHIFT(ts_sym_statement, 8)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_sym_IF, 9)
    SHIFT(ts_sym_VAR, 27)
    SHIFT(ts_aux_sym_repeat_helper1, 112)
    SHIFT(ts_aux_sym_token10, 31)
    SHIFT(ts_aux_sym_token5, 80)
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(1);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_literal, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(2);
    SET_LEX_STATE(0);
    SHIFT(ts_sym_terminator, 3)
    SHIFT(ts_aux_sym_token1, 4)
    SHIFT(ts_aux_sym_token2, 4)
    END_STATE();
    
    STATE(3);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_identifier, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_null, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_number, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_string, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_true, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_IF, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_VAR, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_statement, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(4);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_identifier, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_null, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_number, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_string, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_true, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_IF, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_VAR, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token10, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token5, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_builtin_sym_end, ts_sym_terminator, 1, COLLAPSE({1}))
    END_STATE();
    
    STATE(5);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_expression, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(6);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_identifier, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_null, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_number, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_string, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_true, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_IF, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_VAR, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_builtin_sym_end, ts_sym_statement, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(7);
    SET_LEX_STATE(59);
    ACCEPT_INPUT(ts_builtin_sym_end)
    END_STATE();
    
    STATE(8);
    SET_LEX_STATE(3);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 2)
    SHIFT(ts_sym_expression, 2)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_identifier, 5)
    SHIFT(ts_sym_if_statement, 6)
    SHIFT(ts_sym_literal, 5)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 8)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_sym_IF, 9)
    SHIFT(ts_sym_VAR, 27)
    SHIFT(ts_aux_sym_repeat_helper1, 111)
    SHIFT(ts_aux_sym_token10, 31)
    SHIFT(ts_aux_sym_token5, 80)
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(9);
    SET_LEX_STATE(80);
    SHIFT(ts_aux_sym_token3, 10)
    END_STATE();
    
    STATE(10);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 12)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_identifier, 92)
    SHIFT(ts_sym_literal, 92)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token10, 93)
    SHIFT(ts_aux_sym_token5, 98)
    END_STATE();
    
    STATE(11);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(12);
    SET_LEX_STATE(60);
    SHIFT(ts_aux_sym_token4, 13)
    END_STATE();
    
    STATE(13);
    SET_LEX_STATE(79);
    SHIFT(ts_sym_statement_block, 14)
    SHIFT(ts_aux_sym_token5, 15)
    END_STATE();
    
    STATE(14);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_identifier, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_null, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_number, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_string, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_true, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_IF, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_VAR, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token10, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token5, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_builtin_sym_end, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    END_STATE();
    
    STATE(15);
    SET_LEX_STATE(62);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 16)
    SHIFT(ts_sym_expression, 16)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_identifier, 5)
    SHIFT(ts_sym_if_statement, 19)
    SHIFT(ts_sym_literal, 5)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 20)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_sym_IF, 21)
    SHIFT(ts_sym_VAR, 27)
    SHIFT(ts_aux_sym_repeat_helper2, 109)
    SHIFT(ts_aux_sym_token10, 31)
    SHIFT(ts_aux_sym_token5, 80)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(16);
    SET_LEX_STATE(0);
    SHIFT(ts_sym_terminator, 17)
    SHIFT(ts_aux_sym_token1, 18)
    SHIFT(ts_aux_sym_token2, 18)
    END_STATE();
    
    STATE(17);
    SET_LEX_STATE(62);
    REDUCE(ts_sym_false, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_identifier, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_null, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_number, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_string, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_true, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_IF, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_VAR, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(18);
    SET_LEX_STATE(62);
    REDUCE(ts_sym_false, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_identifier, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_null, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_number, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_string, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_true, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_IF, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_VAR, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token10, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token5, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token6, ts_sym_terminator, 1, COLLAPSE({1}))
    END_STATE();
    
    STATE(19);
    SET_LEX_STATE(62);
    REDUCE(ts_sym_false, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_identifier, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_null, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_number, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_string, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_true, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_IF, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_VAR, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token10, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token5, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(20);
    SET_LEX_STATE(62);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 16)
    SHIFT(ts_sym_expression, 16)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_identifier, 5)
    SHIFT(ts_sym_if_statement, 19)
    SHIFT(ts_sym_literal, 5)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 20)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_sym_IF, 21)
    SHIFT(ts_sym_VAR, 27)
    SHIFT(ts_aux_sym_repeat_helper2, 108)
    SHIFT(ts_aux_sym_token10, 31)
    SHIFT(ts_aux_sym_token5, 80)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(21);
    SET_LEX_STATE(80);
    SHIFT(ts_aux_sym_token3, 22)
    END_STATE();
    
    STATE(22);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 23)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_identifier, 92)
    SHIFT(ts_sym_literal, 92)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token10, 93)
    SHIFT(ts_aux_sym_token5, 98)
    END_STATE();
    
    STATE(23);
    SET_LEX_STATE(60);
    SHIFT(ts_aux_sym_token4, 24)
    END_STATE();
    
    STATE(24);
    SET_LEX_STATE(79);
    SHIFT(ts_sym_statement_block, 25)
    SHIFT(ts_aux_sym_token5, 26)
    END_STATE();
    
    STATE(25);
    SET_LEX_STATE(62);
    REDUCE(ts_sym_false, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_identifier, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_null, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_number, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_string, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_true, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_IF, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_VAR, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token10, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token5, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token6, ts_sym_if_statement, 5, COLLAPSE({1, 1, 0, 1, 0}))
    END_STATE();
    
    STATE(26);
    SET_LEX_STATE(62);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 16)
    SHIFT(ts_sym_expression, 16)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_identifier, 5)
    SHIFT(ts_sym_if_statement, 19)
    SHIFT(ts_sym_literal, 5)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 20)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_sym_IF, 21)
    SHIFT(ts_sym_VAR, 27)
    SHIFT(ts_aux_sym_repeat_helper2, 90)
    SHIFT(ts_aux_sym_token10, 31)
    SHIFT(ts_aux_sym_token5, 80)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(27);
    SET_LEX_STATE(78);
    SHIFT(ts_sym_identifier, 28)
    END_STATE();
    
    STATE(28);
    SET_LEX_STATE(76);
    SHIFT(ts_aux_sym_token7, 29)
    END_STATE();
    
    STATE(29);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_expression, 30)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_identifier, 5)
    SHIFT(ts_sym_literal, 5)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_token10, 31)
    SHIFT(ts_aux_sym_token5, 80)
    END_STATE();
    
    STATE(30);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_assignment, 4, COLLAPSE({1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token2, ts_sym_assignment, 4, COLLAPSE({1, 0, 1, 0}))
    END_STATE();
    
    STATE(31);
    SET_LEX_STATE(70);
    SHIFT(ts_sym_array, 32)
    SHIFT(ts_sym_expression, 33)
    SHIFT(ts_sym_false, 32)
    SHIFT(ts_sym_identifier, 39)
    SHIFT(ts_sym_literal, 39)
    SHIFT(ts_sym_null, 32)
    SHIFT(ts_sym_number, 32)
    SHIFT(ts_sym_object, 32)
    SHIFT(ts_sym_string, 32)
    SHIFT(ts_sym_true, 32)
    SHIFT(ts_aux_sym_token10, 40)
    SHIFT(ts_aux_sym_token11, 79)
    SHIFT(ts_aux_sym_token5, 45)
    SHIFT(ts_builtin_sym_error, 33)
    END_STATE();
    
    STATE(32);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_literal, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token9, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(33);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_repeat_helper4, 34)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 36)
    END_STATE();
    
    STATE(34);
    SET_LEX_STATE(67);
    SHIFT(ts_aux_sym_token11, 35)
    END_STATE();
    
    STATE(35);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(36);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 32)
    SHIFT(ts_sym_expression, 37)
    SHIFT(ts_sym_false, 32)
    SHIFT(ts_sym_identifier, 39)
    SHIFT(ts_sym_literal, 39)
    SHIFT(ts_sym_null, 32)
    SHIFT(ts_sym_number, 32)
    SHIFT(ts_sym_object, 32)
    SHIFT(ts_sym_string, 32)
    SHIFT(ts_sym_true, 32)
    SHIFT(ts_aux_sym_token10, 40)
    SHIFT(ts_aux_sym_token5, 45)
    SHIFT(ts_builtin_sym_error, 37)
    END_STATE();
    
    STATE(37);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_repeat_helper4, 38)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 36)
    END_STATE();
    
    STATE(38);
    SET_LEX_STATE(67);
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(39);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_expression, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token9, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(40);
    SET_LEX_STATE(70);
    SHIFT(ts_sym_array, 32)
    SHIFT(ts_sym_expression, 41)
    SHIFT(ts_sym_false, 32)
    SHIFT(ts_sym_identifier, 39)
    SHIFT(ts_sym_literal, 39)
    SHIFT(ts_sym_null, 32)
    SHIFT(ts_sym_number, 32)
    SHIFT(ts_sym_object, 32)
    SHIFT(ts_sym_string, 32)
    SHIFT(ts_sym_true, 32)
    SHIFT(ts_aux_sym_token10, 40)
    SHIFT(ts_aux_sym_token11, 44)
    SHIFT(ts_aux_sym_token5, 45)
    SHIFT(ts_builtin_sym_error, 41)
    END_STATE();
    
    STATE(41);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_repeat_helper4, 42)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 36)
    END_STATE();
    
    STATE(42);
    SET_LEX_STATE(67);
    SHIFT(ts_aux_sym_token11, 43)
    END_STATE();
    
    STATE(43);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(44);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(45);
    SET_LEX_STATE(74);
    SHIFT(ts_sym_string, 46)
    SHIFT(ts_aux_sym_token6, 75)
    SHIFT(ts_builtin_sym_error, 76)
    END_STATE();
    
    STATE(46);
    SET_LEX_STATE(72);
    SHIFT(ts_aux_sym_token8, 47)
    END_STATE();
    
    STATE(47);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 48)
    SHIFT(ts_sym_expression, 49)
    SHIFT(ts_sym_false, 48)
    SHIFT(ts_sym_identifier, 57)
    SHIFT(ts_sym_literal, 57)
    SHIFT(ts_sym_null, 48)
    SHIFT(ts_sym_number, 48)
    SHIFT(ts_sym_object, 48)
    SHIFT(ts_sym_string, 48)
    SHIFT(ts_sym_true, 48)
    SHIFT(ts_aux_sym_token10, 58)
    SHIFT(ts_aux_sym_token5, 63)
    END_STATE();
    
    STATE(48);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_literal, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token9, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(49);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 50)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(50);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 51)
    END_STATE();
    
    STATE(51);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(52);
    SET_LEX_STATE(75);
    SHIFT(ts_sym_string, 53)
    SHIFT(ts_builtin_sym_error, 73)
    END_STATE();
    
    STATE(53);
    SET_LEX_STATE(72);
    SHIFT(ts_aux_sym_token8, 54)
    END_STATE();
    
    STATE(54);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 48)
    SHIFT(ts_sym_expression, 55)
    SHIFT(ts_sym_false, 48)
    SHIFT(ts_sym_identifier, 57)
    SHIFT(ts_sym_literal, 57)
    SHIFT(ts_sym_null, 48)
    SHIFT(ts_sym_number, 48)
    SHIFT(ts_sym_object, 48)
    SHIFT(ts_sym_string, 48)
    SHIFT(ts_sym_true, 48)
    SHIFT(ts_aux_sym_token10, 58)
    SHIFT(ts_aux_sym_token5, 63)
    END_STATE();
    
    STATE(55);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 56)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(56);
    SET_LEX_STATE(69);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 5, COLLAPSE({1, 0, 1, 0, 1}))
    END_STATE();
    
    STATE(57);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_expression, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token9, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(58);
    SET_LEX_STATE(70);
    SHIFT(ts_sym_array, 32)
    SHIFT(ts_sym_expression, 59)
    SHIFT(ts_sym_false, 32)
    SHIFT(ts_sym_identifier, 39)
    SHIFT(ts_sym_literal, 39)
    SHIFT(ts_sym_null, 32)
    SHIFT(ts_sym_number, 32)
    SHIFT(ts_sym_object, 32)
    SHIFT(ts_sym_string, 32)
    SHIFT(ts_sym_true, 32)
    SHIFT(ts_aux_sym_token10, 40)
    SHIFT(ts_aux_sym_token11, 62)
    SHIFT(ts_aux_sym_token5, 45)
    SHIFT(ts_builtin_sym_error, 59)
    END_STATE();
    
    STATE(59);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_repeat_helper4, 60)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 36)
    END_STATE();
    
    STATE(60);
    SET_LEX_STATE(67);
    SHIFT(ts_aux_sym_token11, 61)
    END_STATE();
    
    STATE(61);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(62);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(63);
    SET_LEX_STATE(74);
    SHIFT(ts_sym_string, 64)
    SHIFT(ts_aux_sym_token6, 69)
    SHIFT(ts_builtin_sym_error, 70)
    END_STATE();
    
    STATE(64);
    SET_LEX_STATE(72);
    SHIFT(ts_aux_sym_token8, 65)
    END_STATE();
    
    STATE(65);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 48)
    SHIFT(ts_sym_expression, 66)
    SHIFT(ts_sym_false, 48)
    SHIFT(ts_sym_identifier, 57)
    SHIFT(ts_sym_literal, 57)
    SHIFT(ts_sym_null, 48)
    SHIFT(ts_sym_number, 48)
    SHIFT(ts_sym_object, 48)
    SHIFT(ts_sym_string, 48)
    SHIFT(ts_sym_true, 48)
    SHIFT(ts_aux_sym_token10, 58)
    SHIFT(ts_aux_sym_token5, 63)
    END_STATE();
    
    STATE(66);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 67)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(67);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 68)
    END_STATE();
    
    STATE(68);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(69);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(70);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 71)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(71);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 72)
    END_STATE();
    
    STATE(72);
    SET_LEX_STATE(68);
    REDUCE(ts_aux_sym_token6, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(73);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 74)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(74);
    SET_LEX_STATE(69);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(75);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(76);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 77)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(77);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 78)
    END_STATE();
    
    STATE(78);
    SET_LEX_STATE(64);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token9, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(79);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(80);
    SET_LEX_STATE(74);
    SHIFT(ts_sym_string, 81)
    SHIFT(ts_aux_sym_token6, 86)
    SHIFT(ts_builtin_sym_error, 87)
    END_STATE();
    
    STATE(81);
    SET_LEX_STATE(72);
    SHIFT(ts_aux_sym_token8, 82)
    END_STATE();
    
    STATE(82);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 48)
    SHIFT(ts_sym_expression, 83)
    SHIFT(ts_sym_false, 48)
    SHIFT(ts_sym_identifier, 57)
    SHIFT(ts_sym_literal, 57)
    SHIFT(ts_sym_null, 48)
    SHIFT(ts_sym_number, 48)
    SHIFT(ts_sym_object, 48)
    SHIFT(ts_sym_string, 48)
    SHIFT(ts_sym_true, 48)
    SHIFT(ts_aux_sym_token10, 58)
    SHIFT(ts_aux_sym_token5, 63)
    END_STATE();
    
    STATE(83);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 84)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(84);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 85)
    END_STATE();
    
    STATE(85);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(86);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(87);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 88)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(88);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 89)
    END_STATE();
    
    STATE(89);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(90);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 91)
    END_STATE();
    
    STATE(91);
    SET_LEX_STATE(62);
    REDUCE(ts_sym_false, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_identifier, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_null, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_number, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_string, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_true, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_IF, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_VAR, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token10, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token5, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    END_STATE();
    
    STATE(92);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(93);
    SET_LEX_STATE(70);
    SHIFT(ts_sym_array, 32)
    SHIFT(ts_sym_expression, 94)
    SHIFT(ts_sym_false, 32)
    SHIFT(ts_sym_identifier, 39)
    SHIFT(ts_sym_literal, 39)
    SHIFT(ts_sym_null, 32)
    SHIFT(ts_sym_number, 32)
    SHIFT(ts_sym_object, 32)
    SHIFT(ts_sym_string, 32)
    SHIFT(ts_sym_true, 32)
    SHIFT(ts_aux_sym_token10, 40)
    SHIFT(ts_aux_sym_token11, 97)
    SHIFT(ts_aux_sym_token5, 45)
    SHIFT(ts_builtin_sym_error, 94)
    END_STATE();
    
    STATE(94);
    SET_LEX_STATE(64);
    SHIFT(ts_aux_sym_repeat_helper4, 95)
    REDUCE(ts_aux_sym_token11, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 36)
    END_STATE();
    
    STATE(95);
    SET_LEX_STATE(67);
    SHIFT(ts_aux_sym_token11, 96)
    END_STATE();
    
    STATE(96);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(97);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(98);
    SET_LEX_STATE(74);
    SHIFT(ts_sym_string, 99)
    SHIFT(ts_aux_sym_token6, 104)
    SHIFT(ts_builtin_sym_error, 105)
    END_STATE();
    
    STATE(99);
    SET_LEX_STATE(72);
    SHIFT(ts_aux_sym_token8, 100)
    END_STATE();
    
    STATE(100);
    SET_LEX_STATE(71);
    SHIFT(ts_sym_array, 48)
    SHIFT(ts_sym_expression, 101)
    SHIFT(ts_sym_false, 48)
    SHIFT(ts_sym_identifier, 57)
    SHIFT(ts_sym_literal, 57)
    SHIFT(ts_sym_null, 48)
    SHIFT(ts_sym_number, 48)
    SHIFT(ts_sym_object, 48)
    SHIFT(ts_sym_string, 48)
    SHIFT(ts_sym_true, 48)
    SHIFT(ts_aux_sym_token10, 58)
    SHIFT(ts_aux_sym_token5, 63)
    END_STATE();
    
    STATE(101);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 102)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(102);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 103)
    END_STATE();
    
    STATE(103);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(104);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(105);
    SET_LEX_STATE(68);
    SHIFT(ts_aux_sym_repeat_helper3, 106)
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token9, 52)
    END_STATE();
    
    STATE(106);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 107)
    END_STATE();
    
    STATE(107);
    SET_LEX_STATE(60);
    REDUCE(ts_aux_sym_token4, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(108);
    SET_LEX_STATE(69);
    REDUCE(ts_aux_sym_token6, ts_aux_sym_repeat_helper2, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(109);
    SET_LEX_STATE(69);
    SHIFT(ts_aux_sym_token6, 110)
    END_STATE();
    
    STATE(110);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_identifier, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_null, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_number, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_string, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_true, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_IF, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_VAR, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token10, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token5, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_statement_block, 3, COLLAPSE({1, 1, 1}))
    END_STATE();
    
    STATE(111);
    SET_LEX_STATE(59);
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(112);
    SET_LEX_STATE(59);
    REDUCE(ts_builtin_sym_end, ts_sym_program, 1, COLLAPSE({1}))
    END_STATE();
    
    END_TABLE();
}

EXPORT_PARSER(ts_parser_javascript);
