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
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
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
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\n')
                ADVANCE(1);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 4:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 5:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(5);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 6:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(7);
            if (lookahead == '\\')
                ADVANCE(9);
            LEX_ERROR();
        case 7:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(7);
            if (lookahead == '\"')
                ADVANCE(8);
            if (lookahead == '\\')
                ADVANCE(9);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_sym_string);
        case 9:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(7);
            if (lookahead == '\"')
                ADVANCE(10);
            if (lookahead == '\\')
                ADVANCE(9);
            LEX_ERROR();
        case 10:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(7);
            if (lookahead == '\"')
                ADVANCE(8);
            if (lookahead == '\\')
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_string);
        case 11:
            if (lookahead == '.')
                ADVANCE(12);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_number);
        case 12:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_number);
        case 14:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 15:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 16:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'a')
                ADVANCE(17);
            if (lookahead == 'u')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 17:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 18:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 's')
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'e')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_false);
        case 21:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'n')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 22:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'c')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 23:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 't')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 24:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'i')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'o')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'n')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__function);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'u')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_null);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'r')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'u')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'e')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_true);
        case 36:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 37:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '\n')
                ADVANCE(38);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 38:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '\n')
                ADVANCE(38);
            if (lookahead == ';')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 39:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(39);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            LEX_ERROR();
        case 40:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 41:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 42:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(42);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '.')
                ADVANCE(3);
            LEX_ERROR();
        case 43:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(43);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'a')
                ADVANCE(17);
            if (lookahead == 'o')
                ADVANCE(45);
            if (lookahead == 'u')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'r')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__for);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'f')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__if);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'a')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'r')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__var);
        case 52:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 53:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(53);
            if (lookahead == '\n')
                ADVANCE(54);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            LEX_ERROR();
        case 54:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(53);
            if (lookahead == '\n')
                ADVANCE(54);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 56:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            LEX_ERROR();
        case 57:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(57);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 58:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(58);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 59:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(59);
            if (lookahead == '\n')
                ADVANCE(60);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            LEX_ERROR();
        case 60:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(59);
            if (lookahead == '\n')
                ADVANCE(60);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 61:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 62:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == '\n')
                ADVANCE(63);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            LEX_ERROR();
        case 63:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == '\n')
                ADVANCE(63);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 64:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 66:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '\n')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 67:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '\n')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '}')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 68:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == ')')
                ADVANCE(40);
            LEX_ERROR();
        case 70:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(41);
            LEX_ERROR();
        case 71:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == ')')
                ADVANCE(40);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '(')
                ADVANCE(2);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            LEX_ERROR();
        case 74:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 75:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == ']')
                ADVANCE(65);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == ':')
                ADVANCE(61);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '\"')
                ADVANCE(6);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(55);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '\"')
                ADVANCE(6);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(55);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == ')')
                ADVANCE(40);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 84:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(55);
            LEX_ERROR();
        case 85:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '\n')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 86:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '\n')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '}')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 87:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == '\n')
                ADVANCE(88);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            LEX_ERROR();
        case 88:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == '\n')
                ADVANCE(88);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 89:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(90);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 90:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 91:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 's')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 92:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == 'e')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 93:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__else);
        case 94:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 95:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '.')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(55);
            LEX_ERROR();
        case 96:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(98);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(97);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(90);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 99:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(98);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '\"')
                ADVANCE(6);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 100:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(98);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(98);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '\n')
                ADVANCE(102);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == ']')
                ADVANCE(65);
            if (lookahead == 'e')
                ADVANCE(90);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(98);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '\n')
                ADVANCE(102);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == ']')
                ADVANCE(65);
            if (lookahead == 'e')
                ADVANCE(90);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__terminator);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(98);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '\n')
                ADVANCE(102);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '(')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(41);
            if (lookahead == '.')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            if (lookahead == ':')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(55);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(14);
            if (lookahead == '[')
                ADVANCE(15);
            if (lookahead == ']')
                ADVANCE(65);
            if (lookahead == 'e')
                ADVANCE(90);
            if (lookahead == 'f')
                ADVANCE(44);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'n')
                ADVANCE(28);
            if (lookahead == 't')
                ADVANCE(32);
            if (lookahead == 'v')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(52);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 99,
    [1] = 72,
    [2] = 96,
    [3] = 73,
    [4] = 68,
    [5] = 0,
    [6] = 43,
    [7] = 72,
    [8] = 96,
    [9] = 56,
    [10] = 37,
    [11] = 5,
    [12] = 53,
    [13] = 5,
    [14] = 0,
    [15] = 0,
    [16] = 0,
    [17] = 83,
    [18] = 73,
    [19] = 68,
    [20] = 39,
    [21] = 43,
    [22] = 72,
    [23] = 5,
    [24] = 73,
    [25] = 68,
    [26] = 42,
    [27] = 43,
    [28] = 56,
    [29] = 37,
    [30] = 43,
    [31] = 53,
    [32] = 0,
    [33] = 43,
    [34] = 56,
    [35] = 0,
    [36] = 43,
    [37] = 87,
    [38] = 5,
    [39] = 0,
    [40] = 79,
    [41] = 77,
    [42] = 5,
    [43] = 73,
    [44] = 68,
    [45] = 57,
    [46] = 43,
    [47] = 43,
    [48] = 58,
    [49] = 43,
    [50] = 59,
    [51] = 62,
    [52] = 58,
    [53] = 43,
    [54] = 0,
    [55] = 76,
    [56] = 73,
    [57] = 68,
    [58] = 64,
    [59] = 43,
    [60] = 58,
    [61] = 64,
    [62] = 66,
    [63] = 72,
    [64] = 68,
    [65] = 64,
    [66] = 71,
    [67] = 70,
    [68] = 69,
    [69] = 68,
    [70] = 56,
    [71] = 70,
    [72] = 69,
    [73] = 68,
    [74] = 64,
    [75] = 64,
    [76] = 64,
    [77] = 74,
    [78] = 0,
    [79] = 83,
    [80] = 39,
    [81] = 39,
    [82] = 39,
    [83] = 69,
    [84] = 64,
    [85] = 83,
    [86] = 39,
    [87] = 69,
    [88] = 39,
    [89] = 5,
    [90] = 39,
    [91] = 69,
    [92] = 56,
    [93] = 39,
    [94] = 84,
    [95] = 5,
    [96] = 39,
    [97] = 79,
    [98] = 77,
    [99] = 5,
    [100] = 57,
    [101] = 57,
    [102] = 57,
    [103] = 58,
    [104] = 39,
    [105] = 83,
    [106] = 39,
    [107] = 69,
    [108] = 57,
    [109] = 57,
    [110] = 76,
    [111] = 64,
    [112] = 74,
    [113] = 39,
    [114] = 5,
    [115] = 64,
    [116] = 74,
    [117] = 56,
    [118] = 64,
    [119] = 82,
    [120] = 5,
    [121] = 64,
    [122] = 79,
    [123] = 77,
    [124] = 5,
    [125] = 57,
    [126] = 58,
    [127] = 64,
    [128] = 81,
    [129] = 77,
    [130] = 5,
    [131] = 57,
    [132] = 58,
    [133] = 56,
    [134] = 57,
    [135] = 80,
    [136] = 5,
    [137] = 57,
    [138] = 79,
    [139] = 77,
    [140] = 5,
    [141] = 57,
    [142] = 58,
    [143] = 57,
    [144] = 76,
    [145] = 64,
    [146] = 74,
    [147] = 57,
    [148] = 57,
    [149] = 76,
    [150] = 64,
    [151] = 74,
    [152] = 64,
    [153] = 64,
    [154] = 75,
    [155] = 75,
    [156] = 57,
    [157] = 78,
    [158] = 58,
    [159] = 57,
    [160] = 78,
    [161] = 58,
    [162] = 64,
    [163] = 78,
    [164] = 58,
    [165] = 64,
    [166] = 75,
    [167] = 39,
    [168] = 75,
    [169] = 39,
    [170] = 78,
    [171] = 58,
    [172] = 39,
    [173] = 39,
    [174] = 64,
    [175] = 0,
    [176] = 75,
    [177] = 85,
    [178] = 58,
    [179] = 0,
    [180] = 37,
    [181] = 58,
    [182] = 57,
    [183] = 66,
    [184] = 72,
    [185] = 68,
    [186] = 57,
    [187] = 57,
    [188] = 58,
    [189] = 0,
    [190] = 78,
    [191] = 58,
    [192] = 42,
    [193] = 66,
    [194] = 72,
    [195] = 68,
    [196] = 42,
    [197] = 42,
    [198] = 42,
    [199] = 42,
    [200] = 83,
    [201] = 39,
    [202] = 69,
    [203] = 42,
    [204] = 42,
    [205] = 94,
    [206] = 72,
    [207] = 96,
    [208] = 0,
    [209] = 5,
    [210] = 5,
    [211] = 5,
    [212] = 42,
    [213] = 94,
    [214] = 72,
    [215] = 5,
    [216] = 42,
    [217] = 94,
    [218] = 56,
    [219] = 37,
    [220] = 89,
    [221] = 53,
    [222] = 0,
    [223] = 89,
    [224] = 89,
    [225] = 89,
    [226] = 94,
    [227] = 89,
    [228] = 43,
    [229] = 58,
    [230] = 89,
    [231] = 85,
    [232] = 37,
    [233] = 56,
    [234] = 42,
    [235] = 95,
    [236] = 5,
    [237] = 42,
    [238] = 79,
    [239] = 77,
    [240] = 5,
    [241] = 57,
    [242] = 58,
    [243] = 42,
    [244] = 42,
    [245] = 78,
    [246] = 58,
    [247] = 42,
    [248] = 76,
    [249] = 64,
    [250] = 74,
    [251] = 42,
    [252] = 42,
    [253] = 75,
    [254] = 69,
    [255] = 89,
    [256] = 69,
    [257] = 37,
    [258] = 89,
    [259] = 94,
    [260] = 43,
    [261] = 69,
    [262] = 58,
    [263] = 39,
    [264] = 66,
    [265] = 72,
    [266] = 68,
    [267] = 39,
    [268] = 39,
    [269] = 69,
    [270] = 0,
    [271] = 0,
    [272] = 5,
    [273] = 5,
    [274] = 42,
    [275] = 94,
    [276] = 43,
    [277] = 69,
    [278] = 58,
    [279] = 0,
    [280] = 66,
    [281] = 72,
    [282] = 68,
    [283] = 0,
    [284] = 5,
    [285] = 5,
    [286] = 42,
    [287] = 94,
    [288] = 72,
    [289] = 5,
    [290] = 42,
    [291] = 94,
    [292] = 72,
    [293] = 96,
    [294] = 5,
    [295] = 5,
    [296] = 42,
    [297] = 94,
    [298] = 72,
    [299] = 5,
    [300] = 42,
    [301] = 94,
    [302] = 56,
    [303] = 37,
    [304] = 97,
    [305] = 53,
    [306] = 0,
    [307] = 97,
    [308] = 97,
    [309] = 97,
    [310] = 94,
    [311] = 97,
    [312] = 43,
    [313] = 58,
    [314] = 97,
    [315] = 85,
    [316] = 37,
    [317] = 69,
    [318] = 97,
    [319] = 69,
    [320] = 97,
    [321] = 94,
    [322] = 56,
    [323] = 37,
    [324] = 99,
    [325] = 53,
    [326] = 0,
    [327] = 99,
    [328] = 99,
    [329] = 99,
    [330] = 43,
    [331] = 58,
    [332] = 99,
    [333] = 85,
    [334] = 37,
    [335] = 69,
    [336] = 99,
    [337] = 69,
    [338] = 100,
    [339] = 99,
    [340] = 100,
    [341] = 100,
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
