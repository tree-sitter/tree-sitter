#include "tree_sitter/parser.h"

#define STATE_COUNT 639
#define SYMBOL_COUNT 57

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
    ts_sym_ternary = 13,
    ts_sym_assignment = 14,
    ts_sym_function_expression = 15,
    ts_sym_function_call = 16,
    ts_sym_property_access = 17,
    ts_sym_formal_parameters = 18,
    ts_sym_literal = 19,
    ts_sym_object = 20,
    ts_sym_array = 21,
    ts_sym__break = 22,
    ts_sym__case = 23,
    ts_sym__default = 24,
    ts_sym__else = 25,
    ts_sym__for = 26,
    ts_sym__function = 27,
    ts_sym__if = 28,
    ts_sym__switch = 29,
    ts_sym__var = 30,
    ts_sym_null = 31,
    ts_sym_true = 32,
    ts_sym_false = 33,
    ts_sym__terminator = 34,
    ts_sym_string = 35,
    ts_sym_identifier = 36,
    ts_sym_number = 37,
    ts_aux_sym_program_repeat0 = 38,
    ts_aux_sym_statement_block_repeat0 = 39,
    ts_aux_sym_switch_statement_repeat0 = 40,
    ts_aux_sym_switch_case_repeat0 = 41,
    ts_aux_sym_function_call_repeat0 = 42,
    ts_aux_sym_formal_parameters_repeat0 = 43,
    ts_aux_sym_object_repeat0 = 44,
    ts_aux_sym_array_repeat0 = 45,
    ts_aux_sym_token0 = 46,
    ts_aux_sym_token1 = 47,
    ts_aux_sym_token2 = 48,
    ts_aux_sym_token3 = 49,
    ts_aux_sym_token4 = 50,
    ts_aux_sym_token5 = 51,
    ts_aux_sym_token6 = 52,
    ts_aux_sym_token7 = 53,
    ts_aux_sym_token8 = 54,
    ts_aux_sym_token9 = 55,
    ts_aux_sym_token10 = 56,
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
    [ts_aux_sym_token5] = "'?'",
    [ts_aux_sym_token6] = "'='",
    [ts_aux_sym_token7] = "','",
    [ts_aux_sym_token8] = "'.'",
    [ts_aux_sym_token9] = "'['",
    [ts_aux_sym_token10] = "']'",
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
            ACCEPT_TOKEN(ts_aux_sym_token9);
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
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '?')
                ADVANCE(57);
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
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 56:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 58:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(58);
            if (lookahead == ')')
                ADVANCE(59);
            LEX_ERROR();
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 60:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(60);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 61:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 62:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 64:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 66:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 67:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(68);
            LEX_ERROR();
        case 68:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 69:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
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
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 71:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '\n')
                ADVANCE(72);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '\n')
                ADVANCE(72);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 73:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(68);
            LEX_ERROR();
        case 74:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '\n')
                ADVANCE(75);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 75:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '\n')
                ADVANCE(75);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\n')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(56);
            LEX_ERROR();
        case 77:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\n')
                ADVANCE(77);
            if (lookahead == ';')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 78:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == ']')
                ADVANCE(68);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(68);
            LEX_ERROR();
        case 84:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(59);
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
                ADVANCE(85);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 85:
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
        case 86:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(68);
            LEX_ERROR();
        case 87:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 88:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
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
                ADVANCE(89);
            if (lookahead == 'd')
                ADVANCE(93);
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
                ADVANCE(70);
            LEX_ERROR();
        case 89:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(90);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 90:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 91:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 92:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__case);
        case 93:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 94:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 95:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 96:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'u')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 97:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 98:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 't')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 99:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__default);
        case 100:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
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
                ADVANCE(85);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '\n')
                ADVANCE(104);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '\n')
                ADVANCE(104);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 105:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == ']')
                ADVANCE(68);
            LEX_ERROR();
        case 106:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(106);
            if (lookahead == ':')
                ADVANCE(63);
            LEX_ERROR();
        case 107:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
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
                ADVANCE(68);
            if (lookahead == 'f')
                ADVANCE(85);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '\n')
                ADVANCE(110);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '\n')
                ADVANCE(110);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 111:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == '\n')
                ADVANCE(112);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 112:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == '\n')
                ADVANCE(112);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 114:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == ',')
                ADVANCE(61);
            LEX_ERROR();
        case 115:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == ')')
                ADVANCE(59);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(54);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '(')
                ADVANCE(54);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 118:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 119:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == 'c')
                ADVANCE(120);
            if (lookahead == 'd')
                ADVANCE(124);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 120:
            if (lookahead == 'a')
                ADVANCE(121);
            LEX_ERROR();
        case 121:
            if (lookahead == 's')
                ADVANCE(122);
            LEX_ERROR();
        case 122:
            if (lookahead == 'e')
                ADVANCE(123);
            LEX_ERROR();
        case 123:
            ACCEPT_TOKEN(ts_sym__case);
        case 124:
            if (lookahead == 'e')
                ADVANCE(125);
            LEX_ERROR();
        case 125:
            if (lookahead == 'f')
                ADVANCE(126);
            LEX_ERROR();
        case 126:
            if (lookahead == 'a')
                ADVANCE(127);
            LEX_ERROR();
        case 127:
            if (lookahead == 'u')
                ADVANCE(128);
            LEX_ERROR();
        case 128:
            if (lookahead == 'l')
                ADVANCE(129);
            LEX_ERROR();
        case 129:
            if (lookahead == 't')
                ADVANCE(130);
            LEX_ERROR();
        case 130:
            ACCEPT_TOKEN(ts_sym__default);
        case 131:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 132:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
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
        case 133:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
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
                ADVANCE(89);
            if (lookahead == 'd')
                ADVANCE(93);
            if (lookahead == 'e')
                ADVANCE(134);
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
                ADVANCE(70);
            LEX_ERROR();
        case 134:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(135);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 135:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(136);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 136:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(137);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 137:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__else);
        case 138:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
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
                ADVANCE(85);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == 'v')
                ADVANCE(48);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
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
                ADVANCE(134);
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
                ADVANCE(70);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
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
                ADVANCE(134);
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
        case 142:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\n')
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
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
                ADVANCE(68);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(89);
            if (lookahead == 'd')
                ADVANCE(93);
            if (lookahead == 'e')
                ADVANCE(134);
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
                ADVANCE(70);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\n')
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
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
                ADVANCE(68);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(89);
            if (lookahead == 'd')
                ADVANCE(93);
            if (lookahead == 'e')
                ADVANCE(134);
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
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__terminator);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\n')
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(59);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '.')
                ADVANCE(55);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(63);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(65);
            if (lookahead == '?')
                ADVANCE(57);
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
                ADVANCE(68);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(89);
            if (lookahead == 'd')
                ADVANCE(93);
            if (lookahead == 'e')
                ADVANCE(134);
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
                ADVANCE(70);
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
    [6] = 84,
    [7] = 60,
    [8] = 58,
    [9] = 52,
    [10] = 84,
    [11] = 60,
    [12] = 58,
    [13] = 60,
    [14] = 102,
    [15] = 62,
    [16] = 84,
    [17] = 60,
    [18] = 58,
    [19] = 62,
    [20] = 102,
    [21] = 60,
    [22] = 58,
    [23] = 66,
    [24] = 64,
    [25] = 102,
    [26] = 67,
    [27] = 84,
    [28] = 60,
    [29] = 58,
    [30] = 67,
    [31] = 60,
    [32] = 64,
    [33] = 102,
    [34] = 60,
    [35] = 60,
    [36] = 117,
    [37] = 113,
    [38] = 60,
    [39] = 69,
    [40] = 69,
    [41] = 69,
    [42] = 52,
    [43] = 69,
    [44] = 102,
    [45] = 62,
    [46] = 102,
    [47] = 52,
    [48] = 66,
    [49] = 71,
    [50] = 102,
    [51] = 67,
    [52] = 102,
    [53] = 62,
    [54] = 102,
    [55] = 67,
    [56] = 66,
    [57] = 73,
    [58] = 102,
    [59] = 67,
    [60] = 73,
    [61] = 67,
    [62] = 73,
    [63] = 102,
    [64] = 67,
    [65] = 67,
    [66] = 117,
    [67] = 113,
    [68] = 67,
    [69] = 69,
    [70] = 52,
    [71] = 71,
    [72] = 102,
    [73] = 52,
    [74] = 52,
    [75] = 117,
    [76] = 113,
    [77] = 52,
    [78] = 69,
    [79] = 74,
    [80] = 52,
    [81] = 76,
    [82] = 69,
    [83] = 116,
    [84] = 138,
    [85] = 102,
    [86] = 102,
    [87] = 78,
    [88] = 84,
    [89] = 60,
    [90] = 58,
    [91] = 78,
    [92] = 107,
    [93] = 80,
    [94] = 79,
    [95] = 60,
    [96] = 140,
    [97] = 80,
    [98] = 79,
    [99] = 106,
    [100] = 102,
    [101] = 81,
    [102] = 79,
    [103] = 84,
    [104] = 60,
    [105] = 58,
    [106] = 81,
    [107] = 81,
    [108] = 108,
    [109] = 83,
    [110] = 82,
    [111] = 60,
    [112] = 84,
    [113] = 60,
    [114] = 58,
    [115] = 83,
    [116] = 83,
    [117] = 102,
    [118] = 62,
    [119] = 102,
    [120] = 83,
    [121] = 66,
    [122] = 86,
    [123] = 102,
    [124] = 67,
    [125] = 86,
    [126] = 107,
    [127] = 80,
    [128] = 79,
    [129] = 67,
    [130] = 106,
    [131] = 102,
    [132] = 81,
    [133] = 79,
    [134] = 67,
    [135] = 102,
    [136] = 62,
    [137] = 102,
    [138] = 81,
    [139] = 66,
    [140] = 87,
    [141] = 102,
    [142] = 67,
    [143] = 87,
    [144] = 108,
    [145] = 83,
    [146] = 82,
    [147] = 67,
    [148] = 102,
    [149] = 83,
    [150] = 82,
    [151] = 83,
    [152] = 86,
    [153] = 102,
    [154] = 83,
    [155] = 83,
    [156] = 117,
    [157] = 113,
    [158] = 83,
    [159] = 69,
    [160] = 74,
    [161] = 83,
    [162] = 116,
    [163] = 102,
    [164] = 78,
    [165] = 132,
    [166] = 139,
    [167] = 132,
    [168] = 69,
    [169] = 76,
    [170] = 116,
    [171] = 102,
    [172] = 78,
    [173] = 113,
    [174] = 119,
    [175] = 119,
    [176] = 102,
    [177] = 62,
    [178] = 88,
    [179] = 88,
    [180] = 88,
    [181] = 52,
    [182] = 88,
    [183] = 76,
    [184] = 76,
    [185] = 88,
    [186] = 116,
    [187] = 138,
    [188] = 102,
    [189] = 102,
    [190] = 78,
    [191] = 132,
    [192] = 88,
    [193] = 116,
    [194] = 102,
    [195] = 78,
    [196] = 132,
    [197] = 133,
    [198] = 132,
    [199] = 88,
    [200] = 116,
    [201] = 102,
    [202] = 78,
    [203] = 113,
    [204] = 119,
    [205] = 106,
    [206] = 88,
    [207] = 102,
    [208] = 100,
    [209] = 84,
    [210] = 60,
    [211] = 58,
    [212] = 100,
    [213] = 100,
    [214] = 102,
    [215] = 62,
    [216] = 102,
    [217] = 100,
    [218] = 66,
    [219] = 101,
    [220] = 102,
    [221] = 67,
    [222] = 101,
    [223] = 100,
    [224] = 101,
    [225] = 102,
    [226] = 100,
    [227] = 100,
    [228] = 117,
    [229] = 113,
    [230] = 100,
    [231] = 69,
    [232] = 74,
    [233] = 100,
    [234] = 102,
    [235] = 52,
    [236] = 69,
    [237] = 101,
    [238] = 71,
    [239] = 107,
    [240] = 80,
    [241] = 79,
    [242] = 100,
    [243] = 106,
    [244] = 102,
    [245] = 81,
    [246] = 79,
    [247] = 100,
    [248] = 81,
    [249] = 87,
    [250] = 102,
    [251] = 81,
    [252] = 81,
    [253] = 117,
    [254] = 113,
    [255] = 81,
    [256] = 69,
    [257] = 74,
    [258] = 81,
    [259] = 79,
    [260] = 69,
    [261] = 103,
    [262] = 79,
    [263] = 52,
    [264] = 69,
    [265] = 109,
    [266] = 102,
    [267] = 81,
    [268] = 79,
    [269] = 52,
    [270] = 107,
    [271] = 80,
    [272] = 79,
    [273] = 81,
    [274] = 106,
    [275] = 102,
    [276] = 81,
    [277] = 79,
    [278] = 81,
    [279] = 108,
    [280] = 83,
    [281] = 82,
    [282] = 81,
    [283] = 105,
    [284] = 107,
    [285] = 80,
    [286] = 79,
    [287] = 83,
    [288] = 106,
    [289] = 102,
    [290] = 81,
    [291] = 79,
    [292] = 83,
    [293] = 83,
    [294] = 108,
    [295] = 83,
    [296] = 82,
    [297] = 83,
    [298] = 105,
    [299] = 83,
    [300] = 81,
    [301] = 81,
    [302] = 111,
    [303] = 79,
    [304] = 52,
    [305] = 108,
    [306] = 83,
    [307] = 82,
    [308] = 52,
    [309] = 105,
    [310] = 52,
    [311] = 116,
    [312] = 113,
    [313] = 81,
    [314] = 115,
    [315] = 114,
    [316] = 58,
    [317] = 113,
    [318] = 66,
    [319] = 114,
    [320] = 58,
    [321] = 113,
    [322] = 100,
    [323] = 108,
    [324] = 83,
    [325] = 82,
    [326] = 100,
    [327] = 105,
    [328] = 100,
    [329] = 79,
    [330] = 116,
    [331] = 113,
    [332] = 100,
    [333] = 102,
    [334] = 62,
    [335] = 102,
    [336] = 62,
    [337] = 66,
    [338] = 118,
    [339] = 102,
    [340] = 67,
    [341] = 118,
    [342] = 62,
    [343] = 118,
    [344] = 102,
    [345] = 62,
    [346] = 62,
    [347] = 117,
    [348] = 113,
    [349] = 62,
    [350] = 69,
    [351] = 74,
    [352] = 62,
    [353] = 79,
    [354] = 116,
    [355] = 113,
    [356] = 62,
    [357] = 107,
    [358] = 80,
    [359] = 79,
    [360] = 62,
    [361] = 106,
    [362] = 102,
    [363] = 81,
    [364] = 79,
    [365] = 62,
    [366] = 62,
    [367] = 108,
    [368] = 83,
    [369] = 82,
    [370] = 62,
    [371] = 105,
    [372] = 62,
    [373] = 52,
    [374] = 88,
    [375] = 71,
    [376] = 119,
    [377] = 69,
    [378] = 103,
    [379] = 88,
    [380] = 79,
    [381] = 79,
    [382] = 88,
    [383] = 102,
    [384] = 62,
    [385] = 102,
    [386] = 78,
    [387] = 66,
    [388] = 131,
    [389] = 102,
    [390] = 67,
    [391] = 131,
    [392] = 78,
    [393] = 131,
    [394] = 102,
    [395] = 78,
    [396] = 78,
    [397] = 117,
    [398] = 113,
    [399] = 78,
    [400] = 69,
    [401] = 74,
    [402] = 78,
    [403] = 79,
    [404] = 116,
    [405] = 113,
    [406] = 78,
    [407] = 107,
    [408] = 80,
    [409] = 79,
    [410] = 78,
    [411] = 106,
    [412] = 102,
    [413] = 81,
    [414] = 79,
    [415] = 78,
    [416] = 78,
    [417] = 108,
    [418] = 83,
    [419] = 82,
    [420] = 78,
    [421] = 105,
    [422] = 78,
    [423] = 58,
    [424] = 133,
    [425] = 52,
    [426] = 133,
    [427] = 76,
    [428] = 76,
    [429] = 133,
    [430] = 116,
    [431] = 138,
    [432] = 102,
    [433] = 102,
    [434] = 78,
    [435] = 132,
    [436] = 133,
    [437] = 116,
    [438] = 102,
    [439] = 78,
    [440] = 132,
    [441] = 133,
    [442] = 132,
    [443] = 133,
    [444] = 116,
    [445] = 102,
    [446] = 78,
    [447] = 113,
    [448] = 119,
    [449] = 79,
    [450] = 133,
    [451] = 58,
    [452] = 102,
    [453] = 52,
    [454] = 133,
    [455] = 71,
    [456] = 69,
    [457] = 103,
    [458] = 133,
    [459] = 79,
    [460] = 58,
    [461] = 58,
    [462] = 52,
    [463] = 102,
    [464] = 76,
    [465] = 107,
    [466] = 80,
    [467] = 106,
    [468] = 102,
    [469] = 52,
    [470] = 102,
    [471] = 71,
    [472] = 58,
    [473] = 58,
    [474] = 119,
    [475] = 119,
    [476] = 79,
    [477] = 79,
    [478] = 69,
    [479] = 58,
    [480] = 139,
    [481] = 52,
    [482] = 139,
    [483] = 76,
    [484] = 76,
    [485] = 139,
    [486] = 116,
    [487] = 138,
    [488] = 102,
    [489] = 102,
    [490] = 78,
    [491] = 132,
    [492] = 139,
    [493] = 116,
    [494] = 102,
    [495] = 78,
    [496] = 132,
    [497] = 139,
    [498] = 132,
    [499] = 139,
    [500] = 116,
    [501] = 102,
    [502] = 78,
    [503] = 113,
    [504] = 119,
    [505] = 79,
    [506] = 139,
    [507] = 58,
    [508] = 102,
    [509] = 52,
    [510] = 139,
    [511] = 71,
    [512] = 69,
    [513] = 103,
    [514] = 139,
    [515] = 79,
    [516] = 58,
    [517] = 58,
    [518] = 58,
    [519] = 79,
    [520] = 116,
    [521] = 113,
    [522] = 83,
    [523] = 105,
    [524] = 105,
    [525] = 67,
    [526] = 67,
    [527] = 105,
    [528] = 60,
    [529] = 106,
    [530] = 102,
    [531] = 81,
    [532] = 79,
    [533] = 60,
    [534] = 60,
    [535] = 78,
    [536] = 132,
    [537] = 69,
    [538] = 58,
    [539] = 79,
    [540] = 116,
    [541] = 113,
    [542] = 52,
    [543] = 74,
    [544] = 67,
    [545] = 79,
    [546] = 116,
    [547] = 113,
    [548] = 67,
    [549] = 71,
    [550] = 79,
    [551] = 74,
    [552] = 60,
    [553] = 79,
    [554] = 116,
    [555] = 113,
    [556] = 60,
    [557] = 67,
    [558] = 64,
    [559] = 62,
    [560] = 102,
    [561] = 60,
    [562] = 60,
    [563] = 52,
    [564] = 76,
    [565] = 76,
    [566] = 2,
    [567] = 116,
    [568] = 138,
    [569] = 102,
    [570] = 102,
    [571] = 78,
    [572] = 132,
    [573] = 2,
    [574] = 116,
    [575] = 102,
    [576] = 78,
    [577] = 132,
    [578] = 141,
    [579] = 132,
    [580] = 2,
    [581] = 116,
    [582] = 102,
    [583] = 78,
    [584] = 113,
    [585] = 119,
    [586] = 79,
    [587] = 2,
    [588] = 58,
    [589] = 102,
    [590] = 52,
    [591] = 2,
    [592] = 71,
    [593] = 69,
    [594] = 103,
    [595] = 2,
    [596] = 79,
    [597] = 141,
    [598] = 52,
    [599] = 141,
    [600] = 76,
    [601] = 76,
    [602] = 141,
    [603] = 116,
    [604] = 138,
    [605] = 102,
    [606] = 102,
    [607] = 78,
    [608] = 132,
    [609] = 141,
    [610] = 116,
    [611] = 102,
    [612] = 78,
    [613] = 132,
    [614] = 141,
    [615] = 132,
    [616] = 141,
    [617] = 116,
    [618] = 102,
    [619] = 78,
    [620] = 113,
    [621] = 119,
    [622] = 79,
    [623] = 141,
    [624] = 58,
    [625] = 102,
    [626] = 52,
    [627] = 141,
    [628] = 71,
    [629] = 69,
    [630] = 103,
    [631] = 141,
    [632] = 79,
    [633] = 58,
    [634] = 58,
    [635] = 58,
    [636] = 58,
    [637] = 0,
    [638] = 0,
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
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(564),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(565),
        [ts_sym__for] = SHIFT(567),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(574),
        [ts_sym__switch] = SHIFT(581),
        [ts_sym__var] = SHIFT(589),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_program_repeat0] = SHIFT(638),
        [ts_aux_sym_token0] = SHIFT(593),
        [ts_aux_sym_token9] = SHIFT(305),
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
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(564),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(565),
        [ts_sym__for] = SHIFT(567),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(574),
        [ts_sym__switch] = SHIFT(581),
        [ts_sym__var] = SHIFT(589),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_program_repeat0] = SHIFT(637),
        [ts_aux_sym_token0] = SHIFT(593),
        [ts_aux_sym_token9] = SHIFT(305),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    [4] = {
        [ts_sym__terminator] = SHIFT(5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [6] = {
        [ts_sym_expression] = SHIFT(7),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(563),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [7] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [8] = {
        [ts_aux_sym_token3] = SHIFT(9),
    },
    [9] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [10] = {
        [ts_sym_expression] = SHIFT(11),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(562),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [11] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [12] = {
        [ts_aux_sym_token3] = SHIFT(13),
    },
    [13] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [14] = {
        [ts_sym_expression] = SHIFT(15),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [15] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(560),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [16] = {
        [ts_sym_expression] = SHIFT(17),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(559),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [17] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(18),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [18] = {
        [ts_aux_sym_token3] = SHIFT(19),
    },
    [19] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [20] = {
        [ts_sym_expression] = SHIFT(21),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [21] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(22),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [22] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 3),
    },
    [23] = {
        [ts_sym_identifier] = SHIFT(24),
    },
    [24] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [25] = {
        [ts_sym_expression] = SHIFT(26),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [26] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(558),
    },
    [27] = {
        [ts_sym_expression] = SHIFT(28),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(557),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [28] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(29),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [29] = {
        [ts_aux_sym_token3] = SHIFT(30),
    },
    [30] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
    },
    [31] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [32] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(33),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [33] = {
        [ts_sym_expression] = SHIFT(34),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [34] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [35] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [36] = {
        [ts_sym_formal_parameters] = SHIFT(37),
        [ts_sym_identifier] = SHIFT(554),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [37] = {
        [ts_sym_statement_block] = SHIFT(38),
        [ts_aux_sym_token0] = SHIFT(39),
    },
    [38] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [39] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(551),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(553),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [40] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(169),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(550),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [41] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    [42] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [43] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [44] = {
        [ts_sym_expression] = SHIFT(45),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [45] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [46] = {
        [ts_sym_expression] = SHIFT(47),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [47] = {
        [ts_sym__terminator] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [48] = {
        [ts_sym_identifier] = SHIFT(49),
    },
    [49] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [50] = {
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [51] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(549),
    },
    [52] = {
        [ts_sym_expression] = SHIFT(53),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [53] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(54),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [54] = {
        [ts_sym_expression] = SHIFT(55),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [55] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = REDUCE(ts_sym_ternary, 5),
    },
    [56] = {
        [ts_sym_identifier] = SHIFT(57),
    },
    [57] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
    },
    [58] = {
        [ts_sym_expression] = SHIFT(59),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [59] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
    },
    [60] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
    },
    [61] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
    },
    [62] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(63),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
    },
    [63] = {
        [ts_sym_expression] = SHIFT(64),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [64] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
    },
    [65] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
    },
    [66] = {
        [ts_sym_formal_parameters] = SHIFT(67),
        [ts_sym_identifier] = SHIFT(546),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [67] = {
        [ts_sym_statement_block] = SHIFT(68),
        [ts_aux_sym_token0] = SHIFT(69),
    },
    [68] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
    },
    [69] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(543),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(545),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [70] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [71] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [72] = {
        [ts_sym_expression] = SHIFT(73),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [73] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [74] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [75] = {
        [ts_sym_formal_parameters] = SHIFT(76),
        [ts_sym_identifier] = SHIFT(540),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [76] = {
        [ts_sym_statement_block] = SHIFT(77),
        [ts_aux_sym_token0] = SHIFT(78),
    },
    [77] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [78] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(79),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(539),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [79] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(80),
    },
    [80] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [81] = {
        [ts_sym__terminator] = SHIFT(82),
    },
    [82] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
    },
    [83] = {
        [ts_aux_sym_token2] = SHIFT(84),
    },
    [84] = {
        [ts_sym_var_declaration] = SHIFT(85),
        [ts_sym_expression_statement] = SHIFT(85),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__var] = SHIFT(468),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [85] = {
        [ts_sym_expression_statement] = SHIFT(86),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [86] = {
        [ts_sym_expression] = SHIFT(87),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(538),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [87] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(536),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [88] = {
        [ts_sym_expression] = SHIFT(89),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(535),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [89] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(90),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [90] = {
        [ts_aux_sym_token3] = SHIFT(91),
    },
    [91] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [92] = {
        [ts_builtin_sym_error] = SHIFT(93),
        [ts_sym_string] = SHIFT(529),
        [ts_sym_identifier] = SHIFT(529),
        [ts_aux_sym_token1] = SHIFT(534),
    },
    [93] = {
        [ts_aux_sym_object_repeat0] = SHIFT(94),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [94] = {
        [ts_aux_sym_token1] = SHIFT(95),
    },
    [95] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [96] = {
        [ts_builtin_sym_error] = SHIFT(97),
        [ts_sym_string] = SHIFT(99),
        [ts_sym_identifier] = SHIFT(99),
    },
    [97] = {
        [ts_aux_sym_object_repeat0] = SHIFT(98),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [98] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [99] = {
        [ts_aux_sym_token4] = SHIFT(100),
    },
    [100] = {
        [ts_sym_expression] = SHIFT(101),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [101] = {
        [ts_aux_sym_object_repeat0] = SHIFT(102),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [102] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [103] = {
        [ts_sym_expression] = SHIFT(104),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(107),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [104] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(105),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [105] = {
        [ts_aux_sym_token3] = SHIFT(106),
    },
    [106] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [107] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [108] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(527),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(528),
    },
    [109] = {
        [ts_aux_sym_array_repeat0] = SHIFT(110),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [110] = {
        [ts_aux_sym_token10] = SHIFT(111),
    },
    [111] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [112] = {
        [ts_sym_expression] = SHIFT(113),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(116),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [113] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(114),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [114] = {
        [ts_aux_sym_token3] = SHIFT(115),
    },
    [115] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
    },
    [116] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
    },
    [117] = {
        [ts_sym_expression] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [118] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [119] = {
        [ts_sym_expression] = SHIFT(120),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
    },
    [120] = {
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_sym_ternary, 5),
    },
    [121] = {
        [ts_sym_identifier] = SHIFT(122),
    },
    [122] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
    },
    [123] = {
        [ts_sym_expression] = SHIFT(124),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [124] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(125),
    },
    [125] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
    },
    [126] = {
        [ts_builtin_sym_error] = SHIFT(127),
        [ts_sym_string] = SHIFT(130),
        [ts_sym_identifier] = SHIFT(130),
        [ts_aux_sym_token1] = SHIFT(526),
    },
    [127] = {
        [ts_aux_sym_object_repeat0] = SHIFT(128),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [128] = {
        [ts_aux_sym_token1] = SHIFT(129),
    },
    [129] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
    },
    [130] = {
        [ts_aux_sym_token4] = SHIFT(131),
    },
    [131] = {
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [132] = {
        [ts_aux_sym_object_repeat0] = SHIFT(133),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [133] = {
        [ts_aux_sym_token1] = SHIFT(134),
    },
    [134] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
    },
    [135] = {
        [ts_sym_expression] = SHIFT(136),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [136] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(137),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [137] = {
        [ts_sym_expression] = SHIFT(138),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [138] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [139] = {
        [ts_sym_identifier] = SHIFT(140),
    },
    [140] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [142] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(143),
    },
    [143] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [144] = {
        [ts_sym_expression] = SHIFT(145),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(524),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(525),
    },
    [145] = {
        [ts_aux_sym_array_repeat0] = SHIFT(146),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [146] = {
        [ts_aux_sym_token10] = SHIFT(147),
    },
    [147] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
    },
    [148] = {
        [ts_sym_expression] = SHIFT(149),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(523),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
    },
    [149] = {
        [ts_aux_sym_array_repeat0] = SHIFT(150),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [150] = {
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [151] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
    },
    [152] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(153),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
    },
    [153] = {
        [ts_sym_expression] = SHIFT(154),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
    },
    [154] = {
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
    },
    [155] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
    },
    [156] = {
        [ts_sym_formal_parameters] = SHIFT(157),
        [ts_sym_identifier] = SHIFT(520),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [157] = {
        [ts_sym_statement_block] = SHIFT(158),
        [ts_aux_sym_token0] = SHIFT(159),
    },
    [158] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
    },
    [159] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(160),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(519),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [160] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(161),
    },
    [161] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
    },
    [162] = {
        [ts_aux_sym_token2] = SHIFT(163),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(518),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [164] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(165),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [165] = {
        [ts_sym_statement] = SHIFT(166),
        [ts_sym_statement_block] = SHIFT(480),
        [ts_sym_for_statement] = SHIFT(480),
        [ts_sym_if_statement] = SHIFT(480),
        [ts_sym_switch_statement] = SHIFT(480),
        [ts_sym_break_statement] = SHIFT(480),
        [ts_sym_var_declaration] = SHIFT(480),
        [ts_sym_expression_statement] = SHIFT(480),
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(483),
        [ts_sym__break] = SHIFT(484),
        [ts_sym__for] = SHIFT(486),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(493),
        [ts_sym__switch] = SHIFT(500),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(512),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [166] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(167),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    [167] = {
        [ts_sym_statement] = SHIFT(168),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(169),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [168] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    [169] = {
        [ts_sym__terminator] = SHIFT(43),
    },
    [170] = {
        [ts_aux_sym_token2] = SHIFT(171),
    },
    [171] = {
        [ts_sym_expression] = SHIFT(172),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(479),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [172] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(173),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [173] = {
        [ts_aux_sym_token0] = SHIFT(174),
    },
    [174] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(477),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [175] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(476),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [176] = {
        [ts_sym_expression] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [177] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(178),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [178] = {
        [ts_sym_statement] = SHIFT(179),
        [ts_sym_statement_block] = SHIFT(180),
        [ts_sym_for_statement] = SHIFT(180),
        [ts_sym_if_statement] = SHIFT(180),
        [ts_sym_switch_statement] = SHIFT(180),
        [ts_sym_break_statement] = SHIFT(180),
        [ts_sym_var_declaration] = SHIFT(180),
        [ts_sym_expression_statement] = SHIFT(180),
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(183),
        [ts_sym__break] = SHIFT(184),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(186),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(193),
        [ts_sym__switch] = SHIFT(200),
        [ts_sym__var] = SHIFT(207),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(475),
        [ts_aux_sym_token0] = SHIFT(377),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [179] = {
        [ts_sym_statement] = SHIFT(179),
        [ts_sym_statement_block] = SHIFT(180),
        [ts_sym_for_statement] = SHIFT(180),
        [ts_sym_if_statement] = SHIFT(180),
        [ts_sym_switch_statement] = SHIFT(180),
        [ts_sym_break_statement] = SHIFT(180),
        [ts_sym_var_declaration] = SHIFT(180),
        [ts_sym_expression_statement] = SHIFT(180),
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(183),
        [ts_sym__break] = SHIFT(184),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(186),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(193),
        [ts_sym__switch] = SHIFT(200),
        [ts_sym__var] = SHIFT(207),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(474),
        [ts_aux_sym_token0] = SHIFT(377),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [180] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    [181] = {
        [ts_sym__terminator] = SHIFT(182),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [182] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [183] = {
        [ts_sym__terminator] = SHIFT(182),
    },
    [184] = {
        [ts_sym__terminator] = SHIFT(185),
    },
    [185] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
    },
    [186] = {
        [ts_aux_sym_token2] = SHIFT(187),
    },
    [187] = {
        [ts_sym_var_declaration] = SHIFT(188),
        [ts_sym_expression_statement] = SHIFT(188),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__var] = SHIFT(468),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [188] = {
        [ts_sym_expression_statement] = SHIFT(189),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [189] = {
        [ts_sym_expression] = SHIFT(190),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(473),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [190] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(191),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [191] = {
        [ts_sym_statement] = SHIFT(192),
        [ts_sym_statement_block] = SHIFT(180),
        [ts_sym_for_statement] = SHIFT(180),
        [ts_sym_if_statement] = SHIFT(180),
        [ts_sym_switch_statement] = SHIFT(180),
        [ts_sym_break_statement] = SHIFT(180),
        [ts_sym_var_declaration] = SHIFT(180),
        [ts_sym_expression_statement] = SHIFT(180),
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(183),
        [ts_sym__break] = SHIFT(184),
        [ts_sym__for] = SHIFT(186),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(193),
        [ts_sym__switch] = SHIFT(200),
        [ts_sym__var] = SHIFT(207),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(377),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [192] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    [193] = {
        [ts_aux_sym_token2] = SHIFT(194),
    },
    [194] = {
        [ts_sym_expression] = SHIFT(195),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(472),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [195] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(196),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [196] = {
        [ts_sym_statement] = SHIFT(197),
        [ts_sym_statement_block] = SHIFT(424),
        [ts_sym_for_statement] = SHIFT(424),
        [ts_sym_if_statement] = SHIFT(424),
        [ts_sym_switch_statement] = SHIFT(424),
        [ts_sym_break_statement] = SHIFT(424),
        [ts_sym_var_declaration] = SHIFT(424),
        [ts_sym_expression_statement] = SHIFT(424),
        [ts_sym_expression] = SHIFT(425),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(427),
        [ts_sym__break] = SHIFT(428),
        [ts_sym__for] = SHIFT(430),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(437),
        [ts_sym__switch] = SHIFT(444),
        [ts_sym__var] = SHIFT(452),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(456),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [197] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(198),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    [198] = {
        [ts_sym_statement] = SHIFT(199),
        [ts_sym_statement_block] = SHIFT(180),
        [ts_sym_for_statement] = SHIFT(180),
        [ts_sym_if_statement] = SHIFT(180),
        [ts_sym_switch_statement] = SHIFT(180),
        [ts_sym_break_statement] = SHIFT(180),
        [ts_sym_var_declaration] = SHIFT(180),
        [ts_sym_expression_statement] = SHIFT(180),
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(183),
        [ts_sym__break] = SHIFT(184),
        [ts_sym__for] = SHIFT(186),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(193),
        [ts_sym__switch] = SHIFT(200),
        [ts_sym__var] = SHIFT(207),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(377),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [199] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    [200] = {
        [ts_aux_sym_token2] = SHIFT(201),
    },
    [201] = {
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(423),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [202] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(203),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [203] = {
        [ts_aux_sym_token0] = SHIFT(204),
    },
    [204] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(381),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [205] = {
        [ts_aux_sym_token4] = SHIFT(206),
    },
    [206] = {
        [ts_sym_statement] = SHIFT(179),
        [ts_sym_statement_block] = SHIFT(180),
        [ts_sym_for_statement] = SHIFT(180),
        [ts_sym_if_statement] = SHIFT(180),
        [ts_sym_switch_statement] = SHIFT(180),
        [ts_sym_break_statement] = SHIFT(180),
        [ts_sym_var_declaration] = SHIFT(180),
        [ts_sym_expression_statement] = SHIFT(180),
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(183),
        [ts_sym__break] = SHIFT(184),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(186),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(193),
        [ts_sym__switch] = SHIFT(200),
        [ts_sym__var] = SHIFT(207),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(376),
        [ts_aux_sym_token0] = SHIFT(377),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [207] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(373),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(375),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [208] = {
        [ts_aux_sym_token2] = SHIFT(209),
        [ts_aux_sym_token5] = SHIFT(214),
        [ts_aux_sym_token8] = SHIFT(218),
        [ts_aux_sym_token9] = SHIFT(220),
    },
    [209] = {
        [ts_sym_expression] = SHIFT(210),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token3] = SHIFT(213),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [210] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(211),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(20),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [211] = {
        [ts_aux_sym_token3] = SHIFT(212),
    },
    [212] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [213] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [214] = {
        [ts_sym_expression] = SHIFT(215),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [215] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(216),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [216] = {
        [ts_sym_expression] = SHIFT(217),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [217] = {
        [ts_aux_sym_token2] = SHIFT(209),
        [ts_aux_sym_token5] = SHIFT(214),
        [ts_aux_sym_token8] = SHIFT(218),
        [ts_aux_sym_token9] = SHIFT(220),
    },
    [218] = {
        [ts_sym_identifier] = SHIFT(219),
    },
    [219] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [220] = {
        [ts_sym_expression] = SHIFT(221),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [221] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(222),
    },
    [222] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [223] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [224] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(225),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [225] = {
        [ts_sym_expression] = SHIFT(226),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [226] = {
        [ts_aux_sym_token2] = SHIFT(209),
        [ts_aux_sym_token5] = SHIFT(214),
        [ts_aux_sym_token8] = SHIFT(218),
        [ts_aux_sym_token9] = SHIFT(220),
    },
    [227] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [228] = {
        [ts_sym_formal_parameters] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(330),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [229] = {
        [ts_sym_statement_block] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(231),
    },
    [230] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [231] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(232),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(329),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [232] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(233),
    },
    [233] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [234] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(235),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(238),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [235] = {
        [ts_sym__terminator] = SHIFT(236),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [236] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [237] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [238] = {
        [ts_sym__terminator] = SHIFT(236),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [239] = {
        [ts_builtin_sym_error] = SHIFT(240),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(243),
        [ts_aux_sym_token1] = SHIFT(322),
    },
    [240] = {
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [241] = {
        [ts_aux_sym_token1] = SHIFT(242),
    },
    [242] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [243] = {
        [ts_aux_sym_token4] = SHIFT(244),
    },
    [244] = {
        [ts_sym_expression] = SHIFT(245),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [245] = {
        [ts_aux_sym_object_repeat0] = SHIFT(246),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [246] = {
        [ts_aux_sym_token1] = SHIFT(247),
    },
    [247] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [248] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [249] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(250),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [250] = {
        [ts_sym_expression] = SHIFT(251),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [251] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [252] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [253] = {
        [ts_sym_formal_parameters] = SHIFT(254),
        [ts_sym_identifier] = SHIFT(311),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [254] = {
        [ts_sym_statement_block] = SHIFT(255),
        [ts_aux_sym_token0] = SHIFT(256),
    },
    [255] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [256] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(257),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(259),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [257] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(258),
    },
    [258] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [259] = {
        [ts_aux_sym_token1] = SHIFT(258),
    },
    [260] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(261),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(265),
        [ts_sym_identifier] = SHIFT(302),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(303),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = SHIFT(304),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [261] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(264),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [262] = {
        [ts_aux_sym_token1] = SHIFT(263),
    },
    [263] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [264] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [265] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = SHIFT(266),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [266] = {
        [ts_sym_expression] = SHIFT(267),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [267] = {
        [ts_aux_sym_object_repeat0] = SHIFT(268),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [268] = {
        [ts_aux_sym_token1] = SHIFT(269),
    },
    [269] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [270] = {
        [ts_builtin_sym_error] = SHIFT(271),
        [ts_sym_string] = SHIFT(274),
        [ts_sym_identifier] = SHIFT(274),
        [ts_aux_sym_token1] = SHIFT(301),
    },
    [271] = {
        [ts_aux_sym_object_repeat0] = SHIFT(272),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [272] = {
        [ts_aux_sym_token1] = SHIFT(273),
    },
    [273] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [274] = {
        [ts_aux_sym_token4] = SHIFT(275),
    },
    [275] = {
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [276] = {
        [ts_aux_sym_object_repeat0] = SHIFT(277),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [277] = {
        [ts_aux_sym_token1] = SHIFT(278),
    },
    [278] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [279] = {
        [ts_sym_expression] = SHIFT(280),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(283),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(300),
    },
    [280] = {
        [ts_aux_sym_array_repeat0] = SHIFT(281),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [281] = {
        [ts_aux_sym_token10] = SHIFT(282),
    },
    [282] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [283] = {
        [ts_aux_sym_array_repeat0] = SHIFT(281),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [284] = {
        [ts_builtin_sym_error] = SHIFT(285),
        [ts_sym_string] = SHIFT(288),
        [ts_sym_identifier] = SHIFT(288),
        [ts_aux_sym_token1] = SHIFT(293),
    },
    [285] = {
        [ts_aux_sym_object_repeat0] = SHIFT(286),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [286] = {
        [ts_aux_sym_token1] = SHIFT(287),
    },
    [287] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
    },
    [288] = {
        [ts_aux_sym_token4] = SHIFT(289),
    },
    [289] = {
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [290] = {
        [ts_aux_sym_object_repeat0] = SHIFT(291),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [291] = {
        [ts_aux_sym_token1] = SHIFT(292),
    },
    [292] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
    },
    [293] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
    },
    [294] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(298),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(299),
    },
    [295] = {
        [ts_aux_sym_array_repeat0] = SHIFT(296),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [296] = {
        [ts_aux_sym_token10] = SHIFT(297),
    },
    [297] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
    },
    [298] = {
        [ts_aux_sym_array_repeat0] = SHIFT(296),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [299] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
    },
    [300] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [301] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [302] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(266),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [303] = {
        [ts_aux_sym_token1] = SHIFT(264),
    },
    [304] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [305] = {
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(309),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(310),
    },
    [306] = {
        [ts_aux_sym_array_repeat0] = SHIFT(307),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [307] = {
        [ts_aux_sym_token10] = SHIFT(308),
    },
    [308] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [309] = {
        [ts_aux_sym_array_repeat0] = SHIFT(307),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [310] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [311] = {
        [ts_sym_formal_parameters] = SHIFT(312),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [312] = {
        [ts_sym_statement_block] = SHIFT(313),
        [ts_aux_sym_token0] = SHIFT(256),
    },
    [313] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [314] = {
        [ts_sym_identifier] = SHIFT(315),
        [ts_aux_sym_token3] = SHIFT(321),
    },
    [315] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(316),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(318),
    },
    [316] = {
        [ts_aux_sym_token3] = SHIFT(317),
    },
    [317] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [318] = {
        [ts_sym_identifier] = SHIFT(319),
    },
    [319] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(320),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(318),
    },
    [320] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [321] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [322] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [323] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(327),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(328),
    },
    [324] = {
        [ts_aux_sym_array_repeat0] = SHIFT(325),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [325] = {
        [ts_aux_sym_token10] = SHIFT(326),
    },
    [326] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [327] = {
        [ts_aux_sym_array_repeat0] = SHIFT(325),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [328] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [329] = {
        [ts_aux_sym_token1] = SHIFT(233),
    },
    [330] = {
        [ts_sym_formal_parameters] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [331] = {
        [ts_sym_statement_block] = SHIFT(332),
        [ts_aux_sym_token0] = SHIFT(231),
    },
    [332] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [333] = {
        [ts_sym_expression] = SHIFT(334),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [334] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(335),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [335] = {
        [ts_sym_expression] = SHIFT(336),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [336] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [337] = {
        [ts_sym_identifier] = SHIFT(338),
    },
    [338] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [339] = {
        [ts_sym_expression] = SHIFT(340),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [340] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(341),
    },
    [341] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [342] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [343] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(344),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [344] = {
        [ts_sym_expression] = SHIFT(345),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [345] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [346] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [347] = {
        [ts_sym_formal_parameters] = SHIFT(348),
        [ts_sym_identifier] = SHIFT(354),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [348] = {
        [ts_sym_statement_block] = SHIFT(349),
        [ts_aux_sym_token0] = SHIFT(350),
    },
    [349] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [350] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(351),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(353),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [351] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(352),
    },
    [352] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [353] = {
        [ts_aux_sym_token1] = SHIFT(352),
    },
    [354] = {
        [ts_sym_formal_parameters] = SHIFT(355),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [355] = {
        [ts_sym_statement_block] = SHIFT(356),
        [ts_aux_sym_token0] = SHIFT(350),
    },
    [356] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [357] = {
        [ts_builtin_sym_error] = SHIFT(358),
        [ts_sym_string] = SHIFT(361),
        [ts_sym_identifier] = SHIFT(361),
        [ts_aux_sym_token1] = SHIFT(366),
    },
    [358] = {
        [ts_aux_sym_object_repeat0] = SHIFT(359),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [359] = {
        [ts_aux_sym_token1] = SHIFT(360),
    },
    [360] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [361] = {
        [ts_aux_sym_token4] = SHIFT(362),
    },
    [362] = {
        [ts_sym_expression] = SHIFT(363),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [363] = {
        [ts_aux_sym_object_repeat0] = SHIFT(364),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [364] = {
        [ts_aux_sym_token1] = SHIFT(365),
    },
    [365] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [366] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [367] = {
        [ts_sym_expression] = SHIFT(368),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(371),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(372),
    },
    [368] = {
        [ts_aux_sym_array_repeat0] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [369] = {
        [ts_aux_sym_token10] = SHIFT(370),
    },
    [370] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [371] = {
        [ts_aux_sym_array_repeat0] = SHIFT(369),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [372] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [373] = {
        [ts_sym__terminator] = SHIFT(374),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [374] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [375] = {
        [ts_sym__terminator] = SHIFT(374),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [376] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
    },
    [377] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(378),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(265),
        [ts_sym_identifier] = SHIFT(302),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(380),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = SHIFT(304),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [378] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(379),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [379] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [380] = {
        [ts_aux_sym_token1] = SHIFT(379),
    },
    [381] = {
        [ts_aux_sym_token1] = SHIFT(382),
    },
    [382] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
    },
    [383] = {
        [ts_sym_expression] = SHIFT(384),
        [ts_sym_ternary] = SHIFT(342),
        [ts_sym_assignment] = SHIFT(342),
        [ts_sym_function_expression] = SHIFT(342),
        [ts_sym_function_call] = SHIFT(342),
        [ts_sym_property_access] = SHIFT(343),
        [ts_sym_literal] = SHIFT(342),
        [ts_sym_object] = SHIFT(346),
        [ts_sym_array] = SHIFT(346),
        [ts_sym__function] = SHIFT(347),
        [ts_sym_null] = SHIFT(346),
        [ts_sym_true] = SHIFT(346),
        [ts_sym_false] = SHIFT(346),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(343),
        [ts_sym_number] = SHIFT(346),
        [ts_aux_sym_token0] = SHIFT(357),
        [ts_aux_sym_token9] = SHIFT(367),
    },
    [384] = {
        [ts_aux_sym_token2] = SHIFT(16),
        [ts_aux_sym_token4] = SHIFT(385),
        [ts_aux_sym_token5] = SHIFT(333),
        [ts_aux_sym_token8] = SHIFT(337),
        [ts_aux_sym_token9] = SHIFT(339),
    },
    [385] = {
        [ts_sym_expression] = SHIFT(386),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [386] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [387] = {
        [ts_sym_identifier] = SHIFT(388),
    },
    [388] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [389] = {
        [ts_sym_expression] = SHIFT(390),
        [ts_sym_ternary] = SHIFT(61),
        [ts_sym_assignment] = SHIFT(61),
        [ts_sym_function_expression] = SHIFT(61),
        [ts_sym_function_call] = SHIFT(61),
        [ts_sym_property_access] = SHIFT(62),
        [ts_sym_literal] = SHIFT(61),
        [ts_sym_object] = SHIFT(65),
        [ts_sym_array] = SHIFT(65),
        [ts_sym__function] = SHIFT(66),
        [ts_sym_null] = SHIFT(65),
        [ts_sym_true] = SHIFT(65),
        [ts_sym_false] = SHIFT(65),
        [ts_sym_string] = SHIFT(65),
        [ts_sym_identifier] = SHIFT(62),
        [ts_sym_number] = SHIFT(65),
        [ts_aux_sym_token0] = SHIFT(126),
        [ts_aux_sym_token9] = SHIFT(144),
    },
    [390] = {
        [ts_aux_sym_token2] = SHIFT(27),
        [ts_aux_sym_token5] = SHIFT(52),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(391),
    },
    [391] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [392] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [393] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(394),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [394] = {
        [ts_sym_expression] = SHIFT(395),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [395] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [396] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [397] = {
        [ts_sym_formal_parameters] = SHIFT(398),
        [ts_sym_identifier] = SHIFT(404),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [398] = {
        [ts_sym_statement_block] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(400),
    },
    [399] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [400] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(401),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(403),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [401] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(402),
    },
    [402] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [403] = {
        [ts_aux_sym_token1] = SHIFT(402),
    },
    [404] = {
        [ts_sym_formal_parameters] = SHIFT(405),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [405] = {
        [ts_sym_statement_block] = SHIFT(406),
        [ts_aux_sym_token0] = SHIFT(400),
    },
    [406] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [407] = {
        [ts_builtin_sym_error] = SHIFT(408),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(411),
        [ts_aux_sym_token1] = SHIFT(416),
    },
    [408] = {
        [ts_aux_sym_object_repeat0] = SHIFT(409),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [409] = {
        [ts_aux_sym_token1] = SHIFT(410),
    },
    [410] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [411] = {
        [ts_aux_sym_token4] = SHIFT(412),
    },
    [412] = {
        [ts_sym_expression] = SHIFT(413),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [413] = {
        [ts_aux_sym_object_repeat0] = SHIFT(414),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [414] = {
        [ts_aux_sym_token1] = SHIFT(415),
    },
    [415] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [416] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [417] = {
        [ts_sym_expression] = SHIFT(418),
        [ts_sym_ternary] = SHIFT(151),
        [ts_sym_assignment] = SHIFT(151),
        [ts_sym_function_expression] = SHIFT(151),
        [ts_sym_function_call] = SHIFT(151),
        [ts_sym_property_access] = SHIFT(152),
        [ts_sym_literal] = SHIFT(151),
        [ts_sym_object] = SHIFT(155),
        [ts_sym_array] = SHIFT(155),
        [ts_builtin_sym_error] = SHIFT(421),
        [ts_sym__function] = SHIFT(156),
        [ts_sym_null] = SHIFT(155),
        [ts_sym_true] = SHIFT(155),
        [ts_sym_false] = SHIFT(155),
        [ts_sym_string] = SHIFT(155),
        [ts_sym_identifier] = SHIFT(152),
        [ts_sym_number] = SHIFT(155),
        [ts_aux_sym_token0] = SHIFT(284),
        [ts_aux_sym_token9] = SHIFT(294),
        [ts_aux_sym_token10] = SHIFT(422),
    },
    [418] = {
        [ts_aux_sym_array_repeat0] = SHIFT(419),
        [ts_aux_sym_token2] = SHIFT(112),
        [ts_aux_sym_token5] = SHIFT(117),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token8] = SHIFT(121),
        [ts_aux_sym_token9] = SHIFT(123),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [419] = {
        [ts_aux_sym_token10] = SHIFT(420),
    },
    [420] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [421] = {
        [ts_aux_sym_array_repeat0] = SHIFT(419),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [422] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [423] = {
        [ts_aux_sym_token3] = SHIFT(203),
    },
    [424] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    [425] = {
        [ts_sym__terminator] = SHIFT(426),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [426] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [427] = {
        [ts_sym__terminator] = SHIFT(426),
    },
    [428] = {
        [ts_sym__terminator] = SHIFT(429),
    },
    [429] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
    },
    [430] = {
        [ts_aux_sym_token2] = SHIFT(431),
    },
    [431] = {
        [ts_sym_var_declaration] = SHIFT(432),
        [ts_sym_expression_statement] = SHIFT(432),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__var] = SHIFT(468),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [432] = {
        [ts_sym_expression_statement] = SHIFT(433),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [433] = {
        [ts_sym_expression] = SHIFT(434),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(461),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [434] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(435),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [435] = {
        [ts_sym_statement] = SHIFT(436),
        [ts_sym_statement_block] = SHIFT(424),
        [ts_sym_for_statement] = SHIFT(424),
        [ts_sym_if_statement] = SHIFT(424),
        [ts_sym_switch_statement] = SHIFT(424),
        [ts_sym_break_statement] = SHIFT(424),
        [ts_sym_var_declaration] = SHIFT(424),
        [ts_sym_expression_statement] = SHIFT(424),
        [ts_sym_expression] = SHIFT(425),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(427),
        [ts_sym__break] = SHIFT(428),
        [ts_sym__for] = SHIFT(430),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(437),
        [ts_sym__switch] = SHIFT(444),
        [ts_sym__var] = SHIFT(452),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(456),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [436] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    [437] = {
        [ts_aux_sym_token2] = SHIFT(438),
    },
    [438] = {
        [ts_sym_expression] = SHIFT(439),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(460),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [439] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(440),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [440] = {
        [ts_sym_statement] = SHIFT(441),
        [ts_sym_statement_block] = SHIFT(424),
        [ts_sym_for_statement] = SHIFT(424),
        [ts_sym_if_statement] = SHIFT(424),
        [ts_sym_switch_statement] = SHIFT(424),
        [ts_sym_break_statement] = SHIFT(424),
        [ts_sym_var_declaration] = SHIFT(424),
        [ts_sym_expression_statement] = SHIFT(424),
        [ts_sym_expression] = SHIFT(425),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(427),
        [ts_sym__break] = SHIFT(428),
        [ts_sym__for] = SHIFT(430),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(437),
        [ts_sym__switch] = SHIFT(444),
        [ts_sym__var] = SHIFT(452),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(456),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [441] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(442),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    [442] = {
        [ts_sym_statement] = SHIFT(443),
        [ts_sym_statement_block] = SHIFT(424),
        [ts_sym_for_statement] = SHIFT(424),
        [ts_sym_if_statement] = SHIFT(424),
        [ts_sym_switch_statement] = SHIFT(424),
        [ts_sym_break_statement] = SHIFT(424),
        [ts_sym_var_declaration] = SHIFT(424),
        [ts_sym_expression_statement] = SHIFT(424),
        [ts_sym_expression] = SHIFT(425),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(427),
        [ts_sym__break] = SHIFT(428),
        [ts_sym__for] = SHIFT(430),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(437),
        [ts_sym__switch] = SHIFT(444),
        [ts_sym__var] = SHIFT(452),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(456),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [443] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    [444] = {
        [ts_aux_sym_token2] = SHIFT(445),
    },
    [445] = {
        [ts_sym_expression] = SHIFT(446),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(451),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [446] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(447),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [447] = {
        [ts_aux_sym_token0] = SHIFT(448),
    },
    [448] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(449),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [449] = {
        [ts_aux_sym_token1] = SHIFT(450),
    },
    [450] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
    },
    [451] = {
        [ts_aux_sym_token3] = SHIFT(447),
    },
    [452] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(453),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(455),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [453] = {
        [ts_sym__terminator] = SHIFT(454),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [454] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [455] = {
        [ts_sym__terminator] = SHIFT(454),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [456] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(457),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(265),
        [ts_sym_identifier] = SHIFT(302),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(459),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = SHIFT(304),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [457] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(458),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [458] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [459] = {
        [ts_aux_sym_token1] = SHIFT(458),
    },
    [460] = {
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [461] = {
        [ts_aux_sym_token3] = SHIFT(435),
    },
    [462] = {
        [ts_sym__terminator] = SHIFT(463),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [463] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [464] = {
        [ts_sym__terminator] = SHIFT(463),
    },
    [465] = {
        [ts_builtin_sym_error] = SHIFT(466),
        [ts_sym_string] = SHIFT(467),
        [ts_sym_identifier] = SHIFT(467),
        [ts_aux_sym_token1] = SHIFT(304),
    },
    [466] = {
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [467] = {
        [ts_aux_sym_token4] = SHIFT(266),
    },
    [468] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(469),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(471),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [469] = {
        [ts_sym__terminator] = SHIFT(470),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [470] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [471] = {
        [ts_sym__terminator] = SHIFT(470),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [472] = {
        [ts_aux_sym_token3] = SHIFT(196),
    },
    [473] = {
        [ts_aux_sym_token3] = SHIFT(191),
    },
    [474] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [475] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
    },
    [476] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [477] = {
        [ts_aux_sym_token1] = SHIFT(478),
    },
    [478] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
    },
    [479] = {
        [ts_aux_sym_token3] = SHIFT(173),
    },
    [480] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    [481] = {
        [ts_sym__terminator] = SHIFT(482),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [482] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [483] = {
        [ts_sym__terminator] = SHIFT(482),
    },
    [484] = {
        [ts_sym__terminator] = SHIFT(485),
    },
    [485] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
    },
    [486] = {
        [ts_aux_sym_token2] = SHIFT(487),
    },
    [487] = {
        [ts_sym_var_declaration] = SHIFT(488),
        [ts_sym_expression_statement] = SHIFT(488),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__var] = SHIFT(468),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [488] = {
        [ts_sym_expression_statement] = SHIFT(489),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [489] = {
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(517),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [490] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(491),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [491] = {
        [ts_sym_statement] = SHIFT(492),
        [ts_sym_statement_block] = SHIFT(480),
        [ts_sym_for_statement] = SHIFT(480),
        [ts_sym_if_statement] = SHIFT(480),
        [ts_sym_switch_statement] = SHIFT(480),
        [ts_sym_break_statement] = SHIFT(480),
        [ts_sym_var_declaration] = SHIFT(480),
        [ts_sym_expression_statement] = SHIFT(480),
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(483),
        [ts_sym__break] = SHIFT(484),
        [ts_sym__for] = SHIFT(486),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(493),
        [ts_sym__switch] = SHIFT(500),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(512),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [492] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    [493] = {
        [ts_aux_sym_token2] = SHIFT(494),
    },
    [494] = {
        [ts_sym_expression] = SHIFT(495),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(516),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [495] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(496),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [496] = {
        [ts_sym_statement] = SHIFT(497),
        [ts_sym_statement_block] = SHIFT(480),
        [ts_sym_for_statement] = SHIFT(480),
        [ts_sym_if_statement] = SHIFT(480),
        [ts_sym_switch_statement] = SHIFT(480),
        [ts_sym_break_statement] = SHIFT(480),
        [ts_sym_var_declaration] = SHIFT(480),
        [ts_sym_expression_statement] = SHIFT(480),
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(483),
        [ts_sym__break] = SHIFT(484),
        [ts_sym__for] = SHIFT(486),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(493),
        [ts_sym__switch] = SHIFT(500),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(512),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [497] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(498),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    [498] = {
        [ts_sym_statement] = SHIFT(499),
        [ts_sym_statement_block] = SHIFT(480),
        [ts_sym_for_statement] = SHIFT(480),
        [ts_sym_if_statement] = SHIFT(480),
        [ts_sym_switch_statement] = SHIFT(480),
        [ts_sym_break_statement] = SHIFT(480),
        [ts_sym_var_declaration] = SHIFT(480),
        [ts_sym_expression_statement] = SHIFT(480),
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(483),
        [ts_sym__break] = SHIFT(484),
        [ts_sym__for] = SHIFT(486),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(493),
        [ts_sym__switch] = SHIFT(500),
        [ts_sym__var] = SHIFT(508),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(512),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [499] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    [500] = {
        [ts_aux_sym_token2] = SHIFT(501),
    },
    [501] = {
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(507),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [502] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(503),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [503] = {
        [ts_aux_sym_token0] = SHIFT(504),
    },
    [504] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(505),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [505] = {
        [ts_aux_sym_token1] = SHIFT(506),
    },
    [506] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
    },
    [507] = {
        [ts_aux_sym_token3] = SHIFT(503),
    },
    [508] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(509),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(511),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [509] = {
        [ts_sym__terminator] = SHIFT(510),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [510] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [511] = {
        [ts_sym__terminator] = SHIFT(510),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [512] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(513),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(265),
        [ts_sym_identifier] = SHIFT(302),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(515),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = SHIFT(304),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [513] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(514),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [514] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [515] = {
        [ts_aux_sym_token1] = SHIFT(514),
    },
    [516] = {
        [ts_aux_sym_token3] = SHIFT(496),
    },
    [517] = {
        [ts_aux_sym_token3] = SHIFT(491),
    },
    [518] = {
        [ts_aux_sym_token3] = SHIFT(165),
    },
    [519] = {
        [ts_aux_sym_token1] = SHIFT(161),
    },
    [520] = {
        [ts_sym_formal_parameters] = SHIFT(521),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [521] = {
        [ts_sym_statement_block] = SHIFT(522),
        [ts_aux_sym_token0] = SHIFT(159),
    },
    [522] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
    },
    [523] = {
        [ts_aux_sym_array_repeat0] = SHIFT(150),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [524] = {
        [ts_aux_sym_array_repeat0] = SHIFT(146),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [525] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
    },
    [526] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
    },
    [527] = {
        [ts_aux_sym_array_repeat0] = SHIFT(110),
        [ts_aux_sym_token7] = SHIFT(148),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [528] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [529] = {
        [ts_aux_sym_token4] = SHIFT(530),
    },
    [530] = {
        [ts_sym_expression] = SHIFT(531),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(248),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(253),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(270),
        [ts_aux_sym_token9] = SHIFT(279),
    },
    [531] = {
        [ts_aux_sym_object_repeat0] = SHIFT(532),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(96),
        [ts_aux_sym_token8] = SHIFT(139),
        [ts_aux_sym_token9] = SHIFT(141),
    },
    [532] = {
        [ts_aux_sym_token1] = SHIFT(533),
    },
    [533] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [534] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [535] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [536] = {
        [ts_sym_statement] = SHIFT(537),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(169),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [537] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    [538] = {
        [ts_aux_sym_token3] = SHIFT(536),
    },
    [539] = {
        [ts_aux_sym_token1] = SHIFT(80),
    },
    [540] = {
        [ts_sym_formal_parameters] = SHIFT(541),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [541] = {
        [ts_sym_statement_block] = SHIFT(542),
        [ts_aux_sym_token0] = SHIFT(78),
    },
    [542] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [543] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(544),
    },
    [544] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
    },
    [545] = {
        [ts_aux_sym_token1] = SHIFT(544),
    },
    [546] = {
        [ts_sym_formal_parameters] = SHIFT(547),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [547] = {
        [ts_sym_statement_block] = SHIFT(548),
        [ts_aux_sym_token0] = SHIFT(69),
    },
    [548] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
    },
    [549] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [550] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [551] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_token1] = SHIFT(552),
    },
    [552] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [553] = {
        [ts_aux_sym_token1] = SHIFT(552),
    },
    [554] = {
        [ts_sym_formal_parameters] = SHIFT(555),
        [ts_aux_sym_token2] = SHIFT(314),
    },
    [555] = {
        [ts_sym_statement_block] = SHIFT(556),
        [ts_aux_sym_token0] = SHIFT(39),
    },
    [556] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [557] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
    },
    [558] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [559] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [560] = {
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_ternary] = SHIFT(31),
        [ts_sym_assignment] = SHIFT(31),
        [ts_sym_function_expression] = SHIFT(31),
        [ts_sym_function_call] = SHIFT(31),
        [ts_sym_property_access] = SHIFT(32),
        [ts_sym_literal] = SHIFT(31),
        [ts_sym_object] = SHIFT(35),
        [ts_sym_array] = SHIFT(35),
        [ts_sym__function] = SHIFT(36),
        [ts_sym_null] = SHIFT(35),
        [ts_sym_true] = SHIFT(35),
        [ts_sym_false] = SHIFT(35),
        [ts_sym_string] = SHIFT(35),
        [ts_sym_identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(35),
        [ts_aux_sym_token0] = SHIFT(92),
        [ts_aux_sym_token9] = SHIFT(108),
    },
    [561] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token7] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token8] = SHIFT(23),
        [ts_aux_sym_token9] = SHIFT(25),
    },
    [562] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [563] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [564] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [565] = {
        [ts_sym__terminator] = SHIFT(566),
    },
    [566] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
    },
    [567] = {
        [ts_aux_sym_token2] = SHIFT(568),
    },
    [568] = {
        [ts_sym_var_declaration] = SHIFT(569),
        [ts_sym_expression_statement] = SHIFT(569),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__var] = SHIFT(468),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [569] = {
        [ts_sym_expression_statement] = SHIFT(570),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [570] = {
        [ts_sym_expression] = SHIFT(571),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(636),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [571] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(572),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [572] = {
        [ts_sym_statement] = SHIFT(573),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(564),
        [ts_sym__break] = SHIFT(565),
        [ts_sym__for] = SHIFT(567),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(574),
        [ts_sym__switch] = SHIFT(581),
        [ts_sym__var] = SHIFT(589),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(593),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [573] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    [574] = {
        [ts_aux_sym_token2] = SHIFT(575),
    },
    [575] = {
        [ts_sym_expression] = SHIFT(576),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(635),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [576] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(577),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [577] = {
        [ts_sym_statement] = SHIFT(578),
        [ts_sym_statement_block] = SHIFT(597),
        [ts_sym_for_statement] = SHIFT(597),
        [ts_sym_if_statement] = SHIFT(597),
        [ts_sym_switch_statement] = SHIFT(597),
        [ts_sym_break_statement] = SHIFT(597),
        [ts_sym_var_declaration] = SHIFT(597),
        [ts_sym_expression_statement] = SHIFT(597),
        [ts_sym_expression] = SHIFT(598),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(600),
        [ts_sym__break] = SHIFT(601),
        [ts_sym__for] = SHIFT(603),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(610),
        [ts_sym__switch] = SHIFT(617),
        [ts_sym__var] = SHIFT(625),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(629),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [578] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(579),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    [579] = {
        [ts_sym_statement] = SHIFT(580),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(564),
        [ts_sym__break] = SHIFT(565),
        [ts_sym__for] = SHIFT(567),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(574),
        [ts_sym__switch] = SHIFT(581),
        [ts_sym__var] = SHIFT(589),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(593),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [580] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    [581] = {
        [ts_aux_sym_token2] = SHIFT(582),
    },
    [582] = {
        [ts_sym_expression] = SHIFT(583),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(588),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [583] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(584),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [584] = {
        [ts_aux_sym_token0] = SHIFT(585),
    },
    [585] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(586),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [586] = {
        [ts_aux_sym_token1] = SHIFT(587),
    },
    [587] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
    },
    [588] = {
        [ts_aux_sym_token3] = SHIFT(584),
    },
    [589] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(590),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(592),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [590] = {
        [ts_sym__terminator] = SHIFT(591),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [591] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [592] = {
        [ts_sym__terminator] = SHIFT(591),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [593] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(594),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(265),
        [ts_sym_identifier] = SHIFT(302),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(596),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = SHIFT(304),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [594] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(595),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [595] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [596] = {
        [ts_aux_sym_token1] = SHIFT(595),
    },
    [597] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
    },
    [598] = {
        [ts_sym__terminator] = SHIFT(599),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(44),
        [ts_aux_sym_token8] = SHIFT(48),
        [ts_aux_sym_token9] = SHIFT(50),
    },
    [599] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
    },
    [600] = {
        [ts_sym__terminator] = SHIFT(599),
    },
    [601] = {
        [ts_sym__terminator] = SHIFT(602),
    },
    [602] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
    },
    [603] = {
        [ts_aux_sym_token2] = SHIFT(604),
    },
    [604] = {
        [ts_sym_var_declaration] = SHIFT(605),
        [ts_sym_expression_statement] = SHIFT(605),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__var] = SHIFT(468),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [605] = {
        [ts_sym_expression_statement] = SHIFT(606),
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(464),
        [ts_sym__function] = SHIFT(75),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(465),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [606] = {
        [ts_sym_expression] = SHIFT(607),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(634),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [607] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(608),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [608] = {
        [ts_sym_statement] = SHIFT(609),
        [ts_sym_statement_block] = SHIFT(597),
        [ts_sym_for_statement] = SHIFT(597),
        [ts_sym_if_statement] = SHIFT(597),
        [ts_sym_switch_statement] = SHIFT(597),
        [ts_sym_break_statement] = SHIFT(597),
        [ts_sym_var_declaration] = SHIFT(597),
        [ts_sym_expression_statement] = SHIFT(597),
        [ts_sym_expression] = SHIFT(598),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(600),
        [ts_sym__break] = SHIFT(601),
        [ts_sym__for] = SHIFT(603),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(610),
        [ts_sym__switch] = SHIFT(617),
        [ts_sym__var] = SHIFT(625),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(629),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [609] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
    },
    [610] = {
        [ts_aux_sym_token2] = SHIFT(611),
    },
    [611] = {
        [ts_sym_expression] = SHIFT(612),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(633),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [612] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(613),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [613] = {
        [ts_sym_statement] = SHIFT(614),
        [ts_sym_statement_block] = SHIFT(597),
        [ts_sym_for_statement] = SHIFT(597),
        [ts_sym_if_statement] = SHIFT(597),
        [ts_sym_switch_statement] = SHIFT(597),
        [ts_sym_break_statement] = SHIFT(597),
        [ts_sym_var_declaration] = SHIFT(597),
        [ts_sym_expression_statement] = SHIFT(597),
        [ts_sym_expression] = SHIFT(598),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(600),
        [ts_sym__break] = SHIFT(601),
        [ts_sym__for] = SHIFT(603),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(610),
        [ts_sym__switch] = SHIFT(617),
        [ts_sym__var] = SHIFT(625),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(629),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [614] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(615),
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
    },
    [615] = {
        [ts_sym_statement] = SHIFT(616),
        [ts_sym_statement_block] = SHIFT(597),
        [ts_sym_for_statement] = SHIFT(597),
        [ts_sym_if_statement] = SHIFT(597),
        [ts_sym_switch_statement] = SHIFT(597),
        [ts_sym_break_statement] = SHIFT(597),
        [ts_sym_var_declaration] = SHIFT(597),
        [ts_sym_expression_statement] = SHIFT(597),
        [ts_sym_expression] = SHIFT(598),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(600),
        [ts_sym__break] = SHIFT(601),
        [ts_sym__for] = SHIFT(603),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(610),
        [ts_sym__switch] = SHIFT(617),
        [ts_sym__var] = SHIFT(625),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(71),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_token0] = SHIFT(629),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [616] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
    },
    [617] = {
        [ts_aux_sym_token2] = SHIFT(618),
    },
    [618] = {
        [ts_sym_expression] = SHIFT(619),
        [ts_sym_ternary] = SHIFT(392),
        [ts_sym_assignment] = SHIFT(392),
        [ts_sym_function_expression] = SHIFT(392),
        [ts_sym_function_call] = SHIFT(392),
        [ts_sym_property_access] = SHIFT(393),
        [ts_sym_literal] = SHIFT(392),
        [ts_sym_object] = SHIFT(396),
        [ts_sym_array] = SHIFT(396),
        [ts_builtin_sym_error] = SHIFT(624),
        [ts_sym__function] = SHIFT(397),
        [ts_sym_null] = SHIFT(396),
        [ts_sym_true] = SHIFT(396),
        [ts_sym_false] = SHIFT(396),
        [ts_sym_string] = SHIFT(396),
        [ts_sym_identifier] = SHIFT(393),
        [ts_sym_number] = SHIFT(396),
        [ts_aux_sym_token0] = SHIFT(407),
        [ts_aux_sym_token9] = SHIFT(417),
    },
    [619] = {
        [ts_aux_sym_token2] = SHIFT(88),
        [ts_aux_sym_token3] = SHIFT(620),
        [ts_aux_sym_token5] = SHIFT(383),
        [ts_aux_sym_token8] = SHIFT(387),
        [ts_aux_sym_token9] = SHIFT(389),
    },
    [620] = {
        [ts_aux_sym_token0] = SHIFT(621),
    },
    [621] = {
        [ts_sym_switch_case] = SHIFT(175),
        [ts_sym__case] = SHIFT(176),
        [ts_sym__default] = SHIFT(205),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(622),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [622] = {
        [ts_aux_sym_token1] = SHIFT(623),
    },
    [623] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
    },
    [624] = {
        [ts_aux_sym_token3] = SHIFT(620),
    },
    [625] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(626),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(237),
        [ts_sym_literal] = SHIFT(223),
        [ts_sym_object] = SHIFT(227),
        [ts_sym_array] = SHIFT(227),
        [ts_sym__function] = SHIFT(228),
        [ts_sym_null] = SHIFT(227),
        [ts_sym_true] = SHIFT(227),
        [ts_sym_false] = SHIFT(227),
        [ts_sym_string] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(628),
        [ts_sym_number] = SHIFT(227),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [626] = {
        [ts_sym__terminator] = SHIFT(627),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [627] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
    },
    [628] = {
        [ts_sym__terminator] = SHIFT(627),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [629] = {
        [ts_sym_statement] = SHIFT(40),
        [ts_sym_statement_block] = SHIFT(41),
        [ts_sym_for_statement] = SHIFT(41),
        [ts_sym_if_statement] = SHIFT(41),
        [ts_sym_switch_statement] = SHIFT(41),
        [ts_sym_break_statement] = SHIFT(41),
        [ts_sym_var_declaration] = SHIFT(41),
        [ts_sym_expression_statement] = SHIFT(41),
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_ternary] = SHIFT(70),
        [ts_sym_assignment] = SHIFT(70),
        [ts_sym_function_expression] = SHIFT(70),
        [ts_sym_function_call] = SHIFT(70),
        [ts_sym_property_access] = SHIFT(71),
        [ts_sym_literal] = SHIFT(70),
        [ts_sym_object] = SHIFT(74),
        [ts_sym_array] = SHIFT(74),
        [ts_builtin_sym_error] = SHIFT(630),
        [ts_sym__break] = SHIFT(81),
        [ts_sym__for] = SHIFT(83),
        [ts_sym__function] = SHIFT(75),
        [ts_sym__if] = SHIFT(162),
        [ts_sym__switch] = SHIFT(170),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(74),
        [ts_sym_true] = SHIFT(74),
        [ts_sym_false] = SHIFT(74),
        [ts_sym_string] = SHIFT(265),
        [ts_sym_identifier] = SHIFT(302),
        [ts_sym_number] = SHIFT(74),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(632),
        [ts_aux_sym_token0] = SHIFT(260),
        [ts_aux_sym_token1] = SHIFT(304),
        [ts_aux_sym_token9] = SHIFT(305),
    },
    [630] = {
        [ts_sym__terminator] = SHIFT(43),
        [ts_aux_sym_object_repeat0] = SHIFT(262),
        [ts_aux_sym_token1] = SHIFT(631),
        [ts_aux_sym_token7] = SHIFT(96),
    },
    [631] = {
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
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [632] = {
        [ts_aux_sym_token1] = SHIFT(631),
    },
    [633] = {
        [ts_aux_sym_token3] = SHIFT(613),
    },
    [634] = {
        [ts_aux_sym_token3] = SHIFT(608),
    },
    [635] = {
        [ts_aux_sym_token3] = SHIFT(577),
    },
    [636] = {
        [ts_aux_sym_token3] = SHIFT(572),
    },
    [637] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [638] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
