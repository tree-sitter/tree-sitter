#include "tree_sitter/parser.h"

#define STATE_COUNT 811
#define SYMBOL_COUNT 77

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
    ts_sym_return_statement = 12,
    ts_sym_delete_statement = 13,
    ts_sym_expression = 14,
    ts_sym_math_op = 15,
    ts_sym_bool_op = 16,
    ts_sym_ternary = 17,
    ts_sym_assignment = 18,
    ts_sym_function_expression = 19,
    ts_sym_function_call = 20,
    ts_sym_property_access = 21,
    ts_sym_formal_parameters = 22,
    ts_sym_literal = 23,
    ts_sym_object = 24,
    ts_sym_array = 25,
    ts_sym__delete = 26,
    ts_sym__return = 27,
    ts_sym__break = 28,
    ts_sym__case = 29,
    ts_sym__default = 30,
    ts_sym__else = 31,
    ts_sym__for = 32,
    ts_sym__function = 33,
    ts_sym__if = 34,
    ts_sym__switch = 35,
    ts_sym__var = 36,
    ts_sym_null = 37,
    ts_sym_true = 38,
    ts_sym_false = 39,
    ts_sym_comment = 40,
    ts_sym__terminator = 41,
    ts_sym_string = 42,
    ts_sym_identifier = 43,
    ts_sym_number = 44,
    ts_aux_sym_program_repeat0 = 45,
    ts_aux_sym_statement_block_repeat0 = 46,
    ts_aux_sym_switch_statement_repeat0 = 47,
    ts_aux_sym_switch_case_repeat0 = 48,
    ts_aux_sym_function_call_repeat0 = 49,
    ts_aux_sym_formal_parameters_repeat0 = 50,
    ts_aux_sym_object_repeat0 = 51,
    ts_aux_sym_array_repeat0 = 52,
    ts_aux_sym_token0 = 53,
    ts_aux_sym_token1 = 54,
    ts_aux_sym_token2 = 55,
    ts_aux_sym_token3 = 56,
    ts_aux_sym_token4 = 57,
    ts_aux_sym_token5 = 58,
    ts_aux_sym_token6 = 59,
    ts_aux_sym_token7 = 60,
    ts_aux_sym_token8 = 61,
    ts_aux_sym_token9 = 62,
    ts_aux_sym_token10 = 63,
    ts_aux_sym_token11 = 64,
    ts_aux_sym_token12 = 65,
    ts_aux_sym_token13 = 66,
    ts_aux_sym_token14 = 67,
    ts_aux_sym_token15 = 68,
    ts_aux_sym_token16 = 69,
    ts_aux_sym_token17 = 70,
    ts_aux_sym_token18 = 71,
    ts_aux_sym_token19 = 72,
    ts_aux_sym_token20 = 73,
    ts_aux_sym_token21 = 74,
    ts_aux_sym_token22 = 75,
    ts_aux_sym_token23 = 76,
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
    [ts_sym_return_statement] = "return_statement",
    [ts_sym_delete_statement] = "delete_statement",
    [ts_sym_expression] = "expression",
    [ts_sym_math_op] = "math_op",
    [ts_sym_bool_op] = "bool_op",
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
    [ts_sym__delete] = "_delete",
    [ts_sym__return] = "_return",
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
    [ts_aux_sym_token9] = "'&&'",
    [ts_aux_sym_token10] = "'||'",
    [ts_aux_sym_token11] = "'==='",
    [ts_aux_sym_token12] = "'=='",
    [ts_aux_sym_token13] = "'<='",
    [ts_aux_sym_token14] = "'<'",
    [ts_aux_sym_token15] = "'>='",
    [ts_aux_sym_token16] = "'>'",
    [ts_aux_sym_token17] = "'!'",
    [ts_aux_sym_token18] = "'?'",
    [ts_aux_sym_token19] = "'='",
    [ts_aux_sym_token20] = "','",
    [ts_aux_sym_token21] = "'.'",
    [ts_aux_sym_token22] = "'['",
    [ts_aux_sym_token23] = "']'",
};

