#include "tree_sitter/parser.h"

STATE_COUNT = 507;
SYMBOL_COUNT = 55;

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
    [ts_builtin_sym_end] = "end",
    [ts_builtin_sym_error] = "error",
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
                ADVANCE(61);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 61:
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
        case 62:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            LEX_ERROR();
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 64:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 65:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '.')
                ADVANCE(57);
            LEX_ERROR();
        case 66:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == ')')
                ADVANCE(63);
            LEX_ERROR();
        case 67:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 68:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '\n')
                ADVANCE(70);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
            LEX_ERROR();
        case 70:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '\n')
                ADVANCE(70);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 71:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 75:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '\n')
                ADVANCE(76);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '\n')
                ADVANCE(76);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 78:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(79);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(79);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(63);
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
                ADVANCE(61);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
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
                ADVANCE(74);
            if (lookahead == 'f')
                ADVANCE(61);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 84:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(77);
            LEX_ERROR();
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
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 88:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 89:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 90:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '\n')
                ADVANCE(91);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 91:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '\n')
                ADVANCE(91);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 92:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '\n')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 93:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '\n')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 94:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 95:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(64);
            LEX_ERROR();
        case 96:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == ')')
                ADVANCE(63);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(97);
            if (lookahead == '(')
                ADVANCE(56);
            LEX_ERROR();
        case 98:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(98);
            if (lookahead == '(')
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            LEX_ERROR();
        case 99:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '\n')
                ADVANCE(100);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
            LEX_ERROR();
        case 100:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '\n')
                ADVANCE(100);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 101:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(71);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(77);
            LEX_ERROR();
        case 103:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
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
                ADVANCE(104);
            if (lookahead == 'd')
                ADVANCE(108);
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
        case 104:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 105:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 's')
                ADVANCE(106);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 106:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 107:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__case);
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
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'f')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 110:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'a')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 111:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'u')
                ADVANCE(112);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 112:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'l')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 113:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 't')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 114:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__default);
        case 115:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
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
                ADVANCE(104);
            if (lookahead == 'd')
                ADVANCE(108);
            if (lookahead == 'e')
                ADVANCE(116);
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
        case 116:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'l')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 117:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 's')
                ADVANCE(118);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 118:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            if (lookahead == 'e')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 119:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__else);
        case 120:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == 'c')
                ADVANCE(121);
            if (lookahead == 'd')
                ADVANCE(125);
            if (lookahead == '}')
                ADVANCE(59);
            LEX_ERROR();
        case 121:
            if (lookahead == 'a')
                ADVANCE(122);
            LEX_ERROR();
        case 122:
            if (lookahead == 's')
                ADVANCE(123);
            LEX_ERROR();
        case 123:
            if (lookahead == 'e')
                ADVANCE(124);
            LEX_ERROR();
        case 124:
            ACCEPT_TOKEN(ts_sym__case);
        case 125:
            if (lookahead == 'e')
                ADVANCE(126);
            LEX_ERROR();
        case 126:
            if (lookahead == 'f')
                ADVANCE(127);
            LEX_ERROR();
        case 127:
            if (lookahead == 'a')
                ADVANCE(128);
            LEX_ERROR();
        case 128:
            if (lookahead == 'u')
                ADVANCE(129);
            LEX_ERROR();
        case 129:
            if (lookahead == 'l')
                ADVANCE(130);
            LEX_ERROR();
        case 130:
            if (lookahead == 't')
                ADVANCE(131);
            LEX_ERROR();
        case 131:
            ACCEPT_TOKEN(ts_sym__default);
        case 132:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == '=')
                ADVANCE(71);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
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
        case 134:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
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
                ADVANCE(61);
            if (lookahead == 'n')
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(43);
            if (lookahead == 'v')
                ADVANCE(47);
            if (lookahead == '{')
                ADVANCE(50);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '.')
                ADVANCE(57);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == '=')
                ADVANCE(71);
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
                ADVANCE(116);
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
        case 137:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
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
                ADVANCE(116);
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
        case 138:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
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
                ADVANCE(74);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(104);
            if (lookahead == 'd')
                ADVANCE(108);
            if (lookahead == 'e')
                ADVANCE(116);
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
        case 140:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
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
                ADVANCE(74);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(104);
            if (lookahead == 'd')
                ADVANCE(108);
            if (lookahead == 'e')
                ADVANCE(116);
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
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(64);
            if (lookahead == '.')
                ADVANCE(57);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(7);
            if (lookahead == ':')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(71);
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
                ADVANCE(74);
            if (lookahead == 'b')
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(104);
            if (lookahead == 'd')
                ADVANCE(108);
            if (lookahead == 'e')
                ADVANCE(116);
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
    [3] = 97,
    [4] = 134,
    [5] = 98,
    [6] = 94,
    [7] = 54,
    [8] = 58,
    [9] = 51,
    [10] = 58,
    [11] = 97,
    [12] = 134,
    [13] = 67,
    [14] = 51,
    [15] = 60,
    [16] = 69,
    [17] = 60,
    [18] = 54,
    [19] = 54,
    [20] = 54,
    [21] = 81,
    [22] = 98,
    [23] = 94,
    [24] = 62,
    [25] = 58,
    [26] = 97,
    [27] = 60,
    [28] = 98,
    [29] = 94,
    [30] = 65,
    [31] = 58,
    [32] = 97,
    [33] = 60,
    [34] = 65,
    [35] = 65,
    [36] = 65,
    [37] = 81,
    [38] = 62,
    [39] = 62,
    [40] = 62,
    [41] = 66,
    [42] = 65,
    [43] = 81,
    [44] = 62,
    [45] = 66,
    [46] = 62,
    [47] = 60,
    [48] = 62,
    [49] = 66,
    [50] = 67,
    [51] = 62,
    [52] = 101,
    [53] = 60,
    [54] = 62,
    [55] = 86,
    [56] = 84,
    [57] = 60,
    [58] = 98,
    [59] = 94,
    [60] = 68,
    [61] = 58,
    [62] = 67,
    [63] = 51,
    [64] = 58,
    [65] = 69,
    [66] = 58,
    [67] = 54,
    [68] = 58,
    [69] = 67,
    [70] = 54,
    [71] = 99,
    [72] = 60,
    [73] = 54,
    [74] = 86,
    [75] = 84,
    [76] = 60,
    [77] = 68,
    [78] = 68,
    [79] = 68,
    [80] = 72,
    [81] = 54,
    [82] = 81,
    [83] = 62,
    [84] = 66,
    [85] = 68,
    [86] = 68,
    [87] = 83,
    [88] = 98,
    [89] = 94,
    [90] = 73,
    [91] = 58,
    [92] = 58,
    [93] = 72,
    [94] = 58,
    [95] = 75,
    [96] = 78,
    [97] = 72,
    [98] = 58,
    [99] = 54,
    [100] = 83,
    [101] = 73,
    [102] = 73,
    [103] = 73,
    [104] = 80,
    [105] = 54,
    [106] = 81,
    [107] = 62,
    [108] = 66,
    [109] = 73,
    [110] = 73,
    [111] = 60,
    [112] = 73,
    [113] = 80,
    [114] = 67,
    [115] = 73,
    [116] = 89,
    [117] = 60,
    [118] = 73,
    [119] = 86,
    [120] = 84,
    [121] = 60,
    [122] = 68,
    [123] = 72,
    [124] = 73,
    [125] = 88,
    [126] = 84,
    [127] = 60,
    [128] = 68,
    [129] = 72,
    [130] = 67,
    [131] = 68,
    [132] = 87,
    [133] = 60,
    [134] = 68,
    [135] = 86,
    [136] = 84,
    [137] = 60,
    [138] = 68,
    [139] = 72,
    [140] = 68,
    [141] = 83,
    [142] = 73,
    [143] = 80,
    [144] = 68,
    [145] = 68,
    [146] = 83,
    [147] = 73,
    [148] = 80,
    [149] = 73,
    [150] = 73,
    [151] = 82,
    [152] = 82,
    [153] = 68,
    [154] = 85,
    [155] = 72,
    [156] = 68,
    [157] = 85,
    [158] = 72,
    [159] = 73,
    [160] = 85,
    [161] = 72,
    [162] = 73,
    [163] = 82,
    [164] = 54,
    [165] = 82,
    [166] = 90,
    [167] = 72,
    [168] = 54,
    [169] = 51,
    [170] = 72,
    [171] = 73,
    [172] = 92,
    [173] = 97,
    [174] = 94,
    [175] = 73,
    [176] = 96,
    [177] = 95,
    [178] = 66,
    [179] = 94,
    [180] = 67,
    [181] = 95,
    [182] = 66,
    [183] = 94,
    [184] = 73,
    [185] = 80,
    [186] = 62,
    [187] = 62,
    [188] = 82,
    [189] = 85,
    [190] = 72,
    [191] = 68,
    [192] = 92,
    [193] = 97,
    [194] = 94,
    [195] = 68,
    [196] = 68,
    [197] = 72,
    [198] = 62,
    [199] = 62,
    [200] = 85,
    [201] = 72,
    [202] = 62,
    [203] = 62,
    [204] = 65,
    [205] = 94,
    [206] = 120,
    [207] = 60,
    [208] = 98,
    [209] = 94,
    [210] = 102,
    [211] = 58,
    [212] = 72,
    [213] = 102,
    [214] = 92,
    [215] = 97,
    [216] = 94,
    [217] = 102,
    [218] = 102,
    [219] = 102,
    [220] = 102,
    [221] = 81,
    [222] = 62,
    [223] = 66,
    [224] = 102,
    [225] = 102,
    [226] = 103,
    [227] = 51,
    [228] = 103,
    [229] = 97,
    [230] = 134,
    [231] = 54,
    [232] = 60,
    [233] = 60,
    [234] = 60,
    [235] = 65,
    [236] = 133,
    [237] = 97,
    [238] = 60,
    [239] = 65,
    [240] = 133,
    [241] = 51,
    [242] = 115,
    [243] = 97,
    [244] = 134,
    [245] = 60,
    [246] = 60,
    [247] = 65,
    [248] = 133,
    [249] = 97,
    [250] = 60,
    [251] = 65,
    [252] = 133,
    [253] = 97,
    [254] = 60,
    [255] = 65,
    [256] = 94,
    [257] = 120,
    [258] = 84,
    [259] = 103,
    [260] = 97,
    [261] = 60,
    [262] = 65,
    [263] = 94,
    [264] = 120,
    [265] = 120,
    [266] = 72,
    [267] = 72,
    [268] = 103,
    [269] = 67,
    [270] = 65,
    [271] = 132,
    [272] = 60,
    [273] = 65,
    [274] = 86,
    [275] = 84,
    [276] = 60,
    [277] = 68,
    [278] = 72,
    [279] = 65,
    [280] = 65,
    [281] = 85,
    [282] = 72,
    [283] = 65,
    [284] = 83,
    [285] = 73,
    [286] = 80,
    [287] = 65,
    [288] = 65,
    [289] = 82,
    [290] = 66,
    [291] = 67,
    [292] = 51,
    [293] = 103,
    [294] = 69,
    [295] = 103,
    [296] = 54,
    [297] = 103,
    [298] = 103,
    [299] = 120,
    [300] = 58,
    [301] = 72,
    [302] = 103,
    [303] = 90,
    [304] = 51,
    [305] = 120,
    [306] = 72,
    [307] = 115,
    [308] = 66,
    [309] = 67,
    [310] = 51,
    [311] = 115,
    [312] = 69,
    [313] = 115,
    [314] = 54,
    [315] = 115,
    [316] = 115,
    [317] = 133,
    [318] = 115,
    [319] = 58,
    [320] = 72,
    [321] = 115,
    [322] = 90,
    [323] = 51,
    [324] = 66,
    [325] = 115,
    [326] = 66,
    [327] = 51,
    [328] = 115,
    [329] = 133,
    [330] = 103,
    [331] = 66,
    [332] = 103,
    [333] = 66,
    [334] = 120,
    [335] = 67,
    [336] = 102,
    [337] = 135,
    [338] = 60,
    [339] = 102,
    [340] = 86,
    [341] = 84,
    [342] = 60,
    [343] = 68,
    [344] = 72,
    [345] = 102,
    [346] = 102,
    [347] = 85,
    [348] = 72,
    [349] = 102,
    [350] = 83,
    [351] = 73,
    [352] = 80,
    [353] = 102,
    [354] = 102,
    [355] = 82,
    [356] = 72,
    [357] = 58,
    [358] = 66,
    [359] = 72,
    [360] = 65,
    [361] = 92,
    [362] = 97,
    [363] = 94,
    [364] = 65,
    [365] = 65,
    [366] = 133,
    [367] = 51,
    [368] = 136,
    [369] = 97,
    [370] = 134,
    [371] = 60,
    [372] = 60,
    [373] = 65,
    [374] = 133,
    [375] = 97,
    [376] = 60,
    [377] = 65,
    [378] = 133,
    [379] = 97,
    [380] = 60,
    [381] = 65,
    [382] = 94,
    [383] = 120,
    [384] = 72,
    [385] = 136,
    [386] = 66,
    [387] = 67,
    [388] = 51,
    [389] = 136,
    [390] = 69,
    [391] = 136,
    [392] = 54,
    [393] = 136,
    [394] = 136,
    [395] = 133,
    [396] = 136,
    [397] = 58,
    [398] = 72,
    [399] = 136,
    [400] = 90,
    [401] = 51,
    [402] = 66,
    [403] = 136,
    [404] = 66,
    [405] = 136,
    [406] = 133,
    [407] = 58,
    [408] = 66,
    [409] = 72,
    [410] = 62,
    [411] = 92,
    [412] = 97,
    [413] = 94,
    [414] = 62,
    [415] = 62,
    [416] = 66,
    [417] = 54,
    [418] = 54,
    [419] = 60,
    [420] = 60,
    [421] = 65,
    [422] = 133,
    [423] = 58,
    [424] = 66,
    [425] = 72,
    [426] = 54,
    [427] = 92,
    [428] = 97,
    [429] = 94,
    [430] = 54,
    [431] = 60,
    [432] = 60,
    [433] = 65,
    [434] = 133,
    [435] = 97,
    [436] = 60,
    [437] = 65,
    [438] = 133,
    [439] = 51,
    [440] = 137,
    [441] = 97,
    [442] = 134,
    [443] = 60,
    [444] = 60,
    [445] = 65,
    [446] = 133,
    [447] = 97,
    [448] = 60,
    [449] = 65,
    [450] = 133,
    [451] = 97,
    [452] = 60,
    [453] = 65,
    [454] = 94,
    [455] = 120,
    [456] = 72,
    [457] = 137,
    [458] = 66,
    [459] = 67,
    [460] = 51,
    [461] = 137,
    [462] = 69,
    [463] = 137,
    [464] = 54,
    [465] = 137,
    [466] = 137,
    [467] = 133,
    [468] = 137,
    [469] = 58,
    [470] = 72,
    [471] = 137,
    [472] = 90,
    [473] = 51,
    [474] = 66,
    [475] = 137,
    [476] = 66,
    [477] = 137,
    [478] = 133,
    [479] = 97,
    [480] = 60,
    [481] = 65,
    [482] = 94,
    [483] = 120,
    [484] = 72,
    [485] = 0,
    [486] = 66,
    [487] = 67,
    [488] = 51,
    [489] = 0,
    [490] = 69,
    [491] = 0,
    [492] = 54,
    [493] = 0,
    [494] = 0,
    [495] = 58,
    [496] = 72,
    [497] = 0,
    [498] = 90,
    [499] = 51,
    [500] = 66,
    [501] = 0,
    [502] = 66,
    [503] = 138,
    [504] = 0,
    [505] = 138,
    [506] = 138,
};

