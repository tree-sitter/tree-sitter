#include "tree_sitter/parser.h"

STATE_COUNT = 333;
SYMBOL_COUNT = 48;

enum {
    ts_sym__else = 2,
    ts_sym__for = 3,
    ts_sym__function = 4,
    ts_sym__if = 5,
    ts_sym__terminator = 6,
    ts_sym__var = 7,
    ts_sym_array = 8,
    ts_sym_assignment = 9,
    ts_sym_expression = 10,
    ts_sym_expression_statement = 11,
    ts_sym_false = 12,
    ts_sym_for_statement = 13,
    ts_sym_formal_parameters = 14,
    ts_sym_function_call = 15,
    ts_sym_function_expression = 16,
    ts_sym_identifier = 17,
    ts_sym_if_statement = 18,
    ts_sym_literal = 19,
    ts_sym_null = 20,
    ts_sym_number = 21,
    ts_sym_object = 22,
    ts_sym_program = 23,
    ts_sym_property_access = 24,
    ts_sym_statement = 25,
    ts_sym_statement_block = 26,
    ts_sym_string = 27,
    ts_sym_true = 28,
    ts_sym_var_declaration = 29,
    ts_aux_sym_repeat_helper1 = 30,
    ts_aux_sym_repeat_helper2 = 31,
    ts_aux_sym_repeat_helper3 = 32,
    ts_aux_sym_repeat_helper4 = 33,
    ts_aux_sym_repeat_helper5 = 34,
    ts_aux_sym_repeat_helper6 = 35,
    ts_aux_sym_token1 = 36,
    ts_aux_sym_token10 = 37,
    ts_aux_sym_token11 = 38,
    ts_aux_sym_token12 = 39,
    ts_aux_sym_token2 = 40,
    ts_aux_sym_token3 = 41,
    ts_aux_sym_token4 = 42,
    ts_aux_sym_token5 = 43,
    ts_aux_sym_token6 = 44,
    ts_aux_sym_token7 = 45,
    ts_aux_sym_token8 = 46,
    ts_aux_sym_token9 = 47,
};

