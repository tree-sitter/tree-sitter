#include "tree_sitter/parser.h"

#define STATE_COUNT 679
#define SYMBOL_COUNT 62

enum {
    ts_sym_program = 2,
    ts_sym_statement = 3,
    ts_sym_statement_block = 4,
    ts_sym_for_statement = 5,
    ts_sym_if_statement = 6,
    ts_sym_switch_statement = 7,
    ts_sym_switch_case = 8,
    ts_sym_break_statement = 9,
    ts_sym_var_declaration = 10,
    ts_sym_expression_statement = 11,
    ts_sym_expression = 12,
    ts_sym_math_op = 13,
    ts_sym_ternary = 14,
    ts_sym_assignment = 15,
    ts_sym_function_expression = 16,
    ts_sym_function_call = 17,
    ts_sym_property_access = 18,
    ts_sym_formal_parameters = 19,
    ts_sym_literal = 20,
    ts_sym_object = 21,
    ts_sym_array = 22,
    ts_sym__break = 23,
    ts_sym__case = 24,
    ts_sym__default = 25,
    ts_sym__else = 26,
    ts_sym__for = 27,
    ts_sym__function = 28,
    ts_sym__if = 29,
    ts_sym__switch = 30,
    ts_sym__var = 31,
    ts_sym_null = 32,
    ts_sym_true = 33,
    ts_sym_false = 34,
    ts_sym__terminator = 35,
    ts_sym_string = 36,
    ts_sym_identifier = 37,
    ts_sym_number = 38,
    ts_aux_sym_program_repeat0 = 39,
    ts_aux_sym_statement_block_repeat0 = 40,
    ts_aux_sym_switch_statement_repeat0 = 41,
    ts_aux_sym_switch_case_repeat0 = 42,
    ts_aux_sym_function_call_repeat0 = 43,
    ts_aux_sym_formal_parameters_repeat0 = 44,
    ts_aux_sym_object_repeat0 = 45,
    ts_aux_sym_array_repeat0 = 46,
    ts_aux_sym_token0 = 47,
    ts_aux_sym_token1 = 48,
    ts_aux_sym_token2 = 49,
    ts_aux_sym_token3 = 50,
    ts_aux_sym_token4 = 51,
    ts_aux_sym_token5 = 52,
    ts_aux_sym_token6 = 53,
    ts_aux_sym_token7 = 54,
    ts_aux_sym_token8 = 55,
    ts_aux_sym_token9 = 56,
    ts_aux_sym_token10 = 57,
    ts_aux_sym_token11 = 58,
    ts_aux_sym_token12 = 59,
    ts_aux_sym_token13 = 60,
    ts_aux_sym_token14 = 61,
};