HIDDEN_SYMBOLS = {
    [ts_sym__delete] = 1,
    [ts_sym__return] = 1,
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
    [ts_aux_sym_token15] = 1,
    [ts_aux_sym_token16] = 1,
    [ts_aux_sym_token17] = 1,
    [ts_aux_sym_token18] = 1,
    [ts_aux_sym_token19] = 1,
    [ts_aux_sym_token20] = 1,
    [ts_aux_sym_token21] = 1,
    [ts_aux_sym_token22] = 1,
    [ts_aux_sym_token23] = 1,
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
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'c') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'd')
                ADVANCE(22);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token17);
        case 4:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(7);
            LEX_ERROR();
        case 5:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(5);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(7);
            LEX_ERROR();
        case 6:
            ACCEPT_TOKEN(ts_sym_string);
        case 7:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(5);
            if (lookahead == '\"')
                ADVANCE(8);
            if (lookahead == '\\')
                ADVANCE(7);
            LEX_ERROR();
        case 8:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(5);
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym_string);
        case 9:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 10:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 11:
            if (lookahead == '/')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (!(lookahead == '\n'))
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym_comment);
        case 13:
            if (lookahead == '.')
                ADVANCE(14);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_number);
        case 14:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(15);
            ACCEPT_TOKEN(ts_sym_number);
        case 16:
            ACCEPT_TOKEN(ts_aux_sym_token22);
        case 17:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 18:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'k')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 21:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__break);
        case 22:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 23:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 24:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 26:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__delete);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(29);
            if (lookahead == 'o')
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_false);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__for);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'c')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'i')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'o')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__function);
        case 42:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__if);
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_null);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 52:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 53:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__return);
        case 54:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'v') ||
                ('x' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'w')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 55:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'i')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 56:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 57:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'c')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 58:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'h')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 59:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__switch);
        case 60:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 61:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 62:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 63:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_true);
        case 64:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(65);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__var);
        case 67:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 68:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '\n')
                ADVANCE(69);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '\n')
                ADVANCE(69);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 70:
            if (lookahead == '&')
                ADVANCE(71);
            LEX_ERROR();
        case 71:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 72:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 73:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 75:
            ACCEPT_TOKEN(ts_aux_sym_token21);
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 77:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 78:
            if (lookahead == '=')
                ADVANCE(79);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 79:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 80:
            if (lookahead == '=')
                ADVANCE(81);
            LEX_ERROR();
        case 81:
            if (lookahead == '=')
                ADVANCE(82);
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 83:
            if (lookahead == '=')
                ADVANCE(84);
            ACCEPT_TOKEN(ts_aux_sym_token16);
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 85:
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 86:
            if (lookahead == '|')
                ADVANCE(87);
            LEX_ERROR();
        case 87:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 88:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == ')')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 90:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 91:
            ACCEPT_TOKEN(ts_aux_sym_token20);
        case 92:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 93:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 94:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 95:
            if (lookahead == '=')
                ADVANCE(81);
            ACCEPT_TOKEN(ts_aux_sym_token19);
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(97);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(ts_aux_sym_token23);
        case 99:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'c') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'd')
                ADVANCE(22);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 100:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 101:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '\n')
                ADVANCE(102);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '\n')
                ADVANCE(102);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 103:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '\n')
                ADVANCE(105);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 105:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '\n')
                ADVANCE(105);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 106:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(106);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 107:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == ',')
                ADVANCE(91);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 110:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 112:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == ']')
                ADVANCE(98);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 114:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(115);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 115:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(29);
            if (lookahead == 'u')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 116:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 118:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 119:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\n')
                ADVANCE(120);
            if (lookahead == ';')
                ADVANCE(77);
            LEX_ERROR();
        case 120:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\n')
                ADVANCE(120);
            if (lookahead == ';')
                ADVANCE(77);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 121:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'c')
                ADVANCE(122);
            if (lookahead == 'd')
                ADVANCE(126);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 122:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(123);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 123:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(124);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 124:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 125:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__case);
        case 126:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(127);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 127:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(128);
            if (lookahead == 'l')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 128:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(129);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 129:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(130);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 130:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(131);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 131:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(132);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 132:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__default);
        case 133:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 134:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(115);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\n')
                ADVANCE(136);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\n')
                ADVANCE(136);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '\n')
                ADVANCE(138);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '\n')
                ADVANCE(138);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(80);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 141:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == ']')
                ADVANCE(98);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == ':')
                ADVANCE(93);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == 'f')
                ADVANCE(115);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 146:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == ')')
                ADVANCE(89);
            LEX_ERROR();
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '(')
                ADVANCE(10);
            LEX_ERROR();
        case 148:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            LEX_ERROR();
        case 149:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(149);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(76);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == '|')
                ADVANCE(86);
            LEX_ERROR();
        case 150:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == '\n')
                ADVANCE(151);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(115);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 151:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == '\n')
                ADVANCE(151);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(115);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == '{')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 152:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == 'c')
                ADVANCE(153);
            if (lookahead == 'd')
                ADVANCE(157);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 153:
            if (lookahead == 'a')
                ADVANCE(154);
            LEX_ERROR();
        case 154:
            if (lookahead == 's')
                ADVANCE(155);
            LEX_ERROR();
        case 155:
            if (lookahead == 'e')
                ADVANCE(156);
            LEX_ERROR();
        case 156:
            ACCEPT_TOKEN(ts_sym__case);
        case 157:
            if (lookahead == 'e')
                ADVANCE(158);
            LEX_ERROR();
        case 158:
            if (lookahead == 'f')
                ADVANCE(159);
            LEX_ERROR();
        case 159:
            if (lookahead == 'a')
                ADVANCE(160);
            LEX_ERROR();
        case 160:
            if (lookahead == 'u')
                ADVANCE(161);
            LEX_ERROR();
        case 161:
            if (lookahead == 'l')
                ADVANCE(162);
            LEX_ERROR();
        case 162:
            if (lookahead == 't')
                ADVANCE(163);
            LEX_ERROR();
        case 163:
            ACCEPT_TOKEN(ts_sym__default);
        case 164:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'c') ||
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'd')
                ADVANCE(22);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 165:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'c')
                ADVANCE(122);
            if (lookahead == 'd')
                ADVANCE(126);
            if (lookahead == 'e')
                ADVANCE(166);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 166:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(167);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 167:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(168);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 168:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(169);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 169:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__else);
        case 170:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'f')
                ADVANCE(115);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'c') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'd')
                ADVANCE(22);
            if (lookahead == 'e')
                ADVANCE(166);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 172:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(172);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            LEX_ERROR();
        case 173:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'c') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'd')
                ADVANCE(22);
            if (lookahead == 'e')
                ADVANCE(166);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            LEX_ERROR();
        case 174:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '\n')
                ADVANCE(175);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(176);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'c')
                ADVANCE(122);
            if (lookahead == 'd')
                ADVANCE(126);
            if (lookahead == 'e')
                ADVANCE(166);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '|')
                ADVANCE(86);
            if (lookahead == '}')
                ADVANCE(100);
            LEX_ERROR();
        case 175:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '\n')
                ADVANCE(175);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(176);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'c')
                ADVANCE(122);
            if (lookahead == 'd')
                ADVANCE(126);
            if (lookahead == 'e')
                ADVANCE(166);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '|')
                ADVANCE(86);
            if (lookahead == '}')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 176:
            if (lookahead == '/')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '\n')
                ADVANCE(175);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(89);
            if (lookahead == '*')
                ADVANCE(72);
            if (lookahead == '+')
                ADVANCE(73);
            if (lookahead == ',')
                ADVANCE(91);
            if (lookahead == '-')
                ADVANCE(74);
            if (lookahead == '.')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(176);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(13);
            if (lookahead == ':')
                ADVANCE(93);
            if (lookahead == ';')
                ADVANCE(77);
            if (lookahead == '<')
                ADVANCE(78);
            if (lookahead == '=')
                ADVANCE(95);
            if (lookahead == '>')
                ADVANCE(83);
            if (lookahead == '?')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(16);
            if (lookahead == ']')
                ADVANCE(98);
            if (lookahead == 'b')
                ADVANCE(17);
            if (lookahead == 'c')
                ADVANCE(122);
            if (lookahead == 'd')
                ADVANCE(126);
            if (lookahead == 'e')
                ADVANCE(166);
            if (lookahead == 'f')
                ADVANCE(28);
            if (lookahead == 'i')
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(44);
            if (lookahead == 'r')
                ADVANCE(48);
            if (lookahead == 's')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(60);
            if (lookahead == 'v')
                ADVANCE(64);
            if (lookahead == '{')
                ADVANCE(67);
            if (lookahead == '|')
                ADVANCE(86);
            if (lookahead == '}')
                ADVANCE(100);
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
    [4] = 68,
    [5] = 2,
    [6] = 114,
    [7] = 90,
    [8] = 88,
    [9] = 68,
    [10] = 114,
    [11] = 90,
    [12] = 88,
    [13] = 90,
    [14] = 134,
    [15] = 90,
    [16] = 134,
    [17] = 90,
    [18] = 134,
    [19] = 90,
    [20] = 134,
    [21] = 90,
    [22] = 134,
    [23] = 90,
    [24] = 134,
    [25] = 92,
    [26] = 114,
    [27] = 90,
    [28] = 88,
    [29] = 92,
    [30] = 134,
    [31] = 90,
    [32] = 88,
    [33] = 96,
    [34] = 94,
    [35] = 134,
    [36] = 97,
    [37] = 114,
    [38] = 90,
    [39] = 88,
    [40] = 97,
    [41] = 90,
    [42] = 94,
    [43] = 134,
    [44] = 90,
    [45] = 90,
    [46] = 148,
    [47] = 145,
    [48] = 90,
    [49] = 99,
    [50] = 99,
    [51] = 99,
    [52] = 68,
    [53] = 99,
    [54] = 134,
    [55] = 68,
    [56] = 134,
    [57] = 68,
    [58] = 134,
    [59] = 68,
    [60] = 134,
    [61] = 68,
    [62] = 134,
    [63] = 68,
    [64] = 134,
    [65] = 92,
    [66] = 134,
    [67] = 68,
    [68] = 96,
    [69] = 101,
    [70] = 134,
    [71] = 97,
    [72] = 134,
    [73] = 97,
    [74] = 134,
    [75] = 97,
    [76] = 134,
    [77] = 97,
    [78] = 134,
    [79] = 97,
    [80] = 134,
    [81] = 97,
    [82] = 134,
    [83] = 92,
    [84] = 134,
    [85] = 97,
    [86] = 96,
    [87] = 103,
    [88] = 134,
    [89] = 97,
    [90] = 103,
    [91] = 97,
    [92] = 103,
    [93] = 134,
    [94] = 97,
    [95] = 97,
    [96] = 148,
    [97] = 145,
    [98] = 97,
    [99] = 99,
    [100] = 68,
    [101] = 101,
    [102] = 134,
    [103] = 68,
    [104] = 68,
    [105] = 148,
    [106] = 145,
    [107] = 68,
    [108] = 99,
    [109] = 104,
    [110] = 68,
    [111] = 134,
    [112] = 106,
    [113] = 114,
    [114] = 90,
    [115] = 88,
    [116] = 106,
    [117] = 107,
    [118] = 143,
    [119] = 109,
    [120] = 108,
    [121] = 90,
    [122] = 172,
    [123] = 109,
    [124] = 108,
    [125] = 142,
    [126] = 134,
    [127] = 110,
    [128] = 108,
    [129] = 114,
    [130] = 90,
    [131] = 88,
    [132] = 110,
    [133] = 107,
    [134] = 134,
    [135] = 111,
    [136] = 114,
    [137] = 90,
    [138] = 88,
    [139] = 111,
    [140] = 107,
    [141] = 111,
    [142] = 134,
    [143] = 90,
    [144] = 144,
    [145] = 113,
    [146] = 112,
    [147] = 90,
    [148] = 114,
    [149] = 90,
    [150] = 88,
    [151] = 113,
    [152] = 107,
    [153] = 113,
    [154] = 134,
    [155] = 113,
    [156] = 134,
    [157] = 113,
    [158] = 134,
    [159] = 113,
    [160] = 134,
    [161] = 113,
    [162] = 134,
    [163] = 113,
    [164] = 134,
    [165] = 92,
    [166] = 134,
    [167] = 113,
    [168] = 96,
    [169] = 116,
    [170] = 134,
    [171] = 97,
    [172] = 116,
    [173] = 143,
    [174] = 109,
    [175] = 108,
    [176] = 97,
    [177] = 142,
    [178] = 134,
    [179] = 110,
    [180] = 108,
    [181] = 97,
    [182] = 134,
    [183] = 110,
    [184] = 134,
    [185] = 110,
    [186] = 134,
    [187] = 110,
    [188] = 134,
    [189] = 110,
    [190] = 134,
    [191] = 110,
    [192] = 134,
    [193] = 92,
    [194] = 134,
    [195] = 110,
    [196] = 96,
    [197] = 117,
    [198] = 134,
    [199] = 97,
    [200] = 117,
    [201] = 134,
    [202] = 111,
    [203] = 97,
    [204] = 134,
    [205] = 111,
    [206] = 134,
    [207] = 111,
    [208] = 134,
    [209] = 111,
    [210] = 134,
    [211] = 111,
    [212] = 134,
    [213] = 111,
    [214] = 134,
    [215] = 92,
    [216] = 134,
    [217] = 111,
    [218] = 96,
    [219] = 118,
    [220] = 134,
    [221] = 97,
    [222] = 118,
    [223] = 134,
    [224] = 97,
    [225] = 144,
    [226] = 113,
    [227] = 112,
    [228] = 97,
    [229] = 134,
    [230] = 113,
    [231] = 112,
    [232] = 113,
    [233] = 116,
    [234] = 134,
    [235] = 113,
    [236] = 113,
    [237] = 148,
    [238] = 145,
    [239] = 113,
    [240] = 99,
    [241] = 104,
    [242] = 113,
    [243] = 150,
    [244] = 68,
    [245] = 99,
    [246] = 99,
    [247] = 143,
    [248] = 109,
    [249] = 108,
    [250] = 68,
    [251] = 142,
    [252] = 134,
    [253] = 110,
    [254] = 108,
    [255] = 68,
    [256] = 110,
    [257] = 117,
    [258] = 134,
    [259] = 110,
    [260] = 110,
    [261] = 148,
    [262] = 145,
    [263] = 110,
    [264] = 99,
    [265] = 104,
    [266] = 110,
    [267] = 119,
    [268] = 99,
    [269] = 147,
    [270] = 170,
    [271] = 134,
    [272] = 134,
    [273] = 111,
    [274] = 164,
    [275] = 99,
    [276] = 119,
    [277] = 147,
    [278] = 134,
    [279] = 111,
    [280] = 164,
    [281] = 171,
    [282] = 164,
    [283] = 99,
    [284] = 147,
    [285] = 134,
    [286] = 111,
    [287] = 145,
    [288] = 152,
    [289] = 152,
    [290] = 134,
    [291] = 92,
    [292] = 121,
    [293] = 121,
    [294] = 121,
    [295] = 68,
    [296] = 121,
    [297] = 119,
    [298] = 134,
    [299] = 106,
    [300] = 101,
    [301] = 121,
    [302] = 134,
    [303] = 106,
    [304] = 134,
    [305] = 106,
    [306] = 134,
    [307] = 106,
    [308] = 134,
    [309] = 106,
    [310] = 134,
    [311] = 106,
    [312] = 134,
    [313] = 106,
    [314] = 134,
    [315] = 92,
    [316] = 134,
    [317] = 106,
    [318] = 96,
    [319] = 133,
    [320] = 134,
    [321] = 97,
    [322] = 133,
    [323] = 133,
    [324] = 106,
    [325] = 148,
    [326] = 145,
    [327] = 106,
    [328] = 99,
    [329] = 104,
    [330] = 106,
    [331] = 134,
    [332] = 106,
    [333] = 68,
    [334] = 99,
    [335] = 133,
    [336] = 101,
    [337] = 143,
    [338] = 109,
    [339] = 108,
    [340] = 106,
    [341] = 142,
    [342] = 134,
    [343] = 110,
    [344] = 108,
    [345] = 106,
    [346] = 143,
    [347] = 109,
    [348] = 108,
    [349] = 110,
    [350] = 142,
    [351] = 134,
    [352] = 110,
    [353] = 108,
    [354] = 110,
    [355] = 134,
    [356] = 111,
    [357] = 110,
    [358] = 111,
    [359] = 118,
    [360] = 134,
    [361] = 111,
    [362] = 111,
    [363] = 148,
    [364] = 145,
    [365] = 111,
    [366] = 99,
    [367] = 104,
    [368] = 111,
    [369] = 108,
    [370] = 99,
    [371] = 135,
    [372] = 99,
    [373] = 137,
    [374] = 139,
    [375] = 108,
    [376] = 68,
    [377] = 134,
    [378] = 111,
    [379] = 68,
    [380] = 143,
    [381] = 109,
    [382] = 108,
    [383] = 111,
    [384] = 142,
    [385] = 134,
    [386] = 110,
    [387] = 108,
    [388] = 111,
    [389] = 134,
    [390] = 110,
    [391] = 144,
    [392] = 113,
    [393] = 112,
    [394] = 110,
    [395] = 141,
    [396] = 143,
    [397] = 109,
    [398] = 108,
    [399] = 113,
    [400] = 142,
    [401] = 134,
    [402] = 110,
    [403] = 108,
    [404] = 113,
    [405] = 113,
    [406] = 134,
    [407] = 111,
    [408] = 113,
    [409] = 134,
    [410] = 111,
    [411] = 111,
    [412] = 134,
    [413] = 111,
    [414] = 144,
    [415] = 113,
    [416] = 112,
    [417] = 111,
    [418] = 141,
    [419] = 134,
    [420] = 113,
    [421] = 144,
    [422] = 113,
    [423] = 112,
    [424] = 113,
    [425] = 141,
    [426] = 113,
    [427] = 111,
    [428] = 110,
    [429] = 111,
    [430] = 134,
    [431] = 68,
    [432] = 144,
    [433] = 113,
    [434] = 112,
    [435] = 68,
    [436] = 141,
    [437] = 68,
    [438] = 147,
    [439] = 145,
    [440] = 111,
    [441] = 146,
    [442] = 107,
    [443] = 88,
    [444] = 145,
    [445] = 96,
    [446] = 107,
    [447] = 88,
    [448] = 145,
    [449] = 110,
    [450] = 106,
    [451] = 134,
    [452] = 111,
    [453] = 106,
    [454] = 134,
    [455] = 106,
    [456] = 144,
    [457] = 113,
    [458] = 112,
    [459] = 106,
    [460] = 141,
    [461] = 106,
    [462] = 108,
    [463] = 147,
    [464] = 145,
    [465] = 106,
    [466] = 134,
    [467] = 92,
    [468] = 134,
    [469] = 92,
    [470] = 134,
    [471] = 92,
    [472] = 134,
    [473] = 92,
    [474] = 134,
    [475] = 92,
    [476] = 134,
    [477] = 92,
    [478] = 134,
    [479] = 92,
    [480] = 96,
    [481] = 149,
    [482] = 134,
    [483] = 97,
    [484] = 149,
    [485] = 92,
    [486] = 149,
    [487] = 134,
    [488] = 92,
    [489] = 92,
    [490] = 148,
    [491] = 145,
    [492] = 92,
    [493] = 99,
    [494] = 104,
    [495] = 92,
    [496] = 108,
    [497] = 147,
    [498] = 145,
    [499] = 92,
    [500] = 143,
    [501] = 109,
    [502] = 108,
    [503] = 92,
    [504] = 142,
    [505] = 134,
    [506] = 110,
    [507] = 108,
    [508] = 92,
    [509] = 92,
    [510] = 134,
    [511] = 111,
    [512] = 92,
    [513] = 134,
    [514] = 92,
    [515] = 144,
    [516] = 113,
    [517] = 112,
    [518] = 92,
    [519] = 141,
    [520] = 92,
    [521] = 150,
    [522] = 68,
    [523] = 121,
    [524] = 121,
    [525] = 119,
    [526] = 121,
    [527] = 147,
    [528] = 170,
    [529] = 134,
    [530] = 134,
    [531] = 111,
    [532] = 164,
    [533] = 121,
    [534] = 147,
    [535] = 134,
    [536] = 111,
    [537] = 164,
    [538] = 165,
    [539] = 164,
    [540] = 121,
    [541] = 147,
    [542] = 134,
    [543] = 111,
    [544] = 145,
    [545] = 152,
    [546] = 142,
    [547] = 121,
    [548] = 134,
    [549] = 68,
    [550] = 121,
    [551] = 101,
    [552] = 152,
    [553] = 99,
    [554] = 135,
    [555] = 121,
    [556] = 108,
    [557] = 108,
    [558] = 121,
    [559] = 88,
    [560] = 165,
    [561] = 68,
    [562] = 165,
    [563] = 119,
    [564] = 134,
    [565] = 101,
    [566] = 165,
    [567] = 150,
    [568] = 68,
    [569] = 165,
    [570] = 165,
    [571] = 119,
    [572] = 165,
    [573] = 147,
    [574] = 170,
    [575] = 134,
    [576] = 134,
    [577] = 111,
    [578] = 164,
    [579] = 165,
    [580] = 147,
    [581] = 134,
    [582] = 111,
    [583] = 164,
    [584] = 165,
    [585] = 164,
    [586] = 165,
    [587] = 147,
    [588] = 134,
    [589] = 111,
    [590] = 145,
    [591] = 152,
    [592] = 108,
    [593] = 165,
    [594] = 88,
    [595] = 134,
    [596] = 68,
    [597] = 165,
    [598] = 101,
    [599] = 99,
    [600] = 135,
    [601] = 165,
    [602] = 108,
    [603] = 88,
    [604] = 88,
    [605] = 68,
    [606] = 134,
    [607] = 119,
    [608] = 134,
    [609] = 68,
    [610] = 134,
    [611] = 101,
    [612] = 88,
    [613] = 88,
    [614] = 152,
    [615] = 152,
    [616] = 108,
    [617] = 108,
    [618] = 99,
    [619] = 88,
    [620] = 171,
    [621] = 68,
    [622] = 171,
    [623] = 119,
    [624] = 134,
    [625] = 101,
    [626] = 171,
    [627] = 150,
    [628] = 68,
    [629] = 171,
    [630] = 171,
    [631] = 119,
    [632] = 171,
    [633] = 147,
    [634] = 170,
    [635] = 134,
    [636] = 134,
    [637] = 111,
    [638] = 164,
    [639] = 171,
    [640] = 147,
    [641] = 134,
    [642] = 111,
    [643] = 164,
    [644] = 171,
    [645] = 164,
    [646] = 171,
    [647] = 147,
    [648] = 134,
    [649] = 111,
    [650] = 145,
    [651] = 152,
    [652] = 108,
    [653] = 171,
    [654] = 88,
    [655] = 134,
    [656] = 68,
    [657] = 171,
    [658] = 101,
    [659] = 99,
    [660] = 135,
    [661] = 171,
    [662] = 108,
    [663] = 88,
    [664] = 88,
    [665] = 88,
    [666] = 88,
    [667] = 108,
    [668] = 147,
    [669] = 145,
    [670] = 110,
    [671] = 108,
    [672] = 147,
    [673] = 145,
    [674] = 113,
    [675] = 141,
    [676] = 141,
    [677] = 97,
    [678] = 97,
    [679] = 141,
    [680] = 90,
    [681] = 90,
    [682] = 110,
    [683] = 142,
    [684] = 134,
    [685] = 110,
    [686] = 108,
    [687] = 90,
    [688] = 90,
    [689] = 106,
    [690] = 101,
    [691] = 99,
    [692] = 108,
    [693] = 147,
    [694] = 145,
    [695] = 68,
    [696] = 104,
    [697] = 97,
    [698] = 108,
    [699] = 147,
    [700] = 145,
    [701] = 97,
    [702] = 101,
    [703] = 108,
    [704] = 104,
    [705] = 90,
    [706] = 108,
    [707] = 147,
    [708] = 145,
    [709] = 90,
    [710] = 107,
    [711] = 97,
    [712] = 94,
    [713] = 107,
    [714] = 107,
    [715] = 92,
    [716] = 134,
    [717] = 90,
    [718] = 107,
    [719] = 90,
    [720] = 107,
    [721] = 68,
    [722] = 119,
    [723] = 134,
    [724] = 101,
    [725] = 2,
    [726] = 150,
    [727] = 68,
    [728] = 2,
    [729] = 2,
    [730] = 119,
    [731] = 2,
    [732] = 147,
    [733] = 170,
    [734] = 134,
    [735] = 134,
    [736] = 111,
    [737] = 164,
    [738] = 2,
    [739] = 147,
    [740] = 134,
    [741] = 111,
    [742] = 164,
    [743] = 173,
    [744] = 164,
    [745] = 2,
    [746] = 147,
    [747] = 134,
    [748] = 111,
    [749] = 145,
    [750] = 152,
    [751] = 108,
    [752] = 2,
    [753] = 88,
    [754] = 134,
    [755] = 68,
    [756] = 2,
    [757] = 101,
    [758] = 99,
    [759] = 135,
    [760] = 2,
    [761] = 108,
    [762] = 173,
    [763] = 68,
    [764] = 173,
    [765] = 119,
    [766] = 134,
    [767] = 101,
    [768] = 173,
    [769] = 150,
    [770] = 68,
    [771] = 173,
    [772] = 173,
    [773] = 119,
    [774] = 173,
    [775] = 147,
    [776] = 170,
    [777] = 134,
    [778] = 134,
    [779] = 111,
    [780] = 164,
    [781] = 173,
    [782] = 147,
    [783] = 134,
    [784] = 111,
    [785] = 164,
    [786] = 173,
    [787] = 164,
    [788] = 173,
    [789] = 147,
    [790] = 134,
    [791] = 111,
    [792] = 145,
    [793] = 152,
    [794] = 108,
    [795] = 173,
    [796] = 88,
    [797] = 134,
    [798] = 68,
    [799] = 173,
    [800] = 101,
    [801] = 99,
    [802] = 135,
    [803] = 173,
    [804] = 108,
    [805] = 88,
    [806] = 88,
    [807] = 88,
    [808] = 88,
    [809] = 0,
    [810] = 0,
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
        [ts_sym_return_statement] = SHIFT(3),
        [ts_sym_delete_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(722),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__delete] = SHIFT(723),
        [ts_sym__return] = SHIFT(726),
        [ts_sym__break] = SHIFT(730),
        [ts_sym__for] = SHIFT(732),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(739),
        [ts_sym__switch] = SHIFT(746),
        [ts_sym__var] = SHIFT(754),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_program_repeat0] = SHIFT(810),
        [ts_aux_sym_token0] = SHIFT(758),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
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
        [ts_sym_return_statement] = SHIFT(3),
        [ts_sym_delete_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(722),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__delete] = SHIFT(723),
        [ts_sym__return] = SHIFT(726),
        [ts_sym__break] = SHIFT(730),
        [ts_sym__for] = SHIFT(732),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(739),
        [ts_sym__switch] = SHIFT(746),
        [ts_sym__var] = SHIFT(754),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_program_repeat0] = SHIFT(809),
        [ts_aux_sym_token0] = SHIFT(758),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [3] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_sym__delete] = REDUCE(ts_sym_statement, 1),
        [ts_sym__return] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [4] = {
        [ts_sym__terminator] = SHIFT(5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [5] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [6] = {
        [ts_sym_expression] = SHIFT(7),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(720),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(721),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
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
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
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
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
    },
    [10] = {
        [ts_sym_expression] = SHIFT(11),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(718),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(719),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
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
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
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
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
    },
    [14] = {
        [ts_sym_expression] = SHIFT(15),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [15] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [16] = {
        [ts_sym_expression] = SHIFT(17),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [17] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [18] = {
        [ts_sym_expression] = SHIFT(19),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [19] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [20] = {
        [ts_sym_expression] = SHIFT(21),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [21] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [22] = {
        [ts_sym_expression] = SHIFT(23),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [23] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [24] = {
        [ts_sym_expression] = SHIFT(25),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [25] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(716),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [26] = {
        [ts_sym_expression] = SHIFT(27),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(715),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [27] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(28),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [28] = {
        [ts_aux_sym_token3] = SHIFT(29),
    },
    [29] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
    },
    [30] = {
        [ts_sym_expression] = SHIFT(31),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(713),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [31] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(32),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [32] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 3),
    },
    [33] = {
        [ts_sym_identifier] = SHIFT(34),
    },
    [34] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
    },
    [35] = {
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [36] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(712),
    },
    [37] = {
        [ts_sym_expression] = SHIFT(38),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(710),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(711),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [38] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(39),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [39] = {
        [ts_aux_sym_token3] = SHIFT(40),
    },
    [40] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
    },
    [41] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [42] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(43),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [43] = {
        [ts_sym_expression] = SHIFT(44),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [44] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [45] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [46] = {
        [ts_sym_formal_parameters] = SHIFT(47),
        [ts_sym_identifier] = SHIFT(707),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [47] = {
        [ts_sym_statement_block] = SHIFT(48),
        [ts_aux_sym_token0] = SHIFT(49),
    },
    [48] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
    },
    [49] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(704),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(706),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [50] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(276),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(703),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [51] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__delete] = REDUCE(ts_sym_statement, 1),
        [ts_sym__return] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [52] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [53] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [54] = {
        [ts_sym_expression] = SHIFT(55),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [55] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [56] = {
        [ts_sym_expression] = SHIFT(57),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [57] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [58] = {
        [ts_sym_expression] = SHIFT(59),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [59] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [60] = {
        [ts_sym_expression] = SHIFT(61),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [61] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [62] = {
        [ts_sym_expression] = SHIFT(63),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [63] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [64] = {
        [ts_sym_expression] = SHIFT(65),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [65] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(66),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [66] = {
        [ts_sym_expression] = SHIFT(67),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [67] = {
        [ts_sym__terminator] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [68] = {
        [ts_sym_identifier] = SHIFT(69),
    },
    [69] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
    },
    [70] = {
        [ts_sym_expression] = SHIFT(71),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [71] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(702),
    },
    [72] = {
        [ts_sym_expression] = SHIFT(73),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [73] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [74] = {
        [ts_sym_expression] = SHIFT(75),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [75] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [76] = {
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [77] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [78] = {
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [79] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [80] = {
        [ts_sym_expression] = SHIFT(81),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [81] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [82] = {
        [ts_sym_expression] = SHIFT(83),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [83] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(84),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [84] = {
        [ts_sym_expression] = SHIFT(85),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [85] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = REDUCE(ts_sym_ternary, 5),
    },
    [86] = {
        [ts_sym_identifier] = SHIFT(87),
    },
    [87] = {
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
    },
    [88] = {
        [ts_sym_expression] = SHIFT(89),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [89] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(90),
    },
    [90] = {
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
    },
    [91] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [92] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(93),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [93] = {
        [ts_sym_expression] = SHIFT(94),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [94] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = REDUCE(ts_sym_assignment, 3),
    },
    [95] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_literal, 1),
    },
    [96] = {
        [ts_sym_formal_parameters] = SHIFT(97),
        [ts_sym_identifier] = SHIFT(699),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [97] = {
        [ts_sym_statement_block] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(99),
    },
    [98] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
    },
    [99] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(696),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(698),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [100] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [101] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [102] = {
        [ts_sym_expression] = SHIFT(103),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [103] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [104] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [105] = {
        [ts_sym_formal_parameters] = SHIFT(106),
        [ts_sym_identifier] = SHIFT(693),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [106] = {
        [ts_sym_statement_block] = SHIFT(107),
        [ts_aux_sym_token0] = SHIFT(108),
    },
    [107] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
    },
    [108] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(109),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(692),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [109] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(110),
    },
    [110] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [111] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(690),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [112] = {
        [ts_aux_sym_token2] = SHIFT(113),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = SHIFT(306),
        [ts_aux_sym_token8] = SHIFT(306),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [113] = {
        [ts_sym_expression] = SHIFT(114),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(117),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(689),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [114] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [115] = {
        [ts_aux_sym_token3] = SHIFT(116),
    },
    [116] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
    },
    [117] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(115),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [118] = {
        [ts_builtin_sym_error] = SHIFT(119),
        [ts_sym_string] = SHIFT(683),
        [ts_sym_identifier] = SHIFT(683),
        [ts_aux_sym_token1] = SHIFT(688),
    },
    [119] = {
        [ts_aux_sym_object_repeat0] = SHIFT(120),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [120] = {
        [ts_aux_sym_token1] = SHIFT(121),
    },
    [121] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
    },
    [122] = {
        [ts_builtin_sym_error] = SHIFT(123),
        [ts_sym_string] = SHIFT(125),
        [ts_sym_identifier] = SHIFT(125),
    },
    [123] = {
        [ts_aux_sym_object_repeat0] = SHIFT(124),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [124] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [125] = {
        [ts_aux_sym_token4] = SHIFT(126),
    },
    [126] = {
        [ts_sym_expression] = SHIFT(127),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [127] = {
        [ts_aux_sym_object_repeat0] = SHIFT(128),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [128] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [129] = {
        [ts_sym_expression] = SHIFT(130),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(133),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(682),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
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
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [131] = {
        [ts_aux_sym_token3] = SHIFT(132),
    },
    [132] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
    },
    [133] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(131),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [134] = {
        [ts_sym_expression] = SHIFT(135),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [135] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(681),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [136] = {
        [ts_sym_expression] = SHIFT(137),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(140),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(141),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [137] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(138),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [138] = {
        [ts_aux_sym_token3] = SHIFT(139),
    },
    [139] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
    },
    [140] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(138),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [141] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
    },
    [142] = {
        [ts_sym_expression] = SHIFT(143),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [143] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [144] = {
        [ts_sym_expression] = SHIFT(145),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(679),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(680),
    },
    [145] = {
        [ts_aux_sym_array_repeat0] = SHIFT(146),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [146] = {
        [ts_aux_sym_token23] = SHIFT(147),
    },
    [147] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
    },
    [148] = {
        [ts_sym_expression] = SHIFT(149),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_builtin_sym_error] = SHIFT(152),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token3] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [149] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(150),
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [150] = {
        [ts_aux_sym_token3] = SHIFT(151),
    },
    [151] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
    },
    [152] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(150),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [153] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
    },
    [154] = {
        [ts_sym_expression] = SHIFT(155),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [155] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [156] = {
        [ts_sym_expression] = SHIFT(157),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [157] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [158] = {
        [ts_sym_expression] = SHIFT(159),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [159] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [160] = {
        [ts_sym_expression] = SHIFT(161),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [161] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [162] = {
        [ts_sym_expression] = SHIFT(163),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [163] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [164] = {
        [ts_sym_expression] = SHIFT(165),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [165] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(166),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [166] = {
        [ts_sym_expression] = SHIFT(167),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [167] = {
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_sym_ternary, 5),
    },
    [168] = {
        [ts_sym_identifier] = SHIFT(169),
    },
    [169] = {
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
    },
    [170] = {
        [ts_sym_expression] = SHIFT(171),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [171] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(172),
    },
    [172] = {
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
    },
    [173] = {
        [ts_builtin_sym_error] = SHIFT(174),
        [ts_sym_string] = SHIFT(177),
        [ts_sym_identifier] = SHIFT(177),
        [ts_aux_sym_token1] = SHIFT(678),
    },
    [174] = {
        [ts_aux_sym_object_repeat0] = SHIFT(175),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [175] = {
        [ts_aux_sym_token1] = SHIFT(176),
    },
    [176] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
    },
    [177] = {
        [ts_aux_sym_token4] = SHIFT(178),
    },
    [178] = {
        [ts_sym_expression] = SHIFT(179),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [179] = {
        [ts_aux_sym_object_repeat0] = SHIFT(180),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [180] = {
        [ts_aux_sym_token1] = SHIFT(181),
    },
    [181] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
    },
    [182] = {
        [ts_sym_expression] = SHIFT(183),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [183] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [184] = {
        [ts_sym_expression] = SHIFT(185),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [185] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [186] = {
        [ts_sym_expression] = SHIFT(187),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [187] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [188] = {
        [ts_sym_expression] = SHIFT(189),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [189] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [190] = {
        [ts_sym_expression] = SHIFT(191),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [191] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [192] = {
        [ts_sym_expression] = SHIFT(193),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [193] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(194),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [194] = {
        [ts_sym_expression] = SHIFT(195),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [195] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [196] = {
        [ts_sym_identifier] = SHIFT(197),
    },
    [197] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
    },
    [198] = {
        [ts_sym_expression] = SHIFT(199),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [199] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(200),
    },
    [200] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
    },
    [201] = {
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [202] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(203),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [203] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
    },
    [204] = {
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [205] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [206] = {
        [ts_sym_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [207] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [208] = {
        [ts_sym_expression] = SHIFT(209),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [209] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [210] = {
        [ts_sym_expression] = SHIFT(211),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [211] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [212] = {
        [ts_sym_expression] = SHIFT(213),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [213] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [214] = {
        [ts_sym_expression] = SHIFT(215),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [215] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(216),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [216] = {
        [ts_sym_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [217] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [218] = {
        [ts_sym_identifier] = SHIFT(219),
    },
    [219] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
    },
    [220] = {
        [ts_sym_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [221] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(222),
    },
    [222] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
    },
    [223] = {
        [ts_sym_expression] = SHIFT(224),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [224] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
    },
    [225] = {
        [ts_sym_expression] = SHIFT(226),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(676),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(677),
    },
    [226] = {
        [ts_aux_sym_array_repeat0] = SHIFT(227),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [227] = {
        [ts_aux_sym_token23] = SHIFT(228),
    },
    [228] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
    },
    [229] = {
        [ts_sym_expression] = SHIFT(230),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(675),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [230] = {
        [ts_aux_sym_array_repeat0] = SHIFT(231),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [231] = {
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [232] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [233] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(234),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [234] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [235] = {
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_sym_assignment, 3),
    },
    [236] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_literal, 1),
    },
    [237] = {
        [ts_sym_formal_parameters] = SHIFT(238),
        [ts_sym_identifier] = SHIFT(672),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [238] = {
        [ts_sym_statement_block] = SHIFT(239),
        [ts_aux_sym_token0] = SHIFT(240),
    },
    [239] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
    },
    [240] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(241),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(671),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [241] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(242),
    },
    [242] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
    },
    [243] = {
        [ts_sym_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym__terminator] = SHIFT(246),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [244] = {
        [ts_sym__terminator] = SHIFT(245),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [245] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [246] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [247] = {
        [ts_builtin_sym_error] = SHIFT(248),
        [ts_sym_string] = SHIFT(251),
        [ts_sym_identifier] = SHIFT(251),
        [ts_aux_sym_token1] = SHIFT(376),
    },
    [248] = {
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [249] = {
        [ts_aux_sym_token1] = SHIFT(250),
    },
    [250] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
    },
    [251] = {
        [ts_aux_sym_token4] = SHIFT(252),
    },
    [252] = {
        [ts_sym_expression] = SHIFT(253),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [253] = {
        [ts_aux_sym_object_repeat0] = SHIFT(254),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [254] = {
        [ts_aux_sym_token1] = SHIFT(255),
    },
    [255] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
    },
    [256] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [257] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(258),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [258] = {
        [ts_sym_expression] = SHIFT(259),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [259] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [260] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [261] = {
        [ts_sym_formal_parameters] = SHIFT(262),
        [ts_sym_identifier] = SHIFT(668),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [262] = {
        [ts_sym_statement_block] = SHIFT(263),
        [ts_aux_sym_token0] = SHIFT(264),
    },
    [263] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
    },
    [264] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(265),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(667),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [265] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(266),
    },
    [266] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [267] = {
        [ts_sym__terminator] = SHIFT(268),
    },
    [268] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [269] = {
        [ts_aux_sym_token2] = SHIFT(270),
    },
    [270] = {
        [ts_sym_var_declaration] = SHIFT(271),
        [ts_sym_expression_statement] = SHIFT(271),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__var] = SHIFT(608),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [271] = {
        [ts_sym_expression_statement] = SHIFT(272),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [272] = {
        [ts_sym_expression] = SHIFT(273),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(666),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [273] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(274),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [274] = {
        [ts_sym_statement] = SHIFT(275),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(276),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [275] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [276] = {
        [ts_sym__terminator] = SHIFT(53),
    },
    [277] = {
        [ts_aux_sym_token2] = SHIFT(278),
    },
    [278] = {
        [ts_sym_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(665),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [279] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(280),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [280] = {
        [ts_sym_statement] = SHIFT(281),
        [ts_sym_statement_block] = SHIFT(620),
        [ts_sym_for_statement] = SHIFT(620),
        [ts_sym_if_statement] = SHIFT(620),
        [ts_sym_switch_statement] = SHIFT(620),
        [ts_sym_break_statement] = SHIFT(620),
        [ts_sym_var_declaration] = SHIFT(620),
        [ts_sym_expression_statement] = SHIFT(620),
        [ts_sym_return_statement] = SHIFT(620),
        [ts_sym_delete_statement] = SHIFT(620),
        [ts_sym_expression] = SHIFT(621),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(623),
        [ts_sym__delete] = SHIFT(624),
        [ts_sym__return] = SHIFT(627),
        [ts_sym__break] = SHIFT(631),
        [ts_sym__for] = SHIFT(633),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(640),
        [ts_sym__switch] = SHIFT(647),
        [ts_sym__var] = SHIFT(655),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(620),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(659),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [281] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(282),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [282] = {
        [ts_sym_statement] = SHIFT(283),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(276),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [283] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [284] = {
        [ts_aux_sym_token2] = SHIFT(285),
    },
    [285] = {
        [ts_sym_expression] = SHIFT(286),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(619),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [286] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(287),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [287] = {
        [ts_aux_sym_token0] = SHIFT(288),
    },
    [288] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(617),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [289] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(616),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [290] = {
        [ts_sym_expression] = SHIFT(291),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [291] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(292),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [292] = {
        [ts_sym_statement] = SHIFT(293),
        [ts_sym_statement_block] = SHIFT(294),
        [ts_sym_for_statement] = SHIFT(294),
        [ts_sym_if_statement] = SHIFT(294),
        [ts_sym_switch_statement] = SHIFT(294),
        [ts_sym_break_statement] = SHIFT(294),
        [ts_sym_var_declaration] = SHIFT(294),
        [ts_sym_expression_statement] = SHIFT(294),
        [ts_sym_return_statement] = SHIFT(294),
        [ts_sym_delete_statement] = SHIFT(294),
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(297),
        [ts_sym__delete] = SHIFT(298),
        [ts_sym__return] = SHIFT(521),
        [ts_sym__break] = SHIFT(525),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(527),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(534),
        [ts_sym__switch] = SHIFT(541),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(294),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(615),
        [ts_aux_sym_token0] = SHIFT(553),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [293] = {
        [ts_sym_statement] = SHIFT(293),
        [ts_sym_statement_block] = SHIFT(294),
        [ts_sym_for_statement] = SHIFT(294),
        [ts_sym_if_statement] = SHIFT(294),
        [ts_sym_switch_statement] = SHIFT(294),
        [ts_sym_break_statement] = SHIFT(294),
        [ts_sym_var_declaration] = SHIFT(294),
        [ts_sym_expression_statement] = SHIFT(294),
        [ts_sym_return_statement] = SHIFT(294),
        [ts_sym_delete_statement] = SHIFT(294),
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(297),
        [ts_sym__delete] = SHIFT(298),
        [ts_sym__return] = SHIFT(521),
        [ts_sym__break] = SHIFT(525),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(527),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(534),
        [ts_sym__switch] = SHIFT(541),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(294),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(614),
        [ts_aux_sym_token0] = SHIFT(553),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [294] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__delete] = REDUCE(ts_sym_statement, 1),
        [ts_sym__return] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [295] = {
        [ts_sym__terminator] = SHIFT(296),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [296] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [297] = {
        [ts_sym__terminator] = SHIFT(296),
    },
    [298] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(300),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [299] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [300] = {
        [ts_sym__terminator] = SHIFT(301),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [301] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__case] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__default] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [302] = {
        [ts_sym_expression] = SHIFT(303),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [303] = {
        [ts_aux_sym_token2] = SHIFT(113),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = SHIFT(306),
        [ts_aux_sym_token8] = SHIFT(306),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token21] = SHIFT(318),
        [ts_aux_sym_token22] = SHIFT(320),
    },
    [304] = {
        [ts_sym_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [305] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [306] = {
        [ts_sym_expression] = SHIFT(307),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [307] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = SHIFT(306),
        [ts_aux_sym_token8] = SHIFT(306),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [308] = {
        [ts_sym_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [309] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [310] = {
        [ts_sym_expression] = SHIFT(311),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [311] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [312] = {
        [ts_sym_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [313] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [314] = {
        [ts_sym_expression] = SHIFT(315),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [315] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(316),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [316] = {
        [ts_sym_expression] = SHIFT(317),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [317] = {
        [ts_aux_sym_token2] = SHIFT(113),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = SHIFT(306),
        [ts_aux_sym_token8] = SHIFT(306),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token21] = SHIFT(318),
        [ts_aux_sym_token22] = SHIFT(320),
    },
    [318] = {
        [ts_sym_identifier] = SHIFT(319),
    },
    [319] = {
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
    },
    [320] = {
        [ts_sym_expression] = SHIFT(321),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [321] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(322),
    },
    [322] = {
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
    },
    [323] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [324] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [325] = {
        [ts_sym_formal_parameters] = SHIFT(326),
        [ts_sym_identifier] = SHIFT(463),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [326] = {
        [ts_sym_statement_block] = SHIFT(327),
        [ts_aux_sym_token0] = SHIFT(328),
    },
    [327] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
    },
    [328] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(329),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(462),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [329] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(330),
    },
    [330] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [331] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(333),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(336),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [332] = {
        [ts_aux_sym_token2] = SHIFT(113),
        [ts_aux_sym_token5] = SHIFT(304),
        [ts_aux_sym_token6] = SHIFT(304),
        [ts_aux_sym_token7] = SHIFT(306),
        [ts_aux_sym_token8] = SHIFT(306),
        [ts_aux_sym_token9] = SHIFT(308),
        [ts_aux_sym_token10] = SHIFT(310),
        [ts_aux_sym_token11] = SHIFT(310),
        [ts_aux_sym_token12] = SHIFT(310),
        [ts_aux_sym_token13] = SHIFT(310),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = SHIFT(310),
        [ts_aux_sym_token16] = SHIFT(310),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token21] = SHIFT(318),
        [ts_aux_sym_token22] = SHIFT(320),
    },
    [333] = {
        [ts_sym__terminator] = SHIFT(334),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [334] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__delete] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__return] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [335] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [336] = {
        [ts_sym__terminator] = SHIFT(334),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [337] = {
        [ts_builtin_sym_error] = SHIFT(338),
        [ts_sym_string] = SHIFT(341),
        [ts_sym_identifier] = SHIFT(341),
        [ts_aux_sym_token1] = SHIFT(450),
    },
    [338] = {
        [ts_aux_sym_object_repeat0] = SHIFT(339),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [339] = {
        [ts_aux_sym_token1] = SHIFT(340),
    },
    [340] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
    },
    [341] = {
        [ts_aux_sym_token4] = SHIFT(342),
    },
    [342] = {
        [ts_sym_expression] = SHIFT(343),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [343] = {
        [ts_aux_sym_object_repeat0] = SHIFT(344),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [344] = {
        [ts_aux_sym_token1] = SHIFT(345),
    },
    [345] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
    },
    [346] = {
        [ts_builtin_sym_error] = SHIFT(347),
        [ts_sym_string] = SHIFT(350),
        [ts_sym_identifier] = SHIFT(350),
        [ts_aux_sym_token1] = SHIFT(449),
    },
    [347] = {
        [ts_aux_sym_object_repeat0] = SHIFT(348),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [348] = {
        [ts_aux_sym_token1] = SHIFT(349),
    },
    [349] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
    },
    [350] = {
        [ts_aux_sym_token4] = SHIFT(351),
    },
    [351] = {
        [ts_sym_expression] = SHIFT(352),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [352] = {
        [ts_aux_sym_object_repeat0] = SHIFT(353),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [353] = {
        [ts_aux_sym_token1] = SHIFT(354),
    },
    [354] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
    },
    [355] = {
        [ts_sym_expression] = SHIFT(356),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [356] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(357),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [357] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
    },
    [358] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [359] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(360),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [360] = {
        [ts_sym_expression] = SHIFT(361),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [361] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [362] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [363] = {
        [ts_sym_formal_parameters] = SHIFT(364),
        [ts_sym_identifier] = SHIFT(438),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [364] = {
        [ts_sym_statement_block] = SHIFT(365),
        [ts_aux_sym_token0] = SHIFT(366),
    },
    [365] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
    },
    [366] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(367),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(369),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [367] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(368),
    },
    [368] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [369] = {
        [ts_aux_sym_token1] = SHIFT(368),
    },
    [370] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(371),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(373),
        [ts_sym_identifier] = SHIFT(374),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(375),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = SHIFT(376),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [371] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = SHIFT(372),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [372] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__delete] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__return] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [373] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = SHIFT(252),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [374] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(252),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [375] = {
        [ts_aux_sym_token1] = SHIFT(372),
    },
    [376] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
    },
    [377] = {
        [ts_sym_expression] = SHIFT(378),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [378] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(379),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [379] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
    },
    [380] = {
        [ts_builtin_sym_error] = SHIFT(381),
        [ts_sym_string] = SHIFT(384),
        [ts_sym_identifier] = SHIFT(384),
        [ts_aux_sym_token1] = SHIFT(429),
    },
    [381] = {
        [ts_aux_sym_object_repeat0] = SHIFT(382),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [382] = {
        [ts_aux_sym_token1] = SHIFT(383),
    },
    [383] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
    },
    [384] = {
        [ts_aux_sym_token4] = SHIFT(385),
    },
    [385] = {
        [ts_sym_expression] = SHIFT(386),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [386] = {
        [ts_aux_sym_object_repeat0] = SHIFT(387),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [387] = {
        [ts_aux_sym_token1] = SHIFT(388),
    },
    [388] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
    },
    [389] = {
        [ts_sym_expression] = SHIFT(390),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [390] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [391] = {
        [ts_sym_expression] = SHIFT(392),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(395),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(428),
    },
    [392] = {
        [ts_aux_sym_array_repeat0] = SHIFT(393),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [393] = {
        [ts_aux_sym_token23] = SHIFT(394),
    },
    [394] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
    },
    [395] = {
        [ts_aux_sym_array_repeat0] = SHIFT(393),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
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
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [398] = {
        [ts_aux_sym_token1] = SHIFT(399),
    },
    [399] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
    },
    [400] = {
        [ts_aux_sym_token4] = SHIFT(401),
    },
    [401] = {
        [ts_sym_expression] = SHIFT(402),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [402] = {
        [ts_aux_sym_object_repeat0] = SHIFT(403),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [403] = {
        [ts_aux_sym_token1] = SHIFT(404),
    },
    [404] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
    },
    [405] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
    },
    [406] = {
        [ts_sym_expression] = SHIFT(407),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [407] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(408),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [408] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
    },
    [409] = {
        [ts_sym_expression] = SHIFT(410),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [410] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(411),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [411] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
    },
    [412] = {
        [ts_sym_expression] = SHIFT(413),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [413] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [414] = {
        [ts_sym_expression] = SHIFT(415),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(418),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(427),
    },
    [415] = {
        [ts_aux_sym_array_repeat0] = SHIFT(416),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [416] = {
        [ts_aux_sym_token23] = SHIFT(417),
    },
    [417] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
    },
    [418] = {
        [ts_aux_sym_array_repeat0] = SHIFT(416),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [419] = {
        [ts_sym_expression] = SHIFT(420),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
    },
    [420] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
    },
    [421] = {
        [ts_sym_expression] = SHIFT(422),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(425),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(426),
    },
    [422] = {
        [ts_aux_sym_array_repeat0] = SHIFT(423),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [423] = {
        [ts_aux_sym_token23] = SHIFT(424),
    },
    [424] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
    },
    [425] = {
        [ts_aux_sym_array_repeat0] = SHIFT(423),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [426] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
    },
    [427] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
    },
    [428] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
    },
    [429] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
    },
    [430] = {
        [ts_sym_expression] = SHIFT(431),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [431] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [432] = {
        [ts_sym_expression] = SHIFT(433),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(436),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(437),
    },
    [433] = {
        [ts_aux_sym_array_repeat0] = SHIFT(434),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [434] = {
        [ts_aux_sym_token23] = SHIFT(435),
    },
    [435] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
    },
    [436] = {
        [ts_aux_sym_array_repeat0] = SHIFT(434),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [437] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
    },
    [438] = {
        [ts_sym_formal_parameters] = SHIFT(439),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [439] = {
        [ts_sym_statement_block] = SHIFT(440),
        [ts_aux_sym_token0] = SHIFT(366),
    },
    [440] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
    },
    [441] = {
        [ts_sym_identifier] = SHIFT(442),
        [ts_aux_sym_token3] = SHIFT(448),
    },
    [442] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(443),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(445),
    },
    [443] = {
        [ts_aux_sym_token3] = SHIFT(444),
    },
    [444] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [445] = {
        [ts_sym_identifier] = SHIFT(446),
    },
    [446] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(447),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(445),
    },
    [447] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [448] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [449] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
    },
    [450] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
    },
    [451] = {
        [ts_sym_expression] = SHIFT(452),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [452] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(453),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [453] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
    },
    [454] = {
        [ts_sym_expression] = SHIFT(455),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(323),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [455] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(312),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [456] = {
        [ts_sym_expression] = SHIFT(457),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(460),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(461),
    },
    [457] = {
        [ts_aux_sym_array_repeat0] = SHIFT(458),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [458] = {
        [ts_aux_sym_token23] = SHIFT(459),
    },
    [459] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
    },
    [460] = {
        [ts_aux_sym_array_repeat0] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [461] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
    },
    [462] = {
        [ts_aux_sym_token1] = SHIFT(330),
    },
    [463] = {
        [ts_sym_formal_parameters] = SHIFT(464),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [464] = {
        [ts_sym_statement_block] = SHIFT(465),
        [ts_aux_sym_token0] = SHIFT(328),
    },
    [465] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
    },
    [466] = {
        [ts_sym_expression] = SHIFT(467),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [467] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [468] = {
        [ts_sym_expression] = SHIFT(469),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [469] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [470] = {
        [ts_sym_expression] = SHIFT(471),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [471] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [472] = {
        [ts_sym_expression] = SHIFT(473),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [473] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [474] = {
        [ts_sym_expression] = SHIFT(475),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [475] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [476] = {
        [ts_sym_expression] = SHIFT(477),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [477] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(478),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [478] = {
        [ts_sym_expression] = SHIFT(479),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [479] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [480] = {
        [ts_sym_identifier] = SHIFT(481),
    },
    [481] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
    },
    [482] = {
        [ts_sym_expression] = SHIFT(483),
        [ts_sym_math_op] = SHIFT(91),
        [ts_sym_bool_op] = SHIFT(91),
        [ts_sym_ternary] = SHIFT(91),
        [ts_sym_assignment] = SHIFT(91),
        [ts_sym_function_expression] = SHIFT(91),
        [ts_sym_function_call] = SHIFT(91),
        [ts_sym_property_access] = SHIFT(92),
        [ts_sym_literal] = SHIFT(91),
        [ts_sym_object] = SHIFT(95),
        [ts_sym_array] = SHIFT(95),
        [ts_sym__function] = SHIFT(96),
        [ts_sym_null] = SHIFT(95),
        [ts_sym_true] = SHIFT(95),
        [ts_sym_false] = SHIFT(95),
        [ts_sym_string] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(92),
        [ts_sym_number] = SHIFT(95),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token2] = SHIFT(201),
        [ts_aux_sym_token17] = SHIFT(223),
        [ts_aux_sym_token22] = SHIFT(225),
    },
    [483] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(72),
        [ts_aux_sym_token6] = SHIFT(72),
        [ts_aux_sym_token7] = SHIFT(74),
        [ts_aux_sym_token8] = SHIFT(74),
        [ts_aux_sym_token9] = SHIFT(76),
        [ts_aux_sym_token10] = SHIFT(78),
        [ts_aux_sym_token11] = SHIFT(78),
        [ts_aux_sym_token12] = SHIFT(78),
        [ts_aux_sym_token13] = SHIFT(78),
        [ts_aux_sym_token14] = SHIFT(80),
        [ts_aux_sym_token15] = SHIFT(78),
        [ts_aux_sym_token16] = SHIFT(78),
        [ts_aux_sym_token18] = SHIFT(82),
        [ts_aux_sym_token21] = SHIFT(86),
        [ts_aux_sym_token22] = SHIFT(88),
        [ts_aux_sym_token23] = SHIFT(484),
    },
    [484] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
    },
    [485] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [486] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(487),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [487] = {
        [ts_sym_expression] = SHIFT(488),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [488] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(466),
        [ts_aux_sym_token6] = SHIFT(466),
        [ts_aux_sym_token7] = SHIFT(468),
        [ts_aux_sym_token8] = SHIFT(468),
        [ts_aux_sym_token9] = SHIFT(470),
        [ts_aux_sym_token10] = SHIFT(472),
        [ts_aux_sym_token11] = SHIFT(472),
        [ts_aux_sym_token12] = SHIFT(472),
        [ts_aux_sym_token13] = SHIFT(472),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = SHIFT(472),
        [ts_aux_sym_token16] = SHIFT(472),
        [ts_aux_sym_token18] = SHIFT(476),
        [ts_aux_sym_token21] = SHIFT(480),
        [ts_aux_sym_token22] = SHIFT(482),
    },
    [489] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_literal, 1),
    },
    [490] = {
        [ts_sym_formal_parameters] = SHIFT(491),
        [ts_sym_identifier] = SHIFT(497),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [491] = {
        [ts_sym_statement_block] = SHIFT(492),
        [ts_aux_sym_token0] = SHIFT(493),
    },
    [492] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
    },
    [493] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(494),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(496),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [494] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(495),
    },
    [495] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [496] = {
        [ts_aux_sym_token1] = SHIFT(495),
    },
    [497] = {
        [ts_sym_formal_parameters] = SHIFT(498),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [498] = {
        [ts_sym_statement_block] = SHIFT(499),
        [ts_aux_sym_token0] = SHIFT(493),
    },
    [499] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
    },
    [500] = {
        [ts_builtin_sym_error] = SHIFT(501),
        [ts_sym_string] = SHIFT(504),
        [ts_sym_identifier] = SHIFT(504),
        [ts_aux_sym_token1] = SHIFT(509),
    },
    [501] = {
        [ts_aux_sym_object_repeat0] = SHIFT(502),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [502] = {
        [ts_aux_sym_token1] = SHIFT(503),
    },
    [503] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
    },
    [504] = {
        [ts_aux_sym_token4] = SHIFT(505),
    },
    [505] = {
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [506] = {
        [ts_aux_sym_object_repeat0] = SHIFT(507),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [507] = {
        [ts_aux_sym_token1] = SHIFT(508),
    },
    [508] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
    },
    [509] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
    },
    [510] = {
        [ts_sym_expression] = SHIFT(511),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [511] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(512),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [512] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
    },
    [513] = {
        [ts_sym_expression] = SHIFT(514),
        [ts_sym_math_op] = SHIFT(485),
        [ts_sym_bool_op] = SHIFT(485),
        [ts_sym_ternary] = SHIFT(485),
        [ts_sym_assignment] = SHIFT(485),
        [ts_sym_function_expression] = SHIFT(485),
        [ts_sym_function_call] = SHIFT(485),
        [ts_sym_property_access] = SHIFT(486),
        [ts_sym_literal] = SHIFT(485),
        [ts_sym_object] = SHIFT(489),
        [ts_sym_array] = SHIFT(489),
        [ts_sym__function] = SHIFT(490),
        [ts_sym_null] = SHIFT(489),
        [ts_sym_true] = SHIFT(489),
        [ts_sym_false] = SHIFT(489),
        [ts_sym_string] = SHIFT(489),
        [ts_sym_identifier] = SHIFT(486),
        [ts_sym_number] = SHIFT(489),
        [ts_aux_sym_token0] = SHIFT(500),
        [ts_aux_sym_token2] = SHIFT(510),
        [ts_aux_sym_token17] = SHIFT(513),
        [ts_aux_sym_token22] = SHIFT(515),
    },
    [514] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = SHIFT(474),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [515] = {
        [ts_sym_expression] = SHIFT(516),
        [ts_sym_math_op] = SHIFT(232),
        [ts_sym_bool_op] = SHIFT(232),
        [ts_sym_ternary] = SHIFT(232),
        [ts_sym_assignment] = SHIFT(232),
        [ts_sym_function_expression] = SHIFT(232),
        [ts_sym_function_call] = SHIFT(232),
        [ts_sym_property_access] = SHIFT(233),
        [ts_sym_literal] = SHIFT(232),
        [ts_sym_object] = SHIFT(236),
        [ts_sym_array] = SHIFT(236),
        [ts_builtin_sym_error] = SHIFT(519),
        [ts_sym__function] = SHIFT(237),
        [ts_sym_null] = SHIFT(236),
        [ts_sym_true] = SHIFT(236),
        [ts_sym_false] = SHIFT(236),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(233),
        [ts_sym_number] = SHIFT(236),
        [ts_aux_sym_token0] = SHIFT(396),
        [ts_aux_sym_token2] = SHIFT(406),
        [ts_aux_sym_token17] = SHIFT(419),
        [ts_aux_sym_token22] = SHIFT(421),
        [ts_aux_sym_token23] = SHIFT(520),
    },
    [516] = {
        [ts_aux_sym_array_repeat0] = SHIFT(517),
        [ts_aux_sym_token2] = SHIFT(148),
        [ts_aux_sym_token5] = SHIFT(154),
        [ts_aux_sym_token6] = SHIFT(154),
        [ts_aux_sym_token7] = SHIFT(156),
        [ts_aux_sym_token8] = SHIFT(156),
        [ts_aux_sym_token9] = SHIFT(158),
        [ts_aux_sym_token10] = SHIFT(160),
        [ts_aux_sym_token11] = SHIFT(160),
        [ts_aux_sym_token12] = SHIFT(160),
        [ts_aux_sym_token13] = SHIFT(160),
        [ts_aux_sym_token14] = SHIFT(162),
        [ts_aux_sym_token15] = SHIFT(160),
        [ts_aux_sym_token16] = SHIFT(160),
        [ts_aux_sym_token18] = SHIFT(164),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token21] = SHIFT(168),
        [ts_aux_sym_token22] = SHIFT(170),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [517] = {
        [ts_aux_sym_token23] = SHIFT(518),
    },
    [518] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
    },
    [519] = {
        [ts_aux_sym_array_repeat0] = SHIFT(517),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [520] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
    },
    [521] = {
        [ts_sym_expression] = SHIFT(522),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym__terminator] = SHIFT(524),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [522] = {
        [ts_sym__terminator] = SHIFT(523),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [523] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__case] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__default] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [524] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [525] = {
        [ts_sym__terminator] = SHIFT(526),
    },
    [526] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [527] = {
        [ts_aux_sym_token2] = SHIFT(528),
    },
    [528] = {
        [ts_sym_var_declaration] = SHIFT(529),
        [ts_sym_expression_statement] = SHIFT(529),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__var] = SHIFT(608),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [529] = {
        [ts_sym_expression_statement] = SHIFT(530),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [530] = {
        [ts_sym_expression] = SHIFT(531),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [531] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(532),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [532] = {
        [ts_sym_statement] = SHIFT(533),
        [ts_sym_statement_block] = SHIFT(294),
        [ts_sym_for_statement] = SHIFT(294),
        [ts_sym_if_statement] = SHIFT(294),
        [ts_sym_switch_statement] = SHIFT(294),
        [ts_sym_break_statement] = SHIFT(294),
        [ts_sym_var_declaration] = SHIFT(294),
        [ts_sym_expression_statement] = SHIFT(294),
        [ts_sym_return_statement] = SHIFT(294),
        [ts_sym_delete_statement] = SHIFT(294),
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(297),
        [ts_sym__delete] = SHIFT(298),
        [ts_sym__return] = SHIFT(521),
        [ts_sym__break] = SHIFT(525),
        [ts_sym__for] = SHIFT(527),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(534),
        [ts_sym__switch] = SHIFT(541),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(294),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(553),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [533] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [534] = {
        [ts_aux_sym_token2] = SHIFT(535),
    },
    [535] = {
        [ts_sym_expression] = SHIFT(536),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(612),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [536] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(537),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [537] = {
        [ts_sym_statement] = SHIFT(538),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_return_statement] = SHIFT(560),
        [ts_sym_delete_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(563),
        [ts_sym__delete] = SHIFT(564),
        [ts_sym__return] = SHIFT(567),
        [ts_sym__break] = SHIFT(571),
        [ts_sym__for] = SHIFT(573),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(580),
        [ts_sym__switch] = SHIFT(587),
        [ts_sym__var] = SHIFT(595),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(560),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(599),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [538] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(539),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [539] = {
        [ts_sym_statement] = SHIFT(540),
        [ts_sym_statement_block] = SHIFT(294),
        [ts_sym_for_statement] = SHIFT(294),
        [ts_sym_if_statement] = SHIFT(294),
        [ts_sym_switch_statement] = SHIFT(294),
        [ts_sym_break_statement] = SHIFT(294),
        [ts_sym_var_declaration] = SHIFT(294),
        [ts_sym_expression_statement] = SHIFT(294),
        [ts_sym_return_statement] = SHIFT(294),
        [ts_sym_delete_statement] = SHIFT(294),
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(297),
        [ts_sym__delete] = SHIFT(298),
        [ts_sym__return] = SHIFT(521),
        [ts_sym__break] = SHIFT(525),
        [ts_sym__for] = SHIFT(527),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(534),
        [ts_sym__switch] = SHIFT(541),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(294),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(553),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [540] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [541] = {
        [ts_aux_sym_token2] = SHIFT(542),
    },
    [542] = {
        [ts_sym_expression] = SHIFT(543),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(559),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [543] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(544),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [544] = {
        [ts_aux_sym_token0] = SHIFT(545),
    },
    [545] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(557),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [546] = {
        [ts_aux_sym_token4] = SHIFT(547),
    },
    [547] = {
        [ts_sym_statement] = SHIFT(293),
        [ts_sym_statement_block] = SHIFT(294),
        [ts_sym_for_statement] = SHIFT(294),
        [ts_sym_if_statement] = SHIFT(294),
        [ts_sym_switch_statement] = SHIFT(294),
        [ts_sym_break_statement] = SHIFT(294),
        [ts_sym_var_declaration] = SHIFT(294),
        [ts_sym_expression_statement] = SHIFT(294),
        [ts_sym_return_statement] = SHIFT(294),
        [ts_sym_delete_statement] = SHIFT(294),
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(297),
        [ts_sym__delete] = SHIFT(298),
        [ts_sym__return] = SHIFT(521),
        [ts_sym__break] = SHIFT(525),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(527),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(534),
        [ts_sym__switch] = SHIFT(541),
        [ts_sym__var] = SHIFT(548),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(294),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(552),
        [ts_aux_sym_token0] = SHIFT(553),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [548] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(549),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(551),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [549] = {
        [ts_sym__terminator] = SHIFT(550),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [550] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__delete] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__return] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [551] = {
        [ts_sym__terminator] = SHIFT(550),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [552] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
    },
    [553] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(554),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(373),
        [ts_sym_identifier] = SHIFT(374),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(556),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = SHIFT(376),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [554] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = SHIFT(555),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [555] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__delete] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__return] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [556] = {
        [ts_aux_sym_token1] = SHIFT(555),
    },
    [557] = {
        [ts_aux_sym_token1] = SHIFT(558),
    },
    [558] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_switch_statement, 7),
    },
    [559] = {
        [ts_aux_sym_token3] = SHIFT(544),
    },
    [560] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__delete] = REDUCE(ts_sym_statement, 1),
        [ts_sym__return] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [561] = {
        [ts_sym__terminator] = SHIFT(562),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [562] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [563] = {
        [ts_sym__terminator] = SHIFT(562),
    },
    [564] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(565),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [565] = {
        [ts_sym__terminator] = SHIFT(566),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [566] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__case] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__default] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__else] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [567] = {
        [ts_sym_expression] = SHIFT(568),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym__terminator] = SHIFT(570),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [568] = {
        [ts_sym__terminator] = SHIFT(569),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [569] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__case] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__default] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__else] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [570] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__case] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__default] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [571] = {
        [ts_sym__terminator] = SHIFT(572),
    },
    [572] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [573] = {
        [ts_aux_sym_token2] = SHIFT(574),
    },
    [574] = {
        [ts_sym_var_declaration] = SHIFT(575),
        [ts_sym_expression_statement] = SHIFT(575),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__var] = SHIFT(608),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [575] = {
        [ts_sym_expression_statement] = SHIFT(576),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [576] = {
        [ts_sym_expression] = SHIFT(577),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [577] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(578),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [578] = {
        [ts_sym_statement] = SHIFT(579),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_return_statement] = SHIFT(560),
        [ts_sym_delete_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(563),
        [ts_sym__delete] = SHIFT(564),
        [ts_sym__return] = SHIFT(567),
        [ts_sym__break] = SHIFT(571),
        [ts_sym__for] = SHIFT(573),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(580),
        [ts_sym__switch] = SHIFT(587),
        [ts_sym__var] = SHIFT(595),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(560),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(599),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [579] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [580] = {
        [ts_aux_sym_token2] = SHIFT(581),
    },
    [581] = {
        [ts_sym_expression] = SHIFT(582),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(603),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [582] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(583),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [583] = {
        [ts_sym_statement] = SHIFT(584),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_return_statement] = SHIFT(560),
        [ts_sym_delete_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(563),
        [ts_sym__delete] = SHIFT(564),
        [ts_sym__return] = SHIFT(567),
        [ts_sym__break] = SHIFT(571),
        [ts_sym__for] = SHIFT(573),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(580),
        [ts_sym__switch] = SHIFT(587),
        [ts_sym__var] = SHIFT(595),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(560),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(599),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [584] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(585),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [585] = {
        [ts_sym_statement] = SHIFT(586),
        [ts_sym_statement_block] = SHIFT(560),
        [ts_sym_for_statement] = SHIFT(560),
        [ts_sym_if_statement] = SHIFT(560),
        [ts_sym_switch_statement] = SHIFT(560),
        [ts_sym_break_statement] = SHIFT(560),
        [ts_sym_var_declaration] = SHIFT(560),
        [ts_sym_expression_statement] = SHIFT(560),
        [ts_sym_return_statement] = SHIFT(560),
        [ts_sym_delete_statement] = SHIFT(560),
        [ts_sym_expression] = SHIFT(561),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(563),
        [ts_sym__delete] = SHIFT(564),
        [ts_sym__return] = SHIFT(567),
        [ts_sym__break] = SHIFT(571),
        [ts_sym__for] = SHIFT(573),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(580),
        [ts_sym__switch] = SHIFT(587),
        [ts_sym__var] = SHIFT(595),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(560),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(599),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [586] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [587] = {
        [ts_aux_sym_token2] = SHIFT(588),
    },
    [588] = {
        [ts_sym_expression] = SHIFT(589),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(594),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [589] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(590),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [590] = {
        [ts_aux_sym_token0] = SHIFT(591),
    },
    [591] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(592),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [592] = {
        [ts_aux_sym_token1] = SHIFT(593),
    },
    [593] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_switch_statement, 7),
    },
    [594] = {
        [ts_aux_sym_token3] = SHIFT(590),
    },
    [595] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(596),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(598),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [596] = {
        [ts_sym__terminator] = SHIFT(597),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [597] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__delete] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__return] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [598] = {
        [ts_sym__terminator] = SHIFT(597),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [599] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(600),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(373),
        [ts_sym_identifier] = SHIFT(374),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(602),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = SHIFT(376),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [600] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = SHIFT(601),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [601] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__delete] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__return] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [602] = {
        [ts_aux_sym_token1] = SHIFT(601),
    },
    [603] = {
        [ts_aux_sym_token3] = SHIFT(583),
    },
    [604] = {
        [ts_aux_sym_token3] = SHIFT(578),
    },
    [605] = {
        [ts_sym__terminator] = SHIFT(606),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [606] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [607] = {
        [ts_sym__terminator] = SHIFT(606),
    },
    [608] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(609),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(611),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [609] = {
        [ts_sym__terminator] = SHIFT(610),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [610] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__function] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [611] = {
        [ts_sym__terminator] = SHIFT(610),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [612] = {
        [ts_aux_sym_token3] = SHIFT(537),
    },
    [613] = {
        [ts_aux_sym_token3] = SHIFT(532),
    },
    [614] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [615] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
    },
    [616] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [617] = {
        [ts_aux_sym_token1] = SHIFT(618),
    },
    [618] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_switch_statement, 7),
    },
    [619] = {
        [ts_aux_sym_token3] = SHIFT(287),
    },
    [620] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym__delete] = REDUCE(ts_sym_statement, 1),
        [ts_sym__return] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [621] = {
        [ts_sym__terminator] = SHIFT(622),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [622] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [623] = {
        [ts_sym__terminator] = SHIFT(622),
    },
    [624] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(625),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [625] = {
        [ts_sym__terminator] = SHIFT(626),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [626] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__else] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [627] = {
        [ts_sym_expression] = SHIFT(628),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym__terminator] = SHIFT(630),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [628] = {
        [ts_sym__terminator] = SHIFT(629),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [629] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__else] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [630] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [631] = {
        [ts_sym__terminator] = SHIFT(632),
    },
    [632] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [633] = {
        [ts_aux_sym_token2] = SHIFT(634),
    },
    [634] = {
        [ts_sym_var_declaration] = SHIFT(635),
        [ts_sym_expression_statement] = SHIFT(635),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__var] = SHIFT(608),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [635] = {
        [ts_sym_expression_statement] = SHIFT(636),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [636] = {
        [ts_sym_expression] = SHIFT(637),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(664),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [637] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(638),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [638] = {
        [ts_sym_statement] = SHIFT(639),
        [ts_sym_statement_block] = SHIFT(620),
        [ts_sym_for_statement] = SHIFT(620),
        [ts_sym_if_statement] = SHIFT(620),
        [ts_sym_switch_statement] = SHIFT(620),
        [ts_sym_break_statement] = SHIFT(620),
        [ts_sym_var_declaration] = SHIFT(620),
        [ts_sym_expression_statement] = SHIFT(620),
        [ts_sym_return_statement] = SHIFT(620),
        [ts_sym_delete_statement] = SHIFT(620),
        [ts_sym_expression] = SHIFT(621),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(623),
        [ts_sym__delete] = SHIFT(624),
        [ts_sym__return] = SHIFT(627),
        [ts_sym__break] = SHIFT(631),
        [ts_sym__for] = SHIFT(633),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(640),
        [ts_sym__switch] = SHIFT(647),
        [ts_sym__var] = SHIFT(655),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(620),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(659),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [639] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [640] = {
        [ts_aux_sym_token2] = SHIFT(641),
    },
    [641] = {
        [ts_sym_expression] = SHIFT(642),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(663),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [642] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(643),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [643] = {
        [ts_sym_statement] = SHIFT(644),
        [ts_sym_statement_block] = SHIFT(620),
        [ts_sym_for_statement] = SHIFT(620),
        [ts_sym_if_statement] = SHIFT(620),
        [ts_sym_switch_statement] = SHIFT(620),
        [ts_sym_break_statement] = SHIFT(620),
        [ts_sym_var_declaration] = SHIFT(620),
        [ts_sym_expression_statement] = SHIFT(620),
        [ts_sym_return_statement] = SHIFT(620),
        [ts_sym_delete_statement] = SHIFT(620),
        [ts_sym_expression] = SHIFT(621),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(623),
        [ts_sym__delete] = SHIFT(624),
        [ts_sym__return] = SHIFT(627),
        [ts_sym__break] = SHIFT(631),
        [ts_sym__for] = SHIFT(633),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(640),
        [ts_sym__switch] = SHIFT(647),
        [ts_sym__var] = SHIFT(655),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(620),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(659),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [644] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(645),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [645] = {
        [ts_sym_statement] = SHIFT(646),
        [ts_sym_statement_block] = SHIFT(620),
        [ts_sym_for_statement] = SHIFT(620),
        [ts_sym_if_statement] = SHIFT(620),
        [ts_sym_switch_statement] = SHIFT(620),
        [ts_sym_break_statement] = SHIFT(620),
        [ts_sym_var_declaration] = SHIFT(620),
        [ts_sym_expression_statement] = SHIFT(620),
        [ts_sym_return_statement] = SHIFT(620),
        [ts_sym_delete_statement] = SHIFT(620),
        [ts_sym_expression] = SHIFT(621),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(623),
        [ts_sym__delete] = SHIFT(624),
        [ts_sym__return] = SHIFT(627),
        [ts_sym__break] = SHIFT(631),
        [ts_sym__for] = SHIFT(633),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(640),
        [ts_sym__switch] = SHIFT(647),
        [ts_sym__var] = SHIFT(655),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(620),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(659),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [646] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [647] = {
        [ts_aux_sym_token2] = SHIFT(648),
    },
    [648] = {
        [ts_sym_expression] = SHIFT(649),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(654),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [649] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(650),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [650] = {
        [ts_aux_sym_token0] = SHIFT(651),
    },
    [651] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(652),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [652] = {
        [ts_aux_sym_token1] = SHIFT(653),
    },
    [653] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_switch_statement, 7),
    },
    [654] = {
        [ts_aux_sym_token3] = SHIFT(650),
    },
    [655] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(656),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(658),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [656] = {
        [ts_sym__terminator] = SHIFT(657),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [657] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__delete] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__return] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [658] = {
        [ts_sym__terminator] = SHIFT(657),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [659] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(660),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(373),
        [ts_sym_identifier] = SHIFT(374),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(662),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = SHIFT(376),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [660] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = SHIFT(661),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [661] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__delete] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__return] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [662] = {
        [ts_aux_sym_token1] = SHIFT(661),
    },
    [663] = {
        [ts_aux_sym_token3] = SHIFT(643),
    },
    [664] = {
        [ts_aux_sym_token3] = SHIFT(638),
    },
    [665] = {
        [ts_aux_sym_token3] = SHIFT(280),
    },
    [666] = {
        [ts_aux_sym_token3] = SHIFT(274),
    },
    [667] = {
        [ts_aux_sym_token1] = SHIFT(266),
    },
    [668] = {
        [ts_sym_formal_parameters] = SHIFT(669),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [669] = {
        [ts_sym_statement_block] = SHIFT(670),
        [ts_aux_sym_token0] = SHIFT(264),
    },
    [670] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
    },
    [671] = {
        [ts_aux_sym_token1] = SHIFT(242),
    },
    [672] = {
        [ts_sym_formal_parameters] = SHIFT(673),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [673] = {
        [ts_sym_statement_block] = SHIFT(674),
        [ts_aux_sym_token0] = SHIFT(240),
    },
    [674] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
    },
    [675] = {
        [ts_aux_sym_array_repeat0] = SHIFT(231),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [676] = {
        [ts_aux_sym_array_repeat0] = SHIFT(227),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [677] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
    },
    [678] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
    },
    [679] = {
        [ts_aux_sym_array_repeat0] = SHIFT(146),
        [ts_aux_sym_token20] = SHIFT(229),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [680] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
    },
    [681] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
    },
    [682] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
    },
    [683] = {
        [ts_aux_sym_token4] = SHIFT(684),
    },
    [684] = {
        [ts_sym_expression] = SHIFT(685),
        [ts_sym_math_op] = SHIFT(256),
        [ts_sym_bool_op] = SHIFT(256),
        [ts_sym_ternary] = SHIFT(256),
        [ts_sym_assignment] = SHIFT(256),
        [ts_sym_function_expression] = SHIFT(256),
        [ts_sym_function_call] = SHIFT(256),
        [ts_sym_property_access] = SHIFT(257),
        [ts_sym_literal] = SHIFT(256),
        [ts_sym_object] = SHIFT(260),
        [ts_sym_array] = SHIFT(260),
        [ts_sym__function] = SHIFT(261),
        [ts_sym_null] = SHIFT(260),
        [ts_sym_true] = SHIFT(260),
        [ts_sym_false] = SHIFT(260),
        [ts_sym_string] = SHIFT(260),
        [ts_sym_identifier] = SHIFT(257),
        [ts_sym_number] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(346),
        [ts_aux_sym_token2] = SHIFT(355),
        [ts_aux_sym_token17] = SHIFT(389),
        [ts_aux_sym_token22] = SHIFT(391),
    },
    [685] = {
        [ts_aux_sym_object_repeat0] = SHIFT(686),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(129),
        [ts_aux_sym_token5] = SHIFT(182),
        [ts_aux_sym_token6] = SHIFT(182),
        [ts_aux_sym_token7] = SHIFT(184),
        [ts_aux_sym_token8] = SHIFT(184),
        [ts_aux_sym_token9] = SHIFT(186),
        [ts_aux_sym_token10] = SHIFT(188),
        [ts_aux_sym_token11] = SHIFT(188),
        [ts_aux_sym_token12] = SHIFT(188),
        [ts_aux_sym_token13] = SHIFT(188),
        [ts_aux_sym_token14] = SHIFT(190),
        [ts_aux_sym_token15] = SHIFT(188),
        [ts_aux_sym_token16] = SHIFT(188),
        [ts_aux_sym_token18] = SHIFT(192),
        [ts_aux_sym_token20] = SHIFT(122),
        [ts_aux_sym_token21] = SHIFT(196),
        [ts_aux_sym_token22] = SHIFT(198),
    },
    [686] = {
        [ts_aux_sym_token1] = SHIFT(687),
    },
    [687] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
    },
    [688] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
    },
    [689] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
    },
    [690] = {
        [ts_sym__terminator] = SHIFT(691),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [691] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [692] = {
        [ts_aux_sym_token1] = SHIFT(110),
    },
    [693] = {
        [ts_sym_formal_parameters] = SHIFT(694),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [694] = {
        [ts_sym_statement_block] = SHIFT(695),
        [ts_aux_sym_token0] = SHIFT(108),
    },
    [695] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
    },
    [696] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(697),
    },
    [697] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
    },
    [698] = {
        [ts_aux_sym_token1] = SHIFT(697),
    },
    [699] = {
        [ts_sym_formal_parameters] = SHIFT(700),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [700] = {
        [ts_sym_statement_block] = SHIFT(701),
        [ts_aux_sym_token0] = SHIFT(99),
    },
    [701] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
    },
    [702] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 4),
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
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
    },
    [703] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [704] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_token1] = SHIFT(705),
    },
    [705] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [706] = {
        [ts_aux_sym_token1] = SHIFT(705),
    },
    [707] = {
        [ts_sym_formal_parameters] = SHIFT(708),
        [ts_aux_sym_token2] = SHIFT(441),
    },
    [708] = {
        [ts_sym_statement_block] = SHIFT(709),
        [ts_aux_sym_token0] = SHIFT(49),
    },
    [709] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
    },
    [710] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(39),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [711] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
    },
    [712] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
    },
    [713] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(32),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [714] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(28),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [715] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
    },
    [716] = {
        [ts_sym_expression] = SHIFT(717),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_literal] = SHIFT(41),
        [ts_sym_object] = SHIFT(45),
        [ts_sym_array] = SHIFT(45),
        [ts_sym__function] = SHIFT(46),
        [ts_sym_null] = SHIFT(45),
        [ts_sym_true] = SHIFT(45),
        [ts_sym_false] = SHIFT(45),
        [ts_sym_string] = SHIFT(45),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(45),
        [ts_aux_sym_token0] = SHIFT(118),
        [ts_aux_sym_token2] = SHIFT(134),
        [ts_aux_sym_token17] = SHIFT(142),
        [ts_aux_sym_token22] = SHIFT(144),
    },
    [717] = {
        [ts_aux_sym_token2] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(14),
        [ts_aux_sym_token6] = SHIFT(14),
        [ts_aux_sym_token7] = SHIFT(16),
        [ts_aux_sym_token8] = SHIFT(16),
        [ts_aux_sym_token9] = SHIFT(18),
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [718] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [719] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
    },
    [720] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [721] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
    },
    [722] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [723] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(724),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [724] = {
        [ts_sym__terminator] = SHIFT(725),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [725] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [726] = {
        [ts_sym_expression] = SHIFT(727),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym__terminator] = SHIFT(729),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [727] = {
        [ts_sym__terminator] = SHIFT(728),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [728] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [729] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [730] = {
        [ts_sym__terminator] = SHIFT(731),
    },
    [731] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [732] = {
        [ts_aux_sym_token2] = SHIFT(733),
    },
    [733] = {
        [ts_sym_var_declaration] = SHIFT(734),
        [ts_sym_expression_statement] = SHIFT(734),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__var] = SHIFT(608),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [734] = {
        [ts_sym_expression_statement] = SHIFT(735),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [735] = {
        [ts_sym_expression] = SHIFT(736),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(808),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [736] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(737),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [737] = {
        [ts_sym_statement] = SHIFT(738),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_return_statement] = SHIFT(3),
        [ts_sym_delete_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(722),
        [ts_sym__delete] = SHIFT(723),
        [ts_sym__return] = SHIFT(726),
        [ts_sym__break] = SHIFT(730),
        [ts_sym__for] = SHIFT(732),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(739),
        [ts_sym__switch] = SHIFT(746),
        [ts_sym__var] = SHIFT(754),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(758),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [738] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [739] = {
        [ts_aux_sym_token2] = SHIFT(740),
    },
    [740] = {
        [ts_sym_expression] = SHIFT(741),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(807),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [741] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(742),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [742] = {
        [ts_sym_statement] = SHIFT(743),
        [ts_sym_statement_block] = SHIFT(762),
        [ts_sym_for_statement] = SHIFT(762),
        [ts_sym_if_statement] = SHIFT(762),
        [ts_sym_switch_statement] = SHIFT(762),
        [ts_sym_break_statement] = SHIFT(762),
        [ts_sym_var_declaration] = SHIFT(762),
        [ts_sym_expression_statement] = SHIFT(762),
        [ts_sym_return_statement] = SHIFT(762),
        [ts_sym_delete_statement] = SHIFT(762),
        [ts_sym_expression] = SHIFT(763),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(765),
        [ts_sym__delete] = SHIFT(766),
        [ts_sym__return] = SHIFT(769),
        [ts_sym__break] = SHIFT(773),
        [ts_sym__for] = SHIFT(775),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(782),
        [ts_sym__switch] = SHIFT(789),
        [ts_sym__var] = SHIFT(797),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(762),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(801),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [743] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(744),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [744] = {
        [ts_sym_statement] = SHIFT(745),
        [ts_sym_statement_block] = SHIFT(3),
        [ts_sym_for_statement] = SHIFT(3),
        [ts_sym_if_statement] = SHIFT(3),
        [ts_sym_switch_statement] = SHIFT(3),
        [ts_sym_break_statement] = SHIFT(3),
        [ts_sym_var_declaration] = SHIFT(3),
        [ts_sym_expression_statement] = SHIFT(3),
        [ts_sym_return_statement] = SHIFT(3),
        [ts_sym_delete_statement] = SHIFT(3),
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(722),
        [ts_sym__delete] = SHIFT(723),
        [ts_sym__return] = SHIFT(726),
        [ts_sym__break] = SHIFT(730),
        [ts_sym__for] = SHIFT(732),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(739),
        [ts_sym__switch] = SHIFT(746),
        [ts_sym__var] = SHIFT(754),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(758),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [745] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [746] = {
        [ts_aux_sym_token2] = SHIFT(747),
    },
    [747] = {
        [ts_sym_expression] = SHIFT(748),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(753),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [748] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(749),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [749] = {
        [ts_aux_sym_token0] = SHIFT(750),
    },
    [750] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(751),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [751] = {
        [ts_aux_sym_token1] = SHIFT(752),
    },
    [752] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_switch_statement, 7),
    },
    [753] = {
        [ts_aux_sym_token3] = SHIFT(749),
    },
    [754] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(755),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(757),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [755] = {
        [ts_sym__terminator] = SHIFT(756),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [756] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__delete] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__return] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [757] = {
        [ts_sym__terminator] = SHIFT(756),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [758] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(759),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(373),
        [ts_sym_identifier] = SHIFT(374),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(761),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = SHIFT(376),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [759] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = SHIFT(760),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [760] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__delete] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__return] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [761] = {
        [ts_aux_sym_token1] = SHIFT(760),
    },
    [762] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_sym__delete] = REDUCE(ts_sym_statement, 1),
        [ts_sym__return] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [763] = {
        [ts_sym__terminator] = SHIFT(764),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [764] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [765] = {
        [ts_sym__terminator] = SHIFT(764),
    },
    [766] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(299),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(767),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(323),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [767] = {
        [ts_sym__terminator] = SHIFT(768),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(302),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [768] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__else] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [769] = {
        [ts_sym_expression] = SHIFT(770),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym__terminator] = SHIFT(772),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [770] = {
        [ts_sym__terminator] = SHIFT(771),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(54),
        [ts_aux_sym_token6] = SHIFT(54),
        [ts_aux_sym_token7] = SHIFT(56),
        [ts_aux_sym_token8] = SHIFT(56),
        [ts_aux_sym_token9] = SHIFT(58),
        [ts_aux_sym_token10] = SHIFT(60),
        [ts_aux_sym_token11] = SHIFT(60),
        [ts_aux_sym_token12] = SHIFT(60),
        [ts_aux_sym_token13] = SHIFT(60),
        [ts_aux_sym_token14] = SHIFT(62),
        [ts_aux_sym_token15] = SHIFT(60),
        [ts_aux_sym_token16] = SHIFT(60),
        [ts_aux_sym_token18] = SHIFT(64),
        [ts_aux_sym_token21] = SHIFT(68),
        [ts_aux_sym_token22] = SHIFT(70),
    },
    [771] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__else] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [772] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__break] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__else] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__for] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__if] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__switch] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__var] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [773] = {
        [ts_sym__terminator] = SHIFT(774),
    },
    [774] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__delete] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym__return] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [775] = {
        [ts_aux_sym_token2] = SHIFT(776),
    },
    [776] = {
        [ts_sym_var_declaration] = SHIFT(777),
        [ts_sym_expression_statement] = SHIFT(777),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__var] = SHIFT(608),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [777] = {
        [ts_sym_expression_statement] = SHIFT(778),
        [ts_sym_expression] = SHIFT(605),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(607),
        [ts_sym__function] = SHIFT(105),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(247),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [778] = {
        [ts_sym_expression] = SHIFT(779),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(806),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [779] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(780),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [780] = {
        [ts_sym_statement] = SHIFT(781),
        [ts_sym_statement_block] = SHIFT(762),
        [ts_sym_for_statement] = SHIFT(762),
        [ts_sym_if_statement] = SHIFT(762),
        [ts_sym_switch_statement] = SHIFT(762),
        [ts_sym_break_statement] = SHIFT(762),
        [ts_sym_var_declaration] = SHIFT(762),
        [ts_sym_expression_statement] = SHIFT(762),
        [ts_sym_return_statement] = SHIFT(762),
        [ts_sym_delete_statement] = SHIFT(762),
        [ts_sym_expression] = SHIFT(763),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(765),
        [ts_sym__delete] = SHIFT(766),
        [ts_sym__return] = SHIFT(769),
        [ts_sym__break] = SHIFT(773),
        [ts_sym__for] = SHIFT(775),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(782),
        [ts_sym__switch] = SHIFT(789),
        [ts_sym__var] = SHIFT(797),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(762),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(801),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [781] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [782] = {
        [ts_aux_sym_token2] = SHIFT(783),
    },
    [783] = {
        [ts_sym_expression] = SHIFT(784),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(805),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [784] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(785),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [785] = {
        [ts_sym_statement] = SHIFT(786),
        [ts_sym_statement_block] = SHIFT(762),
        [ts_sym_for_statement] = SHIFT(762),
        [ts_sym_if_statement] = SHIFT(762),
        [ts_sym_switch_statement] = SHIFT(762),
        [ts_sym_break_statement] = SHIFT(762),
        [ts_sym_var_declaration] = SHIFT(762),
        [ts_sym_expression_statement] = SHIFT(762),
        [ts_sym_return_statement] = SHIFT(762),
        [ts_sym_delete_statement] = SHIFT(762),
        [ts_sym_expression] = SHIFT(763),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(765),
        [ts_sym__delete] = SHIFT(766),
        [ts_sym__return] = SHIFT(769),
        [ts_sym__break] = SHIFT(773),
        [ts_sym__for] = SHIFT(775),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(782),
        [ts_sym__switch] = SHIFT(789),
        [ts_sym__var] = SHIFT(797),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(762),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(801),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [786] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(787),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [787] = {
        [ts_sym_statement] = SHIFT(788),
        [ts_sym_statement_block] = SHIFT(762),
        [ts_sym_for_statement] = SHIFT(762),
        [ts_sym_if_statement] = SHIFT(762),
        [ts_sym_switch_statement] = SHIFT(762),
        [ts_sym_break_statement] = SHIFT(762),
        [ts_sym_var_declaration] = SHIFT(762),
        [ts_sym_expression_statement] = SHIFT(762),
        [ts_sym_return_statement] = SHIFT(762),
        [ts_sym_delete_statement] = SHIFT(762),
        [ts_sym_expression] = SHIFT(763),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(765),
        [ts_sym__delete] = SHIFT(766),
        [ts_sym__return] = SHIFT(769),
        [ts_sym__break] = SHIFT(773),
        [ts_sym__for] = SHIFT(775),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(782),
        [ts_sym__switch] = SHIFT(789),
        [ts_sym__var] = SHIFT(797),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(762),
        [ts_sym_string] = SHIFT(104),
        [ts_sym_identifier] = SHIFT(101),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(801),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [788] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [789] = {
        [ts_aux_sym_token2] = SHIFT(790),
    },
    [790] = {
        [ts_sym_expression] = SHIFT(791),
        [ts_sym_math_op] = SHIFT(358),
        [ts_sym_bool_op] = SHIFT(358),
        [ts_sym_ternary] = SHIFT(358),
        [ts_sym_assignment] = SHIFT(358),
        [ts_sym_function_expression] = SHIFT(358),
        [ts_sym_function_call] = SHIFT(358),
        [ts_sym_property_access] = SHIFT(359),
        [ts_sym_literal] = SHIFT(358),
        [ts_sym_object] = SHIFT(362),
        [ts_sym_array] = SHIFT(362),
        [ts_builtin_sym_error] = SHIFT(796),
        [ts_sym__function] = SHIFT(363),
        [ts_sym_null] = SHIFT(362),
        [ts_sym_true] = SHIFT(362),
        [ts_sym_false] = SHIFT(362),
        [ts_sym_string] = SHIFT(362),
        [ts_sym_identifier] = SHIFT(359),
        [ts_sym_number] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(380),
        [ts_aux_sym_token2] = SHIFT(409),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [791] = {
        [ts_aux_sym_token2] = SHIFT(136),
        [ts_aux_sym_token3] = SHIFT(792),
        [ts_aux_sym_token5] = SHIFT(204),
        [ts_aux_sym_token6] = SHIFT(204),
        [ts_aux_sym_token7] = SHIFT(206),
        [ts_aux_sym_token8] = SHIFT(206),
        [ts_aux_sym_token9] = SHIFT(208),
        [ts_aux_sym_token10] = SHIFT(210),
        [ts_aux_sym_token11] = SHIFT(210),
        [ts_aux_sym_token12] = SHIFT(210),
        [ts_aux_sym_token13] = SHIFT(210),
        [ts_aux_sym_token14] = SHIFT(212),
        [ts_aux_sym_token15] = SHIFT(210),
        [ts_aux_sym_token16] = SHIFT(210),
        [ts_aux_sym_token18] = SHIFT(214),
        [ts_aux_sym_token21] = SHIFT(218),
        [ts_aux_sym_token22] = SHIFT(220),
    },
    [792] = {
        [ts_aux_sym_token0] = SHIFT(793),
    },
    [793] = {
        [ts_sym_switch_case] = SHIFT(289),
        [ts_sym__case] = SHIFT(290),
        [ts_sym__default] = SHIFT(546),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(794),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [794] = {
        [ts_aux_sym_token1] = SHIFT(795),
    },
    [795] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__delete] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym__return] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_switch_statement, 7),
    },
    [796] = {
        [ts_aux_sym_token3] = SHIFT(792),
    },
    [797] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(299),
        [ts_sym_bool_op] = SHIFT(299),
        [ts_sym_ternary] = SHIFT(299),
        [ts_sym_assignment] = SHIFT(798),
        [ts_sym_function_expression] = SHIFT(299),
        [ts_sym_function_call] = SHIFT(299),
        [ts_sym_property_access] = SHIFT(335),
        [ts_sym_literal] = SHIFT(299),
        [ts_sym_object] = SHIFT(324),
        [ts_sym_array] = SHIFT(324),
        [ts_sym__function] = SHIFT(325),
        [ts_sym_null] = SHIFT(324),
        [ts_sym_true] = SHIFT(324),
        [ts_sym_false] = SHIFT(324),
        [ts_sym_string] = SHIFT(324),
        [ts_sym_identifier] = SHIFT(800),
        [ts_sym_number] = SHIFT(324),
        [ts_aux_sym_token0] = SHIFT(337),
        [ts_aux_sym_token2] = SHIFT(451),
        [ts_aux_sym_token17] = SHIFT(454),
        [ts_aux_sym_token22] = SHIFT(456),
    },
    [798] = {
        [ts_sym__terminator] = SHIFT(799),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [799] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__delete] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym__return] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [800] = {
        [ts_sym__terminator] = SHIFT(799),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = SHIFT(102),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [801] = {
        [ts_sym_statement] = SHIFT(50),
        [ts_sym_statement_block] = SHIFT(51),
        [ts_sym_for_statement] = SHIFT(51),
        [ts_sym_if_statement] = SHIFT(51),
        [ts_sym_switch_statement] = SHIFT(51),
        [ts_sym_break_statement] = SHIFT(51),
        [ts_sym_var_declaration] = SHIFT(51),
        [ts_sym_expression_statement] = SHIFT(51),
        [ts_sym_return_statement] = SHIFT(51),
        [ts_sym_delete_statement] = SHIFT(51),
        [ts_sym_expression] = SHIFT(52),
        [ts_sym_math_op] = SHIFT(100),
        [ts_sym_bool_op] = SHIFT(100),
        [ts_sym_ternary] = SHIFT(100),
        [ts_sym_assignment] = SHIFT(100),
        [ts_sym_function_expression] = SHIFT(100),
        [ts_sym_function_call] = SHIFT(100),
        [ts_sym_property_access] = SHIFT(101),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(104),
        [ts_sym_array] = SHIFT(104),
        [ts_builtin_sym_error] = SHIFT(802),
        [ts_sym__delete] = SHIFT(111),
        [ts_sym__return] = SHIFT(243),
        [ts_sym__break] = SHIFT(267),
        [ts_sym__for] = SHIFT(269),
        [ts_sym__function] = SHIFT(105),
        [ts_sym__if] = SHIFT(277),
        [ts_sym__switch] = SHIFT(284),
        [ts_sym__var] = SHIFT(331),
        [ts_sym_null] = SHIFT(104),
        [ts_sym_true] = SHIFT(104),
        [ts_sym_false] = SHIFT(104),
        [ts_sym_comment] = SHIFT(51),
        [ts_sym_string] = SHIFT(373),
        [ts_sym_identifier] = SHIFT(374),
        [ts_sym_number] = SHIFT(104),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(804),
        [ts_aux_sym_token0] = SHIFT(370),
        [ts_aux_sym_token1] = SHIFT(376),
        [ts_aux_sym_token2] = SHIFT(377),
        [ts_aux_sym_token17] = SHIFT(430),
        [ts_aux_sym_token22] = SHIFT(432),
    },
    [802] = {
        [ts_sym__terminator] = SHIFT(53),
        [ts_aux_sym_object_repeat0] = SHIFT(249),
        [ts_aux_sym_token1] = SHIFT(803),
        [ts_aux_sym_token20] = SHIFT(122),
    },
    [803] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__delete] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym__return] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
    },
    [804] = {
        [ts_aux_sym_token1] = SHIFT(803),
    },
    [805] = {
        [ts_aux_sym_token3] = SHIFT(785),
    },
    [806] = {
        [ts_aux_sym_token3] = SHIFT(780),
    },
    [807] = {
        [ts_aux_sym_token3] = SHIFT(742),
    },
    [808] = {
        [ts_aux_sym_token3] = SHIFT(737),
    },
    [809] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [810] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
