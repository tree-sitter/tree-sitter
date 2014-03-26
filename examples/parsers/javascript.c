#include "tree_sitter/parser.h"

STATE_COUNT = 239;
SYMBOL_COUNT = 42;

enum {
    ts_sym__else = 2,
    ts_sym__function = 3,
    ts_sym__if = 4,
    ts_sym__terminator = 5,
    ts_sym__var = 6,
    ts_sym_array = 7,
    ts_sym_assignment = 8,
    ts_sym_expression = 9,
    ts_sym_false = 10,
    ts_sym_formal_parameters = 11,
    ts_sym_function_call = 12,
    ts_sym_function_expression = 13,
    ts_sym_identifier = 14,
    ts_sym_if_statement = 15,
    ts_sym_literal = 16,
    ts_sym_null = 17,
    ts_sym_number = 18,
    ts_sym_object = 19,
    ts_sym_program = 20,
    ts_sym_statement = 21,
    ts_sym_statement_block = 22,
    ts_sym_string = 23,
    ts_sym_true = 24,
    ts_aux_sym_repeat_helper1 = 25,
    ts_aux_sym_repeat_helper2 = 26,
    ts_aux_sym_repeat_helper3 = 27,
    ts_aux_sym_repeat_helper4 = 28,
    ts_aux_sym_repeat_helper5 = 29,
    ts_aux_sym_repeat_helper6 = 30,
    ts_aux_sym_token1 = 31,
    ts_aux_sym_token10 = 32,
    ts_aux_sym_token11 = 33,
    ts_aux_sym_token2 = 34,
    ts_aux_sym_token3 = 35,
    ts_aux_sym_token4 = 36,
    ts_aux_sym_token5 = 37,
    ts_aux_sym_token6 = 38,
    ts_aux_sym_token7 = 39,
    ts_aux_sym_token8 = 40,
    ts_aux_sym_token9 = 41,
};

