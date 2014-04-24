#include "tree_sitter/parser.h"

#define STATE_COUNT 688
#define SYMBOL_COUNT 63

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
    ts_sym_comment = 35,
    ts_sym__terminator = 36,
    ts_sym_string = 37,
    ts_sym_identifier = 38,
    ts_sym_number = 39,
    ts_aux_sym_program_repeat0 = 40,
    ts_aux_sym_statement_block_repeat0 = 41,
    ts_aux_sym_switch_statement_repeat0 = 42,
    ts_aux_sym_switch_case_repeat0 = 43,
    ts_aux_sym_function_call_repeat0 = 44,
    ts_aux_sym_formal_parameters_repeat0 = 45,
    ts_aux_sym_object_repeat0 = 46,
    ts_aux_sym_array_repeat0 = 47,
    ts_aux_sym_token0 = 48,
    ts_aux_sym_token1 = 49,
    ts_aux_sym_token2 = 50,
    ts_aux_sym_token3 = 51,
    ts_aux_sym_token4 = 52,
    ts_aux_sym_token5 = 53,
    ts_aux_sym_token6 = 54,
    ts_aux_sym_token7 = 55,
    ts_aux_sym_token8 = 56,
    ts_aux_sym_token9 = 57,
    ts_aux_sym_token10 = 58,
    ts_aux_sym_token11 = 59,
    ts_aux_sym_token12 = 60,
    ts_aux_sym_token13 = 61,
    ts_aux_sym_token14 = 62,
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
    [ts_sym_comment] = "comment",
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
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
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
            if (lookahead == '/')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (!(lookahead == '\n'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_comment);
        case 10:
            if (lookahead == '.')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_number);
        case 11:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym_number);
        case 13:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 14:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 15:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'r')
                ADVANCE(16);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 16:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(17);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 17:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'a')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 18:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'k')
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__break);
        case 20:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'a')
                ADVANCE(21);
            if (lookahead == 'o')
                ADVANCE(25);
            if (lookahead == 'u')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 21:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'l')
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 22:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 's')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 23:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 24:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_false);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'r')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__for);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'n')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 't')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'i')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'o')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'n')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__function);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'f')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__if);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'u')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'l')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'l')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_null);
        case 40:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'v') ||
                ('x' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'w')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'i')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 't')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'h')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__switch);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'r')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'u')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_true);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
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
                ADVANCE(13);
            if (lookahead == 'r')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 52:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__var);
        case 53:
            ACCEPT_TOKEN(ts_aux_sym_token0);
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
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
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
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 56:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 58:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 60:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 61:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 62:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 64:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == ')')
                ADVANCE(65);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 66:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 67:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 68:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 69:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 70:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 71:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 75:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 77:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '\n')
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '\n')
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 79:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\n')
                ADVANCE(81);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\n')
                ADVANCE(81);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '}')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 82:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '\n')
                ADVANCE(83);
            if (lookahead == ';')
                ADVANCE(62);
            LEX_ERROR();
        case 83:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '\n')
                ADVANCE(83);
            if (lookahead == ';')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 84:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 85:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == ',')
                ADVANCE(67);
            LEX_ERROR();
        case 86:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 87:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 88:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 89:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 90:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 91:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(65);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'f')
                ADVANCE(92);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 92:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'a')
                ADVANCE(21);
            if (lookahead == 'u')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 93:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 94:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 95:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(96);
            if (lookahead == 'd')
                ADVANCE(100);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 96:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'a')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 97:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 's')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 98:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 99:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__case);
        case 100:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 101:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'f')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 102:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'a')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 103:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'u')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 104:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'l')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 105:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 't')
                ADVANCE(106);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 106:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__default);
        case 107:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'f')
                ADVANCE(92);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '\n')
                ADVANCE(111);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '\n')
                ADVANCE(111);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '}')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 112:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == ']')
                ADVANCE(74);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == ':')
                ADVANCE(69);
            LEX_ERROR();
        case 114:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 115:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            if (lookahead == 'f')
                ADVANCE(92);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '\n')
                ADVANCE(117);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '\n')
                ADVANCE(117);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 118:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '\n')
                ADVANCE(119);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 119:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '\n')
                ADVANCE(119);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == ')')
                ADVANCE(65);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == '(')
                ADVANCE(56);
            LEX_ERROR();
        case 123:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '(')
                ADVANCE(56);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            LEX_ERROR();
        case 124:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(124);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 125:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == 'c')
                ADVANCE(126);
            if (lookahead == 'd')
                ADVANCE(130);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 126:
            if (lookahead == 'a')
                ADVANCE(127);
            LEX_ERROR();
        case 127:
            if (lookahead == 's')
                ADVANCE(128);
            LEX_ERROR();
        case 128:
            if (lookahead == 'e')
                ADVANCE(129);
            LEX_ERROR();
        case 129:
            ACCEPT_TOKEN(ts_sym__case);
        case 130:
            if (lookahead == 'e')
                ADVANCE(131);
            LEX_ERROR();
        case 131:
            if (lookahead == 'f')
                ADVANCE(132);
            LEX_ERROR();
        case 132:
            if (lookahead == 'a')
                ADVANCE(133);
            LEX_ERROR();
        case 133:
            if (lookahead == 'u')
                ADVANCE(134);
            LEX_ERROR();
        case 134:
            if (lookahead == 'l')
                ADVANCE(135);
            LEX_ERROR();
        case 135:
            if (lookahead == 't')
                ADVANCE(136);
            LEX_ERROR();
        case 136:
            ACCEPT_TOKEN(ts_sym__default);
        case 137:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(61);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (lookahead == '[')
                ADVANCE(14);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(96);
            if (lookahead == 'd')
                ADVANCE(100);
            if (lookahead == 'e')
                ADVANCE(140);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 140:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'l')
                ADVANCE(141);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 141:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 's')
                ADVANCE(142);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 142:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == 'e')
                ADVANCE(143);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 143:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__else);
        case 144:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '\"')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'f')
                ADVANCE(92);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(140);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 146:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\"')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            LEX_ERROR();
        case 147:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(8);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(140);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            LEX_ERROR();
        case 148:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '\n')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(150);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(96);
            if (lookahead == 'd')
                ADVANCE(100);
            if (lookahead == 'e')
                ADVANCE(140);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
            LEX_ERROR();
        case 149:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '\n')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(150);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(96);
            if (lookahead == 'd')
                ADVANCE(100);
            if (lookahead == 'e')
                ADVANCE(140);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 150:
            if (lookahead == '/')
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '\n')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(56);
            if (lookahead == ')')
                ADVANCE(65);
            if (lookahead == '*')
                ADVANCE(57);
            if (lookahead == '+')
                ADVANCE(58);
            if (lookahead == ',')
                ADVANCE(67);
            if (lookahead == '-')
                ADVANCE(59);
            if (lookahead == '.')
                ADVANCE(60);
            if (lookahead == '/')
                ADVANCE(150);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (lookahead == ':')
                ADVANCE(69);
            if (lookahead == ';')
                ADVANCE(62);
            if (lookahead == '=')
                ADVANCE(71);
            if (lookahead == '?')
                ADVANCE(63);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(14);
            if (lookahead == ']')
                ADVANCE(74);
            if (lookahead == 'b')
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(96);
            if (lookahead == 'd')
                ADVANCE(100);
            if (lookahead == 'e')
                ADVANCE(140);
            if (lookahead == 'f')
                ADVANCE(20);
            if (lookahead == 'i')
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(36);
            if (lookahead == 's')
                ADVANCE(40);
            if (lookahead == 't')
                ADVANCE(46);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(76);
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
    [4] = 54,
    [5] = 2,
    [6] = 91,
    [7] = 66,
    [8] = 64,
    [9] = 54,
    [10] = 91,
    [11] = 66,
    [12] = 64,
    [13] = 66,
    [14] = 109,
    [15] = 66,
    [16] = 109,
    [17] = 66,
    [18] = 109,
    [19] = 68,
    [20] = 91,
    [21] = 66,
    [22] = 64,
    [23] = 68,
    [24] = 109,
    [25] = 66,
    [26] = 64,
    [27] = 72,
    [28] = 70,
    [29] = 109,
    [30] = 73,
    [31] = 91,
    [32] = 66,
    [33] = 64,
    [34] = 73,
    [35] = 66,
    [36] = 70,
    [37] = 109,
    [38] = 66,
    [39] = 66,
    [40] = 66,
    [41] = 123,
    [42] = 120,
    [43] = 66,
    [44] = 75,
    [45] = 75,
    [46] = 75,
    [47] = 54,
    [48] = 75,
    [49] = 109,
    [50] = 54,
    [51] = 109,
    [52] = 54,
    [53] = 109,
    [54] = 68,
    [55] = 109,
    [56] = 54,
    [57] = 72,
    [58] = 77,
    [59] = 109,
    [60] = 73,
    [61] = 109,
    [62] = 73,
    [63] = 109,
    [64] = 73,
    [65] = 109,
    [66] = 68,
    [67] = 109,
    [68] = 73,
    [69] = 72,
    [70] = 79,
    [71] = 109,
    [72] = 73,
    [73] = 79,
    [74] = 73,
    [75] = 79,
    [76] = 109,
    [77] = 73,
    [78] = 73,
    [79] = 73,
    [80] = 123,
    [81] = 120,
    [82] = 73,
    [83] = 75,
    [84] = 54,
    [85] = 77,
    [86] = 109,
    [87] = 54,
    [88] = 54,
    [89] = 54,
    [90] = 123,
    [91] = 120,
    [92] = 54,
    [93] = 75,
    [94] = 80,
    [95] = 54,
    [96] = 82,
    [97] = 75,
    [98] = 122,
    [99] = 144,
    [100] = 109,
    [101] = 109,
    [102] = 84,
    [103] = 91,
    [104] = 66,
    [105] = 64,
    [106] = 84,
    [107] = 85,
    [108] = 114,
    [109] = 87,
    [110] = 86,
    [111] = 66,
    [112] = 146,
    [113] = 87,
    [114] = 86,
    [115] = 113,
    [116] = 109,
    [117] = 88,
    [118] = 86,
    [119] = 91,
    [120] = 66,
    [121] = 64,
    [122] = 88,
    [123] = 85,
    [124] = 88,
    [125] = 115,
    [126] = 90,
    [127] = 89,
    [128] = 66,
    [129] = 91,
    [130] = 66,
    [131] = 64,
    [132] = 90,
    [133] = 85,
    [134] = 90,
    [135] = 109,
    [136] = 90,
    [137] = 109,
    [138] = 90,
    [139] = 109,
    [140] = 68,
    [141] = 109,
    [142] = 90,
    [143] = 72,
    [144] = 93,
    [145] = 109,
    [146] = 73,
    [147] = 93,
    [148] = 114,
    [149] = 87,
    [150] = 86,
    [151] = 73,
    [152] = 113,
    [153] = 109,
    [154] = 88,
    [155] = 86,
    [156] = 73,
    [157] = 109,
    [158] = 88,
    [159] = 109,
    [160] = 88,
    [161] = 109,
    [162] = 68,
    [163] = 109,
    [164] = 88,
    [165] = 72,
    [166] = 94,
    [167] = 109,
    [168] = 73,
    [169] = 94,
    [170] = 115,
    [171] = 90,
    [172] = 89,
    [173] = 73,
    [174] = 109,
    [175] = 90,
    [176] = 89,
    [177] = 90,
    [178] = 93,
    [179] = 109,
    [180] = 90,
    [181] = 90,
    [182] = 90,
    [183] = 123,
    [184] = 120,
    [185] = 90,
    [186] = 75,
    [187] = 80,
    [188] = 90,
    [189] = 122,
    [190] = 109,
    [191] = 84,
    [192] = 138,
    [193] = 145,
    [194] = 138,
    [195] = 75,
    [196] = 82,
    [197] = 122,
    [198] = 109,
    [199] = 84,
    [200] = 120,
    [201] = 125,
    [202] = 125,
    [203] = 109,
    [204] = 68,
    [205] = 95,
    [206] = 95,
    [207] = 95,
    [208] = 54,
    [209] = 95,
    [210] = 82,
    [211] = 82,
    [212] = 95,
    [213] = 122,
    [214] = 144,
    [215] = 109,
    [216] = 109,
    [217] = 84,
    [218] = 138,
    [219] = 95,
    [220] = 122,
    [221] = 109,
    [222] = 84,
    [223] = 138,
    [224] = 139,
    [225] = 138,
    [226] = 95,
    [227] = 122,
    [228] = 109,
    [229] = 84,
    [230] = 120,
    [231] = 125,
    [232] = 113,
    [233] = 95,
    [234] = 109,
    [235] = 107,
    [236] = 91,
    [237] = 66,
    [238] = 64,
    [239] = 107,
    [240] = 85,
    [241] = 107,
    [242] = 109,
    [243] = 107,
    [244] = 109,
    [245] = 107,
    [246] = 109,
    [247] = 68,
    [248] = 109,
    [249] = 107,
    [250] = 72,
    [251] = 108,
    [252] = 109,
    [253] = 73,
    [254] = 108,
    [255] = 107,
    [256] = 108,
    [257] = 109,
    [258] = 107,
    [259] = 107,
    [260] = 107,
    [261] = 123,
    [262] = 120,
    [263] = 107,
    [264] = 75,
    [265] = 80,
    [266] = 107,
    [267] = 109,
    [268] = 54,
    [269] = 75,
    [270] = 108,
    [271] = 77,
    [272] = 114,
    [273] = 87,
    [274] = 86,
    [275] = 107,
    [276] = 113,
    [277] = 109,
    [278] = 88,
    [279] = 86,
    [280] = 107,
    [281] = 88,
    [282] = 94,
    [283] = 109,
    [284] = 88,
    [285] = 88,
    [286] = 88,
    [287] = 123,
    [288] = 120,
    [289] = 88,
    [290] = 75,
    [291] = 80,
    [292] = 88,
    [293] = 86,
    [294] = 75,
    [295] = 110,
    [296] = 86,
    [297] = 54,
    [298] = 75,
    [299] = 116,
    [300] = 109,
    [301] = 88,
    [302] = 86,
    [303] = 54,
    [304] = 114,
    [305] = 87,
    [306] = 86,
    [307] = 88,
    [308] = 113,
    [309] = 109,
    [310] = 88,
    [311] = 86,
    [312] = 88,
    [313] = 115,
    [314] = 90,
    [315] = 89,
    [316] = 88,
    [317] = 112,
    [318] = 114,
    [319] = 87,
    [320] = 86,
    [321] = 90,
    [322] = 113,
    [323] = 109,
    [324] = 88,
    [325] = 86,
    [326] = 90,
    [327] = 90,
    [328] = 115,
    [329] = 90,
    [330] = 89,
    [331] = 90,
    [332] = 112,
    [333] = 90,
    [334] = 88,
    [335] = 88,
    [336] = 118,
    [337] = 86,
    [338] = 54,
    [339] = 115,
    [340] = 90,
    [341] = 89,
    [342] = 54,
    [343] = 112,
    [344] = 54,
    [345] = 122,
    [346] = 120,
    [347] = 88,
    [348] = 121,
    [349] = 85,
    [350] = 64,
    [351] = 120,
    [352] = 72,
    [353] = 85,
    [354] = 64,
    [355] = 120,
    [356] = 107,
    [357] = 115,
    [358] = 90,
    [359] = 89,
    [360] = 107,
    [361] = 112,
    [362] = 107,
    [363] = 86,
    [364] = 122,
    [365] = 120,
    [366] = 107,
    [367] = 109,
    [368] = 68,
    [369] = 109,
    [370] = 68,
    [371] = 109,
    [372] = 68,
    [373] = 109,
    [374] = 68,
    [375] = 72,
    [376] = 124,
    [377] = 109,
    [378] = 73,
    [379] = 124,
    [380] = 68,
    [381] = 124,
    [382] = 109,
    [383] = 68,
    [384] = 68,
    [385] = 68,
    [386] = 123,
    [387] = 120,
    [388] = 68,
    [389] = 75,
    [390] = 80,
    [391] = 68,
    [392] = 86,
    [393] = 122,
    [394] = 120,
    [395] = 68,
    [396] = 114,
    [397] = 87,
    [398] = 86,
    [399] = 68,
    [400] = 113,
    [401] = 109,
    [402] = 88,
    [403] = 86,
    [404] = 68,
    [405] = 68,
    [406] = 115,
    [407] = 90,
    [408] = 89,
    [409] = 68,
    [410] = 112,
    [411] = 68,
    [412] = 54,
    [413] = 95,
    [414] = 77,
    [415] = 125,
    [416] = 75,
    [417] = 110,
    [418] = 95,
    [419] = 86,
    [420] = 86,
    [421] = 95,
    [422] = 109,
    [423] = 84,
    [424] = 109,
    [425] = 84,
    [426] = 109,
    [427] = 68,
    [428] = 109,
    [429] = 84,
    [430] = 72,
    [431] = 137,
    [432] = 109,
    [433] = 73,
    [434] = 137,
    [435] = 84,
    [436] = 137,
    [437] = 109,
    [438] = 84,
    [439] = 84,
    [440] = 84,
    [441] = 123,
    [442] = 120,
    [443] = 84,
    [444] = 75,
    [445] = 80,
    [446] = 84,
    [447] = 86,
    [448] = 122,
    [449] = 120,
    [450] = 84,
    [451] = 114,
    [452] = 87,
    [453] = 86,
    [454] = 84,
    [455] = 113,
    [456] = 109,
    [457] = 88,
    [458] = 86,
    [459] = 84,
    [460] = 84,
    [461] = 115,
    [462] = 90,
    [463] = 89,
    [464] = 84,
    [465] = 112,
    [466] = 84,
    [467] = 64,
    [468] = 139,
    [469] = 54,
    [470] = 139,
    [471] = 82,
    [472] = 82,
    [473] = 139,
    [474] = 122,
    [475] = 144,
    [476] = 109,
    [477] = 109,
    [478] = 84,
    [479] = 138,
    [480] = 139,
    [481] = 122,
    [482] = 109,
    [483] = 84,
    [484] = 138,
    [485] = 139,
    [486] = 138,
    [487] = 139,
    [488] = 122,
    [489] = 109,
    [490] = 84,
    [491] = 120,
    [492] = 125,
    [493] = 86,
    [494] = 139,
    [495] = 64,
    [496] = 109,
    [497] = 54,
    [498] = 139,
    [499] = 77,
    [500] = 75,
    [501] = 110,
    [502] = 139,
    [503] = 86,
    [504] = 64,
    [505] = 64,
    [506] = 54,
    [507] = 109,
    [508] = 82,
    [509] = 114,
    [510] = 87,
    [511] = 113,
    [512] = 109,
    [513] = 54,
    [514] = 109,
    [515] = 77,
    [516] = 64,
    [517] = 64,
    [518] = 125,
    [519] = 125,
    [520] = 86,
    [521] = 86,
    [522] = 75,
    [523] = 64,
    [524] = 145,
    [525] = 54,
    [526] = 145,
    [527] = 82,
    [528] = 82,
    [529] = 145,
    [530] = 122,
    [531] = 144,
    [532] = 109,
    [533] = 109,
    [534] = 84,
    [535] = 138,
    [536] = 145,
    [537] = 122,
    [538] = 109,
    [539] = 84,
    [540] = 138,
    [541] = 145,
    [542] = 138,
    [543] = 145,
    [544] = 122,
    [545] = 109,
    [546] = 84,
    [547] = 120,
    [548] = 125,
    [549] = 86,
    [550] = 145,
    [551] = 64,
    [552] = 109,
    [553] = 54,
    [554] = 145,
    [555] = 77,
    [556] = 75,
    [557] = 110,
    [558] = 145,
    [559] = 86,
    [560] = 64,
    [561] = 64,
    [562] = 64,
    [563] = 86,
    [564] = 122,
    [565] = 120,
    [566] = 90,
    [567] = 112,
    [568] = 112,
    [569] = 73,
    [570] = 73,
    [571] = 112,
    [572] = 66,
    [573] = 113,
    [574] = 109,
    [575] = 88,
    [576] = 86,
    [577] = 66,
    [578] = 66,
    [579] = 84,
    [580] = 138,
    [581] = 75,
    [582] = 64,
    [583] = 86,
    [584] = 122,
    [585] = 120,
    [586] = 54,
    [587] = 80,
    [588] = 73,
    [589] = 86,
    [590] = 122,
    [591] = 120,
    [592] = 73,
    [593] = 77,
    [594] = 86,
    [595] = 80,
    [596] = 66,
    [597] = 86,
    [598] = 122,
    [599] = 120,
    [600] = 66,
    [601] = 85,
    [602] = 73,
    [603] = 70,
    [604] = 85,
    [605] = 85,
    [606] = 68,
    [607] = 109,
    [608] = 66,
    [609] = 85,
    [610] = 66,
    [611] = 85,
    [612] = 54,
    [613] = 82,
    [614] = 82,
    [615] = 2,
    [616] = 122,
    [617] = 144,
    [618] = 109,
    [619] = 109,
    [620] = 84,
    [621] = 138,
    [622] = 2,
    [623] = 122,
    [624] = 109,
    [625] = 84,
    [626] = 138,
    [627] = 147,
    [628] = 138,
    [629] = 2,
    [630] = 122,
    [631] = 109,
    [632] = 84,
    [633] = 120,
    [634] = 125,
    [635] = 86,
    [636] = 2,
    [637] = 64,
    [638] = 109,
    [639] = 54,
    [640] = 2,
    [641] = 77,
    [642] = 75,
    [643] = 110,
    [644] = 2,
    [645] = 86,
    [646] = 147,
    [647] = 54,
    [648] = 147,
    [649] = 82,
    [650] = 82,
    [651] = 147,
    [652] = 122,
    [653] = 144,
    [654] = 109,
    [655] = 109,
    [656] = 84,
    [657] = 138,
    [658] = 147,
    [659] = 122,
    [660] = 109,
    [661] = 84,
    [662] = 138,
    [663] = 147,
    [664] = 138,
    [665] = 147,
    [666] = 122,
    [667] = 109,
    [668] = 84,
    [669] = 120,
    [670] = 125,
    [671] = 86,
    [672] = 147,
    [673] = 64,
    [674] = 109,
    [675] = 54,
    [676] = 147,
    [677] = 77,
    [678] = 75,
    [679] = 110,
    [680] = 147,
    [681] = 86,
    [682] = 64,
    [683] = 64,
    [684] = 64,
    [685] = 64,
    [686] = 0,
    [687] = 0,
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
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(614),
        [ts_sym__for] = SHIFT(616),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(623),
        [ts_sym__switch] = SHIFT(630),
        [ts_sym__var] = SHIFT(638),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_program_repeat0] = SHIFT(687),
        [ts_aux_sym_token0] = SHIFT(642),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__break] = SHIFT(614),
        [ts_sym__for] = SHIFT(616),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(623),
        [ts_sym__switch] = SHIFT(630),
        [ts_sym__var] = SHIFT(638),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_program_repeat0] = SHIFT(686),
        [ts_aux_sym_token0] = SHIFT(642),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
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
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_builtin_sym_error] = SHIFT(611),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(612),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_builtin_sym_error] = SHIFT(609),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(610),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [19] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(607),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
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
        [ts_builtin_sym_error] = SHIFT(605),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(606),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_aux_sym_token14] = SHIFT(603),
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
        [ts_builtin_sym_error] = SHIFT(601),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(602),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_sym_identifier] = SHIFT(598),
        [ts_aux_sym_token2] = SHIFT(348),
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
        [ts_builtin_sym_error] = SHIFT(595),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(597),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_builtin_sym_error] = SHIFT(196),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(594),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
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
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [54] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(55),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
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
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_aux_sym_token14] = SHIFT(593),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [66] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(67),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
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
        [ts_sym_identifier] = SHIFT(590),
        [ts_aux_sym_token2] = SHIFT(348),
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
        [ts_builtin_sym_error] = SHIFT(587),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(589),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_sym_identifier] = SHIFT(584),
        [ts_aux_sym_token2] = SHIFT(348),
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
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(583),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
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
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(512),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [100] = {
        [ts_sym_expression_statement] = SHIFT(101),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [101] = {
        [ts_sym_expression] = SHIFT(102),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(582),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [102] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(580),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
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
        [ts_builtin_sym_error] = SHIFT(107),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(579),
        [ts_aux_sym_token13] = SHIFT(125),
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
        [ts_aux_sym_function_call_repeat0] = SHIFT(105),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [108] = {
        [ts_builtin_sym_error] = SHIFT(109),
        [ts_sym_string] = SHIFT(573),
        [ts_sym_identifier] = SHIFT(573),
        [ts_aux_sym_token1] = SHIFT(578),
    },
    [109] = {
        [ts_aux_sym_object_repeat0] = SHIFT(110),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [110] = {
        [ts_aux_sym_token1] = SHIFT(111),
    },
    [111] = {
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
    [112] = {
        [ts_builtin_sym_error] = SHIFT(113),
        [ts_sym_string] = SHIFT(115),
        [ts_sym_identifier] = SHIFT(115),
    },
    [113] = {
        [ts_aux_sym_object_repeat0] = SHIFT(114),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [114] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [115] = {
        [ts_aux_sym_token4] = SHIFT(116),
    },
    [116] = {
        [ts_sym_expression] = SHIFT(117),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [117] = {
        [ts_aux_sym_object_repeat0] = SHIFT(118),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [118] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [119] = {
        [ts_sym_expression] = SHIFT(120),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_builtin_sym_error] = SHIFT(123),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(124),
        [ts_aux_sym_token13] = SHIFT(125),
    },
    [120] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(121),
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
    [121] = {
        [ts_aux_sym_token3] = SHIFT(122),
    },
    [122] = {
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
    [123] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(121),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [124] = {
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
    [125] = {
        [ts_sym_expression] = SHIFT(126),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(571),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(572),
    },
    [126] = {
        [ts_aux_sym_array_repeat0] = SHIFT(127),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [127] = {
        [ts_aux_sym_token14] = SHIFT(128),
    },
    [128] = {
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
    [129] = {
        [ts_sym_expression] = SHIFT(130),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_builtin_sym_error] = SHIFT(133),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(134),
        [ts_aux_sym_token13] = SHIFT(125),
    },
    [130] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(131),
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
    [131] = {
        [ts_aux_sym_token3] = SHIFT(132),
    },
    [132] = {
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
    [133] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(131),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [134] = {
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
    [135] = {
        [ts_sym_expression] = SHIFT(136),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
    },
    [136] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_math_op, 3),
    },
    [137] = {
        [ts_sym_expression] = SHIFT(138),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
    },
    [138] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_math_op, 3),
    },
    [139] = {
        [ts_sym_expression] = SHIFT(140),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [140] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(141),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
    },
    [142] = {
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_sym_ternary, 5),
    },
    [143] = {
        [ts_sym_identifier] = SHIFT(144),
    },
    [144] = {
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
    [145] = {
        [ts_sym_expression] = SHIFT(146),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
    },
    [146] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(147),
    },
    [147] = {
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
    [148] = {
        [ts_builtin_sym_error] = SHIFT(149),
        [ts_sym_string] = SHIFT(152),
        [ts_sym_identifier] = SHIFT(152),
        [ts_aux_sym_token1] = SHIFT(570),
    },
    [149] = {
        [ts_aux_sym_object_repeat0] = SHIFT(150),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [150] = {
        [ts_aux_sym_token1] = SHIFT(151),
    },
    [151] = {
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
    [152] = {
        [ts_aux_sym_token4] = SHIFT(153),
    },
    [153] = {
        [ts_sym_expression] = SHIFT(154),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [154] = {
        [ts_aux_sym_object_repeat0] = SHIFT(155),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [155] = {
        [ts_aux_sym_token1] = SHIFT(156),
    },
    [156] = {
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
    [157] = {
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [158] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [159] = {
        [ts_sym_expression] = SHIFT(160),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [160] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [161] = {
        [ts_sym_expression] = SHIFT(162),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [162] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(163),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [164] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [165] = {
        [ts_sym_identifier] = SHIFT(166),
    },
    [166] = {
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
    [167] = {
        [ts_sym_expression] = SHIFT(168),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
    },
    [168] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(169),
    },
    [169] = {
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
    [170] = {
        [ts_sym_expression] = SHIFT(171),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(568),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(569),
    },
    [171] = {
        [ts_aux_sym_array_repeat0] = SHIFT(172),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [172] = {
        [ts_aux_sym_token14] = SHIFT(173),
    },
    [173] = {
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
    [174] = {
        [ts_sym_expression] = SHIFT(175),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(567),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
    },
    [175] = {
        [ts_aux_sym_array_repeat0] = SHIFT(176),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [176] = {
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [177] = {
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
    [178] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(179),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
    },
    [179] = {
        [ts_sym_expression] = SHIFT(180),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
    },
    [180] = {
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_sym_assignment, 3),
    },
    [181] = {
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
    [182] = {
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
    [183] = {
        [ts_sym_formal_parameters] = SHIFT(184),
        [ts_sym_identifier] = SHIFT(564),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [184] = {
        [ts_sym_statement_block] = SHIFT(185),
        [ts_aux_sym_token0] = SHIFT(186),
    },
    [185] = {
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
    [186] = {
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
        [ts_builtin_sym_error] = SHIFT(187),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(563),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [187] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(188),
    },
    [188] = {
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
    [189] = {
        [ts_aux_sym_token2] = SHIFT(190),
    },
    [190] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(562),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [191] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(192),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [192] = {
        [ts_sym_statement] = SHIFT(193),
        [ts_sym_statement_block] = SHIFT(524),
        [ts_sym_for_statement] = SHIFT(524),
        [ts_sym_if_statement] = SHIFT(524),
        [ts_sym_switch_statement] = SHIFT(524),
        [ts_sym_break_statement] = SHIFT(524),
        [ts_sym_var_declaration] = SHIFT(524),
        [ts_sym_expression_statement] = SHIFT(524),
        [ts_sym_expression] = SHIFT(525),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(527),
        [ts_sym__break] = SHIFT(528),
        [ts_sym__for] = SHIFT(530),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(537),
        [ts_sym__switch] = SHIFT(544),
        [ts_sym__var] = SHIFT(552),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(524),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(556),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [193] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(194),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [194] = {
        [ts_sym_statement] = SHIFT(195),
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
        [ts_builtin_sym_error] = SHIFT(196),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [195] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [196] = {
        [ts_sym__terminator] = SHIFT(48),
    },
    [197] = {
        [ts_aux_sym_token2] = SHIFT(198),
    },
    [198] = {
        [ts_sym_expression] = SHIFT(199),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(523),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [199] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [200] = {
        [ts_aux_sym_token0] = SHIFT(201),
    },
    [201] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(521),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [202] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(520),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [203] = {
        [ts_sym_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [204] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(205),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [205] = {
        [ts_sym_statement] = SHIFT(206),
        [ts_sym_statement_block] = SHIFT(207),
        [ts_sym_for_statement] = SHIFT(207),
        [ts_sym_if_statement] = SHIFT(207),
        [ts_sym_switch_statement] = SHIFT(207),
        [ts_sym_break_statement] = SHIFT(207),
        [ts_sym_var_declaration] = SHIFT(207),
        [ts_sym_expression_statement] = SHIFT(207),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(210),
        [ts_sym__break] = SHIFT(211),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(213),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(220),
        [ts_sym__switch] = SHIFT(227),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(207),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(519),
        [ts_aux_sym_token0] = SHIFT(416),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [206] = {
        [ts_sym_statement] = SHIFT(206),
        [ts_sym_statement_block] = SHIFT(207),
        [ts_sym_for_statement] = SHIFT(207),
        [ts_sym_if_statement] = SHIFT(207),
        [ts_sym_switch_statement] = SHIFT(207),
        [ts_sym_break_statement] = SHIFT(207),
        [ts_sym_var_declaration] = SHIFT(207),
        [ts_sym_expression_statement] = SHIFT(207),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(210),
        [ts_sym__break] = SHIFT(211),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(213),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(220),
        [ts_sym__switch] = SHIFT(227),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(207),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(518),
        [ts_aux_sym_token0] = SHIFT(416),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [207] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [208] = {
        [ts_sym__terminator] = SHIFT(209),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [209] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [210] = {
        [ts_sym__terminator] = SHIFT(209),
    },
    [211] = {
        [ts_sym__terminator] = SHIFT(212),
    },
    [212] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [213] = {
        [ts_aux_sym_token2] = SHIFT(214),
    },
    [214] = {
        [ts_sym_var_declaration] = SHIFT(215),
        [ts_sym_expression_statement] = SHIFT(215),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(512),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [215] = {
        [ts_sym_expression_statement] = SHIFT(216),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [216] = {
        [ts_sym_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(517),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [217] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(218),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [218] = {
        [ts_sym_statement] = SHIFT(219),
        [ts_sym_statement_block] = SHIFT(207),
        [ts_sym_for_statement] = SHIFT(207),
        [ts_sym_if_statement] = SHIFT(207),
        [ts_sym_switch_statement] = SHIFT(207),
        [ts_sym_break_statement] = SHIFT(207),
        [ts_sym_var_declaration] = SHIFT(207),
        [ts_sym_expression_statement] = SHIFT(207),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(210),
        [ts_sym__break] = SHIFT(211),
        [ts_sym__for] = SHIFT(213),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(220),
        [ts_sym__switch] = SHIFT(227),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(207),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(416),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [219] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [220] = {
        [ts_aux_sym_token2] = SHIFT(221),
    },
    [221] = {
        [ts_sym_expression] = SHIFT(222),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(516),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [222] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(223),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [223] = {
        [ts_sym_statement] = SHIFT(224),
        [ts_sym_statement_block] = SHIFT(468),
        [ts_sym_for_statement] = SHIFT(468),
        [ts_sym_if_statement] = SHIFT(468),
        [ts_sym_switch_statement] = SHIFT(468),
        [ts_sym_break_statement] = SHIFT(468),
        [ts_sym_var_declaration] = SHIFT(468),
        [ts_sym_expression_statement] = SHIFT(468),
        [ts_sym_expression] = SHIFT(469),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(471),
        [ts_sym__break] = SHIFT(472),
        [ts_sym__for] = SHIFT(474),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(481),
        [ts_sym__switch] = SHIFT(488),
        [ts_sym__var] = SHIFT(496),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(468),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [224] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(225),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [225] = {
        [ts_sym_statement] = SHIFT(226),
        [ts_sym_statement_block] = SHIFT(207),
        [ts_sym_for_statement] = SHIFT(207),
        [ts_sym_if_statement] = SHIFT(207),
        [ts_sym_switch_statement] = SHIFT(207),
        [ts_sym_break_statement] = SHIFT(207),
        [ts_sym_var_declaration] = SHIFT(207),
        [ts_sym_expression_statement] = SHIFT(207),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(210),
        [ts_sym__break] = SHIFT(211),
        [ts_sym__for] = SHIFT(213),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(220),
        [ts_sym__switch] = SHIFT(227),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(207),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(416),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [226] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [227] = {
        [ts_aux_sym_token2] = SHIFT(228),
    },
    [228] = {
        [ts_sym_expression] = SHIFT(229),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(467),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [229] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(230),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [230] = {
        [ts_aux_sym_token0] = SHIFT(231),
    },
    [231] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(420),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [232] = {
        [ts_aux_sym_token4] = SHIFT(233),
    },
    [233] = {
        [ts_sym_statement] = SHIFT(206),
        [ts_sym_statement_block] = SHIFT(207),
        [ts_sym_for_statement] = SHIFT(207),
        [ts_sym_if_statement] = SHIFT(207),
        [ts_sym_switch_statement] = SHIFT(207),
        [ts_sym_break_statement] = SHIFT(207),
        [ts_sym_var_declaration] = SHIFT(207),
        [ts_sym_expression_statement] = SHIFT(207),
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(210),
        [ts_sym__break] = SHIFT(211),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(213),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(220),
        [ts_sym__switch] = SHIFT(227),
        [ts_sym__var] = SHIFT(234),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(207),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(415),
        [ts_aux_sym_token0] = SHIFT(416),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [234] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(412),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(414),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [235] = {
        [ts_aux_sym_token2] = SHIFT(236),
        [ts_aux_sym_token5] = SHIFT(242),
        [ts_aux_sym_token6] = SHIFT(242),
        [ts_aux_sym_token7] = SHIFT(244),
        [ts_aux_sym_token8] = SHIFT(244),
        [ts_aux_sym_token9] = SHIFT(246),
        [ts_aux_sym_token12] = SHIFT(250),
        [ts_aux_sym_token13] = SHIFT(252),
    },
    [236] = {
        [ts_sym_expression] = SHIFT(237),
        [ts_sym_math_op] = SHIFT(35),
        [ts_sym_ternary] = SHIFT(35),
        [ts_sym_assignment] = SHIFT(35),
        [ts_sym_function_expression] = SHIFT(35),
        [ts_sym_function_call] = SHIFT(35),
        [ts_sym_property_access] = SHIFT(36),
        [ts_sym_literal] = SHIFT(39),
        [ts_sym_object] = SHIFT(40),
        [ts_sym_array] = SHIFT(40),
        [ts_builtin_sym_error] = SHIFT(240),
        [ts_sym__function] = SHIFT(41),
        [ts_sym_null] = SHIFT(40),
        [ts_sym_true] = SHIFT(40),
        [ts_sym_false] = SHIFT(40),
        [ts_sym_string] = SHIFT(40),
        [ts_sym_identifier] = SHIFT(36),
        [ts_sym_number] = SHIFT(40),
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token3] = SHIFT(241),
        [ts_aux_sym_token13] = SHIFT(125),
    },
    [237] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(238),
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
    [238] = {
        [ts_aux_sym_token3] = SHIFT(239),
    },
    [239] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
    },
    [240] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(238),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [241] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
    },
    [242] = {
        [ts_sym_expression] = SHIFT(243),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(255),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(256),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [243] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(242),
        [ts_aux_sym_token6] = SHIFT(242),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [244] = {
        [ts_sym_expression] = SHIFT(245),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(255),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(256),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [245] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(242),
        [ts_aux_sym_token6] = SHIFT(242),
        [ts_aux_sym_token7] = SHIFT(244),
        [ts_aux_sym_token8] = SHIFT(244),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [246] = {
        [ts_sym_expression] = SHIFT(247),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [247] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [248] = {
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(255),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(256),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [249] = {
        [ts_aux_sym_token2] = SHIFT(236),
        [ts_aux_sym_token5] = SHIFT(242),
        [ts_aux_sym_token6] = SHIFT(242),
        [ts_aux_sym_token7] = SHIFT(244),
        [ts_aux_sym_token8] = SHIFT(244),
        [ts_aux_sym_token9] = SHIFT(246),
        [ts_aux_sym_token12] = SHIFT(250),
        [ts_aux_sym_token13] = SHIFT(252),
    },
    [250] = {
        [ts_sym_identifier] = SHIFT(251),
    },
    [251] = {
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
    [252] = {
        [ts_sym_expression] = SHIFT(253),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
    },
    [253] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(254),
    },
    [254] = {
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(257),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [257] = {
        [ts_sym_expression] = SHIFT(258),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(255),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(256),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [258] = {
        [ts_aux_sym_token2] = SHIFT(236),
        [ts_aux_sym_token5] = SHIFT(242),
        [ts_aux_sym_token6] = SHIFT(242),
        [ts_aux_sym_token7] = SHIFT(244),
        [ts_aux_sym_token8] = SHIFT(244),
        [ts_aux_sym_token9] = SHIFT(246),
        [ts_aux_sym_token12] = SHIFT(250),
        [ts_aux_sym_token13] = SHIFT(252),
    },
    [259] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [260] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [261] = {
        [ts_sym_formal_parameters] = SHIFT(262),
        [ts_sym_identifier] = SHIFT(364),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [262] = {
        [ts_sym_statement_block] = SHIFT(263),
        [ts_aux_sym_token0] = SHIFT(264),
    },
    [263] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
    },
    [264] = {
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
        [ts_builtin_sym_error] = SHIFT(265),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(363),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [265] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(266),
    },
    [266] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [267] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(268),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [268] = {
        [ts_sym__terminator] = SHIFT(269),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [269] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [270] = {
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
    [271] = {
        [ts_sym__terminator] = SHIFT(269),
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
    [272] = {
        [ts_builtin_sym_error] = SHIFT(273),
        [ts_sym_string] = SHIFT(276),
        [ts_sym_identifier] = SHIFT(276),
        [ts_aux_sym_token1] = SHIFT(356),
    },
    [273] = {
        [ts_aux_sym_object_repeat0] = SHIFT(274),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [274] = {
        [ts_aux_sym_token1] = SHIFT(275),
    },
    [275] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
    },
    [276] = {
        [ts_aux_sym_token4] = SHIFT(277),
    },
    [277] = {
        [ts_sym_expression] = SHIFT(278),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [278] = {
        [ts_aux_sym_object_repeat0] = SHIFT(279),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [279] = {
        [ts_aux_sym_token1] = SHIFT(280),
    },
    [280] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
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
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(283),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [283] = {
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [284] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [285] = {
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
    [286] = {
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
    [287] = {
        [ts_sym_formal_parameters] = SHIFT(288),
        [ts_sym_identifier] = SHIFT(345),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [288] = {
        [ts_sym_statement_block] = SHIFT(289),
        [ts_aux_sym_token0] = SHIFT(290),
    },
    [289] = {
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
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(293),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [291] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(292),
    },
    [292] = {
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
    [293] = {
        [ts_aux_sym_token1] = SHIFT(292),
    },
    [294] = {
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
        [ts_builtin_sym_error] = SHIFT(295),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(299),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(337),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(338),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [295] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = SHIFT(298),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [296] = {
        [ts_aux_sym_token1] = SHIFT(297),
    },
    [297] = {
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
    [298] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [299] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = SHIFT(300),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
    },
    [300] = {
        [ts_sym_expression] = SHIFT(301),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [301] = {
        [ts_aux_sym_object_repeat0] = SHIFT(302),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [302] = {
        [ts_aux_sym_token1] = SHIFT(303),
    },
    [303] = {
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
    [304] = {
        [ts_builtin_sym_error] = SHIFT(305),
        [ts_sym_string] = SHIFT(308),
        [ts_sym_identifier] = SHIFT(308),
        [ts_aux_sym_token1] = SHIFT(335),
    },
    [305] = {
        [ts_aux_sym_object_repeat0] = SHIFT(306),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [306] = {
        [ts_aux_sym_token1] = SHIFT(307),
    },
    [307] = {
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
    [308] = {
        [ts_aux_sym_token4] = SHIFT(309),
    },
    [309] = {
        [ts_sym_expression] = SHIFT(310),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [310] = {
        [ts_aux_sym_object_repeat0] = SHIFT(311),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [311] = {
        [ts_aux_sym_token1] = SHIFT(312),
    },
    [312] = {
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
    [313] = {
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(317),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(334),
    },
    [314] = {
        [ts_aux_sym_array_repeat0] = SHIFT(315),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [315] = {
        [ts_aux_sym_token14] = SHIFT(316),
    },
    [316] = {
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
    [317] = {
        [ts_aux_sym_array_repeat0] = SHIFT(315),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [318] = {
        [ts_builtin_sym_error] = SHIFT(319),
        [ts_sym_string] = SHIFT(322),
        [ts_sym_identifier] = SHIFT(322),
        [ts_aux_sym_token1] = SHIFT(327),
    },
    [319] = {
        [ts_aux_sym_object_repeat0] = SHIFT(320),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [320] = {
        [ts_aux_sym_token1] = SHIFT(321),
    },
    [321] = {
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
    [322] = {
        [ts_aux_sym_token4] = SHIFT(323),
    },
    [323] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [324] = {
        [ts_aux_sym_object_repeat0] = SHIFT(325),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [325] = {
        [ts_aux_sym_token1] = SHIFT(326),
    },
    [326] = {
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
    [327] = {
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
    [328] = {
        [ts_sym_expression] = SHIFT(329),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(332),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(333),
    },
    [329] = {
        [ts_aux_sym_array_repeat0] = SHIFT(330),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [330] = {
        [ts_aux_sym_token14] = SHIFT(331),
    },
    [331] = {
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
    [332] = {
        [ts_aux_sym_array_repeat0] = SHIFT(330),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [333] = {
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
    [334] = {
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
    [335] = {
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
    [336] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(300),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(86),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [337] = {
        [ts_aux_sym_token1] = SHIFT(298),
    },
    [338] = {
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
    [339] = {
        [ts_sym_expression] = SHIFT(340),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(343),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(344),
    },
    [340] = {
        [ts_aux_sym_array_repeat0] = SHIFT(341),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [341] = {
        [ts_aux_sym_token14] = SHIFT(342),
    },
    [342] = {
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
    [343] = {
        [ts_aux_sym_array_repeat0] = SHIFT(341),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [344] = {
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
    [345] = {
        [ts_sym_formal_parameters] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [346] = {
        [ts_sym_statement_block] = SHIFT(347),
        [ts_aux_sym_token0] = SHIFT(290),
    },
    [347] = {
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
    [348] = {
        [ts_sym_identifier] = SHIFT(349),
        [ts_aux_sym_token3] = SHIFT(355),
    },
    [349] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(350),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(352),
    },
    [350] = {
        [ts_aux_sym_token3] = SHIFT(351),
    },
    [351] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [352] = {
        [ts_sym_identifier] = SHIFT(353),
    },
    [353] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(354),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(352),
    },
    [354] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [355] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [356] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
    },
    [357] = {
        [ts_sym_expression] = SHIFT(358),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(361),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(362),
    },
    [358] = {
        [ts_aux_sym_array_repeat0] = SHIFT(359),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [359] = {
        [ts_aux_sym_token14] = SHIFT(360),
    },
    [360] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
    },
    [361] = {
        [ts_aux_sym_array_repeat0] = SHIFT(359),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [362] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
    },
    [363] = {
        [ts_aux_sym_token1] = SHIFT(266),
    },
    [364] = {
        [ts_sym_formal_parameters] = SHIFT(365),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [365] = {
        [ts_sym_statement_block] = SHIFT(366),
        [ts_aux_sym_token0] = SHIFT(264),
    },
    [366] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
    },
    [367] = {
        [ts_sym_expression] = SHIFT(368),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [368] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [369] = {
        [ts_sym_expression] = SHIFT(370),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [370] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [371] = {
        [ts_sym_expression] = SHIFT(372),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [372] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(373),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [373] = {
        [ts_sym_expression] = SHIFT(374),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [374] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [375] = {
        [ts_sym_identifier] = SHIFT(376),
    },
    [376] = {
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
    [377] = {
        [ts_sym_expression] = SHIFT(378),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
    },
    [378] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(379),
    },
    [379] = {
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(382),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [382] = {
        [ts_sym_expression] = SHIFT(383),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [383] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [384] = {
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
    [385] = {
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
    [386] = {
        [ts_sym_formal_parameters] = SHIFT(387),
        [ts_sym_identifier] = SHIFT(393),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [387] = {
        [ts_sym_statement_block] = SHIFT(388),
        [ts_aux_sym_token0] = SHIFT(389),
    },
    [388] = {
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
    [389] = {
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
        [ts_builtin_sym_error] = SHIFT(390),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(392),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [390] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(391),
    },
    [391] = {
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
    [392] = {
        [ts_aux_sym_token1] = SHIFT(391),
    },
    [393] = {
        [ts_sym_formal_parameters] = SHIFT(394),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [394] = {
        [ts_sym_statement_block] = SHIFT(395),
        [ts_aux_sym_token0] = SHIFT(389),
    },
    [395] = {
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
    [396] = {
        [ts_builtin_sym_error] = SHIFT(397),
        [ts_sym_string] = SHIFT(400),
        [ts_sym_identifier] = SHIFT(400),
        [ts_aux_sym_token1] = SHIFT(405),
    },
    [397] = {
        [ts_aux_sym_object_repeat0] = SHIFT(398),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [398] = {
        [ts_aux_sym_token1] = SHIFT(399),
    },
    [399] = {
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
    [400] = {
        [ts_aux_sym_token4] = SHIFT(401),
    },
    [401] = {
        [ts_sym_expression] = SHIFT(402),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [402] = {
        [ts_aux_sym_object_repeat0] = SHIFT(403),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [403] = {
        [ts_aux_sym_token1] = SHIFT(404),
    },
    [404] = {
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
    [405] = {
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
    [406] = {
        [ts_sym_expression] = SHIFT(407),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(410),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(411),
    },
    [407] = {
        [ts_aux_sym_array_repeat0] = SHIFT(408),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [408] = {
        [ts_aux_sym_token14] = SHIFT(409),
    },
    [409] = {
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
    [410] = {
        [ts_aux_sym_array_repeat0] = SHIFT(408),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [411] = {
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
    [412] = {
        [ts_sym__terminator] = SHIFT(413),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [413] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [414] = {
        [ts_sym__terminator] = SHIFT(413),
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
    [415] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
    },
    [416] = {
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
        [ts_builtin_sym_error] = SHIFT(417),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(299),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(419),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(338),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [417] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = SHIFT(418),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [418] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [419] = {
        [ts_aux_sym_token1] = SHIFT(418),
    },
    [420] = {
        [ts_aux_sym_token1] = SHIFT(421),
    },
    [421] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [422] = {
        [ts_sym_expression] = SHIFT(423),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [423] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [424] = {
        [ts_sym_expression] = SHIFT(425),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [425] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_math_op, 3),
    },
    [426] = {
        [ts_sym_expression] = SHIFT(427),
        [ts_sym_math_op] = SHIFT(380),
        [ts_sym_ternary] = SHIFT(380),
        [ts_sym_assignment] = SHIFT(380),
        [ts_sym_function_expression] = SHIFT(380),
        [ts_sym_function_call] = SHIFT(380),
        [ts_sym_property_access] = SHIFT(381),
        [ts_sym_literal] = SHIFT(384),
        [ts_sym_object] = SHIFT(385),
        [ts_sym_array] = SHIFT(385),
        [ts_sym__function] = SHIFT(386),
        [ts_sym_null] = SHIFT(385),
        [ts_sym_true] = SHIFT(385),
        [ts_sym_false] = SHIFT(385),
        [ts_sym_string] = SHIFT(385),
        [ts_sym_identifier] = SHIFT(381),
        [ts_sym_number] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token13] = SHIFT(406),
    },
    [427] = {
        [ts_aux_sym_token2] = SHIFT(20),
        [ts_aux_sym_token4] = SHIFT(428),
        [ts_aux_sym_token5] = SHIFT(367),
        [ts_aux_sym_token6] = SHIFT(367),
        [ts_aux_sym_token7] = SHIFT(369),
        [ts_aux_sym_token8] = SHIFT(369),
        [ts_aux_sym_token9] = SHIFT(371),
        [ts_aux_sym_token12] = SHIFT(375),
        [ts_aux_sym_token13] = SHIFT(377),
    },
    [428] = {
        [ts_sym_expression] = SHIFT(429),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [429] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [430] = {
        [ts_sym_identifier] = SHIFT(431),
    },
    [431] = {
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
    [432] = {
        [ts_sym_expression] = SHIFT(433),
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
        [ts_aux_sym_token0] = SHIFT(148),
        [ts_aux_sym_token13] = SHIFT(170),
    },
    [433] = {
        [ts_aux_sym_token2] = SHIFT(31),
        [ts_aux_sym_token5] = SHIFT(61),
        [ts_aux_sym_token6] = SHIFT(61),
        [ts_aux_sym_token7] = SHIFT(63),
        [ts_aux_sym_token8] = SHIFT(63),
        [ts_aux_sym_token9] = SHIFT(65),
        [ts_aux_sym_token12] = SHIFT(69),
        [ts_aux_sym_token13] = SHIFT(71),
        [ts_aux_sym_token14] = SHIFT(434),
    },
    [434] = {
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(437),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [437] = {
        [ts_sym_expression] = SHIFT(438),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [438] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [439] = {
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
    [440] = {
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
    [441] = {
        [ts_sym_formal_parameters] = SHIFT(442),
        [ts_sym_identifier] = SHIFT(448),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [442] = {
        [ts_sym_statement_block] = SHIFT(443),
        [ts_aux_sym_token0] = SHIFT(444),
    },
    [443] = {
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
    [444] = {
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
        [ts_builtin_sym_error] = SHIFT(445),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(447),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [445] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(446),
    },
    [446] = {
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
    [447] = {
        [ts_aux_sym_token1] = SHIFT(446),
    },
    [448] = {
        [ts_sym_formal_parameters] = SHIFT(449),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [449] = {
        [ts_sym_statement_block] = SHIFT(450),
        [ts_aux_sym_token0] = SHIFT(444),
    },
    [450] = {
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
    [451] = {
        [ts_builtin_sym_error] = SHIFT(452),
        [ts_sym_string] = SHIFT(455),
        [ts_sym_identifier] = SHIFT(455),
        [ts_aux_sym_token1] = SHIFT(460),
    },
    [452] = {
        [ts_aux_sym_object_repeat0] = SHIFT(453),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [453] = {
        [ts_aux_sym_token1] = SHIFT(454),
    },
    [454] = {
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
    [455] = {
        [ts_aux_sym_token4] = SHIFT(456),
    },
    [456] = {
        [ts_sym_expression] = SHIFT(457),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [457] = {
        [ts_aux_sym_object_repeat0] = SHIFT(458),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [458] = {
        [ts_aux_sym_token1] = SHIFT(459),
    },
    [459] = {
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
    [460] = {
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
    [461] = {
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_ternary] = SHIFT(177),
        [ts_sym_assignment] = SHIFT(177),
        [ts_sym_function_expression] = SHIFT(177),
        [ts_sym_function_call] = SHIFT(177),
        [ts_sym_property_access] = SHIFT(178),
        [ts_sym_literal] = SHIFT(181),
        [ts_sym_object] = SHIFT(182),
        [ts_sym_array] = SHIFT(182),
        [ts_builtin_sym_error] = SHIFT(465),
        [ts_sym__function] = SHIFT(183),
        [ts_sym_null] = SHIFT(182),
        [ts_sym_true] = SHIFT(182),
        [ts_sym_false] = SHIFT(182),
        [ts_sym_string] = SHIFT(182),
        [ts_sym_identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(182),
        [ts_aux_sym_token0] = SHIFT(318),
        [ts_aux_sym_token13] = SHIFT(328),
        [ts_aux_sym_token14] = SHIFT(466),
    },
    [462] = {
        [ts_aux_sym_array_repeat0] = SHIFT(463),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(135),
        [ts_aux_sym_token7] = SHIFT(137),
        [ts_aux_sym_token8] = SHIFT(137),
        [ts_aux_sym_token9] = SHIFT(139),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token12] = SHIFT(143),
        [ts_aux_sym_token13] = SHIFT(145),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [463] = {
        [ts_aux_sym_token14] = SHIFT(464),
    },
    [464] = {
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
    [465] = {
        [ts_aux_sym_array_repeat0] = SHIFT(463),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [466] = {
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
    [467] = {
        [ts_aux_sym_token3] = SHIFT(230),
    },
    [468] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [469] = {
        [ts_sym__terminator] = SHIFT(470),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [470] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [471] = {
        [ts_sym__terminator] = SHIFT(470),
    },
    [472] = {
        [ts_sym__terminator] = SHIFT(473),
    },
    [473] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [474] = {
        [ts_aux_sym_token2] = SHIFT(475),
    },
    [475] = {
        [ts_sym_var_declaration] = SHIFT(476),
        [ts_sym_expression_statement] = SHIFT(476),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(512),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [476] = {
        [ts_sym_expression_statement] = SHIFT(477),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [477] = {
        [ts_sym_expression] = SHIFT(478),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(505),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [478] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(479),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [479] = {
        [ts_sym_statement] = SHIFT(480),
        [ts_sym_statement_block] = SHIFT(468),
        [ts_sym_for_statement] = SHIFT(468),
        [ts_sym_if_statement] = SHIFT(468),
        [ts_sym_switch_statement] = SHIFT(468),
        [ts_sym_break_statement] = SHIFT(468),
        [ts_sym_var_declaration] = SHIFT(468),
        [ts_sym_expression_statement] = SHIFT(468),
        [ts_sym_expression] = SHIFT(469),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(471),
        [ts_sym__break] = SHIFT(472),
        [ts_sym__for] = SHIFT(474),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(481),
        [ts_sym__switch] = SHIFT(488),
        [ts_sym__var] = SHIFT(496),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(468),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [480] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [481] = {
        [ts_aux_sym_token2] = SHIFT(482),
    },
    [482] = {
        [ts_sym_expression] = SHIFT(483),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(504),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [483] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(484),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [484] = {
        [ts_sym_statement] = SHIFT(485),
        [ts_sym_statement_block] = SHIFT(468),
        [ts_sym_for_statement] = SHIFT(468),
        [ts_sym_if_statement] = SHIFT(468),
        [ts_sym_switch_statement] = SHIFT(468),
        [ts_sym_break_statement] = SHIFT(468),
        [ts_sym_var_declaration] = SHIFT(468),
        [ts_sym_expression_statement] = SHIFT(468),
        [ts_sym_expression] = SHIFT(469),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(471),
        [ts_sym__break] = SHIFT(472),
        [ts_sym__for] = SHIFT(474),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(481),
        [ts_sym__switch] = SHIFT(488),
        [ts_sym__var] = SHIFT(496),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(468),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [485] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(486),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [486] = {
        [ts_sym_statement] = SHIFT(487),
        [ts_sym_statement_block] = SHIFT(468),
        [ts_sym_for_statement] = SHIFT(468),
        [ts_sym_if_statement] = SHIFT(468),
        [ts_sym_switch_statement] = SHIFT(468),
        [ts_sym_break_statement] = SHIFT(468),
        [ts_sym_var_declaration] = SHIFT(468),
        [ts_sym_expression_statement] = SHIFT(468),
        [ts_sym_expression] = SHIFT(469),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(471),
        [ts_sym__break] = SHIFT(472),
        [ts_sym__for] = SHIFT(474),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(481),
        [ts_sym__switch] = SHIFT(488),
        [ts_sym__var] = SHIFT(496),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(468),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [487] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [488] = {
        [ts_aux_sym_token2] = SHIFT(489),
    },
    [489] = {
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(495),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [490] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(491),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [491] = {
        [ts_aux_sym_token0] = SHIFT(492),
    },
    [492] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(493),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [493] = {
        [ts_aux_sym_token1] = SHIFT(494),
    },
    [494] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [495] = {
        [ts_aux_sym_token3] = SHIFT(491),
    },
    [496] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(497),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(499),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [497] = {
        [ts_sym__terminator] = SHIFT(498),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [498] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [499] = {
        [ts_sym__terminator] = SHIFT(498),
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
    [500] = {
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
        [ts_builtin_sym_error] = SHIFT(501),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(299),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(503),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(338),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [501] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = SHIFT(502),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [502] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [503] = {
        [ts_aux_sym_token1] = SHIFT(502),
    },
    [504] = {
        [ts_aux_sym_token3] = SHIFT(484),
    },
    [505] = {
        [ts_aux_sym_token3] = SHIFT(479),
    },
    [506] = {
        [ts_sym__terminator] = SHIFT(507),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [507] = {
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
    [508] = {
        [ts_sym__terminator] = SHIFT(507),
    },
    [509] = {
        [ts_builtin_sym_error] = SHIFT(510),
        [ts_sym_string] = SHIFT(511),
        [ts_sym_identifier] = SHIFT(511),
        [ts_aux_sym_token1] = SHIFT(338),
    },
    [510] = {
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [511] = {
        [ts_aux_sym_token4] = SHIFT(300),
    },
    [512] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(513),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(515),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [513] = {
        [ts_sym__terminator] = SHIFT(514),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [514] = {
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
    [515] = {
        [ts_sym__terminator] = SHIFT(514),
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
    [516] = {
        [ts_aux_sym_token3] = SHIFT(223),
    },
    [517] = {
        [ts_aux_sym_token3] = SHIFT(218),
    },
    [518] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [519] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
    },
    [520] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [521] = {
        [ts_aux_sym_token1] = SHIFT(522),
    },
    [522] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [523] = {
        [ts_aux_sym_token3] = SHIFT(200),
    },
    [524] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [525] = {
        [ts_sym__terminator] = SHIFT(526),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [526] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [527] = {
        [ts_sym__terminator] = SHIFT(526),
    },
    [528] = {
        [ts_sym__terminator] = SHIFT(529),
    },
    [529] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [530] = {
        [ts_aux_sym_token2] = SHIFT(531),
    },
    [531] = {
        [ts_sym_var_declaration] = SHIFT(532),
        [ts_sym_expression_statement] = SHIFT(532),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(512),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [532] = {
        [ts_sym_expression_statement] = SHIFT(533),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [533] = {
        [ts_sym_expression] = SHIFT(534),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(561),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [534] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(535),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [535] = {
        [ts_sym_statement] = SHIFT(536),
        [ts_sym_statement_block] = SHIFT(524),
        [ts_sym_for_statement] = SHIFT(524),
        [ts_sym_if_statement] = SHIFT(524),
        [ts_sym_switch_statement] = SHIFT(524),
        [ts_sym_break_statement] = SHIFT(524),
        [ts_sym_var_declaration] = SHIFT(524),
        [ts_sym_expression_statement] = SHIFT(524),
        [ts_sym_expression] = SHIFT(525),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(527),
        [ts_sym__break] = SHIFT(528),
        [ts_sym__for] = SHIFT(530),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(537),
        [ts_sym__switch] = SHIFT(544),
        [ts_sym__var] = SHIFT(552),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(524),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(556),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [536] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [537] = {
        [ts_aux_sym_token2] = SHIFT(538),
    },
    [538] = {
        [ts_sym_expression] = SHIFT(539),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(560),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [539] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(540),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [540] = {
        [ts_sym_statement] = SHIFT(541),
        [ts_sym_statement_block] = SHIFT(524),
        [ts_sym_for_statement] = SHIFT(524),
        [ts_sym_if_statement] = SHIFT(524),
        [ts_sym_switch_statement] = SHIFT(524),
        [ts_sym_break_statement] = SHIFT(524),
        [ts_sym_var_declaration] = SHIFT(524),
        [ts_sym_expression_statement] = SHIFT(524),
        [ts_sym_expression] = SHIFT(525),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(527),
        [ts_sym__break] = SHIFT(528),
        [ts_sym__for] = SHIFT(530),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(537),
        [ts_sym__switch] = SHIFT(544),
        [ts_sym__var] = SHIFT(552),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(524),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(556),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [541] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(542),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [542] = {
        [ts_sym_statement] = SHIFT(543),
        [ts_sym_statement_block] = SHIFT(524),
        [ts_sym_for_statement] = SHIFT(524),
        [ts_sym_if_statement] = SHIFT(524),
        [ts_sym_switch_statement] = SHIFT(524),
        [ts_sym_break_statement] = SHIFT(524),
        [ts_sym_var_declaration] = SHIFT(524),
        [ts_sym_expression_statement] = SHIFT(524),
        [ts_sym_expression] = SHIFT(525),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(527),
        [ts_sym__break] = SHIFT(528),
        [ts_sym__for] = SHIFT(530),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(537),
        [ts_sym__switch] = SHIFT(544),
        [ts_sym__var] = SHIFT(552),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(524),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(556),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [543] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [544] = {
        [ts_aux_sym_token2] = SHIFT(545),
    },
    [545] = {
        [ts_sym_expression] = SHIFT(546),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(551),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [546] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(547),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [547] = {
        [ts_aux_sym_token0] = SHIFT(548),
    },
    [548] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(549),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [549] = {
        [ts_aux_sym_token1] = SHIFT(550),
    },
    [550] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [551] = {
        [ts_aux_sym_token3] = SHIFT(547),
    },
    [552] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(553),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(555),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [553] = {
        [ts_sym__terminator] = SHIFT(554),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [554] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [555] = {
        [ts_sym__terminator] = SHIFT(554),
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
    [556] = {
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
        [ts_builtin_sym_error] = SHIFT(557),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(299),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(559),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(338),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [557] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = SHIFT(558),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [558] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [559] = {
        [ts_aux_sym_token1] = SHIFT(558),
    },
    [560] = {
        [ts_aux_sym_token3] = SHIFT(540),
    },
    [561] = {
        [ts_aux_sym_token3] = SHIFT(535),
    },
    [562] = {
        [ts_aux_sym_token3] = SHIFT(192),
    },
    [563] = {
        [ts_aux_sym_token1] = SHIFT(188),
    },
    [564] = {
        [ts_sym_formal_parameters] = SHIFT(565),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [565] = {
        [ts_sym_statement_block] = SHIFT(566),
        [ts_aux_sym_token0] = SHIFT(186),
    },
    [566] = {
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
    [567] = {
        [ts_aux_sym_array_repeat0] = SHIFT(176),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [568] = {
        [ts_aux_sym_array_repeat0] = SHIFT(172),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [569] = {
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
    [570] = {
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
    [571] = {
        [ts_aux_sym_array_repeat0] = SHIFT(127),
        [ts_aux_sym_token11] = SHIFT(174),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [572] = {
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
    [573] = {
        [ts_aux_sym_token4] = SHIFT(574),
    },
    [574] = {
        [ts_sym_expression] = SHIFT(575),
        [ts_sym_math_op] = SHIFT(281),
        [ts_sym_ternary] = SHIFT(281),
        [ts_sym_assignment] = SHIFT(281),
        [ts_sym_function_expression] = SHIFT(281),
        [ts_sym_function_call] = SHIFT(281),
        [ts_sym_property_access] = SHIFT(282),
        [ts_sym_literal] = SHIFT(285),
        [ts_sym_object] = SHIFT(286),
        [ts_sym_array] = SHIFT(286),
        [ts_sym__function] = SHIFT(287),
        [ts_sym_null] = SHIFT(286),
        [ts_sym_true] = SHIFT(286),
        [ts_sym_false] = SHIFT(286),
        [ts_sym_string] = SHIFT(286),
        [ts_sym_identifier] = SHIFT(282),
        [ts_sym_number] = SHIFT(286),
        [ts_aux_sym_token0] = SHIFT(304),
        [ts_aux_sym_token13] = SHIFT(313),
    },
    [575] = {
        [ts_aux_sym_object_repeat0] = SHIFT(576),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(119),
        [ts_aux_sym_token5] = SHIFT(157),
        [ts_aux_sym_token6] = SHIFT(157),
        [ts_aux_sym_token7] = SHIFT(159),
        [ts_aux_sym_token8] = SHIFT(159),
        [ts_aux_sym_token9] = SHIFT(161),
        [ts_aux_sym_token11] = SHIFT(112),
        [ts_aux_sym_token12] = SHIFT(165),
        [ts_aux_sym_token13] = SHIFT(167),
    },
    [576] = {
        [ts_aux_sym_token1] = SHIFT(577),
    },
    [577] = {
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
    [578] = {
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
    [579] = {
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
    [580] = {
        [ts_sym_statement] = SHIFT(581),
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
        [ts_builtin_sym_error] = SHIFT(196),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [581] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [582] = {
        [ts_aux_sym_token3] = SHIFT(580),
    },
    [583] = {
        [ts_aux_sym_token1] = SHIFT(95),
    },
    [584] = {
        [ts_sym_formal_parameters] = SHIFT(585),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [585] = {
        [ts_sym_statement_block] = SHIFT(586),
        [ts_aux_sym_token0] = SHIFT(93),
    },
    [586] = {
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
    [587] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(588),
    },
    [588] = {
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
    [589] = {
        [ts_aux_sym_token1] = SHIFT(588),
    },
    [590] = {
        [ts_sym_formal_parameters] = SHIFT(591),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [591] = {
        [ts_sym_statement_block] = SHIFT(592),
        [ts_aux_sym_token0] = SHIFT(83),
    },
    [592] = {
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
    [593] = {
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
    [594] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [595] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_token1] = SHIFT(596),
    },
    [596] = {
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
    [597] = {
        [ts_aux_sym_token1] = SHIFT(596),
    },
    [598] = {
        [ts_sym_formal_parameters] = SHIFT(599),
        [ts_aux_sym_token2] = SHIFT(348),
    },
    [599] = {
        [ts_sym_statement_block] = SHIFT(600),
        [ts_aux_sym_token0] = SHIFT(44),
    },
    [600] = {
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
    [601] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(33),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [602] = {
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
    [603] = {
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
    [604] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(26),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [605] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(22),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [606] = {
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
    [607] = {
        [ts_sym_expression] = SHIFT(608),
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
        [ts_aux_sym_token0] = SHIFT(108),
        [ts_aux_sym_token13] = SHIFT(125),
    },
    [608] = {
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
    [609] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [610] = {
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
    [611] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(24),
    },
    [612] = {
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
    [613] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [614] = {
        [ts_sym__terminator] = SHIFT(615),
    },
    [615] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [616] = {
        [ts_aux_sym_token2] = SHIFT(617),
    },
    [617] = {
        [ts_sym_var_declaration] = SHIFT(618),
        [ts_sym_expression_statement] = SHIFT(618),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(512),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [618] = {
        [ts_sym_expression_statement] = SHIFT(619),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [619] = {
        [ts_sym_expression] = SHIFT(620),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(685),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [620] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(621),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [621] = {
        [ts_sym_statement] = SHIFT(622),
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
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym__break] = SHIFT(614),
        [ts_sym__for] = SHIFT(616),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(623),
        [ts_sym__switch] = SHIFT(630),
        [ts_sym__var] = SHIFT(638),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(642),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [622] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [623] = {
        [ts_aux_sym_token2] = SHIFT(624),
    },
    [624] = {
        [ts_sym_expression] = SHIFT(625),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(684),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [625] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(626),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [626] = {
        [ts_sym_statement] = SHIFT(627),
        [ts_sym_statement_block] = SHIFT(646),
        [ts_sym_for_statement] = SHIFT(646),
        [ts_sym_if_statement] = SHIFT(646),
        [ts_sym_switch_statement] = SHIFT(646),
        [ts_sym_break_statement] = SHIFT(646),
        [ts_sym_var_declaration] = SHIFT(646),
        [ts_sym_expression_statement] = SHIFT(646),
        [ts_sym_expression] = SHIFT(647),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(649),
        [ts_sym__break] = SHIFT(650),
        [ts_sym__for] = SHIFT(652),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(659),
        [ts_sym__switch] = SHIFT(666),
        [ts_sym__var] = SHIFT(674),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(646),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(678),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [627] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(628),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [628] = {
        [ts_sym_statement] = SHIFT(629),
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
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym__break] = SHIFT(614),
        [ts_sym__for] = SHIFT(616),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(623),
        [ts_sym__switch] = SHIFT(630),
        [ts_sym__var] = SHIFT(638),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(642),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [629] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [630] = {
        [ts_aux_sym_token2] = SHIFT(631),
    },
    [631] = {
        [ts_sym_expression] = SHIFT(632),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(637),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [632] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(633),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [633] = {
        [ts_aux_sym_token0] = SHIFT(634),
    },
    [634] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(635),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [635] = {
        [ts_aux_sym_token1] = SHIFT(636),
    },
    [636] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [637] = {
        [ts_aux_sym_token3] = SHIFT(633),
    },
    [638] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(639),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(641),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [639] = {
        [ts_sym__terminator] = SHIFT(640),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [640] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [641] = {
        [ts_sym__terminator] = SHIFT(640),
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
    [642] = {
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
        [ts_builtin_sym_error] = SHIFT(643),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(299),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(645),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(338),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [643] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = SHIFT(644),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [644] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [645] = {
        [ts_aux_sym_token1] = SHIFT(644),
    },
    [646] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
    },
    [647] = {
        [ts_sym__terminator] = SHIFT(648),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(49),
        [ts_aux_sym_token6] = SHIFT(49),
        [ts_aux_sym_token7] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(51),
        [ts_aux_sym_token9] = SHIFT(53),
        [ts_aux_sym_token12] = SHIFT(57),
        [ts_aux_sym_token13] = SHIFT(59),
    },
    [648] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
    },
    [649] = {
        [ts_sym__terminator] = SHIFT(648),
    },
    [650] = {
        [ts_sym__terminator] = SHIFT(651),
    },
    [651] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
    },
    [652] = {
        [ts_aux_sym_token2] = SHIFT(653),
    },
    [653] = {
        [ts_sym_var_declaration] = SHIFT(654),
        [ts_sym_expression_statement] = SHIFT(654),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__var] = SHIFT(512),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [654] = {
        [ts_sym_expression_statement] = SHIFT(655),
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(508),
        [ts_sym__function] = SHIFT(90),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(509),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [655] = {
        [ts_sym_expression] = SHIFT(656),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(683),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [656] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(657),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [657] = {
        [ts_sym_statement] = SHIFT(658),
        [ts_sym_statement_block] = SHIFT(646),
        [ts_sym_for_statement] = SHIFT(646),
        [ts_sym_if_statement] = SHIFT(646),
        [ts_sym_switch_statement] = SHIFT(646),
        [ts_sym_break_statement] = SHIFT(646),
        [ts_sym_var_declaration] = SHIFT(646),
        [ts_sym_expression_statement] = SHIFT(646),
        [ts_sym_expression] = SHIFT(647),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(649),
        [ts_sym__break] = SHIFT(650),
        [ts_sym__for] = SHIFT(652),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(659),
        [ts_sym__switch] = SHIFT(666),
        [ts_sym__var] = SHIFT(674),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(646),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(678),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [658] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
    },
    [659] = {
        [ts_aux_sym_token2] = SHIFT(660),
    },
    [660] = {
        [ts_sym_expression] = SHIFT(661),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(682),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [661] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(662),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [662] = {
        [ts_sym_statement] = SHIFT(663),
        [ts_sym_statement_block] = SHIFT(646),
        [ts_sym_for_statement] = SHIFT(646),
        [ts_sym_if_statement] = SHIFT(646),
        [ts_sym_switch_statement] = SHIFT(646),
        [ts_sym_break_statement] = SHIFT(646),
        [ts_sym_var_declaration] = SHIFT(646),
        [ts_sym_expression_statement] = SHIFT(646),
        [ts_sym_expression] = SHIFT(647),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(649),
        [ts_sym__break] = SHIFT(650),
        [ts_sym__for] = SHIFT(652),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(659),
        [ts_sym__switch] = SHIFT(666),
        [ts_sym__var] = SHIFT(674),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(646),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(678),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [663] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(664),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
    },
    [664] = {
        [ts_sym_statement] = SHIFT(665),
        [ts_sym_statement_block] = SHIFT(646),
        [ts_sym_for_statement] = SHIFT(646),
        [ts_sym_if_statement] = SHIFT(646),
        [ts_sym_switch_statement] = SHIFT(646),
        [ts_sym_break_statement] = SHIFT(646),
        [ts_sym_var_declaration] = SHIFT(646),
        [ts_sym_expression_statement] = SHIFT(646),
        [ts_sym_expression] = SHIFT(647),
        [ts_sym_math_op] = SHIFT(84),
        [ts_sym_ternary] = SHIFT(84),
        [ts_sym_assignment] = SHIFT(84),
        [ts_sym_function_expression] = SHIFT(84),
        [ts_sym_function_call] = SHIFT(84),
        [ts_sym_property_access] = SHIFT(85),
        [ts_sym_literal] = SHIFT(88),
        [ts_sym_object] = SHIFT(89),
        [ts_sym_array] = SHIFT(89),
        [ts_builtin_sym_error] = SHIFT(649),
        [ts_sym__break] = SHIFT(650),
        [ts_sym__for] = SHIFT(652),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(659),
        [ts_sym__switch] = SHIFT(666),
        [ts_sym__var] = SHIFT(674),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(646),
        [ts_sym_string] = SHIFT(89),
        [ts_sym_identifier] = SHIFT(85),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_token0] = SHIFT(678),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [665] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
    },
    [666] = {
        [ts_aux_sym_token2] = SHIFT(667),
    },
    [667] = {
        [ts_sym_expression] = SHIFT(668),
        [ts_sym_math_op] = SHIFT(435),
        [ts_sym_ternary] = SHIFT(435),
        [ts_sym_assignment] = SHIFT(435),
        [ts_sym_function_expression] = SHIFT(435),
        [ts_sym_function_call] = SHIFT(435),
        [ts_sym_property_access] = SHIFT(436),
        [ts_sym_literal] = SHIFT(439),
        [ts_sym_object] = SHIFT(440),
        [ts_sym_array] = SHIFT(440),
        [ts_builtin_sym_error] = SHIFT(673),
        [ts_sym__function] = SHIFT(441),
        [ts_sym_null] = SHIFT(440),
        [ts_sym_true] = SHIFT(440),
        [ts_sym_false] = SHIFT(440),
        [ts_sym_string] = SHIFT(440),
        [ts_sym_identifier] = SHIFT(436),
        [ts_sym_number] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(451),
        [ts_aux_sym_token13] = SHIFT(461),
    },
    [668] = {
        [ts_aux_sym_token2] = SHIFT(103),
        [ts_aux_sym_token3] = SHIFT(669),
        [ts_aux_sym_token5] = SHIFT(422),
        [ts_aux_sym_token6] = SHIFT(422),
        [ts_aux_sym_token7] = SHIFT(424),
        [ts_aux_sym_token8] = SHIFT(424),
        [ts_aux_sym_token9] = SHIFT(426),
        [ts_aux_sym_token12] = SHIFT(430),
        [ts_aux_sym_token13] = SHIFT(432),
    },
    [669] = {
        [ts_aux_sym_token0] = SHIFT(670),
    },
    [670] = {
        [ts_sym_switch_case] = SHIFT(202),
        [ts_sym__case] = SHIFT(203),
        [ts_sym__default] = SHIFT(232),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(671),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [671] = {
        [ts_aux_sym_token1] = SHIFT(672),
    },
    [672] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
    },
    [673] = {
        [ts_aux_sym_token3] = SHIFT(669),
    },
    [674] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(255),
        [ts_sym_ternary] = SHIFT(255),
        [ts_sym_assignment] = SHIFT(675),
        [ts_sym_function_expression] = SHIFT(255),
        [ts_sym_function_call] = SHIFT(255),
        [ts_sym_property_access] = SHIFT(270),
        [ts_sym_literal] = SHIFT(259),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(677),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(272),
        [ts_aux_sym_token13] = SHIFT(357),
    },
    [675] = {
        [ts_sym__terminator] = SHIFT(676),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
    },
    [676] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
    },
    [677] = {
        [ts_sym__terminator] = SHIFT(676),
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
    [678] = {
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
        [ts_builtin_sym_error] = SHIFT(679),
        [ts_sym__break] = SHIFT(96),
        [ts_sym__for] = SHIFT(98),
        [ts_sym__function] = SHIFT(90),
        [ts_sym__if] = SHIFT(189),
        [ts_sym__switch] = SHIFT(197),
        [ts_sym__var] = SHIFT(267),
        [ts_sym_null] = SHIFT(89),
        [ts_sym_true] = SHIFT(89),
        [ts_sym_false] = SHIFT(89),
        [ts_sym_comment] = SHIFT(46),
        [ts_sym_string] = SHIFT(299),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(89),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(681),
        [ts_aux_sym_token0] = SHIFT(294),
        [ts_aux_sym_token1] = SHIFT(338),
        [ts_aux_sym_token13] = SHIFT(339),
    },
    [679] = {
        [ts_sym__terminator] = SHIFT(48),
        [ts_aux_sym_object_repeat0] = SHIFT(296),
        [ts_aux_sym_token1] = SHIFT(680),
        [ts_aux_sym_token11] = SHIFT(112),
    },
    [680] = {
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
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
    },
    [681] = {
        [ts_aux_sym_token1] = SHIFT(680),
    },
    [682] = {
        [ts_aux_sym_token3] = SHIFT(662),
    },
    [683] = {
        [ts_aux_sym_token3] = SHIFT(657),
    },
    [684] = {
        [ts_aux_sym_token3] = SHIFT(626),
    },
    [685] = {
        [ts_aux_sym_token3] = SHIFT(621),
    },
    [686] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [687] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
