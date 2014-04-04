#include "tree_sitter/parser.h"

STATE_COUNT = 342;
SYMBOL_COUNT = 46;

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
    ts_aux_sym_token2 = 38,
    ts_aux_sym_token3 = 39,
    ts_aux_sym_token4 = 40,
    ts_aux_sym_token5 = 41,
    ts_aux_sym_token6 = 42,
    ts_aux_sym_token7 = 43,
    ts_aux_sym_token8 = 44,
    ts_aux_sym_token9 = 45,
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
    [ts_aux_sym_token1] = "'{'",
    [ts_aux_sym_token10] = "']'",
    [ts_aux_sym_token2] = "'}'",
    [ts_aux_sym_token3] = "'('",
    [ts_aux_sym_token4] = "')'",
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
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(5);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 5:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 6:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(6);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 7:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(8);
            if (lookahead == '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 8:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(8);
            if (lookahead == '\"')
                ADVANCE(9);
            if (lookahead == '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(ts_sym_string);
        case 10:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(8);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 11:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(8);
            if (lookahead == '\"')
                ADVANCE(9);
            if (lookahead == '\\')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_string);
        case 12:
            if (lookahead == '.')
                ADVANCE(13);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym_number);
        case 13:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_number);
        case 15:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 16:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 17:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(18);
            if (lookahead == 'u')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 18:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 21:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_false);
        case 22:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 23:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 24:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym__function);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'u')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_null);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'u')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_true);
        case 37:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 38:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\n')
                ADVANCE(39);
            if (lookahead == ';')
                ADVANCE(5);
            LEX_ERROR();
        case 39:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\n')
                ADVANCE(39);
            if (lookahead == ';')
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 40:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(40);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            LEX_ERROR();
        case 41:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 42:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 43:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(43);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(4);
            LEX_ERROR();
        case 44:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(44);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(18);
            if (lookahead == 'o')
                ADVANCE(46);
            if (lookahead == 'u')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym__for);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym__if);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 52:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym__var);
        case 53:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 54:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(54);
            if (lookahead == '\n')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            LEX_ERROR();
        case 55:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(54);
            if (lookahead == '\n')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 56:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 57:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(57);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 58:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(58);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 59:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(59);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 60:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(60);
            if (lookahead == '\n')
                ADVANCE(61);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            LEX_ERROR();
        case 61:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(60);
            if (lookahead == '\n')
                ADVANCE(61);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 63:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (lookahead == '\n')
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            LEX_ERROR();
        case 64:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (lookahead == '\n')
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 65:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 66:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 67:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '\n')
                ADVANCE(68);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 68:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '\n')
                ADVANCE(68);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '}')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 69:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 70:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (lookahead == ')')
                ADVANCE(41);
            LEX_ERROR();
        case 71:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == ',')
                ADVANCE(42);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == ')')
                ADVANCE(41);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(3);
            LEX_ERROR();
        case 74:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '(')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 75:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(66);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == ':')
                ADVANCE(62);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\"')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '\"')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(56);
            if (lookahead == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 84:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(7);
            if (lookahead == ')')
                ADVANCE(41);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 85:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(56);
            LEX_ERROR();
        case 86:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '\n')
                ADVANCE(87);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 87:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '\n')
                ADVANCE(87);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '}')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 88:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '\n')
                ADVANCE(89);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            LEX_ERROR();
        case 89:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '\n')
                ADVANCE(89);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 90:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'e')
                ADVANCE(91);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 91:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 92:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 93:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 94:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym__else);
        case 95:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 96:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(56);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(97);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 98:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(98);
            if (lookahead == '\"')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'e')
                ADVANCE(91);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            LEX_ERROR();
        case 99:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            LEX_ERROR();
        case 100:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '\n')
                ADVANCE(101);
            if (lookahead == '\"')
                ADVANCE(7);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(66);
            if (lookahead == 'e')
                ADVANCE(91);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '\n')
                ADVANCE(101);
            if (lookahead == '\"')
                ADVANCE(7);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(66);
            if (lookahead == 'e')
                ADVANCE(91);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            if (lookahead == '}')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__terminator);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '\n')
                ADVANCE(101);
            if (lookahead == '\"')
                ADVANCE(7);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(41);
            if (lookahead == ',')
                ADVANCE(42);
            if (lookahead == '.')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            if (lookahead == ':')
                ADVANCE(62);
            if (lookahead == ';')
                ADVANCE(5);
            if (lookahead == '=')
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(66);
            if (lookahead == 'e')
                ADVANCE(91);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(48);
            if (lookahead == 'n')
                ADVANCE(29);
            if (lookahead == 't')
                ADVANCE(33);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(37);
            if (lookahead == '}')
                ADVANCE(53);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 95,
    [1] = 73,
    [2] = 97,
    [3] = 74,
    [4] = 69,
    [5] = 0,
    [6] = 44,
    [7] = 73,
    [8] = 97,
    [9] = 57,
    [10] = 38,
    [11] = 6,
    [12] = 54,
    [13] = 6,
    [14] = 0,
    [15] = 0,
    [16] = 0,
    [17] = 84,
    [18] = 74,
    [19] = 69,
    [20] = 40,
    [21] = 44,
    [22] = 73,
    [23] = 6,
    [24] = 74,
    [25] = 69,
    [26] = 43,
    [27] = 44,
    [28] = 57,
    [29] = 38,
    [30] = 44,
    [31] = 54,
    [32] = 0,
    [33] = 44,
    [34] = 57,
    [35] = 0,
    [36] = 44,
    [37] = 88,
    [38] = 6,
    [39] = 0,
    [40] = 80,
    [41] = 78,
    [42] = 6,
    [43] = 74,
    [44] = 69,
    [45] = 58,
    [46] = 44,
    [47] = 44,
    [48] = 59,
    [49] = 44,
    [50] = 60,
    [51] = 63,
    [52] = 59,
    [53] = 44,
    [54] = 0,
    [55] = 77,
    [56] = 74,
    [57] = 69,
    [58] = 65,
    [59] = 44,
    [60] = 59,
    [61] = 65,
    [62] = 67,
    [63] = 73,
    [64] = 69,
    [65] = 65,
    [66] = 72,
    [67] = 71,
    [68] = 70,
    [69] = 69,
    [70] = 57,
    [71] = 71,
    [72] = 70,
    [73] = 69,
    [74] = 65,
    [75] = 65,
    [76] = 65,
    [77] = 75,
    [78] = 0,
    [79] = 84,
    [80] = 40,
    [81] = 40,
    [82] = 40,
    [83] = 70,
    [84] = 65,
    [85] = 84,
    [86] = 40,
    [87] = 70,
    [88] = 40,
    [89] = 6,
    [90] = 40,
    [91] = 70,
    [92] = 57,
    [93] = 40,
    [94] = 85,
    [95] = 6,
    [96] = 40,
    [97] = 80,
    [98] = 78,
    [99] = 6,
    [100] = 58,
    [101] = 58,
    [102] = 58,
    [103] = 59,
    [104] = 40,
    [105] = 84,
    [106] = 40,
    [107] = 70,
    [108] = 58,
    [109] = 58,
    [110] = 77,
    [111] = 65,
    [112] = 75,
    [113] = 40,
    [114] = 6,
    [115] = 65,
    [116] = 75,
    [117] = 57,
    [118] = 65,
    [119] = 83,
    [120] = 6,
    [121] = 65,
    [122] = 80,
    [123] = 78,
    [124] = 6,
    [125] = 58,
    [126] = 59,
    [127] = 65,
    [128] = 82,
    [129] = 78,
    [130] = 6,
    [131] = 58,
    [132] = 59,
    [133] = 57,
    [134] = 58,
    [135] = 81,
    [136] = 6,
    [137] = 58,
    [138] = 80,
    [139] = 78,
    [140] = 6,
    [141] = 58,
    [142] = 59,
    [143] = 58,
    [144] = 77,
    [145] = 65,
    [146] = 75,
    [147] = 58,
    [148] = 58,
    [149] = 77,
    [150] = 65,
    [151] = 75,
    [152] = 65,
    [153] = 65,
    [154] = 76,
    [155] = 76,
    [156] = 58,
    [157] = 79,
    [158] = 59,
    [159] = 58,
    [160] = 79,
    [161] = 59,
    [162] = 65,
    [163] = 79,
    [164] = 59,
    [165] = 65,
    [166] = 76,
    [167] = 40,
    [168] = 76,
    [169] = 40,
    [170] = 79,
    [171] = 59,
    [172] = 40,
    [173] = 40,
    [174] = 65,
    [175] = 0,
    [176] = 76,
    [177] = 86,
    [178] = 59,
    [179] = 0,
    [180] = 38,
    [181] = 59,
    [182] = 58,
    [183] = 67,
    [184] = 73,
    [185] = 69,
    [186] = 58,
    [187] = 58,
    [188] = 59,
    [189] = 0,
    [190] = 79,
    [191] = 59,
    [192] = 43,
    [193] = 67,
    [194] = 73,
    [195] = 69,
    [196] = 43,
    [197] = 43,
    [198] = 43,
    [199] = 43,
    [200] = 84,
    [201] = 40,
    [202] = 70,
    [203] = 43,
    [204] = 43,
    [205] = 95,
    [206] = 73,
    [207] = 97,
    [208] = 0,
    [209] = 6,
    [210] = 6,
    [211] = 6,
    [212] = 43,
    [213] = 95,
    [214] = 73,
    [215] = 6,
    [216] = 43,
    [217] = 95,
    [218] = 57,
    [219] = 38,
    [220] = 90,
    [221] = 54,
    [222] = 0,
    [223] = 90,
    [224] = 90,
    [225] = 90,
    [226] = 95,
    [227] = 90,
    [228] = 44,
    [229] = 59,
    [230] = 90,
    [231] = 86,
    [232] = 38,
    [233] = 57,
    [234] = 43,
    [235] = 96,
    [236] = 6,
    [237] = 43,
    [238] = 80,
    [239] = 78,
    [240] = 6,
    [241] = 58,
    [242] = 59,
    [243] = 43,
    [244] = 43,
    [245] = 79,
    [246] = 59,
    [247] = 43,
    [248] = 77,
    [249] = 65,
    [250] = 75,
    [251] = 43,
    [252] = 43,
    [253] = 76,
    [254] = 70,
    [255] = 90,
    [256] = 70,
    [257] = 38,
    [258] = 90,
    [259] = 95,
    [260] = 44,
    [261] = 70,
    [262] = 59,
    [263] = 40,
    [264] = 67,
    [265] = 73,
    [266] = 69,
    [267] = 40,
    [268] = 40,
    [269] = 70,
    [270] = 0,
    [271] = 0,
    [272] = 6,
    [273] = 6,
    [274] = 43,
    [275] = 95,
    [276] = 44,
    [277] = 70,
    [278] = 59,
    [279] = 0,
    [280] = 67,
    [281] = 73,
    [282] = 69,
    [283] = 0,
    [284] = 6,
    [285] = 6,
    [286] = 43,
    [287] = 95,
    [288] = 73,
    [289] = 6,
    [290] = 43,
    [291] = 95,
    [292] = 73,
    [293] = 97,
    [294] = 6,
    [295] = 6,
    [296] = 43,
    [297] = 95,
    [298] = 73,
    [299] = 6,
    [300] = 43,
    [301] = 95,
    [302] = 57,
    [303] = 38,
    [304] = 98,
    [305] = 54,
    [306] = 0,
    [307] = 98,
    [308] = 98,
    [309] = 98,
    [310] = 95,
    [311] = 98,
    [312] = 44,
    [313] = 59,
    [314] = 98,
    [315] = 86,
    [316] = 38,
    [317] = 70,
    [318] = 98,
    [319] = 70,
    [320] = 98,
    [321] = 95,
    [322] = 57,
    [323] = 38,
    [324] = 95,
    [325] = 54,
    [326] = 0,
    [327] = 95,
    [328] = 95,
    [329] = 95,
    [330] = 44,
    [331] = 59,
    [332] = 95,
    [333] = 86,
    [334] = 38,
    [335] = 70,
    [336] = 95,
    [337] = 70,
    [338] = 99,
    [339] = 95,
    [340] = 99,
    [341] = 99,
};