SYMBOL_NAMES = {
    "error",
    "end",
    "_else",
    "_function",
    "_if",
    "_terminator",
    "_var",
    "array",
    "assignment",
    "expression",
    "false",
    "formal_parameters",
    "function_call",
    "function_expression",
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
    "repeat_helper5",
    "repeat_helper6",
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

HIDDEN_SYMBOLS = {    
    [ts_sym__else] = 1,    
    [ts_sym__function] = 1,    
    [ts_sym__if] = 1,    
    [ts_sym__terminator] = 1,    
    [ts_sym__var] = 1,    
    [ts_aux_sym_repeat_helper1] = 1,    
    [ts_aux_sym_repeat_helper2] = 1,    
    [ts_aux_sym_repeat_helper3] = 1,    
    [ts_aux_sym_repeat_helper4] = 1,    
    [ts_aux_sym_repeat_helper5] = 1,    
    [ts_aux_sym_repeat_helper6] = 1,    
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
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 3:
            if (lookahead == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 5:
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == ',')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 7:
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
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(53);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(76);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
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
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(31);
            if (lookahead == 'u')
                ADVANCE(35);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if (lookahead == 'l')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            if (lookahead == 's')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            if (lookahead == 'e')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            ACCEPT_TOKEN(ts_sym_false);
        case 31:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(32);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 's')
                ADVANCE(33);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(34);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'n')
                ADVANCE(36);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'c')
                ADVANCE(37);
            if ('d' <= lookahead && lookahead <= 'c')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 't')
                ADVANCE(38);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'i')
                ADVANCE(39);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'o')
                ADVANCE(40);
            if ('p' <= lookahead && lookahead <= 'o')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'n')
                ADVANCE(41);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__function);
        case 42:
            ACCEPT_TOKEN(ts_sym__function);
        case 43:
            if (lookahead == 'n')
                ADVANCE(42);
            LEX_ERROR();
        case 44:
            if (lookahead == 'o')
                ADVANCE(43);
            LEX_ERROR();
        case 45:
            if (lookahead == 'i')
                ADVANCE(44);
            LEX_ERROR();
        case 46:
            if (lookahead == 't')
                ADVANCE(45);
            LEX_ERROR();
        case 47:
            if (lookahead == 'c')
                ADVANCE(46);
            LEX_ERROR();
        case 48:
            if (lookahead == 'n')
                ADVANCE(47);
            LEX_ERROR();
        case 49:
            if (lookahead == 'a')
                ADVANCE(27);
            LEX_ERROR();
        case 50:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'f')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            ACCEPT_TOKEN(ts_sym__if);
        case 52:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__if);
        case 53:
            if (lookahead == 'f')
                ADVANCE(51);
            LEX_ERROR();
        case 54:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(55);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 55:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(56);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 56:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(57);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 57:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 58:
            ACCEPT_TOKEN(ts_sym_null);
        case 59:
            if (lookahead == 'l')
                ADVANCE(58);
            LEX_ERROR();
        case 60:
            if (lookahead == 'l')
                ADVANCE(59);
            LEX_ERROR();
        case 61:
            if (lookahead == 'u')
                ADVANCE(60);
            LEX_ERROR();
        case 62:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'r')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 63:
            if (lookahead == 'u')
                ADVANCE(64);
            LEX_ERROR();
        case 64:
            if (lookahead == 'e')
                ADVANCE(65);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_sym_true);
        case 66:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 67:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 68:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 69:
            if (lookahead == 'r')
                ADVANCE(63);
            LEX_ERROR();
        case 70:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(71);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 71:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'r')
                ADVANCE(72);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 72:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__var);
        case 73:
            ACCEPT_TOKEN(ts_sym__var);
        case 74:
            if (lookahead == 'r')
                ADVANCE(73);
            LEX_ERROR();
        case 75:
            if (lookahead == 'a')
                ADVANCE(74);
            LEX_ERROR();
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 78:
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 79:
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == ']')
                ADVANCE(80);
            LEX_ERROR();
        case 80:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 81:
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 82:
            if (lookahead == '{')
                ADVANCE(76);
            LEX_ERROR();
        case 83:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            LEX_ERROR();
        case 84:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if (lookahead == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 85:
            if (lookahead == '(')
                ADVANCE(86);
            LEX_ERROR();
        case 86:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 87:
            if (lookahead == ']')
                ADVANCE(80);
            LEX_ERROR();
        case 88:
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
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(90);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(76);
            LEX_ERROR();
        case 89:
            if (lookahead == 'u')
                ADVANCE(48);
            LEX_ERROR();
        case 90:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 91:
            if (lookahead == ':')
                ADVANCE(92);
            LEX_ERROR();
        case 92:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 93:
            if (lookahead == '\"')
                ADVANCE(8);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 94:
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
                ADVANCE(80);
            if (lookahead == 'f')
                ADVANCE(26);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(90);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(76);
            LEX_ERROR();
        case 95:
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
            if (lookahead == ')')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(90);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(76);
            LEX_ERROR();
        case 96:
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == ']')
                ADVANCE(80);
            LEX_ERROR();
        case 97:
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == ',')
                ADVANCE(6);
            LEX_ERROR();
        case 98:
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 99:
            if (lookahead == '\"')
                ADVANCE(8);
            LEX_ERROR();
        case 100:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ':')
                ADVANCE(92);
            if (lookahead == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 101:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 102:
            if (lookahead == '=')
                ADVANCE(103);
            LEX_ERROR();
        case 103:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 104:
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
                ADVANCE(105);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(112);
            if (lookahead == 'f')
                ADVANCE(26);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(53);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(76);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 105:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 106:
            if (lookahead == 's')
                ADVANCE(107);
            LEX_ERROR();
        case 107:
            if (lookahead == 'e')
                ADVANCE(108);
            LEX_ERROR();
        case 108:
            ACCEPT_TOKEN(ts_sym__else);
        case 109:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 's')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 110:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 111:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__else);
        case 112:
            if (lookahead == 'l')
                ADVANCE(106);
            LEX_ERROR();
        case 113:
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
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(114);
            if (lookahead == 'i')
                ADVANCE(50);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(53);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(62);
            if (lookahead == 'v')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(76);
            LEX_ERROR();
        case 114:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 115:
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 116:
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
                ADVANCE(105);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(112);
            if (lookahead == 'f')
                ADVANCE(26);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(53);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(76);
            LEX_ERROR();
        case 117:
            LEX_ERROR();
        case 118:
            if (lookahead == 'l')
                ADVANCE(106);
            if (lookahead == 'u')
                ADVANCE(48);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(1);
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
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == ',')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == ':')
                ADVANCE(92);
            if (lookahead == ';')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == ']')
                ADVANCE(80);
            if (lookahead == 'e')
                ADVANCE(105);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(26);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(53);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(76);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 113,
    [1] = 83,
    [2] = 85,
    [3] = 82,
    [4] = 0,
    [5] = 7,
    [6] = 85,
    [7] = 88,
    [8] = 83,
    [9] = 85,
    [10] = 82,
    [11] = 3,
    [12] = 7,
    [13] = 83,
    [14] = 102,
    [15] = 88,
    [16] = 0,
    [17] = 0,
    [18] = 0,
    [19] = 101,
    [20] = 95,
    [21] = 83,
    [22] = 85,
    [23] = 82,
    [24] = 5,
    [25] = 7,
    [26] = 0,
    [27] = 7,
    [28] = 7,
    [29] = 7,
    [30] = 7,
    [31] = 78,
    [32] = 94,
    [33] = 83,
    [34] = 85,
    [35] = 82,
    [36] = 79,
    [37] = 7,
    [38] = 78,
    [39] = 79,
    [40] = 7,
    [41] = 100,
    [42] = 88,
    [43] = 83,
    [44] = 85,
    [45] = 82,
    [46] = 81,
    [47] = 7,
    [48] = 78,
    [49] = 81,
    [50] = 84,
    [51] = 5,
    [52] = 3,
    [53] = 82,
    [54] = 83,
    [55] = 5,
    [56] = 3,
    [57] = 82,
    [58] = 81,
    [59] = 81,
    [60] = 78,
    [61] = 0,
    [62] = 99,
    [63] = 91,
    [64] = 88,
    [65] = 81,
    [66] = 78,
    [67] = 81,
    [68] = 98,
    [69] = 95,
    [70] = 5,
    [71] = 5,
    [72] = 3,
    [73] = 81,
    [74] = 88,
    [75] = 5,
    [76] = 3,
    [77] = 5,
    [78] = 97,
    [79] = 95,
    [80] = 5,
    [81] = 3,
    [82] = 5,
    [83] = 94,
    [84] = 79,
    [85] = 79,
    [86] = 87,
    [87] = 5,
    [88] = 88,
    [89] = 79,
    [90] = 87,
    [91] = 79,
    [92] = 96,
    [93] = 95,
    [94] = 5,
    [95] = 3,
    [96] = 79,
    [97] = 79,
    [98] = 93,
    [99] = 91,
    [100] = 88,
    [101] = 81,
    [102] = 78,
    [103] = 5,
    [104] = 94,
    [105] = 79,
    [106] = 87,
    [107] = 81,
    [108] = 94,
    [109] = 79,
    [110] = 87,
    [111] = 79,
    [112] = 79,
    [113] = 93,
    [114] = 91,
    [115] = 88,
    [116] = 81,
    [117] = 78,
    [118] = 79,
    [119] = 93,
    [120] = 91,
    [121] = 88,
    [122] = 81,
    [123] = 78,
    [124] = 81,
    [125] = 81,
    [126] = 81,
    [127] = 78,
    [128] = 81,
    [129] = 79,
    [130] = 81,
    [131] = 78,
    [132] = 79,
    [133] = 81,
    [134] = 5,
    [135] = 81,
    [136] = 78,
    [137] = 5,
    [138] = 5,
    [139] = 5,
    [140] = 81,
    [141] = 81,
    [142] = 78,
    [143] = 78,
    [144] = 7,
    [145] = 0,
    [146] = 81,
    [147] = 78,
    [148] = 0,
    [149] = 79,
    [150] = 87,
    [151] = 0,
    [152] = 0,
    [153] = 78,
    [154] = 5,
    [155] = 5,
    [156] = 3,
    [157] = 0,
    [158] = 0,
    [159] = 93,
    [160] = 91,
    [161] = 78,
    [162] = 3,
    [163] = 3,
    [164] = 3,
    [165] = 113,
    [166] = 85,
    [167] = 88,
    [168] = 3,
    [169] = 113,
    [170] = 0,
    [171] = 104,
    [172] = 104,
    [173] = 104,
    [174] = 104,
    [175] = 113,
    [176] = 104,
    [177] = 7,
    [178] = 78,
    [179] = 104,
    [180] = 3,
    [181] = 115,
    [182] = 95,
    [183] = 5,
    [184] = 3,
    [185] = 3,
    [186] = 3,
    [187] = 94,
    [188] = 79,
    [189] = 87,
    [190] = 3,
    [191] = 3,
    [192] = 93,
    [193] = 91,
    [194] = 88,
    [195] = 81,
    [196] = 78,
    [197] = 3,
    [198] = 3,
    [199] = 81,
    [200] = 78,
    [201] = 3,
    [202] = 104,
    [203] = 113,
    [204] = 7,
    [205] = 78,
    [206] = 0,
    [207] = 85,
    [208] = 88,
    [209] = 3,
    [210] = 113,
    [211] = 85,
    [212] = 88,
    [213] = 3,
    [214] = 113,
    [215] = 0,
    [216] = 116,
    [217] = 116,
    [218] = 116,
    [219] = 116,
    [220] = 113,
    [221] = 116,
    [222] = 7,
    [223] = 78,
    [224] = 116,
    [225] = 116,
    [226] = 113,
    [227] = 0,
    [228] = 113,
    [229] = 113,
    [230] = 113,
    [231] = 113,
    [232] = 7,
    [233] = 78,
    [234] = 113,
    [235] = 117,
    [236] = 113,
    [237] = 117,
    [238] = 117,
};