SYMBOL_NAMES = {
    [ts_sym_program] = "program",
    [ts_sym_statement] = "statement",
    [ts_sym_statement_block] = "statement_block",
    [ts_sym_for_statement] = "for_statement",
    [ts_sym_if_statement] = "if_statement",
    [ts_sym_switch_statement] = "switch_statement",
    [ts_sym_switch_case] = "switch_case",
    [ts_sym_break_statement] = "break_statement",
    [ts_sym_var_declaration] = "var_declaration",
    [ts_sym_expression_statement] = "expression_statement",
    [ts_sym_expression] = "expression",
    [ts_sym_math_op] = "math_op",
    [ts_sym_ternary] = "ternary",
    [ts_sym_assignment] = "assignment",
    [ts_sym_function_expression] = "function_expression",
    [ts_sym_function_call] = "function_call",
    [ts_sym_property_access] = "property_access",
    [ts_sym_formal_parameters] = "formal_parameters",
    [ts_sym_literal] = "literal",
    [ts_sym_object] = "object",
    [ts_sym_array] = "array",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym__break] = "_break",
    [ts_sym__case] = "_case",
    [ts_sym__default] = "_default",
    [ts_sym__else] = "_else",
    [ts_sym__for] = "_for",
    [ts_sym__function] = "_function",
    [ts_sym__if] = "_if",
    [ts_sym__switch] = "_switch",
    [ts_sym__var] = "_var",
    [ts_sym_null] = "null",
    [ts_sym_true] = "true",
    [ts_sym_false] = "false",
    [ts_sym__terminator] = "_terminator",
    [ts_sym_string] = "string",
    [ts_sym_identifier] = "identifier",
    [ts_sym_number] = "number",
    [ts_aux_sym_program_repeat0] = "program_repeat0",
    [ts_aux_sym_statement_block_repeat0] = "statement_block_repeat0",
    [ts_aux_sym_switch_statement_repeat0] = "switch_statement_repeat0",
    [ts_aux_sym_switch_case_repeat0] = "switch_case_repeat0",
    [ts_aux_sym_function_call_repeat0] = "function_call_repeat0",
    [ts_aux_sym_formal_parameters_repeat0] = "formal_parameters_repeat0",
    [ts_aux_sym_object_repeat0] = "object_repeat0",
    [ts_aux_sym_array_repeat0] = "array_repeat0",
    [ts_aux_sym_token0] = "'{'",
    [ts_aux_sym_token1] = "'}'",
    [ts_aux_sym_token2] = "'('",
    [ts_aux_sym_token3] = "')'",
    [ts_aux_sym_token4] = "':'",
    [ts_aux_sym_token5] = "'*'",
    [ts_aux_sym_token6] = "'/'",
    [ts_aux_sym_token7] = "'+'",
    [ts_aux_sym_token8] = "'-'",
    [ts_aux_sym_token9] = "'?'",
    [ts_aux_sym_token10] = "'='",
    [ts_aux_sym_token11] = "','",
    [ts_aux_sym_token12] = "'.'",
    [ts_aux_sym_token13] = "'['",
    [ts_aux_sym_token14] = "']'",
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
    [ts_sym__var] = 1,
    [ts_sym__terminator] = 1,
    [ts_aux_sym_program_repeat0] = 1,
    [ts_aux_sym_statement_block_repeat0] = 1,
    [ts_aux_sym_switch_statement_repeat0] = 1,
    [ts_aux_sym_switch_case_repeat0] = 1,
    [ts_aux_sym_function_call_repeat0] = 1,
    [ts_aux_sym_formal_parameters_repeat0] = 1,
    [ts_aux_sym_object_repeat0] = 1,
    [ts_aux_sym_array_repeat0] = 1,
    [ts_aux_sym_token0] = 1,
    [ts_aux_sym_token1] = 1,
    [ts_aux_sym_token2] = 1,
    [ts_aux_sym_token3] = 1,
    [ts_aux_sym_token4] = 1,
    [ts_aux_sym_token5] = 1,
    [ts_aux_sym_token6] = 1,
    [ts_aux_sym_token7] = 1,
    [ts_aux_sym_token8] = 1,
    [ts_aux_sym_token9] = 1,
    [ts_aux_sym_token10] = 1,
    [ts_aux_sym_token11] = 1,
    [ts_aux_sym_token12] = 1,
    [ts_aux_sym_token13] = 1,
    [ts_aux_sym_token14] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 0:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 3:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(6);
            LEX_ERROR();
        case 4:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(6);
            LEX_ERROR();
        case 5:
            ACCEPT_TOKEN(ts_sym_string);
        case 6:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            if (lookahead == '\"')
                ADVANCE(7);
            if (lookahead == '\\')
                ADVANCE(6);
            LEX_ERROR();
        case 7:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(6);
            ACCEPT_TOKEN(ts_sym_string);
        case 8:
            if (lookahead == '.')
                ADVANCE(9);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            ACCEPT_TOKEN(ts_sym_number);
        case 9:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_number);
        case 11:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 12:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 13:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'r')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 14:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 15:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(16);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 16:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'k')
                ADVANCE(17);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 17:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__break);
        case 18:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(19);
            if (lookahead == 'o')
                ADVANCE(23);
            if (lookahead == 'u')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 21:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 22:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_false);
        case 23:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'r')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 24:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__for);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'c')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 't')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'i')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'o')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'n')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__function);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__if);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'u')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_null);
        case 38:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'v') ||
                ('x' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'w')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'i')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 't')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'c')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'h')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__switch);
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'r')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'u')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_true);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'r')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__var);
        case 51:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 52:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(52);
            if (lookahead == '\n')
                ADVANCE(53);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 53:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(52);
            if (lookahead == '\n')
                ADVANCE(53);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 56:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 58:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 60:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 61:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 62:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == ')')
                ADVANCE(63);
            LEX_ERROR();
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 64:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 66:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 67:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 68:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 69:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 70:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 71:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 72:
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 73:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 75:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '\n')
                ADVANCE(76);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
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
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 77:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(79);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(79);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '}')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\n')
                ADVANCE(81);
            if (lookahead == ';')
                ADVANCE(60);
            LEX_ERROR();
        case 81:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\n')
                ADVANCE(81);
            if (lookahead == ';')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 82:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 84:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 85:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 86:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 87:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 88:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(63);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 89:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 90:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 91:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 92:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(93);
            if (lookahead == 'd')
                ADVANCE(97);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 93:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 94:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 95:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 96:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__case);
        case 97:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 98:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 99:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 100:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'u')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 101:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 102:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 't')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 103:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__default);
        case 104:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 105:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 106:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(106);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 107:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '\n')
                ADVANCE(108);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '\n')
                ADVANCE(108);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '}')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 109:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == ':')
                ADVANCE(67);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 112:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == '\n')
                ADVANCE(114);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 114:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == '\n')
                ADVANCE(114);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '\n')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '\n')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 117:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 118:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == ',')
                ADVANCE(65);
            LEX_ERROR();
        case 119:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == ')')
                ADVANCE(63);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(54);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(54);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 123:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == 'c')
                ADVANCE(124);
            if (lookahead == 'd')
                ADVANCE(128);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 124:
            if (lookahead == 'a')
                ADVANCE(125);
            LEX_ERROR();
        case 125:
            if (lookahead == 's')
                ADVANCE(126);
            LEX_ERROR();
        case 126:
            if (lookahead == 'e')
                ADVANCE(127);
            LEX_ERROR();
        case 127:
            ACCEPT_TOKEN(ts_sym__case);
        case 128:
            if (lookahead == 'e')
                ADVANCE(129);
            LEX_ERROR();
        case 129:
            if (lookahead == 'f')
                ADVANCE(130);
            LEX_ERROR();
        case 130:
            if (lookahead == 'a')
                ADVANCE(131);
            LEX_ERROR();
        case 131:
            if (lookahead == 'u')
                ADVANCE(132);
            LEX_ERROR();
        case 132:
            if (lookahead == 'l')
                ADVANCE(133);
            LEX_ERROR();
        case 133:
            if (lookahead == 't')
                ADVANCE(134);
            LEX_ERROR();
        case 134:
            ACCEPT_TOKEN(ts_sym__default);
        case 135:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(93);
            if (lookahead == 'd')
                ADVANCE(97);
            if (lookahead == 'e')
                ADVANCE(138);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 138:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(139);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 139:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(140);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 140:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(141);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 141:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__else);
        case 142:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(138);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(138);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 146:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\n')
                ADVANCE(147);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(93);
            if (lookahead == 'd')
                ADVANCE(97);
            if (lookahead == 'e')
                ADVANCE(138);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 147:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\n')
                ADVANCE(147);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(93);
            if (lookahead == 'd')
                ADVANCE(97);
            if (lookahead == 'e')
                ADVANCE(138);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym__terminator);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\n')
                ADVANCE(147);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(55);
            if (lookahead == '+')
                ADVANCE(56);
            if (lookahead == ',')
                ADVANCE(65);
            if (lookahead == '-')
                ADVANCE(57);
            if (lookahead == '.')
                ADVANCE(58);
            if (lookahead == '/')
                ADVANCE(59);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(61);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(72);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(93);
            if (lookahead == 'd')
                ADVANCE(97);
            if (lookahead == 'e')
                ADVANCE(138);
            if (lookahead == 'f')
                ADVANCE(18);
            if (lookahead == 'i')
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 2,
    [1] = 0,
    [2] = 2,
    [3] = 2,
    [4] = 52,
    [5] = 2,
    [6] = 88,
    [7] = 64,
    [8] = 62,
    [9] = 52,
    [10] = 88,
    [11] = 64,
    [12] = 62,
    [13] = 64,
    [14] = 106,
    [15] = 64,
    [16] = 106,
    [17] = 64,
    [18] = 106,
    [19] = 66,
    [20] = 88,
    [21] = 64,
    [22] = 62,
    [23] = 66,
    [24] = 106,
    [25] = 64,
    [26] = 62,
    [27] = 70,
    [28] = 68,
    [29] = 106,
    [30] = 71,
    [31] = 88,
    [32] = 64,
    [33] = 62,
    [34] = 71,
    [35] = 64,
    [36] = 68,
    [37] = 106,
    [38] = 64,
    [39] = 64,
    [40] = 64,
    [41] = 121,
    [42] = 117,
    [43] = 64,
    [44] = 73,
    [45] = 73,
    [46] = 73,
    [47] = 52,
    [48] = 73,
    [49] = 106,
    [50] = 52,
    [51] = 106,
    [52] = 52,
    [53] = 106,
    [54] = 66,
    [55] = 106,
    [56] = 52,
    [57] = 70,
    [58] = 75,
    [59] = 106,
    [60] = 71,
    [61] = 106,
    [62] = 71,
    [63] = 106,
    [64] = 71,
    [65] = 106,
    [66] = 66,
    [67] = 106,
    [68] = 71,
    [69] = 70,
    [70] = 77,
    [71] = 106,
    [72] = 71,
    [73] = 77,
    [74] = 71,
    [75] = 77,
    [76] = 106,
    [77] = 71,
    [78] = 71,
    [79] = 71,
    [80] = 121,
    [81] = 117,
    [82] = 71,
    [83] = 73,
    [84] = 52,
    [85] = 75,
    [86] = 106,
    [87] = 52,
    [88] = 52,
    [89] = 52,
    [90] = 121,
    [91] = 117,
    [92] = 52,
    [93] = 73,
    [94] = 78,
    [95] = 52,
    [96] = 80,
    [97] = 73,
    [98] = 120,
    [99] = 142,
    [100] = 106,
    [101] = 106,
    [102] = 82,
    [103] = 88,
    [104] = 64,
    [105] = 62,
    [106] = 82,
    [107] = 111,
    [108] = 84,
    [109] = 83,
    [110] = 64,
    [111] = 144,
    [112] = 84,
    [113] = 83,
    [114] = 110,
    [115] = 106,
    [116] = 85,
    [117] = 83,
    [118] = 88,
    [119] = 64,
    [120] = 62,
    [121] = 85,
    [122] = 85,
    [123] = 112,
    [124] = 87,
    [125] = 86,
    [126] = 64,
    [127] = 88,
    [128] = 64,
    [129] = 62,
    [130] = 87,
    [131] = 87,
    [132] = 106,
    [133] = 87,
    [134] = 106,
    [135] = 87,
    [136] = 106,
    [137] = 66,
    [138] = 106,
    [139] = 87,
    [140] = 70,
    [141] = 90,
    [142] = 106,
    [143] = 71,
    [144] = 90,
    [145] = 111,
    [146] = 84,
    [147] = 83,
    [148] = 71,
    [149] = 110,
    [150] = 106,
    [151] = 85,
    [152] = 83,
    [153] = 71,
    [154] = 106,
    [155] = 85,
    [156] = 106,
    [157] = 85,
    [158] = 106,
    [159] = 66,
    [160] = 106,
    [161] = 85,
    [162] = 70,
    [163] = 91,
    [164] = 106,
    [165] = 71,
    [166] = 91,
    [167] = 112,
    [168] = 87,
    [169] = 86,
    [170] = 71,
    [171] = 106,
    [172] = 87,
    [173] = 86,
    [174] = 87,
    [175] = 90,
    [176] = 106,
    [177] = 87,
    [178] = 87,
    [179] = 87,
    [180] = 121,
    [181] = 117,
    [182] = 87,
    [183] = 73,
    [184] = 78,
    [185] = 87,
    [186] = 120,
    [187] = 106,
    [188] = 82,
    [189] = 136,
    [190] = 143,
    [191] = 136,
    [192] = 73,
    [193] = 80,
    [194] = 120,
    [195] = 106,
    [196] = 82,
    [197] = 117,
    [198] = 123,
    [199] = 123,
    [200] = 106,
    [201] = 66,
    [202] = 92,
    [203] = 92,
    [204] = 92,
    [205] = 52,
    [206] = 92,
    [207] = 80,
    [208] = 80,
    [209] = 92,
    [210] = 120,
    [211] = 142,
    [212] = 106,
    [213] = 106,
    [214] = 82,
    [215] = 136,
    [216] = 92,
    [217] = 120,
    [218] = 106,
    [219] = 82,
    [220] = 136,
    [221] = 137,
    [222] = 136,
    [223] = 92,
    [224] = 120,
    [225] = 106,
    [226] = 82,
    [227] = 117,
    [228] = 123,
    [229] = 110,
    [230] = 92,
    [231] = 106,
    [232] = 104,
    [233] = 88,
    [234] = 64,
    [235] = 62,
    [236] = 104,
    [237] = 104,
    [238] = 106,
    [239] = 104,
    [240] = 106,
    [241] = 104,
    [242] = 106,
    [243] = 66,
    [244] = 106,
    [245] = 104,
    [246] = 70,
    [247] = 105,
    [248] = 106,
    [249] = 71,
    [250] = 105,
    [251] = 104,
    [252] = 105,
    [253] = 106,
    [254] = 104,
    [255] = 104,
    [256] = 104,
    [257] = 121,
    [258] = 117,
    [259] = 104,
    [260] = 73,
    [261] = 78,
    [262] = 104,
    [263] = 106,
    [264] = 52,
    [265] = 73,
    [266] = 105,
    [267] = 75,
    [268] = 111,
    [269] = 84,
    [270] = 83,
    [271] = 104,
    [272] = 110,
    [273] = 106,
    [274] = 85,
    [275] = 83,
    [276] = 104,
    [277] = 85,
    [278] = 91,
    [279] = 106,
    [280] = 85,
    [281] = 85,
    [282] = 85,
    [283] = 121,
    [284] = 117,
    [285] = 85,
    [286] = 73,
    [287] = 78,
    [288] = 85,
    [289] = 83,
    [290] = 73,
    [291] = 107,
    [292] = 83,
    [293] = 52,
    [294] = 73,
    [295] = 113,
    [296] = 106,
    [297] = 85,
    [298] = 83,
    [299] = 52,
    [300] = 111,
    [301] = 84,
    [302] = 83,
    [303] = 85,
    [304] = 110,
    [305] = 106,
    [306] = 85,
    [307] = 83,
    [308] = 85,
    [309] = 112,
    [310] = 87,
    [311] = 86,
    [312] = 85,
    [313] = 109,
    [314] = 111,
    [315] = 84,
    [316] = 83,
    [317] = 87,
    [318] = 110,
    [319] = 106,
    [320] = 85,
    [321] = 83,
    [322] = 87,
    [323] = 87,
    [324] = 112,
    [325] = 87,
    [326] = 86,
    [327] = 87,
    [328] = 109,
    [329] = 87,
    [330] = 85,
    [331] = 85,
    [332] = 115,
    [333] = 83,
    [334] = 52,
    [335] = 112,
    [336] = 87,
    [337] = 86,
    [338] = 52,
    [339] = 109,
    [340] = 52,
    [341] = 120,
    [342] = 117,
    [343] = 85,
    [344] = 119,
    [345] = 118,
    [346] = 62,
    [347] = 117,
    [348] = 70,
    [349] = 118,
    [350] = 62,
    [351] = 117,
    [352] = 104,
    [353] = 112,
    [354] = 87,
    [355] = 86,
    [356] = 104,
    [357] = 109,
    [358] = 104,
    [359] = 83,
    [360] = 120,
    [361] = 117,
    [362] = 104,
    [363] = 106,
    [364] = 66,
    [365] = 106,
    [366] = 66,
    [367] = 106,
    [368] = 66,
    [369] = 106,
    [370] = 66,
    [371] = 70,
    [372] = 122,
    [373] = 106,
    [374] = 71,
    [375] = 122,
    [376] = 66,
    [377] = 122,
    [378] = 106,
    [379] = 66,
    [380] = 66,
    [381] = 66,
    [382] = 121,
    [383] = 117,
    [384] = 66,
    [385] = 73,
    [386] = 78,
    [387] = 66,
    [388] = 83,
    [389] = 120,
    [390] = 117,
    [391] = 66,
    [392] = 111,
    [393] = 84,
    [394] = 83,
    [395] = 66,
    [396] = 110,
    [397] = 106,
    [398] = 85,
    [399] = 83,
    [400] = 66,
    [401] = 66,
    [402] = 112,
    [403] = 87,
    [404] = 86,
    [405] = 66,
    [406] = 109,
    [407] = 66,
    [408] = 52,
    [409] = 92,
    [410] = 75,
    [411] = 123,
    [412] = 73,
    [413] = 107,
    [414] = 92,
    [415] = 83,
    [416] = 83,
    [417] = 92,
    [418] = 106,
    [419] = 82,
    [420] = 106,
    [421] = 82,
    [422] = 106,
    [423] = 66,
    [424] = 106,
    [425] = 82,
    [426] = 70,
    [427] = 135,
    [428] = 106,
    [429] = 71,
    [430] = 135,
    [431] = 82,
    [432] = 135,
    [433] = 106,
    [434] = 82,
    [435] = 82,
    [436] = 82,
    [437] = 121,
    [438] = 117,
    [439] = 82,
    [440] = 73,
    [441] = 78,
    [442] = 82,
    [443] = 83,
    [444] = 120,
    [445] = 117,
    [446] = 82,
    [447] = 111,
    [448] = 84,
    [449] = 83,
    [450] = 82,
    [451] = 110,
    [452] = 106,
    [453] = 85,
    [454] = 83,
    [455] = 82,
    [456] = 82,
    [457] = 112,
    [458] = 87,
    [459] = 86,
    [460] = 82,
    [461] = 109,
    [462] = 82,
    [463] = 62,
    [464] = 137,
    [465] = 52,
    [466] = 137,
    [467] = 80,
    [468] = 80,
    [469] = 137,
    [470] = 120,
    [471] = 142,
    [472] = 106,
    [473] = 106,
    [474] = 82,
    [475] = 136,
    [476] = 137,
    [477] = 120,
    [478] = 106,
    [479] = 82,
    [480] = 136,
    [481] = 137,
    [482] = 136,
    [483] = 137,
    [484] = 120,
    [485] = 106,
    [486] = 82,
    [487] = 117,
    [488] = 123,
    [489] = 83,
    [490] = 137,
    [491] = 62,
    [492] = 106,
    [493] = 52,
    [494] = 137,
    [495] = 75,
    [496] = 73,
    [497] = 107,
    [498] = 137,
    [499] = 83,
    [500] = 62,
    [501] = 62,
    [502] = 52,
    [503] = 106,
    [504] = 80,
    [505] = 111,
    [506] = 84,
    [507] = 110,
    [508] = 106,
    [509] = 52,
    [510] = 106,
    [511] = 75,
    [512] = 62,
    [513] = 62,
    [514] = 123,
    [515] = 123,
    [516] = 83,
    [517] = 83,
    [518] = 73,
    [519] = 62,
    [520] = 143,
    [521] = 52,
    [522] = 143,
    [523] = 80,
    [524] = 80,
    [525] = 143,
    [526] = 120,
    [527] = 142,
    [528] = 106,
    [529] = 106,
    [530] = 82,
    [531] = 136,
    [532] = 143,
    [533] = 120,
    [534] = 106,
    [535] = 82,
    [536] = 136,
    [537] = 143,
    [538] = 136,
    [539] = 143,
    [540] = 120,
    [541] = 106,
    [542] = 82,
    [543] = 117,
    [544] = 123,
    [545] = 83,
    [546] = 143,
    [547] = 62,
    [548] = 106,
    [549] = 52,
    [550] = 143,
    [551] = 75,
    [552] = 73,
    [553] = 107,
    [554] = 143,
    [555] = 83,
    [556] = 62,
    [557] = 62,
    [558] = 62,
    [559] = 83,
    [560] = 120,
    [561] = 117,
    [562] = 87,
    [563] = 109,
    [564] = 109,
    [565] = 71,
    [566] = 71,
    [567] = 109,
    [568] = 64,
    [569] = 110,
    [570] = 106,
    [571] = 85,
    [572] = 83,
    [573] = 64,
    [574] = 64,
    [575] = 82,
    [576] = 136,
    [577] = 73,
    [578] = 62,
    [579] = 83,
    [580] = 120,
    [581] = 117,
    [582] = 52,
    [583] = 78,
    [584] = 71,
    [585] = 83,
    [586] = 120,
    [587] = 117,
    [588] = 71,
    [589] = 75,
    [590] = 83,
    [591] = 78,
    [592] = 64,
    [593] = 83,
    [594] = 120,
    [595] = 117,
    [596] = 64,
    [597] = 71,
    [598] = 68,
    [599] = 66,
    [600] = 106,
    [601] = 64,
    [602] = 64,
    [603] = 52,
    [604] = 80,
    [605] = 80,
    [606] = 2,
    [607] = 120,
    [608] = 142,
    [609] = 106,
    [610] = 106,
    [611] = 82,
    [612] = 136,
    [613] = 2,
    [614] = 120,
    [615] = 106,
    [616] = 82,
    [617] = 136,
    [618] = 145,
    [619] = 136,
    [620] = 2,
    [621] = 120,
    [622] = 106,
    [623] = 82,
    [624] = 117,
    [625] = 123,
    [626] = 83,
    [627] = 2,
    [628] = 62,
    [629] = 106,
    [630] = 52,
    [631] = 2,
    [632] = 75,
    [633] = 73,
    [634] = 107,
    [635] = 2,
    [636] = 83,
    [637] = 145,
    [638] = 52,
    [639] = 145,
    [640] = 80,
    [641] = 80,
    [642] = 145,
    [643] = 120,
    [644] = 142,
    [645] = 106,
    [646] = 106,
    [647] = 82,
    [648] = 136,
    [649] = 145,
    [650] = 120,
    [651] = 106,
    [652] = 82,
    [653] = 136,
    [654] = 145,
    [655] = 136,
    [656] = 145,
    [657] = 120,
    [658] = 106,
    [659] = 82,
    [660] = 117,
    [661] = 123,
    [662] = 83,
    [663] = 145,
    [664] = 62,
    [665] = 106,
    [666] = 52,
    [667] = 145,
    [668] = 75,
    [669] = 73,
    [670] = 107,
    [671] = 145,
    [672] = 83,
    [673] = 62,
    [674] = 62,
    [675] = 62,
    [676] = 62,
    [677] = 0,
    [678] = 0,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_statement] = SHIFT(2),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(605),
        [ts_sym__for] = SHIFT(607),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(614),
        [ts_sym__switch] = SHIFT(621),
        [ts_sym__var] = SHIFT(629),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_program_repeat0] = SHIFT(678),
        [ts_aux_sym_token0] = SHIFT(633),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [2] = {
        [ts_sym_statement] = SHIFT(2),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(605),
        [ts_sym__for] = SHIFT(607),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(614),
        [ts_sym__switch] = SHIFT(621),
        [ts_sym__var] = SHIFT(629),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_program_repeat0] = SHIFT(677),
        [ts_aux_sym_token0] = SHIFT(633),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [3] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [4] = {
        [ts_sym__terminator] = SHIFT(5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [5] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [6] = {
        [ts_sym_expression] = SHIFT(7),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(603),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [7] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [8] = {
        [ts_aux_sym_token3] = SHIFT(9),
    },
    [9] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [10] = {
        [ts_sym_expression] = SHIFT(11),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(602),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [11] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [12] = {
        [ts_aux_sym_token3] = SHIFT(13),
    },
    [13] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [14] = {
        [ts_sym_expression] = SHIFT(15),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [15] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [16] = {
        [ts_sym_expression] = SHIFT(17),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [17] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [18] = {
        [ts_sym_expression] = SHIFT(19),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [19] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(600),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [20] = {
        [ts_sym_expression] = SHIFT(21),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(599),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [21] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(22),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [22] = {
        [ts_aux_sym_token3] = SHIFT(23),
    },
    [23] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [24] = {
        [ts_sym_expression] = SHIFT(25),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [25] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(26),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [26] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 3),
    },
    [27] = {
        [ts_sym_identifier] = SHIFT(28),
    },
    [28] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
    },
    [29] = {
        [ts_sym_expression] = SHIFT(30),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [30] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(598),
    },
    [31] = {
        [ts_sym_expression] = SHIFT(32),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(597),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [32] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(33),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [33] = {
        [ts_aux_sym_token3] = SHIFT(34),
    },
    [34] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
    },
    [35] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [36] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(37),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [37] = {
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [38] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [39] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [40] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [41] = {
        [ts_sym_formal_parameters] = SHIFT(42),
        [ts_sym_identifier] = SHIFT(594),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [42] = {
        [ts_sym_statement_block] = SHIFT(43),
        [ts_aux_sym_token0] = SHIFT(44),
    },
    [43] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [44] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(591),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(593),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [45] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(193),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(590),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [46] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [47] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [48] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [49] = {
        [ts_sym_expression] = SHIFT(50),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [50] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [51] = {
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [52] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [53] = {
        [ts_sym_expression] = SHIFT(54),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [54] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(55),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [55] = {
        [ts_sym_expression] = SHIFT(56),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [56] = {
        [ts_sym__terminator] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [57] = {
        [ts_sym_identifier] = SHIFT(58),
    },
    [58] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
    },
    [59] = {
        [ts_sym_expression] = SHIFT(60),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [60] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(589),
    },
    [61] = {
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [62] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_math_op, 3),
    },
    [63] = {
        [ts_sym_expression] = SHIFT(64),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [64] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_math_op, 3),
    },
    [65] = {
        [ts_sym_expression] = SHIFT(66),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [66] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(67),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [67] = {
        [ts_sym_expression] = SHIFT(68),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [68] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = REDUCE(ts_sym_ternary, 5),
    },
    [69] = {
        [ts_sym_identifier] = SHIFT(70),
    },
    [70] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 3),
    },
    [71] = {
        [ts_sym_expression] = SHIFT(72),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [72] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(73),
    },
    [73] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 4),
    },
    [74] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [75] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(76),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [76] = {
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [77] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = REDUCE(ts_sym_assignment, 3),
    },
    [78] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [79] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
    },
    [80] = {
        [ts_sym_formal_parameters] = SHIFT(81),
        [ts_sym_identifier] = SHIFT(586),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [81] = {
        [ts_sym_statement_block] = SHIFT(82),
        [ts_aux_sym_token0] = SHIFT(83),
    },
    [82] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
    },
    [83] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(583),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(585),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [84] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [85] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [86] = {
        [ts_sym_expression] = SHIFT(87),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [87] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [88] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [89] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [90] = {
        [ts_sym_formal_parameters] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(580),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [91] = {
        [ts_sym_statement_block] = SHIFT(92),
        [ts_aux_sym_token0] = SHIFT(93),
    },
    [92] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [93] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(94),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(579),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [94] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(95),
    },
    [95] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [96] = {
        [ts_sym__terminator] = SHIFT(97),
    },
    [97] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [98] = {
        [ts_aux_sym_token2] = SHIFT(99),
    },
    [99] = {
        [ts_sym_var_declaration] = SHIFT(100),
        [ts_sym_expression_statement] = SHIFT(100),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [100] = {
        [ts_sym_expression_statement] = SHIFT(101),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [101] = {
        [ts_sym_expression] = SHIFT(102),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(578),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [102] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(576),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [103] = {
        [ts_sym_expression] = SHIFT(104),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(575),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [104] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(105),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [105] = {
        [ts_aux_sym_token3] = SHIFT(106),
    },
    [106] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [107] = {
        [ts_builtin_sym_error] = SHIFT(108),
        [ts_sym_string] = SHIFT(569),
        [ts_sym_identifier] = SHIFT(569),
        [ts_aux_sym_token1] = SHIFT(574),
    },
    [108] = {
        [ts_aux_sym_object_repeat0] = SHIFT(109),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [109] = {
        [ts_aux_sym_token1] = SHIFT(110),
    },
    [110] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [111] = {
        [ts_builtin_sym_error] = SHIFT(112),
        [ts_sym_string] = SHIFT(114),
        [ts_sym_identifier] = SHIFT(114),
    },
    [112] = {
        [ts_aux_sym_object_repeat0] = SHIFT(113),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [113] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [114] = {
        [ts_aux_sym_token4] = SHIFT(115),
    },
    [115] = {
        [ts_sym_expression] = SHIFT(116),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [116] = {
        [ts_aux_sym_object_repeat0] = SHIFT(117),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [117] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [118] = {
        [ts_sym_expression] = SHIFT(119),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(122),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [119] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(120),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [120] = {
        [ts_aux_sym_token3] = SHIFT(121),
    },
    [121] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [122] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [123] = {
        [ts_sym_expression] = SHIFT(124),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(567),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(568),
    },
    [124] = {
        [ts_aux_sym_array_repeat0] = SHIFT(125),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [125] = {
        [ts_aux_sym_token14] = SHIFT(126),
    },
    [126] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [127] = {
        [ts_sym_expression] = SHIFT(128),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(131),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [128] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(129),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [129] = {
        [ts_aux_sym_token3] = SHIFT(130),
    },
    [130] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
    },
    [131] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
    },
    [132] = {
        [ts_sym_expression] = SHIFT(133),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
    },
    [133] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_math_op, 3),
    },
    [134] = {
        [ts_sym_expression] = SHIFT(135),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
    },
    [135] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_math_op, 3),
    },
    [136] = {
        [ts_sym_expression] = SHIFT(137),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [137] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(138),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [138] = {
        [ts_sym_expression] = SHIFT(139),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
    },
    [139] = {
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_sym_ternary, 5),
    },
    [140] = {
        [ts_sym_identifier] = SHIFT(141),
    },
    [141] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 3),
    },
    [142] = {
        [ts_sym_expression] = SHIFT(143),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [143] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(144),
    },
    [144] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 4),
    },
    [145] = {
        [ts_builtin_sym_error] = SHIFT(146),
        [ts_sym_string] = SHIFT(149),
        [ts_sym_identifier] = SHIFT(149),
        [ts_aux_sym_token1] = SHIFT(566),
    },
    [146] = {
        [ts_aux_sym_object_repeat0] = SHIFT(147),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [147] = {
        [ts_aux_sym_token1] = SHIFT(148),
    },
    [148] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
    },
    [149] = {
        [ts_aux_sym_token4] = SHIFT(150),
    },
    [150] = {
        [ts_sym_expression] = SHIFT(151),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [151] = {
        [ts_aux_sym_object_repeat0] = SHIFT(152),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [152] = {
        [ts_aux_sym_token1] = SHIFT(153),
    },
    [153] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
    },
    [154] = {
        [ts_sym_expression] = SHIFT(155),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [155] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [156] = {
        [ts_sym_expression] = SHIFT(157),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [157] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [158] = {
        [ts_sym_expression] = SHIFT(159),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [159] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(160),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [160] = {
        [ts_sym_expression] = SHIFT(161),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [161] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [162] = {
        [ts_sym_identifier] = SHIFT(163),
    },
    [163] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
    },
    [164] = {
        [ts_sym_expression] = SHIFT(165),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [165] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(166),
    },
    [166] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
    },
    [167] = {
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(564),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(565),
    },
    [168] = {
        [ts_aux_sym_array_repeat0] = SHIFT(169),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [169] = {
        [ts_aux_sym_token14] = SHIFT(170),
    },
    [170] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
    },
    [171] = {
        [ts_sym_expression] = SHIFT(172),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(563),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
    },
    [172] = {
        [ts_aux_sym_array_repeat0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [173] = {
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [174] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [175] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(176),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [176] = {
        [ts_sym_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
    },
    [177] = {
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_sym_assignment, 3),
    },
    [178] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [179] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
    },
    [180] = {
        [ts_sym_formal_parameters] = SHIFT(181),
        [ts_sym_identifier] = SHIFT(560),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [181] = {
        [ts_sym_statement_block] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(183),
    },
    [182] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
    },
    [183] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(184),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(559),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [184] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(185),
    },
    [185] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
    },
    [186] = {
        [ts_aux_sym_token2] = SHIFT(187),
    },
    [187] = {
        [ts_sym_expression] = SHIFT(188),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(558),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [188] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(189),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [189] = {
        [ts_sym_statement] = SHIFT(190),
        [ts_sym_statement_block] = SHIFT(520),
        [ts_sym_for_statement] = SHIFT(520),
        [ts_sym_if_statement] = SHIFT(520),
        [ts_sym_switch_statement] = SHIFT(520),
        [ts_sym_break_statement] = SHIFT(520),
        [ts_sym_var_declaration] = SHIFT(520),
        [ts_sym_expression_statement] = SHIFT(520),
        [ts_sym_expression] = SHIFT(521),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(523),
        [ts_sym__break] = SHIFT(524),
        [ts_sym__for] = SHIFT(526),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(533),
        [ts_sym__switch] = SHIFT(540),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(552),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [190] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(191),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [191] = {
        [ts_sym_statement] = SHIFT(192),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(193),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [192] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [193] = {
        [ts_sym__terminator] = SHIFT(48),
    },
    [194] = {
        [ts_aux_sym_token2] = SHIFT(195),
    },
    [195] = {
        [ts_sym_expression] = SHIFT(196),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(519),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [196] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(197),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [197] = {
        [ts_aux_sym_token0] = SHIFT(198),
    },
    [198] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(517),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [199] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(516),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [200] = {
        [ts_sym_expression] = SHIFT(201),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [201] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(202),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [202] = {
        [ts_sym_statement] = SHIFT(203),
        [ts_sym_statement_block] = SHIFT(204),
        [ts_sym_for_statement] = SHIFT(204),
        [ts_sym_if_statement] = SHIFT(204),
        [ts_sym_switch_statement] = SHIFT(204),
        [ts_sym_break_statement] = SHIFT(204),
        [ts_sym_var_declaration] = SHIFT(204),
        [ts_sym_expression_statement] = SHIFT(204),
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(207),
        [ts_sym__break] = SHIFT(208),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(210),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(217),
        [ts_sym__switch] = SHIFT(224),
        [ts_sym__var] = SHIFT(231),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(515),
        [ts_aux_sym_token0] = SHIFT(412),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [203] = {
        [ts_sym_statement] = SHIFT(203),
        [ts_sym_statement_block] = SHIFT(204),
        [ts_sym_for_statement] = SHIFT(204),
        [ts_sym_if_statement] = SHIFT(204),
        [ts_sym_switch_statement] = SHIFT(204),
        [ts_sym_break_statement] = SHIFT(204),
        [ts_sym_var_declaration] = SHIFT(204),
        [ts_sym_expression_statement] = SHIFT(204),
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(207),
        [ts_sym__break] = SHIFT(208),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(210),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(217),
        [ts_sym__switch] = SHIFT(224),
        [ts_sym__var] = SHIFT(231),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(514),
        [ts_aux_sym_token0] = SHIFT(412),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [204] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__case] = REDUCE(ts_sym_statement, 1),
        [ts_sym__default] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [205] = {
        [ts_sym__terminator] = SHIFT(206),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [206] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [207] = {
        [ts_sym__terminator] = SHIFT(206),
    },
    [208] = {
        [ts_sym__terminator] = SHIFT(209),
    },
    [209] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [210] = {
        [ts_aux_sym_token2] = SHIFT(211),
    },
    [211] = {
        [ts_sym_var_declaration] = SHIFT(212),
        [ts_sym_expression_statement] = SHIFT(212),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [212] = {
        [ts_sym_expression_statement] = SHIFT(213),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [213] = {
        [ts_sym_expression] = SHIFT(214),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(513),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [214] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(215),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [215] = {
        [ts_sym_statement] = SHIFT(216),
        [ts_sym_statement_block] = SHIFT(204),
        [ts_sym_for_statement] = SHIFT(204),
        [ts_sym_if_statement] = SHIFT(204),
        [ts_sym_switch_statement] = SHIFT(204),
        [ts_sym_break_statement] = SHIFT(204),
        [ts_sym_var_declaration] = SHIFT(204),
        [ts_sym_expression_statement] = SHIFT(204),
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(207),
        [ts_sym__break] = SHIFT(208),
        [ts_sym__for] = SHIFT(210),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(217),
        [ts_sym__switch] = SHIFT(224),
        [ts_sym__var] = SHIFT(231),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(412),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [216] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [217] = {
        [ts_aux_sym_token2] = SHIFT(218),
    },
    [218] = {
        [ts_sym_expression] = SHIFT(219),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(512),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [219] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(220),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [220] = {
        [ts_sym_statement] = SHIFT(221),
        [ts_sym_statement_block] = SHIFT(464),
        [ts_sym_for_statement] = SHIFT(464),
        [ts_sym_if_statement] = SHIFT(464),
        [ts_sym_switch_statement] = SHIFT(464),
        [ts_sym_break_statement] = SHIFT(464),
        [ts_sym_var_declaration] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(464),
        [ts_sym_expression] = SHIFT(465),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(467),
        [ts_sym__break] = SHIFT(468),
        [ts_sym__for] = SHIFT(470),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(477),
        [ts_sym__switch] = SHIFT(484),
        [ts_sym__var] = SHIFT(492),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(496),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [221] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(222),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [222] = {
        [ts_sym_statement] = SHIFT(223),
        [ts_sym_statement_block] = SHIFT(204),
        [ts_sym_for_statement] = SHIFT(204),
        [ts_sym_if_statement] = SHIFT(204),
        [ts_sym_switch_statement] = SHIFT(204),
        [ts_sym_break_statement] = SHIFT(204),
        [ts_sym_var_declaration] = SHIFT(204),
        [ts_sym_expression_statement] = SHIFT(204),
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(207),
        [ts_sym__break] = SHIFT(208),
        [ts_sym__for] = SHIFT(210),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(217),
        [ts_sym__switch] = SHIFT(224),
        [ts_sym__var] = SHIFT(231),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(412),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [223] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [224] = {
        [ts_aux_sym_token2] = SHIFT(225),
    },
    [225] = {
        [ts_sym_expression] = SHIFT(226),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(463),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [226] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(227),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [227] = {
        [ts_aux_sym_token0] = SHIFT(228),
    },
    [228] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(416),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [229] = {
        [ts_aux_sym_token4] = SHIFT(230),
    },
    [230] = {
        [ts_sym_statement] = SHIFT(203),
        [ts_sym_statement_block] = SHIFT(204),
        [ts_sym_for_statement] = SHIFT(204),
        [ts_sym_if_statement] = SHIFT(204),
        [ts_sym_switch_statement] = SHIFT(204),
        [ts_sym_break_statement] = SHIFT(204),
        [ts_sym_var_declaration] = SHIFT(204),
        [ts_sym_expression_statement] = SHIFT(204),
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(207),
        [ts_sym__break] = SHIFT(208),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(210),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(217),
        [ts_sym__switch] = SHIFT(224),
        [ts_sym__var] = SHIFT(231),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(412),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [231] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(408),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(410),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [232] = {
        [ts_aux_sym_token2] = SHIFT(233),
        [ts_aux_sym_token5] = SHIFT(238),
        [ts_aux_sym_token6] = SHIFT(238),
        [ts_aux_sym_token7] = SHIFT(240),
        [ts_aux_sym_token8] = SHIFT(240),
        [ts_aux_sym_token9] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(246),
        [ts_aux_sym_token13] = SHIFT(248),
    },
    [233] = {
        [ts_sym_expression] = SHIFT(234),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token3] = SHIFT(237),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [234] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(235),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = SHIFT(24),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [235] = {
        [ts_aux_sym_token3] = SHIFT(236),
    },
    [236] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [237] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [238] = {
        [ts_sym_expression] = SHIFT(239),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(251),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(252),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [239] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(238),
        [ts_aux_sym_token6] = SHIFT(238),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [240] = {
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(251),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(252),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [241] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(238),
        [ts_aux_sym_token6] = SHIFT(238),
        [ts_aux_sym_token7] = SHIFT(240),
        [ts_aux_sym_token8] = SHIFT(240),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [242] = {
        [ts_sym_expression] = SHIFT(243),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [243] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(244),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [244] = {
        [ts_sym_expression] = SHIFT(245),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(251),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(252),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [245] = {
        [ts_aux_sym_token2] = SHIFT(233),
        [ts_aux_sym_token5] = SHIFT(238),
        [ts_aux_sym_token6] = SHIFT(238),
        [ts_aux_sym_token7] = SHIFT(240),
        [ts_aux_sym_token8] = SHIFT(240),
        [ts_aux_sym_token9] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(246),
        [ts_aux_sym_token13] = SHIFT(248),
    },
    [246] = {
        [ts_sym_identifier] = SHIFT(247),
    },
    [247] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
    },
    [248] = {
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [249] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(250),
    },
    [250] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
    },
    [251] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [252] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(253),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [253] = {
        [ts_sym_expression] = SHIFT(254),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(251),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(252),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [254] = {
        [ts_aux_sym_token2] = SHIFT(233),
        [ts_aux_sym_token5] = SHIFT(238),
        [ts_aux_sym_token6] = SHIFT(238),
        [ts_aux_sym_token7] = SHIFT(240),
        [ts_aux_sym_token8] = SHIFT(240),
        [ts_aux_sym_token9] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(246),
        [ts_aux_sym_token13] = SHIFT(248),
    },
    [255] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [256] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [257] = {
        [ts_sym_formal_parameters] = SHIFT(258),
        [ts_sym_identifier] = SHIFT(360),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [258] = {
        [ts_sym_statement_block] = SHIFT(259),
        [ts_aux_sym_token0] = SHIFT(260),
    },
    [259] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [260] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(261),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(359),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [261] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(262),
    },
    [262] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [263] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(264),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(267),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [264] = {
        [ts_sym__terminator] = SHIFT(265),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [265] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [266] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [267] = {
        [ts_sym__terminator] = SHIFT(265),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [268] = {
        [ts_builtin_sym_error] = SHIFT(269),
        [ts_sym_string] = SHIFT(272),
        [ts_sym_identifier] = SHIFT(272),
        [ts_aux_sym_token1] = SHIFT(352),
    },
    [269] = {
        [ts_aux_sym_object_repeat0] = SHIFT(270),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [270] = {
        [ts_aux_sym_token1] = SHIFT(271),
    },
    [271] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [272] = {
        [ts_aux_sym_token4] = SHIFT(273),
    },
    [273] = {
        [ts_sym_expression] = SHIFT(274),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [274] = {
        [ts_aux_sym_object_repeat0] = SHIFT(275),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [275] = {
        [ts_aux_sym_token1] = SHIFT(276),
    },
    [276] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
    },
    [277] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [278] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(279),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [279] = {
        [ts_sym_expression] = SHIFT(280),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [280] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [281] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [282] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [283] = {
        [ts_sym_formal_parameters] = SHIFT(284),
        [ts_sym_identifier] = SHIFT(341),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [284] = {
        [ts_sym_statement_block] = SHIFT(285),
        [ts_aux_sym_token0] = SHIFT(286),
    },
    [285] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [286] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(287),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(289),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [287] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(288),
    },
    [288] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [289] = {
        [ts_aux_sym_token1] = SHIFT(288),
    },
    [290] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(291),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(295),
        [ts_sym_identifier] = SHIFT(332),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(333),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = SHIFT(334),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [291] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(294),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [292] = {
        [ts_aux_sym_token1] = SHIFT(293),
    },
    [293] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [294] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [295] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = SHIFT(296),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [296] = {
        [ts_sym_expression] = SHIFT(297),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [297] = {
        [ts_aux_sym_object_repeat0] = SHIFT(298),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [298] = {
        [ts_aux_sym_token1] = SHIFT(299),
    },
    [299] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
    },
    [300] = {
        [ts_builtin_sym_error] = SHIFT(301),
        [ts_sym_string] = SHIFT(304),
        [ts_sym_identifier] = SHIFT(304),
        [ts_aux_sym_token1] = SHIFT(331),
    },
    [301] = {
        [ts_aux_sym_object_repeat0] = SHIFT(302),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [302] = {
        [ts_aux_sym_token1] = SHIFT(303),
    },
    [303] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [304] = {
        [ts_aux_sym_token4] = SHIFT(305),
    },
    [305] = {
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [306] = {
        [ts_aux_sym_object_repeat0] = SHIFT(307),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [307] = {
        [ts_aux_sym_token1] = SHIFT(308),
    },
    [308] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
    },
    [309] = {
        [ts_sym_expression] = SHIFT(310),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(313),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(330),
    },
    [310] = {
        [ts_aux_sym_array_repeat0] = SHIFT(311),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [311] = {
        [ts_aux_sym_token14] = SHIFT(312),
    },
    [312] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [313] = {
        [ts_aux_sym_array_repeat0] = SHIFT(311),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [314] = {
        [ts_builtin_sym_error] = SHIFT(315),
        [ts_sym_string] = SHIFT(318),
        [ts_sym_identifier] = SHIFT(318),
        [ts_aux_sym_token1] = SHIFT(323),
    },
    [315] = {
        [ts_aux_sym_object_repeat0] = SHIFT(316),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [316] = {
        [ts_aux_sym_token1] = SHIFT(317),
    },
    [317] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
    },
    [318] = {
        [ts_aux_sym_token4] = SHIFT(319),
    },
    [319] = {
        [ts_sym_expression] = SHIFT(320),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [320] = {
        [ts_aux_sym_object_repeat0] = SHIFT(321),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [321] = {
        [ts_aux_sym_token1] = SHIFT(322),
    },
    [322] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
    },
    [323] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
    },
    [324] = {
        [ts_sym_expression] = SHIFT(325),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(328),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(329),
    },
    [325] = {
        [ts_aux_sym_array_repeat0] = SHIFT(326),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [326] = {
        [ts_aux_sym_token14] = SHIFT(327),
    },
    [327] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
    },
    [328] = {
        [ts_aux_sym_array_repeat0] = SHIFT(326),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [329] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
    },
    [330] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [331] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [332] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(296),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [333] = {
        [ts_aux_sym_token1] = SHIFT(294),
    },
    [334] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [335] = {
        [ts_sym_expression] = SHIFT(336),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(339),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(340),
    },
    [336] = {
        [ts_aux_sym_array_repeat0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [337] = {
        [ts_aux_sym_token14] = SHIFT(338),
    },
    [338] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [339] = {
        [ts_aux_sym_array_repeat0] = SHIFT(337),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [340] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [341] = {
        [ts_sym_formal_parameters] = SHIFT(342),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [342] = {
        [ts_sym_statement_block] = SHIFT(343),
        [ts_aux_sym_token0] = SHIFT(286),
    },
    [343] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [344] = {
        [ts_sym_identifier] = SHIFT(345),
        [ts_aux_sym_token3] = SHIFT(351),
    },
    [345] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(346),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(348),
    },
    [346] = {
        [ts_aux_sym_token3] = SHIFT(347),
    },
    [347] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [348] = {
        [ts_sym_identifier] = SHIFT(349),
    },
    [349] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(350),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(348),
    },
    [350] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [351] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [352] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [353] = {
        [ts_sym_expression] = SHIFT(354),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(357),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(358),
    },
    [354] = {
        [ts_aux_sym_array_repeat0] = SHIFT(355),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [355] = {
        [ts_aux_sym_token14] = SHIFT(356),
    },
    [356] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [357] = {
        [ts_aux_sym_array_repeat0] = SHIFT(355),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [358] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [359] = {
        [ts_aux_sym_token1] = SHIFT(262),
    },
    [360] = {
        [ts_sym_formal_parameters] = SHIFT(361),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [361] = {
        [ts_sym_statement_block] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(260),
    },
    [362] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [363] = {
        [ts_sym_expression] = SHIFT(364),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [364] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [365] = {
        [ts_sym_expression] = SHIFT(366),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [366] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [367] = {
        [ts_sym_expression] = SHIFT(368),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [368] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(369),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [369] = {
        [ts_sym_expression] = SHIFT(370),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [370] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [371] = {
        [ts_sym_identifier] = SHIFT(372),
    },
    [372] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
    },
    [373] = {
        [ts_sym_expression] = SHIFT(374),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [374] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(375),
    },
    [375] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
    },
    [376] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [377] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(378),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [378] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [379] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [380] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [381] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [382] = {
        [ts_sym_formal_parameters] = SHIFT(383),
        [ts_sym_identifier] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [383] = {
        [ts_sym_statement_block] = SHIFT(384),
        [ts_aux_sym_token0] = SHIFT(385),
    },
    [384] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [385] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(386),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(388),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [386] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(387),
    },
    [387] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [388] = {
        [ts_aux_sym_token1] = SHIFT(387),
    },
    [389] = {
        [ts_sym_formal_parameters] = SHIFT(390),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [390] = {
        [ts_sym_statement_block] = SHIFT(391),
        [ts_aux_sym_token0] = SHIFT(385),
    },
    [391] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [392] = {
        [ts_builtin_sym_error] = SHIFT(393),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(396),
        [ts_aux_sym_token1] = SHIFT(401),
    },
    [393] = {
        [ts_aux_sym_object_repeat0] = SHIFT(394),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [394] = {
        [ts_aux_sym_token1] = SHIFT(395),
    },
    [395] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [396] = {
        [ts_aux_sym_token4] = SHIFT(397),
    },
    [397] = {
        [ts_sym_expression] = SHIFT(398),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [398] = {
        [ts_aux_sym_object_repeat0] = SHIFT(399),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [399] = {
        [ts_aux_sym_token1] = SHIFT(400),
    },
    [400] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
    },
    [401] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [402] = {
        [ts_sym_expression] = SHIFT(403),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(406),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(407),
    },
    [403] = {
        [ts_aux_sym_array_repeat0] = SHIFT(404),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [404] = {
        [ts_aux_sym_token14] = SHIFT(405),
    },
    [405] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [406] = {
        [ts_aux_sym_array_repeat0] = SHIFT(404),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [407] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [408] = {
        [ts_sym__terminator] = SHIFT(409),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [409] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__case] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__default] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [410] = {
        [ts_sym__terminator] = SHIFT(409),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [411] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
    },
    [412] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(413),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(295),
        [ts_sym_identifier] = SHIFT(332),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(415),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = SHIFT(334),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [413] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(414),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [414] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__case] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__default] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [415] = {
        [ts_aux_sym_token1] = SHIFT(414),
    },
    [416] = {
        [ts_aux_sym_token1] = SHIFT(417),
    },
    [417] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [418] = {
        [ts_sym_expression] = SHIFT(419),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [419] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [420] = {
        [ts_sym_expression] = SHIFT(421),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [421] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [422] = {
        [ts_sym_expression] = SHIFT(423),
        [ts_sym_math_op] = SHIFT(376),
        [ts_sym_ternary] = SHIFT(376),
        [ts_sym_assignment] = SHIFT(376),
        [ts_sym_function_expression] = SHIFT(376),
        [ts_sym_function_call] = SHIFT(376),
        [ts_sym_property_access] = SHIFT(377),
        [ts_sym_literal] = SHIFT(380),
        [ts_sym_object] = SHIFT(381),
        [ts_sym_array] = SHIFT(381),
        [ts_sym__function] = SHIFT(382),
        [ts_sym_null] = SHIFT(381),
        [ts_sym_true] = SHIFT(381),
        [ts_sym_false] = SHIFT(381),
        [ts_sym_string] = SHIFT(381),
        [ts_sym_identifier] = SHIFT(377),
        [ts_sym_number] = SHIFT(381),
        [ts_aux_sym_token0] = SHIFT(392),
        [ts_aux_sym_token13] = SHIFT(402),
    },
    [423] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(424),
        [ts_aux_sym_token5] = SHIFT(363),
        [ts_aux_sym_token6] = SHIFT(363),
        [ts_aux_sym_token7] = SHIFT(365),
        [ts_aux_sym_token8] = SHIFT(365),
        [ts_aux_sym_token9] = SHIFT(367),
        [ts_aux_sym_token12] = SHIFT(371),
        [ts_aux_sym_token13] = SHIFT(373),
    },
    [424] = {
        [ts_sym_expression] = SHIFT(425),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [425] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [426] = {
        [ts_sym_identifier] = SHIFT(427),
    },
    [427] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 3),
    },
    [428] = {
        [ts_sym_expression] = SHIFT(429),
        [ts_sym_math_op] = SHIFT(74),
        [ts_sym_ternary] = SHIFT(74),
        [ts_sym_assignment] = SHIFT(74),
        [ts_sym_function_expression] = SHIFT(74),
        [ts_sym_function_call] = SHIFT(74),
        [ts_sym_property_access] = SHIFT(75),
        [ts_sym_literal] = SHIFT(78),
        [ts_sym_object] = SHIFT(79),
        [ts_sym_array] = SHIFT(79),
        [ts_sym__function] = SHIFT(80),
        [ts_sym_null] = SHIFT(79),
        [ts_sym_true] = SHIFT(79),
        [ts_sym_false] = SHIFT(79),
        [ts_sym_string] = SHIFT(79),
        [ts_sym_identifier] = SHIFT(75),
        [ts_sym_number] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(145),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [429] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(430),
    },
    [430] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
    },
    [431] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [432] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(433),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [433] = {
        [ts_sym_expression] = SHIFT(434),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [434] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [435] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [436] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [437] = {
        [ts_sym_formal_parameters] = SHIFT(438),
        [ts_sym_identifier] = SHIFT(444),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [438] = {
        [ts_sym_statement_block] = SHIFT(439),
        [ts_aux_sym_token0] = SHIFT(440),
    },
    [439] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [440] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(441),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(443),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [441] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(442),
    },
    [442] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [443] = {
        [ts_aux_sym_token1] = SHIFT(442),
    },
    [444] = {
        [ts_sym_formal_parameters] = SHIFT(445),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [445] = {
        [ts_sym_statement_block] = SHIFT(446),
        [ts_aux_sym_token0] = SHIFT(440),
    },
    [446] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [447] = {
        [ts_builtin_sym_error] = SHIFT(448),
        [ts_sym_string] = SHIFT(451),
        [ts_sym_identifier] = SHIFT(451),
        [ts_aux_sym_token1] = SHIFT(456),
    },
    [448] = {
        [ts_aux_sym_object_repeat0] = SHIFT(449),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [449] = {
        [ts_aux_sym_token1] = SHIFT(450),
    },
    [450] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [451] = {
        [ts_aux_sym_token4] = SHIFT(452),
    },
    [452] = {
        [ts_sym_expression] = SHIFT(453),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [453] = {
        [ts_aux_sym_object_repeat0] = SHIFT(454),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [454] = {
        [ts_aux_sym_token1] = SHIFT(455),
    },
    [455] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
    },
    [456] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [457] = {
        [ts_sym_expression] = SHIFT(458),
        [ts_sym_math_op] = SHIFT(174),
        [ts_sym_ternary] = SHIFT(174),
        [ts_sym_assignment] = SHIFT(174),
        [ts_sym_function_expression] = SHIFT(174),
        [ts_sym_function_call] = SHIFT(174),
        [ts_sym_property_access] = SHIFT(175),
        [ts_sym_literal] = SHIFT(178),
        [ts_sym_object] = SHIFT(179),
        [ts_sym_array] = SHIFT(179),
        [ts_builtin_sym_error] = SHIFT(461),
        [ts_sym__function] = SHIFT(180),
        [ts_sym_null] = SHIFT(179),
        [ts_sym_true] = SHIFT(179),
        [ts_sym_false] = SHIFT(179),
        [ts_sym_string] = SHIFT(179),
        [ts_sym_identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(179),
        [ts_aux_sym_token0] = SHIFT(314),
        [ts_aux_sym_token13] = SHIFT(324),
        [ts_aux_sym_token14] = SHIFT(462),
    },
    [458] = {
        [ts_aux_sym_array_repeat0] = SHIFT(459),
        [ts_aux_sym_token2] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(132),
        [ts_aux_sym_token6] = SHIFT(132),
        [ts_aux_sym_token7] = SHIFT(134),
        [ts_aux_sym_token8] = SHIFT(134),
        [ts_aux_sym_token9] = SHIFT(136),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token12] = SHIFT(140),
        [ts_aux_sym_token13] = SHIFT(142),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [459] = {
        [ts_aux_sym_token14] = SHIFT(460),
    },
    [460] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [461] = {
        [ts_aux_sym_array_repeat0] = SHIFT(459),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [462] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [463] = {
        [ts_aux_sym_token3] = SHIFT(227),
    },
    [464] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__case] = REDUCE(ts_sym_statement, 1),
        [ts_sym__default] = REDUCE(ts_sym_statement, 1),
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [465] = {
        [ts_sym__terminator] = SHIFT(466),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [466] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [467] = {
        [ts_sym__terminator] = SHIFT(466),
    },
    [468] = {
        [ts_sym__terminator] = SHIFT(469),
    },
    [469] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [470] = {
        [ts_aux_sym_token2] = SHIFT(471),
    },
    [471] = {
        [ts_sym_var_declaration] = SHIFT(472),
        [ts_sym_expression_statement] = SHIFT(472),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [472] = {
        [ts_sym_expression_statement] = SHIFT(473),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [473] = {
        [ts_sym_expression] = SHIFT(474),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(501),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [474] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(475),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [475] = {
        [ts_sym_statement] = SHIFT(476),
        [ts_sym_statement_block] = SHIFT(464),
        [ts_sym_for_statement] = SHIFT(464),
        [ts_sym_if_statement] = SHIFT(464),
        [ts_sym_switch_statement] = SHIFT(464),
        [ts_sym_break_statement] = SHIFT(464),
        [ts_sym_var_declaration] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(464),
        [ts_sym_expression] = SHIFT(465),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(467),
        [ts_sym__break] = SHIFT(468),
        [ts_sym__for] = SHIFT(470),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(477),
        [ts_sym__switch] = SHIFT(484),
        [ts_sym__var] = SHIFT(492),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(496),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [476] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [477] = {
        [ts_aux_sym_token2] = SHIFT(478),
    },
    [478] = {
        [ts_sym_expression] = SHIFT(479),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(500),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [479] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(480),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [480] = {
        [ts_sym_statement] = SHIFT(481),
        [ts_sym_statement_block] = SHIFT(464),
        [ts_sym_for_statement] = SHIFT(464),
        [ts_sym_if_statement] = SHIFT(464),
        [ts_sym_switch_statement] = SHIFT(464),
        [ts_sym_break_statement] = SHIFT(464),
        [ts_sym_var_declaration] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(464),
        [ts_sym_expression] = SHIFT(465),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(467),
        [ts_sym__break] = SHIFT(468),
        [ts_sym__for] = SHIFT(470),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(477),
        [ts_sym__switch] = SHIFT(484),
        [ts_sym__var] = SHIFT(492),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(496),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [481] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(482),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [482] = {
        [ts_sym_statement] = SHIFT(483),
        [ts_sym_statement_block] = SHIFT(464),
        [ts_sym_for_statement] = SHIFT(464),
        [ts_sym_if_statement] = SHIFT(464),
        [ts_sym_switch_statement] = SHIFT(464),
        [ts_sym_break_statement] = SHIFT(464),
        [ts_sym_var_declaration] = SHIFT(464),
        [ts_sym_expression_statement] = SHIFT(464),
        [ts_sym_expression] = SHIFT(465),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(467),
        [ts_sym__break] = SHIFT(468),
        [ts_sym__for] = SHIFT(470),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(477),
        [ts_sym__switch] = SHIFT(484),
        [ts_sym__var] = SHIFT(492),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(496),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [483] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [484] = {
        [ts_aux_sym_token2] = SHIFT(485),
    },
    [485] = {
        [ts_sym_expression] = SHIFT(486),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(491),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [486] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [487] = {
        [ts_aux_sym_token0] = SHIFT(488),
    },
    [488] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(489),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [489] = {
        [ts_aux_sym_token1] = SHIFT(490),
    },
    [490] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__case] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__default] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [491] = {
        [ts_aux_sym_token3] = SHIFT(487),
    },
    [492] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(493),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(495),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [493] = {
        [ts_sym__terminator] = SHIFT(494),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [494] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__case] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__default] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [495] = {
        [ts_sym__terminator] = SHIFT(494),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [496] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(497),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(295),
        [ts_sym_identifier] = SHIFT(332),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(499),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = SHIFT(334),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [497] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(498),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [498] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__case] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__default] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [499] = {
        [ts_aux_sym_token1] = SHIFT(498),
    },
    [500] = {
        [ts_aux_sym_token3] = SHIFT(480),
    },
    [501] = {
        [ts_aux_sym_token3] = SHIFT(475),
    },
    [502] = {
        [ts_sym__terminator] = SHIFT(503),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [503] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [504] = {
        [ts_sym__terminator] = SHIFT(503),
    },
    [505] = {
        [ts_builtin_sym_error] = SHIFT(506),
        [ts_sym_string] = SHIFT(507),
        [ts_sym_identifier] = SHIFT(507),
        [ts_aux_sym_token1] = SHIFT(334),
    },
    [506] = {
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [507] = {
        [ts_aux_sym_token4] = SHIFT(296),
    },
    [508] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(509),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(511),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [509] = {
        [ts_sym__terminator] = SHIFT(510),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [510] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [511] = {
        [ts_sym__terminator] = SHIFT(510),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [512] = {
        [ts_aux_sym_token3] = SHIFT(220),
    },
    [513] = {
        [ts_aux_sym_token3] = SHIFT(215),
    },
    [514] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [515] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
    },
    [516] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [517] = {
        [ts_aux_sym_token1] = SHIFT(518),
    },
    [518] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [519] = {
        [ts_aux_sym_token3] = SHIFT(197),
    },
    [520] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [521] = {
        [ts_sym__terminator] = SHIFT(522),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [522] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [523] = {
        [ts_sym__terminator] = SHIFT(522),
    },
    [524] = {
        [ts_sym__terminator] = SHIFT(525),
    },
    [525] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [526] = {
        [ts_aux_sym_token2] = SHIFT(527),
    },
    [527] = {
        [ts_sym_var_declaration] = SHIFT(528),
        [ts_sym_expression_statement] = SHIFT(528),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [528] = {
        [ts_sym_expression_statement] = SHIFT(529),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [529] = {
        [ts_sym_expression] = SHIFT(530),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(557),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [530] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(531),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [531] = {
        [ts_sym_statement] = SHIFT(532),
        [ts_sym_statement_block] = SHIFT(520),
        [ts_sym_for_statement] = SHIFT(520),
        [ts_sym_if_statement] = SHIFT(520),
        [ts_sym_switch_statement] = SHIFT(520),
        [ts_sym_break_statement] = SHIFT(520),
        [ts_sym_var_declaration] = SHIFT(520),
        [ts_sym_expression_statement] = SHIFT(520),
        [ts_sym_expression] = SHIFT(521),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(523),
        [ts_sym__break] = SHIFT(524),
        [ts_sym__for] = SHIFT(526),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(533),
        [ts_sym__switch] = SHIFT(540),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(552),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [532] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [533] = {
        [ts_aux_sym_token2] = SHIFT(534),
    },
    [534] = {
        [ts_sym_expression] = SHIFT(535),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(556),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [535] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(536),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [536] = {
        [ts_sym_statement] = SHIFT(537),
        [ts_sym_statement_block] = SHIFT(520),
        [ts_sym_for_statement] = SHIFT(520),
        [ts_sym_if_statement] = SHIFT(520),
        [ts_sym_switch_statement] = SHIFT(520),
        [ts_sym_break_statement] = SHIFT(520),
        [ts_sym_var_declaration] = SHIFT(520),
        [ts_sym_expression_statement] = SHIFT(520),
        [ts_sym_expression] = SHIFT(521),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(523),
        [ts_sym__break] = SHIFT(524),
        [ts_sym__for] = SHIFT(526),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(533),
        [ts_sym__switch] = SHIFT(540),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(552),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [537] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(538),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [538] = {
        [ts_sym_statement] = SHIFT(539),
        [ts_sym_statement_block] = SHIFT(520),
        [ts_sym_for_statement] = SHIFT(520),
        [ts_sym_if_statement] = SHIFT(520),
        [ts_sym_switch_statement] = SHIFT(520),
        [ts_sym_break_statement] = SHIFT(520),
        [ts_sym_var_declaration] = SHIFT(520),
        [ts_sym_expression_statement] = SHIFT(520),
        [ts_sym_expression] = SHIFT(521),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(523),
        [ts_sym__break] = SHIFT(524),
        [ts_sym__for] = SHIFT(526),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(533),
        [ts_sym__switch] = SHIFT(540),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(552),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [539] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [540] = {
        [ts_aux_sym_token2] = SHIFT(541),
    },
    [541] = {
        [ts_sym_expression] = SHIFT(542),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(547),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [542] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(543),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [543] = {
        [ts_aux_sym_token0] = SHIFT(544),
    },
    [544] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [545] = {
        [ts_aux_sym_token1] = SHIFT(546),
    },
    [546] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [547] = {
        [ts_aux_sym_token3] = SHIFT(543),
    },
    [548] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(549),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(551),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [549] = {
        [ts_sym__terminator] = SHIFT(550),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [550] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [551] = {
        [ts_sym__terminator] = SHIFT(550),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [552] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(553),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(295),
        [ts_sym_identifier] = SHIFT(332),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(555),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = SHIFT(334),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [553] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(554),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [554] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [555] = {
        [ts_aux_sym_token1] = SHIFT(554),
    },
    [556] = {
        [ts_aux_sym_token3] = SHIFT(536),
    },
    [557] = {
        [ts_aux_sym_token3] = SHIFT(531),
    },
    [558] = {
        [ts_aux_sym_token3] = SHIFT(189),
    },
    [559] = {
        [ts_aux_sym_token1] = SHIFT(185),
    },
    [560] = {
        [ts_sym_formal_parameters] = SHIFT(561),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [561] = {
        [ts_sym_statement_block] = SHIFT(562),
        [ts_aux_sym_token0] = SHIFT(183),
    },
    [562] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
    },
    [563] = {
        [ts_aux_sym_array_repeat0] = SHIFT(173),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [564] = {
        [ts_aux_sym_array_repeat0] = SHIFT(169),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [565] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
    },
    [566] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
    },
    [567] = {
        [ts_aux_sym_array_repeat0] = SHIFT(125),
        [ts_aux_sym_token11] = SHIFT(171),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [568] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [569] = {
        [ts_aux_sym_token4] = SHIFT(570),
    },
    [570] = {
        [ts_sym_expression] = SHIFT(571),
        [ts_sym_math_op] = SHIFT(277),
        [ts_sym_ternary] = SHIFT(277),
        [ts_sym_assignment] = SHIFT(277),
        [ts_sym_function_expression] = SHIFT(277),
        [ts_sym_function_call] = SHIFT(277),
        [ts_sym_property_access] = SHIFT(278),
        [ts_sym_literal] = SHIFT(281),
        [ts_sym_object] = SHIFT(282),
        [ts_sym_array] = SHIFT(282),
        [ts_sym__function] = SHIFT(283),
        [ts_sym_null] = SHIFT(282),
        [ts_sym_true] = SHIFT(282),
        [ts_sym_false] = SHIFT(282),
        [ts_sym_string] = SHIFT(282),
        [ts_sym_identifier] = SHIFT(278),
        [ts_sym_number] = SHIFT(282),
        [ts_aux_sym_token0] = SHIFT(300),
        [ts_aux_sym_token13] = SHIFT(309),
    },
    [571] = {
        [ts_aux_sym_object_repeat0] = SHIFT(572),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(118),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token11] = SHIFT(111),
        [ts_aux_sym_token12] = SHIFT(162),
        [ts_aux_sym_token13] = SHIFT(164),
    },
    [572] = {
        [ts_aux_sym_token1] = SHIFT(573),
    },
    [573] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
    },
    [574] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [575] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [576] = {
        [ts_sym_statement] = SHIFT(577),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(193),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [577] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [578] = {
        [ts_aux_sym_token3] = SHIFT(576),
    },
    [579] = {
        [ts_aux_sym_token1] = SHIFT(95),
    },
    [580] = {
        [ts_sym_formal_parameters] = SHIFT(581),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [581] = {
        [ts_sym_statement_block] = SHIFT(582),
        [ts_aux_sym_token0] = SHIFT(93),
    },
    [582] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [583] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(584),
    },
    [584] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
    },
    [585] = {
        [ts_aux_sym_token1] = SHIFT(584),
    },
    [586] = {
        [ts_sym_formal_parameters] = SHIFT(587),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [587] = {
        [ts_sym_statement_block] = SHIFT(588),
        [ts_aux_sym_token0] = SHIFT(83),
    },
    [588] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
    },
    [589] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
    },
    [590] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [591] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(592),
    },
    [592] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [593] = {
        [ts_aux_sym_token1] = SHIFT(592),
    },
    [594] = {
        [ts_sym_formal_parameters] = SHIFT(595),
        [ts_aux_sym_token2] = SHIFT(344),
    },
    [595] = {
        [ts_sym_statement_block] = SHIFT(596),
        [ts_aux_sym_token0] = SHIFT(44),
    },
    [596] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [597] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
    },
    [598] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_property_access, 4),
    },
    [599] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [600] = {
        [ts_sym_expression] = SHIFT(601),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(107),
        [ts_aux_sym_token13] = SHIFT(123),
    },
    [601] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token11] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(29),
    },
    [602] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [603] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [604] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [605] = {
        [ts_sym__terminator] = SHIFT(606),
    },
    [606] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [607] = {
        [ts_aux_sym_token2] = SHIFT(608),
    },
    [608] = {
        [ts_sym_var_declaration] = SHIFT(609),
        [ts_sym_expression_statement] = SHIFT(609),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [609] = {
        [ts_sym_expression_statement] = SHIFT(610),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [610] = {
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(676),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [611] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(612),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [612] = {
        [ts_sym_statement] = SHIFT(613),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_sym__break] = SHIFT(605),
        [ts_sym__for] = SHIFT(607),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(614),
        [ts_sym__switch] = SHIFT(621),
        [ts_sym__var] = SHIFT(629),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(633),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [613] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [614] = {
        [ts_aux_sym_token2] = SHIFT(615),
    },
    [615] = {
        [ts_sym_expression] = SHIFT(616),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(675),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [616] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(617),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [617] = {
        [ts_sym_statement] = SHIFT(618),
        [ts_sym_statement_block] = SHIFT(637),
        [ts_sym_for_statement] = SHIFT(637),
        [ts_sym_if_statement] = SHIFT(637),
        [ts_sym_switch_statement] = SHIFT(637),
        [ts_sym_break_statement] = SHIFT(637),
        [ts_sym_var_declaration] = SHIFT(637),
        [ts_sym_expression_statement] = SHIFT(637),
        [ts_sym_expression] = SHIFT(638),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(640),
        [ts_sym__break] = SHIFT(641),
        [ts_sym__for] = SHIFT(643),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(650),
        [ts_sym__switch] = SHIFT(657),
        [ts_sym__var] = SHIFT(665),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(669),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [618] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(619),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [619] = {
        [ts_sym_statement] = SHIFT(620),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_sym__break] = SHIFT(605),
        [ts_sym__for] = SHIFT(607),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(614),
        [ts_sym__switch] = SHIFT(621),
        [ts_sym__var] = SHIFT(629),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(633),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [620] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [621] = {
        [ts_aux_sym_token2] = SHIFT(622),
    },
    [622] = {
        [ts_sym_expression] = SHIFT(623),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(628),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [623] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(624),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [624] = {
        [ts_aux_sym_token0] = SHIFT(625),
    },
    [625] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(626),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [626] = {
        [ts_aux_sym_token1] = SHIFT(627),
    },
    [627] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [628] = {
        [ts_aux_sym_token3] = SHIFT(624),
    },
    [629] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(630),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(632),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [630] = {
        [ts_sym__terminator] = SHIFT(631),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [631] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [632] = {
        [ts_sym__terminator] = SHIFT(631),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [633] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(634),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(295),
        [ts_sym_identifier] = SHIFT(332),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(636),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = SHIFT(334),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [634] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(635),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [635] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [636] = {
        [ts_aux_sym_token1] = SHIFT(635),
    },
    [637] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_sym__break] = REDUCE(ts_sym_statement, 1),
        [ts_sym__else] = REDUCE(ts_sym_statement, 1),
        [ts_sym__for] = REDUCE(ts_sym_statement, 1),
        [ts_sym__function] = REDUCE(ts_sym_statement, 1),
        [ts_sym__if] = REDUCE(ts_sym_statement, 1),
        [ts_sym__switch] = REDUCE(ts_sym_statement, 1),
        [ts_sym__var] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [638] = {
        [ts_sym__terminator] = SHIFT(639),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [639] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [640] = {
        [ts_sym__terminator] = SHIFT(639),
    },
    [641] = {
        [ts_sym__terminator] = SHIFT(642),
    },
    [642] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [643] = {
        [ts_aux_sym_token2] = SHIFT(644),
    },
    [644] = {
        [ts_sym_var_declaration] = SHIFT(645),
        [ts_sym_expression_statement] = SHIFT(645),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [645] = {
        [ts_sym_expression_statement] = SHIFT(646),
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(505),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [646] = {
        [ts_sym_expression] = SHIFT(647),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(674),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [647] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(648),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [648] = {
        [ts_sym_statement] = SHIFT(649),
        [ts_sym_statement_block] = SHIFT(637),
        [ts_sym_for_statement] = SHIFT(637),
        [ts_sym_if_statement] = SHIFT(637),
        [ts_sym_switch_statement] = SHIFT(637),
        [ts_sym_break_statement] = SHIFT(637),
        [ts_sym_var_declaration] = SHIFT(637),
        [ts_sym_expression_statement] = SHIFT(637),
        [ts_sym_expression] = SHIFT(638),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(640),
        [ts_sym__break] = SHIFT(641),
        [ts_sym__for] = SHIFT(643),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(650),
        [ts_sym__switch] = SHIFT(657),
        [ts_sym__var] = SHIFT(665),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(669),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [649] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [650] = {
        [ts_aux_sym_token2] = SHIFT(651),
    },
    [651] = {
        [ts_sym_expression] = SHIFT(652),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(673),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [652] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(653),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [653] = {
        [ts_sym_statement] = SHIFT(654),
        [ts_sym_statement_block] = SHIFT(637),
        [ts_sym_for_statement] = SHIFT(637),
        [ts_sym_if_statement] = SHIFT(637),
        [ts_sym_switch_statement] = SHIFT(637),
        [ts_sym_break_statement] = SHIFT(637),
        [ts_sym_var_declaration] = SHIFT(637),
        [ts_sym_expression_statement] = SHIFT(637),
        [ts_sym_expression] = SHIFT(638),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(640),
        [ts_sym__break] = SHIFT(641),
        [ts_sym__for] = SHIFT(643),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(650),
        [ts_sym__switch] = SHIFT(657),
        [ts_sym__var] = SHIFT(665),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(669),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [654] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(655),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [655] = {
        [ts_sym_statement] = SHIFT(656),
        [ts_sym_statement_block] = SHIFT(637),
        [ts_sym_for_statement] = SHIFT(637),
        [ts_sym_if_statement] = SHIFT(637),
        [ts_sym_switch_statement] = SHIFT(637),
        [ts_sym_break_statement] = SHIFT(637),
        [ts_sym_var_declaration] = SHIFT(637),
        [ts_sym_expression_statement] = SHIFT(637),
        [ts_sym_expression] = SHIFT(638),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(640),
        [ts_sym__break] = SHIFT(641),
        [ts_sym__for] = SHIFT(643),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(650),
        [ts_sym__switch] = SHIFT(657),
        [ts_sym__var] = SHIFT(665),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(669),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [656] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [657] = {
        [ts_aux_sym_token2] = SHIFT(658),
    },
    [658] = {
        [ts_sym_expression] = SHIFT(659),
        [ts_sym_math_op] = SHIFT(431),
        [ts_sym_ternary] = SHIFT(431),
        [ts_sym_assignment] = SHIFT(431),
        [ts_sym_function_expression] = SHIFT(431),
        [ts_sym_function_call] = SHIFT(431),
        [ts_sym_property_access] = SHIFT(432),
        [ts_sym_literal] = SHIFT(435),
        [ts_sym_object] = SHIFT(436),
        [ts_sym_array] = SHIFT(436),
        [ts_builtin_sym_error] = SHIFT(664),
        [ts_sym__function] = SHIFT(437),
        [ts_sym_null] = SHIFT(436),
        [ts_sym_true] = SHIFT(436),
        [ts_sym_false] = SHIFT(436),
        [ts_sym_string] = SHIFT(436),
        [ts_sym_identifier] = SHIFT(432),
        [ts_sym_number] = SHIFT(436),
        [ts_aux_sym_token0] = SHIFT(447),
        [ts_aux_sym_token13] = SHIFT(457),
    },
    [659] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(660),
        [ts_aux_sym_token5] = SHIFT(418),
        [ts_aux_sym_token6] = SHIFT(418),
        [ts_aux_sym_token7] = SHIFT(420),
        [ts_aux_sym_token8] = SHIFT(420),
        [ts_aux_sym_token9] = SHIFT(422),
        [ts_aux_sym_token12] = SHIFT(426),
        [ts_aux_sym_token13] = SHIFT(428),
    },
    [660] = {
        [ts_aux_sym_token0] = SHIFT(661),
    },
    [661] = {
        [ts_sym_switch_case] = SHIFT(199),
        [ts_sym__case] = SHIFT(200),
        [ts_sym__default] = SHIFT(229),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(662),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [662] = {
        [ts_aux_sym_token1] = SHIFT(663),
    },
    [663] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__break] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__else] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__for] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__function] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__if] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__switch] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__var] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [664] = {
        [ts_aux_sym_token3] = SHIFT(660),
    },
    [665] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(251),
        [ts_sym_assignment] = SHIFT(666),
        [ts_sym_function_expression] = SHIFT(251),
        [ts_sym_function_call] = SHIFT(251),
        [ts_sym_property_access] = SHIFT(266),
        [ts_sym_literal] = SHIFT(255),
        [ts_sym_object] = SHIFT(256),
        [ts_sym_array] = SHIFT(256),
        [ts_sym__function] = SHIFT(257),
        [ts_sym_null] = SHIFT(256),
        [ts_sym_true] = SHIFT(256),
        [ts_sym_false] = SHIFT(256),
        [ts_sym_string] = SHIFT(256),
        [ts_sym_identifier] = SHIFT(668),
        [ts_sym_number] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(268),
        [ts_aux_sym_token13] = SHIFT(353),
    },
    [666] = {
        [ts_sym__terminator] = SHIFT(667),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [667] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__break] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__else] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__for] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__if] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__switch] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [668] = {
        [ts_sym__terminator] = SHIFT(667),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [669] = {
        [ts_sym_statement] = SHIFT(45),
        [ts_sym_statement_block] = SHIFT(46),
        [ts_sym_for_statement] = SHIFT(46),
        [ts_sym_if_statement] = SHIFT(46),
        [ts_sym_switch_statement] = SHIFT(46),
        [ts_sym_break_statement] = SHIFT(46),
        [ts_sym_var_declaration] = SHIFT(46),
        [ts_sym_expression_statement] = SHIFT(46),
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(670),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(186),
        [ts_sym__switch] = SHIFT(194),
        [ts_sym__var] = SHIFT(263),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(295),
        [ts_sym_identifier] = SHIFT(332),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(672),
        [ts_aux_sym_token0] = SHIFT(290),
        [ts_aux_sym_token1] = SHIFT(334),
        [ts_aux_sym_token13] = SHIFT(335),
    },
    [670] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(292),
        [ts_aux_sym_token1] = SHIFT(671),
        [ts_aux_sym_token11] = SHIFT(111),
    },
    [671] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__break] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__else] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__for] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__function] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__if] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__switch] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [672] = {
        [ts_aux_sym_token1] = SHIFT(671),
    },
    [673] = {
        [ts_aux_sym_token3] = SHIFT(653),
    },
    [674] = {
        [ts_aux_sym_token3] = SHIFT(648),
    },
    [675] = {
        [ts_aux_sym_token3] = SHIFT(617),
    },
    [676] = {
        [ts_aux_sym_token3] = SHIFT(612),
    },
    [677] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [678] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
