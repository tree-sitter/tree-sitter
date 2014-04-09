#include "tree_sitter/parser.h"

#define STATE_COUNT 604
#define SYMBOL_COUNT 55

enum {
    ts_sym__break = 2,
    ts_sym__case = 3,
    ts_sym__default = 4,
    ts_sym__else = 5,
    ts_sym__for = 6,
    ts_sym__function = 7,
    ts_sym__if = 8,
    ts_sym__switch = 9,
    ts_sym__terminator = 10,
    ts_sym__var = 11,
    ts_sym_array = 12,
    ts_sym_assignment = 13,
    ts_sym_break_statement = 14,
    ts_sym_expression = 15,
    ts_sym_expression_statement = 16,
    ts_sym_false = 17,
    ts_sym_for_statement = 18,
    ts_sym_formal_parameters = 19,
    ts_sym_function_call = 20,
    ts_sym_function_expression = 21,
    ts_sym_identifier = 22,
    ts_sym_if_statement = 23,
    ts_sym_literal = 24,
    ts_sym_null = 25,
    ts_sym_number = 26,
    ts_sym_object = 27,
    ts_sym_program = 28,
    ts_sym_property_access = 29,
    ts_sym_statement = 30,
    ts_sym_statement_block = 31,
    ts_sym_string = 32,
    ts_sym_switch_case = 33,
    ts_sym_switch_statement = 34,
    ts_sym_true = 35,
    ts_sym_var_declaration = 36,
    ts_aux_sym_repeat_helper1 = 37,
    ts_aux_sym_repeat_helper2 = 38,
    ts_aux_sym_repeat_helper3 = 39,
    ts_aux_sym_repeat_helper4 = 40,
    ts_aux_sym_repeat_helper5 = 41,
    ts_aux_sym_repeat_helper6 = 42,
    ts_aux_sym_repeat_helper7 = 43,
    ts_aux_sym_repeat_helper8 = 44,
    ts_aux_sym_token1 = 45,
    ts_aux_sym_token10 = 46,
    ts_aux_sym_token2 = 47,
    ts_aux_sym_token3 = 48,
    ts_aux_sym_token4 = 49,
    ts_aux_sym_token5 = 50,
    ts_aux_sym_token6 = 51,
    ts_aux_sym_token7 = 52,
    ts_aux_sym_token8 = 53,
    ts_aux_sym_token9 = 54,
};

SYMBOL_NAMES = {
    [ts_sym__break] = "_break",
    [ts_sym__case] = "_case",
    [ts_sym__default] = "_default",
    [ts_sym__else] = "_else",
    [ts_sym__for] = "_for",
    [ts_sym__function] = "_function",
    [ts_sym__if] = "_if",
    [ts_sym__switch] = "_switch",
    [ts_sym__terminator] = "_terminator",
    [ts_sym__var] = "_var",
    [ts_sym_array] = "array",
    [ts_sym_assignment] = "assignment",
    [ts_sym_break_statement] = "break_statement",
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
    [ts_sym_switch_case] = "switch_case",
    [ts_sym_switch_statement] = "switch_statement",
    [ts_sym_true] = "true",
    [ts_sym_var_declaration] = "var_declaration",
    [ts_aux_sym_repeat_helper1] = "repeat_helper1",
    [ts_aux_sym_repeat_helper2] = "repeat_helper2",
    [ts_aux_sym_repeat_helper3] = "repeat_helper3",
    [ts_aux_sym_repeat_helper4] = "repeat_helper4",
    [ts_aux_sym_repeat_helper5] = "repeat_helper5",
    [ts_aux_sym_repeat_helper6] = "repeat_helper6",
    [ts_aux_sym_repeat_helper7] = "repeat_helper7",
    [ts_aux_sym_repeat_helper8] = "repeat_helper8",
    [ts_aux_sym_token1] = "'{'",
    [ts_aux_sym_token10] = "']'",
    [ts_aux_sym_token2] = "'}'",
    [ts_aux_sym_token3] = "'('",
    [ts_aux_sym_token4] = "')'",
    [ts_aux_sym_token5] = "':'",
    [ts_aux_sym_token6] = "'='",
    [ts_aux_sym_token7] = "','",
    [ts_aux_sym_token8] = "'.'",
    [ts_aux_sym_token9] = "'['",
    [ts_builtin_sym_end] = "EOF",
    [ts_builtin_sym_error] = "ERROR",
};