PARSE_TABLE = {
    [0] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(207),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(227),    
        [ts_sym_expression] = SHIFT(227),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(230),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_program] = SHIFT(235),    
        [ts_sym_statement] = SHIFT(236),    
        [ts_sym_statement_block] = SHIFT(230),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper1] = SHIFT(238),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(232),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [1] = {    
        [ts_sym_identifier] = SHIFT(2),
    },
    
    [2] = {    
        [ts_sym_formal_parameters] = SHIFT(3),    
        [ts_aux_sym_token3] = SHIFT(50),
    },
    
    [3] = {    
        [ts_sym_statement_block] = SHIFT(4),    
        [ts_aux_sym_token5] = SHIFT(5),
    },
    
    [4] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [5] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(205),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [6] = {    
        [ts_aux_sym_token3] = SHIFT(7),
    },
    
    [7] = {    
        [ts_sym__function] = SHIFT(8),    
        [ts_sym_array] = SHIFT(163),    
        [ts_sym_expression] = SHIFT(164),    
        [ts_sym_false] = SHIFT(163),    
        [ts_sym_function_call] = SHIFT(180),    
        [ts_sym_function_expression] = SHIFT(180),    
        [ts_sym_identifier] = SHIFT(181),    
        [ts_sym_literal] = SHIFT(180),    
        [ts_sym_null] = SHIFT(163),    
        [ts_sym_number] = SHIFT(163),    
        [ts_sym_object] = SHIFT(163),    
        [ts_sym_string] = SHIFT(163),    
        [ts_sym_true] = SHIFT(163),    
        [ts_aux_sym_token10] = SHIFT(187),    
        [ts_aux_sym_token5] = SHIFT(192),
    },
    
    [8] = {    
        [ts_sym_identifier] = SHIFT(9),
    },
    
    [9] = {    
        [ts_sym_formal_parameters] = SHIFT(10),    
        [ts_aux_sym_token3] = SHIFT(50),
    },
    
    [10] = {    
        [ts_sym_statement_block] = SHIFT(11),    
        [ts_aux_sym_token5] = SHIFT(12),
    },
    
    [11] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [12] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(161),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [13] = {    
        [ts_sym_identifier] = SHIFT(14),
    },
    
    [14] = {    
        [ts_aux_sym_token7] = SHIFT(15),
    },
    
    [15] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(17),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(159),
    },
    
    [16] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
    },
    
    [17] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 4),
    },
    
    [18] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
    },
    
    [19] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token3] = SHIFT(20),
    },
    
    [20] = {    
        [ts_sym__function] = SHIFT(21),    
        [ts_sym_array] = SHIFT(70),    
        [ts_sym_expression] = SHIFT(155),    
        [ts_sym_false] = SHIFT(70),    
        [ts_sym_function_call] = SHIFT(77),    
        [ts_sym_function_expression] = SHIFT(77),    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_literal] = SHIFT(77),    
        [ts_sym_null] = SHIFT(70),    
        [ts_sym_number] = SHIFT(70),    
        [ts_sym_object] = SHIFT(70),    
        [ts_sym_string] = SHIFT(70),    
        [ts_sym_true] = SHIFT(70),    
        [ts_aux_sym_token10] = SHIFT(83),    
        [ts_aux_sym_token4] = SHIFT(158),    
        [ts_aux_sym_token5] = SHIFT(98),
    },
    
    [21] = {    
        [ts_sym_identifier] = SHIFT(22),
    },
    
    [22] = {    
        [ts_sym_formal_parameters] = SHIFT(23),    
        [ts_aux_sym_token3] = SHIFT(50),
    },
    
    [23] = {    
        [ts_sym_statement_block] = SHIFT(24),    
        [ts_aux_sym_token5] = SHIFT(25),
    },
    
    [24] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [25] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(153),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [26] = {    
        [ts_sym__terminator] = SHIFT(27),    
        [ts_aux_sym_token1] = SHIFT(28),    
        [ts_aux_sym_token2] = SHIFT(28),
    },
    
    [27] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 2),    
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
    
    [28] = {    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
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
    
    [29] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),    
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
    
    [30] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(31),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [31] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    
    [32] = {    
        [ts_sym__function] = SHIFT(33),    
        [ts_sym_array] = SHIFT(84),    
        [ts_sym_expression] = SHIFT(149),    
        [ts_sym_false] = SHIFT(84),    
        [ts_sym_function_call] = SHIFT(91),    
        [ts_sym_function_expression] = SHIFT(91),    
        [ts_sym_identifier] = SHIFT(92),    
        [ts_sym_literal] = SHIFT(91),    
        [ts_sym_null] = SHIFT(84),    
        [ts_sym_number] = SHIFT(84),    
        [ts_sym_object] = SHIFT(84),    
        [ts_sym_string] = SHIFT(84),    
        [ts_sym_true] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(108),    
        [ts_aux_sym_token11] = SHIFT(152),    
        [ts_aux_sym_token5] = SHIFT(113),    
        [ts_builtin_sym_error] = SHIFT(149),
    },
    
    [33] = {    
        [ts_sym_identifier] = SHIFT(34),
    },
    
    [34] = {    
        [ts_sym_formal_parameters] = SHIFT(35),    
        [ts_aux_sym_token3] = SHIFT(50),
    },
    
    [35] = {    
        [ts_sym_statement_block] = SHIFT(36),    
        [ts_aux_sym_token5] = SHIFT(37),
    },
    
    [36] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [37] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(38),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [38] = {    
        [ts_aux_sym_token6] = SHIFT(39),
    },
    
    [39] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [40] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(143),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = SHIFT(145),    
        [ts_builtin_sym_error] = SHIFT(146),
    },
    
    [41] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token9] = SHIFT(42),
    },
    
    [42] = {    
        [ts_sym__function] = SHIFT(43),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(59),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(67),    
        [ts_sym_function_expression] = SHIFT(67),    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_sym_literal] = SHIFT(67),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(104),    
        [ts_aux_sym_token5] = SHIFT(119),
    },
    
    [43] = {    
        [ts_sym_identifier] = SHIFT(44),
    },
    
    [44] = {    
        [ts_sym_formal_parameters] = SHIFT(45),    
        [ts_aux_sym_token3] = SHIFT(50),
    },
    
    [45] = {    
        [ts_sym_statement_block] = SHIFT(46),    
        [ts_aux_sym_token5] = SHIFT(47),
    },
    
    [46] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [47] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(48),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [48] = {    
        [ts_aux_sym_token6] = SHIFT(49),
    },
    
    [49] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [50] = {    
        [ts_sym_identifier] = SHIFT(51),    
        [ts_aux_sym_token4] = SHIFT(57),
    },
    
    [51] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(52),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token8] = SHIFT(54),
    },
    
    [52] = {    
        [ts_aux_sym_token4] = SHIFT(53),
    },
    
    [53] = {    
        [ts_aux_sym_token5] = REDUCE(ts_sym_formal_parameters, 4),
    },
    
    [54] = {    
        [ts_sym_identifier] = SHIFT(55),
    },
    
    [55] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(56),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token8] = SHIFT(54),
    },
    
    [56] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    
    [57] = {    
        [ts_aux_sym_token5] = REDUCE(ts_sym_formal_parameters, 2),
    },
    
    [58] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    
    [59] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(60),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [60] = {    
        [ts_aux_sym_token6] = SHIFT(61),
    },
    
    [61] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
    },
    
    [62] = {    
        [ts_sym_string] = SHIFT(63),    
        [ts_builtin_sym_error] = SHIFT(141),
    },
    
    [63] = {    
        [ts_aux_sym_token9] = SHIFT(64),
    },
    
    [64] = {    
        [ts_sym__function] = SHIFT(43),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(65),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(67),    
        [ts_sym_function_expression] = SHIFT(67),    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_sym_literal] = SHIFT(67),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(104),    
        [ts_aux_sym_token5] = SHIFT(119),
    },
    
    [65] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(66),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [66] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 5),
    },
    
    [67] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    
    [68] = {    
        [ts_aux_sym_token3] = SHIFT(69),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    
    [69] = {    
        [ts_sym__function] = SHIFT(21),    
        [ts_sym_array] = SHIFT(70),    
        [ts_sym_expression] = SHIFT(71),    
        [ts_sym_false] = SHIFT(70),    
        [ts_sym_function_call] = SHIFT(77),    
        [ts_sym_function_expression] = SHIFT(77),    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_literal] = SHIFT(77),    
        [ts_sym_null] = SHIFT(70),    
        [ts_sym_number] = SHIFT(70),    
        [ts_sym_object] = SHIFT(70),    
        [ts_sym_string] = SHIFT(70),    
        [ts_sym_true] = SHIFT(70),    
        [ts_aux_sym_token10] = SHIFT(83),    
        [ts_aux_sym_token4] = SHIFT(140),    
        [ts_aux_sym_token5] = SHIFT(98),
    },
    
    [70] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    
    [71] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(72),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token8] = SHIFT(74),
    },
    
    [72] = {    
        [ts_aux_sym_token4] = SHIFT(73),
    },
    
    [73] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    
    [74] = {    
        [ts_sym__function] = SHIFT(21),    
        [ts_sym_array] = SHIFT(70),    
        [ts_sym_expression] = SHIFT(75),    
        [ts_sym_false] = SHIFT(70),    
        [ts_sym_function_call] = SHIFT(77),    
        [ts_sym_function_expression] = SHIFT(77),    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_literal] = SHIFT(77),    
        [ts_sym_null] = SHIFT(70),    
        [ts_sym_number] = SHIFT(70),    
        [ts_sym_object] = SHIFT(70),    
        [ts_sym_string] = SHIFT(70),    
        [ts_sym_true] = SHIFT(70),    
        [ts_aux_sym_token10] = SHIFT(83),    
        [ts_aux_sym_token5] = SHIFT(98),
    },
    
    [75] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(76),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token8] = SHIFT(74),
    },
    
    [76] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 3),
    },
    
    [77] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    
    [78] = {    
        [ts_aux_sym_token3] = SHIFT(79),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    
    [79] = {    
        [ts_sym__function] = SHIFT(21),    
        [ts_sym_array] = SHIFT(70),    
        [ts_sym_expression] = SHIFT(80),    
        [ts_sym_false] = SHIFT(70),    
        [ts_sym_function_call] = SHIFT(77),    
        [ts_sym_function_expression] = SHIFT(77),    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_literal] = SHIFT(77),    
        [ts_sym_null] = SHIFT(70),    
        [ts_sym_number] = SHIFT(70),    
        [ts_sym_object] = SHIFT(70),    
        [ts_sym_string] = SHIFT(70),    
        [ts_sym_true] = SHIFT(70),    
        [ts_aux_sym_token10] = SHIFT(83),    
        [ts_aux_sym_token4] = SHIFT(139),    
        [ts_aux_sym_token5] = SHIFT(98),
    },
    
    [80] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(81),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token8] = SHIFT(74),
    },
    
    [81] = {    
        [ts_aux_sym_token4] = SHIFT(82),
    },
    
    [82] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    
    [83] = {    
        [ts_sym__function] = SHIFT(33),    
        [ts_sym_array] = SHIFT(84),    
        [ts_sym_expression] = SHIFT(85),    
        [ts_sym_false] = SHIFT(84),    
        [ts_sym_function_call] = SHIFT(91),    
        [ts_sym_function_expression] = SHIFT(91),    
        [ts_sym_identifier] = SHIFT(92),    
        [ts_sym_literal] = SHIFT(91),    
        [ts_sym_null] = SHIFT(84),    
        [ts_sym_number] = SHIFT(84),    
        [ts_sym_object] = SHIFT(84),    
        [ts_sym_string] = SHIFT(84),    
        [ts_sym_true] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(108),    
        [ts_aux_sym_token11] = SHIFT(138),    
        [ts_aux_sym_token5] = SHIFT(113),    
        [ts_builtin_sym_error] = SHIFT(85),
    },
    
    [84] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    
    [85] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(86),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token8] = SHIFT(88),
    },
    
    [86] = {    
        [ts_aux_sym_token11] = SHIFT(87),
    },
    
    [87] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    
    [88] = {    
        [ts_sym__function] = SHIFT(33),    
        [ts_sym_array] = SHIFT(84),    
        [ts_sym_expression] = SHIFT(89),    
        [ts_sym_false] = SHIFT(84),    
        [ts_sym_function_call] = SHIFT(91),    
        [ts_sym_function_expression] = SHIFT(91),    
        [ts_sym_identifier] = SHIFT(92),    
        [ts_sym_literal] = SHIFT(91),    
        [ts_sym_null] = SHIFT(84),    
        [ts_sym_number] = SHIFT(84),    
        [ts_sym_object] = SHIFT(84),    
        [ts_sym_string] = SHIFT(84),    
        [ts_sym_true] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(108),    
        [ts_aux_sym_token5] = SHIFT(113),    
        [ts_builtin_sym_error] = SHIFT(89),
    },
    
    [89] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(90),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token8] = SHIFT(88),
    },
    
    [90] = {    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    
    [91] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    
    [92] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token3] = SHIFT(93),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    
    [93] = {    
        [ts_sym__function] = SHIFT(21),    
        [ts_sym_array] = SHIFT(70),    
        [ts_sym_expression] = SHIFT(94),    
        [ts_sym_false] = SHIFT(70),    
        [ts_sym_function_call] = SHIFT(77),    
        [ts_sym_function_expression] = SHIFT(77),    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_literal] = SHIFT(77),    
        [ts_sym_null] = SHIFT(70),    
        [ts_sym_number] = SHIFT(70),    
        [ts_sym_object] = SHIFT(70),    
        [ts_sym_string] = SHIFT(70),    
        [ts_sym_true] = SHIFT(70),    
        [ts_aux_sym_token10] = SHIFT(83),    
        [ts_aux_sym_token4] = SHIFT(97),    
        [ts_aux_sym_token5] = SHIFT(98),
    },
    
    [94] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(95),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token8] = SHIFT(74),
    },
    
    [95] = {    
        [ts_aux_sym_token4] = SHIFT(96),
    },
    
    [96] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    
    [97] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    
    [98] = {    
        [ts_sym_string] = SHIFT(99),    
        [ts_aux_sym_token6] = SHIFT(134),    
        [ts_builtin_sym_error] = SHIFT(135),
    },
    
    [99] = {    
        [ts_aux_sym_token9] = SHIFT(100),
    },
    
    [100] = {    
        [ts_sym__function] = SHIFT(43),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(101),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(67),    
        [ts_sym_function_expression] = SHIFT(67),    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_sym_literal] = SHIFT(67),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(104),    
        [ts_aux_sym_token5] = SHIFT(119),
    },
    
    [101] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(102),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [102] = {    
        [ts_aux_sym_token6] = SHIFT(103),
    },
    
    [103] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    
    [104] = {    
        [ts_sym__function] = SHIFT(33),    
        [ts_sym_array] = SHIFT(84),    
        [ts_sym_expression] = SHIFT(105),    
        [ts_sym_false] = SHIFT(84),    
        [ts_sym_function_call] = SHIFT(91),    
        [ts_sym_function_expression] = SHIFT(91),    
        [ts_sym_identifier] = SHIFT(92),    
        [ts_sym_literal] = SHIFT(91),    
        [ts_sym_null] = SHIFT(84),    
        [ts_sym_number] = SHIFT(84),    
        [ts_sym_object] = SHIFT(84),    
        [ts_sym_string] = SHIFT(84),    
        [ts_sym_true] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(108),    
        [ts_aux_sym_token11] = SHIFT(133),    
        [ts_aux_sym_token5] = SHIFT(113),    
        [ts_builtin_sym_error] = SHIFT(105),
    },
    
    [105] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(106),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token8] = SHIFT(88),
    },
    
    [106] = {    
        [ts_aux_sym_token11] = SHIFT(107),
    },
    
    [107] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    
    [108] = {    
        [ts_sym__function] = SHIFT(33),    
        [ts_sym_array] = SHIFT(84),    
        [ts_sym_expression] = SHIFT(109),    
        [ts_sym_false] = SHIFT(84),    
        [ts_sym_function_call] = SHIFT(91),    
        [ts_sym_function_expression] = SHIFT(91),    
        [ts_sym_identifier] = SHIFT(92),    
        [ts_sym_literal] = SHIFT(91),    
        [ts_sym_null] = SHIFT(84),    
        [ts_sym_number] = SHIFT(84),    
        [ts_sym_object] = SHIFT(84),    
        [ts_sym_string] = SHIFT(84),    
        [ts_sym_true] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(108),    
        [ts_aux_sym_token11] = SHIFT(112),    
        [ts_aux_sym_token5] = SHIFT(113),    
        [ts_builtin_sym_error] = SHIFT(109),
    },
    
    [109] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(110),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token8] = SHIFT(88),
    },
    
    [110] = {    
        [ts_aux_sym_token11] = SHIFT(111),
    },
    
    [111] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    
    [112] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    
    [113] = {    
        [ts_sym_string] = SHIFT(114),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_builtin_sym_error] = SHIFT(130),
    },
    
    [114] = {    
        [ts_aux_sym_token9] = SHIFT(115),
    },
    
    [115] = {    
        [ts_sym__function] = SHIFT(43),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(116),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(67),    
        [ts_sym_function_expression] = SHIFT(67),    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_sym_literal] = SHIFT(67),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(104),    
        [ts_aux_sym_token5] = SHIFT(119),
    },
    
    [116] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(117),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [117] = {    
        [ts_aux_sym_token6] = SHIFT(118),
    },
    
    [118] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    
    [119] = {    
        [ts_sym_string] = SHIFT(120),    
        [ts_aux_sym_token6] = SHIFT(125),    
        [ts_builtin_sym_error] = SHIFT(126),
    },
    
    [120] = {    
        [ts_aux_sym_token9] = SHIFT(121),
    },
    
    [121] = {    
        [ts_sym__function] = SHIFT(43),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(122),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(67),    
        [ts_sym_function_expression] = SHIFT(67),    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_sym_literal] = SHIFT(67),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(104),    
        [ts_aux_sym_token5] = SHIFT(119),
    },
    
    [122] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(123),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [123] = {    
        [ts_aux_sym_token6] = SHIFT(124),
    },
    
    [124] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    
    [125] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    
    [126] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(127),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [127] = {    
        [ts_aux_sym_token6] = SHIFT(128),
    },
    
    [128] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    
    [129] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    
    [130] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(131),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [131] = {    
        [ts_aux_sym_token6] = SHIFT(132),
    },
    
    [132] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    
    [133] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    
    [134] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    
    [135] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(136),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [136] = {    
        [ts_aux_sym_token6] = SHIFT(137),
    },
    
    [137] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    
    [138] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    
    [139] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    
    [140] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    
    [141] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(142),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [142] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    
    [143] = {    
        [ts_aux_sym_token6] = SHIFT(144),
    },
    
    [144] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [145] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
    },
    
    [146] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(147),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [147] = {    
        [ts_aux_sym_token6] = SHIFT(148),
    },
    
    [148] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
    },
    
    [149] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(150),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token8] = SHIFT(88),
    },
    
    [150] = {    
        [ts_aux_sym_token11] = SHIFT(151),
    },
    
    [151] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
    },
    
    [152] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
    },
    
    [153] = {    
        [ts_aux_sym_token6] = SHIFT(154),
    },
    
    [154] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [155] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(156),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token8] = SHIFT(74),
    },
    
    [156] = {    
        [ts_aux_sym_token4] = SHIFT(157),
    },
    
    [157] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
    },
    
    [158] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
    },
    
    [159] = {    
        [ts_sym_string] = SHIFT(160),    
        [ts_aux_sym_token6] = SHIFT(145),    
        [ts_builtin_sym_error] = SHIFT(146),
    },
    
    [160] = {    
        [ts_aux_sym_token9] = SHIFT(42),
    },
    
    [161] = {    
        [ts_aux_sym_token6] = SHIFT(162),
    },
    
    [162] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [163] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
    },
    
    [164] = {    
        [ts_aux_sym_token4] = SHIFT(165),
    },
    
    [165] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(166),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(170),    
        [ts_sym_expression] = SHIFT(170),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(173),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(202),    
        [ts_sym_statement_block] = SHIFT(173),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(177),
    },
    
    [166] = {    
        [ts_aux_sym_token3] = SHIFT(167),
    },
    
    [167] = {    
        [ts_sym__function] = SHIFT(8),    
        [ts_sym_array] = SHIFT(163),    
        [ts_sym_expression] = SHIFT(168),    
        [ts_sym_false] = SHIFT(163),    
        [ts_sym_function_call] = SHIFT(180),    
        [ts_sym_function_expression] = SHIFT(180),    
        [ts_sym_identifier] = SHIFT(181),    
        [ts_sym_literal] = SHIFT(180),    
        [ts_sym_null] = SHIFT(163),    
        [ts_sym_number] = SHIFT(163),    
        [ts_sym_object] = SHIFT(163),    
        [ts_sym_string] = SHIFT(163),    
        [ts_sym_true] = SHIFT(163),    
        [ts_aux_sym_token10] = SHIFT(187),    
        [ts_aux_sym_token5] = SHIFT(192),
    },
    
    [168] = {    
        [ts_aux_sym_token4] = SHIFT(169),
    },
    
    [169] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(166),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(170),    
        [ts_sym_expression] = SHIFT(170),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(173),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(174),    
        [ts_sym_statement_block] = SHIFT(173),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(177),
    },
    
    [170] = {    
        [ts_sym__terminator] = SHIFT(171),    
        [ts_aux_sym_token1] = SHIFT(172),    
        [ts_aux_sym_token2] = SHIFT(172),
    },
    
    [171] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__function] = REDUCE(ts_sym_statement, 2),    
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
    
    [172] = {    
        [ts_sym__else] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
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
    
    [173] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),    
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
    
    [174] = {    
        [ts_sym__else] = SHIFT(175),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [175] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(166),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(170),    
        [ts_sym_expression] = SHIFT(170),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(173),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(176),    
        [ts_sym_statement_block] = SHIFT(173),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(177),
    },
    
    [176] = {    
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [177] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(178),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = SHIFT(145),    
        [ts_builtin_sym_error] = SHIFT(146),
    },
    
    [178] = {    
        [ts_aux_sym_token6] = SHIFT(179),
    },
    
    [179] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [180] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
    },
    
    [181] = {    
        [ts_aux_sym_token3] = SHIFT(182),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
    },
    
    [182] = {    
        [ts_sym__function] = SHIFT(21),    
        [ts_sym_array] = SHIFT(70),    
        [ts_sym_expression] = SHIFT(183),    
        [ts_sym_false] = SHIFT(70),    
        [ts_sym_function_call] = SHIFT(77),    
        [ts_sym_function_expression] = SHIFT(77),    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_literal] = SHIFT(77),    
        [ts_sym_null] = SHIFT(70),    
        [ts_sym_number] = SHIFT(70),    
        [ts_sym_object] = SHIFT(70),    
        [ts_sym_string] = SHIFT(70),    
        [ts_sym_true] = SHIFT(70),    
        [ts_aux_sym_token10] = SHIFT(83),    
        [ts_aux_sym_token4] = SHIFT(186),    
        [ts_aux_sym_token5] = SHIFT(98),
    },
    
    [183] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(184),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token8] = SHIFT(74),
    },
    
    [184] = {    
        [ts_aux_sym_token4] = SHIFT(185),
    },
    
    [185] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
    },
    
    [186] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
    },
    
    [187] = {    
        [ts_sym__function] = SHIFT(33),    
        [ts_sym_array] = SHIFT(84),    
        [ts_sym_expression] = SHIFT(188),    
        [ts_sym_false] = SHIFT(84),    
        [ts_sym_function_call] = SHIFT(91),    
        [ts_sym_function_expression] = SHIFT(91),    
        [ts_sym_identifier] = SHIFT(92),    
        [ts_sym_literal] = SHIFT(91),    
        [ts_sym_null] = SHIFT(84),    
        [ts_sym_number] = SHIFT(84),    
        [ts_sym_object] = SHIFT(84),    
        [ts_sym_string] = SHIFT(84),    
        [ts_sym_true] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(108),    
        [ts_aux_sym_token11] = SHIFT(191),    
        [ts_aux_sym_token5] = SHIFT(113),    
        [ts_builtin_sym_error] = SHIFT(188),
    },
    
    [188] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(189),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token8] = SHIFT(88),
    },
    
    [189] = {    
        [ts_aux_sym_token11] = SHIFT(190),
    },
    
    [190] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
    },
    
    [191] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
    },
    
    [192] = {    
        [ts_sym_string] = SHIFT(193),    
        [ts_aux_sym_token6] = SHIFT(198),    
        [ts_builtin_sym_error] = SHIFT(199),
    },
    
    [193] = {    
        [ts_aux_sym_token9] = SHIFT(194),
    },
    
    [194] = {    
        [ts_sym__function] = SHIFT(43),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(195),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(67),    
        [ts_sym_function_expression] = SHIFT(67),    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_sym_literal] = SHIFT(67),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(104),    
        [ts_aux_sym_token5] = SHIFT(119),
    },
    
    [195] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(196),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [196] = {    
        [ts_aux_sym_token6] = SHIFT(197),
    },
    
    [197] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
    },
    
    [198] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
    },
    
    [199] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(200),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token8] = SHIFT(62),
    },
    
    [200] = {    
        [ts_aux_sym_token6] = SHIFT(201),
    },
    
    [201] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
    },
    
    [202] = {    
        [ts_sym__else] = SHIFT(203),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [203] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(204),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),
    },
    
    [204] = {    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [205] = {    
        [ts_aux_sym_token6] = SHIFT(206),
    },
    
    [206] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [207] = {    
        [ts_aux_sym_token3] = SHIFT(208),
    },
    
    [208] = {    
        [ts_sym__function] = SHIFT(8),    
        [ts_sym_array] = SHIFT(163),    
        [ts_sym_expression] = SHIFT(209),    
        [ts_sym_false] = SHIFT(163),    
        [ts_sym_function_call] = SHIFT(180),    
        [ts_sym_function_expression] = SHIFT(180),    
        [ts_sym_identifier] = SHIFT(181),    
        [ts_sym_literal] = SHIFT(180),    
        [ts_sym_null] = SHIFT(163),    
        [ts_sym_number] = SHIFT(163),    
        [ts_sym_object] = SHIFT(163),    
        [ts_sym_string] = SHIFT(163),    
        [ts_sym_true] = SHIFT(163),    
        [ts_aux_sym_token10] = SHIFT(187),    
        [ts_aux_sym_token5] = SHIFT(192),
    },
    
    [209] = {    
        [ts_aux_sym_token4] = SHIFT(210),
    },
    
    [210] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(211),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(215),    
        [ts_sym_expression] = SHIFT(215),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(218),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(225),    
        [ts_sym_statement_block] = SHIFT(218),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(222),
    },
    
    [211] = {    
        [ts_aux_sym_token3] = SHIFT(212),
    },
    
    [212] = {    
        [ts_sym__function] = SHIFT(8),    
        [ts_sym_array] = SHIFT(163),    
        [ts_sym_expression] = SHIFT(213),    
        [ts_sym_false] = SHIFT(163),    
        [ts_sym_function_call] = SHIFT(180),    
        [ts_sym_function_expression] = SHIFT(180),    
        [ts_sym_identifier] = SHIFT(181),    
        [ts_sym_literal] = SHIFT(180),    
        [ts_sym_null] = SHIFT(163),    
        [ts_sym_number] = SHIFT(163),    
        [ts_sym_object] = SHIFT(163),    
        [ts_sym_string] = SHIFT(163),    
        [ts_sym_true] = SHIFT(163),    
        [ts_aux_sym_token10] = SHIFT(187),    
        [ts_aux_sym_token5] = SHIFT(192),
    },
    
    [213] = {    
        [ts_aux_sym_token4] = SHIFT(214),
    },
    
    [214] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(211),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(215),    
        [ts_sym_expression] = SHIFT(215),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(218),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(219),    
        [ts_sym_statement_block] = SHIFT(218),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(222),
    },
    
    [215] = {    
        [ts_sym__terminator] = SHIFT(216),    
        [ts_aux_sym_token1] = SHIFT(217),    
        [ts_aux_sym_token2] = SHIFT(217),
    },
    
    [216] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__function] = REDUCE(ts_sym_statement, 2),    
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
    
    [217] = {    
        [ts_sym__else] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
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
    
    [218] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),    
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
    
    [219] = {    
        [ts_sym__else] = SHIFT(220),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [220] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(211),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(215),    
        [ts_sym_expression] = SHIFT(215),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(218),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(221),    
        [ts_sym_statement_block] = SHIFT(218),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(222),
    },
    
    [221] = {    
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [222] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(223),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = SHIFT(145),    
        [ts_builtin_sym_error] = SHIFT(146),
    },
    
    [223] = {    
        [ts_aux_sym_token6] = SHIFT(224),
    },
    
    [224] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [225] = {    
        [ts_sym__else] = SHIFT(226),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [226] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(207),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(227),    
        [ts_sym_expression] = SHIFT(227),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(230),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(231),    
        [ts_sym_statement_block] = SHIFT(230),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(232),
    },
    
    [227] = {    
        [ts_sym__terminator] = SHIFT(228),    
        [ts_aux_sym_token1] = SHIFT(229),    
        [ts_aux_sym_token2] = SHIFT(229),
    },
    
    [228] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 2),    
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
    
    [229] = {    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
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
    
    [230] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),    
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
    
    [231] = {    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [232] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(6),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(26),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(29),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(30),    
        [ts_sym_statement_block] = SHIFT(29),    
        [ts_sym_string] = SHIFT(41),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper2] = SHIFT(233),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token6] = SHIFT(145),    
        [ts_builtin_sym_error] = SHIFT(146),
    },
    
    [233] = {    
        [ts_aux_sym_token6] = SHIFT(234),
    },
    
    [234] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [235] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [236] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(207),    
        [ts_sym__var] = SHIFT(13),    
        [ts_sym_array] = SHIFT(16),    
        [ts_sym_assignment] = SHIFT(227),    
        [ts_sym_expression] = SHIFT(227),    
        [ts_sym_false] = SHIFT(16),    
        [ts_sym_function_call] = SHIFT(18),    
        [ts_sym_function_expression] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(230),    
        [ts_sym_literal] = SHIFT(18),    
        [ts_sym_null] = SHIFT(16),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_object] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(236),    
        [ts_sym_statement_block] = SHIFT(230),    
        [ts_sym_string] = SHIFT(16),    
        [ts_sym_true] = SHIFT(16),    
        [ts_aux_sym_repeat_helper1] = SHIFT(237),    
        [ts_aux_sym_token10] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(232),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [237] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    
    [238] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