SYMBOL_NAMES = {
    [ts_sym__else] = "_else",
    [ts_sym__for] = "_for",
    [ts_sym__function] = "_function",
    [ts_sym__if] = "_if",
    [ts_sym__terminator] = "_terminator",
    [ts_sym__var] = "_var",
    [ts_sym_array] = "array",
    [ts_sym_assignment] = "assignment",
    [ts_sym_expression] = "expression",
    [ts_sym_expression_statement] = "expression_statement",
    [ts_sym_false] = "false",
    [ts_sym_for_statement] = "for_statement",
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
    [ts_sym_var_declaration] = "var_declaration",
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
    [ts_sym__for] = 1,    
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
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(32);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(49);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(57);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 6:
            if (lookahead == 'u')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'n')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'c')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 't')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 'i')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'o')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 'n')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            ACCEPT_TOKEN(ts_sym__function);
        case 14:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(15);
            if (lookahead == '\\')
                ADVANCE(21);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(23);
            LEX_ERROR();
        case 15:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\"')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(18);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 16:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\"')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(18);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 17:
            ACCEPT_TOKEN(ts_sym_string);
        case 18:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\"')
                ADVANCE(19);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(18);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 19:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\"')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(18);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_string);
        case 20:
            if (lookahead == '\"')
                ADVANCE(16);
            LEX_ERROR();
        case 21:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\"')
                ADVANCE(22);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(15);
            if (lookahead == '\\')
                ADVANCE(18);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 22:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\"')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(18);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_string);
        case 23:
            if (lookahead == '\"')
                ADVANCE(15);
            LEX_ERROR();
        case 24:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 25:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if (lookahead == '.')
                ADVANCE(27);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_number);
        case 27:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_number);
        case 29:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_number);
        case 30:
            if (lookahead == '.')
                ADVANCE(27);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_number);
        case 31:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 32:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'a')
                ADVANCE(33);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(40);
            if (lookahead == 'u')
                ADVANCE(41);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(34);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 's')
                ADVANCE(35);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'e')
                ADVANCE(36);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_false);
        case 37:
            ACCEPT_TOKEN(ts_sym_false);
        case 38:
            if (lookahead == 'e')
                ADVANCE(37);
            LEX_ERROR();
        case 39:
            if (lookahead == 's')
                ADVANCE(38);
            LEX_ERROR();
        case 40:
            if (lookahead == 'l')
                ADVANCE(39);
            LEX_ERROR();
        case 41:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'n')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'c')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 't')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'i')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'o')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'n')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym__function);
        case 48:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'u')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'u')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 50:
            if (lookahead == 'l')
                ADVANCE(51);
            LEX_ERROR();
        case 51:
            if (lookahead == 'l')
                ADVANCE(52);
            LEX_ERROR();
        case 52:
            ACCEPT_TOKEN(ts_sym_null);
        case 53:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 55:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_null);
        case 56:
            if (lookahead == 'u')
                ADVANCE(50);
            LEX_ERROR();
        case 57:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'r')
                ADVANCE(58);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 58:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'u')
                ADVANCE(59);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 59:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'e')
                ADVANCE(60);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 60:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_true);
        case 61:
            ACCEPT_TOKEN(ts_sym_true);
        case 62:
            if (lookahead == 'e')
                ADVANCE(61);
            LEX_ERROR();
        case 63:
            if (lookahead == 'u')
                ADVANCE(62);
            LEX_ERROR();
        case 64:
            if (lookahead == 'r')
                ADVANCE(63);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 66:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 67:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(68);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            LEX_ERROR();
        case 68:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 69:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 70:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(68);
            if (lookahead == '.')
                ADVANCE(3);
            LEX_ERROR();
        case 71:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(73);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(78);
            if (lookahead == 'i')
                ADVANCE(79);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'v')
                ADVANCE(83);
            if (lookahead == '{')
                ADVANCE(65);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 72:
            if (lookahead == 'a')
                ADVANCE(40);
            LEX_ERROR();
        case 73:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'a')
                ADVANCE(33);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(40);
            if (lookahead == 'o')
                ADVANCE(74);
            if ('p' <= lookahead && lookahead <= 'o')
                ADVANCE(77);
            if (lookahead == 'u')
                ADVANCE(41);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 74:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'r')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 75:
            ACCEPT_TOKEN(ts_sym__for);
        case 76:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym__for);
        case 77:
            if (lookahead == 'r')
                ADVANCE(75);
            LEX_ERROR();
        case 78:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'a')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 79:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(81);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 80:
            ACCEPT_TOKEN(ts_sym__if);
        case 81:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym__if);
        case 82:
            if (lookahead == 'f')
                ADVANCE(80);
            LEX_ERROR();
        case 83:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'a')
                ADVANCE(84);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 84:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'r')
                ADVANCE(85);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 85:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym__var);
        case 86:
            ACCEPT_TOKEN(ts_sym__var);
        case 87:
            if (lookahead == 'r')
                ADVANCE(86);
            LEX_ERROR();
        case 88:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 89:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(90);
            LEX_ERROR();
        case 90:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 91:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            LEX_ERROR();
        case 92:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 93:
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 94:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(95);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(90);
            LEX_ERROR();
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 96:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(95);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 97:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(98);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 99:
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 100:
            if (lookahead == ')')
                ADVANCE(68);
            LEX_ERROR();
        case 101:
            if (lookahead == ')')
                ADVANCE(68);
            if (lookahead == ',')
                ADVANCE(69);
            LEX_ERROR();
        case 102:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == ')')
                ADVANCE(68);
            LEX_ERROR();
        case 103:
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 104:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 105:
            if (lookahead == ']')
                ADVANCE(98);
            LEX_ERROR();
        case 106:
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == ']')
                ADVANCE(98);
            LEX_ERROR();
        case 107:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == 'f')
                ADVANCE(32);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(49);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(57);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 108:
            if (lookahead == ':')
                ADVANCE(95);
            LEX_ERROR();
        case 109:
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 110:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 111:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(90);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 112:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            LEX_ERROR();
        case 113:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(90);
            if (lookahead == ']')
                ADVANCE(98);
            LEX_ERROR();
        case 114:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == ')')
                ADVANCE(68);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(32);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(49);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(57);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 115:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(68);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(90);
            LEX_ERROR();
        case 116:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(90);
            LEX_ERROR();
        case 117:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(118);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(125);
            if (lookahead == 'f')
                ADVANCE(73);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(78);
            if (lookahead == 'i')
                ADVANCE(79);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'v')
                ADVANCE(83);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(126);
            if (lookahead == '{')
                ADVANCE(65);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        case 118:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(119);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(124);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 119:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 's')
                ADVANCE(120);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(123);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 120:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            if (lookahead == 'e')
                ADVANCE(121);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(122);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 121:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym__else);
        case 122:
            ACCEPT_TOKEN(ts_sym__else);
        case 123:
            if (lookahead == 'e')
                ADVANCE(122);
            LEX_ERROR();
        case 124:
            if (lookahead == 's')
                ADVANCE(123);
            LEX_ERROR();
        case 125:
            if (lookahead == 'l')
                ADVANCE(124);
            LEX_ERROR();
        case 126:
            if (lookahead == 'a')
                ADVANCE(87);
            LEX_ERROR();
        case 127:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(73);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(78);
            if (lookahead == 'i')
                ADVANCE(79);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'v')
                ADVANCE(83);
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 128:
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(68);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(90);
            LEX_ERROR();
        case 129:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(32);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(49);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(56);
            if (lookahead == 't')
                ADVANCE(57);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(83);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(126);
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 130:
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(118);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(125);
            if (lookahead == 'f')
                ADVANCE(73);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(78);
            if (lookahead == 'i')
                ADVANCE(79);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'v')
                ADVANCE(83);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(126);
            if (lookahead == '{')
                ADVANCE(65);
            LEX_ERROR();
        case 131:
            LEX_ERROR();
        case 132:
            if (lookahead == 'l')
                ADVANCE(124);
            if (lookahead == 'u')
                ADVANCE(7);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(14);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(24);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(68);
            if (lookahead == ',')
                ADVANCE(69);
            if (lookahead == '.')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(26);
            if (lookahead == ':')
                ADVANCE(95);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(90);
            if (lookahead == '[')
                ADVANCE(31);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == 'e')
                ADVANCE(118);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(132);
            if (lookahead == 'f')
                ADVANCE(73);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(78);
            if (lookahead == 'i')
                ADVANCE(79);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'v')
                ADVANCE(83);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(126);
            if (lookahead == '{')
                ADVANCE(65);
            if (lookahead == '}')
                ADVANCE(88);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 127,
    [1] = 103,
    [2] = 129,
    [3] = 104,
    [4] = 99,
    [5] = 0,
    [6] = 71,
    [7] = 103,
    [8] = 129,
    [9] = 91,
    [10] = 66,
    [11] = 5,
    [12] = 5,
    [13] = 89,
    [14] = 5,
    [15] = 0,
    [16] = 0,
    [17] = 0,
    [18] = 114,
    [19] = 104,
    [20] = 99,
    [21] = 67,
    [22] = 71,
    [23] = 103,
    [24] = 5,
    [25] = 104,
    [26] = 99,
    [27] = 70,
    [28] = 71,
    [29] = 91,
    [30] = 66,
    [31] = 71,
    [32] = 71,
    [33] = 89,
    [34] = 0,
    [35] = 71,
    [36] = 91,
    [37] = 0,
    [38] = 71,
    [39] = 116,
    [40] = 5,
    [41] = 0,
    [42] = 110,
    [43] = 108,
    [44] = 5,
    [45] = 104,
    [46] = 99,
    [47] = 92,
    [48] = 71,
    [49] = 71,
    [50] = 93,
    [51] = 71,
    [52] = 94,
    [53] = 96,
    [54] = 93,
    [55] = 71,
    [56] = 0,
    [57] = 107,
    [58] = 104,
    [59] = 99,
    [60] = 97,
    [61] = 71,
    [62] = 93,
    [63] = 97,
    [64] = 103,
    [65] = 99,
    [66] = 97,
    [67] = 102,
    [68] = 101,
    [69] = 100,
    [70] = 99,
    [71] = 91,
    [72] = 101,
    [73] = 100,
    [74] = 99,
    [75] = 97,
    [76] = 97,
    [77] = 97,
    [78] = 105,
    [79] = 0,
    [80] = 114,
    [81] = 67,
    [82] = 67,
    [83] = 67,
    [84] = 100,
    [85] = 97,
    [86] = 114,
    [87] = 67,
    [88] = 100,
    [89] = 67,
    [90] = 5,
    [91] = 67,
    [92] = 100,
    [93] = 91,
    [94] = 67,
    [95] = 115,
    [96] = 5,
    [97] = 67,
    [98] = 110,
    [99] = 108,
    [100] = 5,
    [101] = 92,
    [102] = 92,
    [103] = 92,
    [104] = 93,
    [105] = 67,
    [106] = 114,
    [107] = 67,
    [108] = 100,
    [109] = 92,
    [110] = 92,
    [111] = 107,
    [112] = 97,
    [113] = 105,
    [114] = 67,
    [115] = 5,
    [116] = 97,
    [117] = 105,
    [118] = 91,
    [119] = 97,
    [120] = 113,
    [121] = 5,
    [122] = 97,
    [123] = 110,
    [124] = 108,
    [125] = 5,
    [126] = 92,
    [127] = 93,
    [128] = 97,
    [129] = 112,
    [130] = 108,
    [131] = 5,
    [132] = 92,
    [133] = 93,
    [134] = 91,
    [135] = 92,
    [136] = 111,
    [137] = 5,
    [138] = 92,
    [139] = 110,
    [140] = 108,
    [141] = 5,
    [142] = 92,
    [143] = 93,
    [144] = 92,
    [145] = 107,
    [146] = 97,
    [147] = 105,
    [148] = 92,
    [149] = 92,
    [150] = 107,
    [151] = 97,
    [152] = 105,
    [153] = 97,
    [154] = 97,
    [155] = 106,
    [156] = 106,
    [157] = 92,
    [158] = 109,
    [159] = 93,
    [160] = 92,
    [161] = 109,
    [162] = 93,
    [163] = 97,
    [164] = 109,
    [165] = 93,
    [166] = 97,
    [167] = 106,
    [168] = 67,
    [169] = 106,
    [170] = 67,
    [171] = 109,
    [172] = 93,
    [173] = 67,
    [174] = 67,
    [175] = 97,
    [176] = 0,
    [177] = 106,
    [178] = 109,
    [179] = 93,
    [180] = 0,
    [181] = 93,
    [182] = 92,
    [183] = 103,
    [184] = 99,
    [185] = 92,
    [186] = 92,
    [187] = 93,
    [188] = 0,
    [189] = 109,
    [190] = 93,
    [191] = 70,
    [192] = 103,
    [193] = 99,
    [194] = 70,
    [195] = 70,
    [196] = 70,
    [197] = 70,
    [198] = 114,
    [199] = 67,
    [200] = 100,
    [201] = 70,
    [202] = 70,
    [203] = 127,
    [204] = 103,
    [205] = 129,
    [206] = 0,
    [207] = 5,
    [208] = 5,
    [209] = 5,
    [210] = 70,
    [211] = 127,
    [212] = 103,
    [213] = 5,
    [214] = 70,
    [215] = 127,
    [216] = 91,
    [217] = 66,
    [218] = 117,
    [219] = 117,
    [220] = 89,
    [221] = 0,
    [222] = 117,
    [223] = 117,
    [224] = 117,
    [225] = 127,
    [226] = 117,
    [227] = 71,
    [228] = 93,
    [229] = 117,
    [230] = 109,
    [231] = 91,
    [232] = 70,
    [233] = 128,
    [234] = 5,
    [235] = 70,
    [236] = 110,
    [237] = 108,
    [238] = 5,
    [239] = 92,
    [240] = 93,
    [241] = 70,
    [242] = 70,
    [243] = 109,
    [244] = 93,
    [245] = 70,
    [246] = 107,
    [247] = 97,
    [248] = 105,
    [249] = 70,
    [250] = 70,
    [251] = 106,
    [252] = 100,
    [253] = 117,
    [254] = 117,
    [255] = 127,
    [256] = 71,
    [257] = 100,
    [258] = 93,
    [259] = 67,
    [260] = 103,
    [261] = 99,
    [262] = 67,
    [263] = 67,
    [264] = 100,
    [265] = 0,
    [266] = 0,
    [267] = 5,
    [268] = 5,
    [269] = 70,
    [270] = 127,
    [271] = 71,
    [272] = 93,
    [273] = 0,
    [274] = 103,
    [275] = 99,
    [276] = 0,
    [277] = 5,
    [278] = 5,
    [279] = 70,
    [280] = 127,
    [281] = 103,
    [282] = 5,
    [283] = 70,
    [284] = 127,
    [285] = 103,
    [286] = 129,
    [287] = 5,
    [288] = 5,
    [289] = 70,
    [290] = 127,
    [291] = 103,
    [292] = 5,
    [293] = 70,
    [294] = 127,
    [295] = 91,
    [296] = 66,
    [297] = 130,
    [298] = 130,
    [299] = 89,
    [300] = 0,
    [301] = 130,
    [302] = 130,
    [303] = 130,
    [304] = 127,
    [305] = 130,
    [306] = 71,
    [307] = 93,
    [308] = 130,
    [309] = 109,
    [310] = 100,
    [311] = 130,
    [312] = 130,
    [313] = 127,
    [314] = 91,
    [315] = 66,
    [316] = 127,
    [317] = 127,
    [318] = 89,
    [319] = 0,
    [320] = 127,
    [321] = 127,
    [322] = 127,
    [323] = 71,
    [324] = 93,
    [325] = 127,
    [326] = 109,
    [327] = 100,
    [328] = 127,
    [329] = 131,
    [330] = 127,
    [331] = 131,
    [332] = 131,
};

