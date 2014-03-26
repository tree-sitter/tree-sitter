#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 36

enum {
    ts_sym__else = 2,
    ts_sym__if = 3,
    ts_sym__terminator = 4,
    ts_sym__var = 5,
    ts_sym_array = 6,
    ts_sym_assignment = 7,
    ts_sym_expression = 8,
    ts_sym_false = 9,
    ts_sym_identifier = 10,
    ts_sym_if_statement = 11,
    ts_sym_literal = 12,
    ts_sym_null = 13,
    ts_sym_number = 14,
    ts_sym_object = 15,
    ts_sym_program = 16,
    ts_sym_statement = 17,
    ts_sym_statement_block = 18,
    ts_sym_string = 19,
    ts_sym_true = 20,
    ts_aux_sym_repeat_helper1 = 21,
    ts_aux_sym_repeat_helper2 = 22,
    ts_aux_sym_repeat_helper3 = 23,
    ts_aux_sym_repeat_helper4 = 24,
    ts_aux_sym_token1 = 25,
    ts_aux_sym_token10 = 26,
    ts_aux_sym_token11 = 27,
    ts_aux_sym_token2 = 28,
    ts_aux_sym_token3 = 29,
    ts_aux_sym_token4 = 30,
    ts_aux_sym_token5 = 31,
    ts_aux_sym_token6 = 32,
    ts_aux_sym_token7 = 33,
    ts_aux_sym_token8 = 34,
    ts_aux_sym_token9 = 35,
};

