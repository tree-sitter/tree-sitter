#include "tree_sitter/parser.h"

STATE_COUNT = 273;
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
    [ts_sym__else] = "_else",
    [ts_sym__function] = "_function",
    [ts_sym__if] = "_if",
    [ts_sym__terminator] = "_terminator",
    [ts_sym__var] = "_var",
    [ts_sym_array] = "array",
    [ts_sym_assignment] = "assignment",
    [ts_sym_expression] = "expression",
    [ts_sym_false] = "false",
    [ts_sym_formal_parameters] = "formal_parameters",
    [ts_sym_function_call] = "function_call",
    [ts_sym_function_expression] = "function_expression",
    [ts_sym_identifier] = "identifier",
    [ts_sym_if_statement] = "if_statement",
    [ts_sym_literal] = "literal",
    [ts_sym_null] = "null",
    [ts_sym_number] = "number",
    [ts_sym_object] = "object",
    [ts_sym_program] = "program",
    [ts_sym_property_access] = "property_access",
    [ts_sym_statement] = "statement",
    [ts_sym_statement_block] = "statement_block",
    [ts_sym_string] = "string",
    [ts_sym_true] = "true",
    [ts_aux_sym_repeat_helper1] = "repeat_helper1",
    [ts_aux_sym_repeat_helper2] = "repeat_helper2",
    [ts_aux_sym_repeat_helper3] = "repeat_helper3",
    [ts_aux_sym_repeat_helper4] = "repeat_helper4",
    [ts_aux_sym_repeat_helper5] = "repeat_helper5",
    [ts_aux_sym_repeat_helper6] = "repeat_helper6",
    [ts_aux_sym_token1] = "'('",
    [ts_aux_sym_token10] = "']'",
    [ts_aux_sym_token11] = "';'",
    [ts_aux_sym_token12] = "'\n'",
    [ts_aux_sym_token2] = "')'",
    [ts_aux_sym_token3] = "'{'",
    [ts_aux_sym_token4] = "'}'",
    [ts_aux_sym_token5] = "'='",
    [ts_aux_sym_token6] = "','",
    [ts_aux_sym_token7] = "'.'",
    [ts_aux_sym_token8] = "':'",
    [ts_aux_sym_token9] = "'['",
    [ts_builtin_sym_end] = "end",
    [ts_builtin_sym_error] = "error",
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
            if (lookahead == 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(63);
            if (lookahead == 'v')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(76);
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
            ACCEPT_TOKEN(ts_sym_false);
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
                ADVANCE(54);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__if);
        case 55:
            ACCEPT_TOKEN(ts_sym__if);
        case 56:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'u')
                ADVANCE(57);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 57:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'l')
                ADVANCE(58);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(61);
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
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 59:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_null);
        case 60:
            ACCEPT_TOKEN(ts_sym_null);
        case 61:
            if (lookahead == 'l')
                ADVANCE(60);
            LEX_ERROR();
        case 62:
            if (lookahead == 'l')
                ADVANCE(61);
            LEX_ERROR();
        case 63:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'r')
                ADVANCE(64);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 64:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'u')
                ADVANCE(65);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            if (lookahead == 'e')
                ADVANCE(66);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_true);
        case 67:
            ACCEPT_TOKEN(ts_sym_true);
        case 68:
            if (lookahead == 'e')
                ADVANCE(67);
            LEX_ERROR();
        case 69:
            if (lookahead == 'u')
                ADVANCE(68);
            LEX_ERROR();
        case 70:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
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
                ADVANCE(26);
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
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__var);
        case 73:
            ACCEPT_TOKEN(ts_sym__var);
        case 74:
            if (lookahead == 'r')
                ADVANCE(73);
            LEX_ERROR();
        case 75:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 77:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 78:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            LEX_ERROR();
        case 79:
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 80:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 81:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(82);
            LEX_ERROR();
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 83:
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 84:
            if (lookahead == ')')
                ADVANCE(6);
            LEX_ERROR();
        case 85:
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(8);
            LEX_ERROR();
        case 86:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == ')')
                ADVANCE(6);
            LEX_ERROR();
        case 87:
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 88:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 89:
            if (lookahead == ']')
                ADVANCE(82);
            LEX_ERROR();
        case 90:
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == ']')
                ADVANCE(82);
            LEX_ERROR();
        case 91:
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
                ADVANCE(82);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(63);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 92:
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
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(63);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 93:
            if (lookahead == ':')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 95:
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 96:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 97:
            if (lookahead == '\"')
                ADVANCE(15);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            LEX_ERROR();
        case 98:
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
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(63);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 99:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(94);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 100:
            if (lookahead == '=')
                ADVANCE(101);
            LEX_ERROR();
        case 101:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 102:
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
                ADVANCE(111);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(112);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(113);
            if (lookahead == 'n')
                ADVANCE(56);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(114);
            if (lookahead == 't')
                ADVANCE(63);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(115);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(116);
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 103:
            if (lookahead == 'l')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            if (lookahead == 's')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            if (lookahead == 'e')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(ts_sym__else);
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
                ADVANCE(104);
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
                ADVANCE(105);
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
                ADVANCE(106);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 110:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym__else);
        case 111:
            if (lookahead == 'a')
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(104);
            LEX_ERROR();
        case 112:
            if (lookahead == 'u')
                ADVANCE(51);
            LEX_ERROR();
        case 113:
            if (lookahead == 'f')
                ADVANCE(55);
            LEX_ERROR();
        case 114:
            if (lookahead == 'u')
                ADVANCE(62);
            LEX_ERROR();
        case 115:
            if (lookahead == 'r')
                ADVANCE(69);
            LEX_ERROR();
        case 116:
            if (lookahead == 'a')
                ADVANCE(74);
            LEX_ERROR();
        case 117:
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
            if (lookahead == 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(63);
            if (lookahead == 'v')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 118:
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
                ADVANCE(111);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(112);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(113);
            if (lookahead == 'n')
                ADVANCE(56);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(114);
            if (lookahead == 't')
                ADVANCE(63);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(115);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(116);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 119:
            LEX_ERROR();
        case 120:
            if (lookahead == 'l')
                ADVANCE(104);
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
                ADVANCE(94);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(82);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(120);
            if (lookahead == 'f')
                ADVANCE(33);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(10);
            if (lookahead == 'i')
                ADVANCE(53);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(113);
            if (lookahead == 'n')
                ADVANCE(56);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(114);
            if (lookahead == 't')
                ADVANCE(63);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(115);
            if (lookahead == 'v')
                ADVANCE(70);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(116);
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 117,
    [1] = 88,
    [2] = 83,
    [3] = 0,
    [4] = 9,
    [5] = 87,
    [6] = 92,
    [7] = 88,
    [8] = 83,
    [9] = 5,
    [10] = 9,
    [11] = 78,
    [12] = 100,
    [13] = 92,
    [14] = 0,
    [15] = 0,
    [16] = 98,
    [17] = 88,
    [18] = 83,
    [19] = 7,
    [20] = 9,
    [21] = 77,
    [22] = 9,
    [23] = 9,
    [24] = 0,
    [25] = 78,
    [26] = 0,
    [27] = 0,
    [28] = 9,
    [29] = 9,
    [30] = 79,
    [31] = 9,
    [32] = 99,
    [33] = 92,
    [34] = 88,
    [35] = 83,
    [36] = 80,
    [37] = 9,
    [38] = 79,
    [39] = 80,
    [40] = 91,
    [41] = 88,
    [42] = 83,
    [43] = 81,
    [44] = 9,
    [45] = 79,
    [46] = 81,
    [47] = 87,
    [48] = 83,
    [49] = 81,
    [50] = 86,
    [51] = 85,
    [52] = 84,
    [53] = 83,
    [54] = 78,
    [55] = 85,
    [56] = 84,
    [57] = 83,
    [58] = 81,
    [59] = 81,
    [60] = 89,
    [61] = 0,
    [62] = 98,
    [63] = 7,
    [64] = 7,
    [65] = 84,
    [66] = 81,
    [67] = 98,
    [68] = 7,
    [69] = 84,
    [70] = 7,
    [71] = 92,
    [72] = 7,
    [73] = 84,
    [74] = 78,
    [75] = 7,
    [76] = 7,
    [77] = 96,
    [78] = 93,
    [79] = 92,
    [80] = 80,
    [81] = 80,
    [82] = 79,
    [83] = 7,
    [84] = 98,
    [85] = 7,
    [86] = 84,
    [87] = 80,
    [88] = 80,
    [89] = 91,
    [90] = 81,
    [91] = 89,
    [92] = 7,
    [93] = 92,
    [94] = 81,
    [95] = 89,
    [96] = 78,
    [97] = 81,
    [98] = 81,
    [99] = 96,
    [100] = 93,
    [101] = 92,
    [102] = 80,
    [103] = 79,
    [104] = 81,
    [105] = 97,
    [106] = 93,
    [107] = 92,
    [108] = 80,
    [109] = 79,
    [110] = 78,
    [111] = 80,
    [112] = 80,
    [113] = 96,
    [114] = 93,
    [115] = 92,
    [116] = 80,
    [117] = 79,
    [118] = 80,
    [119] = 91,
    [120] = 81,
    [121] = 89,
    [122] = 80,
    [123] = 80,
    [124] = 91,
    [125] = 81,
    [126] = 89,
    [127] = 81,
    [128] = 81,
    [129] = 90,
    [130] = 90,
    [131] = 80,
    [132] = 95,
    [133] = 79,
    [134] = 80,
    [135] = 95,
    [136] = 79,
    [137] = 81,
    [138] = 95,
    [139] = 79,
    [140] = 81,
    [141] = 90,
    [142] = 7,
    [143] = 90,
    [144] = 7,
    [145] = 95,
    [146] = 79,
    [147] = 7,
    [148] = 7,
    [149] = 81,
    [150] = 0,
    [151] = 90,
    [152] = 87,
    [153] = 83,
    [154] = 80,
    [155] = 80,
    [156] = 79,
    [157] = 0,
    [158] = 99,
    [159] = 79,
    [160] = 9,
    [161] = 0,
    [162] = 95,
    [163] = 79,
    [164] = 0,
    [165] = 79,
    [166] = 7,
    [167] = 87,
    [168] = 83,
    [169] = 7,
    [170] = 7,
    [171] = 84,
    [172] = 0,
    [173] = 0,
    [174] = 96,
    [175] = 93,
    [176] = 95,
    [177] = 79,
    [178] = 5,
    [179] = 87,
    [180] = 83,
    [181] = 5,
    [182] = 5,
    [183] = 5,
    [184] = 98,
    [185] = 7,
    [186] = 84,
    [187] = 5,
    [188] = 5,
    [189] = 117,
    [190] = 87,
    [191] = 92,
    [192] = 5,
    [193] = 117,
    [194] = 77,
    [195] = 102,
    [196] = 102,
    [197] = 0,
    [198] = 102,
    [199] = 102,
    [200] = 117,
    [201] = 102,
    [202] = 9,
    [203] = 79,
    [204] = 102,
    [205] = 95,
    [206] = 78,
    [207] = 5,
    [208] = 5,
    [209] = 96,
    [210] = 93,
    [211] = 92,
    [212] = 80,
    [213] = 79,
    [214] = 5,
    [215] = 5,
    [216] = 95,
    [217] = 79,
    [218] = 5,
    [219] = 91,
    [220] = 81,
    [221] = 89,
    [222] = 5,
    [223] = 5,
    [224] = 90,
    [225] = 84,
    [226] = 102,
    [227] = 117,
    [228] = 9,
    [229] = 84,
    [230] = 79,
    [231] = 0,
    [232] = 87,
    [233] = 83,
    [234] = 0,
    [235] = 87,
    [236] = 92,
    [237] = 5,
    [238] = 117,
    [239] = 87,
    [240] = 92,
    [241] = 5,
    [242] = 117,
    [243] = 77,
    [244] = 118,
    [245] = 118,
    [246] = 0,
    [247] = 118,
    [248] = 118,
    [249] = 117,
    [250] = 118,
    [251] = 9,
    [252] = 79,
    [253] = 118,
    [254] = 95,
    [255] = 84,
    [256] = 118,
    [257] = 117,
    [258] = 77,
    [259] = 117,
    [260] = 117,
    [261] = 0,
    [262] = 117,
    [263] = 117,
    [264] = 9,
    [265] = 79,
    [266] = 117,
    [267] = 95,
    [268] = 84,
    [269] = 119,
    [270] = 117,
    [271] = 119,
    [272] = 119,
};