PARSE_TABLE = {
    [0] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(435),
        [ts_sym__switch] = SHIFT(479),
        [ts_sym__var] = SHIFT(487),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(491),
        [ts_sym_expression] = SHIFT(492),
        [ts_sym_expression_statement] = SHIFT(491),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(491),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(491),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_program] = SHIFT(503),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(504),
        [ts_sym_statement_block] = SHIFT(491),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(491),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(491),
        [ts_aux_sym_repeat_helper1] = SHIFT(506),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_builtin_sym_error] = SHIFT(499),
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
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(431),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(431),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [5] = {
        [ts_sym_formal_parameters] = SHIFT(6),
        [ts_sym_identifier] = SHIFT(428),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [6] = {
        [ts_sym_statement_block] = SHIFT(7),
        [ts_aux_sym_token1] = SHIFT(8),
    },
    [7] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [8] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(425),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(427),
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
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(419),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(419),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [13] = {
        [ts_sym_assignment] = SHIFT(14),
        [ts_sym_identifier] = SHIFT(16),
    },
    [14] = {
        [ts_sym__terminator] = SHIFT(15),
    },
    [15] = {
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
    [16] = {
        [ts_sym__terminator] = SHIFT(15),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [17] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(20),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
    },
    [18] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [19] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [20] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [21] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(415),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token4] = SHIFT(418),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [22] = {
        [ts_sym_formal_parameters] = SHIFT(23),
        [ts_sym_identifier] = SHIFT(412),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [23] = {
        [ts_sym_statement_block] = SHIFT(24),
        [ts_aux_sym_token1] = SHIFT(25),
    },
    [24] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [25] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(409),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(411),
    },
    [26] = {
        [ts_aux_sym_token3] = SHIFT(27),
    },
    [27] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(365),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(408),
    },
    [28] = {
        [ts_sym_formal_parameters] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(362),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [29] = {
        [ts_sym_statement_block] = SHIFT(30),
        [ts_aux_sym_token1] = SHIFT(31),
    },
    [30] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [31] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(359),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(361),
    },
    [32] = {
        [ts_aux_sym_token3] = SHIFT(33),
    },
    [33] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(358),
    },
    [34] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [35] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [36] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(205),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [37] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(40),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token4] = SHIFT(204),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [38] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [39] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [40] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(41),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [41] = {
        [ts_aux_sym_token4] = SHIFT(42),
    },
    [42] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [43] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(44),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token4] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [44] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [45] = {
        [ts_aux_sym_token4] = SHIFT(46),
    },
    [46] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [47] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(48),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [48] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(49),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [49] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    [50] = {
        [ts_sym_identifier] = SHIFT(51),
    },
    [51] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [52] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [53] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(54),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [54] = {
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [55] = {
        [ts_sym_identifier] = SHIFT(56),
        [ts_sym_string] = SHIFT(56),
        [ts_aux_sym_token2] = SHIFT(199),
        [ts_builtin_sym_error] = SHIFT(200),
    },
    [56] = {
        [ts_aux_sym_token5] = SHIFT(57),
    },
    [57] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(196),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [58] = {
        [ts_sym_formal_parameters] = SHIFT(59),
        [ts_sym_identifier] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [59] = {
        [ts_sym_statement_block] = SHIFT(60),
        [ts_aux_sym_token1] = SHIFT(61),
    },
    [60] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [61] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(190),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(192),
    },
    [62] = {
        [ts_sym_assignment] = SHIFT(63),
        [ts_sym_identifier] = SHIFT(65),
    },
    [63] = {
        [ts_sym__terminator] = SHIFT(64),
    },
    [64] = {
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
    [65] = {
        [ts_sym__terminator] = SHIFT(64),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [66] = {
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
    [67] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [68] = {
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
    [69] = {
        [ts_sym_identifier] = SHIFT(70),
    },
    [70] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [71] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [72] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(73),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
    },
    [73] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [74] = {
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_string] = SHIFT(75),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_builtin_sym_error] = SHIFT(189),
    },
    [75] = {
        [ts_aux_sym_token5] = SHIFT(76),
    },
    [76] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [77] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [78] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [79] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(80),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [80] = {
        [ts_aux_sym_token2] = SHIFT(81),
    },
    [81] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [82] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(83),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token4] = SHIFT(86),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [83] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(84),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [84] = {
        [ts_aux_sym_token4] = SHIFT(85),
    },
    [85] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [86] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [87] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(184),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token10] = SHIFT(187),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(188),
    },
    [88] = {
        [ts_sym_formal_parameters] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(173),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [89] = {
        [ts_sym_statement_block] = SHIFT(90),
        [ts_aux_sym_token1] = SHIFT(91),
    },
    [90] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [91] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(170),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(172),
    },
    [92] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(93),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(169),
    },
    [93] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    [94] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(95),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(96),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(97),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(166),
    },
    [95] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(76),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [96] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = SHIFT(76),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [97] = {
        [ts_aux_sym_token2] = SHIFT(98),
    },
    [98] = {
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
    [99] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [100] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(103),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token10] = SHIFT(164),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(165),
    },
    [101] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [102] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [103] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(104),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [104] = {
        [ts_aux_sym_token10] = SHIFT(105),
    },
    [105] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [106] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(107),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token4] = SHIFT(110),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [107] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [108] = {
        [ts_aux_sym_token4] = SHIFT(109),
    },
    [109] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [110] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [111] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(163),
    },
    [112] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(113),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [113] = {
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 3),
    },
    [114] = {
        [ts_sym_identifier] = SHIFT(115),
    },
    [115] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [116] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(117),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [117] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(118),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token9] = SHIFT(146),
    },
    [118] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [119] = {
        [ts_sym_identifier] = SHIFT(120),
        [ts_sym_string] = SHIFT(120),
        [ts_aux_sym_token2] = SHIFT(159),
        [ts_builtin_sym_error] = SHIFT(160),
    },
    [120] = {
        [ts_aux_sym_token5] = SHIFT(121),
    },
    [121] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(122),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [122] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(123),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [123] = {
        [ts_aux_sym_token2] = SHIFT(124),
    },
    [124] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [125] = {
        [ts_sym_identifier] = SHIFT(126),
        [ts_sym_string] = SHIFT(126),
        [ts_builtin_sym_error] = SHIFT(157),
    },
    [126] = {
        [ts_aux_sym_token5] = SHIFT(127),
    },
    [127] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(128),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [128] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(129),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [129] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 5),
    },
    [130] = {
        [ts_sym_identifier] = SHIFT(131),
    },
    [131] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [132] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(133),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [133] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(134),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [134] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [135] = {
        [ts_sym_identifier] = SHIFT(136),
        [ts_sym_string] = SHIFT(136),
        [ts_aux_sym_token2] = SHIFT(153),
        [ts_builtin_sym_error] = SHIFT(154),
    },
    [136] = {
        [ts_aux_sym_token5] = SHIFT(137),
    },
    [137] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(138),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [138] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(139),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [139] = {
        [ts_aux_sym_token2] = SHIFT(140),
    },
    [140] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [141] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token10] = SHIFT(145),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(152),
    },
    [142] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(143),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [143] = {
        [ts_aux_sym_token10] = SHIFT(144),
    },
    [144] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [145] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [146] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(147),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token10] = SHIFT(150),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(151),
    },
    [147] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [148] = {
        [ts_aux_sym_token10] = SHIFT(149),
    },
    [149] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [150] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [151] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [152] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(143),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [153] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [154] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(155),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [155] = {
        [ts_aux_sym_token2] = SHIFT(156),
    },
    [156] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [157] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(158),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [158] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 3),
    },
    [159] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [160] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(161),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [161] = {
        [ts_aux_sym_token2] = SHIFT(162),
    },
    [162] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [163] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(113),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [164] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [165] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(104),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [166] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [167] = {
        [ts_aux_sym_token2] = SHIFT(168),
    },
    [168] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [169] = {
        [ts_sym__terminator] = SHIFT(68),
    },
    [170] = {
        [ts_aux_sym_token2] = SHIFT(171),
    },
    [171] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [172] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token2] = SHIFT(171),
    },
    [173] = {
        [ts_sym_formal_parameters] = SHIFT(174),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [174] = {
        [ts_sym_statement_block] = SHIFT(175),
        [ts_aux_sym_token1] = SHIFT(91),
    },
    [175] = {
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [176] = {
        [ts_sym_identifier] = SHIFT(177),
        [ts_aux_sym_token4] = SHIFT(183),
    },
    [177] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(178),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = SHIFT(180),
    },
    [178] = {
        [ts_aux_sym_token4] = SHIFT(179),
    },
    [179] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [180] = {
        [ts_sym_identifier] = SHIFT(181),
    },
    [181] = {
        [ts_aux_sym_repeat_helper6] = SHIFT(182),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = SHIFT(180),
    },
    [182] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    [183] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [184] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(185),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [185] = {
        [ts_aux_sym_token10] = SHIFT(186),
    },
    [186] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [187] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [188] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(185),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [189] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [190] = {
        [ts_aux_sym_token2] = SHIFT(191),
    },
    [191] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [192] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token2] = SHIFT(191),
    },
    [193] = {
        [ts_sym_formal_parameters] = SHIFT(194),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [194] = {
        [ts_sym_statement_block] = SHIFT(195),
        [ts_aux_sym_token1] = SHIFT(61),
    },
    [195] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [196] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(197),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [197] = {
        [ts_aux_sym_token2] = SHIFT(198),
    },
    [198] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [199] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [200] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(201),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [201] = {
        [ts_aux_sym_token2] = SHIFT(202),
    },
    [202] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [203] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [204] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [205] = {
        [ts_aux_sym_token1] = SHIFT(206),
    },
    [206] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(356),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [207] = {
        [ts_sym__function] = SHIFT(208),
        [ts_sym_array] = SHIFT(218),
        [ts_sym_assignment] = SHIFT(219),
        [ts_sym_expression] = SHIFT(220),
        [ts_sym_false] = SHIFT(218),
        [ts_sym_function_call] = SHIFT(219),
        [ts_sym_function_expression] = SHIFT(219),
        [ts_sym_identifier] = SHIFT(337),
        [ts_sym_literal] = SHIFT(219),
        [ts_sym_null] = SHIFT(218),
        [ts_sym_number] = SHIFT(218),
        [ts_sym_object] = SHIFT(218),
        [ts_sym_property_access] = SHIFT(219),
        [ts_sym_string] = SHIFT(218),
        [ts_sym_true] = SHIFT(218),
        [ts_aux_sym_token1] = SHIFT(340),
        [ts_aux_sym_token9] = SHIFT(350),
    },
    [208] = {
        [ts_sym_formal_parameters] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(215),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [209] = {
        [ts_sym_statement_block] = SHIFT(210),
        [ts_aux_sym_token1] = SHIFT(211),
    },
    [210] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [211] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(212),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper2, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(214),
    },
    [212] = {
        [ts_aux_sym_token2] = SHIFT(213),
    },
    [213] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [214] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token2] = SHIFT(213),
    },
    [215] = {
        [ts_sym_formal_parameters] = SHIFT(216),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [216] = {
        [ts_sym_statement_block] = SHIFT(217),
        [ts_aux_sym_token1] = SHIFT(211),
    },
    [217] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [218] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [219] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [220] = {
        [ts_aux_sym_token3] = SHIFT(221),
        [ts_aux_sym_token5] = SHIFT(226),
        [ts_aux_sym_token8] = SHIFT(335),
    },
    [221] = {
        [ts_sym__function] = SHIFT(22),
        [ts_sym_array] = SHIFT(38),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_expression] = SHIFT(222),
        [ts_sym_false] = SHIFT(38),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_identifier] = SHIFT(52),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_null] = SHIFT(38),
        [ts_sym_number] = SHIFT(38),
        [ts_sym_object] = SHIFT(38),
        [ts_sym_property_access] = SHIFT(39),
        [ts_sym_string] = SHIFT(38),
        [ts_sym_true] = SHIFT(38),
        [ts_aux_sym_token1] = SHIFT(55),
        [ts_aux_sym_token4] = SHIFT(225),
        [ts_aux_sym_token9] = SHIFT(87),
    },
    [222] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(223),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [223] = {
        [ts_aux_sym_token4] = SHIFT(224),
    },
    [224] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [225] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [226] = {
        [ts_sym__break] = SHIFT(227),
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__for] = SHIFT(229),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(237),
        [ts_sym__switch] = SHIFT(260),
        [ts_sym__var] = SHIFT(291),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(295),
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_expression_statement] = SHIFT(295),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(295),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(295),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(298),
        [ts_sym_statement_block] = SHIFT(295),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(295),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(295),
        [ts_aux_sym_repeat_helper4] = SHIFT(334),
        [ts_aux_sym_token1] = SHIFT(300),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(304),
    },
    [227] = {
        [ts_sym__terminator] = SHIFT(228),
    },
    [228] = {
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
    [229] = {
        [ts_aux_sym_token3] = SHIFT(230),
    },
    [230] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(233),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [231] = {
        [ts_sym__terminator] = SHIFT(232),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [232] = {
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
    [233] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(234),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [234] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(333),
    },
    [235] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(236),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [236] = {
        [ts_sym__break] = SHIFT(227),
        [ts_sym__for] = SHIFT(229),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(237),
        [ts_sym__switch] = SHIFT(260),
        [ts_sym__var] = SHIFT(291),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(295),
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_expression_statement] = SHIFT(295),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(295),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(295),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(332),
        [ts_sym_statement_block] = SHIFT(295),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(295),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(295),
        [ts_aux_sym_token1] = SHIFT(300),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(304),
    },
    [237] = {
        [ts_aux_sym_token3] = SHIFT(238),
    },
    [238] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(239),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(331),
    },
    [239] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(240),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [240] = {
        [ts_sym__break] = SHIFT(241),
        [ts_sym__for] = SHIFT(243),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(249),
        [ts_sym__switch] = SHIFT(253),
        [ts_sym__var] = SHIFT(309),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(313),
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_expression_statement] = SHIFT(313),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(313),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(313),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(328),
        [ts_sym_statement_block] = SHIFT(313),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(313),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(313),
        [ts_aux_sym_token1] = SHIFT(319),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(323),
    },
    [241] = {
        [ts_sym__terminator] = SHIFT(242),
    },
    [242] = {
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
    [243] = {
        [ts_aux_sym_token3] = SHIFT(244),
    },
    [244] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(245),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(245),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [245] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(246),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [246] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(247),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(326),
    },
    [247] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [248] = {
        [ts_sym__break] = SHIFT(241),
        [ts_sym__for] = SHIFT(243),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(249),
        [ts_sym__switch] = SHIFT(253),
        [ts_sym__var] = SHIFT(309),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(313),
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_expression_statement] = SHIFT(313),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(313),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(313),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(325),
        [ts_sym_statement_block] = SHIFT(313),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(313),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(313),
        [ts_aux_sym_token1] = SHIFT(319),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(323),
    },
    [249] = {
        [ts_aux_sym_token3] = SHIFT(250),
    },
    [250] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(251),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(324),
    },
    [251] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(252),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [252] = {
        [ts_sym__break] = SHIFT(241),
        [ts_sym__for] = SHIFT(243),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(249),
        [ts_sym__switch] = SHIFT(253),
        [ts_sym__var] = SHIFT(309),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(313),
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_expression_statement] = SHIFT(313),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(313),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(313),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(316),
        [ts_sym_statement_block] = SHIFT(313),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(313),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(313),
        [ts_aux_sym_token1] = SHIFT(319),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(323),
    },
    [253] = {
        [ts_aux_sym_token3] = SHIFT(254),
    },
    [254] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(255),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(308),
    },
    [255] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(256),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [256] = {
        [ts_aux_sym_token1] = SHIFT(257),
    },
    [257] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(306),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [258] = {
        [ts_aux_sym_token5] = SHIFT(259),
    },
    [259] = {
        [ts_sym__break] = SHIFT(227),
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__for] = SHIFT(229),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(237),
        [ts_sym__switch] = SHIFT(260),
        [ts_sym__var] = SHIFT(291),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(295),
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_expression_statement] = SHIFT(295),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(295),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(295),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(298),
        [ts_sym_statement_block] = SHIFT(295),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(295),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(295),
        [ts_aux_sym_repeat_helper4] = SHIFT(305),
        [ts_aux_sym_token1] = SHIFT(300),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(304),
    },
    [260] = {
        [ts_aux_sym_token3] = SHIFT(261),
    },
    [261] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(262),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(290),
    },
    [262] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(263),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [263] = {
        [ts_aux_sym_token1] = SHIFT(264),
    },
    [264] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(267),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [265] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(266),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [266] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 2),
    },
    [267] = {
        [ts_aux_sym_token2] = SHIFT(268),
    },
    [268] = {
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
    [269] = {
        [ts_sym_identifier] = SHIFT(270),
    },
    [270] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [271] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(272),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [272] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(273),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
    },
    [273] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [274] = {
        [ts_sym_identifier] = SHIFT(275),
        [ts_sym_string] = SHIFT(275),
        [ts_aux_sym_token2] = SHIFT(280),
        [ts_builtin_sym_error] = SHIFT(281),
    },
    [275] = {
        [ts_aux_sym_token5] = SHIFT(276),
    },
    [276] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(277),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [277] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(278),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [278] = {
        [ts_aux_sym_token2] = SHIFT(279),
    },
    [279] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [280] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [281] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(282),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [282] = {
        [ts_aux_sym_token2] = SHIFT(283),
    },
    [283] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [284] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(285),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token10] = SHIFT(288),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(289),
    },
    [285] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(286),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [286] = {
        [ts_aux_sym_token10] = SHIFT(287),
    },
    [287] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [288] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [289] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(286),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [290] = {
        [ts_aux_sym_token4] = SHIFT(263),
    },
    [291] = {
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_identifier] = SHIFT(294),
    },
    [292] = {
        [ts_sym__terminator] = SHIFT(293),
    },
    [293] = {
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
    [294] = {
        [ts_sym__terminator] = SHIFT(293),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [295] = {
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
    [296] = {
        [ts_sym__terminator] = SHIFT(297),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [297] = {
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
    [298] = {
        [ts_sym__break] = SHIFT(227),
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_sym__for] = SHIFT(229),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(237),
        [ts_sym__switch] = SHIFT(260),
        [ts_sym__var] = SHIFT(291),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(295),
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_expression_statement] = SHIFT(295),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(295),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(295),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(298),
        [ts_sym_statement_block] = SHIFT(295),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(295),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(295),
        [ts_aux_sym_repeat_helper4] = SHIFT(299),
        [ts_aux_sym_token1] = SHIFT(300),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 0),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(304),
    },
    [299] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_repeat_helper4, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_repeat_helper4, 2),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper4, 2),
    },
    [300] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(95),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(96),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(301),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(303),
    },
    [301] = {
        [ts_aux_sym_token2] = SHIFT(302),
    },
    [302] = {
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
    [303] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = SHIFT(302),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [304] = {
        [ts_sym__terminator] = SHIFT(297),
    },
    [305] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_case, 3),
    },
    [306] = {
        [ts_aux_sym_token2] = SHIFT(307),
    },
    [307] = {
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
    [308] = {
        [ts_aux_sym_token4] = SHIFT(256),
    },
    [309] = {
        [ts_sym_assignment] = SHIFT(310),
        [ts_sym_identifier] = SHIFT(312),
    },
    [310] = {
        [ts_sym__terminator] = SHIFT(311),
    },
    [311] = {
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
    [312] = {
        [ts_sym__terminator] = SHIFT(311),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [313] = {
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
    [314] = {
        [ts_sym__terminator] = SHIFT(315),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [315] = {
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
    [316] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(317),
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
    [317] = {
        [ts_sym__break] = SHIFT(241),
        [ts_sym__for] = SHIFT(243),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(249),
        [ts_sym__switch] = SHIFT(253),
        [ts_sym__var] = SHIFT(309),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(313),
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_expression_statement] = SHIFT(313),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(313),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(313),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(318),
        [ts_sym_statement_block] = SHIFT(313),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(313),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(313),
        [ts_aux_sym_token1] = SHIFT(319),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(323),
    },
    [318] = {
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
    [319] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(95),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(96),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(320),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(322),
    },
    [320] = {
        [ts_aux_sym_token2] = SHIFT(321),
    },
    [321] = {
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
    [322] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = SHIFT(321),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [323] = {
        [ts_sym__terminator] = SHIFT(315),
    },
    [324] = {
        [ts_aux_sym_token4] = SHIFT(252),
    },
    [325] = {
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
    [326] = {
        [ts_aux_sym_token4] = SHIFT(248),
    },
    [327] = {
        [ts_sym__terminator] = SHIFT(232),
    },
    [328] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(329),
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
    [329] = {
        [ts_sym__break] = SHIFT(227),
        [ts_sym__for] = SHIFT(229),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(237),
        [ts_sym__switch] = SHIFT(260),
        [ts_sym__var] = SHIFT(291),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(295),
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_expression_statement] = SHIFT(295),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(295),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(295),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(330),
        [ts_sym_statement_block] = SHIFT(295),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(295),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(295),
        [ts_aux_sym_token1] = SHIFT(300),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(304),
    },
    [330] = {
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
    [331] = {
        [ts_aux_sym_token4] = SHIFT(240),
    },
    [332] = {
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
    [333] = {
        [ts_aux_sym_token4] = SHIFT(236),
    },
    [334] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_case, 4),
    },
    [335] = {
        [ts_sym_identifier] = SHIFT(336),
    },
    [336] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [337] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(338),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [338] = {
        [ts_sym__function] = SHIFT(208),
        [ts_sym_array] = SHIFT(218),
        [ts_sym_assignment] = SHIFT(219),
        [ts_sym_expression] = SHIFT(339),
        [ts_sym_false] = SHIFT(218),
        [ts_sym_function_call] = SHIFT(219),
        [ts_sym_function_expression] = SHIFT(219),
        [ts_sym_identifier] = SHIFT(337),
        [ts_sym_literal] = SHIFT(219),
        [ts_sym_null] = SHIFT(218),
        [ts_sym_number] = SHIFT(218),
        [ts_sym_object] = SHIFT(218),
        [ts_sym_property_access] = SHIFT(219),
        [ts_sym_string] = SHIFT(218),
        [ts_sym_true] = SHIFT(218),
        [ts_aux_sym_token1] = SHIFT(340),
        [ts_aux_sym_token9] = SHIFT(350),
    },
    [339] = {
        [ts_aux_sym_token3] = SHIFT(221),
        [ts_aux_sym_token5] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(335),
    },
    [340] = {
        [ts_sym_identifier] = SHIFT(341),
        [ts_sym_string] = SHIFT(341),
        [ts_aux_sym_token2] = SHIFT(346),
        [ts_builtin_sym_error] = SHIFT(347),
    },
    [341] = {
        [ts_aux_sym_token5] = SHIFT(342),
    },
    [342] = {
        [ts_sym__function] = SHIFT(58),
        [ts_sym_array] = SHIFT(77),
        [ts_sym_assignment] = SHIFT(78),
        [ts_sym_expression] = SHIFT(343),
        [ts_sym_false] = SHIFT(77),
        [ts_sym_function_call] = SHIFT(78),
        [ts_sym_function_expression] = SHIFT(78),
        [ts_sym_identifier] = SHIFT(132),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_null] = SHIFT(77),
        [ts_sym_number] = SHIFT(77),
        [ts_sym_object] = SHIFT(77),
        [ts_sym_property_access] = SHIFT(78),
        [ts_sym_string] = SHIFT(77),
        [ts_sym_true] = SHIFT(77),
        [ts_aux_sym_token1] = SHIFT(135),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [343] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(344),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token3] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(125),
        [ts_aux_sym_token8] = SHIFT(130),
    },
    [344] = {
        [ts_aux_sym_token2] = SHIFT(345),
    },
    [345] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [346] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [347] = {
        [ts_aux_sym_repeat_helper7] = SHIFT(348),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [348] = {
        [ts_aux_sym_token2] = SHIFT(349),
    },
    [349] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [350] = {
        [ts_sym__function] = SHIFT(88),
        [ts_sym_array] = SHIFT(101),
        [ts_sym_assignment] = SHIFT(102),
        [ts_sym_expression] = SHIFT(351),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_function_call] = SHIFT(102),
        [ts_sym_function_expression] = SHIFT(102),
        [ts_sym_identifier] = SHIFT(116),
        [ts_sym_literal] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_number] = SHIFT(101),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_property_access] = SHIFT(102),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_aux_sym_token1] = SHIFT(119),
        [ts_aux_sym_token10] = SHIFT(354),
        [ts_aux_sym_token9] = SHIFT(146),
        [ts_builtin_sym_error] = SHIFT(355),
    },
    [351] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(352),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token3] = SHIFT(106),
        [ts_aux_sym_token7] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(114),
    },
    [352] = {
        [ts_aux_sym_token10] = SHIFT(353),
    },
    [353] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [354] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [355] = {
        [ts_aux_sym_repeat_helper8] = SHIFT(352),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [356] = {
        [ts_aux_sym_token2] = SHIFT(357),
    },
    [357] = {
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
    [358] = {
        [ts_aux_sym_token4] = SHIFT(205),
    },
    [359] = {
        [ts_aux_sym_token2] = SHIFT(360),
    },
    [360] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [361] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token2] = SHIFT(360),
    },
    [362] = {
        [ts_sym_formal_parameters] = SHIFT(363),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [363] = {
        [ts_sym_statement_block] = SHIFT(364),
        [ts_aux_sym_token1] = SHIFT(31),
    },
    [364] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [365] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(366),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [366] = {
        [ts_sym__break] = SHIFT(367),
        [ts_sym__for] = SHIFT(369),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(375),
        [ts_sym__switch] = SHIFT(379),
        [ts_sym__var] = SHIFT(387),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(391),
        [ts_sym_expression] = SHIFT(392),
        [ts_sym_expression_statement] = SHIFT(391),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(391),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(391),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(405),
        [ts_sym_statement_block] = SHIFT(391),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(391),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(391),
        [ts_aux_sym_token1] = SHIFT(397),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(401),
    },
    [367] = {
        [ts_sym__terminator] = SHIFT(368),
    },
    [368] = {
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
    [369] = {
        [ts_aux_sym_token3] = SHIFT(370),
    },
    [370] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(371),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(371),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [371] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(372),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [372] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(373),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(404),
    },
    [373] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(374),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [374] = {
        [ts_sym__break] = SHIFT(367),
        [ts_sym__for] = SHIFT(369),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(375),
        [ts_sym__switch] = SHIFT(379),
        [ts_sym__var] = SHIFT(387),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(391),
        [ts_sym_expression] = SHIFT(392),
        [ts_sym_expression_statement] = SHIFT(391),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(391),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(391),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(403),
        [ts_sym_statement_block] = SHIFT(391),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(391),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(391),
        [ts_aux_sym_token1] = SHIFT(397),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(401),
    },
    [375] = {
        [ts_aux_sym_token3] = SHIFT(376),
    },
    [376] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(377),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(402),
    },
    [377] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(378),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [378] = {
        [ts_sym__break] = SHIFT(367),
        [ts_sym__for] = SHIFT(369),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(375),
        [ts_sym__switch] = SHIFT(379),
        [ts_sym__var] = SHIFT(387),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(391),
        [ts_sym_expression] = SHIFT(392),
        [ts_sym_expression_statement] = SHIFT(391),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(391),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(391),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(394),
        [ts_sym_statement_block] = SHIFT(391),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(391),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(391),
        [ts_aux_sym_token1] = SHIFT(397),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(401),
    },
    [379] = {
        [ts_aux_sym_token3] = SHIFT(380),
    },
    [380] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(381),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(386),
    },
    [381] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(382),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [382] = {
        [ts_aux_sym_token1] = SHIFT(383),
    },
    [383] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(384),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [384] = {
        [ts_aux_sym_token2] = SHIFT(385),
    },
    [385] = {
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
    [386] = {
        [ts_aux_sym_token4] = SHIFT(382),
    },
    [387] = {
        [ts_sym_assignment] = SHIFT(388),
        [ts_sym_identifier] = SHIFT(390),
    },
    [388] = {
        [ts_sym__terminator] = SHIFT(389),
    },
    [389] = {
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
    [390] = {
        [ts_sym__terminator] = SHIFT(389),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [391] = {
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
    [392] = {
        [ts_sym__terminator] = SHIFT(393),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [393] = {
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
    [394] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(395),
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
    [395] = {
        [ts_sym__break] = SHIFT(367),
        [ts_sym__for] = SHIFT(369),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(375),
        [ts_sym__switch] = SHIFT(379),
        [ts_sym__var] = SHIFT(387),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(391),
        [ts_sym_expression] = SHIFT(392),
        [ts_sym_expression_statement] = SHIFT(391),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(391),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(391),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(396),
        [ts_sym_statement_block] = SHIFT(391),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(391),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(391),
        [ts_aux_sym_token1] = SHIFT(397),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(401),
    },
    [396] = {
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
    [397] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(95),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(96),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(398),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(400),
    },
    [398] = {
        [ts_aux_sym_token2] = SHIFT(399),
    },
    [399] = {
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
    [400] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [401] = {
        [ts_sym__terminator] = SHIFT(393),
    },
    [402] = {
        [ts_aux_sym_token4] = SHIFT(378),
    },
    [403] = {
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
    [404] = {
        [ts_aux_sym_token4] = SHIFT(374),
    },
    [405] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(406),
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
    [406] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(407),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(169),
    },
    [407] = {
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
    [408] = {
        [ts_aux_sym_token4] = SHIFT(366),
    },
    [409] = {
        [ts_aux_sym_token2] = SHIFT(410),
    },
    [410] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [411] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token2] = SHIFT(410),
    },
    [412] = {
        [ts_sym_formal_parameters] = SHIFT(413),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [413] = {
        [ts_sym_statement_block] = SHIFT(414),
        [ts_aux_sym_token1] = SHIFT(25),
    },
    [414] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [415] = {
        [ts_aux_sym_repeat_helper5] = SHIFT(416),
        [ts_aux_sym_token3] = SHIFT(43),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_repeat_helper5, 0),
        [ts_aux_sym_token7] = SHIFT(47),
        [ts_aux_sym_token8] = SHIFT(50),
    },
    [416] = {
        [ts_aux_sym_token4] = SHIFT(417),
    },
    [417] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [418] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [419] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(420),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [420] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(421),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(424),
    },
    [421] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(422),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [422] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(423),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(169),
    },
    [423] = {
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
    [424] = {
        [ts_aux_sym_token4] = SHIFT(422),
    },
    [425] = {
        [ts_aux_sym_token2] = SHIFT(426),
    },
    [426] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [427] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_token2] = SHIFT(426),
    },
    [428] = {
        [ts_sym_formal_parameters] = SHIFT(429),
        [ts_aux_sym_token3] = SHIFT(176),
    },
    [429] = {
        [ts_sym_statement_block] = SHIFT(430),
        [ts_aux_sym_token1] = SHIFT(8),
    },
    [430] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [431] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(432),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [432] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(433),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(502),
    },
    [433] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(434),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [434] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(435),
        [ts_sym__switch] = SHIFT(479),
        [ts_sym__var] = SHIFT(487),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(491),
        [ts_sym_expression] = SHIFT(492),
        [ts_sym_expression_statement] = SHIFT(491),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(491),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(491),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(501),
        [ts_sym_statement_block] = SHIFT(491),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(491),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(491),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [435] = {
        [ts_aux_sym_token3] = SHIFT(436),
    },
    [436] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(437),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(500),
    },
    [437] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(438),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [438] = {
        [ts_sym__break] = SHIFT(439),
        [ts_sym__for] = SHIFT(441),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(447),
        [ts_sym__switch] = SHIFT(451),
        [ts_sym__var] = SHIFT(459),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(463),
        [ts_sym_expression] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(463),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(463),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(463),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(477),
        [ts_sym_statement_block] = SHIFT(463),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(463),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(463),
        [ts_aux_sym_token1] = SHIFT(469),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(473),
    },
    [439] = {
        [ts_sym__terminator] = SHIFT(440),
    },
    [440] = {
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
    [441] = {
        [ts_aux_sym_token3] = SHIFT(442),
    },
    [442] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym__var] = SHIFT(13),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(443),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(443),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [443] = {
        [ts_sym__function] = SHIFT(5),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_expression_statement] = SHIFT(444),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_true] = SHIFT(18),
        [ts_aux_sym_token1] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(327),
    },
    [444] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(445),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(476),
    },
    [445] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(446),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [446] = {
        [ts_sym__break] = SHIFT(439),
        [ts_sym__for] = SHIFT(441),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(447),
        [ts_sym__switch] = SHIFT(451),
        [ts_sym__var] = SHIFT(459),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(463),
        [ts_sym_expression] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(463),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(463),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(463),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(475),
        [ts_sym_statement_block] = SHIFT(463),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(463),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(463),
        [ts_aux_sym_token1] = SHIFT(469),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(473),
    },
    [447] = {
        [ts_aux_sym_token3] = SHIFT(448),
    },
    [448] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(474),
    },
    [449] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(450),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [450] = {
        [ts_sym__break] = SHIFT(439),
        [ts_sym__for] = SHIFT(441),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(447),
        [ts_sym__switch] = SHIFT(451),
        [ts_sym__var] = SHIFT(459),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(463),
        [ts_sym_expression] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(463),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(463),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(463),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(466),
        [ts_sym_statement_block] = SHIFT(463),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(463),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(463),
        [ts_aux_sym_token1] = SHIFT(469),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(473),
    },
    [451] = {
        [ts_aux_sym_token3] = SHIFT(452),
    },
    [452] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(453),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(458),
    },
    [453] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(454),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [454] = {
        [ts_aux_sym_token1] = SHIFT(455),
    },
    [455] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(456),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [456] = {
        [ts_aux_sym_token2] = SHIFT(457),
    },
    [457] = {
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
    [458] = {
        [ts_aux_sym_token4] = SHIFT(454),
    },
    [459] = {
        [ts_sym_assignment] = SHIFT(460),
        [ts_sym_identifier] = SHIFT(462),
    },
    [460] = {
        [ts_sym__terminator] = SHIFT(461),
    },
    [461] = {
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
    [462] = {
        [ts_sym__terminator] = SHIFT(461),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [463] = {
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
    [464] = {
        [ts_sym__terminator] = SHIFT(465),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [465] = {
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
    [466] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(467),
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
    [467] = {
        [ts_sym__break] = SHIFT(439),
        [ts_sym__for] = SHIFT(441),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(447),
        [ts_sym__switch] = SHIFT(451),
        [ts_sym__var] = SHIFT(459),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(463),
        [ts_sym_expression] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(463),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(463),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(463),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(468),
        [ts_sym_statement_block] = SHIFT(463),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(463),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(463),
        [ts_aux_sym_token1] = SHIFT(469),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(473),
    },
    [468] = {
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
    [469] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(95),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(96),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(470),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(472),
    },
    [470] = {
        [ts_aux_sym_token2] = SHIFT(471),
    },
    [471] = {
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
    [472] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = SHIFT(471),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [473] = {
        [ts_sym__terminator] = SHIFT(465),
    },
    [474] = {
        [ts_aux_sym_token4] = SHIFT(450),
    },
    [475] = {
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
    [476] = {
        [ts_aux_sym_token4] = SHIFT(446),
    },
    [477] = {
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(478),
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
    [478] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(435),
        [ts_sym__switch] = SHIFT(479),
        [ts_sym__var] = SHIFT(487),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(491),
        [ts_sym_expression] = SHIFT(492),
        [ts_sym_expression_statement] = SHIFT(491),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(491),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(491),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(494),
        [ts_sym_statement_block] = SHIFT(491),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(491),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(491),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [479] = {
        [ts_aux_sym_token3] = SHIFT(480),
    },
    [480] = {
        [ts_sym__function] = SHIFT(28),
        [ts_sym_array] = SHIFT(34),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_false] = SHIFT(34),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_literal] = SHIFT(35),
        [ts_sym_null] = SHIFT(34),
        [ts_sym_number] = SHIFT(34),
        [ts_sym_object] = SHIFT(34),
        [ts_sym_property_access] = SHIFT(35),
        [ts_sym_string] = SHIFT(34),
        [ts_sym_true] = SHIFT(34),
        [ts_aux_sym_token1] = SHIFT(274),
        [ts_aux_sym_token9] = SHIFT(284),
        [ts_builtin_sym_error] = SHIFT(486),
    },
    [481] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token4] = SHIFT(482),
        [ts_aux_sym_token8] = SHIFT(269),
    },
    [482] = {
        [ts_aux_sym_token1] = SHIFT(483),
    },
    [483] = {
        [ts_sym__case] = SHIFT(207),
        [ts_sym__default] = SHIFT(258),
        [ts_sym_switch_case] = SHIFT(265),
        [ts_aux_sym_repeat_helper3] = SHIFT(484),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [484] = {
        [ts_aux_sym_token2] = SHIFT(485),
    },
    [485] = {
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
    [486] = {
        [ts_aux_sym_token4] = SHIFT(482),
    },
    [487] = {
        [ts_sym_assignment] = SHIFT(488),
        [ts_sym_identifier] = SHIFT(490),
    },
    [488] = {
        [ts_sym__terminator] = SHIFT(489),
    },
    [489] = {
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
    [490] = {
        [ts_sym__terminator] = SHIFT(489),
        [ts_aux_sym_token6] = SHIFT(17),
    },
    [491] = {
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
    [492] = {
        [ts_sym__terminator] = SHIFT(493),
        [ts_aux_sym_token3] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [493] = {
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
    [494] = {
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
    [495] = {
        [ts_sym__break] = SHIFT(9),
        [ts_sym__for] = SHIFT(11),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(26),
        [ts_sym__switch] = SHIFT(32),
        [ts_sym__var] = SHIFT(62),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(66),
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_expression_statement] = SHIFT(66),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(66),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(95),
        [ts_sym_if_statement] = SHIFT(66),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(92),
        [ts_sym_statement_block] = SHIFT(66),
        [ts_sym_string] = SHIFT(96),
        [ts_sym_switch_statement] = SHIFT(66),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(66),
        [ts_aux_sym_repeat_helper2] = SHIFT(496),
        [ts_aux_sym_token1] = SHIFT(94),
        [ts_aux_sym_token2] = SHIFT(99),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_error] = SHIFT(498),
    },
    [496] = {
        [ts_aux_sym_token2] = SHIFT(497),
    },
    [497] = {
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
    [498] = {
        [ts_sym__terminator] = SHIFT(68),
        [ts_aux_sym_repeat_helper7] = SHIFT(167),
        [ts_aux_sym_token2] = SHIFT(497),
        [ts_aux_sym_token7] = SHIFT(125),
    },
    [499] = {
        [ts_sym__terminator] = SHIFT(493),
    },
    [500] = {
        [ts_aux_sym_token4] = SHIFT(438),
    },
    [501] = {
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
    [502] = {
        [ts_aux_sym_token4] = SHIFT(434),
    },
    [503] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [504] = {
        [ts_sym__break] = SHIFT(1),
        [ts_sym__for] = SHIFT(3),
        [ts_sym__function] = SHIFT(5),
        [ts_sym__if] = SHIFT(435),
        [ts_sym__switch] = SHIFT(479),
        [ts_sym__var] = SHIFT(487),
        [ts_sym_array] = SHIFT(18),
        [ts_sym_assignment] = SHIFT(19),
        [ts_sym_break_statement] = SHIFT(491),
        [ts_sym_expression] = SHIFT(492),
        [ts_sym_expression_statement] = SHIFT(491),
        [ts_sym_false] = SHIFT(18),
        [ts_sym_for_statement] = SHIFT(491),
        [ts_sym_function_call] = SHIFT(19),
        [ts_sym_function_expression] = SHIFT(19),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_if_statement] = SHIFT(491),
        [ts_sym_literal] = SHIFT(19),
        [ts_sym_null] = SHIFT(18),
        [ts_sym_number] = SHIFT(18),
        [ts_sym_object] = SHIFT(18),
        [ts_sym_property_access] = SHIFT(19),
        [ts_sym_statement] = SHIFT(504),
        [ts_sym_statement_block] = SHIFT(491),
        [ts_sym_string] = SHIFT(18),
        [ts_sym_switch_statement] = SHIFT(491),
        [ts_sym_true] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(491),
        [ts_aux_sym_repeat_helper1] = SHIFT(505),
        [ts_aux_sym_token1] = SHIFT(495),
        [ts_aux_sym_token9] = SHIFT(100),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_builtin_sym_error] = SHIFT(499),
    },
    [505] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    [506] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
