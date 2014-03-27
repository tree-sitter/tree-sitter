#include "tree_sitter/parser.h"

STATE_COUNT = 265;
SYMBOL_COUNT = 44;

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
    ts_sym_property_access = 21,
    ts_sym_statement = 22,
    ts_sym_statement_block = 23,
    ts_sym_string = 24,
    ts_sym_true = 25,
    ts_aux_sym_repeat_helper1 = 26,
    ts_aux_sym_repeat_helper2 = 27,
    ts_aux_sym_repeat_helper3 = 28,
    ts_aux_sym_repeat_helper4 = 29,
    ts_aux_sym_repeat_helper5 = 30,
    ts_aux_sym_repeat_helper6 = 31,
    ts_aux_sym_token1 = 32,
    ts_aux_sym_token10 = 33,
    ts_aux_sym_token11 = 34,
    ts_aux_sym_token12 = 35,
    ts_aux_sym_token2 = 36,
    ts_aux_sym_token3 = 37,
    ts_aux_sym_token4 = 38,
    ts_aux_sym_token5 = 39,
    ts_aux_sym_token6 = 40,
    ts_aux_sym_token7 = 41,
    ts_aux_sym_token8 = 42,
    ts_aux_sym_token9 = 43,
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
    "property_access",
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
    "token12",
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
    [ts_aux_sym_token12] = 1,    
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
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 5:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == '.')
                ADVANCE(3);
            LEX_ERROR();
        case 6:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 7:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 9:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(56);
            if (lookahead == 'n')
                ADVANCE(57);
            if (lookahead == 't')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(71);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(76);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 10:
            if (lookahead == 'a')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'l')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 's')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 'e')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(ts_sym_false);
        case 15:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(22);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(24);
            LEX_ERROR();
        case 16:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(17);
            if (lookahead == '\"')
                ADVANCE(18);
            if (lookahead == '\\')
                ADVANCE(19);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(21);
            LEX_ERROR();
        case 17:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(17);
            if (lookahead == '\"')
                ADVANCE(18);
            if (lookahead == '\\')
                ADVANCE(19);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(21);
            LEX_ERROR();
        case 18:
            ACCEPT_TOKEN(ts_sym_string);
        case 19:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(17);
            if (lookahead == '\"')
                ADVANCE(20);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(19);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(21);
            LEX_ERROR();
        case 20:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(17);
            if (lookahead == '\"')
                ADVANCE(18);
            if (lookahead == '\\')
                ADVANCE(19);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_string);
        case 21:
            if (lookahead == '\"')
                ADVANCE(17);
            LEX_ERROR();
        case 22:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(17);
            if (lookahead == '\"')
                ADVANCE(23);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(19);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(21);
            LEX_ERROR();
        case 23:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(17);
            if (lookahead == '\"')
                ADVANCE(18);
            if (lookahead == '\\')
                ADVANCE(19);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_string);
        case 24:
            if (lookahead == '\"')
                ADVANCE(16);
            LEX_ERROR();
        case 25:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if (lookahead == '.')
                ADVANCE(28);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_number);
        case 28:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_number);
        case 30:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_number);
        case 31:
            if (lookahead == '.')
                ADVANCE(28);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_number);
        case 32:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 33:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'a')
                ADVANCE(34);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(11);
            if (lookahead == 'u')
                ADVANCE(38);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'l')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 's')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'e')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'n')
                ADVANCE(39);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'c')
                ADVANCE(40);
            if ('d' <= lookahead && lookahead <= 'c')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 't')
                ADVANCE(41);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(42);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'o')
                ADVANCE(43);
            if ('p' <= lookahead && lookahead <= 'o')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'n')
                ADVANCE(44);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__function);
        case 45:
            ACCEPT_TOKEN(ts_sym__function);
        case 46:
            if (lookahead == 'n')
                ADVANCE(45);
            LEX_ERROR();
        case 47:
            if (lookahead == 'o')
                ADVANCE(46);
            LEX_ERROR();
        case 48:
            if (lookahead == 'i')
                ADVANCE(47);
            LEX_ERROR();
        case 49:
            if (lookahead == 't')
                ADVANCE(48);
            LEX_ERROR();
        case 50:
            if (lookahead == 'c')
                ADVANCE(49);
            LEX_ERROR();
        case 51:
            if (lookahead == 'n')
                ADVANCE(50);
            LEX_ERROR();
        case 52:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'a')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 53:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'f')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            ACCEPT_TOKEN(ts_sym__if);
        case 55:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__if);
        case 56:
            if (lookahead == 'f')
                ADVANCE(54);
            LEX_ERROR();
        case 57:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'u')
                ADVANCE(58);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 58:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'l')
                ADVANCE(59);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 59:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'l')
                ADVANCE(60);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 60:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 61:
            ACCEPT_TOKEN(ts_sym_null);
        case 62:
            if (lookahead == 'l')
                ADVANCE(61);
            LEX_ERROR();
        case 63:
            if (lookahead == 'l')
                ADVANCE(62);
            LEX_ERROR();
        case 64:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'r')
                ADVANCE(65);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'u')
                ADVANCE(66);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'e')
                ADVANCE(67);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 67:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 68:
            ACCEPT_TOKEN(ts_sym_true);
        case 69:
            if (lookahead == 'e')
                ADVANCE(68);
            LEX_ERROR();
        case 70:
            if (lookahead == 'u')
                ADVANCE(69);
            LEX_ERROR();
        case 71:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'a')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 72:
            if (lookahead == 'r')
                ADVANCE(73);
            LEX_ERROR();
        case 73:
            ACCEPT_TOKEN(ts_sym__var);
        case 74:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'r')
                ADVANCE(75);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 75:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__var);
        case 76:
            if (lookahead == 'a')
                ADVANCE(72);
            LEX_ERROR();
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 79:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 80:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            LEX_ERROR();
        case 81:
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 82:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 83:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(84);
            LEX_ERROR();
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 85:
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 86:
            if (lookahead == ')')
                ADVANCE(6);
            LEX_ERROR();
        case 87:
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(8);
            LEX_ERROR();
        case 88:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == ')')
                ADVANCE(6);
            LEX_ERROR();
        case 89:
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 90:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 91:
            if (lookahead == ']')
                ADVANCE(84);
            LEX_ERROR();
        case 92:
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == ']')
                ADVANCE(84);
            LEX_ERROR();
        case 93:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(84);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(57);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(94);
            if (lookahead == 't')
                ADVANCE(64);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(95);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 94:
            if (lookahead == 'u')
                ADVANCE(63);
            LEX_ERROR();
        case 95:
            if (lookahead == 'r')
                ADVANCE(70);
            LEX_ERROR();
        case 96:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(57);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(94);
            if (lookahead == 't')
                ADVANCE(64);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(95);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 97:
            if (lookahead == ':')
                ADVANCE(98);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 99:
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 100:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 101:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            LEX_ERROR();
        case 102:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == ')')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(57);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(94);
            if (lookahead == 't')
                ADVANCE(64);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(95);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 103:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(98);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 104:
            if (lookahead == '=')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 106:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(114);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(56);
            if (lookahead == 'n')
                ADVANCE(57);
            if (lookahead == 't')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(71);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(76);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 107:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'l')
                ADVANCE(108);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 108:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 's')
                ADVANCE(109);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(112);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 109:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'e')
                ADVANCE(110);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 110:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__else);
        case 111:
            ACCEPT_TOKEN(ts_sym__else);
        case 112:
            if (lookahead == 'e')
                ADVANCE(111);
            LEX_ERROR();
        case 113:
            if (lookahead == 's')
                ADVANCE(112);
            LEX_ERROR();
        case 114:
            if (lookahead == 'l')
                ADVANCE(113);
            LEX_ERROR();
        case 115:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(10);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(56);
            if (lookahead == 'n')
                ADVANCE(57);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(94);
            if (lookahead == 't')
                ADVANCE(64);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(95);
            if (lookahead == 'v')
                ADVANCE(71);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(76);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 116:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(114);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(56);
            if (lookahead == 'n')
                ADVANCE(57);
            if (lookahead == 't')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(71);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(76);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 117:
            LEX_ERROR();
        case 118:
            if (lookahead == 'l')
                ADVANCE(113);
            if (lookahead == 'u')
                ADVANCE(51);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == ':')
                ADVANCE(98);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(105);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(84);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(56);
            if (lookahead == 'n')
                ADVANCE(57);
            if (lookahead == 't')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(71);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(76);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 115,
    [1] = 90,
    [2] = 85,
    [3] = 0,
    [4] = 9,
    [5] = 89,
    [6] = 96,
    [7] = 90,
    [8] = 85,
    [9] = 5,
    [10] = 9,
    [11] = 80,
    [12] = 104,
    [13] = 96,
    [14] = 0,
    [15] = 0,
    [16] = 102,
    [17] = 90,
    [18] = 85,
    [19] = 7,
    [20] = 9,
    [21] = 79,
    [22] = 9,
    [23] = 9,
    [24] = 0,
    [25] = 80,
    [26] = 0,
    [27] = 0,
    [28] = 9,
    [29] = 9,
    [30] = 81,
    [31] = 9,
    [32] = 103,
    [33] = 96,
    [34] = 90,
    [35] = 85,
    [36] = 82,
    [37] = 9,
    [38] = 81,
    [39] = 82,
    [40] = 93,
    [41] = 90,
    [42] = 85,
    [43] = 83,
    [44] = 9,
    [45] = 81,
    [46] = 83,
    [47] = 89,
    [48] = 85,
    [49] = 83,
    [50] = 88,
    [51] = 87,
    [52] = 86,
    [53] = 85,
    [54] = 80,
    [55] = 87,
    [56] = 86,
    [57] = 85,
    [58] = 83,
    [59] = 83,
    [60] = 91,
    [61] = 0,
    [62] = 102,
    [63] = 7,
    [64] = 7,
    [65] = 86,
    [66] = 83,
    [67] = 102,
    [68] = 7,
    [69] = 86,
    [70] = 7,
    [71] = 96,
    [72] = 7,
    [73] = 86,
    [74] = 80,
    [75] = 7,
    [76] = 7,
    [77] = 100,
    [78] = 97,
    [79] = 96,
    [80] = 82,
    [81] = 82,
    [82] = 81,
    [83] = 7,
    [84] = 102,
    [85] = 7,
    [86] = 86,
    [87] = 82,
    [88] = 82,
    [89] = 93,
    [90] = 83,
    [91] = 91,
    [92] = 7,
    [93] = 96,
    [94] = 83,
    [95] = 91,
    [96] = 80,
    [97] = 83,
    [98] = 83,
    [99] = 100,
    [100] = 97,
    [101] = 96,
    [102] = 82,
    [103] = 81,
    [104] = 83,
    [105] = 101,
    [106] = 97,
    [107] = 96,
    [108] = 82,
    [109] = 81,
    [110] = 80,
    [111] = 82,
    [112] = 82,
    [113] = 100,
    [114] = 97,
    [115] = 96,
    [116] = 82,
    [117] = 81,
    [118] = 82,
    [119] = 93,
    [120] = 83,
    [121] = 91,
    [122] = 82,
    [123] = 82,
    [124] = 93,
    [125] = 83,
    [126] = 91,
    [127] = 83,
    [128] = 83,
    [129] = 92,
    [130] = 92,
    [131] = 82,
    [132] = 99,
    [133] = 81,
    [134] = 82,
    [135] = 99,
    [136] = 81,
    [137] = 83,
    [138] = 99,
    [139] = 81,
    [140] = 83,
    [141] = 92,
    [142] = 7,
    [143] = 92,
    [144] = 7,
    [145] = 99,
    [146] = 81,
    [147] = 7,
    [148] = 7,
    [149] = 83,
    [150] = 0,
    [151] = 92,
    [152] = 89,
    [153] = 85,
    [154] = 82,
    [155] = 82,
    [156] = 81,
    [157] = 0,
    [158] = 103,
    [159] = 81,
    [160] = 9,
    [161] = 0,
    [162] = 99,
    [163] = 81,
    [164] = 0,
    [165] = 81,
    [166] = 7,
    [167] = 89,
    [168] = 85,
    [169] = 7,
    [170] = 7,
    [171] = 86,
    [172] = 0,
    [173] = 0,
    [174] = 100,
    [175] = 97,
    [176] = 81,
    [177] = 5,
    [178] = 89,
    [179] = 85,
    [180] = 5,
    [181] = 5,
    [182] = 5,
    [183] = 102,
    [184] = 7,
    [185] = 86,
    [186] = 5,
    [187] = 5,
    [188] = 115,
    [189] = 89,
    [190] = 96,
    [191] = 5,
    [192] = 115,
    [193] = 79,
    [194] = 106,
    [195] = 106,
    [196] = 0,
    [197] = 106,
    [198] = 106,
    [199] = 115,
    [200] = 106,
    [201] = 9,
    [202] = 81,
    [203] = 106,
    [204] = 80,
    [205] = 5,
    [206] = 5,
    [207] = 100,
    [208] = 97,
    [209] = 96,
    [210] = 82,
    [211] = 81,
    [212] = 5,
    [213] = 5,
    [214] = 99,
    [215] = 81,
    [216] = 5,
    [217] = 93,
    [218] = 83,
    [219] = 91,
    [220] = 5,
    [221] = 5,
    [222] = 92,
    [223] = 106,
    [224] = 115,
    [225] = 9,
    [226] = 81,
    [227] = 0,
    [228] = 89,
    [229] = 85,
    [230] = 0,
    [231] = 89,
    [232] = 96,
    [233] = 5,
    [234] = 115,
    [235] = 89,
    [236] = 96,
    [237] = 5,
    [238] = 115,
    [239] = 79,
    [240] = 116,
    [241] = 116,
    [242] = 0,
    [243] = 116,
    [244] = 116,
    [245] = 115,
    [246] = 116,
    [247] = 9,
    [248] = 81,
    [249] = 116,
    [250] = 116,
    [251] = 115,
    [252] = 79,
    [253] = 115,
    [254] = 115,
    [255] = 0,
    [256] = 115,
    [257] = 115,
    [258] = 9,
    [259] = 81,
    [260] = 115,
    [261] = 117,
    [262] = 115,
    [263] = 117,
    [264] = 117,
};