HIDDEN_SYMBOLS = {
    [ts_sym__break] = 1,
    [ts_sym__case] = 1,
    [ts_sym__default] = 1,
    [ts_sym__else] = 1,
    [ts_sym__for] = 1,
    [ts_sym__function] = 1,
    [ts_sym__if] = 1,
    [ts_sym__switch] = 1,
    [ts_sym__terminator] = 1,
    [ts_sym__var] = 1,
    [ts_aux_sym_repeat_helper1] = 1,
    [ts_aux_sym_repeat_helper2] = 1,
    [ts_aux_sym_repeat_helper3] = 1,
    [ts_aux_sym_repeat_helper4] = 1,
    [ts_aux_sym_repeat_helper5] = 1,
    [ts_aux_sym_repeat_helper6] = 1,
    [ts_aux_sym_repeat_helper7] = 1,
    [ts_aux_sym_repeat_helper8] = 1,
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
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(5);
            LEX_ERROR();
        case 3:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_sym_string);
        case 5:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(5);
            LEX_ERROR();
        case 6:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym_string);
        case 7:
            if (lookahead == '.')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym_number);
        case 8:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_number);
        case 10:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 11:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 12:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'r')
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 13:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 14:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 15:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'k')
                ADVANCE(16);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 16:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__break);
        case 17:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(18);
            if (lookahead == 'o')
                ADVANCE(22);
            if (lookahead == 'u')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 18:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
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
                ADVANCE(10);
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
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 21:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_false);
        case 22:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'r')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 23:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__for);
        case 24:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'c')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 't')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'i')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'o')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__function);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'f')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__if);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'u')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'l')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'l')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_null);
        case 37:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'v') ||
                ('x' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'w')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'i')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 't')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'c')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'h')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__switch);
        case 43:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'r')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'u')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_true);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'r')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__var);
        case 50:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 51:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(51);
            if (lookahead == '\n')
                ADVANCE(52);
            if (lookahead == ';')
                ADVANCE(53);
            LEX_ERROR();
        case 52:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(51);
            if (lookahead == '\n')
                ADVANCE(52);
            if (lookahead == ';')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 53:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 54:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(54);
            if (lookahead == '\n')
                ADVANCE(55);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 55:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(54);
            if (lookahead == '\n')
                ADVANCE(55);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '[')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 56:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 58:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(58);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 60:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(60);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 61:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(61);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 63:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 64:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 65:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (lookahead == ')')
                ADVANCE(62);
            LEX_ERROR();
        case 66:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 67:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 68:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 71:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '\n')
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '\n')
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 74:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 75:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(62);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(77);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 77:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(18);
            if (lookahead == 'u')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 78:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(77);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == ':')
                ADVANCE(84);
            LEX_ERROR();
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 85:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 86:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '\"')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 87:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 88:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            if (lookahead == 'f')
                ADVANCE(77);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 89:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == '\"')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 90:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '\n')
                ADVANCE(91);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 91:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '\n')
                ADVANCE(91);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 92:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '\n')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 93:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '\n')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '[')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 94:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '\n')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 95:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '\n')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '\n')
                ADVANCE(97);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '\n')
                ADVANCE(97);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 98:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(98);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 99:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == ',')
                ADVANCE(64);
            LEX_ERROR();
        case 100:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == ')')
                ADVANCE(62);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '(')
                ADVANCE(56);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '(')
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 103:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 104:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 105:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(106);
            if (lookahead == 'd')
                ADVANCE(110);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 106:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 107:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 's')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 108:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 109:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__case);
        case 110:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 111:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'f')
                ADVANCE(112);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 112:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 113:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'u')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 114:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'l')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 115:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 't')
                ADVANCE(116);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 116:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__default);
        case 117:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(106);
            if (lookahead == 'd')
                ADVANCE(110);
            if (lookahead == 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 118:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'l')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 119:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 's')
                ADVANCE(120);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 120:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 121:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__else);
        case 122:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == 'c')
                ADVANCE(123);
            if (lookahead == 'd')
                ADVANCE(127);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 123:
            if (lookahead == 'a')
                ADVANCE(124);
            LEX_ERROR();
        case 124:
            if (lookahead == 's')
                ADVANCE(125);
            LEX_ERROR();
        case 125:
            if (lookahead == 'e')
                ADVANCE(126);
            LEX_ERROR();
        case 126:
            ACCEPT_TOKEN(ts_sym__case);
        case 127:
            if (lookahead == 'e')
                ADVANCE(128);
            LEX_ERROR();
        case 128:
            if (lookahead == 'f')
                ADVANCE(129);
            LEX_ERROR();
        case 129:
            if (lookahead == 'a')
                ADVANCE(130);
            LEX_ERROR();
        case 130:
            if (lookahead == 'u')
                ADVANCE(131);
            LEX_ERROR();
        case 131:
            if (lookahead == 'l')
                ADVANCE(132);
            LEX_ERROR();
        case 132:
            if (lookahead == 't')
                ADVANCE(133);
            LEX_ERROR();
        case 133:
            ACCEPT_TOKEN(ts_sym__default);
        case 134:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(77);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == '=')
                ADVANCE(67);
            if (lookahead == '[')
                ADVANCE(11);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(106);
            if (lookahead == 'd')
                ADVANCE(110);
            if (lookahead == 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(106);
            if (lookahead == 'd')
                ADVANCE(110);
            if (lookahead == 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__terminator);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(62);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(67);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(11);
            if (lookahead == ']')
                ADVANCE(70);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(106);
            if (lookahead == 'd')
                ADVANCE(110);
            if (lookahead == 'e')
                ADVANCE(118);
            if (lookahead == 'f')
                ADVANCE(17);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(37);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 0,
    [1] = 51,
    [2] = 0,
    [3] = 101,
    [4] = 136,
    [5] = 102,
    [6] = 98,
    [7] = 54,
    [8] = 58,
    [9] = 51,
    [10] = 58,
    [11] = 101,
    [12] = 136,
    [13] = 82,
    [14] = 102,
    [15] = 98,
    [16] = 60,
    [17] = 58,
    [18] = 101,
    [19] = 82,
    [20] = 102,
    [21] = 98,
    [22] = 61,
    [23] = 58,
    [24] = 101,
    [25] = 82,
    [26] = 61,
    [27] = 61,
    [28] = 61,
    [29] = 76,
    [30] = 102,
    [31] = 98,
    [32] = 63,
    [33] = 58,
    [34] = 82,
    [35] = 60,
    [36] = 54,
    [37] = 58,
    [38] = 60,
    [39] = 76,
    [40] = 63,
    [41] = 63,
    [42] = 63,
    [43] = 65,
    [44] = 60,
    [45] = 76,
    [46] = 63,
    [47] = 65,
    [48] = 63,
    [49] = 82,
    [50] = 63,
    [51] = 65,
    [52] = 68,
    [53] = 66,
    [54] = 82,
    [55] = 102,
    [56] = 98,
    [57] = 69,
    [58] = 58,
    [59] = 54,
    [60] = 54,
    [61] = 58,
    [62] = 54,
    [63] = 58,
    [64] = 76,
    [65] = 63,
    [66] = 65,
    [67] = 54,
    [68] = 66,
    [69] = 82,
    [70] = 63,
    [71] = 86,
    [72] = 83,
    [73] = 82,
    [74] = 102,
    [75] = 98,
    [76] = 71,
    [77] = 58,
    [78] = 72,
    [79] = 82,
    [80] = 54,
    [81] = 68,
    [82] = 72,
    [83] = 82,
    [84] = 69,
    [85] = 69,
    [86] = 69,
    [87] = 72,
    [88] = 76,
    [89] = 63,
    [90] = 65,
    [91] = 69,
    [92] = 69,
    [93] = 88,
    [94] = 102,
    [95] = 98,
    [96] = 74,
    [97] = 58,
    [98] = 58,
    [99] = 75,
    [100] = 58,
    [101] = 90,
    [102] = 82,
    [103] = 71,
    [104] = 71,
    [105] = 71,
    [106] = 75,
    [107] = 54,
    [108] = 76,
    [109] = 63,
    [110] = 65,
    [111] = 71,
    [112] = 71,
    [113] = 89,
    [114] = 83,
    [115] = 82,
    [116] = 71,
    [117] = 75,
    [118] = 68,
    [119] = 78,
    [120] = 82,
    [121] = 69,
    [122] = 78,
    [123] = 68,
    [124] = 79,
    [125] = 82,
    [126] = 69,
    [127] = 79,
    [128] = 79,
    [129] = 82,
    [130] = 69,
    [131] = 86,
    [132] = 83,
    [133] = 82,
    [134] = 71,
    [135] = 75,
    [136] = 69,
    [137] = 78,
    [138] = 82,
    [139] = 71,
    [140] = 86,
    [141] = 83,
    [142] = 82,
    [143] = 71,
    [144] = 75,
    [145] = 71,
    [146] = 88,
    [147] = 74,
    [148] = 74,
    [149] = 74,
    [150] = 80,
    [151] = 71,
    [152] = 76,
    [153] = 63,
    [154] = 65,
    [155] = 74,
    [156] = 74,
    [157] = 82,
    [158] = 74,
    [159] = 80,
    [160] = 68,
    [161] = 81,
    [162] = 82,
    [163] = 69,
    [164] = 81,
    [165] = 88,
    [166] = 74,
    [167] = 80,
    [168] = 69,
    [169] = 81,
    [170] = 82,
    [171] = 74,
    [172] = 86,
    [173] = 83,
    [174] = 82,
    [175] = 71,
    [176] = 75,
    [177] = 74,
    [178] = 74,
    [179] = 85,
    [180] = 75,
    [181] = 74,
    [182] = 88,
    [183] = 74,
    [184] = 80,
    [185] = 74,
    [186] = 74,
    [187] = 87,
    [188] = 69,
    [189] = 87,
    [190] = 87,
    [191] = 71,
    [192] = 87,
    [193] = 71,
    [194] = 85,
    [195] = 75,
    [196] = 71,
    [197] = 69,
    [198] = 85,
    [199] = 75,
    [200] = 69,
    [201] = 85,
    [202] = 75,
    [203] = 92,
    [204] = 75,
    [205] = 58,
    [206] = 54,
    [207] = 88,
    [208] = 74,
    [209] = 80,
    [210] = 54,
    [211] = 54,
    [212] = 87,
    [213] = 94,
    [214] = 75,
    [215] = 54,
    [216] = 51,
    [217] = 75,
    [218] = 74,
    [219] = 96,
    [220] = 101,
    [221] = 98,
    [222] = 74,
    [223] = 100,
    [224] = 99,
    [225] = 65,
    [226] = 98,
    [227] = 68,
    [228] = 99,
    [229] = 65,
    [230] = 98,
    [231] = 74,
    [232] = 80,
    [233] = 63,
    [234] = 63,
    [235] = 87,
    [236] = 86,
    [237] = 83,
    [238] = 85,
    [239] = 75,
    [240] = 71,
    [241] = 96,
    [242] = 101,
    [243] = 98,
    [244] = 71,
    [245] = 71,
    [246] = 75,
    [247] = 63,
    [248] = 63,
    [249] = 85,
    [250] = 75,
    [251] = 63,
    [252] = 54,
    [253] = 75,
    [254] = 69,
    [255] = 96,
    [256] = 101,
    [257] = 98,
    [258] = 69,
    [259] = 69,
    [260] = 66,
    [261] = 63,
    [262] = 60,
    [263] = 68,
    [264] = 103,
    [265] = 82,
    [266] = 69,
    [267] = 103,
    [268] = 60,
    [269] = 72,
    [270] = 103,
    [271] = 86,
    [272] = 83,
    [273] = 82,
    [274] = 71,
    [275] = 75,
    [276] = 60,
    [277] = 60,
    [278] = 85,
    [279] = 75,
    [280] = 60,
    [281] = 88,
    [282] = 74,
    [283] = 80,
    [284] = 60,
    [285] = 60,
    [286] = 87,
    [287] = 75,
    [288] = 63,
    [289] = 96,
    [290] = 101,
    [291] = 98,
    [292] = 63,
    [293] = 63,
    [294] = 65,
    [295] = 61,
    [296] = 61,
    [297] = 98,
    [298] = 122,
    [299] = 82,
    [300] = 102,
    [301] = 98,
    [302] = 104,
    [303] = 58,
    [304] = 75,
    [305] = 104,
    [306] = 96,
    [307] = 101,
    [308] = 98,
    [309] = 104,
    [310] = 104,
    [311] = 104,
    [312] = 104,
    [313] = 76,
    [314] = 63,
    [315] = 65,
    [316] = 104,
    [317] = 104,
    [318] = 105,
    [319] = 51,
    [320] = 105,
    [321] = 101,
    [322] = 136,
    [323] = 54,
    [324] = 82,
    [325] = 82,
    [326] = 82,
    [327] = 61,
    [328] = 135,
    [329] = 101,
    [330] = 82,
    [331] = 61,
    [332] = 135,
    [333] = 51,
    [334] = 117,
    [335] = 101,
    [336] = 136,
    [337] = 82,
    [338] = 82,
    [339] = 61,
    [340] = 135,
    [341] = 101,
    [342] = 82,
    [343] = 61,
    [344] = 135,
    [345] = 101,
    [346] = 82,
    [347] = 61,
    [348] = 98,
    [349] = 122,
    [350] = 83,
    [351] = 105,
    [352] = 101,
    [353] = 82,
    [354] = 61,
    [355] = 98,
    [356] = 122,
    [357] = 122,
    [358] = 75,
    [359] = 75,
    [360] = 105,
    [361] = 68,
    [362] = 134,
    [363] = 82,
    [364] = 69,
    [365] = 134,
    [366] = 134,
    [367] = 82,
    [368] = 61,
    [369] = 86,
    [370] = 83,
    [371] = 82,
    [372] = 71,
    [373] = 75,
    [374] = 61,
    [375] = 61,
    [376] = 85,
    [377] = 75,
    [378] = 61,
    [379] = 88,
    [380] = 74,
    [381] = 80,
    [382] = 61,
    [383] = 61,
    [384] = 87,
    [385] = 65,
    [386] = 82,
    [387] = 54,
    [388] = 105,
    [389] = 72,
    [390] = 105,
    [391] = 54,
    [392] = 105,
    [393] = 105,
    [394] = 122,
    [395] = 58,
    [396] = 75,
    [397] = 105,
    [398] = 94,
    [399] = 51,
    [400] = 122,
    [401] = 75,
    [402] = 117,
    [403] = 65,
    [404] = 82,
    [405] = 54,
    [406] = 117,
    [407] = 72,
    [408] = 117,
    [409] = 54,
    [410] = 117,
    [411] = 117,
    [412] = 135,
    [413] = 117,
    [414] = 58,
    [415] = 75,
    [416] = 117,
    [417] = 94,
    [418] = 51,
    [419] = 65,
    [420] = 117,
    [421] = 65,
    [422] = 51,
    [423] = 117,
    [424] = 135,
    [425] = 105,
    [426] = 65,
    [427] = 105,
    [428] = 65,
    [429] = 122,
    [430] = 68,
    [431] = 137,
    [432] = 82,
    [433] = 69,
    [434] = 137,
    [435] = 137,
    [436] = 82,
    [437] = 104,
    [438] = 86,
    [439] = 83,
    [440] = 82,
    [441] = 71,
    [442] = 75,
    [443] = 104,
    [444] = 104,
    [445] = 85,
    [446] = 75,
    [447] = 104,
    [448] = 88,
    [449] = 74,
    [450] = 80,
    [451] = 104,
    [452] = 104,
    [453] = 87,
    [454] = 75,
    [455] = 58,
    [456] = 65,
    [457] = 75,
    [458] = 61,
    [459] = 96,
    [460] = 101,
    [461] = 98,
    [462] = 61,
    [463] = 61,
    [464] = 135,
    [465] = 51,
    [466] = 138,
    [467] = 101,
    [468] = 136,
    [469] = 82,
    [470] = 82,
    [471] = 61,
    [472] = 135,
    [473] = 101,
    [474] = 82,
    [475] = 61,
    [476] = 135,
    [477] = 101,
    [478] = 82,
    [479] = 61,
    [480] = 98,
    [481] = 122,
    [482] = 75,
    [483] = 138,
    [484] = 65,
    [485] = 82,
    [486] = 54,
    [487] = 138,
    [488] = 72,
    [489] = 138,
    [490] = 54,
    [491] = 138,
    [492] = 138,
    [493] = 135,
    [494] = 138,
    [495] = 58,
    [496] = 75,
    [497] = 138,
    [498] = 94,
    [499] = 51,
    [500] = 65,
    [501] = 138,
    [502] = 65,
    [503] = 138,
    [504] = 135,
    [505] = 58,
    [506] = 65,
    [507] = 75,
    [508] = 60,
    [509] = 96,
    [510] = 101,
    [511] = 98,
    [512] = 60,
    [513] = 54,
    [514] = 82,
    [515] = 72,
    [516] = 82,
    [517] = 82,
    [518] = 61,
    [519] = 135,
    [520] = 58,
    [521] = 65,
    [522] = 75,
    [523] = 54,
    [524] = 96,
    [525] = 101,
    [526] = 98,
    [527] = 54,
    [528] = 82,
    [529] = 82,
    [530] = 61,
    [531] = 135,
    [532] = 101,
    [533] = 82,
    [534] = 61,
    [535] = 135,
    [536] = 51,
    [537] = 139,
    [538] = 101,
    [539] = 136,
    [540] = 82,
    [541] = 82,
    [542] = 61,
    [543] = 135,
    [544] = 101,
    [545] = 82,
    [546] = 61,
    [547] = 135,
    [548] = 101,
    [549] = 82,
    [550] = 61,
    [551] = 98,
    [552] = 122,
    [553] = 75,
    [554] = 139,
    [555] = 65,
    [556] = 82,
    [557] = 54,
    [558] = 139,
    [559] = 72,
    [560] = 139,
    [561] = 54,
    [562] = 139,
    [563] = 139,
    [564] = 135,
    [565] = 139,
    [566] = 58,
    [567] = 75,
    [568] = 139,
    [569] = 94,
    [570] = 51,
    [571] = 65,
    [572] = 139,
    [573] = 65,
    [574] = 139,
    [575] = 135,
    [576] = 101,
    [577] = 82,
    [578] = 61,
    [579] = 98,
    [580] = 122,
    [581] = 75,
    [582] = 0,
    [583] = 65,
    [584] = 82,
    [585] = 54,
    [586] = 0,
    [587] = 72,
    [588] = 0,
    [589] = 54,
    [590] = 0,
    [591] = 0,
    [592] = 58,
    [593] = 75,
    [594] = 0,
    [595] = 94,
    [596] = 51,
    [597] = 65,
    [598] = 0,
    [599] = 65,
    [600] = 140,
    [601] = 0,
    [602] = 140,
    [603] = 140,
};