SYMBOL_NAMES = {
    "error",
    "end",
    "_else",
    "_if",
    "_terminator",
    "_var",
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

HIDDEN_SYMBOLS(36) = {    
    [ts_sym__else] = 1,    
    [ts_sym__if] = 1,    
    [ts_sym__terminator] = 1,    
    [ts_sym__var] = 1,    
    [ts_aux_sym_repeat_helper1] = 1,    
    [ts_aux_sym_repeat_helper2] = 1,    
    [ts_aux_sym_repeat_helper3] = 1,    
    [ts_aux_sym_repeat_helper4] = 1,    
    [ts_aux_sym_token1] = 1,    
    [ts_aux_sym_token10] = 1,    
    [ts_aux_sym_token11] = 1,    
    [ts_aux_sym_token2] = 1,    
    [ts_aux_sym_token3] = 1,    
    [ts_aux_sym_token4] = 1,    
    [ts_aux_sym_token5] = 1,    
    [ts_aux_sym_token6] = 1,    
    [ts_aux_sym_token7] = 1,    
    [ts_aux_sym_token8] = 1,    
    [ts_aux_sym_token9] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 0:
            if (lookahead == ')')
                ADVANCE(1);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 2:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 3:
            if (lookahead == 'a')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (lookahead == 'l')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 's')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'e')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_sym_false);
        case 8:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(9);
            if (lookahead == '\\')
                ADVANCE(15);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(17);
            LEX_ERROR();
        case 9:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 10:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_sym_string);
        case 12:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(13);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(10);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 13:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 14:
            if (lookahead == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 15:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(16);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(9);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 16:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 17:
            if (lookahead == '\"')
                ADVANCE(9);
            LEX_ERROR();
        case 18:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if (lookahead == '.')
                ADVANCE(21);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 21:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 23:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            if (lookahead == '.')
                ADVANCE(21);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 25:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 26:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 's')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'f')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            ACCEPT_TOKEN(ts_sym__if);
        case 33:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__if);
        case 34:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(35);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(36);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(37);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            ACCEPT_TOKEN(ts_sym_null);
        case 39:
            if (lookahead == 'l')
                ADVANCE(38);
            LEX_ERROR();
        case 40:
            if (lookahead == 'l')
                ADVANCE(39);
            LEX_ERROR();
        case 41:
            if (lookahead == 'u')
                ADVANCE(40);
            LEX_ERROR();
        case 42:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'r')
                ADVANCE(43);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(44);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(45);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            ACCEPT_TOKEN(ts_sym_true);
        case 47:
            if (lookahead == 'e')
                ADVANCE(46);
            LEX_ERROR();
        case 48:
            if (lookahead == 'u')
                ADVANCE(47);
            LEX_ERROR();
        case 49:
            if (lookahead == 'r')
                ADVANCE(48);
            LEX_ERROR();
        case 50:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if (lookahead == 'r')
                ADVANCE(52);
            LEX_ERROR();
        case 52:
            ACCEPT_TOKEN(ts_sym__var);
        case 53:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'r')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__var);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 56:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 58:
            if (lookahead == '\n')
                ADVANCE(59);
            if (lookahead == ';')
                ADVANCE(60);
            LEX_ERROR();
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 60:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 61:
            if (lookahead == ',')
                ADVANCE(62);
            if (lookahead == ']')
                ADVANCE(63);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 64:
            if (lookahead == ']')
                ADVANCE(63);
            LEX_ERROR();
        case 65:
            if (lookahead == ',')
                ADVANCE(62);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 66:
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 67:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == ']')
                ADVANCE(63);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 68:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 69:
            if (lookahead == ':')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 71:
            if (lookahead == '\"')
                ADVANCE(8);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 72:
            if (lookahead == '\"')
                ADVANCE(8);
            LEX_ERROR();
        case 73:
            if (lookahead == '=')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 75:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            LEX_ERROR();
        case 76:
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 77:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'e')
                ADVANCE(82);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 78:
            if (lookahead == 'l')
                ADVANCE(79);
            LEX_ERROR();
        case 79:
            if (lookahead == 's')
                ADVANCE(80);
            LEX_ERROR();
        case 80:
            if (lookahead == 'e')
                ADVANCE(81);
            LEX_ERROR();
        case 81:
            ACCEPT_TOKEN(ts_sym__else);
        case 82:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(83);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 83:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 's')
                ADVANCE(84);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 84:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 85:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__else);
        case 86:
            if (lookahead == '(')
                ADVANCE(87);
            LEX_ERROR();
        case 87:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 88:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'e')
                ADVANCE(82);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 89:
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(59);
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if (lookahead == '(')
                ADVANCE(87);
            if (lookahead == ')')
                ADVANCE(1);
            if (lookahead == ',')
                ADVANCE(62);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == ':')
                ADVANCE(70);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(74);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == ']')
                ADVANCE(63);
            if (lookahead == 'e')
                ADVANCE(82);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES(123) = {
    [0] = 2,
    [1] = 86,
    [2] = 68,
    [3] = 0,
    [4] = 0,
    [5] = 76,
    [6] = 88,
    [7] = 76,
    [8] = 2,
    [9] = 56,
    [10] = 86,
    [11] = 68,
    [12] = 0,
    [13] = 76,
    [14] = 77,
    [15] = 76,
    [16] = 56,
    [17] = 56,
    [18] = 75,
    [19] = 73,
    [20] = 68,
    [21] = 58,
    [22] = 58,
    [23] = 58,
    [24] = 67,
    [25] = 61,
    [26] = 61,
    [27] = 64,
    [28] = 58,
    [29] = 68,
    [30] = 61,
    [31] = 64,
    [32] = 61,
    [33] = 67,
    [34] = 61,
    [35] = 64,
    [36] = 61,
    [37] = 61,
    [38] = 71,
    [39] = 69,
    [40] = 68,
    [41] = 65,
    [42] = 65,
    [43] = 66,
    [44] = 61,
    [45] = 72,
    [46] = 69,
    [47] = 68,
    [48] = 65,
    [49] = 66,
    [50] = 65,
    [51] = 67,
    [52] = 61,
    [53] = 64,
    [54] = 65,
    [55] = 65,
    [56] = 71,
    [57] = 69,
    [58] = 68,
    [59] = 65,
    [60] = 66,
    [61] = 65,
    [62] = 65,
    [63] = 65,
    [64] = 66,
    [65] = 65,
    [66] = 65,
    [67] = 66,
    [68] = 61,
    [69] = 65,
    [70] = 66,
    [71] = 61,
    [72] = 58,
    [73] = 71,
    [74] = 69,
    [75] = 68,
    [76] = 65,
    [77] = 66,
    [78] = 58,
    [79] = 58,
    [80] = 65,
    [81] = 66,
    [82] = 58,
    [83] = 58,
    [84] = 56,
    [85] = 56,
    [86] = 56,
    [87] = 56,
    [88] = 66,
    [89] = 66,
    [90] = 56,
    [91] = 56,
    [92] = 66,
    [93] = 77,
    [94] = 0,
    [95] = 67,
    [96] = 61,
    [97] = 64,
    [98] = 0,
    [99] = 0,
    [100] = 71,
    [101] = 69,
    [102] = 68,
    [103] = 65,
    [104] = 66,
    [105] = 0,
    [106] = 0,
    [107] = 65,
    [108] = 66,
    [109] = 0,
    [110] = 66,
    [111] = 2,
    [112] = 56,
    [113] = 66,
    [114] = 88,
    [115] = 58,
    [116] = 2,
    [117] = 2,
    [118] = 2,
    [119] = 89,
    [120] = 2,
    [121] = 89,
    [122] = 89,
};

