#include "tree_sitter/parser.h"

#define STATE_COUNT 819
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
    ts_sym_object = 23,
    ts_sym_array = 24,
    ts_sym_comment = 25,
    ts_sym__terminator = 26,
    ts_sym_regex = 27,
    ts_sym_string = 28,
    ts_sym_identifier = 29,
    ts_sym_number = 30,
    ts_sym_null = 31,
    ts_sym_true = 32,
    ts_sym_false = 33,
    ts_aux_sym_program_repeat0 = 34,
    ts_aux_sym_statement_block_repeat0 = 35,
    ts_aux_sym_switch_statement_repeat0 = 36,
    ts_aux_sym_switch_case_repeat0 = 37,
    ts_aux_sym_function_call_repeat0 = 38,
    ts_aux_sym_formal_parameters_repeat0 = 39,
    ts_aux_sym_object_repeat0 = 40,
    ts_aux_sym_array_repeat0 = 41,
    ts_aux_sym_token0 = 42,
    ts_aux_sym_token1 = 43,
    ts_aux_sym_token2 = 44,
    ts_aux_sym_token3 = 45,
    ts_aux_sym_token4 = 46,
    ts_aux_sym_token5 = 47,
    ts_aux_sym_token6 = 48,
    ts_aux_sym_token7 = 49,
    ts_aux_sym_token8 = 50,
    ts_aux_sym_token9 = 51,
    ts_aux_sym_token10 = 52,
    ts_aux_sym_token11 = 53,
    ts_aux_sym_token12 = 54,
    ts_aux_sym_token13 = 55,
    ts_aux_sym_token14 = 56,
    ts_aux_sym_token15 = 57,
    ts_aux_sym_token16 = 58,
    ts_aux_sym_token17 = 59,
    ts_aux_sym_token18 = 60,
    ts_aux_sym_token19 = 61,
    ts_aux_sym_token20 = 62,
    ts_aux_sym_token21 = 63,
    ts_aux_sym_token22 = 64,
    ts_aux_sym_token23 = 65,
    ts_aux_sym_token24 = 66,
    ts_aux_sym_token25 = 67,
    ts_aux_sym_token26 = 68,
    ts_aux_sym_token27 = 69,
    ts_aux_sym_token28 = 70,
    ts_aux_sym_token29 = 71,
    ts_aux_sym_token30 = 72,
    ts_aux_sym_token31 = 73,
    ts_aux_sym_token32 = 74,
    ts_aux_sym_token33 = 75,
    ts_aux_sym_token34 = 76,
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
    [ts_sym_object] = "object",
    [ts_sym_array] = "array",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym_comment] = "comment",
    [ts_sym__terminator] = "_terminator",
    [ts_sym_regex] = "regex",
    [ts_sym_string] = "string",
    [ts_sym_identifier] = "identifier",
    [ts_sym_number] = "number",
    [ts_sym_null] = "null",
    [ts_sym_true] = "true",
    [ts_sym_false] = "false",
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
    [ts_aux_sym_token2] = "",
    [ts_aux_sym_token3] = "'('",
    [ts_aux_sym_token4] = "')'",
    [ts_aux_sym_token5] = "",
    [ts_aux_sym_token6] = "",
    [ts_aux_sym_token7] = "",
    [ts_aux_sym_token8] = "",
    [ts_aux_sym_token9] = "",
    [ts_aux_sym_token10] = "':'",
    [ts_aux_sym_token11] = "",
    [ts_aux_sym_token12] = "",
    [ts_aux_sym_token13] = "",
    [ts_aux_sym_token14] = "",
    [ts_aux_sym_token15] = "'+'",
    [ts_aux_sym_token16] = "'-'",
    [ts_aux_sym_token17] = "'*'",
    [ts_aux_sym_token18] = "'/'",
    [ts_aux_sym_token19] = "'||'",
    [ts_aux_sym_token20] = "'&&'",
    [ts_aux_sym_token21] = "'==='",
    [ts_aux_sym_token22] = "'=='",
    [ts_aux_sym_token23] = "'<='",
    [ts_aux_sym_token24] = "'<'",
    [ts_aux_sym_token25] = "'>='",
    [ts_aux_sym_token26] = "'>'",
    [ts_aux_sym_token27] = "'!'",
    [ts_aux_sym_token28] = "'?'",
    [ts_aux_sym_token29] = "'='",
    [ts_aux_sym_token30] = "",
    [ts_aux_sym_token31] = "','",
    [ts_aux_sym_token32] = "'.'",
    [ts_aux_sym_token33] = "'['",
    [ts_aux_sym_token34] = "']'",
};

