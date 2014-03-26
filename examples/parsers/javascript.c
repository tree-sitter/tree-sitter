#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 42

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

HIDDEN_SYMBOLS(42) = {    
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
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
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
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 8:
            if (lookahead == 'a')
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(13);
            LEX_ERROR();
        case 9:
            if (lookahead == 'l')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 's')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'e')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_sym_false);
        case 13:
            if (lookahead == 'n')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            if (lookahead == 'c')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            if (lookahead == 't')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'i')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'o')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            if (lookahead == 'n')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_sym__function);
        case 20:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(21);
            if (lookahead == '\\')
                ADVANCE(27);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(29);
            LEX_ERROR();
        case 21:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(24);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(26);
            LEX_ERROR();
        case 22:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(24);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(26);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(ts_sym_string);
        case 24:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(25);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(22);
            if (lookahead == '\\')
                ADVANCE(24);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(26);
            LEX_ERROR();
        case 25:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(24);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_string);
        case 26:
            if (lookahead == '\"')
                ADVANCE(22);
            LEX_ERROR();
        case 27:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(28);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(21);
            if (lookahead == '\\')
                ADVANCE(24);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(26);
            LEX_ERROR();
        case 28:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(24);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_string);
        case 29:
            if (lookahead == '\"')
                ADVANCE(21);
            LEX_ERROR();
        case 30:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if (lookahead == '.')
                ADVANCE(33);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_number);
        case 33:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_number);
        case 35:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_number);
        case 36:
            if (lookahead == '.')
                ADVANCE(33);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_number);
        case 37:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 38:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(39);
            if (lookahead == 'u')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'l')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'c')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 't')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'i')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'o')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym__function);
        case 50:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'u')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 52:
            ACCEPT_TOKEN(ts_sym__if);
        case 53:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym__if);
        case 54:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
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
                ADVANCE(31);
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
                ADVANCE(31);
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
                ADVANCE(31);
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
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(63);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 63:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'u')
                ADVANCE(64);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 64:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(65);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            ACCEPT_TOKEN(ts_sym_true);
        case 67:
            if (lookahead == 'e')
                ADVANCE(66);
            LEX_ERROR();
        case 68:
            if (lookahead == 'u')
                ADVANCE(67);
            LEX_ERROR();
        case 69:
            if (lookahead == 'r')
                ADVANCE(68);
            LEX_ERROR();
        case 70:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 71:
            if (lookahead == 'r')
                ADVANCE(72);
            LEX_ERROR();
        case 72:
            ACCEPT_TOKEN(ts_sym__var);
        case 73:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 74:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym__var);
        case 75:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 77:
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 78:
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == ']')
                ADVANCE(79);
            LEX_ERROR();
        case 79:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 80:
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 81:
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 82:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            LEX_ERROR();
        case 83:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if (lookahead == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 84:
            if (lookahead == '(')
                ADVANCE(85);
            LEX_ERROR();
        case 85:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 86:
            if (lookahead == ']')
                ADVANCE(79);
            LEX_ERROR();
        case 87:
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 88:
            if (lookahead == ':')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 90:
            if (lookahead == '\"')
                ADVANCE(20);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 91:
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == ']')
                ADVANCE(79);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 92:
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if (lookahead == ')')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(54);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(61);
            if (lookahead == 't')
                ADVANCE(62);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 93:
            if (lookahead == '(')
                ADVANCE(85);
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == ']')
                ADVANCE(79);
            LEX_ERROR();
        case 94:
            if (lookahead == '(')
                ADVANCE(85);
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == ',')
                ADVANCE(6);
            LEX_ERROR();
        case 95:
            if (lookahead == '(')
                ADVANCE(85);
            if (lookahead == ',')
                ADVANCE(6);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 96:
            if (lookahead == '\"')
                ADVANCE(20);
            LEX_ERROR();
        case 97:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 98:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(85);
            if (lookahead == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 99:
            if (lookahead == '=')
                ADVANCE(100);
            LEX_ERROR();
        case 100:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 101:
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == 'e')
                ADVANCE(106);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
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
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 102:
            if (lookahead == 'l')
                ADVANCE(103);
            LEX_ERROR();
        case 103:
            if (lookahead == 's')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            if (lookahead == 'e')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            ACCEPT_TOKEN(ts_sym__else);
        case 106:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'l')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 107:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 108:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 109:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym__else);
        case 110:
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
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
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 111:
            if (lookahead == '(')
                ADVANCE(85);
            if (lookahead == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 112:
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == 'e')
                ADVANCE(106);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
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
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 113:
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(20);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(30);
            if (lookahead == '(')
                ADVANCE(85);
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == ',')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(100);
            if (lookahead == '[')
                ADVANCE(37);
            if (lookahead == ']')
                ADVANCE(79);
            if (lookahead == 'e')
                ADVANCE(106);
            if (lookahead == 'f')
                ADVANCE(38);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
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
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES(239) = {
    [0] = 110,
    [1] = 82,
    [2] = 84,
    [3] = 81,
    [4] = 0,
    [5] = 7,
    [6] = 84,
    [7] = 87,
    [8] = 82,
    [9] = 84,
    [10] = 81,
    [11] = 3,
    [12] = 7,
    [13] = 82,
    [14] = 99,
    [15] = 87,
    [16] = 0,
    [17] = 0,
    [18] = 0,
    [19] = 98,
    [20] = 92,
    [21] = 82,
    [22] = 84,
    [23] = 81,
    [24] = 5,
    [25] = 7,
    [26] = 0,
    [27] = 7,
    [28] = 7,
    [29] = 7,
    [30] = 7,
    [31] = 77,
    [32] = 91,
    [33] = 82,
    [34] = 84,
    [35] = 81,
    [36] = 78,
    [37] = 7,
    [38] = 77,
    [39] = 78,
    [40] = 7,
    [41] = 97,
    [42] = 87,
    [43] = 82,
    [44] = 84,
    [45] = 81,
    [46] = 80,
    [47] = 7,
    [48] = 77,
    [49] = 80,
    [50] = 83,
    [51] = 5,
    [52] = 3,
    [53] = 81,
    [54] = 82,
    [55] = 5,
    [56] = 3,
    [57] = 81,
    [58] = 80,
    [59] = 80,
    [60] = 77,
    [61] = 0,
    [62] = 96,
    [63] = 88,
    [64] = 87,
    [65] = 80,
    [66] = 77,
    [67] = 80,
    [68] = 95,
    [69] = 92,
    [70] = 5,
    [71] = 5,
    [72] = 3,
    [73] = 80,
    [74] = 87,
    [75] = 5,
    [76] = 3,
    [77] = 5,
    [78] = 94,
    [79] = 92,
    [80] = 5,
    [81] = 3,
    [82] = 5,
    [83] = 91,
    [84] = 78,
    [85] = 78,
    [86] = 86,
    [87] = 5,
    [88] = 87,
    [89] = 78,
    [90] = 86,
    [91] = 78,
    [92] = 93,
    [93] = 92,
    [94] = 5,
    [95] = 3,
    [96] = 78,
    [97] = 78,
    [98] = 90,
    [99] = 88,
    [100] = 87,
    [101] = 80,
    [102] = 77,
    [103] = 5,
    [104] = 91,
    [105] = 78,
    [106] = 86,
    [107] = 80,
    [108] = 91,
    [109] = 78,
    [110] = 86,
    [111] = 78,
    [112] = 78,
    [113] = 90,
    [114] = 88,
    [115] = 87,
    [116] = 80,
    [117] = 77,
    [118] = 78,
    [119] = 90,
    [120] = 88,
    [121] = 87,
    [122] = 80,
    [123] = 77,
    [124] = 80,
    [125] = 80,
    [126] = 80,
    [127] = 77,
    [128] = 80,
    [129] = 78,
    [130] = 80,
    [131] = 77,
    [132] = 78,
    [133] = 80,
    [134] = 5,
    [135] = 80,
    [136] = 77,
    [137] = 5,
    [138] = 5,
    [139] = 5,
    [140] = 80,
    [141] = 80,
    [142] = 77,
    [143] = 77,
    [144] = 7,
    [145] = 0,
    [146] = 80,
    [147] = 77,
    [148] = 0,
    [149] = 78,
    [150] = 86,
    [151] = 0,
    [152] = 0,
    [153] = 77,
    [154] = 5,
    [155] = 5,
    [156] = 3,
    [157] = 0,
    [158] = 0,
    [159] = 90,
    [160] = 88,
    [161] = 77,
    [162] = 3,
    [163] = 3,
    [164] = 3,
    [165] = 110,
    [166] = 84,
    [167] = 87,
    [168] = 3,
    [169] = 110,
    [170] = 0,
    [171] = 101,
    [172] = 101,
    [173] = 101,
    [174] = 101,
    [175] = 110,
    [176] = 101,
    [177] = 7,
    [178] = 77,
    [179] = 101,
    [180] = 3,
    [181] = 111,
    [182] = 92,
    [183] = 5,
    [184] = 3,
    [185] = 3,
    [186] = 3,
    [187] = 91,
    [188] = 78,
    [189] = 86,
    [190] = 3,
    [191] = 3,
    [192] = 90,
    [193] = 88,
    [194] = 87,
    [195] = 80,
    [196] = 77,
    [197] = 3,
    [198] = 3,
    [199] = 80,
    [200] = 77,
    [201] = 3,
    [202] = 101,
    [203] = 110,
    [204] = 7,
    [205] = 77,
    [206] = 0,
    [207] = 84,
    [208] = 87,
    [209] = 3,
    [210] = 110,
    [211] = 84,
    [212] = 87,
    [213] = 3,
    [214] = 110,
    [215] = 0,
    [216] = 112,
    [217] = 112,
    [218] = 112,
    [219] = 112,
    [220] = 110,
    [221] = 112,
    [222] = 7,
    [223] = 77,
    [224] = 112,
    [225] = 112,
    [226] = 110,
    [227] = 0,
    [228] = 110,
    [229] = 110,
    [230] = 110,
    [231] = 110,
    [232] = 7,
    [233] = 77,
    [234] = 110,
    [235] = 113,
    [236] = 110,
    [237] = 113,
    [238] = 113,
};

PARSE_TABLE(239, 42) = {
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