PARSE_TABLE = {
    [0] = {    
        [ts_sym__for] = SHIFT(1),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(281),    
        [ts_sym__var] = SHIFT(314),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(319),    
        [ts_sym_expression_statement] = SHIFT(321),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(321),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(321),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_program] = SHIFT(329),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(330),    
        [ts_sym_statement_block] = SHIFT(321),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(321),    
        [ts_aux_sym_repeat_helper1] = SHIFT(332),    
        [ts_aux_sym_token3] = SHIFT(323),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [1] = {    
        [ts_aux_sym_token1] = SHIFT(2),
    },
    
    [2] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__var] = SHIFT(9),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(277),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(277),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [3] = {    
        [ts_sym_formal_parameters] = SHIFT(4),    
        [ts_sym_identifier] = SHIFT(274),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [4] = {    
        [ts_sym_statement_block] = SHIFT(5),    
        [ts_aux_sym_token3] = SHIFT(6),
    },
    
    [5] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [6] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(272),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(272),
    },
    
    [7] = {    
        [ts_aux_sym_token1] = SHIFT(8),
    },
    
    [8] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__var] = SHIFT(9),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(267),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(267),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [9] = {    
        [ts_sym_assignment] = SHIFT(10),    
        [ts_sym_identifier] = SHIFT(13),
    },
    
    [10] = {    
        [ts_sym__terminator] = SHIFT(11),    
        [ts_aux_sym_token11] = SHIFT(12),    
        [ts_aux_sym_token12] = SHIFT(12),
    },
    
    [11] = {    
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    
    [12] = {    
        [ts_sym__function] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token3] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym__terminator, 1),
    },
    
    [13] = {    
        [ts_sym__terminator] = SHIFT(11),    
        [ts_aux_sym_token11] = SHIFT(12),    
        [ts_aux_sym_token12] = SHIFT(12),    
        [ts_aux_sym_token5] = SHIFT(14),
    },
    
    [14] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(17),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [15] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [16] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [17] = {    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [18] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(263),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token2] = SHIFT(266),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [19] = {    
        [ts_sym_formal_parameters] = SHIFT(20),    
        [ts_sym_identifier] = SHIFT(260),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [20] = {    
        [ts_sym_statement_block] = SHIFT(21),    
        [ts_aux_sym_token3] = SHIFT(22),
    },
    
    [21] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [22] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(258),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(258),
    },
    
    [23] = {    
        [ts_aux_sym_token1] = SHIFT(24),
    },
    
    [24] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(197),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),    
        [ts_builtin_sym_error] = SHIFT(257),
    },
    
    [25] = {    
        [ts_sym_formal_parameters] = SHIFT(26),    
        [ts_sym_identifier] = SHIFT(192),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [26] = {    
        [ts_sym_statement_block] = SHIFT(27),    
        [ts_aux_sym_token3] = SHIFT(28),
    },
    
    [27] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [28] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(190),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(190),
    },
    
    [29] = {    
        [ts_sym_assignment] = SHIFT(30),    
        [ts_sym_identifier] = SHIFT(33),
    },
    
    [30] = {    
        [ts_sym__terminator] = SHIFT(31),    
        [ts_aux_sym_token11] = SHIFT(32),    
        [ts_aux_sym_token12] = SHIFT(32),
    },
    
    [31] = {    
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    
    [32] = {    
        [ts_sym__for] = REDUCE(ts_sym__terminator, 1),    
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
    
    [33] = {    
        [ts_sym__terminator] = SHIFT(31),    
        [ts_aux_sym_token11] = SHIFT(32),    
        [ts_aux_sym_token12] = SHIFT(32),    
        [ts_aux_sym_token5] = SHIFT(14),
    },
    
    [34] = {    
        [ts_sym__terminator] = SHIFT(35),    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = SHIFT(32),    
        [ts_aux_sym_token12] = SHIFT(32),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [35] = {    
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    
    [36] = {    
        [ts_sym_identifier] = SHIFT(37),
    },
    
    [37] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [38] = {    
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),    
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
    
    [39] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [40] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(41),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [41] = {    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [42] = {    
        [ts_sym_identifier] = SHIFT(43),    
        [ts_sym_string] = SHIFT(43),    
        [ts_aux_sym_token4] = SHIFT(56),    
        [ts_builtin_sym_error] = SHIFT(189),
    },
    
    [43] = {    
        [ts_aux_sym_token8] = SHIFT(44),
    },
    
    [44] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(186),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [45] = {    
        [ts_sym_formal_parameters] = SHIFT(46),    
        [ts_sym_identifier] = SHIFT(183),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [46] = {    
        [ts_sym_statement_block] = SHIFT(47),    
        [ts_aux_sym_token3] = SHIFT(48),
    },
    
    [47] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [48] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(181),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(181),
    },
    
    [49] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(50),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [50] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    
    [51] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(52),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(53),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(54),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = SHIFT(56),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(178),
    },
    
    [52] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token5] = SHIFT(40),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token8] = SHIFT(44),
    },
    
    [53] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token8] = SHIFT(44),
    },
    
    [54] = {    
        [ts_aux_sym_token4] = SHIFT(55),
    },
    
    [55] = {    
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [56] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [57] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(77),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token10] = SHIFT(176),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),    
        [ts_builtin_sym_error] = SHIFT(177),
    },
    
    [58] = {    
        [ts_sym_formal_parameters] = SHIFT(59),    
        [ts_sym_identifier] = SHIFT(64),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [59] = {    
        [ts_sym_statement_block] = SHIFT(60),    
        [ts_aux_sym_token3] = SHIFT(61),
    },
    
    [60] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    
    [61] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(62),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper2, 0),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(62),
    },
    
    [62] = {    
        [ts_aux_sym_token4] = SHIFT(63),
    },
    
    [63] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [64] = {    
        [ts_sym_formal_parameters] = SHIFT(65),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [65] = {    
        [ts_sym_statement_block] = SHIFT(66),    
        [ts_aux_sym_token3] = SHIFT(61),
    },
    
    [66] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [67] = {    
        [ts_sym_identifier] = SHIFT(68),    
        [ts_aux_sym_token2] = SHIFT(74),
    },
    
    [68] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(69),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token6] = SHIFT(71),
    },
    
    [69] = {    
        [ts_aux_sym_token2] = SHIFT(70),
    },
    
    [70] = {    
        [ts_aux_sym_token3] = REDUCE(ts_sym_formal_parameters, 4),
    },
    
    [71] = {    
        [ts_sym_identifier] = SHIFT(72),
    },
    
    [72] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(73),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token6] = SHIFT(71),
    },
    
    [73] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    
    [74] = {    
        [ts_aux_sym_token3] = REDUCE(ts_sym_formal_parameters, 2),
    },
    
    [75] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [76] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [77] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(78),    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [78] = {    
        [ts_aux_sym_token10] = SHIFT(79),
    },
    
    [79] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [80] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(83),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token2] = SHIFT(175),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [81] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [82] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [83] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(84),    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(90),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [84] = {    
        [ts_aux_sym_token2] = SHIFT(85),
    },
    
    [85] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [86] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(87),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token2] = SHIFT(174),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [87] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(88),    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(90),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [88] = {    
        [ts_aux_sym_token2] = SHIFT(89),
    },
    
    [89] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [90] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(91),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [91] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(92),    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(90),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [92] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 3),
    },
    
    [93] = {    
        [ts_sym_identifier] = SHIFT(94),
    },
    
    [94] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [95] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token5] = SHIFT(96),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [96] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(97),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [97] = {    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [98] = {    
        [ts_sym_identifier] = SHIFT(99),    
        [ts_sym_string] = SHIFT(99),    
        [ts_aux_sym_token4] = SHIFT(170),    
        [ts_builtin_sym_error] = SHIFT(171),
    },
    
    [99] = {    
        [ts_aux_sym_token8] = SHIFT(100),
    },
    
    [100] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(103),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [101] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [102] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [103] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(104),    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [104] = {    
        [ts_aux_sym_token4] = SHIFT(105),
    },
    
    [105] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [106] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(107),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token2] = SHIFT(110),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [107] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(108),    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(90),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [108] = {    
        [ts_aux_sym_token2] = SHIFT(109),
    },
    
    [109] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [110] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [111] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(112),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token10] = SHIFT(168),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),    
        [ts_builtin_sym_error] = SHIFT(169),
    },
    
    [112] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(113),    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [113] = {    
        [ts_aux_sym_token10] = SHIFT(114),
    },
    
    [114] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [115] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(116),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),    
        [ts_builtin_sym_error] = SHIFT(167),
    },
    
    [116] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(117),    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [117] = {    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    
    [118] = {    
        [ts_sym_identifier] = SHIFT(119),
    },
    
    [119] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [120] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token5] = SHIFT(121),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [121] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(122),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),
    },
    
    [122] = {    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [123] = {    
        [ts_sym_identifier] = SHIFT(124),    
        [ts_sym_string] = SHIFT(124),    
        [ts_aux_sym_token4] = SHIFT(163),    
        [ts_builtin_sym_error] = SHIFT(164),
    },
    
    [124] = {    
        [ts_aux_sym_token8] = SHIFT(125),
    },
    
    [125] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(126),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [126] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(127),    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [127] = {    
        [ts_aux_sym_token4] = SHIFT(128),
    },
    
    [128] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [129] = {    
        [ts_sym_identifier] = SHIFT(130),    
        [ts_sym_string] = SHIFT(130),    
        [ts_builtin_sym_error] = SHIFT(161),
    },
    
    [130] = {    
        [ts_aux_sym_token8] = SHIFT(131),
    },
    
    [131] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(132),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [132] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(133),    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [133] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 5),
    },
    
    [134] = {    
        [ts_sym_identifier] = SHIFT(135),
    },
    
    [135] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [136] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token5] = SHIFT(137),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [137] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(138),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [138] = {    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [139] = {    
        [ts_sym_identifier] = SHIFT(140),    
        [ts_sym_string] = SHIFT(140),    
        [ts_aux_sym_token4] = SHIFT(157),    
        [ts_builtin_sym_error] = SHIFT(158),
    },
    
    [140] = {    
        [ts_aux_sym_token8] = SHIFT(141),
    },
    
    [141] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(142),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [142] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(143),    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [143] = {    
        [ts_aux_sym_token4] = SHIFT(144),
    },
    
    [144] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [145] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(146),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token10] = SHIFT(149),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),    
        [ts_builtin_sym_error] = SHIFT(156),
    },
    
    [146] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(147),    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [147] = {    
        [ts_aux_sym_token10] = SHIFT(148),
    },
    
    [148] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [149] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [150] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(151),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token10] = SHIFT(154),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),    
        [ts_builtin_sym_error] = SHIFT(155),
    },
    
    [151] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(152),    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [152] = {    
        [ts_aux_sym_token10] = SHIFT(153),
    },
    
    [153] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [154] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [155] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(152),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),
    },
    
    [156] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(147),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),
    },
    
    [157] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [158] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(159),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [159] = {    
        [ts_aux_sym_token4] = SHIFT(160),
    },
    
    [160] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [161] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(162),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [162] = {    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    
    [163] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [164] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(165),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [165] = {    
        [ts_aux_sym_token4] = SHIFT(166),
    },
    
    [166] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [167] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(117),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),
    },
    
    [168] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [169] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(113),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),
    },
    
    [170] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [171] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(172),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [172] = {    
        [ts_aux_sym_token4] = SHIFT(173),
    },
    
    [173] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [174] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [175] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [176] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [177] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(78),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),
    },
    
    [178] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(179),    
        [ts_aux_sym_token4] = SHIFT(55),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [179] = {    
        [ts_aux_sym_token4] = SHIFT(180),
    },
    
    [180] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [181] = {    
        [ts_aux_sym_token4] = SHIFT(182),
    },
    
    [182] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [183] = {    
        [ts_sym_formal_parameters] = SHIFT(184),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [184] = {    
        [ts_sym_statement_block] = SHIFT(185),    
        [ts_aux_sym_token3] = SHIFT(48),
    },
    
    [185] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [186] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(187),    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [187] = {    
        [ts_aux_sym_token4] = SHIFT(188),
    },
    
    [188] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [189] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(179),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [190] = {    
        [ts_aux_sym_token4] = SHIFT(191),
    },
    
    [191] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [192] = {    
        [ts_sym_formal_parameters] = SHIFT(193),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [193] = {    
        [ts_sym_statement_block] = SHIFT(194),    
        [ts_aux_sym_token3] = SHIFT(28),
    },
    
    [194] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [195] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    
    [196] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [197] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(203),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [198] = {    
        [ts_sym__function] = SHIFT(19),    
        [ts_sym_array] = SHIFT(81),    
        [ts_sym_assignment] = SHIFT(82),    
        [ts_sym_expression] = SHIFT(199),    
        [ts_sym_false] = SHIFT(81),    
        [ts_sym_function_call] = SHIFT(82),    
        [ts_sym_function_expression] = SHIFT(82),    
        [ts_sym_identifier] = SHIFT(95),    
        [ts_sym_literal] = SHIFT(82),    
        [ts_sym_null] = SHIFT(81),    
        [ts_sym_number] = SHIFT(81),    
        [ts_sym_object] = SHIFT(81),    
        [ts_sym_property_access] = SHIFT(82),    
        [ts_sym_string] = SHIFT(81),    
        [ts_sym_true] = SHIFT(81),    
        [ts_aux_sym_token2] = SHIFT(202),    
        [ts_aux_sym_token3] = SHIFT(98),    
        [ts_aux_sym_token9] = SHIFT(111),
    },
    
    [199] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(200),    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(90),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [200] = {    
        [ts_aux_sym_token2] = SHIFT(201),
    },
    
    [201] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [202] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [203] = {    
        [ts_sym__for] = SHIFT(204),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(212),    
        [ts_sym__var] = SHIFT(216),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(221),    
        [ts_sym_expression_statement] = SHIFT(223),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(223),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(223),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(254),    
        [ts_sym_statement_block] = SHIFT(223),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(223),    
        [ts_aux_sym_token3] = SHIFT(227),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [204] = {    
        [ts_aux_sym_token1] = SHIFT(205),
    },
    
    [205] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__var] = SHIFT(9),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(208),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(208),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [206] = {    
        [ts_sym__terminator] = SHIFT(207),    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = SHIFT(12),    
        [ts_aux_sym_token12] = SHIFT(12),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [207] = {    
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    
    [208] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(209),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [209] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(210),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),
    },
    
    [210] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(211),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [211] = {    
        [ts_sym__for] = SHIFT(204),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(212),    
        [ts_sym__var] = SHIFT(216),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(221),    
        [ts_sym_expression_statement] = SHIFT(223),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(223),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(223),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(253),    
        [ts_sym_statement_block] = SHIFT(223),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(223),    
        [ts_aux_sym_token3] = SHIFT(227),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [212] = {    
        [ts_aux_sym_token1] = SHIFT(213),
    },
    
    [213] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(214),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),    
        [ts_builtin_sym_error] = SHIFT(252),
    },
    
    [214] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(215),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [215] = {    
        [ts_sym__for] = SHIFT(204),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(212),    
        [ts_sym__var] = SHIFT(216),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(221),    
        [ts_sym_expression_statement] = SHIFT(223),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(223),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(223),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(224),    
        [ts_sym_statement_block] = SHIFT(223),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(223),    
        [ts_aux_sym_token3] = SHIFT(227),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [216] = {    
        [ts_sym_assignment] = SHIFT(217),    
        [ts_sym_identifier] = SHIFT(220),
    },
    
    [217] = {    
        [ts_sym__terminator] = SHIFT(218),    
        [ts_aux_sym_token11] = SHIFT(219),    
        [ts_aux_sym_token12] = SHIFT(219),
    },
    
    [218] = {    
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    
    [219] = {    
        [ts_sym__else] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__for] = REDUCE(ts_sym__terminator, 1),    
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
    
    [220] = {    
        [ts_sym__terminator] = SHIFT(218),    
        [ts_aux_sym_token11] = SHIFT(219),    
        [ts_aux_sym_token12] = SHIFT(219),    
        [ts_aux_sym_token5] = SHIFT(14),
    },
    
    [221] = {    
        [ts_sym__terminator] = SHIFT(222),    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = SHIFT(219),    
        [ts_aux_sym_token12] = SHIFT(219),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [222] = {    
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    
    [223] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),    
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
    
    [224] = {    
        [ts_sym__else] = SHIFT(225),    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [225] = {    
        [ts_sym__for] = SHIFT(204),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(212),    
        [ts_sym__var] = SHIFT(216),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(221),    
        [ts_sym_expression_statement] = SHIFT(223),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(223),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(223),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(226),    
        [ts_sym_statement_block] = SHIFT(223),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(223),    
        [ts_aux_sym_token3] = SHIFT(227),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [226] = {    
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [227] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(52),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(53),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(228),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = SHIFT(56),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(230),
    },
    
    [228] = {    
        [ts_aux_sym_token4] = SHIFT(229),
    },
    
    [229] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [230] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(179),    
        [ts_aux_sym_token4] = SHIFT(229),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [231] = {    
        [ts_sym_identifier] = SHIFT(232),
    },
    
    [232] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    
    [233] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token5] = SHIFT(234),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    
    [234] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(235),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),
    },
    
    [235] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 3),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [236] = {    
        [ts_sym_identifier] = SHIFT(237),    
        [ts_sym_string] = SHIFT(237),    
        [ts_aux_sym_token4] = SHIFT(242),    
        [ts_builtin_sym_error] = SHIFT(243),
    },
    
    [237] = {    
        [ts_aux_sym_token8] = SHIFT(238),
    },
    
    [238] = {    
        [ts_sym__function] = SHIFT(45),    
        [ts_sym_array] = SHIFT(101),    
        [ts_sym_assignment] = SHIFT(102),    
        [ts_sym_expression] = SHIFT(239),    
        [ts_sym_false] = SHIFT(101),    
        [ts_sym_function_call] = SHIFT(102),    
        [ts_sym_function_expression] = SHIFT(102),    
        [ts_sym_identifier] = SHIFT(136),    
        [ts_sym_literal] = SHIFT(102),    
        [ts_sym_null] = SHIFT(101),    
        [ts_sym_number] = SHIFT(101),    
        [ts_sym_object] = SHIFT(101),    
        [ts_sym_property_access] = SHIFT(102),    
        [ts_sym_string] = SHIFT(101),    
        [ts_sym_true] = SHIFT(101),    
        [ts_aux_sym_token3] = SHIFT(139),    
        [ts_aux_sym_token9] = SHIFT(145),
    },
    
    [239] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(240),    
        [ts_aux_sym_token1] = SHIFT(106),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),    
        [ts_aux_sym_token7] = SHIFT(134),
    },
    
    [240] = {    
        [ts_aux_sym_token4] = SHIFT(241),
    },
    
    [241] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    
    [242] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    
    [243] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(244),    
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [244] = {    
        [ts_aux_sym_token4] = SHIFT(245),
    },
    
    [245] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    
    [246] = {    
        [ts_sym__function] = SHIFT(58),    
        [ts_sym_array] = SHIFT(75),    
        [ts_sym_assignment] = SHIFT(76),    
        [ts_sym_expression] = SHIFT(247),    
        [ts_sym_false] = SHIFT(75),    
        [ts_sym_function_call] = SHIFT(76),    
        [ts_sym_function_expression] = SHIFT(76),    
        [ts_sym_identifier] = SHIFT(120),    
        [ts_sym_literal] = SHIFT(76),    
        [ts_sym_null] = SHIFT(75),    
        [ts_sym_number] = SHIFT(75),    
        [ts_sym_object] = SHIFT(75),    
        [ts_sym_property_access] = SHIFT(76),    
        [ts_sym_string] = SHIFT(75),    
        [ts_sym_true] = SHIFT(75),    
        [ts_aux_sym_token10] = SHIFT(250),    
        [ts_aux_sym_token3] = SHIFT(123),    
        [ts_aux_sym_token9] = SHIFT(150),    
        [ts_builtin_sym_error] = SHIFT(251),
    },
    
    [247] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(248),    
        [ts_aux_sym_token1] = SHIFT(80),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),    
        [ts_aux_sym_token7] = SHIFT(118),
    },
    
    [248] = {    
        [ts_aux_sym_token10] = SHIFT(249),
    },
    
    [249] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    
    [250] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    
    [251] = {    
        [ts_aux_sym_repeat_helper6] = SHIFT(248),    
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token6] = SHIFT(115),
    },
    
    [252] = {    
        [ts_aux_sym_token2] = SHIFT(215),
    },
    
    [253] = {    
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    
    [254] = {    
        [ts_sym__else] = SHIFT(255),    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [255] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(256),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [256] = {    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [257] = {    
        [ts_aux_sym_token2] = SHIFT(203),
    },
    
    [258] = {    
        [ts_aux_sym_token4] = SHIFT(259),
    },
    
    [259] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [260] = {    
        [ts_sym_formal_parameters] = SHIFT(261),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [261] = {    
        [ts_sym_statement_block] = SHIFT(262),    
        [ts_aux_sym_token3] = SHIFT(22),
    },
    
    [262] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [263] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(264),    
        [ts_aux_sym_token1] = SHIFT(86),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token6] = SHIFT(90),    
        [ts_aux_sym_token7] = SHIFT(93),
    },
    
    [264] = {    
        [ts_aux_sym_token2] = SHIFT(265),
    },
    
    [265] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    
    [266] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    
    [267] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(268),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [268] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(269),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),
    },
    
    [269] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(270),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [270] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(271),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [271] = {    
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token4] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    
    [272] = {    
        [ts_aux_sym_token4] = SHIFT(273),
    },
    
    [273] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [274] = {    
        [ts_sym_formal_parameters] = SHIFT(275),    
        [ts_aux_sym_token1] = SHIFT(67),
    },
    
    [275] = {    
        [ts_sym_statement_block] = SHIFT(276),    
        [ts_aux_sym_token3] = SHIFT(6),
    },
    
    [276] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    
    [277] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(278),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [278] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(279),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),
    },
    
    [279] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(280),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [280] = {    
        [ts_sym__for] = SHIFT(1),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(281),    
        [ts_sym__var] = SHIFT(314),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(319),    
        [ts_sym_expression_statement] = SHIFT(321),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(321),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(321),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(328),    
        [ts_sym_statement_block] = SHIFT(321),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(321),    
        [ts_aux_sym_token3] = SHIFT(323),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [281] = {    
        [ts_aux_sym_token1] = SHIFT(282),
    },
    
    [282] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(283),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),    
        [ts_builtin_sym_error] = SHIFT(327),
    },
    
    [283] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(284),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [284] = {    
        [ts_sym__for] = SHIFT(285),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(291),    
        [ts_sym__var] = SHIFT(295),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(300),    
        [ts_sym_expression_statement] = SHIFT(302),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(302),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(302),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(312),    
        [ts_sym_statement_block] = SHIFT(302),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(302),    
        [ts_aux_sym_token3] = SHIFT(306),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [285] = {    
        [ts_aux_sym_token1] = SHIFT(286),
    },
    
    [286] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__var] = SHIFT(9),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(287),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(287),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [287] = {    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(206),    
        [ts_sym_expression_statement] = SHIFT(288),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_aux_sym_token3] = SHIFT(42),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [288] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(289),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),
    },
    
    [289] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(290),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [290] = {    
        [ts_sym__for] = SHIFT(285),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(291),    
        [ts_sym__var] = SHIFT(295),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(300),    
        [ts_sym_expression_statement] = SHIFT(302),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(302),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(302),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(311),    
        [ts_sym_statement_block] = SHIFT(302),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(302),    
        [ts_aux_sym_token3] = SHIFT(306),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [291] = {    
        [ts_aux_sym_token1] = SHIFT(292),
    },
    
    [292] = {    
        [ts_sym__function] = SHIFT(25),    
        [ts_sym_array] = SHIFT(195),    
        [ts_sym_assignment] = SHIFT(196),    
        [ts_sym_expression] = SHIFT(293),    
        [ts_sym_false] = SHIFT(195),    
        [ts_sym_function_call] = SHIFT(196),    
        [ts_sym_function_expression] = SHIFT(196),    
        [ts_sym_identifier] = SHIFT(233),    
        [ts_sym_literal] = SHIFT(196),    
        [ts_sym_null] = SHIFT(195),    
        [ts_sym_number] = SHIFT(195),    
        [ts_sym_object] = SHIFT(195),    
        [ts_sym_property_access] = SHIFT(196),    
        [ts_sym_string] = SHIFT(195),    
        [ts_sym_true] = SHIFT(195),    
        [ts_aux_sym_token3] = SHIFT(236),    
        [ts_aux_sym_token9] = SHIFT(246),    
        [ts_builtin_sym_error] = SHIFT(310),
    },
    
    [293] = {    
        [ts_aux_sym_token1] = SHIFT(198),    
        [ts_aux_sym_token2] = SHIFT(294),    
        [ts_aux_sym_token7] = SHIFT(231),
    },
    
    [294] = {    
        [ts_sym__for] = SHIFT(285),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(291),    
        [ts_sym__var] = SHIFT(295),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(300),    
        [ts_sym_expression_statement] = SHIFT(302),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(302),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(302),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(303),    
        [ts_sym_statement_block] = SHIFT(302),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(302),    
        [ts_aux_sym_token3] = SHIFT(306),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [295] = {    
        [ts_sym_assignment] = SHIFT(296),    
        [ts_sym_identifier] = SHIFT(299),
    },
    
    [296] = {    
        [ts_sym__terminator] = SHIFT(297),    
        [ts_aux_sym_token11] = SHIFT(298),    
        [ts_aux_sym_token12] = SHIFT(298),
    },
    
    [297] = {    
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
    },
    
    [298] = {    
        [ts_sym__else] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__for] = REDUCE(ts_sym__terminator, 1),    
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
    
    [299] = {    
        [ts_sym__terminator] = SHIFT(297),    
        [ts_aux_sym_token11] = SHIFT(298),    
        [ts_aux_sym_token12] = SHIFT(298),    
        [ts_aux_sym_token5] = SHIFT(14),
    },
    
    [300] = {    
        [ts_sym__terminator] = SHIFT(301),    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = SHIFT(298),    
        [ts_aux_sym_token12] = SHIFT(298),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [301] = {    
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
    },
    
    [302] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),    
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
    
    [303] = {    
        [ts_sym__else] = SHIFT(304),    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [304] = {    
        [ts_sym__for] = SHIFT(285),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(291),    
        [ts_sym__var] = SHIFT(295),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(300),    
        [ts_sym_expression_statement] = SHIFT(302),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(302),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(302),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(305),    
        [ts_sym_statement_block] = SHIFT(302),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(302),    
        [ts_aux_sym_token3] = SHIFT(306),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [305] = {    
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [306] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(52),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(53),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(307),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = SHIFT(56),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(309),
    },
    
    [307] = {    
        [ts_aux_sym_token4] = SHIFT(308),
    },
    
    [308] = {    
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [309] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(179),    
        [ts_aux_sym_token4] = SHIFT(308),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [310] = {    
        [ts_aux_sym_token2] = SHIFT(294),
    },
    
    [311] = {    
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
    },
    
    [312] = {    
        [ts_sym__else] = SHIFT(313),    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),    
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
    
    [313] = {    
        [ts_sym__for] = SHIFT(1),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(281),    
        [ts_sym__var] = SHIFT(314),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(319),    
        [ts_sym_expression_statement] = SHIFT(321),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(321),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(321),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(322),    
        [ts_sym_statement_block] = SHIFT(321),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(321),    
        [ts_aux_sym_token3] = SHIFT(323),    
        [ts_aux_sym_token9] = SHIFT(57),
    },
    
    [314] = {    
        [ts_sym_assignment] = SHIFT(315),    
        [ts_sym_identifier] = SHIFT(318),
    },
    
    [315] = {    
        [ts_sym__terminator] = SHIFT(316),    
        [ts_aux_sym_token11] = SHIFT(317),    
        [ts_aux_sym_token12] = SHIFT(317),
    },
    
    [316] = {    
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
    },
    
    [317] = {    
        [ts_sym__for] = REDUCE(ts_sym__terminator, 1),    
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
    
    [318] = {    
        [ts_sym__terminator] = SHIFT(316),    
        [ts_aux_sym_token11] = SHIFT(317),    
        [ts_aux_sym_token12] = SHIFT(317),    
        [ts_aux_sym_token5] = SHIFT(14),
    },
    
    [319] = {    
        [ts_sym__terminator] = SHIFT(320),    
        [ts_aux_sym_token1] = SHIFT(18),    
        [ts_aux_sym_token11] = SHIFT(317),    
        [ts_aux_sym_token12] = SHIFT(317),    
        [ts_aux_sym_token7] = SHIFT(36),
    },
    
    [320] = {    
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
    },
    
    [321] = {    
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),    
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
    
    [322] = {    
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),    
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
    
    [323] = {    
        [ts_sym__for] = SHIFT(7),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(23),    
        [ts_sym__var] = SHIFT(29),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(34),    
        [ts_sym_expression_statement] = SHIFT(38),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(38),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(52),    
        [ts_sym_if_statement] = SHIFT(38),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(49),    
        [ts_sym_statement_block] = SHIFT(38),    
        [ts_sym_string] = SHIFT(53),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(38),    
        [ts_aux_sym_repeat_helper2] = SHIFT(324),    
        [ts_aux_sym_token3] = SHIFT(51),    
        [ts_aux_sym_token4] = SHIFT(56),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_error] = SHIFT(326),
    },
    
    [324] = {    
        [ts_aux_sym_token4] = SHIFT(325),
    },
    
    [325] = {    
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),    
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
    
    [326] = {    
        [ts_aux_sym_repeat_helper5] = SHIFT(179),    
        [ts_aux_sym_token4] = SHIFT(325),    
        [ts_aux_sym_token6] = SHIFT(129),
    },
    
    [327] = {    
        [ts_aux_sym_token2] = SHIFT(284),
    },
    
    [328] = {    
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),    
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
    },
    
    [329] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [330] = {    
        [ts_sym__for] = SHIFT(1),    
        [ts_sym__function] = SHIFT(3),    
        [ts_sym__if] = SHIFT(281),    
        [ts_sym__var] = SHIFT(314),    
        [ts_sym_array] = SHIFT(15),    
        [ts_sym_assignment] = SHIFT(16),    
        [ts_sym_expression] = SHIFT(319),    
        [ts_sym_expression_statement] = SHIFT(321),    
        [ts_sym_false] = SHIFT(15),    
        [ts_sym_for_statement] = SHIFT(321),    
        [ts_sym_function_call] = SHIFT(16),    
        [ts_sym_function_expression] = SHIFT(16),    
        [ts_sym_identifier] = SHIFT(39),    
        [ts_sym_if_statement] = SHIFT(321),    
        [ts_sym_literal] = SHIFT(16),    
        [ts_sym_null] = SHIFT(15),    
        [ts_sym_number] = SHIFT(15),    
        [ts_sym_object] = SHIFT(15),    
        [ts_sym_property_access] = SHIFT(16),    
        [ts_sym_statement] = SHIFT(330),    
        [ts_sym_statement_block] = SHIFT(321),    
        [ts_sym_string] = SHIFT(15),    
        [ts_sym_true] = SHIFT(15),    
        [ts_sym_var_declaration] = SHIFT(321),    
        [ts_aux_sym_repeat_helper1] = SHIFT(331),    
        [ts_aux_sym_token3] = SHIFT(323),    
        [ts_aux_sym_token9] = SHIFT(57),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [331] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    
    [332] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