PARSE_TABLE(123, 36) = {
    [0] = {    
        [ts_sym__if] = SHIFT(1),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(115),    
        [ts_sym_expression] = SHIFT(115),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(118),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_program] = SHIFT(119),    
        [ts_sym_statement] = SHIFT(120),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper1] = SHIFT(122),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [1] = {    
        [ts_aux_sym_token3] = SHIFT(2),
    },
    
    [2] = {    
        [ts_sym_array] = SHIFT(3),    
        [ts_sym_expression] = SHIFT(4),    
        [ts_sym_false] = SHIFT(3),    
        [ts_sym_identifier] = SHIFT(94),    
        [ts_sym_literal] = SHIFT(94),    
        [ts_sym_null] = SHIFT(3),    
        [ts_sym_number] = SHIFT(3),    
        [ts_sym_object] = SHIFT(3),    
        [ts_sym_string] = SHIFT(3),    
        [ts_sym_true] = SHIFT(3),    
        [ts_aux_sym_token10] = SHIFT(95),    
        [ts_aux_sym_token5] = SHIFT(100),
    },
    
    [3] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
    },
    
    [4] = {    
        [ts_aux_sym_token4] = SHIFT(5),
    },
    
    [5] = {    
        [ts_sym_statement_block] = SHIFT(6),    
        [ts_aux_sym_token5] = SHIFT(112),
    },
    
    [6] = {    
        [ts_sym__else] = SHIFT(7),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [7] = {    
        [ts_sym_statement_block] = SHIFT(8),    
        [ts_aux_sym_token5] = SHIFT(9),
    },
    
    [8] = {    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
    },
    
    [9] = {    
        [ts_sym__if] = SHIFT(10),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(83),    
        [ts_sym_expression] = SHIFT(83),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(86),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_statement] = SHIFT(87),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper2] = SHIFT(110),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [10] = {    
        [ts_aux_sym_token3] = SHIFT(11),
    },
    
    [11] = {    
        [ts_sym_array] = SHIFT(3),    
        [ts_sym_expression] = SHIFT(12),    
        [ts_sym_false] = SHIFT(3),    
        [ts_sym_identifier] = SHIFT(94),    
        [ts_sym_literal] = SHIFT(94),    
        [ts_sym_null] = SHIFT(3),    
        [ts_sym_number] = SHIFT(3),    
        [ts_sym_object] = SHIFT(3),    
        [ts_sym_string] = SHIFT(3),    
        [ts_sym_true] = SHIFT(3),    
        [ts_aux_sym_token10] = SHIFT(95),    
        [ts_aux_sym_token5] = SHIFT(100),
    },
    
    [12] = {    
        [ts_aux_sym_token4] = SHIFT(13),
    },
    
    [13] = {    
        [ts_sym_statement_block] = SHIFT(14),    
        [ts_aux_sym_token5] = SHIFT(91),
    },
    
    [14] = {    
        [ts_sym__else] = SHIFT(15),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [15] = {    
        [ts_sym_statement_block] = SHIFT(16),    
        [ts_aux_sym_token5] = SHIFT(17),
    },
    
    [16] = {    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_if_statement, 7),
    },
    
    [17] = {    
        [ts_sym__if] = SHIFT(10),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(83),    
        [ts_sym_expression] = SHIFT(83),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(86),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_statement] = SHIFT(87),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper2] = SHIFT(89),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [18] = {    
        [ts_sym_identifier] = SHIFT(19),
    },
    
    [19] = {    
        [ts_aux_sym_token7] = SHIFT(20),
    },
    
    [20] = {    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(22),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),
    },
    
    [21] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
    },
    
    [22] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 4),
    },
    
    [23] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
    },
    
    [24] = {    
        [ts_sym_array] = SHIFT(25),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(25),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_literal] = SHIFT(32),    
        [ts_sym_null] = SHIFT(25),    
        [ts_sym_number] = SHIFT(25),    
        [ts_sym_object] = SHIFT(25),    
        [ts_sym_string] = SHIFT(25),    
        [ts_sym_true] = SHIFT(25),    
        [ts_aux_sym_token10] = SHIFT(33),    
        [ts_aux_sym_token11] = SHIFT(72),    
        [ts_aux_sym_token5] = SHIFT(38),    
        [ts_builtin_sym_error] = SHIFT(26),
    },
    
    [25] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    
    [26] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(27),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(29),
    },
    
    [27] = {    
        [ts_aux_sym_token11] = SHIFT(28),
    },
    
    [28] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
    },
    
    [29] = {    
        [ts_sym_array] = SHIFT(25),    
        [ts_sym_expression] = SHIFT(30),    
        [ts_sym_false] = SHIFT(25),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_literal] = SHIFT(32),    
        [ts_sym_null] = SHIFT(25),    
        [ts_sym_number] = SHIFT(25),    
        [ts_sym_object] = SHIFT(25),    
        [ts_sym_string] = SHIFT(25),    
        [ts_sym_true] = SHIFT(25),    
        [ts_aux_sym_token10] = SHIFT(33),    
        [ts_aux_sym_token5] = SHIFT(38),    
        [ts_builtin_sym_error] = SHIFT(30),
    },
    
    [30] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(31),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(29),
    },
    
    [31] = {    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    
    [32] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    
    [33] = {    
        [ts_sym_array] = SHIFT(25),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_false] = SHIFT(25),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_literal] = SHIFT(32),    
        [ts_sym_null] = SHIFT(25),    
        [ts_sym_number] = SHIFT(25),    
        [ts_sym_object] = SHIFT(25),    
        [ts_sym_string] = SHIFT(25),    
        [ts_sym_true] = SHIFT(25),    
        [ts_aux_sym_token10] = SHIFT(33),    
        [ts_aux_sym_token11] = SHIFT(37),    
        [ts_aux_sym_token5] = SHIFT(38),    
        [ts_builtin_sym_error] = SHIFT(34),
    },
    
    [34] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(35),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(29),
    },
    
    [35] = {    
        [ts_aux_sym_token11] = SHIFT(36),
    },
    
    [36] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    
    [37] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    
    [38] = {    
        [ts_sym_string] = SHIFT(39),    
        [ts_aux_sym_token6] = SHIFT(68),    
        [ts_builtin_sym_error] = SHIFT(69),
    },
    
    [39] = {    
        [ts_aux_sym_token8] = SHIFT(40),
    },
    
    [40] = {    
        [ts_sym_array] = SHIFT(41),    
        [ts_sym_expression] = SHIFT(42),    
        [ts_sym_false] = SHIFT(41),    
        [ts_sym_identifier] = SHIFT(50),    
        [ts_sym_literal] = SHIFT(50),    
        [ts_sym_null] = SHIFT(41),    
        [ts_sym_number] = SHIFT(41),    
        [ts_sym_object] = SHIFT(41),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(41),    
        [ts_aux_sym_token10] = SHIFT(51),    
        [ts_aux_sym_token5] = SHIFT(56),
    },
    
    [41] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    
    [42] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(43),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [43] = {    
        [ts_aux_sym_token6] = SHIFT(44),
    },
    
    [44] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    
    [45] = {    
        [ts_sym_string] = SHIFT(46),    
        [ts_builtin_sym_error] = SHIFT(66),
    },
    
    [46] = {    
        [ts_aux_sym_token8] = SHIFT(47),
    },
    
    [47] = {    
        [ts_sym_array] = SHIFT(41),    
        [ts_sym_expression] = SHIFT(48),    
        [ts_sym_false] = SHIFT(41),    
        [ts_sym_identifier] = SHIFT(50),    
        [ts_sym_literal] = SHIFT(50),    
        [ts_sym_null] = SHIFT(41),    
        [ts_sym_number] = SHIFT(41),    
        [ts_sym_object] = SHIFT(41),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(41),    
        [ts_aux_sym_token10] = SHIFT(51),    
        [ts_aux_sym_token5] = SHIFT(56),
    },
    
    [48] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(49),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [49] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 5),
    },
    
    [50] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    
    [51] = {    
        [ts_sym_array] = SHIFT(25),    
        [ts_sym_expression] = SHIFT(52),    
        [ts_sym_false] = SHIFT(25),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_literal] = SHIFT(32),    
        [ts_sym_null] = SHIFT(25),    
        [ts_sym_number] = SHIFT(25),    
        [ts_sym_object] = SHIFT(25),    
        [ts_sym_string] = SHIFT(25),    
        [ts_sym_true] = SHIFT(25),    
        [ts_aux_sym_token10] = SHIFT(33),    
        [ts_aux_sym_token11] = SHIFT(55),    
        [ts_aux_sym_token5] = SHIFT(38),    
        [ts_builtin_sym_error] = SHIFT(52),
    },
    
    [52] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(53),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(29),
    },
    
    [53] = {    
        [ts_aux_sym_token11] = SHIFT(54),
    },
    
    [54] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    
    [55] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    
    [56] = {    
        [ts_sym_string] = SHIFT(57),    
        [ts_aux_sym_token6] = SHIFT(62),    
        [ts_builtin_sym_error] = SHIFT(63),
    },
    
    [57] = {    
        [ts_aux_sym_token8] = SHIFT(58),
    },
    
    [58] = {    
        [ts_sym_array] = SHIFT(41),    
        [ts_sym_expression] = SHIFT(59),    
        [ts_sym_false] = SHIFT(41),    
        [ts_sym_identifier] = SHIFT(50),    
        [ts_sym_literal] = SHIFT(50),    
        [ts_sym_null] = SHIFT(41),    
        [ts_sym_number] = SHIFT(41),    
        [ts_sym_object] = SHIFT(41),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(41),    
        [ts_aux_sym_token10] = SHIFT(51),    
        [ts_aux_sym_token5] = SHIFT(56),
    },
    
    [59] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(60),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [60] = {    
        [ts_aux_sym_token6] = SHIFT(61),
    },
    
    [61] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    
    [62] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    
    [63] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(64),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [64] = {    
        [ts_aux_sym_token6] = SHIFT(65),
    },
    
    [65] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    
    [66] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(67),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [67] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 3),
    },
    
    [68] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    
    [69] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(70),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [70] = {    
        [ts_aux_sym_token6] = SHIFT(71),
    },
    
    [71] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    
    [72] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
    },
    
    [73] = {    
        [ts_sym_string] = SHIFT(74),    
        [ts_aux_sym_token6] = SHIFT(79),    
        [ts_builtin_sym_error] = SHIFT(80),
    },
    
    [74] = {    
        [ts_aux_sym_token8] = SHIFT(75),
    },
    
    [75] = {    
        [ts_sym_array] = SHIFT(41),    
        [ts_sym_expression] = SHIFT(76),    
        [ts_sym_false] = SHIFT(41),    
        [ts_sym_identifier] = SHIFT(50),    
        [ts_sym_literal] = SHIFT(50),    
        [ts_sym_null] = SHIFT(41),    
        [ts_sym_number] = SHIFT(41),    
        [ts_sym_object] = SHIFT(41),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(41),    
        [ts_aux_sym_token10] = SHIFT(51),    
        [ts_aux_sym_token5] = SHIFT(56),
    },
    
    [76] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(77),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [77] = {    
        [ts_aux_sym_token6] = SHIFT(78),
    },
    
    [78] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
    },
    
    [79] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
    },
    
    [80] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(81),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [81] = {    
        [ts_aux_sym_token6] = SHIFT(82),
    },
    
    [82] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
    },
    
    [83] = {    
        [ts_sym__terminator] = SHIFT(84),    
        [ts_aux_sym_token1] = SHIFT(85),    
        [ts_aux_sym_token2] = SHIFT(85),
    },
    
    [84] = {    
        [ts_sym__if] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 2),
    },
    
    [85] = {    
        [ts_sym__if] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__var] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym__terminator, 1),
    },
    
    [86] = {    
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 1),
    },
    
    [87] = {    
        [ts_sym__if] = SHIFT(10),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(83),    
        [ts_sym_expression] = SHIFT(83),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(86),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_statement] = SHIFT(87),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper2] = SHIFT(88),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [88] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    
    [89] = {    
        [ts_aux_sym_token6] = SHIFT(90),
    },
    
    [90] = {    
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [91] = {    
        [ts_sym__if] = SHIFT(10),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(83),    
        [ts_sym_expression] = SHIFT(83),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(86),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_statement] = SHIFT(87),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper2] = SHIFT(92),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [92] = {    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [93] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [94] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
    },
    
    [95] = {    
        [ts_sym_array] = SHIFT(25),    
        [ts_sym_expression] = SHIFT(96),    
        [ts_sym_false] = SHIFT(25),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_literal] = SHIFT(32),    
        [ts_sym_null] = SHIFT(25),    
        [ts_sym_number] = SHIFT(25),    
        [ts_sym_object] = SHIFT(25),    
        [ts_sym_string] = SHIFT(25),    
        [ts_sym_true] = SHIFT(25),    
        [ts_aux_sym_token10] = SHIFT(33),    
        [ts_aux_sym_token11] = SHIFT(99),    
        [ts_aux_sym_token5] = SHIFT(38),    
        [ts_builtin_sym_error] = SHIFT(96),
    },
    
    [96] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(97),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(29),
    },
    
    [97] = {    
        [ts_aux_sym_token11] = SHIFT(98),
    },
    
    [98] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
    },
    
    [99] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
    },
    
    [100] = {    
        [ts_sym_string] = SHIFT(101),    
        [ts_aux_sym_token6] = SHIFT(106),    
        [ts_builtin_sym_error] = SHIFT(107),
    },
    
    [101] = {    
        [ts_aux_sym_token8] = SHIFT(102),
    },
    
    [102] = {    
        [ts_sym_array] = SHIFT(41),    
        [ts_sym_expression] = SHIFT(103),    
        [ts_sym_false] = SHIFT(41),    
        [ts_sym_identifier] = SHIFT(50),    
        [ts_sym_literal] = SHIFT(50),    
        [ts_sym_null] = SHIFT(41),    
        [ts_sym_number] = SHIFT(41),    
        [ts_sym_object] = SHIFT(41),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(41),    
        [ts_aux_sym_token10] = SHIFT(51),    
        [ts_aux_sym_token5] = SHIFT(56),
    },
    
    [103] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(104),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [104] = {    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [105] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
    },
    
    [106] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
    },
    
    [107] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(108),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(45),
    },
    
    [108] = {    
        [ts_aux_sym_token6] = SHIFT(109),
    },
    
    [109] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
    },
    
    [110] = {    
        [ts_aux_sym_token6] = SHIFT(111),
    },
    
    [111] = {    
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [112] = {    
        [ts_sym__if] = SHIFT(10),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(83),    
        [ts_sym_expression] = SHIFT(83),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(86),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_statement] = SHIFT(87),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper2] = SHIFT(113),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [113] = {    
        [ts_aux_sym_token6] = SHIFT(114),
    },
    
    [114] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [115] = {    
        [ts_sym__terminator] = SHIFT(116),    
        [ts_aux_sym_token1] = SHIFT(117),    
        [ts_aux_sym_token2] = SHIFT(117),
    },
    
    [116] = {    
        [ts_sym__if] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 2),
    },
    
    [117] = {    
        [ts_sym__if] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__var] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__terminator, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym__terminator, 1),
    },
    
    [118] = {    
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
    },
    
    [119] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [120] = {    
        [ts_sym__if] = SHIFT(1),    
        [ts_sym__var] = SHIFT(18),    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_assignment] = SHIFT(115),    
        [ts_sym_expression] = SHIFT(115),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(23),    
        [ts_sym_if_statement] = SHIFT(118),    
        [ts_sym_literal] = SHIFT(23),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_statement] = SHIFT(120),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_repeat_helper1] = SHIFT(121),    
        [ts_aux_sym_token10] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(73),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [121] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    
    [122] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