PARSE_TABLE = {
    [0] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(231),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(252),    
        [ts_sym_expression] = SHIFT(255),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(256),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_program] = SHIFT(261),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(262),    
        [ts_sym_statement_block] = SHIFT(256),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper1] = SHIFT(264),    
        [ts_aux_sym_token3] = SHIFT(258),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [1] = {    
        [ts_sym_formal_parameters] = SHIFT(2),    
        [ts_sym_identifier] = SHIFT(228),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [2] = {    
        [ts_sym_statement_block] = SHIFT(3),    
        [ts_aux_sym_token3] = SHIFT(4),
    },
    
    [3] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [4] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(226),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [5] = {    
        [ts_aux_sym_token1] = SHIFT(6),
    },
    
    [6] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(181),    
        [ts_sym_expression] = SHIFT(182),    
        [ts_sym_false] = SHIFT(181),    
        [ts_sym_function_call] = SHIFT(206),    
        [ts_sym_function_expression] = SHIFT(206),    
        [ts_sym_identifier] = SHIFT(206),    
        [ts_sym_literal] = SHIFT(206),    
        [ts_sym_null] = SHIFT(181),    
        [ts_sym_number] = SHIFT(181),    
        [ts_sym_object] = SHIFT(181),    
        [ts_sym_property_access] = SHIFT(206),    
        [ts_sym_string] = SHIFT(181),    
        [ts_sym_true] = SHIFT(181),    
        [ts_aux_sym_token3] = SHIFT(207),    
        [ts_aux_sym_token9] = SHIFT(217),
    },
    
    [7] = {    
        [ts_sym_formal_parameters] = SHIFT(8),    
        [ts_sym_identifier] = SHIFT(178),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [8] = {    
        [ts_sym_statement_block] = SHIFT(9),    
        [ts_aux_sym_token3] = SHIFT(10),
    },
    
    [9] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [10] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(176),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [11] = {    
        [ts_sym_identifier] = SHIFT(12),
    },
    
    [12] = {    
        [ts_aux_sym_token5] = SHIFT(13),
    },
    
    [13] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_expression] = SHIFT(15),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(174),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [14] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [15] = {    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_assignment, 4),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [16] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(170),    
        [ts_sym_false] = SHIFT(63),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(76),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(63),    
        [ts_sym_number] = SHIFT(63),    
        [ts_sym_object] = SHIFT(63),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(63),    
        [ts_sym_true] = SHIFT(63),    
        [ts_aux_sym_token2] = SHIFT(173),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [17] = {    
        [ts_sym_formal_parameters] = SHIFT(18),    
        [ts_sym_identifier] = SHIFT(167),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [18] = {    
        [ts_sym_statement_block] = SHIFT(19),    
        [ts_aux_sym_token3] = SHIFT(20),
    },
    
    [19] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [20] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(165),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [21] = {    
        [ts_sym__terminator] = SHIFT(22),    
        [ts_aux_sym_token11] = SHIFT(23),    
        [ts_aux_sym_token12] = SHIFT(23),
    },
    
    [22] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__if] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 2),
    },
    
    [23] = {    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__if] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__var] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token3] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym__terminator, 1),
    },
    
    [24] = {    
        [ts_sym__terminator] = SHIFT(22),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(23),    
        [ts_aux_sym_token12] = SHIFT(23),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [25] = {    
        [ts_sym_identifier] = SHIFT(26),
    },
    
    [26] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [27] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [28] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    
    [29] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(30),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [30] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    
    [31] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(158),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(159),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(162),
    },
    
    [32] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = SHIFT(33),
    },
    
    [33] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(155),    
        [ts_sym_false] = SHIFT(80),    
        [ts_sym_function_call] = SHIFT(112),    
        [ts_sym_function_expression] = SHIFT(112),    
        [ts_sym_identifier] = SHIFT(112),    
        [ts_sym_literal] = SHIFT(112),    
        [ts_sym_null] = SHIFT(80),    
        [ts_sym_number] = SHIFT(80),    
        [ts_sym_object] = SHIFT(80),    
        [ts_sym_property_access] = SHIFT(112),    
        [ts_sym_string] = SHIFT(80),    
        [ts_sym_true] = SHIFT(80),    
        [ts_aux_sym_token3] = SHIFT(113),    
        [ts_aux_sym_token9] = SHIFT(119),
    },
    
    [34] = {    
        [ts_sym_formal_parameters] = SHIFT(35),    
        [ts_sym_identifier] = SHIFT(152),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [35] = {    
        [ts_sym_statement_block] = SHIFT(36),    
        [ts_aux_sym_token3] = SHIFT(37),
    },
    
    [36] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [37] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(38),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [38] = {    
        [ts_aux_sym_token4] = SHIFT(39),
    },
    
    [39] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [40] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(59),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(98),    
        [ts_sym_function_expression] = SHIFT(98),    
        [ts_sym_identifier] = SHIFT(98),    
        [ts_sym_literal] = SHIFT(98),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_property_access] = SHIFT(98),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(150),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(151),
    },
    
    [41] = {    
        [ts_sym_formal_parameters] = SHIFT(42),    
        [ts_sym_identifier] = SHIFT(47),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [42] = {    
        [ts_sym_statement_block] = SHIFT(43),    
        [ts_aux_sym_token3] = SHIFT(44),
    },
    
    [43] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [44] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(45),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [45] = {    
        [ts_aux_sym_token4] = SHIFT(46),
    },
    
    [46] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [47] = {    
        [ts_sym_formal_parameters] = SHIFT(48),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [48] = {    
        [ts_sym_statement_block] = SHIFT(49),    
        [ts_aux_sym_token3] = SHIFT(44),
    },
    
    [49] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [50] = {    
        [ts_sym_identifier] = SHIFT(51),    
        [ts_aux_sym_token2] = SHIFT(57),
    },
    
    [51] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(52),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token6] = SHIFT(54),
    },
    
    [52] = {    
        [ts_aux_sym_token2] = SHIFT(53),
    },
    
    [53] = {    
        [ts_aux_sym_token3] = REDUCE(ts_sym_formal_parameters, 4),
    },
    
    [54] = {    
        [ts_sym_identifier] = SHIFT(55),
    },
    
    [55] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(56),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token6] = SHIFT(54),
    },
    
    [56] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    
    [57] = {    
        [ts_aux_sym_token3] = REDUCE(ts_sym_formal_parameters, 2),
    },
    
    [58] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [59] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(60),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [60] = {    
        [ts_aux_sym_token10] = SHIFT(61),
    },
    
    [61] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [62] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(64),    
        [ts_sym_false] = SHIFT(63),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(76),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(63),    
        [ts_sym_number] = SHIFT(63),    
        [ts_sym_object] = SHIFT(63),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(63),    
        [ts_sym_true] = SHIFT(63),    
        [ts_aux_sym_token2] = SHIFT(149),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [63] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [64] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(65),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [65] = {    
        [ts_aux_sym_token2] = SHIFT(66),
    },
    
    [66] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [67] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(68),    
        [ts_sym_false] = SHIFT(63),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(76),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(63),    
        [ts_sym_number] = SHIFT(63),    
        [ts_sym_object] = SHIFT(63),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(63),    
        [ts_sym_true] = SHIFT(63),    
        [ts_aux_sym_token2] = SHIFT(148),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [68] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(69),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [69] = {    
        [ts_aux_sym_token2] = SHIFT(70),
    },
    
    [70] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [71] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(72),    
        [ts_sym_false] = SHIFT(63),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(76),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(63),    
        [ts_sym_number] = SHIFT(63),    
        [ts_sym_object] = SHIFT(63),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(63),    
        [ts_sym_true] = SHIFT(63),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [72] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(73),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [73] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 3),
    },
    
    [74] = {    
        [ts_sym_identifier] = SHIFT(75),
    },
    
    [75] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [76] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [77] = {    
        [ts_sym_identifier] = SHIFT(78),    
        [ts_sym_string] = SHIFT(78),    
        [ts_aux_sym_token4] = SHIFT(144),    
        [ts_builtin_sym_error] = SHIFT(145),
    },
    
    [78] = {    
        [ts_aux_sym_token8] = SHIFT(79),
    },
    
    [79] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(81),    
        [ts_sym_false] = SHIFT(80),    
        [ts_sym_function_call] = SHIFT(112),    
        [ts_sym_function_expression] = SHIFT(112),    
        [ts_sym_identifier] = SHIFT(112),    
        [ts_sym_literal] = SHIFT(112),    
        [ts_sym_null] = SHIFT(80),    
        [ts_sym_number] = SHIFT(80),    
        [ts_sym_object] = SHIFT(80),    
        [ts_sym_property_access] = SHIFT(112),    
        [ts_sym_string] = SHIFT(80),    
        [ts_sym_true] = SHIFT(80),    
        [ts_aux_sym_token3] = SHIFT(113),    
        [ts_aux_sym_token9] = SHIFT(119),
    },
    
    [80] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [81] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(82),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [82] = {    
        [ts_aux_sym_token4] = SHIFT(83),
    },
    
    [83] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [84] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(85),    
        [ts_sym_false] = SHIFT(63),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(76),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(63),    
        [ts_sym_number] = SHIFT(63),    
        [ts_sym_object] = SHIFT(63),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(63),    
        [ts_sym_true] = SHIFT(63),    
        [ts_aux_sym_token2] = SHIFT(88),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [85] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(86),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [86] = {    
        [ts_aux_sym_token2] = SHIFT(87),
    },
    
    [87] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [88] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [89] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(90),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(98),    
        [ts_sym_function_expression] = SHIFT(98),    
        [ts_sym_identifier] = SHIFT(98),    
        [ts_sym_literal] = SHIFT(98),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_property_access] = SHIFT(98),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(142),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(143),
    },
    
    [90] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(91),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [91] = {    
        [ts_aux_sym_token10] = SHIFT(92),
    },
    
    [92] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [93] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(94),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(98),    
        [ts_sym_function_expression] = SHIFT(98),    
        [ts_sym_identifier] = SHIFT(98),    
        [ts_sym_literal] = SHIFT(98),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_property_access] = SHIFT(98),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(141),
    },
    
    [94] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(95),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [95] = {    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    
    [96] = {    
        [ts_sym_identifier] = SHIFT(97),
    },
    
    [97] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [98] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [99] = {    
        [ts_sym_identifier] = SHIFT(100),    
        [ts_sym_string] = SHIFT(100),    
        [ts_aux_sym_token4] = SHIFT(137),    
        [ts_builtin_sym_error] = SHIFT(138),
    },
    
    [100] = {    
        [ts_aux_sym_token8] = SHIFT(101),
    },
    
    [101] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(102),    
        [ts_sym_false] = SHIFT(80),    
        [ts_sym_function_call] = SHIFT(112),    
        [ts_sym_function_expression] = SHIFT(112),    
        [ts_sym_identifier] = SHIFT(112),    
        [ts_sym_literal] = SHIFT(112),    
        [ts_sym_null] = SHIFT(80),    
        [ts_sym_number] = SHIFT(80),    
        [ts_sym_object] = SHIFT(80),    
        [ts_sym_property_access] = SHIFT(112),    
        [ts_sym_string] = SHIFT(80),    
        [ts_sym_true] = SHIFT(80),    
        [ts_aux_sym_token3] = SHIFT(113),    
        [ts_aux_sym_token9] = SHIFT(119),
    },
    
    [102] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(103),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [103] = {    
        [ts_aux_sym_token4] = SHIFT(104),
    },
    
    [104] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [105] = {    
        [ts_sym_identifier] = SHIFT(106),    
        [ts_sym_string] = SHIFT(106),    
        [ts_builtin_sym_error] = SHIFT(135),
    },
    
    [106] = {    
        [ts_aux_sym_token8] = SHIFT(107),
    },
    
    [107] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(108),    
        [ts_sym_false] = SHIFT(80),    
        [ts_sym_function_call] = SHIFT(112),    
        [ts_sym_function_expression] = SHIFT(112),    
        [ts_sym_identifier] = SHIFT(112),    
        [ts_sym_literal] = SHIFT(112),    
        [ts_sym_null] = SHIFT(80),    
        [ts_sym_number] = SHIFT(80),    
        [ts_sym_object] = SHIFT(80),    
        [ts_sym_property_access] = SHIFT(112),    
        [ts_sym_string] = SHIFT(80),    
        [ts_sym_true] = SHIFT(80),    
        [ts_aux_sym_token3] = SHIFT(113),    
        [ts_aux_sym_token9] = SHIFT(119),
    },
    
    [108] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(109),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [109] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 5),
    },
    
    [110] = {    
        [ts_sym_identifier] = SHIFT(111),
    },
    
    [111] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [112] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [113] = {    
        [ts_sym_identifier] = SHIFT(114),    
        [ts_sym_string] = SHIFT(114),    
        [ts_aux_sym_token4] = SHIFT(131),    
        [ts_builtin_sym_error] = SHIFT(132),
    },
    
    [114] = {    
        [ts_aux_sym_token8] = SHIFT(115),
    },
    
    [115] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(116),    
        [ts_sym_false] = SHIFT(80),    
        [ts_sym_function_call] = SHIFT(112),    
        [ts_sym_function_expression] = SHIFT(112),    
        [ts_sym_identifier] = SHIFT(112),    
        [ts_sym_literal] = SHIFT(112),    
        [ts_sym_null] = SHIFT(80),    
        [ts_sym_number] = SHIFT(80),    
        [ts_sym_object] = SHIFT(80),    
        [ts_sym_property_access] = SHIFT(112),    
        [ts_sym_string] = SHIFT(80),    
        [ts_sym_true] = SHIFT(80),    
        [ts_aux_sym_token3] = SHIFT(113),    
        [ts_aux_sym_token9] = SHIFT(119),
    },
    
    [116] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(117),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [117] = {    
        [ts_aux_sym_token4] = SHIFT(118),
    },
    
    [118] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [119] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(120),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(98),    
        [ts_sym_function_expression] = SHIFT(98),    
        [ts_sym_identifier] = SHIFT(98),    
        [ts_sym_literal] = SHIFT(98),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_property_access] = SHIFT(98),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(123),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(130),
    },
    
    [120] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(121),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [121] = {    
        [ts_aux_sym_token10] = SHIFT(122),
    },
    
    [122] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [123] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [124] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(125),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(98),    
        [ts_sym_function_expression] = SHIFT(98),    
        [ts_sym_identifier] = SHIFT(98),    
        [ts_sym_literal] = SHIFT(98),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_property_access] = SHIFT(98),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(128),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(129),
    },
    
    [125] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(126),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [126] = {    
        [ts_aux_sym_token10] = SHIFT(127),
    },
    
    [127] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [128] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [129] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(126),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [130] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(121),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [131] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [132] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(133),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [133] = {    
        [ts_aux_sym_token4] = SHIFT(134),
    },
    
    [134] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [135] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(136),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [136] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    
    [137] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [138] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(139),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [139] = {    
        [ts_aux_sym_token4] = SHIFT(140),
    },
    
    [140] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [141] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(95),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [142] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [143] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(91),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [144] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [145] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(146),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [146] = {    
        [ts_aux_sym_token4] = SHIFT(147),
    },
    
    [147] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [148] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [149] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [150] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [151] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(60),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [152] = {    
        [ts_sym_formal_parameters] = SHIFT(153),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [153] = {    
        [ts_sym_statement_block] = SHIFT(154),    
        [ts_aux_sym_token3] = SHIFT(37),
    },
    
    [154] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [155] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(156),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [156] = {    
        [ts_aux_sym_token4] = SHIFT(157),
    },
    
    [157] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [158] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token8] = SHIFT(33),
    },
    
    [159] = {    
        [ts_aux_sym_token4] = SHIFT(160),
    },
    
    [160] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [161] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [162] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(163),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [163] = {    
        [ts_aux_sym_token4] = SHIFT(164),
    },
    
    [164] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [165] = {    
        [ts_aux_sym_token4] = SHIFT(166),
    },
    
    [166] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [167] = {    
        [ts_sym_formal_parameters] = SHIFT(168),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [168] = {    
        [ts_sym_statement_block] = SHIFT(169),    
        [ts_aux_sym_token3] = SHIFT(20),
    },
    
    [169] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [170] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(171),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [171] = {    
        [ts_aux_sym_token2] = SHIFT(172),
    },
    
    [172] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [173] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [174] = {    
        [ts_sym_identifier] = SHIFT(175),    
        [ts_sym_string] = SHIFT(175),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_builtin_sym_error] = SHIFT(162),
    },
    
    [175] = {    
        [ts_aux_sym_token8] = SHIFT(33),
    },
    
    [176] = {    
        [ts_aux_sym_token4] = SHIFT(177),
    },
    
    [177] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [178] = {    
        [ts_sym_formal_parameters] = SHIFT(179),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [179] = {    
        [ts_sym_statement_block] = SHIFT(180),    
        [ts_aux_sym_token3] = SHIFT(10),
    },
    
    [180] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [181] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [182] = {    
        [ts_aux_sym_token1] = SHIFT(183),    
        [ts_aux_sym_token2] = SHIFT(188),    
        [ts_aux_sym_token7] = SHIFT(204),
    },
    
    [183] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(184),    
        [ts_sym_false] = SHIFT(63),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(76),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(63),    
        [ts_sym_number] = SHIFT(63),    
        [ts_sym_object] = SHIFT(63),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(63),    
        [ts_sym_true] = SHIFT(63),    
        [ts_aux_sym_token2] = SHIFT(187),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [184] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(185),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [185] = {    
        [ts_aux_sym_token2] = SHIFT(186),
    },
    
    [186] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [187] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [188] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(189),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(193),    
        [ts_sym_expression] = SHIFT(196),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(197),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(223),    
        [ts_sym_statement_block] = SHIFT(197),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(201),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [189] = {    
        [ts_aux_sym_token1] = SHIFT(190),
    },
    
    [190] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(181),    
        [ts_sym_expression] = SHIFT(191),    
        [ts_sym_false] = SHIFT(181),    
        [ts_sym_function_call] = SHIFT(206),    
        [ts_sym_function_expression] = SHIFT(206),    
        [ts_sym_identifier] = SHIFT(206),    
        [ts_sym_literal] = SHIFT(206),    
        [ts_sym_null] = SHIFT(181),    
        [ts_sym_number] = SHIFT(181),    
        [ts_sym_object] = SHIFT(181),    
        [ts_sym_property_access] = SHIFT(206),    
        [ts_sym_string] = SHIFT(181),    
        [ts_sym_true] = SHIFT(181),    
        [ts_aux_sym_token3] = SHIFT(207),    
        [ts_aux_sym_token9] = SHIFT(217),
    },
    
    [191] = {    
        [ts_aux_sym_token1] = SHIFT(183),    
        [ts_aux_sym_token2] = SHIFT(192),    
        [ts_aux_sym_token7] = SHIFT(204),
    },
    
    [192] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(189),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(193),    
        [ts_sym_expression] = SHIFT(196),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(197),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(198),    
        [ts_sym_statement_block] = SHIFT(197),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(201),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [193] = {    
        [ts_sym__terminator] = SHIFT(194),    
        [ts_aux_sym_token11] = SHIFT(195),    
        [ts_aux_sym_token12] = SHIFT(195),
    },
    
    [194] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 2),
    },
    
    [195] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym__terminator, 1),
    },
    
    [196] = {    
        [ts_sym__terminator] = SHIFT(194),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(195),    
        [ts_aux_sym_token12] = SHIFT(195),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [197] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    
    [198] = {    
        [ts_sym__else] = SHIFT(199),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [199] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(189),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(193),    
        [ts_sym_expression] = SHIFT(196),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(197),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(200),    
        [ts_sym_statement_block] = SHIFT(197),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(201),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [200] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    
    [201] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(158),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(202),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(162),
    },
    
    [202] = {    
        [ts_aux_sym_token4] = SHIFT(203),
    },
    
    [203] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [204] = {    
        [ts_sym_identifier] = SHIFT(205),
    },
    
    [205] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [206] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [207] = {    
        [ts_sym_identifier] = SHIFT(208),    
        [ts_sym_string] = SHIFT(208),    
        [ts_aux_sym_token4] = SHIFT(213),    
        [ts_builtin_sym_error] = SHIFT(214),
    },
    
    [208] = {    
        [ts_aux_sym_token8] = SHIFT(209),
    },
    
    [209] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(210),    
        [ts_sym_false] = SHIFT(80),    
        [ts_sym_function_call] = SHIFT(112),    
        [ts_sym_function_expression] = SHIFT(112),    
        [ts_sym_identifier] = SHIFT(112),    
        [ts_sym_literal] = SHIFT(112),    
        [ts_sym_null] = SHIFT(80),    
        [ts_sym_number] = SHIFT(80),    
        [ts_sym_object] = SHIFT(80),    
        [ts_sym_property_access] = SHIFT(112),    
        [ts_sym_string] = SHIFT(80),    
        [ts_sym_true] = SHIFT(80),    
        [ts_aux_sym_token3] = SHIFT(113),    
        [ts_aux_sym_token9] = SHIFT(119),
    },
    
    [210] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(211),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [211] = {    
        [ts_aux_sym_token4] = SHIFT(212),
    },
    
    [212] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [213] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [214] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(215),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [215] = {    
        [ts_aux_sym_token4] = SHIFT(216),
    },
    
    [216] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [217] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(218),    
        [ts_sym_false] = SHIFT(58),    
        [ts_sym_function_call] = SHIFT(98),    
        [ts_sym_function_expression] = SHIFT(98),    
        [ts_sym_identifier] = SHIFT(98),    
        [ts_sym_literal] = SHIFT(98),    
        [ts_sym_null] = SHIFT(58),    
        [ts_sym_number] = SHIFT(58),    
        [ts_sym_object] = SHIFT(58),    
        [ts_sym_property_access] = SHIFT(98),    
        [ts_sym_string] = SHIFT(58),    
        [ts_sym_true] = SHIFT(58),    
        [ts_aux_sym_token10] = SHIFT(221),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(222),
    },
    
    [218] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(219),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [219] = {    
        [ts_aux_sym_token10] = SHIFT(220),
    },
    
    [220] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [221] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [222] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(219),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [223] = {    
        [ts_sym__else] = SHIFT(224),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [224] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(225),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [225] = {    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    
    [226] = {    
        [ts_aux_sym_token4] = SHIFT(227),
    },
    
    [227] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [228] = {    
        [ts_sym_formal_parameters] = SHIFT(229),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [229] = {    
        [ts_sym_statement_block] = SHIFT(230),    
        [ts_aux_sym_token3] = SHIFT(4),
    },
    
    [230] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [231] = {    
        [ts_aux_sym_token1] = SHIFT(232),
    },
    
    [232] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(181),    
        [ts_sym_expression] = SHIFT(233),    
        [ts_sym_false] = SHIFT(181),    
        [ts_sym_function_call] = SHIFT(206),    
        [ts_sym_function_expression] = SHIFT(206),    
        [ts_sym_identifier] = SHIFT(206),    
        [ts_sym_literal] = SHIFT(206),    
        [ts_sym_null] = SHIFT(181),    
        [ts_sym_number] = SHIFT(181),    
        [ts_sym_object] = SHIFT(181),    
        [ts_sym_property_access] = SHIFT(206),    
        [ts_sym_string] = SHIFT(181),    
        [ts_sym_true] = SHIFT(181),    
        [ts_aux_sym_token3] = SHIFT(207),    
        [ts_aux_sym_token9] = SHIFT(217),
    },
    
    [233] = {    
        [ts_aux_sym_token1] = SHIFT(183),    
        [ts_aux_sym_token2] = SHIFT(234),    
        [ts_aux_sym_token7] = SHIFT(204),
    },
    
    [234] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(235),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(239),    
        [ts_sym_expression] = SHIFT(242),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(243),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(250),    
        [ts_sym_statement_block] = SHIFT(243),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(247),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [235] = {    
        [ts_aux_sym_token1] = SHIFT(236),
    },
    
    [236] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(181),    
        [ts_sym_expression] = SHIFT(237),    
        [ts_sym_false] = SHIFT(181),    
        [ts_sym_function_call] = SHIFT(206),    
        [ts_sym_function_expression] = SHIFT(206),    
        [ts_sym_identifier] = SHIFT(206),    
        [ts_sym_literal] = SHIFT(206),    
        [ts_sym_null] = SHIFT(181),    
        [ts_sym_number] = SHIFT(181),    
        [ts_sym_object] = SHIFT(181),    
        [ts_sym_property_access] = SHIFT(206),    
        [ts_sym_string] = SHIFT(181),    
        [ts_sym_true] = SHIFT(181),    
        [ts_aux_sym_token3] = SHIFT(207),    
        [ts_aux_sym_token9] = SHIFT(217),
    },
    
    [237] = {    
        [ts_aux_sym_token1] = SHIFT(183),    
        [ts_aux_sym_token2] = SHIFT(238),    
        [ts_aux_sym_token7] = SHIFT(204),
    },
    
    [238] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(235),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(239),    
        [ts_sym_expression] = SHIFT(242),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(243),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(244),    
        [ts_sym_statement_block] = SHIFT(243),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(247),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [239] = {    
        [ts_sym__terminator] = SHIFT(240),    
        [ts_aux_sym_token11] = SHIFT(241),    
        [ts_aux_sym_token12] = SHIFT(241),
    },
    
    [240] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 2),
    },
    
    [241] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym__terminator, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym__terminator, 1),
    },
    
    [242] = {    
        [ts_sym__terminator] = SHIFT(240),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(241),    
        [ts_aux_sym_token12] = SHIFT(241),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [243] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
    },
    
    [244] = {    
        [ts_sym__else] = SHIFT(245),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [245] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(235),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(239),    
        [ts_sym_expression] = SHIFT(242),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(243),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(246),    
        [ts_sym_statement_block] = SHIFT(243),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(247),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [246] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
    },
    
    [247] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(158),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(248),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(162),
    },
    
    [248] = {    
        [ts_aux_sym_token4] = SHIFT(249),
    },
    
    [249] = {    
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
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [250] = {    
        [ts_sym__else] = SHIFT(251),    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [251] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(231),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(252),    
        [ts_sym_expression] = SHIFT(255),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(256),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(257),    
        [ts_sym_statement_block] = SHIFT(256),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(258),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [252] = {    
        [ts_sym__terminator] = SHIFT(253),    
        [ts_aux_sym_token11] = SHIFT(254),    
        [ts_aux_sym_token12] = SHIFT(254),
    },
    
    [253] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__if] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 2),
    },
    
    [254] = {    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__if] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__var] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token3] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym__terminator, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym__terminator, 1),
    },
    
    [255] = {    
        [ts_sym__terminator] = SHIFT(253),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(254),    
        [ts_aux_sym_token12] = SHIFT(254),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [256] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
    },
    
    [257] = {    
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
    },
    
    [258] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(5),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(32),    
        [ts_sym_if_statement] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(29),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(158),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper2] = SHIFT(259),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(162),
    },
    
    [259] = {    
        [ts_aux_sym_token4] = SHIFT(260),
    },
    
    [260] = {    
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [261] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [262] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(231),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(252),    
        [ts_sym_expression] = SHIFT(255),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(256),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(262),    
        [ts_sym_statement_block] = SHIFT(256),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper1] = SHIFT(263),    
        [ts_aux_sym_token3] = SHIFT(258),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [263] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    
    [264] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