PARSE_TABLE = {
    [0] = {
        [ts_sym__for] = SHIFT(1),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(288),
        [ts_sym__var] = SHIFT(322),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_expression_statement] = SHIFT(328),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(328),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(328),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_program] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(339),
        [ts_sym_statement_block] = SHIFT(328),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(328),
        [ts_aux_sym_repeat_helper1] = SHIFT(341),
        [ts_aux_sym_token1] = SHIFT(330),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_builtin_sym_error] = SHIFT(334),
    },
    [1] = {
        [ts_aux_sym_token3] = SHIFT(2),
    },
    [2] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym__var] = SHIFT(9),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(284),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(284),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [3] = {
        [ts_sym_formal_parameters] = SHIFT(4),
        [ts_sym_identifier] = SHIFT(281),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [4] = {
        [ts_sym_statement_block] = SHIFT(5),
        [ts_aux_sym_token1] = SHIFT(6),
    },
    [5] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    [6] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(278),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(280),
    },
    [7] = {
        [ts_aux_sym_token3] = SHIFT(8),
    },
    [8] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym__var] = SHIFT(9),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(272),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(272),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [9] = {
        [ts_sym_assignment] = SHIFT(10),
        [ts_sym_identifier] = SHIFT(12),
    },
    [10] = {
        [ts_sym__terminator] = SHIFT(11),
    },
    [11] = {
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
    },
    [12] = {
        [ts_sym__terminator] = SHIFT(11),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [13] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(16),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
    },
    [14] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    [15] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [16] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [17] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(268),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token4] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [18] = {
        [ts_sym_formal_parameters] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(265),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [19] = {
        [ts_sym_statement_block] = SHIFT(20),
        [ts_aux_sym_token1] = SHIFT(21),
    },
    [20] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    [21] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(264),
    },
    [22] = {
        [ts_aux_sym_token3] = SHIFT(23),
    },
    [23] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(199),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(261),
    },
    [24] = {
        [ts_sym_formal_parameters] = SHIFT(25),
        [ts_sym_identifier] = SHIFT(194),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [25] = {
        [ts_sym_statement_block] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(27),
    },
    [26] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    [27] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(191),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(193),
    },
    [28] = {
        [ts_sym_assignment] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(31),
    },
    [29] = {
        [ts_sym__terminator] = SHIFT(30),
    },
    [30] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
    },
    [31] = {
        [ts_sym__terminator] = SHIFT(30),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [32] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [33] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
    },
    [34] = {
        [ts_sym_identifier] = SHIFT(35),
    },
    [35] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    [36] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
    },
    [37] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(38),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [38] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(39),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
    },
    [39] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [40] = {
        [ts_sym_identifier] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_aux_sym_token2] = SHIFT(54),
        [ts_builtin_sym_error] = SHIFT(190),
    },
    [41] = {
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [42] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(187),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [43] = {
        [ts_sym_formal_parameters] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [44] = {
        [ts_sym_statement_block] = SHIFT(45),
        [ts_aux_sym_token1] = SHIFT(46),
    },
    [45] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    [46] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(181),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(183),
    },
    [47] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(180),
    },
    [48] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    [49] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = SHIFT(54),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(177),
    },
    [50] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(38),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [51] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [52] = {
        [ts_aux_sym_token2] = SHIFT(53),
    },
    [53] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
    },
    [54] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    [55] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(76),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token10] = SHIFT(175),
        [ts_aux_sym_token9] = SHIFT(149),
        [ts_builtin_sym_error] = SHIFT(176),
    },
    [56] = {
        [ts_sym_formal_parameters] = SHIFT(57),
        [ts_sym_identifier] = SHIFT(63),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [57] = {
        [ts_sym_statement_block] = SHIFT(58),
        [ts_aux_sym_token1] = SHIFT(59),
    },
    [58] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
    },
    [59] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(60),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(62),
    },
    [60] = {
        [ts_aux_sym_token2] = SHIFT(61),
    },
    [61] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    [62] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_token2] = SHIFT(61),
    },
    [63] = {
        [ts_sym_formal_parameters] = SHIFT(64),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [64] = {
        [ts_sym_statement_block] = SHIFT(65),
        [ts_aux_sym_token1] = SHIFT(59),
    },
    [65] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    [66] = {
        [ts_sym_identifier] = SHIFT(67),
        [ts_aux_sym_token4] = SHIFT(73),
    },
    [67] = {
        [ts_aux_sym_repeat_helper4] = SHIFT(68),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token6] = SHIFT(70),
    },
    [68] = {
        [ts_aux_sym_token4] = SHIFT(69),
    },
    [69] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [70] = {
        [ts_sym_identifier] = SHIFT(71),
    },
    [71] = {
        [ts_aux_sym_repeat_helper4] = SHIFT(72),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token6] = SHIFT(70),
    },
    [72] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    [73] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [74] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    [75] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [76] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(77),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = SHIFT(114),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [77] = {
        [ts_aux_sym_token10] = SHIFT(78),
    },
    [78] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    [79] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(82),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token4] = SHIFT(174),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [80] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    [81] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [82] = {
        [ts_aux_sym_repeat_helper3] = SHIFT(83),
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_aux_sym_token6] = SHIFT(89),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [83] = {
        [ts_aux_sym_token4] = SHIFT(84),
    },
    [84] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    [85] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(86),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token4] = SHIFT(173),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [86] = {
        [ts_aux_sym_repeat_helper3] = SHIFT(87),
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_aux_sym_token6] = SHIFT(89),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [87] = {
        [ts_aux_sym_token4] = SHIFT(88),
    },
    [88] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    [89] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(90),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [90] = {
        [ts_aux_sym_repeat_helper3] = SHIFT(91),
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_aux_sym_token6] = SHIFT(89),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [91] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 3),
    },
    [92] = {
        [ts_sym_identifier] = SHIFT(93),
    },
    [93] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    [94] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(95),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [95] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(96),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [96] = {
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [97] = {
        [ts_sym_identifier] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_aux_sym_token2] = SHIFT(169),
        [ts_builtin_sym_error] = SHIFT(170),
    },
    [98] = {
        [ts_aux_sym_token8] = SHIFT(99),
    },
    [99] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(102),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [100] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    [101] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [102] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(103),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(128),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [103] = {
        [ts_aux_sym_token2] = SHIFT(104),
    },
    [104] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    [105] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(106),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token4] = SHIFT(109),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [106] = {
        [ts_aux_sym_repeat_helper3] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_aux_sym_token6] = SHIFT(89),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [107] = {
        [ts_aux_sym_token4] = SHIFT(108),
    },
    [108] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    [109] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    [110] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(111),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token10] = SHIFT(167),
        [ts_aux_sym_token9] = SHIFT(149),
        [ts_builtin_sym_error] = SHIFT(168),
    },
    [111] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(112),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = SHIFT(114),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [112] = {
        [ts_aux_sym_token10] = SHIFT(113),
    },
    [113] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    [114] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(115),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token9] = SHIFT(149),
        [ts_builtin_sym_error] = SHIFT(166),
    },
    [115] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(116),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = SHIFT(114),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [116] = {
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    [117] = {
        [ts_sym_identifier] = SHIFT(118),
    },
    [118] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    [119] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(120),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [120] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(121),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token9] = SHIFT(149),
    },
    [121] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [122] = {
        [ts_sym_identifier] = SHIFT(123),
        [ts_sym_string] = SHIFT(123),
        [ts_aux_sym_token2] = SHIFT(162),
        [ts_builtin_sym_error] = SHIFT(163),
    },
    [123] = {
        [ts_aux_sym_token8] = SHIFT(124),
    },
    [124] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(125),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [125] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(126),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(128),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [126] = {
        [ts_aux_sym_token2] = SHIFT(127),
    },
    [127] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    [128] = {
        [ts_sym_identifier] = SHIFT(129),
        [ts_sym_string] = SHIFT(129),
        [ts_builtin_sym_error] = SHIFT(160),
    },
    [129] = {
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [130] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(131),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [131] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(132),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(128),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [132] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 5),
    },
    [133] = {
        [ts_sym_identifier] = SHIFT(134),
    },
    [134] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    [135] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(136),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [136] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(137),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [137] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [138] = {
        [ts_sym_identifier] = SHIFT(139),
        [ts_sym_string] = SHIFT(139),
        [ts_aux_sym_token2] = SHIFT(156),
        [ts_builtin_sym_error] = SHIFT(157),
    },
    [139] = {
        [ts_aux_sym_token8] = SHIFT(140),
    },
    [140] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(141),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [141] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(142),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(128),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [142] = {
        [ts_aux_sym_token2] = SHIFT(143),
    },
    [143] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    [144] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(145),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token10] = SHIFT(148),
        [ts_aux_sym_token9] = SHIFT(149),
        [ts_builtin_sym_error] = SHIFT(155),
    },
    [145] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(146),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = SHIFT(114),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [146] = {
        [ts_aux_sym_token10] = SHIFT(147),
    },
    [147] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    [148] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    [149] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(150),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token10] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(149),
        [ts_builtin_sym_error] = SHIFT(154),
    },
    [150] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(151),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = SHIFT(114),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [151] = {
        [ts_aux_sym_token10] = SHIFT(152),
    },
    [152] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    [153] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    [154] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(151),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token6] = SHIFT(114),
    },
    [155] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(146),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token6] = SHIFT(114),
    },
    [156] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    [157] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(158),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [158] = {
        [ts_aux_sym_token2] = SHIFT(159),
    },
    [159] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    [160] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(161),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [161] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    [162] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    [163] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(164),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [164] = {
        [ts_aux_sym_token2] = SHIFT(165),
    },
    [165] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    [166] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(116),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token6] = SHIFT(114),
    },
    [167] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    [168] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(112),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token6] = SHIFT(114),
    },
    [169] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    [170] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(171),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [171] = {
        [ts_aux_sym_token2] = SHIFT(172),
    },
    [172] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    [173] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    [174] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    [175] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    [176] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(77),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token6] = SHIFT(114),
    },
    [177] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_repeat_helper5] = SHIFT(178),
        [ts_aux_sym_token2] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [178] = {
        [ts_aux_sym_token2] = SHIFT(179),
    },
    [179] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    [180] = {
        [ts_sym__terminator] = SHIFT(33),
    },
    [181] = {
        [ts_aux_sym_token2] = SHIFT(182),
    },
    [182] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    [183] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_token2] = SHIFT(182),
    },
    [184] = {
        [ts_sym_formal_parameters] = SHIFT(185),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [185] = {
        [ts_sym_statement_block] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(46),
    },
    [186] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    [187] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(188),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(128),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [188] = {
        [ts_aux_sym_token2] = SHIFT(189),
    },
    [189] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    [190] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(178),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [191] = {
        [ts_aux_sym_token2] = SHIFT(192),
    },
    [192] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    [193] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_token2] = SHIFT(192),
    },
    [194] = {
        [ts_sym_formal_parameters] = SHIFT(195),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [195] = {
        [ts_sym_statement_block] = SHIFT(196),
        [ts_aux_sym_token1] = SHIFT(27),
    },
    [196] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    [197] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
    },
    [198] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [199] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(205),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [200] = {
        [ts_sym__function] = SHIFT(18),
        [ts_sym_array] = SHIFT(80),
        [ts_sym_assignment] = SHIFT(81),
        [ts_sym_expression] = SHIFT(201),
        [ts_sym_false] = SHIFT(80),
        [ts_sym_function_call] = SHIFT(81),
        [ts_sym_function_expression] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(94),
        [ts_sym_literal] = SHIFT(81),
        [ts_sym_null] = SHIFT(80),
        [ts_sym_number] = SHIFT(80),
        [ts_sym_object] = SHIFT(80),
        [ts_sym_property_access] = SHIFT(81),
        [ts_sym_string] = SHIFT(80),
        [ts_sym_true] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(97),
        [ts_aux_sym_token4] = SHIFT(204),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [201] = {
        [ts_aux_sym_repeat_helper3] = SHIFT(202),
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_aux_sym_token6] = SHIFT(89),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [202] = {
        [ts_aux_sym_token4] = SHIFT(203),
    },
    [203] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    [204] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    [205] = {
        [ts_sym__for] = SHIFT(206),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(214),
        [ts_sym__var] = SHIFT(218),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(222),
        [ts_sym_expression_statement] = SHIFT(224),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(224),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(224),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(258),
        [ts_sym_statement_block] = SHIFT(224),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(224),
        [ts_aux_sym_token1] = SHIFT(228),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(232),
    },
    [206] = {
        [ts_aux_sym_token3] = SHIFT(207),
    },
    [207] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym__var] = SHIFT(9),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(210),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(210),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [208] = {
        [ts_sym__terminator] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [209] = {
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
    },
    [210] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(211),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [211] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(212),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(256),
    },
    [212] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(213),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [213] = {
        [ts_sym__for] = SHIFT(206),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(214),
        [ts_sym__var] = SHIFT(218),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(222),
        [ts_sym_expression_statement] = SHIFT(224),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(224),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(224),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(255),
        [ts_sym_statement_block] = SHIFT(224),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(224),
        [ts_aux_sym_token1] = SHIFT(228),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(232),
    },
    [214] = {
        [ts_aux_sym_token3] = SHIFT(215),
    },
    [215] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(216),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(254),
    },
    [216] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(217),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [217] = {
        [ts_sym__for] = SHIFT(206),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(214),
        [ts_sym__var] = SHIFT(218),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(222),
        [ts_sym_expression_statement] = SHIFT(224),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(224),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(224),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(225),
        [ts_sym_statement_block] = SHIFT(224),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(224),
        [ts_aux_sym_token1] = SHIFT(228),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(232),
    },
    [218] = {
        [ts_sym_assignment] = SHIFT(219),
        [ts_sym_identifier] = SHIFT(221),
    },
    [219] = {
        [ts_sym__terminator] = SHIFT(220),
    },
    [220] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
    },
    [221] = {
        [ts_sym__terminator] = SHIFT(220),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [222] = {
        [ts_sym__terminator] = SHIFT(223),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [223] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
    },
    [224] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
    },
    [225] = {
        [ts_sym__else] = SHIFT(226),
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
    },
    [226] = {
        [ts_sym__for] = SHIFT(206),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(214),
        [ts_sym__var] = SHIFT(218),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(222),
        [ts_sym_expression_statement] = SHIFT(224),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(224),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(224),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(227),
        [ts_sym_statement_block] = SHIFT(224),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(224),
        [ts_aux_sym_token1] = SHIFT(228),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(232),
    },
    [227] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
    },
    [228] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(229),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = SHIFT(54),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(231),
    },
    [229] = {
        [ts_aux_sym_token2] = SHIFT(230),
    },
    [230] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
    },
    [231] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_repeat_helper5] = SHIFT(178),
        [ts_aux_sym_token2] = SHIFT(230),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [232] = {
        [ts_sym__terminator] = SHIFT(223),
    },
    [233] = {
        [ts_sym_identifier] = SHIFT(234),
    },
    [234] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
    },
    [235] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(236),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
    },
    [236] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(237),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
    },
    [237] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [238] = {
        [ts_sym_identifier] = SHIFT(239),
        [ts_sym_string] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(244),
        [ts_builtin_sym_error] = SHIFT(245),
    },
    [239] = {
        [ts_aux_sym_token8] = SHIFT(240),
    },
    [240] = {
        [ts_sym__function] = SHIFT(43),
        [ts_sym_array] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(101),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_false] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(101),
        [ts_sym_function_expression] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(135),
        [ts_sym_literal] = SHIFT(101),
        [ts_sym_null] = SHIFT(100),
        [ts_sym_number] = SHIFT(100),
        [ts_sym_object] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_string] = SHIFT(100),
        [ts_sym_true] = SHIFT(100),
        [ts_aux_sym_token1] = SHIFT(138),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [241] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(242),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token3] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(128),
        [ts_aux_sym_token7] = SHIFT(133),
    },
    [242] = {
        [ts_aux_sym_token2] = SHIFT(243),
    },
    [243] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
    },
    [244] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
    },
    [245] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(246),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [246] = {
        [ts_aux_sym_token2] = SHIFT(247),
    },
    [247] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
    },
    [248] = {
        [ts_sym__function] = SHIFT(56),
        [ts_sym_array] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(75),
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(75),
        [ts_sym_function_expression] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_literal] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_number] = SHIFT(74),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_aux_sym_token1] = SHIFT(122),
        [ts_aux_sym_token10] = SHIFT(252),
        [ts_aux_sym_token9] = SHIFT(149),
        [ts_builtin_sym_error] = SHIFT(253),
    },
    [249] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(250),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token3] = SHIFT(79),
        [ts_aux_sym_token6] = SHIFT(114),
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [250] = {
        [ts_aux_sym_token10] = SHIFT(251),
    },
    [251] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
    },
    [252] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
    },
    [253] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(250),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token6] = SHIFT(114),
    },
    [254] = {
        [ts_aux_sym_token4] = SHIFT(217),
    },
    [255] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
    },
    [256] = {
        [ts_aux_sym_token4] = SHIFT(213),
    },
    [257] = {
        [ts_sym__terminator] = SHIFT(209),
    },
    [258] = {
        [ts_sym__else] = SHIFT(259),
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
    },
    [259] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(260),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(180),
    },
    [260] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
    },
    [261] = {
        [ts_aux_sym_token4] = SHIFT(205),
    },
    [262] = {
        [ts_aux_sym_token2] = SHIFT(263),
    },
    [263] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    [264] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_token2] = SHIFT(263),
    },
    [265] = {
        [ts_sym_formal_parameters] = SHIFT(266),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [266] = {
        [ts_sym_statement_block] = SHIFT(267),
        [ts_aux_sym_token1] = SHIFT(21),
    },
    [267] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    [268] = {
        [ts_aux_sym_repeat_helper3] = SHIFT(269),
        [ts_aux_sym_token3] = SHIFT(85),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_aux_sym_token6] = SHIFT(89),
        [ts_aux_sym_token7] = SHIFT(92),
    },
    [269] = {
        [ts_aux_sym_token4] = SHIFT(270),
    },
    [270] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
    },
    [271] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
    },
    [272] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(273),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [273] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(274),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(277),
    },
    [274] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(275),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [275] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(276),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(180),
    },
    [276] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
    },
    [277] = {
        [ts_aux_sym_token4] = SHIFT(275),
    },
    [278] = {
        [ts_aux_sym_token2] = SHIFT(279),
    },
    [279] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
    },
    [280] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_token2] = SHIFT(279),
    },
    [281] = {
        [ts_sym_formal_parameters] = SHIFT(282),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [282] = {
        [ts_sym_statement_block] = SHIFT(283),
        [ts_aux_sym_token1] = SHIFT(6),
    },
    [283] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
    },
    [284] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(285),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [285] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(286),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(337),
    },
    [286] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(287),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [287] = {
        [ts_sym__for] = SHIFT(1),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(288),
        [ts_sym__var] = SHIFT(322),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_expression_statement] = SHIFT(328),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(328),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(328),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(336),
        [ts_sym_statement_block] = SHIFT(328),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(328),
        [ts_aux_sym_token1] = SHIFT(330),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(334),
    },
    [288] = {
        [ts_aux_sym_token3] = SHIFT(289),
    },
    [289] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(335),
    },
    [290] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(291),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [291] = {
        [ts_sym__for] = SHIFT(292),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(298),
        [ts_sym__var] = SHIFT(302),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_expression_statement] = SHIFT(308),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(308),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(308),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(320),
        [ts_sym_statement_block] = SHIFT(308),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(308),
        [ts_aux_sym_token1] = SHIFT(312),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(316),
    },
    [292] = {
        [ts_aux_sym_token3] = SHIFT(293),
    },
    [293] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym__var] = SHIFT(9),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(294),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [294] = {
        [ts_sym__function] = SHIFT(3),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_expression_statement] = SHIFT(295),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(40),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(257),
    },
    [295] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(319),
    },
    [296] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(297),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [297] = {
        [ts_sym__for] = SHIFT(292),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(298),
        [ts_sym__var] = SHIFT(302),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_expression_statement] = SHIFT(308),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(308),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(308),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(318),
        [ts_sym_statement_block] = SHIFT(308),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(308),
        [ts_aux_sym_token1] = SHIFT(312),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(316),
    },
    [298] = {
        [ts_aux_sym_token3] = SHIFT(299),
    },
    [299] = {
        [ts_sym__function] = SHIFT(24),
        [ts_sym_array] = SHIFT(197),
        [ts_sym_assignment] = SHIFT(198),
        [ts_sym_expression] = SHIFT(300),
        [ts_sym_false] = SHIFT(197),
        [ts_sym_function_call] = SHIFT(198),
        [ts_sym_function_expression] = SHIFT(198),
        [ts_sym_identifier] = SHIFT(235),
        [ts_sym_literal] = SHIFT(198),
        [ts_sym_null] = SHIFT(197),
        [ts_sym_number] = SHIFT(197),
        [ts_sym_object] = SHIFT(197),
        [ts_sym_property_access] = SHIFT(198),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_true] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(238),
        [ts_aux_sym_token9] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(317),
    },
    [300] = {
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token4] = SHIFT(301),
        [ts_aux_sym_token7] = SHIFT(233),
    },
    [301] = {
        [ts_sym__for] = SHIFT(292),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(298),
        [ts_sym__var] = SHIFT(302),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_expression_statement] = SHIFT(308),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(308),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(308),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(309),
        [ts_sym_statement_block] = SHIFT(308),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(308),
        [ts_aux_sym_token1] = SHIFT(312),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(316),
    },
    [302] = {
        [ts_sym_assignment] = SHIFT(303),
        [ts_sym_identifier] = SHIFT(305),
    },
    [303] = {
        [ts_sym__terminator] = SHIFT(304),
    },
    [304] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
    },
    [305] = {
        [ts_sym__terminator] = SHIFT(304),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [306] = {
        [ts_sym__terminator] = SHIFT(307),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [307] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
    },
    [308] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
    },
    [309] = {
        [ts_sym__else] = SHIFT(310),
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
    },
    [310] = {
        [ts_sym__for] = SHIFT(292),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(298),
        [ts_sym__var] = SHIFT(302),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_expression_statement] = SHIFT(308),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(308),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(308),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(311),
        [ts_sym_statement_block] = SHIFT(308),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(308),
        [ts_aux_sym_token1] = SHIFT(312),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(316),
    },
    [311] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
    },
    [312] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(313),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = SHIFT(54),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(315),
    },
    [313] = {
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [314] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
    },
    [315] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_repeat_helper5] = SHIFT(178),
        [ts_aux_sym_token2] = SHIFT(314),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [316] = {
        [ts_sym__terminator] = SHIFT(307),
    },
    [317] = {
        [ts_aux_sym_token4] = SHIFT(301),
    },
    [318] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
    },
    [319] = {
        [ts_aux_sym_token4] = SHIFT(297),
    },
    [320] = {
        [ts_sym__else] = SHIFT(321),
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
    },
    [321] = {
        [ts_sym__for] = SHIFT(1),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(288),
        [ts_sym__var] = SHIFT(322),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_expression_statement] = SHIFT(328),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(328),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(328),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(329),
        [ts_sym_statement_block] = SHIFT(328),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(328),
        [ts_aux_sym_token1] = SHIFT(330),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(334),
    },
    [322] = {
        [ts_sym_assignment] = SHIFT(323),
        [ts_sym_identifier] = SHIFT(325),
    },
    [323] = {
        [ts_sym__terminator] = SHIFT(324),
    },
    [324] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
    },
    [325] = {
        [ts_sym__terminator] = SHIFT(324),
        [ts_aux_sym_token5] = SHIFT(13),
    },
    [326] = {
        [ts_sym__terminator] = SHIFT(327),
        [ts_aux_sym_token3] = SHIFT(17),
        [ts_aux_sym_token7] = SHIFT(34),
    },
    [327] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
    },
    [328] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
    },
    [329] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
    },
    [330] = {
        [ts_sym__for] = SHIFT(7),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(22),
        [ts_sym__var] = SHIFT(28),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_expression_statement] = SHIFT(36),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(36),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(36),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(47),
        [ts_sym_statement_block] = SHIFT(36),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(36),
        [ts_aux_sym_repeat_helper2] = SHIFT(331),
        [ts_aux_sym_token1] = SHIFT(49),
        [ts_aux_sym_token2] = SHIFT(54),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_error] = SHIFT(333),
    },
    [331] = {
        [ts_aux_sym_token2] = SHIFT(332),
    },
    [332] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
    },
    [333] = {
        [ts_sym__terminator] = SHIFT(33),
        [ts_aux_sym_repeat_helper5] = SHIFT(178),
        [ts_aux_sym_token2] = SHIFT(332),
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [334] = {
        [ts_sym__terminator] = SHIFT(327),
    },
    [335] = {
        [ts_aux_sym_token4] = SHIFT(291),
    },
    [336] = {
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
    },
    [337] = {
        [ts_aux_sym_token4] = SHIFT(287),
    },
    [338] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [339] = {
        [ts_sym__for] = SHIFT(1),
        [ts_sym__function] = SHIFT(3),
        [ts_sym__if] = SHIFT(288),
        [ts_sym__var] = SHIFT(322),
        [ts_sym_array] = SHIFT(14),
        [ts_sym_assignment] = SHIFT(15),
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_expression_statement] = SHIFT(328),
        [ts_sym_false] = SHIFT(14),
        [ts_sym_for_statement] = SHIFT(328),
        [ts_sym_function_call] = SHIFT(15),
        [ts_sym_function_expression] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(37),
        [ts_sym_if_statement] = SHIFT(328),
        [ts_sym_literal] = SHIFT(15),
        [ts_sym_null] = SHIFT(14),
        [ts_sym_number] = SHIFT(14),
        [ts_sym_object] = SHIFT(14),
        [ts_sym_property_access] = SHIFT(15),
        [ts_sym_statement] = SHIFT(339),
        [ts_sym_statement_block] = SHIFT(328),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_true] = SHIFT(14),
        [ts_sym_var_declaration] = SHIFT(328),
        [ts_aux_sym_repeat_helper1] = SHIFT(340),
        [ts_aux_sym_token1] = SHIFT(330),
        [ts_aux_sym_token9] = SHIFT(55),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_builtin_sym_error] = SHIFT(334),
    },
    [340] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    [341] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
