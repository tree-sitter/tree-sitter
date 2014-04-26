#include "tree_sitter/parser.h"

#define STATE_COUNT 803
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
    [23] = 92,
    [24] = 114,
    [25] = 90,
    [26] = 88,
    [27] = 92,
    [28] = 134,
    [29] = 90,
    [30] = 88,
    [31] = 96,
    [32] = 94,
    [33] = 134,
    [34] = 97,
    [35] = 114,
    [36] = 90,
    [37] = 88,
    [38] = 97,
    [39] = 90,
    [40] = 94,
    [41] = 134,
    [42] = 90,
    [43] = 90,
    [44] = 90,
    [45] = 148,
    [46] = 145,
    [47] = 90,
    [48] = 99,
    [49] = 99,
    [50] = 99,
    [51] = 68,
    [52] = 99,
    [53] = 134,
    [54] = 68,
    [55] = 134,
    [56] = 68,
    [57] = 134,
    [58] = 68,
    [59] = 134,
    [60] = 68,
    [61] = 134,
    [62] = 92,
    [63] = 134,
    [64] = 68,
    [65] = 96,
    [66] = 101,
    [67] = 134,
    [68] = 97,
    [69] = 134,
    [70] = 97,
    [71] = 134,
    [72] = 97,
    [73] = 134,
    [74] = 97,
    [75] = 134,
    [76] = 97,
    [77] = 134,
    [78] = 92,
    [79] = 134,
    [80] = 97,
    [81] = 96,
    [82] = 103,
    [83] = 134,
    [84] = 97,
    [85] = 103,
    [86] = 97,
    [87] = 103,
    [88] = 134,
    [89] = 97,
    [90] = 97,
    [91] = 97,
    [92] = 148,
    [93] = 145,
    [94] = 97,
    [95] = 99,
    [96] = 68,
    [97] = 101,
    [98] = 134,
    [99] = 68,
    [100] = 68,
    [101] = 68,
    [102] = 148,
    [103] = 145,
    [104] = 68,
    [105] = 99,
    [106] = 104,
    [107] = 68,
    [108] = 134,
    [109] = 106,
    [110] = 114,
    [111] = 90,
    [112] = 88,
    [113] = 106,
    [114] = 107,
    [115] = 143,
    [116] = 109,
    [117] = 108,
    [118] = 90,
    [119] = 172,
    [120] = 109,
    [121] = 108,
    [122] = 142,
    [123] = 134,
    [124] = 110,
    [125] = 108,
    [126] = 114,
    [127] = 90,
    [128] = 88,
    [129] = 110,
    [130] = 107,
    [131] = 134,
    [132] = 111,
    [133] = 114,
    [134] = 90,
    [135] = 88,
    [136] = 111,
    [137] = 107,
    [138] = 111,
    [139] = 134,
    [140] = 90,
    [141] = 144,
    [142] = 113,
    [143] = 112,
    [144] = 90,
    [145] = 114,
    [146] = 90,
    [147] = 88,
    [148] = 113,
    [149] = 107,
    [150] = 113,
    [151] = 134,
    [152] = 113,
    [153] = 134,
    [154] = 113,
    [155] = 134,
    [156] = 113,
    [157] = 134,
    [158] = 113,
    [159] = 134,
    [160] = 92,
    [161] = 134,
    [162] = 113,
    [163] = 96,
    [164] = 116,
    [165] = 134,
    [166] = 97,
    [167] = 116,
    [168] = 143,
    [169] = 109,
    [170] = 108,
    [171] = 97,
    [172] = 142,
    [173] = 134,
    [174] = 110,
    [175] = 108,
    [176] = 97,
    [177] = 134,
    [178] = 110,
    [179] = 134,
    [180] = 110,
    [181] = 134,
    [182] = 110,
    [183] = 134,
    [184] = 110,
    [185] = 134,
    [186] = 92,
    [187] = 134,
    [188] = 110,
    [189] = 96,
    [190] = 117,
    [191] = 134,
    [192] = 97,
    [193] = 117,
    [194] = 134,
    [195] = 111,
    [196] = 97,
    [197] = 134,
    [198] = 111,
    [199] = 134,
    [200] = 111,
    [201] = 134,
    [202] = 111,
    [203] = 134,
    [204] = 111,
    [205] = 134,
    [206] = 92,
    [207] = 134,
    [208] = 111,
    [209] = 96,
    [210] = 118,
    [211] = 134,
    [212] = 97,
    [213] = 118,
    [214] = 134,
    [215] = 97,
    [216] = 144,
    [217] = 113,
    [218] = 112,
    [219] = 97,
    [220] = 134,
    [221] = 113,
    [222] = 112,
    [223] = 113,
    [224] = 116,
    [225] = 134,
    [226] = 113,
    [227] = 113,
    [228] = 113,
    [229] = 148,
    [230] = 145,
    [231] = 113,
    [232] = 99,
    [233] = 104,
    [234] = 113,
    [235] = 150,
    [236] = 68,
    [237] = 99,
    [238] = 99,
    [239] = 143,
    [240] = 109,
    [241] = 108,
    [242] = 68,
    [243] = 142,
    [244] = 134,
    [245] = 110,
    [246] = 108,
    [247] = 68,
    [248] = 110,
    [249] = 117,
    [250] = 134,
    [251] = 110,
    [252] = 110,
    [253] = 110,
    [254] = 148,
    [255] = 145,
    [256] = 110,
    [257] = 99,
    [258] = 104,
    [259] = 110,
    [260] = 119,
    [261] = 99,
    [262] = 147,
    [263] = 170,
    [264] = 134,
    [265] = 134,
    [266] = 111,
    [267] = 164,
    [268] = 99,
    [269] = 119,
    [270] = 147,
    [271] = 134,
    [272] = 111,
    [273] = 164,
    [274] = 171,
    [275] = 164,
    [276] = 99,
    [277] = 147,
    [278] = 134,
    [279] = 111,
    [280] = 145,
    [281] = 152,
    [282] = 152,
    [283] = 134,
    [284] = 92,
    [285] = 121,
    [286] = 121,
    [287] = 121,
    [288] = 68,
    [289] = 121,
    [290] = 119,
    [291] = 134,
    [292] = 106,
    [293] = 101,
    [294] = 121,
    [295] = 134,
    [296] = 106,
    [297] = 134,
    [298] = 106,
    [299] = 134,
    [300] = 106,
    [301] = 134,
    [302] = 106,
    [303] = 134,
    [304] = 106,
    [305] = 134,
    [306] = 92,
    [307] = 134,
    [308] = 106,
    [309] = 96,
    [310] = 133,
    [311] = 134,
    [312] = 97,
    [313] = 133,
    [314] = 133,
    [315] = 106,
    [316] = 106,
    [317] = 148,
    [318] = 145,
    [319] = 106,
    [320] = 99,
    [321] = 104,
    [322] = 106,
    [323] = 134,
    [324] = 106,
    [325] = 68,
    [326] = 99,
    [327] = 133,
    [328] = 101,
    [329] = 143,
    [330] = 109,
    [331] = 108,
    [332] = 106,
    [333] = 142,
    [334] = 134,
    [335] = 110,
    [336] = 108,
    [337] = 106,
    [338] = 143,
    [339] = 109,
    [340] = 108,
    [341] = 110,
    [342] = 142,
    [343] = 134,
    [344] = 110,
    [345] = 108,
    [346] = 110,
    [347] = 134,
    [348] = 111,
    [349] = 110,
    [350] = 111,
    [351] = 118,
    [352] = 134,
    [353] = 111,
    [354] = 111,
    [355] = 111,
    [356] = 148,
    [357] = 145,
    [358] = 111,
    [359] = 99,
    [360] = 104,
    [361] = 111,
    [362] = 108,
    [363] = 99,
    [364] = 135,
    [365] = 99,
    [366] = 137,
    [367] = 139,
    [368] = 108,
    [369] = 68,
    [370] = 134,
    [371] = 111,
    [372] = 68,
    [373] = 143,
    [374] = 109,
    [375] = 108,
    [376] = 111,
    [377] = 142,
    [378] = 134,
    [379] = 110,
    [380] = 108,
    [381] = 111,
    [382] = 134,
    [383] = 110,
    [384] = 144,
    [385] = 113,
    [386] = 112,
    [387] = 110,
    [388] = 141,
    [389] = 143,
    [390] = 109,
    [391] = 108,
    [392] = 113,
    [393] = 142,
    [394] = 134,
    [395] = 110,
    [396] = 108,
    [397] = 113,
    [398] = 113,
    [399] = 134,
    [400] = 111,
    [401] = 113,
    [402] = 134,
    [403] = 111,
    [404] = 111,
    [405] = 134,
    [406] = 111,
    [407] = 144,
    [408] = 113,
    [409] = 112,
    [410] = 111,
    [411] = 141,
    [412] = 134,
    [413] = 113,
    [414] = 144,
    [415] = 113,
    [416] = 112,
    [417] = 113,
    [418] = 141,
    [419] = 113,
    [420] = 111,
    [421] = 110,
    [422] = 111,
    [423] = 134,
    [424] = 68,
    [425] = 144,
    [426] = 113,
    [427] = 112,
    [428] = 68,
    [429] = 141,
    [430] = 68,
    [431] = 147,
    [432] = 145,
    [433] = 111,
    [434] = 146,
    [435] = 107,
    [436] = 88,
    [437] = 145,
    [438] = 96,
    [439] = 107,
    [440] = 88,
    [441] = 145,
    [442] = 110,
    [443] = 106,
    [444] = 134,
    [445] = 111,
    [446] = 106,
    [447] = 134,
    [448] = 106,
    [449] = 144,
    [450] = 113,
    [451] = 112,
    [452] = 106,
    [453] = 141,
    [454] = 106,
    [455] = 108,
    [456] = 147,
    [457] = 145,
    [458] = 106,
    [459] = 134,
    [460] = 92,
    [461] = 134,
    [462] = 92,
    [463] = 134,
    [464] = 92,
    [465] = 134,
    [466] = 92,
    [467] = 134,
    [468] = 92,
    [469] = 134,
    [470] = 92,
    [471] = 96,
    [472] = 149,
    [473] = 134,
    [474] = 97,
    [475] = 149,
    [476] = 92,
    [477] = 149,
    [478] = 134,
    [479] = 92,
    [480] = 92,
    [481] = 92,
    [482] = 148,
    [483] = 145,
    [484] = 92,
    [485] = 99,
    [486] = 104,
    [487] = 92,
    [488] = 108,
    [489] = 147,
    [490] = 145,
    [491] = 92,
    [492] = 143,
    [493] = 109,
    [494] = 108,
    [495] = 92,
    [496] = 142,
    [497] = 134,
    [498] = 110,
    [499] = 108,
    [500] = 92,
    [501] = 92,
    [502] = 134,
    [503] = 111,
    [504] = 92,
    [505] = 134,
    [506] = 92,
    [507] = 144,
    [508] = 113,
    [509] = 112,
    [510] = 92,
    [511] = 141,
    [512] = 92,
    [513] = 150,
    [514] = 68,
    [515] = 121,
    [516] = 121,
    [517] = 119,
    [518] = 121,
    [519] = 147,
    [520] = 170,
    [521] = 134,
    [522] = 134,
    [523] = 111,
    [524] = 164,
    [525] = 121,
    [526] = 147,
    [527] = 134,
    [528] = 111,
    [529] = 164,
    [530] = 165,
    [531] = 164,
    [532] = 121,
    [533] = 147,
    [534] = 134,
    [535] = 111,
    [536] = 145,
    [537] = 152,
    [538] = 142,
    [539] = 121,
    [540] = 134,
    [541] = 68,
    [542] = 121,
    [543] = 101,
    [544] = 152,
    [545] = 99,
    [546] = 135,
    [547] = 121,
    [548] = 108,
    [549] = 108,
    [550] = 121,
    [551] = 88,
    [552] = 165,
    [553] = 68,
    [554] = 165,
    [555] = 119,
    [556] = 134,
    [557] = 101,
    [558] = 165,
    [559] = 150,
    [560] = 68,
    [561] = 165,
    [562] = 165,
    [563] = 119,
    [564] = 165,
    [565] = 147,
    [566] = 170,
    [567] = 134,
    [568] = 134,
    [569] = 111,
    [570] = 164,
    [571] = 165,
    [572] = 147,
    [573] = 134,
    [574] = 111,
    [575] = 164,
    [576] = 165,
    [577] = 164,
    [578] = 165,
    [579] = 147,
    [580] = 134,
    [581] = 111,
    [582] = 145,
    [583] = 152,
    [584] = 108,
    [585] = 165,
    [586] = 88,
    [587] = 134,
    [588] = 68,
    [589] = 165,
    [590] = 101,
    [591] = 99,
    [592] = 135,
    [593] = 165,
    [594] = 108,
    [595] = 88,
    [596] = 88,
    [597] = 68,
    [598] = 134,
    [599] = 119,
    [600] = 134,
    [601] = 68,
    [602] = 134,
    [603] = 101,
    [604] = 88,
    [605] = 88,
    [606] = 152,
    [607] = 152,
    [608] = 108,
    [609] = 108,
    [610] = 99,
    [611] = 88,
    [612] = 171,
    [613] = 68,
    [614] = 171,
    [615] = 119,
    [616] = 134,
    [617] = 101,
    [618] = 171,
    [619] = 150,
    [620] = 68,
    [621] = 171,
    [622] = 171,
    [623] = 119,
    [624] = 171,
    [625] = 147,
    [626] = 170,
    [627] = 134,
    [628] = 134,
    [629] = 111,
    [630] = 164,
    [631] = 171,
    [632] = 147,
    [633] = 134,
    [634] = 111,
    [635] = 164,
    [636] = 171,
    [637] = 164,
    [638] = 171,
    [639] = 147,
    [640] = 134,
    [641] = 111,
    [642] = 145,
    [643] = 152,
    [644] = 108,
    [645] = 171,
    [646] = 88,
    [647] = 134,
    [648] = 68,
    [649] = 171,
    [650] = 101,
    [651] = 99,
    [652] = 135,
    [653] = 171,
    [654] = 108,
    [655] = 88,
    [656] = 88,
    [657] = 88,
    [658] = 88,
    [659] = 108,
    [660] = 147,
    [661] = 145,
    [662] = 110,
    [663] = 108,
    [664] = 147,
    [665] = 145,
    [666] = 113,
    [667] = 141,
    [668] = 141,
    [669] = 97,
    [670] = 97,
    [671] = 141,
    [672] = 90,
    [673] = 90,
    [674] = 110,
    [675] = 142,
    [676] = 134,
    [677] = 110,
    [678] = 108,
    [679] = 90,
    [680] = 90,
    [681] = 106,
    [682] = 101,
    [683] = 99,
    [684] = 108,
    [685] = 147,
    [686] = 145,
    [687] = 68,
    [688] = 104,
    [689] = 97,
    [690] = 108,
    [691] = 147,
    [692] = 145,
    [693] = 97,
    [694] = 101,
    [695] = 108,
    [696] = 104,
    [697] = 90,
    [698] = 108,
    [699] = 147,
    [700] = 145,
    [701] = 90,
    [702] = 107,
    [703] = 97,
    [704] = 94,
    [705] = 107,
    [706] = 107,
    [707] = 92,
    [708] = 134,
    [709] = 90,
    [710] = 107,
    [711] = 90,
    [712] = 107,
    [713] = 68,
    [714] = 119,
    [715] = 134,
    [716] = 101,
    [717] = 2,
    [718] = 150,
    [719] = 68,
    [720] = 2,
    [721] = 2,
    [722] = 119,
    [723] = 2,
    [724] = 147,
    [725] = 170,
    [726] = 134,
    [727] = 134,
    [728] = 111,
    [729] = 164,
    [730] = 2,
    [731] = 147,
    [732] = 134,
    [733] = 111,
    [734] = 164,
    [735] = 173,
    [736] = 164,
    [737] = 2,
    [738] = 147,
    [739] = 134,
    [740] = 111,
    [741] = 145,
    [742] = 152,
    [743] = 108,
    [744] = 2,
    [745] = 88,
    [746] = 134,
    [747] = 68,
    [748] = 2,
    [749] = 101,
    [750] = 99,
    [751] = 135,
    [752] = 2,
    [753] = 108,
    [754] = 173,
    [755] = 68,
    [756] = 173,
    [757] = 119,
    [758] = 134,
    [759] = 101,
    [760] = 173,
    [761] = 150,
    [762] = 68,
    [763] = 173,
    [764] = 173,
    [765] = 119,
    [766] = 173,
    [767] = 147,
    [768] = 170,
    [769] = 134,
    [770] = 134,
    [771] = 111,
    [772] = 164,
    [773] = 173,
    [774] = 147,
    [775] = 134,
    [776] = 111,
    [777] = 164,
    [778] = 173,
    [779] = 164,
    [780] = 173,
    [781] = 147,
    [782] = 134,
    [783] = 111,
    [784] = 145,
    [785] = 152,
    [786] = 108,
    [787] = 173,
    [788] = 88,
    [789] = 134,
    [790] = 68,
    [791] = 173,
    [792] = 101,
    [793] = 99,
    [794] = 135,
    [795] = 173,
    [796] = 108,
    [797] = 88,
    [798] = 88,
    [799] = 88,
    [800] = 88,
    [801] = 0,
    [802] = 0,
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
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__delete] = SHIFT(715),
        [ts_sym__return] = SHIFT(718),
        [ts_sym__break] = SHIFT(722),
        [ts_sym__for] = SHIFT(724),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(731),
        [ts_sym__switch] = SHIFT(738),
        [ts_sym__var] = SHIFT(746),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_program_repeat0] = SHIFT(802),
        [ts_aux_sym_token0] = SHIFT(750),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
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
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__delete] = SHIFT(715),
        [ts_sym__return] = SHIFT(718),
        [ts_sym__break] = SHIFT(722),
        [ts_sym__for] = SHIFT(724),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(731),
        [ts_sym__switch] = SHIFT(738),
        [ts_sym__var] = SHIFT(746),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_program_repeat0] = SHIFT(801),
        [ts_aux_sym_token0] = SHIFT(750),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
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
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
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
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(712),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(713),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
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
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(710),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(711),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
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
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [16] = {
        [ts_sym_expression] = SHIFT(17),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [18] = {
        [ts_sym_expression] = SHIFT(19),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [20] = {
        [ts_sym_expression] = SHIFT(21),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [22] = {
        [ts_sym_expression] = SHIFT(23),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [23] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(708),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [24] = {
        [ts_sym_expression] = SHIFT(25),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(706),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(707),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_aux_sym_token10] = SHIFT(20),
        [ts_aux_sym_token11] = SHIFT(20),
        [ts_aux_sym_token12] = SHIFT(20),
        [ts_aux_sym_token13] = SHIFT(20),
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [26] = {
        [ts_aux_sym_token3] = SHIFT(27),
    },
    [27] = {
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
    [28] = {
        [ts_sym_expression] = SHIFT(29),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(705),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [29] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(30),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [30] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 3),
    },
    [31] = {
        [ts_sym_identifier] = SHIFT(32),
    },
    [32] = {
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
    [33] = {
        [ts_sym_expression] = SHIFT(34),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [34] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(704),
    },
    [35] = {
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(702),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(703),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [36] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(37),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [37] = {
        [ts_aux_sym_token3] = SHIFT(38),
    },
    [38] = {
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
    [39] = {
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
    [40] = {
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
        [ts_aux_sym_token19] = SHIFT(41),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [41] = {
        [ts_sym_expression] = SHIFT(42),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [42] = {
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [43] = {
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
    [44] = {
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
    [45] = {
        [ts_sym_formal_parameters] = SHIFT(46),
        [ts_sym_identifier] = SHIFT(699),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [46] = {
        [ts_sym_statement_block] = SHIFT(47),
        [ts_aux_sym_token0] = SHIFT(48),
    },
    [47] = {
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
    [48] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(696),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(698),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [49] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(269),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(695),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [50] = {
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
    [51] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [52] = {
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
    [53] = {
        [ts_sym_expression] = SHIFT(54),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [54] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [55] = {
        [ts_sym_expression] = SHIFT(56),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [56] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [57] = {
        [ts_sym_expression] = SHIFT(58),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [58] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [59] = {
        [ts_sym_expression] = SHIFT(60),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [60] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [61] = {
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [62] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(63),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [63] = {
        [ts_sym_expression] = SHIFT(64),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [64] = {
        [ts_sym__terminator] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [65] = {
        [ts_sym_identifier] = SHIFT(66),
    },
    [66] = {
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
    [67] = {
        [ts_sym_expression] = SHIFT(68),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [68] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(694),
    },
    [69] = {
        [ts_sym_expression] = SHIFT(70),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [70] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [71] = {
        [ts_sym_expression] = SHIFT(72),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [72] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [73] = {
        [ts_sym_expression] = SHIFT(74),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [74] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [75] = {
        [ts_sym_expression] = SHIFT(76),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [76] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [77] = {
        [ts_sym_expression] = SHIFT(78),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [78] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(79),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [79] = {
        [ts_sym_expression] = SHIFT(80),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [80] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = REDUCE(ts_sym_ternary, 5),
    },
    [81] = {
        [ts_sym_identifier] = SHIFT(82),
    },
    [82] = {
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
    [83] = {
        [ts_sym_expression] = SHIFT(84),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [84] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(85),
    },
    [85] = {
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
    [86] = {
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
    [87] = {
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
        [ts_aux_sym_token19] = SHIFT(88),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [88] = {
        [ts_sym_expression] = SHIFT(89),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [89] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = REDUCE(ts_sym_assignment, 3),
    },
    [90] = {
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
    [91] = {
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
    [92] = {
        [ts_sym_formal_parameters] = SHIFT(93),
        [ts_sym_identifier] = SHIFT(691),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [93] = {
        [ts_sym_statement_block] = SHIFT(94),
        [ts_aux_sym_token0] = SHIFT(95),
    },
    [94] = {
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
    [95] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(688),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(690),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [96] = {
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
    [97] = {
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [98] = {
        [ts_sym_expression] = SHIFT(99),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [99] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
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
    [102] = {
        [ts_sym_formal_parameters] = SHIFT(103),
        [ts_sym_identifier] = SHIFT(685),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [103] = {
        [ts_sym_statement_block] = SHIFT(104),
        [ts_aux_sym_token0] = SHIFT(105),
    },
    [104] = {
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
    [105] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(106),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(684),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [106] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(107),
    },
    [107] = {
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
    [108] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(682),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [109] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = SHIFT(299),
        [ts_aux_sym_token8] = SHIFT(299),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = SHIFT(305),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [110] = {
        [ts_sym_expression] = SHIFT(111),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(114),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(681),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [111] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(112),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [112] = {
        [ts_aux_sym_token3] = SHIFT(113),
    },
    [113] = {
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
    [114] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(112),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [115] = {
        [ts_builtin_sym_error] = SHIFT(116),
        [ts_sym_string] = SHIFT(675),
        [ts_sym_identifier] = SHIFT(675),
        [ts_aux_sym_token1] = SHIFT(680),
    },
    [116] = {
        [ts_aux_sym_object_repeat0] = SHIFT(117),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [117] = {
        [ts_aux_sym_token1] = SHIFT(118),
    },
    [118] = {
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
    [119] = {
        [ts_builtin_sym_error] = SHIFT(120),
        [ts_sym_string] = SHIFT(122),
        [ts_sym_identifier] = SHIFT(122),
    },
    [120] = {
        [ts_aux_sym_object_repeat0] = SHIFT(121),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [121] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [122] = {
        [ts_aux_sym_token4] = SHIFT(123),
    },
    [123] = {
        [ts_sym_expression] = SHIFT(124),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [124] = {
        [ts_aux_sym_object_repeat0] = SHIFT(125),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [125] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [126] = {
        [ts_sym_expression] = SHIFT(127),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(130),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(674),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [127] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(128),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [128] = {
        [ts_aux_sym_token3] = SHIFT(129),
    },
    [129] = {
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
    [130] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(128),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [131] = {
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [132] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(673),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [133] = {
        [ts_sym_expression] = SHIFT(134),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(137),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(138),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [134] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(135),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [135] = {
        [ts_aux_sym_token3] = SHIFT(136),
    },
    [136] = {
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
    [137] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(135),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [138] = {
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
    [139] = {
        [ts_sym_expression] = SHIFT(140),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [140] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(671),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(672),
    },
    [142] = {
        [ts_aux_sym_array_repeat0] = SHIFT(143),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [143] = {
        [ts_aux_sym_token23] = SHIFT(144),
    },
    [144] = {
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
    [145] = {
        [ts_sym_expression] = SHIFT(146),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_builtin_sym_error] = SHIFT(149),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [146] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(147),
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = SHIFT(28),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [147] = {
        [ts_aux_sym_token3] = SHIFT(148),
    },
    [148] = {
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
    [149] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(147),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [150] = {
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
    [151] = {
        [ts_sym_expression] = SHIFT(152),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [152] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [153] = {
        [ts_sym_expression] = SHIFT(154),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [154] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [155] = {
        [ts_sym_expression] = SHIFT(156),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [156] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [157] = {
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [158] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [159] = {
        [ts_sym_expression] = SHIFT(160),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [160] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(161),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [161] = {
        [ts_sym_expression] = SHIFT(162),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [162] = {
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_sym_ternary, 5),
    },
    [163] = {
        [ts_sym_identifier] = SHIFT(164),
    },
    [164] = {
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
    [165] = {
        [ts_sym_expression] = SHIFT(166),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [166] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(167),
    },
    [167] = {
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
    [168] = {
        [ts_builtin_sym_error] = SHIFT(169),
        [ts_sym_string] = SHIFT(172),
        [ts_sym_identifier] = SHIFT(172),
        [ts_aux_sym_token1] = SHIFT(670),
    },
    [169] = {
        [ts_aux_sym_object_repeat0] = SHIFT(170),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [170] = {
        [ts_aux_sym_token1] = SHIFT(171),
    },
    [171] = {
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
    [172] = {
        [ts_aux_sym_token4] = SHIFT(173),
    },
    [173] = {
        [ts_sym_expression] = SHIFT(174),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [174] = {
        [ts_aux_sym_object_repeat0] = SHIFT(175),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [175] = {
        [ts_aux_sym_token1] = SHIFT(176),
    },
    [176] = {
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
    [177] = {
        [ts_sym_expression] = SHIFT(178),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [178] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [179] = {
        [ts_sym_expression] = SHIFT(180),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [180] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [181] = {
        [ts_sym_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [182] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [183] = {
        [ts_sym_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [184] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [185] = {
        [ts_sym_expression] = SHIFT(186),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [186] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(187),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [187] = {
        [ts_sym_expression] = SHIFT(188),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [188] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [189] = {
        [ts_sym_identifier] = SHIFT(190),
    },
    [190] = {
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
    [191] = {
        [ts_sym_expression] = SHIFT(192),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [192] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(193),
    },
    [193] = {
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
    [194] = {
        [ts_sym_expression] = SHIFT(195),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [195] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(196),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [196] = {
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
    [197] = {
        [ts_sym_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [198] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [199] = {
        [ts_sym_expression] = SHIFT(200),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [200] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [201] = {
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [202] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [203] = {
        [ts_sym_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [204] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [205] = {
        [ts_sym_expression] = SHIFT(206),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [206] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(207),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [207] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [208] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [209] = {
        [ts_sym_identifier] = SHIFT(210),
    },
    [210] = {
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
    [211] = {
        [ts_sym_expression] = SHIFT(212),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [212] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(213),
    },
    [213] = {
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
    [214] = {
        [ts_sym_expression] = SHIFT(215),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [215] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
    },
    [216] = {
        [ts_sym_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(668),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(669),
    },
    [217] = {
        [ts_aux_sym_array_repeat0] = SHIFT(218),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [218] = {
        [ts_aux_sym_token23] = SHIFT(219),
    },
    [219] = {
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
    [220] = {
        [ts_sym_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(667),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [221] = {
        [ts_aux_sym_array_repeat0] = SHIFT(222),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [222] = {
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [223] = {
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
    [224] = {
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
        [ts_aux_sym_token19] = SHIFT(225),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [225] = {
        [ts_sym_expression] = SHIFT(226),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [226] = {
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_sym_assignment, 3),
    },
    [227] = {
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
    [228] = {
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
    [229] = {
        [ts_sym_formal_parameters] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(664),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [230] = {
        [ts_sym_statement_block] = SHIFT(231),
        [ts_aux_sym_token0] = SHIFT(232),
    },
    [231] = {
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
    [232] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(233),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(663),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [233] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(234),
    },
    [234] = {
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
    [235] = {
        [ts_sym_expression] = SHIFT(236),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym__terminator] = SHIFT(238),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [236] = {
        [ts_sym__terminator] = SHIFT(237),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [237] = {
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
    [238] = {
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
    [239] = {
        [ts_builtin_sym_error] = SHIFT(240),
        [ts_sym_string] = SHIFT(243),
        [ts_sym_identifier] = SHIFT(243),
        [ts_aux_sym_token1] = SHIFT(369),
    },
    [240] = {
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [241] = {
        [ts_aux_sym_token1] = SHIFT(242),
    },
    [242] = {
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
    [243] = {
        [ts_aux_sym_token4] = SHIFT(244),
    },
    [244] = {
        [ts_sym_expression] = SHIFT(245),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [245] = {
        [ts_aux_sym_object_repeat0] = SHIFT(246),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [246] = {
        [ts_aux_sym_token1] = SHIFT(247),
    },
    [247] = {
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
    [248] = {
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
    [249] = {
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
        [ts_aux_sym_token19] = SHIFT(250),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [250] = {
        [ts_sym_expression] = SHIFT(251),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [251] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [252] = {
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
    [253] = {
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
    [254] = {
        [ts_sym_formal_parameters] = SHIFT(255),
        [ts_sym_identifier] = SHIFT(660),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [255] = {
        [ts_sym_statement_block] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(257),
    },
    [256] = {
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
    [257] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(258),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(659),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [258] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(259),
    },
    [259] = {
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
    [260] = {
        [ts_sym__terminator] = SHIFT(261),
    },
    [261] = {
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
    [262] = {
        [ts_aux_sym_token2] = SHIFT(263),
    },
    [263] = {
        [ts_sym_var_declaration] = SHIFT(264),
        [ts_sym_expression_statement] = SHIFT(264),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [264] = {
        [ts_sym_expression_statement] = SHIFT(265),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [265] = {
        [ts_sym_expression] = SHIFT(266),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(658),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [266] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(267),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [267] = {
        [ts_sym_statement] = SHIFT(268),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(269),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [268] = {
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
    [269] = {
        [ts_sym__terminator] = SHIFT(52),
    },
    [270] = {
        [ts_aux_sym_token2] = SHIFT(271),
    },
    [271] = {
        [ts_sym_expression] = SHIFT(272),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(657),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [272] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(273),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [273] = {
        [ts_sym_statement] = SHIFT(274),
        [ts_sym_statement_block] = SHIFT(612),
        [ts_sym_for_statement] = SHIFT(612),
        [ts_sym_if_statement] = SHIFT(612),
        [ts_sym_switch_statement] = SHIFT(612),
        [ts_sym_break_statement] = SHIFT(612),
        [ts_sym_var_declaration] = SHIFT(612),
        [ts_sym_expression_statement] = SHIFT(612),
        [ts_sym_return_statement] = SHIFT(612),
        [ts_sym_delete_statement] = SHIFT(612),
        [ts_sym_expression] = SHIFT(613),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(651),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [274] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(275),
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
    [275] = {
        [ts_sym_statement] = SHIFT(276),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(269),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [276] = {
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
    [277] = {
        [ts_aux_sym_token2] = SHIFT(278),
    },
    [278] = {
        [ts_sym_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(611),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [279] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(280),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [280] = {
        [ts_aux_sym_token0] = SHIFT(281),
    },
    [281] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(609),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [282] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(608),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [283] = {
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [284] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(285),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [285] = {
        [ts_sym_statement] = SHIFT(286),
        [ts_sym_statement_block] = SHIFT(287),
        [ts_sym_for_statement] = SHIFT(287),
        [ts_sym_if_statement] = SHIFT(287),
        [ts_sym_switch_statement] = SHIFT(287),
        [ts_sym_break_statement] = SHIFT(287),
        [ts_sym_var_declaration] = SHIFT(287),
        [ts_sym_expression_statement] = SHIFT(287),
        [ts_sym_return_statement] = SHIFT(287),
        [ts_sym_delete_statement] = SHIFT(287),
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(290),
        [ts_sym__delete] = SHIFT(291),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(287),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(607),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [286] = {
        [ts_sym_statement] = SHIFT(286),
        [ts_sym_statement_block] = SHIFT(287),
        [ts_sym_for_statement] = SHIFT(287),
        [ts_sym_if_statement] = SHIFT(287),
        [ts_sym_switch_statement] = SHIFT(287),
        [ts_sym_break_statement] = SHIFT(287),
        [ts_sym_var_declaration] = SHIFT(287),
        [ts_sym_expression_statement] = SHIFT(287),
        [ts_sym_return_statement] = SHIFT(287),
        [ts_sym_delete_statement] = SHIFT(287),
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(290),
        [ts_sym__delete] = SHIFT(291),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(287),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(606),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [287] = {
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
    [288] = {
        [ts_sym__terminator] = SHIFT(289),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [289] = {
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
    [290] = {
        [ts_sym__terminator] = SHIFT(289),
    },
    [291] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(293),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [292] = {
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
    [293] = {
        [ts_sym__terminator] = SHIFT(294),
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [294] = {
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
    [295] = {
        [ts_sym_expression] = SHIFT(296),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [296] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = SHIFT(299),
        [ts_aux_sym_token8] = SHIFT(299),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = SHIFT(305),
        [ts_aux_sym_token21] = SHIFT(309),
        [ts_aux_sym_token22] = SHIFT(311),
    },
    [297] = {
        [ts_sym_expression] = SHIFT(298),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [298] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [299] = {
        [ts_sym_expression] = SHIFT(300),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [300] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = SHIFT(299),
        [ts_aux_sym_token8] = SHIFT(299),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [301] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [302] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [303] = {
        [ts_sym_expression] = SHIFT(304),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [304] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [305] = {
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [306] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(307),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [307] = {
        [ts_sym_expression] = SHIFT(308),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [308] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = SHIFT(299),
        [ts_aux_sym_token8] = SHIFT(299),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = SHIFT(305),
        [ts_aux_sym_token21] = SHIFT(309),
        [ts_aux_sym_token22] = SHIFT(311),
    },
    [309] = {
        [ts_sym_identifier] = SHIFT(310),
    },
    [310] = {
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
    [311] = {
        [ts_sym_expression] = SHIFT(312),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [312] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(313),
    },
    [313] = {
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
    [314] = {
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [315] = {
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
    [316] = {
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
    [317] = {
        [ts_sym_formal_parameters] = SHIFT(318),
        [ts_sym_identifier] = SHIFT(456),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [318] = {
        [ts_sym_statement_block] = SHIFT(319),
        [ts_aux_sym_token0] = SHIFT(320),
    },
    [319] = {
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
    [320] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(321),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(455),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [321] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(322),
    },
    [322] = {
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
    [323] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(325),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(328),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [324] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(297),
        [ts_aux_sym_token6] = SHIFT(297),
        [ts_aux_sym_token7] = SHIFT(299),
        [ts_aux_sym_token8] = SHIFT(299),
        [ts_aux_sym_token9] = SHIFT(301),
        [ts_aux_sym_token10] = SHIFT(303),
        [ts_aux_sym_token11] = SHIFT(303),
        [ts_aux_sym_token12] = SHIFT(303),
        [ts_aux_sym_token13] = SHIFT(303),
        [ts_aux_sym_token14] = SHIFT(303),
        [ts_aux_sym_token15] = SHIFT(303),
        [ts_aux_sym_token16] = SHIFT(303),
        [ts_aux_sym_token18] = SHIFT(305),
        [ts_aux_sym_token21] = SHIFT(309),
        [ts_aux_sym_token22] = SHIFT(311),
    },
    [325] = {
        [ts_sym__terminator] = SHIFT(326),
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
    [326] = {
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
    [327] = {
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [328] = {
        [ts_sym__terminator] = SHIFT(326),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [329] = {
        [ts_builtin_sym_error] = SHIFT(330),
        [ts_sym_string] = SHIFT(333),
        [ts_sym_identifier] = SHIFT(333),
        [ts_aux_sym_token1] = SHIFT(443),
    },
    [330] = {
        [ts_aux_sym_object_repeat0] = SHIFT(331),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [331] = {
        [ts_aux_sym_token1] = SHIFT(332),
    },
    [332] = {
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
    [333] = {
        [ts_aux_sym_token4] = SHIFT(334),
    },
    [334] = {
        [ts_sym_expression] = SHIFT(335),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [335] = {
        [ts_aux_sym_object_repeat0] = SHIFT(336),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [336] = {
        [ts_aux_sym_token1] = SHIFT(337),
    },
    [337] = {
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
    [338] = {
        [ts_builtin_sym_error] = SHIFT(339),
        [ts_sym_string] = SHIFT(342),
        [ts_sym_identifier] = SHIFT(342),
        [ts_aux_sym_token1] = SHIFT(442),
    },
    [339] = {
        [ts_aux_sym_object_repeat0] = SHIFT(340),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [340] = {
        [ts_aux_sym_token1] = SHIFT(341),
    },
    [341] = {
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
    [342] = {
        [ts_aux_sym_token4] = SHIFT(343),
    },
    [343] = {
        [ts_sym_expression] = SHIFT(344),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [344] = {
        [ts_aux_sym_object_repeat0] = SHIFT(345),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [345] = {
        [ts_aux_sym_token1] = SHIFT(346),
    },
    [346] = {
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
    [347] = {
        [ts_sym_expression] = SHIFT(348),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [348] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(349),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [349] = {
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
    [350] = {
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
    [351] = {
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
        [ts_aux_sym_token19] = SHIFT(352),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [352] = {
        [ts_sym_expression] = SHIFT(353),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [353] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [354] = {
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
    [355] = {
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
    [356] = {
        [ts_sym_formal_parameters] = SHIFT(357),
        [ts_sym_identifier] = SHIFT(431),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [357] = {
        [ts_sym_statement_block] = SHIFT(358),
        [ts_aux_sym_token0] = SHIFT(359),
    },
    [358] = {
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
    [359] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(360),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(362),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [360] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(361),
    },
    [361] = {
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
    [362] = {
        [ts_aux_sym_token1] = SHIFT(361),
    },
    [363] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(364),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(368),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [364] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = SHIFT(365),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [365] = {
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
    [366] = {
        [ts_sym__terminator] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
        [ts_aux_sym_token4] = SHIFT(244),
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
    [367] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(244),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [368] = {
        [ts_aux_sym_token1] = SHIFT(365),
    },
    [369] = {
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
    [370] = {
        [ts_sym_expression] = SHIFT(371),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [371] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(372),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [372] = {
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
    [373] = {
        [ts_builtin_sym_error] = SHIFT(374),
        [ts_sym_string] = SHIFT(377),
        [ts_sym_identifier] = SHIFT(377),
        [ts_aux_sym_token1] = SHIFT(422),
    },
    [374] = {
        [ts_aux_sym_object_repeat0] = SHIFT(375),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [375] = {
        [ts_aux_sym_token1] = SHIFT(376),
    },
    [376] = {
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
    [377] = {
        [ts_aux_sym_token4] = SHIFT(378),
    },
    [378] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [379] = {
        [ts_aux_sym_object_repeat0] = SHIFT(380),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [380] = {
        [ts_aux_sym_token1] = SHIFT(381),
    },
    [381] = {
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
    [382] = {
        [ts_sym_expression] = SHIFT(383),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [383] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [384] = {
        [ts_sym_expression] = SHIFT(385),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(388),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(421),
    },
    [385] = {
        [ts_aux_sym_array_repeat0] = SHIFT(386),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [386] = {
        [ts_aux_sym_token23] = SHIFT(387),
    },
    [387] = {
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
    [388] = {
        [ts_aux_sym_array_repeat0] = SHIFT(386),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [389] = {
        [ts_builtin_sym_error] = SHIFT(390),
        [ts_sym_string] = SHIFT(393),
        [ts_sym_identifier] = SHIFT(393),
        [ts_aux_sym_token1] = SHIFT(398),
    },
    [390] = {
        [ts_aux_sym_object_repeat0] = SHIFT(391),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [391] = {
        [ts_aux_sym_token1] = SHIFT(392),
    },
    [392] = {
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
    [393] = {
        [ts_aux_sym_token4] = SHIFT(394),
    },
    [394] = {
        [ts_sym_expression] = SHIFT(395),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [395] = {
        [ts_aux_sym_object_repeat0] = SHIFT(396),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [396] = {
        [ts_aux_sym_token1] = SHIFT(397),
    },
    [397] = {
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
    [398] = {
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
    [399] = {
        [ts_sym_expression] = SHIFT(400),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [400] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(401),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [401] = {
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
    [402] = {
        [ts_sym_expression] = SHIFT(403),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [403] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(404),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [404] = {
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
    [405] = {
        [ts_sym_expression] = SHIFT(406),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [406] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [407] = {
        [ts_sym_expression] = SHIFT(408),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(411),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(420),
    },
    [408] = {
        [ts_aux_sym_array_repeat0] = SHIFT(409),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [409] = {
        [ts_aux_sym_token23] = SHIFT(410),
    },
    [410] = {
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
    [411] = {
        [ts_aux_sym_array_repeat0] = SHIFT(409),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [412] = {
        [ts_sym_expression] = SHIFT(413),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [413] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
    },
    [414] = {
        [ts_sym_expression] = SHIFT(415),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(418),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(419),
    },
    [415] = {
        [ts_aux_sym_array_repeat0] = SHIFT(416),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [416] = {
        [ts_aux_sym_token23] = SHIFT(417),
    },
    [417] = {
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
    [418] = {
        [ts_aux_sym_array_repeat0] = SHIFT(416),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [419] = {
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
    [420] = {
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
    [421] = {
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
    [422] = {
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
    [423] = {
        [ts_sym_expression] = SHIFT(424),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [424] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [425] = {
        [ts_sym_expression] = SHIFT(426),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(429),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(430),
    },
    [426] = {
        [ts_aux_sym_array_repeat0] = SHIFT(427),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [427] = {
        [ts_aux_sym_token23] = SHIFT(428),
    },
    [428] = {
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
    [429] = {
        [ts_aux_sym_array_repeat0] = SHIFT(427),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [430] = {
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
    [431] = {
        [ts_sym_formal_parameters] = SHIFT(432),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [432] = {
        [ts_sym_statement_block] = SHIFT(433),
        [ts_aux_sym_token0] = SHIFT(359),
    },
    [433] = {
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
    [434] = {
        [ts_sym_identifier] = SHIFT(435),
        [ts_aux_sym_token3] = SHIFT(441),
    },
    [435] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(436),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(438),
    },
    [436] = {
        [ts_aux_sym_token3] = SHIFT(437),
    },
    [437] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [438] = {
        [ts_sym_identifier] = SHIFT(439),
    },
    [439] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(440),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(438),
    },
    [440] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [441] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [442] = {
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
    [443] = {
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
    [444] = {
        [ts_sym_expression] = SHIFT(445),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [445] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(446),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [446] = {
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
    [447] = {
        [ts_sym_expression] = SHIFT(448),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(314),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [448] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [449] = {
        [ts_sym_expression] = SHIFT(450),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(453),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(454),
    },
    [450] = {
        [ts_aux_sym_array_repeat0] = SHIFT(451),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [451] = {
        [ts_aux_sym_token23] = SHIFT(452),
    },
    [452] = {
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
    [453] = {
        [ts_aux_sym_array_repeat0] = SHIFT(451),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [454] = {
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
    [455] = {
        [ts_aux_sym_token1] = SHIFT(322),
    },
    [456] = {
        [ts_sym_formal_parameters] = SHIFT(457),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [457] = {
        [ts_sym_statement_block] = SHIFT(458),
        [ts_aux_sym_token0] = SHIFT(320),
    },
    [458] = {
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
    [459] = {
        [ts_sym_expression] = SHIFT(460),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [460] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [461] = {
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [462] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [463] = {
        [ts_sym_expression] = SHIFT(464),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [464] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [465] = {
        [ts_sym_expression] = SHIFT(466),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [466] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [467] = {
        [ts_sym_expression] = SHIFT(468),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [468] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = SHIFT(469),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [469] = {
        [ts_sym_expression] = SHIFT(470),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [470] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [471] = {
        [ts_sym_identifier] = SHIFT(472),
    },
    [472] = {
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
    [473] = {
        [ts_sym_expression] = SHIFT(474),
        [ts_sym_math_op] = SHIFT(86),
        [ts_sym_bool_op] = SHIFT(86),
        [ts_sym_ternary] = SHIFT(86),
        [ts_sym_assignment] = SHIFT(86),
        [ts_sym_function_expression] = SHIFT(86),
        [ts_sym_function_call] = SHIFT(86),
        [ts_sym_property_access] = SHIFT(87),
        [ts_sym_literal] = SHIFT(90),
        [ts_sym_object] = SHIFT(91),
        [ts_sym_array] = SHIFT(91),
        [ts_sym__function] = SHIFT(92),
        [ts_sym_null] = SHIFT(91),
        [ts_sym_true] = SHIFT(91),
        [ts_sym_false] = SHIFT(91),
        [ts_sym_string] = SHIFT(91),
        [ts_sym_identifier] = SHIFT(87),
        [ts_sym_number] = SHIFT(91),
        [ts_aux_sym_token0] = SHIFT(168),
        [ts_aux_sym_token2] = SHIFT(194),
        [ts_aux_sym_token17] = SHIFT(214),
        [ts_aux_sym_token22] = SHIFT(216),
    },
    [474] = {
        [ts_aux_sym_token2] = SHIFT(35),
        [ts_aux_sym_token5] = SHIFT(69),
        [ts_aux_sym_token6] = SHIFT(69),
        [ts_aux_sym_token7] = SHIFT(71),
        [ts_aux_sym_token8] = SHIFT(71),
        [ts_aux_sym_token9] = SHIFT(73),
        [ts_aux_sym_token10] = SHIFT(75),
        [ts_aux_sym_token11] = SHIFT(75),
        [ts_aux_sym_token12] = SHIFT(75),
        [ts_aux_sym_token13] = SHIFT(75),
        [ts_aux_sym_token14] = SHIFT(75),
        [ts_aux_sym_token15] = SHIFT(75),
        [ts_aux_sym_token16] = SHIFT(75),
        [ts_aux_sym_token18] = SHIFT(77),
        [ts_aux_sym_token21] = SHIFT(81),
        [ts_aux_sym_token22] = SHIFT(83),
        [ts_aux_sym_token23] = SHIFT(475),
    },
    [475] = {
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
    [476] = {
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
    [477] = {
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
        [ts_aux_sym_token19] = SHIFT(478),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [478] = {
        [ts_sym_expression] = SHIFT(479),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [479] = {
        [ts_aux_sym_token2] = SHIFT(24),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(465),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(467),
        [ts_aux_sym_token21] = SHIFT(471),
        [ts_aux_sym_token22] = SHIFT(473),
    },
    [480] = {
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
    [481] = {
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
    [482] = {
        [ts_sym_formal_parameters] = SHIFT(483),
        [ts_sym_identifier] = SHIFT(489),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [483] = {
        [ts_sym_statement_block] = SHIFT(484),
        [ts_aux_sym_token0] = SHIFT(485),
    },
    [484] = {
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
    [485] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(486),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(488),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [486] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(487),
    },
    [487] = {
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
    [488] = {
        [ts_aux_sym_token1] = SHIFT(487),
    },
    [489] = {
        [ts_sym_formal_parameters] = SHIFT(490),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [490] = {
        [ts_sym_statement_block] = SHIFT(491),
        [ts_aux_sym_token0] = SHIFT(485),
    },
    [491] = {
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
    [492] = {
        [ts_builtin_sym_error] = SHIFT(493),
        [ts_sym_string] = SHIFT(496),
        [ts_sym_identifier] = SHIFT(496),
        [ts_aux_sym_token1] = SHIFT(501),
    },
    [493] = {
        [ts_aux_sym_object_repeat0] = SHIFT(494),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [494] = {
        [ts_aux_sym_token1] = SHIFT(495),
    },
    [495] = {
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
    [496] = {
        [ts_aux_sym_token4] = SHIFT(497),
    },
    [497] = {
        [ts_sym_expression] = SHIFT(498),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [498] = {
        [ts_aux_sym_object_repeat0] = SHIFT(499),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [499] = {
        [ts_aux_sym_token1] = SHIFT(500),
    },
    [500] = {
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
    [501] = {
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
    [502] = {
        [ts_sym_expression] = SHIFT(503),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [503] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(504),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [504] = {
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
    [505] = {
        [ts_sym_expression] = SHIFT(506),
        [ts_sym_math_op] = SHIFT(476),
        [ts_sym_bool_op] = SHIFT(476),
        [ts_sym_ternary] = SHIFT(476),
        [ts_sym_assignment] = SHIFT(476),
        [ts_sym_function_expression] = SHIFT(476),
        [ts_sym_function_call] = SHIFT(476),
        [ts_sym_property_access] = SHIFT(477),
        [ts_sym_literal] = SHIFT(480),
        [ts_sym_object] = SHIFT(481),
        [ts_sym_array] = SHIFT(481),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(481),
        [ts_sym_true] = SHIFT(481),
        [ts_sym_false] = SHIFT(481),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(477),
        [ts_sym_number] = SHIFT(481),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [506] = {
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [507] = {
        [ts_sym_expression] = SHIFT(508),
        [ts_sym_math_op] = SHIFT(223),
        [ts_sym_bool_op] = SHIFT(223),
        [ts_sym_ternary] = SHIFT(223),
        [ts_sym_assignment] = SHIFT(223),
        [ts_sym_function_expression] = SHIFT(223),
        [ts_sym_function_call] = SHIFT(223),
        [ts_sym_property_access] = SHIFT(224),
        [ts_sym_literal] = SHIFT(227),
        [ts_sym_object] = SHIFT(228),
        [ts_sym_array] = SHIFT(228),
        [ts_builtin_sym_error] = SHIFT(511),
        [ts_sym__function] = SHIFT(229),
        [ts_sym_null] = SHIFT(228),
        [ts_sym_true] = SHIFT(228),
        [ts_sym_false] = SHIFT(228),
        [ts_sym_string] = SHIFT(228),
        [ts_sym_identifier] = SHIFT(224),
        [ts_sym_number] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(512),
    },
    [508] = {
        [ts_aux_sym_array_repeat0] = SHIFT(509),
        [ts_aux_sym_token2] = SHIFT(145),
        [ts_aux_sym_token5] = SHIFT(151),
        [ts_aux_sym_token6] = SHIFT(151),
        [ts_aux_sym_token7] = SHIFT(153),
        [ts_aux_sym_token8] = SHIFT(153),
        [ts_aux_sym_token9] = SHIFT(155),
        [ts_aux_sym_token10] = SHIFT(157),
        [ts_aux_sym_token11] = SHIFT(157),
        [ts_aux_sym_token12] = SHIFT(157),
        [ts_aux_sym_token13] = SHIFT(157),
        [ts_aux_sym_token14] = SHIFT(157),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(159),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token21] = SHIFT(163),
        [ts_aux_sym_token22] = SHIFT(165),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [509] = {
        [ts_aux_sym_token23] = SHIFT(510),
    },
    [510] = {
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
    [511] = {
        [ts_aux_sym_array_repeat0] = SHIFT(509),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [512] = {
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
    [513] = {
        [ts_sym_expression] = SHIFT(514),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym__terminator] = SHIFT(516),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [514] = {
        [ts_sym__terminator] = SHIFT(515),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [515] = {
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
    [516] = {
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
    [517] = {
        [ts_sym__terminator] = SHIFT(518),
    },
    [518] = {
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
    [519] = {
        [ts_aux_sym_token2] = SHIFT(520),
    },
    [520] = {
        [ts_sym_var_declaration] = SHIFT(521),
        [ts_sym_expression_statement] = SHIFT(521),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [521] = {
        [ts_sym_expression_statement] = SHIFT(522),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [522] = {
        [ts_sym_expression] = SHIFT(523),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(605),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [523] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(524),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [524] = {
        [ts_sym_statement] = SHIFT(525),
        [ts_sym_statement_block] = SHIFT(287),
        [ts_sym_for_statement] = SHIFT(287),
        [ts_sym_if_statement] = SHIFT(287),
        [ts_sym_switch_statement] = SHIFT(287),
        [ts_sym_break_statement] = SHIFT(287),
        [ts_sym_var_declaration] = SHIFT(287),
        [ts_sym_expression_statement] = SHIFT(287),
        [ts_sym_return_statement] = SHIFT(287),
        [ts_sym_delete_statement] = SHIFT(287),
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(290),
        [ts_sym__delete] = SHIFT(291),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(287),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [525] = {
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
    [526] = {
        [ts_aux_sym_token2] = SHIFT(527),
    },
    [527] = {
        [ts_sym_expression] = SHIFT(528),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [528] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(529),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [529] = {
        [ts_sym_statement] = SHIFT(530),
        [ts_sym_statement_block] = SHIFT(552),
        [ts_sym_for_statement] = SHIFT(552),
        [ts_sym_if_statement] = SHIFT(552),
        [ts_sym_switch_statement] = SHIFT(552),
        [ts_sym_break_statement] = SHIFT(552),
        [ts_sym_var_declaration] = SHIFT(552),
        [ts_sym_expression_statement] = SHIFT(552),
        [ts_sym_return_statement] = SHIFT(552),
        [ts_sym_delete_statement] = SHIFT(552),
        [ts_sym_expression] = SHIFT(553),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(591),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [530] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(531),
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
    [531] = {
        [ts_sym_statement] = SHIFT(532),
        [ts_sym_statement_block] = SHIFT(287),
        [ts_sym_for_statement] = SHIFT(287),
        [ts_sym_if_statement] = SHIFT(287),
        [ts_sym_switch_statement] = SHIFT(287),
        [ts_sym_break_statement] = SHIFT(287),
        [ts_sym_var_declaration] = SHIFT(287),
        [ts_sym_expression_statement] = SHIFT(287),
        [ts_sym_return_statement] = SHIFT(287),
        [ts_sym_delete_statement] = SHIFT(287),
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(290),
        [ts_sym__delete] = SHIFT(291),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(287),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [532] = {
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
    [533] = {
        [ts_aux_sym_token2] = SHIFT(534),
    },
    [534] = {
        [ts_sym_expression] = SHIFT(535),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(551),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [535] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(536),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [536] = {
        [ts_aux_sym_token0] = SHIFT(537),
    },
    [537] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(549),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [538] = {
        [ts_aux_sym_token4] = SHIFT(539),
    },
    [539] = {
        [ts_sym_statement] = SHIFT(286),
        [ts_sym_statement_block] = SHIFT(287),
        [ts_sym_for_statement] = SHIFT(287),
        [ts_sym_if_statement] = SHIFT(287),
        [ts_sym_switch_statement] = SHIFT(287),
        [ts_sym_break_statement] = SHIFT(287),
        [ts_sym_var_declaration] = SHIFT(287),
        [ts_sym_expression_statement] = SHIFT(287),
        [ts_sym_return_statement] = SHIFT(287),
        [ts_sym_delete_statement] = SHIFT(287),
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(290),
        [ts_sym__delete] = SHIFT(291),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(287),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(544),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [540] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(541),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(543),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [541] = {
        [ts_sym__terminator] = SHIFT(542),
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
    [542] = {
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
    [543] = {
        [ts_sym__terminator] = SHIFT(542),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [544] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 3),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
    },
    [545] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(546),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(548),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [546] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = SHIFT(547),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [547] = {
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
    [548] = {
        [ts_aux_sym_token1] = SHIFT(547),
    },
    [549] = {
        [ts_aux_sym_token1] = SHIFT(550),
    },
    [550] = {
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
    [551] = {
        [ts_aux_sym_token3] = SHIFT(536),
    },
    [552] = {
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
    [553] = {
        [ts_sym__terminator] = SHIFT(554),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [554] = {
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
    [555] = {
        [ts_sym__terminator] = SHIFT(554),
    },
    [556] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(557),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [557] = {
        [ts_sym__terminator] = SHIFT(558),
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [558] = {
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
    [559] = {
        [ts_sym_expression] = SHIFT(560),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym__terminator] = SHIFT(562),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [560] = {
        [ts_sym__terminator] = SHIFT(561),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [561] = {
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
    [562] = {
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
    [563] = {
        [ts_sym__terminator] = SHIFT(564),
    },
    [564] = {
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
    [565] = {
        [ts_aux_sym_token2] = SHIFT(566),
    },
    [566] = {
        [ts_sym_var_declaration] = SHIFT(567),
        [ts_sym_expression_statement] = SHIFT(567),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [567] = {
        [ts_sym_expression_statement] = SHIFT(568),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [568] = {
        [ts_sym_expression] = SHIFT(569),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(596),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [569] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(570),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [570] = {
        [ts_sym_statement] = SHIFT(571),
        [ts_sym_statement_block] = SHIFT(552),
        [ts_sym_for_statement] = SHIFT(552),
        [ts_sym_if_statement] = SHIFT(552),
        [ts_sym_switch_statement] = SHIFT(552),
        [ts_sym_break_statement] = SHIFT(552),
        [ts_sym_var_declaration] = SHIFT(552),
        [ts_sym_expression_statement] = SHIFT(552),
        [ts_sym_return_statement] = SHIFT(552),
        [ts_sym_delete_statement] = SHIFT(552),
        [ts_sym_expression] = SHIFT(553),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(591),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [571] = {
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
    [572] = {
        [ts_aux_sym_token2] = SHIFT(573),
    },
    [573] = {
        [ts_sym_expression] = SHIFT(574),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(595),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [574] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(575),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [575] = {
        [ts_sym_statement] = SHIFT(576),
        [ts_sym_statement_block] = SHIFT(552),
        [ts_sym_for_statement] = SHIFT(552),
        [ts_sym_if_statement] = SHIFT(552),
        [ts_sym_switch_statement] = SHIFT(552),
        [ts_sym_break_statement] = SHIFT(552),
        [ts_sym_var_declaration] = SHIFT(552),
        [ts_sym_expression_statement] = SHIFT(552),
        [ts_sym_return_statement] = SHIFT(552),
        [ts_sym_delete_statement] = SHIFT(552),
        [ts_sym_expression] = SHIFT(553),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(591),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [576] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__case] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__default] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(577),
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
    [577] = {
        [ts_sym_statement] = SHIFT(578),
        [ts_sym_statement_block] = SHIFT(552),
        [ts_sym_for_statement] = SHIFT(552),
        [ts_sym_if_statement] = SHIFT(552),
        [ts_sym_switch_statement] = SHIFT(552),
        [ts_sym_break_statement] = SHIFT(552),
        [ts_sym_var_declaration] = SHIFT(552),
        [ts_sym_expression_statement] = SHIFT(552),
        [ts_sym_return_statement] = SHIFT(552),
        [ts_sym_delete_statement] = SHIFT(552),
        [ts_sym_expression] = SHIFT(553),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(591),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [578] = {
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
    [579] = {
        [ts_aux_sym_token2] = SHIFT(580),
    },
    [580] = {
        [ts_sym_expression] = SHIFT(581),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(586),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [581] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(582),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [582] = {
        [ts_aux_sym_token0] = SHIFT(583),
    },
    [583] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(584),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [584] = {
        [ts_aux_sym_token1] = SHIFT(585),
    },
    [585] = {
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
    [586] = {
        [ts_aux_sym_token3] = SHIFT(582),
    },
    [587] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(588),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(590),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [588] = {
        [ts_sym__terminator] = SHIFT(589),
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
    [589] = {
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
    [590] = {
        [ts_sym__terminator] = SHIFT(589),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [591] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(592),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(594),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [592] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = SHIFT(593),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [593] = {
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
    [594] = {
        [ts_aux_sym_token1] = SHIFT(593),
    },
    [595] = {
        [ts_aux_sym_token3] = SHIFT(575),
    },
    [596] = {
        [ts_aux_sym_token3] = SHIFT(570),
    },
    [597] = {
        [ts_sym__terminator] = SHIFT(598),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [598] = {
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
    [599] = {
        [ts_sym__terminator] = SHIFT(598),
    },
    [600] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(601),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(603),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [601] = {
        [ts_sym__terminator] = SHIFT(602),
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
    [602] = {
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
    [603] = {
        [ts_sym__terminator] = SHIFT(602),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [604] = {
        [ts_aux_sym_token3] = SHIFT(529),
    },
    [605] = {
        [ts_aux_sym_token3] = SHIFT(524),
    },
    [606] = {
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [607] = {
        [ts_sym__case] = REDUCE(ts_sym_switch_case, 4),
        [ts_sym__default] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
    },
    [608] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [609] = {
        [ts_aux_sym_token1] = SHIFT(610),
    },
    [610] = {
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
    [611] = {
        [ts_aux_sym_token3] = SHIFT(280),
    },
    [612] = {
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
    [613] = {
        [ts_sym__terminator] = SHIFT(614),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [614] = {
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
    [615] = {
        [ts_sym__terminator] = SHIFT(614),
    },
    [616] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(617),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [617] = {
        [ts_sym__terminator] = SHIFT(618),
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [618] = {
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
    [619] = {
        [ts_sym_expression] = SHIFT(620),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym__terminator] = SHIFT(622),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [620] = {
        [ts_sym__terminator] = SHIFT(621),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [621] = {
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
    [622] = {
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
    [623] = {
        [ts_sym__terminator] = SHIFT(624),
    },
    [624] = {
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
    [625] = {
        [ts_aux_sym_token2] = SHIFT(626),
    },
    [626] = {
        [ts_sym_var_declaration] = SHIFT(627),
        [ts_sym_expression_statement] = SHIFT(627),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [627] = {
        [ts_sym_expression_statement] = SHIFT(628),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [628] = {
        [ts_sym_expression] = SHIFT(629),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(656),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [629] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(630),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [630] = {
        [ts_sym_statement] = SHIFT(631),
        [ts_sym_statement_block] = SHIFT(612),
        [ts_sym_for_statement] = SHIFT(612),
        [ts_sym_if_statement] = SHIFT(612),
        [ts_sym_switch_statement] = SHIFT(612),
        [ts_sym_break_statement] = SHIFT(612),
        [ts_sym_var_declaration] = SHIFT(612),
        [ts_sym_expression_statement] = SHIFT(612),
        [ts_sym_return_statement] = SHIFT(612),
        [ts_sym_delete_statement] = SHIFT(612),
        [ts_sym_expression] = SHIFT(613),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(651),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [631] = {
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
    [632] = {
        [ts_aux_sym_token2] = SHIFT(633),
    },
    [633] = {
        [ts_sym_expression] = SHIFT(634),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(655),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [634] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(635),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [635] = {
        [ts_sym_statement] = SHIFT(636),
        [ts_sym_statement_block] = SHIFT(612),
        [ts_sym_for_statement] = SHIFT(612),
        [ts_sym_if_statement] = SHIFT(612),
        [ts_sym_switch_statement] = SHIFT(612),
        [ts_sym_break_statement] = SHIFT(612),
        [ts_sym_var_declaration] = SHIFT(612),
        [ts_sym_expression_statement] = SHIFT(612),
        [ts_sym_return_statement] = SHIFT(612),
        [ts_sym_delete_statement] = SHIFT(612),
        [ts_sym_expression] = SHIFT(613),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(651),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [636] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(637),
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
    [637] = {
        [ts_sym_statement] = SHIFT(638),
        [ts_sym_statement_block] = SHIFT(612),
        [ts_sym_for_statement] = SHIFT(612),
        [ts_sym_if_statement] = SHIFT(612),
        [ts_sym_switch_statement] = SHIFT(612),
        [ts_sym_break_statement] = SHIFT(612),
        [ts_sym_var_declaration] = SHIFT(612),
        [ts_sym_expression_statement] = SHIFT(612),
        [ts_sym_return_statement] = SHIFT(612),
        [ts_sym_delete_statement] = SHIFT(612),
        [ts_sym_expression] = SHIFT(613),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(651),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [638] = {
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
    [639] = {
        [ts_aux_sym_token2] = SHIFT(640),
    },
    [640] = {
        [ts_sym_expression] = SHIFT(641),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(646),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [641] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(642),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [642] = {
        [ts_aux_sym_token0] = SHIFT(643),
    },
    [643] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(644),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [644] = {
        [ts_aux_sym_token1] = SHIFT(645),
    },
    [645] = {
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
    [646] = {
        [ts_aux_sym_token3] = SHIFT(642),
    },
    [647] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(648),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(650),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [648] = {
        [ts_sym__terminator] = SHIFT(649),
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
    [649] = {
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
    [650] = {
        [ts_sym__terminator] = SHIFT(649),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [651] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(652),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(654),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [652] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = SHIFT(653),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [653] = {
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
    [654] = {
        [ts_aux_sym_token1] = SHIFT(653),
    },
    [655] = {
        [ts_aux_sym_token3] = SHIFT(635),
    },
    [656] = {
        [ts_aux_sym_token3] = SHIFT(630),
    },
    [657] = {
        [ts_aux_sym_token3] = SHIFT(273),
    },
    [658] = {
        [ts_aux_sym_token3] = SHIFT(267),
    },
    [659] = {
        [ts_aux_sym_token1] = SHIFT(259),
    },
    [660] = {
        [ts_sym_formal_parameters] = SHIFT(661),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [661] = {
        [ts_sym_statement_block] = SHIFT(662),
        [ts_aux_sym_token0] = SHIFT(257),
    },
    [662] = {
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
    [663] = {
        [ts_aux_sym_token1] = SHIFT(234),
    },
    [664] = {
        [ts_sym_formal_parameters] = SHIFT(665),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [665] = {
        [ts_sym_statement_block] = SHIFT(666),
        [ts_aux_sym_token0] = SHIFT(232),
    },
    [666] = {
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
    [667] = {
        [ts_aux_sym_array_repeat0] = SHIFT(222),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [668] = {
        [ts_aux_sym_array_repeat0] = SHIFT(218),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [669] = {
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
    [670] = {
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
    [671] = {
        [ts_aux_sym_array_repeat0] = SHIFT(143),
        [ts_aux_sym_token20] = SHIFT(220),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [672] = {
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
    [673] = {
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
    [674] = {
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
    [675] = {
        [ts_aux_sym_token4] = SHIFT(676),
    },
    [676] = {
        [ts_sym_expression] = SHIFT(677),
        [ts_sym_math_op] = SHIFT(248),
        [ts_sym_bool_op] = SHIFT(248),
        [ts_sym_ternary] = SHIFT(248),
        [ts_sym_assignment] = SHIFT(248),
        [ts_sym_function_expression] = SHIFT(248),
        [ts_sym_function_call] = SHIFT(248),
        [ts_sym_property_access] = SHIFT(249),
        [ts_sym_literal] = SHIFT(252),
        [ts_sym_object] = SHIFT(253),
        [ts_sym_array] = SHIFT(253),
        [ts_sym__function] = SHIFT(254),
        [ts_sym_null] = SHIFT(253),
        [ts_sym_true] = SHIFT(253),
        [ts_sym_false] = SHIFT(253),
        [ts_sym_string] = SHIFT(253),
        [ts_sym_identifier] = SHIFT(249),
        [ts_sym_number] = SHIFT(253),
        [ts_aux_sym_token0] = SHIFT(338),
        [ts_aux_sym_token2] = SHIFT(347),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [677] = {
        [ts_aux_sym_object_repeat0] = SHIFT(678),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(177),
        [ts_aux_sym_token7] = SHIFT(179),
        [ts_aux_sym_token8] = SHIFT(179),
        [ts_aux_sym_token9] = SHIFT(181),
        [ts_aux_sym_token10] = SHIFT(183),
        [ts_aux_sym_token11] = SHIFT(183),
        [ts_aux_sym_token12] = SHIFT(183),
        [ts_aux_sym_token13] = SHIFT(183),
        [ts_aux_sym_token14] = SHIFT(183),
        [ts_aux_sym_token15] = SHIFT(183),
        [ts_aux_sym_token16] = SHIFT(183),
        [ts_aux_sym_token18] = SHIFT(185),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(189),
        [ts_aux_sym_token22] = SHIFT(191),
    },
    [678] = {
        [ts_aux_sym_token1] = SHIFT(679),
    },
    [679] = {
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
    [680] = {
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
    [681] = {
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
    [682] = {
        [ts_sym__terminator] = SHIFT(683),
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [683] = {
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
    [684] = {
        [ts_aux_sym_token1] = SHIFT(107),
    },
    [685] = {
        [ts_sym_formal_parameters] = SHIFT(686),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [686] = {
        [ts_sym_statement_block] = SHIFT(687),
        [ts_aux_sym_token0] = SHIFT(105),
    },
    [687] = {
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
    [688] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(689),
    },
    [689] = {
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
    [690] = {
        [ts_aux_sym_token1] = SHIFT(689),
    },
    [691] = {
        [ts_sym_formal_parameters] = SHIFT(692),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [692] = {
        [ts_sym_statement_block] = SHIFT(693),
        [ts_aux_sym_token0] = SHIFT(95),
    },
    [693] = {
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
    [694] = {
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
    [695] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [696] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(697),
    },
    [697] = {
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
    [698] = {
        [ts_aux_sym_token1] = SHIFT(697),
    },
    [699] = {
        [ts_sym_formal_parameters] = SHIFT(700),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [700] = {
        [ts_sym_statement_block] = SHIFT(701),
        [ts_aux_sym_token0] = SHIFT(48),
    },
    [701] = {
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
    [702] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(37),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [703] = {
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
    [704] = {
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
    [705] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(30),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [706] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(26),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [707] = {
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
    [708] = {
        [ts_sym_expression] = SHIFT(709),
        [ts_sym_math_op] = SHIFT(39),
        [ts_sym_bool_op] = SHIFT(39),
        [ts_sym_ternary] = SHIFT(39),
        [ts_sym_assignment] = SHIFT(39),
        [ts_sym_function_expression] = SHIFT(39),
        [ts_sym_function_call] = SHIFT(39),
        [ts_sym_property_access] = SHIFT(40),
        [ts_sym_literal] = SHIFT(43),
        [ts_sym_object] = SHIFT(44),
        [ts_sym_array] = SHIFT(44),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(44),
        [ts_sym_true] = SHIFT(44),
        [ts_sym_false] = SHIFT(44),
        [ts_sym_string] = SHIFT(44),
        [ts_sym_identifier] = SHIFT(40),
        [ts_sym_number] = SHIFT(44),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
    },
    [709] = {
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
        [ts_aux_sym_token14] = SHIFT(20),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(22),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(31),
        [ts_aux_sym_token22] = SHIFT(33),
    },
    [710] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [711] = {
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
    [712] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(28),
    },
    [713] = {
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
    [714] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [715] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(716),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [716] = {
        [ts_sym__terminator] = SHIFT(717),
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [717] = {
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
    [718] = {
        [ts_sym_expression] = SHIFT(719),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym__terminator] = SHIFT(721),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [719] = {
        [ts_sym__terminator] = SHIFT(720),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [720] = {
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
    [721] = {
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
    [722] = {
        [ts_sym__terminator] = SHIFT(723),
    },
    [723] = {
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
    [724] = {
        [ts_aux_sym_token2] = SHIFT(725),
    },
    [725] = {
        [ts_sym_var_declaration] = SHIFT(726),
        [ts_sym_expression_statement] = SHIFT(726),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [726] = {
        [ts_sym_expression_statement] = SHIFT(727),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [727] = {
        [ts_sym_expression] = SHIFT(728),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(800),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [728] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(729),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [729] = {
        [ts_sym_statement] = SHIFT(730),
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
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym__delete] = SHIFT(715),
        [ts_sym__return] = SHIFT(718),
        [ts_sym__break] = SHIFT(722),
        [ts_sym__for] = SHIFT(724),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(731),
        [ts_sym__switch] = SHIFT(738),
        [ts_sym__var] = SHIFT(746),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(750),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [730] = {
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
    [731] = {
        [ts_aux_sym_token2] = SHIFT(732),
    },
    [732] = {
        [ts_sym_expression] = SHIFT(733),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(799),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [733] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(734),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [734] = {
        [ts_sym_statement] = SHIFT(735),
        [ts_sym_statement_block] = SHIFT(754),
        [ts_sym_for_statement] = SHIFT(754),
        [ts_sym_if_statement] = SHIFT(754),
        [ts_sym_switch_statement] = SHIFT(754),
        [ts_sym_break_statement] = SHIFT(754),
        [ts_sym_var_declaration] = SHIFT(754),
        [ts_sym_expression_statement] = SHIFT(754),
        [ts_sym_return_statement] = SHIFT(754),
        [ts_sym_delete_statement] = SHIFT(754),
        [ts_sym_expression] = SHIFT(755),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(793),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [735] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(736),
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
    [736] = {
        [ts_sym_statement] = SHIFT(737),
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
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym__delete] = SHIFT(715),
        [ts_sym__return] = SHIFT(718),
        [ts_sym__break] = SHIFT(722),
        [ts_sym__for] = SHIFT(724),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(731),
        [ts_sym__switch] = SHIFT(738),
        [ts_sym__var] = SHIFT(746),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(750),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [737] = {
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
    [738] = {
        [ts_aux_sym_token2] = SHIFT(739),
    },
    [739] = {
        [ts_sym_expression] = SHIFT(740),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(745),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [740] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(741),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [741] = {
        [ts_aux_sym_token0] = SHIFT(742),
    },
    [742] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(743),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [743] = {
        [ts_aux_sym_token1] = SHIFT(744),
    },
    [744] = {
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
    [745] = {
        [ts_aux_sym_token3] = SHIFT(741),
    },
    [746] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(747),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(749),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [747] = {
        [ts_sym__terminator] = SHIFT(748),
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
    [748] = {
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
    [749] = {
        [ts_sym__terminator] = SHIFT(748),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [750] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(751),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(753),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [751] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = SHIFT(752),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [752] = {
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
    [753] = {
        [ts_aux_sym_token1] = SHIFT(752),
    },
    [754] = {
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
    [755] = {
        [ts_sym__terminator] = SHIFT(756),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [756] = {
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
    [757] = {
        [ts_sym__terminator] = SHIFT(756),
    },
    [758] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(292),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(759),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(314),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [759] = {
        [ts_sym__terminator] = SHIFT(760),
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
        [ts_aux_sym_token19] = SHIFT(295),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [760] = {
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
    [761] = {
        [ts_sym_expression] = SHIFT(762),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym__terminator] = SHIFT(764),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [762] = {
        [ts_sym__terminator] = SHIFT(763),
        [ts_aux_sym_token2] = SHIFT(6),
        [ts_aux_sym_token5] = SHIFT(53),
        [ts_aux_sym_token6] = SHIFT(53),
        [ts_aux_sym_token7] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(55),
        [ts_aux_sym_token9] = SHIFT(57),
        [ts_aux_sym_token10] = SHIFT(59),
        [ts_aux_sym_token11] = SHIFT(59),
        [ts_aux_sym_token12] = SHIFT(59),
        [ts_aux_sym_token13] = SHIFT(59),
        [ts_aux_sym_token14] = SHIFT(59),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(61),
        [ts_aux_sym_token21] = SHIFT(65),
        [ts_aux_sym_token22] = SHIFT(67),
    },
    [763] = {
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
    [764] = {
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
    [765] = {
        [ts_sym__terminator] = SHIFT(766),
    },
    [766] = {
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
    [767] = {
        [ts_aux_sym_token2] = SHIFT(768),
    },
    [768] = {
        [ts_sym_var_declaration] = SHIFT(769),
        [ts_sym_expression_statement] = SHIFT(769),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [769] = {
        [ts_sym_expression_statement] = SHIFT(770),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [770] = {
        [ts_sym_expression] = SHIFT(771),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(798),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [771] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(772),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [772] = {
        [ts_sym_statement] = SHIFT(773),
        [ts_sym_statement_block] = SHIFT(754),
        [ts_sym_for_statement] = SHIFT(754),
        [ts_sym_if_statement] = SHIFT(754),
        [ts_sym_switch_statement] = SHIFT(754),
        [ts_sym_break_statement] = SHIFT(754),
        [ts_sym_var_declaration] = SHIFT(754),
        [ts_sym_expression_statement] = SHIFT(754),
        [ts_sym_return_statement] = SHIFT(754),
        [ts_sym_delete_statement] = SHIFT(754),
        [ts_sym_expression] = SHIFT(755),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(793),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [773] = {
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
    [774] = {
        [ts_aux_sym_token2] = SHIFT(775),
    },
    [775] = {
        [ts_sym_expression] = SHIFT(776),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(797),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [776] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(777),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [777] = {
        [ts_sym_statement] = SHIFT(778),
        [ts_sym_statement_block] = SHIFT(754),
        [ts_sym_for_statement] = SHIFT(754),
        [ts_sym_if_statement] = SHIFT(754),
        [ts_sym_switch_statement] = SHIFT(754),
        [ts_sym_break_statement] = SHIFT(754),
        [ts_sym_var_declaration] = SHIFT(754),
        [ts_sym_expression_statement] = SHIFT(754),
        [ts_sym_return_statement] = SHIFT(754),
        [ts_sym_delete_statement] = SHIFT(754),
        [ts_sym_expression] = SHIFT(755),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(793),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [778] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(779),
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
    [779] = {
        [ts_sym_statement] = SHIFT(780),
        [ts_sym_statement_block] = SHIFT(754),
        [ts_sym_for_statement] = SHIFT(754),
        [ts_sym_if_statement] = SHIFT(754),
        [ts_sym_switch_statement] = SHIFT(754),
        [ts_sym_break_statement] = SHIFT(754),
        [ts_sym_var_declaration] = SHIFT(754),
        [ts_sym_expression_statement] = SHIFT(754),
        [ts_sym_return_statement] = SHIFT(754),
        [ts_sym_delete_statement] = SHIFT(754),
        [ts_sym_expression] = SHIFT(755),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_string] = SHIFT(101),
        [ts_sym_identifier] = SHIFT(97),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_token0] = SHIFT(793),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [780] = {
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
    [781] = {
        [ts_aux_sym_token2] = SHIFT(782),
    },
    [782] = {
        [ts_sym_expression] = SHIFT(783),
        [ts_sym_math_op] = SHIFT(350),
        [ts_sym_bool_op] = SHIFT(350),
        [ts_sym_ternary] = SHIFT(350),
        [ts_sym_assignment] = SHIFT(350),
        [ts_sym_function_expression] = SHIFT(350),
        [ts_sym_function_call] = SHIFT(350),
        [ts_sym_property_access] = SHIFT(351),
        [ts_sym_literal] = SHIFT(354),
        [ts_sym_object] = SHIFT(355),
        [ts_sym_array] = SHIFT(355),
        [ts_builtin_sym_error] = SHIFT(788),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(355),
        [ts_sym_true] = SHIFT(355),
        [ts_sym_false] = SHIFT(355),
        [ts_sym_string] = SHIFT(355),
        [ts_sym_identifier] = SHIFT(351),
        [ts_sym_number] = SHIFT(355),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [783] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(784),
        [ts_aux_sym_token5] = SHIFT(197),
        [ts_aux_sym_token6] = SHIFT(197),
        [ts_aux_sym_token7] = SHIFT(199),
        [ts_aux_sym_token8] = SHIFT(199),
        [ts_aux_sym_token9] = SHIFT(201),
        [ts_aux_sym_token10] = SHIFT(203),
        [ts_aux_sym_token11] = SHIFT(203),
        [ts_aux_sym_token12] = SHIFT(203),
        [ts_aux_sym_token13] = SHIFT(203),
        [ts_aux_sym_token14] = SHIFT(203),
        [ts_aux_sym_token15] = SHIFT(203),
        [ts_aux_sym_token16] = SHIFT(203),
        [ts_aux_sym_token18] = SHIFT(205),
        [ts_aux_sym_token21] = SHIFT(209),
        [ts_aux_sym_token22] = SHIFT(211),
    },
    [784] = {
        [ts_aux_sym_token0] = SHIFT(785),
    },
    [785] = {
        [ts_sym_switch_case] = SHIFT(282),
        [ts_sym__case] = SHIFT(283),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(786),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [786] = {
        [ts_aux_sym_token1] = SHIFT(787),
    },
    [787] = {
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
    [788] = {
        [ts_aux_sym_token3] = SHIFT(784),
    },
    [789] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(292),
        [ts_sym_bool_op] = SHIFT(292),
        [ts_sym_ternary] = SHIFT(292),
        [ts_sym_assignment] = SHIFT(790),
        [ts_sym_function_expression] = SHIFT(292),
        [ts_sym_function_call] = SHIFT(292),
        [ts_sym_property_access] = SHIFT(327),
        [ts_sym_literal] = SHIFT(315),
        [ts_sym_object] = SHIFT(316),
        [ts_sym_array] = SHIFT(316),
        [ts_sym__function] = SHIFT(317),
        [ts_sym_null] = SHIFT(316),
        [ts_sym_true] = SHIFT(316),
        [ts_sym_false] = SHIFT(316),
        [ts_sym_string] = SHIFT(316),
        [ts_sym_identifier] = SHIFT(792),
        [ts_sym_number] = SHIFT(316),
        [ts_aux_sym_token0] = SHIFT(329),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [790] = {
        [ts_sym__terminator] = SHIFT(791),
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
    [791] = {
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
    [792] = {
        [ts_sym__terminator] = SHIFT(791),
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
        [ts_aux_sym_token19] = SHIFT(98),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [793] = {
        [ts_sym_statement] = SHIFT(49),
        [ts_sym_statement_block] = SHIFT(50),
        [ts_sym_for_statement] = SHIFT(50),
        [ts_sym_if_statement] = SHIFT(50),
        [ts_sym_switch_statement] = SHIFT(50),
        [ts_sym_break_statement] = SHIFT(50),
        [ts_sym_var_declaration] = SHIFT(50),
        [ts_sym_expression_statement] = SHIFT(50),
        [ts_sym_return_statement] = SHIFT(50),
        [ts_sym_delete_statement] = SHIFT(50),
        [ts_sym_expression] = SHIFT(51),
        [ts_sym_math_op] = SHIFT(96),
        [ts_sym_bool_op] = SHIFT(96),
        [ts_sym_ternary] = SHIFT(96),
        [ts_sym_assignment] = SHIFT(96),
        [ts_sym_function_expression] = SHIFT(96),
        [ts_sym_function_call] = SHIFT(96),
        [ts_sym_property_access] = SHIFT(97),
        [ts_sym_literal] = SHIFT(100),
        [ts_sym_object] = SHIFT(101),
        [ts_sym_array] = SHIFT(101),
        [ts_builtin_sym_error] = SHIFT(794),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(235),
        [ts_sym__break] = SHIFT(260),
        [ts_sym__for] = SHIFT(262),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(270),
        [ts_sym__switch] = SHIFT(277),
        [ts_sym__var] = SHIFT(323),
        [ts_sym_null] = SHIFT(101),
        [ts_sym_true] = SHIFT(101),
        [ts_sym_false] = SHIFT(101),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(101),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(796),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [794] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(241),
        [ts_aux_sym_token1] = SHIFT(795),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [795] = {
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
    [796] = {
        [ts_aux_sym_token1] = SHIFT(795),
    },
    [797] = {
        [ts_aux_sym_token3] = SHIFT(777),
    },
    [798] = {
        [ts_aux_sym_token3] = SHIFT(772),
    },
    [799] = {
        [ts_aux_sym_token3] = SHIFT(734),
    },
    [800] = {
        [ts_aux_sym_token3] = SHIFT(729),
    },
    [801] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [802] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