HIDDEN_SYMBOLS = {
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
    [ts_aux_sym_token24] = 1,
    [ts_aux_sym_token25] = 1,
    [ts_aux_sym_token26] = 1,
    [ts_aux_sym_token27] = 1,
    [ts_aux_sym_token28] = 1,
    [ts_aux_sym_token29] = 1,
    [ts_aux_sym_token30] = 1,
    [ts_aux_sym_token31] = 1,
    [ts_aux_sym_token32] = 1,
    [ts_aux_sym_token33] = 1,
    [ts_aux_sym_token34] = 1,
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'd')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_token27);
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
            if (!((lookahead == '\'') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            LEX_ERROR();
        case 11:
            if (!((lookahead == '\'') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\'')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (!((lookahead == '\'') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\'')
                ADVANCE(13);
            if (lookahead == '\\')
                ADVANCE(12);
            LEX_ERROR();
        case 13:
            if (!((lookahead == '\'') ||
                (lookahead == '\\')))
                ADVANCE(11);
            if (lookahead == '\'')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym_string);
        case 14:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 15:
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 16:
            ACCEPT_TOKEN(ts_aux_sym_token16);
        case 17:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 18:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(19);
            if (lookahead == '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_sym_regex);
        case 20:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(21);
            if (lookahead == '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 21:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(19);
            if (lookahead == '\\')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_regex);
        case 22:
            if (!(lookahead == '\n'))
                ADVANCE(22);
            ACCEPT_TOKEN(ts_sym_comment);
        case 23:
            if (lookahead == '.')
                ADVANCE(24);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            LEX_ERROR();
        case 25:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_number);
        case 26:
            ACCEPT_TOKEN(ts_aux_sym_token33);
        case 27:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'k')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 32:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 33:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 34:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 38:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(39);
            if (lookahead == 'o')
                ADVANCE(43);
            if (lookahead == 'u')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 41:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_false);
        case 43:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'c')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'i')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'o')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token30);
        case 52:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 53:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 54:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 55:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 56:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 57:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_null);
        case 58:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 59:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 60:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 61:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 62:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 63:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 64:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'v') ||
                ('x' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'w')
                ADVANCE(65);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'i')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 67:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'c')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 68:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'h')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 69:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 70:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 71:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(72);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 72:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 73:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_true);
        case 74:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(75);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 75:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 76:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 78:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(79);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(79);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 80:
            if (lookahead == '&')
                ADVANCE(81);
            LEX_ERROR();
        case 81:
            ACCEPT_TOKEN(ts_aux_sym_token20);
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token17);
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_token32);
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 85:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 86:
            if (lookahead == '=')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_aux_sym_token24);
        case 87:
            ACCEPT_TOKEN(ts_aux_sym_token23);
        case 88:
            if (lookahead == '=')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            if (lookahead == '=')
                ADVANCE(90);
            ACCEPT_TOKEN(ts_aux_sym_token22);
        case 90:
            ACCEPT_TOKEN(ts_aux_sym_token21);
        case 91:
            if (lookahead == '=')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_aux_sym_token26);
        case 92:
            ACCEPT_TOKEN(ts_aux_sym_token25);
        case 93:
            ACCEPT_TOKEN(ts_aux_sym_token28);
        case 94:
            if (lookahead == '|')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_token19);
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == ')')
                ADVANCE(97);
            LEX_ERROR();
        case 97:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 98:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(98);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 99:
            ACCEPT_TOKEN(ts_aux_sym_token31);
        case 100:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 101:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 102:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 103:
            if (lookahead == '=')
                ADVANCE(89);
            ACCEPT_TOKEN(ts_aux_sym_token29);
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            LEX_ERROR();
        case 105:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(ts_aux_sym_token34);
        case 107:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 108:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 109:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 110:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == ',')
                ADVANCE(99);
            LEX_ERROR();
        case 112:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'd')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 114:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == '\n')
                ADVANCE(115);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == '\n')
                ADVANCE(115);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 116:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 118:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
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
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\n')
                ADVANCE(120);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 121:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '\n')
                ADVANCE(122);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '\n')
                ADVANCE(122);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 123:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '\n')
                ADVANCE(124);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '\n')
                ADVANCE(124);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 125:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '\n')
                ADVANCE(126);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '\n')
                ADVANCE(126);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\n')
                ADVANCE(128);
            if (lookahead == ';')
                ADVANCE(85);
            LEX_ERROR();
        case 128:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\n')
                ADVANCE(128);
            if (lookahead == ';')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 129:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 130:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(131);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 131:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(132);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 132:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(133);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 133:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 134:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(135);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 135:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(136);
            if (lookahead == 'l')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 136:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(137);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 137:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(138);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 138:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(139);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 139:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(140);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 140:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 141:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == 'c')
                ADVANCE(142);
            if (lookahead == 'd')
                ADVANCE(146);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 142:
            if (lookahead == 'a')
                ADVANCE(143);
            LEX_ERROR();
        case 143:
            if (lookahead == 's')
                ADVANCE(144);
            LEX_ERROR();
        case 144:
            if (lookahead == 'e')
                ADVANCE(145);
            LEX_ERROR();
        case 145:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 146:
            if (lookahead == 'e')
                ADVANCE(147);
            LEX_ERROR();
        case 147:
            if (lookahead == 'f')
                ADVANCE(148);
            LEX_ERROR();
        case 148:
            if (lookahead == 'a')
                ADVANCE(149);
            LEX_ERROR();
        case 149:
            if (lookahead == 'u')
                ADVANCE(150);
            LEX_ERROR();
        case 150:
            if (lookahead == 'l')
                ADVANCE(151);
            LEX_ERROR();
        case 151:
            if (lookahead == 't')
                ADVANCE(152);
            LEX_ERROR();
        case 152:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 153:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(153);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 154:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(154);
            if (lookahead == ']')
                ADVANCE(106);
            LEX_ERROR();
        case 155:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(155);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(88);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 156:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 157:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(18);
            if (lookahead == '\\')
                ADVANCE(20);
            LEX_ERROR();
        case 158:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(39);
            if (lookahead == 'u')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 159:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 160:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == ']')
                ADVANCE(106);
            LEX_ERROR();
        case 161:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 162:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(162);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 163:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(163);
            if (lookahead == ':')
                ADVANCE(101);
            LEX_ERROR();
        case 164:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(108);
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
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 167:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == ')')
                ADVANCE(97);
            LEX_ERROR();
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == '(')
                ADVANCE(14);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(14);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '&')
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '\n')
                ADVANCE(172);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 172:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '\n')
                ADVANCE(172);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == '{')
                ADVANCE(77);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 173:
            START_TOKEN();
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
                (lookahead == 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'd')
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 174:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 175:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(176);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 176:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(177);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 177:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(178);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 178:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 179:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(179);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 180:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(180);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'd')
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 181:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(181);
            if (lookahead == '\"')
                ADVANCE(4);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '\'')
                ADVANCE(10);
            LEX_ERROR();
        case 182:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(182);
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
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'd')
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            LEX_ERROR();
        case 183:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(183);
            if (lookahead == '\n')
                ADVANCE(184);
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
                ADVANCE(80);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(185);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '|')
                ADVANCE(94);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 184:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(183);
            if (lookahead == '\n')
                ADVANCE(184);
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
                ADVANCE(80);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(185);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '|')
                ADVANCE(94);
            if (lookahead == '}')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 185:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '\\')
                ADVANCE(20);
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(183);
            if (lookahead == '\n')
                ADVANCE(184);
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
                ADVANCE(80);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(82);
            if (lookahead == '+')
                ADVANCE(15);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(16);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(185);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            if (lookahead == ':')
                ADVANCE(101);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(86);
            if (lookahead == '=')
                ADVANCE(103);
            if (lookahead == '>')
                ADVANCE(91);
            if (lookahead == '?')
                ADVANCE(93);
            if (lookahead == '[')
                ADVANCE(26);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'b')
                ADVANCE(27);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(54);
            if (lookahead == 'r')
                ADVANCE(58);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(70);
            if (lookahead == 'v')
                ADVANCE(74);
            if (lookahead == '{')
                ADVANCE(77);
            if (lookahead == '|')
                ADVANCE(94);
            if (lookahead == '}')
                ADVANCE(108);
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
    [4] = 78,
    [5] = 2,
    [6] = 156,
    [7] = 98,
    [8] = 96,
    [9] = 78,
    [10] = 156,
    [11] = 98,
    [12] = 96,
    [13] = 98,
    [14] = 162,
    [15] = 98,
    [16] = 162,
    [17] = 98,
    [18] = 162,
    [19] = 98,
    [20] = 162,
    [21] = 98,
    [22] = 162,
    [23] = 98,
    [24] = 162,
    [25] = 100,
    [26] = 156,
    [27] = 98,
    [28] = 96,
    [29] = 100,
    [30] = 162,
    [31] = 98,
    [32] = 96,
    [33] = 104,
    [34] = 102,
    [35] = 162,
    [36] = 105,
    [37] = 156,
    [38] = 98,
    [39] = 96,
    [40] = 105,
    [41] = 98,
    [42] = 102,
    [43] = 162,
    [44] = 98,
    [45] = 164,
    [46] = 109,
    [47] = 107,
    [48] = 98,
    [49] = 181,
    [50] = 109,
    [51] = 107,
    [52] = 163,
    [53] = 162,
    [54] = 110,
    [55] = 107,
    [56] = 156,
    [57] = 98,
    [58] = 96,
    [59] = 110,
    [60] = 111,
    [61] = 162,
    [62] = 112,
    [63] = 156,
    [64] = 98,
    [65] = 96,
    [66] = 112,
    [67] = 111,
    [68] = 112,
    [69] = 162,
    [70] = 98,
    [71] = 162,
    [72] = 98,
    [73] = 169,
    [74] = 166,
    [75] = 98,
    [76] = 113,
    [77] = 113,
    [78] = 113,
    [79] = 78,
    [80] = 113,
    [81] = 162,
    [82] = 78,
    [83] = 162,
    [84] = 78,
    [85] = 162,
    [86] = 78,
    [87] = 162,
    [88] = 78,
    [89] = 162,
    [90] = 78,
    [91] = 162,
    [92] = 100,
    [93] = 162,
    [94] = 78,
    [95] = 104,
    [96] = 114,
    [97] = 162,
    [98] = 105,
    [99] = 162,
    [100] = 105,
    [101] = 162,
    [102] = 105,
    [103] = 162,
    [104] = 105,
    [105] = 162,
    [106] = 105,
    [107] = 162,
    [108] = 105,
    [109] = 162,
    [110] = 100,
    [111] = 162,
    [112] = 105,
    [113] = 104,
    [114] = 116,
    [115] = 162,
    [116] = 105,
    [117] = 116,
    [118] = 105,
    [119] = 116,
    [120] = 162,
    [121] = 105,
    [122] = 164,
    [123] = 109,
    [124] = 107,
    [125] = 105,
    [126] = 163,
    [127] = 162,
    [128] = 110,
    [129] = 107,
    [130] = 105,
    [131] = 162,
    [132] = 110,
    [133] = 162,
    [134] = 110,
    [135] = 162,
    [136] = 110,
    [137] = 162,
    [138] = 110,
    [139] = 162,
    [140] = 110,
    [141] = 162,
    [142] = 100,
    [143] = 162,
    [144] = 110,
    [145] = 104,
    [146] = 117,
    [147] = 162,
    [148] = 105,
    [149] = 117,
    [150] = 162,
    [151] = 112,
    [152] = 105,
    [153] = 162,
    [154] = 112,
    [155] = 162,
    [156] = 112,
    [157] = 162,
    [158] = 112,
    [159] = 162,
    [160] = 112,
    [161] = 162,
    [162] = 112,
    [163] = 162,
    [164] = 100,
    [165] = 162,
    [166] = 112,
    [167] = 104,
    [168] = 118,
    [169] = 162,
    [170] = 105,
    [171] = 118,
    [172] = 162,
    [173] = 105,
    [174] = 162,
    [175] = 105,
    [176] = 169,
    [177] = 166,
    [178] = 105,
    [179] = 113,
    [180] = 78,
    [181] = 114,
    [182] = 162,
    [183] = 78,
    [184] = 164,
    [185] = 109,
    [186] = 107,
    [187] = 78,
    [188] = 163,
    [189] = 162,
    [190] = 110,
    [191] = 107,
    [192] = 78,
    [193] = 110,
    [194] = 117,
    [195] = 162,
    [196] = 110,
    [197] = 164,
    [198] = 109,
    [199] = 107,
    [200] = 110,
    [201] = 163,
    [202] = 162,
    [203] = 110,
    [204] = 107,
    [205] = 110,
    [206] = 162,
    [207] = 112,
    [208] = 110,
    [209] = 112,
    [210] = 118,
    [211] = 162,
    [212] = 112,
    [213] = 164,
    [214] = 109,
    [215] = 107,
    [216] = 112,
    [217] = 163,
    [218] = 162,
    [219] = 110,
    [220] = 107,
    [221] = 112,
    [222] = 162,
    [223] = 110,
    [224] = 162,
    [225] = 110,
    [226] = 169,
    [227] = 166,
    [228] = 110,
    [229] = 113,
    [230] = 119,
    [231] = 110,
    [232] = 107,
    [233] = 113,
    [234] = 121,
    [235] = 113,
    [236] = 123,
    [237] = 125,
    [238] = 107,
    [239] = 78,
    [240] = 168,
    [241] = 179,
    [242] = 162,
    [243] = 162,
    [244] = 112,
    [245] = 173,
    [246] = 113,
    [247] = 127,
    [248] = 162,
    [249] = 112,
    [250] = 78,
    [251] = 162,
    [252] = 112,
    [253] = 112,
    [254] = 162,
    [255] = 112,
    [256] = 162,
    [257] = 112,
    [258] = 169,
    [259] = 166,
    [260] = 112,
    [261] = 113,
    [262] = 119,
    [263] = 112,
    [264] = 107,
    [265] = 168,
    [266] = 162,
    [267] = 112,
    [268] = 173,
    [269] = 180,
    [270] = 173,
    [271] = 113,
    [272] = 168,
    [273] = 162,
    [274] = 112,
    [275] = 166,
    [276] = 141,
    [277] = 141,
    [278] = 107,
    [279] = 162,
    [280] = 100,
    [281] = 129,
    [282] = 129,
    [283] = 129,
    [284] = 78,
    [285] = 129,
    [286] = 127,
    [287] = 141,
    [288] = 113,
    [289] = 121,
    [290] = 129,
    [291] = 107,
    [292] = 127,
    [293] = 113,
    [294] = 162,
    [295] = 153,
    [296] = 156,
    [297] = 98,
    [298] = 96,
    [299] = 153,
    [300] = 111,
    [301] = 153,
    [302] = 165,
    [303] = 155,
    [304] = 154,
    [305] = 98,
    [306] = 156,
    [307] = 98,
    [308] = 96,
    [309] = 155,
    [310] = 111,
    [311] = 155,
    [312] = 162,
    [313] = 155,
    [314] = 162,
    [315] = 155,
    [316] = 162,
    [317] = 155,
    [318] = 162,
    [319] = 155,
    [320] = 162,
    [321] = 155,
    [322] = 162,
    [323] = 100,
    [324] = 162,
    [325] = 155,
    [326] = 104,
    [327] = 159,
    [328] = 162,
    [329] = 105,
    [330] = 159,
    [331] = 165,
    [332] = 155,
    [333] = 154,
    [334] = 105,
    [335] = 162,
    [336] = 155,
    [337] = 154,
    [338] = 155,
    [339] = 159,
    [340] = 162,
    [341] = 155,
    [342] = 164,
    [343] = 109,
    [344] = 107,
    [345] = 155,
    [346] = 163,
    [347] = 162,
    [348] = 110,
    [349] = 107,
    [350] = 155,
    [351] = 165,
    [352] = 155,
    [353] = 154,
    [354] = 110,
    [355] = 160,
    [356] = 162,
    [357] = 112,
    [358] = 155,
    [359] = 165,
    [360] = 155,
    [361] = 154,
    [362] = 112,
    [363] = 160,
    [364] = 162,
    [365] = 155,
    [366] = 162,
    [367] = 155,
    [368] = 169,
    [369] = 166,
    [370] = 155,
    [371] = 113,
    [372] = 119,
    [373] = 155,
    [374] = 107,
    [375] = 171,
    [376] = 78,
    [377] = 113,
    [378] = 113,
    [379] = 162,
    [380] = 78,
    [381] = 162,
    [382] = 78,
    [383] = 169,
    [384] = 166,
    [385] = 78,
    [386] = 113,
    [387] = 119,
    [388] = 78,
    [389] = 107,
    [390] = 162,
    [391] = 153,
    [392] = 162,
    [393] = 153,
    [394] = 162,
    [395] = 153,
    [396] = 162,
    [397] = 153,
    [398] = 162,
    [399] = 153,
    [400] = 162,
    [401] = 153,
    [402] = 162,
    [403] = 100,
    [404] = 162,
    [405] = 153,
    [406] = 104,
    [407] = 161,
    [408] = 162,
    [409] = 105,
    [410] = 161,
    [411] = 153,
    [412] = 161,
    [413] = 162,
    [414] = 153,
    [415] = 164,
    [416] = 109,
    [417] = 107,
    [418] = 153,
    [419] = 163,
    [420] = 162,
    [421] = 110,
    [422] = 107,
    [423] = 153,
    [424] = 153,
    [425] = 162,
    [426] = 112,
    [427] = 153,
    [428] = 162,
    [429] = 153,
    [430] = 162,
    [431] = 153,
    [432] = 169,
    [433] = 166,
    [434] = 153,
    [435] = 113,
    [436] = 119,
    [437] = 153,
    [438] = 107,
    [439] = 165,
    [440] = 155,
    [441] = 154,
    [442] = 78,
    [443] = 160,
    [444] = 165,
    [445] = 155,
    [446] = 154,
    [447] = 155,
    [448] = 160,
    [449] = 155,
    [450] = 78,
    [451] = 168,
    [452] = 166,
    [453] = 153,
    [454] = 167,
    [455] = 111,
    [456] = 96,
    [457] = 166,
    [458] = 104,
    [459] = 111,
    [460] = 96,
    [461] = 166,
    [462] = 165,
    [463] = 155,
    [464] = 154,
    [465] = 153,
    [466] = 160,
    [467] = 153,
    [468] = 162,
    [469] = 100,
    [470] = 162,
    [471] = 100,
    [472] = 162,
    [473] = 100,
    [474] = 162,
    [475] = 100,
    [476] = 162,
    [477] = 100,
    [478] = 162,
    [479] = 100,
    [480] = 162,
    [481] = 100,
    [482] = 104,
    [483] = 170,
    [484] = 162,
    [485] = 105,
    [486] = 170,
    [487] = 100,
    [488] = 170,
    [489] = 162,
    [490] = 100,
    [491] = 164,
    [492] = 109,
    [493] = 107,
    [494] = 100,
    [495] = 163,
    [496] = 162,
    [497] = 110,
    [498] = 107,
    [499] = 100,
    [500] = 100,
    [501] = 162,
    [502] = 112,
    [503] = 100,
    [504] = 162,
    [505] = 100,
    [506] = 162,
    [507] = 100,
    [508] = 169,
    [509] = 166,
    [510] = 100,
    [511] = 113,
    [512] = 119,
    [513] = 100,
    [514] = 107,
    [515] = 168,
    [516] = 166,
    [517] = 100,
    [518] = 165,
    [519] = 155,
    [520] = 154,
    [521] = 100,
    [522] = 160,
    [523] = 100,
    [524] = 114,
    [525] = 113,
    [526] = 168,
    [527] = 166,
    [528] = 78,
    [529] = 168,
    [530] = 166,
    [531] = 155,
    [532] = 112,
    [533] = 110,
    [534] = 155,
    [535] = 160,
    [536] = 160,
    [537] = 105,
    [538] = 160,
    [539] = 98,
    [540] = 78,
    [541] = 113,
    [542] = 161,
    [543] = 114,
    [544] = 168,
    [545] = 179,
    [546] = 162,
    [547] = 162,
    [548] = 112,
    [549] = 173,
    [550] = 129,
    [551] = 168,
    [552] = 162,
    [553] = 112,
    [554] = 173,
    [555] = 174,
    [556] = 173,
    [557] = 129,
    [558] = 168,
    [559] = 162,
    [560] = 112,
    [561] = 166,
    [562] = 141,
    [563] = 107,
    [564] = 129,
    [565] = 163,
    [566] = 129,
    [567] = 141,
    [568] = 127,
    [569] = 129,
    [570] = 162,
    [571] = 78,
    [572] = 129,
    [573] = 114,
    [574] = 171,
    [575] = 78,
    [576] = 129,
    [577] = 129,
    [578] = 162,
    [579] = 114,
    [580] = 129,
    [581] = 96,
    [582] = 174,
    [583] = 78,
    [584] = 174,
    [585] = 127,
    [586] = 113,
    [587] = 121,
    [588] = 174,
    [589] = 107,
    [590] = 168,
    [591] = 179,
    [592] = 162,
    [593] = 162,
    [594] = 112,
    [595] = 173,
    [596] = 174,
    [597] = 168,
    [598] = 162,
    [599] = 112,
    [600] = 173,
    [601] = 174,
    [602] = 173,
    [603] = 174,
    [604] = 168,
    [605] = 162,
    [606] = 112,
    [607] = 166,
    [608] = 141,
    [609] = 107,
    [610] = 174,
    [611] = 96,
    [612] = 127,
    [613] = 174,
    [614] = 162,
    [615] = 78,
    [616] = 174,
    [617] = 114,
    [618] = 171,
    [619] = 78,
    [620] = 174,
    [621] = 174,
    [622] = 162,
    [623] = 114,
    [624] = 174,
    [625] = 96,
    [626] = 96,
    [627] = 78,
    [628] = 162,
    [629] = 127,
    [630] = 162,
    [631] = 78,
    [632] = 162,
    [633] = 114,
    [634] = 96,
    [635] = 96,
    [636] = 141,
    [637] = 107,
    [638] = 113,
    [639] = 96,
    [640] = 180,
    [641] = 78,
    [642] = 180,
    [643] = 127,
    [644] = 113,
    [645] = 121,
    [646] = 180,
    [647] = 107,
    [648] = 168,
    [649] = 179,
    [650] = 162,
    [651] = 162,
    [652] = 112,
    [653] = 173,
    [654] = 180,
    [655] = 168,
    [656] = 162,
    [657] = 112,
    [658] = 173,
    [659] = 180,
    [660] = 173,
    [661] = 180,
    [662] = 168,
    [663] = 162,
    [664] = 112,
    [665] = 166,
    [666] = 141,
    [667] = 107,
    [668] = 180,
    [669] = 96,
    [670] = 127,
    [671] = 180,
    [672] = 162,
    [673] = 78,
    [674] = 180,
    [675] = 114,
    [676] = 171,
    [677] = 78,
    [678] = 180,
    [679] = 180,
    [680] = 162,
    [681] = 114,
    [682] = 180,
    [683] = 96,
    [684] = 96,
    [685] = 96,
    [686] = 168,
    [687] = 166,
    [688] = 112,
    [689] = 96,
    [690] = 168,
    [691] = 166,
    [692] = 110,
    [693] = 112,
    [694] = 110,
    [695] = 119,
    [696] = 105,
    [697] = 107,
    [698] = 168,
    [699] = 166,
    [700] = 105,
    [701] = 105,
    [702] = 114,
    [703] = 107,
    [704] = 119,
    [705] = 98,
    [706] = 107,
    [707] = 168,
    [708] = 166,
    [709] = 98,
    [710] = 98,
    [711] = 110,
    [712] = 163,
    [713] = 162,
    [714] = 110,
    [715] = 107,
    [716] = 98,
    [717] = 98,
    [718] = 111,
    [719] = 105,
    [720] = 102,
    [721] = 111,
    [722] = 111,
    [723] = 100,
    [724] = 162,
    [725] = 98,
    [726] = 111,
    [727] = 98,
    [728] = 111,
    [729] = 78,
    [730] = 127,
    [731] = 0,
    [732] = 113,
    [733] = 121,
    [734] = 2,
    [735] = 107,
    [736] = 168,
    [737] = 179,
    [738] = 162,
    [739] = 162,
    [740] = 112,
    [741] = 173,
    [742] = 2,
    [743] = 168,
    [744] = 162,
    [745] = 112,
    [746] = 173,
    [747] = 182,
    [748] = 173,
    [749] = 2,
    [750] = 168,
    [751] = 162,
    [752] = 112,
    [753] = 166,
    [754] = 141,
    [755] = 107,
    [756] = 2,
    [757] = 96,
    [758] = 127,
    [759] = 2,
    [760] = 162,
    [761] = 78,
    [762] = 2,
    [763] = 114,
    [764] = 171,
    [765] = 78,
    [766] = 2,
    [767] = 2,
    [768] = 162,
    [769] = 114,
    [770] = 2,
    [771] = 182,
    [772] = 78,
    [773] = 182,
    [774] = 127,
    [775] = 113,
    [776] = 121,
    [777] = 182,
    [778] = 107,
    [779] = 168,
    [780] = 179,
    [781] = 162,
    [782] = 162,
    [783] = 112,
    [784] = 173,
    [785] = 182,
    [786] = 168,
    [787] = 162,
    [788] = 112,
    [789] = 173,
    [790] = 182,
    [791] = 173,
    [792] = 182,
    [793] = 168,
    [794] = 162,
    [795] = 112,
    [796] = 166,
    [797] = 141,
    [798] = 107,
    [799] = 182,
    [800] = 96,
    [801] = 127,
    [802] = 182,
    [803] = 162,
    [804] = 78,
    [805] = 182,
    [806] = 114,
    [807] = 171,
    [808] = 78,
    [809] = 182,
    [810] = 182,
    [811] = 162,
    [812] = 114,
    [813] = 182,
    [814] = 96,
    [815] = 96,
    [816] = 96,
    [817] = 96,
    [818] = 0,
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
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(730),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_program_repeat0] = SHIFT(818),
        [ts_aux_sym_token0] = SHIFT(732),
        [ts_aux_sym_token2] = SHIFT(736),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(743),
        [ts_aux_sym_token7] = SHIFT(750),
        [ts_aux_sym_token11] = SHIFT(758),
        [ts_aux_sym_token12] = SHIFT(760),
        [ts_aux_sym_token13] = SHIFT(764),
        [ts_aux_sym_token14] = SHIFT(768),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
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
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(730),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_program_repeat0] = SHIFT(731),
        [ts_aux_sym_token0] = SHIFT(732),
        [ts_aux_sym_token2] = SHIFT(736),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(743),
        [ts_aux_sym_token7] = SHIFT(750),
        [ts_aux_sym_token11] = SHIFT(758),
        [ts_aux_sym_token12] = SHIFT(760),
        [ts_aux_sym_token13] = SHIFT(764),
        [ts_aux_sym_token14] = SHIFT(768),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [3] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [4] = {
        [ts_sym__terminator] = SHIFT(5),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [5] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(728),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(729),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [7] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [8] = {
        [ts_aux_sym_token4] = SHIFT(9),
    },
    [9] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(726),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(727),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [11] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [12] = {
        [ts_aux_sym_token4] = SHIFT(13),
    },
    [13] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [15] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [17] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [19] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [21] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [23] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [24] = {
        [ts_sym_expression] = SHIFT(25),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [25] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(724),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(722),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(723),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [27] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(28),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [28] = {
        [ts_aux_sym_token4] = SHIFT(29),
    },
    [29] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(721),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [31] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(32),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [32] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 3),
    },
    [33] = {
        [ts_sym_identifier] = SHIFT(34),
    },
    [34] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
    },
    [35] = {
        [ts_sym_expression] = SHIFT(36),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [36] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(720),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(718),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(719),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [38] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(39),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [39] = {
        [ts_aux_sym_token4] = SHIFT(40),
    },
    [40] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_call, 5),
    },
    [41] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [42] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(43),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [44] = {
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [45] = {
        [ts_builtin_sym_error] = SHIFT(46),
        [ts_sym_string] = SHIFT(712),
        [ts_sym_identifier] = SHIFT(712),
        [ts_aux_sym_token1] = SHIFT(717),
    },
    [46] = {
        [ts_aux_sym_object_repeat0] = SHIFT(47),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [47] = {
        [ts_aux_sym_token1] = SHIFT(48),
    },
    [48] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
    },
    [49] = {
        [ts_builtin_sym_error] = SHIFT(50),
        [ts_sym_string] = SHIFT(52),
        [ts_sym_identifier] = SHIFT(52),
    },
    [50] = {
        [ts_aux_sym_object_repeat0] = SHIFT(51),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [51] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 3),
    },
    [52] = {
        [ts_aux_sym_token10] = SHIFT(53),
    },
    [53] = {
        [ts_sym_expression] = SHIFT(54),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [54] = {
        [ts_aux_sym_object_repeat0] = SHIFT(55),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [55] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [56] = {
        [ts_sym_expression] = SHIFT(57),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(60),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(711),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [57] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(58),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [58] = {
        [ts_aux_sym_token4] = SHIFT(59),
    },
    [59] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
    },
    [60] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(58),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [61] = {
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [62] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(710),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [63] = {
        [ts_sym_expression] = SHIFT(64),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(67),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(68),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [64] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(65),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [65] = {
        [ts_aux_sym_token4] = SHIFT(66),
    },
    [66] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
    },
    [67] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(65),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [68] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
    },
    [69] = {
        [ts_sym_expression] = SHIFT(70),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [70] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
    },
    [71] = {
        [ts_sym_expression] = SHIFT(72),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [72] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
    },
    [73] = {
        [ts_sym_formal_parameters] = SHIFT(74),
        [ts_sym_identifier] = SHIFT(707),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [74] = {
        [ts_sym_statement_block] = SHIFT(75),
        [ts_aux_sym_token0] = SHIFT(76),
    },
    [75] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
    },
    [76] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(704),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(706),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [77] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(247),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(703),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [78] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [79] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [80] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [81] = {
        [ts_sym_expression] = SHIFT(82),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [82] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [83] = {
        [ts_sym_expression] = SHIFT(84),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [84] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [85] = {
        [ts_sym_expression] = SHIFT(86),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [86] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [87] = {
        [ts_sym_expression] = SHIFT(88),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [88] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [89] = {
        [ts_sym_expression] = SHIFT(90),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [90] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [91] = {
        [ts_sym_expression] = SHIFT(92),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [92] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(93),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [93] = {
        [ts_sym_expression] = SHIFT(94),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [94] = {
        [ts_sym__terminator] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [95] = {
        [ts_sym_identifier] = SHIFT(96),
    },
    [96] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
    },
    [97] = {
        [ts_sym_expression] = SHIFT(98),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [98] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(702),
    },
    [99] = {
        [ts_sym_expression] = SHIFT(100),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [100] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [101] = {
        [ts_sym_expression] = SHIFT(102),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [102] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [103] = {
        [ts_sym_expression] = SHIFT(104),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [104] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [105] = {
        [ts_sym_expression] = SHIFT(106),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [106] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [107] = {
        [ts_sym_expression] = SHIFT(108),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [108] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [109] = {
        [ts_sym_expression] = SHIFT(110),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [110] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(111),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [111] = {
        [ts_sym_expression] = SHIFT(112),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [112] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = REDUCE(ts_sym_ternary, 5),
    },
    [113] = {
        [ts_sym_identifier] = SHIFT(114),
    },
    [114] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_property_access, 3),
    },
    [115] = {
        [ts_sym_expression] = SHIFT(116),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [116] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(117),
    },
    [117] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_property_access, 4),
    },
    [118] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 1),
    },
    [119] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(120),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 1),
    },
    [120] = {
        [ts_sym_expression] = SHIFT(121),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [121] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = REDUCE(ts_sym_assignment, 3),
    },
    [122] = {
        [ts_builtin_sym_error] = SHIFT(123),
        [ts_sym_string] = SHIFT(126),
        [ts_sym_identifier] = SHIFT(126),
        [ts_aux_sym_token1] = SHIFT(701),
    },
    [123] = {
        [ts_aux_sym_object_repeat0] = SHIFT(124),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [124] = {
        [ts_aux_sym_token1] = SHIFT(125),
    },
    [125] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_object, 4),
    },
    [126] = {
        [ts_aux_sym_token10] = SHIFT(127),
    },
    [127] = {
        [ts_sym_expression] = SHIFT(128),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [128] = {
        [ts_aux_sym_object_repeat0] = SHIFT(129),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [129] = {
        [ts_aux_sym_token1] = SHIFT(130),
    },
    [130] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token34] = REDUCE(ts_sym_object, 6),
    },
    [131] = {
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [132] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [133] = {
        [ts_sym_expression] = SHIFT(134),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [134] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [135] = {
        [ts_sym_expression] = SHIFT(136),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [136] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [137] = {
        [ts_sym_expression] = SHIFT(138),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [138] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [139] = {
        [ts_sym_expression] = SHIFT(140),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [140] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [142] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(143),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [143] = {
        [ts_sym_expression] = SHIFT(144),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [144] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [145] = {
        [ts_sym_identifier] = SHIFT(146),
    },
    [146] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
    },
    [147] = {
        [ts_sym_expression] = SHIFT(148),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [148] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(149),
    },
    [149] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
    },
    [150] = {
        [ts_sym_expression] = SHIFT(151),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [151] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(152),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [152] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 3),
    },
    [153] = {
        [ts_sym_expression] = SHIFT(154),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [154] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [155] = {
        [ts_sym_expression] = SHIFT(156),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [156] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [157] = {
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [158] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [159] = {
        [ts_sym_expression] = SHIFT(160),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [160] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [161] = {
        [ts_sym_expression] = SHIFT(162),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [162] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [164] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(165),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [165] = {
        [ts_sym_expression] = SHIFT(166),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [166] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [167] = {
        [ts_sym_identifier] = SHIFT(168),
    },
    [168] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
    },
    [169] = {
        [ts_sym_expression] = SHIFT(170),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [170] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(171),
    },
    [171] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
    },
    [172] = {
        [ts_sym_expression] = SHIFT(173),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [173] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 2),
    },
    [174] = {
        [ts_sym_expression] = SHIFT(175),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [175] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 2),
    },
    [176] = {
        [ts_sym_formal_parameters] = SHIFT(177),
        [ts_sym_identifier] = SHIFT(698),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [177] = {
        [ts_sym_statement_block] = SHIFT(178),
        [ts_aux_sym_token0] = SHIFT(179),
    },
    [178] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_expression, 3),
    },
    [179] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(695),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(697),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [180] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [181] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [182] = {
        [ts_sym_expression] = SHIFT(183),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [183] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [184] = {
        [ts_builtin_sym_error] = SHIFT(185),
        [ts_sym_string] = SHIFT(188),
        [ts_sym_identifier] = SHIFT(188),
        [ts_aux_sym_token1] = SHIFT(239),
    },
    [185] = {
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [186] = {
        [ts_aux_sym_token1] = SHIFT(187),
    },
    [187] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
    },
    [188] = {
        [ts_aux_sym_token10] = SHIFT(189),
    },
    [189] = {
        [ts_sym_expression] = SHIFT(190),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [190] = {
        [ts_aux_sym_object_repeat0] = SHIFT(191),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [191] = {
        [ts_aux_sym_token1] = SHIFT(192),
    },
    [192] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
    },
    [193] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [194] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(195),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [195] = {
        [ts_sym_expression] = SHIFT(196),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [196] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [197] = {
        [ts_builtin_sym_error] = SHIFT(198),
        [ts_sym_string] = SHIFT(201),
        [ts_sym_identifier] = SHIFT(201),
        [ts_aux_sym_token1] = SHIFT(694),
    },
    [198] = {
        [ts_aux_sym_object_repeat0] = SHIFT(199),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [199] = {
        [ts_aux_sym_token1] = SHIFT(200),
    },
    [200] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
    },
    [201] = {
        [ts_aux_sym_token10] = SHIFT(202),
    },
    [202] = {
        [ts_sym_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [203] = {
        [ts_aux_sym_object_repeat0] = SHIFT(204),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [204] = {
        [ts_aux_sym_token1] = SHIFT(205),
    },
    [205] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
    },
    [206] = {
        [ts_sym_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [207] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(208),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [208] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
    },
    [209] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [210] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(211),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [211] = {
        [ts_sym_expression] = SHIFT(212),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [212] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [213] = {
        [ts_builtin_sym_error] = SHIFT(214),
        [ts_sym_string] = SHIFT(217),
        [ts_sym_identifier] = SHIFT(217),
        [ts_aux_sym_token1] = SHIFT(693),
    },
    [214] = {
        [ts_aux_sym_object_repeat0] = SHIFT(215),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [215] = {
        [ts_aux_sym_token1] = SHIFT(216),
    },
    [216] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
    },
    [217] = {
        [ts_aux_sym_token10] = SHIFT(218),
    },
    [218] = {
        [ts_sym_expression] = SHIFT(219),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [219] = {
        [ts_aux_sym_object_repeat0] = SHIFT(220),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [220] = {
        [ts_aux_sym_token1] = SHIFT(221),
    },
    [221] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
    },
    [222] = {
        [ts_sym_expression] = SHIFT(223),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [223] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
    },
    [224] = {
        [ts_sym_expression] = SHIFT(225),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [225] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
    },
    [226] = {
        [ts_sym_formal_parameters] = SHIFT(227),
        [ts_sym_identifier] = SHIFT(690),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [227] = {
        [ts_sym_statement_block] = SHIFT(228),
        [ts_aux_sym_token0] = SHIFT(229),
    },
    [228] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
    },
    [229] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(230),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(232),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [230] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(231),
    },
    [231] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [232] = {
        [ts_aux_sym_token1] = SHIFT(231),
    },
    [233] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(234),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(238),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [234] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(235),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [235] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [236] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(189),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [237] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(189),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [238] = {
        [ts_aux_sym_token1] = SHIFT(235),
    },
    [239] = {
        [ts_sym__terminator] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
    },
    [240] = {
        [ts_aux_sym_token3] = SHIFT(241),
    },
    [241] = {
        [ts_sym_var_declaration] = SHIFT(242),
        [ts_sym_expression_statement] = SHIFT(242),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token12] = SHIFT(630),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [242] = {
        [ts_sym_expression_statement] = SHIFT(243),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [243] = {
        [ts_sym_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(689),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [244] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(245),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [245] = {
        [ts_sym_statement] = SHIFT(246),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(247),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [246] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [247] = {
        [ts_sym__terminator] = SHIFT(80),
    },
    [248] = {
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [249] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(250),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [250] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
    },
    [251] = {
        [ts_sym_expression] = SHIFT(252),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [252] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(253),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [253] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
    },
    [254] = {
        [ts_sym_expression] = SHIFT(255),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [255] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
    },
    [256] = {
        [ts_sym_expression] = SHIFT(257),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [257] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
    },
    [258] = {
        [ts_sym_formal_parameters] = SHIFT(259),
        [ts_sym_identifier] = SHIFT(686),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [259] = {
        [ts_sym_statement_block] = SHIFT(260),
        [ts_aux_sym_token0] = SHIFT(261),
    },
    [260] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
    },
    [261] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(262),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(264),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [262] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(263),
    },
    [263] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [264] = {
        [ts_aux_sym_token1] = SHIFT(263),
    },
    [265] = {
        [ts_aux_sym_token3] = SHIFT(266),
    },
    [266] = {
        [ts_sym_expression] = SHIFT(267),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(685),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [267] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(268),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [268] = {
        [ts_sym_statement] = SHIFT(269),
        [ts_sym_statement_block] = SHIFT(640),
        [ts_sym_for_statement] = SHIFT(640),
        [ts_sym_if_statement] = SHIFT(640),
        [ts_sym_switch_statement] = SHIFT(640),
        [ts_sym_break_statement] = SHIFT(640),
        [ts_sym_var_declaration] = SHIFT(640),
        [ts_sym_expression_statement] = SHIFT(640),
        [ts_sym_return_statement] = SHIFT(640),
        [ts_sym_delete_statement] = SHIFT(640),
        [ts_sym_expression] = SHIFT(641),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(643),
        [ts_sym_comment] = SHIFT(640),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(644),
        [ts_aux_sym_token2] = SHIFT(648),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(655),
        [ts_aux_sym_token7] = SHIFT(662),
        [ts_aux_sym_token11] = SHIFT(670),
        [ts_aux_sym_token12] = SHIFT(672),
        [ts_aux_sym_token13] = SHIFT(676),
        [ts_aux_sym_token14] = SHIFT(680),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [269] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token6] = SHIFT(270),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [270] = {
        [ts_sym_statement] = SHIFT(271),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(247),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [271] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [272] = {
        [ts_aux_sym_token3] = SHIFT(273),
    },
    [273] = {
        [ts_sym_expression] = SHIFT(274),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(639),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [274] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(275),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [275] = {
        [ts_aux_sym_token0] = SHIFT(276),
    },
    [276] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(637),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [277] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(278),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [278] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [279] = {
        [ts_sym_expression] = SHIFT(280),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [280] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(281),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [281] = {
        [ts_sym_statement] = SHIFT(282),
        [ts_sym_statement_block] = SHIFT(283),
        [ts_sym_for_statement] = SHIFT(283),
        [ts_sym_if_statement] = SHIFT(283),
        [ts_sym_switch_statement] = SHIFT(283),
        [ts_sym_break_statement] = SHIFT(283),
        [ts_sym_var_declaration] = SHIFT(283),
        [ts_sym_expression_statement] = SHIFT(283),
        [ts_sym_return_statement] = SHIFT(283),
        [ts_sym_delete_statement] = SHIFT(283),
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(286),
        [ts_sym_comment] = SHIFT(283),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(636),
        [ts_aux_sym_token0] = SHIFT(288),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(544),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(551),
        [ts_aux_sym_token7] = SHIFT(558),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(568),
        [ts_aux_sym_token12] = SHIFT(570),
        [ts_aux_sym_token13] = SHIFT(574),
        [ts_aux_sym_token14] = SHIFT(578),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [282] = {
        [ts_sym_statement] = SHIFT(282),
        [ts_sym_statement_block] = SHIFT(283),
        [ts_sym_for_statement] = SHIFT(283),
        [ts_sym_if_statement] = SHIFT(283),
        [ts_sym_switch_statement] = SHIFT(283),
        [ts_sym_break_statement] = SHIFT(283),
        [ts_sym_var_declaration] = SHIFT(283),
        [ts_sym_expression_statement] = SHIFT(283),
        [ts_sym_return_statement] = SHIFT(283),
        [ts_sym_delete_statement] = SHIFT(283),
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(286),
        [ts_sym_comment] = SHIFT(283),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(287),
        [ts_aux_sym_token0] = SHIFT(288),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(544),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(551),
        [ts_aux_sym_token7] = SHIFT(558),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(568),
        [ts_aux_sym_token12] = SHIFT(570),
        [ts_aux_sym_token13] = SHIFT(574),
        [ts_aux_sym_token14] = SHIFT(578),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [283] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [284] = {
        [ts_sym__terminator] = SHIFT(285),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [285] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [286] = {
        [ts_sym__terminator] = SHIFT(285),
    },
    [287] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [288] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(289),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(291),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [289] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(290),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [290] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [291] = {
        [ts_aux_sym_token1] = SHIFT(290),
    },
    [292] = {
        [ts_sym__terminator] = SHIFT(293),
    },
    [293] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [294] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(540),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(543),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [295] = {
        [ts_aux_sym_token3] = SHIFT(296),
        [ts_aux_sym_token15] = SHIFT(392),
        [ts_aux_sym_token16] = SHIFT(392),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = SHIFT(396),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = SHIFT(402),
        [ts_aux_sym_token32] = SHIFT(406),
        [ts_aux_sym_token33] = SHIFT(408),
    },
    [296] = {
        [ts_sym_expression] = SHIFT(297),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(300),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(301),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [297] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(298),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [298] = {
        [ts_aux_sym_token4] = SHIFT(299),
    },
    [299] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
    },
    [300] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(298),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [301] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
    },
    [302] = {
        [ts_sym_expression] = SHIFT(303),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(538),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(539),
    },
    [303] = {
        [ts_aux_sym_array_repeat0] = SHIFT(304),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [304] = {
        [ts_aux_sym_token34] = SHIFT(305),
    },
    [305] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
    },
    [306] = {
        [ts_sym_expression] = SHIFT(307),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(310),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(311),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [307] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(308),
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = SHIFT(30),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [308] = {
        [ts_aux_sym_token4] = SHIFT(309),
    },
    [309] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 5),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_call, 5),
    },
    [310] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(308),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [311] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_call, 3),
    },
    [312] = {
        [ts_sym_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [313] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [314] = {
        [ts_sym_expression] = SHIFT(315),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [315] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [316] = {
        [ts_sym_expression] = SHIFT(317),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [317] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [318] = {
        [ts_sym_expression] = SHIFT(319),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [319] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [320] = {
        [ts_sym_expression] = SHIFT(321),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [321] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [322] = {
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [323] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(324),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [324] = {
        [ts_sym_expression] = SHIFT(325),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [325] = {
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_sym_ternary, 5),
    },
    [326] = {
        [ts_sym_identifier] = SHIFT(327),
    },
    [327] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_property_access, 3),
    },
    [328] = {
        [ts_sym_expression] = SHIFT(329),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [329] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(330),
    },
    [330] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_property_access, 4),
    },
    [331] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(536),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(537),
    },
    [332] = {
        [ts_aux_sym_array_repeat0] = SHIFT(333),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [333] = {
        [ts_aux_sym_token34] = SHIFT(334),
    },
    [334] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_array, 4),
    },
    [335] = {
        [ts_sym_expression] = SHIFT(336),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(535),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [336] = {
        [ts_aux_sym_array_repeat0] = SHIFT(337),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [337] = {
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [338] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 1),
    },
    [339] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(340),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 1),
    },
    [340] = {
        [ts_sym_expression] = SHIFT(341),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [341] = {
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_sym_assignment, 3),
    },
    [342] = {
        [ts_builtin_sym_error] = SHIFT(343),
        [ts_sym_string] = SHIFT(346),
        [ts_sym_identifier] = SHIFT(346),
        [ts_aux_sym_token1] = SHIFT(534),
    },
    [343] = {
        [ts_aux_sym_object_repeat0] = SHIFT(344),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [344] = {
        [ts_aux_sym_token1] = SHIFT(345),
    },
    [345] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_object, 4),
    },
    [346] = {
        [ts_aux_sym_token10] = SHIFT(347),
    },
    [347] = {
        [ts_sym_expression] = SHIFT(348),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [348] = {
        [ts_aux_sym_object_repeat0] = SHIFT(349),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [349] = {
        [ts_aux_sym_token1] = SHIFT(350),
    },
    [350] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token34] = REDUCE(ts_sym_object, 6),
    },
    [351] = {
        [ts_sym_expression] = SHIFT(352),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(355),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(533),
    },
    [352] = {
        [ts_aux_sym_array_repeat0] = SHIFT(353),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [353] = {
        [ts_aux_sym_token34] = SHIFT(354),
    },
    [354] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
    },
    [355] = {
        [ts_aux_sym_array_repeat0] = SHIFT(353),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [356] = {
        [ts_sym_expression] = SHIFT(357),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [357] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(358),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [358] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 3),
    },
    [359] = {
        [ts_sym_expression] = SHIFT(360),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(363),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(532),
    },
    [360] = {
        [ts_aux_sym_array_repeat0] = SHIFT(361),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [361] = {
        [ts_aux_sym_token34] = SHIFT(362),
    },
    [362] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
    },
    [363] = {
        [ts_aux_sym_array_repeat0] = SHIFT(361),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [364] = {
        [ts_sym_expression] = SHIFT(365),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [365] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 2),
    },
    [366] = {
        [ts_sym_expression] = SHIFT(367),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
    },
    [367] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 2),
    },
    [368] = {
        [ts_sym_formal_parameters] = SHIFT(369),
        [ts_sym_identifier] = SHIFT(529),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [369] = {
        [ts_sym_statement_block] = SHIFT(370),
        [ts_aux_sym_token0] = SHIFT(371),
    },
    [370] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_expression, 3),
    },
    [371] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(372),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(374),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [372] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(373),
    },
    [373] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_statement_block, 3),
    },
    [374] = {
        [ts_aux_sym_token1] = SHIFT(373),
    },
    [375] = {
        [ts_sym_expression] = SHIFT(376),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym__terminator] = SHIFT(378),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [376] = {
        [ts_sym__terminator] = SHIFT(377),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [377] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [378] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [379] = {
        [ts_sym_expression] = SHIFT(380),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [380] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
    },
    [381] = {
        [ts_sym_expression] = SHIFT(382),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [382] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
    },
    [383] = {
        [ts_sym_formal_parameters] = SHIFT(384),
        [ts_sym_identifier] = SHIFT(526),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [384] = {
        [ts_sym_statement_block] = SHIFT(385),
        [ts_aux_sym_token0] = SHIFT(386),
    },
    [385] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
    },
    [386] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(387),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(389),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [387] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(388),
    },
    [388] = {
        [ts_sym__terminator] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [389] = {
        [ts_aux_sym_token1] = SHIFT(388),
    },
    [390] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(524),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [391] = {
        [ts_aux_sym_token3] = SHIFT(296),
        [ts_aux_sym_token15] = SHIFT(392),
        [ts_aux_sym_token16] = SHIFT(392),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = SHIFT(396),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = SHIFT(402),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [392] = {
        [ts_sym_expression] = SHIFT(393),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [393] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(392),
        [ts_aux_sym_token16] = SHIFT(392),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = SHIFT(396),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [394] = {
        [ts_sym_expression] = SHIFT(395),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [395] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [396] = {
        [ts_sym_expression] = SHIFT(397),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [397] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(392),
        [ts_aux_sym_token16] = SHIFT(392),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = SHIFT(396),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [398] = {
        [ts_sym_expression] = SHIFT(399),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [399] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [400] = {
        [ts_sym_expression] = SHIFT(401),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [401] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [402] = {
        [ts_sym_expression] = SHIFT(403),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [403] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(404),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [404] = {
        [ts_sym_expression] = SHIFT(405),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [405] = {
        [ts_aux_sym_token3] = SHIFT(296),
        [ts_aux_sym_token15] = SHIFT(392),
        [ts_aux_sym_token16] = SHIFT(392),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = SHIFT(396),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = SHIFT(402),
        [ts_aux_sym_token32] = SHIFT(406),
        [ts_aux_sym_token33] = SHIFT(408),
    },
    [406] = {
        [ts_sym_identifier] = SHIFT(407),
    },
    [407] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
    },
    [408] = {
        [ts_sym_expression] = SHIFT(409),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [409] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(410),
    },
    [410] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
    },
    [411] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [412] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [413] = {
        [ts_sym_expression] = SHIFT(414),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [414] = {
        [ts_aux_sym_token3] = SHIFT(296),
        [ts_aux_sym_token15] = SHIFT(392),
        [ts_aux_sym_token16] = SHIFT(392),
        [ts_aux_sym_token17] = SHIFT(394),
        [ts_aux_sym_token18] = SHIFT(394),
        [ts_aux_sym_token19] = SHIFT(396),
        [ts_aux_sym_token20] = SHIFT(398),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = SHIFT(402),
        [ts_aux_sym_token32] = SHIFT(406),
        [ts_aux_sym_token33] = SHIFT(408),
    },
    [415] = {
        [ts_builtin_sym_error] = SHIFT(416),
        [ts_sym_string] = SHIFT(419),
        [ts_sym_identifier] = SHIFT(419),
        [ts_aux_sym_token1] = SHIFT(424),
    },
    [416] = {
        [ts_aux_sym_object_repeat0] = SHIFT(417),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [417] = {
        [ts_aux_sym_token1] = SHIFT(418),
    },
    [418] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
    },
    [419] = {
        [ts_aux_sym_token10] = SHIFT(420),
    },
    [420] = {
        [ts_sym_expression] = SHIFT(421),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [421] = {
        [ts_aux_sym_object_repeat0] = SHIFT(422),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [422] = {
        [ts_aux_sym_token1] = SHIFT(423),
    },
    [423] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
    },
    [424] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
    },
    [425] = {
        [ts_sym_expression] = SHIFT(426),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [426] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(427),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [427] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
    },
    [428] = {
        [ts_sym_expression] = SHIFT(429),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [429] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(400),
        [ts_aux_sym_token22] = SHIFT(400),
        [ts_aux_sym_token23] = SHIFT(400),
        [ts_aux_sym_token24] = SHIFT(400),
        [ts_aux_sym_token25] = SHIFT(400),
        [ts_aux_sym_token26] = SHIFT(400),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
    },
    [430] = {
        [ts_sym_expression] = SHIFT(431),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(412),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [431] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
    },
    [432] = {
        [ts_sym_formal_parameters] = SHIFT(433),
        [ts_sym_identifier] = SHIFT(451),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [433] = {
        [ts_sym_statement_block] = SHIFT(434),
        [ts_aux_sym_token0] = SHIFT(435),
    },
    [434] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
    },
    [435] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(436),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(438),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [436] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(437),
    },
    [437] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [438] = {
        [ts_aux_sym_token1] = SHIFT(437),
    },
    [439] = {
        [ts_sym_expression] = SHIFT(440),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(443),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(450),
    },
    [440] = {
        [ts_aux_sym_array_repeat0] = SHIFT(441),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [441] = {
        [ts_aux_sym_token34] = SHIFT(442),
    },
    [442] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
    },
    [443] = {
        [ts_aux_sym_array_repeat0] = SHIFT(441),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [444] = {
        [ts_sym_expression] = SHIFT(445),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(448),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(449),
    },
    [445] = {
        [ts_aux_sym_array_repeat0] = SHIFT(446),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [446] = {
        [ts_aux_sym_token34] = SHIFT(447),
    },
    [447] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_array, 4),
    },
    [448] = {
        [ts_aux_sym_array_repeat0] = SHIFT(446),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [449] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_array, 2),
    },
    [450] = {
        [ts_sym__terminator] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
    },
    [451] = {
        [ts_sym_formal_parameters] = SHIFT(452),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [452] = {
        [ts_sym_statement_block] = SHIFT(453),
        [ts_aux_sym_token0] = SHIFT(435),
    },
    [453] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
    },
    [454] = {
        [ts_sym_identifier] = SHIFT(455),
        [ts_aux_sym_token4] = SHIFT(461),
    },
    [455] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(456),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(458),
    },
    [456] = {
        [ts_aux_sym_token4] = SHIFT(457),
    },
    [457] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [458] = {
        [ts_sym_identifier] = SHIFT(459),
    },
    [459] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(460),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(458),
    },
    [460] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [461] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [462] = {
        [ts_sym_expression] = SHIFT(463),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(466),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(467),
    },
    [463] = {
        [ts_aux_sym_array_repeat0] = SHIFT(464),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [464] = {
        [ts_aux_sym_token34] = SHIFT(465),
    },
    [465] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
    },
    [466] = {
        [ts_aux_sym_array_repeat0] = SHIFT(464),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [467] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
    },
    [468] = {
        [ts_sym_expression] = SHIFT(469),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [469] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [470] = {
        [ts_sym_expression] = SHIFT(471),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [471] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [472] = {
        [ts_sym_expression] = SHIFT(473),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [473] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [474] = {
        [ts_sym_expression] = SHIFT(475),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [475] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [476] = {
        [ts_sym_expression] = SHIFT(477),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [477] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [478] = {
        [ts_sym_expression] = SHIFT(479),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [479] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(480),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [480] = {
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [481] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [482] = {
        [ts_sym_identifier] = SHIFT(483),
    },
    [483] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 3),
    },
    [484] = {
        [ts_sym_expression] = SHIFT(485),
        [ts_sym_math_op] = SHIFT(118),
        [ts_sym_bool_op] = SHIFT(118),
        [ts_sym_ternary] = SHIFT(118),
        [ts_sym_assignment] = SHIFT(118),
        [ts_sym_function_expression] = SHIFT(118),
        [ts_sym_function_call] = SHIFT(118),
        [ts_sym_property_access] = SHIFT(119),
        [ts_sym_object] = SHIFT(118),
        [ts_sym_array] = SHIFT(118),
        [ts_sym_regex] = SHIFT(118),
        [ts_sym_string] = SHIFT(118),
        [ts_sym_identifier] = SHIFT(119),
        [ts_sym_number] = SHIFT(118),
        [ts_sym_null] = SHIFT(118),
        [ts_sym_true] = SHIFT(118),
        [ts_sym_false] = SHIFT(118),
        [ts_aux_sym_token0] = SHIFT(122),
        [ts_aux_sym_token3] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(172),
        [ts_aux_sym_token16] = SHIFT(172),
        [ts_aux_sym_token27] = SHIFT(174),
        [ts_aux_sym_token30] = SHIFT(176),
        [ts_aux_sym_token33] = SHIFT(331),
    },
    [485] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(99),
        [ts_aux_sym_token16] = SHIFT(99),
        [ts_aux_sym_token17] = SHIFT(101),
        [ts_aux_sym_token18] = SHIFT(101),
        [ts_aux_sym_token19] = SHIFT(103),
        [ts_aux_sym_token20] = SHIFT(105),
        [ts_aux_sym_token21] = SHIFT(107),
        [ts_aux_sym_token22] = SHIFT(107),
        [ts_aux_sym_token23] = SHIFT(107),
        [ts_aux_sym_token24] = SHIFT(107),
        [ts_aux_sym_token25] = SHIFT(107),
        [ts_aux_sym_token26] = SHIFT(107),
        [ts_aux_sym_token28] = SHIFT(109),
        [ts_aux_sym_token32] = SHIFT(113),
        [ts_aux_sym_token33] = SHIFT(115),
        [ts_aux_sym_token34] = SHIFT(486),
    },
    [486] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
    },
    [487] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [488] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(489),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [489] = {
        [ts_sym_expression] = SHIFT(490),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [490] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token15] = SHIFT(468),
        [ts_aux_sym_token16] = SHIFT(468),
        [ts_aux_sym_token17] = SHIFT(470),
        [ts_aux_sym_token18] = SHIFT(470),
        [ts_aux_sym_token19] = SHIFT(472),
        [ts_aux_sym_token20] = SHIFT(474),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = SHIFT(478),
        [ts_aux_sym_token32] = SHIFT(482),
        [ts_aux_sym_token33] = SHIFT(484),
    },
    [491] = {
        [ts_builtin_sym_error] = SHIFT(492),
        [ts_sym_string] = SHIFT(495),
        [ts_sym_identifier] = SHIFT(495),
        [ts_aux_sym_token1] = SHIFT(500),
    },
    [492] = {
        [ts_aux_sym_object_repeat0] = SHIFT(493),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [493] = {
        [ts_aux_sym_token1] = SHIFT(494),
    },
    [494] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 4),
    },
    [495] = {
        [ts_aux_sym_token10] = SHIFT(496),
    },
    [496] = {
        [ts_sym_expression] = SHIFT(497),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [497] = {
        [ts_aux_sym_object_repeat0] = SHIFT(498),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [498] = {
        [ts_aux_sym_token1] = SHIFT(499),
    },
    [499] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
    },
    [500] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
    },
    [501] = {
        [ts_sym_expression] = SHIFT(502),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [502] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(503),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [503] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
    },
    [504] = {
        [ts_sym_expression] = SHIFT(505),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [505] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token21] = SHIFT(476),
        [ts_aux_sym_token22] = SHIFT(476),
        [ts_aux_sym_token23] = SHIFT(476),
        [ts_aux_sym_token24] = SHIFT(476),
        [ts_aux_sym_token25] = SHIFT(476),
        [ts_aux_sym_token26] = SHIFT(476),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 2),
    },
    [506] = {
        [ts_sym_expression] = SHIFT(507),
        [ts_sym_math_op] = SHIFT(487),
        [ts_sym_bool_op] = SHIFT(487),
        [ts_sym_ternary] = SHIFT(487),
        [ts_sym_assignment] = SHIFT(487),
        [ts_sym_function_expression] = SHIFT(487),
        [ts_sym_function_call] = SHIFT(487),
        [ts_sym_property_access] = SHIFT(488),
        [ts_sym_object] = SHIFT(487),
        [ts_sym_array] = SHIFT(487),
        [ts_sym_regex] = SHIFT(487),
        [ts_sym_string] = SHIFT(487),
        [ts_sym_identifier] = SHIFT(488),
        [ts_sym_number] = SHIFT(487),
        [ts_sym_null] = SHIFT(487),
        [ts_sym_true] = SHIFT(487),
        [ts_sym_false] = SHIFT(487),
        [ts_aux_sym_token0] = SHIFT(491),
        [ts_aux_sym_token3] = SHIFT(501),
        [ts_aux_sym_token15] = SHIFT(504),
        [ts_aux_sym_token16] = SHIFT(504),
        [ts_aux_sym_token27] = SHIFT(506),
        [ts_aux_sym_token30] = SHIFT(508),
        [ts_aux_sym_token33] = SHIFT(518),
    },
    [507] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 2),
    },
    [508] = {
        [ts_sym_formal_parameters] = SHIFT(509),
        [ts_sym_identifier] = SHIFT(515),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [509] = {
        [ts_sym_statement_block] = SHIFT(510),
        [ts_aux_sym_token0] = SHIFT(511),
    },
    [510] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 3),
    },
    [511] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(512),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(514),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [512] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(513),
    },
    [513] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [514] = {
        [ts_aux_sym_token1] = SHIFT(513),
    },
    [515] = {
        [ts_sym_formal_parameters] = SHIFT(516),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [516] = {
        [ts_sym_statement_block] = SHIFT(517),
        [ts_aux_sym_token0] = SHIFT(511),
    },
    [517] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
    },
    [518] = {
        [ts_sym_expression] = SHIFT(519),
        [ts_sym_math_op] = SHIFT(338),
        [ts_sym_bool_op] = SHIFT(338),
        [ts_sym_ternary] = SHIFT(338),
        [ts_sym_assignment] = SHIFT(338),
        [ts_sym_function_expression] = SHIFT(338),
        [ts_sym_function_call] = SHIFT(338),
        [ts_sym_property_access] = SHIFT(339),
        [ts_sym_object] = SHIFT(338),
        [ts_sym_array] = SHIFT(338),
        [ts_builtin_sym_error] = SHIFT(522),
        [ts_sym_regex] = SHIFT(338),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(339),
        [ts_sym_number] = SHIFT(338),
        [ts_sym_null] = SHIFT(338),
        [ts_sym_true] = SHIFT(338),
        [ts_sym_false] = SHIFT(338),
        [ts_aux_sym_token0] = SHIFT(342),
        [ts_aux_sym_token3] = SHIFT(356),
        [ts_aux_sym_token15] = SHIFT(364),
        [ts_aux_sym_token16] = SHIFT(364),
        [ts_aux_sym_token27] = SHIFT(366),
        [ts_aux_sym_token30] = SHIFT(368),
        [ts_aux_sym_token33] = SHIFT(444),
        [ts_aux_sym_token34] = SHIFT(523),
    },
    [519] = {
        [ts_aux_sym_array_repeat0] = SHIFT(520),
        [ts_aux_sym_token3] = SHIFT(306),
        [ts_aux_sym_token15] = SHIFT(312),
        [ts_aux_sym_token16] = SHIFT(312),
        [ts_aux_sym_token17] = SHIFT(314),
        [ts_aux_sym_token18] = SHIFT(314),
        [ts_aux_sym_token19] = SHIFT(316),
        [ts_aux_sym_token20] = SHIFT(318),
        [ts_aux_sym_token21] = SHIFT(320),
        [ts_aux_sym_token22] = SHIFT(320),
        [ts_aux_sym_token23] = SHIFT(320),
        [ts_aux_sym_token24] = SHIFT(320),
        [ts_aux_sym_token25] = SHIFT(320),
        [ts_aux_sym_token26] = SHIFT(320),
        [ts_aux_sym_token28] = SHIFT(322),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token32] = SHIFT(326),
        [ts_aux_sym_token33] = SHIFT(328),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [520] = {
        [ts_aux_sym_token34] = SHIFT(521),
    },
    [521] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 4),
    },
    [522] = {
        [ts_aux_sym_array_repeat0] = SHIFT(520),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [523] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
    },
    [524] = {
        [ts_sym__terminator] = SHIFT(525),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [525] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [526] = {
        [ts_sym_formal_parameters] = SHIFT(527),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [527] = {
        [ts_sym_statement_block] = SHIFT(528),
        [ts_aux_sym_token0] = SHIFT(386),
    },
    [528] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
    },
    [529] = {
        [ts_sym_formal_parameters] = SHIFT(530),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [530] = {
        [ts_sym_statement_block] = SHIFT(531),
        [ts_aux_sym_token0] = SHIFT(371),
    },
    [531] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_expression, 4),
    },
    [532] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
    },
    [533] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
    },
    [534] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_object, 2),
    },
    [535] = {
        [ts_aux_sym_array_repeat0] = SHIFT(337),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [536] = {
        [ts_aux_sym_array_repeat0] = SHIFT(333),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [537] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_array, 2),
    },
    [538] = {
        [ts_aux_sym_array_repeat0] = SHIFT(304),
        [ts_aux_sym_token31] = SHIFT(335),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [539] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_array, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_array, 2),
    },
    [540] = {
        [ts_sym__terminator] = SHIFT(541),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [541] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [542] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [543] = {
        [ts_sym__terminator] = SHIFT(541),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [544] = {
        [ts_aux_sym_token3] = SHIFT(545),
    },
    [545] = {
        [ts_sym_var_declaration] = SHIFT(546),
        [ts_sym_expression_statement] = SHIFT(546),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token12] = SHIFT(630),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [546] = {
        [ts_sym_expression_statement] = SHIFT(547),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [547] = {
        [ts_sym_expression] = SHIFT(548),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(635),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [548] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(549),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [549] = {
        [ts_sym_statement] = SHIFT(550),
        [ts_sym_statement_block] = SHIFT(283),
        [ts_sym_for_statement] = SHIFT(283),
        [ts_sym_if_statement] = SHIFT(283),
        [ts_sym_switch_statement] = SHIFT(283),
        [ts_sym_break_statement] = SHIFT(283),
        [ts_sym_var_declaration] = SHIFT(283),
        [ts_sym_expression_statement] = SHIFT(283),
        [ts_sym_return_statement] = SHIFT(283),
        [ts_sym_delete_statement] = SHIFT(283),
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(286),
        [ts_sym_comment] = SHIFT(283),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(288),
        [ts_aux_sym_token2] = SHIFT(544),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(551),
        [ts_aux_sym_token7] = SHIFT(558),
        [ts_aux_sym_token11] = SHIFT(568),
        [ts_aux_sym_token12] = SHIFT(570),
        [ts_aux_sym_token13] = SHIFT(574),
        [ts_aux_sym_token14] = SHIFT(578),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [550] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [551] = {
        [ts_aux_sym_token3] = SHIFT(552),
    },
    [552] = {
        [ts_sym_expression] = SHIFT(553),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(634),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [553] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(554),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [554] = {
        [ts_sym_statement] = SHIFT(555),
        [ts_sym_statement_block] = SHIFT(582),
        [ts_sym_for_statement] = SHIFT(582),
        [ts_sym_if_statement] = SHIFT(582),
        [ts_sym_switch_statement] = SHIFT(582),
        [ts_sym_break_statement] = SHIFT(582),
        [ts_sym_var_declaration] = SHIFT(582),
        [ts_sym_expression_statement] = SHIFT(582),
        [ts_sym_return_statement] = SHIFT(582),
        [ts_sym_delete_statement] = SHIFT(582),
        [ts_sym_expression] = SHIFT(583),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(585),
        [ts_sym_comment] = SHIFT(582),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(586),
        [ts_aux_sym_token2] = SHIFT(590),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(597),
        [ts_aux_sym_token7] = SHIFT(604),
        [ts_aux_sym_token11] = SHIFT(612),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token13] = SHIFT(618),
        [ts_aux_sym_token14] = SHIFT(622),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [555] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token6] = SHIFT(556),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [556] = {
        [ts_sym_statement] = SHIFT(557),
        [ts_sym_statement_block] = SHIFT(283),
        [ts_sym_for_statement] = SHIFT(283),
        [ts_sym_if_statement] = SHIFT(283),
        [ts_sym_switch_statement] = SHIFT(283),
        [ts_sym_break_statement] = SHIFT(283),
        [ts_sym_var_declaration] = SHIFT(283),
        [ts_sym_expression_statement] = SHIFT(283),
        [ts_sym_return_statement] = SHIFT(283),
        [ts_sym_delete_statement] = SHIFT(283),
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(286),
        [ts_sym_comment] = SHIFT(283),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(288),
        [ts_aux_sym_token2] = SHIFT(544),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(551),
        [ts_aux_sym_token7] = SHIFT(558),
        [ts_aux_sym_token11] = SHIFT(568),
        [ts_aux_sym_token12] = SHIFT(570),
        [ts_aux_sym_token13] = SHIFT(574),
        [ts_aux_sym_token14] = SHIFT(578),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [557] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [558] = {
        [ts_aux_sym_token3] = SHIFT(559),
    },
    [559] = {
        [ts_sym_expression] = SHIFT(560),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(581),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [560] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(561),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [561] = {
        [ts_aux_sym_token0] = SHIFT(562),
    },
    [562] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(563),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [563] = {
        [ts_aux_sym_token1] = SHIFT(564),
    },
    [564] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [565] = {
        [ts_aux_sym_token10] = SHIFT(566),
    },
    [566] = {
        [ts_sym_statement] = SHIFT(282),
        [ts_sym_statement_block] = SHIFT(283),
        [ts_sym_for_statement] = SHIFT(283),
        [ts_sym_if_statement] = SHIFT(283),
        [ts_sym_switch_statement] = SHIFT(283),
        [ts_sym_break_statement] = SHIFT(283),
        [ts_sym_var_declaration] = SHIFT(283),
        [ts_sym_expression_statement] = SHIFT(283),
        [ts_sym_return_statement] = SHIFT(283),
        [ts_sym_delete_statement] = SHIFT(283),
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(286),
        [ts_sym_comment] = SHIFT(283),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(567),
        [ts_aux_sym_token0] = SHIFT(288),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(544),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(551),
        [ts_aux_sym_token7] = SHIFT(558),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(568),
        [ts_aux_sym_token12] = SHIFT(570),
        [ts_aux_sym_token13] = SHIFT(574),
        [ts_aux_sym_token14] = SHIFT(578),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [567] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_case, 3),
    },
    [568] = {
        [ts_sym__terminator] = SHIFT(569),
    },
    [569] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [570] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(571),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(573),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [571] = {
        [ts_sym__terminator] = SHIFT(572),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [572] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [573] = {
        [ts_sym__terminator] = SHIFT(572),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [574] = {
        [ts_sym_expression] = SHIFT(575),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym__terminator] = SHIFT(577),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [575] = {
        [ts_sym__terminator] = SHIFT(576),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [576] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [577] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [578] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(579),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [579] = {
        [ts_sym__terminator] = SHIFT(580),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [580] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [581] = {
        [ts_aux_sym_token4] = SHIFT(561),
    },
    [582] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [583] = {
        [ts_sym__terminator] = SHIFT(584),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [584] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [585] = {
        [ts_sym__terminator] = SHIFT(584),
    },
    [586] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(587),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(589),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [587] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(588),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [588] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [589] = {
        [ts_aux_sym_token1] = SHIFT(588),
    },
    [590] = {
        [ts_aux_sym_token3] = SHIFT(591),
    },
    [591] = {
        [ts_sym_var_declaration] = SHIFT(592),
        [ts_sym_expression_statement] = SHIFT(592),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token12] = SHIFT(630),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [592] = {
        [ts_sym_expression_statement] = SHIFT(593),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [593] = {
        [ts_sym_expression] = SHIFT(594),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(626),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [594] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(595),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [595] = {
        [ts_sym_statement] = SHIFT(596),
        [ts_sym_statement_block] = SHIFT(582),
        [ts_sym_for_statement] = SHIFT(582),
        [ts_sym_if_statement] = SHIFT(582),
        [ts_sym_switch_statement] = SHIFT(582),
        [ts_sym_break_statement] = SHIFT(582),
        [ts_sym_var_declaration] = SHIFT(582),
        [ts_sym_expression_statement] = SHIFT(582),
        [ts_sym_return_statement] = SHIFT(582),
        [ts_sym_delete_statement] = SHIFT(582),
        [ts_sym_expression] = SHIFT(583),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(585),
        [ts_sym_comment] = SHIFT(582),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(586),
        [ts_aux_sym_token2] = SHIFT(590),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(597),
        [ts_aux_sym_token7] = SHIFT(604),
        [ts_aux_sym_token11] = SHIFT(612),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token13] = SHIFT(618),
        [ts_aux_sym_token14] = SHIFT(622),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [596] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token8] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [597] = {
        [ts_aux_sym_token3] = SHIFT(598),
    },
    [598] = {
        [ts_sym_expression] = SHIFT(599),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(625),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [599] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(600),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [600] = {
        [ts_sym_statement] = SHIFT(601),
        [ts_sym_statement_block] = SHIFT(582),
        [ts_sym_for_statement] = SHIFT(582),
        [ts_sym_if_statement] = SHIFT(582),
        [ts_sym_switch_statement] = SHIFT(582),
        [ts_sym_break_statement] = SHIFT(582),
        [ts_sym_var_declaration] = SHIFT(582),
        [ts_sym_expression_statement] = SHIFT(582),
        [ts_sym_return_statement] = SHIFT(582),
        [ts_sym_delete_statement] = SHIFT(582),
        [ts_sym_expression] = SHIFT(583),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(585),
        [ts_sym_comment] = SHIFT(582),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(586),
        [ts_aux_sym_token2] = SHIFT(590),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(597),
        [ts_aux_sym_token7] = SHIFT(604),
        [ts_aux_sym_token11] = SHIFT(612),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token13] = SHIFT(618),
        [ts_aux_sym_token14] = SHIFT(622),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [601] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token6] = SHIFT(602),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [602] = {
        [ts_sym_statement] = SHIFT(603),
        [ts_sym_statement_block] = SHIFT(582),
        [ts_sym_for_statement] = SHIFT(582),
        [ts_sym_if_statement] = SHIFT(582),
        [ts_sym_switch_statement] = SHIFT(582),
        [ts_sym_break_statement] = SHIFT(582),
        [ts_sym_var_declaration] = SHIFT(582),
        [ts_sym_expression_statement] = SHIFT(582),
        [ts_sym_return_statement] = SHIFT(582),
        [ts_sym_delete_statement] = SHIFT(582),
        [ts_sym_expression] = SHIFT(583),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(585),
        [ts_sym_comment] = SHIFT(582),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(586),
        [ts_aux_sym_token2] = SHIFT(590),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(597),
        [ts_aux_sym_token7] = SHIFT(604),
        [ts_aux_sym_token11] = SHIFT(612),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token13] = SHIFT(618),
        [ts_aux_sym_token14] = SHIFT(622),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [603] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [604] = {
        [ts_aux_sym_token3] = SHIFT(605),
    },
    [605] = {
        [ts_sym_expression] = SHIFT(606),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(611),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [606] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(607),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [607] = {
        [ts_aux_sym_token0] = SHIFT(608),
    },
    [608] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(609),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [609] = {
        [ts_aux_sym_token1] = SHIFT(610),
    },
    [610] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [611] = {
        [ts_aux_sym_token4] = SHIFT(607),
    },
    [612] = {
        [ts_sym__terminator] = SHIFT(613),
    },
    [613] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [614] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(615),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(617),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [615] = {
        [ts_sym__terminator] = SHIFT(616),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [616] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [617] = {
        [ts_sym__terminator] = SHIFT(616),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [618] = {
        [ts_sym_expression] = SHIFT(619),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym__terminator] = SHIFT(621),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [619] = {
        [ts_sym__terminator] = SHIFT(620),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [620] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [621] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [622] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(623),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [623] = {
        [ts_sym__terminator] = SHIFT(624),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [624] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [625] = {
        [ts_aux_sym_token4] = SHIFT(600),
    },
    [626] = {
        [ts_aux_sym_token4] = SHIFT(595),
    },
    [627] = {
        [ts_sym__terminator] = SHIFT(628),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [628] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [629] = {
        [ts_sym__terminator] = SHIFT(628),
    },
    [630] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(631),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(633),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [631] = {
        [ts_sym__terminator] = SHIFT(632),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [632] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [633] = {
        [ts_sym__terminator] = SHIFT(632),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [634] = {
        [ts_aux_sym_token4] = SHIFT(554),
    },
    [635] = {
        [ts_aux_sym_token4] = SHIFT(549),
    },
    [636] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_case, 4),
    },
    [637] = {
        [ts_aux_sym_token1] = SHIFT(638),
    },
    [638] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [639] = {
        [ts_aux_sym_token4] = SHIFT(275),
    },
    [640] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [641] = {
        [ts_sym__terminator] = SHIFT(642),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [642] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [643] = {
        [ts_sym__terminator] = SHIFT(642),
    },
    [644] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(645),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(647),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [645] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(646),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [646] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [647] = {
        [ts_aux_sym_token1] = SHIFT(646),
    },
    [648] = {
        [ts_aux_sym_token3] = SHIFT(649),
    },
    [649] = {
        [ts_sym_var_declaration] = SHIFT(650),
        [ts_sym_expression_statement] = SHIFT(650),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token12] = SHIFT(630),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [650] = {
        [ts_sym_expression_statement] = SHIFT(651),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [651] = {
        [ts_sym_expression] = SHIFT(652),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(684),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [652] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(653),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [653] = {
        [ts_sym_statement] = SHIFT(654),
        [ts_sym_statement_block] = SHIFT(640),
        [ts_sym_for_statement] = SHIFT(640),
        [ts_sym_if_statement] = SHIFT(640),
        [ts_sym_switch_statement] = SHIFT(640),
        [ts_sym_break_statement] = SHIFT(640),
        [ts_sym_var_declaration] = SHIFT(640),
        [ts_sym_expression_statement] = SHIFT(640),
        [ts_sym_return_statement] = SHIFT(640),
        [ts_sym_delete_statement] = SHIFT(640),
        [ts_sym_expression] = SHIFT(641),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(643),
        [ts_sym_comment] = SHIFT(640),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(644),
        [ts_aux_sym_token2] = SHIFT(648),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(655),
        [ts_aux_sym_token7] = SHIFT(662),
        [ts_aux_sym_token11] = SHIFT(670),
        [ts_aux_sym_token12] = SHIFT(672),
        [ts_aux_sym_token13] = SHIFT(676),
        [ts_aux_sym_token14] = SHIFT(680),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [654] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [655] = {
        [ts_aux_sym_token3] = SHIFT(656),
    },
    [656] = {
        [ts_sym_expression] = SHIFT(657),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(683),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [657] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(658),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [658] = {
        [ts_sym_statement] = SHIFT(659),
        [ts_sym_statement_block] = SHIFT(640),
        [ts_sym_for_statement] = SHIFT(640),
        [ts_sym_if_statement] = SHIFT(640),
        [ts_sym_switch_statement] = SHIFT(640),
        [ts_sym_break_statement] = SHIFT(640),
        [ts_sym_var_declaration] = SHIFT(640),
        [ts_sym_expression_statement] = SHIFT(640),
        [ts_sym_return_statement] = SHIFT(640),
        [ts_sym_delete_statement] = SHIFT(640),
        [ts_sym_expression] = SHIFT(641),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(643),
        [ts_sym_comment] = SHIFT(640),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(644),
        [ts_aux_sym_token2] = SHIFT(648),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(655),
        [ts_aux_sym_token7] = SHIFT(662),
        [ts_aux_sym_token11] = SHIFT(670),
        [ts_aux_sym_token12] = SHIFT(672),
        [ts_aux_sym_token13] = SHIFT(676),
        [ts_aux_sym_token14] = SHIFT(680),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [659] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token6] = SHIFT(660),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [660] = {
        [ts_sym_statement] = SHIFT(661),
        [ts_sym_statement_block] = SHIFT(640),
        [ts_sym_for_statement] = SHIFT(640),
        [ts_sym_if_statement] = SHIFT(640),
        [ts_sym_switch_statement] = SHIFT(640),
        [ts_sym_break_statement] = SHIFT(640),
        [ts_sym_var_declaration] = SHIFT(640),
        [ts_sym_expression_statement] = SHIFT(640),
        [ts_sym_return_statement] = SHIFT(640),
        [ts_sym_delete_statement] = SHIFT(640),
        [ts_sym_expression] = SHIFT(641),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(643),
        [ts_sym_comment] = SHIFT(640),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(644),
        [ts_aux_sym_token2] = SHIFT(648),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(655),
        [ts_aux_sym_token7] = SHIFT(662),
        [ts_aux_sym_token11] = SHIFT(670),
        [ts_aux_sym_token12] = SHIFT(672),
        [ts_aux_sym_token13] = SHIFT(676),
        [ts_aux_sym_token14] = SHIFT(680),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [661] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [662] = {
        [ts_aux_sym_token3] = SHIFT(663),
    },
    [663] = {
        [ts_sym_expression] = SHIFT(664),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(669),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [664] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(665),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [665] = {
        [ts_aux_sym_token0] = SHIFT(666),
    },
    [666] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(667),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [667] = {
        [ts_aux_sym_token1] = SHIFT(668),
    },
    [668] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [669] = {
        [ts_aux_sym_token4] = SHIFT(665),
    },
    [670] = {
        [ts_sym__terminator] = SHIFT(671),
    },
    [671] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [672] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(673),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(675),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [673] = {
        [ts_sym__terminator] = SHIFT(674),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [674] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [675] = {
        [ts_sym__terminator] = SHIFT(674),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [676] = {
        [ts_sym_expression] = SHIFT(677),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym__terminator] = SHIFT(679),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [677] = {
        [ts_sym__terminator] = SHIFT(678),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [678] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [679] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [680] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(681),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [681] = {
        [ts_sym__terminator] = SHIFT(682),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [682] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [683] = {
        [ts_aux_sym_token4] = SHIFT(658),
    },
    [684] = {
        [ts_aux_sym_token4] = SHIFT(653),
    },
    [685] = {
        [ts_aux_sym_token4] = SHIFT(268),
    },
    [686] = {
        [ts_sym_formal_parameters] = SHIFT(687),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [687] = {
        [ts_sym_statement_block] = SHIFT(688),
        [ts_aux_sym_token0] = SHIFT(261),
    },
    [688] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
    },
    [689] = {
        [ts_aux_sym_token4] = SHIFT(245),
    },
    [690] = {
        [ts_sym_formal_parameters] = SHIFT(691),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [691] = {
        [ts_sym_statement_block] = SHIFT(692),
        [ts_aux_sym_token0] = SHIFT(229),
    },
    [692] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
    },
    [693] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
    },
    [694] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
    },
    [695] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(696),
    },
    [696] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_statement_block, 3),
    },
    [697] = {
        [ts_aux_sym_token1] = SHIFT(696),
    },
    [698] = {
        [ts_sym_formal_parameters] = SHIFT(699),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [699] = {
        [ts_sym_statement_block] = SHIFT(700),
        [ts_aux_sym_token0] = SHIFT(179),
    },
    [700] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_expression, 4),
    },
    [701] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token34] = REDUCE(ts_sym_object, 2),
    },
    [702] = {
        [ts_sym__terminator] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
    },
    [703] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [704] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_token1] = SHIFT(705),
    },
    [705] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [706] = {
        [ts_aux_sym_token1] = SHIFT(705),
    },
    [707] = {
        [ts_sym_formal_parameters] = SHIFT(708),
        [ts_aux_sym_token3] = SHIFT(454),
    },
    [708] = {
        [ts_sym_statement_block] = SHIFT(709),
        [ts_aux_sym_token0] = SHIFT(76),
    },
    [709] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_expression, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_expression, 4),
    },
    [710] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 3),
    },
    [711] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
    },
    [712] = {
        [ts_aux_sym_token10] = SHIFT(713),
    },
    [713] = {
        [ts_sym_expression] = SHIFT(714),
        [ts_sym_math_op] = SHIFT(193),
        [ts_sym_bool_op] = SHIFT(193),
        [ts_sym_ternary] = SHIFT(193),
        [ts_sym_assignment] = SHIFT(193),
        [ts_sym_function_expression] = SHIFT(193),
        [ts_sym_function_call] = SHIFT(193),
        [ts_sym_property_access] = SHIFT(194),
        [ts_sym_object] = SHIFT(193),
        [ts_sym_array] = SHIFT(193),
        [ts_sym_regex] = SHIFT(193),
        [ts_sym_string] = SHIFT(193),
        [ts_sym_identifier] = SHIFT(194),
        [ts_sym_number] = SHIFT(193),
        [ts_sym_null] = SHIFT(193),
        [ts_sym_true] = SHIFT(193),
        [ts_sym_false] = SHIFT(193),
        [ts_aux_sym_token0] = SHIFT(197),
        [ts_aux_sym_token3] = SHIFT(206),
        [ts_aux_sym_token15] = SHIFT(222),
        [ts_aux_sym_token16] = SHIFT(222),
        [ts_aux_sym_token27] = SHIFT(224),
        [ts_aux_sym_token30] = SHIFT(226),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [714] = {
        [ts_aux_sym_object_repeat0] = SHIFT(715),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(131),
        [ts_aux_sym_token16] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(133),
        [ts_aux_sym_token18] = SHIFT(133),
        [ts_aux_sym_token19] = SHIFT(135),
        [ts_aux_sym_token20] = SHIFT(137),
        [ts_aux_sym_token21] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(139),
        [ts_aux_sym_token23] = SHIFT(139),
        [ts_aux_sym_token24] = SHIFT(139),
        [ts_aux_sym_token25] = SHIFT(139),
        [ts_aux_sym_token26] = SHIFT(139),
        [ts_aux_sym_token28] = SHIFT(141),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(145),
        [ts_aux_sym_token33] = SHIFT(147),
    },
    [715] = {
        [ts_aux_sym_token1] = SHIFT(716),
    },
    [716] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 6),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 6),
    },
    [717] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token19] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token24] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token25] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token26] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token28] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token31] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token32] = REDUCE(ts_sym_object, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_object, 2),
    },
    [718] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(39),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [719] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_function_call, 3),
    },
    [720] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token15] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token16] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token17] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token18] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token19] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token21] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token22] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token23] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token24] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token25] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token26] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token28] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token29] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token31] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token32] = REDUCE(ts_sym_property_access, 4),
        [ts_aux_sym_token33] = REDUCE(ts_sym_property_access, 4),
    },
    [721] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(32),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [722] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(28),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [723] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
    },
    [724] = {
        [ts_sym_expression] = SHIFT(725),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(69),
        [ts_aux_sym_token16] = SHIFT(69),
        [ts_aux_sym_token27] = SHIFT(71),
        [ts_aux_sym_token30] = SHIFT(73),
        [ts_aux_sym_token33] = SHIFT(302),
    },
    [725] = {
        [ts_aux_sym_token3] = SHIFT(10),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = SHIFT(16),
        [ts_aux_sym_token18] = SHIFT(16),
        [ts_aux_sym_token19] = SHIFT(18),
        [ts_aux_sym_token20] = SHIFT(20),
        [ts_aux_sym_token21] = SHIFT(22),
        [ts_aux_sym_token22] = SHIFT(22),
        [ts_aux_sym_token23] = SHIFT(22),
        [ts_aux_sym_token24] = SHIFT(22),
        [ts_aux_sym_token25] = SHIFT(22),
        [ts_aux_sym_token26] = SHIFT(22),
        [ts_aux_sym_token28] = SHIFT(24),
        [ts_aux_sym_token31] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token32] = SHIFT(33),
        [ts_aux_sym_token33] = SHIFT(35),
    },
    [726] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [727] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
    },
    [728] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [729] = {
        [ts_sym__terminator] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token24] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token25] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token26] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token28] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_function_call, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_function_call, 3),
    },
    [730] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [731] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [732] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(733),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(735),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [733] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(734),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [734] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [735] = {
        [ts_aux_sym_token1] = SHIFT(734),
    },
    [736] = {
        [ts_aux_sym_token3] = SHIFT(737),
    },
    [737] = {
        [ts_sym_var_declaration] = SHIFT(738),
        [ts_sym_expression_statement] = SHIFT(738),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token12] = SHIFT(630),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [738] = {
        [ts_sym_expression_statement] = SHIFT(739),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [739] = {
        [ts_sym_expression] = SHIFT(740),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(817),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [740] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(741),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [741] = {
        [ts_sym_statement] = SHIFT(742),
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
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(730),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(732),
        [ts_aux_sym_token2] = SHIFT(736),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(743),
        [ts_aux_sym_token7] = SHIFT(750),
        [ts_aux_sym_token11] = SHIFT(758),
        [ts_aux_sym_token12] = SHIFT(760),
        [ts_aux_sym_token13] = SHIFT(764),
        [ts_aux_sym_token14] = SHIFT(768),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [742] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [743] = {
        [ts_aux_sym_token3] = SHIFT(744),
    },
    [744] = {
        [ts_sym_expression] = SHIFT(745),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(816),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [745] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(746),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [746] = {
        [ts_sym_statement] = SHIFT(747),
        [ts_sym_statement_block] = SHIFT(771),
        [ts_sym_for_statement] = SHIFT(771),
        [ts_sym_if_statement] = SHIFT(771),
        [ts_sym_switch_statement] = SHIFT(771),
        [ts_sym_break_statement] = SHIFT(771),
        [ts_sym_var_declaration] = SHIFT(771),
        [ts_sym_expression_statement] = SHIFT(771),
        [ts_sym_return_statement] = SHIFT(771),
        [ts_sym_delete_statement] = SHIFT(771),
        [ts_sym_expression] = SHIFT(772),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(774),
        [ts_sym_comment] = SHIFT(771),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(775),
        [ts_aux_sym_token2] = SHIFT(779),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(786),
        [ts_aux_sym_token7] = SHIFT(793),
        [ts_aux_sym_token11] = SHIFT(801),
        [ts_aux_sym_token12] = SHIFT(803),
        [ts_aux_sym_token13] = SHIFT(807),
        [ts_aux_sym_token14] = SHIFT(811),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [747] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token6] = SHIFT(748),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [748] = {
        [ts_sym_statement] = SHIFT(749),
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
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(730),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(732),
        [ts_aux_sym_token2] = SHIFT(736),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(743),
        [ts_aux_sym_token7] = SHIFT(750),
        [ts_aux_sym_token11] = SHIFT(758),
        [ts_aux_sym_token12] = SHIFT(760),
        [ts_aux_sym_token13] = SHIFT(764),
        [ts_aux_sym_token14] = SHIFT(768),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [749] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [750] = {
        [ts_aux_sym_token3] = SHIFT(751),
    },
    [751] = {
        [ts_sym_expression] = SHIFT(752),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [752] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(753),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [753] = {
        [ts_aux_sym_token0] = SHIFT(754),
    },
    [754] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(755),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [755] = {
        [ts_aux_sym_token1] = SHIFT(756),
    },
    [756] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [757] = {
        [ts_aux_sym_token4] = SHIFT(753),
    },
    [758] = {
        [ts_sym__terminator] = SHIFT(759),
    },
    [759] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [760] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(761),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(763),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [761] = {
        [ts_sym__terminator] = SHIFT(762),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [762] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [763] = {
        [ts_sym__terminator] = SHIFT(762),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [764] = {
        [ts_sym_expression] = SHIFT(765),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym__terminator] = SHIFT(767),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [765] = {
        [ts_sym__terminator] = SHIFT(766),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [766] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [767] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [768] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(769),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [769] = {
        [ts_sym__terminator] = SHIFT(770),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [770] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [771] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = REDUCE(ts_sym_statement, 1),
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [772] = {
        [ts_sym__terminator] = SHIFT(773),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [773] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [774] = {
        [ts_sym__terminator] = SHIFT(773),
    },
    [775] = {
        [ts_sym_statement] = SHIFT(77),
        [ts_sym_statement_block] = SHIFT(78),
        [ts_sym_for_statement] = SHIFT(78),
        [ts_sym_if_statement] = SHIFT(78),
        [ts_sym_switch_statement] = SHIFT(78),
        [ts_sym_break_statement] = SHIFT(78),
        [ts_sym_var_declaration] = SHIFT(78),
        [ts_sym_expression_statement] = SHIFT(78),
        [ts_sym_return_statement] = SHIFT(78),
        [ts_sym_delete_statement] = SHIFT(78),
        [ts_sym_expression] = SHIFT(79),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(776),
        [ts_sym_comment] = SHIFT(78),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(236),
        [ts_sym_identifier] = SHIFT(237),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(778),
        [ts_aux_sym_token0] = SHIFT(233),
        [ts_aux_sym_token1] = SHIFT(239),
        [ts_aux_sym_token2] = SHIFT(240),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(265),
        [ts_aux_sym_token7] = SHIFT(272),
        [ts_aux_sym_token11] = SHIFT(292),
        [ts_aux_sym_token12] = SHIFT(294),
        [ts_aux_sym_token13] = SHIFT(375),
        [ts_aux_sym_token14] = SHIFT(390),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [776] = {
        [ts_sym__terminator] = SHIFT(80),
        [ts_aux_sym_object_repeat0] = SHIFT(186),
        [ts_aux_sym_token1] = SHIFT(777),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [777] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_statement_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_comment] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [778] = {
        [ts_aux_sym_token1] = SHIFT(777),
    },
    [779] = {
        [ts_aux_sym_token3] = SHIFT(780),
    },
    [780] = {
        [ts_sym_var_declaration] = SHIFT(781),
        [ts_sym_expression_statement] = SHIFT(781),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token12] = SHIFT(630),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [781] = {
        [ts_sym_expression_statement] = SHIFT(782),
        [ts_sym_expression] = SHIFT(627),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [782] = {
        [ts_sym_expression] = SHIFT(783),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(815),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [783] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(784),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [784] = {
        [ts_sym_statement] = SHIFT(785),
        [ts_sym_statement_block] = SHIFT(771),
        [ts_sym_for_statement] = SHIFT(771),
        [ts_sym_if_statement] = SHIFT(771),
        [ts_sym_switch_statement] = SHIFT(771),
        [ts_sym_break_statement] = SHIFT(771),
        [ts_sym_var_declaration] = SHIFT(771),
        [ts_sym_expression_statement] = SHIFT(771),
        [ts_sym_return_statement] = SHIFT(771),
        [ts_sym_delete_statement] = SHIFT(771),
        [ts_sym_expression] = SHIFT(772),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(774),
        [ts_sym_comment] = SHIFT(771),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(775),
        [ts_aux_sym_token2] = SHIFT(779),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(786),
        [ts_aux_sym_token7] = SHIFT(793),
        [ts_aux_sym_token11] = SHIFT(801),
        [ts_aux_sym_token12] = SHIFT(803),
        [ts_aux_sym_token13] = SHIFT(807),
        [ts_aux_sym_token14] = SHIFT(811),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [785] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_for_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [786] = {
        [ts_aux_sym_token3] = SHIFT(787),
    },
    [787] = {
        [ts_sym_expression] = SHIFT(788),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(814),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [788] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(789),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [789] = {
        [ts_sym_statement] = SHIFT(790),
        [ts_sym_statement_block] = SHIFT(771),
        [ts_sym_for_statement] = SHIFT(771),
        [ts_sym_if_statement] = SHIFT(771),
        [ts_sym_switch_statement] = SHIFT(771),
        [ts_sym_break_statement] = SHIFT(771),
        [ts_sym_var_declaration] = SHIFT(771),
        [ts_sym_expression_statement] = SHIFT(771),
        [ts_sym_return_statement] = SHIFT(771),
        [ts_sym_delete_statement] = SHIFT(771),
        [ts_sym_expression] = SHIFT(772),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(774),
        [ts_sym_comment] = SHIFT(771),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(775),
        [ts_aux_sym_token2] = SHIFT(779),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(786),
        [ts_aux_sym_token7] = SHIFT(793),
        [ts_aux_sym_token11] = SHIFT(801),
        [ts_aux_sym_token12] = SHIFT(803),
        [ts_aux_sym_token13] = SHIFT(807),
        [ts_aux_sym_token14] = SHIFT(811),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [790] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token6] = SHIFT(791),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [791] = {
        [ts_sym_statement] = SHIFT(792),
        [ts_sym_statement_block] = SHIFT(771),
        [ts_sym_for_statement] = SHIFT(771),
        [ts_sym_if_statement] = SHIFT(771),
        [ts_sym_switch_statement] = SHIFT(771),
        [ts_sym_break_statement] = SHIFT(771),
        [ts_sym_var_declaration] = SHIFT(771),
        [ts_sym_expression_statement] = SHIFT(771),
        [ts_sym_return_statement] = SHIFT(771),
        [ts_sym_delete_statement] = SHIFT(771),
        [ts_sym_expression] = SHIFT(772),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_builtin_sym_error] = SHIFT(774),
        [ts_sym_comment] = SHIFT(771),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(775),
        [ts_aux_sym_token2] = SHIFT(779),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token5] = SHIFT(786),
        [ts_aux_sym_token7] = SHIFT(793),
        [ts_aux_sym_token11] = SHIFT(801),
        [ts_aux_sym_token12] = SHIFT(803),
        [ts_aux_sym_token13] = SHIFT(807),
        [ts_aux_sym_token14] = SHIFT(811),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [792] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [793] = {
        [ts_aux_sym_token3] = SHIFT(794),
    },
    [794] = {
        [ts_sym_expression] = SHIFT(795),
        [ts_sym_math_op] = SHIFT(209),
        [ts_sym_bool_op] = SHIFT(209),
        [ts_sym_ternary] = SHIFT(209),
        [ts_sym_assignment] = SHIFT(209),
        [ts_sym_function_expression] = SHIFT(209),
        [ts_sym_function_call] = SHIFT(209),
        [ts_sym_property_access] = SHIFT(210),
        [ts_sym_object] = SHIFT(209),
        [ts_sym_array] = SHIFT(209),
        [ts_builtin_sym_error] = SHIFT(800),
        [ts_sym_regex] = SHIFT(209),
        [ts_sym_string] = SHIFT(209),
        [ts_sym_identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(209),
        [ts_sym_null] = SHIFT(209),
        [ts_sym_true] = SHIFT(209),
        [ts_sym_false] = SHIFT(209),
        [ts_aux_sym_token0] = SHIFT(213),
        [ts_aux_sym_token3] = SHIFT(251),
        [ts_aux_sym_token15] = SHIFT(254),
        [ts_aux_sym_token16] = SHIFT(254),
        [ts_aux_sym_token27] = SHIFT(256),
        [ts_aux_sym_token30] = SHIFT(258),
        [ts_aux_sym_token33] = SHIFT(359),
    },
    [795] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(796),
        [ts_aux_sym_token15] = SHIFT(153),
        [ts_aux_sym_token16] = SHIFT(153),
        [ts_aux_sym_token17] = SHIFT(155),
        [ts_aux_sym_token18] = SHIFT(155),
        [ts_aux_sym_token19] = SHIFT(157),
        [ts_aux_sym_token20] = SHIFT(159),
        [ts_aux_sym_token21] = SHIFT(161),
        [ts_aux_sym_token22] = SHIFT(161),
        [ts_aux_sym_token23] = SHIFT(161),
        [ts_aux_sym_token24] = SHIFT(161),
        [ts_aux_sym_token25] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(161),
        [ts_aux_sym_token28] = SHIFT(163),
        [ts_aux_sym_token32] = SHIFT(167),
        [ts_aux_sym_token33] = SHIFT(169),
    },
    [796] = {
        [ts_aux_sym_token0] = SHIFT(797),
    },
    [797] = {
        [ts_sym_switch_case] = SHIFT(277),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(798),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(279),
        [ts_aux_sym_token9] = SHIFT(565),
    },
    [798] = {
        [ts_aux_sym_token1] = SHIFT(799),
    },
    [799] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_switch_statement, 7),
        [ts_builtin_sym_end] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_comment] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_null] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_true] = REDUCE(ts_sym_switch_statement, 7),
        [ts_sym_false] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token3] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token6] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token7] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token11] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token12] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token13] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token14] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token15] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token16] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [800] = {
        [ts_aux_sym_token4] = SHIFT(796),
    },
    [801] = {
        [ts_sym__terminator] = SHIFT(802),
    },
    [802] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_break_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [803] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(804),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(542),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(806),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [804] = {
        [ts_sym__terminator] = SHIFT(805),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [805] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_var_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_comment] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [806] = {
        [ts_sym__terminator] = SHIFT(805),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(182),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [807] = {
        [ts_sym_expression] = SHIFT(808),
        [ts_sym_math_op] = SHIFT(180),
        [ts_sym_bool_op] = SHIFT(180),
        [ts_sym_ternary] = SHIFT(180),
        [ts_sym_assignment] = SHIFT(180),
        [ts_sym_function_expression] = SHIFT(180),
        [ts_sym_function_call] = SHIFT(180),
        [ts_sym_property_access] = SHIFT(181),
        [ts_sym_object] = SHIFT(180),
        [ts_sym_array] = SHIFT(180),
        [ts_sym__terminator] = SHIFT(810),
        [ts_sym_regex] = SHIFT(180),
        [ts_sym_string] = SHIFT(180),
        [ts_sym_identifier] = SHIFT(181),
        [ts_sym_number] = SHIFT(180),
        [ts_sym_null] = SHIFT(180),
        [ts_sym_true] = SHIFT(180),
        [ts_sym_false] = SHIFT(180),
        [ts_aux_sym_token0] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(248),
        [ts_aux_sym_token15] = SHIFT(379),
        [ts_aux_sym_token16] = SHIFT(379),
        [ts_aux_sym_token27] = SHIFT(381),
        [ts_aux_sym_token30] = SHIFT(383),
        [ts_aux_sym_token33] = SHIFT(439),
    },
    [808] = {
        [ts_sym__terminator] = SHIFT(809),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(81),
        [ts_aux_sym_token16] = SHIFT(81),
        [ts_aux_sym_token17] = SHIFT(83),
        [ts_aux_sym_token18] = SHIFT(83),
        [ts_aux_sym_token19] = SHIFT(85),
        [ts_aux_sym_token20] = SHIFT(87),
        [ts_aux_sym_token21] = SHIFT(89),
        [ts_aux_sym_token22] = SHIFT(89),
        [ts_aux_sym_token23] = SHIFT(89),
        [ts_aux_sym_token24] = SHIFT(89),
        [ts_aux_sym_token25] = SHIFT(89),
        [ts_aux_sym_token26] = SHIFT(89),
        [ts_aux_sym_token28] = SHIFT(91),
        [ts_aux_sym_token32] = SHIFT(95),
        [ts_aux_sym_token33] = SHIFT(97),
    },
    [809] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [810] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_return_statement, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token3] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token6] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [811] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(411),
        [ts_sym_bool_op] = SHIFT(411),
        [ts_sym_ternary] = SHIFT(411),
        [ts_sym_assignment] = SHIFT(411),
        [ts_sym_function_expression] = SHIFT(411),
        [ts_sym_function_call] = SHIFT(411),
        [ts_sym_property_access] = SHIFT(812),
        [ts_sym_object] = SHIFT(411),
        [ts_sym_array] = SHIFT(411),
        [ts_sym_regex] = SHIFT(411),
        [ts_sym_string] = SHIFT(411),
        [ts_sym_identifier] = SHIFT(412),
        [ts_sym_number] = SHIFT(411),
        [ts_sym_null] = SHIFT(411),
        [ts_sym_true] = SHIFT(411),
        [ts_sym_false] = SHIFT(411),
        [ts_aux_sym_token0] = SHIFT(415),
        [ts_aux_sym_token3] = SHIFT(425),
        [ts_aux_sym_token15] = SHIFT(428),
        [ts_aux_sym_token16] = SHIFT(428),
        [ts_aux_sym_token27] = SHIFT(430),
        [ts_aux_sym_token30] = SHIFT(432),
        [ts_aux_sym_token33] = SHIFT(462),
    },
    [812] = {
        [ts_sym__terminator] = SHIFT(813),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token26] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token28] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token29] = SHIFT(413),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [813] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_delete_statement, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_comment] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_null] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_true] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_false] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [814] = {
        [ts_aux_sym_token4] = SHIFT(789),
    },
    [815] = {
        [ts_aux_sym_token4] = SHIFT(784),
    },
    [816] = {
        [ts_aux_sym_token4] = SHIFT(746),
    },
    [817] = {
        [ts_aux_sym_token4] = SHIFT(741),
    },
    [818] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
