#include "tree_sitter/parser.h"

#define STATE_COUNT 604
#define SYMBOL_COUNT 55

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
    ts_sym_assignment = 13,
    ts_sym_function_expression = 14,
    ts_sym_function_call = 15,
    ts_sym_property_access = 16,
    ts_sym_formal_parameters = 17,
    ts_sym_literal = 18,
    ts_sym_object = 19,
    ts_sym_array = 20,
    ts_sym__break = 21,
    ts_sym__case = 22,
    ts_sym__default = 23,
    ts_sym__else = 24,
    ts_sym__for = 25,
    ts_sym__function = 26,
    ts_sym__if = 27,
    ts_sym__switch = 28,
    ts_sym__var = 29,
    ts_sym_null = 30,
    ts_sym_true = 31,
    ts_sym_false = 32,
    ts_sym__terminator = 33,
    ts_sym_string = 34,
    ts_sym_identifier = 35,
    ts_sym_number = 36,
    ts_aux_sym_program_repeat0 = 37,
    ts_aux_sym_statement_block_repeat0 = 38,
    ts_aux_sym_switch_statement_repeat0 = 39,
    ts_aux_sym_switch_case_repeat0 = 40,
    ts_aux_sym_function_call_repeat0 = 41,
    ts_aux_sym_formal_parameters_repeat0 = 42,
    ts_aux_sym_object_repeat0 = 43,
    ts_aux_sym_array_repeat0 = 44,
    ts_aux_sym_token0 = 45,
    ts_aux_sym_token1 = 46,
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
    [ts_aux_sym_token5] = "'='",
    [ts_aux_sym_token6] = "','",
    [ts_aux_sym_token7] = "'.'",
    [ts_aux_sym_token8] = "'['",
    [ts_aux_sym_token9] = "']'",
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
            ACCEPT_TOKEN(ts_aux_sym_token8);
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
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 56:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 57:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(57);
            if (lookahead == ')')
                ADVANCE(58);
            LEX_ERROR();
        case 58:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 59:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(59);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 60:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 61:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(61);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 63:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 64:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 66:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
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
                ADVANCE(67);
            LEX_ERROR();
        case 67:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 68:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '\n')
                ADVANCE(69);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '\n')
                ADVANCE(69);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 70:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 71:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '\n')
                ADVANCE(72);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '\n')
                ADVANCE(72);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 73:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '\n')
                ADVANCE(74);
            if (lookahead == ';')
                ADVANCE(56);
            LEX_ERROR();
        case 74:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '\n')
                ADVANCE(74);
            if (lookahead == ';')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 75:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(58);
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
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 82:
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
        case 83:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 84:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 85:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 86:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 87:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
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
                ADVANCE(88);
            if (lookahead == 'd')
                ADVANCE(92);
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
                ADVANCE(67);
            LEX_ERROR();
        case 88:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(89);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 89:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(90);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 90:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 91:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__case);
        case 92:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 93:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'f')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 94:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'a')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 95:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'u')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 96:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 97:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 't')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 98:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__default);
        case 99:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
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
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
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
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '\n')
                ADVANCE(103);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '\n')
                ADVANCE(103);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 104:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 105:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == ':')
                ADVANCE(86);
            LEX_ERROR();
        case 106:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(106);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 107:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
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
                ADVANCE(65);
            if (lookahead == 'f')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(44);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '\n')
                ADVANCE(109);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '\n')
                ADVANCE(109);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '\n')
                ADVANCE(111);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '\n')
                ADVANCE(111);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 112:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == '{')
                ADVANCE(51);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(60);
            LEX_ERROR();
        case 114:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == ')')
                ADVANCE(58);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '(')
                ADVANCE(54);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(54);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == 'c')
                ADVANCE(118);
            if (lookahead == 'd')
                ADVANCE(122);
            if (lookahead == '}')
                ADVANCE(67);
            LEX_ERROR();
        case 118:
            if (lookahead == 'a')
                ADVANCE(119);
            LEX_ERROR();
        case 119:
            if (lookahead == 's')
                ADVANCE(120);
            LEX_ERROR();
        case 120:
            if (lookahead == 'e')
                ADVANCE(121);
            LEX_ERROR();
        case 121:
            ACCEPT_TOKEN(ts_sym__case);
        case 122:
            if (lookahead == 'e')
                ADVANCE(123);
            LEX_ERROR();
        case 123:
            if (lookahead == 'f')
                ADVANCE(124);
            LEX_ERROR();
        case 124:
            if (lookahead == 'a')
                ADVANCE(125);
            LEX_ERROR();
        case 125:
            if (lookahead == 'u')
                ADVANCE(126);
            LEX_ERROR();
        case 126:
            if (lookahead == 'l')
                ADVANCE(127);
            LEX_ERROR();
        case 127:
            if (lookahead == 't')
                ADVANCE(128);
            LEX_ERROR();
        case 128:
            ACCEPT_TOKEN(ts_sym__default);
        case 129:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
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
        case 131:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
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
                ADVANCE(88);
            if (lookahead == 'd')
                ADVANCE(92);
            if (lookahead == 'e')
                ADVANCE(132);
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
                ADVANCE(67);
            LEX_ERROR();
        case 132:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'l')
                ADVANCE(133);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 133:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 's')
                ADVANCE(134);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 134:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == 'e')
                ADVANCE(135);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 135:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym__else);
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
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            if (lookahead == '[')
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(82);
            if (lookahead == 'n')
                ADVANCE(34);
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
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == '.')
                ADVANCE(55);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(62);
            if (lookahead == '[')
                ADVANCE(12);
            LEX_ERROR();
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
                ADVANCE(132);
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
                ADVANCE(67);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(11);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
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
                ADVANCE(132);
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
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
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
                ADVANCE(65);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(88);
            if (lookahead == 'd')
                ADVANCE(92);
            if (lookahead == 'e')
                ADVANCE(132);
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
                ADVANCE(67);
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
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
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
                ADVANCE(65);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(88);
            if (lookahead == 'd')
                ADVANCE(92);
            if (lookahead == 'e')
                ADVANCE(132);
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
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__terminator);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(54);
            if (lookahead == ')')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '.')
                ADVANCE(55);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            if (lookahead == ':')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(56);
            if (lookahead == '=')
                ADVANCE(62);
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
                ADVANCE(65);
            if (lookahead == 'b')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(88);
            if (lookahead == 'd')
                ADVANCE(92);
            if (lookahead == 'e')
                ADVANCE(132);
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
                ADVANCE(67);
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
    [6] = 81,
    [7] = 59,
    [8] = 57,
    [9] = 52,
    [10] = 81,
    [11] = 59,
    [12] = 57,
    [13] = 59,
    [14] = 101,
    [15] = 59,
    [16] = 57,
    [17] = 63,
    [18] = 61,
    [19] = 101,
    [20] = 64,
    [21] = 81,
    [22] = 59,
    [23] = 57,
    [24] = 64,
    [25] = 59,
    [26] = 61,
    [27] = 101,
    [28] = 59,
    [29] = 59,
    [30] = 116,
    [31] = 112,
    [32] = 59,
    [33] = 66,
    [34] = 66,
    [35] = 66,
    [36] = 52,
    [37] = 66,
    [38] = 63,
    [39] = 68,
    [40] = 101,
    [41] = 64,
    [42] = 63,
    [43] = 70,
    [44] = 101,
    [45] = 64,
    [46] = 70,
    [47] = 64,
    [48] = 70,
    [49] = 101,
    [50] = 64,
    [51] = 64,
    [52] = 116,
    [53] = 112,
    [54] = 64,
    [55] = 66,
    [56] = 52,
    [57] = 68,
    [58] = 101,
    [59] = 52,
    [60] = 52,
    [61] = 116,
    [62] = 112,
    [63] = 52,
    [64] = 66,
    [65] = 71,
    [66] = 52,
    [67] = 73,
    [68] = 66,
    [69] = 115,
    [70] = 136,
    [71] = 101,
    [72] = 101,
    [73] = 75,
    [74] = 81,
    [75] = 59,
    [76] = 57,
    [77] = 75,
    [78] = 106,
    [79] = 77,
    [80] = 76,
    [81] = 59,
    [82] = 139,
    [83] = 77,
    [84] = 76,
    [85] = 105,
    [86] = 101,
    [87] = 78,
    [88] = 76,
    [89] = 81,
    [90] = 59,
    [91] = 57,
    [92] = 78,
    [93] = 78,
    [94] = 107,
    [95] = 80,
    [96] = 79,
    [97] = 59,
    [98] = 81,
    [99] = 59,
    [100] = 57,
    [101] = 80,
    [102] = 80,
    [103] = 101,
    [104] = 80,
    [105] = 79,
    [106] = 63,
    [107] = 83,
    [108] = 101,
    [109] = 64,
    [110] = 83,
    [111] = 106,
    [112] = 77,
    [113] = 76,
    [114] = 64,
    [115] = 105,
    [116] = 101,
    [117] = 78,
    [118] = 76,
    [119] = 64,
    [120] = 63,
    [121] = 84,
    [122] = 101,
    [123] = 64,
    [124] = 84,
    [125] = 107,
    [126] = 80,
    [127] = 79,
    [128] = 64,
    [129] = 80,
    [130] = 83,
    [131] = 101,
    [132] = 80,
    [133] = 80,
    [134] = 116,
    [135] = 112,
    [136] = 80,
    [137] = 66,
    [138] = 71,
    [139] = 80,
    [140] = 115,
    [141] = 101,
    [142] = 75,
    [143] = 130,
    [144] = 138,
    [145] = 130,
    [146] = 66,
    [147] = 73,
    [148] = 115,
    [149] = 101,
    [150] = 75,
    [151] = 112,
    [152] = 117,
    [153] = 117,
    [154] = 101,
    [155] = 85,
    [156] = 81,
    [157] = 59,
    [158] = 57,
    [159] = 85,
    [160] = 85,
    [161] = 87,
    [162] = 87,
    [163] = 87,
    [164] = 52,
    [165] = 87,
    [166] = 73,
    [167] = 73,
    [168] = 87,
    [169] = 115,
    [170] = 136,
    [171] = 101,
    [172] = 101,
    [173] = 75,
    [174] = 130,
    [175] = 87,
    [176] = 115,
    [177] = 101,
    [178] = 75,
    [179] = 130,
    [180] = 131,
    [181] = 130,
    [182] = 87,
    [183] = 115,
    [184] = 101,
    [185] = 75,
    [186] = 112,
    [187] = 117,
    [188] = 105,
    [189] = 87,
    [190] = 101,
    [191] = 99,
    [192] = 81,
    [193] = 59,
    [194] = 57,
    [195] = 99,
    [196] = 99,
    [197] = 63,
    [198] = 100,
    [199] = 101,
    [200] = 64,
    [201] = 100,
    [202] = 52,
    [203] = 87,
    [204] = 99,
    [205] = 100,
    [206] = 99,
    [207] = 116,
    [208] = 112,
    [209] = 99,
    [210] = 66,
    [211] = 71,
    [212] = 99,
    [213] = 101,
    [214] = 52,
    [215] = 66,
    [216] = 68,
    [217] = 106,
    [218] = 77,
    [219] = 76,
    [220] = 99,
    [221] = 105,
    [222] = 101,
    [223] = 78,
    [224] = 76,
    [225] = 99,
    [226] = 78,
    [227] = 84,
    [228] = 101,
    [229] = 78,
    [230] = 78,
    [231] = 116,
    [232] = 112,
    [233] = 78,
    [234] = 66,
    [235] = 71,
    [236] = 78,
    [237] = 76,
    [238] = 66,
    [239] = 102,
    [240] = 76,
    [241] = 52,
    [242] = 66,
    [243] = 108,
    [244] = 101,
    [245] = 78,
    [246] = 76,
    [247] = 52,
    [248] = 106,
    [249] = 77,
    [250] = 76,
    [251] = 78,
    [252] = 105,
    [253] = 101,
    [254] = 78,
    [255] = 76,
    [256] = 78,
    [257] = 107,
    [258] = 80,
    [259] = 79,
    [260] = 78,
    [261] = 104,
    [262] = 106,
    [263] = 77,
    [264] = 76,
    [265] = 80,
    [266] = 105,
    [267] = 101,
    [268] = 78,
    [269] = 76,
    [270] = 80,
    [271] = 80,
    [272] = 107,
    [273] = 80,
    [274] = 79,
    [275] = 80,
    [276] = 104,
    [277] = 80,
    [278] = 78,
    [279] = 78,
    [280] = 110,
    [281] = 76,
    [282] = 52,
    [283] = 107,
    [284] = 80,
    [285] = 79,
    [286] = 52,
    [287] = 104,
    [288] = 52,
    [289] = 115,
    [290] = 112,
    [291] = 78,
    [292] = 114,
    [293] = 113,
    [294] = 57,
    [295] = 112,
    [296] = 63,
    [297] = 113,
    [298] = 57,
    [299] = 112,
    [300] = 99,
    [301] = 107,
    [302] = 80,
    [303] = 79,
    [304] = 99,
    [305] = 104,
    [306] = 99,
    [307] = 76,
    [308] = 115,
    [309] = 112,
    [310] = 99,
    [311] = 68,
    [312] = 117,
    [313] = 66,
    [314] = 102,
    [315] = 87,
    [316] = 76,
    [317] = 76,
    [318] = 87,
    [319] = 63,
    [320] = 129,
    [321] = 101,
    [322] = 64,
    [323] = 129,
    [324] = 75,
    [325] = 129,
    [326] = 101,
    [327] = 75,
    [328] = 75,
    [329] = 116,
    [330] = 112,
    [331] = 75,
    [332] = 66,
    [333] = 71,
    [334] = 75,
    [335] = 76,
    [336] = 115,
    [337] = 112,
    [338] = 75,
    [339] = 106,
    [340] = 77,
    [341] = 76,
    [342] = 75,
    [343] = 105,
    [344] = 101,
    [345] = 78,
    [346] = 76,
    [347] = 75,
    [348] = 75,
    [349] = 107,
    [350] = 80,
    [351] = 79,
    [352] = 75,
    [353] = 104,
    [354] = 75,
    [355] = 57,
    [356] = 131,
    [357] = 52,
    [358] = 131,
    [359] = 73,
    [360] = 73,
    [361] = 131,
    [362] = 115,
    [363] = 136,
    [364] = 101,
    [365] = 101,
    [366] = 75,
    [367] = 130,
    [368] = 131,
    [369] = 115,
    [370] = 101,
    [371] = 75,
    [372] = 130,
    [373] = 131,
    [374] = 130,
    [375] = 131,
    [376] = 115,
    [377] = 101,
    [378] = 75,
    [379] = 112,
    [380] = 117,
    [381] = 76,
    [382] = 131,
    [383] = 57,
    [384] = 101,
    [385] = 52,
    [386] = 131,
    [387] = 68,
    [388] = 66,
    [389] = 102,
    [390] = 131,
    [391] = 76,
    [392] = 57,
    [393] = 57,
    [394] = 52,
    [395] = 101,
    [396] = 73,
    [397] = 106,
    [398] = 77,
    [399] = 105,
    [400] = 101,
    [401] = 52,
    [402] = 101,
    [403] = 68,
    [404] = 57,
    [405] = 57,
    [406] = 117,
    [407] = 117,
    [408] = 63,
    [409] = 137,
    [410] = 101,
    [411] = 64,
    [412] = 137,
    [413] = 85,
    [414] = 137,
    [415] = 101,
    [416] = 85,
    [417] = 85,
    [418] = 116,
    [419] = 112,
    [420] = 85,
    [421] = 66,
    [422] = 71,
    [423] = 85,
    [424] = 76,
    [425] = 115,
    [426] = 112,
    [427] = 85,
    [428] = 106,
    [429] = 77,
    [430] = 76,
    [431] = 85,
    [432] = 105,
    [433] = 101,
    [434] = 78,
    [435] = 76,
    [436] = 85,
    [437] = 85,
    [438] = 107,
    [439] = 80,
    [440] = 79,
    [441] = 85,
    [442] = 104,
    [443] = 85,
    [444] = 76,
    [445] = 76,
    [446] = 66,
    [447] = 57,
    [448] = 138,
    [449] = 52,
    [450] = 138,
    [451] = 73,
    [452] = 73,
    [453] = 138,
    [454] = 115,
    [455] = 136,
    [456] = 101,
    [457] = 101,
    [458] = 75,
    [459] = 130,
    [460] = 138,
    [461] = 115,
    [462] = 101,
    [463] = 75,
    [464] = 130,
    [465] = 138,
    [466] = 130,
    [467] = 138,
    [468] = 115,
    [469] = 101,
    [470] = 75,
    [471] = 112,
    [472] = 117,
    [473] = 76,
    [474] = 138,
    [475] = 57,
    [476] = 101,
    [477] = 52,
    [478] = 138,
    [479] = 68,
    [480] = 66,
    [481] = 102,
    [482] = 138,
    [483] = 76,
    [484] = 57,
    [485] = 57,
    [486] = 57,
    [487] = 76,
    [488] = 115,
    [489] = 112,
    [490] = 80,
    [491] = 104,
    [492] = 64,
    [493] = 64,
    [494] = 104,
    [495] = 104,
    [496] = 59,
    [497] = 105,
    [498] = 101,
    [499] = 78,
    [500] = 76,
    [501] = 59,
    [502] = 59,
    [503] = 75,
    [504] = 130,
    [505] = 66,
    [506] = 57,
    [507] = 76,
    [508] = 115,
    [509] = 112,
    [510] = 52,
    [511] = 71,
    [512] = 64,
    [513] = 76,
    [514] = 115,
    [515] = 112,
    [516] = 64,
    [517] = 68,
    [518] = 76,
    [519] = 71,
    [520] = 59,
    [521] = 76,
    [522] = 115,
    [523] = 112,
    [524] = 59,
    [525] = 64,
    [526] = 61,
    [527] = 59,
    [528] = 52,
    [529] = 73,
    [530] = 73,
    [531] = 2,
    [532] = 115,
    [533] = 136,
    [534] = 101,
    [535] = 101,
    [536] = 75,
    [537] = 130,
    [538] = 2,
    [539] = 115,
    [540] = 101,
    [541] = 75,
    [542] = 130,
    [543] = 140,
    [544] = 130,
    [545] = 2,
    [546] = 115,
    [547] = 101,
    [548] = 75,
    [549] = 112,
    [550] = 117,
    [551] = 76,
    [552] = 2,
    [553] = 57,
    [554] = 101,
    [555] = 52,
    [556] = 2,
    [557] = 68,
    [558] = 66,
    [559] = 102,
    [560] = 2,
    [561] = 76,
    [562] = 140,
    [563] = 52,
    [564] = 140,
    [565] = 73,
    [566] = 73,
    [567] = 140,
    [568] = 115,
    [569] = 136,
    [570] = 101,
    [571] = 101,
    [572] = 75,
    [573] = 130,
    [574] = 140,
    [575] = 115,
    [576] = 101,
    [577] = 75,
    [578] = 130,
    [579] = 140,
    [580] = 130,
    [581] = 140,
    [582] = 115,
    [583] = 101,
    [584] = 75,
    [585] = 112,
    [586] = 117,
    [587] = 76,
    [588] = 140,
    [589] = 57,
    [590] = 101,
    [591] = 52,
    [592] = 140,
    [593] = 68,
    [594] = 66,
    [595] = 102,
    [596] = 140,
    [597] = 76,
    [598] = 57,
    [599] = 57,
    [600] = 57,
    [601] = 57,
    [602] = 0,
    [603] = 0,
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
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(529),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(530),
        [ts_sym__for] = SHIFT(532),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(539),
        [ts_sym__switch] = SHIFT(546),
        [ts_sym__var] = SHIFT(554),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_program_repeat0] = SHIFT(603),
        [ts_aux_sym_token0] = SHIFT(558),
        [ts_aux_sym_token8] = SHIFT(283),
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
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(529),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(530),
        [ts_sym__for] = SHIFT(532),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(539),
        [ts_sym__switch] = SHIFT(546),
        [ts_sym__var] = SHIFT(554),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_program_repeat0] = SHIFT(602),
        [ts_aux_sym_token0] = SHIFT(558),
        [ts_aux_sym_token8] = SHIFT(283),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
    },
    [4] = {
        [ts_sym__terminator] = SHIFT(5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [6] = {
        [ts_sym_expression] = SHIFT(7),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(528),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [7] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [8] = {
        [ts_aux_sym_token3] = SHIFT(9),
    },
    [9] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [10] = {
        [ts_sym_expression] = SHIFT(11),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(527),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [11] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [12] = {
        [ts_aux_sym_token3] = SHIFT(13),
    },
    [13] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [14] = {
        [ts_sym_expression] = SHIFT(15),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [15] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(16),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [16] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 3),
    },
    [17] = {
        [ts_sym_identifier] = SHIFT(18),
    },
    [18] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [19] = {
        [ts_sym_expression] = SHIFT(20),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [20] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(526),
    },
    [21] = {
        [ts_sym_expression] = SHIFT(22),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(525),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [22] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(23),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [23] = {
        [ts_aux_sym_token3] = SHIFT(24),
    },
    [24] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [25] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [26] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(27),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [27] = {
        [ts_sym_expression] = SHIFT(28),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [28] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [29] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [30] = {
        [ts_sym_formal_parameters] = SHIFT(31),
        [ts_sym_identifier] = SHIFT(522),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [31] = {
        [ts_sym_statement_block] = SHIFT(32),
        [ts_aux_sym_token0] = SHIFT(33),
    },
    [32] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [33] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(519),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(521),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [34] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(147),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(518),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [35] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
    },
    [36] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [37] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [38] = {
        [ts_sym_identifier] = SHIFT(39),
    },
    [39] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [40] = {
        [ts_sym_expression] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [41] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(517),
    },
    [42] = {
        [ts_sym_identifier] = SHIFT(43),
    },
    [43] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [44] = {
        [ts_sym_expression] = SHIFT(45),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [45] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(46),
    },
    [46] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [47] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [48] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [49] = {
        [ts_sym_expression] = SHIFT(50),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [50] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = REDUCE(ts_sym_assignment, 3),
    },
    [51] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [52] = {
        [ts_sym_formal_parameters] = SHIFT(53),
        [ts_sym_identifier] = SHIFT(514),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [53] = {
        [ts_sym_statement_block] = SHIFT(54),
        [ts_aux_sym_token0] = SHIFT(55),
    },
    [54] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [55] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(511),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(513),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [56] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [57] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [58] = {
        [ts_sym_expression] = SHIFT(59),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [59] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [60] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [61] = {
        [ts_sym_formal_parameters] = SHIFT(62),
        [ts_sym_identifier] = SHIFT(508),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [62] = {
        [ts_sym_statement_block] = SHIFT(63),
        [ts_aux_sym_token0] = SHIFT(64),
    },
    [63] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [64] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(65),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(507),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [65] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(66),
    },
    [66] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [67] = {
        [ts_sym__terminator] = SHIFT(68),
    },
    [68] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
    },
    [69] = {
        [ts_aux_sym_token2] = SHIFT(70),
    },
    [70] = {
        [ts_sym_var_declaration] = SHIFT(71),
        [ts_sym_expression_statement] = SHIFT(71),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__var] = SHIFT(400),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [71] = {
        [ts_sym_expression_statement] = SHIFT(72),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [72] = {
        [ts_sym_expression] = SHIFT(73),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(506),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [73] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(504),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [74] = {
        [ts_sym_expression] = SHIFT(75),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(503),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [75] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(76),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [76] = {
        [ts_aux_sym_token3] = SHIFT(77),
    },
    [77] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [78] = {
        [ts_builtin_sym_error] = SHIFT(79),
        [ts_sym_string] = SHIFT(497),
        [ts_sym_identifier] = SHIFT(497),
        [ts_aux_sym_token1] = SHIFT(502),
    },
    [79] = {
        [ts_aux_sym_object_repeat0] = SHIFT(80),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [80] = {
        [ts_aux_sym_token1] = SHIFT(81),
    },
    [81] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [82] = {
        [ts_builtin_sym_error] = SHIFT(83),
        [ts_sym_string] = SHIFT(85),
        [ts_sym_identifier] = SHIFT(85),
    },
    [83] = {
        [ts_aux_sym_object_repeat0] = SHIFT(84),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [84] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [85] = {
        [ts_aux_sym_token4] = SHIFT(86),
    },
    [86] = {
        [ts_sym_expression] = SHIFT(87),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [87] = {
        [ts_aux_sym_object_repeat0] = SHIFT(88),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [88] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [89] = {
        [ts_sym_expression] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(93),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [90] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(91),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [91] = {
        [ts_aux_sym_token3] = SHIFT(92),
    },
    [92] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [93] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [94] = {
        [ts_sym_expression] = SHIFT(95),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(495),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(496),
    },
    [95] = {
        [ts_aux_sym_array_repeat0] = SHIFT(96),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [96] = {
        [ts_aux_sym_token9] = SHIFT(97),
    },
    [97] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [98] = {
        [ts_sym_expression] = SHIFT(99),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(102),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [99] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(100),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [100] = {
        [ts_aux_sym_token3] = SHIFT(101),
    },
    [101] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
    },
    [102] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [103] = {
        [ts_sym_expression] = SHIFT(104),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(494),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
    },
    [104] = {
        [ts_aux_sym_array_repeat0] = SHIFT(105),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [105] = {
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [106] = {
        [ts_sym_identifier] = SHIFT(107),
    },
    [107] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 3),
    },
    [108] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [109] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(110),
    },
    [110] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_property_access, 4),
    },
    [111] = {
        [ts_builtin_sym_error] = SHIFT(112),
        [ts_sym_string] = SHIFT(115),
        [ts_sym_identifier] = SHIFT(115),
        [ts_aux_sym_token1] = SHIFT(493),
    },
    [112] = {
        [ts_aux_sym_object_repeat0] = SHIFT(113),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [113] = {
        [ts_aux_sym_token1] = SHIFT(114),
    },
    [114] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [115] = {
        [ts_aux_sym_token4] = SHIFT(116),
    },
    [116] = {
        [ts_sym_expression] = SHIFT(117),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [117] = {
        [ts_aux_sym_object_repeat0] = SHIFT(118),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [118] = {
        [ts_aux_sym_token1] = SHIFT(119),
    },
    [119] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [120] = {
        [ts_sym_identifier] = SHIFT(121),
    },
    [121] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [122] = {
        [ts_sym_expression] = SHIFT(123),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [123] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(124),
    },
    [124] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
    },
    [125] = {
        [ts_sym_expression] = SHIFT(126),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(491),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(492),
    },
    [126] = {
        [ts_aux_sym_array_repeat0] = SHIFT(127),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [127] = {
        [ts_aux_sym_token9] = SHIFT(128),
    },
    [128] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [129] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [130] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(131),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    [131] = {
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
    },
    [132] = {
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_sym_assignment, 3),
    },
    [133] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    [134] = {
        [ts_sym_formal_parameters] = SHIFT(135),
        [ts_sym_identifier] = SHIFT(488),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [135] = {
        [ts_sym_statement_block] = SHIFT(136),
        [ts_aux_sym_token0] = SHIFT(137),
    },
    [136] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
    },
    [137] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(138),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [138] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(139),
    },
    [139] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [140] = {
        [ts_aux_sym_token2] = SHIFT(141),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(486),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [142] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(143),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [143] = {
        [ts_sym_statement] = SHIFT(144),
        [ts_sym_statement_block] = SHIFT(448),
        [ts_sym_for_statement] = SHIFT(448),
        [ts_sym_if_statement] = SHIFT(448),
        [ts_sym_switch_statement] = SHIFT(448),
        [ts_sym_break_statement] = SHIFT(448),
        [ts_sym_var_declaration] = SHIFT(448),
        [ts_sym_expression_statement] = SHIFT(448),
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(451),
        [ts_sym__break] = SHIFT(452),
        [ts_sym__for] = SHIFT(454),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(461),
        [ts_sym__switch] = SHIFT(468),
        [ts_sym__var] = SHIFT(476),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(480),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [144] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(145),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
    },
    [145] = {
        [ts_sym_statement] = SHIFT(146),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(147),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [146] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
    },
    [147] = {
        [ts_sym__terminator] = SHIFT(37),
    },
    [148] = {
        [ts_aux_sym_token2] = SHIFT(149),
    },
    [149] = {
        [ts_sym_expression] = SHIFT(150),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(447),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [150] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [151] = {
        [ts_aux_sym_token0] = SHIFT(152),
    },
    [152] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(445),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [153] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(444),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [154] = {
        [ts_sym_expression] = SHIFT(155),
        [ts_sym_assignment] = SHIFT(413),
        [ts_sym_function_expression] = SHIFT(413),
        [ts_sym_function_call] = SHIFT(413),
        [ts_sym_property_access] = SHIFT(414),
        [ts_sym_literal] = SHIFT(413),
        [ts_sym_object] = SHIFT(417),
        [ts_sym_array] = SHIFT(417),
        [ts_sym__function] = SHIFT(418),
        [ts_sym_null] = SHIFT(417),
        [ts_sym_true] = SHIFT(417),
        [ts_sym_false] = SHIFT(417),
        [ts_sym_string] = SHIFT(417),
        [ts_sym_identifier] = SHIFT(414),
        [ts_sym_number] = SHIFT(417),
        [ts_aux_sym_token0] = SHIFT(428),
        [ts_aux_sym_token8] = SHIFT(438),
    },
    [155] = {
        [ts_aux_sym_token2] = SHIFT(156),
        [ts_aux_sym_token4] = SHIFT(161),
        [ts_aux_sym_token7] = SHIFT(408),
        [ts_aux_sym_token8] = SHIFT(410),
    },
    [156] = {
        [ts_sym_expression] = SHIFT(157),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(160),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [157] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(158),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [158] = {
        [ts_aux_sym_token3] = SHIFT(159),
    },
    [159] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [160] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [161] = {
        [ts_sym_statement] = SHIFT(162),
        [ts_sym_statement_block] = SHIFT(163),
        [ts_sym_for_statement] = SHIFT(163),
        [ts_sym_if_statement] = SHIFT(163),
        [ts_sym_switch_statement] = SHIFT(163),
        [ts_sym_break_statement] = SHIFT(163),
        [ts_sym_var_declaration] = SHIFT(163),
        [ts_sym_expression_statement] = SHIFT(163),
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(166),
        [ts_sym__break] = SHIFT(167),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(169),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(176),
        [ts_sym__switch] = SHIFT(183),
        [ts_sym__var] = SHIFT(190),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(407),
        [ts_aux_sym_token0] = SHIFT(313),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [162] = {
        [ts_sym_statement] = SHIFT(162),
        [ts_sym_statement_block] = SHIFT(163),
        [ts_sym_for_statement] = SHIFT(163),
        [ts_sym_if_statement] = SHIFT(163),
        [ts_sym_switch_statement] = SHIFT(163),
        [ts_sym_break_statement] = SHIFT(163),
        [ts_sym_var_declaration] = SHIFT(163),
        [ts_sym_expression_statement] = SHIFT(163),
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(166),
        [ts_sym__break] = SHIFT(167),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(169),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(176),
        [ts_sym__switch] = SHIFT(183),
        [ts_sym__var] = SHIFT(190),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(406),
        [ts_aux_sym_token0] = SHIFT(313),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [163] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
    },
    [164] = {
        [ts_sym__terminator] = SHIFT(165),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [165] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [166] = {
        [ts_sym__terminator] = SHIFT(165),
    },
    [167] = {
        [ts_sym__terminator] = SHIFT(168),
    },
    [168] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
    },
    [169] = {
        [ts_aux_sym_token2] = SHIFT(170),
    },
    [170] = {
        [ts_sym_var_declaration] = SHIFT(171),
        [ts_sym_expression_statement] = SHIFT(171),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__var] = SHIFT(400),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [171] = {
        [ts_sym_expression_statement] = SHIFT(172),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [172] = {
        [ts_sym_expression] = SHIFT(173),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(405),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [173] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(174),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [174] = {
        [ts_sym_statement] = SHIFT(175),
        [ts_sym_statement_block] = SHIFT(163),
        [ts_sym_for_statement] = SHIFT(163),
        [ts_sym_if_statement] = SHIFT(163),
        [ts_sym_switch_statement] = SHIFT(163),
        [ts_sym_break_statement] = SHIFT(163),
        [ts_sym_var_declaration] = SHIFT(163),
        [ts_sym_expression_statement] = SHIFT(163),
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(166),
        [ts_sym__break] = SHIFT(167),
        [ts_sym__for] = SHIFT(169),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(176),
        [ts_sym__switch] = SHIFT(183),
        [ts_sym__var] = SHIFT(190),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(313),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [175] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
    },
    [176] = {
        [ts_aux_sym_token2] = SHIFT(177),
    },
    [177] = {
        [ts_sym_expression] = SHIFT(178),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(404),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [178] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [179] = {
        [ts_sym_statement] = SHIFT(180),
        [ts_sym_statement_block] = SHIFT(356),
        [ts_sym_for_statement] = SHIFT(356),
        [ts_sym_if_statement] = SHIFT(356),
        [ts_sym_switch_statement] = SHIFT(356),
        [ts_sym_break_statement] = SHIFT(356),
        [ts_sym_var_declaration] = SHIFT(356),
        [ts_sym_expression_statement] = SHIFT(356),
        [ts_sym_expression] = SHIFT(357),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(359),
        [ts_sym__break] = SHIFT(360),
        [ts_sym__for] = SHIFT(362),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(369),
        [ts_sym__switch] = SHIFT(376),
        [ts_sym__var] = SHIFT(384),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(388),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [180] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(181),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
    },
    [181] = {
        [ts_sym_statement] = SHIFT(182),
        [ts_sym_statement_block] = SHIFT(163),
        [ts_sym_for_statement] = SHIFT(163),
        [ts_sym_if_statement] = SHIFT(163),
        [ts_sym_switch_statement] = SHIFT(163),
        [ts_sym_break_statement] = SHIFT(163),
        [ts_sym_var_declaration] = SHIFT(163),
        [ts_sym_expression_statement] = SHIFT(163),
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(166),
        [ts_sym__break] = SHIFT(167),
        [ts_sym__for] = SHIFT(169),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(176),
        [ts_sym__switch] = SHIFT(183),
        [ts_sym__var] = SHIFT(190),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(313),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [182] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
    },
    [183] = {
        [ts_aux_sym_token2] = SHIFT(184),
    },
    [184] = {
        [ts_sym_expression] = SHIFT(185),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(355),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [185] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(186),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [186] = {
        [ts_aux_sym_token0] = SHIFT(187),
    },
    [187] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(317),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [188] = {
        [ts_aux_sym_token4] = SHIFT(189),
    },
    [189] = {
        [ts_sym_statement] = SHIFT(162),
        [ts_sym_statement_block] = SHIFT(163),
        [ts_sym_for_statement] = SHIFT(163),
        [ts_sym_if_statement] = SHIFT(163),
        [ts_sym_switch_statement] = SHIFT(163),
        [ts_sym_break_statement] = SHIFT(163),
        [ts_sym_var_declaration] = SHIFT(163),
        [ts_sym_expression_statement] = SHIFT(163),
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(166),
        [ts_sym__break] = SHIFT(167),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(169),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(176),
        [ts_sym__switch] = SHIFT(183),
        [ts_sym__var] = SHIFT(190),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(312),
        [ts_aux_sym_token0] = SHIFT(313),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [190] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(202),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [191] = {
        [ts_aux_sym_token2] = SHIFT(192),
        [ts_aux_sym_token7] = SHIFT(197),
        [ts_aux_sym_token8] = SHIFT(199),
    },
    [192] = {
        [ts_sym_expression] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(25),
        [ts_sym_function_expression] = SHIFT(25),
        [ts_sym_function_call] = SHIFT(25),
        [ts_sym_property_access] = SHIFT(26),
        [ts_sym_literal] = SHIFT(25),
        [ts_sym_object] = SHIFT(29),
        [ts_sym_array] = SHIFT(29),
        [ts_sym__function] = SHIFT(30),
        [ts_sym_null] = SHIFT(29),
        [ts_sym_true] = SHIFT(29),
        [ts_sym_false] = SHIFT(29),
        [ts_sym_string] = SHIFT(29),
        [ts_sym_identifier] = SHIFT(26),
        [ts_sym_number] = SHIFT(29),
        [ts_aux_sym_token0] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(196),
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [193] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(194),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(17),
        [ts_aux_sym_token8] = SHIFT(19),
    },
    [194] = {
        [ts_aux_sym_token3] = SHIFT(195),
    },
    [195] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
    },
    [196] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [197] = {
        [ts_sym_identifier] = SHIFT(198),
    },
    [198] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [199] = {
        [ts_sym_expression] = SHIFT(200),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [200] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(201),
    },
    [201] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
    },
    [202] = {
        [ts_sym__terminator] = SHIFT(203),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [203] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [204] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [205] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [206] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [207] = {
        [ts_sym_formal_parameters] = SHIFT(208),
        [ts_sym_identifier] = SHIFT(308),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [208] = {
        [ts_sym_statement_block] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(210),
    },
    [209] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [210] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(211),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(307),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [211] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(212),
    },
    [212] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [213] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(214),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(216),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [214] = {
        [ts_sym__terminator] = SHIFT(215),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [215] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [216] = {
        [ts_sym__terminator] = SHIFT(215),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [217] = {
        [ts_builtin_sym_error] = SHIFT(218),
        [ts_sym_string] = SHIFT(221),
        [ts_sym_identifier] = SHIFT(221),
        [ts_aux_sym_token1] = SHIFT(300),
    },
    [218] = {
        [ts_aux_sym_object_repeat0] = SHIFT(219),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [219] = {
        [ts_aux_sym_token1] = SHIFT(220),
    },
    [220] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [221] = {
        [ts_aux_sym_token4] = SHIFT(222),
    },
    [222] = {
        [ts_sym_expression] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [223] = {
        [ts_aux_sym_object_repeat0] = SHIFT(224),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [224] = {
        [ts_aux_sym_token1] = SHIFT(225),
    },
    [225] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [226] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [227] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(228),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [228] = {
        [ts_sym_expression] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [229] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [230] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [231] = {
        [ts_sym_formal_parameters] = SHIFT(232),
        [ts_sym_identifier] = SHIFT(289),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [232] = {
        [ts_sym_statement_block] = SHIFT(233),
        [ts_aux_sym_token0] = SHIFT(234),
    },
    [233] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [234] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(235),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(237),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [235] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(236),
    },
    [236] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [237] = {
        [ts_aux_sym_token1] = SHIFT(236),
    },
    [238] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(239),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(281),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [239] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = SHIFT(242),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [240] = {
        [ts_aux_sym_token1] = SHIFT(241),
    },
    [241] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [242] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [243] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = SHIFT(244),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [244] = {
        [ts_sym_expression] = SHIFT(245),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [245] = {
        [ts_aux_sym_object_repeat0] = SHIFT(246),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [246] = {
        [ts_aux_sym_token1] = SHIFT(247),
    },
    [247] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [248] = {
        [ts_builtin_sym_error] = SHIFT(249),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(252),
        [ts_aux_sym_token1] = SHIFT(279),
    },
    [249] = {
        [ts_aux_sym_object_repeat0] = SHIFT(250),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [250] = {
        [ts_aux_sym_token1] = SHIFT(251),
    },
    [251] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [252] = {
        [ts_aux_sym_token4] = SHIFT(253),
    },
    [253] = {
        [ts_sym_expression] = SHIFT(254),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [254] = {
        [ts_aux_sym_object_repeat0] = SHIFT(255),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [255] = {
        [ts_aux_sym_token1] = SHIFT(256),
    },
    [256] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [257] = {
        [ts_sym_expression] = SHIFT(258),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(261),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(278),
    },
    [258] = {
        [ts_aux_sym_array_repeat0] = SHIFT(259),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [259] = {
        [ts_aux_sym_token9] = SHIFT(260),
    },
    [260] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [261] = {
        [ts_aux_sym_array_repeat0] = SHIFT(259),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [262] = {
        [ts_builtin_sym_error] = SHIFT(263),
        [ts_sym_string] = SHIFT(266),
        [ts_sym_identifier] = SHIFT(266),
        [ts_aux_sym_token1] = SHIFT(271),
    },
    [263] = {
        [ts_aux_sym_object_repeat0] = SHIFT(264),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [264] = {
        [ts_aux_sym_token1] = SHIFT(265),
    },
    [265] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    [266] = {
        [ts_aux_sym_token4] = SHIFT(267),
    },
    [267] = {
        [ts_sym_expression] = SHIFT(268),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [268] = {
        [ts_aux_sym_object_repeat0] = SHIFT(269),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [269] = {
        [ts_aux_sym_token1] = SHIFT(270),
    },
    [270] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    [271] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [272] = {
        [ts_sym_expression] = SHIFT(273),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(276),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(277),
    },
    [273] = {
        [ts_aux_sym_array_repeat0] = SHIFT(274),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [274] = {
        [ts_aux_sym_token9] = SHIFT(275),
    },
    [275] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    [276] = {
        [ts_aux_sym_array_repeat0] = SHIFT(274),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [277] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [278] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [279] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [280] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(244),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [281] = {
        [ts_aux_sym_token1] = SHIFT(242),
    },
    [282] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [283] = {
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(287),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(288),
    },
    [284] = {
        [ts_aux_sym_array_repeat0] = SHIFT(285),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [285] = {
        [ts_aux_sym_token9] = SHIFT(286),
    },
    [286] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [287] = {
        [ts_aux_sym_array_repeat0] = SHIFT(285),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [288] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [289] = {
        [ts_sym_formal_parameters] = SHIFT(290),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [290] = {
        [ts_sym_statement_block] = SHIFT(291),
        [ts_aux_sym_token0] = SHIFT(234),
    },
    [291] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [292] = {
        [ts_sym_identifier] = SHIFT(293),
        [ts_aux_sym_token3] = SHIFT(299),
    },
    [293] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(294),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(296),
    },
    [294] = {
        [ts_aux_sym_token3] = SHIFT(295),
    },
    [295] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [296] = {
        [ts_sym_identifier] = SHIFT(297),
    },
    [297] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(298),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(296),
    },
    [298] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [299] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [300] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [301] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(305),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(306),
    },
    [302] = {
        [ts_aux_sym_array_repeat0] = SHIFT(303),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [303] = {
        [ts_aux_sym_token9] = SHIFT(304),
    },
    [304] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [305] = {
        [ts_aux_sym_array_repeat0] = SHIFT(303),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [306] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [307] = {
        [ts_aux_sym_token1] = SHIFT(212),
    },
    [308] = {
        [ts_sym_formal_parameters] = SHIFT(309),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [309] = {
        [ts_sym_statement_block] = SHIFT(310),
        [ts_aux_sym_token0] = SHIFT(210),
    },
    [310] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [311] = {
        [ts_sym__terminator] = SHIFT(203),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [312] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
    },
    [313] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(314),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [314] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = SHIFT(315),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [315] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [316] = {
        [ts_aux_sym_token1] = SHIFT(315),
    },
    [317] = {
        [ts_aux_sym_token1] = SHIFT(318),
    },
    [318] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
    },
    [319] = {
        [ts_sym_identifier] = SHIFT(320),
    },
    [320] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [321] = {
        [ts_sym_expression] = SHIFT(322),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [322] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(323),
    },
    [323] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
    },
    [324] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [325] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(326),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [326] = {
        [ts_sym_expression] = SHIFT(327),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [327] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [328] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [329] = {
        [ts_sym_formal_parameters] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(336),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [330] = {
        [ts_sym_statement_block] = SHIFT(331),
        [ts_aux_sym_token0] = SHIFT(332),
    },
    [331] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [332] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(333),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(335),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [333] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(334),
    },
    [334] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [335] = {
        [ts_aux_sym_token1] = SHIFT(334),
    },
    [336] = {
        [ts_sym_formal_parameters] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [337] = {
        [ts_sym_statement_block] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(332),
    },
    [338] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [339] = {
        [ts_builtin_sym_error] = SHIFT(340),
        [ts_sym_string] = SHIFT(343),
        [ts_sym_identifier] = SHIFT(343),
        [ts_aux_sym_token1] = SHIFT(348),
    },
    [340] = {
        [ts_aux_sym_object_repeat0] = SHIFT(341),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [341] = {
        [ts_aux_sym_token1] = SHIFT(342),
    },
    [342] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [343] = {
        [ts_aux_sym_token4] = SHIFT(344),
    },
    [344] = {
        [ts_sym_expression] = SHIFT(345),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [345] = {
        [ts_aux_sym_object_repeat0] = SHIFT(346),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [346] = {
        [ts_aux_sym_token1] = SHIFT(347),
    },
    [347] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [348] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [349] = {
        [ts_sym_expression] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(353),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(354),
    },
    [350] = {
        [ts_aux_sym_array_repeat0] = SHIFT(351),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [351] = {
        [ts_aux_sym_token9] = SHIFT(352),
    },
    [352] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [353] = {
        [ts_aux_sym_array_repeat0] = SHIFT(351),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [354] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [355] = {
        [ts_aux_sym_token3] = SHIFT(186),
    },
    [356] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
    },
    [357] = {
        [ts_sym__terminator] = SHIFT(358),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [358] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [359] = {
        [ts_sym__terminator] = SHIFT(358),
    },
    [360] = {
        [ts_sym__terminator] = SHIFT(361),
    },
    [361] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
    },
    [362] = {
        [ts_aux_sym_token2] = SHIFT(363),
    },
    [363] = {
        [ts_sym_var_declaration] = SHIFT(364),
        [ts_sym_expression_statement] = SHIFT(364),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__var] = SHIFT(400),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [364] = {
        [ts_sym_expression_statement] = SHIFT(365),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [365] = {
        [ts_sym_expression] = SHIFT(366),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(393),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [366] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [367] = {
        [ts_sym_statement] = SHIFT(368),
        [ts_sym_statement_block] = SHIFT(356),
        [ts_sym_for_statement] = SHIFT(356),
        [ts_sym_if_statement] = SHIFT(356),
        [ts_sym_switch_statement] = SHIFT(356),
        [ts_sym_break_statement] = SHIFT(356),
        [ts_sym_var_declaration] = SHIFT(356),
        [ts_sym_expression_statement] = SHIFT(356),
        [ts_sym_expression] = SHIFT(357),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(359),
        [ts_sym__break] = SHIFT(360),
        [ts_sym__for] = SHIFT(362),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(369),
        [ts_sym__switch] = SHIFT(376),
        [ts_sym__var] = SHIFT(384),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(388),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [368] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
    },
    [369] = {
        [ts_aux_sym_token2] = SHIFT(370),
    },
    [370] = {
        [ts_sym_expression] = SHIFT(371),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(392),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [371] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(372),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [372] = {
        [ts_sym_statement] = SHIFT(373),
        [ts_sym_statement_block] = SHIFT(356),
        [ts_sym_for_statement] = SHIFT(356),
        [ts_sym_if_statement] = SHIFT(356),
        [ts_sym_switch_statement] = SHIFT(356),
        [ts_sym_break_statement] = SHIFT(356),
        [ts_sym_var_declaration] = SHIFT(356),
        [ts_sym_expression_statement] = SHIFT(356),
        [ts_sym_expression] = SHIFT(357),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(359),
        [ts_sym__break] = SHIFT(360),
        [ts_sym__for] = SHIFT(362),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(369),
        [ts_sym__switch] = SHIFT(376),
        [ts_sym__var] = SHIFT(384),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(388),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [373] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(374),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
    },
    [374] = {
        [ts_sym_statement] = SHIFT(375),
        [ts_sym_statement_block] = SHIFT(356),
        [ts_sym_for_statement] = SHIFT(356),
        [ts_sym_if_statement] = SHIFT(356),
        [ts_sym_switch_statement] = SHIFT(356),
        [ts_sym_break_statement] = SHIFT(356),
        [ts_sym_var_declaration] = SHIFT(356),
        [ts_sym_expression_statement] = SHIFT(356),
        [ts_sym_expression] = SHIFT(357),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(359),
        [ts_sym__break] = SHIFT(360),
        [ts_sym__for] = SHIFT(362),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(369),
        [ts_sym__switch] = SHIFT(376),
        [ts_sym__var] = SHIFT(384),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(388),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [375] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
    },
    [376] = {
        [ts_aux_sym_token2] = SHIFT(377),
    },
    [377] = {
        [ts_sym_expression] = SHIFT(378),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(383),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [378] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(379),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [379] = {
        [ts_aux_sym_token0] = SHIFT(380),
    },
    [380] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(381),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [381] = {
        [ts_aux_sym_token1] = SHIFT(382),
    },
    [382] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
    },
    [383] = {
        [ts_aux_sym_token3] = SHIFT(379),
    },
    [384] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(385),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(387),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [385] = {
        [ts_sym__terminator] = SHIFT(386),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [386] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [387] = {
        [ts_sym__terminator] = SHIFT(386),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [388] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(389),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(391),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [389] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = SHIFT(390),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [390] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [391] = {
        [ts_aux_sym_token1] = SHIFT(390),
    },
    [392] = {
        [ts_aux_sym_token3] = SHIFT(372),
    },
    [393] = {
        [ts_aux_sym_token3] = SHIFT(367),
    },
    [394] = {
        [ts_sym__terminator] = SHIFT(395),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [395] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [396] = {
        [ts_sym__terminator] = SHIFT(395),
    },
    [397] = {
        [ts_builtin_sym_error] = SHIFT(398),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(399),
        [ts_aux_sym_token1] = SHIFT(282),
    },
    [398] = {
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [399] = {
        [ts_aux_sym_token4] = SHIFT(244),
    },
    [400] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(401),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(403),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [401] = {
        [ts_sym__terminator] = SHIFT(402),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [402] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [403] = {
        [ts_sym__terminator] = SHIFT(402),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [404] = {
        [ts_aux_sym_token3] = SHIFT(179),
    },
    [405] = {
        [ts_aux_sym_token3] = SHIFT(174),
    },
    [406] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [407] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
    },
    [408] = {
        [ts_sym_identifier] = SHIFT(409),
    },
    [409] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 3),
    },
    [410] = {
        [ts_sym_expression] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(47),
        [ts_sym_function_expression] = SHIFT(47),
        [ts_sym_function_call] = SHIFT(47),
        [ts_sym_property_access] = SHIFT(48),
        [ts_sym_literal] = SHIFT(47),
        [ts_sym_object] = SHIFT(51),
        [ts_sym_array] = SHIFT(51),
        [ts_sym__function] = SHIFT(52),
        [ts_sym_null] = SHIFT(51),
        [ts_sym_true] = SHIFT(51),
        [ts_sym_false] = SHIFT(51),
        [ts_sym_string] = SHIFT(51),
        [ts_sym_identifier] = SHIFT(48),
        [ts_sym_number] = SHIFT(51),
        [ts_aux_sym_token0] = SHIFT(111),
        [ts_aux_sym_token8] = SHIFT(125),
    },
    [411] = {
        [ts_aux_sym_token2] = SHIFT(21),
        [ts_aux_sym_token7] = SHIFT(42),
        [ts_aux_sym_token8] = SHIFT(44),
        [ts_aux_sym_token9] = SHIFT(412),
    },
    [412] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
    },
    [413] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [414] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(415),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [415] = {
        [ts_sym_expression] = SHIFT(416),
        [ts_sym_assignment] = SHIFT(413),
        [ts_sym_function_expression] = SHIFT(413),
        [ts_sym_function_call] = SHIFT(413),
        [ts_sym_property_access] = SHIFT(414),
        [ts_sym_literal] = SHIFT(413),
        [ts_sym_object] = SHIFT(417),
        [ts_sym_array] = SHIFT(417),
        [ts_sym__function] = SHIFT(418),
        [ts_sym_null] = SHIFT(417),
        [ts_sym_true] = SHIFT(417),
        [ts_sym_false] = SHIFT(417),
        [ts_sym_string] = SHIFT(417),
        [ts_sym_identifier] = SHIFT(414),
        [ts_sym_number] = SHIFT(417),
        [ts_aux_sym_token0] = SHIFT(428),
        [ts_aux_sym_token8] = SHIFT(438),
    },
    [416] = {
        [ts_aux_sym_token2] = SHIFT(156),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token7] = SHIFT(408),
        [ts_aux_sym_token8] = SHIFT(410),
    },
    [417] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
    },
    [418] = {
        [ts_sym_formal_parameters] = SHIFT(419),
        [ts_sym_identifier] = SHIFT(425),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [419] = {
        [ts_sym_statement_block] = SHIFT(420),
        [ts_aux_sym_token0] = SHIFT(421),
    },
    [420] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
    },
    [421] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(422),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(424),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [422] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(423),
    },
    [423] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [424] = {
        [ts_aux_sym_token1] = SHIFT(423),
    },
    [425] = {
        [ts_sym_formal_parameters] = SHIFT(426),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [426] = {
        [ts_sym_statement_block] = SHIFT(427),
        [ts_aux_sym_token0] = SHIFT(421),
    },
    [427] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [428] = {
        [ts_builtin_sym_error] = SHIFT(429),
        [ts_sym_string] = SHIFT(432),
        [ts_sym_identifier] = SHIFT(432),
        [ts_aux_sym_token1] = SHIFT(437),
    },
    [429] = {
        [ts_aux_sym_object_repeat0] = SHIFT(430),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [430] = {
        [ts_aux_sym_token1] = SHIFT(431),
    },
    [431] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
    },
    [432] = {
        [ts_aux_sym_token4] = SHIFT(433),
    },
    [433] = {
        [ts_sym_expression] = SHIFT(434),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [434] = {
        [ts_aux_sym_object_repeat0] = SHIFT(435),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [435] = {
        [ts_aux_sym_token1] = SHIFT(436),
    },
    [436] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [437] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [438] = {
        [ts_sym_expression] = SHIFT(439),
        [ts_sym_assignment] = SHIFT(129),
        [ts_sym_function_expression] = SHIFT(129),
        [ts_sym_function_call] = SHIFT(129),
        [ts_sym_property_access] = SHIFT(130),
        [ts_sym_literal] = SHIFT(129),
        [ts_sym_object] = SHIFT(133),
        [ts_sym_array] = SHIFT(133),
        [ts_builtin_sym_error] = SHIFT(442),
        [ts_sym__function] = SHIFT(134),
        [ts_sym_null] = SHIFT(133),
        [ts_sym_true] = SHIFT(133),
        [ts_sym_false] = SHIFT(133),
        [ts_sym_string] = SHIFT(133),
        [ts_sym_identifier] = SHIFT(130),
        [ts_sym_number] = SHIFT(133),
        [ts_aux_sym_token0] = SHIFT(262),
        [ts_aux_sym_token8] = SHIFT(272),
        [ts_aux_sym_token9] = SHIFT(443),
    },
    [439] = {
        [ts_aux_sym_array_repeat0] = SHIFT(440),
        [ts_aux_sym_token2] = SHIFT(98),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token7] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [440] = {
        [ts_aux_sym_token9] = SHIFT(441),
    },
    [441] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
    },
    [442] = {
        [ts_aux_sym_array_repeat0] = SHIFT(440),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [443] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [444] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [445] = {
        [ts_aux_sym_token1] = SHIFT(446),
    },
    [446] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
    },
    [447] = {
        [ts_aux_sym_token3] = SHIFT(151),
    },
    [448] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
    },
    [449] = {
        [ts_sym__terminator] = SHIFT(450),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [450] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [451] = {
        [ts_sym__terminator] = SHIFT(450),
    },
    [452] = {
        [ts_sym__terminator] = SHIFT(453),
    },
    [453] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
    },
    [454] = {
        [ts_aux_sym_token2] = SHIFT(455),
    },
    [455] = {
        [ts_sym_var_declaration] = SHIFT(456),
        [ts_sym_expression_statement] = SHIFT(456),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__var] = SHIFT(400),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [456] = {
        [ts_sym_expression_statement] = SHIFT(457),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [457] = {
        [ts_sym_expression] = SHIFT(458),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(485),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [458] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [459] = {
        [ts_sym_statement] = SHIFT(460),
        [ts_sym_statement_block] = SHIFT(448),
        [ts_sym_for_statement] = SHIFT(448),
        [ts_sym_if_statement] = SHIFT(448),
        [ts_sym_switch_statement] = SHIFT(448),
        [ts_sym_break_statement] = SHIFT(448),
        [ts_sym_var_declaration] = SHIFT(448),
        [ts_sym_expression_statement] = SHIFT(448),
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(451),
        [ts_sym__break] = SHIFT(452),
        [ts_sym__for] = SHIFT(454),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(461),
        [ts_sym__switch] = SHIFT(468),
        [ts_sym__var] = SHIFT(476),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(480),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [460] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
    },
    [461] = {
        [ts_aux_sym_token2] = SHIFT(462),
    },
    [462] = {
        [ts_sym_expression] = SHIFT(463),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(484),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [463] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(464),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [464] = {
        [ts_sym_statement] = SHIFT(465),
        [ts_sym_statement_block] = SHIFT(448),
        [ts_sym_for_statement] = SHIFT(448),
        [ts_sym_if_statement] = SHIFT(448),
        [ts_sym_switch_statement] = SHIFT(448),
        [ts_sym_break_statement] = SHIFT(448),
        [ts_sym_var_declaration] = SHIFT(448),
        [ts_sym_expression_statement] = SHIFT(448),
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(451),
        [ts_sym__break] = SHIFT(452),
        [ts_sym__for] = SHIFT(454),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(461),
        [ts_sym__switch] = SHIFT(468),
        [ts_sym__var] = SHIFT(476),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(480),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [465] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(466),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
    },
    [466] = {
        [ts_sym_statement] = SHIFT(467),
        [ts_sym_statement_block] = SHIFT(448),
        [ts_sym_for_statement] = SHIFT(448),
        [ts_sym_if_statement] = SHIFT(448),
        [ts_sym_switch_statement] = SHIFT(448),
        [ts_sym_break_statement] = SHIFT(448),
        [ts_sym_var_declaration] = SHIFT(448),
        [ts_sym_expression_statement] = SHIFT(448),
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(451),
        [ts_sym__break] = SHIFT(452),
        [ts_sym__for] = SHIFT(454),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(461),
        [ts_sym__switch] = SHIFT(468),
        [ts_sym__var] = SHIFT(476),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(480),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [467] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
    },
    [468] = {
        [ts_aux_sym_token2] = SHIFT(469),
    },
    [469] = {
        [ts_sym_expression] = SHIFT(470),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(475),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [470] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(471),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [471] = {
        [ts_aux_sym_token0] = SHIFT(472),
    },
    [472] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(473),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [473] = {
        [ts_aux_sym_token1] = SHIFT(474),
    },
    [474] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
    },
    [475] = {
        [ts_aux_sym_token3] = SHIFT(471),
    },
    [476] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(477),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [477] = {
        [ts_sym__terminator] = SHIFT(478),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [478] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [479] = {
        [ts_sym__terminator] = SHIFT(478),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [480] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(481),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(483),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [481] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = SHIFT(482),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [482] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [483] = {
        [ts_aux_sym_token1] = SHIFT(482),
    },
    [484] = {
        [ts_aux_sym_token3] = SHIFT(464),
    },
    [485] = {
        [ts_aux_sym_token3] = SHIFT(459),
    },
    [486] = {
        [ts_aux_sym_token3] = SHIFT(143),
    },
    [487] = {
        [ts_aux_sym_token1] = SHIFT(139),
    },
    [488] = {
        [ts_sym_formal_parameters] = SHIFT(489),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [489] = {
        [ts_sym_statement_block] = SHIFT(490),
        [ts_aux_sym_token0] = SHIFT(137),
    },
    [490] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [491] = {
        [ts_aux_sym_array_repeat0] = SHIFT(127),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [492] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    [493] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    [494] = {
        [ts_aux_sym_array_repeat0] = SHIFT(105),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [495] = {
        [ts_aux_sym_array_repeat0] = SHIFT(96),
        [ts_aux_sym_token6] = SHIFT(103),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [496] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
    },
    [497] = {
        [ts_aux_sym_token4] = SHIFT(498),
    },
    [498] = {
        [ts_sym_expression] = SHIFT(499),
        [ts_sym_assignment] = SHIFT(226),
        [ts_sym_function_expression] = SHIFT(226),
        [ts_sym_function_call] = SHIFT(226),
        [ts_sym_property_access] = SHIFT(227),
        [ts_sym_literal] = SHIFT(226),
        [ts_sym_object] = SHIFT(230),
        [ts_sym_array] = SHIFT(230),
        [ts_sym__function] = SHIFT(231),
        [ts_sym_null] = SHIFT(230),
        [ts_sym_true] = SHIFT(230),
        [ts_sym_false] = SHIFT(230),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(227),
        [ts_sym_number] = SHIFT(230),
        [ts_aux_sym_token0] = SHIFT(248),
        [ts_aux_sym_token8] = SHIFT(257),
    },
    [499] = {
        [ts_aux_sym_object_repeat0] = SHIFT(500),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(82),
        [ts_aux_sym_token7] = SHIFT(120),
        [ts_aux_sym_token8] = SHIFT(122),
    },
    [500] = {
        [ts_aux_sym_token1] = SHIFT(501),
    },
    [501] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
    },
    [502] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
    },
    [503] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [504] = {
        [ts_sym_statement] = SHIFT(505),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(147),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [505] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
    },
    [506] = {
        [ts_aux_sym_token3] = SHIFT(504),
    },
    [507] = {
        [ts_aux_sym_token1] = SHIFT(66),
    },
    [508] = {
        [ts_sym_formal_parameters] = SHIFT(509),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [509] = {
        [ts_sym_statement_block] = SHIFT(510),
        [ts_aux_sym_token0] = SHIFT(64),
    },
    [510] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [511] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(512),
    },
    [512] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
    },
    [513] = {
        [ts_aux_sym_token1] = SHIFT(512),
    },
    [514] = {
        [ts_sym_formal_parameters] = SHIFT(515),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [515] = {
        [ts_sym_statement_block] = SHIFT(516),
        [ts_aux_sym_token0] = SHIFT(55),
    },
    [516] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
    },
    [517] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
    },
    [518] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [519] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_token1] = SHIFT(520),
    },
    [520] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [521] = {
        [ts_aux_sym_token1] = SHIFT(520),
    },
    [522] = {
        [ts_sym_formal_parameters] = SHIFT(523),
        [ts_aux_sym_token2] = SHIFT(292),
    },
    [523] = {
        [ts_sym_statement_block] = SHIFT(524),
        [ts_aux_sym_token0] = SHIFT(33),
    },
    [524] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
    },
    [525] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
    },
    [526] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_property_access, 4),
    },
    [527] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [528] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
    },
    [529] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [530] = {
        [ts_sym__terminator] = SHIFT(531),
    },
    [531] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
    },
    [532] = {
        [ts_aux_sym_token2] = SHIFT(533),
    },
    [533] = {
        [ts_sym_var_declaration] = SHIFT(534),
        [ts_sym_expression_statement] = SHIFT(534),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__var] = SHIFT(400),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [534] = {
        [ts_sym_expression_statement] = SHIFT(535),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [535] = {
        [ts_sym_expression] = SHIFT(536),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(601),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [536] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(537),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [537] = {
        [ts_sym_statement] = SHIFT(538),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(529),
        [ts_sym__break] = SHIFT(530),
        [ts_sym__for] = SHIFT(532),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(539),
        [ts_sym__switch] = SHIFT(546),
        [ts_sym__var] = SHIFT(554),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(558),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [538] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
    },
    [539] = {
        [ts_aux_sym_token2] = SHIFT(540),
    },
    [540] = {
        [ts_sym_expression] = SHIFT(541),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(600),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [541] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(542),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [542] = {
        [ts_sym_statement] = SHIFT(543),
        [ts_sym_statement_block] = SHIFT(562),
        [ts_sym_for_statement] = SHIFT(562),
        [ts_sym_if_statement] = SHIFT(562),
        [ts_sym_switch_statement] = SHIFT(562),
        [ts_sym_break_statement] = SHIFT(562),
        [ts_sym_var_declaration] = SHIFT(562),
        [ts_sym_expression_statement] = SHIFT(562),
        [ts_sym_expression] = SHIFT(563),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(565),
        [ts_sym__break] = SHIFT(566),
        [ts_sym__for] = SHIFT(568),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(575),
        [ts_sym__switch] = SHIFT(582),
        [ts_sym__var] = SHIFT(590),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(594),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [543] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(544),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
    },
    [544] = {
        [ts_sym_statement] = SHIFT(545),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(529),
        [ts_sym__break] = SHIFT(530),
        [ts_sym__for] = SHIFT(532),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(539),
        [ts_sym__switch] = SHIFT(546),
        [ts_sym__var] = SHIFT(554),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(558),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [545] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
    },
    [546] = {
        [ts_aux_sym_token2] = SHIFT(547),
    },
    [547] = {
        [ts_sym_expression] = SHIFT(548),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(553),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [548] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(549),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [549] = {
        [ts_aux_sym_token0] = SHIFT(550),
    },
    [550] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(551),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [551] = {
        [ts_aux_sym_token1] = SHIFT(552),
    },
    [552] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
    },
    [553] = {
        [ts_aux_sym_token3] = SHIFT(549),
    },
    [554] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(555),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(557),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [555] = {
        [ts_sym__terminator] = SHIFT(556),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [556] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [557] = {
        [ts_sym__terminator] = SHIFT(556),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [558] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(559),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(561),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [559] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = SHIFT(560),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [560] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [561] = {
        [ts_aux_sym_token1] = SHIFT(560),
    },
    [562] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
    },
    [563] = {
        [ts_sym__terminator] = SHIFT(564),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token7] = SHIFT(38),
        [ts_aux_sym_token8] = SHIFT(40),
    },
    [564] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
    },
    [565] = {
        [ts_sym__terminator] = SHIFT(564),
    },
    [566] = {
        [ts_sym__terminator] = SHIFT(567),
    },
    [567] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
    },
    [568] = {
        [ts_aux_sym_token2] = SHIFT(569),
    },
    [569] = {
        [ts_sym_var_declaration] = SHIFT(570),
        [ts_sym_expression_statement] = SHIFT(570),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__var] = SHIFT(400),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [570] = {
        [ts_sym_expression_statement] = SHIFT(571),
        [ts_sym_expression] = SHIFT(394),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(396),
        [ts_sym__function] = SHIFT(61),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(397),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [571] = {
        [ts_sym_expression] = SHIFT(572),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [572] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(573),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [573] = {
        [ts_sym_statement] = SHIFT(574),
        [ts_sym_statement_block] = SHIFT(562),
        [ts_sym_for_statement] = SHIFT(562),
        [ts_sym_if_statement] = SHIFT(562),
        [ts_sym_switch_statement] = SHIFT(562),
        [ts_sym_break_statement] = SHIFT(562),
        [ts_sym_var_declaration] = SHIFT(562),
        [ts_sym_expression_statement] = SHIFT(562),
        [ts_sym_expression] = SHIFT(563),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(565),
        [ts_sym__break] = SHIFT(566),
        [ts_sym__for] = SHIFT(568),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(575),
        [ts_sym__switch] = SHIFT(582),
        [ts_sym__var] = SHIFT(590),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(594),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [574] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
    },
    [575] = {
        [ts_aux_sym_token2] = SHIFT(576),
    },
    [576] = {
        [ts_sym_expression] = SHIFT(577),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(598),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [577] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(578),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [578] = {
        [ts_sym_statement] = SHIFT(579),
        [ts_sym_statement_block] = SHIFT(562),
        [ts_sym_for_statement] = SHIFT(562),
        [ts_sym_if_statement] = SHIFT(562),
        [ts_sym_switch_statement] = SHIFT(562),
        [ts_sym_break_statement] = SHIFT(562),
        [ts_sym_var_declaration] = SHIFT(562),
        [ts_sym_expression_statement] = SHIFT(562),
        [ts_sym_expression] = SHIFT(563),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(565),
        [ts_sym__break] = SHIFT(566),
        [ts_sym__for] = SHIFT(568),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(575),
        [ts_sym__switch] = SHIFT(582),
        [ts_sym__var] = SHIFT(590),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(594),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [579] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(580),
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
    },
    [580] = {
        [ts_sym_statement] = SHIFT(581),
        [ts_sym_statement_block] = SHIFT(562),
        [ts_sym_for_statement] = SHIFT(562),
        [ts_sym_if_statement] = SHIFT(562),
        [ts_sym_switch_statement] = SHIFT(562),
        [ts_sym_break_statement] = SHIFT(562),
        [ts_sym_var_declaration] = SHIFT(562),
        [ts_sym_expression_statement] = SHIFT(562),
        [ts_sym_expression] = SHIFT(563),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(565),
        [ts_sym__break] = SHIFT(566),
        [ts_sym__for] = SHIFT(568),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(575),
        [ts_sym__switch] = SHIFT(582),
        [ts_sym__var] = SHIFT(590),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(60),
        [ts_sym_identifier] = SHIFT(57),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_token0] = SHIFT(594),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [581] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
    },
    [582] = {
        [ts_aux_sym_token2] = SHIFT(583),
    },
    [583] = {
        [ts_sym_expression] = SHIFT(584),
        [ts_sym_assignment] = SHIFT(324),
        [ts_sym_function_expression] = SHIFT(324),
        [ts_sym_function_call] = SHIFT(324),
        [ts_sym_property_access] = SHIFT(325),
        [ts_sym_literal] = SHIFT(324),
        [ts_sym_object] = SHIFT(328),
        [ts_sym_array] = SHIFT(328),
        [ts_builtin_sym_error] = SHIFT(589),
        [ts_sym__function] = SHIFT(329),
        [ts_sym_null] = SHIFT(328),
        [ts_sym_true] = SHIFT(328),
        [ts_sym_false] = SHIFT(328),
        [ts_sym_string] = SHIFT(328),
        [ts_sym_identifier] = SHIFT(325),
        [ts_sym_number] = SHIFT(328),
        [ts_aux_sym_token0] = SHIFT(339),
        [ts_aux_sym_token8] = SHIFT(349),
    },
    [584] = {
        [ts_aux_sym_token2] = SHIFT(74),
        [ts_aux_sym_token3] = SHIFT(585),
        [ts_aux_sym_token7] = SHIFT(319),
        [ts_aux_sym_token8] = SHIFT(321),
    },
    [585] = {
        [ts_aux_sym_token0] = SHIFT(586),
    },
    [586] = {
        [ts_sym_switch_case] = SHIFT(153),
        [ts_sym__case] = SHIFT(154),
        [ts_sym__default] = SHIFT(188),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(587),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [587] = {
        [ts_aux_sym_token1] = SHIFT(588),
    },
    [588] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
    },
    [589] = {
        [ts_aux_sym_token3] = SHIFT(585),
    },
    [590] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_assignment] = SHIFT(591),
        [ts_sym_function_expression] = SHIFT(204),
        [ts_sym_function_call] = SHIFT(204),
        [ts_sym_property_access] = SHIFT(205),
        [ts_sym_literal] = SHIFT(204),
        [ts_sym_object] = SHIFT(206),
        [ts_sym_array] = SHIFT(206),
        [ts_sym__function] = SHIFT(207),
        [ts_sym_null] = SHIFT(206),
        [ts_sym_true] = SHIFT(206),
        [ts_sym_false] = SHIFT(206),
        [ts_sym_string] = SHIFT(206),
        [ts_sym_identifier] = SHIFT(593),
        [ts_sym_number] = SHIFT(206),
        [ts_aux_sym_token0] = SHIFT(217),
        [ts_aux_sym_token8] = SHIFT(301),
    },
    [591] = {
        [ts_sym__terminator] = SHIFT(592),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [592] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
    },
    [593] = {
        [ts_sym__terminator] = SHIFT(592),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = SHIFT(58),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
    },
    [594] = {
        [ts_sym_statement] = SHIFT(34),
        [ts_sym_statement_block] = SHIFT(35),
        [ts_sym_for_statement] = SHIFT(35),
        [ts_sym_if_statement] = SHIFT(35),
        [ts_sym_switch_statement] = SHIFT(35),
        [ts_sym_break_statement] = SHIFT(35),
        [ts_sym_var_declaration] = SHIFT(35),
        [ts_sym_expression_statement] = SHIFT(35),
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_assignment] = SHIFT(56),
        [ts_sym_function_expression] = SHIFT(56),
        [ts_sym_function_call] = SHIFT(56),
        [ts_sym_property_access] = SHIFT(57),
        [ts_sym_literal] = SHIFT(56),
        [ts_sym_object] = SHIFT(60),
        [ts_sym_array] = SHIFT(60),
        [ts_builtin_sym_error] = SHIFT(595),
        [ts_sym__break] = SHIFT(67),
        [ts_sym__for] = SHIFT(69),
        [ts_sym__function] = SHIFT(61),
        [ts_sym__if] = SHIFT(140),
        [ts_sym__switch] = SHIFT(148),
        [ts_sym__var] = SHIFT(213),
        [ts_sym_null] = SHIFT(60),
        [ts_sym_true] = SHIFT(60),
        [ts_sym_false] = SHIFT(60),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(60),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(597),
        [ts_aux_sym_token0] = SHIFT(238),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token8] = SHIFT(283),
    },
    [595] = {
        [ts_sym__terminator] = SHIFT(37),
        [ts_aux_sym_object_repeat0] = SHIFT(240),
        [ts_aux_sym_token1] = SHIFT(596),
        [ts_aux_sym_token6] = SHIFT(82),
    },
    [596] = {
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
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
    },
    [597] = {
        [ts_aux_sym_token1] = SHIFT(596),
    },
    [598] = {
        [ts_aux_sym_token3] = SHIFT(578),
    },
    [599] = {
        [ts_aux_sym_token3] = SHIFT(573),
    },
    [600] = {
        [ts_aux_sym_token3] = SHIFT(542),
    },
    [601] = {
        [ts_aux_sym_token3] = SHIFT(537),
    },
    [602] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [603] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