PARSE_TABLE = {
    [0] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(235),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(258),    
        [ts_sym_expression] = SHIFT(261),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(262),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_program] = SHIFT(269),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(270),    
        [ts_sym_statement_block] = SHIFT(262),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper1] = SHIFT(272),    
        [ts_aux_sym_token3] = SHIFT(264),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [1] = {    
        [ts_sym_formal_parameters] = SHIFT(2),    
        [ts_sym_identifier] = SHIFT(232),    
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
        [ts_aux_sym_repeat_helper2] = SHIFT(230),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(230),
    },
    
    [5] = {    
        [ts_aux_sym_token1] = SHIFT(6),
    },
    
    [6] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(182),    
        [ts_sym_expression] = SHIFT(183),    
        [ts_sym_false] = SHIFT(182),    
        [ts_sym_function_call] = SHIFT(208),    
        [ts_sym_function_expression] = SHIFT(208),    
        [ts_sym_identifier] = SHIFT(208),    
        [ts_sym_literal] = SHIFT(208),    
        [ts_sym_null] = SHIFT(182),    
        [ts_sym_number] = SHIFT(182),    
        [ts_sym_object] = SHIFT(182),    
        [ts_sym_property_access] = SHIFT(208),    
        [ts_sym_string] = SHIFT(182),    
        [ts_sym_true] = SHIFT(182),    
        [ts_aux_sym_token3] = SHIFT(209),    
        [ts_aux_sym_token9] = SHIFT(219),    
        [ts_builtin_sym_error] = SHIFT(229),
    },
    
    [7] = {    
        [ts_sym_formal_parameters] = SHIFT(8),    
        [ts_sym_identifier] = SHIFT(179),    
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
        [ts_aux_sym_repeat_helper2] = SHIFT(177),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(177),
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
        [ts_builtin_sym_error] = SHIFT(165),
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
        [ts_builtin_sym_error] = SHIFT(38),
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
        [ts_builtin_sym_error] = SHIFT(45),
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
        [ts_aux_sym_token4] = SHIFT(160),    
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
        [ts_builtin_sym_error] = SHIFT(176),
    },
    
    [175] = {    
        [ts_aux_sym_token8] = SHIFT(33),
    },
    
    [176] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(163),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [177] = {    
        [ts_aux_sym_token4] = SHIFT(178),
    },
    
    [178] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [179] = {    
        [ts_sym_formal_parameters] = SHIFT(180),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [180] = {    
        [ts_sym_statement_block] = SHIFT(181),    
        [ts_aux_sym_token3] = SHIFT(10),
    },
    
    [181] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [182] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [183] = {    
        [ts_aux_sym_token1] = SHIFT(184),    
        [ts_aux_sym_token2] = SHIFT(189),    
        [ts_aux_sym_token7] = SHIFT(206),
    },
    
    [184] = {    
        [ts_sym__function] = SHIFT(17),    
        [ts_sym_array] = SHIFT(63),    
        [ts_sym_expression] = SHIFT(185),    
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
        [ts_aux_sym_token2] = SHIFT(188),    
        [ts_aux_sym_token3] = SHIFT(77),    
        [ts_aux_sym_token9] = SHIFT(89),
    },
    
    [185] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(186),    
        [ts_aux_sym_token1] = SHIFT(67),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(71),    
        [ts_aux_sym_token7] = SHIFT(74),
    },
    
    [186] = {    
        [ts_aux_sym_token2] = SHIFT(187),
    },
    
    [187] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [188] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [189] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(190),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(194),    
        [ts_sym_expression] = SHIFT(197),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(198),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(226),    
        [ts_sym_statement_block] = SHIFT(198),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(202),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [190] = {    
        [ts_aux_sym_token1] = SHIFT(191),
    },
    
    [191] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(182),    
        [ts_sym_expression] = SHIFT(192),    
        [ts_sym_false] = SHIFT(182),    
        [ts_sym_function_call] = SHIFT(208),    
        [ts_sym_function_expression] = SHIFT(208),    
        [ts_sym_identifier] = SHIFT(208),    
        [ts_sym_literal] = SHIFT(208),    
        [ts_sym_null] = SHIFT(182),    
        [ts_sym_number] = SHIFT(182),    
        [ts_sym_object] = SHIFT(182),    
        [ts_sym_property_access] = SHIFT(208),    
        [ts_sym_string] = SHIFT(182),    
        [ts_sym_true] = SHIFT(182),    
        [ts_aux_sym_token3] = SHIFT(209),    
        [ts_aux_sym_token9] = SHIFT(219),    
        [ts_builtin_sym_error] = SHIFT(225),
    },
    
    [192] = {    
        [ts_aux_sym_token1] = SHIFT(184),    
        [ts_aux_sym_token2] = SHIFT(193),    
        [ts_aux_sym_token7] = SHIFT(206),
    },
    
    [193] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(190),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(194),    
        [ts_sym_expression] = SHIFT(197),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(198),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(199),    
        [ts_sym_statement_block] = SHIFT(198),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(202),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [194] = {    
        [ts_sym__terminator] = SHIFT(195),    
        [ts_aux_sym_token11] = SHIFT(196),    
        [ts_aux_sym_token12] = SHIFT(196),
    },
    
    [195] = {    
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
    
    [196] = {    
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
    
    [197] = {    
        [ts_sym__terminator] = SHIFT(195),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(196),    
        [ts_aux_sym_token12] = SHIFT(196),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [198] = {    
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
    
    [199] = {    
        [ts_sym__else] = SHIFT(200),    
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
    
    [200] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(190),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(194),    
        [ts_sym_expression] = SHIFT(197),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(198),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(201),    
        [ts_sym_statement_block] = SHIFT(198),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(202),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [201] = {    
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
    
    [202] = {    
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
        [ts_aux_sym_repeat_helper2] = SHIFT(203),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(205),
    },
    
    [203] = {    
        [ts_aux_sym_token4] = SHIFT(204),
    },
    
    [204] = {    
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
    
    [205] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(163),    
        [ts_aux_sym_token4] = SHIFT(204),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [206] = {    
        [ts_sym_identifier] = SHIFT(207),
    },
    
    [207] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [208] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [209] = {    
        [ts_sym_identifier] = SHIFT(210),    
        [ts_sym_string] = SHIFT(210),    
        [ts_aux_sym_token4] = SHIFT(215),    
        [ts_builtin_sym_error] = SHIFT(216),
    },
    
    [210] = {    
        [ts_aux_sym_token8] = SHIFT(211),
    },
    
    [211] = {    
        [ts_sym__function] = SHIFT(34),    
        [ts_sym_array] = SHIFT(80),    
        [ts_sym_expression] = SHIFT(212),    
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
    
    [212] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(213),    
        [ts_aux_sym_token1] = SHIFT(84),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),    
        [ts_aux_sym_token7] = SHIFT(110),
    },
    
    [213] = {    
        [ts_aux_sym_token4] = SHIFT(214),
    },
    
    [214] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [215] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [216] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(217),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [217] = {    
        [ts_aux_sym_token4] = SHIFT(218),
    },
    
    [218] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [219] = {    
        [ts_sym__function] = SHIFT(41),    
        [ts_sym_array] = SHIFT(58),    
        [ts_sym_expression] = SHIFT(220),    
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
        [ts_aux_sym_token10] = SHIFT(223),    
        [ts_aux_sym_token3] = SHIFT(99),    
        [ts_aux_sym_token9] = SHIFT(124),    
        [ts_builtin_sym_error] = SHIFT(224),
    },
    
    [220] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(221),    
        [ts_aux_sym_token1] = SHIFT(62),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),    
        [ts_aux_sym_token7] = SHIFT(96),
    },
    
    [221] = {    
        [ts_aux_sym_token10] = SHIFT(222),
    },
    
    [222] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [223] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [224] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(221),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(93),
    },
    
    [225] = {    
        [ts_aux_sym_token2] = SHIFT(193),
    },
    
    [226] = {    
        [ts_sym__else] = SHIFT(227),    
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
    
    [227] = {    
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
        [ts_sym_statement] = SHIFT(228),    
        [ts_sym_statement_block] = SHIFT(28),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [228] = {    
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
    
    [229] = {    
        [ts_aux_sym_token2] = SHIFT(189),
    },
    
    [230] = {    
        [ts_aux_sym_token4] = SHIFT(231),
    },
    
    [231] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [232] = {    
        [ts_sym_formal_parameters] = SHIFT(233),    
        [ts_aux_sym_token1] = SHIFT(50),
    },
    
    [233] = {    
        [ts_sym_statement_block] = SHIFT(234),    
        [ts_aux_sym_token3] = SHIFT(4),
    },
    
    [234] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [235] = {    
        [ts_aux_sym_token1] = SHIFT(236),
    },
    
    [236] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(182),    
        [ts_sym_expression] = SHIFT(237),    
        [ts_sym_false] = SHIFT(182),    
        [ts_sym_function_call] = SHIFT(208),    
        [ts_sym_function_expression] = SHIFT(208),    
        [ts_sym_identifier] = SHIFT(208),    
        [ts_sym_literal] = SHIFT(208),    
        [ts_sym_null] = SHIFT(182),    
        [ts_sym_number] = SHIFT(182),    
        [ts_sym_object] = SHIFT(182),    
        [ts_sym_property_access] = SHIFT(208),    
        [ts_sym_string] = SHIFT(182),    
        [ts_sym_true] = SHIFT(182),    
        [ts_aux_sym_token3] = SHIFT(209),    
        [ts_aux_sym_token9] = SHIFT(219),    
        [ts_builtin_sym_error] = SHIFT(268),
    },
    
    [237] = {    
        [ts_aux_sym_token1] = SHIFT(184),    
        [ts_aux_sym_token2] = SHIFT(238),    
        [ts_aux_sym_token7] = SHIFT(206),
    },
    
    [238] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(239),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(243),    
        [ts_sym_expression] = SHIFT(246),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(247),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(256),    
        [ts_sym_statement_block] = SHIFT(247),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(251),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [239] = {    
        [ts_aux_sym_token1] = SHIFT(240),
    },
    
    [240] = {    
        [ts_sym__function] = SHIFT(7),    
        [ts_sym_array] = SHIFT(182),    
        [ts_sym_expression] = SHIFT(241),    
        [ts_sym_false] = SHIFT(182),    
        [ts_sym_function_call] = SHIFT(208),    
        [ts_sym_function_expression] = SHIFT(208),    
        [ts_sym_identifier] = SHIFT(208),    
        [ts_sym_literal] = SHIFT(208),    
        [ts_sym_null] = SHIFT(182),    
        [ts_sym_number] = SHIFT(182),    
        [ts_sym_object] = SHIFT(182),    
        [ts_sym_property_access] = SHIFT(208),    
        [ts_sym_string] = SHIFT(182),    
        [ts_sym_true] = SHIFT(182),    
        [ts_aux_sym_token3] = SHIFT(209),    
        [ts_aux_sym_token9] = SHIFT(219),    
        [ts_builtin_sym_error] = SHIFT(255),
    },
    
    [241] = {    
        [ts_aux_sym_token1] = SHIFT(184),    
        [ts_aux_sym_token2] = SHIFT(242),    
        [ts_aux_sym_token7] = SHIFT(206),
    },
    
    [242] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(239),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(243),    
        [ts_sym_expression] = SHIFT(246),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(247),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(248),    
        [ts_sym_statement_block] = SHIFT(247),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(251),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [243] = {    
        [ts_sym__terminator] = SHIFT(244),    
        [ts_aux_sym_token11] = SHIFT(245),    
        [ts_aux_sym_token12] = SHIFT(245),
    },
    
    [244] = {    
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
    
    [245] = {    
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
    
    [246] = {    
        [ts_sym__terminator] = SHIFT(244),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(245),    
        [ts_aux_sym_token12] = SHIFT(245),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [247] = {    
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
    
    [248] = {    
        [ts_sym__else] = SHIFT(249),    
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
    
    [249] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(239),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(243),    
        [ts_sym_expression] = SHIFT(246),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(247),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(250),    
        [ts_sym_statement_block] = SHIFT(247),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(251),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [250] = {    
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
    
    [251] = {    
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
        [ts_aux_sym_repeat_helper2] = SHIFT(252),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(254),
    },
    
    [252] = {    
        [ts_aux_sym_token4] = SHIFT(253),
    },
    
    [253] = {    
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
    
    [254] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(163),    
        [ts_aux_sym_token4] = SHIFT(253),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [255] = {    
        [ts_aux_sym_token2] = SHIFT(242),
    },
    
    [256] = {    
        [ts_sym__else] = SHIFT(257),    
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
    
    [257] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(235),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(258),    
        [ts_sym_expression] = SHIFT(261),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(262),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(263),    
        [ts_sym_statement_block] = SHIFT(262),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_token3] = SHIFT(264),    
        [ts_aux_sym_token9] = SHIFT(40),
    },
    
    [258] = {    
        [ts_sym__terminator] = SHIFT(259),    
        [ts_aux_sym_token11] = SHIFT(260),    
        [ts_aux_sym_token12] = SHIFT(260),
    },
    
    [259] = {    
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
    
    [260] = {    
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
    
    [261] = {    
        [ts_sym__terminator] = SHIFT(259),    
        [ts_aux_sym_token1] = SHIFT(16),    
        [ts_aux_sym_token11] = SHIFT(260),    
        [ts_aux_sym_token12] = SHIFT(260),    
        [ts_aux_sym_token7] = SHIFT(25),
    },
    
    [262] = {    
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
    
    [263] = {    
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
    
    [264] = {    
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
        [ts_aux_sym_repeat_helper2] = SHIFT(265),    
        [ts_aux_sym_token3] = SHIFT(31),    
        [ts_aux_sym_token4] = SHIFT(161),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_error] = SHIFT(267),
    },
    
    [265] = {    
        [ts_aux_sym_token4] = SHIFT(266),
    },
    
    [266] = {    
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
    
    [267] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(163),    
        [ts_aux_sym_token4] = SHIFT(266),    
        [ts_aux_sym_token6] = SHIFT(105),
    },
    
    [268] = {    
        [ts_aux_sym_token2] = SHIFT(238),
    },
    
    [269] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [270] = {    
        [ts_sym__function] = SHIFT(1),    
        [ts_sym__if] = SHIFT(235),    
        [ts_sym__var] = SHIFT(11),    
        [ts_sym_array] = SHIFT(14),    
        [ts_sym_assignment] = SHIFT(258),    
        [ts_sym_expression] = SHIFT(261),    
        [ts_sym_false] = SHIFT(14),    
        [ts_sym_function_call] = SHIFT(27),    
        [ts_sym_function_expression] = SHIFT(27),    
        [ts_sym_identifier] = SHIFT(27),    
        [ts_sym_if_statement] = SHIFT(262),    
        [ts_sym_literal] = SHIFT(27),    
        [ts_sym_null] = SHIFT(14),    
        [ts_sym_number] = SHIFT(14),    
        [ts_sym_object] = SHIFT(14),    
        [ts_sym_property_access] = SHIFT(27),    
        [ts_sym_statement] = SHIFT(270),    
        [ts_sym_statement_block] = SHIFT(262),    
        [ts_sym_string] = SHIFT(14),    
        [ts_sym_true] = SHIFT(14),    
        [ts_aux_sym_repeat_helper1] = SHIFT(271),    
        [ts_aux_sym_token3] = SHIFT(264),    
        [ts_aux_sym_token9] = SHIFT(40),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [271] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    
    [272] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