PARSE_TABLE = {
    [0] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(532),
        [ts_sym__switch] = SHIFT(576),
        [ts_sym__var] = SHIFT(584),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(588),
        [ts_sym_expression] = SHIFT(589),
        [ts_sym_expression_statement] = SHIFT(588),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(588),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(588),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_program] = SHIFT(600),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(601),
        [ts_sym_statement_block] = SHIFT(588),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(588),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(588),
        [ts_aux_sym_repeat_helper1] = SHIFT(603),
        [ts_aux_sym_token1] = SHIFT(592),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_builtin_sym_error] = SHIFT(596),
    },
    [1] = {
        [ts_sym__terminator] = SHIFT(2),
    },
    [2] = {
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
    },
    [3] = {
        [ts_aux_sym_token3] = SHIFT(4),
    },
    [4] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(528),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(528),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [5] = {
        [ts_sym_formal_parameters] = SHIFT(6),
        [ts_sym_identifier] = SHIFT(525),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [6] = {
        [ts_sym_statement_block] = SHIFT(7),
        [ts_aux_sym_token1] = SHIFT(8),
    },
    [7] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [8] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(522),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(524),
    },
    [9] = {
        [ts_sym__terminator] = SHIFT(10),
    },
    [10] = {
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
    },
    [11] = {
        [ts_aux_sym_token3] = SHIFT(12),
    },
    [12] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(516),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(516),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [13] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(513),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(515),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [14] = {
        [ts_sym_formal_parameters] = SHIFT(15),
        [ts_sym_identifier] = SHIFT(510),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [15] = {
        [ts_sym_statement_block] = SHIFT(16),
        [ts_aux_sym_token1] = SHIFT(17),
    },
    [16] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [17] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(507),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(509),
    },
    [18] = {
        [ts_aux_sym_token3] = SHIFT(19),
    },
    [19] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(463),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(506),
    },
    [20] = {
        [ts_sym_formal_parameters] = SHIFT(21),
        [ts_sym_identifier] = SHIFT(460),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [21] = {
        [ts_sym_statement_block] = SHIFT(22),
        [ts_aux_sym_token1] = SHIFT(23),
    },
    [22] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [23] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(457),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(459),
    },
    [24] = {
        [ts_aux_sym_token3] = SHIFT(25),
    },
    [25] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(28),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(456),
    },
    [26] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [27] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [28] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(297),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [29] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(293),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(296),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [30] = {
        [ts_sym_formal_parameters] = SHIFT(31),
        [ts_sym_identifier] = SHIFT(290),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [31] = {
        [ts_sym_statement_block] = SHIFT(32),
        [ts_aux_sym_token1] = SHIFT(33),
    },
    [32] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [33] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(287),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(289),
    },
    [34] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(36),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(269),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [35] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [36] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [37] = {
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
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
    [38] = {
        [ts_aux_sym_token3] = SHIFT(39),
        [ts_aux_sym_token8] = SHIFT(263),
        [ts_aux_sym_token9] = SHIFT(265),
    },
    [39] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(262),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [40] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [41] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [42] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(43),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [43] = {
        [ts_aux_sym_token4] = SHIFT(44),
    },
    [44] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [45] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(46),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(261),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [46] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(47),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [47] = {
        [ts_aux_sym_token4] = SHIFT(48),
    },
    [48] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [49] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(50),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [50] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(51),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [51] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    [52] = {
        [ts_sym_identifier] = SHIFT(53),
    },
    [53] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [54] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(259),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [55] = {
        [ts_sym_formal_parameters] = SHIFT(56),
        [ts_sym_identifier] = SHIFT(256),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [56] = {
        [ts_sym_statement_block] = SHIFT(57),
        [ts_aux_sym_token1] = SHIFT(58),
    },
    [57] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [58] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(253),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(255),
    },
    [59] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [60] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [61] = {
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
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
    [62] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [63] = {
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
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
    [64] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(65),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(252),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [65] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(66),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [66] = {
        [ts_aux_sym_token4] = SHIFT(67),
    },
    [67] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [68] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [69] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(70),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [70] = {
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [71] = {
        [ts_sym_identifier] = SHIFT(72),
        [ts_sym_string] = SHIFT(72),
        [ts_aux_sym_token2] = SHIFT(248),
        [ts_builtin_sym_error] = SHIFT(249),
    },
    [72] = {
        [ts_aux_sym_token5] = SHIFT(73),
    },
    [73] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(245),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [74] = {
        [ts_sym_formal_parameters] = SHIFT(75),
        [ts_sym_identifier] = SHIFT(242),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [75] = {
        [ts_sym_statement_block] = SHIFT(76),
        [ts_aux_sym_token1] = SHIFT(77),
    },
    [76] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [77] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(239),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(241),
    },
    [78] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [79] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(80),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
    },
    [80] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [81] = {
        [ts_sym_identifier] = SHIFT(82),
    },
    [82] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [83] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(86),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [84] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [85] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [86] = {
        [ts_aux_sym_token10] = SHIFT(87),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [87] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [88] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(89),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(92),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [89] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(90),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [90] = {
        [ts_aux_sym_token4] = SHIFT(91),
    },
    [91] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [92] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [93] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(234),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(235),
    },
    [94] = {
        [ts_sym_formal_parameters] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(220),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [95] = {
        [ts_sym_statement_block] = SHIFT(96),
        [ts_aux_sym_token1] = SHIFT(97),
    },
    [96] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [97] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(217),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(219),
    },
    [98] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(99),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(216),
    },
    [99] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    [100] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(203),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(204),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(213),
    },
    [101] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(102),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [102] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(105),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [103] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [104] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [105] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(106),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [106] = {
        [ts_aux_sym_token2] = SHIFT(107),
    },
    [107] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [108] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(112),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [109] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(110),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [110] = {
        [ts_aux_sym_token4] = SHIFT(111),
    },
    [111] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [112] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [113] = {
        [ts_sym_identifier] = SHIFT(114),
        [ts_sym_string] = SHIFT(114),
        [ts_builtin_sym_error] = SHIFT(201),
    },
    [114] = {
        [ts_aux_sym_token5] = SHIFT(115),
    },
    [115] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(116),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [116] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(117),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [117] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 5),
    },
    [118] = {
        [ts_sym_identifier] = SHIFT(119),
    },
    [119] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [120] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(121),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [121] = {
        [ts_aux_sym_token10] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [122] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [123] = {
        [ts_sym_identifier] = SHIFT(124),
    },
    [124] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [125] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(126),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [126] = {
        [ts_aux_sym_token10] = SHIFT(127),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [127] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [128] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(129),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [129] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(130),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [130] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [131] = {
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_string] = SHIFT(132),
        [ts_aux_sym_token2] = SHIFT(197),
        [ts_builtin_sym_error] = SHIFT(198),
    },
    [132] = {
        [ts_aux_sym_token5] = SHIFT(133),
    },
    [133] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(134),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [134] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(135),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [135] = {
        [ts_aux_sym_token2] = SHIFT(136),
    },
    [136] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [137] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(138),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [138] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(139),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [139] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [140] = {
        [ts_sym_identifier] = SHIFT(141),
        [ts_sym_string] = SHIFT(141),
        [ts_aux_sym_token2] = SHIFT(193),
        [ts_builtin_sym_error] = SHIFT(194),
    },
    [141] = {
        [ts_aux_sym_token5] = SHIFT(142),
    },
    [142] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(143),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [143] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(144),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [144] = {
        [ts_aux_sym_token2] = SHIFT(145),
    },
    [145] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [146] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(149),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(191),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(192),
    },
    [147] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [148] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [149] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(150),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [150] = {
        [ts_aux_sym_token10] = SHIFT(151),
    },
    [151] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [152] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(153),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [153] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(154),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [154] = {
        [ts_aux_sym_token4] = SHIFT(155),
    },
    [155] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [156] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [157] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(190),
    },
    [158] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(159),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [159] = {
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 3),
    },
    [160] = {
        [ts_sym_identifier] = SHIFT(161),
    },
    [161] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [162] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(163),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [163] = {
        [ts_aux_sym_token10] = SHIFT(164),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [164] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [165] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(166),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(189),
    },
    [166] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(167),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [167] = {
        [ts_aux_sym_token10] = SHIFT(168),
    },
    [168] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [169] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(170),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [170] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(171),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token9] = SHIFT(182),
    },
    [171] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [172] = {
        [ts_sym_identifier] = SHIFT(173),
        [ts_sym_string] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(178),
        [ts_builtin_sym_error] = SHIFT(179),
    },
    [173] = {
        [ts_aux_sym_token5] = SHIFT(174),
    },
    [174] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(175),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [175] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(176),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [176] = {
        [ts_aux_sym_token2] = SHIFT(177),
    },
    [177] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [178] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [179] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(180),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [180] = {
        [ts_aux_sym_token2] = SHIFT(181),
    },
    [181] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [182] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(183),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(186),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(187),
    },
    [183] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(184),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [184] = {
        [ts_aux_sym_token10] = SHIFT(185),
    },
    [185] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [186] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [187] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(184),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [188] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [189] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(167),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [190] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(159),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [191] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [192] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(150),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [193] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [194] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(195),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [195] = {
        [ts_aux_sym_token2] = SHIFT(196),
    },
    [196] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [197] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [198] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(199),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [199] = {
        [ts_aux_sym_token2] = SHIFT(200),
    },
    [200] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [201] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(202),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [202] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 3),
    },
    [203] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = SHIFT(102),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [204] = {
        [ts_aux_sym_token2] = SHIFT(205),
    },
    [205] = {
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
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
    [206] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [207] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(211),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(212),
    },
    [208] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(209),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [209] = {
        [ts_aux_sym_token10] = SHIFT(210),
    },
    [210] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [211] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [212] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(209),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [213] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = SHIFT(205),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [214] = {
        [ts_aux_sym_token2] = SHIFT(215),
    },
    [215] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [216] = {
        [ts_sym__terminator] = SHIFT(63),
    },
    [217] = {
        [ts_aux_sym_token2] = SHIFT(218),
    },
    [218] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [219] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(218),
    },
    [220] = {
        [ts_sym_formal_parameters] = SHIFT(221),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [221] = {
        [ts_sym_statement_block] = SHIFT(222),
        [ts_aux_sym_token1] = SHIFT(97),
    },
    [222] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [223] = {
        [ts_sym_identifier] = SHIFT(224),
        [ts_aux_sym_token4] = SHIFT(230),
    },
    [224] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(225),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = SHIFT(227),
    },
    [225] = {
        [ts_aux_sym_token4] = SHIFT(226),
    },
    [226] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [227] = {
        [ts_sym_identifier] = SHIFT(228),
    },
    [228] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(229),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = SHIFT(227),
    },
    [229] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    [230] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [231] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(232),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [232] = {
        [ts_aux_sym_token10] = SHIFT(233),
    },
    [233] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [234] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [235] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(232),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [236] = {
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_string] = SHIFT(237),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_builtin_sym_error] = SHIFT(238),
    },
    [237] = {
        [ts_aux_sym_token5] = SHIFT(102),
    },
    [238] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [239] = {
        [ts_aux_sym_token2] = SHIFT(240),
    },
    [240] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [241] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(240),
    },
    [242] = {
        [ts_sym_formal_parameters] = SHIFT(243),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [243] = {
        [ts_sym_statement_block] = SHIFT(244),
        [ts_aux_sym_token1] = SHIFT(77),
    },
    [244] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [245] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(246),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [246] = {
        [ts_aux_sym_token2] = SHIFT(247),
    },
    [247] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [248] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [249] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(250),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [250] = {
        [ts_aux_sym_token2] = SHIFT(251),
    },
    [251] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [252] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [253] = {
        [ts_aux_sym_token2] = SHIFT(254),
    },
    [254] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [255] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(254),
    },
    [256] = {
        [ts_sym_formal_parameters] = SHIFT(257),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [257] = {
        [ts_sym_statement_block] = SHIFT(258),
        [ts_aux_sym_token1] = SHIFT(58),
    },
    [258] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [259] = {
        [ts_aux_sym_token10] = SHIFT(260),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [260] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [261] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [262] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [263] = {
        [ts_sym_identifier] = SHIFT(264),
    },
    [264] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [265] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(266),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [266] = {
        [ts_aux_sym_token10] = SHIFT(267),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [267] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [268] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [269] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [270] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [271] = {
        [ts_sym_identifier] = SHIFT(272),
        [ts_sym_string] = SHIFT(272),
        [ts_aux_sym_token2] = SHIFT(277),
        [ts_builtin_sym_error] = SHIFT(278),
    },
    [272] = {
        [ts_aux_sym_token5] = SHIFT(273),
    },
    [273] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(274),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [274] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(275),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [275] = {
        [ts_aux_sym_token2] = SHIFT(276),
    },
    [276] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [277] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [278] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(279),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [279] = {
        [ts_aux_sym_token2] = SHIFT(280),
    },
    [280] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [281] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(282),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(285),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(286),
    },
    [282] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(283),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [283] = {
        [ts_aux_sym_token10] = SHIFT(284),
    },
    [284] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [285] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [286] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(283),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [287] = {
        [ts_aux_sym_token2] = SHIFT(288),
    },
    [288] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [289] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(288),
    },
    [290] = {
        [ts_sym_formal_parameters] = SHIFT(291),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [291] = {
        [ts_sym_statement_block] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(33),
    },
    [292] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [293] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(294),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [294] = {
        [ts_aux_sym_token4] = SHIFT(295),
    },
    [295] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [296] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [297] = {
        [ts_aux_sym_token1] = SHIFT(298),
    },
    [298] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(454),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [299] = {
        [ts_sym__function] = SHIFT(300),
        [ts_sym_array] = SHIFT(310),
        [ts_sym_assignment] = SHIFT(311),
        [ts_sym_expression] = SHIFT(312),
        [ts_sym_false] = SHIFT(310),
        [ts_sym_function_call] = SHIFT(311),
        [ts_sym_function_expression] = SHIFT(311),
        [ts_sym_identifier] = SHIFT(435),
        [ts_sym_literal] = SHIFT(311),
        [ts_sym_null] = SHIFT(310),
        [ts_sym_number] = SHIFT(310),
        [ts_sym_object] = SHIFT(310),
        [ts_sym_property_access] = SHIFT(435),
        [ts_sym_string] = SHIFT(310),
        [ts_sym_true] = SHIFT(310),
        [ts_aux_sym_token1] = SHIFT(438),
        [ts_aux_sym_token9] = SHIFT(448),
    },
    [300] = {
        [ts_sym_formal_parameters] = SHIFT(301),
        [ts_sym_identifier] = SHIFT(307),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [301] = {
        [ts_sym_statement_block] = SHIFT(302),
        [ts_aux_sym_token1] = SHIFT(303),
    },
    [302] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [303] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(304),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(306),
    },
    [304] = {
        [ts_aux_sym_token2] = SHIFT(305),
    },
    [305] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [306] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(305),
    },
    [307] = {
        [ts_sym_formal_parameters] = SHIFT(308),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [308] = {
        [ts_sym_statement_block] = SHIFT(309),
        [ts_aux_sym_token1] = SHIFT(303),
    },
    [309] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [310] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [311] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [312] = {
        [ts_aux_sym_token3] = SHIFT(313),
        [ts_aux_sym_token5] = SHIFT(318),
        [ts_aux_sym_token8] = SHIFT(430),
        [ts_aux_sym_token9] = SHIFT(432),
    },
    [313] = {
        [ts_sym__function] = SHIFT(30),
        [ts_sym_array] = SHIFT(40),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(68),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_number] = SHIFT(40),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_property_access] = SHIFT(68),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_aux_sym_token1] = SHIFT(71),
        [ts_aux_sym_token4] = SHIFT(317),
        [ts_aux_sym_token9] = SHIFT(93),
    },
    [314] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(315),
        [ts_aux_sym_token3] = SHIFT(45),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(49),
        [ts_aux_sym_token8] = SHIFT(52),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [315] = {
        [ts_aux_sym_token4] = SHIFT(316),
    },
    [316] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [317] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [318] = {
        [ts_sym__break] = SHIFT(319),
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__for] = SHIFT(321),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(329),
        [ts_sym__switch] = SHIFT(352),
        [ts_sym__var] = SHIFT(386),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(390),
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_expression_statement] = SHIFT(390),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(390),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(390),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(393),
        [ts_sym_statement_block] = SHIFT(390),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(390),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(390),
        [ts_aux_sym_repeat_helper4] = SHIFT(429),
        [ts_aux_sym_token1] = SHIFT(395),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(399),
    },
    [319] = {
        [ts_sym__terminator] = SHIFT(320),
    },
    [320] = {
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
    },
    [321] = {
        [ts_aux_sym_token3] = SHIFT(322),
    },
    [322] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(325),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(325),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [323] = {
        [ts_sym__terminator] = SHIFT(324),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [324] = {
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
    [325] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(326),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [326] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(327),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(428),
    },
    [327] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(328),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [328] = {
        [ts_sym__break] = SHIFT(319),
        [ts_sym__for] = SHIFT(321),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(329),
        [ts_sym__switch] = SHIFT(352),
        [ts_sym__var] = SHIFT(386),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(390),
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_expression_statement] = SHIFT(390),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(390),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(390),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(427),
        [ts_sym_statement_block] = SHIFT(390),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(390),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(390),
        [ts_aux_sym_token1] = SHIFT(395),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(399),
    },
    [329] = {
        [ts_aux_sym_token3] = SHIFT(330),
    },
    [330] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(331),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(426),
    },
    [331] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(332),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [332] = {
        [ts_sym__break] = SHIFT(333),
        [ts_sym__for] = SHIFT(335),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(341),
        [ts_sym__switch] = SHIFT(345),
        [ts_sym__var] = SHIFT(404),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(408),
        [ts_sym_expression] = SHIFT(409),
        [ts_sym_expression_statement] = SHIFT(408),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(408),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(408),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(423),
        [ts_sym_statement_block] = SHIFT(408),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(408),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(408),
        [ts_aux_sym_token1] = SHIFT(414),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(418),
    },
    [333] = {
        [ts_sym__terminator] = SHIFT(334),
    },
    [334] = {
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
    },
    [335] = {
        [ts_aux_sym_token3] = SHIFT(336),
    },
    [336] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(337),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(337),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [337] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(338),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [338] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(339),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(421),
    },
    [339] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(340),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [340] = {
        [ts_sym__break] = SHIFT(333),
        [ts_sym__for] = SHIFT(335),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(341),
        [ts_sym__switch] = SHIFT(345),
        [ts_sym__var] = SHIFT(404),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(408),
        [ts_sym_expression] = SHIFT(409),
        [ts_sym_expression_statement] = SHIFT(408),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(408),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(408),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(420),
        [ts_sym_statement_block] = SHIFT(408),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(408),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(408),
        [ts_aux_sym_token1] = SHIFT(414),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(418),
    },
    [341] = {
        [ts_aux_sym_token3] = SHIFT(342),
    },
    [342] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(343),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(419),
    },
    [343] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(344),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [344] = {
        [ts_sym__break] = SHIFT(333),
        [ts_sym__for] = SHIFT(335),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(341),
        [ts_sym__switch] = SHIFT(345),
        [ts_sym__var] = SHIFT(404),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(408),
        [ts_sym_expression] = SHIFT(409),
        [ts_sym_expression_statement] = SHIFT(408),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(408),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(408),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(411),
        [ts_sym_statement_block] = SHIFT(408),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(408),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(408),
        [ts_aux_sym_token1] = SHIFT(414),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(418),
    },
    [345] = {
        [ts_aux_sym_token3] = SHIFT(346),
    },
    [346] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(347),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(403),
    },
    [347] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(348),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [348] = {
        [ts_aux_sym_token1] = SHIFT(349),
    },
    [349] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(401),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [350] = {
        [ts_aux_sym_token5] = SHIFT(351),
    },
    [351] = {
        [ts_sym__break] = SHIFT(319),
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__for] = SHIFT(321),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(329),
        [ts_sym__switch] = SHIFT(352),
        [ts_sym__var] = SHIFT(386),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(390),
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_expression_statement] = SHIFT(390),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(390),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(390),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(393),
        [ts_sym_statement_block] = SHIFT(390),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(390),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(390),
        [ts_aux_sym_repeat_helper4] = SHIFT(400),
        [ts_aux_sym_token1] = SHIFT(395),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(399),
    },
    [352] = {
        [ts_aux_sym_token3] = SHIFT(353),
    },
    [353] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(354),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(385),
    },
    [354] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(355),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [355] = {
        [ts_aux_sym_token1] = SHIFT(356),
    },
    [356] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(359),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [357] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(358),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [358] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 2),
    },
    [359] = {
        [ts_aux_sym_token2] = SHIFT(360),
    },
    [360] = {
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
    },
    [361] = {
        [ts_sym_identifier] = SHIFT(362),
    },
    [362] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [363] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(364),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [364] = {
        [ts_aux_sym_token10] = SHIFT(365),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [365] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [366] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [367] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(368),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
    },
    [368] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [369] = {
        [ts_sym_identifier] = SHIFT(370),
        [ts_sym_string] = SHIFT(370),
        [ts_aux_sym_token2] = SHIFT(375),
        [ts_builtin_sym_error] = SHIFT(376),
    },
    [370] = {
        [ts_aux_sym_token5] = SHIFT(371),
    },
    [371] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(372),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [372] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(373),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [373] = {
        [ts_aux_sym_token2] = SHIFT(374),
    },
    [374] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [375] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [376] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(377),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [377] = {
        [ts_aux_sym_token2] = SHIFT(378),
    },
    [378] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [379] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(380),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(383),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(384),
    },
    [380] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(381),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [381] = {
        [ts_aux_sym_token10] = SHIFT(382),
    },
    [382] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [383] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [384] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(381),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [385] = {
        [ts_aux_sym_token4] = SHIFT(355),
    },
    [386] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(387),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(389),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [387] = {
        [ts_sym__terminator] = SHIFT(388),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [388] = {
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__case] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__default] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
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
    [389] = {
        [ts_sym__terminator] = SHIFT(388),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [390] = {
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__case] = REDUCE(ts_sym_statement, 1),
        [ts_sym__default] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
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
    [391] = {
        [ts_sym__terminator] = SHIFT(392),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [392] = {
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
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
    [393] = {
        [ts_sym__break] = SHIFT(319),
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__for] = SHIFT(321),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(329),
        [ts_sym__switch] = SHIFT(352),
        [ts_sym__var] = SHIFT(386),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(390),
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_expression_statement] = SHIFT(390),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(390),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(390),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(393),
        [ts_sym_statement_block] = SHIFT(390),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(390),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(390),
        [ts_aux_sym_repeat_helper4] = SHIFT(394),
        [ts_aux_sym_token1] = SHIFT(395),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(399),
    },
    [394] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 2),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 2),
    },
    [395] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(203),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(396),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(398),
    },
    [396] = {
        [ts_aux_sym_token2] = SHIFT(397),
    },
    [397] = {
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__case] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__default] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
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
    [398] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = SHIFT(397),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [399] = {
        [ts_sym__terminator] = SHIFT(392),
    },
    [400] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_case, 3),
    },
    [401] = {
        [ts_aux_sym_token2] = SHIFT(402),
    },
    [402] = {
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
    },
    [403] = {
        [ts_aux_sym_token4] = SHIFT(348),
    },
    [404] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(405),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(407),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [405] = {
        [ts_sym__terminator] = SHIFT(406),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [406] = {
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__case] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__default] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
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
    [407] = {
        [ts_sym__terminator] = SHIFT(406),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [408] = {
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__case] = REDUCE(ts_sym_statement, 1),
        [ts_sym__default] = REDUCE(ts_sym_statement, 1),
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
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
    [409] = {
        [ts_sym__terminator] = SHIFT(410),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [410] = {
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
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
    [411] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(412),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
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
    [412] = {
        [ts_sym__break] = SHIFT(333),
        [ts_sym__for] = SHIFT(335),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(341),
        [ts_sym__switch] = SHIFT(345),
        [ts_sym__var] = SHIFT(404),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(408),
        [ts_sym_expression] = SHIFT(409),
        [ts_sym_expression_statement] = SHIFT(408),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(408),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(408),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(413),
        [ts_sym_statement_block] = SHIFT(408),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(408),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(408),
        [ts_aux_sym_token1] = SHIFT(414),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(418),
    },
    [413] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
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
    [414] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(203),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(415),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(417),
    },
    [415] = {
        [ts_aux_sym_token2] = SHIFT(416),
    },
    [416] = {
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__case] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__default] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
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
    [417] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = SHIFT(416),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [418] = {
        [ts_sym__terminator] = SHIFT(410),
    },
    [419] = {
        [ts_aux_sym_token4] = SHIFT(344),
    },
    [420] = {
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
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
    [421] = {
        [ts_aux_sym_token4] = SHIFT(340),
    },
    [422] = {
        [ts_sym__terminator] = SHIFT(324),
    },
    [423] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(424),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
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
    [424] = {
        [ts_sym__break] = SHIFT(319),
        [ts_sym__for] = SHIFT(321),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(329),
        [ts_sym__switch] = SHIFT(352),
        [ts_sym__var] = SHIFT(386),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(390),
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_expression_statement] = SHIFT(390),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(390),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(390),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(425),
        [ts_sym_statement_block] = SHIFT(390),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(390),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(390),
        [ts_aux_sym_token1] = SHIFT(395),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(399),
    },
    [425] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
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
    [426] = {
        [ts_aux_sym_token4] = SHIFT(332),
    },
    [427] = {
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
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
    [428] = {
        [ts_aux_sym_token4] = SHIFT(328),
    },
    [429] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_case, 4),
    },
    [430] = {
        [ts_sym_identifier] = SHIFT(431),
    },
    [431] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [432] = {
        [ts_sym__function] = SHIFT(55),
        [ts_sym_array] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(85),
        [ts_sym_expression] = SHIFT(433),
        [ts_sym_false] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(85),
        [ts_sym_function_expression] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(128),
        [ts_sym_literal] = SHIFT(85),
        [ts_sym_null] = SHIFT(84),
        [ts_sym_number] = SHIFT(84),
        [ts_sym_object] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(128),
        [ts_sym_string] = SHIFT(84),
        [ts_sym_true] = SHIFT(84),
        [ts_aux_sym_token1] = SHIFT(131),
        [ts_aux_sym_token9] = SHIFT(165),
    },
    [433] = {
        [ts_aux_sym_token10] = SHIFT(434),
        [ts_aux_sym_token3] = SHIFT(88),
        [ts_aux_sym_token8] = SHIFT(123),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [434] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [435] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(436),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [436] = {
        [ts_sym__function] = SHIFT(300),
        [ts_sym_array] = SHIFT(310),
        [ts_sym_assignment] = SHIFT(311),
        [ts_sym_expression] = SHIFT(437),
        [ts_sym_false] = SHIFT(310),
        [ts_sym_function_call] = SHIFT(311),
        [ts_sym_function_expression] = SHIFT(311),
        [ts_sym_identifier] = SHIFT(435),
        [ts_sym_literal] = SHIFT(311),
        [ts_sym_null] = SHIFT(310),
        [ts_sym_number] = SHIFT(310),
        [ts_sym_object] = SHIFT(310),
        [ts_sym_property_access] = SHIFT(435),
        [ts_sym_string] = SHIFT(310),
        [ts_sym_true] = SHIFT(310),
        [ts_aux_sym_token1] = SHIFT(438),
        [ts_aux_sym_token9] = SHIFT(448),
    },
    [437] = {
        [ts_aux_sym_token3] = SHIFT(313),
        [ts_aux_sym_token5] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(430),
        [ts_aux_sym_token9] = SHIFT(432),
    },
    [438] = {
        [ts_sym_identifier] = SHIFT(439),
        [ts_sym_string] = SHIFT(439),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_builtin_sym_error] = SHIFT(445),
    },
    [439] = {
        [ts_aux_sym_token5] = SHIFT(440),
    },
    [440] = {
        [ts_sym__function] = SHIFT(74),
        [ts_sym_array] = SHIFT(103),
        [ts_sym_assignment] = SHIFT(104),
        [ts_sym_expression] = SHIFT(441),
        [ts_sym_false] = SHIFT(103),
        [ts_sym_function_call] = SHIFT(104),
        [ts_sym_function_expression] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(137),
        [ts_sym_literal] = SHIFT(104),
        [ts_sym_null] = SHIFT(103),
        [ts_sym_number] = SHIFT(103),
        [ts_sym_object] = SHIFT(103),
        [ts_sym_property_access] = SHIFT(137),
        [ts_sym_string] = SHIFT(103),
        [ts_sym_true] = SHIFT(103),
        [ts_aux_sym_token1] = SHIFT(140),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [441] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(442),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(108),
        [ts_aux_sym_token7] = SHIFT(113),
        [ts_aux_sym_token8] = SHIFT(118),
        [ts_aux_sym_token9] = SHIFT(120),
    },
    [442] = {
        [ts_aux_sym_token2] = SHIFT(443),
    },
    [443] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [444] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [445] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(446),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [446] = {
        [ts_aux_sym_token2] = SHIFT(447),
    },
    [447] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [448] = {
        [ts_sym__function] = SHIFT(94),
        [ts_sym_array] = SHIFT(147),
        [ts_sym_assignment] = SHIFT(148),
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_false] = SHIFT(147),
        [ts_sym_function_call] = SHIFT(148),
        [ts_sym_function_expression] = SHIFT(148),
        [ts_sym_identifier] = SHIFT(169),
        [ts_sym_literal] = SHIFT(148),
        [ts_sym_null] = SHIFT(147),
        [ts_sym_number] = SHIFT(147),
        [ts_sym_object] = SHIFT(147),
        [ts_sym_property_access] = SHIFT(169),
        [ts_sym_string] = SHIFT(147),
        [ts_sym_true] = SHIFT(147),
        [ts_aux_sym_token1] = SHIFT(172),
        [ts_aux_sym_token10] = SHIFT(452),
        [ts_aux_sym_token9] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(453),
    },
    [449] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(450),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(152),
        [ts_aux_sym_token7] = SHIFT(157),
        [ts_aux_sym_token8] = SHIFT(160),
        [ts_aux_sym_token9] = SHIFT(162),
    },
    [450] = {
        [ts_aux_sym_token10] = SHIFT(451),
    },
    [451] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [452] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [453] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(450),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(157),
    },
    [454] = {
        [ts_aux_sym_token2] = SHIFT(455),
    },
    [455] = {
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
    },
    [456] = {
        [ts_aux_sym_token4] = SHIFT(297),
    },
    [457] = {
        [ts_aux_sym_token2] = SHIFT(458),
    },
    [458] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [459] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(458),
    },
    [460] = {
        [ts_sym_formal_parameters] = SHIFT(461),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [461] = {
        [ts_sym_statement_block] = SHIFT(462),
        [ts_aux_sym_token1] = SHIFT(23),
    },
    [462] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [463] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(464),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [464] = {
        [ts_sym__break] = SHIFT(465),
        [ts_sym__for] = SHIFT(467),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(473),
        [ts_sym__switch] = SHIFT(477),
        [ts_sym__var] = SHIFT(485),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(489),
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_expression_statement] = SHIFT(489),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(489),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(489),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(503),
        [ts_sym_statement_block] = SHIFT(489),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(489),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(489),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [465] = {
        [ts_sym__terminator] = SHIFT(466),
    },
    [466] = {
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
    },
    [467] = {
        [ts_aux_sym_token3] = SHIFT(468),
    },
    [468] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(469),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(469),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [469] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(470),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [470] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(471),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(502),
    },
    [471] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(472),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [472] = {
        [ts_sym__break] = SHIFT(465),
        [ts_sym__for] = SHIFT(467),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(473),
        [ts_sym__switch] = SHIFT(477),
        [ts_sym__var] = SHIFT(485),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(489),
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_expression_statement] = SHIFT(489),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(489),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(489),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(501),
        [ts_sym_statement_block] = SHIFT(489),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(489),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(489),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [473] = {
        [ts_aux_sym_token3] = SHIFT(474),
    },
    [474] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(475),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(500),
    },
    [475] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(476),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [476] = {
        [ts_sym__break] = SHIFT(465),
        [ts_sym__for] = SHIFT(467),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(473),
        [ts_sym__switch] = SHIFT(477),
        [ts_sym__var] = SHIFT(485),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(489),
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_expression_statement] = SHIFT(489),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(489),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(489),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(492),
        [ts_sym_statement_block] = SHIFT(489),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(489),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(489),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [477] = {
        [ts_aux_sym_token3] = SHIFT(478),
    },
    [478] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(479),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(484),
    },
    [479] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(480),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [480] = {
        [ts_aux_sym_token1] = SHIFT(481),
    },
    [481] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(482),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [482] = {
        [ts_aux_sym_token2] = SHIFT(483),
    },
    [483] = {
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
    },
    [484] = {
        [ts_aux_sym_token4] = SHIFT(480),
    },
    [485] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(486),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [486] = {
        [ts_sym__terminator] = SHIFT(487),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [487] = {
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
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
    [488] = {
        [ts_sym__terminator] = SHIFT(487),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [489] = {
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
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
    [490] = {
        [ts_sym__terminator] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [491] = {
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
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
    [492] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(493),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
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
    [493] = {
        [ts_sym__break] = SHIFT(465),
        [ts_sym__for] = SHIFT(467),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(473),
        [ts_sym__switch] = SHIFT(477),
        [ts_sym__var] = SHIFT(485),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(489),
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_expression_statement] = SHIFT(489),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(489),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(489),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(494),
        [ts_sym_statement_block] = SHIFT(489),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(489),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(489),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [494] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
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
    [495] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(203),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(496),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(498),
    },
    [496] = {
        [ts_aux_sym_token2] = SHIFT(497),
    },
    [497] = {
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
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
    [498] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = SHIFT(497),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [499] = {
        [ts_sym__terminator] = SHIFT(491),
    },
    [500] = {
        [ts_aux_sym_token4] = SHIFT(476),
    },
    [501] = {
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
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
    [502] = {
        [ts_aux_sym_token4] = SHIFT(472),
    },
    [503] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(504),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
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
    [504] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(505),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(216),
    },
    [505] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
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
    [506] = {
        [ts_aux_sym_token4] = SHIFT(464),
    },
    [507] = {
        [ts_aux_sym_token2] = SHIFT(508),
    },
    [508] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [509] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(508),
    },
    [510] = {
        [ts_sym_formal_parameters] = SHIFT(511),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [511] = {
        [ts_sym_statement_block] = SHIFT(512),
        [ts_aux_sym_token1] = SHIFT(17),
    },
    [512] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [513] = {
        [ts_sym__terminator] = SHIFT(514),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [514] = {
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
    [515] = {
        [ts_sym__terminator] = SHIFT(514),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [516] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(517),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [517] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(518),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(521),
    },
    [518] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(519),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [519] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(520),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(216),
    },
    [520] = {
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
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
    [521] = {
        [ts_aux_sym_token4] = SHIFT(519),
    },
    [522] = {
        [ts_aux_sym_token2] = SHIFT(523),
    },
    [523] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [524] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_token2] = SHIFT(523),
    },
    [525] = {
        [ts_sym_formal_parameters] = SHIFT(526),
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [526] = {
        [ts_sym_statement_block] = SHIFT(527),
        [ts_aux_sym_token1] = SHIFT(8),
    },
    [527] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [528] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(529),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [529] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(530),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(599),
    },
    [530] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(531),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [531] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(532),
        [ts_sym__switch] = SHIFT(576),
        [ts_sym__var] = SHIFT(584),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(588),
        [ts_sym_expression] = SHIFT(589),
        [ts_sym_expression_statement] = SHIFT(588),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(588),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(588),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(598),
        [ts_sym_statement_block] = SHIFT(588),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(588),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(588),
        [ts_aux_sym_token1] = SHIFT(592),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(596),
    },
    [532] = {
        [ts_aux_sym_token3] = SHIFT(533),
    },
    [533] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(534),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(597),
    },
    [534] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(535),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [535] = {
        [ts_sym__break] = SHIFT(536),
        [ts_sym__for] = SHIFT(538),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(544),
        [ts_sym__switch] = SHIFT(548),
        [ts_sym__var] = SHIFT(556),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(574),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_aux_sym_token1] = SHIFT(566),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(570),
    },
    [536] = {
        [ts_sym__terminator] = SHIFT(537),
    },
    [537] = {
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
    },
    [538] = {
        [ts_aux_sym_token3] = SHIFT(539),
    },
    [539] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(540),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(540),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [540] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_expression_statement] = SHIFT(541),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_true] = SHIFT(59),
        [ts_aux_sym_token1] = SHIFT(236),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(422),
    },
    [541] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(542),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(573),
    },
    [542] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(543),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [543] = {
        [ts_sym__break] = SHIFT(536),
        [ts_sym__for] = SHIFT(538),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(544),
        [ts_sym__switch] = SHIFT(548),
        [ts_sym__var] = SHIFT(556),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(572),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_aux_sym_token1] = SHIFT(566),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(570),
    },
    [544] = {
        [ts_aux_sym_token3] = SHIFT(545),
    },
    [545] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(546),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(571),
    },
    [546] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(547),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [547] = {
        [ts_sym__break] = SHIFT(536),
        [ts_sym__for] = SHIFT(538),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(544),
        [ts_sym__switch] = SHIFT(548),
        [ts_sym__var] = SHIFT(556),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(563),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_aux_sym_token1] = SHIFT(566),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(570),
    },
    [548] = {
        [ts_aux_sym_token3] = SHIFT(549),
    },
    [549] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(550),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(555),
    },
    [550] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(551),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [551] = {
        [ts_aux_sym_token1] = SHIFT(552),
    },
    [552] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(553),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [553] = {
        [ts_aux_sym_token2] = SHIFT(554),
    },
    [554] = {
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
    },
    [555] = {
        [ts_aux_sym_token4] = SHIFT(551),
    },
    [556] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(557),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(559),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [557] = {
        [ts_sym__terminator] = SHIFT(558),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [558] = {
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
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
    [559] = {
        [ts_sym__terminator] = SHIFT(558),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [560] = {
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
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
    [561] = {
        [ts_sym__terminator] = SHIFT(562),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [562] = {
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
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
    [563] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(564),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
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
    [564] = {
        [ts_sym__break] = SHIFT(536),
        [ts_sym__for] = SHIFT(538),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(544),
        [ts_sym__switch] = SHIFT(548),
        [ts_sym__var] = SHIFT(556),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(565),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_aux_sym_token1] = SHIFT(566),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(570),
    },
    [565] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
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
    [566] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(203),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(567),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(569),
    },
    [567] = {
        [ts_aux_sym_token2] = SHIFT(568),
    },
    [568] = {
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
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
    [569] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = SHIFT(568),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [570] = {
        [ts_sym__terminator] = SHIFT(562),
    },
    [571] = {
        [ts_aux_sym_token4] = SHIFT(547),
    },
    [572] = {
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
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
    [573] = {
        [ts_aux_sym_token4] = SHIFT(543),
    },
    [574] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(575),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
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
    [575] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(532),
        [ts_sym__switch] = SHIFT(576),
        [ts_sym__var] = SHIFT(584),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(588),
        [ts_sym_expression] = SHIFT(589),
        [ts_sym_expression_statement] = SHIFT(588),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(588),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(588),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(591),
        [ts_sym_statement_block] = SHIFT(588),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(588),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(588),
        [ts_aux_sym_token1] = SHIFT(592),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(596),
    },
    [576] = {
        [ts_aux_sym_token3] = SHIFT(577),
    },
    [577] = {
        [ts_sym__function] = SHIFT(20),
        [ts_sym_array] = SHIFT(26),
        [ts_sym_assignment] = SHIFT(27),
        [ts_sym_expression] = SHIFT(578),
        [ts_sym_false] = SHIFT(26),
        [ts_sym_function_call] = SHIFT(27),
        [ts_sym_function_expression] = SHIFT(27),
        [ts_sym_identifier] = SHIFT(366),
        [ts_sym_literal] = SHIFT(27),
        [ts_sym_null] = SHIFT(26),
        [ts_sym_number] = SHIFT(26),
        [ts_sym_object] = SHIFT(26),
        [ts_sym_property_access] = SHIFT(366),
        [ts_sym_string] = SHIFT(26),
        [ts_sym_true] = SHIFT(26),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(379),
        [ts_builtin_sym_error] = SHIFT(583),
    },
    [578] = {
        [ts_aux_sym_token3] = SHIFT(29),
        [ts_aux_sym_token4] = SHIFT(579),
        [ts_aux_sym_token8] = SHIFT(361),
        [ts_aux_sym_token9] = SHIFT(363),
    },
    [579] = {
        [ts_aux_sym_token1] = SHIFT(580),
    },
    [580] = {
        [ts_sym__case] = SHIFT(299),
        [ts_sym__default] = SHIFT(350),
        [ts_sym_switch_case] = SHIFT(357),
        [ts_aux_sym_repeat_helper3] = SHIFT(581),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [581] = {
        [ts_aux_sym_token2] = SHIFT(582),
    },
    [582] = {
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
    },
    [583] = {
        [ts_aux_sym_token4] = SHIFT(579),
    },
    [584] = {
        [ts_sym__function] = SHIFT(14),
        [ts_sym_array] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(585),
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(268),
        [ts_sym_identifier] = SHIFT(587),
        [ts_sym_literal] = SHIFT(268),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_number] = SHIFT(35),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_aux_sym_token1] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(281),
    },
    [585] = {
        [ts_sym__terminator] = SHIFT(586),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [586] = {
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
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
    [587] = {
        [ts_sym__terminator] = SHIFT(586),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(79),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [588] = {
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
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
    [589] = {
        [ts_sym__terminator] = SHIFT(590),
        [ts_aux_sym_token3] = SHIFT(64),
        [ts_aux_sym_token8] = SHIFT(81),
        [ts_aux_sym_token9] = SHIFT(83),
    },
    [590] = {
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
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
    [591] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
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
    [592] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(18),
        [ts_sym__switch] = SHIFT(24),
        [ts_sym__var] = SHIFT(34),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(61),
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_expression_statement] = SHIFT(61),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_if_statement] = SHIFT(61),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(98),
        [ts_sym_statement_block] = SHIFT(61),
        [ts_sym_string] = SHIFT(203),
        [ts_sym_switch_statement] = SHIFT(61),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(61),
        [ts_aux_sym_repeat_helper2] = SHIFT(593),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(595),
    },
    [593] = {
        [ts_aux_sym_token2] = SHIFT(594),
    },
    [594] = {
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
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
    [595] = {
        [ts_sym__terminator] = SHIFT(63),
        [ts_aux_sym_repeat_helper7] = SHIFT(214),
        [ts_aux_sym_token2] = SHIFT(594),
        [ts_aux_sym_token7] = SHIFT(113),
    },
    [596] = {
        [ts_sym__terminator] = SHIFT(590),
    },
    [597] = {
        [ts_aux_sym_token4] = SHIFT(535),
    },
    [598] = {
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
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
    [599] = {
        [ts_aux_sym_token4] = SHIFT(531),
    },
    [600] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [601] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(532),
        [ts_sym__switch] = SHIFT(576),
        [ts_sym__var] = SHIFT(584),
        [ts_sym_array] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(60),
        [ts_sym_break_statement] = SHIFT(588),
        [ts_sym_expression] = SHIFT(589),
        [ts_sym_expression_statement] = SHIFT(588),
        [ts_sym_false] = SHIFT(59),
        [ts_sym_for_statement] = SHIFT(588),
        [ts_sym_function_call] = SHIFT(60),
        [ts_sym_function_expression] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(588),
        [ts_sym_literal] = SHIFT(60),
        [ts_sym_null] = SHIFT(59),
        [ts_sym_number] = SHIFT(59),
        [ts_sym_object] = SHIFT(59),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_statement] = SHIFT(601),
        [ts_sym_statement_block] = SHIFT(588),
        [ts_sym_string] = SHIFT(59),
        [ts_sym_switch_statement] = SHIFT(588),
        [ts_sym_true] = SHIFT(59),
        [ts_sym_var_declaration] = SHIFT(588),
        [ts_aux_sym_repeat_helper1] = SHIFT(602),
        [ts_aux_sym_token1] = SHIFT(592),
        [ts_aux_sym_token9] = SHIFT(207),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_builtin_sym_error] = SHIFT(596),
    },
    [602] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    [603] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
