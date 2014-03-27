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
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(54);
            if (lookahead == 'i')
                ADVANCE(55);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(58);
            if (lookahead == 'n')
                ADVANCE(59);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(66);
            if (lookahead == 't')
                ADVANCE(67);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(74);
            if (lookahead == 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(78);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 10:
            if (lookahead == 'a')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'r')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_sym__var);
        case 13:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(14);
            if (lookahead == '\\')
                ADVANCE(20);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(22);
            LEX_ERROR();
        case 14:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\"')
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(17);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(19);
            LEX_ERROR();
        case 15:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\"')
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(17);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(19);
            LEX_ERROR();
        case 16:
            ACCEPT_TOKEN(ts_sym_string);
        case 17:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\"')
                ADVANCE(18);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(15);
            if (lookahead == '\\')
                ADVANCE(17);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(19);
            LEX_ERROR();
        case 18:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\"')
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(17);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_string);
        case 19:
            if (lookahead == '\"')
                ADVANCE(15);
            LEX_ERROR();
        case 20:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\"')
                ADVANCE(21);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(14);
            if (lookahead == '\\')
                ADVANCE(17);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(19);
            LEX_ERROR();
        case 21:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\"')
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(17);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_string);
        case 22:
            if (lookahead == '\"')
                ADVANCE(14);
            LEX_ERROR();
        case 23:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 24:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 25:
            if (lookahead == '.')
                ADVANCE(26);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_number);
        case 26:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_number);
        case 28:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_number);
        case 29:
            if (lookahead == '.')
                ADVANCE(26);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_number);
        case 30:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 31:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'a')
                ADVANCE(39);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(46);
            if (lookahead == 'u')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if (lookahead == 'n')
                ADVANCE(33);
            LEX_ERROR();
        case 33:
            if (lookahead == 'c')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            if (lookahead == 't')
                ADVANCE(35);
            LEX_ERROR();
        case 35:
            if (lookahead == 'i')
                ADVANCE(36);
            LEX_ERROR();
        case 36:
            if (lookahead == 'o')
                ADVANCE(37);
            LEX_ERROR();
        case 37:
            if (lookahead == 'n')
                ADVANCE(38);
            LEX_ERROR();
        case 38:
            ACCEPT_TOKEN(ts_sym__function);
        case 39:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'l')
                ADVANCE(40);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(41);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'e')
                ADVANCE(42);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_false);
        case 43:
            ACCEPT_TOKEN(ts_sym_false);
        case 44:
            if (lookahead == 'e')
                ADVANCE(43);
            LEX_ERROR();
        case 45:
            if (lookahead == 's')
                ADVANCE(44);
            LEX_ERROR();
        case 46:
            if (lookahead == 'l')
                ADVANCE(45);
            LEX_ERROR();
        case 47:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'n')
                ADVANCE(48);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'c')
                ADVANCE(49);
            if ('d' <= lookahead && lookahead <= 'c')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 't')
                ADVANCE(50);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 50:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'i')
                ADVANCE(51);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'o')
                ADVANCE(52);
            if ('p' <= lookahead && lookahead <= 'o')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 52:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'n')
                ADVANCE(53);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 53:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym__function);
        case 54:
            if (lookahead == 'a')
                ADVANCE(46);
            LEX_ERROR();
        case 55:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(56);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 56:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym__if);
        case 57:
            ACCEPT_TOKEN(ts_sym__if);
        case 58:
            if (lookahead == 'f')
                ADVANCE(57);
            LEX_ERROR();
        case 59:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'u')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 60:
            if (lookahead == 'l')
                ADVANCE(61);
            LEX_ERROR();
        case 61:
            if (lookahead == 'l')
                ADVANCE(62);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_sym_null);
        case 63:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'l')
                ADVANCE(64);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 64:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'l')
                ADVANCE(65);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_null);
        case 66:
            if (lookahead == 'u')
                ADVANCE(60);
            LEX_ERROR();
        case 67:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'r')
                ADVANCE(68);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 68:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'u')
                ADVANCE(69);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(72);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 69:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'e')
                ADVANCE(70);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 70:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_true);
        case 71:
            ACCEPT_TOKEN(ts_sym_true);
        case 72:
            if (lookahead == 'e')
                ADVANCE(71);
            LEX_ERROR();
        case 73:
            if (lookahead == 'u')
                ADVANCE(72);
            LEX_ERROR();
        case 74:
            if (lookahead == 'r')
                ADVANCE(73);
            LEX_ERROR();
        case 75:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'a')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 76:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'r')
                ADVANCE(77);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 77:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym__var);
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 79:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 80:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 81:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            LEX_ERROR();
        case 82:
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 83:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 84:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(85);
            LEX_ERROR();
        case 85:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 86:
            if (lookahead == '{')
                ADVANCE(78);
            LEX_ERROR();
        case 87:
            if (lookahead == ')')
                ADVANCE(6);
            LEX_ERROR();
        case 88:
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(8);
            LEX_ERROR();
        case 89:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if (lookahead == ')')
                ADVANCE(6);
            LEX_ERROR();
        case 90:
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 91:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 92:
            if (lookahead == ']')
                ADVANCE(85);
            LEX_ERROR();
        case 93:
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == ']')
                ADVANCE(85);
            LEX_ERROR();
        case 94:
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == ']')
                ADVANCE(85);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(95);
            if (lookahead == 'n')
                ADVANCE(59);
            if (lookahead == 't')
                ADVANCE(67);
            if (lookahead == '{')
                ADVANCE(78);
            LEX_ERROR();
        case 95:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == 'a')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 96:
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(95);
            if (lookahead == 'n')
                ADVANCE(59);
            if (lookahead == 't')
                ADVANCE(67);
            if (lookahead == '{')
                ADVANCE(78);
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
                ADVANCE(79);
            LEX_ERROR();
        case 100:
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 101:
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            LEX_ERROR();
        case 102:
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if (lookahead == ')')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(95);
            if (lookahead == 'n')
                ADVANCE(59);
            if (lookahead == 't')
                ADVANCE(67);
            if (lookahead == '{')
                ADVANCE(78);
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
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(114);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(54);
            if (lookahead == 'i')
                ADVANCE(55);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(58);
            if (lookahead == 'n')
                ADVANCE(59);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(66);
            if (lookahead == 't')
                ADVANCE(67);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(74);
            if (lookahead == 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(78);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 107:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
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
                ADVANCE(24);
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
                ADVANCE(24);
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
                ADVANCE(24);
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
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(54);
            if (lookahead == 'i')
                ADVANCE(55);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(58);
            if (lookahead == 'n')
                ADVANCE(59);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(66);
            if (lookahead == 't')
                ADVANCE(67);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(74);
            if (lookahead == 'v')
                ADVANCE(75);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(10);
            if (lookahead == '{')
                ADVANCE(78);
            LEX_ERROR();
        case 116:
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(114);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(54);
            if (lookahead == 'i')
                ADVANCE(55);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(58);
            if (lookahead == 'n')
                ADVANCE(59);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(66);
            if (lookahead == 't')
                ADVANCE(67);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(74);
            if (lookahead == 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(78);
            LEX_ERROR();
        case 117:
            LEX_ERROR();
        case 118:
            if (lookahead == 'u')
                ADVANCE(32);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(13);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(23);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(6);
            if (lookahead == ',')
                ADVANCE(8);
            if (lookahead == '.')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            if (lookahead == ':')
                ADVANCE(98);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(105);
            if (lookahead == '[')
                ADVANCE(30);
            if (lookahead == ']')
                ADVANCE(85);
            if (lookahead == 'e')
                ADVANCE(107);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(114);
            if (lookahead == 'f')
                ADVANCE(31);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(118);
            if (lookahead == 'i')
                ADVANCE(55);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(58);
            if (lookahead == 'n')
                ADVANCE(59);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(66);
            if (lookahead == 't')
                ADVANCE(67);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(74);
            if (lookahead == 'v')
                ADVANCE(75);
            if (lookahead == '{')
                ADVANCE(78);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 115,
    [1] = 91,
    [2] = 86,
    [3] = 0,
    [4] = 9,
    [5] = 90,
    [6] = 96,
    [7] = 91,
    [8] = 86,
    [9] = 5,
    [10] = 9,
    [11] = 81,
    [12] = 104,
    [13] = 96,
    [14] = 0,
    [15] = 0,
    [16] = 102,
    [17] = 91,
    [18] = 86,
    [19] = 7,
    [20] = 9,
    [21] = 80,
    [22] = 9,
    [23] = 9,
    [24] = 0,
    [25] = 81,
    [26] = 0,
    [27] = 0,
    [28] = 9,
    [29] = 9,
    [30] = 82,
    [31] = 9,
    [32] = 103,
    [33] = 96,
    [34] = 91,
    [35] = 86,
    [36] = 83,
    [37] = 9,
    [38] = 82,
    [39] = 83,
    [40] = 94,
    [41] = 91,
    [42] = 86,
    [43] = 84,
    [44] = 9,
    [45] = 82,
    [46] = 84,
    [47] = 90,
    [48] = 86,
    [49] = 84,
    [50] = 89,
    [51] = 88,
    [52] = 87,
    [53] = 86,
    [54] = 81,
    [55] = 88,
    [56] = 87,
    [57] = 86,
    [58] = 84,
    [59] = 84,
    [60] = 92,
    [61] = 0,
    [62] = 102,
    [63] = 7,
    [64] = 7,
    [65] = 87,
    [66] = 84,
    [67] = 102,
    [68] = 7,
    [69] = 87,
    [70] = 7,
    [71] = 96,
    [72] = 7,
    [73] = 87,
    [74] = 81,
    [75] = 7,
    [76] = 7,
    [77] = 100,
    [78] = 97,
    [79] = 96,
    [80] = 83,
    [81] = 83,
    [82] = 82,
    [83] = 7,
    [84] = 102,
    [85] = 7,
    [86] = 87,
    [87] = 83,
    [88] = 83,
    [89] = 94,
    [90] = 84,
    [91] = 92,
    [92] = 7,
    [93] = 96,
    [94] = 84,
    [95] = 92,
    [96] = 81,
    [97] = 84,
    [98] = 84,
    [99] = 100,
    [100] = 97,
    [101] = 96,
    [102] = 83,
    [103] = 82,
    [104] = 84,
    [105] = 101,
    [106] = 97,
    [107] = 96,
    [108] = 83,
    [109] = 82,
    [110] = 81,
    [111] = 83,
    [112] = 83,
    [113] = 100,
    [114] = 97,
    [115] = 96,
    [116] = 83,
    [117] = 82,
    [118] = 83,
    [119] = 94,
    [120] = 84,
    [121] = 92,
    [122] = 83,
    [123] = 83,
    [124] = 94,
    [125] = 84,
    [126] = 92,
    [127] = 84,
    [128] = 84,
    [129] = 93,
    [130] = 93,
    [131] = 83,
    [132] = 99,
    [133] = 82,
    [134] = 83,
    [135] = 99,
    [136] = 82,
    [137] = 84,
    [138] = 99,
    [139] = 82,
    [140] = 84,
    [141] = 93,
    [142] = 7,
    [143] = 93,
    [144] = 7,
    [145] = 99,
    [146] = 82,
    [147] = 7,
    [148] = 7,
    [149] = 84,
    [150] = 0,
    [151] = 93,
    [152] = 90,
    [153] = 86,
    [154] = 83,
    [155] = 83,
    [156] = 82,
    [157] = 0,
    [158] = 103,
    [159] = 82,
    [160] = 9,
    [161] = 0,
    [162] = 99,
    [163] = 82,
    [164] = 0,
    [165] = 82,
    [166] = 7,
    [167] = 90,
    [168] = 86,
    [169] = 7,
    [170] = 7,
    [171] = 87,
    [172] = 0,
    [173] = 0,
    [174] = 100,
    [175] = 97,
    [176] = 99,
    [177] = 82,
    [178] = 5,
    [179] = 90,
    [180] = 86,
    [181] = 5,
    [182] = 5,
    [183] = 5,
    [184] = 102,
    [185] = 7,
    [186] = 87,
    [187] = 5,
    [188] = 5,
    [189] = 115,
    [190] = 90,
    [191] = 96,
    [192] = 5,
    [193] = 115,
    [194] = 80,
    [195] = 106,
    [196] = 106,
    [197] = 0,
    [198] = 106,
    [199] = 106,
    [200] = 115,
    [201] = 106,
    [202] = 9,
    [203] = 82,
    [204] = 106,
    [205] = 99,
    [206] = 81,
    [207] = 5,
    [208] = 5,
    [209] = 100,
    [210] = 97,
    [211] = 96,
    [212] = 83,
    [213] = 82,
    [214] = 5,
    [215] = 5,
    [216] = 99,
    [217] = 82,
    [218] = 5,
    [219] = 94,
    [220] = 84,
    [221] = 92,
    [222] = 5,
    [223] = 5,
    [224] = 93,
    [225] = 87,
    [226] = 106,
    [227] = 115,
    [228] = 9,
    [229] = 87,
    [230] = 82,
    [231] = 0,
    [232] = 90,
    [233] = 86,
    [234] = 0,
    [235] = 90,
    [236] = 96,
    [237] = 5,
    [238] = 115,
    [239] = 90,
    [240] = 96,
    [241] = 5,
    [242] = 115,
    [243] = 80,
    [244] = 116,
    [245] = 116,
    [246] = 0,
    [247] = 116,
    [248] = 116,
    [249] = 115,
    [250] = 116,
    [251] = 9,
    [252] = 82,
    [253] = 116,
    [254] = 99,
    [255] = 87,
    [256] = 116,
    [257] = 115,
    [258] = 80,
    [259] = 115,
    [260] = 115,
    [261] = 0,
    [262] = 115,
    [263] = 115,
    [264] = 9,
    [265] = 82,
    [266] = 115,
    [267] = 99,
    [268] = 87,
    [269] = 117,
    [270] = 115,
    [271] = 117,
    [272] = 117,
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
